/* Attention, read head file at first. ****************************************/
/* Includes ------------------------------------------------------------------*/
#include "j1939_ecu_spn.h"
#if USE_J1939_ECU_SPN == 1

#include <string.h>

#if USE_J1939_ECU_SPN_SHELL == 1
#include "shell.h"
#endif

#if USE_J1939_ECU_SPN_ROM == 1
#endif

/* Constants -----------------------------------------------------------------*/
/* Define --------------------------------------------------------------------*/
/* Macro ---------------------------------------------------------------------*/
#ifndef SIZEOF_ARRAY
#define SIZEOF_ARRAY(val) (sizeof(val) / sizeof(val[0]))
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
    char*    str; //!< �������ֵ�Ͳ�������ΪNULL��������ַ����ͣ�����Ϊ��ַ
} j1939_spn_para_t;

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
\brief IUPT��Ϣ
*/
typedef struct
{
    uint32_t spn;  //!< ���
    uint8_t  comp; //!< ����
    uint8_t  comd; //!< ��ĸ
    char*    str;  //!< ��д����
} j1939_iupr_t;

/* Variables -----------------------------------------------------------------*/
static j1939_dtc_t  s_dtc_lst[J1939_DTC_MAX_NUM];
static j1939_iupr_t s_iupr_lst[J1939_IUPR_NUM];

