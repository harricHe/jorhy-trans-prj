///////////////////////////////////////////////////////////////////////////
/// COPYRIGHT NOTICE
/// Copyright (c) 2009, xx�Ƽ����޹�˾(��Ȩ����) 
/// All rights reserved. 
/// 
/// @file      MySQLAccess.cpp 
/// @brief     MySQL���ݿ�ģ��ʵ��
///
/// @version   1.0 (�汾����)
/// @author    Jorhy (joorhy@gmail.com) 
/// @date      2015/04/22 11:11 
///
///
/// �޶�˵��������汾
///////////////////////////////////////////////////////////////////////////  
#include "MySQLAccess.h"
#include "XlHelper.h"
#include <time.h>
#include "XlHelper.h"


#include <iostream>

JO_IMPLEMENT_SINGLETON(MySQLAccess)

CMySQLAccess::CMySQLAccess()
{
	m_mysql = new MYSQL();
	m_bConnected = false;
}

CMySQLAccess::~CMySQLAccess()
{
	if (m_mysql != NULL)
	{
		delete m_mysql;
	}
}

j_result_t CMySQLAccess::Connect(const j_char_t *pAddr, j_int16_t nPort, const j_char_t *pUa, const j_char_t *pPwd)
{
	//�������ݿ�  
	if (!mysql_real_connect(m_mysql, pAddr, pUa, pPwd, "veh_data", 0, NULL, CLIENT_LOCAL_FILES))
	{
		J_OS::LOGINFO("Failed to connect to database: Error: %s", mysql_error(m_mysql));
		return J_DB_ERROR;
	}
	mysql_set_character_set(m_mysql, "gbk");
	//mysql_real_query(m_mysql,"SET NAMES 'UTF8'", strlen("SET NAMES 'UTF8'"));
	//mysql_query(m_mysql,"SET NAMES UTF8");
	J_OS::LOGINFO("character name: %s", mysql_character_set_name(m_mysql));

	m_bConnected = true;

	return J_OK;
}

j_result_t CMySQLAccess::Init()
{
	// ��ʼ��mysql  
	if (!mysql_init(m_mysql))
	{
		J_OS::LOGINFO("Failed to connect to database: Error: %s", mysql_error(m_mysql));
		return J_DB_ERROR;
	}

	return J_OK;
}

j_result_t CMySQLAccess::Release()
{
	return J_OK;
}

j_result_t CMySQLAccess::Login(const char *pUserName, const char *pPasswd, int nForce, int &nRet)
{
	if (!m_bConnected)
	{
		return J_DB_ERROR;
	}

	j_result_t nResult = J_OK;
	try
	{
		int ret;
		char strCmd[128] = { 0 };
		sprintf(strCmd, "SELECT * FROM UserInfo WHERE AccountName='%s';", pUserName);
		ret = mysql_real_query(m_mysql, strCmd, strlen(strCmd));//��ѯ
		if (ret == 0)
		{
			MYSQL_FIELD *fd;
			MYSQL_ROW sql_row;
			MYSQL_RES *result = mysql_store_result(m_mysql);//�����ѯ�������ݵ�result
			if (result->row_count != 0)
			{
				sql_row = mysql_fetch_row(result);

				int row = mysql_num_rows(result);
				int column = mysql_num_fields(result);
				for (int i = 0; fd = mysql_fetch_field(result); i++)//��ȡ����
				{
					if (strcmp("Password", fd->name) == 0)
					{
						if (strcmp(pPasswd, sql_row[i]) != 0)
						{
							nRet = 2;
							nResult = J_DB_ERROR;
							break;
						}
						else if (nForce)
						{
							sprintf(strCmd, "UPDATE UserInfo SET Online=1 WHERE AccountName='%s';", pUserName);
							ret = mysql_real_query(m_mysql, strCmd, strlen(strCmd));
							nRet = 0;
							break;
						}
					}

					if (!nForce && strcmp("Online", fd->name) == 0)
					{
						if (sql_row[i] != NULL && atoi(sql_row[i]) == 1)
						{
							nRet = 6;
							nResult = J_DB_ERROR;
							break;
						}
					}
				}

				memset(strCmd, 0, sizeof(strCmd));
				sprintf(strCmd, "UPDATE UserInfo SET Online=1 WHERE AccountName='%s';", pUserName);
				ret = mysql_real_query(m_mysql, strCmd, strlen(strCmd));
			}
			else
			{
				nRet = 1;
				return J_DB_ERROR;
			}

			if (result != NULL)
			{
				mysql_free_result(result);
			}
		}
	}
	catch (...)
	{
		J_OS::LOGDEBUG("CMySQLAccess::Login Exception");
		return J_DB_ERROR;
	}

	return nResult;
}

