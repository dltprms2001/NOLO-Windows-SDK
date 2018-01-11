# NOLO-Windows-SDK    
* 下列两个版本的 Window SDK 均提供所有 NOLO 数据，包括头盔、手柄、基站等实时数据。**注意：我们已停止 ZEROMQ 版本的更新和维护，开发者请选择 USBHID 版本进行开发。**
* PC头盔类的开发者可以使用NOLO提供的数据接入各游戏平台。  
* 手机投屏软件类的开发者可以使用NOLO提供的数据接入各游戏平台。  
NOLO提供了头盔的定位数据和姿态数据,当手机陀螺仪提供的姿态数据不够稳定时请选择NOLO提供的姿态数据。  
* 游戏类的开发者可以使用NOLO提供的数据开发各平台游戏。  
对于Unity游戏开发者可以选择NOLO提供的 [Unity SDK](https://github.com/NOLOVR/NOLO-Unity-SDK)。  
对于Mobile游戏开发者可以选择NOLO提供的 [Android SDK](https://github.com/NOLOVR/NOLO-Android-SDK)。  
对于其他游戏开发者可以选择NOLO提供的 Windows SDK（本SDK）。  
* 应用类的开发者可以使用NOLO提供的数据开发各种应用软件。
#
## 快速入门
### **[NOLO-USBHID-SDK](https://github.com/NOLOVR/NOLO-Windows-SDK/tree/master/NOLOVR/NOLO_USBHID_SDK) [使用说明](/HIDGetStarted_CN.md)**
    NOLO-USBHID-SDK 直接通过 USB 线读取 NOLO 定位数据，开发时不需要安装 NOLO PC 软件.  
    
### [NOLO-ZEROMQ-SDK](https://github.com/NOLOVR/NOLO-Windows-SDK/tree/master/NOLOVR/NOLO_ZEROMQ_SDK) [使用说明](/GetStarted_CN.md) （注意：此版本已停止更新）
    NOLO-ZEROMQ-SDK 通过 ZEROMQ 网络传输协议从 NOLO PC 软件读取数据，开发时需要安装 NOLO PC 软件.    
    NOLO PC 软件默认提供 SteamVR 手柄驱动.  
#
## 参考案例
[使用案例](https://github.com/NOLOVR/NOLO-Windows-SDK/tree/master/Examples)

## 注意事项
Nolo 的位置和姿态坐标系与 OpenVR 不同，详情点击[此处](https://github.com/NOLOVR/NOLO-Windows-SDK/blob/master/NOLOVR/NOLO_USBHID_SDK/Notice_CN.pdf)。

## 版本历史  
详情点击[此处](https://github.com/NOLOVR/NOLO-Windows-SDK/releases)。