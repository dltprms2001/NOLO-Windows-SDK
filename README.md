# NOLO-windows
NOLO Windows SDK
#
# 要闻速览
  （1）快速说明  
       NOLO在PC端使用ZeroMQ套接字作为低延迟传输，与您选择的任何语言进行交互。它可以在本地和远程通过网络工作.    
       在nolo_driver_for_windows软件运行时，作为PUB and Router ZMQ套接字服务端，通过PUB套接字广播NoloData结构数据包，  
       通过Router套接字接收byte data[64]手柄震动数据包，data[1]表示左手震动强度，data[2]表示右手震动强度。  
       PUB套接字端口号：tcp://*:1314    
       Router套接字端口号：tcp://*:1315  
       
       在noloRuntime,dll运行时，作为SUB and Dealter ZMQ 套接字客户端，通过SUB套接字接收NoloData结构数据包，通过  
       Dealter套接字发送byte data[64]手柄震动数据包.    
       
       nolo_api介绍了noloRuntime.dll插件的接口函数，您可以获取到头部数据,手柄数据,基站数据.您也可以向下发送震动数据.   
   （2）入门  
        1：安装Nolo_driver_for_windows_setup.msi软件
        2：安装NOLO_Windows_Setup.msi软件
        3：bin目录下提供了noloRuntime.dll插件
        4：include目录下提供了nolo_api,详细说明了noloRuntime.dll外接口函数和数据结构.   
       
   （3）使用策略  
        A:您可以自己创建SUB and Dealter ZMQ套接字作为客户端监听PUB and Router 套接字的端口号,获取NoloData结构数据  
          并发送byte data[64]震动数据.   
        B:你也可以通过noloRuntime.dll插件获取nolo数据,我们已经在noloRuntime.dll里实现了对PUB and Sub套接字的监听并  
          提供获取nolo数据和发送震动数据的接口api.  
          
   （4）NOLO_windows软件  
          NOLO_windows软件是使用noloRuntime.dll插件的一个案例，实时监听NOLO数据.  
   （5）nolo API<br>
          nolo api 在incude的目录下，里面提供了noloRuntime.dll的接口函数和数据结构.<br>
          每个接口函数和数据结构体都有详细的注释.
#
        
        
