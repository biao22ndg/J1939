/* Attention, read head file at first. ****************************************/
/* Includes ------------------------------------------------------------------*/
#include "j1939_ecu_spn.h"
#if USE_J1939_ECU_SPN == 1

#include <string.h>

#include "bsp_tim.h"

#if USE_J1939_ECU_SPN_SHELL == 1
#include "shell.h"
#endif

#if USE_J1939_ECU_SPN_LOG == 1
#include "bsp_shell.h"
#endif

#if USE_J1939_ECU_SPN_EASYFLASH == 1
#include "easyflash.h"
#endif

/* Constants -----------------------------------------------------------------*/
/* Define --------------------------------------------------------------------*/
/* Macro ---------------------------------------------------------------------*/
#ifndef SIZEOF_ARRAY
#define SIZEOF_ARRAY(val) (sizeof(val) / sizeof(val[0]))
#endif

#define J1939_SPN_NUM (SIZEOF_ARRAY(s_spn_info_lst))

#if USE_J1939_ECU_SPN_LOG == 1
#define j1939_spn_log(fmt, ...) bsp_shell_printf(fmt, ##__VA_ARGS__)
#else
#define j1939_spn_log(fmt, ...)
#endif

/* Typedef -------------------------------------------------------------------*/
/*!
\brief ���ɲ����Ľṹ��Ϣ
*/
typedef struct
{
    uint16_t no;  //!< ���
    int16_t  off; //!< ƫ��
    float    rsl; //!< ����
    char *   str; //!< �������ֵ�Ͳ�������ΪNULL��������ַ����ͣ�����Ϊ��ַ
} j1939_spn_info_t;

/*!
\brief ��������Ϣ
*/
typedef struct
{
    uint32_t spn; //!< a.δ֪�����ı��(SPN) 19 λ
    uint8_t  fmi; //!< b.����ģʽ��־(FMI) 5 λ
    uint8_t  oc;  //!< c.��������(OC) 7 λ
    uint8_t  cm;  //!< d.δ֪������ŵ�ת����ʽ(CM) 1 λ
} j1939_dtc_t;

/*!
\brief IUPR��Ϣ
*/
typedef struct
{
    uint32_t spn;  //!< ���
    uint8_t  comp; //!< ����
    uint8_t  comd; //!< ��ĸ
    char *   str;  //!< ��д����
} j1939_iupr_t;

