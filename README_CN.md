# NOLO-windows
NOLO Windows SDK
#
# 要闻速览
  （1）快速说明  
       NOLO使用ZeroMQ套接字作为低延迟传输，与您选择的任何语言进行交互.它可以在本地和远程通过网络工作.  
       详细介绍请参阅ZeroMQ官网：http://zeromq.org/    
       我们采用了PUB And Router ZMQ套接字作为服务端,Sub And Dealter ZMQ套接字作为客户端,服务端PUB  
       套接字进行单向广播数据包,Router套接字进行单向接收数据包,客户端Sub套接字进行单向接收数据包,Dealter套接字进行单向发送数据包。
       通过Router套接字接收byte data[64]手柄震动数据包,data[1]表示左手震动强度,data[2]表示右手震动强度.  
       Router套接字端口号：tcp://*:1315  
       PUB套接字端口号:tcp://*:1314  
       Nolo_driver_for_windows软件作为NOLO ZeroMQ服务端  
       noloRuntime.dll作为NOLO ZeroMQ客户端  
       NOLO_Windows软件是使用noloRuntime.dll的一个参考案例，实时监听NOLO服务端数据以及向服务端发送震动数据.  
   （2）入门   
        1：安装Nolo_driver_for_windows_setup.msi软件(必须).   
        2：安装NOLO_Windows_Setup.msi软件(可选).  
        3：bin目录下提供了noloRuntime.dll插件以及所依赖的插件.  
        4：include目录下提供了nolo_api,详细说明了noloRuntime.dll外接口函数和数据结构.    
        5: ducuments目录下提供了NoloVrWindows sdk的详细说明.  
#
        
        
