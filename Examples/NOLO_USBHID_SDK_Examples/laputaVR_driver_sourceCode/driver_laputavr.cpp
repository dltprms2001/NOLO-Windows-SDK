//============ Copyright (c) LaputaVR Corporation, All rights reserved. ============
#include <openvr_driver.h>
#include "driverlog.h"
#include "driver_laputavr.h"
#include <vector>
#include <thread>
#include <chrono>
#include <string>
#include <laputa_usb_exports.h>
#include <laputa_screen.h>

#if defined( _WINDOWS )
#include <Windows.h>
#endif

using namespace vr;
using namespace std;


#if defined(_WIN32)
#define LP_DLL_EXPORT extern "C" __declspec( dllexport )
#define LP_DLL_IMPORT extern "C" __declspec( dllimport )
#elif defined(__GNUC__) || defined(COMPILER_GCC) || defined(__APPLE__)
#define LP_DLL_EXPORT extern "C" __attribute__((visibility("default")))
#define LP_DLL_IMPORT extern "C" 
#else
#error "Unsupported Platform."
#endif

// Initialize quaternion
inline HmdQuaternion_t HmdQuaternion_Init(double w, double x, double y, double z)
{
	HmdQuaternion_t quat;
	quat.w = w;
	quat.x = x;
	quat.y = y;
	quat.z = z;
	return quat;
}

// Set matrix34
inline void HmdMatrix_SetIdentity(HmdMatrix34_t *pMatrix)
{
	pMatrix->m[0][0] = 1.f;
	pMatrix->m[0][1] = 0.f;
	pMatrix->m[0][2] = 0.f;
	pMatrix->m[0][3] = 0.f;
	pMatrix->m[1][0] = 0.f;
	pMatrix->m[1][1] = 1.f;
	pMatrix->m[1][2] = 0.f;
	pMatrix->m[1][3] = 0.f;
	pMatrix->m[2][0] = 0.f;
	pMatrix->m[2][1] = 0.f;
	pMatrix->m[2][2] = 1.f;
	pMatrix->m[2][3] = 0.f;
}

void WatchdogThreadFunction()
{
	while (!g_bExiting)
	{
#if defined( _WINDOWS )
		// on windows send the event when the Y key is pressed.
		if ((0x01 & GetAsyncKeyState('Y')) != 0)
		{
			// Y key was pressed. 
			g_clientDriverLaputa.WatchdogWakeUp();
		}
		std::this_thread::sleep_for(std::chrono::microseconds(500));
#else
		// for the other platforms, just send one every five seconds
		std::this_thread::sleep_for(std::chrono::seconds(5));
		g_clientDriverNull.WatchdogWakeUp();
#endif
	}
}

#pragma region CClientDriver_Laputa_Implemention
EVRInitError CClientDriver_Laputa::Init(vr::EClientDriverMode eDriverMode, vr::IDriverLog * pDriverLog, vr::IClientDriverHost * pDriverHost, const char * pchUserDriverConfigDir, const char * pchDriverInstallDir)
{
	m_pClientDriverHost = pDriverHost;
	InitDriverLog(pDriverLog);

	m_eDriverMode = eDriverMode;

	if (!m_bInit)
	{
		if (m_pClientDriverHost)
		{
			IVRSettings *pSettings = (IVRSettings *)m_pClientDriverHost->GetGenericInterface(IVRSettings_Version);
			//DriverLog("Client::Getting *pSettings...\n");
			if (!m_bEnableLaputaDriver && pSettings)
			{
				//DriverLog("Client:: Getting m_bEnableLaputaDriver...\n");
				m_bEnableLaputaDriver = pSettings->GetBool(k_pch_Laputa_Section, k_pch_Laputa_EnableLaputaDriver_Bool);
				string s;
				if (m_bEnableLaputaDriver)
					s = "True";
				else
					s = "False";
				//DriverLog("Client:: Got m_bEnableLaputaDriver: ",s.c_str(),"\n");
			}
		}
		m_bInit = true;
		DriverLog("Initialize Client Driver successful!\n");
	}

	if (eDriverMode == ClientDriverMode_Watchdog)
	{
		if (!m_bEnableLaputaDriver)
		{
			return VRInitError_Init_LowPowerWatchdogNotSupported;
		}

		// Watchdog mode on Windows starts a thread that listens for the 'Y' key on the keyboard to 
		// be pressed. A real driver should wait for a system button event or something else from the 
		// the hardware that signals that the VR system should start up.

		g_bExiting = false;
		m_pWatchdogThread = new std::thread(WatchdogThreadFunction);
		if (!m_pWatchdogThread)
		{
			DriverLog("Unable to create watchdog thread\n");
			return VRInitError_Driver_Failed;
		}
	}

	return VRInitError_None;
}

