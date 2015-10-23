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
#include "XlDataBusDef.h"

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
	j_result_t UpdateDevInfo(const XlHostResponse::HostInfo &hostInfo, bool bOnline);
	/// ��ȡ�豸��Ϣ
	j_result_t GetDevInfo(XlHostResponse::HostInfo &hostInfo);
	/// ���ӱ�����Ϣ
	j_result_t InsertAlarmInfo(const char *pHostId, const XlHostResponse::AlarmInfo& alarmInfo);
	/// ����豸��־�����ʱ��
	time_t GetDevLogLastTime(const char *pHostId);
	/// ������־��Ϣ
	j_result_t InsertLogInfo(const char *pHostId, time_t tmStart, time_t tmEnd);
	/// �����豸IDɾ��RecordingLog �������־��Ϣ
	j_result_t DeleteLogInfo(const char *pHostId);
	/// ͬ����־��Ϣ
	j_result_t SyncLogInfo(const char *pHostId, time_t tmFirstItem);
	/// �����ı���Ϣ
	j_result_t AddContextInfo(long lUserID, const char *pTitle, const char *pContext, std::vector<j_string_t> &vecHost);
	/// �����ļ�
	j_result_t AddFileInfo(long lUserID, const char *pFileName, const char *pFilePath, std::vector<j_string_t> &vecHost);
	/// �����ı���Ϣ
	j_result_t UpdateContextInfo(long lMessageID, int nMessageState, int nDetailState);
	/// �����ļ�
	j_result_t UpdateFileInfo(long lFileID, int nFileState, int nDetailState);
	/// ɾ���ı���Ϣ
	j_result_t DelContextInfo(long lMessageID);
	/// ɾ���ļ�
	j_result_t DelFileInfo(long lFileID);
	/// ��ȡ�ı���Ϣ�б�
	j_result_t GetContextList(const char *pHostId, HostContextVec &contextVec);
	/// ��ȡ�ļ��б�
	j_result_t GetFileInfoList(const char *pHostId, HostFileInfoVec &fileVec);

	/*int	CMySQLAccess::Ansi2UTF8(LPCSTR sInput, j_string_t& sOutput);

	int	CMySQLAccess::Ansi2Unicode(LPCSTR input, j_wstring_t& output);*/
private:
	MYSQL *m_mysql;
	j_boolean_t m_bConnected;
};

JO_DECLARE_SINGLETON(MySQLAccess)

#endif // ~__MYSQLACCESS_H_
