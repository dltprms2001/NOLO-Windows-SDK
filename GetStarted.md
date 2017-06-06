# Getting started[中文]()  
* :Install[Nolo_driver_for_windows_setup.msi](https://github.com/NOLOVR/NOLO-Driver-For-Windows/raw/master/NOLOVR/Nolo_driver_for_windows_setup.msi) software.  
* :Open Nolo_driver_for_windows software.  
* :C/C++Project(VS development tools)  

    1: New VS C ++ project.
        <div><img width=400 heigh=200 src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/1.jpg"/></div>
    2: Click Project -> Properties -> C / C ++ -> General -> Additional directory,load NOLOVR/include.  
        <div><img width=400 heigh=200 src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/2.jpg"/></div> 
        <div><img width=400 heigh=200 src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/3.jpg"/></div> 
        <div><img width=400 heigh=200 src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/4.jpg"/></div> 
        <div><img width=400 heigh=200 src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/5.jpg"/></div>
        <div><img width=400 heigh=200 src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/6.jpg"/></div>
    3:In the NOLOVR / bin directory, select the dll plugin to copy to your project directory.  
        V140-VS2015 operating environment  
        V120-VS2013 operating environment  
        V110-Vs2012 operating environment  
        NoloRuntime.dll depends on libzmq.dll  
        <div><img width=400 heigh=200 src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/7.jpg"/></div>
    4:Reference link #pragma comment(lib,"noloRuntime.lib file path").  
    5:Register the callback function,Open the client.  

    ```
        NOLO::disConnect_FunCallBack(disConnectFunc);  
        NOLO::connectSuccess_FunCallBack(connectFunc);  
        NOLO::expandDataNotify_FuncCallBack(expandFunc);  
        NOLO::open_Nolo_ZeroMQ();  
    ```  
    6:Normal use of other interface functions in nolo_api.  
    7:When exiting the program,close the client.  
    ```
         NOLO::close_Nolo_ZeroMQ();
    ```  

    <div><img width=400 heigh=200 src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/7.jpg"/></div>

* :C# Project(VS development tools)  
    1: New VS C# project.
        <div><img width=400 heigh=200 src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/9.jpg"/></div>
    2: Copy the NOLOVR / include / nolo_api.cs file into the project.  
        <div><img width=400 heigh=200 src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/10.jpg"/></div>
    3:In the NOLOVR / bin select dll copy to your project directory.  
        V140-VS2015 operating environment  
        V120-VS2013 operating environment  
        V110-Vs2012 operating environment  
        NoloRuntime.dll depends on libzmq.dll  
    <div><img width=400 heigh=200 src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/11.jpg"/></div>
    4:Register the callback function,Open the client.  

    5:Normal use of other interface functions in nolo_api.cs.  
    6:When exiting the program,close the client. 
    ```
        NOLOClient_V1_API.close_Nolo_ZeroMQ();
    ```  
    <div><img width=400 heigh=200 src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/12.jpg"/></div>
#