/*!
* @copyright  2004-2013  Apache License, Version 2.0 FULLSAIL
* @filename   zce_bytes_encrypt.h
* @author     Sailzeng <sailerzeng@gmail.com>
* @version
* @date       2013��4��5��
*             �����ڣ�������H7N9���Ϻ�����һ�����ӣ�10��һ���ֻ�
*             �ӿ�ʼд��CBC��ɣ���Ȼ����20���죬һ�����м��е�æ��һ����
*             ��������һ������Ч�ʼ��罵�ͣ�
*             2013��4��20��
*             «ɽ����7�������߰�Ϣ��
* 
* @brief      ���ܺ������ṩ��һЩ ������ܺ������Լ���֯���飩���ܵ��㷨������ֱ��ʹ�÷�������㷨
*             ��Ϊ���ԣ�Ŀǰ�Ѿ�֧�ֵĲ��԰���TEA,XTEA,XXTEA,RC5,RC6,CAST5,CAST6(CAST-256)
*             MARS,AES,���кܶ�������KEY���ȣ����������������˲�ͬ���塣������Щ���������д����
*             ��ϵͳ��.
*             Ҳ��δ���ῼ�ǵ��㷨��twofish��safer+��
* 
*             ��֯�㷨��ֵѡ������õĲ���CBC����ʵ���ǵ�ʵ�ָ��ӽ�CBC-MAC����
*             http://zh.wikipedia.org/zh-hant/%E5%9D%97%E5%AF%86%E7%A0%81%E7%9A%84%E5%B7%A5%E4%BD%9C%E6%A8%A1%E5%BC%8F
*             ���������Ѿ����Ժ��൱��ļ��ܴ����а�һ���ˡ����
*             ZCE_Crypt ��һ�����������ݵļ���ģ�棬������ݼ����㷨��KEY_SIZE����Կ���ȣ�
*             ��BLOCK_SIZE ����������㷨ÿ�δ����Ŀ鳤�ȣ����д�������������ʹ��CBC��֯��
*             ��������ǰ��һ��BLOCK���ݺͺ���BLOCK��򣩺�����㷨���м��ܡ������㷨ֻ������Ĳ��ԣ�
* 
* @details    CBC�Ĵ��룬��ӵ����ȫ��Ȩ���ǲο�ά���㷨ʵ�ֵ�ģ��
*             ����������㷨�󲿷ִ����Ǵ�openssl��Cryptlib��libtom-crypt��taocrypt
*             PolarSSL����ֲ������Ҳ���൱�Ĵ�������ά������ http://code.ohloh.net
*             ���������ҵ���ֲ�����ǰ���Щ������ȫת�������Լ��Ķ�����������ת���ȣ�
*             һ�����û��˵��������key���ȣ��ʹ���ʵ�ֵĹ�ϵ���Ҿ�����Ŭ��������һ����
*             ��ϵ
* 
*             ����ѧϰ��֪ʶ����Ҳ���¿���TX���㷨��
*             http://www.cnblogs.com/fullsail/archive/2013/04/29/3051456.html
* 
*             ���ܲ������ݣ����ÿ�δ���251���ֽڵ����ݣ�ÿ�δ���������sub key,��ʱ��õ���
*             ����������
*             �㷨������_���С_key��С_������         ���ܰ�����(251�ֽ�)    ���ܰ�����(251�ֽ�)      �����ٶ�(M/s)      �����ٶ�(M/s)  SUBKEY����          SUBKEY����
*                                                                                                                            ���ٶȵ�Ӱ��(%)       ���ٶȵ�Ӱ��(%)
*             XOR_Crypt_16_16_1                          2179373.79          2255380.04          625.602         647.420           2.89            -0.76
*             TEA_Crypt_8_16_16                           297709.87           305490.29           85.459          87.692           0.31            -0.88
*             TEA_Crypt_8_16_32                           153337.02           159825.81           44.016          45.878          -6.96             7.51
*             TEA_Crypt_8_16_64                            78425.59            79057.65           22.512          22.693          -0.03             1.90
*             TEA_Crypt_8_16_19                           261299.81           284318.22           75.007          81.615           2.58            -2.19
*             XTEA_Crypt_8_16_16                          311079.10           324171.13           89.297          93.055           0.27            -1.25
*             XTEA_Crypt_8_16_32                          158950.12           164494.35           45.627          47.219           0.72             7.35
*             XTEA_Crypt_8_16_64                           81008.23            83274.39           23.253          23.904          -0.91            -0.51
*             XXTEA_Crypt_8_16_32                         124498.73           119149.72           35.738          34.202          -6.02             6.48
*             XXTEA_Crypt_16_16_16                        188572.49           197193.52           54.130          56.605           0.98            -0.34
*             GOST_Crypt_8_32_32                           87889.64            87696.79           25.229          25.173          -0.56             4.66
*             RC5_Crypt_8_16_12                           539206.99           632568.60          154.782         181.582           4.26            11.15
*             RC5_Crypt_8_16_20                           340218.62           380260.96           97.661         109.156          -4.05            15.76
*             RC6_Crypt_16_16_12                          571960.13           623101.80          164.184         178.865           4.69             3.50
*             RC6_Crypt_16_16_20                          356239.78           407268.43          102.260         116.908           5.53             8.83
*             CAST5_Crypt_8_16_8                          504649.43           497531.56          144.862         142.819           5.89             8.83
*             CAST5_Crypt_8_12_16                         247408.71           250209.50           71.020          71.824           5.56             6.31
*             CAST5_Crypt_8_16_12                         323645.37           327082.12           92.904          93.890           6.69             8.57
*             CAST6_Crypt_16_16_48                        174607.61           166313.80           50.122          47.741          20.12            20.95
*             CAST6_Crypt_16_24_48                        171788.15           174149.38           49.312          49.990          20.18            26.61
*             CAST6_Crypt_16_32_48                        173675.19           171758.58           49.854          49.304          17.22            25.10
*             MARS_Crypt_16_16_1                          221375.70           213635.99           63.547          61.325          29.57            20.70
*             MARS_Crypt_16_24_1                          221147.89           213917.35           63.481          61.406          28.58            30.71
*             MARS_Crypt_16_32_1                          219511.06           214845.17           63.011          61.672          30.32            38.10
*             AES_Crypt_16_16_10                          490680.63           450712.15          140.852         129.379           6.26             3.86
*             AES_Crypt_16_24_12                          410409.45           387073.16          117.810         111.111           5.13            21.18
*             AES_Crypt_16_32_14                          365328.38           322226.87          104.869          92.497           4.11             9.04
* 
*             �Ա�һ�£����ı����60%
*             TEA_Crypt_8_16_16                           297709.87           305490.29           85.459          87.692
*             TXTEA16                                     184472.20           185296.85           52.853          53.644
* 
*             ÿ�ζ�ʹ��SUB KEY���в����������ܵ�Ӱ�첢��̫������Ϊԭ�����£�
*             1.Ŀǰѡ����㷨KEY == >SUB KEY������������Ҫ����CPU�ĵط�����Blowfish�����㷨���ٿ��ܾʹ��٣�
*             2.��Կ�ĳ��Ȼ��Ǻ̵ܶģ����Ա���Ҫ���ܵ����ģ�
*             3.��������Ӧ�ö����ÿ�����Ҫ�����Ǽ�ʱ���µ�
*             4.RC��CAST��MARS��AES�����㷨ʹ��sub key����Ӧ�ö���������
* 
* @note       1.�ܶ��㷨��ģ�嶼��typedef����ֱ��ʹ��typedef���࣬��Ϊ����ʵ�����м���ģ�
*             2.ʵ�ֵ��㷨�ܶ�ʱ��û�п���ĳЩƽ̨���ܳ��ֵ�BUS ERROR���⣬���ˣ��ҵĴ�������ֲ��
*               RISC( SPARC)CPU����(ZINDEX_TO_LEUINT32����ת���Ǵ�ָ���ȡ�����ģ������Ƕ���
*               �������X86��ϵ��OK������һЩ SPARC �ܹ� CPU���ǻᱨ������֪��������ˣ����)
*               ����������������CRYPT_XOR_BLOCK��ZINDEX_TO_LEUINT32��ZLEUINT32_TO_INDEX
*               ��Щ��Ҫ�Ľ���
*             3.���д����ڶ�ȡ������Ĭ�ϲ���Сͷ���У��������Ϊ���Ǿ����󲿷�ʱ����Сͷ�Ļ���������
*               �����д��뿼�ǹ���ͷ���������⣬���ֻ����������������У�
* 
*             ������
*             ����������    ��������   �ʣ�����
*             L O V E   L O V E   L O V E GO GO GO
*             L O V E   L O V E   L O V E GO GO GO
*             �������ͷ�� ���ܹ�������
*             ̤��������·   �Ҳ������Ĳ���
*             �������ϼ   Ⱦ������֮��
*             ˼����һ���Ҿ�  ���ϵ�����
*             ��Ѫ��ǻ ����  ������δ֪��Զ��
*             ÿһ���ٻ�ͷ��   �ؼҵ�·�ָ���
*             ������ ���� �ɴ�������������
*             �Ǹ����ҳ�˼ĺ�� �����Ĺ���
*             ������ �һ����� ��֪���Ķ�ǣ��
*             ������ �һ����� ��������ҵļ�
*             L O V E   L O V E   L O V E GO GO GO
*             ��Υ�����˰� ���еİ��˅�
*             �ú���¯�� ��һյ˼����Ȳ�
*             �ұ����ϼ��� �����Ѳ�����
*             һ��䳪������ ���ϵ��ʴ�
*             �������� ����  �Ұ׷��ԲԵĵ���
*             ���������ӵ�� ��ůƯ���ļ��
*             ������ ���� �ɴ�������������
*             ��Զ���ҳ�˼ĺ��  ��ȥ�ĵط�
*             ������ �һ����� ��֪���Ķ�ǣ��
*             ������ �һ����� ��������ҵļ�
*             L O V E   L O V E   L O V E  L O V E
*             ������ �һ����� ��֪���Ķ�ǣ��
*             ������ �һ����� ��������ҵļ�
*             ������ �һ����� ��֪���Ķ�ǣ��
*             ������ �һ����� ��������ҵļ�
*             L O V E  L O V E   L O V E GO GO GO
*             L O V E  L O V E   L O V E GO GO GO
*/

#ifndef ZCE_LIB_BYTES_ENCRYPT_H_
#define ZCE_LIB_BYTES_ENCRYPT_H_

#include "zce_boost_random.h"
#include "zce_trace_log_debug.h"
#include "zce_os_adapt_string.h"

//��Ϊģ�������Ե�ʣ������ò��ִ���㶨Ϊ�棬��������ʱ����
#if defined (ZCE_OS_WINDOWS)
#pragma warning ( push )
#pragma warning ( disable : 4127)
#endif

namespace ZCE_LIB
{

//=================================================================================================================

/*!
@brief      �ṩECB����ܣ�CBC��֯���ܵļ��ܷ�ʽ��ʹ�ø��ּ����㷨��Ϊ
            ���ԣ���һ����������Ҫ��ʹ��typedef��OK�ˣ�

            ����CBC�Ľ�֯�㷨�����ǵ�ʵ�ֺͱ�׼����һ�£�
             A.)һ��BLOCK���ȵ�IV������������
             B.)��������
             C.)һ��4�ֽڵ�0������У������(������ʵ׼ȷ��˵������CBC-MACģʽ)
             D.)�����ʶ�������㷨Ϊ��Ҫ����3����д3���ֽڵ�3�������Ҫ���볤��11��
                ��д11���ֽڵ�11�����������0������һ��BLOCK_SIZE�ֽڵ�BLOCK_SIZEֵ��

            ������֯�㷨��Ҳ�������Աȶ��Ժ�CBC��û�����ƣ�����ʱû��ʵ�ֵı�Ҫ���Ժ�Ҳ��
            ��ʵ��һ���㷨�����ļ����������ѡ�

@tparam     ENCRYPT_STRATEGY �����㷨���ԣ�
@note       �����㷨��BLOCK_SIZE ������4�ı��������ڵ���8������С�ڵ���256��
*/
template < typename ENCRYPT_STRATEGY >
class ZCE_Crypt
{

public:
    //
    typedef typename ENCRYPT_STRATEGY::SUBKEY_STRUCT   CRYPT_SUBKEY_STRUCT;

    /*!
    @brief
    @param      key        ��Կ
    @param      key_len    ��Կ����
    @param      sub_key    ��Կ��������key
    @param      if_encrypt �Ƿ��ǽ��м��ܴ�������Ϊ��Щ�㷨������AES�ˣ���SKEY�����ܺͼ��ܲ�ͬ��
    */
    inline static void key_setup(const unsigned char *key,
                                 size_t key_len,
                                 typename ENCRYPT_STRATEGY::SUBKEY_STRUCT *sub_key,
                                 bool if_encrypt)
    {
        unsigned char real_key[ENCRYPT_STRATEGY::KEY_SIZE];
        const unsigned char *proc_key = key;
        //���key�ĳ��Ȳ�������key����һ�´�����
        if (key_len <  ENCRYPT_STRATEGY::KEY_SIZE )
        {
            generate_real_key(key, key_len, real_key);
            proc_key = real_key;
        }

        ENCRYPT_STRATEGY::key_setup(proc_key, sub_key, if_encrypt);
    }

    /*!
    @brief      ECB�ļ��ܣ�����һ���飬��ĳ��Ⱦ����㷨BLOCK_SIZE
    @param      key         ���ܵ���Կ
    @param      key_len     ���ܵ���Կ����
    @param      src_buf     ԭ��
    @param      cipher_buf  ���ɵ�����
    @note       ע�⣬���ֻ��һ������м��ܣ������ϣ�������Զ������м��ܣ�
                ����ѡ��cbc�ķ�ʽ�������Ҫ��ˣ����ڷ�װһ��������ֱ�������
                ���������ʣ���Ϊ�󲿷ּ����㷨�������Կ����ת��Ϊһ��SKEY����
                ��ֱ��ʹ������������޶����Ӻ�ʱ
    */
    inline static void ecb_encrypt(const unsigned char *key,
                                   size_t key_len,
                                   const unsigned char *src_buf,
                                   unsigned char *cipher_buf)
    {
        //����õ�sub key
        typename ENCRYPT_STRATEGY::SUBKEY_STRUCT sub_key;
        key_setup(key, key_len, &sub_key, true);

        ENCRYPT_STRATEGY::ecb_encrypt(&sub_key, src_buf, cipher_buf);
    }

    /*!
    @brief      ECBģʽ�Ľ��ܣ�����һ���飬��ĳ��Ⱦ����㷨BLOCK_SIZE
    @param      key         ���ܵ���Կ
    @param      key_len     ��Կ�ĳ���
    @param      cipher_buf  ����
    @param      src_buf     ���ɵ�ԭ��
    @note       ��ecb_encrypt ����
    */
    inline  static void ecb_decrypt(const unsigned char *key,
                                    size_t key_len,
                                    const unsigned char *cipher_buf,
                                    unsigned char *src_buf)
    {
        //����õ�sub key
        typename ENCRYPT_STRATEGY::SUBKEY_STRUCT sub_key;
        key_setup(key, key_len, &sub_key, false);

        ENCRYPT_STRATEGY::ecb_decrypt(&sub_key, cipher_buf, src_buf);
    }

    /*!
    @brief      ��ԭ�ļ��ܵõ����ģ�����BUFFER���賤�ȣ��ͼ����㷨��BLOCK_SIZE�й�ϵ��
                ���ĳ���=IV(һ��BLOCK)+ԭ�ĳ���+4���ֽڵ�У��0����+����pid�ĳ��ȣ�

                �����ÿ���ַ�����дΪ������ȣ�
    @return     size_t     ��������BUFFER����Ҫ����
    @param[in]  source_len ԭ�ĳ���
    */
    inline static size_t cbc_cipher_buflen(size_t src_len)
    {
        return ((src_len + sizeof(uint32_t)) / ENCRYPT_STRATEGY::BLOCK_SIZE  + 2 ) * ENCRYPT_STRATEGY::BLOCK_SIZE;
    }

    /*!
    @brief      �����Ľ��ܵõ�ԭ�ģ�ԭ��BUFFER����ĳ��ȣ�ע��������ȱ�ʵ��ԭ��Ҫ��һ�㣬���㴦����У��
    @return     size_t     ԭ��BUFFER����ĳ���
    @param[in]  cipher_len
    @note
    */
    inline static size_t cbc_source_buflen(size_t cipher_len)
    {
        return cipher_len - ENCRYPT_STRATEGY::BLOCK_SIZE ;
    }