/* Variables -----------------------------------------------------------------*/
// clang-format off
// *INDENT-OFF*
static const j1939_spn_info_t s_spn_info_lst[] = {
/*   SPN    ƫ��ֵ   ����           �ַ��� */
    {2,     0,       0.4,           NULL},                    /*!< ���� */
    {84,    0,       0.004,         NULL},                    /*!< ���� */
    {91,    0,       0.4,           NULL},                    /*!< ����̤��λ�� */
    {92,    0,       0.004,         NULL},                    /*!< ���㸺�� */
    {96,    0,       0.4,           NULL},                    /*!< ����Һλ */
    {102,   0,       2,             NULL},                    /*!< �������������1ѹ�� */
    {105,   -40,     1,             NULL},                    /*!< �������������1�¶� */
    {106,   0,       2,             NULL},                    /*!< ������������ѹ�� */
    {108,   0,       0.5,           NULL},                    /*!< ����ѹ��(ֱ�Ӳ��������ֵ) */
    {110,   -40,     1,             NULL},                    /*!< ��������ȴҺ�¶� */
    {132,   0,       0.05,          NULL},                    /*!< ������ */
    {158,   0,       0.05,          NULL},                    /*!< Կ�׿��ص�ص��� */
    {168,   0,       0.05,          NULL},                    /*!< ��ص���/��Դ����1 */
    {171,   -273,    0.03125,       NULL},                    /*!< ��Χ�����¶� */
    {172,   -40,     1,             NULL},                    /*!< �����������¶� */
    {174,   -40,     1,             NULL},                    /*!< ������ȼ���¶�1 */
    {182,   0,       0.5,           NULL},                    /*!< С���ͺ� */
    {183,   0,       0.05,          NULL},                    /*!< ������ȼ������ */
    {184,   0,       0.002,         NULL},                    /*!< ˲ʱ�ͺ� */
    {190,   0,       0.125,         NULL},                    /*!< ������ת�� */
    {237,   0,       1,             "LVHFA162565025146"},     /*!< VIN */
    {244,   0,       0.125,         NULL},                    /*!< С����� */
    {245,   0,       0.125,         NULL},                    /*!< �ܵ��г���� */
    {246,   0,       0.05,          NULL},                    /*!< �����ۼ�����ʱ�� */
    {247,   0,       0.05,          NULL},                    /*!< ������������ʱ�� */
    {250,   0,       0.5,           NULL},                    /*!< ���ͺ� */
    {444,   0,       0.05,          NULL},                    /*!< ��ص���/��Դ����2 */
    {503,   0,       0.001,         NULL},                    /*!< С���ͺ�(�߾���) */
    {513,   -125,    0.5,           NULL},                    /*!< ������ʵ��Ť�� */
    {514,   -125,    0.5,           NULL},                    /*!< Ħ��Ť�� */
    {899,   0,       1,             NULL},                    /*!< ������Ť��ģʽ */
    {917,   0,       5,             NULL},                    /*!< �ܵ��г���̣��߾��ȣ� */
    {918,   0,       5,             NULL},                    /*!< С�����(�߾���) */
    {1029,  0,       0.05,          NULL},                    /*!< ƽ���ͺ� */
    {1119,  0,       0.0025,        NULL},                    /*!< ������ʵ���������� */
    {1131,  -40,     1,             NULL},                    /*!< �������������2�¶� */
    {1132,  -40,     1,             NULL},                    /*!< �������������3�¶� */
    {1133,  -40,     1,             NULL},                    /*!< �������������4�¶� */
    {1193,  0,       1,             NULL},                    /*!< ����������������ʱ�� */
    {1218,  0,       1,             NULL},                    /*!< ����ǰ������������ */
    {1241,  0,       0.05,          NULL},                    /*!< ������������������1 */
    {1600,  0,       0.001,         NULL},                    /*!< �߷ֱ��ʵķ�����ȼ������ */
    {1624,  0,       0.004,         NULL},                    /*!< ���� */
    {1634,  0,       1,             NULL},                    /*!< ����궨ʶ���(CVN) */
    {1635,  0,       1,             "JMB*36761500"},          /*!< �궨��֤�루CALID�� */
    {1761,  0,       0.4,           NULL},                    /*!< ���ش߻�����Һλ */
    {1802,  -40,     1,             NULL},                    /*!< �������������5�¶� */
    {1806,  -40,     1,             NULL},                    /*!< �������������6�¶� */
    {1846,  0,       1,             NULL},                    /*!< ����������׼Ť�� */
    {2659,  0,       0.05,          NULL},                    /*!< ������������ѭ��1(EGR1)�������� */
    {3031,  -40,     1,             NULL},                    /*!< ����1-���ͷ�������Һ��1�¶� */
    {3069,  0,       1,             NULL},                    /*!< ���ϵƼ�������ʻ��� */
    {3216,  -200,    0.05,          NULL},                    /*!< ����1-����NOxŨ�� */
    {3217,  -12,     0.000514,      NULL},                    /*!< ����1-�������� */
    {3226,  -200,    0.05,          NULL},                    /*!< ����1-����NOxŨ�� */
    {3227,  -12,     0.000514,      NULL},                    /*!< ����1-�������� */
    {3236,  0,       0.2,           NULL},                    /*!< ����1-������������ */
    {3242,  0,       0.03125,       NULL},                    /*!< ����1-DPF�����¶� */
    {3246,  0,       0.03125,       NULL},                    /*!< ����1-DPF�����¶� */
    {3251,  0,       0.1,           NULL},                    /*!< ����1-DPFѹ�� */
    {3255,  -200,    0.05,          NULL},                    /*!< ����2-����NOxŨ�� */
    {3256,  -12,     0.000514,      NULL},                    /*!< ����2-�������� */
    {3265,  -200,    0.05,          NULL},                    /*!< ����2-����NOxŨ�� */
    {3266,  -12,     0.000514,      NULL},                    /*!< ����2-�������� */
    {3276,  0,       0.03125,       NULL},                    /*!< ����2-DPF�����¶� */
    {3280,  0,       0.03125,       NULL},                    /*!< ����2-DPF�����¶�(�д�С��) */
    {3285,  0,       0.1,           NULL},                    /*!< ����2-DPFѹ�� */
    {3468,  -40,     1,             NULL},                    /*!< ������ȼ���¶�2 */
    {3562,  0,       2,             NULL},                    /*!< �������������ѹ��2 */
    {4331,  0,       0.3,           NULL},                    /*!< ����1-���ͻ�SCRϵͳʵ�ʻ�ԭ������ */
    {4332,  0,       1,             NULL},                    /*!< ����1-SCRϵͳ״̬ */
    {4333,  0,       0.1,           NULL},                    /*!< ����1-���ͻ�SCRϵͳ�ۼ����������� */
    {4360,  -273,    0.03125,       NULL},                    /*!< ����1-SCR�߻��������¶� */
    {4363,  -273,    0.03125,       NULL},                    /*!< ����1-SCR�߻��������¶� */
    {4364,  0,       0.4,           NULL},                    /*!< ����1-SCRת��Ч�� */
    {4368,  -40,     1,             NULL},                    /*!< ����1-���ͷ�������Һ��2�¶� */
    {4374,  0,       0.5,           NULL},                    /*!< ����1-���ͻ���Һ�����ת�� */
    {4375,  0,       0.4,           NULL},                    /*!< ����1-������Һ�������ٷ��� */
    {4384,  0,       0.3,           NULL},                    /*!< ����2-���ͻ�SCRϵͳʵ�ʻ�ԭ������ */
    {4385,  0,       1,             NULL},                    /*!< ����2-SCRϵͳ״̬ */
    {4386,  0,       0.1,           NULL},                    /*!< ����2-���ͻ�SCRϵͳ�ۼ����������� */
    {4413,  -273,    0.03125,       NULL},                    /*!< ����2-SCR�߻��������¶� */
    {4415,  -273,    0.03125,       NULL},                    /*!< ����2-SCR�߻��������¶� */
    {4419,  0,       0.4,           NULL},                    /*!< ����2-SCRת��Ч�� */
    {4427,  -40,     1,             NULL},                    /*!< ����2-���ͷ�������Һ��1�¶� */
    {4434,  -40,     1,             NULL},                    /*!< ����2-���ͷ�������Һ��2�¶� */
    {4440,  0,       0.5,           NULL},                    /*!< ����2-���ͻ���Һ�����ת�� */
    {4441,  0,       0.4,           NULL},                    /*!< ����2-������Һ�������ٷ��� */
    {5257,  0,       0.05,          NULL},                    /*!< ������������ѭ��2(EGR2)�������� */
};
// *INDENT-ON*
// clang-format on

