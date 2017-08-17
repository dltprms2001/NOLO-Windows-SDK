# NOLO-windows SDK   [中文](https://github.com/NOLOVR/NOLO-Windows-SDK/blob/master/README_CN.md)

- The role and significance of the NOLO Windows SDK  
    * The SDK provides all data of NOLO, including real-time data from headset marker, controllers, base station and so on. 
    * PC helmet developers can use NOLO  data to access  a variety of gaming platforms.  
    * Mobile phone projection screen software developers can use NOLO data to access a variety of game platforms.  
      NOLO provides tracking and rotation data of headset marker.Please use the rotation data provided by NOLO, when the rotation data provided by the handset gyroscope is not stable.  
    * Game developers can use NOLO data to develop games on various platforms.  
      Unity game developers can choose Unity SDK provided by NOLO.  
      Mobile game developers can choose Android SDK provided by NOLO.  
      Other game developers can choose Windows SDK provided by NOLO.  
    * Application developers can use the data provided by NOLO to develop a variety of application software.   
## NOLO USBHID SDK [Getting started](https://github.com/NOLOVR/NOLO-Windows-SDK/blob/master/HIDGetStarted.md) 
    NOLO USBHID SDK directly reads NOLO tracking data through USB.  
     Under this situation,you do not need to install NOLO PC software when you're developing.
#
## NOLO ZEROMQ SDK [Getting started](https://github.com/NOLOVR/NOLO-Windows-SDK/blob/master/GetStarted.md) 
    NOLO ZEROMQ SDK reads data on NOLO PC software via ZEROMQ network transfer protocol  
    Under this situation,you need to install NOLO PC software when you're developing.  
    nolo pc software acquiescently provides steamvr controller driver. 
#


# [Notice](https://github.com/NOLOVR/NOLO-Windows-SDK/blob/master/NOLOVR/NOLO_USBHID_SDK/Notice_EN.pdf)
# [Use case](https://github.com/NOLOVR/NOLO-Windows-SDK/tree/master/Examples)
# Changes  
NOLO ZEROMQ SDK:  
V1
- 2017/5/31  
  * Add double click the menu button and system key callback notification interface function 
- 2017/7/7  
  * Add noloRuntime receive data from NOLO PC software callback notification immediately  
#
NOLO USBHID SDK:  
V1
- 2017/8/7
  * release
#

        
        
