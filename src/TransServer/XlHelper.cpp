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

j_result_t CXlHelper::MakeResponse2(j_char_t bCmd, j_char_t bFlag, j_int32_t nSeq, j_char_t *pData, j_int32_t nLen, j_char_t *pBody)
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
	pTail->verify = CheckNum2(pBody, sizeof(CXlProtocol::CmdHeader) + nLen);
	pTail->endCode = 0xFE;

	return J_OK;
}

j_uint32_t CXlHelper::CheckNum(j_char_t *pData, j_int32_t nLen)
{
	j_uint32_t nCheckNum = 0xFE;
	for (int i=0; i<nLen; ++i)
	{
		nCheckNum += pData[i];
		//nCheckNum %= 256;
	}

	return (nCheckNum % 256);
}

j_uint32_t CXlHelper::CheckNum2(j_char_t *pData, j_int32_t nLen)
{
	__int64 nCheckNum = 0xFE;
	for (int i=0; i<nLen; ++i)
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
	if(!sInput)	return 0;
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