static volatile j1939_spn_ctrl_t s_spn_ctrl_lst[SIZEOF_ARRAY(s_spn_info_lst)];
static volatile j1939_dtc_t      s_dtc_lst[J1939_DTC_MAX_NUM];
static volatile j1939_iupr_t     s_iupr_lst[J1939_IUPR_NUM];

/* Function prototypes -------------------------------------------------------*/
/* Functions -----------------------------------------------------------------*/
/* ͨ�����ֲ��ҷ�����SPN��ƫ��ֵ */
int16_t j1939_spn_search(uint16_t spn_no)
{
    uint16_t low  = 0;
    uint16_t mid  = 0;
    uint16_t high = SIZEOF_ARRAY(s_spn_info_lst) - 1;

    while (low <= high)
    {
        mid = (low + high) / 2; // ������������ż���и�ֵ����

        if (spn_no < s_spn_info_lst[mid].no)
        {
            high = mid - 1; // ��mid-1����Ϊmid�Ѿ��ȽϹ���
        }
        else if (spn_no > s_spn_info_lst[mid].no)
        {
            low = mid + 1;
        }
        else
        {
            return mid;
        }
    }

    return -1;
}

uint32_t j1939_ecu_spn_get_val(uint16_t spn_no)
{
    uint32_t ret = 0;

    int16_t i = j1939_spn_search(spn_no);

    if (i < 0)
    {
        return ret;
    }

    if (s_spn_info_lst[i].str == NULL) // ��ֵ�Ͳ���
    {
        ret = (s_spn_ctrl_lst[i].val - s_spn_info_lst[i].off) / s_spn_info_lst[i].rsl;
    }
    else // �ַ����Ĳ���
    {
        ret = (uint32_t)s_spn_info_lst[i].str;
    }

    return ret;
}

