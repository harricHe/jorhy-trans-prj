#ifndef _GPS_DATA_DEF_H_
#define _GPS_DATA_DEF_H_

#define GPS_DEV_ID_LEN						32
#define GPS_MAX_DEV_CHN_NUM					16
#define GPS_MAX_DEV_IO_NUM					8
#define GPS_MAX_TEMP_SENSOR_NUM				4

#define GPSSERVER_TYPE_LOGIN				1
#define GPSSERVER_TYPE_GATEWAY				2
#define GPSSERVER_TYPE_MEDIA				3
#define GPSSERVER_TYPE_USRMGR				4
#define GPSSERVER_TYPE_STORAGE				5
#define GPSSERVER_TYPE_WEB					6
#define GPSSERVER_TYPE_DOWN					7		//���ط�����
#define GPSSERVER_TYPE_MANAGER				99		//���������

#define GPS_FILE_LOCATION_DEVICE			1
#define GPS_FILE_LOCATION_STOSVR			2
//�ͻ���3������������������������ظ���3�Ȳ���
#define GPS_FILE_LOCATION_DOWNSVR			4		//���ط�����¼������


#define GPS_FILE_ATTRIBUTE_JPEG				1
#define GPS_FILE_ATTRIBUTE_RECORD			2

#define GPS_LOGIN_SUC						0		//Login direction server success
#define GPS_LOGIN_FAILED					1		//Login direction server failed
#define	GPS_LOGIN_DISCNT					2		//Login direction server disconnect
#define	GPS_LOGIN_NAME_ERR					3		//Login direction server user name error
#define	GPS_LOGIN_PWD_ERR					4		//Login direction server user pwd error
#define	GPS_LOGIN_FULL_ERR					5		//Login direction server ���û��������û�����
#define	GPS_LOGIN_VER_ERR					6		//Login direction server version error
#define	GPS_LOGIN_USR_CHANGE				7		//Login direction server ���û�������λ�ý��е�¼��
#define GPS_LOGIN_USR_DEL					8		//Login direction server ���û���ɾ����
#define	GPS_LOGIN_EXPIRED					9		//Login direction server use expired
#define	GPS_LOGIN_SERVER_EMPTY				10		//Login direction server �����߲������û���������Ϣ��
#define GPS_LOGIN_PRIVILEGE_CHANGE			11		//�û�Ȩ�޷��ͱ仯
#define	GPS_LOGIN_SVR_CONFIG_CHANGE			12		//������������Ϣ���ͱ仯

#define GPS_LOGIN_TYPE_GPS_CLIENT			1

#define GPS_DEV_DOWN_DEV					0
#define GPS_DEV_DOWN_GROUP					1
#define GPS_DEV_DOWN_FAILED					2
#define GPS_DEV_DOWN_SUC					3

#define GPS_DOWN_CONFIG_DATA				1
#define GPS_DOWN_CONFIG_FAILED				2
#define GPS_DOWN_CONFIG_SUC					3
#define GPS_DOWN_MAP_MARKER					4		//��ͼ�����Ϣ
#define GPS_DOWN_MAP_LINE					5		//��ͼ��·��Ϣ
#define GPS_DOWM_MAP_TAB_INFO				6		//��ͼ�������


//hw 2013/1/19
//���ӷ��������������� 0-ʹ�þ�����IP�� 1-ʹ�ù�����IP
#define GPS_NET_TYPE_LAN		0
#define GPS_NET_TYPE_WAN		1

//�ͻ���������Ϣλ����
//0λ����������
#define GPS_DOWN_CONFIG_SVR_CONFIG			0
//1λ�û�Ȩ��
#define GPS_DOWN_CONFIG_PRIVILEG			1
//2λ��ͼ����
#define GPS_DOWN_CONFIG_MAP_CONFIG			2
//3λ�û���Ϣ
#define GPS_DOWN_CONFIG_USER_INFO			3
//4λ�û�����
#define	GPS_DWON_CONFIG_USER_TYPE			4


/*
//2λ�豸�б�
#define GPS_DOWN_CONFIG_DEVICE				2
//3λ��������
#define GPS_DOWN_CONFIG_ALARM_SHIELD		3
//5λ�ҵĵ�ͼ
#define GPS_DOWN_CONFIG_MY_MAP				5
*/

#define GPS_DOWNLOAD_MSG_FAILED				1
#define GPS_DOWNLOAD_MSG_BEGIN				2
#define GPS_DOWNLOAD_MSG_FINISHED			3
#define GPS_DOWNLOAD_MSG_PROCESS			4

