# NOLO-windows
NOLO Windows SDK
#
# Quick description  
    NOLO users ZeroMQ sockets as a low-latency transmission to interact with any language of your choice.  
    It can work locally and remotely over the network.For more information, please refer to ZeroMQ website:http://zeromq.org/  
    We use the PUB And Router ZMQ socket as a server,Sub And Dealter ZMQ socket as a client.Server PUB socket for   
    unidirectional broadcast packets, Router socket to receive packets in one direction, the client Sub socket to   
    receive packets in one direction, Dealer socket for one-way to send packets Receive byte data through the Router  
    socket [64] handle vibration data packet, data [1] that left hand vibration intensity, data [2] that the right hand vibration  
    intensity.  
    Router socket port number:tcp://*:1315.  
    PUB socket port number:tcp://*:1314.  
    Nolo_driver_for_windows software as a NOLO ZeroMQ server.  
    NoloRuntime.dll as the NOLO ZeroMQ client.  
    NOLO_Windows software is a reference case using noloRuntime.dll, real-time monitoring NOLO server-side data   
    and send vibration data to the server.
#
# Getting started  
    1: Install Nolo_driver_for_windows_setup.msi software (required).  
    2: Install the NOLO_Windows_Setup.msi software (optional).  
    3: Bin directory provides the noloRuntime.dll plugin and the dependent plugins.  
    4: The include directory provides nolo_api, detailing the outer interface functions and data structures of noloRuntime.dll.  
    5: The ducuments directory provides a detailed description of NoloVrWindows sdk.
#
        
        