j_result_t CMySQLAccess::GetUserNameById(j_int32_t userId, j_string_t &userName)
{
	if (!m_bConnected)
	{
		return J_DB_ERROR;
	}

	try
	{
		char strCmd[128] = { 0 };
		sprintf(strCmd, "SELECT AccountName FROM UserInfo WHERE UserID=%d;", userId);
		int ret = mysql_real_query(m_mysql, strCmd, strlen(strCmd));
		if (ret == 0)
		{
			MYSQL_FIELD *fd;
			MYSQL_ROW sql_row;
			MYSQL_RES *result = mysql_store_result(m_mysql);//�����ѯ�������ݵ�result
			if (result)
			{
				for (int i = 0; fd = mysql_fetch_field(result); i++)//��ȡ����
				{
					if (strcmp("AccountName", fd->name) == 0)
					{
						sql_row = mysql_fetch_row(result);
						userName = sql_row[i];
						break;
					}
				}
			}
		}
		else
		{
			return J_DB_ERROR;
		}
	}
	catch (...)
	{
		J_OS::LOGDEBUG("CMySQLAccess::GetUserNameById Exception");
		return J_DB_ERROR;
	}

	return J_OK;
}

j_result_t CMySQLAccess::Logout(const char *pUserName)
{
	if (!m_bConnected)
	{
		return J_DB_ERROR;
	}

	try
	{
		char strCmd[128] = { 0 };
		sprintf(strCmd, "UPDATE UserInfo SET Online=0 WHERE AccountName='%s';", pUserName);
		int ret = mysql_real_query(m_mysql, strCmd, strlen(strCmd));
	}
	catch (...)
	{
		J_OS::LOGDEBUG("CMySQLAccess::Logout Exception");
		return J_DB_ERROR;
	}

	return J_OK;
}

j_result_t  CMySQLAccess::UpdateFileInfo(j_int32_t nFileId, j_int32_t nState, bool bFlag)
{
	if (!m_bConnected)
	{
		return J_DB_ERROR;
	}

	try
	{
		time_t loacl_tm = time(0);
		tm *today = localtime(&loacl_tm);
		char strCmd[128] = { 0 };
		if (bFlag)
		{
			sprintf(strCmd, "UPDATE FileInfo SET State=%d, CopyTime='%04d-%02d-%02d' WHERE FileID=%d;"
				, nState, today->tm_year + 1900, today->tm_mon, today->tm_mday, nFileId);
		}
		else
		{
			sprintf(strCmd, "UPDATE FileInfo SET State=%d WHERE FileID=%d;"
				, nState, nFileId);
		}
		int ret = mysql_real_query(m_mysql, strCmd, strlen(strCmd));
	}
	catch (...)
	{
		J_OS::LOGDEBUG("CMySQLAccess::UpdateFileInfo Exception");
		return J_DB_ERROR;
	}

	return J_OK;
}

j_result_t CMySQLAccess::UpdateDevInfo(const CXlDataBusInfo::XldRespHostInfo &hostInfo, bool bOnline)
{
	if (!m_bConnected)
	{
		return J_DB_ERROR;
	}

	try
	{
		char strCmd[256] = { 0 };
		sprintf(strCmd, "SELECT * FROM Equipment WHERE EquipmentID='%s';", hostInfo.hostId);
		int ret = mysql_real_query(m_mysql, strCmd, strlen(strCmd));

		MYSQL_RES *results = mysql_store_result(m_mysql);
		if (results->row_count == 0)
		{
			memset(strCmd, 0, sizeof(strCmd));
			sprintf(strCmd, "INSERT INTO Equipment (EquipmentID,VehicleNO,PhoneNum,TotalChannels,Online,State) VALUES ('%s','%s','%s',%d,%d,%d);",
				hostInfo.hostId, hostInfo.vehicleNum, hostInfo.phoneNum, hostInfo.totalChannels, bOnline, 1);
			ret = mysql_real_query(m_mysql, strCmd, strlen(strCmd));
		}

		memset(strCmd, 0, sizeof(strCmd));
		if (bOnline == true)
		{
			sprintf(strCmd, "UPDATE Equipment SET VehicleNO='%s',PhoneNum='%s',TotalChannels=%d,Online=%d WHERE EquipmentID='%s';",
				hostInfo.vehicleNum, hostInfo.phoneNum, hostInfo.totalChannels & 0xFF, bOnline, hostInfo.hostId);
		}
		else
		{
			sprintf(strCmd, "UPDATE Equipment SET Online=%d WHERE EquipmentID='%s';",
				bOnline, hostInfo.hostId);
		}
		ret = mysql_real_query(m_mysql, strCmd, strlen(strCmd));

		char *mediaType = (char *)hostInfo.data;

		char *pChannelData = mediaType + hostInfo.mediaTypeNum;
		char *pChannelEnd = NULL;
		for (int i = 0; i < hostInfo.totalChannels; i++)
		{
			memset(strCmd, 0, sizeof(strCmd));
			sprintf(strCmd, "SELECT * FROM EquipmentDetail WHERE EquipmentID='%s' AND channel=%d;", hostInfo.hostId, i + 1);
			ret = mysql_real_query(m_mysql, strCmd, strlen(strCmd));

			char channelName[64] = { 0 };
			j_string_t strChannelName;
			int nameLen = 0;
			pChannelEnd = strstr(pChannelData, "#");
			if (pChannelEnd != NULL)
			{
				nameLen = pChannelEnd - pChannelData;
				memcpy(channelName, pChannelData, nameLen);
			}
			else
			{
				strcpy(channelName, pChannelData);
			}
			pChannelData += (nameLen + 1);

			memset(strCmd, 0, sizeof(strCmd));

			results = mysql_store_result(m_mysql);
			if (results->row_count == 0)
			{
				sprintf(strCmd, "INSERT INTO EquipmentDetail (EquipmentID,channel,channelType,channelName) VALUES ('%s',%d,%d,'%s');",
					hostInfo.hostId, i + 1, mediaType[i] & 0xFF, channelName);
			}
			else
			{
				sprintf(strCmd, "UPDATE EquipmentDetail SET channelType=%d,channelName='%s' WHERE EquipmentID='%s' AND channel = %d;",
					mediaType[i] & 0xFF, channelName, hostInfo.hostId, i + 1);
			}
			ret = mysql_real_query(m_mysql, strCmd, strlen(strCmd));
		}
	}
	catch (...)
	{
		J_OS::LOGDEBUG("CSqlServerAccess::UpdateDevInfo Exception");
		return J_DB_ERROR;
	}

	return J_OK;
}

