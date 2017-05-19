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
///NoloRuntime.dll api
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
    //nolo controller struct
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
	///nolo head tracking struct
	typedef struct HMD
	{

		int HMDVersionID;

		Vector3 HMDPosition;

		Vector3 HMDInirPostion;

		UINT HMDTwoPointDriftAngle;

		Quaternion HMDRotation;

		int state;
	}HMD;
    ///nolo base station struct
	typedef struct BaseStation
	{

		int BaseStationVersionID;

		int BaseStationPower;
	}BaseStation;
    ///nolo all data struct
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
    /// nolo Device type enumerate
	typedef enum NoloDeviceType
	{
		HmdDevice = 0,
		LeftControllerDevice,
		RightControllerDevice,
		BaseStationOne
	}NoloDeviceType;
    //
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
	///NoloRuntime.dll calls this method as a ZeroMQ socket client when disconnected to the server
	NOLO_API  bool PASCAL disConnenct_FunCallBack(funcCallBack fun);
	///NoloRuntime.dll calls this method as a ZeroMQ socket client when connected to the server
	NOLO_API  bool PASCAL connectSuccess_FunCallBack(funcCallBack fun);
	///According to the type of equipment and vibration intensity to send data packets to the nolo server
	NOLO_API  void PASCAL set_Nolo_TriggerHapticPulse(NoloDeviceType deviceType, int intensity);
	///Returns all data for nolo
	NOLO_API  NoloData PASCAL get_Nolo_NoloData();
	//NOLO Controller API
	
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
	NOLO_API UINT PASCAL get_Nolo_HMDTwoPointDriftAngle();
	//
	NOLO_API int PASCAL get_Nolo_VersionID();
	///get NOLO Controller States By Device Type
	NOLO_API ControllerStates PASCAL get_Nolo_ControllerStates(NoloDeviceType devicetype);
	///get NOLO Pose By Device Type
	NOLO_API Nolo_Pose PASCAL get_Nolo_Pose(NoloDeviceType devicetype);
}
#endif // _NOLO_API_H_