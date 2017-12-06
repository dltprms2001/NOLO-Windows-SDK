#pragma once
#ifndef _NOLO_V_0_1_RC_API_H_
#define _NOLO_V_0_1_RC_API_H_

#define WIN32_LEAN_AND_MEAN    
#include <windows.h>
#include <math.h>

#ifndef NOLO_API
#define NOLO_API extern "C"
#else
#define NOLO_API
#endif
///Nolo_USBHID.dll api
namespace NOLO {
	struct Vector2
	{
		float x;
		float y;
	};
	struct Vector3
	{
		float x;
		float y;
		float z;
	};

	struct Quaternion
	{
		float x;
		float y;
		float z;
		float w;
		
	};

    enum EBattery
    {
	    ShutDown=0,
	    Low,
	    Middle,
	    High,
    };

	enum EDoubleClickKeyType {

		press = 0,
		trigger,
		menu,
		grip,
		cancel
	};

	//Struct of NOLO controller data 
	struct Controller
	{

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
        /*
		  0~1 Touchpad  touched:1; Not touched:0
		*/
		int ControllerTouched;
        /*
		   x:-1~1
		   y:-1~1
		*/
		Vector2 ControllerTouchAxis;
        /*
		  0~100:normal
		  255:Shut down
		*/
		EBattery ControllerBattery;
		/* Velocity of the pose in meters/second */
	    Vector3 vecVelocity;

	    /* Acceleration of the pose in meters/second */
	    Vector3 vecAcceleration;

	    /* Angular velocity of the pose in axis-angle 
	     * representation. The direction is the angle of
	     * rotation and the magnitude is the angle around
	     * that axis in radians/second. */
	    Vector3 vecAngularVelocity;

	    /* Angular acceleration of the pose in axis-angle 
	     * representation. The direction is the angle of
	     * rotation and the magnitude is the angle around
	     * that axis in radians/second^2. */
	    Vector3 vecAngularAcceleration;
		 /*
		   state & 1 ==1 :normal:state & 1 ==0: Be blocked
		*/
		int state;
		
	};
	//Struct of NOLO headset marker data
	struct HMD
	{

		Vector3 HMDPosition;
		/*
		  When pressing the pair button on the headset marker,
		  we record the position data of the headset to calibrate the height of the ground.
		  Open vr don't need this data.
		*/
		Vector3 HMDInitPosition;

		Quaternion HMDRotation;
		/* Velocity of the pose in meters/second */
		Vector3 vecVelocity;

		/* Acceleration of the pose in meters/second */
		Vector3 vecAcceleration;

		/* Angular velocity of the pose in axis-angle
		* representation. The direction is the angle of
		* rotation and the magnitude is the angle around
		* that axis in radians/second. */
		Vector3 vecAngularVelocity;

		/* Angular acceleration of the pose in axis-angle
		* representation. The direction is the angle of
		* rotation and the magnitude is the angle around
		* that axis in radians/second^2. */
		Vector3 vecAngularAcceleration;
        /*
		   state & 1 ==1 :normal:state & 1 ==0: Be blocked
		*/
		int state;
	};
	//Struct of NOLO base station data
	struct BaseStation
	{
	    Vector3  vecPosition;
        /*
		  0~100:normal
		*/
		EBattery BaseStationPower;
	};
	//Struct of all NOLO devices data
	struct NoloData {
        
		Controller left_Controller_Data;

		Controller right_Controller_Data;

		HMD hmdData;

		BaseStation baseStationData;

	};
    // Enumerarion of NOLO devices types
	enum NoloDeviceType
	{
		HmdDevice = 0,
		LeftControllerDevice,
		RightControllerDevice,
		BaseStationDevice
	};

	enum ExpandMsgType {
	  //180 degree turn-around
	  DoubleClickKeyTurnAround=1,
	  //recenter
	  DoubleClickSystemRecenter
    };
	
	enum EPlayMode {
	    //Place the base station horizontally
		HorizontalMode = 0,
		//Place the base station on the ceiling
		CeilingMode
	};
	
	typedef void(__cdecl * noloDataNotifyCallBack)(NoloData _noloData , void * context);
	typedef void(__cdecl *funcCallBack)(void * context);
	typedef void(__cdecl *expandMsgCallBack)(ExpandMsgType expandMsgType , void * context);
	

