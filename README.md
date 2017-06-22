# NOLO-windows SDK   [中文](https://github.com/NOLOVR/NOLO-Windows-SDK/blob/master/README_CN.md)

- The role and significance of the NOLO Windows SDK  
    * The SDK provides NOLO all the data, including real-time data such as helmets, handles, base stations and so on.  
    * PC helmet developers can use NOLO  data to access  a variety of gaming platforms.  
      Which in the Steam platform, NOLO provided Steam Vr game handle driver, developers only need to access the head positioning data.  
      While on other platforms, such as the Oculus platform, developers can use the handle and helmet data provided by NOLO to access game platform.  
    * Mobile phone cast screen software category developers can use NOLO  data to access  a variety of   gaming platforms.  
      NOLO provides helmet positioning data and rotation data,When the rotation data provided by the handset gyroscope is not stable enough, please select the rotation data provided by NOLO.  
      Which in the Steam platform, NOLO provided Steam Vr game handle driver, developers only need to access the head positioning data.  
      While on other platforms, such as the Oculus platform, developers can use NOLO to provide the handle and helmet data access game platform.   
    * Game developers can use NOLO data to develop various platform games.  
      For Unity game developers can choose NOLO provided Unity SDK.  
      For mobile game developers can choose NOLO provided Android SDK.  
      For other game developers can choose NOLO provided Windows SDK.  
    * Application developers can use the data provided by NOLO to develop a variety of application software.   
   
- [API channels](https://github.com/NOLOVR/NOLO-Windows-SDK/wiki)  

- [Getting started](https://github.com/NOLOVR/NOLO-Windows-SDK/blob/master/GetStarted.md) 
# Precautions
  * Double click on the handle The system button will calibrate the handle posture.
  * For the SteamVR platform, double-click the handle menu button is a key to turn around the function, SteamVR handle will rotate 180 degrees, because we have driver_nolo.dll in the handle positioning data and rotating data conversion, if the developer to add a Key to turn the function, you need to change the head positioning data and rotating data, this can refer to [OSVR-NOLO](https://github.com/NOLOVR/NOLO-Others/tree/master/NOLO_OSVR_SteamvrDriver/Source_Code) source code.  
#
# Changes  
V1
- Add double click the menu button and system key callback notification interface function 
#

        
        
