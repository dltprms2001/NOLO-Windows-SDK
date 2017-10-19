#include "HMDDeviceDriver.h"


CHMDDeviceDriver::CHMDDeviceDriver()
{

	memset(&posR, 0, sizeof(posR));
	rotQ.x = 0; rotQ.y = 1; rotQ.z = 0; rotQ.w = 0;
	IsTurnAround = false;

	huaDisplayComponent = createHmdDriver();

	m_unObjectId = vr::k_unTrackedDeviceIndexInvalid;
	m_ulPropertyContainer = vr::k_ulInvalidPropertyContainer;

	DriverLog("Using settings values\n");
	m_flIPD = vr::VRSettings()->GetFloat(k_pch_SteamVR_Section, k_pch_SteamVR_IPD_Float);
	m_sSerialNumber = "1234";
	DriverLog("driver_null: Serial Number: %s\n", m_sSerialNumber.c_str());
	DriverLog("driver_null: IPD: %f\n", m_flIPD);
}


CHMDDeviceDriver::~CHMDDeviceDriver()
{
	huaDisplayComponent = NULL;
}

EVRInitError CHMDDeviceDriver::Activate(vr::TrackedDeviceIndex_t unObjectId)
{

	DriverLog("===============Activate HuaWeiNOLO=========\n");

	m_unObjectId = unObjectId;
	m_ulPropertyContainer = vr::VRProperties()->TrackedDeviceToPropertyContainer(m_unObjectId);

	vr::VRProperties()->SetStringProperty(m_ulPropertyContainer, Prop_ModelNumber_String, "ViveMV");
	vr::VRProperties()->SetStringProperty(m_ulPropertyContainer, Prop_ManufacturerName_String,"HTC");
	vr::VRProperties()->SetStringProperty(m_ulPropertyContainer, Prop_RenderModelName_String, "1234");
	vr::VRProperties()->SetFloatProperty(m_ulPropertyContainer, Prop_UserIpdMeters_Float, m_flIPD);
	vr::VRProperties()->SetFloatProperty(m_ulPropertyContainer, Prop_UserHeadToEyeDepthMeters_Float, 0.f);
	vr::VRProperties()->SetFloatProperty(m_ulPropertyContainer, Prop_DisplayFrequency_Float, 0.0);
	vr::VRProperties()->SetFloatProperty(m_ulPropertyContainer, Prop_SecondsFromVsyncToPhotons_Float, 0.0);

	// return a constant that's not 0 (invalid) or 1 (reserved for Oculus)
	vr::VRProperties()->SetUint64Property(m_ulPropertyContainer, Prop_CurrentUniverseId_Uint64, 2);

	// avoid "not fullscreen" warnings from vrmonitor
	vr::VRProperties()->SetBoolProperty(m_ulPropertyContainer, Prop_IsOnDesktop_Bool, false);

	return VRInitError_None;
}

void CHMDDeviceDriver::Deactivate()
{

	DriverLog("===============Deactivate=========\n");
	m_unObjectId = vr::k_unTrackedDeviceIndexInvalid;
	releaseHmdDriver(huaDisplayComponent);

}

void CHMDDeviceDriver::EnterStandby()
{
}

void * CHMDDeviceDriver::GetComponent(const char * pchComponentNameAndVersion)
{
	if (!_stricmp(pchComponentNameAndVersion, vr::IVRDisplayComponent_Version))
	{
		return huaDisplayComponent;
	}
	return NULL;
}

void CHMDDeviceDriver::PowerOff()
{
}

void CHMDDeviceDriver::DebugRequest(const char * pchRequest, char * pchResponseBuffer, uint32_t unResponseBufferSize)
{
	if (unResponseBufferSize >= 1)
		pchResponseBuffer[0] = 0;
}

void CHMDDeviceDriver::GetWindowBounds(int32_t * pnX, int32_t * pnY, uint32_t * pnWidth, uint32_t * pnHeight)
{
	huaDisplayComponent->GetWindowBounds(pnX, pnY, pnWidth, pnHeight);
}

bool CHMDDeviceDriver::IsDisplayOnDesktop()
{
	return huaDisplayComponent->IsDisplayOnDesktop();
}

bool CHMDDeviceDriver::IsDisplayRealDisplay()
{
	return huaDisplayComponent->IsDisplayRealDisplay();
}

