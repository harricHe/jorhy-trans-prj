///////////////////////////////////////////////////////////////////////////
/// COPYRIGHT NOTICE
/// Copyright (c) 2009, xx�Ƽ����޹�˾(��Ȩ����) 
/// All rights reserved. 
/// 
/// @file      XlHelper.cpp 
/// @brief     �����ӿ�ʵ��
///
/// @version   1.0 (�汾����)
/// @author    Jorhy (joorhy@gmail.com) 
/// @date      2013/11/01 09:03 
/// �޶�˵��������汾
///////////////////////////////////////////////////////////////////////////  
#include "XlHelper.h"
#include "XlProtocol.h"
#include <iostream>
#include <sstream>
using namespace std;

const DWORD SIZE_BUFF = 1024;

j_result_t CXlHelper::MakeRequest(j_char_t bCmd, j_char_t bFlag, j_int32_t nSeq, j_char_t *pData, j_int32_t nLen, j_char_t *pBody)
{
	//���ͷ��Ϣ
	CXlProtocol::CmdHeader *pHeader = (CXlProtocol::CmdHeader *)pBody;
	pHeader->beginCode = 0xFF;
	pHeader->version = CXlProtocol::xl_frame_request;
	pHeader->seq = nSeq;
	pHeader->flag = bFlag;
	pHeader->cmd = bCmd;
	pHeader->length = nLen;
	//���������
	if (nLen > 0)
		memcpy(pBody + sizeof(CXlProtocol::CmdHeader), pData, nLen);
	//���β��Ϣ
	CXlProtocol::CmdTail *pTail = (CXlProtocol::CmdTail *)(pBody + sizeof(CXlProtocol::CmdHeader) + nLen);
	pTail->verify = CheckNum(pBody, sizeof(CXlProtocol::CmdHeader) + nLen);
	pTail->endCode = 0xFE;

	return J_OK;
}

j_result_t CXlHelper::MakeResponse(j_char_t bCmd, j_char_t bFlag, j_int32_t nSeq, j_char_t *pData, j_int32_t nLen, j_char_t *pBody)
{
	//���ͷ��Ϣ
	CXlProtocol::CmdHeader *pHeader = (CXlProtocol::CmdHeader *)pBody;
	pHeader->beginCode = 0xFF;
	pHeader->version = CXlProtocol::xl_framer_response;
	pHeader->seq = nSeq;
	pHeader->flag = bFlag;
	pHeader->cmd = bCmd;
	pHeader->length = nLen;
	//���������
	if (nLen > 0)
		memcpy(pBody + sizeof(CXlProtocol::CmdHeader), pData, nLen);
	//���β��Ϣ
	CXlProtocol::CmdTail *pTail = (CXlProtocol::CmdTail *)(pBody + sizeof(CXlProtocol::CmdHeader) + nLen);
	pTail->verify = CheckNum(pBody, sizeof(CXlProtocol::CmdHeader) + nLen);
	pTail->endCode = 0xFE;

	return J_OK;
}

j_result_t CXlHelper::MakeMessage(j_char_t bCmd, j_char_t bFlag, j_int32_t nSeq, j_char_t *pData, j_int32_t nLen, j_char_t *pBody)
{
	//���ͷ��Ϣ
	CXlProtocol::CmdHeader *pHeader = (CXlProtocol::CmdHeader *)pBody;
	pHeader->beginCode = 0xFF;
	pHeader->version = CXlProtocol::xl_frame_message;
	pHeader->seq = nSeq;
	pHeader->flag = bFlag;
	pHeader->cmd = bCmd;
	pHeader->length = nLen;
	//���������
	if (nLen > 0)
		memcpy(pBody + sizeof(CXlProtocol::CmdHeader), pData, nLen);
	//���β��Ϣ
	CXlProtocol::CmdTail *pTail = (CXlProtocol::CmdTail *)(pBody + sizeof(CXlProtocol::CmdHeader) + nLen);
	pTail->verify = CheckNum(pBody, sizeof(CXlProtocol::CmdHeader) + nLen);
	pTail->endCode = 0xFE;

	return J_OK;
}

j_uint32_t CXlHelper::CheckNum(j_char_t *pData, j_int32_t nLen)
{
	j_uint32_t nCheckNum = 0xFE;
	for (int i = 0; i < nLen; ++i)
	{
		nCheckNum += pData[i];
		//nCheckNum %= 256;
	}

	return (nCheckNum % 256);
}

