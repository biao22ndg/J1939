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
\brief 可疑参数的结构信息
*/
typedef struct
{
    uint16_t no;  //!< 编号
    int16_t  off; //!< 偏移
    float    rsl; //!< 比例
    char *   str; //!< 如果是数值型参数，设为NULL；如果是字符串型，则设为地址
} j1939_spn_info_t;

/*!
\brief 故障码信息
*/
typedef struct
{
    uint32_t spn; //!< a.未知参数的编号(SPN) 19 位
    uint8_t  fmi; //!< b.故障模式标志(FMI) 5 位
    uint8_t  oc;  //!< c.发生次数(OC) 7 位
    uint8_t  cm;  //!< d.未知参数编号的转化方式(CM) 1 位
} j1939_dtc_t;

/*!
\brief IUPR信息
*/
typedef struct
{
    uint32_t spn;  //!< 编号
    uint8_t  comp; //!< 分子
    uint8_t  comd; //!< 分母
    char *   str;  //!< 缩写名称
} j1939_iupr_t;

/* Variables -----------------------------------------------------------------*/
// clang-format off
// *INDENT-OFF*
static const j1939_spn_info_t s_spn_info_lst[] = {
/*   SPN    偏移值   比例           字符串 */
    {2,     0,       0.4,           NULL},                    /*!< 案例 */
    {84,    0,       0.004,         NULL},                    /*!< 车速 */
    {91,    0,       0.4,           NULL},                    /*!< 加速踏板位置 */
    {92,    0,       0.004,         NULL},                    /*!< 计算负荷 */
    {96,    0,       0.4,           NULL},                    /*!< 油箱液位 */
    {102,   0,       2,             NULL},                    /*!< 发动机进气歧管1压力 */
    {105,   -40,     1,             NULL},                    /*!< 发动机进气歧管1温度 */
    {106,   0,       2,             NULL},                    /*!< 发动机进气口压力 */
    {108,   0,       0.5,           NULL},                    /*!< 大气压力(直接测量或估计值) */
    {110,   -40,     1,             NULL},                    /*!< 发动机冷却液温度 */
    {132,   0,       0.05,          NULL},                    /*!< 进气量 */
    {158,   0,       0.05,          NULL},                    /*!< 钥匙开关电池电势 */
    {168,   0,       0.05,          NULL},                    /*!< 电池电势/电源输入1 */
    {171,   -273,    0.03125,       NULL},                    /*!< 周围空气温度 */
    {172,   -40,     1,             NULL},                    /*!< 发动机进气温度 */
    {174,   -40,     1,             NULL},                    /*!< 发动机燃料温度1 */
    {182,   0,       0.5,           NULL},                    /*!< 小计油耗 */
    {183,   0,       0.05,          NULL},                    /*!< 发动机燃料流量 */
    {184,   0,       0.002,         NULL},                    /*!< 瞬时油耗 */
    {190,   0,       0.125,         NULL},                    /*!< 发动机转速 */
    {237,   0,       1,             "LVHFA162565025146"},     /*!< VIN */
    {244,   0,       0.125,         NULL},                    /*!< 小计里程 */
    {245,   0,       0.125,         NULL},                    /*!< 总的行车里程 */
    {246,   0,       0.05,          NULL},                    /*!< 车辆累计运行时间 */
    {247,   0,       0.05,          NULL},                    /*!< 发动机运行总时间 */
    {250,   0,       0.5,           NULL},                    /*!< 总油耗 */
    {444,   0,       0.05,          NULL},                    /*!< 电池电势/电源输入2 */
    {503,   0,       0.001,         NULL},                    /*!< 小计油耗(高精度) */
    {513,   -125,    0.5,           NULL},                    /*!< 发动机实际扭矩 */
    {514,   -125,    0.5,           NULL},                    /*!< 摩擦扭矩 */
    {899,   0,       1,             NULL},                    /*!< 发动机扭矩模式 */
    {917,   0,       5,             NULL},                    /*!< 总的行车里程（高精度） */
    {918,   0,       5,             NULL},                    /*!< 小计里程(高精度) */
    {1029,  0,       0.05,          NULL},                    /*!< 平均油耗 */
    {1119,  0,       0.0025,        NULL},                    /*!< 发动机实际氧气排量 */
    {1131,  -40,     1,             NULL},                    /*!< 发动机进气歧管2温度 */
    {1132,  -40,     1,             NULL},                    /*!< 发动机进气歧管3温度 */
    {1133,  -40,     1,             NULL},                    /*!< 发动机进气歧管4温度 */
    {1193,  0,       1,             NULL},                    /*!< 发动机重启后运行时间 */
    {1218,  0,       1,             NULL},                    /*!< （当前）故障码总数 */
    {1241,  0,       0.05,          NULL},                    /*!< 发动机空气质量流量1 */
    {1600,  0,       0.001,         NULL},                    /*!< 高分辨率的发动机燃料流量 */
    {1624,  0,       0.004,         NULL},                    /*!< 车速 */
    {1634,  0,       1,             NULL},                    /*!< 软件标定识别号(CVN) */
    {1635,  0,       1,             "JMB*36761500"},          /*!< 标定验证码（CALID） */
    {1761,  0,       0.4,           NULL},                    /*!< 尿素催化剂罐液位 */
    {1802,  -40,     1,             NULL},                    /*!< 发动机进气歧管5温度 */
    {1806,  -40,     1,             NULL},                    /*!< 发动机进气歧管6温度 */
    {1846,  0,       1,             NULL},                    /*!< 发动机最大基准扭矩 */
    {2659,  0,       0.05,          NULL},                    /*!< 发动机废气再循环1(EGR1)质量流量 */
    {3031,  -40,     1,             NULL},                    /*!< 后处理1-柴油发动机排液箱1温度 */
    {3069,  0,       1,             NULL},                    /*!< 故障灯激活后的行驶里程 */
    {3216,  -200,    0.05,          NULL},                    /*!< 后处理1-进口NOx浓度 */
    {3217,  -12,     0.000514,      NULL},                    /*!< 后处理1-氧气进量 */
    {3226,  -200,    0.05,          NULL},                    /*!< 后处理1-出口NOx浓度 */
    {3227,  -12,     0.000514,      NULL},                    /*!< 后处理1-氧气排量 */
    {3236,  0,       0.2,           NULL},                    /*!< 后处理1-排气质量流量 */
    {3242,  0,       0.03125,       NULL},                    /*!< 后处理1-DPF进气温度 */
    {3246,  0,       0.03125,       NULL},                    /*!< 后处理1-DPF排气温度 */
    {3251,  0,       0.1,           NULL},                    /*!< 后处理1-DPF压差 */
    {3255,  -200,    0.05,          NULL},                    /*!< 后处理2-进口NOx浓度 */
    {3256,  -12,     0.000514,      NULL},                    /*!< 后处理2-氧气排量 */
    {3265,  -200,    0.05,          NULL},                    /*!< 后处理2-出口NOx浓度 */
    {3266,  -12,     0.000514,      NULL},                    /*!< 后处理2-氧气排量 */
    {3276,  0,       0.03125,       NULL},                    /*!< 后处理2-DPF进气温度 */
    {3280,  0,       0.03125,       NULL},                    /*!< 后处理2-DPF排气温度(有大小端) */
    {3285,  0,       0.1,           NULL},                    /*!< 后处理2-DPF压差 */
    {3468,  -40,     1,             NULL},                    /*!< 发动机燃料温度2 */
    {3562,  0,       2,             NULL},                    /*!< 发动机进气歧管压力2 */
    {4331,  0,       0.3,           NULL},                    /*!< 后处理1-柴油机SCR系统实际还原剂用量 */
    {4332,  0,       1,             NULL},                    /*!< 后处理1-SCR系统状态 */
    {4333,  0,       0.1,           NULL},                    /*!< 后处理1-柴油机SCR系统累计尿素消耗量 */
    {4360,  -273,    0.03125,       NULL},                    /*!< 后处理1-SCR催化剂进气温度 */
    {4363,  -273,    0.03125,       NULL},                    /*!< 后处理1-SCR催化剂排气温度 */
    {4364,  0,       0.4,           NULL},                    /*!< 后处理1-SCR转换效率 */
    {4368,  -40,     1,             NULL},                    /*!< 后处理1-柴油发动机排液箱2温度 */
    {4374,  0,       0.5,           NULL},                    /*!< 后处理1-柴油机排液泵马达转速 */
    {4375,  0,       0.4,           NULL},                    /*!< 后处理1-柴油排液泵驱动百分率 */
    {4384,  0,       0.3,           NULL},                    /*!< 后处理2-柴油机SCR系统实际还原剂用量 */
    {4385,  0,       1,             NULL},                    /*!< 后处理2-SCR系统状态 */
    {4386,  0,       0.1,           NULL},                    /*!< 后处理2-柴油机SCR系统累计尿素消耗量 */
    {4413,  -273,    0.03125,       NULL},                    /*!< 后处理2-SCR催化剂进气温度 */
    {4415,  -273,    0.03125,       NULL},                    /*!< 后处理2-SCR催化剂排气温度 */
    {4419,  0,       0.4,           NULL},                    /*!< 后处理2-SCR转换效率 */
    {4427,  -40,     1,             NULL},                    /*!< 后处理2-柴油发动机排液箱1温度 */
    {4434,  -40,     1,             NULL},                    /*!< 后处理2-柴油发动机排液箱2温度 */
    {4440,  0,       0.5,           NULL},                    /*!< 后处理2-柴油机排液泵马达转速 */
    {4441,  0,       0.4,           NULL},                    /*!< 后处理2-柴油排液泵驱动百分率 */
    {5257,  0,       0.05,          NULL},                    /*!< 发动机废气再循环2(EGR2)质量流量 */
};
// *INDENT-ON*
// clang-format on

