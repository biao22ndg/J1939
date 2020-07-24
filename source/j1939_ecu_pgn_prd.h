/*!*****************************************************************************
\file       j1939_ecu_prd.h
\details    Encoding:GB2312, j1939_ecu_prd.
\note       #define USE_J1939_ECU_PRD 1:Enable module, 0:Disable module.\n

\pre        Section: ģ����Ϣ-��Դ
\author     Section: ģ����Ϣ-ά��
\version    Section: �޸���ʷ-�汾
\date       Section: �޸���ʷ-����

\section    ģ����Ϣ
<table>
<tr><th>����   <td>j1939_ecu_prdģ��
<tr><th>ά��   <td>Yangwb
<tr><th>��Դ   <td>
-# GPIO: PA9, PA10, USART1
-# bsp_time

<tr><th>����   <td>
-# ���ڽ���
-# ��־�ײ����
</table>

\section    �޸���ʷ
<table>
<tr><th>����        <th>Ӳ���汾    <th>����汾  <th>����    <th>����  </tr>
<tr><td>2020/01/01  <td>v1.0.01     <td>v1.0.01   <td>Yangwb  <td>
-# �жϽ���
-# ��ѯ����
</tr>
</table>

\section    ʹ�òο�
\code
int main(void)
{
    j1939_ecu_prd_init();
    while (1)
    {
        j1939_ecu_prd_task();
    }
}
\endcode

*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __J1939_ECU_PRD_H
#define __J1939_ECU_PRD_H

/* Module switch -------------------------------------------------------------*/
#if (defined(ECU_SIM_V2))
#define USE_J1939_ECU_PRD       1 //!< Module Enable
#define USE_J1939_ECU_PRD_SHELL 1 //!< Function Enable
#define USE_J1939_ECU_PRD_ROM   1 //!< Function Enable
#else
#define USE_J1939_ECU_PRD 0 //!< Module Enable
#endif

#if USE_J1939_ECU_PRD == 1
/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

/* Define --------------------------------------------------------------------*/
/* Macro ---------------------------------------------------------------------*/
/* Typedef -------------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
/* Functions -----------------------------------------------------------------*/
void j1939_ecu_pgn_prd_init(void);
void j1939_ecu_pgn_prd_task(void);

#endif /* end of USE_J1939_ECU_PRD */
#endif /* end of __J1939_ECU_PRD_H */
