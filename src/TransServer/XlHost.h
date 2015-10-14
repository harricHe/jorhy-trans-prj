///////////////////////////////////////////////////////////////////////////
/// COPYRIGHT NOTICE
/// Copyright (c) 2009, xx�Ƽ����޹�˾(��Ȩ����) 
/// All rights reserved. 
/// 
/// @file      XlHost.h 
/// @brief     XL_DVR�豸ģ��
///
/// @version   1.0 (�汾����)
/// @author    Jorhy (joorhy@gmail.com) 
/// @date      2013/09/22 17:40 
///
///
/// �޶�˵��������汾
///////////////////////////////////////////////////////////////////////////  
#ifndef __XLHOST_H_
#define __XLHOST_H_
#include "j_includes.h"
#include "x_socket.h"
#include "XlHostRespData.h"
#include "XlHostCmdData.h"
#include "XlClientCmdData.h"
/// ����Ĺ���:  XL�豸������
class CXlHost : public J_Host
{
	struct GUIDKey
	{
		GUIDKey(GUID session)
		{
			memcpy(&_session, &session, sizeof(GUID));
		}
		bool operator < (const GUIDKey &other) const
		{
			if (other._session.Data1 == _session.Data1)
			{
				if (_session.Data2 == other._session.Data2)
				{
					if (_session.Data3 == other._session.Data3)
					{
						return ((((UINT64)_session.Data4) < ((UINT64)other._session.Data4)));
					}
					return _session.Data3 < other._session.Data3;
				}
				return _session.Data2 < other._session.Data2;
			}
			return _session.Data1 < other._session.Data1;
		}
		GUID _session;
	};

public:
	CXlHost(j_string_t strHostId, j_socket_t nSock);
	~CXlHost();

public:
	///J_Host
	virtual j_result_t CreateChannel(const j_int32_t nChannelNum, J_Obj *&pObj);
	virtual j_boolean_t IsReady();
	virtual j_result_t OnBroken();
	virtual j_result_t GetHostId(j_string_t &strDevId);
	virtual j_result_t OnHandleRead(J_AsioDataBase *pAsioData);
	virtual j_result_t OnHandleWrite(J_AsioDataBase *pAsioData);
	virtual j_result_t OnRequest(const CXlClientCmdData &cmdData);

private:
	/// �����ı���Ϣ
	j_result_t OnMessage(const CXlHostRespData &respData);
	/// ������Ϣ
	j_result_t OnHeartBeat(const CXlHostRespData &respData);
	/// �����׼������
	j_result_t OnPrepare(const CXlHostRespData &respData);
	/// ������Ϣ(����GPS)
	j_result_t OnAlarmInfo(const CXlHostRespData &respData);
	/// ʵʱ��Ƶ����
	j_result_t OnRealData(const CXlHostRespData *respData);
	/// ��ʷ��Ƶ����
	j_result_t OnVodData(const CXlHostRespData *respData);
	/// ����ʱ�ӵķ�����Ϣ
	j_result_t OnConrrectTime(const CXlHostRespData &respData);
	/// ��ȡ�豸��Ϣ�ķ�����Ϣ
	j_result_t OnHostInfo(const CXlHostRespData &respData);
	/// ��ȡ��־�ķ�����Ϣ
	j_result_t OnOnOffInfo(const CXlHostRespData &respData);
	/// ����¼����Ϣ
	j_result_t OnUpdateVodInfo(const CXlHostRespData &respData);
	/// �Խ�����
	j_result_t OnTalkBackCommand(const CXlHostRespData &respData);
	j_result_t OnTalkBackData(const CXlHostRespData &respData);
	/// ���󷵻ش���
	j_result_t OnResponse(const CXlHostRespData &respData);

private:
	/// �ͻ��˷���������ʵʱ��Ƶ
	j_result_t StartRealPlay(const CXlClientCmdData &cmdData);
	/// �ͻ��˷�����ֹͣʵʱ��Ƶ
	j_result_t StopRealPlay(const CXlClientCmdData &cmdData);
	/// �ͻ��˷�����������ʷ��Ƶ
	j_result_t StartVod(const CXlClientCmdData &cmdData);
	/// �ͻ��˷�����ֹͣʵʱ��Ƶ
	j_result_t StopVod(const CXlClientCmdData &cmdData);
	/// �ͻ��˷������ı���Ϣ
	j_result_t SendContent(const CXlClientCmdData &cmdData);
	/// �ͻ��˷������ļ��ϴ�
	j_result_t SendFile(const CXlClientCmdData &cmdData);
	/// �ͻ��˷����ĶԽ�����
	j_result_t TalkBackCommand(const CXlClientCmdData &cmdData);
	j_result_t TalkBackData(const CXlClientCmdData &cmdData);

private:
	void GetChannel(j_uint64_t channel);

private:
	j_boolean_t m_bReady;
	j_socket_t m_socket;
	j_string_t m_hostId;
	j_int32_t m_lastBreatTime;

	j_char_t *m_readBuff;
	j_char_t *m_writeBuff;
	j_char_t *m_dataBuffer;

	j_int32_t m_ioState;							//�豸��״̬
	J_StreamHeader m_streamHeader;					//��Ƶ����ͷ��
	CRingBuffer m_ringBuffer;

	J_OS::TLocker_t m_vecClientLocker;
	std::vector<J_Client *> m_vecClient;

	std::vector<int> m_vecChannel;
	ChannelMap m_channelRealMap;

	std::map<GUIDKey, int> m_channelVodMap;

	HostContextVec m_contextVec;
	HostFileInfoVec m_fileInfoVec;
};

#endif