void CHMDDeviceDriver::GetRecommendedRenderTargetSize(uint32_t * pnWidth, uint32_t * pnHeight)
{
	huaDisplayComponent->GetRecommendedRenderTargetSize(pnWidth, pnHeight);
}

void CHMDDeviceDriver::GetEyeOutputViewport(EVREye eEye, uint32_t * pnX, uint32_t * pnY, uint32_t * pnWidth, uint32_t * pnHeight)
{
	huaDisplayComponent->GetEyeOutputViewport(eEye, pnX, pnY, pnWidth, pnHeight);
}

void CHMDDeviceDriver::GetProjectionRaw(EVREye eEye, float * pfLeft, float * pfRight, float * pfTop, float * pfBottom)
{
	huaDisplayComponent->GetProjectionRaw(eEye, pfLeft, pfRight, pfTop, pfBottom);
}

DistortionCoordinates_t CHMDDeviceDriver::ComputeDistortion(EVREye eEye, float fU, float fV)
{
	return huaDisplayComponent->ComputeDistortion(eEye, fU, fV);
}

DriverPose_t CHMDDeviceDriver::GetPose()
{
	return m_pose;
}

DriverPose_t CHMDDeviceDriver::GetPose(HMD noloHMD)
{
	m_pose.poseTimeOffset = -0.016f;
	m_pose.poseIsValid = true;
	m_pose.result = TrackingResult_Running_OK;
	m_pose.deviceIsConnected = true;
	m_pose.willDriftInYaw = true;
	m_pose.shouldApplyHeadModel = false;

	m_pose.qWorldFromDriverRotation = HmdQuaternion_Init(1, 0, 0, 0);
	m_pose.qDriverFromHeadRotation = HmdQuaternion_Init(1, 0, 0, 0);

	// NOLO VR driver
	m_pose.vecWorldFromDriverTranslation[0] = 0;
	m_pose.vecWorldFromDriverTranslation[1] = 0;
	m_pose.vecWorldFromDriverTranslation[2] = 0;

	m_pose.vecDriverFromHeadTranslation[0] = 0.000f;
	m_pose.vecDriverFromHeadTranslation[1] = 0.000f;
	m_pose.vecDriverFromHeadTranslation[2] = 0.000f;

	m_pose.vecPosition[0] = noloHMD.HMDPosition.x;
	m_pose.vecPosition[1] = noloHMD.HMDPosition.y;
	m_pose.vecPosition[2] = -noloHMD.HMDPosition.z;

	m_pose.qRotation.w = -noloHMD.HMDRotation.w;
	m_pose.qRotation.x = noloHMD.HMDRotation.x;
	m_pose.qRotation.y = noloHMD.HMDRotation.y;
	m_pose.qRotation.z = -noloHMD.HMDRotation.z;

	DQuaternion rot(noloHMD.HMDRotation);
	if (IsTurnAround) {

		rot = rotQ * rot;
		m_pose.vecPosition[0] = 2 * posR.x - m_pose.vecPosition[0];
		m_pose.vecPosition[2] = -(2 * posR.z + m_pose.vecPosition[2]);

		m_pose.qRotation.w = -rot.w;
		m_pose.qRotation.x = rot.x;
		m_pose.qRotation.y = rot.y;
		m_pose.qRotation.z = -rot.z;
	}
	return m_pose;
}

void CHMDDeviceDriver::RunFrame(HMD hmd)
{
	// In a real driver, this should happen from some pose tracking thread.
	// The RunFrame interval is unspecified and can be very irregular if some other
	// driver blocks it for some periodic task.
	if (m_unObjectId != vr::k_unTrackedDeviceIndexInvalid)
	{
		vr::VRServerDriverHost()->TrackedDevicePoseUpdated(m_unObjectId, GetPose(hmd), sizeof(DriverPose_t));
	}
}

std::string CHMDDeviceDriver::GetSerialNumber()
{
	return m_sSerialNumber;
}

void CHMDDeviceDriver::setPos(Vector3 pos)
{
	memcpy(&posR,&pos,sizeof(Vector3));
}

void CHMDDeviceDriver::setTurnAround(bool turn)
{
	IsTurnAround = turn;
}

