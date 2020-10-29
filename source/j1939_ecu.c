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
/* Variables -----------------------------------------------------------------*/

/* Function prototypes -------------------------------------------------------*/
/* Functions -----------------------------------------------------------------*/
bool j1939_ecu_init(void)
{
    static bool s_init = false;

    if (s_init != false)
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
    J1939_Poll();
    j1939_ecu_pgn_prd_task();
}

#endif /* end of USE_J1939_ECU */
