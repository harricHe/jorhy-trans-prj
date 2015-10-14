#ifndef __XL_HOST_RESP_DATA_H__
#define __XL_HOST_RESP_DATA_H__
#include "XlProtocol.h"

#pragma pack(push)
#pragma pack(1)
struct CXlHostRespData
{
	struct RespMessage
	{
		char szID[32];					///< ����
		unsigned int unMsg;				///< ��Ϣ��
		unsigned long ulDataSize;		///< ��Ϣ���ݳ���
		char data[1];					///< ��Ϣ��
	};

	struct RespHostId
	{
		char hostId[32];				///< ����ID
	};

	struct RespCorrectTime
	{
		unsigned char  code;			///< 0-�ɹ�, 1-ʧ��
	};

	struct RespHostInfo
	{
		char hostId[32];			///< �豸ID
		char vehicleNum[8];			///< �г���
		char phoneNum[12];			///< �绰����
		char totalChannels;			///< ͨ����Ŀ
		char mediaTypeNum;			///< ý������
		int  chNameSize;			///< ͨ�����Ƴ���
		char data[1];				///< ͨ������
	};

	typedef struct RespAlarmInfo
	{
		time_t tmTimeStamp;				///< ʱ���
		char bAlarm;					///< ��������
		double dLatitude;
		double dLongitude;
		double dGPSSpeed;
	};

	struct RespRealData
	{
		char hostId[32];				///< �豸ID
		unsigned char channel;			///< ͨ����
		char data[1];
	};

	struct RespStopReal
	{
		unsigned char  code;			///< 0-�ɹ�, 1-ʧ��
	};

	struct RespVodData
	{
		GUID sessionId;					///< �ػ�ID	
		char hostId[32];				///< �豸ID
		unsigned char channel;			///< ͨ����
		char data[1];
	};

	struct RespStopVod
	{
		unsigned char  code;			///< 0-�ɹ�, 1-ʧ��
	};

	struct RespConrrectTime
	{
		unsigned char  code;			///< 0-�ɹ�, 1-ʧ��
	};

	struct RespOnOffInfo
	{
		time_t tmStart;					/// ��ʼʱ��
		time_t tmEnd;					/// ����ʱ��
	};

	struct RespVodInfo
	{
		time_t tmStart;					/// ��ʼʱ��
		time_t tmEnd;					/// ����ʱ��
	};

	typedef struct RespTalkCmd
	{
		char account[32];   	///< �˻���
		char equID[32];		///< �豸ID
		int state;

	};

	typedef struct RespTalkData
	{
		char account[32];	 	///< �˻���
		char equID[32];		///< �豸ID
		unsigned int size;		///< ����������
	};

	CXlProtocol::CmdHeader respHeader;
	union
	{
		RespMessage respMessage;
		RespHostId respHostId;
		RespCorrectTime respConrrectTime;
		RespHostInfo respHostInfo;
		RespAlarmInfo respAlarmInfo;
		RespRealData respRealData;
		RespStopReal respStopReal;
		RespVodData respVodData;
		RespStopVod respStopVod;
		RespOnOffInfo respOnOffInfo;
		RespVodInfo respVodInfo;
		RespTalkCmd respTalkCmd;
		RespTalkData respTalkData;
		char pData[1];
	};
};
#pragma pack(pop)

#endif //!__XL_HOST_RESP_DATA_H__