    /*!
    @brief      ����û�����Կ���ȱ��㷨Ҫ����٣��������������һ�������㹻����Կ
    @param      key       �û�����Կ
    @param      key_len   �û�����Կ�ĳ���
    @param      real_key  �����㹻����Կ
    */
    inline static void generate_real_key(const unsigned char *key,
                                         size_t key_len,
                                         unsigned char *real_key)
    {
        size_t copykey_count = 0;
        size_t once_copy = 0;
        do
        {
            once_copy = (ENCRYPT_STRATEGY::KEY_SIZE - copykey_count > key_len) ? key_len : ENCRYPT_STRATEGY::KEY_SIZE - copykey_count;
            memcpy(real_key + copykey_count, key, once_copy);
            copykey_count += once_copy;

        }
        while (copykey_count < ENCRYPT_STRATEGY::KEY_SIZE);
    }

    //�����ʹ���������ӿ��ٶȣ�ԭ����uint64_t�����Ż���ϣ����OS64λ�ϣ��ܸ��Ӹ�Ч��
    //������ֱ��������Ż�������2�죬����O1������O2���Ͼͻᷢ���������⣬����ִ�д��󣬣�����������ȡ����һ��ֵ�Ĳ��ִ���
#ifndef CRYPT_XOR_BLOCK
#define CRYPT_XOR_BLOCK(result_ptr,x_ptr,y_ptr)  \
    for (size_t i = 0; i < ENCRYPT_STRATEGY::BLOCK_SIZE / sizeof(uint32_t); ++i) \
    { \
        *(((uint32_t *)result_ptr) + i) = (*(((uint32_t *)x_ptr) + i)) ^ (*((uint32_t *)(y_ptr) + i)); \
    }
#endif

    /*!
    @brief      CBC����
                ������㷨�����ܶ��ǰ���һ��BLOCK���У����Ա��벹�뵽һ��BLOCK���������ֽڣ�
                ����ռ�պñ�BLOCK������������ô���������һ��BLOCK
    @return     int         ����0��ʶ���ܳɹ���-1��ʶʧ�ܣ�һ�����ʧ�ܱ�ʾ��������
    @param[in]     key         ��Կ
    @param[in]     key_len     ��Կ����
    @param[in]     src_buf     ԭ��
    @param[in]     src_len     ԭ�ĳ���
    @param[out]    cipher_buf  ���ĵ�BUFFER
    @param[in,out] cipher_len  ���ĳ��ȣ���α�ʶ����BUFFER�ĳ��ȣ�����ʱ���������ĵ�ʵ�ʳ���
    */
    static int cbc_encrypt(const unsigned char *key,
                           size_t key_len,
                           const unsigned char *src_buf,
                           size_t src_len,
                           unsigned char *cipher_buf,
                           size_t *cipher_len)
    {

        //����������������ʶ��Ի��߷��ش���
        ZCE_ASSERT( key
                    && src_buf
                    && cipher_buf
                    && key_len > 0
                    && src_len > 0 );
        if (key == NULL
            || src_buf == NULL
            || cipher_buf == NULL
            || key_len <= 0
            || src_len <= 0)
        {
            ZLOG_ERROR("Fun[%s] key[%p][%lu] soucre[%p][%lu] cipher[%p][%lu] ",
                       __ZCE_FUNCTION__,
                       key,
                       key_len,
                       src_buf,
                       src_len,
                       cipher_buf,
                       *cipher_len
                      );
            return -1;
        }

        //����õ�sub key
        typename ENCRYPT_STRATEGY::SUBKEY_STRUCT sub_key;
        key_setup(key, key_len, &sub_key, true);

        return cbc_encrypt_skey(&sub_key,
                                src_buf,
                                src_len,
                                cipher_buf,
                                cipher_len);
    }

    /*!
    @brief      �ܶ�����㷨��ʵ�����key������һ��sub_key����ʵ������ܣ����ܶ��������sub_key���У�
                �����ⲿ�ִ�������������������Ҫ���ٴ��������Կ��Ǳ���sub_key��Ȼ����д���
    @return     int
    @param      sub_key ��key���ɵ���key��ʹ��key_setup��������
    @note       ������������ο�cbc_encrypt
    */
    static int cbc_encrypt_skey(const typename ENCRYPT_STRATEGY::SUBKEY_STRUCT *sub_key,
                                const unsigned char *src_buf,
                                size_t src_len,
                                unsigned char *cipher_buf,
                                size_t *cipher_len)
    {
        //����BUF����Ҫ�ĳ��ȣ�
        size_t cphbuf_need_len  = ((src_len + sizeof(uint32_t)) / ENCRYPT_STRATEGY::BLOCK_SIZE  + 2 )
                                  * ENCRYPT_STRATEGY::BLOCK_SIZE;

        //����������������ʶ��Ի��߷��ش���
        ZCE_ASSERT(sub_key
                   && src_buf
                   && cipher_buf
                   && src_len > 0
                   && *cipher_len >= cphbuf_need_len );
        if ( sub_key == NULL
             || src_buf == NULL
             || cipher_buf == NULL
             || src_len <= 0
             || *cipher_len < cphbuf_need_len )
        {
            ZLOG_ERROR("Fun[%s] sub_key [%p] soucre[%p][%lu] cipher[%p][%lu], cipher buffer need len[%lu]. ",
                       __ZCE_FUNCTION__,
                       sub_key,
                       src_buf,
                       src_len,
                       cipher_buf,
                       *cipher_len,
                       cphbuf_need_len
                      );
            return -1;
        }

        //�õ����ĳ���
        *cipher_len = cphbuf_need_len;

        //���ڼ�¼���������������+4����Ϊβ�Ͳ�0��ʱ�򣬿������һ��BLOCK�����дһ���жϴ��롣
        unsigned char xor_result[ENCRYPT_STRATEGY::BLOCK_SIZE];
        unsigned char last_prc_block[ENCRYPT_STRATEGY::BLOCK_SIZE + sizeof(uint32_t)];

        //��������㷨����IV.���������������
        unsigned char *write_ptr = cipher_buf;
        for (size_t i = 0; i < ENCRYPT_STRATEGY::BLOCK_SIZE / sizeof(uint32_t); ++i)
        {
            ZUINT32_TO_INDEX(write_ptr,i,ZCE_LIB::mt19937_instance::instance()->rand());
        }
        const unsigned char *xor_ptr = write_ptr;
        write_ptr += ENCRYPT_STRATEGY::BLOCK_SIZE;
        const unsigned char *read_ptr = src_buf;

        //
        size_t remain_len = src_len;
        while (remain_len > ENCRYPT_STRATEGY::BLOCK_SIZE )
        {
            //����������64bit�ĵĴ��룬�����Ż�����
            CRYPT_XOR_BLOCK(xor_result, read_ptr, xor_ptr);

            //ʹ�ü����㷨��ECBģʽ�����ݿ���м���
            ENCRYPT_STRATEGY::ecb_encrypt(sub_key, xor_result, write_ptr);

            remain_len -= ENCRYPT_STRATEGY::BLOCK_SIZE;
            xor_ptr = write_ptr;
            write_ptr += ENCRYPT_STRATEGY::BLOCK_SIZE;
            read_ptr += ENCRYPT_STRATEGY::BLOCK_SIZE;
        }

        //���һЩ���ݣ�����Ҫ�ڴ�����2��BLOCK
        if (remain_len > 0)
        {
            memcpy(last_prc_block, src_buf + src_len - remain_len, remain_len );
        }

        //β����4���ֽڵ�0������У����֤�����ַ�������Ч��Ӧ�ýӽ�CRC32
        //�ռ��Ͽ����˲�0����Ŀ���
        *((uint32_t *)(last_prc_block + remain_len)) = 0;
        remain_len += sizeof (uint32_t);

        //����Ѿ�����һ��BLOCK
        if (remain_len + sizeof (uint32_t) >= ENCRYPT_STRATEGY::BLOCK_SIZE)
        {

            //���BLOCK������
            CRYPT_XOR_BLOCK(xor_result, last_prc_block, xor_ptr);

            //ʹ�ü����㷨��ECBģʽ�����ݿ���м���
            ENCRYPT_STRATEGY::ecb_encrypt(sub_key, xor_result, write_ptr);

            remain_len -=  ENCRYPT_STRATEGY::BLOCK_SIZE;
            xor_ptr = write_ptr;
            write_ptr += ENCRYPT_STRATEGY::BLOCK_SIZE;

            //����0Ҫ���ڵڶ���2��BLOCK�ˣ�
            for (size_t k = 0; k < remain_len; ++k)
            {
                *(last_prc_block + k) = 0;
            }
        }

        //����һ��block,
        size_t pad_len = ENCRYPT_STRATEGY::BLOCK_SIZE - remain_len;
        for (size_t i = 0; i < pad_len; ++i)
        {
            *(last_prc_block + remain_len + i) = (uint8_t)(pad_len);
        }

        //���
        CRYPT_XOR_BLOCK(xor_result, last_prc_block, xor_ptr);

        //ʹ�ü����㷨��ECBģʽ�����ݿ���м���
        ENCRYPT_STRATEGY::ecb_encrypt(sub_key, xor_result, write_ptr);

        return 0;
    }

    /*!
    @brief      CBC���ܣ�
    @return     int         ����0��ʾ���ܳɹ���-1��ʾʧ�ܣ�ԭ�������У��λ���󣬲������ݴ���,���������
    @param[in]     key         ��Կ
    @param[in]     key_len     ��Կ����
    @param[in]     cipher_buf  ����
    @param[in]     cipher_len  ���ĵĳ���
    @param[out]    src_buf     ����ԭ�ĵ�BUFFER
    @param[in,out] src_len     ��������Ǳ�ʾԭ��BUFFER�ĳ��ȣ�����ʱ��ʾԭ�ĵĳ���
    */
    static int cbc_decrypt(const unsigned char *key,
                           size_t key_len,
                           const unsigned char *cipher_buf,
                           size_t cipher_len,
                           unsigned char *src_buf,
                           size_t *src_len)
    {
        //
        size_t srcbuf_need_len  = cipher_len - ENCRYPT_STRATEGY::BLOCK_SIZE;

        //����������������ʶ��Ի��߷��ش���
        ZCE_ASSERT( key
                    && src_buf
                    && cipher_buf
                    && key_len > 0
                    && cipher_len >=  ENCRYPT_STRATEGY::BLOCK_SIZE * 2
                    && 0 == cipher_len % ENCRYPT_STRATEGY::BLOCK_SIZE
                    && *src_len >= srcbuf_need_len);
        if (key == NULL
            || src_buf == NULL
            || cipher_buf == NULL
            || key_len <= 0
            || cipher_len < ENCRYPT_STRATEGY::BLOCK_SIZE * 2
            || 0 != cipher_len % ENCRYPT_STRATEGY::BLOCK_SIZE
            || *src_len < srcbuf_need_len )
        {
            ZLOG_ERROR("Fun[%s] key[%p][%lu] cipher[%p][%lu] soucre[%p][%lu] cipher buffer need len[%lu].",
                       __ZCE_FUNCTION__,
                       key,
                       key_len,
                       cipher_buf,
                       cipher_len,
                       src_buf,
                       *src_len,
                       srcbuf_need_len
                      );
            return -1;
        }

        //����õ�sub key
        typename ENCRYPT_STRATEGY::SUBKEY_STRUCT sub_key;
        key_setup(key, key_len, &sub_key, false);

        return cbc_decrypt_skey(&sub_key,
                                cipher_buf,
                                cipher_len,
                                src_buf,
                                src_len);

    }

    /*!
    @brief
    @return     int
    @param      sub_key
    @note       ��������˵����ο�cbc_decrypt
    */
    static int cbc_decrypt_skey(const typename ENCRYPT_STRATEGY::SUBKEY_STRUCT *sub_key,
                                const unsigned char *cipher_buf,
                                size_t cipher_len,
                                unsigned char *src_buf,
                                size_t *src_len)
    {
        //
        size_t srcbuf_need_len  = cipher_len - ENCRYPT_STRATEGY::BLOCK_SIZE;

        //����������������ʶ��Ի��߷��ش���
        ZCE_ASSERT( sub_key
                    && src_buf
                    && cipher_buf
                    && cipher_len >=  ENCRYPT_STRATEGY::BLOCK_SIZE * 2
                    && 0 == cipher_len % ENCRYPT_STRATEGY::BLOCK_SIZE
                    && *src_len >= srcbuf_need_len);
        if ( sub_key == NULL
             ||  src_buf == NULL
             || cipher_buf == NULL
             || cipher_len < ENCRYPT_STRATEGY::BLOCK_SIZE * 2
             || 0 != cipher_len % ENCRYPT_STRATEGY::BLOCK_SIZE
             || *src_len < srcbuf_need_len )
        {
            ZLOG_ERROR("Fun[%s] sub_key[%p] cipher[%p][%lu] soucre[%p][%lu] cipher buffer need len[%lu].",
                       __ZCE_FUNCTION__,
                       sub_key,
                       cipher_buf,
                       cipher_len,
                       src_buf,
                       *src_len,
                       srcbuf_need_len
                      );
            return -1;
        }

        unsigned char *write_ptr = src_buf;
        const unsigned char *xor_ptr = cipher_buf;
        const unsigned char *read_ptr = (cipher_buf +  ENCRYPT_STRATEGY::BLOCK_SIZE);
        size_t remain_len = cipher_len - ENCRYPT_STRATEGY::BLOCK_SIZE ;
        unsigned char decrypt_result[ENCRYPT_STRATEGY::BLOCK_SIZE];

        while (remain_len > 0 )
        {
            //ʹ�ü����㷨��ECBģʽ�����ݿ���м���
            ENCRYPT_STRATEGY::ecb_decrypt(sub_key, read_ptr, decrypt_result);

            //�����
            CRYPT_XOR_BLOCK(write_ptr, decrypt_result, xor_ptr);

            remain_len -= ENCRYPT_STRATEGY::BLOCK_SIZE;
            xor_ptr = read_ptr;
            write_ptr += ENCRYPT_STRATEGY::BLOCK_SIZE;
            read_ptr += ENCRYPT_STRATEGY::BLOCK_SIZE;
        }

        //�����pid�˼����ֽ�,������Щpid���ֽ�Ӧ�ö������ֵ��
        size_t pid_len = src_buf[srcbuf_need_len - 1];
        if (pid_len > ENCRYPT_STRATEGY::BLOCK_SIZE)
        {
            return -1;
        }
        for (size_t i = 1; i <= pid_len; ++i)
        {
            if ( pid_len != src_buf[srcbuf_need_len - i] )
            {
                ZLOG_ERROR("Fun[%s] pid data fill error.", __ZCE_FUNCTION__);
                return -1;
            }
        }

        //���0У��
        for (size_t j = 1; j <= sizeof(uint32_t); ++j)
        {
            if ( '\0' != src_buf[srcbuf_need_len - pid_len - j] )
            {
                ZLOG_ERROR("Fun[%s] zero data verify error.", __ZCE_FUNCTION__);
                return -1;
            }
        }

        //ԭ��ʵ�ʳ���
        *src_len = srcbuf_need_len - pid_len - sizeof(uint32_t);
        return 0;
    }

#undef CRYPT_XOR_BLOCK

public:
    //
    const static size_t CRYPT_BLOCK_SIZE = ENCRYPT_STRATEGY::BLOCK_SIZE;

};

//=================================================================================================================

/*!
@brief      ��key��sub key��ͬ���ǵ�key_setup�����Ļ���
*/
class SubKey_Is_Key_ECB
{

public:

    struct SUBKEY_IS_KEY
    {
        const unsigned char *skey_;
    };

    //Ϊ��ͨ��ZCE_Crypt ʵ�ֵ�ת������
    static void key_setup(const unsigned char *key,
                          SUBKEY_IS_KEY *sub_key,
                          bool  /*if_encrypt*/ )
    {
        sub_key->skey_ = key;
    }
};

/*!
@brief      ���Key�Ǳ�ת��������ʹ�ã�ʹ�������Ϊ����

@tparam     key_size  key�ĳ��ȣ�������4�ı���
*/
template <size_t key_size>
class SubKey_Is_Uint32Ary_ECB
{

public:

    struct SUBKEY_IS_Uint32Ary
    {
        uint32_t skey_[key_size / sizeof(uint32_t)];
    };

    //Ϊ��ͨ��ZCE_Crypt ʵ�ֵ�ת������
    static void key_setup(const unsigned char *key,
                          SUBKEY_IS_Uint32Ary *sub_key,
                          bool  /*if_encrypt*/ )
    {
        //ΪʲôҪ��ZINDEX_TO_LEUINT32 ����꣬��֤����ƽ̨ʹ�õ��ֽ���һ��
        for (size_t i = 0; i < key_size / sizeof(uint32_t); ++i )
        {
            sub_key->skey_[i] = ZINDEX_TO_LEUINT32(key, i);
        }
    }
};

/*!
@brief      ��16���ֽڣ�4��UIN32��KEY���ػ�
*/
template<>
class SubKey_Is_Uint32Ary_ECB<16>
{

public:

    struct SUBKEY_IS_Uint32Ary
    {
        uint32_t skey_[4];
    };

    //Ϊ��ͨ��ZCE_Crypt ʵ�ֵ�ת������
    static void key_setup(const unsigned char *key,
                          SUBKEY_IS_Uint32Ary *sub_key,
                          bool  /*if_encrypt*/ )
    {
        sub_key->skey_[0] = ZINDEX_TO_LEUINT32(key, 0);
        sub_key->skey_[1] = ZINDEX_TO_LEUINT32(key, 1);
        sub_key->skey_[2] = ZINDEX_TO_LEUINT32(key, 2);
        sub_key->skey_[3] = ZINDEX_TO_LEUINT32(key, 3);
    };
};

/*!
@brief      ��32���ֽڣ�8��UIN32��KEY���ػ�
*/
template<>
class SubKey_Is_Uint32Ary_ECB<32>
{

public:

    struct SUBKEY_IS_Uint32Ary
    {
        uint32_t skey_[8];
    };

    //Ϊ��ͨ��ZCE_Crypt ʵ�ֵ�ת������
    static void key_setup(const unsigned char *key,
                          SUBKEY_IS_Uint32Ary *sub_key,
                          bool  /*if_encrypt*/ )
    {
        sub_key->skey_[0] = ZINDEX_TO_LEUINT32(key, 0);
        sub_key->skey_[1] = ZINDEX_TO_LEUINT32(key, 1);
        sub_key->skey_[2] = ZINDEX_TO_LEUINT32(key, 2);
        sub_key->skey_[3] = ZINDEX_TO_LEUINT32(key, 3);
        sub_key->skey_[4] = ZINDEX_TO_LEUINT32(key, 4);
        sub_key->skey_[5] = ZINDEX_TO_LEUINT32(key, 5);
        sub_key->skey_[6] = ZINDEX_TO_LEUINT32(key, 6);
        sub_key->skey_[7] = ZINDEX_TO_LEUINT32(key, 7);
    };
};

//=================================================================================================================
/*!
@brief      ʹ�������м��ܵĲ����࣬��Ҫ��Ϊ�˲���CBC�����ģ�
            �ܼ򵥣���Ȼ�ٶ�Ҳ��,�����ʱ��Ҳ���룬��Щʱ���������㹻�ˣ���
            ��������£�����һ�����ӣ��������дĳ�������㷨��ECB���ܲ��ԣ�
            ����CBC��ʹ��
*/
class XOR_ECB  : public SubKey_Is_Key_ECB
{
public:

    //XOR�㷨ֱ��ʹ���û���KEY��
    typedef  SUBKEY_IS_KEY SUBKEY_STRUCT;

    ///�����ܺ���
    static void ecb_encrypt(const SUBKEY_STRUCT *skey,
                            const unsigned char *src_block,
                            unsigned char *cipher_block);
    ///�����ܺ���
    static void ecb_decrypt(const SUBKEY_STRUCT *skey,
                            const unsigned char *cipher_block,
                            unsigned char *src_block);

public:
    //����㷨һ�δ���һ��BLOCK�ĳ���
    const static size_t BLOCK_SIZE = 16;
    //����㷨KEY�ĳ���
    const static size_t KEY_SIZE   = 16;
};

//�򵥵������ܣ���Ҫ���ڲ���ZCE_Crypt��
//typedef����ԭ���ǣ������㷨���ƣ��㷨������BLOCK���ȣ�key���ȣ�����(�Ƽ�������������key������һ����ϵ)
typedef ZCE_Crypt<XOR_ECB>   XOR_Crypt_16_16_1;

//=================================================================================================================

/*!
@brief      TEA�ļ����㷨������ο�����ά����
            ����㷨��������ΪTecent�õĶ࣬��������㷨֪���Ƚϴ�
            ���㷨ʹ����һ�����س�������Ϊ����������Դ�ڻƽ���ʣ��Ա�֤ÿһ�ּ��ܶ�����ͬ��
            ���ĵľ�ȷֵ�ƺ�������Ҫ������ TEA ��������Ϊ ��=��(��5 - 1)231��
            ��Ҳ���ǳ����е� 0��9E3779B9��
@tparam     round_size  ���ܵ��������Ƽ�������32����64��TX��ֵ����16�֣����Լ����Խ��ͣ���Ȼ���ܺ�һЩ��
                        ������ֵ������Ӧ��Ҳ���ԡ�
@note       �㷨��ʹ����ZINDEX_TO_LEUINT32����Щ�꣬��ʵ���൱������Ϊ�㷨�ı�����Сͷ��
*/
template <size_t round_size>
class TEA_ECB  : public SubKey_Is_Uint32Ary_ECB<16>
{
public:
    //
    static const uint32_t DELTA = 0x9e3779b9;

    //ʹ��������ΪSUB KEY��
    typedef   SUBKEY_IS_Uint32Ary SUBKEY_STRUCT ;

    //���ܺ���
    static void ecb_encrypt(const SUBKEY_STRUCT *sub_key,
                            const unsigned char *src_block,
                            unsigned char *cipher_block)
    {
        //ΪʲôҪ��ZINDEX_TO_LEUINT32,��ΪҪ��֤��ƽ̨�¼���һ��
        uint32_t v0 = ZINDEX_TO_LEUINT32(src_block, 0);
        uint32_t v1 = ZINDEX_TO_LEUINT32(src_block, 1);
        uint32_t sum = 0;

        const uint32_t *k = sub_key->skey_;

        /* basic cycle start */
        for (size_t i = 0; i < round_size; i++)
        {
            sum += DELTA;
            v0 += ((v1 << 4) + k[0]) ^ (v1 + sum) ^ ((v1 >> 5) + k[1]);
            v1 += ((v0 << 4) + k[2]) ^ (v0 + sum) ^ ((v0 >> 5) + k[3]);
        }
        ZLEUINT32_TO_INDEX(cipher_block, 0, v0);
        ZLEUINT32_TO_INDEX(cipher_block, 1, v1);
    }
    //���ܺ���
    static void ecb_decrypt(const SUBKEY_STRUCT *sub_key,
                            const unsigned char *cipher_block,
                            unsigned char *src_block)
    {
        uint32_t v0 = ZINDEX_TO_LEUINT32(cipher_block, 0);
        uint32_t v1 = ZINDEX_TO_LEUINT32(cipher_block, 1);
        uint32_t sum = DELTA ;
        sum *= round_size;

        const uint32_t *k = sub_key->skey_;

        //�ּ���ѭ��
        for (size_t i = 0; i < round_size; i++)
        {
            /* basic cycle start */
            v1 -= ((v0 << 4) + k[2]) ^ (v0 + sum) ^ ((v0 >> 5) + k[3]);
            v0 -= ((v1 << 4) + k[0]) ^ (v1 + sum) ^ ((v1 >> 5) + k[1]);
            sum -= DELTA;
        }                                              /* end cycle */
        ZLEUINT32_TO_INDEX(src_block, 0, v0);
        ZLEUINT32_TO_INDEX(src_block, 1, v1);
    }

public:
    //TEA�㷨һ�δ���һ��BLOCK�ĳ���
    const static size_t BLOCK_SIZE = 8;
    //TEA�㷨KEY�ĳ���
    const static size_t KEY_SIZE   = 16;
};

//TEA�㷨��TX�õ���16�֣��㷨�����Ƽ���32�֣�����64�֣�
//typedef����ԭ���ǣ������㷨���ƣ����㷨������BLOCK����key���ȣ�����(�Ƽ�������������key������һ����ϵ)��
typedef ZCE_Crypt<TEA_ECB<16 > > TEA_Crypt_8_16_16;
typedef ZCE_Crypt<TEA_ECB<32 > > TEA_Crypt_8_16_32;
typedef ZCE_Crypt<TEA_ECB<64 > > TEA_Crypt_8_16_64;

//=================================================================================================================

/*!
@brief      XTEA �� TEA ʹ������ͬ�ļ����㣬���������˽�Ȼ��ͬ��˳��
            Ϊ����ֹ��Կ���������ĸ�����Կ���ڼ��ܹ����У�ԭ 128 λ����
            Կ�����Ϊ 4 �� 32 λ������Կ��������һ�ֲ�̫����ķ�ʽ����
            ��ϣ����ٶȸ����ˡ�
            http://en.wikipedia.org/wiki/XTEA
@tparam     round_size ���ܵ�����
*/
template <size_t round_size>
class XTEA_ECB  : public SubKey_Is_Uint32Ary_ECB<16>
{
public:
    //
    static const uint32_t DELTA = 0x9e3779b9;

    //ʹ��������ΪSUB KEY��
    typedef   SUBKEY_IS_Uint32Ary SUBKEY_STRUCT ;

    //���ܺ���
    static void ecb_encrypt(const SUBKEY_STRUCT *sub_key,
                            const unsigned char *src_block,
                            unsigned char *cipher_block)
    {
        //ΪʲôҪ��ZINDEX_TO_LEUINT32,��ΪҪ��֤��ƽ̨�¼���һ��
        uint32_t v0 = ZINDEX_TO_LEUINT32(src_block, 0);
        uint32_t v1 = ZINDEX_TO_LEUINT32(src_block, 1);
        uint32_t sum = 0;

        const uint32_t *k = sub_key->skey_;

        //��ѭ��
        for (size_t i = 0; i < round_size; i++)
        {
            v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + k[sum & 3]);
            sum += DELTA;
            v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + k[(sum >> 11) & 3]);
        }
        ZLEUINT32_TO_INDEX(cipher_block, 0, v0);
        ZLEUINT32_TO_INDEX(cipher_block, 1, v1);
    }
    //���ܺ���
    static void ecb_decrypt(const SUBKEY_STRUCT *sub_key,
                            const unsigned char *cipher_block,
                            unsigned char *src_block)
    {
        uint32_t v0 = ZINDEX_TO_LEUINT32(cipher_block, 0);
        uint32_t v1 = ZINDEX_TO_LEUINT32(cipher_block, 1);
        uint32_t sum = DELTA;
        sum *= round_size;

        const uint32_t *k = sub_key->skey_;

        for (size_t i = 0; i < round_size; i++)
        {
            v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + k[(sum >> 11) & 3]);
            sum -= DELTA;
            v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + k[sum & 3]);
        }
        ZLEUINT32_TO_INDEX(src_block, 0, v0);
        ZLEUINT32_TO_INDEX(src_block, 1, v1);
    }

public:
    //XTEA�㷨һ�δ���һ��BLOCK�ĳ���
    const static size_t BLOCK_SIZE = 8;
    //XTEA�㷨KEY�ĳ���
    const static size_t KEY_SIZE   = 16;
};

//XTEA�㷨��
//typedef����ԭ���ǣ������㷨���ƣ��㷨������BLOCK���ȣ�key���ȣ�����(�Ƽ�������������key������һ����ϵ)
typedef ZCE_Crypt<XTEA_ECB<16 > > XTEA_Crypt_8_16_16;
typedef ZCE_Crypt<XTEA_ECB<32 > > XTEA_Crypt_8_16_32;
typedef ZCE_Crypt<XTEA_ECB<64 > > XTEA_Crypt_8_16_64;

//=================================================================================================================

/*!
@brief      Ҳ����ΪCorrected Block TEA,�����ǲο���ά����XXTEA��TEA��XTEA
            ��һ���ش�Ĳ�ͬ�ǵ������
            http://en.wikipedia.org/wiki/XXTEA
            ʹ��ά���Ĵ��뻹����һ���Ż����´���ʧЧ���⣬���¡�
@tparam     block_size
@tparam     round_size  round_size = 6 + 52/(block_size/4)

*/
template <size_t block_size , size_t round_size>
class XXTEA_ECB  : public SubKey_Is_Uint32Ary_ECB<16>
{
public:
    //
    static const uint32_t DELTA = 0x9e3779b9;

    //ʹ��������ΪSUB KEY��
    typedef   SUBKEY_IS_Uint32Ary SUBKEY_STRUCT ;

#define XXTEA_MX (((z>>5^y<<2) + (y>>3^z<<4)) ^ ((sum^y) + (k[(p&3)^e] ^ z)))

    //���ܺ���
    static void ecb_encrypt(const SUBKEY_STRUCT *sub_key,
                            const unsigned char *src_block,
                            unsigned char *cipher_block)
    {

        const uint32_t *k = sub_key->skey_;

        uint32_t  sum = 0, y, z , e , p;

        size_t rounds = round_size;
        size_t num_uint32 = block_size / sizeof(uint32_t);

        uint32_t v[block_size / sizeof(uint32_t)];
        for (size_t i = 0; i < num_uint32; ++i)
        {
            v[i] = ZINDEX_TO_LEUINT32(src_block, i);
        }

        z = v[num_uint32 - 1];
        do
        {
            sum += DELTA;
            e = (sum >> 2) & 3;
            for ( p = 0; p < num_uint32 - 1; ++p)
            {
                y = v[p + 1];
                z = v[p] += XXTEA_MX;
            }
            y = v[0];
            z = v[num_uint32 - 1] += XXTEA_MX;
        }
        while (--rounds);

        for (size_t i = 0; i < num_uint32; ++i)
        {
            ZLEUINT32_TO_INDEX(cipher_block, i, v[i]);
        }
    }

    //���ܺ���
    static void ecb_decrypt(const SUBKEY_STRUCT *sub_key,
                            const unsigned char *cipher_block,
                            unsigned char *src_block)
    {

        uint32_t sum = DELTA;
        sum *= round_size;

        const uint32_t *k = sub_key->skey_;

        uint32_t v[block_size / sizeof(uint32_t)];
        uint32_t num_uint32 = block_size / sizeof(uint32_t);
        size_t rounds = round_size;

        for (size_t i = 0; i < num_uint32; ++i)
        {
            v[i] = ZINDEX_TO_LEUINT32(cipher_block, i);
        }
        uint32_t y, z , e , p;
        y = v[0];
        do
        {
            e = (sum >> 2) & 3;
            for (p = num_uint32 - 1; p > 0; p--)
            {
                z = v[p - 1];
                y = v[p] -= XXTEA_MX;
            }
            z = v[num_uint32 - 1];
            y = v[0] -= XXTEA_MX;
            sum -= DELTA;
        }
        while (--rounds);

        //���������һ���в�Ʊ�������飬�Ż��������⣬
        //������δ�������ά���������whileѭ��ԭ���Ĵ�����������ʽ
        //while ((sum -= DELTA) != 0);
        //����VS2010��Realse �汾���Ż�ѡ�O1��O2���򿪺������
        //whileѭ����Ȼ���������ˣ���һЩ�ֵ��ÿ�����࣬Ҳ����ˡ�����shit happen��

        for (size_t i = 0; i < num_uint32; ++i)
        {
            ZLEUINT32_TO_INDEX(src_block, i, v[i]);
        }
    }

#undef XXTEA_MX

public:
    //XXTEA�㷨һ�δ���һ��BLOCK�ĳ���
    const static size_t BLOCK_SIZE = block_size;
    //XXTEA�㷨KEY�ĳ���
    const static size_t KEY_SIZE   = 16;
};

typedef ZCE_Crypt<XXTEA_ECB<8, 32 > >  XXTEA_Crypt_8_16_32;
typedef ZCE_Crypt<XXTEA_ECB<16, 16 > > XXTEA_Crypt_16_16_16;

//=================================================================================================================

/*!
@brief      GOST�ǵ�������KKB������ļ����㷨����ʵ���DES��
            ����������Ӵ�����������GOST����ԿҪ��256λ����������
            ���԰�ȫ�Ժ���DES,���ʵ�ֵ�����ֻ����32�֣��������޷��ı䣩
*/
class GOST_ECB : public SubKey_Is_Uint32Ary_ECB<32>
{
public:

    //�㷨ֱ��ʹ���û���KEY��
    typedef   SUBKEY_IS_Uint32Ary SUBKEY_STRUCT ;

    ///GOST���ܺ���
    static void ecb_encrypt(const SUBKEY_STRUCT *sub_key,
                            const unsigned char *src_block,
                            unsigned char *cipher_block);
    ///GOST���ܺ���
    static void ecb_decrypt(const SUBKEY_STRUCT *sub_key,
                            const unsigned char *cipher_block,
                            unsigned char *src_block);

