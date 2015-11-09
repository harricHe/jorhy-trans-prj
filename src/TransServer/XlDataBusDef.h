#ifndef __XL_DATA_BUS_DEF__
#define __XL_DATA_BUS_DEF__
#include "XlProtocol.h"
#include "x_ringbuffer.h"

#pragma pack(push)
#pragma pack(1)

namespace XlClientRequest
{
	struct Login
	{
		char userName[16];		///< �˻���
		char passWord[16];  	///< ����
		int  nForced;			///< 1 ǿ�Ƶ�¼��0 ��ǿ�Ƶ�¼
		long version;			///< �ͻ��˰汾
	};

	struct RealAlarm
	{
		char  hostId[32];		///< �豸ID
	};

	struct RealPlay
	{
		char hostId[32];		///< �豸ID
		long long channel;		///< ͨ����
	};

	struct VodPlay
	{
		GUID sessionId;			///< �ػ�ID
		char hostId[32];		///< �豸ID
		long long channel;		///< ͨ����	
		time_t tmStartTime;		///< ��ʼʱ��
		time_t tmEndTime;		///< ����ʱ��
	};

	struct ContextInfo
	{
		long lUserID;                             ///< �û�ID 
		int nMessageTitleSize;  				  ///< ��Ϣ���ⳤ��
		unsigned long ulMessageSize;			  ///< ��Ϣ���ݳ���
		int nDevCount;							  ///< �豸����
		char pData[1];
	};

	struct FileInfo
	{
		long lUserID;                         ///< �û�ID 
		int nFileNameSize;  				  ///< �ļ����Ƴ���
		unsigned long ulFileSize;			  ///< �ļ�����
		int nDevCount;						  ///< �豸����
		char pData[1];
	};

	struct TalkCmd
	{
		char account[32];   	///< �˻���
		char equID[32];			///< �豸ID
		int state;

	};

	struct TalkData
	{
		char account[32];	 	///< �˻���
		char equID[32];			///< �豸ID
		unsigned int size;		///< ����������
	};
}

namespace XlClientResponse
{
	struct Message
	{
		char szID[32];					///< ����
		unsigned int unMsg;				///< ��Ϣ��
		unsigned long ulDataSize;		///< ��Ϣ���ݳ���
		char data[1];					///< ��Ϣ��
	};

	struct Login
	{
		int code;				///< 0-��¼�ɹ�, 1-��¼ʧ��, 2-�û�������, 3-�������, 4-�û��������û���, 5-�ͻ��˰汾���ͻ����, 6-�û���������λ�ý��е�¼
	};

	struct Logout
	{
		unsigned char  code;	///< 0-�ɹ�, 1-ʧ��
	};

	struct ErrorCode
	{
		unsigned char  code;	///< 0-�ɹ�, 1-ʧ��
	};

	struct VehicleStatus
	{
		char szID[32];					///< ����
		time_t tmTimeStamp;    			///< ʱ���
		long long llStatus;    			///< ����״̬
		double dLatitude;				///< ά��
		double dLongitude;     			///< ����
		double dGPSSpeed;    			///< GPS�ٶ�
		double dDirection;				///< ����ǰ������
	};

	struct AlarmInfo
	{
		char szID[32];					///< ����
		time_t  tmTimeStamp;			///< ʱ���
		int  nKind;    					///< ��������
		int  nType;						///< ��������0:�������  1:��������
	};

	struct TransmitMessage
	{
		unsigned long ulMessageID;    	///< ��ϢID
		int state;  					///< ״̬
	};

	struct TransmitFile
	{
		unsigned long ulFileID;    		///< �ļ�ID
		int state;  					///< ״̬
	};

	struct EquipmentState
	{
		char szID[32];					///< �豸ID
		int  state;						///< 1���ߣ�0����
	};

	struct TalkCmd
	{
		char account[32];   			///< �˻���
		char equID[32];					///< �豸ID
		int state;

	};

	struct TalkData
	{
		char account[32];	 	///< �˻���
		char equID[32];			///< �豸ID
		unsigned int size;		///< ����������
	};
}

namespace XlHostRequest
{
	struct ConrrectTime
	{
		time_t systime;				///< ϵͳʱ��
	};

