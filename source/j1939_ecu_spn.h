/*!*****************************************************************************
\file       j1939_ecu_spn.h
\details    Encoding:GB2312, j1939_ecu_spn.
\note       #define USE_J1939_ECU_SPN 1:Enable module, 0:Disable module.\n

\pre        Section: 模块信息-资源
\author     Section: 模块信息-维护
\version    Section: 修改历史-版本
\date       Section: 修改历史-日期

\section    模块信息
<table>
<tr><th>名称   <td>j1939_ecu_spn模块
<tr><th>维护   <td>Yangwb
<tr><th>资源   <td>
-# GPIO: PA9, PA10, USART1
-# bsp_time

<tr><th>功能   <td>
-# 串口接收
-# 日志底层输出
</table>

\section    修改历史
<table>
<tr><th>日期        <th>硬件版本    <th>软件版本  <th>作者    <th>描述  </tr>
<tr><td>2020/01/01  <td>v1.0.01     <td>v1.0.01   <td>Yangwb  <td>
-# 中断接收
-# 查询发送
</tr>
</table>

\section    使用参考
\code
int main(void)
{
    j1939_ecu_spn_init();
    while (1)
    {
        j1939_ecu_spn_task();
    }
}
\endcode

*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __J1939_ECU_SPN_H
#define __J1939_ECU_SPN_H

/* Module switch -------------------------------------------------------------*/
#if (defined(ECU_SIM_V2))
#define USE_J1939_ECU_SPN           1 //!< Module Enable
#define USE_J1939_ECU_SPN_SHELL     1 //!< Function Enable
#define USE_J1939_ECU_SPN_LOG       1 //!< Function Enable
#define USE_J1939_ECU_SPN_EASYFLASH 1 //!< Function Enable
#else
#define USE_J1939_ECU_SPN 0 //!< Module Enable
#endif

#if USE_J1939_ECU_SPN == 1
/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

/* Define --------------------------------------------------------------------*/
#define J1939_DTC_MAX_NUM 10 //!< 最多支持几个故障码
#define J1939_IUPR_NUM    20 //!< 有几个IUPR

/* Macro ---------------------------------------------------------------------*/
#define KEEP_BITS_1(val) (val & 0x01)
#define KEEP_BITS_2(val) (val & 0x03)
#define KEEP_BITS_3(val) (val & 0x07)
#define KEEP_BITS_4(val) (val & 0x0F)
#define KEEP_BITS_5(val) (val & 0x1F)
#define KEEP_BITS_6(val) (val & 0x3F)
#define KEEP_BITS_7(val) (val & 0x7F)
#define KEEP_BITS_8(val) (val & 0xFF)

/* Typedef -------------------------------------------------------------------*/
/*!
\brief 参数的状态
*/
typedef struct
{
    float    val;  //!< 当前值
    float    min;  //!< 最小值
    float    max;  //!< 最大值
    float    step; //!< 步进
    uint16_t time; //!< 间隔时间
    uint16_t cnt;  //!< 时间计数
    bool     dir_up;
} j1939_spn_ctrl_t;

/* Variables -----------------------------------------------------------------*/
/* Functions -----------------------------------------------------------------*/
bool     j1939_ecu_spn_init(void);
bool     j1939_ecu_spn_set_val(uint16_t spn, uint32_t val);
uint32_t j1939_ecu_spn_get_val(uint16_t spn);

uint8_t  j1939_ecu_spn_dtc_get_num(void);
uint32_t j1939_ecu_spn_dtc_get_one(uint8_t idx);
bool     j1939_ecu_spn_dtc_set_one(uint8_t  idx,
                                   uint32_t spn,
                                   uint8_t  fmi,
                                   uint8_t  oc,
                                   uint8_t  cm);

uint8_t  j1939_ecu_spn_iupr_get_num(void);
uint32_t j1939_ecu_spn_iupr_get_one(uint8_t idx, uint8_t typ);

#endif /* end of USE_J1939_ECU_SPN */
#endif /* end of __J1939_ECU_SPN_H */
