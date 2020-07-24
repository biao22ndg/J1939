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
#define USE_J1939_ECU_SPN       1 //!< Module Enable
#define USE_J1939_ECU_SPN_SHELL 1 //!< Function Enable
#define USE_J1939_ECU_SPN_ROM   1 //!< Function Enable
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

/* Variables -----------------------------------------------------------------*/
/* Functions -----------------------------------------------------------------*/
bool     j1939_ecu_spn_init(void);
uint32_t j1939_ecu_spn_get_val(uint16_t spn_no);

uint8_t  j1939_ecu_spn_get_active_dtc_num(void);
uint32_t j1939_ecu_spn_get_one_dtc(uint8_t idx);
uint8_t  j1939_ecu_spn_get_all_dtc(uint32_t* dtc_p, uint8_t max);
bool     j1939_ecu_spn_set_dtc(uint8_t  idx,
                               uint32_t spn,
                               uint8_t  fmi,
                               uint8_t  oc,
                               uint8_t  cm);
uint8_t  j1939_ecu_spn_get_num(void);
uint32_t j1939_ecu_spn_get_iupr(uint8_t idx, uint8_t typ);

#if 0
float    j1939_ecu_spn_get_val_f(uint16_t off);
int16_t  j1939_ecu_spn_bin_search(uint16_t spn_no);
#endif

#endif /* end of USE_J1939_ECU_SPN */
#endif /* end of __J1939_ECU_SPN_H */
