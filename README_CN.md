# NOLO-windows
NOLO Windows SDK

- 快速入门    
    * :安装[Nolo_driver_for_windows_setup.msi](https://github.com/LYRobotix/NOLO-Driver-For-Windows/raw/master/NOLOVR/Nolo_driver_for_windows_setup.msi)软件.
    * :C/C++工程(VS开发工具)  
        1:新建VS C++工程.  
        2:点击项目->属性->C/C++->常规->附加目录，加载NOLOVR/include.  
        3:在NOLOVR/bin目录下选择需要的dll插件复制到您的工程根目录.  
        4:引用链接#pragma comment(lib,"noloRuntime.lib文件路径").  
        5:注册回调函数,开启客户端.  
        ```
        NOLO::disConnect_FunCallBack(disConnectFunc);  
        NOLO::connectSuccess_FunCallBack(connectFunc);  
        NOLO::expandDataNotify_FuncCallBack(expandFunc);  
        NOLO::open_Nolo_ZeroMQ();  
        ```
        6:正常使用nolo_api中的其他接口函数.  
        7:退出程序时,关闭客户端  
         ```
         NOLO::close_Nolo_ZeroMQ();
         ```
    * :C#工程(VS开发工具)  
        1:新建VS C#工程.  
        2:复制NOLOVR/include/nolo_api.cs文件到工程中.  
        3:在NOLOVR/bin中选择需要的dll复制到您的工程根目录下.  
        4:注册回调函数，开启客户端  
        ```
        NOLOClient_V1_API.connectSuccess_FunCallBack(connectFunc);
        NOLOClient_V1_API.disConnect_FunCallBack(disConnectFunc);
        NOLOClient_V1_API.expandDataNotify_FuncCallBack(expandDataFunc);
        NOLOClient_V1_API.open_Nolo_ZeroMQ();
        ```
        5:正常使用nolo_api.cs中的其他接口函数  
        6:退出程序时，关闭客户端  
        ```
        NOLOClient_V1_API.close_Nolo_ZeroMQ();
        ```

        
- [接口说明](https://github.com/LYRobotix/NOLO-Windows-SDK/wiki)
#