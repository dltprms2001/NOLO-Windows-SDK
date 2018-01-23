# Getting started [中文](/HIDGetStarted_CN.md)  

## C/C++Project (Visual Studio IDE)  

1. New VS C ++ project.
    <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/1.jpg"/></div>

2. Click Project -> Properties -> C / C ++ -> General -> Additional directory, load NOLOVR/NOLO_USBHID_SDK/include.  
    <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/2.jpg"/></div> 
    <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/3.jpg"/></div> 
    <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/4.jpg"/></div> 
    <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/18.jpg"/></div>
    <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/19.jpg"/></div>

3. Under NOLOVR/NOLO_USBHID_SDK/bin directory, select the right folder (which includes dll files) to copy to your project directory.\
    V140 for VS2015\
    V120 for VS2013\
    V110 for VS2012 
    <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/20.jpg"/></div>

4. Type in the following code to include the library:
    ```
    #pragma comment(lib,"[libPathNoLo_USBHID.lib");
    ```

5. At this point you should be able to use all interface functions in nolo_api.

6. Upon exiting the program, close the client.  
    ```
    NOLO::close_Nolo_Device();
    ```  

## C# Project (Visual Studio IDE)

1. New VS C# project.
    <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/9.jpg"/></div>

2. Copy the NOLOVR/NOLO_USBHID_SDK / include / nolo_api.cs file into the project.  
    <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/10.jpg"/></div>

3. Under NOLOVR/NOLO_USBHID_SDK/bin directory, select the right folder (which includes dll files) to copy to your project directory.\
    V140 for VS2015\
    V120 for VS2013\
    V110 for VS2012   
    <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/22.jpg"/></div>

4. At this point you should be able to use all interface functions in nolo_api. 

5. Upon exiting the program,close the client. 
    ```
    NOLOClient_V2_API.close_Nolo_Device();
    ```  
    <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/23.jpg"/></div>
#