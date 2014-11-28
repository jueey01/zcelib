#include "zce_predefine.h"
#include "zce_sqlite_conf_table.h"


//Ŀǰ�汾����ֻ����һ��
#if SQLITE_VERSION_NUMBER >= 3005000


/*****************************************************************************************************************
struct General_SQLite_Config һ����ͨ�õĴ�DB�м�õ�ͨ��������Ϣ�ķ���
*****************************************************************************************************************/
General_SQLite_Config::General_SQLite_Config()
{
    sql_string_ = new char[MAX_SQLSTRING_LEN];
}


General_SQLite_Config::~General_SQLite_Config()
{
    if (sql_string_)
    {
        delete sql_string_;
        sql_string_ = NULL;
    }
}


//��д��SQL
void General_SQLite_Config::sql_replace(unsigned int table_id,
                                        unsigned int conf_id_1,
                                        unsigned int conf_id_2,
                                        const AI_IIJIMA_BINARY_DATA &conf_data,
                                        unsigned int last_mod_time)
{
    //��������SQL
    char *ptmppoint = sql_string_;
    size_t buflen = MAX_SQLSTRING_LEN;

    int len = snprintf(ptmppoint, buflen, "REPLACE INTO config_table_%u "
                       "(conf_id_1,conf_id_2,conf_data,last_mod_time ) VALUES "
                       "(%u,%u,'%s',%u) ",
                       table_id,
                       conf_id_1,
                       conf_id_2,
                       conf_data.ai_iijima_data_,
                       last_mod_time
                      );
    ptmppoint += len;
    buflen -= len;
}

//�õ�ѡ��һ��ȷ�����ݵ�SQL
void General_SQLite_Config::sql_select(unsigned int table_id,
                                       unsigned int conf_id_1,
                                       unsigned int conf_id_2)
{
    char *ptmppoint = sql_string_;
    size_t buflen = MAX_SQLSTRING_LEN;

    //����SQL
    int len = snprintf(ptmppoint, buflen, "SELECT conf_id_1,conf_id_2,conf_data,last_mod_time "
                       "FROM config_table_%u WHERE ((conf_id_1=%u) AND (conf_id_2=%u)) ",
                       table_id,
                       conf_id_1,
                       conf_id_2);
    ptmppoint += len;
    buflen -= len;
}

//�õ�ɾ�����ݵ�SQL
void General_SQLite_Config::sql_delete(unsigned int table_id,
                                       unsigned int conf_id_1,
                                       unsigned int conf_id_2)
{

    char *ptmppoint = sql_string_;
    size_t buflen = MAX_SQLSTRING_LEN;

    int len = snprintf(ptmppoint, buflen, "DELETE FROM config_table_%u WHERE ((conf_id_1=%u) AND (conf_id_2=%u)) ",
                       table_id,
                       conf_id_1,
                       conf_id_2);
    ptmppoint += len;
    buflen -= len;
}
//
void General_SQLite_Config::sql_getcounter(unsigned int table_id)
{
    //����SQL
    char *ptmppoint = sql_string_;
    size_t buflen = MAX_SQLSTRING_LEN;

    int len = snprintf(ptmppoint, buflen, "SELECT COUNT(*) FROM config_table_%u ",
                       table_id);
    ptmppoint += len;
    buflen -= len;
}

//
void General_SQLite_Config::sql_getarray(unsigned int table_id,
                                         unsigned int startno,
                                         unsigned int numquery)
{
    char *ptmppoint = sql_string_;
    size_t buflen = MAX_SQLSTRING_LEN;

    //����SQL
    int len = snprintf(ptmppoint, buflen, "SELECT conf_id_1,conf_id_2,conf_data,last_mod_time "
                       "FROM config_table_%u ",
                       table_id);
    ptmppoint += len;
    buflen -= len;

    //���Ҫ��ѯLIMIT����Ŀ
    if (numquery != 0)
    {
        len = snprintf(ptmppoint, buflen, "LIMIT %u,%u ", startno, numquery);
        ptmppoint += len;
        buflen -= len;
    }
}




#endif //SQLITE_VERSION_NUMBER >= 3005000