void CClientDriver_Laputa::WatchdogWakeUp()
{
	if (m_pClientDriverHost)
		m_pClientDriverHost->WatchdogWakeUp();
}

void CClientDriver_Laputa::Cleanup()
{
	g_bExiting = true;
	if (m_pWatchdogThread)
	{
		m_pWatchdogThread->join();
		delete m_pWatchdogThread;
		m_pWatchdogThread = nullptr;
	}
	CleanupDriverLog();
}

bool CClientDriver_Laputa::BIsHmdPresent(const char *pchUserDriverConfigDir)
{
	// optimistically return true. We'll have a chance to say whether there's actually an HMD later.
	// This should do something quick like look for a USB VID/PID combination that makes it likely
	// there's an HMD attached.
	return true;
}

// ------------------------------------------------------------------------------------------
// Purpose: Return a mesh that contains the hidden area for the current HMD
// ------------------------------------------------------------------------------------------
HiddenAreaMesh_t CClientDriver_Laputa::GetHiddenAreaMesh(EVREye eEye, EHiddenAreaMeshType type)
{
	// Null doesn't do visible area meshes
	vr::HiddenAreaMesh_t mesh;
	mesh.pVertexData = NULL;
	mesh.unTriangleCount = 0;
	return mesh;
}

#pragma endregion


#pragma region CServerDriver_Laputa_Implemention
// Implemention of CServerDriver_Laputa

CServerDriver_Laputa::CServerDriver_Laputa()
	: m_pLaputaHmdLatest(NULL)
	, m_bEnableLaputaDriver(false)
	, laputa_dev(NULL)
{
}

CServerDriver_Laputa::~CServerDriver_Laputa()
{
}

EVRInitError CServerDriver_Laputa::Init(IDriverLog *pDriverLog, IServerDriverHost *pDriverHost, const char *pchUserDriverConfigDir, const char *pchDriverInstallDir)
{
	InitDriverLog(pDriverLog);

	this->laputa_dev = laputa_device_init();
	if (!this->laputa_dev)
	{
		DriverLog("Initialized LaputaVR HMD driver failed!\n");
		m_bEnableLaputaDriver = false;
	}
	else
	{
		DriverLog("Initialized LaputaVR HMD driver successful!\n");
		m_bEnableLaputaDriver = true;
	}

	if (!m_bEnableLaputaDriver)
	{
		DriverLog("Cannot find LaputaVR HMD!\n");
		return VRInitError_Init_HmdNotFound;
	}

	DriverLog("Found LaputaVR HMD!\n");

	m_pLaputaHmdLatest = new CLaputaDeviceDriver(pDriverHost,this->laputa_dev);

	return VRInitError_None;
}

void CServerDriver_Laputa::Cleanup()
{
	CleanupDriverLog();

	close_Nolo_Device();

	if (this->laputa_dev)
		laputa_device_free(this->laputa_dev);

	delete m_pLaputaHmdLatest;
	m_pLaputaHmdLatest = NULL;
}


uint32_t CServerDriver_Laputa::GetTrackedDeviceCount()
{
	if (m_bEnableLaputaDriver)
		return 1;

	return 0;
}

ITrackedDeviceServerDriver *CServerDriver_Laputa::GetTrackedDeviceDriver(uint32_t unWhich)
{
	return m_pLaputaHmdLatest;
}

ITrackedDeviceServerDriver* CServerDriver_Laputa::FindTrackedDeviceDriver(const char *pchId)
{
	return m_pLaputaHmdLatest;
}

