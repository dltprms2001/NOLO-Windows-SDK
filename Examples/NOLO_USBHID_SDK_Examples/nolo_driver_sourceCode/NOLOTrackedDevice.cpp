#include "NOLOTrackedDevice.h"



NOLOTrackedDevice::NOLOTrackedDevice(std::string std, int mid)
{
	memset(&posR, 0, sizeof(posR));
	rotQ.x = 0; rotQ.y = 1; rotQ.z = 0; rotQ.w = 0;
	IsTurnAround = false;
	m_ulPropertyContainer = vr::k_ulInvalidPropertyContainer;
	m_sSerialNumber = std;
	m_sModelNumber = "vr_controller_vive_1_5";
	m_id = mid;

}

NOLOTrackedDevice::~NOLOTrackedDevice()
{
}

EVRInitError NOLOTrackedDevice::Activate(uint32_t unObjectId)
{
	m_unObjectId = unObjectId;
	m_ulPropertyContainer = vr::VRProperties()->TrackedDeviceToPropertyContainer(m_unObjectId);

	vr::VRProperties()->SetStringProperty(m_ulPropertyContainer, Prop_SerialNumber_String, m_sSerialNumber.c_str());
	vr::VRProperties()->SetStringProperty(m_ulPropertyContainer, Prop_ModelNumber_String, m_sModelNumber.c_str());
	vr::VRProperties()->SetStringProperty(m_ulPropertyContainer, Prop_RenderModelName_String, m_sModelNumber.c_str());
	vr::VRProperties()->SetStringProperty(m_ulPropertyContainer, Prop_ManufacturerName_String, "HTC");

	uint64_t reval= vr::ButtonMaskFromId(vr::k_EButton_ApplicationMenu) |
		vr::ButtonMaskFromId(vr::k_EButton_SteamVR_Touchpad) |
		vr::ButtonMaskFromId(vr::k_EButton_SteamVR_Trigger) |
		vr::ButtonMaskFromId(vr::k_EButton_System) |
		vr::ButtonMaskFromId(vr::k_EButton_Grip);
	vr::VRProperties()->SetUint64Property(m_ulPropertyContainer, Prop_SupportedButtons_Uint64, reval);
	return VRInitError_None;
}

void NOLOTrackedDevice::Deactivate()
{
	m_unObjectId = k_unTrackedDeviceIndexInvalid;
}

void NOLOTrackedDevice::EnterStandby()
{
}

void * NOLOTrackedDevice::GetComponent(const char * pchComponentNameAndVersion)
{
	if (!_stricmp(pchComponentNameAndVersion, vr::IVRControllerComponent_Version))
	{
		return (vr::IVRControllerComponent*)this;
	}

	return NULL;
}

void NOLOTrackedDevice::DebugRequest(const char * pchRequest, char * pchResponseBuffer, uint32_t unResponseBufferSize)
{
	if (unResponseBufferSize >= 1)
		pchResponseBuffer[0] = 0;
}

DriverPose_t NOLOTrackedDevice::GetPose()
{
	return m_Pose;
}

