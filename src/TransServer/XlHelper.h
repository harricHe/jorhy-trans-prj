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

class CXlHelper
{
public:
	/// ���ýӿ�
	static j_result_t MakeRequest(j_char_t bCmd, j_char_t bFlag, j_int32_t nSeq, j_char_t *pData, j_int32_t nLen, j_char_t *pBody);
	static j_result_t MakeResponse(j_char_t bCmd, j_char_t bFlag, j_int32_t nSeq, j_char_t *pData, j_int32_t nLen, j_char_t *pBody);
	static j_result_t MakeResponse2(j_char_t bCmd, j_char_t bFlag, j_int32_t nSeq, j_char_t *pData, j_int32_t nLen, j_char_t *pBody);
	static j_uint32_t CheckNum(j_char_t *pData, j_int32_t nLen);
	static j_uint32_t CheckNum2(j_char_t *pData, j_int32_t nLen);
	static j_result_t MakeNetData(J_AsioDataBase *pAsioData, j_char_t *pDataBuff, j_int32_t nLen);
	//static j_result_t BlockSocket();
	static int Unicode2Ansi(LPCWSTR sInput, j_string_t& sOutput);
};
#endif // !__XLHELPER_H_
