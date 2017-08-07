#include "NOLOServerDriver.h"

bool NOLOServerDriver::flag_ConnectNolo = false;
bool NOLOServerDriver::flag_DisConnectNolo = false;

Vector3 NOLOServerDriver::posR;
NOLOServerDriver::NOLOServerDriver() : m_bStopRequested(false)
{

}

NOLOServerDriver::~NOLOServerDriver()
{
	Cleanup();
}

vr::EVRInitError NOLOServerDriver::Init(vr::IDriverLog * pDriverLog, vr::IServerDriverHost * pDriverHost, const char * pchUserDriverConfigDir, const char * pchDriverInstallDir)
{
	InitDriverLog(pDriverLog);
	DriverLog(">>>>>>>>>>>>>>>>>>>>>>>>IServerTrackedDeviceProvider Init<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
	m_pDriverHost = pDriverHost;
	m_strDriverInstallDir = pchDriverInstallDir;

	memset(&noloData,0,sizeof(noloData));
	flagTurnAround = false;
	rotQ.w = 0; rotQ.x = 0; rotQ.y = 1; rotQ.z = 0;
	//打开监听zeromq
	registerConnectSuccessCallBack(connect_Nolo,this);
	registerDisConnectCallBack(disconnect_Nolo,this);
	registerNoloDataNotifyCallBack(ThreadEntry,this);
	registerExpandDataNotifyCallBack(expandDataNotify,this);
	Sleep(100);
	search_Nolo_Device();

	//ScanForNewControllers();
	noloLeftController=NULL;
	noloRightController=NULL;
	//m_Thread = std::thread(ThreadEntry, this);
	//m_Thread.detach();
	return vr::VRInitError_None;
}

void NOLOServerDriver::ThreadEntry( NoloData noloData, void * context)
{
	NOLOServerDriver* pDriver = reinterpret_cast<NOLOServerDriver*>(context);
	
	pDriver->ThreadFunc(noloData);
}

void NOLOServerDriver::ThreadFunc(const NoloData _noloData)
{
	std::recursive_mutex m_Mutex;
	std::lock_guard<std::recursive_mutex> lock(m_Mutex);
	memcpy(&noloData, &_noloData, sizeof(noloData));
	static bool flag_Once = false;
	static bool flag_left = false;
	static bool flag_right = false;
	static bool flag_LIsConnect = false;
	static bool flag_RIsConnect = false;

		CtrData leftcontroller;
		CtrData rightcontroller;
		flag_LIsConnect = true;
		flag_RIsConnect = true;

		if (flagTurnAround)
		{

			noloData.left_Controller_Data.ControllerRotation = rotQ * noloData.left_Controller_Data.ControllerRotation;

			noloData.left_Controller_Data.ControllerPosition.x = (2 * posR.x - noloData.left_Controller_Data.ControllerPosition.x);
			noloData.left_Controller_Data.ControllerPosition.z = 2 * posR.z - noloData.left_Controller_Data.ControllerPosition.z;

			noloData.right_Controller_Data.ControllerRotation = rotQ *noloData.right_Controller_Data.ControllerRotation;

			noloData.right_Controller_Data.ControllerPosition.x = (2 * posR.x - noloData.right_Controller_Data.ControllerPosition.x);
			noloData.right_Controller_Data.ControllerPosition.z = 2 * posR.z - noloData.right_Controller_Data.ControllerPosition.z;
		}
		
		leftcontroller.pos[0] = noloData.left_Controller_Data.ControllerPosition.x;
		leftcontroller.pos[1] = noloData.left_Controller_Data.ControllerPosition.y;
		leftcontroller.pos[2] = noloData.left_Controller_Data.ControllerPosition.z;

		leftcontroller.rot_quat[0] = noloData.left_Controller_Data.ControllerRotation.w;
		leftcontroller.rot_quat[1] = noloData.left_Controller_Data.ControllerRotation.x;
		leftcontroller.rot_quat[2] = noloData.left_Controller_Data.ControllerRotation.y;
		leftcontroller.rot_quat[3] = noloData.left_Controller_Data.ControllerRotation.z;

		rightcontroller.pos[0] = noloData.right_Controller_Data.ControllerPosition.x;
		rightcontroller.pos[1] = noloData.right_Controller_Data.ControllerPosition.y;
		rightcontroller.pos[2] = noloData.right_Controller_Data.ControllerPosition.z;


		rightcontroller.rot_quat[0] = noloData.right_Controller_Data.ControllerRotation.w;
		rightcontroller.rot_quat[1] = noloData.right_Controller_Data.ControllerRotation.x;
		rightcontroller.rot_quat[2] = noloData.right_Controller_Data.ControllerRotation.y;
		rightcontroller.rot_quat[3] = noloData.right_Controller_Data.ControllerRotation.z;

		leftcontroller.buttons = noloData.left_Controller_Data.Buttons;
		rightcontroller.buttons = noloData.right_Controller_Data.Buttons;


		leftcontroller.joyStick_X = noloData.left_Controller_Data.ControllerTouchAxis.x;
		leftcontroller.joyStick_Y = noloData.left_Controller_Data.ControllerTouchAxis.y;


		rightcontroller.joyStick_X = noloData.right_Controller_Data.ControllerTouchAxis.x;
		rightcontroller.joyStick_Y = noloData.right_Controller_Data.ControllerTouchAxis.y;

		leftcontroller.touch = noloData.left_Controller_Data.ControllerTouched;
		rightcontroller.touch = noloData.right_Controller_Data.ControllerTouched;

		leftcontroller.status = noloData.left_Controller_Data.state;
		rightcontroller.status = noloData.right_Controller_Data.state;

		leftcontroller.vecVelocity[0] = noloData.left_Controller_Data.vecVelocity.x;
		leftcontroller.vecVelocity[1] = noloData.left_Controller_Data.vecVelocity.y;
		leftcontroller.vecVelocity[2] = noloData.left_Controller_Data.vecVelocity.z;
		leftcontroller.vecAngularVelocity[0] = noloData.left_Controller_Data.vecAngularVelocity.x;
		leftcontroller.vecAngularVelocity[1] = noloData.left_Controller_Data.vecAngularVelocity.y;
		leftcontroller.vecAngularVelocity[2] = noloData.left_Controller_Data.vecAngularVelocity.z;
		rightcontroller.vecVelocity[0] = noloData.right_Controller_Data.vecVelocity.x;
		rightcontroller.vecVelocity[1] = noloData.right_Controller_Data.vecVelocity.y;
		rightcontroller.vecVelocity[2] = noloData.right_Controller_Data.vecVelocity.z;
		rightcontroller.vecAngularVelocity[0] = noloData.right_Controller_Data.vecAngularVelocity.x;
		rightcontroller.vecAngularVelocity[1] = noloData.right_Controller_Data.vecAngularVelocity.y;
		rightcontroller.vecAngularVelocity[2] = noloData.right_Controller_Data.vecAngularVelocity.z;

		if (flag_DisConnectNolo)
		{
			rightcontroller.status = 0;
			leftcontroller.status = 0;
			flag_LIsConnect = false;
			flag_RIsConnect = false;
		}

		if (flag_ConnectNolo) {

			if (noloData.left_Controller_Data.ControllerBattery == EBattery::ShutDown) {
				flag_LIsConnect = false;
			}

			if (noloData.right_Controller_Data.ControllerBattery == EBattery::ShutDown) {
				flag_RIsConnect = false;
			}

			if (flag_Once == false) {

				if (flag_left == false && leftcontroller.status) {
					DriverLog("===================Create NOLO LeftTrackedDevice======================\n");
					if (m_pDriverHost != NULL) {
						try
						{
							if (noloLeftController == NULL) {
								noloLeftController = new NOLOTrackedDevice(m_pDriverHost, 0);
								m_vecControllers.push_back(noloLeftController);
								m_pDriverHost->TrackedDeviceAdded(noloLeftController->GetSerialNumber());
								flag_left = true;
							}
						}
						catch (const std::exception& e)
						{
							DriverLog("===================Create NOLO LeftTrackedDevice Exception======================\n");
						}
					}

				}

				if (flag_right == false && rightcontroller.status) {
					DriverLog("===================Create NOLO RightTrackedDevice======================\n");
					if (m_pDriverHost != NULL) {
						try
						{
							if (noloRightController == NULL) {
								noloRightController = new NOLOTrackedDevice(m_pDriverHost, 1);
								m_vecControllers.push_back(noloRightController);
								m_pDriverHost->TrackedDeviceAdded(noloRightController->GetSerialNumber());
								flag_right = true;
							}


						}
						catch (const std::exception&)
						{
							DriverLog("===================Create NOLO RightTrackedDevice Exception======================\n");
						}

					}

				}

				if (flag_left && flag_right) {
					DriverLog("===================Create NOLO Device Over======================\n");
					flag_Once = true;
				}
			}

		}

		if (flag_left) {
			leftcontroller.status = 1;//创建出来后一直显示
			leftcontroller.isConnect = flag_LIsConnect;
			noloLeftController->RunFrame(leftcontroller);
		}
		
		if (flag_right) {
			rightcontroller.status = 1;
			rightcontroller.isConnect = flag_RIsConnect;
			noloRightController->RunFrame(rightcontroller);
		}
}

void NOLOServerDriver::connect_Nolo(void* context)
{
	DriverLog("===================Connect NOLO Server======================\n");
	flag_DisConnectNolo = false;
	flag_ConnectNolo = true;
}

void NOLOServerDriver::disconnect_Nolo(void * context)
{
	DriverLog("===================DisConnect NOLO Server======================\n");
	flag_ConnectNolo = false;
	flag_DisConnectNolo = true;
}

void NOLOServerDriver::expandDataNotify(ExpandMsgType type, void * context)
{
	NOLOServerDriver* pDriver = reinterpret_cast<NOLOServerDriver*>(context);
	pDriver->expandDataFunc(type);
}

void NOLOServerDriver::expandDataFunc(ExpandMsgType type)
{
	static bool IsTurn = false;
	if (type== ExpandMsgType::DoubleClickKeyTurnAround) {
	
		if (IsTurn == false) {
			flagTurnAround = true;
			posR = noloData.hmdData.HMDPosition;
			IsTurn = true;
		}
		else
		{
			if (IsTurn) {
				flagTurnAround = false;
				IsTurn = false;
			}
		}
	}
}


void NOLOServerDriver::Cleanup()
{
	DriverLog("===================Cleanup======================\n");
	close_Nolo_Device();
	//for (int i = 0; i < 30; i++) {

	//	notify_Nolo_GameOver();
	//}
	m_bStopRequested = true;
	
	if (noloLeftController!=NULL) {
	
		noloLeftController->Deactivate();
		delete noloLeftController;
		noloLeftController = NULL;
	}
	if (noloRightController != NULL) {
		noloRightController->Deactivate();
		delete noloRightController;
		noloRightController = NULL;
	}
	m_vecControllers.clear();
}

const char * const * NOLOServerDriver::GetInterfaceVersions()
{
	return vr::k_InterfaceVersions;
}

uint32_t NOLOServerDriver::GetTrackedDeviceCount()
{
	scope_lock lock(m_Mutex);

	return m_vecControllers.size();
}

vr::ITrackedDeviceServerDriver * NOLOServerDriver::GetTrackedDeviceDriver(uint32_t unWhich)
{
	scope_lock lock(m_Mutex);

	if (unWhich < m_vecControllers.size())
		return m_vecControllers[unWhich];

	return nullptr;
}

vr::ITrackedDeviceServerDriver * NOLOServerDriver::FindTrackedDeviceDriver(const char * pchId)
{
	scope_lock lock(m_Mutex);

	for (auto it = m_vecControllers.begin(); it != m_vecControllers.end(); ++it)
	{
		if (0 == strcmp((*it)->GetSerialNumber(), pchId))
		{
			return *it;
		}
	}
	return nullptr;
}

void NOLOServerDriver::RunFrame()
{
}

bool NOLOServerDriver::ShouldBlockStandbyMode()
{
	return false;
}

void NOLOServerDriver::EnterStandby()
{
}

void NOLOServerDriver::LeaveStandby()
{
}
