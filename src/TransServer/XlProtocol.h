#ifndef __XL_PROTOCOL_H__
#define __XL_PROTOCOL_H__
#include "windows.h"

#pragma pack(push)
#pragma pack(1)
struct CXlProtocol
{
	enum FrameType
	{
		xl_frame_message = 0,
        xl_frame_request = 1,
        xl_framer_response = 2
	};
	/// ý����������
	enum ControlType
	{
		xl_ctrl_data = 0,
        xl_ctrl_start = 1,
        xl_ctrl_stream = 2,
        xl_ctrl_end = 3,
        xl_ctrl_stop = 4
	};

	/// ����״̬
	enum CmdState
	{
		xl_init_state = 0,
		xl_read_head_state,
		xl_read_data_state,
		xl_write_body_state,
		xl_error_state,
	};

	/// ��ʶ�붨��
	enum FlagType
	{
		xl_pack_start = 0x00,
		xl_pack_continue = 0x01,
		xl_pack_end = 0x02,
	};


	/// ��Ϣ����
	enum MessageType
	{
		xld_copyed_file = 0x01,				///< �ѿ����ļ�
		xld_readed_file = 0x02,				///< �Ѷ���Ϣ
		xld_camera_status = 0x03,			///< ����ͷ״̬

		xlc_msg_force_offline = 0x01,		///< �û���ǿ������
		xlc_msg_user_deleted = 0x02,		///< �û���ɾ��
		xlc_copyed_file = 0x03,				///< �ѿ����ļ�
		xlc_readed_file = 0x04,				///< �Ѷ���Ϣ
		xlc_camera_status = 0x05,			///< ����ͷ״̬
		xlc_dev_info_changed = 0x06,		///< �豸��Ϣ�����仯

		xlc_dev_state = 0xA0,				///< �豸״̬
	};

	/// �Խ�״̬
	enum AudioState
    {
        xla_busy,
        xla_acccept,
        xla_refuse,
        xla_end,
        xla_request,
        xla_offline,
        xla_timeout
	};

	/// ����ָ���  
	enum CmdType
	{
		//�첽��Ϣ���쳣����
		xld_message = 0x00,					///< �첽��Ϣ���쳣����
		//��������
		xld_register = 0x01,				///< ����ע��
		xld_conrrent_time = 0x02,			///< �����豸Уʱ
		xld_heartbeat = 0x03,				///< �������
		//�豸��Ϣ
		xld_get_dvr_info = 0x04,			///< �豸��Ϣ��ȡ
		xld_set_dvr_info = 0x05,			///< �����豸��Ϣ
		xld_server_ready = 0x06,			///< �����豸��Ϣ
		//ʵʱ��Ƶ
		xld_start_real_play = 0x10,			///< ��ʼʵʱ��Ƶ����
		xld_stop_real_play = 0x10,			///< ֹͣʵʱ��Ƶ����
		xld_start_real_view = 0x12,			///< ��ʼʵʱ��ƵԤ��
		xld_stop_real_view = 0x12,			///< ֹͣʵʱ��ƵԤ��
		//Զ�̻ط�&��Ƶ����
		xld_start_vod_play = 0x14,			///< ��ʼ¼��ط�
		xld_stop_vod_play = 0x14,			///< ֹͣ¼��ط�
		xld_start_vod_download = 0x15,		///< ��ʼ¼������
		xld_stop_vod_download = 0x16,		///< ֹͣ¼������
		//�������ݼ�¼
		xld_alarm_info = 0x21,				///< ʵʱ��������
		xld_get_on_off_log = 0x22,			///< ���ػ���־
		xld_first_vod_timestamp = 0x23,		///< ����/��ȡ��һ����Ƶ�ļ��Ŀ�ʼʱ��
		xld_update_vod_info = 0x24,			///< ����¼����Ϣ
		//�������ݴ���
		xld_upload_file = 0x30,				///< �ļ�����
		xld_trans_context = 0x31,			///< �ı���ϢͨѶ
		//�Խ�����
		xld_talk_data_in = 0x40,			///< �Խ�����
		xld_talk_data_out = 0x41,			///< �Խ�����
		xld_talk_cmd_out = 0x42,			///< �Խ�����
		xld_talk_cmd_in = 0x43,				///< ����Խ�
		//�ͻ���֮��ͨ��

		//�첽��Ϣ���쳣����
		xlc_message = 0x50,					///< �첽��Ϣ���쳣����
		//�ͻ�����������
		xlc_heart_beat = 0x51,				///< �ͻ�����������
		//�û���֤
		xlc_login = 0x52,					///< �û���¼
		xlc_logout = 0x53,					///< ע����¼
		//ʵʱ����
		xlc_real_alarm = 0x60,				///< ʵʱ������Ϣʹ��
		//ʵʱ��Ƶ
		xlc_real_play = 0x70,				///< ʵʱ��Ƶ����
		//Զ�̻ط�
		xlc_vod_play = 0x71,				///< ¼��ط�
		xlc_vod_download = 0x72,			///< ¼������
		//�������ݴ���
		xlc_trans_context = 0x80,			///< �����ı���Ϣ
		xlc_upload_file = 0x81,				///< �ļ�����
		//�Խ�����
		xlc_talk_data_out = 0x90,				///< �Խ�����
		xlc_talk_data_in = 0x91,				///< �Խ�����
		xlc_talk_cmd_in = 0x92,				///< �Խ�����
		xlc_talk_cmd_out = 0x93,				///< ����Խ�
		//�ͻ���֮��ͨ��
	};

	struct CmdHeader
	{
		char beginCode;			///< ��ʼ��־-0xFF
		char version;			///< �汾��
		int seq;				///< ���к�
		unsigned char cmd;		///< ������,��CmdType����
		char flag;				///< ״̬�� 0x0��ʾ��ʼ, 0x1������, 0x2�������
		int length;				///< ���ݳ���,������ͷ���ݺ�β����				
	};

	struct CmdTail
	{
		char verify;			///< У����
		char endCode;			///< ������־-0xFE
	};
};
#pragma pack(pop)

#endif //!__XL_PROTOCOL_H__