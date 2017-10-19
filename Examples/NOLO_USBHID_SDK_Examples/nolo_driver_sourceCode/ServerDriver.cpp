#include "ServerDriver.h"

CServerDriver::CServerDriver() :m_pNullHmdLatest(NULL), m_bEnableNullDriver(false)
{
}


CServerDriver::~CServerDriver()
{
}

EVRInitError CServerDriver::Init(IVRDriverContext * pDriverContext)
{
	VR_INIT_SERVER_DRIVER_CONTEXT(pDriverContext);
	InitDriverLog(vr::VRDriverLog());
	DriverLog("===============CServerDriver Init=========\n");

	//set_Nolo_PlayModel(EPlayModel::SuspensionModel);
	isTurnAround = false;
	registerNoloDataNotifyCallBack(&CServerDriver::noloDataNotifyThread, this);
	registerExpandDataNotifyCallBack(CServerDriver::expandDataNotifyFunc, this);
	search_Nolo_Device();
	//set_Nolo_PlayMode(EPlayMode::CeilingMode);

	m_pNullHmdLatest = new CHMDDeviceDriver();
	noloLeftController = new NOLOTrackedDevice("1314",0);
    noloRightController = new NOLOTrackedDevice("1315",1);

	vr::VRServerDriverHost()->TrackedDeviceAdded(m_pNullHmdLatest->GetSerialNumber().c_str(), vr::TrackedDeviceClass_HMD, m_pNullHmdLatest);
	vr::VRServerDriverHost()->TrackedDeviceAdded(noloLeftController->GetSerialNumber().c_str(), vr::TrackedDeviceClass_Controller, noloLeftController);
	vr::VRServerDriverHost()->TrackedDeviceAdded(noloRightController->GetSerialNumber().c_str(), vr::TrackedDeviceClass_Controller, noloRightController);
	return VRInitError_None;
}

void CServerDriver::Cleanup()
{
	CleanupDriverLog();
	delete m_pNullHmdLatest;
	m_pNullHmdLatest = NULL;
	delete noloLeftController;
	noloLeftController = NULL;
	delete noloRightController;
	noloRightController = NULL;

	close_Nolo_Device();
}

const char * const * CServerDriver::GetInterfaceVersions()
{
	return vr::k_InterfaceVersions;
}

void CServerDriver::RunFrame()
{
	
}

bool CServerDriver::ShouldBlockStandbyMode()
{
	return false;
}

void CServerDriver::EnterStandby()
{
}

void CServerDriver::LeaveStandby()
{
}

void CServerDriver::noloDataNotifyThread(NoloData data, void * context)
{
	CServerDriver* pDriver= reinterpret_cast<CServerDriver*>(context);
	pDriver->noloDataNotify(data);
}

void CServerDriver::noloDataNotify(NoloData data)
{
	if (m_pNullHmdLatest)
	{
		m_pNullHmdLatest->RunFrame(data.hmdData);
	}
	if (noloLeftController)
	{
		noloLeftController->RunFrame(data.left_Controller_Data);
	}
	if (noloRightController)
	{
		noloRightController->RunFrame(data.right_Controller_Data);
	}
}

void CServerDriver::expandDataNotifyFunc(ExpandMsgType type, void * context)
{
	CServerDriver * that = reinterpret_cast<CServerDriver*>(context);
	that->expandDataNotify(type);
}

void CServerDriver::expandDataNotify(ExpandMsgType type)
{
	if (type == ExpandMsgType::DoubleClickKeyTurnAround) {
		if (isTurnAround == false) {

			isTurnAround = true;
			HMD hmdPos = get_Nolo_HMDData();
			m_pNullHmdLatest->setPos(hmdPos.HMDPosition);
			m_pNullHmdLatest->setTurnAround(true);
			noloLeftController->setPos(hmdPos.HMDPosition);
			noloLeftController->setTurnAround(true);
			noloRightController->setPos(hmdPos.HMDPosition);
			noloRightController->setTurnAround(true);
		}
		else
		{
			m_pNullHmdLatest->setTurnAround(false);
			noloLeftController->setTurnAround(false);
			noloRightController->setTurnAround(false);
			isTurnAround = false;
		}
	}
}
