#ifndef __JO_DBUS_H_
#define __JO_DBUS_H_
#include "j_includes.h"
#include "x_timer.h"
#include "x_lock.h"

#ifdef WIN32
typedef unsigned (X_JO_API *j_data_event_t)(J_DObj *);
#else
typedef void *(*j_data_event_t)(J_DObj *); 
#endif 

class CDBus
{
	typedef std::map<j_string_t, j_data_event_t> DBusEventMap;
	typedef std::map<J_Obj*, DBusEventMap> ClientMethodMap;
	typedef std::map<j_string_t, DBusEventMap> ServerMethodMap;
	typedef ClientMethodMap ClientSignalMap;

	struct InvokeKey
	{
		InvokeKey(j_string_t strServerID, j_string_t strMethodName)
		{
			serverID = strServerID;
			methodName = strMethodName;
		}
		j_string_t serverID;
		j_string_t methodName;

		j_boolean_t operator < (const InvokeKey &other) const
		{
			if (serverID == other.serverID)
			{
				return methodName < other.methodName;
			}

			return serverID < other.serverID;
		}
	};
	typedef std::vector<j_data_event_t> DBusEventVector;
	typedef std::map<InvokeKey, DBusEventVector> InvokeMethodMap;

public:
	CDBus();
	~CDBus();

public:
	/// �ͻ��˵��ýӿ�
	///@param[in]	pObj �ͻ��˶���
	///@param[in]	strName ��������
	///@param[in]	pCallback �ص�����
	///@return 		��
	void registerMethod(J_Obj *pObj, j_string_t strName, j_data_event_t pCallback);
	///@param[in]	pObj �ͻ��˶���
	///@param[in]	strName �ź�����
	///@param[in]	pCallback �ص�����
	///@return 		��
	void registerSignal(J_Obj *pObj, j_string_t strName, j_data_event_t pCallback);
	///@param[in]	pObj �ͻ��˶���
	///@param[in]	strServerID ����������ID
	///@param[in]	strName ��������
	///@param[in]	pParm ����
	///@return 		��
	void invoke(J_Obj *pObj, j_string_t strServerID, j_string_t strName, J_DObj *pParm) ;

	/// �������˵��ýӿ�
	///@param[in]	serverID ����������ID
	///@param[in]	strName ��������
	///@param[in]	pCallback �ص�����
	///@return 		��
	void registerMethod(j_string_t serverID, j_string_t strName, j_data_event_t pCallback);
	///@param[in]	serverID ����������ID
	///@param[in]	strName ��������
	///@param[in]	pParm ����
	///@return 		��
	void sendResponse(j_string_t serverID, j_string_t strName, J_DObj *pParm);
	///@param[in]	serverID ����������ID
	///@param[in]	strName �ź�����
	///@param[in]	pParm ����
	///@return 		��
	void boradcastSignal(j_string_t serverID, j_string_t strName, J_DObj *pParm);

private:
	ClientMethodMap m_clientMethodMap;
	ClientSignalMap m_clientSignalMap;
	ServerMethodMap m_serverMethodMap;
	InvokeMethodMap m_invokeMethodMap;
};

JO_DECLARE_SINGLETON(DBus)

#endif //~__JO_DBUS_H_