void CServerDriver_Laputa::RunFrame()
{
	if (m_pLaputaHmdLatest)
	{
		m_pLaputaHmdLatest->RunFrame();
	}
}

#pragma endregion

#pragma region CLaputaDeviceDriver_Implemention
// Implemention of CLaputaDeviceDriver

bool CLaputaDeviceDriver::isConnectNolo = false;
bool CLaputaDeviceDriver::isTurnAround = false;
HMD CLaputaDeviceDriver::hmd;
Vector3 CLaputaDeviceDriver::posR{ 0,0,0 };
Quaternion CLaputaDeviceDriver::rotQ{ 0,1,0,0 };
bool CLaputaDeviceDriver::m_bIsRecenter = false;
HmdQuaternion_t CLaputaDeviceDriver::m_qcorr{ 1,0,0,0 };
void CLaputaDeviceDriver::connect_Nolo(void * context)
{
	DriverLog("=====================connect NOLO===========================\n");
	isConnectNolo = true;
}
void CLaputaDeviceDriver::disconnect_Nolo(void * context)
{
	DriverLog("=====================disconnect NOLO===========================\n");
	isConnectNolo = false;
}
void CLaputaDeviceDriver::expandDataNotify(ExpandMsgType type, void * context)
{
	static bool bTurn = false;
	if (ExpandMsgType::DoubleClickKeyTurnAround == type) 
	{
		if (!bTurn)
		{
			DriverLog("=====================Trun 180===========================\n");
			isTurnAround = true;
			posR = hmd.HMDPosition;
			bTurn = true;
		}
		else
		{
			isTurnAround = false;
			bTurn = false;
		}
	}
	if (type == ExpandMsgType::DoubleClickSystemRecenter)
	{
		m_bIsRecenter = true;
	}

}
void CLaputaDeviceDriver::noloDataNotify(NoloData data, void * context)
{
	memcpy(&hmd, &data.hmdData, sizeof(hmd));
}