#define GPS_UPLOAD_MSG_FAILED				1
#define GPS_UPLOAD_MSG_FINISHED				2
#define GPS_UPLOAD_MSG_PROCESS				3

const int GPS_CTRL_TYPE_OIL_STOP			= 1;	//�Ͽ���·
const int GPS_CTRL_TYPE_OIL_RESTORE			= 2;	//�ָ���·
const int GPS_CTRL_TYPE_ELEC_STOP			= 3;	//�Ͽ���·
const int GPS_CTRL_TYPE_ELEC_RESTORE		= 4;	//�ָ���·
const int GPS_CTRL_TYPE_REBOOT				= 5;	//�������� 
const int GPS_CTRL_TYPE_RESET				= 6;	//�豸��λ
const int GPS_CTRL_TYPE_MOD_DEV_NUM_OR_GET_STATUS = 7;//�޸��豸�š���ȡ�豸״̬
const int GPS_CTRL_TYPE_3G_REBOOT_IP       =8;     //IP,3G,����

const int GPS_MNGCMD_SEND_SMS				= 1;    //���Ͷ���Ϣ
const int GPS_MNGCMD_SEND_TEXT				= 2;    //����TTS���豸�Ͻ��в��ŷ��͵��ļ�
const int GPS_MNGCMD_SEND_PTZ				= 3;    //PTZ����ָ��
const int GPS_MNGCMD_SEND_CTRL				= 4;    //���Ϳ���ָ�����͡��ϵ��
const int GPS_MNGCMD_READ_STATUS			= 5;    //��ȡ����״̬
const int GPS_MNGCMD_CHANGE_USR_PWD			= 6;    //�޸��û�����
const int GPS_MNGCMD_SET_GPS_INTERVAL		= 7;    //����GPS���ʱ��
const int GPS_MNGCMD_CHECK_CTRL_USR			= 8;	//���Ϳ�������ǰУ���û�
const int GPS_MNGCMD_READ_MOTION_PARAM		= 9;	//��ȡ�ƶ�������
const int GPS_MNGCMD_SET_MOTION_PARAM		= 10;   //�����ƶ�������
const int GPS_MNGCMD_READ_NETFLOW_STATISTICS	= 11;   //��ȡ������Ϣ
const int GPS_MNGCMD_SET_NETFLOW_PARAM			= 12;	//������������
const int GPS_MNGCMD_CLEAR_NETFLOW_STATISTICS	= 13;   //�������ͳ��
const int GPS_MNGCMD_ADJUST_NETFLOW_STATISTICS	= 14;	//��������ͳ��
const int GPS_MNGCMD_SET_USR_ALARMSHIELD	= 15;		//���ñ�������
const int GPS_MNGCMD_ADD_MAP_MARKER			= 16;		//��ӵ�ͼ�����Ϣ
const int GPS_MNGCMD_DEL_MAP_MARKER			= 17;		//ɾ����ͼ�����Ϣ
const int GPS_MNGCMD_SEND_DISPATCH_COMMAND	= 18;		//���͵���ָ����Ϣ
const int GPS_MNGCMD_ADD_MAP_MARKERINFO		= 19;		//��ӵ�ͼ�������
const int GPS_MNGCMD_SET_USER_MAP_CONFIG	= 20;		//�����û���ͼ����
const int GPS_MNGCMD_SET_CONFIG				= 21;		//�����豸����
const int GPS_MNGCMD_GET_CONFIG				= 22;		//��ȡ�豸����

// const int GPS_MNGCMD_SET_VIDEO_CONFIG		= 21;		//�����豸��Ƶ����
// const int GPS_MNGCMD_SET_AUDIO_CONFIG		= 22;		//�����豸��Ƶ����
// const int GPS_MNGCMD_SET_PTZ_CONFIG			= 23;		//�����豸��̨����
// const int GPS_MNGCMD_GET_VIDEO_CONFIG		= 24;		//��ȡ�豸��Ƶ����
// const int GPS_MNGCMD_GET_AUDIO_CONFIG		= 25;		//��ȡ�豸��Ƶ����
// const int GPS_MNGCMD_GET_PTZ_CONFIG			= 26;		//��ȡ�豸��̨����

const int GPS_MAPMARKER_TYPE_POINT			= 1;		//��
const int GPS_MAPMARKER_TYPE_RECTANGLE		= 2;		//����
const int GPS_MAPMARKER_TYPE_POLYGON		= 3;		//�����
const int GPS_MAPMARKER_TYPE_LINE			= 4;		//·��

//�洢·�����壬�洢ʾ��	"E:\\gStorage\\RECORD_FILE\\100001\\2012-07-03\\"
const char GPS_STORAGE_PATH[]				= "gStorage";
const char GPS_RECORD_PATH[]				= "RECORD_FILE";

//0λ-����Χ��
//1λ-����
//2λ-�Զ�����
//3λ-3g����ͳ��
//4λ-�ֻ��ͻ���
//5λ-�㲥
//6λ-���Ĵ洢
//7λ-��Ա��λ
#define GPS_SVR_CONFIG_FENCE			0
#define GPS_SVR_CONFIG_SMS				1
#define GPS_SVR_CONFIG_AUTO_DONW		2
#define GPS_SVR_CONFIG_FLOW				3
#define GPS_SVR_CONFIG_PHONE			4
#define GPS_SVR_CONFIG_PLAYBACK			5
#define GPS_SVR_CONFIG_CENTER_STORAGE	6
#define GPS_SVR_CONFIG_TRACKER			7

//�û����Ͷ���
#define GPS_USER_TYPE_COMMON	0	//��ͨ�û�
#define GPS_USER_TYPE_ADMIN		1	//����Ա
#define GPS_USER_TYPE_TEST		2	//�����û�

#pragma pack(4)

typedef struct _tagGPSDEVDevInfo
{
	int		nID;				//Device Index
	char	szName[32];			//Device Name
	char	szIDNO[32];			//Device id
	int		nType;				//0 :Encoder, 1 :Decoder
	unsigned char ucChanNum;			//Channel Number
	unsigned char ucIoInNum;			//IO ������Ŀ
	unsigned char ucTempSensorNum;	//�¶ȴ�������Ŀ
	unsigned char ucIcon;	//����ͼ��
	char	szChnName[GPS_MAX_DEV_CHN_NUM][16];		
	char	szIoInName[GPS_MAX_DEV_IO_NUM][16];
	char	szTempSensorName[GPS_MAX_TEMP_SENSOR_NUM][16];
	int		nGroup;				//Device Group Index
	int		nOnline;			//Device Online Status
	
	char	szSIMCard[16];		//SIM����
	char	szVehiColor[16];	//������ɫ
	char	szVehiBand[16];		//����Ʒ��
	char	szVehiType[16];		//��������
	char	szVehiUse[16];		//������;
	char	szVehiCampany[16];	//������˾
	char	szDriverName[16];	//˾������
	char	szDriverTele[16];	//˾���绰
	unsigned int uiModule;		//ģ�����
	char    szReserve[60];		//�����ֶ�
}GPSDEVDevInfo_S, *LPGPSDEVDevInfo_S;

typedef struct _tagGPSMDVRInfo
{
	unsigned char ucIoInNum;			//IO ������Ŀ
	unsigned char ucTempSensorNum;	//�¶ȴ�������Ŀ
	unsigned char szRes[2];
	char	szChnName[GPS_MAX_DEV_CHN_NUM][16];		
	char	szIoInName[GPS_MAX_DEV_IO_NUM][16];
	char	szTempSensorName[GPS_MAX_TEMP_SENSOR_NUM][16];
	
	char	szVehiColor[16];	//������ɫ
	char	szVehiBand[16];		//����Ʒ��
	char	szVehiType[16];		//��������
	char	szVehiUse[16];		//������;
	char	szVehiCampany[16];	//������˾
	char	szDriverName[16];	//˾������
	char	szDriverTele[16];	//˾���绰
	char    szReserve[60];		//�����ֶ�
}GPSMDVRInfo_S, *LPGPSMDVRInfo_S;

typedef struct _tagGPSMobileDevInfo
{
	unsigned char nSex;			//�Ա�
	char strIDCar[19];			//���֤18λ
	char strUserNumber[16];		//���15
	char strGroupName[64];		//��������
	char strAddress[256];		//סַ
	int nUserPost;				//ְλ
	int	nEquip;					//һλ��ʾһ��װ��
	char szReserve[64];			//����64�ֶ�
}GPSMobileDevInfo_S, *LPGPSMobileDevInfo_S;

