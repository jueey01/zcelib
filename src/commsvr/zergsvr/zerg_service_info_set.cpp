#include "zerg_predefine.h"
#include "zerg_service_info_set.h"
#include "zerg_tcp_ctrl_handler.h"



/****************************************************************************************************
class  Service_Info_Set ,
��˼һ�£�
�Ƿ�Ӧ���������װ����Ҳ��ì�ܣ������TCP_Svc_Handlerֱ��ʹ��STL�ķ�װ���ݣ�
��ô���ǵķ�װ���پۺ͵ķ�ʽ������ô�ĺá���TCP_Svc_Handler��Ҫ�ٴη�װ��������
****************************************************************************************************/
Service_Info_Set::Service_Info_Set()
{
}

Service_Info_Set::~Service_Info_Set()
{
    //ZLOG_INFO("[zergsvr] Service_Info_Set::~Service_Info_Set.");
}

void Service_Info_Set::init_services_peerinfo(size_t szpeer)
{
    svr_info_set_.rehash(szpeer);
}

//����SERVICEINFO��ѯPEER��Ϣ
int Service_Info_Set::find_services_peerinfo(const SERVICES_ID &svrinfo, TCP_Svc_Handler *&svrhandle)
{
    MapOfSvrPeerInfo::iterator iter = svr_info_set_.find(svrinfo);

    if (iter == svr_info_set_.end())
    {
        ZLOG_ERROR("[zergsvr] Can't find svchanle info. Svrinfo Type|ID:[%u|%u] .",
            svrinfo.services_type_,
            svrinfo.services_id_);
        return SOAR_RET::ERR_ZERG_NO_FIND_EVENT_HANDLE;
    }

    svrhandle = (*(iter)).second;
    return SOAR_RET::SOAR_RET_SUCC;
}



/******************************************************************************************
Author          : Sail ZENGXING  Date Of Creation: 2007��5��29��
Function        : Service_Info_Set::replace_services_peerInfo
Return          : int
Parameter List  :
Param1: const SERVICES_ID& svrinfo ԭ�͵�SVC INFO������
Param2: TCP_Svc_Handler* new_svchdl  �����ӵķ�����
Param3: TCP_Svc_Handler*& old_svchdl ���ԭ����һ��svrinfo��Ӧ��Hdler,����֪ͨ��,
Description     : ����PEER��Ϣ��
Calls           :
Called By       :
Other           : ���ص�old_svchdl,������������
Modify Record   :
******************************************************************************************/
int Service_Info_Set::replace_services_peerInfo(const SERVICES_ID &svrinfo,
    TCP_Svc_Handler *new_svchdl,
    TCP_Svc_Handler *&old_svchdl)
{
    old_svchdl = NULL;
    MapOfSvrPeerInfo::iterator iter = svr_info_set_.find(svrinfo);

    //�Ѿ�����صļ�¼��
    if (iter != svr_info_set_.end())
    {
        old_svchdl = (*iter).second;

        const size_t TMP_ADDR_LEN = 32;
        char new_addr[TMP_ADDR_LEN], old_addr[TMP_ADDR_LEN];
        strncpy(new_addr, new_svchdl->get_peer_address(), TMP_ADDR_LEN);
        strncpy(old_addr, old_svchdl->get_peer_address(), TMP_ADDR_LEN);

        ZLOG_INFO("[zergsvr] replace_services_peerInfo:%u|%u ,Find Old IP|Port:[%s|%u],New IP Port[%s|%u],Replace old.",
            svrinfo.services_type_,
            svrinfo.services_id_,
            old_addr,
            old_svchdl->get_peer_port(),
            new_addr,
            new_svchdl->get_peer_port()
            );

    }

    svr_info_set_[svrinfo] = new_svchdl;

    return SOAR_RET::SOAR_RET_SUCC;
}