DriverPose_t NOLOTrackedDevice::GetPose(Controller ctrData)
{
	m_Pose.poseTimeOffset = -0.016f;
	m_Pose.qWorldFromDriverRotation.w = 1.0;
	m_Pose.qWorldFromDriverRotation.x = 0.0;
	m_Pose.qWorldFromDriverRotation.y = 0.0;
	m_Pose.qWorldFromDriverRotation.z = 0.0;
	m_Pose.vecWorldFromDriverTranslation[0] = 0.0;
	m_Pose.vecWorldFromDriverTranslation[1] = 0.0;
	m_Pose.vecWorldFromDriverTranslation[2] = 0.0;

	m_Pose.qDriverFromHeadRotation.w = 1.0f;
	m_Pose.qDriverFromHeadRotation.x = 0.0f;
	m_Pose.qDriverFromHeadRotation.y = 0.0f;
	m_Pose.qDriverFromHeadRotation.z = 0.0f;
	m_Pose.vecDriverFromHeadTranslation[0] = 0.000f;
	m_Pose.vecDriverFromHeadTranslation[1] = 0.007f;
	m_Pose.vecDriverFromHeadTranslation[2] = -0.073f;

	m_Pose.vecAcceleration[0] = 0.0;
	m_Pose.vecAcceleration[1] = 0.0;
	m_Pose.vecAcceleration[2] = 0.0;
	m_Pose.vecAngularAcceleration[0] = 0.0;
	m_Pose.vecAngularAcceleration[1] = 0.0;
	m_Pose.vecAngularAcceleration[2] = 0.0;

	m_Pose.result = vr::TrackingResult_Running_OK;
	m_Pose.willDriftInYaw = false;
	m_Pose.shouldApplyHeadModel = false;

	m_Pose.poseIsValid = true;//这是控制未就绪的地方
	m_Pose.deviceIsConnected = true;

	m_Pose.vecPosition[0] = ctrData.ControllerPosition.x;
	m_Pose.vecPosition[1] = ctrData.ControllerPosition.y;
	m_Pose.vecPosition[2] = -ctrData.ControllerPosition.z;
	m_Pose.qRotation.w = -ctrData.ControllerRotation.w;
	m_Pose.qRotation.x = ctrData.ControllerRotation.x;
	m_Pose.qRotation.y = ctrData.ControllerRotation.y;
	m_Pose.qRotation.z = -ctrData.ControllerRotation.z;
	m_Pose.vecVelocity[0] = ctrData.vecVelocity.x;
	m_Pose.vecVelocity[1] = ctrData.vecVelocity.y;
	m_Pose.vecVelocity[2] = ctrData.vecVelocity.z;
	m_Pose.vecAngularVelocity[0] = ctrData.vecAngularVelocity.x;
	m_Pose.vecAngularVelocity[1] = ctrData.vecAngularVelocity.y;
	m_Pose.vecAngularVelocity[2] = ctrData.vecAngularVelocity.z;

	DQuaternion rot(ctrData.ControllerRotation);
	if (IsTurnAround) {

		rot = rotQ * rot;
		m_Pose.vecPosition[0] = 2 * posR.x - m_Pose.vecPosition[0];
		m_Pose.vecPosition[2] = -(2 * posR.z + m_Pose.vecPosition[2]);

		m_Pose.qRotation.w = -rot.w;
		m_Pose.qRotation.x = rot.x;
		m_Pose.qRotation.y = rot.y;
		m_Pose.qRotation.z = -rot.z;

		m_Pose.vecVelocity[0] = -ctrData.vecVelocity.x;
		m_Pose.vecVelocity[2] = -ctrData.vecVelocity.z;
		m_Pose.vecAngularVelocity[0] = -ctrData.vecAngularVelocity.x;
		m_Pose.vecAngularVelocity[2] = -ctrData.vecAngularVelocity.z;
	}
	return m_Pose;
}

std::string NOLOTrackedDevice::GetSerialNumber()
{
	return m_sSerialNumber;
}

void NOLOTrackedDevice::RunFrame(Controller ctrData)
{
	if (m_unObjectId != vr::k_unTrackedDeviceIndexInvalid)
	{
		GetControllerState(ctrData);
		vr::VRServerDriverHost()->TrackedDevicePoseUpdated(m_unObjectId, GetPose(ctrData), sizeof(DriverPose_t));
	}
}

VRControllerState_t NOLOTrackedDevice::GetControllerState()
{
	return m_ControllerState;
}

VRControllerState_t NOLOTrackedDevice::GetControllerState(Controller ctrData)
{

	vr::VRControllerState_t NewState = { 0 };
	NewState.unPacketNum = m_ControllerState.unPacketNum + 1;
	if (ctrData.Buttons & NOLO_BUTTON_1) {
		//DriverLog("==============press=============\n");
		NewState.ulButtonPressed |= vr::ButtonMaskFromId(k_EButton_Button1);
		SendButtonUpdates(&vr::IVRServerDriverHost::TrackedDeviceButtonPressed, GetDPadButton(ctrData.ControllerTouchAxis.x, ctrData.ControllerTouchAxis.y));
	}
	if (ctrData.Buttons & NOLO_BUTTON_2) {
		//DriverLog("==============trigger=============\n");
		NewState.ulButtonTouched |= vr::ButtonMaskFromId(k_EButton_Button2);
	}
	if (ctrData.Buttons & NOLO_BUTTON_3) {
		//DriverLog("==============menu=============\n");
		NewState.ulButtonPressed |= vr::ButtonMaskFromId(k_EButton_Button3);
	}

	if (ctrData.Buttons & NOLO_BUTTON_4) {
		//DriverLog("==============system=============\n");
		NewState.ulButtonPressed |= vr::ButtonMaskFromId(k_EButton_Button4);
	}
	if (ctrData.Buttons & NOLO_BUTTON_5) {
		//DriverLog("==============grip=============\n");
		NewState.ulButtonPressed |= vr::ButtonMaskFromId(k_EButton_Button5);
	}

	// All pressed buttons are touched
	if (ctrData.Buttons & NOLO_BUTTON_1)
		NewState.ulButtonPressed |= vr::ButtonMaskFromId(vr::k_EButton_Axis0);
	if (ctrData.Buttons & NOLO_BUTTON_2)
		NewState.ulButtonTouched |= vr::ButtonMaskFromId(vr::k_EButton_Axis1);
	if (ctrData.Buttons & NOLO_BUTTON_2)
		NewState.ulButtonPressed |= vr::ButtonMaskFromId(vr::k_EButton_Axis1);
	if (ctrData.ControllerTouched)
		NewState.ulButtonTouched |= vr::ButtonMaskFromId(vr::k_EButton_Axis0);

	NewState.ulButtonTouched |= NewState.ulButtonPressed;

	uint64_t ulChangedTouched = NewState.ulButtonTouched ^ m_ControllerState.ulButtonTouched;
	uint64_t ulChangedPressed = NewState.ulButtonPressed ^ m_ControllerState.ulButtonPressed;

	SendButtonUpdates(&IVRServerDriverHost::TrackedDeviceButtonTouched, ulChangedTouched & NewState.ulButtonTouched);
	SendButtonUpdates(&IVRServerDriverHost::TrackedDeviceButtonPressed, ulChangedPressed & NewState.ulButtonPressed);
	SendButtonUpdates(&IVRServerDriverHost::TrackedDeviceButtonUnpressed, ulChangedPressed & ~NewState.ulButtonPressed);
	SendButtonUpdates(&IVRServerDriverHost::TrackedDeviceButtonUntouched, ulChangedTouched & ~NewState.ulButtonTouched);


	NewState.rAxis[0].x = ctrData.ControllerTouchAxis.x;
	NewState.rAxis[0].y = ctrData.ControllerTouchAxis.y;
	NewState.rAxis[1].x = ctrData.Buttons & NOLO_BUTTON_2;
	NewState.rAxis[1].y = 0.0f;

	if (NewState.rAxis[0].x != m_ControllerState.rAxis[0].x || NewState.rAxis[0].y != m_ControllerState.rAxis[0].y)
		vr::VRServerDriverHost()->TrackedDeviceAxisUpdated(m_unObjectId, 0, NewState.rAxis[0]);
	if (NewState.rAxis[1].x != m_ControllerState.rAxis[1].x)
		vr::VRServerDriverHost()->TrackedDeviceAxisUpdated(m_unObjectId, 1, NewState.rAxis[1]);

	m_ControllerState = NewState;
	return m_ControllerState;
}