	struct ConfigDev
	{
		char szID[32];             	///< �豸ID
		char szVehicleID[32];       ///< �г���
		ULONG ulPhoneNum;           ///< �绰����
		int nTotalChannels;         ///< ͨ����Ŀ
		int nTypeSize;				///< ý�����ͳ���
		int nNameSize;		  		///< ͨ�����Ƴ���
	};

	struct VehiclleStatus
	{
		time_t tmTimeStamp;			///< ʱ���
		long long llStatus;    		///< ����״̬
		double dLatitude;			///< γ��
		double dLongitude;			///< ����
		double dGPSSpeed;			///< GPS�ٶ�
		double dDirection;			///< ����ǰ������
	};

	struct AlarmInfo
	{
		time_t  tmTimeStamp;		///< ʱ���
		int  nKind;    				///< ��������
		int  nType;					///< ��������0:�������  1:��������
	};

	struct RealPlay
	{
		char szID[32];              ///< �豸ID
		long long llChnStatus; 		///< ͨ����
	};

	struct StartVod
	{
		GUID session;				///< �ػ�ID
		char szID[32];				///< �豸ID
		long long llChnStatus; 		///< ͨ����
		time_t tmStartTime;			///< ��ʼʱ��
		time_t tmEndTime;			///< ����ʱ��
	};

	struct StopVod
	{
		GUID session;				///< �ػ�ID
		char szID[32];				///< �豸ID
		long long llChnStatus; 		///< ͨ����
	};

	struct OnOffInfo
	{
		time_t tmStart;				///< ��ʼʱ��
		time_t tmEnd;				///< ����ʱ��
	};

	struct UpdateVodAck
	{
		unsigned char  code;		///< 0-ʧ��, 1-�ɹ�
	};

	struct ContextInfo
	{
		struct ContextHeader
		{
			long lUserID;                             ///< �û�ID 
			long lMessageID;                          ///< ��ϢID 
			int nMessageTitleSize;  				  ///< ��Ϣ���ⳤ��
			unsigned long ulMessageSize;			  ///< ��Ϣ�峤��
			char data[1];
		};

		char *pContext;								  ///< ��Ϣ����
		union
		{
			ContextHeader header;
			char pData[1];
		};
	};

	struct FileInfo
	{
		struct FileInfoHeader
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
			FileInfoHeader header;
			char pData[1];
		};
	};

	struct TalkCmd
	{
		char account[32];   	///< �˻���
		char equID[32];			///< �豸ID
		int state;

	};

	struct TalkData
	{
		char account[32];	 	///< �˻���
		char equID[32];			///< �豸ID
		unsigned int size;		///< ����������
	};
}

namespace XlHostResponse
{
	struct Message
	{
		struct TransFile
		{
			long lFileID;
			int nState;   		///< 0 �����ɹ� 
			time_t tmTime;		///< �������ʱ��ʱ��
		};

		struct TransMessage
		{
			long lMessageID;
			int nState;			///< 0 ��Ϣ�Ѷ� 
			time_t tmTime;		///< ��Ϣ�Ѷ�ʱ��ʱ��
		};

		struct CamaraStatus
		{
			int nStatusSize;	///< ����ͷ״̬
			time_t tmTime;		///< ���ʱ��
		};

		struct TransMessageReceive
		{
			long lUserID;		///< �û�ID
			int nTitleSize;		///< ��Ϣ����
			int nContentSize;	///< ��Ϣ����
		};

		char szID[32];					///< ����
		unsigned int unMsg;				///< ��Ϣ��
		unsigned long ulDataSize;		///< ��Ϣ���ݳ���
		union
		{
			TransFile transFile;
			TransMessage transMassge;
			CamaraStatus camaraStatus;
			TransMessageReceive transMessageReceive;
			char data[1];					///< ��Ϣ��
		};
	};

	struct HostId
	{
		char hostId[32];				///< ����ID
	};

	struct CorrectTime
	{
		unsigned char  code;			///< 0-�ɹ�, 1-ʧ��
	};

	struct VehicleStatus
	{
		unsigned char  code;			///< 0-�ɹ�, 1-ʧ��
	};

	struct AlarmInfo
	{
		unsigned char  code;			///< 0-�ɹ�, 1-ʧ��
	};

	struct HostInfo
	{
		char hostId[32];			///< �豸ID
		char vehicleNum[8];			///< �г���
		char phoneNum[12];			///< �绰����
		char totalChannels;			///< ͨ����Ŀ
		char mediaTypeNum;			///< ý������
		int  chNameSize;			///< ͨ�����Ƴ���
		char data[1];				///< ͨ������
	};