typedef struct _tagGPSDevInfo
{
	int nID;
	char szIDNO[32];				//Device id
	char szName[32];				//Device Name
	char szSIMCard[16];				//�绰
	int nDevType;					//�豸������		MDVR��MOBILE��
	int	nDevSubType;				//�豸������		��ͨGPS��ͨ����Ŀ��Ҫ����Ϊ0��
	int	nGroup;						//Device Group Index
	int nOnline;					//Device Online Status
	unsigned int uiModule;			//ģ�����
	unsigned char ucChanNum;		//Channel Number
	unsigned char ucIcon;			//����ͼ��
	char strRemark[94];				//��ע		//ԭ��Ϊ126
	char cProtocol;					//Э������
	char cAudioCodec;				//��Ƶ���������ͣ�����Խ�ʱ��ʹ�ô˲���
	char cDiskType;					//��������
	char strReserve[29];			//����
	union
	{
		GPSMDVRInfo_S gDVRInfo;
		GPSMobileDevInfo_S gMobileDevInfo;
	};
}GPSDevInfo_S, *LPGPSDevInfo_S;

typedef struct _tagGPSChnName
{
	char szName[16];		// Channel Name
}GPSChnName_S, *LPGPSChnName_S;

typedef GPSChnName_S GPSIOName_S;

typedef struct _tagGPSDEVGroup
{
	int		nID;			//Group Index
	char	szName[32];		//Group Name
	int		nParent;		//Parent Group,  -1 : no Parent
	char	szRemarks[64];	//
}GPSDEVGroup_S, *LPGPSDEVGroup_S;

typedef struct _tagGPSAddrInfo
{
	char szLanIP[64];
	char szDeviceIP[64];
	char szClientIP[64];
	unsigned short usDevicePort;
	unsigned short usClientPort;
	unsigned short usReserve[2];
}GPSAddrInfo_S;

typedef struct _tagGPSServerInfo
{
	int nID;
	char szIDNO[32];
	char szName[32];
	long nGroup;
	GPSAddrInfo_S	Addr;
}GPSServerInfo_S, *LPGPSServerInfo_S;

typedef struct _tagGPSServerAddr
{
	int nSvrID;
	GPSAddrInfo_S Addr;
}GPSServerAddr_S, *LPGPSServerAddr_S;

typedef struct _tagGPSMEDIAFile
{
	char	szFile[256]; 	/*��·�����ļ���*/
	unsigned int uiBegintime;
	unsigned int uiEndtime;
	char	szDevID[GPS_DEV_ID_LEN];			//�豸ID
	int		nChn;
	unsigned int nFileLen;
	int		nFileType;
	int		nLocation;		//λ�ã��豸�ϵ�¼���ļ������Ǵ洢�����ϵ�¼���ļ�
	int		nSvrID;			//�洢������ID����Ϊ�洢�������ϵ��ļ�ʱ��Ч
}GPSMEDIAFile_S, *LPGPSMEDIAFile_S;

typedef struct _tagGPSDEVUpgradeFile
{
	char szVersion[32];
	int	nDevType;
	int nFileLength;
}GPSDEVUpgradeFile_S, *LPGPSDEVUpgradeFile_S;

//���α�������
typedef struct _tagGPSAlarmShield
{
	int		nAlarmType;			//��������		
}GPSAlarmShield_S, *LPGPSAlarmShield_S;

//��ͼ��ǵ�����
typedef struct _tagGPSMarkerInfo
{
	int nID;				//���ݿ�ID����
	int nMarkerID;			//GPSMapMarker_S�ṹ���nID
	unsigned char nType;	//�豸����
	unsigned char nDevNum;	//��Ŀ(��nTypeΪ�����ʱ��nNumΪ���������Ŀ)
	char	szReserve[26];	//����
}GPSMarkerInfo_S, *LPGPSMarkerInfo_S;
//��ͼ���
typedef struct _tagGPSMapMarker
{
	int		nID;
	int		nMarkerType;		//������ͣ���״����(������)
	int		nType;				//��������ͷ������԰��
	int		nCreator;			//�����˱�ǵ��û�
	BOOL	bShare;				//�Ƿ�������������˾�����û������Կ����˱����Ϣ
	char	szName[32];			//�������
	char	szJingDu[256];		//�����ַ���,�ɰ��������������״���;���
	char	szWeiDu[256];		//γ���ַ���,�;����ַ���һһ��Ӧ
	char	szColor[10];		//��ɫ
	char	szRemark[64];		//��ע
	unsigned short	nExtinguisherNum;	//���������
	char	szReserver[30];
}GPSMapMarker_S, *LPGPSMapMarker_S;

