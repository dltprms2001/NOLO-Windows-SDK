# NOLO-Windows-SDKs [中文](https://github.com/NOLOVR/NOLO-Windows-SDK/blob/master/README_CN.md)
* The following 2 SDK's provide all data from NOLO, including real-time data from headset marker, controllers and base station. **You can choose to incorporate either one into your game(s).**
* Developers can use NOLO data to communicate with a variety of game platforms.\
NOLO's headset marker provides both position and rotation data. You can use data from NOLO if data from your Helmet-Mounted-Display(HMD)'s IMU is not stable.  
* Game developers can use NOLO to develop games on various platforms.\
Unity developers can use Unity SDK provided by NOLO.  
Native Android developers can use Android SDK provided by NOLO.  
Windows developers can use Windows SDK (this SDK) provided by NOLO. 

#
## NOLO USBHID SDK [Getting started](https://github.com/NOLOVR/NOLO-Windows-SDK/blob/master/HIDGetStarted.md) 
    NOLO USBHID SDK reads NOLO tracking data directly through USB port.  
    With this SDK, you DON'T need to install NOLO PC software (NOLO Driver for Windows) during development.
#
## NOLO ZEROMQ SDK [Getting started](https://github.com/NOLOVR/NOLO-Windows-SDK/blob/master/GetStarted.md) 
    NOLO ZEROMQ SDK reads data from NOLO PC software via ZEROMQ network transfer protocol.  
    In this case, you'll need to install NOLO PC software (NOLO Driver for Windows) during development.
    Notice that NOLO PC software acquiescently provides steamvr controller driver. 
#

## Examples
See examples [here](https://github.com/NOLOVR/NOLO-Windows-SDK/tree/master/Examples).

## Notice
 **IMPORTANT!** NOLO's coordinate system is different from that of OpenVR. Read details [here](https://github.com/NOLOVR/NOLO-Windows-SDK/blob/master/NOLOVR/NOLO_USBHID_SDK/Notice_EN.pdf)! 

## Help & Discussions
Get help and submit questions [here](https://github.com/NOLOVR/NOLO-Windows-SDK/issues).

## Updates  
View release notes [here](https://github.com/NOLOVR/NOLO-Windows-SDK/releases).

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

        
        
