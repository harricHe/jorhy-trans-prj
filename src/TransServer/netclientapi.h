#ifndef _NET_CLIENT_API_H_
#define _NET_CLIENT_API_H_ 

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the LIBNETCLIENT_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// NETCLIENT_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef LIBNETCLIENT_EXPORTS
#define NETCLIENT_API __declspec(dllexport)
#else
#define NETCLIENT_API __declspec(dllimport)
#endif

#define  API_CALL	WINAPI

#include "GPSDeviceDef.h"
#include "GPSDataDef.h"
#include "GPSErrorDef.h"

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(4)

typedef struct _tagGPSTimeEx
{
	short Year;
	char  Month;
	char  Day;
	char  Hour;
	char  Minute;
	char  Second;
	char  Reserve;
}GPSTimeEx, *LPGPSTimeEx;		//hw

typedef struct _tagGPSRECFile
{
	GPSTimeEx	DateBeg;
	GPSTimeEx	DateEnd;
	char		szFile[MAX_PATH];
}GPSRECFile_S, *LPGPSRECFile_S;

typedef struct _tagGPSFile
{
	char	szFile[256]; 	/*��·�����ļ���*/
	int		nYear;
	int		nMonth;
	int		nDay;
	unsigned int uiBegintime;
	unsigned int uiEndtime;
	char	szDevIDNO[32];			//�豸ID
	int		nChn;
	unsigned int nFileLen;
	int		nFileType;
	int		nLocation;		//λ�ã��豸�ϵ�¼���ļ������Ǵ洢�����ϵ�¼���ļ�
	int		nSvrID;			//�洢������ID����Ϊ�洢�������ϵ��ļ�ʱ��Ч
}GPSFile_S, *LPIGPSFile_S;

typedef struct _tagGPSMCMsg
{
	int nMsgType;
	int nResult;
	void* pParam[6];
	void* pMngCmdClass;
}GPSMCMsg_S, *LPGPSMCMsg_S;

typedef void (CALLBACK * FUNDownDataCB)(int nType, void* pData, void * pUsr);

#pragma pack()

NETCLIENT_API int	API_CALL	NETCLIENT_Initialize();
NETCLIENT_API void	API_CALL	NETCLIENT_UnInitialize();
//����������������Χ1-10������²��������ͨ���жϺ󣬻��������
//����־��ѯ���켣������
NETCLIENT_API void	API_CALL	NETCLIENT_SetRecntCount(int nCount);

//hw 2012/1/19
//���ӷ��������������� 0-ʹ�þ�����IP(GPS_NET_TYPE_LAN)�� 1-ʹ�ù�����IP(GPS_NET_TYPE_WAN)
NETCLIENT_API int	API_CALL	NETCLIENT_GetNetType();

