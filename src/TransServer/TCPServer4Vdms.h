///////////////////////////////////////////////////////////////////////////
/// COPYRIGHT NOTICE
/// Copyright (c) 2009, xx�Ƽ����޹�˾(��Ȩ����) 
/// All rights reserved. 
/// 
/// @file		  TcpServer4Vdms.h 
/// @brief       �ͻ���TCP������ģ��
///
/// @version   1.0 (�汾����)
/// @author    Jorhy (joorhy@gmail.com) 
/// @date       2015/07/15 15:11 
///
///
/// �޶�˵��������汾
///////////////////////////////////////////////////////////////////////////  
#ifndef __TCP_SERVER4VDMS_H_
#define __TCP_SERVER4VDMS_H_
#include "j_includes.h"
#include "hi_voice_api.h"
#include "netclientapi.h"

/// ����Ĺ���:  �ͻ�������
/// ��ɿͻ�����ع��� 
class CTcpServer4Vdms : public J_Service
{
	typedef std::map<j_string_t, GPSDevInfo_S> DeviceMap;
public:
	CTcpServer4Vdms();
	~CTcpServer4Vdms();

public:
	/// J_Service
	j_result_t StartServer(const j_string_t &strIniPath);
	j_result_t StopServer();

private:
	void StartDeviceLoad(j_boolean_t bReload);
	void StopDeviceLoad();

	void StartDevAlarm();
	void StopDevAlarm();

private:
	static void WINAPI FuncLoginMsg(int nMsg, void *pUser)
	{
		(static_cast<CTcpServer4Vdms *>(pUser))->DoLoginMsg(nMsg);
	}
	void DoLoginMsg(int nMsg);

	//�����б���Ϣ
	static void WINAPI FuncDownloadDev(int nType, void *pData, void *pUser)
	{
		(static_cast<CTcpServer4Vdms *>(pUser))->DoDownloadDev(nType, pData);
	}
	void DoDownloadDev(int nType, void *pData);

	static void WINAPI FuncAlarmInfo(const char* pAlarm, int nLength, void* pUser)
	{
		(static_cast<CTcpServer4Vdms *>(pUser))->DoAlarmInfo(pAlarm, nLength);
	}
	void DoAlarmInfo(const char* pAlarm, int nLength);

private:
	j_boolean_t m_bLogining;
	j_boolean_t m_bLoginSuccess;

	//�����б���
	long m_lLoadHandle;
	j_boolean_t m_bReloadDev;
	long m_lAlarmHaneld;
	DeviceMap m_deviceMap;
};
#endif //~__TCP_SERVER4VDMS_H_