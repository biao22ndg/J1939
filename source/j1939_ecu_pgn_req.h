/*!*****************************************************************************
\file       j1939_ecu_req.h
\details    Encoding:GB2312, j1939_ecu_req.
\note       #define USE_J1939_ECU_REQ 1:Enable module, 0:Disable module.\n

\pre        Section: 模块信息-资源
\author     Section: 模块信息-维护
\version    Section: 修改历史-版本
\date       Section: 修改历史-日期

\section    模块信息
<table>
<tr><th>名称   <td>j1939_ecu_req模块
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
    j1939_ecu_req_init();
    while (1)
    {
        j1939_ecu_req_task();
    }
}
\endcode

*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __J1939_ECU_REQ_H
#define __J1939_ECU_REQ_H

/* Module switch -------------------------------------------------------------*/
#if (defined(ECU_SIM_V2))
#define USE_J1939_ECU_REQ       1 //!< Module Enable
#define USE_J1939_ECU_REQ_SHELL 1 //!< Function Enable
#define USE_J1939_ECU_REQ_ROM   1 //!< Function Enable
#else
#define USE_J1939_ECU_REQ 0 //!< Module Enable
#endif

#if USE_J1939_ECU_REQ == 1
/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

/* Define --------------------------------------------------------------------*/
/* Macro ---------------------------------------------------------------------*/
/* Typedef -------------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
/* Functions -----------------------------------------------------------------*/
bool j1939_ecu_pgn_req_init(void);

#endif /* end of USE_J1939_ECU_REQ */
#endif /* end of __J1939_ECU_REQ_H */