    //GOST����Կ������32�ֽ�256bits��GOST�㷨���ʱ�DES�򵥣���֮���԰�ȫ��Ҫ��һЩ����Ҫ������Ϊkey��
    const static size_t KEY_SIZE   = 32;
    //GOSTÿ�δ�����BLOCK��С
    const static size_t BLOCK_SIZE = 8;

    //
    static const uint32_t GOST_WZ_SPKEY[32];
    //
    static const unsigned char GOST_WZ_SP[8][16];
};

//Ĭ��GOST����8�ֽڵ�BLOCK��32�ֽڣ�256bits����key��32��,
//typedef����ԭ���ǣ������㷨���ƣ��㷨������BLOCK���ȣ�key���ȣ�����(�Ƽ�������������key������һ����ϵ)
typedef ZCE_Crypt < GOST_ECB > GOST_Crypt_8_32_32;

//=================================================================================================================

/*!
@brief      RC�㷨��S�ж��壬S���ӵĳ��Ⱥ������й�ϵ�������֧�ֵ��������
            ��32��
*/
class RC_SBOX_Define
{
protected:
    //���ļ�������
    const static size_t MAX_ROUND_SIZE = 32;
    //���һЩ��Ҳ������ħ������,������ʹ��32�֣�����RC�㷨����������Ҫ����32,RC_STAB��ʵҲ�������ɣ���Ϊ���ٶȣ�����
    //68 = 32 * 2 + 2 + 2; ��ʵRC5�����66��RC6������68
    static const uint32_t RC_SBOX[(MAX_ROUND_SIZE + 2) * 2];
};

/*!
@brief      RC�����㷨�Ļ��࣬������չRC5��RC6�㷨��RC�Ƚ�DES�������ǿ죬�ǳ��죬
            ������ܱ���SKEY��KEY��S�м���õ��Ķ���������һ���ٶ�Ӧ�ÿ��Է�
            RC�㷨��ʵҲ���Կ��Ա任key�ĳ��ȣ��Լ�BLOCK���ȣ��Լ����ܵ������Ķ�����
            �Ҷ�͵��KEY�������˹̶� �������Ҫ����RC��skey������
@tparam     round_size  ���ܵ�������Ϊ4��8������12����20����32,���ֵ32
@tparam     skey_size   SBOX�Ĵ�С��RC5��RC6�㷨�е㲻һ����RC5�㷨Ϊ����+2
                        RC6�㷨Ϊ����+4
*/
template <size_t key_size, size_t round_size, size_t sbox_size >
class RC_ECB_Base : public RC_SBOX_Define
{
public:

    //RC6��key���ȿ�����8-128�ֽ�(64-1024bit)�������ѡ��16�ֽ�(128bit)
    const static size_t KEY_SIZE   = key_size;

    struct RC_SUBKEY
    {
        uint32_t skey_[ sbox_size];
    };

    //���ܵ�����
    const static size_t ROUND_SIZE = round_size;
    //S BOX�Ĵ�С
    const static size_t SBOX_SIZE  = sbox_size;

    //
    static void key_setup(const unsigned char *key ,
                          RC_SUBKEY *subkey,
                          bool  /*if_encrypt*/ )
    {

        uint32_t a = 0, b = 0;

        // copy the key into the L array
        uint32_t lkey[KEY_SIZE / sizeof(uint32_t)];
        for (size_t i = 0; i < key_size / sizeof(uint32_t); i++)
        {
            lkey[i] = ZINDEX_TO_LEUINT32(key, i);
        }

        /* key_setup the S array */
        memcpy(subkey->skey_, RC_SBOX, SBOX_SIZE * sizeof(uint32_t));

        for (size_t i = 0, j = 0; i < sbox_size; ++i)
        {
            a = subkey->skey_[i] = ZCE_ROTL32(subkey->skey_[i] + a + b, 3);
            b = lkey[j] = ZCE_ROTL32(lkey[j] + a + b, (a + b) & 31);

            if (++j == KEY_SIZE / sizeof(uint32_t) )
            {
                j = 0;
            }
        }
    }
};

/*!
@brief      RC5�ļ����㷨��ֱ�ӴӴ����������RC6�򵥲���
            http://en.wikipedia.org/wiki/RC5
@tparam     round_size ���ܵ�������
@tparam     sbox_size  SBOX�Ĵ�С
*/
template <size_t key_size, size_t round_size , size_t sbox_size >
class RC5_ECB : public RC_ECB_Base< key_size, round_size, sbox_size >
{
public:

    //Ϊ�˷���ZCE_Crypt,�������KEY���ͣ�
    typedef typename RC_ECB_Base<key_size, round_size, sbox_size>::RC_SUBKEY  SUBKEY_STRUCT;

    //���ܺ���
    static void ecb_encrypt(const SUBKEY_STRUCT *sub_key,
                            const unsigned char *src_block,
                            unsigned char *cipher_block)
    {

        uint32_t  a = ZINDEX_TO_LEUINT32(src_block, 0) + sub_key->skey_[0];
        uint32_t  b = ZINDEX_TO_LEUINT32(src_block, 1) + sub_key->skey_[1];
        for (size_t i = 1; i <= round_size; i++)
        {
            a = ZCE_ROTL32(a ^ b, b & 31) + sub_key->skey_[2 * i];
            b = ZCE_ROTL32(b ^ a, a & 31) + sub_key->skey_[2 * i + 1];
        }
        ZLEUINT32_TO_INDEX(cipher_block, 0, a);
        ZLEUINT32_TO_INDEX(cipher_block, 1, b);
    }
    //���ܺ���
    static void ecb_decrypt(const SUBKEY_STRUCT *subkey,
                            const unsigned char *cipher_block,
                            unsigned char *src_block)
    {

        uint32_t  a = ZINDEX_TO_LEUINT32(cipher_block, 0);
        uint32_t  b = ZINDEX_TO_LEUINT32(cipher_block, 1);

        for (size_t i = round_size; i > 0; i--)
        {
            b = ZCE_ROTR32(b - subkey->skey_[2 * i + 1], a) ^ a;
            a = ZCE_ROTR32(a - subkey->skey_[2 * i], b) ^ b;
        }
        ZLEUINT32_TO_INDEX(src_block, 0, a - subkey->skey_[0]);
        ZLEUINT32_TO_INDEX(src_block, 1, b - subkey->skey_[1]);
    }

public:
    //ÿ�δ�����BLOCK������8���ֽ�
    const static size_t BLOCK_SIZE = 8;
};

//RC5�Ƽ��ļ����㷨��������12�֣�RC5_Crypt_16_12_8����ά������Ҳд��һ��
//12-round RC5 (with 64-bit blocks) is susceptible to a differential attack using 2^44 chosen plaintexts
//typedef����ԭ���ǣ������㷨���ƣ��㷨������BLOCK���ȣ�key���ȣ�����(�Ƽ�������������key������һ����ϵ)
typedef ZCE_Crypt < RC5_ECB < 16, 12, 12 * 2 + 2 > > RC5_Crypt_8_16_12;
typedef ZCE_Crypt < RC5_ECB < 16, 20, 20 * 2 + 2 > > RC5_Crypt_8_16_20;

/*!
@brief      RC6������AES�ĺ�ѡ����֮һ��
            http://en.wikipedia.org/wiki/RC6
            RC6 һ������£��Ƽ�128bit��Կ��128bitBLOCK������20.
*/
template <size_t key_size, size_t round_size , size_t sbox_size >
class RC6_ECB : public RC_ECB_Base<key_size, round_size, sbox_size >
{
public:

#define EN_RC6_RND(i,a,b,c,d)                             \
    t = ZCE_ROTL32(b * (b + b + 1), 5);                   \
    u = ZCE_ROTL32(d * (d + d + 1), 5);                   \
    a = ZCE_ROTL32(a ^ t, u ) + skey_ptr[i];              \
    c = ZCE_ROTL32(c ^ u, t ) + skey_ptr[i + 1]

#define DE_RC6_RND(i,a,b,c,d)                             \
    u = ZCE_ROTL32(d * (d + d + 1), 5);                   \
    t = ZCE_ROTL32(b * (b + b + 1), 5);                   \
    c = ZCE_ROTR32(c - skey_ptr[i + 1], t ) ^ u;          \
    a = ZCE_ROTR32(a - skey_ptr[i], u ) ^ t

    //Ϊ�˷���ZCE_Crypt��typedef����
    typedef typename RC_ECB_Base<key_size, round_size, sbox_size>::RC_SUBKEY  SUBKEY_STRUCT;

    //���ܺ���
    static void ecb_encrypt(const SUBKEY_STRUCT *sub_key,
                            const unsigned char *src_block,
                            unsigned char *cipher_block)
    {
        uint32_t  t = 0, u = 0;
        const uint32_t *skey_ptr = sub_key->skey_;
        uint32_t a = ZINDEX_TO_LEUINT32(src_block, 0);
        uint32_t b = ZINDEX_TO_LEUINT32(src_block, 1) + skey_ptr[0];
        uint32_t c = ZINDEX_TO_LEUINT32(src_block, 2);
        uint32_t d = ZINDEX_TO_LEUINT32(src_block, 3) + skey_ptr[1];

        for (size_t i = 0; i < round_size / sizeof(uint32_t); ++i)
        {
            EN_RC6_RND( i * 8 + 2, a, b, c, d);
            EN_RC6_RND( i * 8 + 4, b, c, d, a);
            EN_RC6_RND( i * 8 + 6, c, d, a, b);
            EN_RC6_RND( i * 8 + 8, d, a, b, c);
        }

        ZLEUINT32_TO_INDEX(cipher_block, 0, a + skey_ptr[sbox_size - 2]);
        ZLEUINT32_TO_INDEX(cipher_block, 1, b);
        ZLEUINT32_TO_INDEX(cipher_block, 2, c + skey_ptr[sbox_size - 1]);
        ZLEUINT32_TO_INDEX(cipher_block, 3, d);
    }
    //���ܺ���
    static void ecb_decrypt(const SUBKEY_STRUCT *sub_key,
                            const unsigned char *cipher_block,
                            unsigned char *src_block)
    {
        uint32_t t = 0, u = 0;
        const uint32_t *skey_ptr = sub_key->skey_;
        uint32_t a = ZINDEX_TO_LEUINT32(cipher_block, 0) - skey_ptr[sbox_size - 2];
        uint32_t b = ZINDEX_TO_LEUINT32(cipher_block, 1);
        uint32_t c = ZINDEX_TO_LEUINT32(cipher_block, 2) - skey_ptr[sbox_size - 1];
        uint32_t d = ZINDEX_TO_LEUINT32(cipher_block, 3);

        for (size_t i = 0; i < round_size / sizeof(uint32_t); ++i)
        {
            DE_RC6_RND(sbox_size - 8 * i - 4, d, a, b, c);
            DE_RC6_RND(sbox_size - 8 * i - 6, c, d, a, b);
            DE_RC6_RND(sbox_size - 8 * i - 8, b, c, d, a);
            DE_RC6_RND(sbox_size - 8 * i - 10, a, b, c, d);
        }
        ZLEUINT32_TO_INDEX(src_block, 0, a);
        ZLEUINT32_TO_INDEX(src_block, 1, b - skey_ptr[0]);
        ZLEUINT32_TO_INDEX(src_block, 2, c);
        ZLEUINT32_TO_INDEX(src_block, 3, d - skey_ptr[1]);
    }
#undef EN_RC6_RND
#undef DE_RC6_RND

public:
    //ÿ�δ�����BLOCK������16���ֽ�
    const static size_t BLOCK_SIZE = 16;
};

//ģ������Ǽ���������RC6�Ƽ��ļ����㷨��������20��������Ǽ���ǿ�ȣ��Ƽ�ʹ��RC6_Crypt_16_20_16
//typedef����ԭ���ǣ������㷨���ƣ��㷨������BLOCK���ȣ�key���ȣ�����(�Ƽ�������������key������һ����ϵ)
typedef ZCE_Crypt < RC6_ECB < 16, 12, 12 * 2 + 4 > > RC6_Crypt_16_16_12;
typedef ZCE_Crypt < RC6_ECB < 16, 20, 20 * 2 + 4 > > RC6_Crypt_16_16_20;

//=================================================================================================================

class CAST_SBOX_Define
{
protected:
    //SBOX��CAST5��8����CAST6����ǰ��4����
    static const uint32_t CAST_SBOX[8][256];

protected:
    //CAST6 �㷨��ħ����������KEY����
    static const uint32_t CAST6_KEY_MASK[192];
    //CAST6 �㷨��ħ����������KEY����
    static const uint8_t  CAST6_KEY_ROT[32];
};

//����CAST6_KEY_ROTAST�㷨��SBOX����CAST5��CAST6�㷨ʹ��
template < size_t round_size>
class CAST_ECB_Base  : public CAST_SBOX_Define
{
protected:

    struct CAST_SUBKEY
    {
        uint32_t mkey_[round_size];
        uint8_t  rkey_[round_size];
    };
};

#define CAST_F1(x, a, s, r)                                                   \
    t = ZCE_ROTL32(s + a, r);                                                 \
    x ^= ((CAST_SBOX_Define::CAST_SBOX[0][ZUINT32_3BYTE(t)] ^ CAST_SBOX_Define::CAST_SBOX[1][ZUINT32_2BYTE(t)]) - \
          CAST_SBOX_Define::CAST_SBOX[2][ZUINT32_1BYTE(t)]) + CAST_SBOX_Define::CAST_SBOX[3][ZUINT32_0BYTE(t)];
#define CAST_F2(x, a, s, r)                                                   \
    t = ZCE_ROTL32(s ^ a, r);                                                 \
    x ^= ((CAST_SBOX_Define::CAST_SBOX[0][ZUINT32_3BYTE(t)] - CAST_SBOX_Define::CAST_SBOX[1][ZUINT32_2BYTE(t)]) + \
          CAST_SBOX_Define::CAST_SBOX[2][ZUINT32_1BYTE(t)]) ^ CAST_SBOX_Define::CAST_SBOX[3][ZUINT32_0BYTE(t)];
#define CAST_F3(x, a, s, r)                                                   \
    t = ZCE_ROTL32(s - a, r);                                                 \
    x ^= ((CAST_SBOX_Define::CAST_SBOX[0][ZUINT32_3BYTE(t)] + CAST_SBOX_Define::CAST_SBOX[1][ZUINT32_2BYTE(t)]) ^ \
          CAST_SBOX_Define::CAST_SBOX[2][ZUINT32_1BYTE(t)]) - CAST_SBOX_Define::CAST_SBOX[3][ZUINT32_0BYTE(t)];

/*!
@brief      CAST5 ECB�����㷨���ֱ���ΪCAST128,
            �����ѡ�����Կ128bits��BLOCK64bit��Ĭ������16��
            CAST5����Կ���ȿ��Ը��̣�40-128bits��8bit��������������������12��16
            ��KEY���Ⱥͣ������ĳ�ģ�����Ӧ��Ҳ���ѣ�
@tparam     key_size   ��Կ���ȣ������ֵ����8��64bits����12��96bits����16��128bits��
@tparam     round_size ���ܵ����������key_size > 80bits����þ�Ҫ16�֣������ֵ����4,8,12,16

*/
template <size_t key_size, size_t round_size>
class CAST5_ECB : public CAST_ECB_Base < round_size >
{
public:

    //Ϊ�˷���ZCE_Crypt,�������KEY���ͣ�
    typedef typename CAST_ECB_Base<round_size>::CAST_SUBKEY  SUBKEY_STRUCT;

