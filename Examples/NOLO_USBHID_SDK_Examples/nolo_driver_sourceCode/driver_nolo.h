#include "myopenvr.h"
#include "ClientDriver.h"
#include "ServerDriver.h"
static CClientDriver  g_ClientDriver;
static CServerDriver  g_ServerDriver;
// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� NOLO_DRIVER_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// NOLO_DRIVER_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#define HMD_DLL_EXPORT extern "C" __declspec( dllexport )
//#if defined(_WIN32)
//#define HMD_DLL_EXPORT extern "C" __declspec( dllexport )
//#define HMD_DLL_IMPORT extern "C" __declspec( dllimport )
//#elif defined(__GNUC__) || defined(COMPILER_GCC) || defined(__APPLE__)
//#define HMD_DLL_EXPORT extern "C" __attribute__((visibility("default")))
//#define HMD_DLL_IMPORT extern "C" 
//#else
//#error "Unsupported Platform."
//#endif
//-----------------------------------------------------------------------------
// Purpose:steam������ڣ�����һ��CServerDriver_Nolo��һ��CClientDriver_Nolo
//-----------------------------------------------------------------------------
HMD_DLL_EXPORT void *HmdDriverFactory(const char *pInterfaceName, int *pReturnCode);