#pragma once
#include "myopenvr.h"
#include "HMDDeviceDriver.h"
#include "NOLOTrackedDevice.h"
class CServerDriver:public IServerTrackedDeviceProvider
{
public:
	CServerDriver();
	~CServerDriver();
	EVRInitError Init(IVRDriverContext *pDriverContext);
	void Cleanup();
	const char * const *GetInterfaceVersions();
	void RunFrame();
	bool ShouldBlockStandbyMode();
	void EnterStandby();
	void LeaveStandby();

	static void noloDataNotifyThread(NoloData data,void * context);
	void noloDataNotify(NoloData data);

	static void expandDataNotifyFunc(ExpandMsgType type, void * context);

	void expandDataNotify(ExpandMsgType type);

	bool isTurnAround;
private:
	CHMDDeviceDriver *m_pNullHmdLatest;
	NOLOTrackedDevice * noloLeftController;
	NOLOTrackedDevice * noloRightController;

	bool m_bEnableNullDriver;
};

