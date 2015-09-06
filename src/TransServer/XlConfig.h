///////////////////////////////////////////////////////////////////////////
/// COPYRIGHT NOTICE
/// Copyright (c) 2009, xx�Ƽ����޹�˾(��Ȩ����) 
/// All rights reserved. 
/// 
/// @file      XlConfig.h 
/// @brief     ���ݿ�����м�ӿ�
///
/// @version   1.0 (�汾����)
/// @author    Jorhy (joorhy@gmail.com) 
/// @date      2013/11/01 09:02 
/// �޶�˵��������汾
///////////////////////////////////////////////////////////////////////////  
#ifndef __XLCONFIG_H_
#define __XLCONFIG_H_
#include "j_includes.h"
class CXlConfig
{
public:
	CXlConfig();
	~CXlConfig();

public:
	void Init(j_char_t *pReadBuff, j_char_t * pWriteBuff)
	{
		m_readBuff = pReadBuff;
		m_writeBuff = pWriteBuff;
	}
	j_result_t ProcessConfigRequest(j_int32_t nType, J_AsioDataBase *pAsioData);
	j_result_t ProcessConfigData(j_int32_t nType, J_AsioDataBase *pAsioData);

private:
	/// ��������
	j_result_t ProcessDvrList(J_AsioDataBase *pAsioData);
	j_result_t ProcessUserList(J_AsioDataBase *pAsioData);
	j_result_t ProcessDepartmentList(J_AsioDataBase *pAsioData);
	j_result_t ProcessLog(J_AsioDataBase *pAsioData);
	j_result_t ProcessAlarm(J_AsioDataBase *pAsioData);
	///�������ݽӿ�
	j_result_t MakeLogData(J_AsioDataBase *pAsioData);
	j_result_t MakeAlarmData(J_AsioDataBase *pAsioData);
	j_result_t MakeDvrListData(J_AsioDataBase *pAsioData);
	j_result_t MakeUserListData(J_AsioDataBase *pAsioData);
	j_result_t MakeDepartmentListData(J_AsioDataBase *pAsioData);
	///�������ݽӿ�
	j_result_t OnGetAlarmInfo(J_AsioDataBase *pAsioData);
	j_result_t OnGetTotleDvrInfo(J_AsioDataBase *pAsioData);
	j_result_t OnGetTotleUserInfo(J_AsioDataBase *pAsioData);
	j_result_t OnGetDvrList(J_AsioDataBase *pAsioData);
	j_result_t OnGetUserList(J_AsioDataBase *pAsioData);
	j_result_t OnGetDepartmentList(J_AsioDataBase *pAsioData);
	j_result_t OnGetDvrInfo(J_AsioDataBase *pAsioData);
	j_result_t OnGetUserInfo(J_AsioDataBase *pAsioData);
	j_result_t OnGetDepartmentInfo(J_AsioDataBase *pAsioData);
	j_result_t OnAddDvrInfo(J_AsioDataBase *pAsioData);
	j_result_t OnAddUserInfo(J_AsioDataBase *pAsioData);
	j_result_t OnAddDepartmentInfo(J_AsioDataBase *pAsioData);
	j_result_t OnModDvrInfo(J_AsioDataBase *pAsioData);
	j_result_t OnModUserInfo(J_AsioDataBase *pAsioData);
	j_result_t OnModDepartmentInfo(J_AsioDataBase *pAsioData);
	j_result_t OnDelDvrInfo(J_AsioDataBase *pAsioData);
	j_result_t OnDelUserInfo(J_AsioDataBase *pAsioData);
	j_result_t OnDelDepartmentInfo(J_AsioDataBase *pAsioData);
	///�豸��Ϣ
	j_result_t OnGetDevInfo(J_AsioDataBase *pAsioData);
	j_result_t OnGetLogInfo(J_AsioDataBase *pAsioData);
private:
	j_int32_t m_ioDvrListState;						//�豸��Ϣ����״̬
	j_int32_t m_ioUserListState;						//�û���Ϣ����״̬
	j_int32_t m_ioDepartmentListState;			//��λ��Ϣ����״̬
	j_int32_t m_ioAlarmState;							//��������״̬
	j_int32_t m_ioLogState;								//��־����״̬

	j_char_t *m_readBuff;								//�������󻺴���
	j_char_t *m_writeBuff;								//����ͻ�����
	j_char_t *m_dvrBuff;									//�豸��Ϣ���ͻ�����
	j_char_t *m_userBuff;								//�û���Ϣ���ͻ�����
	j_char_t *m_departmentBuff;						//��λ��Ϣ���ͻ�����
	j_char_t *m_alarmBuff;								//�������ͻ�����
	j_char_t *m_logBuff;									//��־���ͻ����� 

	CliHostInfoQueue m_dvrInfoQueue;							//�豸��Ϣ�������
	CliUserInfoQueue m_userInfoQueue;						//�û���Ϣ�������
	CliDepartmentInfoQueue m_departmentInfoQueue;	//��λ��Ϣ�������
	DevLogInfoQueue m_logInfoQueue;								//��ʷ��־�������
	CliAlarmInfoQueue m_alarmInfoQueue;						//��ʷ�����������
};
#endif //~__XLCONFIG_H_