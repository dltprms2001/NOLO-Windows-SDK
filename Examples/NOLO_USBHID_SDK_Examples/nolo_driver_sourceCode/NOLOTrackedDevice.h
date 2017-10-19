#pragma once
#include "myopenvr.h"
class NOLOTrackedDevice : public ITrackedDeviceServerDriver, public IVRControllerComponent
{
public:
	NOLOTrackedDevice(std::string id,int mid);
	~NOLOTrackedDevice();

	virtual EVRInitError Activate(uint32_t unObjectId);

	virtual void Deactivate() ;

	/** Handles a request from the system to put this device into standby mode. What that means is defined per-device. */
	virtual void EnterStandby() ;

	/** Requests a component interface of the driver for device-specific functionality. The driver should return NULL
	* if the requested interface or version is not supported. */
	virtual void *GetComponent(const char *pchComponentNameAndVersion) ;

	/** A VR Client has made this debug request of the driver. The set of valid requests is entirely
	* up to the driver and the client to figure out, as is the format of the response. Responses that
	* exceed the length of the supplied buffer should be truncated and null terminated */
	virtual void DebugRequest(const char *pchRequest, char *pchResponseBuffer, uint32_t unResponseBufferSize) ;

	// ------------------------------------
	// Tracking Methods
	// ------------------------------------
	virtual DriverPose_t GetPose() ;

	DriverPose_t GetPose(Controller ctrData);

	std::string GetSerialNumber();

	void RunFrame(Controller ctrData);

	/** Gets the current state of a controller. */
	virtual VRControllerState_t GetControllerState();

	VRControllerState_t GetControllerState(Controller ctrData);

	/** Returns a uint64 property. If the property is not available this function will return 0. */
	virtual bool TriggerHapticPulse(uint32_t unAxisId, uint16_t usPulseDurationMicroseconds) ;


	typedef void (IVRServerDriverHost::*ButtonUpdate)(uint32_t unWhichDevice, vr::EVRButtonId eButtonId, double eventTimeOffset);

	void SendButtonUpdates(ButtonUpdate ButtonEvent, uint64_t ulMask);

	vr::EVRButtonId GetDPadButton(float float_x, float float_y);

	void setPos(Vector3 pos);

	void setTurnAround(bool turn);
private:
	VRControllerState_t m_ControllerState;
	vr::DriverPose_t m_Pose;


	unsigned short m_firmware_revision;
	unsigned short m_hardware_revision;

	vr::TrackedDeviceIndex_t m_unObjectId;
	vr::PropertyContainerHandle_t m_ulPropertyContainer;

	std::string m_sSerialNumber;
	std::string m_sModelNumber;

	int m_id;

	bool flag_TriggerDown = false;
	bool flag_Throw = false;

	bool IsTurnAround;
 	DQuaternion rotQ;
	DVector3 posR;
};

