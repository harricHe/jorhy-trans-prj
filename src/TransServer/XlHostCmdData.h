#ifndef __XL_HOST_CMD_H__
#define __XL_HOST_CMD_H__
#include "XlProtocol.h"

#pragma pack(push)
#pragma pack(1)
struct CXlHostCmdData
{
	struct CmdConrrectTime
	{
		time_t systime;				///< ��ǰϵͳʱ��
	};

	struct CmdConfigDev
	{
		char szID[32];             	//����ID
		char szVehicleID[32];       //����
		ULONG ulPhoneNum;           //�绰����
		int nTotalChannels;         //ͨ������
		int nTypeSize;				//����ͷ����
		int nNameSize;		  		//ͨ�����Ƴ��ȣ��ԡ�#������
	};

	struct CmdRealPlay
	{
		char szID[32];              //����ID
		long long llChnStatus; 		//ͨ������״̬  ���֧��64��ͨ��
	};

	struct CmdStartVod
	{
		GUID session;				//�ط�session
		char szID[32];				//����ID 
		long long llChnStatus; 		//ͨ������״̬  ���֧��64��ͨ��
		time_t tmStartTime;			//�طſ�ʼʱ��
		time_t tmEndTime;			//�طŽ���ʱ�䡣���طŵ����ڣ�����Ϊ-1
	};

	struct CmdStopVod
	{
		GUID session;				//�ط�session
		char szID[32];				//����ID
		long long llChnStatus; 		//ͨ������/�ر�״̬  ���֧��64��ͨ��
	};

	struct CmdOnOffInfo
	{
		time_t tmStart;				//��ʼʱ��, ��ȡ�����е���־tmStartΪ-1
		time_t tmEnd;				//����ʱ��, ��ȡ�����е���־tmEndΪ-1
	};

	struct CmdUpdateVodAck
	{
		unsigned char  code;		///< 0-�ɹ�, 1-ʧ��
	};

	struct CmdContextInfo
	{
		struct ContextHeader
		{
			long lUserID;                             ///< �û�ID 
			int nMessageTitleSize;  				  ///< ��Ϣ���ⳤ��
			unsigned long ulMessageSize;			  ///< ��Ϣ���ݳ���
			int nDevCount;							  ///< �豸����
			char data[1];
		};

		char *pContext;								  ///< ��Ϣ����
		union
		{
			ContextHeader header;
			char pData[1];
		};
	};

	struct CmdFileInfo
	{
		struct FileInfoHeader
		{
			long lUserID;                         ///< �û�ID 
			int nFileNameSize;  				  ///< �ļ����Ƴ���
			unsigned long ulFileSize;			  ///< �ļ�����
			int nDevCount;						  ///< �豸����
			char pData[1];
		};

		union
		{
			FileInfoHeader header;
			char pData[1];
		};
	};

	typedef struct CmdTalkCmd
	{
		char account[32];   	///< �˻���
		char equID[32];		///< �豸ID
		int state;

	};

	typedef struct CmdTalkData
	{
		char account[32];	 	///< �˻���
		char equID[32];		///< �豸ID
		unsigned int size;		///< ����������
	};

	CXlProtocol::CmdHeader cmdHeader;
	union
	{
		CmdConrrectTime cmdConrrectTime;
		CmdConfigDev cmdConfigDev;
		CmdRealPlay cmdRealPlay;
		CmdStartVod cmdStartVod;
		CmdStopVod cmdStopVod;
		CmdOnOffInfo cmdOnOffInfo;
		CmdUpdateVodAck cmdUpdateVodAck;
		CmdTalkCmd cmdTalkCmd;
		CmdTalkData cmdTalkData;
		char pData[1];
	};
	CXlProtocol::CmdTail tail;
};

typedef std::vector<CXlHostCmdData::CmdContextInfo> HostContextVec;
typedef std::vector<CXlHostCmdData::CmdFileInfo> HostFileInfoVec;

#pragma pack(pop)
#endif //!__XL_HOST_CMD_H__