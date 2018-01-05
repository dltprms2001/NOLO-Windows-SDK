# Getting started [中文](/HIDGetStarted_CN.md)  

* :C/C++Project(VS development tools)  

    1: New VS C ++ project.
        <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/1.jpg"/></div>
    2: Click Project -> Properties -> C / C ++ -> General -> Additional directory,load NOLOVR/include.  
        <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/2.jpg"/></div> 
        <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/3.jpg"/></div> 
        <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/4.jpg"/></div> 
        <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/18.jpg"/></div>
        <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/19.jpg"/></div>
    3:In the NOLOVR / bin directory, select the dll plugin to copy to your project directory.  
        V140-VS2015 operating environment  
        V120-VS2013 operating environment  
        V110-Vs2012 operating environment  
        <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/20.jpg"/></div>
    4:Reference link #pragma comment(lib,"NoLo_USBHID.lib file path").  

    5:Normal use of other interface functions in nolo_api. 

    6:When exiting the program,close the client.  
    ```
         NOLO::close_Nolo_Device();
    ```  

* :C# Project(VS development tools)  
    1: New VS C# project.
        <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/9.jpg"/></div>
    2: Copy the NOLOVR/NOLO_USBHID_SDK / include / nolo_api.cs file into the project.  
        <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/10.jpg"/></div>
    3:In the NOLOVR/NOLO_USBHID_SDK / bin select dll copy to your project directory.  
        V140-VS2015 operating environment  
        V120-VS2013 operating environment  
        V110-Vs2012 operating environment  
    <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/22.jpg"/></div>

    4:Normal use of other interface functions in nolo_api.cs.  

    5:When exiting the program,close the client. 

    ```
        NOLOClient_V2_API.close_Nolo_Device();
    ```  
    <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/23.jpg"/></div>
#