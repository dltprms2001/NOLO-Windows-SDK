# NOLO-Windows-SDK [中文](https://github.com/NOLOVR/NOLO-Windows-SDK/blob/master/README_CN.md)
You can use **either** SDK listed below to develop Windows game(s) that supports NOLO.\
Both SDKs provide all data from NOLO, including real-time data from headset marker, controllers and base station. **You should choose to incorporate either one into your game(s).**

#
## Getting Started
### NOLO-USBHID-SDK [Downloads](https://github.com/NOLOVR/NOLO-Windows-SDK/tree/master/NOLOVR/NOLO_USBHID_SDK), [Instructions](/HIDGetStarted.md)

    NOLO-USBHID-SDK reads NOLO tracking data directly through USB port.  
    In this case, you DON'T need to install NOLO PC software (NOLO Driver for Windows) during development.

### NOLO-ZEROMQ-SDK [Downloads](https://github.com/NOLOVR/NOLO-Windows-SDK/tree/master/NOLOVR/NOLO_ZEROMQ_SDK), [Instructions](/GetStarted.md)

    NOLO-ZEROMQ-SDK reads data from NOLO PC software via ZEROMQ network transfer protocol.  
    In this case, you'll need to install NOLO PC software (NOLO Driver for Windows, available on github.com/nolovr) during development.
    Notice that NOLO PC software acquiescently provides steamvr controller driver. 
#
## Examples
See examples [here](https://github.com/NOLOVR/NOLO-Windows-SDK/tree/master/Examples).

## Notes
- **IMPORTANT!** NOLO's coordinate system is different from that of OpenVR. Read details [here](https://github.com/NOLOVR/NOLO-Windows-SDK/blob/master/NOLOVR/NOLO_USBHID_SDK/Notice_EN.pdf)!

- Developers can use NOLO data to communicate with a variety of game platforms.\
NOLO's headset marker provides both position and rotation data. You can use data from NOLO if data from your Helmet-Mounted-Display(HMD)'s IMU is not stable. 

- Game developers can use NOLO to develop games on various platforms.\
Unity developers can use [Unity SDK](https://github.com/NOLOVR/NOLO-Unity-SDK) provided by NOLO.  
Native Android developers can use [Android SDK](https://github.com/NOLOVR/NOLO-Android-SDK) provided by NOLO.\
Windows developers can use Windows SDK (this SDK) provided by NOLO. 

## Help & Discussions
Get help and submit questions [here](https://github.com/NOLOVR/NOLO-Windows-SDK/issues).

## Release notes  
View release notes [here](https://github.com/NOLOVR/NOLO-Windows-SDK/releases).