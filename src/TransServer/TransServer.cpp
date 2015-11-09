///////////////////////////////////////////////////////////////////////////
/// COPYRIGHT NOTICE
/// Copyright (c) 2009, xx�Ƽ����޹�˾(��Ȩ����) 
/// All rights reserved. 
/// 
/// @file      nvr.cpp 
/// @brief     NVRӦ�ó���ģ��
///
/// @version   1.0 (�汾����)
/// @author    Jorhy (joorhy@gmail.com) 
/// @date      2013/09/18 17:11 
///
///
/// �޶�˵��������汾
///////////////////////////////////////////////////////////////////////////  
#include "TcpServer4Client.h"
#include "TcpServer4Device.h"
#include "MySQLAccess.h"

#ifdef _DEBUG
#pragma comment (lib, "Debug\\core.lib")
#else
#pragma comment (lib, "Release\\core.lib")
#endif

CTcpServer4Device g_deviceServer;
CTcpServer4Client g_clientServer;

const char *g_ini_file = ".//TranServer.ini";

int main(int argc, char **argv)
{
	///��ʼ�����ݿ�
	if (GetPrivateProfileInt("data_base", "enable", 0, g_ini_file) == 1)
	{
		char strDbAddr[16] = { 0 };
		char strDbUser[32] = { 0 };
		char strDbPassWord[32] = { 0 };
		int nDbPort = GetPrivateProfileInt("data_base", "port", 3306, g_ini_file);
		GetPrivateProfileString("data_base", "addr", "10.0.0.123", strDbAddr, sizeof(strDbAddr), g_ini_file);
		GetPrivateProfileString("data_base", "user", "root", strDbUser, sizeof(strDbUser), g_ini_file);
		GetPrivateProfileString("data_base", "password", "123456", strDbPassWord, sizeof(strDbPassWord), g_ini_file);
		JoDataBaseObj->Init();
		if (JoDataBaseObj->Connect(strDbAddr, nDbPort, strDbUser, strDbPassWord) != J_OK)
		{
			J_OS::LOGINFO("���ݿ�����ʧ��, IP��ַ:%s,�˿�:%d,�û���:%s,����:%s", strDbAddr, nDbPort, strDbUser, strDbPassWord);
			//return -1;
		}
	}

	///�����豸��������
	if (GetPrivateProfileInt("device", "enable", 0, g_ini_file) == 1)
	{
		if (g_deviceServer.StartServer(g_ini_file) != J_OK)
		{
			J_OS::LOGINFO("�����豸��������ʧ��");
			//return -1;
		}
	}

	///�����ͻ���������
	if (GetPrivateProfileInt("client", "enable", 0, g_ini_file) == 1)
	{
		if (g_clientServer.StartServer(g_ini_file) != J_OK)
		{
			J_OS::LOGINFO("�����ͻ���������ʧ��");
			//return -1;
		}
	}

	while (true)
	{
		Sleep(100);
	}

	///ֹͣ�ͻ���������
	g_clientServer.StopServer();
	///ֹͣ�豸��������
	g_deviceServer.StopServer();
	///ֹͣƽ̨����
	JoDataBaseObj->Release();

	return 0;
}