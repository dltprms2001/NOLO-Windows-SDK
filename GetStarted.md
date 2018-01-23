# Getting started [中文](/GetStarted_CN.md)  
## Preparation
* Install [Nolo_driver_for_windows_setup.msi](https://github.com/NOLOVR/NOLO-Driver-For-Windows/tree/master/NOLOVR)  
* Open Nolo_driver_for_windows.
#
## C/C++Project (Visual Studio IDE)  
1. New VS C++ project.
    <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/1.jpg"/></div>

2. Click Project -> Properties -> C/C++ -> General -> Additional directory, load NOLOVR/include.  
    <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/2.jpg"/></div> 
    <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/3.jpg"/></div> 
    <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/4.jpg"/></div> 
    <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/5.jpg"/></div>
    <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/6.jpg"/></div>

3. Under NOLOVR / bin directory, select the right folder (which includes dll files) to copy to your project directory.  
    * V140 for VS2015 
    * V120 for VS2013  
    * V110 for VS2012

    Note: noloRuntime.dll depends on libzmq.dll  
    <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/7.jpg"/></div>

4. Type in the following code to include the library:
    ```
    #pragma comment(lib,"[libPath]noloRuntime.lib");
    ```

5. Type in the following code to register callback functions and launch Nolo-Driver-For-Windows. 

    ```
    NOLO::disConnect_FunCallBack(disConnectFunc);  
    NOLO::connectSuccess_FunCallBack(connectFunc);  
    NOLO::expandDataNotify_FuncCallBack(expandFunc);  
    NOLO::open_Nolo_ZeroMQ();  
    ```  
6. At this point you should be able to use all interface functions in nolo_api.

7. Upon exiting the program, close the client.  
    ```
    NOLO::close_Nolo_ZeroMQ();
    ```  
    <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/7.jpg"/></div>

## C# Project (Visual Studio IDE)  
1. New VS C# project.
    <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/9.jpg"/></div>

2. Copy the NOLOVR / include / nolo_api.cs file into the project.  
    <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/10.jpg"/></div>

3. Under NOLOVR / bin directory, select the right folder (which includes dll files) to copy to your project directory.
    * V140 for VS2015 
    * V120 for VS2013  
    * V110 for VS2012  
    
    Note: noloRuntime.dll depends on libzmq.dll  
    <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/11.jpg"/></div>

4. Type in the following code to register callback functions and launch Nolo-Driver-For-Windows.

5. At this point you should be able to use all interface functions in nolo_api.

6. Upon exiting the program, close the client. 
    ```
    NOLOClient_V1_API.close_Nolo_ZeroMQ();
    ```  
    <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/12.jpg"/></div>
#