	/**
	  ******************************************************************************
	  * Function description:Search for NOLO device
	  * Parameter:NULL
	  * Return Value:NULL
	  * Remarks:NULL
	  ******************************************************************************
	*/
	NOLO_API  void _cdecl search_Nolo_Device();
 	/*
      ******************************************************************************
      * Function description:Close the connection with NOLO device and release resources
      * Parameter:NULL
      * Return Value:NULL
      * Remarks:NULL
      ******************************************************************************
   */
	NOLO_API  void _cdecl close_Nolo_Device();
    /*
      ******************************************************************************
      * Function description:Get call-back notification when disconnect NOLO device
      * Parameter:Parameter fun ,custom function pointer
      * Return Value:Returns the function registration status:false or true
      * Remarks:NULL
      ******************************************************************************
    */
	NOLO_API  bool _cdecl registerDisConnectCallBack(funcCallBack fun , void * context);
	/*
      ******************************************************************************
      * Function description:Get call-back notification when connect NOLO device
      * Parameter:Parameter fun ,custom function pointer
      * Return Value:Returns the function registration status:false or true
      * Remarks:NULL
      ******************************************************************************
    */
	NOLO_API  bool _cdecl registerConnectSuccessCallBack(funcCallBack fun , void * context);
		/*
      ******************************************************************************
      * Function description:Interface of Double click the customizable button( The Default is the menu button)  or the system button to notify in real time
      * Parameter:Parameter fun ,custom function pointer
      * Return Value:Returns the function registration status:false or true
      * Remarks:
      ******************************************************************************
    */
	NOLO_API  bool _cdecl registerExpandDataNotifyCallBack(expandMsgCallBack fun , void * context);
	/*
      ******************************************************************************
      * Function description:Get call-back notification whenever getting new data through USB
      * Parameter:Parameter fun ,custom function pointer
      * Return Value:Returns the function registration status:false or true
      * Remarks:NULL
      ******************************************************************************
    */
	NOLO_API  bool _cdecl registerNoloDataNotifyCallBack(noloDataNotifyCallBack fun , void * context);
	/*
      ******************************************************************************
      * Function description:Set vibration functions of NOLO controller
      * Parameter:Parameter devicetype is an enumeration type,Parameter intensity : Vibration intensity range from 0~100, the bigger the stronger
      * Return Value:Return bool type
      * Remarks:Parameter devicetype  LeftControllerDevice RightControllerDevice
      ******************************************************************************
    */
	NOLO_API  bool _cdecl set_Nolo_TriggerHapticPulse(NoloDeviceType deviceType, int intensity);
	/*
      ******************************************************************************
      * Function description:Get all data interface function of NOLO
      * Parameter:NULL
      * Return Value:Returns the NoloData structure data
      * Remarks:NULL
      ******************************************************************************
    */
	NOLO_API  NoloData _cdecl get_Nolo_NoloData();
	/*
      ******************************************************************************
      * Function description:Get all data interface function of NOLO left controller
      * Parameter:NULL
      * Return Value:Returns the Controller structure data
      * Remarks:NULL
      ******************************************************************************
    */
	NOLO_API  Controller _cdecl get_Nolo_LeftControllerData();
	/*
      ******************************************************************************
      * Function description:Get all data interface function of NOLO right controller
      * Parameter:NULL
      * Return Value:Returns the Controller structure data
      * Remarks:NULL
      ******************************************************************************
    */
	NOLO_API  Controller _cdecl get_Nolo_RightControllerData();
	/*
      ******************************************************************************
      * Function description:Get all data interface function of NOLO headset marker
      * Parameter:NULL
      * Return Value:Returns the HMD structure data
      * Remarks:NULL
      ******************************************************************************
    */
	NOLO_API HMD _cdecl get_Nolo_HMDData();
	/*
      ******************************************************************************
      * Function description:Get all data interface function of NOLO base station
      * Parameter:NULL 
      * Return Value:Returns the BaseStation structure data
      * Remarks:NULL
      ******************************************************************************
    */
	NOLO_API BaseStation _cdecl get_Nolo_BaseStationData();
	/*
      ******************************************************************************
      * Function description:Get status data of NOLO battery power based on the type of device
      * Parameter:Parameter devicetype is an enumeration type
      * Return Value:Returns the EBattery enumeration type:shut down  low  middle  high
      * Remarks:NULL
      ******************************************************************************
    */
	NOLO_API EBattery _cdecl get_Nolo_Battery(NoloDeviceType deviceType);
	/*
	******************************************************************************
	* Function description: Customize the 180 degree turn-around hot key by the button types. The default is double click the menu button
	* Parameter:Parameter keyType is an enumeration type
	* Return Value:NULL
	* Remarks:NULL
	******************************************************************************
	*/
	NOLO_API void _cdecl set_Nolo_TurnAroundKey(EDoubleClickKeyType keyType);
	/*
	******************************************************************************
	* Function description:Customize the Flat Mode and Ceiling Mode according to EPlay Model.
	* Parameter:Parameter Type is an enumeration type
	* Return Value:NULL
	* Remarks:NULL
	******************************************************************************
	*/
	NOLO_API void _cdecl set_Nolo_PlayMode(EPlayMode  Type) ;
	
	/*
	******************************************************************************
	* Function description:Set the tracking center of HMD.
	* Parameter:
		@v is an Vector3 type .The relative position between the centre point of headset marker ball and 
	the mid point of two glasses (Coordinate origin be the mid point of two glasses, x-axis be the left-right 
	direction, y-axis be the up-down direction, and z-axis be the forward-backward direction).
		@strHmdTypeName is the helmet type name
	* Return Value:NULL
	* Remarks:
	    Set the relative position between the centre point of headset marker ball and the mid point of two glasses. 
	With the difference in parameter settings of various headsets, convert the tracking position of headset marker 
	to the actual position of the mid point of two glasses (i.e. making latter one the origin of a coordinate
	system of this two. 
	******************************************************************************
	*/
	NOLO_API void _cdecl set_Nolo_HmdTrackingCenter(Vector3 v,const char *strHmdTypeName);

	
	/******************************************************************************
	Description   : Allow the NoloDriver send information to the nolo server.
	Return Value  : NULL
	Remarks       : NULL
	Parameter List:
		@bPermit:default value is true ,set true to perimit send imformation.
	******************************************************************************/
	NOLO_API void _cdecl set_PermitHttp(bool bPermit);

}
#endif // _NOLO_V_0_1_RC_API_H_