static const j1939_spn_para_t s_spn_p_l[] = {
    {2, 0, 0.4, NULL},                /*!< ����̤��λ�� */
    {84, 0, 0.004, NULL},             /*!< ���� */
    {91, 0, 0.4, NULL},               /*!< ����̤��λ�� */
    {92, 0, 0.004, NULL},             /*!< ���㸺�� */
    {96, 0, 0.4, NULL},               /*!< ����Һλ */
    {102, 0, 2, NULL},                /*!< �������������1ѹ�� */
    {105, -40, 1, NULL},              /*!< �������������1�¶� */
    {106, 0, 2, NULL},                /*!< ������������ѹ�� */
    {108, 0, 0.5, NULL},              /*!< ����ѹ��(ֱ�Ӳ��������ֵ) */
    {110, -40, 1, NULL},              /*!< ��������ȴҺ�¶� */
    {132, 0, 0.05, NULL},             /*!< ������ */
    {158, 0, 0.05, NULL},             /*!< Կ�׿��ص�ص��� */
    {168, 0, 0.05, NULL},             /*!< ��ص���/��Դ����1 */
    {171, -273, 0.03125, NULL},       /*!< ��Χ�����¶� */
    {172, -40, 1, NULL},              /*!< �����������¶� */
    {174, -40, 1, NULL},              /*!< ������ȼ���¶�1 */
    {182, 0, 0.5, NULL},              /*!< С���ͺ� */
    {183, 0, 0.05, NULL},             /*!< ������ȼ������ */
    {184, 0, 0.002, NULL},            /*!< ˲ʱ�ͺ� */
    {190, 0, 0.125, NULL},            /*!< ������ת�� */
    {237, 0, 1, "LVHFA162565025146"}, /*!< VIN */
    {244, 0, 0.125, NULL},            /*!< С����� */
    {245, 0, 0.125, NULL},            /*!< �ܵ��г���� */
    {246, 0, 0.05, NULL},             /*!< �����ۼ�����ʱ�� */
    {247, 0, 0.05, NULL},             /*!< ������������ʱ�� */
    {250, 0, 0.5, NULL},              /*!< ���ͺ� */
    {444, 0, 0.05, NULL},             /*!< ��ص���/��Դ����2 */
    {503, 0, 0.001, NULL},            /*!< С���ͺ�(�߾���) */
    {513, -125, 0.5, NULL},           /*!< ������ʵ��Ť�� */
    {514, -125, 0.5, NULL},           /*!< Ħ��Ť�� */
    {899, 0, 1, NULL},                /*!< ������Ť��ģʽ */
    {917, 0, 5, NULL},                /*!< �ܵ��г���̣��߾��ȣ� */
    {918, 0, 5, NULL},                /*!< С�����(�߾���) */
    {1029, 0, 0.05, NULL},            /*!< ƽ���ͺ� */
    {1119, 0, 0.0025, NULL},          /*!< ������ʵ���������� */
    {1131, -40, 1, NULL},             /*!< �������������2�¶� */
    {1132, -40, 1, NULL},             /*!< �������������3�¶� */
    {1133, -40, 1, NULL},             /*!< �������������4�¶� */
    {1193, 0, 1, NULL},               /*!< ����������������ʱ�� */
    {1218, 0, 1, NULL},               /*!< ����ǰ������������ */
    {1241, 0, 0.05, NULL},            /*!< ������������������1 */
    {1600, 0, 0.001, NULL},           /*!< �߷ֱ��ʵķ�����ȼ������ */
    {1624, 0, 0.004, NULL},           /*!< ���� */
    {1634, 0, 1, NULL},               /*!< ����궨ʶ���(CVN) */
    {1635, 0, 1, "JMB*36761500"},     /*!< �궨��֤�루CALID�� */
    {1761, 0, 0.4, NULL},             /*!< ���ش߻�����Һλ */
    {1802, -40, 1, NULL},             /*!< �������������5�¶� */
    {1806, -40, 1, NULL},             /*!< �������������6�¶� */
    {1846, 0, 1, NULL},               /*!< ����������׼Ť�� */
    {2659, 0, 0.05, NULL},            /*!< ������������ѭ��1 (EGR1)�������� */
    {3031, -40, 1, NULL},             /*!< ����1-���ͷ�������Һ��1�¶� */
    {3069, 0, 1, NULL},               /*!< Distance Travelled While MIL is Activated */
    {3216, -200, 0.05, NULL},         /*!< ����-1����NOxŨ�� */
    {3217, -12, 0.000514, NULL},      /*!< ����1-�������� */
    {3226, -200, 0.05, NULL},         /*!< ����-1����NOxŨ�� */
    {3227, -12, 0.000514, NULL},      /*!< ����1-�������� */
    {3236, 0, 0.2, NULL},             /*!< ����1-������������ */
    {3242, 0, 0.03125, NULL},         /*!< ����_1-DPF�����¶� */
    {3246, 0, 0.03125, NULL},         /*!< ����_1-DPF�����¶� */
    {3251, 0, 0.1, NULL},             /*!< ����-1 DPFѹ�� */
    {3255, -200, 0.05, NULL},         /*!< ����-2����NOxŨ�� */
    {3256, -12, 0.000514, NULL},      /*!< ����2-�������� */
    {3265, -200, 0.05, NULL},         /*!< ����-2����NOxŨ�� */
    {3266, -12, 0.000514, NULL},      /*!< ����2-�������� */
    {3276, 0, 0.03125, NULL},         /*!< ����_2-DPF�����¶� */
    {3280, 0, 0.03125, NULL},         /*!< ����_2-DPF�����¶�(�д�С��) */
    {3285, 0, 0.1, NULL},             /*!< ����-2 DPFѹ�� */
    {3468, -40, 1, NULL},             /*!< ������ȼ���¶�2 */
    {3562, 0, 2, NULL},               /*!< �������������2ѹ�� */
    {4331, 0, 0.3, NULL},             /*!< ����1-���ͻ�SCRϵͳʵ�ʻ�ԭ������ */
    {4332, 0, 1, NULL},               /*!< ����1-SCRϵͳ״̬ */
    {4333, 0, 0.1, NULL},             /*!< ����1-���ͻ�SCRϵͳ�ۼ����������� */
    {4360, -273, 0.03125, NULL},      /*!< ����_1-SCR�߻��������¶� */
    {4363, -273, 0.03125, NULL},      /*!< ����_1-SCR�߻��������¶� */
    {4364, 0, 0.4, NULL},             /*!< ����-1 SCRת��Ч�� */
    {4368, -40, 1, NULL},             /*!< ����1-���ͷ�������Һ��2�¶� */
    {4374, 0, 0.5, NULL},             /*!< ����1-���ͻ���Һ�����ת�� */
    {4375, 0, 0.4, NULL},             /*!< ����1-������Һ�������ٷ��� */
    {4384, 0, 0.3, NULL},             /*!< ����2-���ͻ�SCRϵͳʵ�ʻ�ԭ������ */
    {4385, 0, 1, NULL},               /*!< ����2-SCRϵͳ״̬ */
    {4386, 0, 0.1, NULL},             /*!< ����2-���ͻ�SCRϵͳ�ۼ����������� */
    {4413, -273, 0.03125, NULL},      /*!< ����_2-SCR�߻��������¶� */
    {4415, -273, 0.03125, NULL},      /*!< ����_2-SCR�߻��������¶� */
    {4419, 0, 0.4, NULL},             /*!< ����-2 SCRת��Ч�� */
    {4427, -40, 1, NULL},             /*!< ����2-���ͷ�������Һ��1�¶� */
    {4434, -40, 1, NULL},             /*!< ����2-���ͷ�������Һ��2�¶� */
    {4440, 0, 0.5, NULL},             /*!< ����2-���ͻ���Һ�����ת�� */
    {4441, 0, 0.4, NULL},             /*!< ����2-������Һ�������ٷ��� */
    {5257, 0, 0.05, NULL},            /*!< ������������ѭ��2 (EGR2)�������� */
};

