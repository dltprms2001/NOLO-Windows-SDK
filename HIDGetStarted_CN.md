
# 快速入门  [English](https://github.com/NOLOVR/NOLO-Windows-SDK/blob/master/HIDGetStarted.md)  
* :C/C++工程(VS开发工具)  
    1:新建VS C++工程.
         <div><img width=400 heigh=200 src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/1.jpg"></div>
    2:点击项目->属性->C/C++->常规->附加目录，加载NOLOVR/NOLO_USBHID_SDK/include. 
        <div><img width=400 heigh=200 src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/2.jpg"></div> 
        <div><img width=400 heigh=200 src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/3.jpg"></div> 
        <div><img width=400 heigh=200 src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/4.jpg"></div> 
        <div><img width=400 heigh=200 src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/18.jpg"></div>
        <div><img width=400 heigh=200 src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/19.jpg"></div>
    3:在NOLOVR/NOLO_USBHID_SDK/bin目录下选择需要的dll插件复制到您的工程目录.   
        V140对应VS2015的运行环境  
        V120对应VS2013的运行环境  
        V110对应Vs2012的运行环境  
        <div><img width=400 heigh=200 src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/20.jpg"></div>
    4:引用链接#pragma comment(lib,"NoLo_USBHID.lib文件路径").  

    5:正常使用nolo_api中的其他接口函数.  

    6:退出程序时,关闭客户端  
    ```
         NOLO::close_Nolo_Device();
    ```  
    * :C#工程(VS开发工具)  

    1:新建VS C#工程.
        <div><img width=400 heigh=200 src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/9.jpg"></div>
    2:复制NOLOVR/NOLO_USBHID_SDK/include/nolo_api.cs文件到工程中.  
        <div><img width=400 heigh=200 src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/10.jpg"></div>
    3:在NOLOVR/NOLO_USBHID_SDK/bin中选择需要的dll复制到您的工程目录下.  
        V140对应VS2015的运行环境  
        V120对应VS2013的运行环境  
        V110对应Vs2012的运行环境  
        <div><img width=400 heigh=200 src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/22.jpg"></div>

    4:正常使用nolo_api.cs中的其他接口函数  

    5:退出程序时，关闭客户端  

    ```
        NOLOClient_V2_API.close_Nolo_Device();
    ```  
    <div><img width=400 heigh=200 src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/23.jpg"></div>

#
 
  
