///////////////////////////////////////////////////////////////////////////
/// COPYRIGHT NOTICE
/// Copyright (c) 2009, xx�Ƽ����޹�˾(��Ȩ����) 
/// All rights reserved. 
/// 
/// @file      DahuaHost.h 
/// @brief     Dahua_DVR�豸ģ��
///
/// @version   1.0 (�汾����)
/// @author    Jorhy (joorhy@gmail.com) 
/// @date      2015/07/15 17:40 
///
///
/// �޶�˵��������汾
///////////////////////////////////////////////////////////////////////////  
#ifndef __DAHUAHOST_H_
#define __DAHUAHOST_H_

#include "j_includes.h"
#include "dhnetsdk.h"

/// ����Ĺ���:  �󻪳����豸������
class CDahuaHost : public J_Host
{
public:
	CDahuaHost(j_string_t strHostId, j_int64_t llHandle);
	~CDahuaHost();

public:
	virtual j_result_t CreateChannel(const j_int32_t nChannelNum, J_Obj *&pObj);
	virtual j_boolean_t IsReady() { return true; }
	virtual j_result_t OnBroken();
	virtual j_result_t GetHostId(j_string_t &strDevId) { strDevId = m_hostId; return J_OK; }
	virtual j_result_t OnHandleRead(J_AsioDataBase *pAsioData) { return 0; }
	virtual j_result_t OnHandleWrite(J_AsioDataBase *pAsioData) { return 0; }
	virtual j_result_t OnRequest(const CXlDataBusInfo &cmdData);

public:
	j_int64_t GetLoginHandle() const { return m_llHandle;  }
private:
	/// �ͻ��˷���������ʵʱ��Ƶ
	j_result_t StartRealPlay(const CXlDataBusInfo &cmdData);
	/// �ͻ��˷�����ֹͣʵʱ��Ƶ
	j_result_t StopRealPlay(const CXlDataBusInfo &cmdData);

private:
	j_int64_t m_llHandle;
	j_string_t m_hostId;
};

#endif //__DAHUAHOST_H_