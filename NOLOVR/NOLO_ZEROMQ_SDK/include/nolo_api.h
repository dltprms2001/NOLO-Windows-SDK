#pragma once
#ifndef _NOLO_V1_API_H_
#define _NOLO_V1_API_H_
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
		friend Vector3 operator -(const Vector3 _v1, const Vector3 _v2) {

		Vector3 v;
		v.x = _v1.x - _v2.x; v.y = _v1.y - _v2.y; v.z = _v1.z - _v2.z;
		return v;
		}
	}Vector3;

	typedef struct Quaternion
	{
		float x;
		float y;
		float z;
		float w;
		friend Quaternion operator*(const Quaternion qa, const Quaternion qb) {

		Quaternion qa_const_copy(qa), qb_const_copy(qb), qc;

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
		Vector3 HMDInitPosition;

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
			expandData[1]:0 nomal ,1 Double click menu
		*/
		BYTE expandData[64];
	}NoloData;
    /// nolo Device type enumerate
	typedef enum NoloDeviceType
	{
		HmdDevice = 0,
		LeftControllerDevice,
		RightControllerDevice,
		BaseStationDevice
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

	typedef enum ExpandMsgType {

	  DoubleClickMenu=1,
	  DoubleClickSystem
    }ExpandMsgType;

	typedef void(__cdecl * noloData_FuncCallBackNotify)(NoloData _noloData);
	typedef void(__cdecl *expandMsg_FuncCallBack)(ExpandMsgType expandMsgType);
	typedef void(__cdecl *funcCallBack)();
	///Open the ZeroMQ client to recevice nolo data
	NOLO_API  bool _cdecl open_Nolo_ZeroMQ();
	///Close the ZeroMQ client to release the resource
	NOLO_API  void _cdecl close_Nolo_ZeroMQ();
	///NoloRuntime.dll calls this method as a ZeroMQ socket client when disconnected to the server
	NOLO_API  bool _cdecl disConnect_FunCallBack(funcCallBack fun);
	///NoloRuntime.dll calls this method as a ZeroMQ socket client when connected to the server
	NOLO_API  bool _cdecl connectSuccess_FunCallBack(funcCallBack fun);
	///According to the type of equipment and vibration intensity to send data packets to the nolo server
	NOLO_API  void _cdecl set_Nolo_TriggerHapticPulse(NoloDeviceType deviceType, int intensity);
	///Returns all data for nolo
	NOLO_API  NoloData _cdecl get_Nolo_NoloData();
	///returns nolo controller data
	NOLO_API  Controller _cdecl get_Nolo_LeftControllerData();
	///returns nolo controller data
	NOLO_API  Controller _cdecl get_Nolo_RightControllerData();
	///returns nolo head tracking data
	NOLO_API HMD _cdecl get_Nolo_HMDData();
	///returns nolo Expand data
	NOLO_API BYTE* _cdecl get_Nolo_ExpandData();
	///returns nolo init head tracking data
	NOLO_API Vector3 _cdecl get_Nolo_HMDInitPosition();
	///returns nolo device state by device type
	NOLO_API int _cdecl get_Nolo_StateByDeviceType(NoloDeviceType type);
	///returns nolo device battery by device type
	NOLO_API int _cdecl get_Nolo_Battery(NoloDeviceType deviceType);
	//
	NOLO_API UINT _cdecl get_Nolo_HMDTwoPointDriftAngle();
	///get device version id by device type
	NOLO_API int _cdecl get_Nolo_VersionID(NoloDeviceType devicetype);
	///get NOLO Controller States By Device Type
	NOLO_API ControllerStates _cdecl get_Nolo_ControllerStates(NoloDeviceType devicetype);
	///get NOLO Pose By Device Type
	NOLO_API Nolo_Pose _cdecl get_Nolo_Pose(NoloDeviceType devicetype);
	///Interface of Double-click the menu key or the system key to notify in real time
	NOLO_API  bool _cdecl expandDataNotify_FuncCallBack(expandMsg_FuncCallBack fun);
	///Callback function which is called whenever new data has been received
	///I will call back when I receive the data from the NOLO software,Returns the function registration status
	NOLO_API  bool _cdecl noloDataNotify_FuncCallBack(noloData_FuncCallBackNotify fun);
}
#endif // _NOLO_V1_API_H_