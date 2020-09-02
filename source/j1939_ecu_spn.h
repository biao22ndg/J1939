/*!*****************************************************************************
\file       j1939_ecu_spn.h
\details    Encoding:GB2312, j1939_ecu_spn.
\note       #define USE_J1939_ECU_SPN 1:Enable module, 0:Disable module.\n

\pre        Section: ģ����Ϣ-��Դ
\author     Section: ģ����Ϣ-ά��
\version    Section: �޸���ʷ-�汾
\date       Section: �޸���ʷ-����

\section    ģ����Ϣ
<table>
<tr><th>����   <td>j1939_ecu_spnģ��
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
#define J1939_DTC_MAX_NUM 10 //!< ���֧�ּ���������
#define J1939_IUPR_NUM    20 //!< �м���IUPR

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
\brief ������״̬
*/
typedef struct
{
    float    val;  //!< ��ǰֵ
    float    min;  //!< ��Сֵ
    float    max;  //!< ���ֵ
    float    step; //!< ����
    uint16_t time; //!< ���ʱ��
    uint16_t cnt;  //!< ʱ�����
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