void j1939_spn_update(void)
{
    uint16_t i;

    for (i = 0; i < SIZEOF_ARRAY(s_spn_info_lst); i++)
    {
        if (s_spn_ctrl_lst[i].time == 0)
        {
            s_spn_ctrl_lst[i].val = s_spn_ctrl_lst[i].min;
            continue;
        }

        s_spn_ctrl_lst[i].cnt++;
        if (s_spn_ctrl_lst[i].cnt < s_spn_ctrl_lst[i].time)
        {
            continue;
        }
        s_spn_ctrl_lst[i].cnt = 0;

        if (s_spn_ctrl_lst[i].dir_up != false) // �������ϵ���
        {
            s_spn_ctrl_lst[i].val += s_spn_ctrl_lst[i].step;
            if (s_spn_ctrl_lst[i].val >= s_spn_ctrl_lst[i].max) // ��������ֵ
            {
                s_spn_ctrl_lst[i].val    = s_spn_ctrl_lst[i].max; // ����������ֵ
                s_spn_ctrl_lst[i].dir_up = false;                 // ��Ϊ���µݼ�
            }
        }
        else // �������µݼ�
        {
            s_spn_ctrl_lst[i].val -= s_spn_ctrl_lst[i].step;
            if (s_spn_ctrl_lst[i].val <= s_spn_ctrl_lst[i].min) // ��������ֵ
            {
                s_spn_ctrl_lst[i].val    = s_spn_ctrl_lst[i].min; // ����������ֵ
                s_spn_ctrl_lst[i].dir_up = true;                  // ��Ϊ���ϵ���
            }
        }
    }
}

uint8_t j1939_ecu_spn_dtc_get_num(void)
{
    uint8_t i   = 0;
    uint8_t num = 0;

    for (i = 0; i < J1939_DTC_MAX_NUM; i++)
    {
        if (s_dtc_lst[i].spn != 0)
        {
            num++;
        }
    }

    return num;
}

uint32_t j1939_ecu_spn_dtc_get_one(uint8_t idx)
{
    uint8_t ret[4];

    /*
    �ֽڣ� 3 8��1 λ SPN��SPN �ĵ� 8 λ��Чλ�������ЧλΪ�� 8 λ��
    �ֽڣ� 4 8��1 λ SPN��SPN �ĵ� 2 ���ֽڣ������ЧλΪ�� 8 λ��
    �ֽڣ� 5 8��6 λ SPN����Чλ�еĸ� 3 λ�������ЧλΪ�� 8 λ��
    5��1 λ FMI(�����ЧλΪ�� 5 λ)
    �ֽڣ� 6 8    λ δ֪������ŵ�ת����ʽ
    7��1 λ ��������
    */
    ret[0] = s_dtc_lst[idx].spn >> 11;
    ret[1] = s_dtc_lst[idx].spn >> 3;
    ret[2] = (s_dtc_lst[idx].spn & 0X07) << 5;
    ret[2] |= s_dtc_lst[idx].fmi;
    ret[3] = (s_dtc_lst[idx].cm << 7) | s_dtc_lst[idx].oc;

    return (*(uint32_t *)ret);
}

bool j1939_ecu_spn_dtc_set_one(uint8_t  idx,
                               uint32_t spn,
                               uint8_t  fmi,
                               uint8_t  oc,
                               uint8_t  cm)
{
    uint8_t i = 0;

    if (idx >= J1939_DTC_MAX_NUM)
    {
        return false;
    }

    s_dtc_lst[idx].spn = spn;
    s_dtc_lst[idx].fmi = fmi;
    s_dtc_lst[idx].oc  = oc;
    s_dtc_lst[idx].cm  = cm;

    return true;
}

uint8_t j1939_ecu_spn_iupr_get_num(void)
{
    return J1939_IUPR_NUM;
}

uint32_t j1939_ecu_spn_iupr_get_one(uint8_t idx, uint8_t typ)
{
    if (idx >= J1939_IUPR_NUM)
    {
        return 0;
    }

    if (typ == 0)
    {
        return s_iupr_lst[idx].spn;
    }
    else if (typ == 1)
    {
        return s_iupr_lst[idx].comp;
    }
    else if (typ == 2)
    {
        return s_iupr_lst[idx].comd;
    }
    else
    {
        return 0;
    }
}