CLaputaDeviceDriver::CLaputaDeviceDriver(IServerDriverHost *pDriverHost, void* laputa_dev)
		: m_pServerDriverHost(pDriverHost)
		, m_unObjectId(vr::k_unTrackedDeviceIndexInvalid)
		, laputa_dev(NULL)
{
	if (!laputa_dev)
	{
		DriverLog("Cannot find LaputaVR devices!");
		return;
	}
	else
	{
		this->laputa_dev = laputa_dev;
	}

	LaputaScreenInfo lp_sc_info;
	int err=LaputaScreen::GetLaputaScreen(&lp_sc_info);
	
	IVRSettings *pSettings = m_pServerDriverHost ? m_pServerDriverHost->GetSettings(vr::IVRSettings_Version) : NULL;
	m_nDisplayMode = pSettings->GetInt32(k_pch_Laputa_Section, k_pch_Laputa_DisplayMode_Int32);
	
	switch (m_nDisplayMode)
	{
	case 0:
		err = GET_SCREEN_SUCC;
		break;
	case 1:
		err=GET_SCREEN_ERR;
		break;
	default:
		break;
	}

	if (err == GET_SCREEN_ERR)
	{
		DriverLog("Could not get LAPUTA VR HMD information. Using default values\n");

		m_flIPD = pSettings->GetFloat(k_pch_SteamVR_Section, k_pch_SteamVR_IPD_Float);

		char buf[1024];
		pSettings->GetString(k_pch_Laputa_Section, k_pch_Laputa_SerialNumber_String, buf, sizeof(buf));
		m_sSerialNumber = buf;

		pSettings->GetString(k_pch_Laputa_Section, k_pch_Laputa_ModelNumber_String, buf, sizeof(buf));
		m_sModelNumber = buf;

		m_nWindowX = pSettings->GetInt32(k_pch_Laputa_Section, k_pch_Laputa_WindowX_Int32);
		m_nWindowY = pSettings->GetInt32(k_pch_Laputa_Section, k_pch_Laputa_WindowY_Int32);
		m_nWindowWidth = pSettings->GetInt32(k_pch_Laputa_Section, k_pch_Laputa_WindowWidth_Int32);
		m_nWindowHeight = pSettings->GetInt32(k_pch_Laputa_Section, k_pch_Laputa_WindowHeight_Int32);
		m_nRenderWidth = pSettings->GetInt32(k_pch_Laputa_Section, k_pch_Laputa_RenderWidth_Int32);
		m_nRenderHeight = pSettings->GetInt32(k_pch_Laputa_Section, k_pch_Laputa_RenderHeight_Int32);
		m_flSecondsFromVsyncToPhotons = pSettings->GetFloat(k_pch_Laputa_Section, k_pch_Laputa_SecondsFromVsyncToPhotons_Float);
		m_flDisplayFrequency = pSettings->GetFloat(k_pch_Laputa_Section, k_pch_Laputa_DisplayFrequency_Float);
		
	}
	else if(err==GET_SCREEN_SUCC)
	{
		m_sSerialNumber = lp_sc_info.vendor_name;
		m_sModelNumber = lp_sc_info.product_sn_name;

		m_nWindowX = lp_sc_info.x_position;
		m_nWindowY = lp_sc_info.y_position;
		m_nWindowWidth = lp_sc_info.width;
		m_nWindowHeight = lp_sc_info.height;
		m_nRenderWidth = lp_sc_info.width;
		m_nRenderHeight = lp_sc_info.height;
		m_flSecondsFromVsyncToPhotons = 0.0;
		m_flDisplayFrequency = (float)lp_sc_info.frequency;
		m_flIPD = 0.065f;
		m_is_landscape = m_nWindowHeight < m_nWindowWidth;
		
		CheckAndSetupScreen();
	}

	DriverLog("Serial Number: %s\n", m_sSerialNumber.c_str());
	DriverLog("Model Number: %s\n", m_sModelNumber.c_str());
	DriverLog("Window: %d %d %d %d\n", m_nWindowX, m_nWindowY, m_nWindowWidth, m_nWindowHeight);
	DriverLog("Render Target: %d %d\n", m_nRenderWidth, m_nRenderHeight);
	DriverLog("Seconds from Vsync to Photons: %f\n", m_flSecondsFromVsyncToPhotons);
	DriverLog("Display Frequency: %f\n", m_flDisplayFrequency);
	DriverLog("IPD: %f\n", m_flIPD);

	// NOLO VR driver
	memset(&posR, 0, sizeof(posR));
	rotQ.w = 0; rotQ.x = 0; rotQ.y = 1; rotQ.z = 0;
}

CLaputaDeviceDriver::~CLaputaDeviceDriver()
{
	m_pServerDriverHost = NULL;
}

EVRInitError CLaputaDeviceDriver::Activate(uint32_t unObjectId)
{
	// NoloVR driver
	registerDisConnectCallBack(disconnect_Nolo, this);
	registerConnectSuccessCallBack(connect_Nolo, this);
	registerExpandDataNotifyCallBack(expandDataNotify, this);
	registerNoloDataNotifyCallBack(noloDataNotify, this);
	search_Nolo_Device();

	m_unObjectId = unObjectId;
	return VRInitError_None;
}

void CLaputaDeviceDriver::Deactivate()
{
	m_unObjectId = vr::k_unTrackedDeviceIndexInvalid;
}

void* CLaputaDeviceDriver::GetComponent(const char *pchComponentNameAndVersion)
{
	if (!_stricmp(pchComponentNameAndVersion, vr::IVRDisplayComponent_Version))
	{
		return (vr::IVRDisplayComponent*)this;
	}

	// override this to add a component to a driver
	return NULL;
}


void CLaputaDeviceDriver::GetWindowBounds(int32_t *pnX, int32_t *pnY, uint32_t *pnWidth, uint32_t *pnHeight)
{
	*pnX = m_nWindowX;
	*pnY = m_nWindowY;
	*pnWidth = m_nWindowWidth;
	*pnHeight = m_nWindowHeight;
}

bool CLaputaDeviceDriver::IsDisplayOnDesktop()
{
	return true;
}

// If return false, the render image will display on the main monitor (computer monitor).
// If return true, the render image will display on the HMD display.
bool CLaputaDeviceDriver::IsDisplayRealDisplay()
{
	return true;
}

