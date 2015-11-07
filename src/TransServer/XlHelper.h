///////////////////////////////////////////////////////////////////////////
/// COPYRIGHT NOTICE
/// Copyright (c) 2009, xx�Ƽ����޹�˾(��Ȩ����) 
/// All rights reserved. 
/// 
/// @file      XlHelper.h 
/// @brief     �����ӿ�
///
/// @version   1.0 (�汾����)
/// @author    Jorhy (joorhy@gmail.com) 
/// @date      2013/11/01 09:02 
/// �޶�˵��������汾
///////////////////////////////////////////////////////////////////////////  
#ifndef __XLHELPER_H_
#define __XLHELPER_H_
#include "j_includes.h"

#define arr_size 32

class CXlHelper
{
public:
	/// ���ýӿ�
	static j_result_t MakeRequest(j_char_t bCmd, j_char_t bFlag, j_int32_t nSeq, j_char_t *pData, j_int32_t nLen, j_char_t *pBody);
	static j_result_t MakeResponse(j_char_t bCmd, j_char_t bFlag, j_int32_t nSeq, j_char_t *pData, j_int32_t nLen, j_char_t *pBody);
	static j_result_t MakeMessage(j_char_t bCmd, j_char_t bFlag, j_int32_t nSeq, j_char_t *pData, j_int32_t nLen, j_char_t *pBody);
	static j_uint32_t CheckNum(j_char_t *pData, j_int32_t nLen);
	static j_uint32_t CheckNum2(j_char_t *pData, j_int32_t nLen);
	static j_result_t MakeNetData(J_AsioDataBase *pAsioData, j_char_t *pDataBuff, j_int32_t nLen);
	//static j_result_t BlockSocket();
	static int Unicode2Ansi(LPCWSTR sInput, j_string_t& sOutput);
	static int Ansi2Unicode(LPCSTR input, j_wstring_t& output);

	// ��ȡʱ���
	static char* GetTimestamp(j_boolean_t isMillisecond);

	// ��ȡϵͳʱ�䵱ǰ��ʱ���
	static void GetTimestamp(j_boolean_t isMillisecond, char outTimeInterval[]);

	// ��֤ʱ����Ƿ���ȷ
	static bool ActionTimestampCheck(long long time, long timezone);

	// �����������ļ����ļ���
	static j_string_t RenameFile(const j_string_t oldFileName);

	// ����GUID
	static const char* CreateNewGuid();

private:
	// ����/ƽ���ж�
	static	int IsLeap(unsigned short year);
};
#endif // !__XLHELPER_H_
