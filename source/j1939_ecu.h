/*!*****************************************************************************
\file       j1939_ecu.h
\details    Encoding:GB2312, j1939_ecu.
\note       #define USE_J1939_ECU_PRD 1:Enable module, 0:Disable module.\n

\pre        Section: ģ����Ϣ-��Դ
\author     Section: ģ����Ϣ-ά��
\version    Section: �޸���ʷ-�汾
\date       Section: �޸���ʷ-����

\section    ģ����Ϣ
<table>
<tr><th>����   <td>j1939_ecuģ��
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
    j1939_ecu_init();
    while (1)
    {
        j1939_ecu_task();
    }
}
\endcode

*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __J1939_ECU_H
#define __J1939_ECU_H

/* Module switch -------------------------------------------------------------*/
#if (defined(ECU_SIM_V2))
#define USE_J1939_ECU       1 //!< Module Enable
#define USE_J1939_ECU_SHELL 1 //!< Function Enable
#else
#define USE_J1939_ECU 0 //!< Module Enable
#endif

#if USE_J1939_ECU == 1
/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

/* Define --------------------------------------------------------------------*/
/* Macro ---------------------------------------------------------------------*/
/* Typedef -------------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
/* Functions -----------------------------------------------------------------*/
bool j1939_ecu_init(void);
void j1939_ecu_task(void);    //!< main task, call in while(1).
void j1939_ecu_run(bool stt); //!< false:stop task, true:run task.
bool j1939_ecu_get_stt(void); //!< false:stop, true:running.

#else /* else of USE_J1939_ECU*/

#endif /* end of USE_J1939_ECU */
#endif /* end of __J1939_ECU_H */
