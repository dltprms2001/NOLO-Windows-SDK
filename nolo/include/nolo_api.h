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

		int ControllerVersionID;

		Vector3 ControllerPosition;

		Quaternion ControllerRotation;
        /*
		  0x0000_XXX1:press
          0x0000_XX1X:trigger
          0x0000_X1XX:menu
          0x0000_1XXX:system
          0x0001_XXXX:grip
		*/
		UINT Buttons;
        ///nolo touch
		int ControllerTouched;
        /*
		   x:-1~1
		   y:-1~1
		*/
		Vector2 ControllerTouchAxis;
        /*
		  0~100：normal
		  255:Shut down
		*/
		int ControllerBattery;
        /*
		  0：Be blocked
		  1：normal
		*/
		int state;
	}Controller;
	///nolo head tracking struct
	typedef struct HMD
	{
        ///Handle version ID
		int HMDVersionID;

		Vector3 HMDPosition;
        ///Handle Init Position 
		Vector3 HMDInirPostion;

		UINT HMDTwoPointDriftAngle;

		Quaternion HMDRotation;
        /*
		  0：Be blocked
		  1：normal
		*/
		int state;
	}HMD;
    ///nolo base station struct
	typedef struct BaseStation
	{
        ///base station version id
		int BaseStationVersionID;
        /*
		  0~100:normal
		*/
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
			expandData[0]>>1 :Double click System
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
	   /*
		  0x0000_XXX1:press
          0x0000_XX1X:trigger
          0x0000_X1XX:menu
          0x0000_1XXX:system
          0x0001_XXXX:grip
		*/
		UINT noloButtons;
	    ///Handle with touch
		UINT noloButtonTouch;
		/*
		   x:-1~1
		   y:-1~1
		*/
		Vector2 touchpadAxis;
	}ControllerStates;

	typedef void(*funcCallBack)();
	//
	NOLO_API  bool PASCAL open_Nolo_ZeroMQ();
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
	///returns nolo controller data
	NOLO_API  Controller PASCAL get_Nolo_LeftControllerData();
	///returns nolo controller data
	NOLO_API  Controller PASCAL get_Nolo_RightControllerData();
	///returns nolo head tracking data
	NOLO_API HMD PASCAL get_Nolo_HMDData();
	///returns nolo Expand data
	NOLO_API BYTE* PASCAL get_Nolo_ExpandData();
	///returns nolo init head tracking data
	NOLO_API Vector3 PASCAL get_Nolo_HMDInirPostion();
	///returns nolo device state by device type
	NOLO_API int PASCAL get_Nolo_StateByDeviceType(NoloDeviceType type);
	///returns nolo device battery by device type
	NOLO_API int PASCAL get_Nolo_Battery(NoloDeviceType deviceType);
	//
	NOLO_API UINT PASCAL get_Nolo_HMDTwoPointDriftAngle();
	//
	NOLO_API int PASCAL get_Nolo_VersionID(NoloDeviceType devicetype);
	///get NOLO Controller States By Device Type
	NOLO_API ControllerStates PASCAL get_Nolo_ControllerStates(NoloDeviceType devicetype);
	///get NOLO Pose By Device Type
	NOLO_API Nolo_Pose PASCAL get_Nolo_Pose(NoloDeviceType devicetype);
}
#endif // _NOLO_API_H_