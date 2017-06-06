
# 快速入门  [English]()  
* :安装[Nolo_driver_for_windows_setup.msi](https://github.com/NOLOVR/NOLO-Driver-For-Windows/raw/master/NOLOVR/Nolo_driver_for_windows_setup.msi)软件.
* :启动Nolo_driver_for_windows软件.  
* :C/C++工程(VS开发工具)  
    1:新建VS C++工程.
         <div><img width=400 heigh=200 src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/1.jpg"></div>
    2:点击项目->属性->C/C++->常规->附加目录，加载NOLOVR/include. 
        <div><img width=400 heigh=200 src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/2.jpg"></div> 
        <div><img width=400 heigh=200 src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/3.jpg"></div> 
        <div><img width=400 heigh=200 src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/4.jpg"></div> 
        <div><img width=400 heigh=200 src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/5.jpg"></div>
        <div><img width=400 heigh=200 src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/6.jpg"></div>
    3:在NOLOVR/bin目录下选择需要的dll插件复制到您的工程目录.   
        V140对应VS2015的运行环境  
        V120对应VS2013的运行环境  
        V110对应Vs2012的运行环境  
        noloRuntime.dll依赖libzmq.dll   
        <div><img width=400 heigh=200 src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/7.jpg"></div>
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
    <div><img width=400 heigh=200 src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/8.jpg"></div>
    * :C#工程(VS开发工具)  

    1:新建VS C#工程.
        <div><img width=400 heigh=200 src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/9.jpg"></div>
    2:复制NOLOVR/include/nolo_api.cs文件到工程中.  
        <div><img width=400 heigh=200 src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/10.jpg"></div>
    3:在NOLOVR/bin中选择需要的dll复制到您的工程目录下.  
        V140对应VS2015的运行环境  
        V120对应VS2013的运行环境  
        V110对应Vs2012的运行环境  
        noloRuntime.dll依赖libzmq.dll   
        <div><img width=400 heigh=200 src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/11.jpg"></div>

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
    <div><img width=400 heigh=200 src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/12.jpg"></div>

#
 
  
