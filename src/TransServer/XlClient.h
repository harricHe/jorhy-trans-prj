///////////////////////////////////////////////////////////////////////////
/// COPYRIGHT NOTICE
/// Copyright (c) 2009, xx�Ƽ����޹�˾(��Ȩ����) 
/// All rights reserved. 
/// 
/// @file      Client.h 
/// @brief     �ͻ���ģ��
///
/// @version   1.0 (�汾����)
/// @author    Jorhy (joorhy@gmail.com) 
/// @date      2013/09/24 15:11 
///
///
/// �޶�˵��������汾
///////////////////////////////////////////////////////////////////////////  
#ifndef __XL_CLIENT_H_
#define __XL_CLIENT_H_

#include "j_includes.h"
#include "x_socket.h"
#include "x_timer.h"
#include "XlDataBusDef.h"
/// ����Ĺ���:  �ͻ���ҵ������
class CXlClient : public J_Client
{
	typedef std::vector<CXlDataBusInfo> RequestVec;
	struct VehicleStatusEnable
	{
		j_boolean_t vehStatus;
		j_boolean_t alarmInfo;
	};
	typedef std::map<j_string_t, VehicleStatusEnable> VehicleEnableMap;
public:
	CXlClient(j_socket_t nSock);
	~CXlClient();

public:
	///J_Client
	j_boolean_t IsReady();
	j_result_t OnHandleRead(J_AsioDataBase *pAsioData);
	j_result_t OnHandleWrite(J_AsioDataBase *pAsioData);
	j_result_t OnRequest(const CXlDataBusInfo &cmdData);
	j_result_t OnResponse(const CXlDataBusInfo &respData);
	j_result_t OnMessage(j_string_t strHostId, const CXlDataBusInfo &respData);
	j_result_t OnBroken();

private:
	/// ��������
	j_result_t OnLogin(const CXlDataBusInfo &cmdData);
	j_result_t OnLogout(const CXlDataBusInfo &cmdData);
	j_result_t OnHeartBeat(const CXlDataBusInfo &cmdData);
	j_result_t SendRequest(const CXlDataBusInfo &cmdData);
	j_result_t OnTalkBackCommand(const CXlDataBusInfo &cmdData);
	j_result_t OnTalkBackData(const CXlDataBusInfo &cmdData);
	/// ������Ϣ����
	j_result_t SaveRequest(const CXlDataBusInfo &cmdData, j_boolean_t bSave);
	j_result_t EnableVehStatus(const CXlDataBusInfo &cmdData, j_boolean_t bEnable);
	j_result_t Recovery();
	/// ���ݴ���
	j_result_t SaveContext(const CXlDataBusInfo &cmdData);
	j_result_t SaveFiles(const CXlDataBusInfo &cmdData);
	/// �Խ�
	j_result_t TalkBackCommand(const CXlDataBusInfo &cmdData);
	j_result_t TalkBackData(const CXlDataBusInfo &cmdData);
	/// ��ִ��Ϣ
	j_result_t MessageBack(const CXlDataBusInfo &cmdData);

private:
	j_char_t m_userName[32];						//�û���
	j_char_t *m_readBuff;							//�������󻺴���
	j_char_t *m_writeBuff;							//����ͻ�����
	j_char_t *m_dataBuff;							//���ݻ�����

	j_int32_t m_ioCmdState;							//��������״̬
	j_int32_t m_ioDataState;						//��Ƶ����״̬
	CRingBuffer m_ringBuffer;						//��Ƶ������
	J_StreamHeader m_streamHeader;					//��Ƶ����ͷ��
	j_long_t m_nRefCnt;								//��Ƶ�����ü���

	j_int32_t m_state;								//�ͻ���״̬
	j_int32_t m_lastBreatTime;

	J_OS::CTLock m_locker;
	RequestVec m_requestVec;
	VehicleEnableMap m_vehEnableMap;

	/// ������Ϣ
	long m_lUserID;
	j_string_t m_strTitle;
	j_string_t m_strContext;
	FILE *m_pFile;									// �����ļ�д�ļ�����
	std::vector<j_string_t> m_transTargetMap;

	int m_nFileTotleSize;
};
#endif // ~__XL_CLIENT_H_
