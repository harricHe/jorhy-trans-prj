#ifndef __DATA_BUS_H_
#define __DATA_BUS_H_
#include "j_includes.h"
#include "x_timer.h"
#include "x_lock.h"
#include "XlClientCmdData.h"
#include "XlClientRespData.h"

class CDataBus
{
	/// �豸ע��
	typedef std::map<j_string_t, J_Host *> HostMap;
	/// ��Ϣ����
	typedef std::map<j_string_t, J_Client *> MessageMap;
	/// ��Ϣ���󼰻ظ�
	struct RequestKey
	{
		RequestKey(){}
		RequestKey(J_Client *pClient, j_uint32_t nSeq)
		{
			this->pClient = pClient;
			this->nSeq = nSeq;
		}
		bool operator < (const RequestKey &other) const
		{
			if (other.pClient == pClient)
			{
				return nSeq < other.nSeq;
			}
			return pClient < other.pClient;
		}
		J_Client *pClient;
		j_uint32_t nSeq;
	};
	struct RequestInfo
	{
		J_Client *pClient;
		CXlProtocol::CmdHeader cmdHeader;
		j_int32_t nTimeOut;
	};
	typedef std::map<RequestKey, RequestInfo> RequestMap;
	typedef std::map<j_uint32_t, RequestKey> ResponseMap;
	/// ��Ϣ��ʱ
	typedef std::map<RequestKey, J_Client *> RequestTimeOutMap;
public:
	CDataBus();
	~CDataBus();

public:
	/// ע���豸����
	/// @param[in]		strHostId �豸ID
	/// @param[in]		pHost �豸���� 
	/// @return			�μ�j_errtype.h 
	j_result_t RegisterDevice(j_string_t strHostId, J_Host *pHost);
	/// �����������
	/// @param[in]		pClient �������
	/// @return			�μ�j_errtype.h 
	j_result_t ClearRequest(J_Client *pClient);
	/// �����豸��Ϣ
	/// @param[in]		pClient �����߶���
	/// @param[in]		strUserId �û�ID
	/// @return			�μ�j_errtype.h 
	j_result_t SubscribeMsg(j_string_t strUserId, J_Client *pClient);
	/// ����������Ϣ
	/// @param[in]		cmdData ������Ϣ����
	/// @param[in]		pClient ������
	/// @param[in]		nTimeOut ����ʱʱ��,��λms 
	/// @return			�μ�j_errtype.h 
	j_result_t Request(j_string_t strHostId, J_Client *pClient, const CXlClientCmdData cmdData, j_uint32_t nTimeOut = 3000);
	/// ����Ӧ����Ϣ
	/// @param[in]		respData Ӧ����Ϣ����
	/// @return			�μ�j_errtype.h 
	j_result_t Response(const CXlClientRespData &respData);
	/// �¼���Ϣ
	/// @param[in]		strHostId �豸ID
	/// @param[in]		respData �¼���Ϣ����
	/// @return			�μ�j_errtype.h 
	j_result_t OnMessage(j_string_t strHostId, const CXlClientRespData &respData);
	
	/// ��ȡȫ��Ψһ�����к�
	/// @return			���к�
	j_uint32_t GetUniqueSeq() { return m_nUniqueSeq++; }

private:
	static void OnTimer(void *pUser)
	{
		(static_cast<CDataBus *>(pUser))->CheckState();
	}
	void CheckState();

private:
	J_OS::CTimer m_timer;
	J_OS::CTLock m_locker;

	volatile j_uint32_t m_nUniqueSeq;

	HostMap m_hostMap;
	MessageMap m_messageMap;
	RequestMap m_requestMap;
	ResponseMap m_responseMap;
	RequestTimeOutMap m_requestTimeOutMap;
};

JO_DECLARE_SINGLETON(DataBus)

#endif //~__DATA_BUS_H_