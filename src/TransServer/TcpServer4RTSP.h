///////////////////////////////////////////////////////////////////////////
/// COPYRIGHT NOTICE
/// Copyright (c) 2009, xx�Ƽ����޹�˾(��Ȩ����) 
/// All rights reserved. 
/// 
/// @file		  TcpServer4RTSP.h 
/// @brief       �ͻ���TCP������ģ��
///
/// @version   1.0 (�汾����)
/// @author    Jorhy (joorhy@gmail.com) 
/// @date       2015/04/22 09:43 
///
///
/// �޶�˵��������汾
///////////////////////////////////////////////////////////////////////////  
#ifndef __TCP_SERVER4MOBILE_H_
#define __TCP_SERVER4MOBILE_H_
#include "j_includes.h"
#include "x_asio_win.h"

/// ����Ĺ���:  �ͻ�������
/// ��ɿͻ�����ع��� 
class CTcpServer4RTSP : public J_AsioUser
					  , public J_Service
{
public:
	CTcpServer4RTSP();
	~CTcpServer4RTSP();

public:
	///AsioUser
	virtual j_result_t OnAccept(J_AsioDataBase *pAsioData, int nRet);
	virtual j_result_t OnRead(J_AsioDataBase *pAsioData, int nRet);
	virtual j_result_t OnWrite(J_AsioDataBase *pAsioData, int nRet);
	virtual j_result_t OnBroken(J_AsioDataBase *pAsioData, int nRet);

	///J_Service   
	j_result_t StartServer(const j_string_t &strIniPath);
	j_result_t StopServer();

private:
	J_AsioDataBase m_asioData;
	CXAsio m_asio;

	J_OS::CTLock m_locker;
	J_AsioDataMap m_asioDataMap;
};
#endif //~__TCP_SERVER4MOBILE_H_