void CLaputaDeviceDriver::GetRecommendedRenderTargetSize(uint32_t *pnWidth, uint32_t *pnHeight)
{
	*pnWidth = static_cast<uint32_t>(m_nRenderWidth*1.0);
	*pnHeight = static_cast<uint32_t>(m_nRenderHeight*1.0);
}

/** debug request from a client */
void CLaputaDeviceDriver::DebugRequest(const char *pchRequest, char *pchResponseBuffer, uint32_t unResponseBufferSize)
{
	if (unResponseBufferSize >= 1)
		pchResponseBuffer[0] = 0;
}

// TODO
// - Need to make this function adaptive to screens with different orientations.
void CLaputaDeviceDriver::GetEyeOutputViewport(EVREye eEye, uint32_t *pnX, uint32_t *pnY, uint32_t *pnWidth, uint32_t *pnHeight)
{

	*pnWidth = m_nWindowWidth / 2;
	*pnHeight = m_nWindowHeight;
	// Default screen orientation is landscape.
	if (eEye == Eye_Left)
	{
		*pnX = 0;
		*pnY = 0;
		DriverLog("Eye_Left:: X:%d, Y:%d, Width:%d, Height:%d\n", *pnX, *pnY, *pnWidth,*pnHeight);
	}
	else
	{
		*pnX = m_nWindowWidth / 2;
		*pnY = 0;
		DriverLog("Eye_Right:: X:%d, Y:%d, Width:%d, Height:%d\n", *pnX,*pnY,*pnWidth, *pnHeight);
	}
}

void CLaputaDeviceDriver::GetProjectionRaw(EVREye eEye, float *pfLeft, float *pfRight, float *pfTop, float *pfBottom)
{
	*pfLeft = -1.0;
	*pfRight = 1.0;
	*pfTop = -1.0;
	*pfBottom = 1.0;
}

DistortionCoordinates_t CLaputaDeviceDriver::ComputeDistortion(EVREye eEye, float fU, float fV)
{
	DistortionCoordinates_t coordinates;
	coordinates.rfBlue[0] = fU;
	coordinates.rfBlue[1] = fV;
	coordinates.rfGreen[0] = fU;
	coordinates.rfGreen[1] = fV;
	coordinates.rfRed[0] = fU;
	coordinates.rfRed[1] = fV;
	return coordinates;
}

