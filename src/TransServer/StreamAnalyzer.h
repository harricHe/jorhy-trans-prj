/*************************************************************************
**                           streamAnalyzer 

**      (c) Copyright 1992-2004, ZheJiang Dahua Technology Stock Co.Ltd.
**                         All Rights Reserved
**
**	File  Name		: StreamAnalyzer.h
**	Description		: streamAnalyzer header
**	Modification	: 2010/07/13	yeym	Create the file
**************************************************************************/
#ifndef __STREAM_ANALYZER_H
#define __STREAM_ANALYZER_H
#define INOUT
#define IN
#define OUT

#ifndef _WIN32
#define __stdcall
#endif

//#include <windows.h>
#include <vector>
#include "platform.h"

#ifdef WIN32
#ifdef STREAMANALYZER_EXPORTS
#define ANALYZER_API __declspec(dllexport)
#else
#define ANALYZER_API __declspec(dllimport)
#endif
#else
#define ANALYZER_API
#endif

#ifndef NOERROR
#define NOERROR	0
#endif

#ifdef __cplusplus
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
// ֡����
typedef enum _ANA_MEDIA_TYPE
{
	FRAME_TYPE_UNKNOWN = 0,			//֡���Ͳ���֪
	FRAME_TYPE_VIDEO,				//֡��������Ƶ֡
	FRAME_TYPE_AUDIO,				//֡��������Ƶ֡
	FRAME_TYPE_DATA					//֡����������֡
}ANA_MEDIA_TYPE;

// ������
typedef enum _FRAME_SUB_TYPE
{
	TYPE_DATA_INVALID = -1,				//������Ч
	TYPE_VIDEO_I_FRAME = 0 ,			// I֡
	TYPE_VIDEO_P_FRAME,				// P֡
	TYPE_VIDEO_B_FRAME,				// B֡
	TYPE_VIDEO_S_FRAME,				// S֡
	TYPE_WATERMARK_TEXT,			//ˮӡ����ΪTEXT����
	TYPE_WATERMARK_JPEG,			//ˮӡ����ΪJPEG����
	TYPE_WATERMARK_BMP,				//ˮӡ����ΪBMP����
	TYPE_DATA_INTL,					//���ܷ���֡
	TYPE_VIDEO_JPEG_FRAME,
	TYPE_DATA_ITS					//its��Ϣ֡
}FRAME_SUB_TYPE;						

// ��������
typedef enum _ENCODE_TYPE
{
	ENCODE_VIDEO_UNKNOWN = 0,		//��Ƶ�����ʽ����֪
	ENCODE_VIDEO_MPEG4 ,			//��Ƶ�����ʽ��MPEG4
	ENCODE_VIDEO_HI_H264,			//��Ƶ�����ʽ�Ǻ�˼H264
	ENCODE_VIDEO_DH_H264,			//��Ƶ�����ʽ�Ǵ�����H264
	ENCODE_VIDEO_JPEG,				//��Ƶ�����ʽ�Ǳ�׼JPEG
	ENCODE_VIDEO_INVALID,			//��Ƶ�����ʽ��Ч

	ENCODE_AUDIO_PCM = 7,			//��Ƶ�����ʽ��PCM8
	ENCODE_AUDIO_G729,				//��Ƶ�����ʽ��G729
	ENCODE_AUDIO_IMA,				//��Ƶ�����ʽ��IMA
	ENCODE_PCM_MULAW,				//��Ƶ�����ʽ��PCM MULAW
	ENCODE_AUDIO_G721,				//��Ƶ�����ʽ��G721
	ENCODE_PCM8_VWIS,				//��Ƶ�����ʽ��PCM8_VWIS
	ENCODE_MS_ADPCM,				//��Ƶ�����ʽ��MS_ADPCM
	ENCODE_AUDIO_G711A,				//��Ƶ�����ʽ��G711A
	ENCODE_AUDIO_AMR,				//��Ƶ�����ʽ��AMR
	ENCODE_AUDIO_PCM16,				//��Ƶ�����ʽ��PCM16
	ENCODE_AUDIO_G711U = 22,		//��Ƶ�����ʽ��G711U
	ENCODE_AUDIO_G723,				//��Ƶ�����ʽ��G723
	ENCODE_AUDIO_AAC = 26,			//��Ƶ�����ʽ��AAC
	ENCODE_AUDIO_TALK = 30,
	ENCODE_VIDEO_H263,
	ENCODE_VIDEO_PACKET
}ENCODE_TYPE;
		
