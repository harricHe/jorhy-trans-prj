///////////////////////////////////////////////////////////////////////////
/// COPYRIGHT NOTICE
/// Copyright (c) 2009, xx�Ƽ����޹�˾(��Ȩ����) 
/// All rights reserved. 
/// 
/// @file      SqlServerAccess.h 
/// @brief     SqlServer���ݿ�ģ��
///
/// @version   1.0 (�汾����)
/// @author    Jorhy (joorhy@gmail.com) 
/// @date      2013/09/22 11:08 
///
///
/// �޶�˵��������汾
///////////////////////////////////////////////////////////////////////////  
#ifndef __SQLSERVERACCESS_H_
#define __SQLSERVERACCESS_H_
#include "j_includes.h"
#include "XlDataBusDef.h"

#import "msado15.dll" no_namespace rename("EOF", "EndOfFile")
/// ����Ĺ���:  SqlServer���ݿ������
/// ���ݿ����ɾ�Ĳ� 
class CSqlServerAccess : public J_DbAccess
{
public:
	CSqlServerAccess();
	~CSqlServerAccess();

public:
	///J_DbAccess
	virtual j_result_t Connect(const j_char_t *pAddr, j_int16_t nPort, const j_char_t *pUa, const j_char_t *pPwd);
	virtual j_result_t Init();
	virtual j_result_t Release();

public:
	/// �û���¼
	j_result_t Login(const char *pUserName, const char *pPasswd, int nForce, int &nRet);
	/// ��ȡ�û���
	j_result_t GetUserNameById(j_int32_t userId, j_string_t &userName);
	/// �û��˳�
	j_result_t Logout(const char *pUserName);
	/// �޸��ļ���Ϣ
	j_result_t UpdateFileInfo(j_int32_t nFileId, j_int32_t nState, bool bFlag = true);
	/// �޸��豸��Ϣ
	j_result_t UpdateDevInfo(const XlHostResponse::HostInfo &hostInfo, bool bOnline);
	/// ��ȡ�豸��Ϣ
	j_result_t GetDevInfo(XlHostResponse::HostInfo &hostInfo);
	/// ���ӱ�����Ϣ
	j_result_t InsertAlarmInfo(const char *pHostId, const XlHostResponse::AlarmInfo& alarmInfo);
	/// ����豸��־�����ʱ��
	time_t GetDevLogLastTime(const char *pHostId);
	/// ������־��Ϣ
	j_result_t InsertLogInfo(const char *pHostId, int nState, time_t tmTimeStamp);

private:  
	_ConnectionPtr m_pConn;		/// ���Ӷ���  
	_RecordsetPtr m_pRec;				/// ��¼������  
	_CommandPtr m_pCmd;			/// �������
};

JO_DECLARE_SINGLETON(SqlServerAccess)

#endif // ~__SQLSERVERACCESS_H_