    //����ԭʼ��Կ�������㷨����Ҫ����Կ
    static void key_setup(const unsigned char *key,
                          SUBKEY_STRUCT *sub_key,
                          bool  /*if_encrypt*/ )
    {
        uint32_t x[4], z[4];
        uint32_t *mkey_ptr = sub_key->mkey_;
        uint8_t *rkey_ptr = sub_key->rkey_;
        x[0] = ZINDEX_TO_LEUINT32(key, 0);
        x[1] = ZINDEX_TO_LEUINT32(key, 1);
        x[2] = 0;
        x[3] = 0;
        //���ݲ�ͬ��KEY SIZE ���д���
        if (12 == key_size || 16 == key_size  )
        {
            x[2] = ZINDEX_TO_LEUINT32(key, 2);
            if (16 == key_size )
            {
                x[3] = ZINDEX_TO_LEUINT32(key, 3);
            }
        }
        size_t i = 0;

#define CAST5_GB(x, i) (((x[(15-i)>>2])>>(uint32_t)(8*((15-i)&3)))&255)

        //��һ·����skey��
        z[3] = x[3] ^ CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(x, 0xD)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(x, 0xF)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(x, 0xC)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(x, 0xE)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(x, 0x8)];
        z[2] = x[1] ^ CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(z, 0x0)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(z, 0x2)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(z, 0x1)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(z, 0x3)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(x, 0xA)];
        z[1] = x[0] ^ CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(z, 0x7)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(z, 0x6)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(z, 0x5)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(z, 0x4)] ^ CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(x, 0x9)];
        z[0] = x[2] ^ CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(z, 0xA)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(z, 0x9)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(z, 0xb)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(z, 0x8)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(x, 0xB)];
        mkey_ptr[i++] = CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(z, 0x8)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(z, 0x9)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(z, 0x7)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(z, 0x6)] ^ CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(z, 0x2)];
        mkey_ptr[i++] = CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(z, 0xA)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(z, 0xB)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(z, 0x5)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(z, 0x4)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(z, 0x6)];
        mkey_ptr[i++] = CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(z, 0xC)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(z, 0xd)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(z, 0x3)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(z, 0x2)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(z, 0x9)];
        mkey_ptr[i++] = CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(z, 0xE)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(z, 0xF)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(z, 0x1)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(z, 0x0)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(z, 0xc)];

        if (round_size > 4)
        {
            x[3] = z[1] ^ CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(z, 0x5)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(z, 0x7)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(z, 0x4)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(z, 0x6)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(z, 0x0)];
            x[2] = z[3] ^ CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(x, 0x0)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(x, 0x2)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(x, 0x1)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(x, 0x3)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(z, 0x2)];
            x[1] = z[2] ^ CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(x, 0x7)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(x, 0x6)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(x, 0x5)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(x, 0x4)] ^ CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(z, 0x1)];
            x[0] = z[0] ^ CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(x, 0xA)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(x, 0x9)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(x, 0xb)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(x, 0x8)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(z, 0x3)];
            mkey_ptr[i++] = CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(x, 0x3)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(x, 0x2)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(x, 0xc)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(x, 0xd)] ^ CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(x, 0x8)];
            mkey_ptr[i++] = CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(x, 0x1)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(x, 0x0)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(x, 0xe)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(x, 0xf)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(x, 0xd)];
            mkey_ptr[i++] = CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(x, 0x7)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(x, 0x6)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(x, 0x8)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(x, 0x9)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(x, 0x3)];
            mkey_ptr[i++] = CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(x, 0x5)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(x, 0x4)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(x, 0xa)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(x, 0xb)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(x, 0x7)];
        }
        if (round_size > 8)
        {
            z[3] = x[3] ^ CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(x, 0xD)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(x, 0xF)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(x, 0xC)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(x, 0xE)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(x, 0x8)];
            z[2] = x[1] ^ CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(z, 0x0)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(z, 0x2)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(z, 0x1)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(z, 0x3)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(x, 0xA)];
            z[1] = x[0] ^ CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(z, 0x7)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(z, 0x6)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(z, 0x5)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(z, 0x4)] ^ CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(x, 0x9)];
            z[0] = x[2] ^ CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(z, 0xA)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(z, 0x9)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(z, 0xb)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(z, 0x8)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(x, 0xB)];
            mkey_ptr[i++] = CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(z, 0x3)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(z, 0x2)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(z, 0xc)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(z, 0xd)] ^ CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(z, 0x9)];
            mkey_ptr[i++] = CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(z, 0x1)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(z, 0x0)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(z, 0xe)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(z, 0xf)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(z, 0xc)];
            mkey_ptr[i++] = CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(z, 0x7)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(z, 0x6)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(z, 0x8)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(z, 0x9)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(z, 0x2)];
            mkey_ptr[i++] = CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(z, 0x5)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(z, 0x4)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(z, 0xa)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(z, 0xb)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(z, 0x6)];
        }
        if (round_size > 12)
        {
            x[3] = z[1] ^ CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(z, 0x5)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(z, 0x7)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(z, 0x4)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(z, 0x6)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(z, 0x0)];
            x[2] = z[3] ^ CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(x, 0x0)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(x, 0x2)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(x, 0x1)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(x, 0x3)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(z, 0x2)];
            x[1] = z[2] ^ CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(x, 0x7)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(x, 0x6)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(x, 0x5)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(x, 0x4)] ^ CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(z, 0x1)];
            x[0] = z[0] ^ CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(x, 0xA)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(x, 0x9)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(x, 0xb)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(x, 0x8)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(z, 0x3)];
            mkey_ptr[i++] = CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(x, 0x8)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(x, 0x9)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(x, 0x7)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(x, 0x6)] ^ CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(x, 0x3)];
            mkey_ptr[i++] = CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(x, 0xa)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(x, 0xb)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(x, 0x5)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(x, 0x4)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(x, 0x7)];
            mkey_ptr[i++] = CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(x, 0xc)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(x, 0xd)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(x, 0x3)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(x, 0x2)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(x, 0x8)];
            mkey_ptr[i++] = CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(x, 0xe)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(x, 0xf)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(x, 0x1)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(x, 0x0)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(x, 0xd)];
        }

        //�ڶ��ּ���rkey����ת�ĳ���
        i = 0;
        z[3] = x[3] ^ CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(x, 0xD)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(x, 0xF)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(x, 0xC)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(x, 0xE)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(x, 0x8)];
        z[2] = x[1] ^ CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(z, 0x0)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(z, 0x2)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(z, 0x1)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(z, 0x3)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(x, 0xA)];
        z[1] = x[0] ^ CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(z, 0x7)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(z, 0x6)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(z, 0x5)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(z, 0x4)] ^ CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(x, 0x9)];
        z[0] = x[2] ^ CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(z, 0xA)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(z, 0x9)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(z, 0xb)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(z, 0x8)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(x, 0xB)];
        rkey_ptr[i++] = (CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(z, 0x8)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(z, 0x9)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(z, 0x7)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(z, 0x6)] ^ CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(z, 0x2)]) & 0xFF;
        rkey_ptr[i++] = (CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(z, 0xA)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(z, 0xB)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(z, 0x5)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(z, 0x4)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(z, 0x6)]) & 0xFF;
        rkey_ptr[i++] = (CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(z, 0xC)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(z, 0xd)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(z, 0x3)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(z, 0x2)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(z, 0x9)]) & 0xFF;
        rkey_ptr[i++] = (CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(z, 0xE)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(z, 0xF)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(z, 0x1)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(z, 0x0)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(z, 0xc)]) & 0xFF;

        if (round_size > 4)
        {
            x[3] = z[1] ^ CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(z, 0x5)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(z, 0x7)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(z, 0x4)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(z, 0x6)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(z, 0x0)];
            x[2] = z[3] ^ CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(x, 0x0)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(x, 0x2)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(x, 0x1)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(x, 0x3)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(z, 0x2)];
            x[1] = z[2] ^ CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(x, 0x7)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(x, 0x6)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(x, 0x5)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(x, 0x4)] ^ CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(z, 0x1)];
            x[0] = z[0] ^ CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(x, 0xA)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(x, 0x9)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(x, 0xb)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(x, 0x8)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(z, 0x3)];
            rkey_ptr[i++] = (CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(x, 0x3)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(x, 0x2)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(x, 0xc)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(x, 0xd)] ^ CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(x, 0x8)]) & 0xFF;
            rkey_ptr[i++] = (CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(x, 0x1)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(x, 0x0)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(x, 0xe)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(x, 0xf)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(x, 0xd)]) & 0xFF;
            rkey_ptr[i++] = (CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(x, 0x7)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(x, 0x6)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(x, 0x8)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(x, 0x9)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(x, 0x3)]) & 0xFF;
            rkey_ptr[i++] = (CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(x, 0x5)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(x, 0x4)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(x, 0xa)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(x, 0xb)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(x, 0x7)]) & 0xFF;
        }
        if (round_size > 8)
        {
            z[3] = x[3] ^ CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(x, 0xD)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(x, 0xF)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(x, 0xC)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(x, 0xE)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(x, 0x8)];
            z[2] = x[1] ^ CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(z, 0x0)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(z, 0x2)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(z, 0x1)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(z, 0x3)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(x, 0xA)];
            z[1] = x[0] ^ CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(z, 0x7)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(z, 0x6)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(z, 0x5)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(z, 0x4)] ^ CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(x, 0x9)];
            z[0] = x[2] ^ CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(z, 0xA)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(z, 0x9)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(z, 0xb)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(z, 0x8)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(x, 0xB)];
            rkey_ptr[i++] = (CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(z, 0x3)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(z, 0x2)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(z, 0xc)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(z, 0xd)] ^ CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(z, 0x9)]) & 0xFF;
            rkey_ptr[i++] = (CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(z, 0x1)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(z, 0x0)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(z, 0xe)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(z, 0xf)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(z, 0xc)]) & 0xFF;
            rkey_ptr[i++] = (CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(z, 0x7)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(z, 0x6)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(z, 0x8)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(z, 0x9)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(z, 0x2)]) & 0xFF;
            rkey_ptr[i++] = (CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(z, 0x5)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(z, 0x4)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(z, 0xa)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(z, 0xb)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(z, 0x6)]) & 0xFF;
        }
        if (round_size > 12)
        {
            x[3] = z[1] ^ CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(z, 0x5)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(z, 0x7)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(z, 0x4)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(z, 0x6)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(z, 0x0)];
            x[2] = z[3] ^ CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(x, 0x0)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(x, 0x2)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(x, 0x1)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(x, 0x3)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(z, 0x2)];
            x[1] = z[2] ^ CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(x, 0x7)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(x, 0x6)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(x, 0x5)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(x, 0x4)] ^ CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(z, 0x1)];
            x[0] = z[0] ^ CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(x, 0xA)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(x, 0x9)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(x, 0xb)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(x, 0x8)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(z, 0x3)];
            rkey_ptr[i++] = (CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(x, 0x8)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(x, 0x9)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(x, 0x7)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(x, 0x6)] ^ CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(x, 0x3)]) & 0xFF;
            rkey_ptr[i++] = (CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(x, 0xa)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(x, 0xb)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(x, 0x5)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(x, 0x4)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(x, 0x7)]) & 0xFF;
            rkey_ptr[i++] = (CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(x, 0xc)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(x, 0xd)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(x, 0x3)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(x, 0x2)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(x, 0x8)]) & 0xFF;
            rkey_ptr[i++] = (CAST_SBOX_Define::CAST_SBOX[4][CAST5_GB(x, 0xe)] ^ CAST_SBOX_Define::CAST_SBOX[5][CAST5_GB(x, 0xf)] ^ CAST_SBOX_Define::CAST_SBOX[6][CAST5_GB(x, 0x1)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(x, 0x0)] ^ CAST_SBOX_Define::CAST_SBOX[7][CAST5_GB(x, 0xd)]) & 0xFF;
        }
#undef CAST5_GB
    }

    //���ܺ�����CAST5��һ�㽨����Կ>80bits,���Դ���16��
    static void ecb_encrypt(const SUBKEY_STRUCT *sub_key,
                            const unsigned char *src_block,
                            unsigned char *cipher_block)
    {
        const uint32_t *mkey_ptr = sub_key->mkey_;
        const uint8_t *rkey_ptr = sub_key->rkey_;
        uint32_t t = 0;
        uint32_t l = ZINDEX_TO_LEUINT32(src_block, 0);
        uint32_t r = ZINDEX_TO_LEUINT32(src_block, 1);

        CAST_F1(l, r,  mkey_ptr[0], rkey_ptr[0]);
        CAST_F2(r, l,  mkey_ptr[1], rkey_ptr[1]);
        CAST_F3(l, r,  mkey_ptr[2], rkey_ptr[2]);
        CAST_F1(r, l,  mkey_ptr[3], rkey_ptr[3]);

        if (round_size > 4 )
        {
            CAST_F2(l, r,  mkey_ptr[4], rkey_ptr[4]);
            CAST_F3(r, l,  mkey_ptr[5], rkey_ptr[5]);
            CAST_F1(l, r,  mkey_ptr[6], rkey_ptr[6]);
            CAST_F2(r, l,  mkey_ptr[7], rkey_ptr[7]);
        }
        if (round_size > 8 )
        {
            CAST_F3(l, r,  mkey_ptr[8], rkey_ptr[8]);
            CAST_F1(r, l,  mkey_ptr[9], rkey_ptr[9]);
            CAST_F2(l, r,  mkey_ptr[10], rkey_ptr[10]);
            CAST_F3(r, l,  mkey_ptr[11], rkey_ptr[11]);
        }
        //���Ҫ����16�ִ���
        if (round_size > 12)
        {
            CAST_F1(l, r, mkey_ptr[12], rkey_ptr[12]);
            CAST_F2(r, l, mkey_ptr[13], rkey_ptr[13]);
            CAST_F3(l, r, mkey_ptr[14], rkey_ptr[14]);
            CAST_F1(r, l, mkey_ptr[15], rkey_ptr[15]);
        }

        //ע�����˳��������ȡ˳���෴
        ZLEUINT32_TO_INDEX(cipher_block, 0, r);
        ZLEUINT32_TO_INDEX(cipher_block, 1, l);
    }

    //���ܺ�������Կ>80bits,���Դ���16��
    static void ecb_decrypt(const SUBKEY_STRUCT *sub_key,
                            const unsigned char *cipher_block,
                            unsigned char *src_block)
    {
        const uint32_t *mkey_ptr = sub_key->mkey_;
        const uint8_t *rkey_ptr = sub_key->rkey_;
        uint32_t t = 0;
        uint32_t r = ZINDEX_TO_LEUINT32(cipher_block, 0);
        uint32_t l = ZINDEX_TO_LEUINT32(cipher_block, 1);

        //���Ҫ����16�ִ���
        if (round_size > 12)
        {
            CAST_F1(r, l, mkey_ptr[15], rkey_ptr[15]);
            CAST_F3(l, r, mkey_ptr[14], rkey_ptr[14]);
            CAST_F2(r, l, mkey_ptr[13], rkey_ptr[13]);
            CAST_F1(l, r, mkey_ptr[12], rkey_ptr[12]);
        }
        if (round_size > 8 )
        {
            CAST_F3(r, l, mkey_ptr[11], rkey_ptr[11]);
            CAST_F2(l, r, mkey_ptr[10], rkey_ptr[10]);
            CAST_F1(r, l, mkey_ptr[9], rkey_ptr[9]);
            CAST_F3(l, r, mkey_ptr[8], rkey_ptr[8]);
        }
        if (round_size > 4)
        {
            CAST_F2(r, l,  mkey_ptr[7], rkey_ptr[7]);
            CAST_F1(l, r,  mkey_ptr[6], rkey_ptr[6]);
            CAST_F3(r, l,  mkey_ptr[5], rkey_ptr[5]);
            CAST_F2(l, r,  mkey_ptr[4], rkey_ptr[4]);
        }
        CAST_F1(r, l,  mkey_ptr[3], rkey_ptr[3]);
        CAST_F3(l, r,  mkey_ptr[2], rkey_ptr[2]);
        CAST_F2(r, l,  mkey_ptr[1], rkey_ptr[1]);
        CAST_F1(l, r,  mkey_ptr[0], rkey_ptr[0]);

        //ע�����˳��������ȡ˳���෴
        ZLEUINT32_TO_INDEX(src_block, 0, l);
        ZLEUINT32_TO_INDEX(src_block, 1, r);

    }

public:
    //
    const static size_t BLOCK_SIZE = 8;
    //��Կ���ȣ������ֵ����8��64bits����12��96bits����16��128bits��
    const static size_t KEY_SIZE   = key_size;
};

//��һ����������Կ���ȣ��ڶ��������Ǽ���������������Ǽ���Ч�����Ƽ�CAST5_Crypt_16_16_8
//typedef����ԭ���ǣ������㷨���ƣ��㷨������BLOCK���ȣ�key���ȣ�����(�Ƽ�������������key������һ����ϵ)
//ע����Կ���������8��
typedef ZCE_Crypt<CAST5_ECB<8, 12>  >  CAST5_Crypt_8_8_12;
typedef ZCE_Crypt<CAST5_ECB<12, 16> >  CAST5_Crypt_8_12_16;
typedef ZCE_Crypt<CAST5_ECB<16, 8>  >  CAST5_Crypt_8_16_8;
typedef ZCE_Crypt<CAST5_ECB<16, 12> >  CAST5_Crypt_8_16_12;
typedef ZCE_Crypt<CAST5_ECB<16, 16> >  CAST5_Crypt_8_16_16;