/******************************************************************************************
Author          : Sail ZENGXING  Date Of Creation: 2007��5��29��
Function        : Service_Info_Set::add_services_peerinfo
Return          : int
Parameter List  :
Param1: const SERVICES_ID& svrinfo SVC INFO������
Param2: TCP_Svc_Handler* new_svchdl  �����ӵķ�����
Description     : ����PEER��Ϣ��
Calls           :
Called By       :
Other           : ���ص�old_svchdl,������������
Modify Record   :
******************************************************************************************/
int Service_Info_Set::add_services_peerinfo(const SERVICES_ID &svrinfo,
    TCP_Svc_Handler *new_svchdl)
{
    MapOfSvrPeerInfo::iterator iter = svr_info_set_.find(svrinfo);

    //�Ѿ�����صļ�¼��
    if (iter != svr_info_set_.end())
    {
        TCP_Svc_Handler *old_svchdl = (*iter).second;

        //һ��������˼�����⵼���˴����������д���������ֱ��֪��Ϊʲô������ֱ����ScottxuҪ�����
        const size_t TMP_ADDR_LEN = 32;
        char new_addr[TMP_ADDR_LEN], old_addr[TMP_ADDR_LEN];
        strncpy(new_addr, new_svchdl->get_peer_address(), TMP_ADDR_LEN);
        strncpy(old_addr, old_svchdl->get_peer_address(), TMP_ADDR_LEN);

        ZLOG_ERROR("[zergsvr] add_services_peerinfo:%u|%u Fail,Find Old IP|Port:[%s|%u],New IP Port[%s|%u],Replace old.",
            svrinfo.services_type_,
            svrinfo.services_id_,
            old_addr,
            old_svchdl->get_peer_port(),
            new_addr,
            new_svchdl->get_peer_port()
            );
        return SOAR_RET::ERR_ZERG_SERVER_ALREADY_LONGIN;
    }

    svr_info_set_[svrinfo] = new_svchdl;

    return SOAR_RET::SOAR_RET_SUCC;
}


/******************************************************************************************
Author          : Sail ZENGXING  Date Of Creation: 2006��3��22��
Function        : Service_Info_Set::del_services_peerInfo
Return          : size_t
Parameter List  :
Param1: const SERVICES_ID& svrinfo
Description     : ����SERVICES_ID,ɾ��PEER��Ϣ,
Calls           :
Called By       :
Other           :
Modify Record   :
******************************************************************************************/
size_t Service_Info_Set::del_services_peerInfo(const SERVICES_ID &svrinfo)
{
    MapOfSvrPeerInfo::iterator iter = svr_info_set_.find(svrinfo);

    size_t szdel = svr_info_set_.erase(svrinfo);

    //���û���ҵ�,99.99%������Ӧ���Ǵ���д��������,���ǲ���û�гɹ������.������handle_close.
    if (szdel <= 0)
    {
        ZLOG_INFO("[zergsvr] Can't Service_Info_Set::del_services_peerInfo Size svr_info_set_ %u: szdel:%u svrinfo:%u|%u .",
            svr_info_set_.size(),
            szdel,
            svrinfo.services_type_,
            svrinfo.services_id_);
    }

    //ZCE_ASSERT(szdel >0 );
    return szdel;
}

//
size_t Service_Info_Set::get_services_peersize()
{
    return svr_info_set_.size();
}


/******************************************************************************************
Author          : Sail ZENGXING  Date Of Creation: 2006��10��17��
Function        : Service_Info_Set::dump_svr_peerinfo
Return          : void
Parameter List  :
Param1: char* ret_string
Param2: size_t& str_len
Param3: size_t startno        ��ѯ
Param4: size_t numquery       ��ѯ
Description     :
Calls           :
Called By       :
Other           :
Modify Record   :
******************************************************************************************/
void Service_Info_Set::dump_svr_peerinfo(std::ostringstream &ostr_stream, size_t startno, size_t numquery)
{
    //

    MapOfSvrPeerInfo::iterator iter_tmp = svr_info_set_.begin();
    MapOfSvrPeerInfo::iterator iter_end = svr_info_set_.end();

    //����һ���ǳ��ǳ���ʱ�Ĳ���.
    for (size_t i = 0; iter_tmp != iter_end; ++iter_tmp, ++i)
    {
        //��ѯ��ʼ
        if (i < startno)
        {
            continue;
        }

        //���ڲ�ѯ�ĸ�������
        if (numquery > 0 && i > numquery + startno)
        {
            break;
        }

        SERVICES_ID svr_info = (*(iter_tmp)).first;
        TCP_Svc_Handler *svrhandle = (*(iter_tmp)).second;
        svrhandle->dump_status_info(ostr_stream);
    }

    return;
}

//�ر����е�PEER
void Service_Info_Set::clear_and_closeall()
{
    const size_t SHOWINFO_NUMBER = 500;

    ZLOG_INFO("[zergsvr] Has %u peer want to close. Please wait. ACE that is accursed.", svr_info_set_.size());

    //������������Ǿ��Ե���
    while (svr_info_set_.size() > 0)
    {
        if (svr_info_set_.size() % SHOWINFO_NUMBER == 0)
        {
            ZLOG_INFO("[zergsvr] Now remain %u peer want to close. Please wait. ACE that is accursed.", svr_info_set_.size());
        }

        MapOfSvrPeerInfo::iterator iter = svr_info_set_.begin();
        TCP_Svc_Handler *svrhandle = (*(iter)).second;

        //TCP_Svc_Handler::handle_close������del_services_peerInfo
        svrhandle->handle_close();
    }
}

