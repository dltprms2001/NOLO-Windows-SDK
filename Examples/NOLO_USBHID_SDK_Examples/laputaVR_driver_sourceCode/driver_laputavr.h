#ifndef DRIVER_LAPUTAVR_H
#define DRIVER_LAPUTAVR_H

#ifdef _MSC_VER
#define _WIN32_WINNT 0x0501
#endif

#include <openvr_driver.h>
#include <vector>
#include <thread>
#include <chrono>
#include <string>
#include "nolo_api.h"
#include "QuaternionHelper/QuaternionHelper.h"
using namespace vr;
using namespace std;
using namespace NOLO;
using namespace QuaternionHelper;

bool g_bExiting = false; // Used for watchdog.
void WatchdogThreadFunction(); // Watchdog callback function for thread.

// keys for use with the settings API
static const char * const k_pch_Laputa_Section = "driver_laputa";
static const char * const k_pch_Laputa_EnableLaputaDriver_Bool = "enable";
static const char * const k_pch_Laputa_SerialNumber_String = "serialNumber";
static const char * const k_pch_Laputa_ModelNumber_String = "modelNumber";
static const char * const k_pch_Laputa_WindowX_Int32 = "windowX";
static const char * const k_pch_Laputa_WindowY_Int32 = "windowY";
static const char * const k_pch_Laputa_WindowWidth_Int32 = "windowWidth";
static const char * const k_pch_Laputa_WindowHeight_Int32 = "windowHeight";
static const char * const k_pch_Laputa_RenderWidth_Int32 = "renderWidth";
static const char * const k_pch_Laputa_RenderHeight_Int32 = "renderHeight";
static const char * const k_pch_Laputa_SecondsFromVsyncToPhotons_Float = "secondsFromVsyncToPhotons";
static const char * const k_pch_Laputa_DisplayFrequency_Float = "displayFrequency";
static const char * const k_pch_Laputa_DisplayMode_Int32 = "displayMode";

class CLaputaDeviceDriver;

#pragma region CClientDriver_Laputa_Declaration
//-----------------------------------------------------------------------------
// Purpose: CClientDriver_Laputa class derived from IClientTrackedDeviceProvider
//-----------------------------------------------------------------------------

class CClientDriver_Laputa : public IClientTrackedDeviceProvider
{
public:
	CClientDriver_Laputa()
		: m_bEnableLaputaDriver(false)
		, m_bInit(false)
	{
		m_eDriverMode = ClientDriverMode_Normal;
		m_pWatchdogThread = nullptr;
	}

	EVRInitError Init(vr::EClientDriverMode eDriverMode, vr::IDriverLog *pDriverLog, vr::IClientDriverHost *pDriverHost, const char *pchUserDriverConfigDir, const char *pchDriverInstallDir);
	void Cleanup();
	bool BIsHmdPresent(const char *pchUserDriverConfigDir);
	EVRInitError SetDisplayId(const char *pchDisplayId) { return VRInitError_None; } // Null doesn't care
	HiddenAreaMesh_t GetHiddenAreaMesh(EVREye eEye, EHiddenAreaMeshType type);
	uint32_t GetMCImage(uint32_t *pImgWidth, uint32_t *pImgHeight, uint32_t *pChannels, void *pDataBuffer, uint32_t unBufferLen) { return 0; }

	void WatchdogWakeUp();
private:
	IClientDriverHost *m_pClientDriverHost;

	bool m_bEnableLaputaDriver;
	bool m_bInit;
	vr::EClientDriverMode m_eDriverMode;
	std::thread *m_pWatchdogThread;
};
CClientDriver_Laputa g_clientDriverLaputa;
#pragma endregion CClientDriver_Laputa_Declaration