j_result_t CMySQLAccess::GetDevInfo(CXlDataBusInfo::XldRespHostInfo &hostInfo)
{
	if (!m_bConnected)
	{
		return J_DB_ERROR;
	}

	try
	{
		char strCmd[128] = { 0 };
		sprintf(strCmd, "SELECT * FROM Equipment WHERE EquipmentID='%s';", hostInfo.hostId);
		int ret = mysql_real_query(m_mysql, strCmd, strlen(strCmd));
		if (ret != 0)
		{
			return J_UNKNOW;
		}

		MYSQL_FIELD *fd;
		MYSQL_ROW sql_row;
		MYSQL_RES *result = mysql_store_result(m_mysql);//�����ѯ�������ݵ�result
		if (result)
		{
			for (int i = 0; fd = mysql_fetch_field(result); i++)//��ȡ����
			{
				if (strcmp("VehicleNO", fd->name) == 0)
				{
					sql_row = mysql_fetch_row(result);
					strcpy(hostInfo.vehicleNum, sql_row[i]);
				}
				if (strcmp("PhoneNum", fd->name) == 0)
				{
					sql_row = mysql_fetch_row(result);
					strcpy(hostInfo.phoneNum, sql_row[i]);
				}
				if (strcmp("TotalChannels", fd->name) == 0)
				{
					sql_row = mysql_fetch_row(result);
					hostInfo.totalChannels = atoi(sql_row[i]);
				}
			}
		}
	}
	catch (...)
	{
		J_OS::LOGDEBUG("CMySQLAccess::GetDevInfo Exception");
		return J_DB_ERROR;
	}

	return J_OK;
}

j_result_t CMySQLAccess::InsertAlarmInfo(const char *pHostId, const CXlDataBusInfo::XldRespAlarmInfo& alarmInfo)
{
	if (!m_bConnected)
	{
		return J_DB_ERROR;
	}

	try
	{
		char strCmd[512] = { 0 };
		//sprintf(strCmd, "INSERT INTO Alarm(EquipmentID,Alarm,GPS_Latitude,GPS_Longitude,GPS_Speed,Speed,TimeStamp)VALUES('%s',%I64d,%f,%f,%f,%f,%d);",
		//	pHostId, alarmInfo.bAlarm & 0xFF, alarmInfo.gps.dLatitude, alarmInfo.gps.dLongitude, alarmInfo.gps.dGPSSpeed, alarmInfo.speed, alarmInfo.tmTimeStamp);
		//m_pConn->Execute((_bstr_t)strCmd, NULL, adCmdText);
	}
	catch (...)
	{
		return J_DB_ERROR;
	}

	return J_OK;
}

time_t CMySQLAccess::GetDevLogLastTime(const char *pHostId)
{
	if (!m_bConnected)
	{
		return time(0) * 1000;
	}

	time_t tmReturn = 0;
	try
	{
		char strCmd[128] = { 0 };
		sprintf(strCmd, "SELECT MAX(TimeStamp) FROM EquipmentLog WHERE EquipmentID='%s';", pHostId);
		int ret = mysql_real_query(m_mysql, strCmd, strlen(strCmd));
		if (ret == 0)
		{
			MYSQL_FIELD *fd;
			MYSQL_ROW sql_row;
			MYSQL_RES *result = mysql_store_result(m_mysql);//�����ѯ�������ݵ�
			if (result->row_count != 0)
			{
				sql_row = mysql_fetch_row(result);
				if (sql_row[0] != NULL)
				{
					tmReturn = atol(sql_row[0]) * 1000;
				}
			}
		}
	}
	catch (...)
	{

	}

	return tmReturn;
}


/***********************************************************************************************************
 * ���򴴽����Խ���                     �����޸�:�Խ���
 * �������ܣ������豸IDɾ��RecordingLog �������־��Ϣ
 * ����˵����
 *  pHostId���豸ID
 * ע�����ʹ��֮ǰ��Ҫȷ���н�����豸ID����Ψһ��,����
 * �޸����ڣ�2015/10/09 09:36:00
 ***********************************************************************************************************/
