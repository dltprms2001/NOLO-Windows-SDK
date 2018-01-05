# NOLO-windows SDK    
* SDK提供了NOLO所有数据,包括了头盔、手柄、基站等实时数据. 
* PC头盔类的开发者可以使用NOLO提供的数据接入各游戏平台.  
* 手机投屏软件类的开发者可以使用NOLO提供的数据接入各游戏平台.  
NOLO提供了头盔的定位数据和姿态数据,当手机陀螺仪提供的姿态数据不够稳定时请选择NOLO提供的姿态数据.  
* 游戏类的开发者可以使用NOLO提供的数据开发各平台游戏.  
对于Unity游戏开发者可以选择NOLO提供的Unity SDK.  
对于Mobile游戏开发者可以选择NOLO提供的Android SDK.  
对于其他游戏开发者可以选择NOLO提供的Windows SDK.  
* 应用类的开发者可以使用NOLO提供的数据开发各种应用软件. 
#
## NOLO USBHID SDK [快速入门](https://github.com/NOLOVR/NOLO-Windows-SDK/blob/master/HIDGetStarted_CN.md) 
    NOLO USBHID SDK直接通过USB线读取NOLO定位数据，开发时不需要安装NOLO PC软件.  
    
#
## NOLO ZEROMQ SDK  [快速入门](https://github.com/NOLOVR/NOLO-Windows-SDK/blob/master/GetStarted_CN.md) 
    NOLO ZEROMQ SDK通过ZEROMQ网络传输协议从NOLO PC软件读取数据，开发时需要安装NOLO PC软件.    
    NOLO PC软件默认提供SteamVR手柄驱动.  
#
## 参考案例
[使用案例](https://github.com/NOLOVR/NOLO-Windows-SDK/tree/master/Examples)

## 注意事项
Nolo 的位置和姿态坐标系与 OpenVR 不同，详情点击[此处](https://github.com/NOLOVR/NOLO-Windows-SDK/blob/master/NOLOVR/NOLO_USBHID_SDK/Notice_CN.pdf)。

## 版本历史  
详情点击[此处](https://github.com/NOLOVR/NOLO-Windows-SDK/releases)。