// Get pose(quaternion) 
DriverPose_t CLaputaDeviceDriver::GetPose()
{
	float q[4] = { 0.0f }; // quatertnion
	laputa_get_quaternion(this->laputa_dev, q);
	
	DriverPose_t pose = { 0 };
	pose.poseTimeOffset = 0;
	pose.poseIsValid = true;
	pose.result = TrackingResult_Running_OK;
	pose.deviceIsConnected = true;
	pose.willDriftInYaw = true;
	pose.shouldApplyHeadModel = false;

	pose.qWorldFromDriverRotation = HmdQuaternion_Init(1, 0, 0, 0);
	pose.qDriverFromHeadRotation = HmdQuaternion_Init(1, 0, 0, 0);

	// NOLO VR driver
	pose.vecWorldFromDriverTranslation[0] = 0;
	pose.vecWorldFromDriverTranslation[1] = 0;
	pose.vecWorldFromDriverTranslation[2] = 0;

	pose.vecDriverFromHeadTranslation[0] = 0.000f;
	pose.vecDriverFromHeadTranslation[1] = 0.007f;
	pose.vecDriverFromHeadTranslation[2] = -0.073f;

	if (isConnectNolo)
	{
		HMD noloHMD = get_Nolo_HMDData();
		memcpy(&noloHMD, &hmd, sizeof(noloHMD));
		
		//==============================================DoubleClickMenu turn 180

		if (isTurnAround)
		{
			Quaternion hmdR;
			hmdR.w = q[0];
			hmdR.x = q[2];
			hmdR.y = q[3];
			hmdR.z = q[1];
			hmdR = rotQ*hmdR;

			noloHMD.HMDPosition.z = 2 * posR.z - noloHMD.HMDPosition.z;
			noloHMD.HMDPosition.x = 2 * posR.x - noloHMD.HMDPosition.x;


			pose.vecPosition[0] = noloHMD.HMDPosition.x;
			pose.vecPosition[1] = noloHMD.HMDPosition.y;
			pose.vecPosition[2] = -noloHMD.HMDPosition.z;

			pose.qRotation.w = hmdR.w;
			pose.qRotation.x = hmdR.x;
			pose.qRotation.y = hmdR.y;
			pose.qRotation.z = hmdR.z;

			// Update hmd quaternion by m_qcorr
			QuaternionRecenter(pose.qRotation, m_qcorr);
		}
		else if (m_bIsRecenter)
		{
			HmdQuaternion_t hmdR;
			hmdR.w = q[0];
			hmdR.x = q[2];
			hmdR.y = q[3];
			hmdR.z = q[1];

			// m_qocrr is used for yaw recenter.
			m_qcorr = GetQuaternionCorr(hmdR);
			m_bIsRecenter = false;
		}
		else
		{
			pose.vecPosition[0] = noloHMD.HMDPosition.x;
			pose.vecPosition[1] = noloHMD.HMDPosition.y;
			pose.vecPosition[2] = -noloHMD.HMDPosition.z;

			pose.qRotation.w = q[0];
			pose.qRotation.x = q[2];
			pose.qRotation.y = q[3];
			pose.qRotation.z = q[1];

			// Update hmd quaternion by m_qcorr
			QuaternionRecenter(pose.qRotation, m_qcorr);
		}

		pose.poseIsValid = !!noloHMD.state;
	}
	else
	{
		pose.qRotation.w = q[0];
		pose.qRotation.x = q[2];
		pose.qRotation.y = q[3];
		pose.qRotation.z = q[1];

		// Update hmd quaternion by m_qcorr
		QuaternionRecenter(pose.qRotation, m_qcorr);
	}

	pose.vecVelocity[0] = 0;
	pose.vecVelocity[1] = 0;
	pose.vecVelocity[2] = 0;

	pose.vecAcceleration[0] = 0;
	pose.vecAcceleration[1] = 0;
	pose.vecAcceleration[2] = 0;

	pose.vecAngularVelocity[0] = 0;
	pose.vecAngularVelocity[1] = 0;
	pose.vecAngularVelocity[2] = 0;

	pose.vecAngularAcceleration[0] = 0;
	pose.vecAngularAcceleration[1] = 0;
	pose.vecAngularAcceleration[2] = 0;

	return pose;
}

bool CLaputaDeviceDriver::GetBoolTrackedDeviceProperty(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError *pError)
{
	*pError = vr::TrackedProp_Success;

	switch (prop)
	{
	case vr::Prop_IsOnDesktop_Bool:
		// If return false, it will avoid "not fullscreen" warnings from vrmonitor
		return true;
	}

	*pError = vr::TrackedProp_ValueNotProvidedByDevice;
	return false;
}

float CLaputaDeviceDriver::GetFloatTrackedDeviceProperty(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError *pError)
{
	vr::ETrackedPropertyError error = vr::TrackedProp_ValueNotProvidedByDevice;
	float fRetVal = 0;
	switch (prop)
	{
	case vr::Prop_UserIpdMeters_Float:
		fRetVal = m_flIPD;
		error = TrackedProp_Success;
		break;

	case vr::Prop_UserHeadToEyeDepthMeters_Float:
		error = vr::TrackedProp_Success;
		fRetVal = 0.f;
		break;

	case vr::Prop_DisplayFrequency_Float:
		error = vr::TrackedProp_Success;
		fRetVal = m_flDisplayFrequency;
		break;

	case vr::Prop_SecondsFromVsyncToPhotons_Float:
		error = vr::TrackedProp_Success;
		fRetVal = m_flSecondsFromVsyncToPhotons;
		break;

	}

	if (pError)
	{
		*pError = error;
	}

	return fRetVal;
}

int32_t CLaputaDeviceDriver::GetInt32TrackedDeviceProperty(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError *pError)
{
	int32_t nRetVal = 0;
	vr::ETrackedPropertyError error = vr::TrackedProp_UnknownProperty;

	switch (prop)
	{
	case vr::Prop_DeviceClass_Int32:
		nRetVal = vr::TrackedDeviceClass_HMD;
		error = vr::TrackedProp_Success;
		break;
	}

	if (pError)
	{
		*pError = error;
	}

	return nRetVal;
}

