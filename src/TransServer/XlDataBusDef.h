#ifndef __XL_DATA_BUS_DEF__
#define __XL_DATA_BUS_DEF__
#include "XlProtocol.h"
#include "x_ringbuffer.h"

#pragma pack(push)
#pragma pack(1)
struct CXlDataBusInfo
{
/***************************************************************************************/
/************************for client request*********************************************/
	struct XlcCmdLogin
	{
		char userName[16];		///< �˻���
		char passWord[16];  	///< ����
		int  nForced;			///< 1 ǿ�Ƶ�¼��0 ��ǿ�Ƶ�¼
		long version;			///< �ͻ��˰汾
	};

	struct XlcCmdRealAlarm
	{
		char  hostId[32];		///< �豸ID
	};

	struct XlcCmdRealPlay
	{
		char hostId[32];		///< �豸ID
		long long channel;		///< ͨ����
		CRingBuffer *pBuffer;
	};

	struct XlcCmdStartVod
	{
		GUID sessionId;			///< �ػ�ID
		char hostId[32];		///< �豸ID
		long long channel;		///< ͨ����	
		time_t tmStartTime;		///< ��ʼʱ��
		time_t tmEndTime;		///< ����ʱ��
		CRingBuffer *pBuffer;
	};

	struct XlcCmdStopVod
	{
		GUID sessionId;			///< �ػ�ID
		char hostId[32];		///< �豸ID
		long long channel;		///< ͨ����	
		CRingBuffer *pBuffer;
	};

	struct XlcCmdContextInfo
	{
		long lUserID;                             ///< �û�ID 
		int nMessageTitleSize;  				  ///< ��Ϣ���ⳤ��
		unsigned long ulMessageSize;			  ///< ��Ϣ���ݳ���
		int nDevCount;							  ///< �豸����
		char pData[1];
	};

	struct XlcCmdFileInfo
	{
		long lUserID;                         ///< �û�ID 
		int nFileNameSize;  				  ///< �ļ����Ƴ���
		unsigned long ulFileSize;			  ///< �ļ�����
		int nDevCount;						  ///< �豸����
		char pData[1];
	};

	struct XlcCmdTalkCmd
	{
		char account[32];   	///< �˻���
		char equID[32];			///< �豸ID
		int state;

	};

	struct XlcCmdTalkData
	{
		char account[32];	 	///< �˻���
		char equID[32];		///< �豸ID
		unsigned int size;		///< ����������
	};

/***************************************************************************************/
/************************for client response********************************************/
	struct XlcRespMessage
	{
		char szID[32];					///< ����
		unsigned int unMsg;				///< ��Ϣ��
		unsigned long ulDataSize;		///< ��Ϣ���ݳ���
		char data[1];					///< ��Ϣ��
	};

	struct XlcRespLogin
	{
		int code;				///< 0-��¼�ɹ�, 1-��¼ʧ��, 2-�û�������, 3-�������, 4-�û��������û���, 5-�ͻ��˰汾���ͻ����, 6-�û���������λ�ý��е�¼
	};

	struct XlcRespLogout
	{
		unsigned char  code;	///< 0-�ɹ�, 1-ʧ��
	};

	struct XlcRespErrorCode
	{
		unsigned char  code;	///< 0-�ɹ�, 1-ʧ��
	};

	struct XlcRespAlarmInfo
	{
		char szID[32];					///< ����
		time_t tmTimeStamp;				///< ʱ���
		char bAlarm;					///< ��������
		double dLatitude;
		double dLongitude;
		double dGPSSpeed;
	};

	struct XlcRespTransmitMessage
	{
		unsigned long ulMessageID;    	/// ��ϢID
		int state;  					/// ״̬
	};

	struct XlcRespTransmitFile
	{
		unsigned long ulFileID;    		/// �ļ�ID
		int state;  					/// ״̬
	};

	struct XlcRespEquipmentState
	{
		char szID[32];					/// �豸ID
		int  state;						/// 1���ߣ�0����
	};
	
	struct XlcRespTalkCmd
	{
		char account[32];   	///< �˻���
		char equID[32];		///< �豸ID
		int state;

	};

