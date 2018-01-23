# 快速入门  [English](/HIDGetStarted.md)  
## C/C++工程(VS开发工具)  
1. 新建VS C++工程.
    <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/1.jpg"></div>

2. 点击项目->属性->C/C++->常规->附加目录，加载NOLOVR/NOLO_USBHID_SDK/include. 
    <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/2.jpg"></div> 
    <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/3.jpg"></div> 
    <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/4.jpg"></div> 
    <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/18.jpg"></div>
    <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/19.jpg"></div>

3. 从 NOLOVR/NOLO_USBHID_SDK/bin 目录下选择对应的文件夹（包含dll插件）复制到您的工程目录。\
    V140对应VS2015的运行环境\
    V120对应VS2013的运行环境\
    V110对应VS2012的运行环境
    <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/20.jpg"></div>

4. 开发库依赖：#pragma comment(lib,"[libPathNoLo_USBHID.lib"); 

5. 完成以上步骤之后即可正常使用nolo_api中的其他接口函数.

6. 退出程序时,关闭客户端  
    ```
    NOLO::close_Nolo_Device();
    ```  
## C#工程(VS开发工具)  
1. 新建VS C#工程.
    <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/9.jpg"></div>

2. 复制NOLOVR/NOLO_USBHID_SDK/include/nolo_api.cs文件到工程中.  
    <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/10.jpg"></div>

3. 从 NOLOVR/NOLO_USBHID_SDK/bin 目录下选择对应的文件夹（包含dll插件）复制到您的工程目录。\
    V140对应VS2015的运行环境\
    V120对应VS2013的运行环境\
    V110对应VS2012的运行环境 
    <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/22.jpg"></div>

4. 完成以上步骤之后即可正常使用nolo_api中的其他接口函数.
  
5. 退出程序时，关闭客户端  

    ```
    NOLOClient_V2_API.close_Nolo_Device();
    ```  
    <div><img src="https://github.com/NOLOVR/NOLO-Others/blob/master/Windows-SDK-Others/picture/23.jpg"></div>

#
 
  