//=============================�ͻ��˵�¼====================================//
NETCLIENT_API int  API_CALL		NETCLIENT_RegLoginMsg(void* pUsr, void (CALLBACK * FUNLoginMsgCB)(int nMsg, void * pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_LoginDirSvr(const char* pSvrIP, unsigned short usPort, const char* szCompany, const char* szUsr, const char* szPwd, int nType);
NETCLIENT_API int	API_CALL	NETCLIENT_LogoutDirSvr();

//=============================��ȡ�������Ŀͻ��˺�WEBǰ̨�˿���Ϣ====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_DOWNOpenAppInfo(long* lpHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DOWNRegAppInfoCB(long lHandle, void* pUsr, void (CALLBACK * FUNDownAppInfoCB)(int nType, void* pData, void * pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_DOWNStartAppInfo(long lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DOWNStopAppInfo(long lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DOWNCloseAppInfo(long lHandle);

//=============================��ȡwebǰ̨�˿�====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_DEVOpenWebClientInfoDown(long* lpHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DEVRegWebClientInfoDownCB(long lHandle, void* pUsr, void (CALLBACK * FUNDownWebClientInfoCB)(int nType, void* pData, void * pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_DEVStartWebClientInfoDown(long lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DEVStopWebClientInfoDown(long lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DEVCloseWebClientInfoDown(long lHandle);

//=============================�豸����====================================//
//NETCLIENT_API int	API_CALL	NETCLIENT_DEVDownDevList(int nMgrType, int nDevType, void* pUsr, void (CALLBACK * FUNDownDevListCB)(int nType, void* pData, void * pUsr), int nCompany = -1);
NETCLIENT_API int	API_CALL	NETCLIENT_DEVDeviceChangeCB(void* pUsr, void (CALLBACK * FUNDeviceChangeCB)(int nReserve, void* pUsr));

//=============================�豸��Ϣ���أ�ʹ���̷߳�ʽ====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_DEVOpenDevDown(long* lpHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DEVRegDevDownCB(long lHandle, void* pUsr, void (CALLBACK * FUNDownDevCB)(int nType, void* pData, void * pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_DEVStartDevDown(long lHandle, int nMgrType, int nDevType);
NETCLIENT_API int	API_CALL	NETCLIENT_DEVStopDevDown(long lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DEVCloseDevDown(long lHandle);

//������Ա�նˣ�����֮ǰ�Ľӿ�
NETCLIENT_API int	API_CALL	NETCLIENT_DEVOpenDevDownEx(long* lpHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DEVRegDevDownCBEx(long lHandle, void* pUsr, void (CALLBACK * FUNDownDevCBEx)(int nType, void* pData, void * pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_DEVStartDevDownEx(long lHandle, int nMgrType, int nDevType);
NETCLIENT_API int	API_CALL	NETCLIENT_DEVStopDevDownEx(long lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DEVCloseDevDownEx(long lHandle);

//=============================�������ι���, ʹ���̷߳�ʽ====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_DEVOpenArmShieldDown(long* lpHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DEVRegArmShieldDownCB(long lHandle, void* pUsr, void (CALLBACK * FUNDownArmShieldCB)(int nType, void* pData, void * pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_DEVStartArmShieldDown(long lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DEVStopArmShieldDown(long lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DEVCloseArmShieldDown(long lHandle);
//NETCLIENT_API int	API_CALL	NETCLIENT_AlarmShieldChangCB(void* pUsr,  void(CALLBACK* FUNAlarmShieldChangeCB)(int nReserve, void* pUsr));

//=============================��ͼ��ǩ����, ʹ���̷߳�ʽ====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_DEVOpenMapTabDown(long* lpHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DEVRegMapTabDownCB(long lHandle, void* pUsr, void (CALLBACK * FUNDownMapTabCB)(int nType, void* pData, void * pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_DEVStartMapTabDown(long lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DEVStopMapTabDown(long lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DEVCloseMapTabDown(long lHandle);
//NETCLIENT_API int	API_CALL	NETCLIENT_MapTabChangCB(void* pUsr,  void(CALLBACK* FUNMapTabChangeCB)(int nReserve, void* pUsr));

//=============================�û���ͼ����, ʹ���̷߳�ʽ====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_DEVOpenUserMapInfoDown(long* lpHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DEVRegUserMapInfoDownCB(long lHandle, void* pUsr, void (CALLBACK * FUNDownUserMapInfoCB)(int nType, void* pData, void * pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_DEVStartUserMapInfoDown(long lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DEVStopUserMapInfoDown(long lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DEVCloseUserMapInfoDown(long lHandle);

//=============================�û�Ȩ��, ʹ���̷߳�ʽ====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_DEVOpenUserPrivilegeDown(long* lpHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DEVRegUserPrivilegeDownCB(long lHandle, void* pUsr, void (CALLBACK * FUNDownUserPrivilegeCB)(int nType, void* pData, void * pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_DEVStartUserPrivilegeDown(long lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DEVStopUserPrivilegeDown(long lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DEVCloseUserPrivilegeDown(long lHandle);

//=============================���������ã�ʹ���̷߳�ʽ====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_DEVOpenSvrConfigDown(long* lpHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DEVRegSvrConfigDownCB(long lHandle, void* pUsr, void (CALLBACK * FUNDownSvrConfigCB)(int nType, void* pData, void * pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_DEVStartSvrConfigDown(long lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DEVStopSvrConfigDown(long lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DEVCloseSvrConfigDown(long lHandle);

//=============================�û���Ϣ��ʹ���̷߳�ʽ====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_DEVOpenUserInfoDown(long* lpHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DEVRegUserInfoDownCB(long lHandle, void* pUsr, void (CALLBACK * FUNDownUserInfoCB)(int nType, int nSubType, void* pData, void * pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_DEVSetUserInfoConfigDown(long lHandle, unsigned int nDownConfig);
NETCLIENT_API int	API_CALL	NETCLIENT_DEVStartUserInfoDown(long lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DEVStopUserInfoDown(long lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DEVCloseUserInfoDown(long lHandle);

//=============================����͸����������====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_OpenUserTransparent(long* lpHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_RegUserTransparentCB(long lHandle, void* pUsr, void (CALLBACK * FUNUserTransparentCB)(int nType, const char* pDataBuf, int nDataLen, void * pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_SetUserTransData(long lHandle, const char* pDataBuf, int nDataLen);
NETCLIENT_API int	API_CALL	NETCLIENT_StartUserTransparent(long lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_StopUserTransparent(long lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_CloseUserTransparent(long lHandle);

//=============================��ȡ�豸����====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_DLOpenGetDevCfg(long* lpGetDevCfg, const char* szDevIDNO);
NETCLIENT_API int	API_CALL	NETCLIENT_DLSetGetDCfgMsgCB(long lGetDevCfg, void* pUsr
														 , void (CALLBACK *FUNMsgCB)(int nMsg, int nParam, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_DLSetGetDCfgDataCB(long lGetDevCfg, void* pUsr
														  , void (CALLBACK *FUNDataCB)(const char* pBuf, int nLen, long nPos, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_DLStartGetDevCfg(long lGetDevCfg);
NETCLIENT_API int	API_CALL	NETCLIENT_DLStopGetDevCfg(long lGetDevCfg);
NETCLIENT_API int	API_CALL	NETCLIENT_DLCloseGetDevCfg(long lGetDevCfg);	

//=============================���ϴ��豸������������====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_UDPOpenUploadDevParams(long* lHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_UDPSetUploadMsgCB(long lUploadHandle, void* pUsr, void (CALLBACK *FUNMsgCB)(int nMsg, int nParam, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_UDPStartUpload(long lUploadHandle, const char* szSrcFile);
NETCLIENT_API int	API_CALL	NETCLIENT_UDPStopUpload(long lUploadHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_UDPGetDestFileName(long lUploadHandle, int* lpSvrID, char* pDestFile);
NETCLIENT_API int	API_CALL	NETCLIENT_UDPCloseUpload(long lUploadHandle);

//=============================�ӷ������������ļ��ϴ����豸====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_ULOpenSetDevCfg(long* lpSetDevCfg, const char* szDevIDNO, int nSvrID, const char* szFile);
NETCLIENT_API int	API_CALL	NETCLIENT_ULSetSetDCfgMsgCB(long lSetDevCfg, void* pUsr
														 , void (CALLBACK *FUNMsgCB)(int nMsg, int nParam, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_ULStartSetDevCfg(long lSetDevCfg);
NETCLIENT_API int	API_CALL	NETCLIENT_ULStopSetDevCfg(long lSetDevCfg);
NETCLIENT_API int	API_CALL	NETCLIENT_ULCloseSetDevCfg(long lSetDevCfg);

//=============================�ļ�����====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_DLOpenSearchFile(long* lpSearchHandle, const char* szDevIDNO, int nLocation);
NETCLIENT_API int	API_CALL	NETCLIENT_DLOpenSrchFileEx(long* lpSearchHandle, const char* szDevIDNO, int nLocation, int nAttributenFile);
NETCLIENT_API int	API_CALL	NETCLIENT_DLSetSearchMsgCB(long lSearchHandle, void* pUsr
														  , void (CALLBACK *FUNMsgCB)(int nMsg, int nParam, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_DLSetSearchFileCB(long lSearchHandle, void* pUsr
														   , void (CALLBACK *FUNFileCB)(GPSFile_S* pFile, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_DLStartSearchFile(long lSearchHandle, int nYear, int nMonth, int nDay
														  , int nRecType, int nChn, int nBegTime, int nEndTime);
NETCLIENT_API int	API_CALL	NETCLIENT_DLStopSearchFile(long lSearchHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DLCloseSearchFile(long lSearchHandle);	

//=============================�ļ�����====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_DLOpenDownFile(long* lpDownHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DLOpenDownFileEx(long* lpDownHandle, int nAttribute);
NETCLIENT_API int	API_CALL	NETCLIENT_DLSetDFileMsgCB(long lDownHandle, void* pUsr
														 , void (CALLBACK *FUNMsgCB)(int nMsg, int nParam, void* pUsr));
//ȡ�ļ��������ݣ���λKByte
NETCLIENT_API int	API_CALL	NETCLIENT_DLGetFlowRate(long lDownHandle, int* lpFlowRate);
//�����ط�ʽ����׷�����أ��߱��ϵ�̴�����
NETCLIENT_API int	API_CALL	NETCLIENT_DLStartDownFile(long lDownHandle, GPSFile_S* pFile, char* szDownFile);
NETCLIENT_API int	API_CALL	NETCLIENT_DLStopDownFile(long lDownHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DLCloseDownFile(long lDownHandle);	

//=============================������־��ѯ====================================//
// NETCLIENT_API int	API_CALL	NETCLIENT_OpenAlarmQuery(long* lpAlarmQueryHandle, int nPage, int nItemCount);
// NETCLIENT_API int	API_CALL	NETCLIENT_SetAlarmQueryMsgCB(long lAlarmQueryHandle, void* pUsr, void (CALLBACK *FUNMsgCB)(int nMsg, int nParam, void* pUsr));
// NETCLIENT_API int	API_CALL	NETCLIENT_SetAlarmQueryDataCB(long lAlarmQueryHandle, void* pUsr, void (CALLBACK *FUNVehiArmCB)(const char* pAlarm, int nLength, void* pUsr));
// NETCLIENT_API int	API_CALL	NETCLIENT_StartAlarmQuery(long lAlarmQueryHandle, GPSDeviceIDNO_S* pDevice, int nDevCount, int* pArmType, int nTyCount, SYSTEMTIME* tmBeg, SYSTEMTIME* tmEnd);
// NETCLIENT_API int	API_CALL	NETCLIENT_StopAlarmQuery(long lAlarmQueryHandle);
// NETCLIENT_API int	API_CALL	NETCLIENT_CloseAlarmQuery(long lAlarmQueryHandle);

//=============================��ȡ�豸״̬��Ϣ====================================//
//�²�ÿ5���Ӵӷ���������һ���豸״̬��Ϣ
NETCLIENT_API int	API_CALL	NETCLIENT_VSOpenVehiStatus(long* lpVSHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_VSSetStatusCB(long lVSHandle, void* pUsr, void (CALLBACK *FUNVehiStatusCB)(GPSVehicleState_S* pVehiRun, char* pOnline, int nCount, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_VSSetStatusDevice(long lVSHandle, GPSDeviceIDNO_S* pDevice, int nCount);
NETCLIENT_API int	API_CALL	NETCLIENT_VSStartVSChan(long lVSHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_VSStopVSChan(long lVSHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_VSCloseVehiStatus(long lVSHandle);

//=============================�豸����GPS====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_VROpenVehiRun(long* lpVRHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_VRSetRunningCB(long lVRHandle, void* pUsr, void (CALLBACK *FUNVehiRunningCB)(GPSVehicleState_S* pVehiRun, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_VRStartVRChan(long lVRHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_VRStopVRChan(long lVRHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_VRAddDevice(long lVRHandle, int nDevID, const char* szDevIDNO);
NETCLIENT_API int	API_CALL	NETCLIENT_VRDelDevice(long lVRHandle, int nDevID);
NETCLIENT_API int	API_CALL	NETCLIENT_VRCloseVehiRun(long lVRHandle);

//=============================�豸������Ϣ====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_VAOpenVehiAlarm(long* lpVAHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_VASetAlarmDevice(long lVAHandle, GPSDeviceIDNO_S* pDevice, int nCount);
NETCLIENT_API int	API_CALL	NETCLIENT_VASetAlarmInfoCB(long lVAHandle, void* pUsr, void (CALLBACK *FUNAlarmInfoCB)(const char* pAlarm, int nLength, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_VAStartVAChan(long lVAHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_VAStopVAChan(long lVAHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_VACloseVehiAlarm(long lVAHandle);

//=============================�켣��ѯ====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_VTOpenVehiTrack(long* lpVTrackHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_VTSetVTrackMsgCB(long lVTrackHandle, void* pUsr, void (CALLBACK *FUNVehiTrackMsgCB)(int nMsg, int nParam, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_VTSetVTrackDataCB(long lVTrackHandle, void* pUsr, void (CALLBACK *FUNVehiTrackDataCB)(GPSVehicleTrack_S* pVehiTrack, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_VTStartVehiTrack(long lVTrackHandle, char* szDevIDNO, const SYSTEMTIME* pBegTime, const SYSTEMTIME* pEndTime, int nType, int nDistance, int nParkTime);
NETCLIENT_API int	API_CALL	NETCLIENT_VTStopVehiTrack(long lVTrackHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_VTCloseVehiTrack(long lVTrackHandle);

//=============================�ϴ��ļ�====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_GetDevUpgradeFileInfo(const char* szFile, GPSDEVUpgradeFile_S* pFileInfo);

NETCLIENT_API int	API_CALL	NETCLIENT_ULOpenDevUpgradeFile(long* lHandle, GPSDEVUpgradeFile_S* pFile, const char* szSrcFile);
NETCLIENT_API int	API_CALL	NETCLIENT_ULOpenDevParamFile(long* lHandle, const char* szSrcFile);
NETCLIENT_API int	API_CALL	NETCLIENT_ULSetUploadMsgCB(long lUploadHandle, void* pUsr, void (CALLBACK *FUNMsgCB)(int nMsg, int nParam, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_ULStartUpload(long lUploadHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_ULStopUpload(long lUploadHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_ULGetDestFileName(long lUploadHandle, int* lpSvrID, char* pDestFile);
NETCLIENT_API int	API_CALL	NETCLIENT_ULCloseUpload(long lUploadHandle);

//=============================Զ������====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_DUOpenDevUpgrade(long* lHandle, const char* szDevIDNO, GPSDEVUpgradeFile_S* pFile, int nSvrID, const char* szUpFile);
NETCLIENT_API int	API_CALL	NETCLIENT_DUSetDevUpMsgCB(long lUploadHandle, void* pUsr, void (CALLBACK *FUNMsgCB)(int nMsg, int nParam, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_DUStartDevUpgrade(long lUploadHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DUStopDevUgprade(long lUploadHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_DUCloseDevUpgrade(long lUploadHandle);

//=============================���������������====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_MCStartWork();
NETCLIENT_API int	API_CALL	NETCLIENT_MCStopWork();
NETCLIENT_API int	API_CALL	NETCLIENT_MCRegMsgCB(void* pUsr, void (CALLBACK * FUNMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr));
NETCLIENT_API int	API_CALL	NETCLIENT_MCReleaseMsg(GPSMCMsg_S* pMsg);
NETCLIENT_API int	API_CALL	NETCLIENT_MCReleaseHandle(long lHandle);

//���Ͷ���Ϣ�������֪ͨ�豸�������������ĵ�ַ
NETCLIENT_API int	API_CALL	NETCLIENT_MCSendSMS(const char* szDevIDNO, int nSMSType, const char* szPhoneNO, const char* szText); //���Ͷ���
//����TTS
NETCLIENT_API int	API_CALL	NETCLIENT_MCSendText(const char* szDevIDNO, const char* szText, void* pUsr, void (CALLBACK * FUNMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr));
//�������������Ͷϵ�
NETCLIENT_API int	API_CALL	NETCLIENT_MCSendCtrl(const char* szDevIDNO, int nCtrlType, const char* szUsr, const char* szPwd);
//��̨����
NETCLIENT_API int	API_CALL	NETCLIENT_MCSendPtz(const char* szDevIDNO, int nChn, int nCommand, int nSpeed, int nParam);
//��ȡ����״̬
NETCLIENT_API int	API_CALL	NETCLIENT_MCReadDevStatus(const char* szDevIDNO, void* pUsr, void (CALLBACK * FUNMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr));
//�޸��û�����
NETCLIENT_API int	API_CALL	NETCLIENT_MCChangeUsrPwd(const char* szOld, const char* szNew, void* pUsr, void (CALLBACK * FUNMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr), long* lpHandle);
//����GPSʱ����
NETCLIENT_API int	API_CALL	NETCLIENT_MCSetGpsInterval(const char* szDevIDNO, BOOL bStart, int nDistance, int nTime, int nType);
//���Ϳ���ָ��ʱУ��ƽ̨�û�
NETCLIENT_API int	API_CALL	NETCLIENT_MCCheckCtrlUsr(const char* szUsr, const char* szPwd);
//��ȡ�ƶ�������
NETCLIENT_API int	API_CALL	NETCLIENT_MCReadMotionParam(const char* szDevIDNO, int nChannel
														  , void* pUsr, void (CALLBACK * FUNMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr)
														  , long* lpHandle);
//�����ƶ�������
NETCLIENT_API int	API_CALL	NETCLIENT_MCSetMotionParam(const char* szDevIDNO, int nChannel, GPSMotionParam_S* pMotion
														 , void* pUsr, void (CALLBACK * FUNMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr)
														 , long* lpHandle);
//��ȡ��������������Ϣ
NETCLIENT_API int	API_CALL	NETCLIENT_MCReadNetFlowStatistics(const char* szDevIDNO
														  , void* pUsr, void (CALLBACK * FUNMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr)
														  , long* lpHandle);
//������������ͳ�Ʋ���
NETCLIENT_API int	API_CALL	NETCLIENT_MCSetNetFlowParam(const char* szDevIDNO, GPSNetFlowStatistics_S* pNetParam
														 , void* pUsr, void (CALLBACK * FUNMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr)
														 , long* lpHandle);
//�����������ͳ��
NETCLIENT_API int	API_CALL	NETCLIENT_MCClearNetFlowStatistics(const char* szDevIDNO
														  , void* pUsr, void (CALLBACK * FUNMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr)
														  , long* lpHandle);
//����������������
NETCLIENT_API int	API_CALL	NETCLIENT_MCAdjustNetFlowStatistics(const char* szDevIDNO, int nMBFlow
														 , void* pUsr, void (CALLBACK * FUNMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr)
														 , long* lpHandle);
//�����û��������� 
NETCLIENT_API int	API_CALL	NETCLIENT_MCSetUsrAlarmShield(const GPSAlarmShield_S* pAlarm, int nCount
														 , void* pUsr, void (CALLBACK * FUNMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr)
														 , long* lpHandle);
//��ӵ�ͼ�����Ϣ
NETCLIENT_API int	API_CALL	NETCLIENT_MCAddMapMarker(const GPSMapMarker_S* pMarker
														  , void* pUsr, void (CALLBACK * FUNMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr)
														  , long* lpHandle);
//��ӵ�ͼ�������
NETCLIENT_API int	API_CALL	NETCLIENT_MCAddMapMarkerInfo(const GPSMarkerInfo_S* pMarkerInfo
														 , void* pUsr, void (CALLBACK * FUNMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr)
														  , long* lpHandle);
//ɾ����ͼ�����Ϣ
NETCLIENT_API int	API_CALL	NETCLIENT_MCDelMapMarker(int nMarkerID
														 , void* pUsr, void (CALLBACK * FUNMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr)
														 , long* lpHandle);
//���͵���ָ����Ϣ
NETCLIENT_API int	API_CALL	NETCLIENT_MCSendDispatchCommand(const char* szDevIDNO, const GPSDispatchCommand_S* lpDispatch
														 , void* pUsr, void (CALLBACK * FUNMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr)
														 , long* lpHandle);
//�����û���ͼ����
NETCLIENT_API int	API_CALL	NETCLIENT_MCSetUsrMapConfig(const UserMapConfig_S* pUserMapConfig, void* pUsr, 
															void (CALLBACK * FUNMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr)
															  , long* lpHandle);

//��������
NETCLIENT_API int	API_CALL	NETCLIENT_MCSendCfg(const char* szDevIDNO, const char* pCfg, int nLen, int nCMDCfg
													   , void* pUsr, void (CALLBACK * FUNMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr)
													   , long* lpHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_MCGetCfg(const char* szDevIDNO, int nCMDCfg
													  , void* pUsr, void (CALLBACK * FUNMCMsgCB)(GPSMCMsg_S* pMsg, void* pUsr)
													  , long* lpHandle);

//=============================�����������ָ�����ʹ��TCP��ʽֱ�ӷ�������====================================//
NETCLIENT_API int	API_CALL	NETCLIENT_CMDAddMapLine(const GPSMapLine_S* pLine, void* pUsr, FUNDownDataCB pfnDownData
														 , long* lpHandle);
NETCLIENT_API int	API_CALL	NETCLIENT_CMDReleaseHandle(long lHandle);


#ifdef __cplusplus
}
#endif

#endif

