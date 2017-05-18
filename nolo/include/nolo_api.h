#pragma once
#ifndef _NOLO_API_H_
#define _NOLO_API_H_
#define WIN32_LEAN_AND_MEAN    
#include <windows.h>
#include <math.h>

#ifndef NOLO_API
#define NOLO_API extern "C"
#else
#define NOLO_API
#endif

namespace NOLO {
	typedef struct Vector2
	{
		float x;
		float y;
	}Vector2;
	typedef struct Vector3
	{
		float x;
		float y;
		float z;
	}Vector3;

	typedef struct Quaternion
	{
		float x;
		float y;
		float z;
		float w;
	}Quaternion;
	typedef struct Controller
	{

		int LeftControllerVersionID;

		Vector3 LeftControllerPosition;

		Quaternion LeftControllerRotation;

		UINT LeftButtons;

		int LeftControllerTouched;

		Vector2 LeftControllerTouchAxis;

		int LeftControllerBattery;

		int state;
	}Controller;
	typedef struct HMD
	{

		int HMDVersionID;

		Vector3 HMDPosition;

		Vector3 HMDInirPostion;

		UINT HMDTwoPointDriftAngle;

		Quaternion HMDRotation;

		int state;
	}HMD;

	typedef struct BaseStation
	{

		int BaseStationVersionID;

		int BaseStationPower;
	}BaseStation;

	typedef struct NoloData {

		Controller left_Handle_Data;

		Controller right_Handle_Data;

		HMD hmdData;

		BaseStation baseStationData;
		/**
			expandData[0]>>0 :Double click Menu
			expandData[1]>>1 :Double click System
		*/
		BYTE expandData[64];
	}NoloData;

	typedef enum NoloDeviceType
	{
		HmdDevice = 0,
		LeftControllerDevice,
		RightControllerDevice,
		BaseStationOne
	}NoloDeviceType;

	typedef struct  Nolo_Pose
	{
		Vector3 pos;
		Quaternion rot;
	}Nolo_Pose;
	//
	typedef struct ControllerStates
	{
		UINT noloButtons;
		UINT noloButtonTouch;
		Vector2 touchpadAxis;
	}ControllerStates;

	typedef void(*funcCallBack)();
	//
	NOLO_API  void PASCAL open_Nolo_ZeroMQ();
	//
	NOLO_API  void PASCAL close_Nolo_ZeroMQ();
	//
	NOLO_API  bool PASCAL disConnenct_FunCallBack(funcCallBack fun);
	//
	NOLO_API  bool PASCAL connectSuccess_FunCallBack(funcCallBack fun);
	//
	NOLO_API  void PASCAL set_Nolo_TriggerHapticPulse(NoloDeviceType deviceType, int intensity);
	//
	NOLO_API  NoloData PASCAL get_Nolo_NoloData();
	//
	NOLO_API  Controller PASCAL get_Nolo_LeftControllerData();
	//
	NOLO_API  Controller PASCAL get_Nolo_RightControllerData();
	//
	NOLO_API HMD PASCAL get_Nolo_HMDData();
	//
	NOLO_API BYTE* PASCAL get_Nolo_ExpandData();
	//
	NOLO_API Vector3 PASCAL get_Nolo_HMDInirPostion();
	//
	NOLO_API int PASCAL get_Nolo_StateByDeviceType();
	//
	NOLO_API int PASCAL get_Nolo_Battery();
	//
	NOLO_API void PASCAL set_Nolo_TriggerHapticPulse(NoloDeviceType deviceType, int intensity);
	//
	NOLO_API UINT PASCAL get_Nolo_HMDTwoPointDriftAngle();
	//
	NOLO_API int PASCAL get_Nolo_VersionID();
	//
	NOLO_API ControllerStates PASCAL get_Nolo_ControllerStates();
	//
	NOLO_API Nolo_Pose PASCAL get_Nolo_Pose();
}
#endif // _NOLO_API_H_