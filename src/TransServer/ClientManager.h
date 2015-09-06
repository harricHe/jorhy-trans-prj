///////////////////////////////////////////////////////////////////////////
/// COPYRIGHT NOTICE
/// Copyright (c) 2009, xx�Ƽ����޹�˾(��Ȩ����) 
/// All rights reserved. 
/// 
/// @file         ClientManager.h 
/// @brief       �ͻ��˹���ģ��
///
/// @version   1.0 (�汾����)
/// @author    Jorhy (joorhy@gmail.com) 
/// @date       2013/09/18 16:59 
///
///
/// �޶�˵��������汾
///////////////////////////////////////////////////////////////////////////  
#ifndef __CLIENT_MANAGER_H_
#define __CLIENT_MANAGER_H_
#include "j_includes.h"
#include "x_lock.h"
#include "x_timer.h"

/// ����Ĺ���:  ����ͻ�����Ϣ
/// �����Ǹ�����ģ��
/// ����ͻ��˵ĵ�¼���˳����������ݵȲ���
enum ClientType
{
	RTSP_CLIENT = 1,
	XL_CLIENT = 2,
};

class CClientManager
{
	typedef std::map<j_socket_t, J_Client *> ClientMap;
	typedef std::map<j_string_t, J_Client *> UserMap;
public:
	CClientManager();
	~CClientManager();

public:
	/// �û���¼
	/// @param[in]		pUserName �û��� 
	/// @param[in]		pPasswd ����
	/// @param[in]		nForce ǿ�Ƶ�¼��־
	/// @param[in]		nRett ����ֵ
	/// @param[in]		pClient �ͻ��˶���
	/// @return			�μ�j_errtype.h 
	j_result_t Login(const char *pUserName, const char *pPasswd, int nForce, int &nRet, J_Client *pClient);
	/// �û�ע��
	/// @param[in]		pUserName �û��� 
	/// @param[in]		pClient �ͻ��˶���
	/// @return			�μ�j_errtype.h 
	j_result_t Logout(const char *pUserName, J_Client *pClient);
	/// �����ͻ��˶���
	/// @param[in]		nSock �豸���� 
	/// @param[out]   NULL-ʧ��,����ΪClient����
	/// @return			�μ�j_errtype.h 
	J_Client *CreateClientObj(j_socket_t nSock, j_int32_t clientType = XL_CLIENT);
	/// �������ӻ�ȡ�ͻ��˶���
	/// @param[in]		nSock �豸���� 
	/// @return			Client����,NULL-δ�ҵ�   
	J_Client *GetClientObj(j_socket_t nSock);
	/// �����û�����ȡ�ͻ��˶��� 
	/// @param[in]		userName �û��� 
	/// @return			Client����,NULL-δ�ҵ�   
	J_Client *GetClientObj(j_string_t userName);
	///ɾ���ͻ��˶���
	/// @param[in]		nSock �豸���� 
	/// @return			
	void ReleaseClientObj(j_socket_t nSock);

private:
	static void OnTimer(void *pUser)
	{
		(static_cast<CClientManager *>(pUser))->CheckClient();
	}
	void CheckClient();

private:
	ClientMap m_clientMap;
	J_OS::CTLock m_lockerUser;
	UserMap m_userMap;
	J_OS::CTimer m_timer;
};

JO_DECLARE_SINGLETON(ClientManager)

#endif //~__CLIENT_MANAGER_H_