enum
{
	DH_ERROR_NOFIND_HEADER = -20, 	//������Ϣ����,��û��֡ͷ
	DH_ERROR_FILE, 					//�ļ�����ʧ��
	DH_ERROR_MM, 					//�ڴ����ʧ��
	DH_ERROR_NOOBJECT, 				//��������Ӧ�Ķ���
	DH_ERROR_ORDER, 				//�ӿڵ��ô�����ȷ
	DH_ERROR_TIMEOUT, 				//����ʱ
	DH_ERROR_EXPECPT_MODE, 			//�ӿڵ��ò���ȷ
	DH_ERROR_PARAMETER, 			//��������
	DH_ERROR_NOKNOWN, 				//����ԭ��δ��
	DH_ERROR_NOSUPPORT, 			//���ṩʵ��
	DH_ERROR_OVER,
	DH_ERROR_LOCKTIMEOUT,
	DH_NOERROR = NOERROR 			//û�д���
};


typedef enum _STREAM_TYPE
{
	DH_STREAM_UNKNOWN = 0,
	DH_STREAM_MPEG4,		
	DH_STREAM_DHPT =3,
	DH_STREAM_NEW,
	DH_STREAM_HB,
	DH_STREAM_AUDIO,
	DH_STREAM_PS,
	DH_STREAM_DHSTD,
	DH_STREAM_ASF,
	DH_STREAM_DHAV,
	DH_STREAM_3GPP,
	DH_STREAM_RAW,	
	DH_STREAM_TS,
}STREAM_TYPE;

enum
{
	E_STREAM_NOERROR = 0,		//����У������
	E_STREAM_TIMESTAND,			//ʱ�����δʵ��
	E_STREAM_LENGTH,			//������Ϣ����
	E_STREAM_HEAD_VERIFY,		//δʵ��
	E_STREAM_VERIFY,			//����У��ʧ��
	E_STREAM_HEADER,			//����û��֡ͷ
	E_STREAM_NOKNOWN,			//����֪����δʵ��
	E_STREAM_LOSTFRAME,
	E_STREAM_WATERMARK
};

enum
{
	DEINTERLACE_PAIR = 0,
	DEINTERLACE_SINGLE,
	DEINTERLACE_NONE,
};
////////////////////////////////////////////////////////////////////////////////////////////////
#pragma pack(1)

typedef struct _DHTIME								
{
	DWORD second		:6;					//	��	1-60		
	DWORD minute		:6;					//	��	1-60		
	DWORD hour			:5;					//	ʱ	1-24		
	DWORD day			:5;					//	��	1-31		
	DWORD month			:4;					//	��	1-12		
	DWORD year			:6;					//	��	2000-2063	
}DHTIME,*pDHTIME;
// ֡��Ϣ
typedef struct __ANA_FRAME_INFO
{
	ANA_MEDIA_TYPE		nType;				// ֡����
	FRAME_SUB_TYPE	nSubType;			// ������
	STREAM_TYPE		nStreamType;		// ���ݴ��Э�����ͣ�DHAV��
	ENCODE_TYPE		nEncodeType;		// ��������

	uint8*	        pHeader;			// ����֡ͷ������ָ��
	uint32			nLength;			// ����֡ͷ�����ݳ���
	uint8*	        pFrameBody;			// ������ָ��
	uint32			nBodyLength;		// �����ݳ���
	uint32			dwFrameNum;			// ֡��ţ���֡�ж�

	uint32			nDeinterlace;		// �⽻��
	uint8			nFrameRate;			// ֡��
	uint8			nMediaFlag;				// �������ͱ�ǣ�h264������(0����������2����˼����)
	uint16			nWidth;				// �ֱ���
	uint16			nHeight;

	uint16			nSamplesPerSec;		// ������
	uint8			nBitsPerSample;		// λ��
	uint8			nChannels;

	// ʱ������
	uint16			nYear;	
	uint16			nMonth;
	uint16			nDay;
	uint16			nHour;
	uint16			nMinute;
	uint16			nSecond;
	uint32			dwTimeStamp;		// ʱ��� mktime������ֵ
	
	uint32			Reserved[5];
	uint32			bValid;				// ����У�飭����ˮӡ
} ANA_FRAME_INFO;


typedef	struct  __ANA_INDEX_INFO
{
	uint32	filePos;						//�ؼ�֡���ļ��е�ƫ��
	uint32	dwFrameNum;						//�ؼ�֡֡��
	uint32 dwFrameLen;						//�ؼ�֡֡��
	uint32 frameRate;						//֡��
	uint32	frameTime;						//�ؼ�֡ʱ��
}ANA_INDEX_INFO;

//������Ϣ�ṹ
#define  MAX_TRACKPOINT_NUM 10

typedef struct _ANA_IVS_POINT
{
	uint16 		x; 
	uint16 		y; 
	uint16		xSize;
	uint16		ySize;
	//�켣����������Ӿ��ε����ģ�����X��Y��XSize��YSize�������������Ӿ������꣨left��top��right��bottom����
	//RECT=(X-XSize, Y-YSize, X+XSize, Y+YSize)
	
}ANA_IVS_POINT; 