j_uint32_t CXlHelper::CheckNum2(j_char_t *pData, j_int32_t nLen)
{
	__int64 nCheckNum = 0xFE;
	for (int i = 0; i < nLen; ++i)
	{
		nCheckNum += pData[i];
		//nCheckNum %= 256;
	}

	return (nCheckNum % 256);
}

j_result_t CXlHelper::MakeNetData(J_AsioDataBase *pAsioData, j_char_t *pDataBuff, j_int32_t nLen)
{
	if (pAsioData->ioCall == J_AsioDataBase::j_read_e)
	{
		pAsioData->ioRead.buf = pDataBuff;
		pAsioData->ioRead.bufLen = nLen;
		pAsioData->ioRead.finishedLen = 0;
		pAsioData->ioRead.whole = true;
		pAsioData->ioRead.shared = true;
	}
	else if (pAsioData->ioCall == J_AsioDataBase::j_write_e)
	{
		pAsioData->ioWrite.buf = pDataBuff;
		pAsioData->ioWrite.bufLen = nLen;
		pAsioData->ioWrite.finishedLen = 0;
		pAsioData->ioWrite.whole = true;
		pAsioData->ioWrite.shared = true;
	}
	return J_OK;
}

int	CXlHelper::Unicode2Ansi(LPCWSTR sInput, j_string_t& sOutput)
{
	if (!sInput)	return 0;
	int nnn = wcslen(sInput);
	int len = WideCharToMultiByte(CP_ACP, 0, sInput, wcslen(sInput), NULL, 0, NULL, NULL);

	char *ansiBuffer = new char[len + 1];
	if (len == WideCharToMultiByte(CP_ACP, 0, sInput, wcslen(sInput), ansiBuffer, len, NULL, NULL))
	{
		ansiBuffer[len] = '\0';
		sOutput = ansiBuffer;
		delete[] ansiBuffer;

		return len;
	}
	delete[] ansiBuffer;

	return 0;
}
int CXlHelper::Ansi2Unicode(LPCSTR input, j_wstring_t& output)
{
	if (!input) return 0;

	int wideLen = MultiByteToWideChar(CP_ACP, 0, input, strlen(input), NULL, 0);

	WCHAR *unicodeBuffer = new WCHAR[wideLen + 1];
	if (wideLen == MultiByteToWideChar(CP_ACP, 0, input, strlen(input), unicodeBuffer, wideLen))
	{
		unicodeBuffer[wideLen] = L'\0';
		output = unicodeBuffer;
		delete[] unicodeBuffer;

		return wideLen;
	}
	delete[] unicodeBuffer;

	return 0;
}


/***********************************************************************************************************
 * ���򴴽����Խ���                     �����޸�:�Խ���
 * �������ܣ���ȡ��ǰʱ���ʱ���
 * ����˵����
 *   isMillisecond:true ��ʾ13λ�ĺ��뼶�����ݣ�False ��ʾ10λ���뼶����
 * ע�����null
 * �޸����ڣ�2015/10/15 15:53:00
 ***********************************************************************************************************/
char* CXlHelper::GetTimestamp(j_boolean_t isMillisecond)
{
	time_t t = time(NULL);																						//��ȡϵͳʱ��
	char timeInterval[32] = { 0 };
	if (isMillisecond)
		sprintf_s(timeInterval, sizeof(timeInterval), "%ld000", t);
	else
		sprintf_s(timeInterval, sizeof(timeInterval), "%ld", t);
	return timeInterval;
}


/***********************************************************************************************************
* ���򴴽����Խ���                     �����޸�:�Խ���
* �������ܣ���ȡ��ǰʱ���ʱ���
* ����˵����
*   isMillisecond:true ��ʾ13λ�ĺ��뼶�����ݣ�False ��ʾ10λ���뼶����
* outTimeInterval���û�ȡ�õ�ǰ�����ʱ�������������鳤�ȱ�����32
* ע�����outTimeInterval �����鳤�ȱ�����32
* �޸����ڣ�2015/10/15 16:53:00
***********************************************************************************************************/
void CXlHelper::GetTimestamp(j_boolean_t isMillisecond, char outTimeInterval[])
{
	time_t t = time(NULL);																						//��ȡϵͳʱ��
	char timeInterval[arr_size] = { 0 };
	if (isMillisecond)
		sprintf_s(timeInterval, sizeof(timeInterval), "%ld000", t);
	else
		sprintf_s(timeInterval, sizeof(timeInterval), "%ld", t);
	strncpy(outTimeInterval, timeInterval, sizeof(timeInterval) - 1);
}