j_result_t CMySQLAccess::DeleteLogInfo(const char *pHostId)
{
	if (NULL == pHostId)
		return J_DB_ERROR;

	if (!m_bConnected)
		return J_DB_ERROR;
	try
	{
		char strCmd[512] = { 0 };
		MYSQL_RES *result;
		int resCount;
		sprintf(strCmd, "DELETE * FROM recordinglog WHERE EquipmentID='%s'",
			pHostId);
		int ret = mysql_real_query(m_mysql, strCmd, strlen(strCmd));
		if (ret == 0)
			return J_OK;
		else
			return J_DB_ERROR;
	}
	catch (...)
	{
		return J_DB_ERROR;
	}
	return J_OK;
}


/***********************************************************************************************************
 * ���򴴽���������           �����޸ģ��Խ���
 * �������ܣ������ݿ�recordinglog�����������־��Ϣ,�����ظ��������ݡ�
 * ����˵����
 *  pHostId���豸ID
 *  tmStart����־��ʼʱ��
 *    tmEnd����־����ʱ��
 * ע�����δ�������ʱ����м�⣬ʹ��֮ǰ�벻Ҫ����Ƿ����ݡ�
 * �޸����ڣ�2015/09/16/ 16:02:00
 ***********************************************************************************************************/
j_result_t CMySQLAccess::InsertLogInfo(const char *pHostId, time_t tmStart, time_t tmEnd)
{	
	if (!CXlHelper::ActionTimestampCheck(tmStart, 8) || !CXlHelper::ActionTimestampCheck(tmEnd, 8))						//ȷ�����뵽ָ�����ݿ��ʱ�����ʽ����ȷ��
		return J_DB_ERROR;

	if (!m_bConnected)
		return J_DB_ERROR;
	try
	{
		char strCmd[512] = { 0 };
		MYSQL_RES *result;
		int resCount;
		sprintf(strCmd, "SELECT LogID FROM recordinglog WHERE StartTime = '%I64u' AND EquipmentID='%s'",
			tmStart, pHostId);
		int ret = mysql_real_query(m_mysql, strCmd, strlen(strCmd));

		if (ret == 0)                                                                                               //��־��ǰ���ݲ�ѯ�ɹ�
		{
			result = mysql_store_result(m_mysql);
			resCount = mysql_num_rows(result);
			mysql_free_result(result);
			memset(strCmd, 0, sizeof(strCmd));
			if (resCount > 0)																						//��־��ǰ�豸����ʼʱ�������ݿ��д���
			{
				sprintf(strCmd, "SELECT MAX(LogID) FROM recordinglog WHERE StartTime = '%I64u' AND EndTime < '%I64u' AND EquipmentID='%s'",
					tmStart, tmEnd, pHostId);
				ret = mysql_real_query(m_mysql, strCmd, strlen(strCmd));
				if (ret == 0)																					    //�Խ���ʱ��Ϊ��־�����ݲ�ѯ�ɹ�
				{
					long logId = -1;
					MYSQL_ROW sql_row;
					result = mysql_store_result(m_mysql);
					resCount = mysql_num_rows(result);
					if (resCount == 1)																				//��־��ǰ��ѯ�з��ؽ��
					{
						sql_row = mysql_fetch_row(result);
						if (sql_row[0] != NULL)
						{
							logId = atol(sql_row[0]);
							mysql_free_result(result);
							memset(strCmd, 0, sizeof(strCmd));
							sprintf(strCmd, "UPDATE recordinglog SET EndTime = '%I64u' WHERE LogID = '%d'", tmEnd, logId);
							ret = mysql_real_query(m_mysql, strCmd, strlen(strCmd));
							if (ret == 0)
								return J_OK;																		//���ݸ��³ɹ�
							else
								return J_DB_ERROR;																	//���ݸ���ʧ��
						}
						else
							return J_DB_ERROR;
					}
					else
					{
						return J_DB_ERROR;																			//�޷����½���ʱ��
					}
				}
				else
				{
					return J_DB_ERROR;																			    //�Խ���ʱ��ͳ���Ϊ���������ݲ�ѯʧ��
				}
			}
			else																									//��ǰ���������ݿ��в�����,ֻ��ֱ�Ӳ�������
			{
				sprintf(strCmd, "INSERT INTO recordinglog(EquipmentID,StartTime,EndTime) VALUES('%s','%I64u','%I64u')",
					pHostId, tmStart, tmEnd);
				ret = mysql_real_query(m_mysql, strCmd, strlen(strCmd));
				if (ret == 0)																					    //���ݲ���ɹ�
					return J_OK;
				else
					return J_DB_ERROR;																				//��������ʧ��
			}
		}
		else
		{
			return J_DB_ERROR;																						//�Կ�ʼʱ��ͳ���Ϊ���������ݲ�ѯʧ��
		}
	}
	catch (...)
	{
		return J_DB_ERROR;
	}
	return J_OK;
}


/***********************************************************************************************************
 * ���򴴽���������                     �����޸�:�Խ���
 * �������ܣ�����orɾ��DVR ����recordingfirsttime���������
 * ����˵����
 *  pHostId������ID
 *  tmFirstItem��ʱ��
 * ע�����null
 * �޸����ڣ�2015/10/12 14:38:00
 ***********************************************************************************************************/