typedef struct _tagGPSMapLine
{
	GPSMapMarker_S	Marker;		//����������mapMarker����һ��
	char	szJingDu[110000];	//�������9999���켣�㣨ÿ���켣�����11���ַ�  113.134234��
	char	szWeiDu[110000];	//�������9999���켣��
}GPSMapLine_S, *LPGPSMapLine_S;

//����Χ��
typedef struct _tagGPSMapFence
{
	int		nID;			//Χ�����
	char	szDevIDNO[40];	//�������
	int		nMarkerID;		//��ͼ��Ǳ��
	int		nAccessAlarm;	//�������򱨾���0��������1�����ڱ�����2�����ⱨ����
	int		nSpeedAlarm;	//�ٶȱ�����0��������1�����ڱ�����2�����ⱨ����
	int		nSpeedHigh;		//����ٶȣ���λ����  100 = 10.0���
	int		nSpeedLow;		//����ٶ�
	int		nParkAlarm;		//ͣ��������0��������1�����ڱ�����2�����ⱨ����
	int		nParkTime;		//ͣ��������ʱ�����60�룩��λ��
	int		nDoorAlarm;		//���ű���
	int		nBeginTime;		//��ʼʱ�䡢������ʼʱ��
	int		nEndTime;		//����ʱ�䡢��������ʱ��
}GPSMapFence_S, *LPGPSMapFence_S;

//Χ��
typedef struct _tagGPSMapFenceInfo
{
	GPSMapFence_S mapFence;
	GPSMapMarker_S mapMarker;
}GPSMapFenceInfo_S, *LPGPSMapFenceInfo_S;

//�ͻ��������õ�����Ϣ
typedef struct _tagGPSUPFileInfo
{
	char	szModuleName[32];
	char	szVersion[128];
	char 	szPath[128];
	char	szSHA1[128];
	int		nFileLength;
	char	szReserve[32];	//����
}GPSUPFileInfo_S, *LPGPSUPFileInfo_S;

typedef struct _tagGPSUPVersion
{
	char	szVersion[32];
	char	szDate[32];
	char	szSHA1[128];
	char	szKeyModule[32];
	char	szReserve[32];	//����
}GPSUPVersion_S, *LPGPSUPVersion_S;

//�ͻ��˵�¼ʱ���ӷ������л�ȡ�ͻ���APP��Ϣ
typedef struct _tagGPSAppInfo
{
	int		nAppVersion;				//�ͻ��˰汾	6.1.1.1	=  6 * 1000000 + 1 * 10000 + 1 * 100 + 1	ÿ���汾�����������
	int		nWebPort;					//WEB�������˿�
	char	szHost[128];				//��ַ����  192.168.1.100������˲���Ϊ����ֱ��ʹ���û���������ip
	char	szWebApp[32];				//WEB App��ַ����gpsweb������˲���Ϊ�գ���ʹ��
	char	szVerUrl[128];				//�汾��������		/product/gViewer/upgrade.html
										//˵�����ʵ�ַΪ  http://szHost:nWebPort/szWebApp/szVerUrl	���� http://�û�������ַ:nWebPort/szVerUrl
	char	szReserve[32];				//��������
}GPSAppInfo_S;

//�û���ͼ������Ϣ
typedef struct _tagUserMapConfig
{
	int nMapType;		//��ͼ����
	int	nJingDu;		//����	4�ֽ� ��������	9999999 = 9.999999 
	int nWeiDu;			//γ��	4�ֽ� ��������	9999999 = 9.999999
	int nZoom;			//���ż���
	char szReserve[128];
}UserMapConfig_S, *LPUserMapConfig_S;

//������������Ϣ
typedef struct _tagSvrConfig
{
	unsigned long lSvrConfig;
}SvrConfig_S, *LPSvrConfig_S;

//�û���Ϣ
typedef struct _tagClientUserInfo
{
	char szCompanyLogoFile[MAX_PATH];		//��˾logo�ļ�·��
	SYSTEMTIME timeCompanyLogoUpdate;		//��˾logo����ʱ��
	char szUserLogoFile[MAX_PATH];			//�û�logo�ļ�·��
	SYSTEMTIME timeUserLogoUpdate;			//�û�logo����ʱ��
}ClientUserInfo_S, *LPClientUserInfo_S;


#pragma pack()

#endif