/***********************************************************************************************************
 * ���򴴽����Խ���                     �����޸�:�Խ���
 * �������ܣ������������ļ����ļ���
 * ����˵����
 * oldFileName��ԭ�ļ���
 * ע�����null
 * �޸����ڣ�2015\10\16 15:13:00
 ***********************************************************************************************************/
j_string_t CXlHelper::RenameFile(const j_string_t oldFileName)
{
	char timeInterval[arr_size] = { 0 };
	GetTimestamp(true, timeInterval);																				// ��ȡ��ǰϵͳ��ʱ���

	char fileName[128] = { 0 };
	strcpy(fileName, oldFileName.c_str());
	char *ext = strrchr(fileName, '.');

	if (ext)
	{
		*ext = '\0';
		ext++;
	}

	j_string_t loc_str;																								// ������װ�µ��ļ���
	loc_str = fileName;
	j_string_t newFileName;

	newFileName.append(loc_str);																					// �ļ���
	loc_str = timeInterval;																							// ʱ���
	newFileName.append(loc_str);
	newFileName.append(".");																						// .
	loc_str = ext;																									// ��չ��
	newFileName.append(loc_str);
	return newFileName;
}


/***********************************************************************************************************
* �������ߣ��Խ���
* �������ܣ���鵱�������껹��ƽ��
* ����˵����
*     year����Ҫ�������
* ע�����null
* �޸����ڣ�2015/10/08 17:58:00
***********************************************************************************************************/
int CXlHelper::IsLeap(unsigned short year)
{
	return ((year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0));
}

/***********************************************************************************************************
* �������ߣ��Խ���
* �������ܣ����ʱ���ת����ʱ���ʽ�Ƿ�����
* ����˵����
*     time��ʱ���
* timezone��Ĭ��Ϊ8����ʱ�����޸�
* ע�����null
* �޸����ڣ�2015/10/08 18:01:00
***********************************************************************************************************/
bool CXlHelper::ActionTimestampCheck(long long time, long timezone)
{
	ostringstream os;																								// ��long ���͵�ʱ���ת�����ַ������͵�ʱ���
	os << time;
	string result;
	istringstream is(os.str());
	is >> result;

	bool isMilsecond = false;																						// ��ǵ�ǰ�����ʱ����Ǻ��뼶
	int timeLen = result.size();
	switch (timeLen)
	{
	case 13:
		isMilsecond = true;
		break;
	case 10:
		isMilsecond = false;
		break;
	default:
		return false;
		break;
	}

	const int monthLengths[2][13] =																					// ����ÿ���������ۼ�
	{
		{ 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 },
		{ 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 }
	};
	const int yearLengths[2] = { 365, 366 };																		// ����ƽ�ꡢ���������
	int year(0), month(0), minMonth(0), maxMonth(0), days(0), clock(0), isLeap(0), day(0), hour(0), minute(0), second(0);
	if (isMilsecond)
		time /= 1000;																							    // �Ѻ���ת������
	time += timezone * 60 * 60;
	days = time / 86400;																							// ����
	clock = time % 86400;																							// Сʱ��

	if (clock < 0)
	{
		clock += 86400;
		days -= 1;
	}

	if (days >= 0)
	{
		year = days / 366;
		days -= year * 365 + (year + 1) / 4 - (year + 69) / 100 + (year + 369) / 400;
		for (year = year + 1970;; year++)
		{
			isLeap = IsLeap(year);
			if (days < yearLengths[isLeap])
			{
				break;
			}
			days -= yearLengths[isLeap];
		}
	}
	else
	{
		year = days / 366;
		days -= year * 365 + (year - 2) / 4 - (year - 30) / 100 + (year - 30) / 400;
		for (year = year + 1970 - 1;; year--)
		{
			isLeap = false;
			days += yearLengths[isLeap];
			if (days >= 0)
			{
				break;
			}
		}
	}

	minMonth = 0;
	maxMonth = 12;
	for (month = 5; month < 12 && month>0; month = (minMonth + maxMonth) / 2)
	{
		if (days < monthLengths[isLeap][month])
		{
			maxMonth = month;
		}
		else if (days >= monthLengths[isLeap][month + 1])
		{
			minMonth = month;
		}
		else
		{
			break;
		}
	}
	days -= monthLengths[isLeap][month];
	month++;
	day = days + 1;

	hour = clock / 3600;																							// ��ȡ��ǰʱ�����Сʱ����
	clock = clock % 3600;
	minute = clock / 60;																							// ��ȡ��ǰʱ����ķ��Ӳ���
	second = clock % 60;																							// ��ȡ��ǰʱ��������Ӳ���

	if (year < 1970 && year>2099)																					// ��鵱ǰʱ������겿���Ƿ�Ϸ�
		return false;

	if (month < 1 && month>12)																						// ��鵱ǰʱ������²����Ƿ�Ϸ�
		return false;

	if (day < 1 && day>31)																							// ��鵱ǰʱ������첿���Ƿ�Ϸ�
		return false;

	if (hour < 1 && hour>24)																						// ��鵱ǰʱ�����Сʱ�����Ƿ�Ϸ�
		return false;

	if (minute < 1 && minute>60)																					// ��鵱ǰʱ����ķ��Ӳ����Ƿ�Ϸ�
		return false;

	if (second < 1 && second>60)																					// ��鵱ǰʱ��������Ӳ����Ƿ�Ϸ�
		return false;
	return true;
}