j_result_t CMySQLAccess::SyncLogInfo(const char *pHostId, time_t tmFirstItem)
{
	if (NULL == pHostId)																							// ȷ���豸ID ��Ϊ��
		return J_DB_ERROR;

	if (!CXlHelper::ActionTimestampCheck(tmFirstItem, 8))														    // ȷ����ǰ��ʱ�����ʽ����ȷ��
		return J_DB_ERROR;

	if (!m_bConnected)
		return J_DB_ERROR;

	try
	{
		return J_OK;
		char strCmd[128] = { 0 };
		sprintf(strCmd, "UPDATE recordingfirsttime set FristTime= '%I64u' WHERE EquipmentID = '%s'", tmFirstItem, pHostId);
		int ret = mysql_real_query(m_mysql, strCmd, strlen(strCmd));
		if (ret == 0)
			return J_OK;
		else
			return J_DB_ERROR;
	}
	catch (...)
	{
		//J_OS::LOGDEBUG("CSqlServerAccess::UpdateDevInfo Exception");
		return J_DB_ERROR;
	}
	return J_OK;
}


/***********************************************************************************************************
 * ���򴴽���������                     �����޸�:�Խ���
 * �������ܣ���TransMessage���ݱ���������һ������    ����һ���豸�Ƿ����ߣ�
 * ����˵����
 *  lUserID���û�ID
 *   pTitle����Ϣ����
 * pContext����Ϣ����
 *  vecHost���豸ID
 * ע�����null
 * �޸����ڣ�2015/10/12 14:37:00
 ***********************************************************************************************************/
j_result_t CMySQLAccess::AddContextInfo(long lUserID, const char *pTitle, const char *pContext, std::vector<j_string_t> &vecHost)
{
	if (!m_bConnected)
		return J_DB_ERROR;

	try
	{
		char strCmd[256] = { 0 };
		char timeInterval[arr_size] = { 0 };
		CXlHelper::GetTimestamp(true, timeInterval);																// ��ȡϵͳʱ���

		/*int locSize = sizeof(pTitle);
		j_string_t klkl = mysql_character_set_name(m_mysql);

		j_string_t s(pTitle);

		j_string_t loc_strs;
		loc_strs = CXlHelper::ASCII2UTF_8(s);*/
		//CXlHelper::Ansi2UTF8("��", loc_strs);


		sprintf(strCmd, "INSERT INTO TransMessage(UserID,Title,Content,SendTime)VALUES(%d,'%s','%s','%s');",
			lUserID, pTitle, pContext, timeInterval);
		int ret = mysql_real_query(m_mysql, strCmd, strlen(strCmd));
		if (ret == 0)
		{
			int nMessageID = mysql_insert_id(m_mysql);																//��ȡ��ǰ�������ݺ��MessageIDֵ
			if (nMessageID >= 0)
			{
				std::vector<j_string_t>::iterator it = vecHost.begin();
				for (; it != vecHost.end(); it++)
				{
					memset(strCmd, 0, sizeof(strCmd));
					sprintf(strCmd,																					// �Ķ�ʱ��ͽ���ʱ��Ĭ��һ����״̬Ĭ�ϳ��ض��Ѿ�����
						"INSERT INTO TransMessageDetail(MessageID,EquipmentID,State,ReceTime,ReadTime)VALUES(%d,'%s','%d','%s','%s');",
						nMessageID, it->c_str(), 1, &timeInterval, &timeInterval);
					ret = mysql_real_query(m_mysql, strCmd, strlen(strCmd));
				}
			}
			else
			{
				return J_DB_ERROR;
			}
#pragma region [   ԭ���Ĵ����߼�   ]

			//memset(strCmd, 0, sizeof(strCmd));
			//sprintf(strCmd, "SELECT MAX(MessageID) FROM TransMessage;");

			//ret = mysql_real_query(m_mysql, strCmd, strlen(strCmd));
			//if (ret == 0)
			//{
			//	MYSQL_ROW sql_row_message_id;
			//	MYSQL_RES *result_message_id = mysql_store_result(m_mysql);                                         //�����ѯ�������ݵ�
			//	int nMessageID = 0;
			//	if (result_message_id->row_count != 0)
			//	{
			//		sql_row_message_id = mysql_fetch_row(result_message_id);
			//		if (sql_row_message_id[0] != NULL)
			//		{
			//			nMessageID = atol(sql_row_message_id[0]);
			//		}
			//	}

			//	std::vector<j_string_t>::iterator it = vecHost.begin();
			//	for (; it != vecHost.end(); it++)
			//	{
			//		memset(strCmd, 0, sizeof(strCmd));
			//		sprintf(strCmd, "INSERT INTO TransMessageDetail(MessageID,EquipmentID)VALUES(%d,'%s');", nMessageID, it->c_str());
			//		ret = mysql_real_query(m_mysql, strCmd, strlen(strCmd));
			//	}
			//}
#pragma endregion
		}

	}
	catch (...)
	{
		return J_DB_ERROR;
	}

	return J_OK;
}


