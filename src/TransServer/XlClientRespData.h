#ifndef __XL_CLIENT_RESP_DATA__
#define __XL_CLIENT_RESP_DATA__
#include "XlProtocol.h"

#pragma pack(push)
#pragma pack(1)
struct CXlClientRespData
{
	struct RespMessage
	{
		char szID[32];					///< ����
		unsigned int unMsg;				///< ��Ϣ��
		unsigned long ulDataSize;		///< ��Ϣ���ݳ���
		char data[1];					///< ��Ϣ��
	};

	struct RespLogin
	{
		int code;				///< 0-��¼�ɹ�, 1-��¼ʧ��, 2-�û�������, 3-�������, 4-�û��������û���, 5-�ͻ��˰汾���ͻ����, 6-�û���������λ�ý��е�¼
	};

	struct RespLogout
	{
		unsigned char  code;	///< 0-�ɹ�, 1-ʧ��
	};

	struct RespErrorCode
	{
		unsigned char  code;	///< 0-�ɹ�, 1-ʧ��
	};

	typedef struct RespAlarmInfo
	{
		char szID[32];					///< ����
		time_t tmTimeStamp;				///< ʱ���
		char bAlarm;					///< ��������
		double dLatitude;
		double dLongitude;
		double dGPSSpeed;
	};

	struct RespTransmitMessage
	{
		unsigned long ulMessageID;    	/// ��ϢID
		int state;  					/// ״̬
	};

	struct RespTransmitFile
	{
		unsigned long ulFileID;    		/// �ļ�ID
		int state;  					/// ״̬
	};

	struct RespEquipmentState
	{
		char szID[32];					/// �豸ID
		int  state;						/// 1���ߣ�0����
	};
	CXlProtocol::CmdHeader respHeader;
	union
	{
		RespMessage respMessage;
		RespLogin respLogin;
		RespLogout respLogout;
		RespErrorCode respErrorCode;
		RespAlarmInfo respAlarmInfo;
		RespTransmitMessage respTransmitMessage;
		RespTransmitFile respTransmitFile;
		RespEquipmentState respEquipmentState;
		char pData[1];
	};
};
#pragma pack(pop)

#endif //!__XL_CLIENT_RESP_DATA__