	struct RealData
	{
		char hostId[32];				///< �豸ID
		unsigned char channel;			///< ͨ����
		char data[1];
	};

	struct StopReal
	{
		unsigned char  code;			///< 0-�ɹ�, 1-ʧ��
	};

	struct VodData
	{
		GUID sessionId;					///< �ػ�ID	
		char hostId[32];				///< �豸ID
		unsigned char channel;			///< ͨ����
		char data[1];
	};

	struct StopVod
	{
		unsigned char  code;			///< 0-�ɹ�, 1-ʧ��
	};

	struct ConrrectTime
	{
		unsigned char  code;			///< 0-�ɹ�, 1-ʧ��
	};

	struct OnOffInfo
	{
		time_t tmStart;					/// ��ʼʱ��
		time_t tmEnd;					/// ����ʱ��
	};

	struct VodInfo
	{
		time_t tmStart;					/// ��ʼʱ��
		time_t tmEnd;					/// ����ʱ��
	};
	struct SyncVodInfo
	{
		time_t tmFristItem;				/// ��һ������ʱ��
	};

	struct TalkCmd
	{
		char account[32];   	///< �˻���
		char equID[32];			///< �豸ID
		int state;

	};

	struct TalkData
	{
		char account[32];	 	///< �˻���
		char equID[32];			///< �豸ID
		unsigned int size;		///< ����������
	};
}

struct CXlDataBusInfo
{

	CXlProtocol::CmdHeader header;
	union
	{
		union {
			XlClientRequest::Login login;
			XlClientRequest::RealAlarm realAlarm;
			XlClientRequest::RealPlay realPlay;
			XlClientRequest::VodPlay vodPlay;
			XlClientRequest::ContextInfo contextInfo;
			XlClientRequest::FileInfo fileInfo;
			XlClientRequest::TalkCmd talkCmd;
			XlClientRequest::TalkData talkData;
		} clientRequest;

		union {
			XlClientResponse::Message message;
			XlClientResponse::Login login;
			XlClientResponse::Logout logout;
			XlClientResponse::ErrorCode errorCode;
			XlClientResponse::VehicleStatus vehicleStatus;
			XlClientResponse::AlarmInfo alarmInfo;
			XlClientResponse::TransmitMessage transmitMessage;
			XlClientResponse::TransmitFile transmitFile;
			XlClientResponse::EquipmentState equipmentState;
			XlClientResponse::TalkCmd talkCmd;
			XlClientResponse::TalkData talkData;
		} clientResponse;

		union {
			XlHostRequest::ConrrectTime conrrectTime;
			XlHostRequest::ConfigDev configDev;
			XlHostRequest::VehiclleStatus vehicleStatus;
			XlHostRequest::AlarmInfo alarmInfo;
			XlHostRequest::RealPlay realPlay;
			XlHostRequest::StartVod startVod;
			XlHostRequest::StopVod stopVod;
			XlHostRequest::OnOffInfo onOffInfo;
			XlHostRequest::UpdateVodAck updateVodAck;
			XlHostRequest::TalkCmd talkCmd;
			XlHostRequest::TalkData talkData;
		} hostRequest;

		union {
			XlHostResponse::Message message;
			XlHostResponse::HostId hostId;
			XlHostResponse::ConrrectTime conrrectTime;
			XlHostResponse::AlarmInfo alarmInfo;
			XlHostResponse::HostInfo hostInfo;
			XlHostResponse::RealData realData;
			XlHostResponse::StopReal stopReal;
			XlHostResponse::VodData vodData;
			XlHostResponse::StopVod stopVod;
			XlHostResponse::OnOffInfo onOffInfo;
			XlHostResponse::VodInfo vodInfo;
			XlHostResponse::SyncVodInfo syncVodInfo;
			XlHostResponse::TalkCmd talkCmd;
			XlHostResponse::TalkData talkData;
		} hostResponse;
		char pData[1];
	};
};
#pragma pack(pop)

typedef std::vector<XlHostRequest::ContextInfo *> HostContextVec;
typedef std::vector<XlHostRequest::FileInfo *> HostFileInfoVec;

#endif //!__XL_DATA_BUS_DEF__