/***********************************************************************************************************
 * ���򴴽���������                     �����޸�:�Խ���
 * �������ܣ���transfile���ݱ���������һ������---��һ��״̬
 * ����˵����
 *   lUserID�����������ļ����û�ID
 * pFileName�������ļ�������
 * pFilePath�������ļ���ת������˴洢��λ��
 *   vecHost�����ո��ļ��ĳ��ؿͻ���ID
 * ע�����null
 * �޸����ڣ�2015\10\15 14:57:00
 ***********************************************************************************************************/
j_result_t CMySQLAccess::AddFileInfo(long lUserID, const char *pFileName, const char *pFilePath, std::vector<j_string_t> &vecHost)
{
	if (!m_bConnected || lUserID < 0 || NULL == pFileName || NULL == pFilePath)
		return J_DB_ERROR;

	char timeInterval[arr_size] = { 0 };
	CXlHelper::GetTimestamp(true, timeInterval);																	// ��ȡ��ǰϵͳ��ʱ���
	try
	{
		char strCmd[512] = { 0 };
		sprintf(strCmd, "INSERT INTO TransFile(UserID,Name,FilePath,SendTime)VALUES(%d,'%s','%s','%s');",
			lUserID, pFileName, pFilePath, timeInterval);															// Ĭ�Ϸ���ʱ���ɾ��ʱ��һ��

		int ret = mysql_real_query(m_mysql, strCmd, strlen(strCmd));
		if (ret == 0)
		{
			int nFileID = mysql_insert_id(m_mysql);																    //��ȡ��ǰ�������ݺ��nFileIDֵ
			if (nFileID >= 0)
			{
				std::vector<j_string_t>::iterator it = vecHost.begin();
				for (; it != vecHost.end(); it++)
				{
					memset(strCmd, 0, sizeof(strCmd));
					sprintf(strCmd, "INSERT INTO TransFileDetail(FileID,EquipmentID,ReceTime)VALUES(%d,'%s','%s');", nFileID, it->c_str(), timeInterval);
					ret = mysql_real_query(m_mysql, strCmd, strlen(strCmd));
				}
			}
			else
			{
				return J_DB_ERROR;
			}
		}
	}
	catch (...)
	{
		return J_DB_ERROR;
	}

	return J_OK;

#pragma region [   �޸�֮ǰ�Ĵ���   ]
	//if (!m_bConnected)
	//{
	//	return J_DB_ERROR;
	//}

	//try
	//{
	//	char strCmd[128] = { 0 };
	//	sprintf(strCmd, "INSERT INTO TransFile(UserID,Name,FilePath)VALUES(%d,'%s','%s');",
	//		lUserID, pTitle, pFilePath);
	//	int ret = mysql_real_query(m_mysql, strCmd, strlen(strCmd));
	//	if (ret == 0)
	//	{
	//		memset(strCmd, 0, sizeof(strCmd));
	//		sprintf(strCmd, "SELECT MAX(FileID) FROM TransFile;");

	//		ret = mysql_real_query(m_mysql, strCmd, strlen(strCmd));
	//		if (ret == 0)
	//		{
	//			MYSQL_ROW sql_row_file_id;
	//			MYSQL_RES *result_file_id = mysql_store_result(m_mysql);//�����ѯ�������ݵ�
	//			int nFileID = 0;
	//			if (result_file_id->row_count != 0)
	//			{
	//				sql_row_file_id = mysql_fetch_row(result_file_id);
	//				if (sql_row_file_id[0] != NULL)
	//				{
	//					nFileID = atol(sql_row_file_id[0]);
	//				}
	//			}

	//			std::vector<j_string_t>::iterator it = vecHost.begin();
	//			for (; it != vecHost.end(); it++)
	//			{
	//				memset(strCmd, 0, sizeof(strCmd));
	//				sprintf(strCmd, "INSERT INTO TransFileDetail(FileID,EquipmentID)VALUES(%d,'%s');", nFileID, it->c_str());
	//				ret = mysql_real_query(m_mysql, strCmd, strlen(strCmd));
	//			}
	//		}
	//	}

	//}
	//catch (...)
	//{
	//	return J_DB_ERROR;
	//}

	//return J_OK;
#pragma endregion
}


/***********************************************************************************************************
 * ���򴴽���������                     �����޸�:�Խ���
 * �������ܣ�����������Ϣ��־
 * ����˵����
 *    lMessageID��������ϢID
 * nMessageState����Ϣ״̬
 *  nDetailState����ϸ״̬
 * ע�����null
 * �޸����ڣ�2015/10/12 14:15:00
 ***********************************************************************************************************/
j_result_t CMySQLAccess::UpdateContextInfo(long lMessageID, int nMessageState, int nDetailState)
{
	if (lMessageID < 0)																								// ��ǰλ�õ���ϢID����Ϊ����
		return J_DB_ERROR;

	if (!m_bConnected)
		return J_DB_ERROR;

	try
	{
		return J_OK;
		char strCmd[128] = { 0 };																					// ����transmessage����Ϣ״̬
		sprintf(strCmd, "UPDATE transmessage set DealStatus= '%s' WHERE MessageID = '%s'", nMessageState, lMessageID);
		int ret = mysql_real_query(m_mysql, strCmd, strlen(strCmd));
		if (ret == 0)
		{
			memset(strCmd, 0, sizeof(strCmd));																		// ����transmessagedetail����Ϣ״̬
			sprintf(strCmd, "UPDATE transmessagedetail set State= '%s' WHERE MessageID = '%s'", nDetailState, lMessageID);
			ret = mysql_real_query(m_mysql, strCmd, strlen(strCmd));
			return	ret == 0 ? J_OK : J_DB_ERROR;
		}
		else
			return J_DB_ERROR;
	}
	catch (...)
	{
		return J_DB_ERROR;
	}
	return J_OK;
}


