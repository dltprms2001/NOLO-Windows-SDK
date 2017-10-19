#pragma once
#include "myopenvr.h"
class CHMDDeviceDriver :public ITrackedDeviceServerDriver, public IVRDisplayComponent
{
public:
	CHMDDeviceDriver();
	~CHMDDeviceDriver();
	EVRInitError Activate(vr::TrackedDeviceIndex_t unObjectId);
	void Deactivate();
	void EnterStandby();
	void *GetComponent(const char *pchComponentNameAndVersion);
	void PowerOff();
	void DebugRequest(const char *pchRequest, char *pchResponseBuffer, uint32_t unResponseBufferSize);

	void GetWindowBounds(int32_t *pnX, int32_t *pnY, uint32_t *pnWidth, uint32_t *pnHeight);
	bool IsDisplayOnDesktop();
	bool IsDisplayRealDisplay();
	void GetRecommendedRenderTargetSize(uint32_t *pnWidth, uint32_t *pnHeight);
	void GetEyeOutputViewport(EVREye eEye, uint32_t *pnX, uint32_t *pnY, uint32_t *pnWidth, uint32_t *pnHeight);
	void GetProjectionRaw(EVREye eEye, float *pfLeft, float *pfRight, float *pfTop, float *pfBottom);
	DistortionCoordinates_t ComputeDistortion(EVREye eEye, float fU, float fV);

	DriverPose_t GetPose();
	DriverPose_t GetPose(HMD hmd);
	void RunFrame(HMD hmd);
	std::string GetSerialNumber();

	void setPos(Vector3 pos);
	void setTurnAround(bool turn);
private:
	//===========xiaoyang================
	IVRDisplayComponent* huaDisplayComponent;
	DriverPose_t m_pose;
	//===================================
	vr::TrackedDeviceIndex_t m_unObjectId;
	vr::PropertyContainerHandle_t m_ulPropertyContainer;

	std::string m_sSerialNumber;
	std::string m_sModelNumber;

	int32_t m_nWindowX;
	int32_t m_nWindowY;
	int32_t m_nWindowWidth;
	int32_t m_nWindowHeight;
	int32_t m_nRenderWidth;
	int32_t m_nRenderHeight;
	float m_flSecondsFromVsyncToPhotons;
	float m_flDisplayFrequency;
	float m_flIPD;

	bool IsTurnAround;
	DQuaternion rotQ;
	DVector3 posR;
};

