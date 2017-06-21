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
   
- [接口说明](https://github.com/NOLOVR/NOLO-Windows-SDK/wiki)  

- [快速入门](https://github.com/NOLOVR/NOLO-Windows-SDK/blob/master/GetStarted_CN.md)  
# 注意事项
  * 双击手柄system按键将会标定手柄姿态.
  * 对于SteamVR平台,双击手柄menu按键是一键转身功能,SteamVR中的手柄将会旋转180度,是因为我们已经在driver_nolo.dll里对手柄数据进行了坐标系转换和姿态变换,如果对接NOLO-Windows-SDK的开发者要添加一键转身功能时，需要对头部数据进行坐标系转换和姿态变换,这个可以参考[OSVR-NOLO](https://github.com/NOLOVR/NOLO-Others/tree/master/NOLO_OSVR_SteamvrDriver/Source_Code)的源码.
#
# 变化  
V1
- 添加双击手柄menu和system按键回调通知接口函数
#