/***********************************************************************************************************
 * ���򴴽���������                     �����޸�:������
 * �������ܣ����������ļ���־
 * ����˵����
 *      lFileID�������ļ�ID
 *   nFileState���ļ�״̬
 * nDetailState����ϸ״̬
 * ע�����null
 * �޸����ڣ�2015/10/12 14:17:00
 ***********************************************************************************************************/
j_result_t CMySQLAccess::UpdateFileInfo(long lFileID, int nFileState, int nDetailState)
{
	if (lFileID < 0)																								// ��ǰλ�õ��ļ�ID����Ϊ����
		return J_DB_ERROR;

	if (!m_bConnected)
		return J_DB_ERROR;

	try
	{
		return J_OK;
		char strCmd[128] = { 0 };																					// ����transfile����Ϣ״̬
		sprintf(strCmd, "UPDATE transfile set State= '%s' WHERE MessageID = '%s'", nFileState, lFileID);
		int ret = mysql_real_query(m_mysql, strCmd, strlen(strCmd));
		if (ret == 0)
		{
			memset(strCmd, 0, sizeof(strCmd));																		// ����transfiledetail����Ϣ״̬
			sprintf(strCmd, "UPDATE transfiledetail set State= '%s' WHERE MessageID = '%s'", nDetailState, lFileID);
			ret = mysql_real_query(m_mysql, strCmd, strlen(strCmd));
			return	ret == 0 ? J_OK : J_DB_ERROR;
		}
		else
			return J_DB_ERROR;
	}
	catch (...)
	{
		return J_DB_ERROR;
	}
	return J_OK;
}


/***********************************************************************************************************
 * ���򴴽���������                     �����޸�:�Խ���
 * �������ܣ�ɾ��������Ϣ��־
 * ����˵����
 * lMessageID��������ϢID
 * ע�����null
 * �޸����ڣ�2015/10/12 14:18:00
 ***********************************************************************************************************/
j_result_t CMySQLAccess::DelContextInfo(long lMessageID)
{
	if (lMessageID < 0)																								// ��ǰλ�õ���ϢID����Ϊ����
		return J_DB_ERROR;

	if (!m_bConnected)
		return J_DB_ERROR;

	try
	{
		/// ����ɾ����
	}
	catch (...)
	{
		return J_DB_ERROR;
	}

	/// TODO by zhao jin jun
	return J_OK;
}


/***********************************************************************************************************
 * ���򴴽���������                     �����޸�:�Խ���
 * �������ܣ�ɾ�������ļ���־
 * ����˵����
 *  lFileID�������ļ�ID
 * ע�����null
 * �޸����ڣ�2015/10/12 14:20:00
 ***********************************************************************************************************/
j_result_t CMySQLAccess::DelFileInfo(long lFileID)
{
	if (lFileID < 0)																								// ��ǰλ�õ��ļ�ID����Ϊ����
		return J_DB_ERROR;

	if (!m_bConnected)
		return J_DB_ERROR;

	try
	{
		/// ����ɾ����
	}
	catch (...)
	{
		return J_DB_ERROR;
	}
	return J_OK;
}

