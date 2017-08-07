# NOLO-windows SDK 

- NOLO Windows SDK的作用和意义  
    * SDK提供了NOLO所有数据,包括了头盔、手柄、基站等实时数据.  
    * PC头盔类的开发者可以使用NOLO提供的数据接入各游戏平台.  
      其中在Steam平台上,NOLO提供了玩Steamvr游戏的手柄驱动,开发者只需要接入头部定位数据就行.  
      而在其他平台,如Oculus平台，开发者可以使用NOLO提供的手柄和头盔数据接入游戏平台.  
    * 手机投屏软件类的开发者可以使用NOLO提供的数据接入各游戏平台.  
      NOLO提供了头盔的定位数据和姿态数据,当手机陀螺仪提供的姿态数据不够稳定时请选择NOLO提供的姿态数据.  
      其中在Steam平台上,NOLO提供了玩Steamvr游戏的手柄驱动,开发者只需要接入头部定位数据就行.  
      而在其他平台,如Oculus平台，开发者可以使用NOLO提供的手柄和头盔数据接入.  
    * 游戏类的开发者可以使用NOLO提供的数据开发各平台游戏.  
      对于Unity游戏开发者可以选择NOLO提供的Unity SDK.  
      对于Mobile游戏开发者可以选择NOLO提供的Android SDK.
      对于其他游戏开发者可以选择NOLO提供的Windows SDK.  
    * 应用类的开发者可以使用NOLO提供的数据开发各种应用软件.  
   

- [快速入门](https://github.com/NOLOVR/NOLO-Windows-SDK/blob/master/GetStarted_CN.md)  
- [注意事项]()

# 变化  
NOLO ZEROMQ SDK:  
V1
- 2017/5/31 
  * 添加双击手柄menu和system按键回调通知接口函数  
- 2017/7/7  
  * 添加noloRuntime从NOLO PC 软件接收到数据立刻回调通知  
#
NOLO USBHID SDK:  
V1
- 2017/8/7
  * 发布
#