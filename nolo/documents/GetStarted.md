# Get Start
如下图所示，NOLO设备共由基站、头盔定位器和手柄三部分构成，基站和手柄以无线通信的方式与头盔定位器交互，头盔定位器将数据汇总后通过USB协议与电脑双向通信，电脑端Nolo_driver_for_windows软件可获得NOLO设备的数据信息，并通过ZeroMQ协议与nolo_api进行双向数据传输。其中，Nolo_driver_for_windows软件是PUB and Router ZMQ套接字的服务端，noloRuntime.dll是SUB and Dealter ZMQ套接字的客户端。  
  
  
As shown in the figure below, the NOLO device consists of a base station, a headset marker and two controllers, the base station and the controllers interact with the headset marker in a wireless communication. The headset marker gather the data and communicate with computer in two-way through the USB protocol. Computer-side Nolo_driver_for_windows software can get the data information of NOLO device, and transfer data to nolo_api in two-way through the ZeroMQ protocol. Nolo_driver_for_windows software is the socket server of PUB and Router ZMQ, noloRuntime.dll is the socket client of SUB and Dealer ZMQ.