j_result_t CMySQLAccess::GetContextList(const char *pHostId, HostContextVec &contextVec)
{
	if (!m_bConnected)
	{
		return J_DB_ERROR;
	}

	try
	{
		mysql_set_character_set(m_mysql, "unicode");
		char strCmd[128] = { 0 };
		sprintf(strCmd, "SELECT MessageID FROM TransMessageDetail WHERE EquipmentID='%s';", pHostId);
		int ret = mysql_real_query(m_mysql, strCmd, strlen(strCmd));
		if (ret == 0)
		{
			MYSQL_ROW sql_row_message_id;
			MYSQL_RES *result_message_id = mysql_store_result(m_mysql);//�����ѯ�������ݵ�
			int nMessageID = 0;
			if (result_message_id->row_count != 0)
			{
				for (; sql_row_message_id = mysql_fetch_row(result_message_id);)
				{
					if (sql_row_message_id[0] != NULL)
					{
						nMessageID = atol(sql_row_message_id[0]);
					}

					memset(strCmd, 0, sizeof(strCmd));
					sprintf(strCmd, "SELECT UserID,Title,Content  FROM TransMessage WHERE MessageID=%d;", nMessageID);

					ret = mysql_real_query(m_mysql, strCmd, strlen(strCmd));
					if (ret == 0)
					{
						MYSQL_FIELD *fd_message;
						MYSQL_ROW sql_row_message;
						MYSQL_RES *result_message = mysql_store_result(m_mysql);//�����ѯ�������ݵ�
						if (result_message->row_count != 0)
						{
							int nUserID = 0;
							int nTitleLen = 0;
							char *pTitle = NULL;
							int nContentLen = 0;
							char *pContent = NULL;

							sql_row_message = mysql_fetch_row(result_message);
							for (int j = 0; fd_message = mysql_fetch_field(result_message); j++)//��ȡ����
							{
								if (strcmp("UserID", fd_message->name) == 0)
								{
									nUserID = atoi(sql_row_message[j]);
								}
								if (strcmp("Title", fd_message->name) == 0)
								{
									nTitleLen = strlen(sql_row_message[j]);
									pTitle = new char[nTitleLen + 1];
									memset(pTitle, 0, nTitleLen + 1);
									memcpy(pTitle, sql_row_message[j], nTitleLen);
								}
								if (strcmp("Content", fd_message->name) == 0)
								{
									nContentLen = strlen(sql_row_message[j]);
									pContent = new char[nContentLen + 1];
									memset(pContent, 0, nContentLen + 1);
									memcpy(pContent, sql_row_message[j], nContentLen);
								}
							}

							CXlDataBusInfo::XldCmdContextInfo *pContentInfo = (CXlDataBusInfo::XldCmdContextInfo *)malloc(sizeof(CXlDataBusInfo::XldCmdContextInfo) + nTitleLen);
							pContentInfo->header.lUserID = nUserID;
							pContentInfo->header.lMessageID = nMessageID;
							pContentInfo->header.nMessageTitleSize = nTitleLen;
							pContentInfo->header.ulMessageSize = nContentLen;
							memcpy(pContentInfo->header.data, pTitle, nTitleLen);
							delete[]pTitle;
							pContentInfo->pContext = pContent;
							contextVec.push_back(pContentInfo);
						}
					}
				}
			}
		}

	}
	catch (...)
	{
		return J_DB_ERROR;
	}

	return J_OK;
}

j_result_t CMySQLAccess::GetFileInfoList(const char *pHostId, HostFileInfoVec &fileVec)
{
	if (!m_bConnected)
	{
		return J_DB_ERROR;
	}

	try
	{
		char strCmd[128] = { 0 };
		sprintf(strCmd, "SELECT FileID FROM TransFileDetail WHERE EquipmentID='%s';", pHostId);
		int ret = mysql_real_query(m_mysql, strCmd, strlen(strCmd));
		if (ret == 0)
		{
			MYSQL_ROW sql_row_file_id;
			MYSQL_RES *result_file_id = mysql_store_result(m_mysql);//�����ѯ�������ݵ�
			int nFileID = 0;
			if (result_file_id->row_count != 0)
			{
				for (; sql_row_file_id = mysql_fetch_row(result_file_id);)
				{
					if (sql_row_file_id[0] != NULL)
					{
						nFileID = atol(sql_row_file_id[0]);
					}

					memset(strCmd, 0, sizeof(strCmd));
					sprintf(strCmd, "SELECT UserID,Name,FilePath FROM TransFile WHERE FileID=%d;", nFileID);

					ret = mysql_real_query(m_mysql, strCmd, strlen(strCmd));
					if (ret == 0)
					{
						MYSQL_FIELD *fd_file;
						MYSQL_ROW sql_row_file;
						MYSQL_RES *result_file = mysql_store_result(m_mysql);//�����ѯ�������ݵ�
						if (result_file->row_count != 0)
						{
							int nUserID = 0;
							int nTitleLen = 0;
							char *pTitle = NULL;
							int nFilePathLen = 0;
							char *pFileName = NULL;

							sql_row_file = mysql_fetch_row(result_file);
							for (int j = 0; fd_file = mysql_fetch_field(result_file); j++)//��ȡ����
							{
								if (strcmp("UserID", fd_file->name) == 0)
								{
									nUserID = atoi(sql_row_file[j]);
								}
								if (strcmp("Name", fd_file->name) == 0)
								{
									nTitleLen = strlen(sql_row_file[j]);
									pTitle = new char[nTitleLen + 1];
									memset(pTitle, 0, nTitleLen + 1);
									memcpy(pTitle, sql_row_file[j], nTitleLen);
								}
								if (strcmp("FilePath", fd_file->name) == 0)
								{
									nFilePathLen = strlen(sql_row_file[j]);
									pFileName = new char[nFilePathLen + 1];
									memset(pFileName, 0, nFilePathLen + 1);
									memcpy(pFileName, sql_row_file[j], nFilePathLen);
								}
							}

							CXlDataBusInfo::XldCmdFileInfo *pFileInfo = (CXlDataBusInfo::XldCmdFileInfo *)malloc(sizeof(CXlDataBusInfo::XldCmdFileInfo) + nTitleLen);
							pFileInfo->header.lUserID = nUserID;
							pFileInfo->header.nFileID = nFileID;
							pFileInfo->header.nFileNameSize = nTitleLen;
							pFileInfo->header.ulFileSize = 0;
							memcpy(pFileInfo->header.pData, pTitle, nTitleLen);
							delete[]pTitle;
							pFileInfo->pFileName = pFileName;
							fileVec.push_back(pFileInfo);
						}

					}
				}
			}
		}

	}
	catch (...)
	{
		return J_DB_ERROR;
	}

	return J_OK;
}