	struct XlcRespTalkData
	{
		char account[32];	 	///< �˻���
		char equID[32];		///< �豸ID
		unsigned int size;		///< ����������
	};

/***************************************************************************************/
/************************for device request*********************************************/
	struct XldCmdConrrectTime
	{
		time_t systime;				///< ??C?I?I3E??a
	};

	struct XldCmdConfigDev
	{
		char szID[32];             	//EeOAID
		char szVehicleID[32];       //3?oA
		ULONG ulPhoneNum;           //?c>?oAAe
		int nTotalChannels;         //I??A,oEu
		int nTypeSize;				//EaInI.AaDI
		int nNameSize;		  		//I??AAu3A3$?E???O!?#!?,o?a
	};

	struct XldCmdRealPlay
	{
		char szID[32];              //3?A?ID
		long long llChnStatus; 		//I??A?aAo??`?  ?i?oO?3O64,oI??A
	};

	struct XldCmdStartVod
	{
		GUID session;				//>O.Asession
		char szID[32];				//3?A?ID 
		long long llChnStatus; 		//I??A?aAo??`?  ?i?oO?3O64,oI??A
		time_t tmStartTime;			//>O.A?aE?E??a
		time_t tmEndTime;			//>O.A?aEoE??a!?Eo>O.A??IOOU??EeOAIa-1
	};

	struct XldCmdStopVod
	{
		GUID session;				//>O.Asession
		char szID[32];				//3?A?ID
		long long llChnStatus; 		//I??A?aAo/1O?O??`?  ?i?oO?3O64,oI??A
	};

	struct XldCmdOnOffInfo
	{
		time_t tmStart;				//?aE?E??a, EoE!?AEuOD?AEOO?tmStartIa-1
		time_t tmEnd;				//?aEoE??a, EoE!?AEuOD?AEOO?tmEndIa-1
	};

	struct XldCmdUpdateVodAck
	{
		unsigned char  code;		///< 0-3E1|, 1-E??U
	};

	struct XldCmdContextInfo
	{
		struct XldContextHeader
		{
			long lUserID;                             ///< OA>?ID 
			long lMessageID;                          ///< ��ϢID 
			int nMessageTitleSize;  				  ///< IuIc?eIa3$?E
			unsigned long ulMessageSize;			  ///< IuIcAUEY3$?E
			char data[1];
		};

		char *pContext;								  ///< IuIcAUEY
		union
		{
			XldContextHeader header;
			char pData[1];
		};
	};

	struct XldCmdFileInfo
	{
		struct XldFileInfoHeader
		{
			long lUserID;                         ///< �û�ID 
			int nFileID;                          ///< �ļ�ID 
			int nFileNameSize;  			      ///< �ļ����Ƴ���
			unsigned long ulFileSize;			  ///< �ļ��ܳ�
			char pData[1];
		};

		char *pFileName;
		union
		{
			XldFileInfoHeader header;
			char pData[1];
		};
	};

	struct XldCmdTalkCmd
	{
		char account[32];   	///< �˻���
		char equID[32];		///< �豸ID
		int state;

	};

	struct XldCmdTalkData
	{
		char account[32];	 	///< �˻���
		char equID[32];		///< �豸ID
		unsigned int size;		///< ����������
	};
/***************************************************************************************/
/************************for device request*********************************************/
	struct XldRespMessage
	{
		char szID[32];					///< ����
		unsigned int unMsg;				///< ��Ϣ��
		unsigned long ulDataSize;		///< ��Ϣ���ݳ���
		char data[1];					///< ��Ϣ��
	};

	struct XldRespHostId
	{
		char hostId[32];				///< ����ID
	};

	struct XldRespCorrectTime
	{
		unsigned char  code;			///< 0-�ɹ�, 1-ʧ��
	};

	struct XldRespHostInfo
	{
		char hostId[32];			///< �豸ID
		char vehicleNum[8];			///< �г���
		char phoneNum[12];			///< �绰����
		char totalChannels;			///< ͨ����Ŀ
		char mediaTypeNum;			///< ý������
		int  chNameSize;			///< ͨ�����Ƴ���
		char data[1];				///< ͨ������
	};

	typedef struct XldRespAlarmInfo
	{
		time_t tmTimeStamp;				///< ʱ���
		char bAlarm;					///< ��������
		double dLatitude;
		double dLongitude;
		double dGPSSpeed;
	};