int	CXlHelper::Ansi2UTF8(LPCSTR sInput, j_string_t &sOutput)
{
	int	 _utf8Size = SIZE_BUFF;
	CHAR *_utf8Buff = new CHAR[SIZE_BUFF];
	j_wstring_t tmpUnicode;

	if (Ansi2Unicode(sInput, tmpUnicode) <= 0)
		return 0;

	LPCWSTR wInput(tmpUnicode.c_str());
	int u8Len = WideCharToMultiByte(CP_UTF8, 0, wInput, wcslen(wInput), NULL, 0, NULL, NULL);

	if (u8Len + 1 > _utf8Size)
	{
		if (_utf8Buff != NULL)
			delete[] _utf8Buff;
		_utf8Size = u8Len + 1;
		_utf8Buff = new CHAR[_utf8Size];
	}

	if (u8Len == WideCharToMultiByte(CP_UTF8, 0, wInput, wcslen(wInput), _utf8Buff, u8Len, NULL, NULL))
	{
		_utf8Buff[u8Len] = '\0';
		sOutput = _utf8Buff;
		return u8Len;
	}

	return 0;
}



//ascii ת Utf8
j_string_t CXlHelper::ASCII2UTF_8(j_string_t &strAsciiCode)
{
	j_string_t strRet("");
	//�Ȱ� ascii תΪ unicode
	j_wstring_t wstr = Acsi2WideByte(strAsciiCode);
	//���� unicode תΪ utf8
	strRet = Unicode2Utf8(wstr);
	return strRet;
}



//ascii ת Unicode
j_wstring_t CXlHelper::Acsi2WideByte(j_string_t &strascii)
{
	int widesize = MultiByteToWideChar(CP_ACP, 0, (char*)strascii.c_str(), -1, NULL, 0);
	if (widesize == ERROR_NO_UNICODE_TRANSLATION)
	{
		throw std::exception("Invalid UTF-8 sequence.");
	}
	if (widesize == 0)
	{
		throw std::exception("Error in conversion.");
	}
	std::vector<wchar_t> resultstring(widesize);
	int convresult = MultiByteToWideChar(CP_ACP, 0, (char*)strascii.c_str(), -1, &resultstring[0], widesize);


	if (convresult != widesize)
	{
		throw std::exception("La falla!");
	}

	return j_wstring_t(&resultstring[0]);
}


//Unicode ת Utf8
j_string_t CXlHelper::Unicode2Utf8(const j_wstring_t &widestring)
{
	int utf8size = ::WideCharToMultiByte(CP_UTF8, 0, widestring.c_str(), -1, NULL, 0, NULL, NULL);
	if (utf8size == 0)
	{
		throw std::exception("Error in conversion.");
	}

	std::vector<char> resultstring(utf8size);

	int convresult = ::WideCharToMultiByte(CP_UTF8, 0, widestring.c_str(), -1, &resultstring[0], utf8size, NULL, NULL);

	if (convresult != utf8size)
	{
		throw std::exception("La falla!");
	}

	return j_string_t(&resultstring[0]);
}

//wstring ת string ��������
j_string_t CXlHelper::WstrToStr(const j_wstring_t& ws)
{
	j_string_t curLocale = setlocale(LC_ALL, NULL);        // curLocale = "C";
	setlocale(LC_ALL, "chs");
	const wchar_t* _Source = ws.c_str();
	size_t _Dsize = 2 * ws.size() + 1;
	char *_Dest = new char[_Dsize];
	memset(_Dest, 0, _Dsize);
	wcstombs(_Dest, _Source, _Dsize);
	j_string_t result = _Dest;
	delete[]_Dest;
	setlocale(LC_ALL, curLocale.c_str());
	return result;
}