static volatile j1939_spn_ctrl_t s_spn_ctrl_lst[SIZEOF_ARRAY(s_spn_info_lst)];
static volatile j1939_dtc_t      s_dtc_lst[J1939_DTC_MAX_NUM];
static volatile j1939_iupr_t     s_iupr_lst[J1939_IUPR_NUM];

/* Function prototypes -------------------------------------------------------*/
/* Functions -----------------------------------------------------------------*/
/* 通过二分查找法搜索SPN的偏移值 */
int16_t j1939_spn_search(uint16_t spn_no)
{
    uint16_t low  = 0;
    uint16_t mid  = 0;
    uint16_t high = SIZEOF_ARRAY(s_spn_info_lst) - 1;

    while (low <= high)
    {
        mid = (low + high) / 2; // 奇数，无论奇偶，有个值就行

        if (spn_no < s_spn_info_lst[mid].no)
        {
            high = mid - 1; // 是mid-1，因为mid已经比较过了
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

    if (s_spn_info_lst[i].str == NULL) // 数值型参数
    {
        ret = (s_spn_ctrl_lst[i].val - s_spn_info_lst[i].off) / s_spn_info_lst[i].rsl;
    }
    else // 字符串的参数
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

        if (s_spn_ctrl_lst[i].dir_up != false) // 正在向上递增
        {
            s_spn_ctrl_lst[i].val += s_spn_ctrl_lst[i].step;
            if (s_spn_ctrl_lst[i].val >= s_spn_ctrl_lst[i].max) // 到达上限值
            {
                s_spn_ctrl_lst[i].val    = s_spn_ctrl_lst[i].max; // 限制在上限值
                s_spn_ctrl_lst[i].dir_up = false;                 // 改为向下递减
            }
        }
        else // 正在向下递减
        {
            s_spn_ctrl_lst[i].val -= s_spn_ctrl_lst[i].step;
            if (s_spn_ctrl_lst[i].val <= s_spn_ctrl_lst[i].min) // 到达下限值
            {
                s_spn_ctrl_lst[i].val    = s_spn_ctrl_lst[i].min; // 限制在下限值
                s_spn_ctrl_lst[i].dir_up = true;                  // 改为向上递增
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
    字节： 3 8～1 位 SPN，SPN 的低 8 位有效位（最高有效位为第 8 位）
    字节： 4 8～1 位 SPN，SPN 的第 2 个字节（最高有效位为第 8 位）
    字节： 5 8～6 位 SPN，有效位中的高 3 位（最高有效位为第 8 位）
    5～1 位 FMI(最高有效位为第 5 位)
    字节： 6 8    位 未知参数编号的转化方式
    7～1 位 发生次数
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

    // 检查SPN顺序是否从小到大
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

    bsp_tim_reg_cbk_1ms(j1939_spn_update); // 注册定时事件管理任务
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
// SHELL_EXPORT_CMD(属性, 命令名, 函数, 描述)
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0) | SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC),
                 spncmd,
                 j1939_spn_cmd,
                 "spncmd 84 10 120 5 100:设置SPN84最小10，最大120，每次增减5，每100ms一次");
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
