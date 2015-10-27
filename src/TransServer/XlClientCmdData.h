#ifndef __XL_CLIENT_CMD_DATA__
#define __XL_CLIENT_CMD_DATA__
#include "XlProtocol.h"

#pragma pack(push)
#pragma pack(1)
struct CXlClientCmdData
{
	struct CmdLogin
	{
		char userName[16];		///< �˻���
		char passWord[16];  	///< ����
		int  nForced;			///< 1 ǿ�Ƶ�¼��0 ��ǿ�Ƶ�¼
		long version;			///< �ͻ��˰汾
	};

	struct CmdRealAlarm
	{
		char  hostId[32];		///< �豸ID
	};

	struct CmdRealPlay
	{
		char hostId[32];		///< �豸ID
		long long channel;		///< ͨ����
		CRingBuffer *pBuffer;
	};

	typedef struct CmdStartVod
	{
		GUID sessionId;			///< �ػ�ID
		char hostId[32];		///< �豸ID
		long long channel;		///< ͨ����	
		time_t tmStartTime;		///< ��ʼʱ��
		time_t tmEndTime;		///< ����ʱ��
		CRingBuffer *pBuffer;
	};

	typedef struct CmdStopVod
	{
		GUID sessionId;			///< �ػ�ID
		char hostId[32];		///< �豸ID
		long long channel;		///< ͨ����	
		CRingBuffer *pBuffer;
	};

	typedef struct CmdContextInfo
	{
		long lUserID;                             ///< �û�ID 
		int nMessageTitleSize;  				  ///< ��Ϣ���ⳤ��
		unsigned long ulMessageSize;			  ///< ��Ϣ���ݳ���
		int nDevCount;							  ///< �豸����
		char pData[1];
	};

	typedef struct CmdFileInfo
	{
		long lUserID;                         ///< �û�ID 
		int nFileNameSize;  				  ///< �ļ����Ƴ���
		unsigned long ulFileSize;			  ///< �ļ�����
		int nDevCount;						  ///< �豸����
		char pData[1];
	};

	CXlProtocol::CmdHeader cmdHeader;
	union
	{
		CmdLogin cmdLogin;
		CmdRealAlarm cmdRealAlarm;
		CmdRealPlay cmdRealPlay;
		CmdStartVod cmdStartVod;
		CmdStopVod cmdStopVod;
		CmdContextInfo cmdContextInfo;
		CmdFileInfo cmdFileInfo;
		char pData[1];
	};
};
#pragma pack(pop)

#endif //!__XL_CLIENT_CMD_DATA__