/*!
@brief      CAST6 �ֱ���ΪCAST256��Ҳ��AES�ı�ѡ������
            һ���Ƽ���BLOCK64bit������48��,CAST6�������ǹ̶���48��
            ��Ҳ��̫ȷ���Ƿ���Լ��٣����㷨�Ͽ�Ӧ�ÿ��ԣ���48���������6*4������6*4�ķ���
            �е�˵����
            CAST6����Կ���� 128, 160, 192, 224 or 256 bit
@tparam     key_size   ��Կ���ȣ������ֵ����16��128bits��,20,24,28,32
@tparam     round_size ���ܵ������������֧��12��24.36��48��
*/
template <size_t key_size, size_t round_size>
class CAST6_ECB :  public CAST_ECB_Base < round_size >
{

public:

    //Ϊ�˷���ZCE_Crypt,�������KEY���ͣ�
    typedef typename CAST_ECB_Base<round_size>::CAST_SUBKEY  SUBKEY_STRUCT;

    //����ԭʼ��Կ�������㷨����Ҫ����Կ
    static void key_setup(const unsigned char *key,
                          SUBKEY_STRUCT *sub_key,
                          bool  /*if_encrypt*/ )
    {

        uint32_t x[8], t = 0;
        uint32_t *mkey_ptr = sub_key->mkey_;
        uint8_t *rkey_ptr = sub_key->rkey_;

        x[0] = ZINDEX_TO_LEUINT32(key, 0);
        x[1] = ZINDEX_TO_LEUINT32(key, 1);
        x[2] = ZINDEX_TO_LEUINT32(key, 2);
        x[3] = ZINDEX_TO_LEUINT32(key, 3);
        x[4] = x[5] = x[6] = x[7] = 0;

        for (size_t j = 4; j < key_size / sizeof( uint32_t); ++j)
        {
            x[j] = ZINDEX_TO_LEUINT32(key, j);
        }

        for (size_t j = 0; j < round_size; j += 4)
        {
            CAST_F1(x[6], x[7], CAST_SBOX_Define::CAST6_KEY_MASK[4 * j + 0], CAST_SBOX_Define::CAST6_KEY_ROT[(4 * j + 0) & 31]);
            CAST_F2(x[5], x[6], CAST_SBOX_Define::CAST6_KEY_MASK[4 * j + 1], CAST_SBOX_Define::CAST6_KEY_ROT[(4 * j + 1) & 31]);
            CAST_F3(x[4], x[5], CAST_SBOX_Define::CAST6_KEY_MASK[4 * j + 2], CAST_SBOX_Define::CAST6_KEY_ROT[(4 * j + 2) & 31]);
            CAST_F1(x[3], x[4], CAST_SBOX_Define::CAST6_KEY_MASK[4 * j + 3], CAST_SBOX_Define::CAST6_KEY_ROT[(4 * j + 3) & 31]);
            CAST_F2(x[2], x[3], CAST_SBOX_Define::CAST6_KEY_MASK[4 * j + 4], CAST_SBOX_Define::CAST6_KEY_ROT[(4 * j + 4) & 31]);
            CAST_F3(x[1], x[2], CAST_SBOX_Define::CAST6_KEY_MASK[4 * j + 5], CAST_SBOX_Define::CAST6_KEY_ROT[(4 * j + 5) & 31]);
            CAST_F1(x[0], x[1], CAST_SBOX_Define::CAST6_KEY_MASK[4 * j + 6], CAST_SBOX_Define::CAST6_KEY_ROT[(4 * j + 6) & 31]);
            CAST_F2(x[7], x[0], CAST_SBOX_Define::CAST6_KEY_MASK[4 * j + 7], CAST_SBOX_Define::CAST6_KEY_ROT[(4 * j + 7) & 31]);
            CAST_F1(x[6], x[7], CAST_SBOX_Define::CAST6_KEY_MASK[4 * j + 8], CAST_SBOX_Define::CAST6_KEY_ROT[(4 * j + 8) & 31]);
            CAST_F2(x[5], x[6], CAST_SBOX_Define::CAST6_KEY_MASK[4 * j + 9], CAST_SBOX_Define::CAST6_KEY_ROT[(4 * j + 9) & 31]);
            CAST_F3(x[4], x[5], CAST_SBOX_Define::CAST6_KEY_MASK[4 * j + 10], CAST_SBOX_Define::CAST6_KEY_ROT[(4 * j + 10) & 31]);
            CAST_F1(x[3], x[4], CAST_SBOX_Define::CAST6_KEY_MASK[4 * j + 11], CAST_SBOX_Define::CAST6_KEY_ROT[(4 * j + 11) & 31]);
            CAST_F2(x[2], x[3], CAST_SBOX_Define::CAST6_KEY_MASK[4 * j + 12], CAST_SBOX_Define::CAST6_KEY_ROT[(4 * j + 12) & 31]);
            CAST_F3(x[1], x[2], CAST_SBOX_Define::CAST6_KEY_MASK[4 * j + 13], CAST_SBOX_Define::CAST6_KEY_ROT[(4 * j + 13) & 31]);
            CAST_F1(x[0], x[1], CAST_SBOX_Define::CAST6_KEY_MASK[4 * j + 14], CAST_SBOX_Define::CAST6_KEY_ROT[(4 * j + 14) & 31]);
            CAST_F2(x[7], x[0], CAST_SBOX_Define::CAST6_KEY_MASK[4 * j + 15], CAST_SBOX_Define::CAST6_KEY_ROT[(4 * j + 15) & 31]);

            rkey_ptr[j  ] = (x[0]) & 0xFF;
            rkey_ptr[j + 1] = (x[2]) & 0xFF;
            rkey_ptr[j + 2] = (x[4]) & 0xFF;
            rkey_ptr[j + 3] = (x[6]) & 0xFF;

            mkey_ptr[j  ] = x[7];
            mkey_ptr[j + 1] = x[5];
            mkey_ptr[j + 2] = x[3];
            mkey_ptr[j + 3] = x[1];
        }
    }

    //CAST6���ܺ���
    static void ecb_encrypt(const SUBKEY_STRUCT *sub_key,
                            const unsigned char *src_block,
                            unsigned char *cipher_block)
    {

        const uint32_t *mkey_ptr = sub_key->mkey_;
        const uint8_t *rkey_ptr = sub_key->rkey_;
        uint32_t t = 0;

        uint32_t a = ZINDEX_TO_LEUINT32(src_block, 0);
        uint32_t b = ZINDEX_TO_LEUINT32(src_block, 1);
        uint32_t c = ZINDEX_TO_LEUINT32(src_block, 2);
        uint32_t d = ZINDEX_TO_LEUINT32(src_block, 3);

        //48�ִ���
        //����Qi
        CAST_F1(c, d, mkey_ptr[ 0], rkey_ptr[ 0]);
        CAST_F2(b, c, mkey_ptr[ 1], rkey_ptr[ 1]);
        CAST_F3(a, b, mkey_ptr[ 2], rkey_ptr[ 2]);
        CAST_F1(d, a, mkey_ptr[ 3], rkey_ptr[ 3]);
        CAST_F1(c, d, mkey_ptr[ 4], rkey_ptr[ 4]);
        CAST_F2(b, c, mkey_ptr[ 5], rkey_ptr[ 5]);
        CAST_F3(a, b, mkey_ptr[ 6], rkey_ptr[ 6]);
        CAST_F1(d, a, mkey_ptr[ 7], rkey_ptr[ 7]);
        CAST_F1(c, d, mkey_ptr[ 8], rkey_ptr[ 8]);
        CAST_F2(b, c, mkey_ptr[ 9], rkey_ptr[ 9]);
        CAST_F3(a, b, mkey_ptr[10], rkey_ptr[10]);
        CAST_F1(d, a, mkey_ptr[11], rkey_ptr[11]);
        if (round_size > 12 )
        {
            CAST_F1(c, d, mkey_ptr[12], rkey_ptr[12]);
            CAST_F2(b, c, mkey_ptr[13], rkey_ptr[13]);
            CAST_F3(a, b, mkey_ptr[14], rkey_ptr[14]);
            CAST_F1(d, a, mkey_ptr[15], rkey_ptr[15]);
            CAST_F1(c, d, mkey_ptr[16], rkey_ptr[16]);
            CAST_F2(b, c, mkey_ptr[17], rkey_ptr[17]);
            CAST_F3(a, b, mkey_ptr[18], rkey_ptr[18]);
            CAST_F1(d, a, mkey_ptr[19], rkey_ptr[19]);
            CAST_F1(c, d, mkey_ptr[20], rkey_ptr[20]);
            CAST_F2(b, c, mkey_ptr[21], rkey_ptr[21]);
            CAST_F3(a, b, mkey_ptr[22], rkey_ptr[22]);
            CAST_F1(d, a, mkey_ptr[23], rkey_ptr[23]);
        }
        //����QBARi
        if (round_size > 24)
        {
            CAST_F1(d, a, mkey_ptr[27], rkey_ptr[27]);
            CAST_F3(a, b, mkey_ptr[26], rkey_ptr[26]);
            CAST_F2(b, c, mkey_ptr[25], rkey_ptr[25]);
            CAST_F1(c, d, mkey_ptr[24], rkey_ptr[24]);
            CAST_F1(d, a, mkey_ptr[31], rkey_ptr[31]);
            CAST_F3(a, b, mkey_ptr[30], rkey_ptr[30]);
            CAST_F2(b, c, mkey_ptr[29], rkey_ptr[29]);
            CAST_F1(c, d, mkey_ptr[28], rkey_ptr[28]);
            CAST_F1(d, a, mkey_ptr[35], rkey_ptr[35]);
            CAST_F3(a, b, mkey_ptr[34], rkey_ptr[34]);
            CAST_F2(b, c, mkey_ptr[33], rkey_ptr[33]);
            CAST_F1(c, d, mkey_ptr[32], rkey_ptr[32]);
        }
        if (round_size > 36)
        {
            CAST_F1(d, a, mkey_ptr[39], rkey_ptr[39]);
            CAST_F3(a, b, mkey_ptr[38], rkey_ptr[38]);
            CAST_F2(b, c, mkey_ptr[37], rkey_ptr[37]);
            CAST_F1(c, d, mkey_ptr[36], rkey_ptr[36]);
            CAST_F1(d, a, mkey_ptr[43], rkey_ptr[43]);
            CAST_F3(a, b, mkey_ptr[42], rkey_ptr[42]);
            CAST_F2(b, c, mkey_ptr[41], rkey_ptr[41]);
            CAST_F1(c, d, mkey_ptr[40], rkey_ptr[40]);
            CAST_F1(d, a, mkey_ptr[47], rkey_ptr[47]);
            CAST_F3(a, b, mkey_ptr[46], rkey_ptr[46]);
            CAST_F2(b, c, mkey_ptr[45], rkey_ptr[45]);
            CAST_F1(c, d, mkey_ptr[44], rkey_ptr[44]);
        }

        ZLEUINT32_TO_INDEX(cipher_block, 0, a);
        ZLEUINT32_TO_INDEX(cipher_block, 1, b);
        ZLEUINT32_TO_INDEX(cipher_block, 2, c);
        ZLEUINT32_TO_INDEX(cipher_block, 3, d);

    }
    //CAST6���ܺ���
    static void ecb_decrypt(const SUBKEY_STRUCT *sub_key,
                            const unsigned char *cipher_block,
                            unsigned char *src_block)
    {
        const uint32_t *mkey_ptr = sub_key->mkey_;
        const uint8_t *rkey_ptr = sub_key->rkey_;
        uint32_t t = 0;

        uint32_t a = ZINDEX_TO_LEUINT32(cipher_block, 0);
        uint32_t b = ZINDEX_TO_LEUINT32(cipher_block, 1);
        uint32_t c = ZINDEX_TO_LEUINT32(cipher_block, 2);
        uint32_t d = ZINDEX_TO_LEUINT32(cipher_block, 3);

        //48�ִ���
        //����QBARi
        if (round_size > 36 )
        {
            CAST_F1(c, d, mkey_ptr[44], rkey_ptr[44]);
            CAST_F2(b, c, mkey_ptr[45], rkey_ptr[45]);
            CAST_F3(a, b, mkey_ptr[46], rkey_ptr[46]);
            CAST_F1(d, a, mkey_ptr[47], rkey_ptr[47]);
            CAST_F1(c, d, mkey_ptr[40], rkey_ptr[40]);
            CAST_F2(b, c, mkey_ptr[41], rkey_ptr[41]);
            CAST_F3(a, b, mkey_ptr[42], rkey_ptr[42]);
            CAST_F1(d, a, mkey_ptr[43], rkey_ptr[43]);
            CAST_F1(c, d, mkey_ptr[36], rkey_ptr[36]);
            CAST_F2(b, c, mkey_ptr[37], rkey_ptr[37]);
            CAST_F3(a, b, mkey_ptr[38], rkey_ptr[38]);
            CAST_F1(d, a, mkey_ptr[39], rkey_ptr[39]);
        }
        if (round_size > 24 )
        {
            CAST_F1(c, d, mkey_ptr[32], rkey_ptr[32]);
            CAST_F2(b, c, mkey_ptr[33], rkey_ptr[33]);
            CAST_F3(a, b, mkey_ptr[34], rkey_ptr[34]);
            CAST_F1(d, a, mkey_ptr[35], rkey_ptr[35]);
            CAST_F1(c, d, mkey_ptr[28], rkey_ptr[28]);
            CAST_F2(b, c, mkey_ptr[29], rkey_ptr[29]);
            CAST_F3(a, b, mkey_ptr[30], rkey_ptr[30]);
            CAST_F1(d, a, mkey_ptr[31], rkey_ptr[31]);
            CAST_F1(c, d, mkey_ptr[24], rkey_ptr[24]);
            CAST_F2(b, c, mkey_ptr[25], rkey_ptr[25]);
            CAST_F3(a, b, mkey_ptr[26], rkey_ptr[26]);
            CAST_F1(d, a, mkey_ptr[27], rkey_ptr[27]);
        }
        //����Qi
        if (round_size > 12 )
        {
            CAST_F1(d, a, mkey_ptr[23], rkey_ptr[23]);
            CAST_F3(a, b, mkey_ptr[22], rkey_ptr[22]);
            CAST_F2(b, c, mkey_ptr[21], rkey_ptr[21]);
            CAST_F1(c, d, mkey_ptr[20], rkey_ptr[20]);
            CAST_F1(d, a, mkey_ptr[19], rkey_ptr[19]);
            CAST_F3(a, b, mkey_ptr[18], rkey_ptr[18]);
            CAST_F2(b, c, mkey_ptr[17], rkey_ptr[17]);
            CAST_F1(c, d, mkey_ptr[16], rkey_ptr[16]);
            CAST_F1(d, a, mkey_ptr[15], rkey_ptr[15]);
            CAST_F3(a, b, mkey_ptr[14], rkey_ptr[14]);
            CAST_F2(b, c, mkey_ptr[13], rkey_ptr[13]);
            CAST_F1(c, d, mkey_ptr[12], rkey_ptr[12]);
        }
        CAST_F1(d, a, mkey_ptr[11], rkey_ptr[11]);
        CAST_F3(a, b, mkey_ptr[10], rkey_ptr[10]);
        CAST_F2(b, c, mkey_ptr[ 9], rkey_ptr[ 9]);
        CAST_F1(c, d, mkey_ptr[ 8], rkey_ptr[ 8]);
        CAST_F1(d, a, mkey_ptr[ 7], rkey_ptr[ 7]);
        CAST_F3(a, b, mkey_ptr[ 6], rkey_ptr[ 6]);
        CAST_F2(b, c, mkey_ptr[ 5], rkey_ptr[ 5]);
        CAST_F1(c, d, mkey_ptr[ 4], rkey_ptr[ 4]);
        CAST_F1(d, a, mkey_ptr[ 3], rkey_ptr[ 3]);
        CAST_F3(a, b, mkey_ptr[ 2], rkey_ptr[ 2]);
        CAST_F2(b, c, mkey_ptr[ 1], rkey_ptr[ 1]);
        CAST_F1(c, d, mkey_ptr[ 0], rkey_ptr[ 0]);

        ZLEUINT32_TO_INDEX(src_block, 0, a);
        ZLEUINT32_TO_INDEX(src_block, 1, b);
        ZLEUINT32_TO_INDEX(src_block, 2, c);
        ZLEUINT32_TO_INDEX(src_block, 3, d);
    }

public:
    //
    const static size_t BLOCK_SIZE = 16;
    //
    const static size_t KEY_SIZE   = key_size;
};

#undef CAST_F1
#undef CAST_F2
#undef CAST_F3