	struct XldRespRealData
	{
		char hostId[32];				///< �豸ID
		unsigned char channel;			///< ͨ����
		char data[1];
	};

	struct XldRespStopReal
	{
		unsigned char  code;			///< 0-�ɹ�, 1-ʧ��
	};

	struct XldRespVodData
	{
		GUID sessionId;					///< �ػ�ID	
		char hostId[32];				///< �豸ID
		unsigned char channel;			///< ͨ����
		char data[1];
	};

	struct XldRespStopVod
	{
		unsigned char  code;			///< 0-�ɹ�, 1-ʧ��
	};

	struct XldRespConrrectTime
	{
		unsigned char  code;			///< 0-�ɹ�, 1-ʧ��
	};

	struct XldRespOnOffInfo
	{
		time_t tmStart;					/// ��ʼʱ��
		time_t tmEnd;					/// ����ʱ��
	};

	struct XldRespVodInfo
	{
		time_t tmStart;					/// ��ʼʱ��
		time_t tmEnd;					/// ����ʱ��
	};
	struct XldRespSyncVodInfo
	{
		time_t tmFristItem;				/// ��һ������ʱ��
	};

	typedef struct XldRespTalkCmd
	{
		char account[32];   	///< �˻���
		char equID[32];			///< �豸ID
		int state;

	};

	typedef struct XldRespTalkData
	{
		char account[32];	 	///< �˻���
		char equID[32];			///< �豸ID
		unsigned int size;		///< ����������
	};

	CXlProtocol::CmdHeader header;
	union
	{
		/// for client request
		XlcCmdLogin xlcCmdLogin;
		XlcCmdRealAlarm xlcCmdRealAlarm;
		XlcCmdRealPlay xlcCmdRealPlay;
		XlcCmdStartVod xlcCmdStartVod;
		XlcCmdStopVod xlcCmdStopVod;
		XlcCmdContextInfo xlcCmdContextInfo;
		XlcCmdFileInfo xlcCmdFileInfo;
		XlcCmdTalkCmd xlcCmdTalkCmd;
		XlcCmdTalkData xlcCmdTalkData;
		/// for client response
		XlcRespMessage xlcRespMessage;
		XlcRespLogin xlcRespLogin;
		XlcRespLogout xlcRespLogout;
		XlcRespErrorCode xlcRespErrorCode;
		XlcRespAlarmInfo xlcRespAlarmInfo;
		XlcRespTransmitMessage xlcRespTransmitMessage;
		XlcRespTransmitFile xlcRespTransmitFile;
		XlcRespEquipmentState xlcRespEquipmentState;
		XlcRespTalkCmd xlcRespTalkCmd;
		XlcRespTalkData xlcRespTalkData;
		/// for device request
		XldCmdConrrectTime xldCmdConrrectTime;
		XldCmdConfigDev xldCmdConfigDev;
		XldCmdRealPlay xldCmdRealPlay;
		XldCmdStartVod xldCmdStartVod;
		XldCmdStopVod xldCmdStopVod;
		XldCmdOnOffInfo xldCmdOnOffInfo;
		XldCmdUpdateVodAck xldCmdUpdateVodAck;
		XldCmdTalkCmd xldCmdTalkCmd;
		XldCmdTalkData xldCmdTalkData;
		/// for device response
		XldRespMessage xldRespMessage;
		XldRespHostId xldRespHostId;
		XldRespCorrectTime xldRespConrrectTime;
		XldRespHostInfo xldRespHostInfo;
		XldRespAlarmInfo xldRespAlarmInfo;
		XldRespRealData xldRespRealData;
		XldRespStopReal xldRespStopReal;
		XldRespVodData xldRespVodData;
		XldRespStopVod xldRespStopVod;
		XldRespOnOffInfo xldRespOnOffInfo;
		XldRespVodInfo xldRespVodInfo;
		XldRespSyncVodInfo xldRespSyncVodInfo;
		XldRespTalkCmd xldRespTalkCmd;
		XldRespTalkData xldRespTalkData;
		/// for data
		char pData[1];
	};
};
#pragma pack(pop)

typedef std::vector<CXlDataBusInfo::XldCmdContextInfo *> HostContextVec;
typedef std::vector<CXlDataBusInfo::XldCmdFileInfo *> HostFileInfoVec;

#endif //!__XL_DATA_BUS_DEF__