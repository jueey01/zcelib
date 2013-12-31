/*!
* @copyright  2004-2013  Apache License, Version 2.0 FULLSAIL
* @filename   zce_mysql_process.h
* @author     Sailzeng <sailerzeng@gmail.com>
* @version
* @date       2005��05��18��
* @brief      ��ȡMYSQL���ݿ����,���ڶ�ȡDB��������Ϣ
* 
* @details    �ڲ��б�֤�Զ������Ļ��ƣ��㲻�ò����������
* 
* @note
* 
*/

#ifndef ZCE_LIB_MYSQL_STMT_RESULT_H_
#define ZCE_LIB_MYSQL_STMT_RESULT_H_

#include "zce_boost_non_copyable.h"

//�����Ҫ��MYSQL�Ŀ�
#if defined MYSQL_VERSION_ID

#include "zce_mysql_connect.h"
#include "zce_mysql_command.h"

/*!
@brief      ��ȡMYSQL���ݿ����,���ڲ���MySQL DB�ķ���
            ����������װ��connect,command,�����ͨ��ZCE_Mysql_Result��ý��
*/
class ZCELIB_EXPORT ZCE_Mysql_Process : ZCE_NON_Copyable
{

protected:
    //ʵ����
    static ZCE_Mysql_Process   *instance_;

public:

    ///���캯����
    ZCE_Mysql_Process();
    ///��������
    ~ZCE_Mysql_Process();

    /*!
    * @brief      ��ʼ��������,ʹ��hostname��������,���Բ��������Ӻ��������ӣ����Լ����ơ�
    * @return     int             0�ɹ���-1ʧ��
    * @param      host_name       DB HOST����,IP��ַ
    * @param      user            DB USER����
    * @param      pwd             DB PWD����
    * @param      port            �˿�
    * @param      connect_atonce  �Ƿ��������ӷ�����
    */
    int init_mysql_server(const char *host_name,
                          const char *user,
                          const char *pwd,
                          unsigned int port = MYSQL_PORT,
                          bool connect_atonce = false);

    /*!
    * @brief      ��ʼ��MYSQL��ʹ��UNIX socket file����(UNIX��)�����������ܵ�(Windows��),
    *             ֻ��ʼ��Ҳ������,ֻ�����ڱ���
    * @return     int              0�ɹ���-1ʧ��
    * @param      unix_socket_file SOCKET FILE���ƻ��������ܵ�����
    * @param      user             DB USER����
    * @param      pwd              DB PWD����
    * @param      connect_atonce   �Ƿ��������ӷ�����
    */
    int init_mysql_socketfile(const char *unix_socket_file,
                              const char *user,
                              const char *pwd,
                              bool connect_atonce = false);

    ///����Query ������,���ϣ����ʼ�����������,ʹ���������
    int connect_mysql_server();
    ///�Ͽ�����
    void disconnect_mysql_server();

    /*!
    * @brief      ���ڷ�SELECT���(INSERT,UPDATE)
    * @return     int
    * @param      sql
    * @param      numaffect
    * @param      insertid
    * @param      sqllen
    */
    int db_process_query(const char *sql,
                         unsigned int &numaffect,
                         unsigned int &insertid,
                         size_t sqllen = 0);

    /*!
    * @brief      ����SELECT���,ֱ��ת��������ϵķ���
    * @return     int
    * @param      sql
    * @param      numaffect
    * @param      dbresult
    * @param      sqllen
    */
    int db_process_query(const char *sql,
                         unsigned int &numaffect,
                         ZCE_Mysql_Result &dbresult,
                         size_t sqllen = 0);

    /*!
    * @brief      ����SELECT���,����use_result�õ�������ϵķ���
    * @return     int
    * @param      sql
    * @param      dbresult
    * @param      sqllen
    * @note
    */
    int db_process_query(const char *sql,
                         ZCE_Mysql_Result &dbresult,
                         size_t sqllen = 0);

    ///�õ�MYSQL����Ĵ��󷵻�
    unsigned int get_return_error(char *szerr, size_t buflen);

    ///�������Str
    const char *get_return_error_str();
    ///DB���صĴ���ID
    unsigned int get_return_error_id();

    ///�õ�DB���ʵ����
    const char *get_query_sql(void);

    ///�õ�Real Escape String ,Real��ʾ���ݵ�ǰ��MYSQL Connet���ַ���,�õ�Escape String
    ///Escape String Ϊ���ַ����е�����ַ�����ת�������,����',",\���ַ�
    unsigned int make_real_escape_string(char *tostr,
                                         const char *fromstr,
                                         unsigned int fromlen);

public:
    ///Ϊ��SingleTon��׼��
    ///ʵ����ֵ
    static void instance(ZCE_Mysql_Process *);
    ///���ʵ��
    static ZCE_Mysql_Process *instance();
    ///���ʵ��
    static void clean_instance();

protected:

    ///���ݿ�IP��ַ
    std::string       db_hostname_;
    ///DB���ݿ�Ķ˿ں���
    unsigned int      db_port_;

    ///UNIX soket file���ƣ����������ܵ�����
    std::string       db_socket_file_;

    ///���ݿ��û�����
    std::string       db_user_name_;
    ///DB���ݿ�����ID
    std::string       db_password_;

    ///MYSQL���ݿ����Ӷ���
    ZCE_Mysql_Connect db_connect_;

    ///MYSQL����ִ�ж���
    ZCE_Mysql_Command db_command_;
};

#endif //#if defined MYSQL_VERSION_ID

#endif //ZCE_LIB_MYSQL_STMT_RESULT_H_