typedef struct _ANA_IVS_OBJ
{
	uint32				obj_id;						// ����id
	uint32				enable;						 // 0 ��ʾɾ������  1��ʾ����켣��Ϣ��Ч
	ANA_IVS_POINT 	track_point[MAX_TRACKPOINT_NUM]; 
	uint32				trackpt_num;				// �����������track_point��Ч����
}ANA_IVS_OBJ;

typedef struct _ANA_IVS_PrePos
{
	uint32				nPresetCount;			//Ԥ�õ���Ϣ��������λ: 1�ֽ�
	uint8*				pPresetPos;				//Ԥ�õ���Ϣָ��
}ANA_IVS_PrePos;
#pragma  pack()


typedef enum  _IVS_METHOD
{
	IVS_track,									//��������֡�����ƶ��켣��Ϣ
	IVS_Preset									//������̨Ԥ�õ���Ϣ
}IVS_METHOD;

enum CHECK_ERROR_LEVEL
{
	CHECK_NO_LEVEL = 0,
	CHECK_PART_LEVEL,
	CHECK_COMPLETE_LEVEL
};



typedef	HANDLE		ANA_HANDLE;
typedef PHANDLE		PANA_HANDLE;

/************************************************************************
 ** �ӿڶ���
 ***********************************************************************/

// ��������������
ANALYZER_API int32	__stdcall ANA_CreateStream(IN DWORD dwSize,OUT PANA_HANDLE pHandle);

// ��������������
ANALYZER_API void	__stdcall ANA_Destroy(IN ANA_HANDLE hHandle);

// ��������������������(�����Ѿ����ͽ�ȥ��Ӧ�Ĵ�С��������ֵ��=dwSize����Ҫ��δ��ͣ�������Ҫ������Ӧ��pBuffer	\
//						��Ϊ�˷�ֹ�����뻺����С�ڿͻ�������dwSize��������ѭ�������߶�����	--YEYM 2010/5/19)
ANALYZER_API int32	__stdcall ANA_InputData(IN ANA_HANDLE hHandle, IN PBYTE pBuffer, IN DWORD dwSize);

// ��������������ȡ֡����(-1��ʧ�ܣ�0���ɹ���1���������ѿ�)
ANALYZER_API int32	__stdcall ANA_GetNextFrame(IN ANA_HANDLE hHandle, OUT ANA_FRAME_INFO* pstFrameInfo);

// ��������������л�������
ANALYZER_API BOOL	__stdcall ANA_ClearBuffer(IN ANA_HANDLE hHandle);

// ��ȡ�����������л���ʣ������
ANALYZER_API int32	__stdcall ANA_GetRemainData(IN ANA_HANDLE hHandle, IN PBYTE pData, INOUT DWORD* pSize);

// ��ȡ������
ANALYZER_API int32	__stdcall ANA_GetLastError(IN ANA_HANDLE hHandle);

ANALYZER_API int32	__stdcall ANA_ParseIvsFrame(IN ANA_FRAME_INFO* pstFrameInfo,INOUT unsigned char* buffer,IN int len,IN IVS_METHOD type);

ANALYZER_API int32	__stdcall ANA_CreateFileIndexEx(IN ANA_HANDLE hHandle,IN struct timeval* tv = NULL,IN int flag = 0);

ANALYZER_API int32	__stdcall ANA_WaitForCreateIndexComplete(IN ANA_HANDLE hHandle);

ANALYZER_API int32	__stdcall ANA_CreateFile(const char* filePath,OUT PANA_HANDLE pHandle);

// ��������������ȡ֡����(-1��ʧ�ܣ�0���ɹ���1���������ѿ�)
ANALYZER_API int32	__stdcall ANA_GetNextAudio(IN ANA_HANDLE hHandle, OUT ANA_FRAME_INFO* pstFrameInfo);

ANALYZER_API int32	__stdcall ANA_ParseFile(IN ANA_HANDLE handle);

ANALYZER_API int32	__stdcall ANA_GetIndexByOffset(IN ANA_HANDLE handle,IN int offset,OUT ANA_INDEX_INFO*);

ANALYZER_API int32	__stdcall ANA_GetMediaFrame(IN ANA_HANDLE hHandle, OUT ANA_FRAME_INFO* pstFrameInfo);

ANALYZER_API int32	__stdcall ANA_Reset(IN ANA_HANDLE hHandle,IN int);

ANALYZER_API int32	__stdcall ANA_EnableError(IN ANA_HANDLE hHandle,IN int nEnableLevel);
#ifdef __cplusplus
}
#endif


#endif // __STREAM_ANALYZER_H