//��һ����������Կ���ȣ��ڶ��������Ǽ���������������Ǽ���Ч����48�ֵĶ�ֵ���Ƽ�
//typedef����ԭ���ǣ������㷨���ƣ��㷨������BLOCK���ȣ�key���ȣ�����(�Ƽ�������������key������һ����ϵ)
typedef ZCE_Crypt<CAST6_ECB<16, 12> >  CAST6_Crypt_16_16_12;
typedef ZCE_Crypt<CAST6_ECB<16, 24> >  CAST6_Crypt_16_16_24;
typedef ZCE_Crypt<CAST6_ECB<16, 36> >  CAST6_Crypt_16_16_36;
typedef ZCE_Crypt<CAST6_ECB<16, 48> >  CAST6_Crypt_16_16_48;
typedef ZCE_Crypt<CAST6_ECB<20, 48> >  CAST6_Crypt_16_20_48;
typedef ZCE_Crypt<CAST6_ECB<24, 48> >  CAST6_Crypt_16_24_48;
typedef ZCE_Crypt<CAST6_ECB<28, 48> >  CAST6_Crypt_16_28_48;
typedef ZCE_Crypt<CAST6_ECB<32, 48> >  CAST6_Crypt_16_32_48;

//=================================================================================================================
//MARS�㷨��Ķ���
class MARS_ECB_Define
{
protected:
    //
    static const uint32_t  MARS_S_BOX[512];
    //
    static const uint32_t  MARS_IM1[15];
    //
    static const uint32_t  MARS_IM2[15];
    //
    static const uint32_t  MARS_IM7[15];
    //
    static const uint32_t  MARS_I4M[15];
    //
    static const uint32_t  MARS_B_TAB[4];

};

/*!
@brief      MARS�����㷨ʵ��
            http://en.wikipedia.org/wiki/MARS_%28cryptography%29
@tparam     key_size KEY�ĳ��ȣ�������16�ֽڣ�128bits�� - 56�ֽ� ��448bits��ÿ������4�ֽڣ�
@note       �������㷨��һ���ĵط�
            MARS has a heterogeneous structure: several rounds of a cryptographic
            core are "jacketed" by unkeyed mixing rounds, together with key whitening.
*/
template <size_t key_size>
class MARS_ECB : public MARS_ECB_Define
{
public:

    struct MARS_SUBKEY
    {

        uint32_t  ll_key_[40];
    };

    typedef MARS_SUBKEY  SUBKEY_STRUCT;

    static void key_setup(const unsigned char *key,
                          SUBKEY_STRUCT *sub_key,
                          bool  /*if_encrypt*/)
    {

        uint32_t t_key[16];
        uint32_t *ll_key = sub_key->ll_key_;

        uint32_t key_word_num = key_size / sizeof(uint32_t);
        for (size_t i = 0; i < key_word_num; ++i)
        {
            t_key[i] = ZINDEX_TO_LEUINT32(key, i);
        }
        //��дKEY����
        t_key[key_word_num] = key_word_num;
        //��д0
        for (size_t i = key_word_num + 1; i < 15; ++i)
        {
            t_key[i] = 0;
        }

        for (size_t i = 0; i < 4; ++i)
        {
            for (size_t j = 0; j < 15; ++j)
            {
                t_key[j] ^= ZCE_ROTL32(t_key[MARS_IM7[j]] ^ t_key[MARS_IM2[j]], 3) ^ (4 * j + i);
            }
            for (size_t m = 0; m < 4; ++m)
            {
                for (size_t j = 0; j < 15; ++j)
                {
                    t_key[j] = ZCE_ROTL32(t_key[j] + MARS_S_BOX[t_key[MARS_IM1[j]] & 511], 9);
                }
            }
            for (size_t j = 0; j < 10; ++j)
            {
                ll_key[10 * i + j] = t_key[MARS_I4M[j]];
            }
        }

        uint32_t x = 0;
        uint32_t y = 0;
        for (size_t i = 5; i < 37; i += 2)
        {
            x = ll_key[i] | 3;
            y = (~x ^ (x >> 1)) & 0x7fffffff;
            y &= (y >> 1) & (y >> 2);
            y &= (y >> 3) & (y >> 6);

            if (y)
            {
                y <<= 1;
                y |= (y << 1);
                y |= (y << 2);
                y |= (y << 4);
                y &= 0xfffffffc;
                x ^= (ZCE_ROTL32(MARS_B_TAB[ll_key[i] & 3], ll_key[i - 1]) & y);
            }

            ll_key[i] = x;
        }
    }

#define MARS_F_MIX(a,b,c,d)           \
    r = ZCE_ROTR32(a, 8);             \
    b ^= MARS_S_BOX[a & 255];         \
    b += MARS_S_BOX[(r & 255) + 256]; \
    r = ZCE_ROTR32(a, 16);            \
    a = ZCE_ROTR32(a, 24);            \
    c += MARS_S_BOX[r & 255];         \
    d ^= MARS_S_BOX[(a & 255) + 256]

#define MARS_B_MIX(a,b,c,d)           \
    r = ZCE_ROTL32(a, 8);             \
    b ^= MARS_S_BOX[(a & 255) + 256]; \
    c -= MARS_S_BOX[r & 255];         \
    r = ZCE_ROTL32(a, 16);            \
    a  = ZCE_ROTL32(a, 24);           \
    d -= MARS_S_BOX[(r & 255) + 256]; \
    d ^= MARS_S_BOX[a & 255]

#define MARS_F_KTR(a,b,c,d,i)        \
    m = a + ll_key[i];               \
    a = ZCE_ROTL32(a, 13);           \
    r = a * ll_key[i + 1];           \
    l = MARS_S_BOX[m & 511];         \
    r = ZCE_ROTL32(r, 5);            \
    c += ZCE_ROTL32(m, r);           \
    l ^= r;                          \
    r = ZCE_ROTL32(r, 5);            \
    l ^= r;                          \
    d ^= r;                          \
    b += ZCE_ROTL32(l, r)

#define MARS_R_KTR(a,b,c,d,i)        \
    r = a * ll_key[i + 1];           \
    a = ZCE_ROTR32(a, 13);           \
    m = a + ll_key[i];               \
    l = MARS_S_BOX[m & 511];         \
    r = ZCE_ROTL32(r, 5);            \
    l ^= r;                          \
    c -= ZCE_ROTL32(m, r);           \
    r = ZCE_ROTL32(r, 5);            \
    l ^= r;                          \
    d ^= r;                          \
    b -= ZCE_ROTL32(l, r)

    static void ecb_encrypt(const SUBKEY_STRUCT *sub_key,
                            const unsigned char *src_block,
                            unsigned char *cipher_block)
    {

        unsigned int   a, b, c, d, l, m, r;
        const uint32_t *ll_key = sub_key->ll_key_;

        a = ZINDEX_TO_LEUINT32(src_block, 0) + ll_key[0];
        b = ZINDEX_TO_LEUINT32(src_block, 1) + ll_key[1];
        c = ZINDEX_TO_LEUINT32(src_block, 2) + ll_key[2];
        d = ZINDEX_TO_LEUINT32(src_block, 3) + ll_key[3];

        MARS_F_MIX(a, b, c, d);
        a += d;
        MARS_F_MIX(b, c, d, a);
        b += c;
        MARS_F_MIX(c, d, a, b);
        MARS_F_MIX(d, a, b, c);
        MARS_F_MIX(a, b, c, d);
        a += d;
        MARS_F_MIX(b, c, d, a);
        b += c;
        MARS_F_MIX(c, d, a, b);
        MARS_F_MIX(d, a, b, c);

        MARS_F_KTR(a, b, c, d, 4);
        MARS_F_KTR(b, c, d, a, 6);
        MARS_F_KTR(c, d, a, b, 8);
        MARS_F_KTR(d, a, b, c, 10);
        MARS_F_KTR(a, b, c, d, 12);
        MARS_F_KTR(b, c, d, a, 14);
        MARS_F_KTR(c, d, a, b, 16);
        MARS_F_KTR(d, a, b, c, 18);
        MARS_F_KTR(a, d, c, b, 20);
        MARS_F_KTR(b, a, d, c, 22);
        MARS_F_KTR(c, b, a, d, 24);
        MARS_F_KTR(d, c, b, a, 26);
        MARS_F_KTR(a, d, c, b, 28);
        MARS_F_KTR(b, a, d, c, 30);
        MARS_F_KTR(c, b, a, d, 32);
        MARS_F_KTR(d, c, b, a, 34);

        MARS_B_MIX(a, b, c, d);
        MARS_B_MIX(b, c, d, a);
        c -= b;
        MARS_B_MIX(c, d, a, b);
        d -= a;
        MARS_B_MIX(d, a, b, c);
        MARS_B_MIX(a, b, c, d);
        MARS_B_MIX(b, c, d, a);
        c -= b;
        MARS_B_MIX(c, d, a, b);
        d -= a;
        MARS_B_MIX(d, a, b, c);

        ZLEUINT32_TO_INDEX(cipher_block, 0, a - ll_key[36]);
        ZLEUINT32_TO_INDEX(cipher_block, 1, b - ll_key[37]);
        ZLEUINT32_TO_INDEX(cipher_block, 2, c - ll_key[38]);
        ZLEUINT32_TO_INDEX(cipher_block, 3, d - ll_key[39]);
    }

    //
    static void ecb_decrypt(const SUBKEY_STRUCT *sub_key,
                            const unsigned char *cipher_block,
                            unsigned char *src_block)
    {

        unsigned int   a, b, c, d, l, m, r;
        const uint32_t *ll_key = sub_key->ll_key_;

        d = ZINDEX_TO_LEUINT32(cipher_block, 0) + ll_key[36];
        c = ZINDEX_TO_LEUINT32(cipher_block, 1) + ll_key[37];
        b = ZINDEX_TO_LEUINT32(cipher_block, 2) + ll_key[38];
        a = ZINDEX_TO_LEUINT32(cipher_block, 3) + ll_key[39];

        MARS_F_MIX(a, b, c, d);
        a += d;
        MARS_F_MIX(b, c, d, a);
        b += c;
        MARS_F_MIX(c, d, a, b);
        MARS_F_MIX(d, a, b, c);
        MARS_F_MIX(a, b, c, d);
        a += d;
        MARS_F_MIX(b, c, d, a);
        b += c;
        MARS_F_MIX(c, d, a, b);
        MARS_F_MIX(d, a, b, c);

        MARS_R_KTR(a, b, c, d, 34);
        MARS_R_KTR(b, c, d, a, 32);
        MARS_R_KTR(c, d, a, b, 30);
        MARS_R_KTR(d, a, b, c, 28);
        MARS_R_KTR(a, b, c, d, 26);
        MARS_R_KTR(b, c, d, a, 24);
        MARS_R_KTR(c, d, a, b, 22);
        MARS_R_KTR(d, a, b, c, 20);
        MARS_R_KTR(a, d, c, b, 18);
        MARS_R_KTR(b, a, d, c, 16);
        MARS_R_KTR(c, b, a, d, 14);
        MARS_R_KTR(d, c, b, a, 12);
        MARS_R_KTR(a, d, c, b, 10);
        MARS_R_KTR(b, a, d, c, 8);
        MARS_R_KTR(c, b, a, d, 6);
        MARS_R_KTR(d, c, b, a, 4);

        MARS_B_MIX(a, b, c, d);
        MARS_B_MIX(b, c, d, a);
        c -= b;
        MARS_B_MIX(c, d, a, b);
        d -= a;
        MARS_B_MIX(d, a, b, c);
        MARS_B_MIX(a, b, c, d);
        MARS_B_MIX(b, c, d, a);
        c -= b;
        MARS_B_MIX(c, d, a, b);
        d -= a;
        MARS_B_MIX(d, a, b, c);

        ZLEUINT32_TO_INDEX(src_block, 0, d - ll_key[0]);
        ZLEUINT32_TO_INDEX(src_block, 1, c - ll_key[1]);
        ZLEUINT32_TO_INDEX(src_block, 2, b - ll_key[2]);
        ZLEUINT32_TO_INDEX(src_block, 3, a - ll_key[3]);
    }

#undef MARS_F_MIX
#undef MARS_B_MIX
#undef MARS_F_KTR
#undef MARS_R_KTR

    //
    const static size_t BLOCK_SIZE = 16;
    //
    const static size_t KEY_SIZE   = key_size;

};

//���ۿ���ѡ��16��20��24��28��32��36��40��44��48��52��56��Ϊkey����
//typedef����ԭ���ǣ������㷨���ƣ��㷨������BLOCK���ȣ�key���ȣ�����(�Ƽ�������������key������һ����ϵ)
typedef ZCE_Crypt<MARS_ECB<16> > MARS_Crypt_16_16_1;
typedef ZCE_Crypt<MARS_ECB<24> > MARS_Crypt_16_24_1;
typedef ZCE_Crypt<MARS_ECB<32> > MARS_Crypt_16_32_1;

//=================================================================================================================
//AES ���㷨��������Taocrypt�⣬
class AES_ECB_Define
{
protected:
    //�����õ�SBOX
    static const uint32_t TE_SBOX[5][256];
    //�����õ�BOX
    static const uint32_t TD_SBOX[5][256];
    //
    static const uint32_t AES_RCON[10];
};

/*!
@brief      �����ϴ����,AES�ļ����㷨��
            ���㷨Ϊ����ʱ����ѧ��Joan Daemen��Vincent Rijmen����ƣ������λ���ߵ����֣�
            ��RijndaelΪ��Ͷ��߼����ܱ�׼����ѡ���̡���Rijndael�ķ������� "Rhine doll"��
            ��Square�Ľ�����

            http://zh.wikipedia.org/wiki/%E9%AB%98%E7%BA%A7%E5%8A%A0%E5%AF%86%E6%A0%87%E5%87%86
            http://en.wikipedia.org/wiki/Advanced_Encryption_Standard
@tparam     key_size     16,24,32
@tparam     round_size   10,12,14 rounds_ = keylen / 4 + 6;
@note
*/
template <size_t key_size, size_t round_size>
class AES_ECB : public AES_ECB_Define
{
public:

    struct AES_SUBKEY
    {
        uint32_t skey_[round_size * 4 + 4];
    };

    //Ϊ�˷���ZCE_Crypt,�������KEY���ͣ�
    typedef AES_SUBKEY  SUBKEY_STRUCT;