bool j1939_ecu_spn_init(void)
{
    uint16_t i;
    uint8_t  len_rd;
    char     spn_str[] = "SPN123456";

    // ���SPN˳���Ƿ��С����
    for (i = 1; i < J1939_SPN_NUM; i++)
    {
        if (s_spn_info_lst[i - 1].no > s_spn_info_lst[i].no)
        {
            j1939_spn_log("J1939 SPN sort wrong:%d > %d\r\n", s_spn_info_lst[i - 1].no, s_spn_info_lst[i].no);
            while (1)
            {
            }
        }
    }

#if USE_J1939_ECU_SPN_EASYFLASH == 1
    for (i = 0; i < J1939_SPN_NUM; i++)
    {
        snprintf(&spn_str[3], sizeof(spn_str) - 3, "%d", s_spn_info_lst[i].no);

        len_rd = ef_get_env_blob(spn_str, (void *)&s_spn_ctrl_lst[i], sizeof(s_spn_ctrl_lst[i]), NULL);

        if (len_rd <= 0)
        {
            s_spn_ctrl_lst[i].min  = 50;
            s_spn_ctrl_lst[i].max  = 50;
            s_spn_ctrl_lst[i].step = 0;
            s_spn_ctrl_lst[i].time = 0;
            s_spn_ctrl_lst[i].val  = 0;

            ef_set_env_blob(spn_str, (void *)&s_spn_ctrl_lst[i], sizeof(s_spn_ctrl_lst[i]));
        }
    }

#endif

    j1939_spn_log("J1939 spnmeter control:\r\n");
    j1939_spn_log("   SPN      Min       Max       Step      Time\r\n");
    for (i = 0; i < J1939_SPN_NUM; i++)
    {
        j1939_spn_log("%6d: %-8.2f  %-8.2f  %-8.2f  %-5d\r\n",
                      s_spn_info_lst[i].no,
                      s_spn_ctrl_lst[i].min,
                      s_spn_ctrl_lst[i].max,
                      s_spn_ctrl_lst[i].step,
                      s_spn_ctrl_lst[i].time);
    }
    j1939_spn_log("\r\n\r\n");

    bsp_tim_reg_cbk_1ms(j1939_spn_update); // ע�ᶨʱ�¼���������
    return true;
}

bool j1939_spn_cmd(uint32_t spn, uint32_t min, uint32_t max, uint32_t step, uint16_t time)
{
    int16_t i         = j1939_spn_search(spn);
    char    spn_str[] = "SPN123456";

#if USE_J1939_ECU_SPN_EASYFLASH == 1
    EfErrCode result;
#endif

    if (i < 0)
    {
        return false;
    }

    s_spn_ctrl_lst[i].min  = min;
    s_spn_ctrl_lst[i].max  = max;
    s_spn_ctrl_lst[i].step = step;
    s_spn_ctrl_lst[i].time = time;

#if USE_J1939_ECU_SPN_EASYFLASH == 1
    snprintf(&spn_str[3], sizeof(spn_str) - 3, "%d", s_spn_info_lst[i].no);
    result = ef_set_env_blob(spn_str, (void *)&s_spn_ctrl_lst[i], sizeof(s_spn_ctrl_lst[i]));

    if (result != EF_NO_ERR)
    {
        return result;
    }
#endif

    return true;
}
#if (USE_J1939_ECU_SPN_SHELL == 1)
// SHELL_EXPORT_CMD(����, ������, ����, ����)
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0) | SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC),
                 spncmd,
                 j1939_spn_cmd,
                 "spncmd 84 10 120 5 100:����SPN84��С10�����120��ÿ������5��ÿ100msһ��");
#endif

bool j1939_spn_set(uint16_t idx, j1939_spn_ctrl_t *dat_p)
{
    char spn_str[] = "SPN123456";

    s_spn_ctrl_lst[idx] = *dat_p;

#if USE_J1939_ECU_SPN_EASYFLASH == 1
    snprintf(&spn_str[3], sizeof(spn_str) - 3, "%d", s_spn_info_lst[idx].no);

    ef_set_env_blob(spn_str, (void *)&s_spn_ctrl_lst[idx], sizeof(s_spn_ctrl_lst[idx]));
#endif

    return true;
}

bool j1939_spn_get(uint16_t idx, j1939_spn_ctrl_t *dat_p)
{
    if (idx >= J1939_SPN_NUM)
    {
        return false;
    }

    *dat_p = s_spn_ctrl_lst[idx];
    return true;
}

uint32_t j1939_spn_get_no(uint16_t idx)
{
    if (idx >= J1939_SPN_NUM)
    {
        return NULL;
    }

    return s_spn_info_lst[idx].no;
}

uint8_t j1939_spn_get_num(void)
{
    return J1939_SPN_NUM;
}

#endif /* end of USE_J1939_ECU_SPN */