bool NOLOTrackedDevice::TriggerHapticPulse(uint32_t unAxisId, uint16_t usPulseDurationMicroseconds)
{
	int n = usPulseDurationMicroseconds / 40;

	if (n>50) {

		n = 50;
	}

	if (m_id == 0) {

		set_Nolo_TriggerHapticPulse(NoloDeviceType::LeftControllerDevice, 50 + n);
	}
	else if (m_id == 1)
	{
		set_Nolo_TriggerHapticPulse(NoloDeviceType::RightControllerDevice, 50 + n);
	}
	return true;
}

void NOLOTrackedDevice::SendButtonUpdates(ButtonUpdate ButtonEvent, uint64_t ulMask)
{
	if (!ulMask)
		return;

	for (int i = 0; i< vr::k_EButton_Max; i++)
	{
		vr::EVRButtonId button = (vr::EVRButtonId)i;

		uint64_t bit = ButtonMaskFromId(button);

		if ((bit & ulMask))
		{
			(vr::VRServerDriverHost()->*ButtonEvent)(m_unObjectId, button, 0.0);
		}
	}
}

vr::EVRButtonId NOLOTrackedDevice::GetDPadButton(float float_x, float float_y)
{
	if (float_x > 1.0 || float_x < -1.0
		|| float_y > 1.0 || float_y < -1.0) {
		//LOG(WARNING) << "GetDPadButton[" << m_cControllerRole << "]: error postion(" << float_x << "," << float_y << ")";
		return vr::k_EButton_Max;
	}

	int x = float_x * 10000.0f, y = float_y * 10000.0f;
	//UP:-y<x<y
	if (x > -y && x < y) {
		//LOG_EVERY_N(INFO, 1 * 90) << "GetDPadButton[" << m_cControllerRole << "]:k_EButton_DPad_Up";
		return vr::k_EButton_DPad_Up;
	}
	//DOWN:y<x<-y
	if (x > y && x < -y) {
		//LOG_EVERY_N(INFO, 1 * 90) << "GetDPadButton[" << m_cControllerRole << "]:k_EButton_DPad_Down";
		return vr::k_EButton_DPad_Down;
	}
	//LEFT:x<y<-x
	if (y > x && y < -x) {
		//LOG_EVERY_N(INFO, 1 * 90) << "GetDPadButton[" << m_cControllerRole << "]:k_EButton_DPad_Left";
		return vr::k_EButton_DPad_Left;
	}
	//RIGHT:-x<y<x
	if (y > -x && y < x) {
		//LOG_EVERY_N(INFO, 1 * 90) << "GetDPadButton[" << m_cControllerRole << "]:k_EButton_DPad_Right";
		return vr::k_EButton_DPad_Right;
	}

	//LOG_EVERY_N(INFO, 1 * 90) << "GetDPadButton[" << m_cControllerRole << "]:unknown region(" << x << "," << y << "),float(" << float_x << "," << "" << float_y << ")";
	return vr::k_EButton_Max;
}

void NOLOTrackedDevice::setPos(Vector3 pos)
{
	memcpy(&posR,&pos,sizeof(Vector3));
}

void NOLOTrackedDevice::setTurnAround(bool turn)
{
	IsTurnAround = turn;
}
