/* Attention, read head file at first. ****************************************/
/* Includes ------------------------------------------------------------------*/
#include "j1939_ecu.h"

#if (USE_J1939_ECU == 1)
#include "bsp_can.h"
#include "j1939.h"
#include "j1939_ecu_pgn_prd.h"
#include "j1939_ecu_pgn_req.h"
#include "j1939_ecu_spn.h"

#if USE_J1939_ECU_SHELL == 1
#include "shell.h"
#endif

/* Constants -----------------------------------------------------------------*/
/* Define --------------------------------------------------------------------*/
/* Macro ---------------------------------------------------------------------*/
/* Typedef -------------------------------------------------------------------*/
typedef struct
{
    bool init;
    bool run;
} j1939_ecu_stt_t;

/* Variables -----------------------------------------------------------------*/
static volatile j1939_ecu_stt_t s_j1939_ecu_stt = {0};

/* Function prototypes -------------------------------------------------------*/
/* Functions -----------------------------------------------------------------*/
void j1939_ecu_run(bool stt)
{
    s_j1939_ecu_stt.run = stt;
}
#if USE_J1939_ECU_SHELL == 1
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0) | SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC), /* 属性 */
                 j1939run,                                                      /* 命令名 */
                 j1939_ecu_run,                                                 /* 函数 */
                 "j1939run 1:启动J1939模拟任务");                               /* 描述 */
#endif

bool j1939_ecu_init(void)
{
    if (s_j1939_ecu_stt.init != false)
    {
        return true;
    }

    // 网络层初始化
    J1939_Initialization();
    bsp_can_reg_rx_cbk(CAN_A, j1939_can_rx_irq);

    // 应用层初始化
    j1939_ecu_spn_init();
    j1939_ecu_pgn_req_init();
    j1939_ecu_pgn_prd_init();

    return true;
}

void j1939_ecu_task(void)
{
    if (s_j1939_ecu_stt.run != false)
    {
        J1939_Poll();
        j1939_ecu_pgn_prd_task();
    }
}

bool j1939_ecu_get_stt(void)
{
    return s_j1939_ecu_stt.run;
}

#endif /* end of USE_J1939_ECU */
