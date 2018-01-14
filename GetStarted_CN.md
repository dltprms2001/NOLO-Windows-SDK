# 快速入门  [English](/GetStarted.md) 
## 准备工作 
* 安装 [Nolo_driver_for_windows_setup.msi](https://github.com/NOLOVR/NOLO-Driver-For-Windows/tree/master/NOLOVR) 软件.
* 启动 Nolo_driver_for_windows 软件.  
#
## C/C++工程 (VS开发工具)  
1. 新建VS C++工程.
     <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/1.jpg"></div>

2. 点击项目->属性->C/C++->常规->附加目录，加载NOLOVR/include. 
    <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/2.jpg"></div> 
    <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/3.jpg"></div> 
    <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/4.jpg"></div> 
    <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/5.jpg"></div>
    <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/6.jpg"></div>

3. 从 NOLOVR/bin 目录下选择对应的文件夹（包含dll插件）复制到您的工程目录。\
    V140对应VS2015的运行环境  
    V120对应VS2013的运行环境  
    V110对应VS2012的运行环境  
    注意：noloRuntime.dll 依赖于 libzmq.dll   
    <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/7.jpg"></div>

4. 开发库依赖：#pragma comment(lib,"[libPath]noloRuntime.lib");

5. 键入以下代码注册回调函数, 并自动启动 Nolo Driver for Windows
    ```
    NOLO::disConnect_FunCallBack(disConnectFunc);  
    NOLO::connectSuccess_FunCallBack(connectFunc);  
    NOLO::expandDataNotify_FuncCallBack(expandFunc);  
    NOLO::open_Nolo_ZeroMQ();  
     ```  

6. 完成以上步骤之后即可正常使用nolo_api中的其他接口函数.

7. 退出程序时, 关闭客户端  
    ```
    NOLO::close_Nolo_ZeroMQ();
    ```  
    <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/8.jpg"></div>

 ## C#工程 (VS开发工具)  

1. 新建VS C#工程.
    <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/9.jpg"></div>

2. 复制NOLOVR/include/nolo_api.cs文件到工程中.  
    <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/10.jpg"></div>

3. 从 NOLOVR/bin 目录下选择对应的文件夹（包含dll插件）复制到您的工程目录。\
    V140对应VS2015的运行环境  
    V120对应VS2013的运行环境  
    V110对应VS2012的运行环境  
    注意：noloRuntime.dll 依赖于 libzmq.dll  
    <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/11.jpg"></div>

4. 键入以下代码注册回调函数, 并自动启动 Nolo Driver for Windows

    ```
    NOLOClient_V1_API.connectSuccess_FunCallBack(connectFunc);
    NOLOClient_V1_API.disConnect_FunCallBack(disConnectFunc);
    NOLOClient_V1_API.expandDataNotify_FuncCallBack(expandDataFunc);
    NOLOClient_V1_API.open_Nolo_ZeroMQ();
    ```  

5. 完成以上步骤之后即可正常使用nolo_api中的其他接口函数.

6. 退出程序时，关闭客户端  

    ```
    NOLOClient_V1_API.close_Nolo_ZeroMQ();
    ```  
    <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/12.jpg"></div>

#
 
  