    //���ɼ��������SKEY��ע�⣬AES�ļ��ܺͽ��ܵ�sub key���ǲ�һ���ģ��������������ΪɶҪ����������˰ɣ�
    static void key_setup(const unsigned char *key, SUBKEY_STRUCT *sub_key, bool if_encrypt)
    {
        uint32_t temp = 0, *rk = sub_key->skey_;
        for (size_t k = 0; k < key_size / sizeof(uint32_t); ++k)
        {
            rk[k] =  ZINDEX_TO_LEUINT32(key, k);
        }
        size_t i = 0;
        switch (key_size)
        {
            case 16:
                while (true)
                {
                    temp  = rk[3];
                    rk[4] = rk[0] ^
                            (TE_SBOX[4][ZUINT32_2BYTE(temp)] & 0xff000000) ^
                            (TE_SBOX[4][ZUINT32_1BYTE(temp)] & 0x00ff0000) ^
                            (TE_SBOX[4][ZUINT32_0BYTE(temp)] & 0x0000ff00) ^
                            (TE_SBOX[4][ZUINT32_3BYTE(temp)] & 0x000000ff) ^
                            AES_RCON[i];
                    rk[5] = rk[1] ^ rk[4];
                    rk[6] = rk[2] ^ rk[5];
                    rk[7] = rk[3] ^ rk[6];
                    if (++i == 10)
                    {
                        break;
                    }
                    rk += 4;
                }
                break;

            case 24:
                while (true)    // for (;;) here triggers a bug in VC60 SP4 w/ Pro Pack
                {
                    temp = rk[ 5];
                    rk[ 6] = rk[ 0] ^
                             (TE_SBOX[4][ZUINT32_2BYTE(temp)] & 0xff000000) ^
                             (TE_SBOX[4][ZUINT32_1BYTE(temp)] & 0x00ff0000) ^
                             (TE_SBOX[4][ZUINT32_0BYTE(temp)] & 0x0000ff00) ^
                             (TE_SBOX[4][ZUINT32_3BYTE(temp)] & 0x000000ff) ^
                             AES_RCON[i];
                    rk[ 7] = rk[ 1] ^ rk[ 6];
                    rk[ 8] = rk[ 2] ^ rk[ 7];
                    rk[ 9] = rk[ 3] ^ rk[ 8];
                    if (++i == 8)
                    {
                        break;
                    }
                    rk[10] = rk[ 4] ^ rk[ 9];
                    rk[11] = rk[ 5] ^ rk[10];
                    rk += 6;
                }
                break;

            case 32:
                while (true)
                {
                    temp = rk[ 7];
                    rk[ 8] = rk[ 0] ^
                             (TE_SBOX[4][ZUINT32_2BYTE(temp)] & 0xff000000) ^
                             (TE_SBOX[4][ZUINT32_1BYTE(temp)] & 0x00ff0000) ^
                             (TE_SBOX[4][ZUINT32_0BYTE(temp)] & 0x0000ff00) ^
                             (TE_SBOX[4][ZUINT32_3BYTE(temp)] & 0x000000ff) ^
                             AES_RCON[i];
                    rk[ 9] = rk[ 1] ^ rk[ 8];
                    rk[10] = rk[ 2] ^ rk[ 9];
                    rk[11] = rk[ 3] ^ rk[10];
                    if (++i == 7)
                    {
                        break;
                    }
                    temp = rk[11];
                    rk[12] = rk[ 4] ^
                             (TE_SBOX[4][ZUINT32_3BYTE(temp)] & 0xff000000) ^
                             (TE_SBOX[4][ZUINT32_2BYTE(temp)] & 0x00ff0000) ^
                             (TE_SBOX[4][ZUINT32_1BYTE(temp)] & 0x0000ff00) ^
                             (TE_SBOX[4][ZUINT32_0BYTE(temp)] & 0x000000ff);
                    rk[13] = rk[ 5] ^ rk[12];
                    rk[14] = rk[ 6] ^ rk[13];
                    rk[15] = rk[ 7] ^ rk[14];

                    rk += 8;
                }
                break;
        }

        //����ǽ���
        if (if_encrypt == false)
        {
            rk = sub_key->skey_;

            /* invert the order of the round keys: */
            for (size_t i = 0, j = 4 * round_size; i < j; i += 4, j -= 4)
            {
                temp = rk[i];
                rk[i] = rk[j];
                rk[j] = temp;
                temp = rk[i + 1];
                rk[i + 1] = rk[j + 1];
                rk[j + 1] = temp;
                temp = rk[i + 2];
                rk[i + 2] = rk[j + 2];
                rk[j + 2] = temp;
                temp = rk[i + 3];
                rk[i + 3] = rk[j + 3];
                rk[j + 3] = temp;
            }
            // apply the inverse MixColumn transform to all round keys but the
            // first and the last:
            for (size_t i = 1; i < round_size; i++)
            {
                rk += 4;
                rk[0] =
                    TD_SBOX[0][TE_SBOX[4][ZUINT32_3BYTE(rk[0])] & 0xff] ^
                    TD_SBOX[1][TE_SBOX[4][ZUINT32_2BYTE(rk[0])] & 0xff] ^
                    TD_SBOX[2][TE_SBOX[4][ZUINT32_1BYTE(rk[0])] & 0xff] ^
                    TD_SBOX[3][TE_SBOX[4][ZUINT32_0BYTE(rk[0])] & 0xff];
                rk[1] =
                    TD_SBOX[0][TE_SBOX[4][ZUINT32_3BYTE(rk[1])] & 0xff] ^
                    TD_SBOX[1][TE_SBOX[4][ZUINT32_2BYTE(rk[1])] & 0xff] ^
                    TD_SBOX[2][TE_SBOX[4][ZUINT32_1BYTE(rk[1])] & 0xff] ^
                    TD_SBOX[3][TE_SBOX[4][ZUINT32_0BYTE(rk[1])] & 0xff];
                rk[2] =
                    TD_SBOX[0][TE_SBOX[4][ZUINT32_3BYTE(rk[2])] & 0xff] ^
                    TD_SBOX[1][TE_SBOX[4][ZUINT32_2BYTE(rk[2])] & 0xff] ^
                    TD_SBOX[2][TE_SBOX[4][ZUINT32_1BYTE(rk[2])] & 0xff] ^
                    TD_SBOX[3][TE_SBOX[4][ZUINT32_0BYTE(rk[2])] & 0xff];
                rk[3] =
                    TD_SBOX[0][TE_SBOX[4][ZUINT32_3BYTE(rk[3])] & 0xff] ^
                    TD_SBOX[1][TE_SBOX[4][ZUINT32_2BYTE(rk[3])] & 0xff] ^
                    TD_SBOX[2][TE_SBOX[4][ZUINT32_1BYTE(rk[3])] & 0xff] ^
                    TD_SBOX[3][TE_SBOX[4][ZUINT32_0BYTE(rk[3])] & 0xff];
            }
        }
    }

public:

    //�����ܺ���
    static void ecb_encrypt(const SUBKEY_STRUCT *sub_key,
                            const unsigned char *src_block,
                            unsigned char *cipher_block)
    {

        uint32_t s0 = ZINDEX_TO_LEUINT32(src_block, 0);
        uint32_t s1 = ZINDEX_TO_LEUINT32(src_block, 1);
        uint32_t s2 = ZINDEX_TO_LEUINT32(src_block, 2);
        uint32_t s3 = ZINDEX_TO_LEUINT32(src_block, 3);

        uint32_t t0, t1, t2, t3;
        const uint32_t *rk = sub_key->skey_;

        s0 ^= rk[0];
        s1 ^= rk[1];
        s2 ^= rk[2];
        s3 ^= rk[3];

        // Nr - 1 full rounds:
        unsigned int r = round_size >> 1;
        for (;;)
        {
            t0 =
                TE_SBOX[0][ZUINT32_3BYTE(s0)]  ^
                TE_SBOX[1][ZUINT32_2BYTE(s1)]  ^
                TE_SBOX[2][ZUINT32_1BYTE(s2)]  ^
                TE_SBOX[3][ZUINT32_0BYTE(s3)]  ^
                rk[4];
            t1 =
                TE_SBOX[0][ZUINT32_3BYTE(s1)]  ^
                TE_SBOX[1][ZUINT32_2BYTE(s2)]  ^
                TE_SBOX[2][ZUINT32_1BYTE(s3)]  ^
                TE_SBOX[3][ZUINT32_0BYTE(s0)]  ^
                rk[5];
            t2 =
                TE_SBOX[0][ZUINT32_3BYTE(s2)] ^
                TE_SBOX[1][ZUINT32_2BYTE(s3)]  ^
                TE_SBOX[2][ZUINT32_1BYTE(s0)]  ^
                TE_SBOX[3][ZUINT32_0BYTE(s1)]  ^
                rk[6];
            t3 =
                TE_SBOX[0][ZUINT32_3BYTE(s3)] ^
                TE_SBOX[1][ZUINT32_2BYTE(s0)]  ^
                TE_SBOX[2][ZUINT32_1BYTE(s1)]  ^
                TE_SBOX[3][ZUINT32_0BYTE(s2)]  ^
                rk[7];

            rk += 8;
            if (--r == 0)
            {
                break;
            }

            s0 =
                TE_SBOX[0][ZUINT32_3BYTE(t0)] ^
                TE_SBOX[1][ZUINT32_2BYTE(t1)] ^
                TE_SBOX[2][ZUINT32_1BYTE(t2)] ^
                TE_SBOX[3][ZUINT32_0BYTE(t3)] ^
                rk[0];
            s1 =
                TE_SBOX[0][ZUINT32_3BYTE(t1)] ^
                TE_SBOX[1][ZUINT32_2BYTE(t2)] ^
                TE_SBOX[2][ZUINT32_1BYTE(t3)] ^
                TE_SBOX[3][ZUINT32_0BYTE(t0)] ^
                rk[1];
            s2 =
                TE_SBOX[0][ZUINT32_3BYTE(t2)] ^
                TE_SBOX[1][ZUINT32_2BYTE(t3)] ^
                TE_SBOX[2][ZUINT32_1BYTE(t0)] ^
                TE_SBOX[3][ZUINT32_0BYTE(t1)] ^
                rk[2];
            s3 =
                TE_SBOX[0][ZUINT32_3BYTE(t3)] ^
                TE_SBOX[1][ZUINT32_2BYTE(t0)] ^
                TE_SBOX[2][ZUINT32_1BYTE(t1)] ^
                TE_SBOX[3][ZUINT32_0BYTE(t2)] ^
                rk[3];
        }

        //apply last round and
        //map cipher state to byte array block:
        s0 =
            (TE_SBOX[4][ZUINT32_3BYTE(t0)] & 0xff000000) ^
            (TE_SBOX[4][ZUINT32_2BYTE(t1)] & 0x00ff0000) ^
            (TE_SBOX[4][ZUINT32_1BYTE(t2)] & 0x0000ff00) ^
            (TE_SBOX[4][ZUINT32_0BYTE(t3)] & 0x000000ff) ^
            rk[0];
        s1 =
            (TE_SBOX[4][ZUINT32_3BYTE(t1)] & 0xff000000) ^
            (TE_SBOX[4][ZUINT32_2BYTE(t2)] & 0x00ff0000) ^
            (TE_SBOX[4][ZUINT32_1BYTE(t3)] & 0x0000ff00) ^
            (TE_SBOX[4][ZUINT32_0BYTE(t0)] & 0x000000ff) ^
            rk[1];
        s2 =
            (TE_SBOX[4][ZUINT32_3BYTE(t2)] & 0xff000000) ^
            (TE_SBOX[4][ZUINT32_2BYTE(t3)] & 0x00ff0000) ^
            (TE_SBOX[4][ZUINT32_1BYTE(t0)] & 0x0000ff00) ^
            (TE_SBOX[4][ZUINT32_0BYTE(t1)] & 0x000000ff) ^
            rk[2];
        s3 =
            (TE_SBOX[4][ZUINT32_3BYTE(t3)] & 0xff000000) ^
            (TE_SBOX[4][ZUINT32_2BYTE(t0)] & 0x00ff0000) ^
            (TE_SBOX[4][ZUINT32_1BYTE(t1)] & 0x0000ff00) ^
            (TE_SBOX[4][ZUINT32_0BYTE(t2)] & 0x000000ff) ^
            rk[3];

        ZLEUINT32_TO_INDEX(cipher_block, 0, s0);
        ZLEUINT32_TO_INDEX(cipher_block, 1, s1);
        ZLEUINT32_TO_INDEX(cipher_block, 2, s2);
        ZLEUINT32_TO_INDEX(cipher_block, 3, s3);
    }
    //�����ܺ���
    static void ecb_decrypt(const SUBKEY_STRUCT *sub_key,
                            const unsigned char *cipher_block,
                            unsigned char *src_block)
    {

        uint32_t s0 = ZINDEX_TO_LEUINT32(cipher_block, 0);
        uint32_t s1 = ZINDEX_TO_LEUINT32(cipher_block, 1);
        uint32_t s2 = ZINDEX_TO_LEUINT32(cipher_block, 2);
        uint32_t s3 = ZINDEX_TO_LEUINT32(cipher_block, 3);

        uint32_t t0, t1, t2, t3;
        const uint32_t *rk = sub_key->skey_;

        s0 ^= rk[0];
        s1 ^= rk[1];
        s2 ^= rk[2];
        s3 ^= rk[3];

        //Nr - 1 full rounds:
        unsigned int r = round_size >> 1;
        for (;;)
        {
            t0 =
                TD_SBOX[0][ZUINT32_3BYTE(s0)] ^
                TD_SBOX[1][ZUINT32_2BYTE(s3)] ^
                TD_SBOX[2][ZUINT32_1BYTE(s2)] ^
                TD_SBOX[3][ZUINT32_0BYTE(s1)] ^
                rk[4];
            t1 =
                TD_SBOX[0][ZUINT32_3BYTE(s1)] ^
                TD_SBOX[1][ZUINT32_2BYTE(s0)] ^
                TD_SBOX[2][ZUINT32_1BYTE(s3)] ^
                TD_SBOX[3][ZUINT32_0BYTE(s2)] ^
                rk[5];
            t2 =
                TD_SBOX[0][ZUINT32_3BYTE(s2)] ^
                TD_SBOX[1][ZUINT32_2BYTE(s1)] ^
                TD_SBOX[2][ZUINT32_1BYTE(s0)] ^
                TD_SBOX[3][ZUINT32_0BYTE(s3)] ^
                rk[6];
            t3 =
                TD_SBOX[0][ZUINT32_3BYTE(s3)] ^
                TD_SBOX[1][ZUINT32_2BYTE(s2)] ^
                TD_SBOX[2][ZUINT32_1BYTE(s1)] ^
                TD_SBOX[3][ZUINT32_0BYTE(s0)] ^
                rk[7];

            rk += 8;
            if (--r == 0)
            {
                break;
            }

            s0 =
                TD_SBOX[0][ZUINT32_3BYTE(t0)] ^
                TD_SBOX[1][ZUINT32_2BYTE(t3)] ^
                TD_SBOX[2][ZUINT32_1BYTE(t2)] ^
                TD_SBOX[3][ZUINT32_0BYTE(t1)] ^
                rk[0];
            s1 =
                TD_SBOX[0][ZUINT32_3BYTE(t1)] ^
                TD_SBOX[1][ZUINT32_2BYTE(t0)] ^
                TD_SBOX[2][ZUINT32_1BYTE(t3)] ^
                TD_SBOX[3][ZUINT32_0BYTE(t2)] ^
                rk[1];
            s2 =
                TD_SBOX[0][ZUINT32_3BYTE(t2)] ^
                TD_SBOX[1][ZUINT32_2BYTE(t1)] ^
                TD_SBOX[2][ZUINT32_1BYTE(t0)] ^
                TD_SBOX[3][ZUINT32_0BYTE(t3)] ^
                rk[2];
            s3 =
                TD_SBOX[0][ZUINT32_3BYTE(t3)] ^
                TD_SBOX[1][ZUINT32_2BYTE(t2)] ^
                TD_SBOX[2][ZUINT32_1BYTE(t1)] ^
                TD_SBOX[3][ZUINT32_0BYTE(t0)] ^
                rk[3];
        }

        //apply last round and map cipher state to byte array block:
        s0 =
            (TD_SBOX[4][ZUINT32_3BYTE(t0)] & 0xff000000) ^
            (TD_SBOX[4][ZUINT32_2BYTE(t3)] & 0x00ff0000) ^
            (TD_SBOX[4][ZUINT32_1BYTE(t2)] & 0x0000ff00) ^
            (TD_SBOX[4][ZUINT32_0BYTE(t1)] & 0x000000ff) ^
            rk[0];
        s1 =
            (TD_SBOX[4][ZUINT32_3BYTE(t1)] & 0xff000000) ^
            (TD_SBOX[4][ZUINT32_2BYTE(t0)] & 0x00ff0000) ^
            (TD_SBOX[4][ZUINT32_1BYTE(t3)] & 0x0000ff00) ^
            (TD_SBOX[4][ZUINT32_0BYTE(t2)] & 0x000000ff) ^
            rk[1];
        s2 =
            (TD_SBOX[4][ZUINT32_3BYTE(t2)] & 0xff000000) ^
            (TD_SBOX[4][ZUINT32_2BYTE(t1)] & 0x00ff0000) ^
            (TD_SBOX[4][ZUINT32_1BYTE(t0)] & 0x0000ff00) ^
            (TD_SBOX[4][ZUINT32_0BYTE(t3)] & 0x000000ff) ^
            rk[2];
        s3 =
            (TD_SBOX[4][ZUINT32_3BYTE(t3)] & 0xff000000) ^
            (TD_SBOX[4][ZUINT32_2BYTE(t2)] & 0x00ff0000) ^
            (TD_SBOX[4][ZUINT32_1BYTE(t1)] & 0x0000ff00) ^
            (TD_SBOX[4][ZUINT32_0BYTE(t0)] & 0x000000ff) ^
            rk[3];

        ZLEUINT32_TO_INDEX(src_block, 0, s0);
        ZLEUINT32_TO_INDEX(src_block, 1, s1);
        ZLEUINT32_TO_INDEX(src_block, 2, s2);
        ZLEUINT32_TO_INDEX(src_block, 3, s3);
    }

public:
    //����㷨һ�δ���һ��BLOCK�ĳ���
    const static size_t BLOCK_SIZE = 16;
    //����㷨KEY�ĳ���
    const static size_t KEY_SIZE   = key_size;
};

//24�ֽڵ�key��196bits),32�ֽڵĵ�key(256bits)��keyҲ����ΪAES2
//typedef����ԭ���ǣ������㷨���ƣ��㷨������BLOCK���ȣ�key���ȣ�����(�Ƽ�������������key������һ����ϵ)
typedef ZCE_Crypt<AES_ECB<16, 10> > AES_Crypt_16_16_10;
typedef ZCE_Crypt<AES_ECB<24, 12> > AES_Crypt_16_24_12;
typedef ZCE_Crypt<AES_ECB<32, 14> > AES_Crypt_16_32_14;

};

#if defined (ZCE_OS_WINDOWS)
#pragma warning ( pop )
#endif

#endif //#ifndef ZCE_LIB_BYTES_ENCRYPT_H_
