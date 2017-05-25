# NOLO-windows
NOLO Windows SDK
#
# 要闻速览
  （1）快速说明  
      如下图所示,NOLO设备共由基站、头盔定位器和手柄三部分构成,基站和手柄以无线通信的方式与头盔定位器交互,  
      头盔定位器将数据汇总后通过USB协议与电脑双向通信,电脑端Nolo_driver_for_windows软件可获得NOLO设备的  
      数据信息,并通过ZeroMQ协议与nolo_api进行双向数据传输.其中,Nolo_driver_for_windows软件是PUB and  
      Router ZMQ套接字的服务端,noloRuntime.dll是SUB and Dealter ZMQ套接字的客户端.  
   （2）入门    
        1: 安装vc_redist.x64.exe.  
        2：安装Nolo_driver_for_windows_setup.msi软件(必须).<br>   
        3：安装NOLO_Windows_Setup.msi软件(可选).  
        4：bin目录下提供了noloRuntime.dll插件以及所依赖的插件.  
        5：include目录下提供了nolo_api,详细说明了noloRuntime.dll外接口函数和数据结构.<br>   
        6: ducuments目录下提供了NoloVrWindows sdk的详细说明.  
#
