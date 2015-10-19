///////////////////////////////////////////////////////////////////////////
/// COPYRIGHT NOTICE
/// Copyright (c) 2009, xx�Ƽ����޹�˾(��Ȩ����) 
/// All rights reserved. 
/// 
/// @file         ClientManager.cpp 
/// @brief       �ͻ��˹���ģ��ʵ��
///
/// @version   1.0 (�汾����)
/// @author    Jorhy (joorhy@gmail.com) 
/// @date       2013/09/18 17:02 
///
///
/// �޶�˵��������汾
///////////////////////////////////////////////////////////////////////////  
#include "x_asio_win.h"
#include "ClientManager.h"
#include "XlClient.h"
#include "RtspClient.h"
#include "MsSqlServer.h"
#include "MySQLAccess.h"

JO_IMPLEMENT_SINGLETON(ClientManager)

CClientManager::CClientManager()
{
	m_timer.Create(1000, CClientManager::OnTimer, this);
}

CClientManager::~CClientManager()
{
	m_timer.Destroy();
}


/***********************************************************************************************************
 * ���򴴽���������                     �����޸�:�Խ���
 * �������ܣ��ͻ��˵�¼
 * ����˵����
 * pUserName���û���
 *   pPasswd������
 *    nForce��
 *      nRet��
 *   pClient��
 * ע�����null
 * �޸����ڣ�2015/10/09 18:00:00
 ***********************************************************************************************************/
j_result_t CClientManager::Login(const char *pUserName, const char *pPasswd, int nForce, int &nRet, J_Client *pClient)
{
	if (JoDataBaseObj->Login(pUserName, pPasswd, nForce, nRet) == J_OK)
	{
		TLock(m_lockerUser);
		UserMap::iterator it = m_userMap.find(pUserName);
		if (it != m_userMap.end() && nForce == 1)
		{
			//it->second->SendMsgInfo("", xlc_msg_user, xlc_force_login);
		}
		m_userMap[pUserName] = pClient;

		TUnlock(m_lockerUser);
	}
	return J_OK;
}

j_result_t CClientManager::Logout(const char *pUserName, J_Client *pClient)
{
	TLock(m_lockerUser);
	UserMap::iterator it = m_userMap.find(pUserName);
	if (it != m_userMap.end())
	{
		if (pClient == it->second)
		{
			JoDataBaseObj->Logout(pUserName);
			m_userMap.erase(pUserName);
		}
	}
	TUnlock(m_lockerUser);

	return J_OK;
}

J_Client *CClientManager::CreateClientObj(j_socket_t nSock, j_int32_t clientType)
{
	J_Client *pClient = NULL;
	if (clientType == XL_CLIENT)
	{
		pClient = new CXlClient(nSock);
	}
	else if (clientType == RTSP_CLIENT)
	{
		pClient = new CRTSPClient(nSock);
	}

	if (pClient != NULL)
	{
		m_clientMap[nSock] = pClient;
	}
	J_OS::LOGINFO("CClientManager::CreateClientObj Socket = %d", nSock.sock);

	return pClient;
}

J_Client *CClientManager::GetClientObj(j_socket_t nSock)
{
	J_Client *pClient = NULL;
	ClientMap::iterator it = m_clientMap.find(nSock);
	if (it != m_clientMap.end())
	{
		pClient = it->second;
	}

	return pClient;
}

J_Client *CClientManager::GetClientObj(j_string_t userName)
{
	J_Client *pClient = NULL;
	TLock(m_lockerUser);
	UserMap::iterator it = m_userMap.find(userName);
	if (it != m_userMap.end())
	{
		pClient = it->second;
	}
	TUnlock(m_lockerUser);

	return pClient;
}

void CClientManager::ReleaseClientObj(j_socket_t nSock)
{
	J_Client *pClient = NULL;
	ClientMap::iterator it = m_clientMap.find(nSock);
	if (it != m_clientMap.end())
	{
		pClient = it->second;
		pClient->OnBroken();
		j_close_socket(it->first.sock);
		delete pClient;
		m_clientMap.erase(it);
	}
}

void CClientManager::CheckClient()
{
	CXAsio::LockSlice();
	ClientMap::iterator it = m_clientMap.begin();
	for (; it != m_clientMap.end(); it++)
	{
		J_Client *pClient = it->second;
		if (!pClient->IsReady())
		{
			///����ͻ��˶���
			pClient = it->second;
			pClient->OnBroken();
			j_close_socket(it->first.sock);
			delete pClient;
			m_clientMap.erase(it);
			break;
		}
	}
	CXAsio::UnlockSlice();
}