#pragma region CServerDriver_Laputa_Declaration
//-----------------------------------------------------------------------------
// Purpose: CServerDriver_Laputa class derived from IServerTrackedDeviceProvider class
//-----------------------------------------------------------------------------
class CServerDriver_Laputa : public IServerTrackedDeviceProvider
{
public:
	CServerDriver_Laputa();
	~CServerDriver_Laputa();
	EVRInitError Init(IDriverLog *pDriverLog, vr::IServerDriverHost *pDriverHost, const char *pchUserDriverConfigDir, const char *pchDriverInstallDir);
	void Cleanup();
	const char * const *GetInterfaceVersions() { return vr::k_InterfaceVersions; }
	uint32_t GetTrackedDeviceCount();
	ITrackedDeviceServerDriver *GetTrackedDeviceDriver(uint32_t unWhich);
	ITrackedDeviceServerDriver* FindTrackedDeviceDriver(const char *pchId);
	void RunFrame();
	bool ShouldBlockStandbyMode() { return false; }
	void EnterStandby() {}
	void LeaveStandby() {}

private:
	CLaputaDeviceDriver *m_pLaputaHmdLatest;
	void *laputa_dev;
	bool m_bEnableLaputaDriver;
};

CServerDriver_Laputa g_serverDriverLaputa;
#pragma endregion CServerDriver_Laputa_Declaration

#pragma region CLaputaDeviceDriver_Declaration
//-----------------------------------------------------------------------------
// Purpose: The device driver class derived from ITrackedDevicesServerDriver and
//			IVRDisplayComponent classes.
//-----------------------------------------------------------------------------
class CLaputaDeviceDriver : public vr::ITrackedDeviceServerDriver, public vr::IVRDisplayComponent
{
public:
	CLaputaDeviceDriver(IServerDriverHost *pDriverHost,void* laputa_dev);
	~CLaputaDeviceDriver();

	EVRInitError Activate(uint32_t unObjectId);
	void Deactivate();
	void EnterStandby() {}
	void PowerOff() {}
	void *GetComponent(const char *pchComponentNameAndVersion);
	void DebugRequest(const char *pchRequest, char *pchResponseBuffer, uint32_t unResponseBufferSize);

	void GetWindowBounds(int32_t *pnX, int32_t *pnY, uint32_t *pnWidth, uint32_t *pnHeight);
	bool IsDisplayOnDesktop();
	bool IsDisplayRealDisplay();
	void GetRecommendedRenderTargetSize(uint32_t *pnWidth, uint32_t *pnHeight);
	void GetEyeOutputViewport(EVREye eEye, uint32_t *pnX, uint32_t *pnY, uint32_t *pnWidth, uint32_t *pnHeight);
	void GetProjectionRaw(EVREye eEye, float *pfLeft, float *pfRight, float *pfTop, float *pfBottom);
	DistortionCoordinates_t ComputeDistortion(EVREye eEye, float fU, float fV);

	DriverPose_t GetPose();
	bool GetBoolTrackedDeviceProperty(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError *pError);
	float GetFloatTrackedDeviceProperty(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError *pError);
	int32_t GetInt32TrackedDeviceProperty(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError *pError);
	uint64_t GetUint64TrackedDeviceProperty(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError *pError);
	vr::HmdMatrix34_t GetMatrix34TrackedDeviceProperty(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError *pError);
	uint32_t GetStringTrackedDeviceProperty(vr::ETrackedDeviceProperty prop, char *pchValue, uint32_t unBufferSize, vr::ETrackedPropertyError *pError);
	std::string GetStringTrackedDeviceProperty(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError *pError);
	void RunFrame();
	void CheckAndSetupScreen();

// NOLO VR driver
public:
	static bool isConnectNolo;
	static bool isTurnAround;
	static bool isRecenter;
	static Vector3 posR;
	static Quaternion rotQ;
	static HMD hmd;
	static void connect_Nolo(void * context);
	static void disconnect_Nolo(void * context);
	static void expandDataNotify(ExpandMsgType type, void * context);
	static void noloDataNotify(NoloData data, void * context);

	// props for recenter yaw
	static bool m_bIsRecenter;
	static HmdQuaternion_t m_qcorr;

private:
	void* laputa_dev;
	IServerDriverHost *m_pServerDriverHost;
	uint32_t m_unObjectId;

	string m_sSerialNumber;
	string m_sModelNumber;

	int32_t m_nWindowX;
	int32_t m_nWindowY;
	int32_t m_nWindowWidth;
	int32_t m_nWindowHeight;
	int32_t m_nRenderWidth;
	int32_t m_nRenderHeight;
	int32_t m_nDisplayMode;
	float m_flSecondsFromVsyncToPhotons;
	float m_flDisplayFrequency;
	float m_flIPD;
	bool m_is_landscape;
};
#pragma endregion CLaputaDeviceDriver_Declaration

#endif