uint64_t CLaputaDeviceDriver::GetUint64TrackedDeviceProperty(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError *pError)
{
	*pError = vr::TrackedProp_Success;

	switch (prop)
	{
	case vr::Prop_CurrentUniverseId_Uint64:
		// return a constant that's not 0 (invalid) or 1 (reserved for Oculus)
		return 2;
	}

	*pError = vr::TrackedProp_ValueNotProvidedByDevice;
	return 0;
}

HmdMatrix34_t CLaputaDeviceDriver:: GetMatrix34TrackedDeviceProperty(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError *pError)
{
	*pError = vr::TrackedProp_ValueNotProvidedByDevice;
	HmdMatrix34_t matIdentity;
	HmdMatrix_SetIdentity(&matIdentity);
	return matIdentity;
}

uint32_t CLaputaDeviceDriver::GetStringTrackedDeviceProperty(vr::ETrackedDeviceProperty prop, char *pchValue, uint32_t unBufferSize, vr::ETrackedPropertyError *pError)
{
	std::string sValue = GetStringTrackedDeviceProperty(prop, pError);
	if (*pError == vr::TrackedProp_Success)
	{
		if (sValue.size() + 1 > unBufferSize)
		{
			*pError = vr::TrackedProp_BufferTooSmall;
		}
		else
		{
			strcpy_s(pchValue, unBufferSize, sValue.c_str());
		}
		return (uint32_t)sValue.size() + 1;
	}
	return 0;
}

string CLaputaDeviceDriver::GetStringTrackedDeviceProperty(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError *pError)
{
	*pError = vr::TrackedProp_ValueNotProvidedByDevice;
	std::string sRetVal;

	switch (prop)
	{
	case vr::Prop_ModelNumber_String:
		sRetVal = m_sModelNumber;
		*pError = vr::TrackedProp_Success;
		break;

	case vr::Prop_SerialNumber_String:
		sRetVal = m_sSerialNumber;
		*pError = vr::TrackedProp_Success;
		break;
	}

	return sRetVal;
}

void CLaputaDeviceDriver::RunFrame()
{
	// In a real driver, this should happen from some pose tracking thread.
	// The RunFrame interval is unspecified and can be very irregular if some other
	// driver blocks it for some periodic task.
	if (m_unObjectId != vr::k_unTrackedDeviceIndexInvalid)
	{
		m_pServerDriverHost->TrackedDevicePoseUpdated(m_unObjectId, GetPose());
	}
}
#pragma endregion


void CLaputaDeviceDriver::CheckAndSetupScreen()
{
	LaputaScreenInfo lp_sc_info;
	int err = LaputaScreen::GetLaputaScreen(&lp_sc_info);
	if (err == GET_SCREEN_ERR)
	{
		DriverLog("Get LaputaVR HMD display settings failed!\n");
		return;
	}
	if (lp_sc_info.orientation != DMDO_90 || lp_sc_info.orientation != DMDO_DEFAULT)
		err = LaputaScreen::SetLaputaScreenLandscapeFlipped(lp_sc_info);
	else
	{
		DriverLog("The LaputaVR HMD display settings has been set well!\n");
		return;
	}
	if (err != INVALID)
		DriverLog("Set LaputaVR HMD display settings successful!\n");
	else
	{
		DriverLog("Set LaputaVR HMD display settings failed!\n");
		return;
	}
}

//-----------------------------------------------------------------------------
// Purpose: Factory function for steamvr, will be called before any other 
//			functions.
//-----------------------------------------------------------------------------
LP_DLL_EXPORT void *HmdDriverFactory(const char *pInterfaceName, int *pReturnCode)
{
	//system("laputa_screen_test.exe");
	if (0 == strcmp(IServerTrackedDeviceProvider_Version, pInterfaceName))
	{
		return &g_serverDriverLaputa;
	}
	if (0 == strcmp(IClientTrackedDeviceProvider_Version, pInterfaceName))
	{
		return &g_clientDriverLaputa;
	}

	if (pReturnCode)
		*pReturnCode = VRInitError_Init_InterfaceNotFound;

	return NULL;
}