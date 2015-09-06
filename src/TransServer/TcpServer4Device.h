///////////////////////////////////////////////////////////////////////////
/// COPYRIGHT NOTICE
/// Copyright (c) 2009, xx�Ƽ����޹�˾(��Ȩ����) 
/// All rights reserved. 
/// 
/// @file			TcpServer4Dev.h 
/// @brief			�豸��TCP����ģ��
///
/// @version    1.0 (�汾����)
/// @author     Jorhy (joorhy@gmail.com) 
/// @date			2013/09/18 17:12 
///
///
/// �޶�˵��������汾
///////////////////////////////////////////////////////////////////////////  

#ifndef __TCP_SERVER4DEV_H_
#define __TCP_SERVER4DEV_H_
#include "j_includes.h"
#include "x_asio_win.h"
/// ����Ĺ���:  ǰ���豸TCP������
/// �������ǰ���豸������\n
/// ���DVRע�ᡢУʱ��������ػ���־�ϴ�������ά�֡�ʵʱ��������ȡ�豸��Ϣ�ȹ���
class CTcpServer4Device : public J_AsioUser
						, public J_Service
{
	struct DeviceInfo
	{
		j_string_t strHostId;
		AsioDataInfo asioDataInfo;
	};
	typedef std::map<j_socket_t, DeviceInfo> DeviceMap;
public:
	CTcpServer4Device();
	~CTcpServer4Device();

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
	DeviceMap m_devMap;
};

#endif //~__TCP_SERVER4DEV_H_