# NOLO-Windows-SDK [中文](https://github.com/NOLOVR/NOLO-Windows-SDK/blob/master/README_CN.md)
* This SDK provides all data from NOLO, including real-time data from headset marker, controllers and base station. 
* Developers can use NOLO data to access  a variety of game platforms.  
NOLO's headset marker can provide position and rotation data.You can use the rotation data provided by it when the rotation data provided by your HMD's IMU is not stable.  
* Game developers can use NOLO to develop games on various platforms.  
Unity developers can choose Unity SDK provided by NOLO.  
Native Android developers can choose Android SDK provided by NOLO.  
Windows developers can choose Windows SDK provided by NOLO. 

## NOLO USBHID SDK [Getting started](https://github.com/NOLOVR/NOLO-Windows-SDK/blob/master/HIDGetStarted.md) 
    NOLO USBHID SDK directly reads NOLO tracking data through USB.  
     In this situation,you needn't install NOLO PC software(NOLO Driver for Windows) when you're developing.
#
## NOLO ZEROMQ SDK [Getting started](https://github.com/NOLOVR/NOLO-Windows-SDK/blob/master/GetStarted.md) 
    NOLO ZEROMQ SDK reads data on NOLO PC software via ZEROMQ network transfer protocol.  
    In this situation,you need install NOLO PC software(NOLO Driver for Windows) when you're developing.  
    You should notice that NOLO PC software acquiescently provides steamvr controller driver. 
#


# [Notice](https://github.com/NOLOVR/NOLO-Windows-SDK/blob/master/NOLOVR/NOLO_USBHID_SDK/Notice_EN.pdf)
# [Use case](https://github.com/NOLOVR/NOLO-Windows-SDK/tree/master/Examples)
# Changes  
NOLO ZEROMQ SDK:  
V1
- 2017/5/31  
  * Add double click the menu button callback notification interface and double click system button callback notification interface.
- 2017/7/7  
  * Add receive data from NOLO PC software callback notification interface for noloRuntime.  
#
NOLO USBHID SDK:  
The version number of Windows SDK is now changed from V1 to V_0_1_RC beta.
- 2017/8/7
  * Release  
- 2017/9/11  
  * Provide velocity and angular velocity.
- 2017/10/19
  * Add the function to switch the play mode: the horizontal mode and the ceiling mode.  
    	NOLO_API void _cdecl set_Nolo_PlayMode(EPlayMode  Type) ;
- 2017/10/19
  * Set the tracking center of HMD.   
  	NOLO_API void _cdecl set_Nolo_HmdTrackingCenter(Vector3 v) ;
- 2017/12/6
  * Set HMD's rotation center and HMD type name   
  	NOLO_API void _cdecl set_Nolo_HmdTrackingCenter(Vector3 v，const char *strHmdTypeName) ;
  * Set whether to allow sending Http messages   
    NOLO_API void _cdecl set_PermitHttp(bool bPermit);
  * Added directional buttons on the touchpad (i.e. up, down, left, right);
  * Fixed a bug on controllers where the touch panel was not sensitive on edges.
#

        
        
