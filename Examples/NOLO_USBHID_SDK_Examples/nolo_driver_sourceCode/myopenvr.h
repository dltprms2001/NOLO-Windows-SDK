#pragma once
#include <openvr_driver.h>
#include "nolo_api.h"
#include <thread>
#include "driver_log.h"
#define WIN32_LEAN_AND_MEAN    
#include <windows.h>
#include <math.h>
using namespace vr;
using namespace NOLO;
// keys for use with the settings API
static const char * const k_pch_HuaWeiNOLO_Section = "Test";
static const char * const k_pch_HuaWeiNOLO_EnableHuaWeiNOLODriver_Bool = "enable";
static const char * const k_pch_HuaWeiNOLO_SerialNumber_String = "serialNumber";
static const char * const k_pch_HuaWeiNOLO_ModelNumber_String = "modelNumber";
static const char * const k_pch_HuaWeiNOLO_WindowX_Int32 = "windowX";
static const char * const k_pch_HuaWeiNOLO_WindowY_Int32 = "windowY";
static const char * const k_pch_HuaWeiNOLO_WindowWidth_Int32 = "windowWidth";
static const char * const k_pch_HuaWeiNOLO_WindowHeight_Int32 = "windowHeight";
static const char * const k_pch_HuaWeiNOLO_RenderWidth_Int32 = "renderWidth";
static const char * const k_pch_HuaWeiNOLO_RenderHeight_Int32 = "renderHeight";
static const char * const k_pch_HuaWeiNOLO_SecondsFromVsyncToPhotons_Float = "secondsFromVsyncToPhotons";
static const char * const k_pch_HuaWeiNOLO_DisplayFrequency_Float = "displayFrequency";

inline HmdQuaternion_t HmdQuaternion_Init(double w, double x, double y, double z)
{
	HmdQuaternion_t quat;
	quat.w = w;
	quat.x = x;
	quat.y = y;
	quat.z = z;
	return quat;
}

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

#define NOLO_BUTTON_1        (0x01<<0)//press
#define NOLO_BUTTON_2        (0x01<<1)//trigger
#define NOLO_BUTTON_3        (0x01<<2)//menu
#define NOLO_BUTTON_4        (0x01<<3)//system
#define NOLO_BUTTON_5        (0x01<<4)//grip


static const vr::EVRButtonId k_EButton_Button1 = vr::k_EButton_SteamVR_Touchpad;
static const vr::EVRButtonId k_EButton_Button2 = vr::k_EButton_SteamVR_Trigger;
static const vr::EVRButtonId k_EButton_Button3 = vr::k_EButton_ApplicationMenu;
static const vr::EVRButtonId k_EButton_Button4 = vr::k_EButton_System;
static const vr::EVRButtonId k_EButton_Button5 = vr::k_EButton_Grip;

typedef struct DVector3
{
	float x;
	float y;
	float z;

	DVector3() {
		x = 0.0;
		y = 0.0;
		z = 0.0;
	}
	DVector3(float _x, float _y, float _z) {

		x = _x; y = _y; z = _z;
	}
	void normalize() {

		float len = sqrt(x*x + y*y + z*z);
		x /= len;
		y /= len;
		z /= len;
	}
}DVector3;


typedef struct DQuaternion
{
	float x;
	float y;
	float z;
	float w;

	DQuaternion() {
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 1.0f;
	}

	DQuaternion(Quaternion qt) {

		x = qt.x;
		y = qt.y;
		z = qt.z;
		w = qt.w;
	}

	DQuaternion(float _x, float _y, float _z, float _w) {

		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}

	static DQuaternion rotation(const DVector3 anix, const float angle) {

		DVector3 axis(anix);
		axis.normalize();

		float cosa = cos(angle / 2.0f);
		float sina = sin(angle / 2.0f);

		DQuaternion result(sina*anix.x, sina*anix.y, sina*anix.z, cosa);
		result.normalize();
		return result;
	}


	friend DQuaternion operator*(const DQuaternion qa, const DQuaternion qb) {

		DQuaternion qa_const_copy(qa), qb_const_copy(qb), qc;

		qc.w = qa_const_copy.w*qb_const_copy.w - qa_const_copy.x *qb_const_copy.x
			- qa_const_copy.y*qb_const_copy.y - qa_const_copy.z*qb_const_copy.z;

		qc.x = qa_const_copy.x*qb_const_copy.w + qa_const_copy.w *qb_const_copy.x
			+ qa_const_copy.y*qb_const_copy.z - qa_const_copy.z*qb_const_copy.y;

		qc.y = qa_const_copy.y*qb_const_copy.w + qa_const_copy.w *qb_const_copy.y
			+ qa_const_copy.z*qb_const_copy.x - qa_const_copy.x*qb_const_copy.z;

		qc.z = qa_const_copy.z*qb_const_copy.w + qa_const_copy.w *qb_const_copy.z
			+ qa_const_copy.x*qb_const_copy.y - qa_const_copy.y*qb_const_copy.x;
		return qc;
	}

	void normalize() {

		float len = sqrt(x*x + y*y + z*z + w*w);

		x /= len;
		y /= len;
		z /= len;
		w /= len;
	}

}DQuaternion;

////nolo_api.h
//#pragma comment(lib,"..\\x64\\debug\\NoLo_USBHID.lib")
////华为接口函数
//#pragma comment(lib,"..\\x64\\debug\\Hmd.lib")
//nolo_api.h
#pragma comment(lib,"..\\x64\\release\\NoLo_USBHID.lib")
#pragma comment(lib,"..\\x64\\release\\Hmd.lib")
__declspec(dllimport) IVRDisplayComponent *  createHmdDriver();
__declspec(dllimport) void   releaseHmdDriver(IVRDisplayComponent * display);