static float s_spn_v_l[SIZEOF_ARRAY(s_spn_p_l)];

/* Function prototypes -------------------------------------------------------*/
/* Functions -----------------------------------------------------------------*/
/* ͨ�����ֲ��ҷ�����SPN��ƫ��ֵ */
int16_t j1939_ecu_spn_bin_search(uint16_t spn_no)
{
    uint16_t low  = 0;
    uint16_t mid  = 0;
    uint16_t high = SIZEOF_ARRAY(s_spn_p_l) - 1;

    while (low <= high)
    {
        mid = (low + high) / 2; // ������������ż���и�ֵ����

        if (spn_no < s_spn_p_l[mid].no)
        {
            high = mid - 1; // ��mid-1����Ϊmid�Ѿ��ȽϹ���
        }
        else if (spn_no > s_spn_p_l[mid].no)
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

    int16_t i = j1939_ecu_spn_bin_search(spn_no);

    if (i < 0)
    {
        return ret;
    }

    if (s_spn_p_l[i].str == NULL) // ��ֵ�Ͳ���
    {
        ret = (s_spn_v_l[i] - s_spn_p_l[i].off) / s_spn_p_l[i].rsl;
    }
    else // �ַ����Ĳ���
    {
        ret = (uint32_t)s_spn_p_l[i].str;
    }

    return ret;
}

static bool j1939_set_spn_val(uint16_t spn, uint32_t val)
{
    int16_t i = j1939_ecu_spn_bin_search(spn);
    if (i >= 0)
    {
        s_spn_v_l[i] = ((float)val) / 100;
        return true;
    }
    else
    {
        return false;
    }
}
#if USE_J1939_ECU_SPN_SHELL == 1
// SHELL_EXPORT_CMD(����, ������, ����, ����)
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0) | SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC),
                 setspn,
                 j1939_set_spn_val,
                 "setspn 91 5012:����SPN91Ϊ50.12");
#endif

uint8_t j1939_ecu_spn_get_active_dtc_num(void)
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

uint32_t j1939_ecu_spn_get_one_dtc(uint8_t idx)
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

    return (*(uint32_t*)ret);
}

uint8_t j1939_ecu_spn_get_all_dtc(uint32_t* dtc_p, uint8_t max)
{
    uint16_t i   = 0;
    uint8_t  cnt = 0;

    for (i = 0; i < SIZEOF_ARRAY(s_spn_p_l); i++)
    {
        if (s_dtc_lst[i].spn != 0)
        {
            *dtc_p = j1939_ecu_spn_get_one_dtc(i);
            cnt++;
            max--;
            if (max == 0)
            {
                return cnt;
            }
        }
    }

    return cnt;
}

bool j1939_ecu_spn_set_dtc(uint8_t  idx,
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

uint8_t j1939_ecu_spn_get_num(void)
{
    return J1939_IUPR_NUM;
}

uint32_t j1939_ecu_spn_get_iupr(uint8_t idx, uint8_t typ)
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
    for (i = 0; i < SIZEOF_ARRAY(s_spn_p_l); i++)
    {
        s_spn_v_l[i] = 20;
    }

    for (i = 0; i < J1939_DTC_MAX_NUM; i++)
    {
        s_dtc_lst[i].spn = 0;
    }

    return true;
}

float j1939_ecu_spn_get_val_f(uint16_t off)
{
    return s_spn_v_l[off];
}

#endif /* end of USE_J1939_ECU_SPN */
