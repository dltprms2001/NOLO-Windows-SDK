using System;
using System.Runtime.InteropServices;
namespace NOLO
{
    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public struct Vector3
    {
        public float x;
        public float y;
        public float z;

    }
    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public struct Vector2
    {
        public float x;
        public float y;
    }
    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public struct Quaternion
    {
        public float x;
        public float y;
        public float z;
        public float w;
    }
    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    //nolo controller struct
    public struct Controller
    {

        public int ControllerVersionID;

        public Vector3 ControllerPosition;

        public Quaternion ControllerRotation;
        /*
		  0x0000_XXX1:press
          0x0000_XX1X:trigger
          0x0000_X1XX:menu
          0x0000_1XXX:system
          0x0001_XXXX:grip
		*/
        public uint Buttons;
        ///nolo touch
		public int ControllerTouched;
        /*
		   x:-1~1
		   y:-1~1
		*/
        public Vector2 ControllerTouchAxis;
        /*
		  0~100：normal
		  255:Shut down
		*/
        public int ControllerBattery;
        /*
		  0：Be blocked
		  1：normal
		*/
        public int state;
    };
    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    ///nolo head tracking struct
    public struct HMD
    {
        ///Handle version ID
		public int HMDVersionID;

        public Vector3 HMDPosition;
        ///Handle Init Position 
		public Vector3 HMDInirPostion;

        public uint HMDTwoPointDriftAngle;

        public Quaternion HMDRotation;
        /*
		  0：Be blocked
		  1：normal
		*/
        public int state;
    }
    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    ///nolo base station struct
    public struct BaseStation
    {
        ///base station version id
		public int BaseStationVersionID;
        /*
		  0~100:normal
		*/
        public int BaseStationPower;
    }
    /// nolo Device type enumerate
    public enum NoloDeviceType
    {
        HmdDevice = 0,
        LeftControllerDevice = 1,
        RightControllerDevice = 2,
        BaseStationOne = 3,
    };

    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public struct Nolo_Pose
    {
        public Vector3 pos;
        public Quaternion rot;
    };
    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    //
    public struct ControllerStates
    {
        /*
           0x0000_XXX1:press
           0x0000_XX1X:trigger
           0x0000_X1XX:menu
           0x0000_1XXX:system
           0x0001_XXXX:grip
         */
        public uint noloButtons;
        ///Handle with touch
        public uint noloButtonTouch;
        /*
		   x:-1~1
		   y:-1~1
		*/
        public Vector2 touchpadAxis;
    };
    [UnmanagedFunctionPointer(CallingConvention.StdCall)]
    public delegate void funcCallback();


    public class ClientAPI
    {
	    ///Open the ZeroMQ client to recevice nolo data
        [DllImportAttribute("noloRuntime", CallingConvention = CallingConvention.StdCall, EntryPoint = "open_Nolo_ZeroMQ")]
        public  static extern bool open_Nolo_ZeroMQ();
        ///Close the ZeroMQ client to release the resource
        [DllImportAttribute("noloRuntime", CallingConvention = CallingConvention.StdCall, EntryPoint = "close_Nolo_ZeroMQ")]
        public  static extern void close_Nolo_ZeroMQ();
		///NoloRuntime.dll calls this method as a ZeroMQ socket client when disconnected to the server
        [DllImportAttribute("noloRuntime", CallingConvention = CallingConvention.StdCall, EntryPoint = "disConnenct_FunCallBack")]
        public static extern bool disConnenct_FunCallBack(funcCallback funcCallBace);
		///NoloRuntime.dll calls this method as a ZeroMQ socket client when connected to the server
        [DllImportAttribute("noloRuntime", CallingConvention = CallingConvention.StdCall, EntryPoint = "connectSuccess_FunCallBack")]
        public static extern bool connectSuccess_FunCallBack(funcCallback funcCallBace);
		///According to the type of equipment and vibration intensity to send data packets to the nolo server
        [DllImportAttribute("noloRuntime", CallingConvention = CallingConvention.StdCall, EntryPoint = "set_Nolo_TriggerHapticPulse")]
        public static extern void set_Nolo_TriggerHapticPulse(NoloDeviceType deviceType, int intensity);

	    ///returns nolo controller data
        [DllImportAttribute("noloRuntime", CallingConvention = CallingConvention.StdCall, EntryPoint = "get_Nolo_LeftControllerData")]
        public static extern Controller get_Nolo_LeftControllerData();

		///returns nolo controller data
        [DllImportAttribute("noloRuntime", CallingConvention = CallingConvention.StdCall, EntryPoint = "get_Nolo_RightControllerData")]
        public static extern Controller get_Nolo_RightControllerData();
		///returns nolo head tracking data
        [DllImportAttribute("noloRuntime", CallingConvention = CallingConvention.StdCall, EntryPoint = "get_Nolo_HMDData")]
        public static extern HMD get_Nolo_HMDData();
		/*
			returns nolo Expand data 
			return byte ExpandData[64]
			ExpandData[0]>>0 :Double click Menu
			ExpandData[1]>>1 :Double click system
		*/
        [DllImportAttribute("noloRuntime", CallingConvention = CallingConvention.StdCall, EntryPoint = "get_Nolo_ExpandData")]
        public static extern IntPtr get_Nolo_ExpandData();

		///returns nolo init head tracking data
        [DllImportAttribute("noloRuntime", CallingConvention = CallingConvention.StdCall, EntryPoint = "get_Nolo_HMDInirPostion")]
        public static extern Vector3 get_Nolo_HMDInirPostion();
		///returns nolo device state by device type
        [DllImportAttribute("noloRuntime", CallingConvention = CallingConvention.StdCall, EntryPoint = "get_Nolo_StateByDeviceType")]
        public static extern int get_Nolo_StateByDeviceType(NoloDeviceType devicetype);

		///returns nolo device battery by device type
        [DllImportAttribute("noloRuntime", CallingConvention = CallingConvention.StdCall, EntryPoint = "get_Nolo_Battery")]
        public static extern int get_Nolo_Battery(NoloDeviceType devicetype);

        [DllImportAttribute("noloRuntime", CallingConvention = CallingConvention.StdCall, EntryPoint = "get_Nolo_HMDTwoPointDriftAngle")]
        public static extern uint get_Nolo_HMDTwoPointDriftAngle();

        [DllImportAttribute("noloRuntime", CallingConvention = CallingConvention.StdCall, EntryPoint = "get_Nolo_VersionID")]
        public static extern int get_Nolo_VersionID(NoloDeviceType devicetype);
        ///get NOLO Controller States By Device Type
		[DllImportAttribute("noloRuntime", CallingConvention = CallingConvention.StdCall, EntryPoint = "get_Nolo_ControllerStates")]
        public static extern ControllerStates get_Nolo_ControllerStates(NoloDeviceType devicetype);
		///get NOLO Pose By Device Type
        [DllImportAttribute("noloRuntime", CallingConvention = CallingConvention.StdCall, EntryPoint = "get_Nolo_Pose")]
        public static extern Nolo_Pose get_Nolo_Pose(NoloDeviceType devicetype);
    }

}
