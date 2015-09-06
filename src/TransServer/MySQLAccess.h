///////////////////////////////////////////////////////////////////////////
/// COPYRIGHT NOTICE
/// Copyright (c) 2009, xx�Ƽ����޹�˾(��Ȩ����) 
/// All rights reserved. 
/// 
/// @file      MySQLAccess.h 
/// @brief     MySQL���ݿ�ģ��
///
/// @version   1.0 (�汾����)
/// @author    Jorhy (joorhy@gmail.com) 
/// @date      2015/04/22 11:08 
///
///
/// �޶�˵��������汾
///////////////////////////////////////////////////////////////////////////  
#ifndef __MYSQLACCESS_H_
#define __MYSQLACCESS_H_
#include "j_includes.h"
#include "mysql.h"
#include "XlHostRespData.h"
#include "XlHostCmdData.h"

/// ����Ĺ���:  MySQL���ݿ������
/// ���ݿ����ɾ�Ĳ� 
class CMySQLAccess : public J_DbAccess
{
public:
	CMySQLAccess();
	~CMySQLAccess();

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
	j_result_t UpdateDevInfo(const CXlHostRespData::RespHostInfo &hostInfo, bool bOnline);
	/// ��ȡ�豸��Ϣ
	j_result_t GetDevInfo(CXlHostRespData::RespHostInfo &hostInfo);
	/// ���ӱ�����Ϣ
	j_result_t InsertAlarmInfo(const char *pHostId, const CXlHostRespData::RespAlarmInfo& alarmInfo);
	/// ����豸��־�����ʱ��
	time_t GetDevLogLastTime(const char *pHostId);
	/// ������־��Ϣ
	j_result_t InsertLogInfo(const char *pHostId, time_t tmStart, time_t tmEnd);
	/// �����ı���Ϣ
	j_result_t UpdateContextInfo(long lUserID, const char *pTitle, const char *pContext, std::vector<j_string_t> &vecHost);
	/// �����ļ�
	j_result_t UpdateFileInfo(long lUserID, const char *pTitle, const char *pFilePath, std::vector<j_string_t> &vecHost);
	/// ��ȡ�ı���Ϣ�б�
	j_result_t GetContextList(const char *pHostId, HostContextVec &contextVec);
	/// ��ȡ�ļ��б�
	j_result_t GetFileInfoList(const char *pHostId, HostFileInfoVec &contextVec);

private:  
	MYSQL *m_mysql;
	j_boolean_t m_bConnected;
};

JO_DECLARE_SINGLETON(MySQLAccess)

#endif // ~__MYSQLACCESS_H_
