/* Attention, read head file at first. ****************************************/
/* Includes ------------------------------------------------------------------*/
#include "j1939_ecu_pgn_prd.h"
#if USE_J1939_ECU_PRD == 1

#include <string.h>

#include "bsp_tim.h"
#include "j1939.h"
#include "j1939_ecu_spn.h"

#if USE_J1939_ECU_PRD_SHELL == 1
#include "shell.h"
#endif

#if USE_J1939_ECU_PRD_ROM == 1
#endif

/* Constants -----------------------------------------------------------------*/
/* Define --------------------------------------------------------------------*/
/* Macro ---------------------------------------------------------------------*/
#ifndef SIZEOF_ARRAY
#define SIZEOF_ARRAY(val) (sizeof(val) / sizeof(val[0]))
#endif

/* Function prototypes -------------------------------------------------------*/
static bool prd_pgn_fun_61443(void);
static bool prd_pgn_fun_61444(void);
static bool prd_pgn_fun_65170(void);
static bool prd_pgn_fun_65188(void);
static bool prd_pgn_fun_65248(void);
static bool prd_pgn_fun_65262(void);
static bool prd_pgn_fun_65265(void);
static bool prd_pgn_fun_65266(void);
static bool prd_pgn_fun_65269(void);
static bool prd_pgn_fun_65270(void);
static bool prd_pgn_fun_61455(void);
static bool prd_pgn_fun_61450(void);
static bool prd_pgn_fun_61475(void);
static bool prd_pgn_fun_61478(void);
static bool prd_pgn_fun_65243(void);
static bool prd_pgn_fun_64831(void);
static bool prd_pgn_fun_65132(void);
static bool prd_pgn_fun_65226(void);
static bool prd_pgn_fun_65276(void);
static bool prd_pgn_fun_65251(void);
static bool prd_pgn_fun_65247(void);
static bool prd_pgn_fun_64824(void);
static bool prd_pgn_fun_64830(void);
static bool prd_pgn_fun_61454(void);
static bool prd_pgn_fun_61456(void);
static bool prd_pgn_fun_61457(void);
static bool prd_pgn_fun_65110(void);
static bool prd_pgn_fun_64947(void);
static bool prd_pgn_fun_64948(void);
static bool prd_pgn_fun_64945(void);
static bool prd_pgn_fun_64944(void);
static bool prd_pgn_fun_64943(void);
static bool prd_pgn_fun_64946(void);
static bool prd_pgn_fun_65217(void);
static bool prd_pgn_fun_64821(void);
static bool prd_pgn_fun_64820(void);

/* Typedef -------------------------------------------------------------------*/
typedef struct
{
    uint16_t no;
    bool (*cbk)(void);
    uint16_t cnt;
    bool     en;
    uint16_t period;
} j1939_pgn_prd_t;

/* Variables -----------------------------------------------------------------*/
static volatile j1939_pgn_prd_t s_pgn_prd_l[] = {
    {61443, prd_pgn_fun_61443, 0, true, 50},
    {61444, prd_pgn_fun_61444, 0, true, 100},
    {61450, prd_pgn_fun_61450, 0, true, 50},
    {61454, prd_pgn_fun_61454, 0, true, 50},
    {61455, prd_pgn_fun_61455, 0, true, 50},
    {61456, prd_pgn_fun_61456, 0, true, 50},
    {61457, prd_pgn_fun_61457, 0, true, 50},
    {61475, prd_pgn_fun_61475, 0, true, 50},
    {61478, prd_pgn_fun_61478, 0, true, 50},
    {64820, prd_pgn_fun_64820, 0, true, 1000},
    {64821, prd_pgn_fun_64821, 0, true, 1000},
    {64824, prd_pgn_fun_64824, 0, true, 500},
    {64830, prd_pgn_fun_64830, 0, true, 500},
    {64831, prd_pgn_fun_64831, 0, true, 500},
    {64943, prd_pgn_fun_64943, 0, true, 500},
    {64944, prd_pgn_fun_64944, 0, true, 500},
    {64945, prd_pgn_fun_64945, 0, true, 500},
    {64946, prd_pgn_fun_64946, 0, true, 500},
    {64947, prd_pgn_fun_64947, 0, true, 500},
    {64948, prd_pgn_fun_64948, 0, true, 500},
    {65110, prd_pgn_fun_65110, 0, true, 1000},
    {65132, prd_pgn_fun_65132, 0, true, 50},
    {65170, prd_pgn_fun_65170, 0, true, 100},
    {65188, prd_pgn_fun_65188, 0, true, 1000},
    {65217, prd_pgn_fun_65217, 0, true, 1000},
    {65226, prd_pgn_fun_65226, 0, true, 1000},
    {65243, prd_pgn_fun_65243, 0, true, 500},
    {65247, prd_pgn_fun_65247, 0, true, 250},
    {65248, prd_pgn_fun_65248, 0, true, 100},
    {65251, prd_pgn_fun_65251, 0, true, 1000},
    {65262, prd_pgn_fun_65262, 0, true, 1000},
    {65265, prd_pgn_fun_65265, 0, true, 100},
    {65266, prd_pgn_fun_65266, 0, true, 100},
    {65269, prd_pgn_fun_65269, 0, true, 1000},
    {65270, prd_pgn_fun_65270, 0, true, 500},
    {65276, prd_pgn_fun_65276, 0, true, 1000},
};

/* Functions -----------------------------------------------------------------*/
static bool prd_pgn_fun_61443(void)
{
    /* 
    PGN 61443 Electronic Engine Controller 2 EEC2 
    Identifies electronic engine control related parameters. 
    Transmission Repetition Rate: 50 msec (preferred) or Engine Speed Dependent (if required by application) 
    Data Length: 8 
    Extended Data Page: 0 
    Data Page: 0 
    PDU Format: 240 
    PDU Specific: 3 PGN Supporting Information:  
    Default Priority: 3 
    Parameter Group Number: 61443  (0x00F003) 
    Start Position Length Parameter Name SPN 
    */
    J1939_MESSAGE tx_msg;
    memset(&tx_msg, 0, sizeof(tx_msg));

    tx_msg.Mxe.DataLength    = 8;
    tx_msg.Mxe.DataPage      = 0;
    tx_msg.Mxe.Res           = 0;
    tx_msg.Mxe.PDUFormat     = 240;
    tx_msg.Mxe.PDUSpecific   = 3;
    tx_msg.Mxe.Priority      = 3;
    tx_msg.Mxe.SourceAddress = 0x00;

    /*
    1.1 2 bits Accelerator Pedal 1 Low Idle Switch 558 
    1.3 2 bits Accelerator Pedal Kickdown Switch 559 
    1.5 2 bits Road Speed Limit Status 1437 
    1.7 2 bits Accelerator Pedal 2 Low Idle Switch 2970 
    */
    tx_msg.Mxe.Data[0] |= KEEP_BITS_2(j1939_ecu_spn_get_val(558)) << 0;
    tx_msg.Mxe.Data[0] |= KEEP_BITS_2(j1939_ecu_spn_get_val(559)) << 2;
    tx_msg.Mxe.Data[0] |= KEEP_BITS_2(j1939_ecu_spn_get_val(1437)) << 4;
    tx_msg.Mxe.Data[0] |= KEEP_BITS_2(j1939_ecu_spn_get_val(2970)) << 5;

    /*
    2 1 byte Accelerator Pedal Position 1 91 
    3 1 byte Engine Percent Load At Current Speed 92 
    4 1 byte Remote Accelerator Pedal Position 974 
    5 1 byte Accelerator Pedal Position 2 29 
    */
    tx_msg.Mxe.Data[1] |= j1939_ecu_spn_get_val(91);
    tx_msg.Mxe.Data[2] |= j1939_ecu_spn_get_val(92);
    tx_msg.Mxe.Data[3] |= j1939_ecu_spn_get_val(974);
    tx_msg.Mxe.Data[4] |= j1939_ecu_spn_get_val(29);

    /*
    6.1 2 bits Vehicle Acceleration Rate Limit Status 2979 
    6.3 2 bits Momentary Engine Maximum Power Enable Feedback 5021 
    6.5 2 bits DPF Thermal Management Active 5399 
    6.7 2 bits SCR Thermal Management Active 5400 
    */
    tx_msg.Mxe.Data[5] |= KEEP_BITS_2(j1939_ecu_spn_get_val(2979)) << 0;
    tx_msg.Mxe.Data[5] |= KEEP_BITS_2(j1939_ecu_spn_get_val(5021)) << 2;
    tx_msg.Mxe.Data[5] |= KEEP_BITS_2(j1939_ecu_spn_get_val(5399)) << 4;
    tx_msg.Mxe.Data[5] |= KEEP_BITS_2(j1939_ecu_spn_get_val(5400)) << 5;

    /*
    7 1 byte Actual Maximum Available Engine - Percent Torque 3357 
    8 1 byte Estimated Pumping - Percent Torque 5398 
    */
    tx_msg.Mxe.Data[6] |= j1939_ecu_spn_get_val(3357);
    tx_msg.Mxe.Data[7] |= j1939_ecu_spn_get_val(5398);

    if (J1939_Send_Message(&tx_msg, Select_CAN_NODE_1) == RC_SUCCESS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

static bool prd_pgn_fun_61444(void)
{
    /* 
    PGN 61444 Electronic Engine Controller 1 EEC1 
    Engine related parameters 
    Transmission Repetition Rate: engine speed dependent 
    Data Length: 8 
    Extended Data Page: 0 
    Data Page: 0 
    PDU Format: 240 
    PDU Specific: 4 PGN Supporting Information:  
    Default Priority: 3 
    Parameter Group Number: 61444  (0x00F004) 
    Start Position Length Parameter Name SPN 
    */
    J1939_MESSAGE tx_msg;
    memset(&tx_msg, 0, sizeof(tx_msg));

    tx_msg.Mxe.DataLength    = 8;
    tx_msg.Mxe.DataPage      = 0;
    tx_msg.Mxe.Res           = 0;
    tx_msg.Mxe.PDUFormat     = 240;
    tx_msg.Mxe.PDUSpecific   = 4;
    tx_msg.Mxe.Priority      = 3;
    tx_msg.Mxe.SourceAddress = 0x00;

    /*
    1.1 4 bits Engine Torque Mode 899 
    1.5 4 bits Actual Engine - Percent Torque High Resolution 4154 
    */
    tx_msg.Mxe.Data[0] |= KEEP_BITS_4(j1939_ecu_spn_get_val(899)) << 0;
    tx_msg.Mxe.Data[0] |= KEEP_BITS_4(j1939_ecu_spn_get_val(4154)) << 4;

    /*
    2 1 byte Driver's Demand Engine - Percent Torque 512 
    3 1 byte Actual Engine - Percent Torque 513 
    */
    tx_msg.Mxe.Data[1] |= j1939_ecu_spn_get_val(512);
    tx_msg.Mxe.Data[2] |= j1939_ecu_spn_get_val(513);

    /*
    4-5 2 bytes Engine Speed 190 
    */
    *(uint16_t *)(&tx_msg.Mxe.Data[3]) |= j1939_ecu_spn_get_val(190);

    /*
    6 1 byte Source Address of Controlling Device for Engine Control 1483 
    */
    tx_msg.Mxe.Data[5] |= j1939_ecu_spn_get_val(1483);

    /*
    7.1 4 bits Engine Starter Mode 1675 
    */
    tx_msg.Mxe.Data[6] |= KEEP_BITS_4(j1939_ecu_spn_get_val(1675)) << 0;

    /*
    8 1 byte Engine Demand – Percent Torque 2432 
    */
    tx_msg.Mxe.Data[7] |= j1939_ecu_spn_get_val(2432);

    if (J1939_Send_Message(&tx_msg, Select_CAN_NODE_1) == RC_SUCCESS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

static bool prd_pgn_fun_65170(void)
{
    /*
    PGN 65170 Engine Information  EI 
    Transmission Repetition Rate: 100 ms 
    Data Length: 8 
    Extended Data Page: 0 
    Data Page: 0 
    PDU Format: 254 
    PDU Specific: 146 PGN Supporting Information:  
    Default Priority: 7 
    Parameter Group Number: 65170  (0x00FE92) 
    Start Position Length Parameter Name SPN 
    */
    J1939_MESSAGE tx_msg;
    memset(&tx_msg, 0, sizeof(tx_msg));

    tx_msg.Mxe.DataLength    = 8;
    tx_msg.Mxe.DataPage      = 0;
    tx_msg.Mxe.Res           = 0;
    tx_msg.Mxe.PDUFormat     = 254;
    tx_msg.Mxe.PDUSpecific   = 146;
    tx_msg.Mxe.Priority      = 7;
    tx_msg.Mxe.SourceAddress = 0x00;

    /*
    1 1 byte Engine Pre-filter Oil Pressure 1208 
    */
    tx_msg.Mxe.Data[0] |= j1939_ecu_spn_get_val(1208);

    /*
    2-3 2 bytes Engine Exhaust Gas Pressure 1 1209 
    */
    *(uint16_t *)(&tx_msg.Mxe.Data[1]) |= j1939_ecu_spn_get_val(1209);

    /*
    4 1 byte Engine Fuel Rack Position 1210 
    */
    tx_msg.Mxe.Data[3] |= j1939_ecu_spn_get_val(1210);

    /*
    5-6 2 bytes Engine Gas Mass Flow Rate 1 1241 
    7-8 2 bytes Instantaneous Estimated Brake Power 1242 
    */
    *(uint16_t *)(&tx_msg.Mxe.Data[4]) |= j1939_ecu_spn_get_val(1241);
    *(uint16_t *)(&tx_msg.Mxe.Data[6]) |= j1939_ecu_spn_get_val(1242);

    if (J1939_Send_Message(&tx_msg, Select_CAN_NODE_1) == RC_SUCCESS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

static bool prd_pgn_fun_65188(void)
{
    /*
    PGN 65188 Engine Temperature 2 ET2 
    Transmission Repetition Rate: 1s 
    Data Length: 8 
    Extended Data Page: 0 
    Data Page: 0 
    PDU Format: 254 
    PDU Specific: 164 PGN Supporting Information:  
    Default Priority: 6 
    Parameter Group Number: 65188  (0x00FEA4) 
    Start Position Length Parameter Name SPN 
    */
    J1939_MESSAGE tx_msg;
    memset(&tx_msg, 0, sizeof(tx_msg));

    tx_msg.Mxe.DataLength    = 8;
    tx_msg.Mxe.DataPage      = 0;
    tx_msg.Mxe.Res           = 0;
    tx_msg.Mxe.PDUFormat     = 254;
    tx_msg.Mxe.PDUSpecific   = 164;
    tx_msg.Mxe.Priority      = 6;
    tx_msg.Mxe.SourceAddress = 0x00;

    /*
    1-2 2 bytes Engine Oil Temperature 2 1135 
    3-4 2 bytes Engine ECU Temperature 1136 
    5-6 2 bytes Engine Exhaust Gas Recirculation 1 Differential Pressure 411 
    7-8 2 bytes Engine Exhaust Gas Recirculation 1 Temperature 412 
    */
    *(uint16_t *)(&tx_msg.Mxe.Data[0]) |= j1939_ecu_spn_get_val(1135);
    *(uint16_t *)(&tx_msg.Mxe.Data[2]) |= j1939_ecu_spn_get_val(1136);
    *(uint16_t *)(&tx_msg.Mxe.Data[4]) |= j1939_ecu_spn_get_val(411);
    *(uint16_t *)(&tx_msg.Mxe.Data[6]) |= j1939_ecu_spn_get_val(412);

    if (J1939_Send_Message(&tx_msg, Select_CAN_NODE_1) == RC_SUCCESS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

static bool prd_pgn_fun_65248(void)
{
    /*
    PGN 65248 Vehicle Distance  VD 
    Transmission Repetition Rate: 100 ms 
    Data Length: 8 
    Extended Data Page: 0 
    Data Page: 0 
    PDU Format: 254 
    PDU Specific: 224 PGN Supporting Information:  
    Default Priority: 6 
    Parameter Group Number: 65248  (0x00FEE0) 
    Start Position Length Parameter Name SPN 
    1-4 4 bytes Trip Distance 244 
    5-8 4 bytes Total Vehicle Distance 245 
    */
    J1939_MESSAGE tx_msg;
    memset(&tx_msg, 0, sizeof(tx_msg));

    tx_msg.Mxe.DataLength    = 8;
    tx_msg.Mxe.DataPage      = 0;
    tx_msg.Mxe.Res           = 0;
    tx_msg.Mxe.PDUFormat     = 254;
    tx_msg.Mxe.PDUSpecific   = 224;
    tx_msg.Mxe.Priority      = 6;
    tx_msg.Mxe.SourceAddress = 0x00;

    *(uint32_t *)(&tx_msg.Mxe.Data[0]) |= j1939_ecu_spn_get_val(244);
    *(uint32_t *)(&tx_msg.Mxe.Data[4]) |= j1939_ecu_spn_get_val(245);

    if (J1939_Send_Message(&tx_msg, Select_CAN_NODE_1) == RC_SUCCESS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

static bool prd_pgn_fun_65262(void)
{
    /*
    PGN 65262 Engine Temperature 1 ET1 
    Transmission Repetition Rate: 1 s 
    Data Length: 8 
    Extended Data Page: 0 
    Data Page: 0 
    PDU Format: 254 
    PDU Specific: 238 PGN Supporting Information:  
    Default Priority: 6 
    Parameter Group Number: 65262  (0x00FEEE) 
    Start Position Length Parameter Name SPN 
    */
    J1939_MESSAGE tx_msg;
    memset(&tx_msg, 0, sizeof(tx_msg));

    tx_msg.Mxe.DataLength    = 8;
    tx_msg.Mxe.DataPage      = 0;
    tx_msg.Mxe.Res           = 0;
    tx_msg.Mxe.PDUFormat     = 254;
    tx_msg.Mxe.PDUSpecific   = 238;
    tx_msg.Mxe.Priority      = 6;
    tx_msg.Mxe.SourceAddress = 0x00;

    /*
    1 1 byte Engine Coolant Temperature 110 
    2 1 byte Engine Fuel Temperature 1 174 
    */
    tx_msg.Mxe.Data[0] |= j1939_ecu_spn_get_val(110);
    tx_msg.Mxe.Data[1] |= j1939_ecu_spn_get_val(174);

    /*
    3-4 2 bytes Engine Oil Temperature 1 175 
    5-6 2 bytes Engine Turbocharger Oil Temperature 176 
    */
    *(uint16_t *)(&tx_msg.Mxe.Data[2]) |= j1939_ecu_spn_get_val(175);
    *(uint16_t *)(&tx_msg.Mxe.Data[4]) |= j1939_ecu_spn_get_val(176);

    /*
    7 1 byte Engine Intercooler Temperature 52 
    8 1 byte Engine Intercooler Thermostat Opening 1134 
    */
    tx_msg.Mxe.Data[6] |= j1939_ecu_spn_get_val(52);
    tx_msg.Mxe.Data[7] |= j1939_ecu_spn_get_val(1134);

    if (J1939_Send_Message(&tx_msg, Select_CAN_NODE_1) == RC_SUCCESS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

static bool prd_pgn_fun_65265(void)
{
    /*
    PGN 65265 Cruise Control/Vehicle Speed 1 CCVS1 
    Cruise Control/Vehicle Speed 1 
    Transmission Repetition Rate: 100 ms 
    Data Length: 8 
    Extended Data Page: 0 
    Data Page: 0 
    PDU Format: 254 
    PDU Specific: 241 PGN Supporting Information:  
    Default Priority: 6 
    Parameter Group Number: 65265  (0x00FEF1) 
    Start Position Length Parameter Name SPN 
    */
    J1939_MESSAGE tx_msg;
    memset(&tx_msg, 0, sizeof(tx_msg));

    tx_msg.Mxe.DataLength    = 8;
    tx_msg.Mxe.DataPage      = 0;
    tx_msg.Mxe.Res           = 0;
    tx_msg.Mxe.PDUFormat     = 254;
    tx_msg.Mxe.PDUSpecific   = 241;
    tx_msg.Mxe.Priority      = 6;
    tx_msg.Mxe.SourceAddress = 0x00;

    /*
    1.1 2 bits Two Speed Axle Switch 69 
    1.3 2 bits Parking Brake Switch 70 
    1.5 2 bits Cruise Control Pause Switch 1633 
    1.7 2 bits Park Brake Release Inhibit Request 3807 
    */
    tx_msg.Mxe.Data[0] |= KEEP_BITS_2(j1939_ecu_spn_get_val(69)) << 0;
    tx_msg.Mxe.Data[0] |= KEEP_BITS_2(j1939_ecu_spn_get_val(70)) << 2;
    tx_msg.Mxe.Data[0] |= KEEP_BITS_2(j1939_ecu_spn_get_val(1633)) << 4;
    tx_msg.Mxe.Data[0] |= KEEP_BITS_2(j1939_ecu_spn_get_val(3807)) << 6;

    /*
    2-3 2 bytes Wheel-Based Vehicle Speed 84 
    */
    *(uint16_t *)(&tx_msg.Mxe.Data[1]) |= j1939_ecu_spn_get_val(84);

    /*
    4.1 2 bits Cruise Control Active 595 
    4.3 2 bits Cruise Control Enable Switch 596 
    4.5 2 bits Brake Switch 597 
    4.7 2 bits Clutch Switch 598 
    */
    tx_msg.Mxe.Data[3] |= KEEP_BITS_2(j1939_ecu_spn_get_val(595)) << 0;
    tx_msg.Mxe.Data[3] |= KEEP_BITS_2(j1939_ecu_spn_get_val(596)) << 2;
    tx_msg.Mxe.Data[3] |= KEEP_BITS_2(j1939_ecu_spn_get_val(597)) << 4;
    tx_msg.Mxe.Data[3] |= KEEP_BITS_2(j1939_ecu_spn_get_val(598)) << 6;

    /*
    5.1 2 bits Cruise Control Set Switch 599 
    5.3 2 bits Cruise Control Coast (Decelerate) Switch 600 
    5.5 2 bits Cruise Control Resume Switch 601 
    5.7 2 bits Cruise Control Accelerate Switch 602 
    */
    tx_msg.Mxe.Data[4] |= KEEP_BITS_2(j1939_ecu_spn_get_val(599)) << 0;
    tx_msg.Mxe.Data[4] |= KEEP_BITS_2(j1939_ecu_spn_get_val(600)) << 2;
    tx_msg.Mxe.Data[4] |= KEEP_BITS_2(j1939_ecu_spn_get_val(601)) << 4;
    tx_msg.Mxe.Data[4] |= KEEP_BITS_2(j1939_ecu_spn_get_val(602)) << 6;

    /*
    6 1 byte Cruise Control Set Speed 86 
    */
    tx_msg.Mxe.Data[5] |= j1939_ecu_spn_get_val(86);

    /*
    7.1 5 bits PTO Governor State 976 
    7.6 3 bits Cruise Control States 527 
    */
    tx_msg.Mxe.Data[6] |= KEEP_BITS_5(j1939_ecu_spn_get_val(976)) << 0;
    tx_msg.Mxe.Data[6] |= KEEP_BITS_3(j1939_ecu_spn_get_val(527)) << 5;

    /*
    8.1 2 bits Engine Idle Increment Switch 968 
    8.3 2 bits Engine Idle Decrement Switch 967 
    8.5 2 bits Engine Test Mode Switch 966 
    8.7 2 bits Engine Shutdown Override Switch 1237 
    */
    tx_msg.Mxe.Data[7] |= KEEP_BITS_2(j1939_ecu_spn_get_val(968)) << 0;
    tx_msg.Mxe.Data[7] |= KEEP_BITS_2(j1939_ecu_spn_get_val(967)) << 2;
    tx_msg.Mxe.Data[7] |= KEEP_BITS_2(j1939_ecu_spn_get_val(966)) << 4;
    tx_msg.Mxe.Data[7] |= KEEP_BITS_2(j1939_ecu_spn_get_val(1237)) << 6;

    if (J1939_Send_Message(&tx_msg, Select_CAN_NODE_1) == RC_SUCCESS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

static bool prd_pgn_fun_65266(void)
{
    /*
    PGN 65266 Fuel Economy (Liquid) LFE1 
    Transmission Repetition Rate: 100 ms 
    Data Length: 8 
    Extended Data Page: 0 
    Data Page: 0 
    PDU Format: 254 
    PDU Specific: 242 PGN Supporting Information:  
    Default Priority: 6 
    Parameter Group Number: 65266  (0x00FEF2) 
    Start Position Length Parameter Name SPN 
    */
    J1939_MESSAGE tx_msg;
    memset(&tx_msg, 0, sizeof(tx_msg));

    tx_msg.Mxe.DataLength    = 8;
    tx_msg.Mxe.DataPage      = 0;
    tx_msg.Mxe.Res           = 0;
    tx_msg.Mxe.PDUFormat     = 254;
    tx_msg.Mxe.PDUSpecific   = 242;
    tx_msg.Mxe.Priority      = 6;
    tx_msg.Mxe.SourceAddress = 0x00;

    /*
    1-2 2 bytes Engine Fuel Rate 183 
    3-4 2 bytes Engine Instantaneous Fuel Economy 184 
    5-6 2 bytes Engine Average Fuel Economy 185 
    */
    *(uint16_t *)(&tx_msg.Mxe.Data[0]) |= j1939_ecu_spn_get_val(183);
    *(uint16_t *)(&tx_msg.Mxe.Data[2]) |= j1939_ecu_spn_get_val(184);
    *(uint16_t *)(&tx_msg.Mxe.Data[4]) |= j1939_ecu_spn_get_val(185);

    /*
    7 1 byte Engine Throttle Valve 1 Position 51 
    8 1 byte Engine Throttle Valve 2 Position 3673 
    */
    tx_msg.Mxe.Data[6] |= j1939_ecu_spn_get_val(51);
    tx_msg.Mxe.Data[7] |= j1939_ecu_spn_get_val(3673);

    if (J1939_Send_Message(&tx_msg, Select_CAN_NODE_1) == RC_SUCCESS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

static bool prd_pgn_fun_65269(void)
{
    /*
    PGN 65269 Ambient Conditions AMB 
    Transmission Repetition Rate: 1 s 
    Data Length: 8 
    Extended Data Page: 0 
    Data Page: 0 
    PDU Format: 254 
    PDU Specific: 245 PGN Supporting Information:  
    Default Priority: 6 
    Parameter Group Number: 65269  (0x00FEF5) 
    Start Position Length Parameter Name SPN 
    */
    J1939_MESSAGE tx_msg;
    memset(&tx_msg, 0, sizeof(tx_msg));

    tx_msg.Mxe.DataLength    = 8;
    tx_msg.Mxe.DataPage      = 0;
    tx_msg.Mxe.Res           = 0;
    tx_msg.Mxe.PDUFormat     = 254;
    tx_msg.Mxe.PDUSpecific   = 245;
    tx_msg.Mxe.Priority      = 6;
    tx_msg.Mxe.SourceAddress = 0x00;

    /*
    1 1 byte Barometric Pressure 108 
    */
    tx_msg.Mxe.Data[0] |= j1939_ecu_spn_get_val(108);

    /*
    2-3 2 bytes Cab Interior Temperature 170 
    4-5 2 bytes Ambient Air Temperature 171 
    */
    *(uint16_t *)(&tx_msg.Mxe.Data[1]) |= j1939_ecu_spn_get_val(170);
    *(uint16_t *)(&tx_msg.Mxe.Data[3]) |= j1939_ecu_spn_get_val(171);

    /*
    6 1 byte Engine Air Intake Temperature 172 
    */
    tx_msg.Mxe.Data[5] |= j1939_ecu_spn_get_val(172);

    /*
    7-8 2 bytes Road Surface Temperature 79 
    */
    *(uint16_t *)(&tx_msg.Mxe.Data[6]) |= j1939_ecu_spn_get_val(79);

    if (J1939_Send_Message(&tx_msg, Select_CAN_NODE_1) == RC_SUCCESS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

static bool prd_pgn_fun_65270(void)
{
    /*
    PGN 65270 Intake/Exhaust Conditions 1 IC1 
    Transmission Repetition Rate: 0.5 s 
    Data Length: 8 
    Extended Data Page: 0 
    Data Page: 0 
    PDU Format: 254 
    PDU Specific: 246 PGN Supporting Information:  
    Default Priority: 6 
    Parameter Group Number: 65270  (0x00FEF6) 
    Start Position Length Parameter Name SPN 
    */
    J1939_MESSAGE tx_msg;
    memset(&tx_msg, 0, sizeof(tx_msg));

    tx_msg.Mxe.DataLength    = 8;
    tx_msg.Mxe.DataPage      = 0;
    tx_msg.Mxe.Res           = 0;
    tx_msg.Mxe.PDUFormat     = 254;
    tx_msg.Mxe.PDUSpecific   = 246;
    tx_msg.Mxe.Priority      = 6;
    tx_msg.Mxe.SourceAddress = 0x00;

    /*
    1 1 byte Engine Diesel Particulate Filter Intake Pressure 81 
    2 1 byte Engine Intake Manifold #1 Pressure 102 
    3 1 byte Engine Intake Manifold 1 Temperature 105 
    4 1 byte Engine Air Intake Pressure 106 
    5 1 byte Engine Air Filter 1 Differential Pressure 107 
    */
    tx_msg.Mxe.Data[0] |= j1939_ecu_spn_get_val(81);
    tx_msg.Mxe.Data[1] |= j1939_ecu_spn_get_val(102);
    tx_msg.Mxe.Data[2] |= j1939_ecu_spn_get_val(105);
    tx_msg.Mxe.Data[3] |= j1939_ecu_spn_get_val(106);
    tx_msg.Mxe.Data[4] |= j1939_ecu_spn_get_val(107);

    /*
    6-7 2 bytes Engine Exhaust Gas Temperature 173 
    */
    *(uint16_t *)(&tx_msg.Mxe.Data[5]) |= j1939_ecu_spn_get_val(173);

    /*
    8 1 byte Engine Coolant Filter Differential Pressure 112 
    */
    tx_msg.Mxe.Data[7] |= j1939_ecu_spn_get_val(112);

    if (J1939_Send_Message(&tx_msg, Select_CAN_NODE_1) == RC_SUCCESS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

static bool prd_pgn_fun_61455(void)
{
    /* 
     PGN 61455 Aftertreatment 1 Outlet Gas 1 AT1OG1
    The purpose of this PGN is to group the aftertreatment outlet sensor data for bank 1. These values include the NOx,
    %O2, Status' of the sensors with respect to the power being supplied and the heating element, errors and stability of the
    readings.
    Transmission Repetition Rate: 50 ms
    Data Length: 8
    Extended Data Page: 0
    Data Page: 0
    PDU Format: 240
    PDU Specific: 15 PGN Supporting Information:
    Default Priority: 6
    Parameter Group Number: 61455 (0x00F00F)
    Start Position Length Parameter Name SPN
    */
    J1939_MESSAGE tx_msg;
    memset(&tx_msg, 0, sizeof(tx_msg));

    tx_msg.Mxe.DataLength    = 8;
    tx_msg.Mxe.DataPage      = 0;
    tx_msg.Mxe.Res           = 0;
    tx_msg.Mxe.PDUFormat     = 240;
    tx_msg.Mxe.PDUSpecific   = 15;
    tx_msg.Mxe.Priority      = 6;
    tx_msg.Mxe.SourceAddress = 0x00;

    /*
    1-2 2 bytes Aftertreatment 1 Outlet NOx 3226
    3-4 2 bytes Aftertreatment 1 Outlet O2 3227
    */
    *(uint16_t *)(&tx_msg.Mxe.Data[0]) |= j1939_ecu_spn_get_val(3226);
    *(uint16_t *)(&tx_msg.Mxe.Data[2]) |= j1939_ecu_spn_get_val(3227);

    /*
    5.1 2 bits Aftertreatment 1 Outlet Gas Sensor Power Status 3228
    5.3 2 bits Aftertreatment 1 Outlet Gas Sensor at Temperature 3229
    5.5 2 bits Aftertreatment 1 Outlet NOx Reading Stable 3230
    5.7 2 bits Aftertreatment 1 Outlet Wide-Range %O2 Reading Stable 3231
    */
    tx_msg.Mxe.Data[4] |= KEEP_BITS_2(j1939_ecu_spn_get_val(3228)) << 0;
    tx_msg.Mxe.Data[4] |= KEEP_BITS_2(j1939_ecu_spn_get_val(3229)) << 2;
    tx_msg.Mxe.Data[4] |= KEEP_BITS_2(j1939_ecu_spn_get_val(3230)) << 4;
    tx_msg.Mxe.Data[4] |= KEEP_BITS_2(j1939_ecu_spn_get_val(3231)) << 6;

    /*
    6.1 5 bits Aftertreatment 1 Outlet Gas Sensor Heater Preliminary FMI 3232
    6.6 2 bits Aftertreatment 1 Outlet Gas Sensor Heater Control 3233
    */
    tx_msg.Mxe.Data[5] |= KEEP_BITS_5(j1939_ecu_spn_get_val(3230)) << 0;
    tx_msg.Mxe.Data[5] |= KEEP_BITS_2(j1939_ecu_spn_get_val(3231)) << 5;

    /*
    7.1 5 bits Aftertreatment 1 Outlet NOx Sensor Preliminary FMI 3234
    7.6 3 bits NOx Sensor ATO1 Self-diagnosis Status 5713
    */
    tx_msg.Mxe.Data[6] |= KEEP_BITS_5(j1939_ecu_spn_get_val(3234)) << 0;
    tx_msg.Mxe.Data[6] |= KEEP_BITS_3(j1939_ecu_spn_get_val(5713)) << 5;

    /*
    8.1 5 bits Aftertreatment 1 Outlet Oxygen Sensor Preliminary FMI 3235 
    */
    tx_msg.Mxe.Data[7] |= KEEP_BITS_5(j1939_ecu_spn_get_val(3235)) << 0;

    if (J1939_Send_Message(&tx_msg, Select_CAN_NODE_1) == RC_SUCCESS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

static bool prd_pgn_fun_61450(void)
{
    /* 
    PGN 61450 Engine Gas Flow Rate EGF1 
    Flow rates of Air and mixed gasses into the engine cylinders. 
    Transmission Repetition Rate: 50 ms 
    Data Length: 8 
    Extended Data Page: 0 
    Data Page: 0 
    PDU Format: 240 
    PDU Specific: 10 PGN Supporting Information:  
    Default Priority: 3 
    Parameter Group Number: 61450  (0x00F00A) 
    Start Position Length Parameter Name SPN 
    1-2 2 bytes Engine Exhaust Gas Recirculation 1 (EGR1) Mass Flow Rate 2659 
    3-4 2 bytes Engine Intake Air Mass Flow Rate 132 
    5-6 2 bytes Engine Exhaust Gas Recirculation 2 (EGR2) Mass Flow Rate 5257 
    */
    J1939_MESSAGE tx_msg;
    memset(&tx_msg, 0, sizeof(tx_msg));

    tx_msg.Mxe.DataLength    = 8;
    tx_msg.Mxe.DataPage      = 0;
    tx_msg.Mxe.Res           = 0;
    tx_msg.Mxe.PDUFormat     = 240;
    tx_msg.Mxe.PDUSpecific   = 10;
    tx_msg.Mxe.Priority      = 3;
    tx_msg.Mxe.SourceAddress = 0x00;

    *(uint16_t *)(&tx_msg.Mxe.Data[0]) |= j1939_ecu_spn_get_val(2659);
    *(uint16_t *)(&tx_msg.Mxe.Data[2]) |= j1939_ecu_spn_get_val(132);
    *(uint16_t *)(&tx_msg.Mxe.Data[4]) |= j1939_ecu_spn_get_val(5257);

    if (J1939_Send_Message(&tx_msg, Select_CAN_NODE_1) == RC_SUCCESS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

static bool prd_pgn_fun_61475(void)
{
    /* 
        PGN 61475 Aftertreatment 1 SCR Dosing System Information 1 A1SCRDSI1 
        This message contains SCR dosing system information for aftertreatment system 1 (or bank 1).  See PGN 64833 for 
        more information. 
        Transmission Repetition Rate: 50 ms 
        Data Length: 8 
        Extended Data Page: 0 
        Data Page: 0 
        PDU Format: 240 
        PDU Specific: 35 PGN Supporting Information:  
        Default Priority: 3 
        Parameter Group Number: 61475  (0x00F023) 
        Start Position Length Parameter Name SPN 
    */
    J1939_MESSAGE tx_msg;
    memset(&tx_msg, 0, sizeof(tx_msg));

    tx_msg.Mxe.DataLength    = 8;
    tx_msg.Mxe.DataPage      = 0;
    tx_msg.Mxe.Res           = 0;
    tx_msg.Mxe.PDUFormat     = 240;
    tx_msg.Mxe.PDUSpecific   = 35;
    tx_msg.Mxe.Priority      = 3;
    tx_msg.Mxe.SourceAddress = 0x00;

    /*
    1-2 2 bytes Aftertreatment 1 Diesel Exhaust Fluid Actual Dosing Quantity 4331 
    */
    *(uint16_t *)(&tx_msg.Mxe.Data[0]) |= j1939_ecu_spn_get_val(4331);

    /*
    3.1 4 bits Aftertreatment 1 SCR System State 4332 
    */
    tx_msg.Mxe.Data[2] |= KEEP_BITS_4(j1939_ecu_spn_get_val(4332)) << 0;

    /*
    4-5 2 bytes Aftertreatment 1 Diesel Exhaust Fluid Actual Quantity of Integrator 4333 
    */
    *(uint16_t *)(&tx_msg.Mxe.Data[3]) |= j1939_ecu_spn_get_val(4333);

    /*
    6 1 byte Aftertreatment 1 Diesel Exhaust Fluid Doser Absolute Pressure 4334 
    */
    tx_msg.Mxe.Data[5] |= j1939_ecu_spn_get_val(4334);

    if (J1939_Send_Message(&tx_msg, Select_CAN_NODE_1) == RC_SUCCESS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

static bool prd_pgn_fun_61478(void)
{
    /* 
        PGN 61478 Aftertreatment 2 SCR Dosing System Information 1 A2SCRDSI1 
        This message contains SCR dosing system information for aftertreatment system 2 (or bank 2).  See PGN 64827 for 
        more information. 
        Transmission Repetition Rate: 50 ms 
        Data Length: 8 
        Extended Data Page: 0 
        Data Page: 0 
        PDU Format: 240 
        PDU Specific: 38 PGN Supporting Information:  
        Default Priority: 3 
        Parameter Group Number: 61478  (0x00F026) 
        Start Position Length Parameter Name SPN 
    */

    J1939_MESSAGE tx_msg;
    memset(&tx_msg, 0, sizeof(tx_msg));

    tx_msg.Mxe.DataLength    = 8;
    tx_msg.Mxe.DataPage      = 0;
    tx_msg.Mxe.Res           = 0;
    tx_msg.Mxe.PDUFormat     = 240;
    tx_msg.Mxe.PDUSpecific   = 28;
    tx_msg.Mxe.Priority      = 3;
    tx_msg.Mxe.SourceAddress = 0x00;

    /*
    1-2 2 bytes Aftertreatment 2 Diesel Exhaust Fluid Actual Dosing Quantity 4384 
    */
    *(uint16_t *)(&tx_msg.Mxe.Data[0]) |= j1939_ecu_spn_get_val(4384);

    /*
    3.1 4 bits Aftertreatment 2 SCR System State 4385 
    */
    tx_msg.Mxe.Data[2] |= KEEP_BITS_4(j1939_ecu_spn_get_val(4385)) << 0;

    /*
    4-5 2 bytes Aftertreatment 2 Diesel Exhaust Fluid Actual Quantity of Integrator 4386 
   */
    *(uint16_t *)(&tx_msg.Mxe.Data[3]) |= j1939_ecu_spn_get_val(4386);

    /*
    6 1 byte Aftertreatment 2 Diesel Exhaust Fluid Dosing Absolute Pressure 4387 
    */
    tx_msg.Mxe.Data[5] |= j1939_ecu_spn_get_val(4387);

    if (J1939_Send_Message(&tx_msg, Select_CAN_NODE_1) == RC_SUCCESS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

static bool prd_pgn_fun_65243(void)
{
    /* 
    PGN 65243 Engine Fluid Level/Pressure 2 EFL/P2
    2nd PGN which identifies parameters that are either measuring various pressures within the engine or identifying engine
    fluid levels
    Transmission Repetition Rate: 0.5 s
    Data Length: 8
    Extended Data Page: 0
    Data Page: 0
    PDU Format: 254
    PDU Specific: 219 PGN Supporting Information:
    Default Priority: 6
    Parameter Group Number: 65243 (0x00FEDB)
    Start Position Length Parameter Name SPN
    */
    J1939_MESSAGE tx_msg;
    memset(&tx_msg, 0, sizeof(tx_msg));

    tx_msg.Mxe.DataLength    = 8;
    tx_msg.Mxe.DataPage      = 0;
    tx_msg.Mxe.Res           = 0;
    tx_msg.Mxe.PDUFormat     = 254;
    tx_msg.Mxe.PDUSpecific   = 219;
    tx_msg.Mxe.Priority      = 6;
    tx_msg.Mxe.SourceAddress = 0x00;

    /*
    1-2 2 bytes Engine Injection Control Pressure 164
    3-4 2 bytes Engine Injector Metering Rail 1 Pressure 157
    5-6 2 bytes Engine Injector Timing Rail 1 Pressure 156
    7-8 2 bytes Engine Injector Metering Rail 2 Pressure 1349 
    */
    *(uint16_t *)(&tx_msg.Mxe.Data[0]) |= j1939_ecu_spn_get_val(164);
    *(uint16_t *)(&tx_msg.Mxe.Data[2]) |= j1939_ecu_spn_get_val(157);
    *(uint16_t *)(&tx_msg.Mxe.Data[4]) |= j1939_ecu_spn_get_val(156);
    *(uint16_t *)(&tx_msg.Mxe.Data[6]) |= j1939_ecu_spn_get_val(1349);

    if (J1939_Send_Message(&tx_msg, Select_CAN_NODE_1) == RC_SUCCESS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

static bool prd_pgn_fun_64831(void)
{
    /* 
    PGN 64831 Aftertreatment 1 SCR Exhaust Gas Pressures A1SCREGP
    This message contains SCR catalyst exhaust gas pressure information for aftertreatment system 1 (or bank 1).
    Transmission Repetition Rate: 500 ms
    Data Length: 8
    Extended Data Page: 0
    Data Page: 0
    PDU Format: 253
    PDU Specific: 63 PGN Supporting Information:
    Default Priority: 6
    Parameter Group Number: 64831 (0x00FD3F)
    Start Position Length Parameter Name SPN
    */
    J1939_MESSAGE tx_msg;
    memset(&tx_msg, 0, sizeof(tx_msg));

    tx_msg.Mxe.DataLength    = 8;
    tx_msg.Mxe.DataPage      = 0;
    tx_msg.Mxe.Res           = 0;
    tx_msg.Mxe.PDUFormat     = 253;
    tx_msg.Mxe.PDUSpecific   = 63;
    tx_msg.Mxe.Priority      = 6;
    tx_msg.Mxe.SourceAddress = 0x00;

    /*
    1-2 2 bytes Aftertreatment 1 SCR Exhaust Gas Differential Pressure 4358
    */
    *(uint16_t *)(&tx_msg.Mxe.Data[0]) |= j1939_ecu_spn_get_val(4358);

    /*
    3.1 5 bits Aftertreatment 1 SCR Exhaust Gas Differential Pressure Preliminary FMI 4359
    */
    tx_msg.Mxe.Data[2] |= KEEP_BITS_2(j1939_ecu_spn_get_val(4359)) << 0;

    if (J1939_Send_Message(&tx_msg, Select_CAN_NODE_1) == RC_SUCCESS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

static bool prd_pgn_fun_65132(void)
{
    /* 
    PGN 65132 Tachograph  TCO1 
    Transmission Repetition Rate: 50 ms 
    Data Length: 8 
    Extended Data Page: 0 
    Data Page: 0 
    PDU Format: 254 
    PDU Specific: 108 PGN Supporting Information:  
    Default Priority: 3 
    Parameter Group Number: 65132  (0x00FE6C) 
    Start Position Length Parameter Name SPN 
    */

    J1939_MESSAGE tx_msg;
    memset(&tx_msg, 0, sizeof(tx_msg));

    tx_msg.Mxe.DataLength    = 8;
    tx_msg.Mxe.DataPage      = 0;
    tx_msg.Mxe.Res           = 0;
    tx_msg.Mxe.PDUFormat     = 254;
    tx_msg.Mxe.PDUSpecific   = 108;
    tx_msg.Mxe.Priority      = 6;
    tx_msg.Mxe.SourceAddress = 0x00;

    /*
    1.1 3 bits Driver 1 working state 1612 
    1.4 3 bits Driver 2 working state 1613 
    1.7 2 bits Vehicle motion 1611 
    */
    tx_msg.Mxe.Data[0] |= KEEP_BITS_3(j1939_ecu_spn_get_val(1612)) << 0;
    tx_msg.Mxe.Data[0] |= KEEP_BITS_3(j1939_ecu_spn_get_val(1613)) << 3;
    tx_msg.Mxe.Data[0] |= KEEP_BITS_2(j1939_ecu_spn_get_val(1611)) << 6;

    /*
    2.1 4 bits Driver 1 Time Related States 1617 
    2.5 2 bits Driver card, driver 1 1615 
    2.7 2 bits Vehicle Overspeed 1614 
    */
    tx_msg.Mxe.Data[1] |= KEEP_BITS_4(j1939_ecu_spn_get_val(1617)) << 0;
    tx_msg.Mxe.Data[1] |= KEEP_BITS_2(j1939_ecu_spn_get_val(1615)) << 4;
    tx_msg.Mxe.Data[1] |= KEEP_BITS_2(j1939_ecu_spn_get_val(1614)) << 6;

    /*
    3.1 4 bits Driver 2 Time Related States 1618 
    3.5 2 bits Driver card, driver 2 1616 
    */
    tx_msg.Mxe.Data[2] |= KEEP_BITS_4(j1939_ecu_spn_get_val(1618)) << 0;
    tx_msg.Mxe.Data[2] |= KEEP_BITS_2(j1939_ecu_spn_get_val(1616)) << 4;

    /*
    4.1 2 bits System event 1622 
    4.3 2 bits Handling information 1621 
    4.5 2 bits Tachograph performance 1620 
    4.7 2 bits Direction indicator 1619 
    */
    tx_msg.Mxe.Data[3] |= KEEP_BITS_2(j1939_ecu_spn_get_val(1622)) << 0;
    tx_msg.Mxe.Data[3] |= KEEP_BITS_2(j1939_ecu_spn_get_val(1621)) << 2;
    tx_msg.Mxe.Data[3] |= KEEP_BITS_2(j1939_ecu_spn_get_val(1620)) << 4;
    tx_msg.Mxe.Data[3] |= KEEP_BITS_2(j1939_ecu_spn_get_val(1619)) << 6;

    /*
    5-6 2 bytes Tachograph output shaft speed 1623 
    7-8 2 bytes Tachograph vehicle speed 1624 
    */
    *(uint16_t *)(&tx_msg.Mxe.Data[4]) |= j1939_ecu_spn_get_val(1623);
    *(uint16_t *)(&tx_msg.Mxe.Data[6]) |= j1939_ecu_spn_get_val(1623);

    if (J1939_Send_Message(&tx_msg, Select_CAN_NODE_1) == RC_SUCCESS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

static bool prd_pgn_fun_65226(void)
{
    /*
    5.7.1 ACTIVE DIAGNOSTIC TROUBLE CODES (DM1)—The information communicated is limited to the currently active
    diagnostic trouble codes preceded by the diagnostic lamp status. Both are used to notify other components
    on the network of the diagnostic condition of the transmitting electronic component. The data contains the
    lamp status and a list of diagnostic codes and occurrence counts for currently active diagnostic trouble
    codes. This is all DTCs including those that are emissions related.
    The currently defined lamps (Malfunction Indicator Lamp, Red Stop Lamp, Amber Warning Lamp, and
    Protect Lamp) are associated with DTCs. If the transmitting electronic component does not have active
    DTCs, then the lamp status from that component will indicate that the lamps should be off. However, the
    component controlling the actual lamp illumination must consider the status from all components that use
    these lamps before changing the state of the lamps.
    There may be applications that require additional lamp definitions to accomplish their function (e.g. a lamp
    that indicates when cruise control is actively controlling would require a separate lamp in another PG).
    Transmission Rate: A DM1 message is transmitted whenever a DTC becomes an active fault
    and at a normal update rate of only once per second thereafter. If a fault
    has been active for 1 second or longer, and then becomes inactive, a
    DM1 message shall be transmitted to reflect this state change. If a
    different DTC changes state within the 1 second update period, a new
    DM1 message is transmitted to reflect this new DTC. To prevent a high
    message rate due to intermittent faults that have a very high frequency, it
    is recommended that no more than one state change per DTC per second
    be transmitted. Thus a DTC that becomes active/inactive twice within a 1
    second interval, such as shown in Example Case 1, would have one
    message identifying the DTC becoming active, and one at the next
    periodic transmission identifying it being inactive. This message is sent
    only when there is an active DTC existing or in response to a request.
    Note that this Parameter Group will require using the “multipacket
    Transport” Parameter Group (reference SAE J1939-21) when more than
    one active DTC exists.
    Data Length: Variable
    Data page: 0
    PDU Format: 254
    PDU Specific: 202
    Default Priority: 6
    Parameter Group Number: 65226 (00FECA16)
    Byte: 1 bits 8-7 Malfunction Indicator Lamp Status See 5.7.1.1
    bits 6-5 Red Stop Lamp Status See 5.7.1.2
    bits 4-3 Amber Warning Lamp Status See 5.7.1.3
    bits 2-1 Protect Lamp Status See 5.7.1.4
    Byte: 2 bits 8-7 Reserved for SAE assignment Lamp Status
    bits 6-5 Reserved for SAE assignment Lamp Status
    bits 4-3 Reserved for SAE assignment Lamp Status
    bits 2-1 Reserved for SAE assignment Lamp Status
    Byte: 3 bits 8-1 SPN, 8 least significant bits of SPN See 5.7.1.5
    (most significant at bit 8)
    Byte: 4 bits 8-1 SPN, second byte of SPN See 5.7.1.5
    (most significant at bit 8)
    Byte: 5 bits 8-6 SPN, 3 most significant bits See 5.7.1.5
    (most significant at bit 8)
    bits 5-1 FMI
    (most significant at bit 5) See 5.7.1.6
    Byte: 6 bit 8 SPN Conversion Method See 5.7.1.7
    bits 7-1 Occurrence Count See 5.7.1.8
    NOTE—When the occurrence count is not available it should be set to all ones.
    */

    /*
    字节1：灯状态
    8～7 位 故障指示灯状态
    6～5 位 红色停止灯状态
    4～3 位 琥珀色警告灯状态
    2～1 位 保护灯状态

    字节2：
    8～7 位 预留以用来表示 SAE 任务灯状态
    6～5 位 预留以用来表示 SAE 任务灯状态
    4～3 位 预留以用来表示 SAE 任务灯状态
    2～1 位 预留以用来表示 SAE 任务灯状态
    */
    static uint8_t req_pgn_tx_buf[50];
    uint8_t        dat_cnt = 0;

    uint32_t spn;
    uint8_t  fmi;
    uint8_t  oc;
    uint8_t  cm;

    if (j1939_ecu_spn_get_active_dtc_num() == 0)
    {
        req_pgn_tx_buf[dat_cnt++] = 0;
    }
    else
    {
        req_pgn_tx_buf[dat_cnt++] = 0x01 << 6;
    }
    req_pgn_tx_buf[dat_cnt++] = 0x00;

    /*
    字节： 3 8～1 位 SPN，SPN 的低 8 位有效位（最高有效位为第 8 位）
    字节： 4 8～1 位 SPN，SPN 的第 2 个字节（最高有效位为第 8 位）
    字节： 5 8～6 位 SPN，有效位中的高 3 位（最高有效位为第 8 位）
    5～1 位 FMI(最高有效位为第 5 位)
    字节： 6 8    位 未知参数编号的转化方式
    7～1 位 发生次数
    */

    req_pgn_tx_buf[dat_cnt++] = (uint8_t)(spn >> 11);
    req_pgn_tx_buf[dat_cnt++] = (uint8_t)(spn >> 3);
    req_pgn_tx_buf[dat_cnt++] = (((uint8_t)(spn & 0X07)) << 5) | fmi;
    req_pgn_tx_buf[dat_cnt++] = (cm << 7) | oc;

    req_pgn_tx_buf[dat_cnt++] = (uint8_t)(spn >> 11);
    req_pgn_tx_buf[dat_cnt++] = (uint8_t)(spn >> 3);
    req_pgn_tx_buf[dat_cnt++] = (((uint8_t)(spn & 0X07)) << 5) | fmi;
    req_pgn_tx_buf[dat_cnt++] = (cm << 7) | oc;

    req_pgn_tx_buf[dat_cnt++] = (uint8_t)(spn >> 11);
    req_pgn_tx_buf[dat_cnt++] = (uint8_t)(spn >> 3);
    req_pgn_tx_buf[dat_cnt++] = (((uint8_t)(spn & 0X07)) << 5) | fmi;
    req_pgn_tx_buf[dat_cnt++] = (cm << 7) | oc;

    if (J1939_TP_TX_Message(0x00FECA, J1939_GLOBAL_ADDRESS, req_pgn_tx_buf, dat_cnt, Select_CAN_NODE_1) == RC_SUCCESS)
    {
        return true;
    }
    return false;
}

static bool prd_pgn_fun_65276(void)
{
    /*
    PGN 65276 Dash Display  D
    Transmission Repetition Rate: 1s 
    Data Length: 8 
    Extended Data Page: 0 
    Data Page: 0 
    PDU Format: 254 
    PDU Specific: 252 PGN Supporting Information:  
    Default Priority: 6 
    Parameter Group Number: 65276  (0x00FEFC) 
    Start Position Length Parameter Name SPN 
    */
    J1939_MESSAGE tx_msg;
    memset(&tx_msg, 0, sizeof(tx_msg));

    tx_msg.Mxe.DataLength    = 8;
    tx_msg.Mxe.DataPage      = 0;
    tx_msg.Mxe.Res           = 0;
    tx_msg.Mxe.PDUFormat     = 254;
    tx_msg.Mxe.PDUSpecific   = 3;
    tx_msg.Mxe.Priority      = 6;
    tx_msg.Mxe.SourceAddress = 0x00;

    /*
    1 1 byte Washer Fluid Level 80 
    2 1 byte Fuel Level 1 96 
    3 1 byte Engine Fuel Filter Differential Pressure 95 
    4 1 byte Engine Oil Filter Differential Pressure 99 
    */
    tx_msg.Mxe.Data[0] |= j1939_ecu_spn_get_val(80);
    tx_msg.Mxe.Data[1] |= j1939_ecu_spn_get_val(96);
    tx_msg.Mxe.Data[2] |= j1939_ecu_spn_get_val(95);
    tx_msg.Mxe.Data[3] |= j1939_ecu_spn_get_val(99);

    /*
    5-6 2 bytes Cargo Ambient Temperature 169 
    */
    *(uint16_t *)(&tx_msg.Mxe.Data[4]) |= j1939_ecu_spn_get_val(169);

    /*
    7 1 byte Fuel Level 2 38 
    */
    tx_msg.Mxe.Data[6] |= j1939_ecu_spn_get_val(38);

    if (J1939_Send_Message(&tx_msg, Select_CAN_NODE_1) == RC_SUCCESS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

static bool prd_pgn_fun_65251(void)
{
    /*
    PGN 65251 Engine Configuration 1 EC1 
    This map describes the stationary behavior of the engine and the speed dependent available indicated torque.  This map 
    should reflect the effect of changes due to barometric pressure, engine temperature, and any other stationary changes 
    (sensor failures, etc.) which influence the engine torque curve more than 10%.  This map is only valid for maximum boost 
    pressure.  At low boost pressures the torque limit may be much lower. 
    
    The engine configuration message must be sent at any time that the engine configuration map has changed by more than 
    10% of speed or torque (due to events other than boost pressure) since that last time the message was transmitted.  As 
    an alternative, it may be sent periodically, once every 5 s.  It shall also be sent on response to a configuration request 
    message. 
    
    The engine characteristic can be described in one of three modes.  Mode 1 provides a complete curve of speed and 
    torque points (see PGN65251_A).  Modes 2 and 3 provide a partial curve of speed and torque points and a separate 
    endspeed governor characteristic.  In modes 2 and 3, the receiver of the engine configuration message has to calculate 
    the minimum of the engine torque curve and the endspeed governor characteristic to get the final available engine torque. 
    
    Mode 2 provides a high idle point where torque equals zero (point 6) and the endspeed governor gain Kp (see Figure 
    PGN65251_B).  Mode 3 provides the kick-in point of the endspeed governor (point 2) and the governor gain Kp (see 
    Figure PGN65251_C). 
    
    The selection of the three modes can be done by setting the parameters as shown in 'Table PGN65251_A. 
    
    Grandfathered definition for systems that implemented this message prior to July, 2010: On change of torque/speed 
    points of more than 10% since last transmission.  Alternative: Every 5 s. 
    Transmission Repetition Rate: Every 5 s and on change of  torque/speed points of more than 10% since last 
    transmission but no faster than every 500 ms 
    Data Length: 39 
    Extended Data Page: 0 
    Data Page: 0 
    PDU Format: 254 
    PDU Specific: 227 PGN Supporting Information: See Appendix D - PGN 65251 
    Default Priority: 6 
    Parameter Group Number: 65251  (0x00FEE3) 
    Start Position Length Parameter Name SPN 
    */
    uint8_t tx_dat[39];

    /*
    01-02 2 bytes Engine Speed At Idle, Point 1 (Engine Configuration) 188 
    03 1 byte Engine Percent Torque At Idle, Point 1 (Engine Configuration) 539 

    04-05 2 bytes Engine Speed At Point 2 (Engine Configuration) 528 
    06 1 byte Engine Percent Torque At Point 2 (Engine Configuration) 540 

    07-08 2 bytes Engine Speed At Point 3 (Engine Configuration) 529 
    09 1 byte Engine Percent Torque At Point 3 (Engine Configuration) 541 

    10-11 2 bytes Engine Speed At Point 4 (Engine Configuration) 530 
    12 1 byte Engine Percent Torque At Point 4 (Engine Configuration) 542 

    13-14 2 bytes Engine Speed At Point 5 (Engine Configuration) 531 
    15 1 byte Engine Percent Torque At Point 5 (Engine Configuration) 543 
    */
    *(uint16_t *)(&tx_dat[0]) |= j1939_ecu_spn_get_val(188);
    tx_dat[2] |= j1939_ecu_spn_get_val(539);

    *(uint16_t *)(&tx_dat[3]) |= j1939_ecu_spn_get_val(528);
    tx_dat[5] |= j1939_ecu_spn_get_val(540);

    *(uint16_t *)(&tx_dat[6]) |= j1939_ecu_spn_get_val(529);
    tx_dat[8] |= j1939_ecu_spn_get_val(541);

    *(uint16_t *)(&tx_dat[9]) |= j1939_ecu_spn_get_val(530);
    tx_dat[11] |= j1939_ecu_spn_get_val(542);

    *(uint16_t *)(&tx_dat[12]) |= j1939_ecu_spn_get_val(531);
    tx_dat[14] |= j1939_ecu_spn_get_val(543);

    /*
    16-17 2 bytes Engine Speed At High Idle, Point 6 (Engine Configuration) 532 
    18-19 2 bytes Engine Gain (Kp) Of The Endspeed Governor (Engine Configuration) 545 
    20-21 2 bytes Engine Reference Torque (Engine Configuration) 544 
    22-23 2 bytes Engine Maximum Momentary Override Speed, Point 7 (Engine Configuration) 533 
    */
    *(uint16_t *)(&tx_dat[15]) |= j1939_ecu_spn_get_val(532);
    *(uint16_t *)(&tx_dat[17]) |= j1939_ecu_spn_get_val(545);
    *(uint16_t *)(&tx_dat[19]) |= j1939_ecu_spn_get_val(544);
    *(uint16_t *)(&tx_dat[21]) |= j1939_ecu_spn_get_val(533);

    /*
    24 1 byte Engine Maximum Momentary Override Time Limit (Engine Configuration) 534 
    25 1 byte Engine Requested Speed Control Range Lower Limit (Engine Configuration) 535 
    26 1 byte Engine Requested Speed Control Range Upper Limit (Engine Configuration) 536 
    27 1 byte Engine Requested Torque Control Range Lower Limit (Engine Configuration) 537 
    28 1 byte Engine Requested Torque Control Range Upper Limit (Engine Configuration) 538 
    */
    tx_dat[23] |= j1939_ecu_spn_get_val(534);
    tx_dat[24] |= j1939_ecu_spn_get_val(535);
    tx_dat[25] |= j1939_ecu_spn_get_val(536);
    tx_dat[26] |= j1939_ecu_spn_get_val(537);
    tx_dat[27] |= j1939_ecu_spn_get_val(538);

    /*
    29-30 2 bytes Engine Extended Range Requested Speed Control Range Upper Limit (Engine configuration) 1712 
    31-32 2 bytes Engine Moment of Inertia 1794 
    33-34 2 bytes Engine Default Torque Limit 1846 
    */
    *(uint16_t *)(&tx_dat[28]) |= j1939_ecu_spn_get_val(1712);
    *(uint16_t *)(&tx_dat[30]) |= j1939_ecu_spn_get_val(1794);
    *(uint16_t *)(&tx_dat[32]) |= j1939_ecu_spn_get_val(1846);

    /*
    35 8 bits Support Variable Rate TSC1 Message 3344 
    36 8 bits Support TSC1 Control Purpose Group 1 3345 
    37 8 bits Support TSC1 Control Purpose Group 2 3346 
    38 8 bits Support TSC1 Control Purpose Group 3 3347 
    39 8 bits Support TSC1 Control Purpose Group 4 3348 
    */
    tx_dat[34] |= j1939_ecu_spn_get_val(3344);
    tx_dat[35] |= j1939_ecu_spn_get_val(3345);
    tx_dat[36] |= j1939_ecu_spn_get_val(3346);
    tx_dat[37] |= j1939_ecu_spn_get_val(3347);
    tx_dat[38] |= j1939_ecu_spn_get_val(3348);

    if (J1939_TP_TX_Message(65251, J1939_GLOBAL_ADDRESS, tx_dat, 39, Select_CAN_NODE_1) == RC_SUCCESS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

static bool prd_pgn_fun_65247(void)
{
    /*
    PGN 65247 Electronic Engine Controller 3 EEC3 
    Transmission Repetition Rate: 250 msec (preferred) or Engine Speed Dependent (if required by application) 
    Data Length: 8 
    Extended Data Page: 0 
    Data Page: 0 
    PDU Format: 254 
    PDU Specific: 223 PGN Supporting Information:  
    Default Priority: 6 
    Parameter Group Number: 65247  (0x00FEDF) 
    Start Position Length Parameter Name SPN 
    */
    J1939_MESSAGE tx_msg;
    memset(&tx_msg, 0, sizeof(tx_msg));

    tx_msg.Mxe.DataLength    = 8;
    tx_msg.Mxe.DataPage      = 0;
    tx_msg.Mxe.Res           = 0;
    tx_msg.Mxe.PDUFormat     = 254;
    tx_msg.Mxe.PDUSpecific   = 223;
    tx_msg.Mxe.Priority      = 6;
    tx_msg.Mxe.SourceAddress = 0x00;

    /*
    1 1 byte Nominal Friction - Percent Torque 514 
    */
    tx_msg.Mxe.Data[0] |= j1939_ecu_spn_get_val(514);

    /*
    2-3 2 bytes Engine's Desired Operating Speed 515 
    */
    *(uint16_t *)(&tx_msg.Mxe.Data[1]) |= j1939_ecu_spn_get_val(515);

    /*
    4 1 byte Engine's Desired Operating Speed Asymmetry Adjustment 519 
    5 1 byte Estimated Engine Parasitic Losses - Percent Torque 2978 
    */
    tx_msg.Mxe.Data[3] |= j1939_ecu_spn_get_val(519);
    tx_msg.Mxe.Data[4] |= j1939_ecu_spn_get_val(2978);

    /*
    6-7 2 bytes Aftertreatment 1 Exhaust Gas Mass Flow 3236 
    */
    *(uint16_t *)(&tx_msg.Mxe.Data[5]) |= j1939_ecu_spn_get_val(3236);

    /*
    8.1 2 bits Aftertreatment 1 Intake Dew Point 3237 
    8.3 2 bits Aftertreatment 1 Exhaust Dew Point 3238 
    8.5 2 bits Aftertreatment 2 Intake Dew Point 3239 
    8.7 2 bits Aftertreatment 2 Exhaust Dew Point 3240 
    */
    tx_msg.Mxe.Data[7] |= KEEP_BITS_2(j1939_ecu_spn_get_val(3237)) << 0;
    tx_msg.Mxe.Data[7] |= KEEP_BITS_2(j1939_ecu_spn_get_val(3238)) << 2;
    tx_msg.Mxe.Data[7] |= KEEP_BITS_2(j1939_ecu_spn_get_val(3239)) << 4;
    tx_msg.Mxe.Data[7] |= KEEP_BITS_2(j1939_ecu_spn_get_val(3240)) << 6;

    if (J1939_Send_Message(&tx_msg, Select_CAN_NODE_1) == RC_SUCCESS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

static bool prd_pgn_fun_64824(void)
{
    /*
    PGN 64824 Aftertreatment 2 SCR Exhaust Gas Temperature 1 A2SCREGT1
    This message contains SCR catalyst intake and outlet exhaust gas temperature information for aftertreatment system 2
    (or bank 2).
    Transmission Repetition Rate: 500 ms
    Data Length: 8
    Extended Data Page: 0
    Data Page: 0
    PDU Format: 253
    PDU Specific: 56 PGN Supporting Information:
    Default Priority: 6
    Parameter Group Number: 64824 (0x00FD38)
    Start Position Length Parameter Name SPN
    */
    J1939_MESSAGE tx_msg;
    memset(&tx_msg, 0, sizeof(tx_msg));

    tx_msg.Mxe.DataLength    = 8;
    tx_msg.Mxe.DataPage      = 0;
    tx_msg.Mxe.Res           = 0;
    tx_msg.Mxe.PDUFormat     = 253;
    tx_msg.Mxe.PDUSpecific   = 56;
    tx_msg.Mxe.Priority      = 6;
    tx_msg.Mxe.SourceAddress = 0x00;

    /*
    1-2 2 bytes Aftertreatment 2 SCR Catalyst Intake Gas Temperature 4413
    */
    *(uint16_t *)(&tx_msg.Mxe.Data[0]) |= j1939_ecu_spn_get_val(4413);

    /*
    3.1 5 bits Aftertreatment 2 SCR Catalyst Intake Gas Temperature Preliminary FMI 4414
    */
    tx_msg.Mxe.Data[2] |= KEEP_BITS_5(j1939_ecu_spn_get_val(4414)) << 0;

    /*
    4-5 2 bytes Aftertreatment 2 SCR Catalyst Outlet Gas Temperature 4415
    */
    *(uint16_t *)(&tx_msg.Mxe.Data[3]) |= j1939_ecu_spn_get_val(4415);

    /*
    6.1 5 bits Aftertreatment 2 SCR Catalyst Outlet Gas Temperature Preliminary FMI 4416
    */
    tx_msg.Mxe.Data[1] |= KEEP_BITS_5(j1939_ecu_spn_get_val(3218)) << 0;

    if (J1939_Send_Message(&tx_msg, Select_CAN_NODE_1) == RC_SUCCESS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

static bool prd_pgn_fun_64830(void)
{
    /*
    PGN 64830 Aftertreatment 1 SCR Exhaust Gas Temperature 1 A1SCREGT1
    This message contains SCR catalyst intake and outlet exhaust gas temperature information for aftertreatment system 1
    (or bank 1).
    Transmission Repetition Rate: 500 ms
    Data Length: 8
    Extended Data Page: 0
    Data Page: 0
    PDU Format: 253
    PDU Specific: 62 PGN Supporting Information:
    Default Priority: 5
    Parameter Group Number: 64830 (0x00FD3E)
    Start Position Length Parameter Name SPN
    */
    J1939_MESSAGE tx_msg;
    memset(&tx_msg, 0, sizeof(tx_msg));

    tx_msg.Mxe.DataLength    = 8;
    tx_msg.Mxe.DataPage      = 0;
    tx_msg.Mxe.Res           = 0;
    tx_msg.Mxe.PDUFormat     = 253;
    tx_msg.Mxe.PDUSpecific   = 62;
    tx_msg.Mxe.Priority      = 6;
    tx_msg.Mxe.SourceAddress = 0x00;

    /*
    1-2 2 bytes Aftertreatment 1 SCR Catalyst Intake Gas Temperature 4360
    */
    *(uint16_t *)(&tx_msg.Mxe.Data[0]) |= j1939_ecu_spn_get_val(4360);

    /*
    3.1 5 bits Aftertreatment 1 SCR Catalyst Intake Gas Temperature Preliminary FMI 4361
    */
    tx_msg.Mxe.Data[2] |= KEEP_BITS_5(j1939_ecu_spn_get_val(4361)) << 0;

    /*
    4-5 2 bytes Aftertreatment 1 SCR Catalyst Outlet Gas Temperature 4363
    */
    *(uint16_t *)(&tx_msg.Mxe.Data[3]) |= j1939_ecu_spn_get_val(4363);

    /*
    6.1 5 bits Aftertreatment 1 SCR Catalyst Outlet Gas Temperature Preliminary FMI 4362
    */
    tx_msg.Mxe.Data[5] |= KEEP_BITS_5(j1939_ecu_spn_get_val(4362)) << 0;

    if (J1939_Send_Message(&tx_msg, Select_CAN_NODE_1) == RC_SUCCESS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

static bool prd_pgn_fun_61454(void)
{
    /*
    PGN 61454 Aftertreatment 1 Intake Gas 1 AT1IG1
    The purpose of this PGN is to group the aftertreatment intake sensor data for bank 1. These values include the NOx,
    %O2 , Status's of the sensors with respect to the power being supplied and the heating element, errors and stability of the
    readings.
    Transmission Repetition Rate: 50 ms
    Data Length: 8
    Extended Data Page: 0
    Data Page: 0
    PDU Format: 240
    PDU Specific: 14 PGN Supporting Information:
    Default Priority: 6
    Parameter Group Number: 61454 (0x00F00E)
    Start Position Length Parameter Name SPN
    */
    J1939_MESSAGE tx_msg;
    memset(&tx_msg, 0, sizeof(tx_msg));

    tx_msg.Mxe.DataLength    = 8;
    tx_msg.Mxe.DataPage      = 0;
    tx_msg.Mxe.Res           = 0;
    tx_msg.Mxe.PDUFormat     = 240;
    tx_msg.Mxe.PDUSpecific   = 14;
    tx_msg.Mxe.Priority      = 6;
    tx_msg.Mxe.SourceAddress = 0x00;

    /*
    1-2 2 bytes Aftertreatment 1 Intake NOx 3216
    3-4 2 bytes Aftertreatment 1 Intake O2 3217
    */
    *(uint16_t *)(&tx_msg.Mxe.Data[0]) |= j1939_ecu_spn_get_val(3216);
    *(uint16_t *)(&tx_msg.Mxe.Data[2]) |= j1939_ecu_spn_get_val(3217);

    /*
    5.1 2 bits Aftertreatment 1 Intake Gas Sensor Power Status 3218
    5.3 2 bits Aftertreatment 1 Intake Gas Sensor at Temperature 3219
    5.5 2 bits Aftertreatment 1 Intake NOx Reading Stable 3220
    5.7 2 bits Aftertreatment 1 Intake Wide-Range % O2 Reading Stable 3221
    */
    tx_msg.Mxe.Data[4] |= KEEP_BITS_2(j1939_ecu_spn_get_val(3218)) << 0;
    tx_msg.Mxe.Data[4] |= KEEP_BITS_2(j1939_ecu_spn_get_val(3219)) << 2;
    tx_msg.Mxe.Data[4] |= KEEP_BITS_2(j1939_ecu_spn_get_val(3220)) << 4;
    tx_msg.Mxe.Data[4] |= KEEP_BITS_2(j1939_ecu_spn_get_val(3221)) << 6;

    /*
    6.1 5 bits Aftertreatment 1 Intake Gas Sensor Heater Preliminary FMI 3222
    6.6 2 bits Aftertreatment 1 Intake Gas Sensor Heater Control 3223
    */
    tx_msg.Mxe.Data[5] |= KEEP_BITS_5(j1939_ecu_spn_get_val(3222)) << 0;
    tx_msg.Mxe.Data[5] |= KEEP_BITS_2(j1939_ecu_spn_get_val(3223)) << 5;

    /*
    7.1 5 bits Aftertreatment 1 Intake NOx Sensor Preliminary FMI 3224
    7.6 3 bits NOx Sensor ATI1 Self-diagnosis Status 5714
    */
    tx_msg.Mxe.Data[6] |= KEEP_BITS_5(j1939_ecu_spn_get_val(3224)) << 0;
    tx_msg.Mxe.Data[6] |= KEEP_BITS_3(j1939_ecu_spn_get_val(5714)) << 5;

    /*
     8.1 5 bits Aftertreatment 1 Intake Oxygen Sensor Preliminary FMI 3225
   */
    tx_msg.Mxe.Data[7] |= KEEP_BITS_5(j1939_ecu_spn_get_val(3225)) << 0;

    if (J1939_Send_Message(&tx_msg, Select_CAN_NODE_1) == RC_SUCCESS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

static bool prd_pgn_fun_61456(void)
{
    /*
    PGN 61456 Aftertreatment 2 Intake Gas 1 AT2IG1
    The purpose of this PGN is to group the aftertreatment intake sensor data for bank 2. These values include the NOx,
    %O2, status of the sensors with respect to the power being supplied and the heating element, errors and stability of the
    readings.
    Transmission Repetition Rate: 50 ms
    Data Length: 8
    Extended Data Page: 0
    Data Page: 0
    PDU Format: 240
    PDU Specific: 16 PGN Supporting Information:
    Default Priority: 6
    Parameter Group Number: 61456 (0x00F010)
    Start Position Length Parameter Name SPN
    */
    J1939_MESSAGE tx_msg;
    memset(&tx_msg, 0, sizeof(tx_msg));

    tx_msg.Mxe.DataLength    = 8;
    tx_msg.Mxe.DataPage      = 0;
    tx_msg.Mxe.Res           = 0;
    tx_msg.Mxe.PDUFormat     = 240;
    tx_msg.Mxe.PDUSpecific   = 16;
    tx_msg.Mxe.Priority      = 6;
    tx_msg.Mxe.SourceAddress = 0x00;

    /*
    1-2 2 bytes Aftertreatment 2 Intake NOx 3255
    3-4 2 bytes Aftertreatment 2 Intake O2 3256
    */
    *(uint16_t *)(&tx_msg.Mxe.Data[0]) |= j1939_ecu_spn_get_val(3255);
    *(uint16_t *)(&tx_msg.Mxe.Data[2]) |= j1939_ecu_spn_get_val(3256);

    /*
    5.1 2 bits Aftertreatment 2 Intake Gas Sensor Power Status 3257
    5.3 2 bits Aftertreatment 2 Intake Gas Sensor at Temperature 3258
    5.5 2 bits Aftertreatment 2 Intake NOx Reading Stable 3259
    5.7 2 bits Aftertreatment 2 Intake Wide-Range % O2 Reading Stable 3260
    */
    tx_msg.Mxe.Data[4] |= KEEP_BITS_2(j1939_ecu_spn_get_val(3257)) << 0;
    tx_msg.Mxe.Data[4] |= KEEP_BITS_2(j1939_ecu_spn_get_val(3258)) << 2;
    tx_msg.Mxe.Data[4] |= KEEP_BITS_2(j1939_ecu_spn_get_val(3259)) << 4;
    tx_msg.Mxe.Data[4] |= KEEP_BITS_2(j1939_ecu_spn_get_val(3260)) << 6;

    /*
    6.1 5 bits Aftertreatment 2 Intake Gas Sensor Heater Preliminary FMI 3261
    6.6 2 bits Aftertreatment 2 Intake Gas Sensor Heater Control 3262
    */
    tx_msg.Mxe.Data[5] |= KEEP_BITS_5(j1939_ecu_spn_get_val(3261)) << 0;
    tx_msg.Mxe.Data[5] |= KEEP_BITS_2(j1939_ecu_spn_get_val(3262)) << 5;

    /*
    7.1 5 bits Aftertreatment 2 Intake NOx Sensor Preliminary FMI 3263
    7.6 3 bits NOx Sensor ATI2 Self-diagnosis Status 5716
    */
    tx_msg.Mxe.Data[6] |= KEEP_BITS_5(j1939_ecu_spn_get_val(3263)) << 0;
    tx_msg.Mxe.Data[6] |= KEEP_BITS_3(j1939_ecu_spn_get_val(5716)) << 5;

    /*
    8.1 5 bits Aftertreatment 2 Intake Oxygen Sensor Preliminary FMI 3264
    */
    tx_msg.Mxe.Data[7] |= KEEP_BITS_5(j1939_ecu_spn_get_val(3264)) << 0;

    if (J1939_Send_Message(&tx_msg, Select_CAN_NODE_1) == RC_SUCCESS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

static bool prd_pgn_fun_61457(void)
{
    /*
    PGN 61457 Aftertreatment 2 Outlet Gas 1 AT2OG1
    The purpose of this PGN is to group the aftertreatment outlet sensor data for bank 2. These values include the NOx,
    %O2, status of the sensors with respect to the power being supplied and the heating element, errors and stability of the
    readings.
    Transmission Repetition Rate: 50 ms
    Data Length: 8
    Extended Data Page: 0
    Data Page: 0
    PDU Format: 240
    PDU Specific: 17 PGN Supporting Information:
    Default Priority: 6
    Parameter Group Number: 61457 (0x00F011)
    Start Position Length Parameter Name SPN
    */
    J1939_MESSAGE tx_msg;
    memset(&tx_msg, 0, sizeof(tx_msg));

    tx_msg.Mxe.DataLength    = 8;
    tx_msg.Mxe.DataPage      = 0;
    tx_msg.Mxe.Res           = 0;
    tx_msg.Mxe.PDUFormat     = 240;
    tx_msg.Mxe.PDUSpecific   = 17;
    tx_msg.Mxe.Priority      = 6;
    tx_msg.Mxe.SourceAddress = 0x00;

    /*
    1-2 2 bytes Aftertreatment 2 Outlet NOx 3265
    3-4 2 bytes Aftertreatment 2 Outlet O2 3266
    */
    *(uint16_t *)(&tx_msg.Mxe.Data[0]) |= j1939_ecu_spn_get_val(3265);
    *(uint16_t *)(&tx_msg.Mxe.Data[2]) |= j1939_ecu_spn_get_val(3266);

    /*
    5.1 2 bits Aftertreatment 2 Outlet Gas Sensor Power Status 3267
    5.3 2 bits Aftertreatment 2 Outlet Gas Sensor at Temperature 3268
    5.5 2 bits Aftertreatment 2 Outlet NOx Reading Stable 3269
    5.7 2 bits Aftertreatment 2 Outlet Wide-Range % O2 Reading Stable 3270
    */
    tx_msg.Mxe.Data[4] |= KEEP_BITS_2(j1939_ecu_spn_get_val(3267)) << 0;
    tx_msg.Mxe.Data[4] |= KEEP_BITS_2(j1939_ecu_spn_get_val(3268)) << 2;
    tx_msg.Mxe.Data[4] |= KEEP_BITS_2(j1939_ecu_spn_get_val(3269)) << 4;
    tx_msg.Mxe.Data[4] |= KEEP_BITS_2(j1939_ecu_spn_get_val(3270)) << 6;

    /*
    6.1 5 bits Aftertreatment 2 Outlet Gas Sensor Heater Preliminary FMI 3271
    6.6 2 bits Aftertreatment 2 Outlet Gas Sensor Heater Control 3272
    */
    tx_msg.Mxe.Data[5] |= KEEP_BITS_5(j1939_ecu_spn_get_val(3271)) << 0;
    tx_msg.Mxe.Data[5] |= KEEP_BITS_2(j1939_ecu_spn_get_val(3272)) << 5;

    /*
    7.1 5 bits Aftertreatment 2 Outlet NOx Sensor Preliminary FMI 3273
    7.6 3 bits NOx Sensor ATO2 Self-diagnosis Status 5715
    */
    tx_msg.Mxe.Data[6] |= KEEP_BITS_5(j1939_ecu_spn_get_val(3273)) << 0;
    tx_msg.Mxe.Data[6] |= KEEP_BITS_3(j1939_ecu_spn_get_val(5715)) << 5;

    /*
    8.1 5 bits Aftertreatment 2 Outlet Oxygen Sensor Preliminary FMI 3274
    */
    tx_msg.Mxe.Data[7] |= KEEP_BITS_5(j1939_ecu_spn_get_val(3274)) << 0;

    if (J1939_Send_Message(&tx_msg, Select_CAN_NODE_1) == RC_SUCCESS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

static bool prd_pgn_fun_65110(void)
{
    /*
    PGN 65110 Aftertreatment 1 Diesel Exhaust Fluid Tank 1 Information AT1T1I 
    Contains information on various tank levels 
    Transmission Repetition Rate: 1 s 
    Data Length: 8 
    Extended Data Page: 0 
    Data Page: 0 
    PDU Format: 254 
    PDU Specific: 86 PGN Supporting Information:  
    Default Priority: 6 
    Parameter Group Number: 65110  (0x00FE56) 
    Start Position Length Parameter Name SPN 
    */
    J1939_MESSAGE tx_msg;
    memset(&tx_msg, 0, sizeof(tx_msg));

    tx_msg.Mxe.DataLength    = 8;
    tx_msg.Mxe.DataPage      = 0;
    tx_msg.Mxe.Res           = 0;
    tx_msg.Mxe.PDUFormat     = 254;
    tx_msg.Mxe.PDUSpecific   = 86;
    tx_msg.Mxe.Priority      = 6;
    tx_msg.Mxe.SourceAddress = 0x00;

    /*
    1 1 byte Aftertreatment 1 Diesel Exhaust Fluid Tank Level 1761 
    2 1 byte Aftertreatment 1 Diesel Exhaust Fluid Tank Temperature 3031 
    */
    tx_msg.Mxe.Data[0] |= j1939_ecu_spn_get_val(1761);
    tx_msg.Mxe.Data[1] |= j1939_ecu_spn_get_val(3031);

    /*
    3-4 2 bytes Aftertreatment 1 Diesel Exhaust Fluid Tank Level 2 3517 
    */
    *(uint16_t *)(&tx_msg.Mxe.Data[2]) |= j1939_ecu_spn_get_val(3517);

    /*
    5.1 5 bits Aftertreatment 1 Diesel Exhaust Fluid Tank Level Preliminary FMI 3532 
    5.6 3 bits Aftertreatment Selective Catalytic Reduction Operator Inducement Active 5245 
    */
    tx_msg.Mxe.Data[4] |= KEEP_BITS_5(j1939_ecu_spn_get_val(3532)) << 0;
    tx_msg.Mxe.Data[4] |= KEEP_BITS_3(j1939_ecu_spn_get_val(5245)) << 5;

    /*
    6.1 5 bits Aftertreatment 1 Diesel Exhaust Fluid Tank 1 Temperature Preliminary FMI 4365 
    6.6 3 bits Aftertreatment SCR Operator Inducement Severity 5246 
    */
    tx_msg.Mxe.Data[5] |= KEEP_BITS_5(j1939_ecu_spn_get_val(4365)) << 0;
    tx_msg.Mxe.Data[5] |= KEEP_BITS_3(j1939_ecu_spn_get_val(5246)) << 5;

    /*
    7 1 byte Aftertreatment 1 Diesel Exhaust Fluid Tank Heater 3363 
    */
    tx_msg.Mxe.Data[6] |= j1939_ecu_spn_get_val(3363);

    /*
    8.1 5 bits Aftertreatment 1 Diesel Exhaust Fluid Tank 1 Heater Preliminary FMI 4366 
    */
    tx_msg.Mxe.Data[7] |= KEEP_BITS_5(j1939_ecu_spn_get_val(3218)) << 0;

    if (J1939_Send_Message(&tx_msg, Select_CAN_NODE_1) == RC_SUCCESS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

static bool prd_pgn_fun_64947(void)
{
    /*
    PGN 64947 Aftertreatment 1 Outlet Gas 2 AT1OG2 
    The purpose of this PGN is to group the aftertreatment outlet gas temperature messages. 
    Transmission Repetition Rate: 500 ms 
    Data Length: 8 
    Extended Data Page: 0 
    Data Page: 0 
    PDU Format: 253 
    PDU Specific: 179 PGN Supporting Information: See Appendix D - PGN 64948 
    Default Priority: 6 
    Parameter Group Number: 64947  (0x00FDB3) 
    Start Position Length Parameter Name SPN 
    */
    J1939_MESSAGE tx_msg;
    memset(&tx_msg, 0, sizeof(tx_msg));

    tx_msg.Mxe.DataLength    = 8;
    tx_msg.Mxe.DataPage      = 0;
    tx_msg.Mxe.Res           = 0;
    tx_msg.Mxe.PDUFormat     = 253;
    tx_msg.Mxe.PDUSpecific   = 179;
    tx_msg.Mxe.Priority      = 6;
    tx_msg.Mxe.SourceAddress = 0x00;

    /*
    1-2 2 bytes Aftertreatment 1 Exhaust Gas Temperature 3 3245 
    3-4 2 bytes Aftertreatment 1 Diesel Particulate Filter Outlet Gas Temperature 3246 
    */
    *(uint16_t *)(&tx_msg.Mxe.Data[0]) |= j1939_ecu_spn_get_val(3245);
    *(uint16_t *)(&tx_msg.Mxe.Data[2]) |= j1939_ecu_spn_get_val(3246);

    /*
    5.1 5 bits Aftertreatment 1 Exhaust Gas Temperature 3 Preliminary FMI 3247 
    */
    tx_msg.Mxe.Data[4] |= KEEP_BITS_5(j1939_ecu_spn_get_val(3247)) << 0;

    /*
    6.1 5 bits Aftertreatment 1 Diesel Particulate Filter Outlet Exhaust Gas Temperature  Preliminary FMI 3248 
    */
    tx_msg.Mxe.Data[5] |= KEEP_BITS_5(j1939_ecu_spn_get_val(3248)) << 0;

    if (J1939_Send_Message(&tx_msg, Select_CAN_NODE_1) == RC_SUCCESS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

static bool prd_pgn_fun_64948(void)
{
    /*
    PGN 64948 Aftertreatment 1 Intake Gas 2 AT1IG2 
    The purpose of this PGN is to group the aftertreatment intake gas temperature messages for bank 1. 
    Transmission Repetition Rate: 500 ms 
    Data Length: 8 
    Extended Data Page: 0 
    Data Page: 0 
    PDU Format: 253 
    PDU Specific: 180 PGN Supporting Information: See Appendix D - PGN 64948 
    Default Priority: 6 
    Parameter Group Number: 64948  (0x00FDB4) 
    Start Position Length Parameter Name SPN 
    */
    J1939_MESSAGE tx_msg;
    memset(&tx_msg, 0, sizeof(tx_msg));

    tx_msg.Mxe.DataLength    = 8;
    tx_msg.Mxe.DataPage      = 0;
    tx_msg.Mxe.Res           = 0;
    tx_msg.Mxe.PDUFormat     = 253;
    tx_msg.Mxe.PDUSpecific   = 180;
    tx_msg.Mxe.Priority      = 6;
    tx_msg.Mxe.SourceAddress = 0x00;

    /*
    1-2 2 bytes Aftertreatment 1 Exhaust Gas Temperature 1 3241 
    3-4 2 bytes Aftertreatment 1 Diesel Particulate Filter Intake Gas Temperature 3242 
    */
    *(uint16_t *)(&tx_msg.Mxe.Data[0]) |= j1939_ecu_spn_get_val(3241);
    *(uint16_t *)(&tx_msg.Mxe.Data[2]) |= j1939_ecu_spn_get_val(3242);

    /*
    5.1 5 bits Aftertreatment 1 Exhaust Gas Temperature 1 Preliminary FMI 3243 
    */
    tx_msg.Mxe.Data[4] |= KEEP_BITS_5(j1939_ecu_spn_get_val(3243)) << 0;

    /*
    6.1 5 bits Aftertreatment 1 Diesel Particulate Filter Intake Gas Temperature Preliminary FMI 3244 
    */
    tx_msg.Mxe.Data[5] |= KEEP_BITS_5(j1939_ecu_spn_get_val(3244)) << 0;

    if (J1939_Send_Message(&tx_msg, Select_CAN_NODE_1) == RC_SUCCESS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

static bool prd_pgn_fun_64945(void)
{
    /*
    PGN 64945 Aftertreatment 2 Intake Gas 2 AT2IG2 
    The purpose of this PGN is to group the aftertreatment intake gas temperature messages for bank 2. 
    Transmission Repetition Rate: 500 ms 
    Data Length: 8 
    Extended Data Page: 0 
    Data Page: 0 
    PDU Format: 253 
    PDU Specific: 177 PGN Supporting Information: See Appendix D - PGN 64948 
    Default Priority: 6 
    Parameter Group Number: 64945  (0x00FDB1) 
    Start Position Length Parameter Name SPN 
    */
    J1939_MESSAGE tx_msg;
    memset(&tx_msg, 0, sizeof(tx_msg));

    tx_msg.Mxe.DataLength    = 8;
    tx_msg.Mxe.DataPage      = 0;
    tx_msg.Mxe.Res           = 0;
    tx_msg.Mxe.PDUFormat     = 253;
    tx_msg.Mxe.PDUSpecific   = 144;
    tx_msg.Mxe.Priority      = 6;
    tx_msg.Mxe.SourceAddress = 0x00;

    /*
    1-2 2 bytes Aftertreatment 2 Exhaust Gas Temperature 1 3275 
    3-4 2 bytes Aftertreatment 2 Diesel Particulate Filter Intake Gas Temperature 3276 
    */
    *(uint16_t *)(&tx_msg.Mxe.Data[0]) |= j1939_ecu_spn_get_val(3275);
    *(uint16_t *)(&tx_msg.Mxe.Data[2]) |= j1939_ecu_spn_get_val(3276);

    /*
     5.1 5 bits Aftertreatment 2 Exhaust Gas Temperature 1 Preliminary FMI 3277 
   */
    tx_msg.Mxe.Data[4] |= KEEP_BITS_5(j1939_ecu_spn_get_val(3277)) << 0;

    /*
    6.1 5 bits Aftertreatment 2 Diesel Particulate Filter Intake Gas Temperature Preliminary FMI 3278 
    */
    tx_msg.Mxe.Data[5] |= KEEP_BITS_5(j1939_ecu_spn_get_val(3278)) << 0;

    if (J1939_Send_Message(&tx_msg, Select_CAN_NODE_1) == RC_SUCCESS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

static bool prd_pgn_fun_64944(void)
{
    /*
    PGN 64944 Aftertreatment 2 Outlet Gas 2 AT2OG2 
    The purpose of this PGN is to group the aftertreatment outlet gas temperature messages for bank 2. 
    Transmission Repetition Rate: 500 ms 
    Data Length: 8 
    Extended Data Page: 0 
    Data Page: 0 
    PDU Format: 253 
    PDU Specific: 176 PGN Supporting Information: See Appendix D - PGN 64948 
    Default Priority: 6 
    Parameter Group Number: 64944  (0x00FDB0) 
    Start Position Length Parameter Name SPN 
    */
    J1939_MESSAGE tx_msg;
    memset(&tx_msg, 0, sizeof(tx_msg));

    tx_msg.Mxe.DataLength    = 8;
    tx_msg.Mxe.DataPage      = 0;
    tx_msg.Mxe.Res           = 0;
    tx_msg.Mxe.PDUFormat     = 253;
    tx_msg.Mxe.PDUSpecific   = 176;
    tx_msg.Mxe.Priority      = 6;
    tx_msg.Mxe.SourceAddress = 0x00;

    /*
    1-2 2 bytes Aftertreatment 2 Exhaust Gas Temperature 3 3279 
    3-4 2 bytes Aftertreatment 2 Diesel Particulate Filter Outlet Gas Temperature 3280 
    */
    *(uint16_t *)(&tx_msg.Mxe.Data[0]) |= j1939_ecu_spn_get_val(3279);
    *(uint16_t *)(&tx_msg.Mxe.Data[2]) |= j1939_ecu_spn_get_val(3280);

    /*
    5.1 5 bits Aftertreatment 2 Exhaust Gas Temperature 3 Preliminary FMI 3281 
    */
    tx_msg.Mxe.Data[4] |= KEEP_BITS_5(j1939_ecu_spn_get_val(3281)) << 0;

    /*
    6.1 5 bits Aftertreatment 2 Diesel Particulate Filter Exhaust Gas Temperature  Preliminary FMI 3282  
    */
    tx_msg.Mxe.Data[5] |= KEEP_BITS_5(j1939_ecu_spn_get_val(3282)) << 0;

    if (J1939_Send_Message(&tx_msg, Select_CAN_NODE_1) == RC_SUCCESS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

static bool prd_pgn_fun_64943(void)
{
    /*
    PGN 64943 Aftertreatment 2 Intermediate Gas AT2IMG 
    The purpose of this PGN is to group the aftertreatment intermediate gas temperature and pressure messages for bank 2. 
    Transmission Repetition Rate: 500 ms 
    Data Length: 8 
    Extended Data Page: 0 
    Data Page: 0 
    PDU Format: 253 
    PDU Specific: 175 PGN Supporting Information: See Appendix D - PGN 64948 
    Default Priority: 6 
    Parameter Group Number: 64943  (0x00FDAF) 
    Start Position Length Parameter Name SPN 
    */
    J1939_MESSAGE tx_msg;
    memset(&tx_msg, 0, sizeof(tx_msg));

    tx_msg.Mxe.DataLength    = 8;
    tx_msg.Mxe.DataPage      = 0;
    tx_msg.Mxe.Res           = 0;
    tx_msg.Mxe.PDUFormat     = 253;
    tx_msg.Mxe.PDUSpecific   = 175;
    tx_msg.Mxe.Priority      = 6;
    tx_msg.Mxe.SourceAddress = 0x00;

    /*
    1-2 2 bytes Aftertreatment 2 Exhaust Gas Temperature 2 3283 
    3-4 2 bytes Aftertreatment 2 Diesel Particulate Filter Intermediate Gas Temperature 3284 
    5-6 2 bytes Aftertreatment 2 Diesel Particulate Filter Differential Pressure 3285 
    */
    *(uint16_t *)(&tx_msg.Mxe.Data[0]) |= j1939_ecu_spn_get_val(3283);
    *(uint16_t *)(&tx_msg.Mxe.Data[2]) |= j1939_ecu_spn_get_val(3284);
    *(uint16_t *)(&tx_msg.Mxe.Data[4]) |= j1939_ecu_spn_get_val(3285);

    /*
    7.1 5 bits Aftertreatment 2 Exhaust Gas Temperature 2 Preliminary FMI 3286 
    */
    tx_msg.Mxe.Data[6] |= KEEP_BITS_5(j1939_ecu_spn_get_val(3286)) << 0;

    /*
    7.6-8.1 5 bits Aftertreatment 2 Diesel Particulate Filter Delta Pressure Preliminary FMI 3287 
    */
    *(uint16_t *)(&tx_msg.Mxe.Data[6]) |= KEEP_BITS_2(j1939_ecu_spn_get_val(3287)) << 5;

    /*
    8.3 5 bits Aftertreatment 2 Diesel Particulate Filter Intermediate Gas Temperature Preliminary FMI 3288 
    */
    tx_msg.Mxe.Data[7] |= KEEP_BITS_2(j1939_ecu_spn_get_val(3218)) << 2;

    if (J1939_Send_Message(&tx_msg, Select_CAN_NODE_1) == RC_SUCCESS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

static bool prd_pgn_fun_64946(void)
{
    /*
    PGN 64946 Aftertreatment 1 Intermediate Gas 
    The purpose of this PGN is to group the aftertreatment intermediate gas temperature and pressure messages.
    Note: The 5 bits of SPN 3253 are positioned into the data field in the following manner. The 2 most significant bits are
    placed in bits 2-1 of byte 8 such that the most significant bit of SPN 3253 located at byte 8 bit 2, and the 3 least significant
    bits are placed in bits 8-6 of byte 7 such that the least significant bit of SPN 3253 located at byte 7 bit 6.
    Transmission Repetition Rate: 500 ms
    Data Length: 8
    Extended Data Page: 0
    Data Page: 0
    PDU Format: 253
    PDU Specific: 178 PGN Supporting Information: See Appendix D - PGN 64948
    Default Priority: 6
    Parameter Group Number: 64946 (0x00FDB2)
    Start Position Length Parameter Name SPN
    */
    J1939_MESSAGE tx_msg;
    memset(&tx_msg, 0, sizeof(tx_msg));

    tx_msg.Mxe.DataLength    = 8;
    tx_msg.Mxe.DataPage      = 0;
    tx_msg.Mxe.Res           = 0;
    tx_msg.Mxe.PDUFormat     = 253;
    tx_msg.Mxe.PDUSpecific   = 178;
    tx_msg.Mxe.Priority      = 6;
    tx_msg.Mxe.SourceAddress = 0x00;

    /*
    1-2 2 bytes Aftertreatment 1 Exhaust Gas Temperature 2 3249
    3-4 2 bytes Aftertreatment 1 Diesel Particulate Filter Intermediate GasTemperature 3250
    5-6 2 bytes Aftertreatment 1 Diesel Particulate Filter Differential Pressure 3251
    */
    *(uint16_t *)(&tx_msg.Mxe.Data[0]) |= j1939_ecu_spn_get_val(3249);
    *(uint16_t *)(&tx_msg.Mxe.Data[2]) |= j1939_ecu_spn_get_val(3250);
    *(uint16_t *)(&tx_msg.Mxe.Data[4]) |= j1939_ecu_spn_get_val(3251);

    /*
    7.1 5 bits Aftertreatment 1 Exhaust Gas Temperature 2 Preliminary FMI 3252
    */
    tx_msg.Mxe.Data[6] |= KEEP_BITS_5(j1939_ecu_spn_get_val(3252)) << 0;

    /*
    7.6-8.1 5 bits Aftertreatment 1 Diesel Particulate Filter Delta PressurePreliminary FMI 3253
    */
    *(uint16_t *)(&tx_msg.Mxe.Data[6]) |= KEEP_BITS_2(j1939_ecu_spn_get_val(3253)) << 5;

    /*
    8.3 5 bits Aftertreatment 1 Diesel Particulate Filter Intermediate GasTemperature Preliminary FMI 3254
    */
    tx_msg.Mxe.Data[7] |= KEEP_BITS_2(j1939_ecu_spn_get_val(3254)) << 2;

    if (J1939_Send_Message(&tx_msg, Select_CAN_NODE_1) == RC_SUCCESS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

static bool prd_pgn_fun_65217(void)
{
    /*
        PGN 65217 High Resolution Vehicle Distance VDHR 
        Transmission Repetition Rate: 1 s 
        Data Length: 8 
        Extended Data Page: 0 
        Data Page: 0 
        PDU Format: 254 
        PDU Specific: 193 PGN Supporting Information:  
        Default Priority: 6 
        Parameter Group Number: 65217  (0x00FEC1) 
        Start Position Length Parameter Name SPN 
        1-4 4 bytes High Resolution Total Vehicle Distance 917 
        5-8 4 bytes High Resolution Trip Distance 918 
        */
    J1939_MESSAGE tx_msg;
    memset(&tx_msg, 0, sizeof(tx_msg));

    tx_msg.Mxe.DataLength    = 8;
    tx_msg.Mxe.DataPage      = 0;
    tx_msg.Mxe.Res           = 0;
    tx_msg.Mxe.PDUFormat     = 254;
    tx_msg.Mxe.PDUSpecific   = 193;
    tx_msg.Mxe.Priority      = 6;
    tx_msg.Mxe.SourceAddress = 0x00;

    *(uint32_t *)(&tx_msg.Mxe.Data[0]) |= j1939_ecu_spn_get_val(917);
    *(uint32_t *)(&tx_msg.Mxe.Data[4]) |= j1939_ecu_spn_get_val(918);

    if (J1939_Send_Message(&tx_msg, Select_CAN_NODE_1) == RC_SUCCESS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

static bool prd_pgn_fun_64821(void)
{
    /*
    PGN 64821 Aftertreatment 2 SCR Reagant Tank 1 Information A2SCRRT1I 
    This message contains SCR reagent tank 1 information for aftertreatment system 2 (or bank 2).  The first tank for the 
    aftertreatment sytem is primary reagent storage tank. 
    Transmission Repetition Rate: 1 s 
    Data Length: 8 
    Extended Data Page: 0 
    Data Page: 0 
    PDU Format: 253 
    PDU Specific: 53 PGN Supporting Information:  
    Default Priority: 6 
    Parameter Group Number: 64821  (0x00FD35) 
    Start Position Length Parameter Name SPN 
    */
    J1939_MESSAGE tx_msg;
    memset(&tx_msg, 0, sizeof(tx_msg));

    tx_msg.Mxe.DataLength    = 8;
    tx_msg.Mxe.DataPage      = 0;
    tx_msg.Mxe.Res           = 0;
    tx_msg.Mxe.PDUFormat     = 253;
    tx_msg.Mxe.PDUSpecific   = 53;
    tx_msg.Mxe.Priority      = 6;
    tx_msg.Mxe.SourceAddress = 0x00;

    /*
    1 1 byte Aftertreatment 2 Diesel Exhaust Fluid Tank Level 4426 
    2 1 byte Aftertreatment 2 Diesel Exhaust Fluid Tank Temperature 4427 
    */
    tx_msg.Mxe.Data[0] |= j1939_ecu_spn_get_val(4426);
    tx_msg.Mxe.Data[1] |= j1939_ecu_spn_get_val(4427);

    /*
    3-4 2 bytes Aftertreatment 2 Diesel Exhaust Fluid Tank Level 2 4428 
    */
    *(uint16_t *)(&tx_msg.Mxe.Data[2]) |= j1939_ecu_spn_get_val(4428);

    /*
    5.1 5 bits Aftertreatment 2 Diesel Exhaust Fluid Tank Level Preliminary FMI 4429 
    */
    tx_msg.Mxe.Data[4] |= KEEP_BITS_5(j1939_ecu_spn_get_val(4429)) << 0;

    /*
    6.1 5 bits Aftertreatment 2 Diesel Exhaust Fluid Tank 1 Temperature Preliminary FMI 4430 
    */
    tx_msg.Mxe.Data[5] |= KEEP_BITS_5(j1939_ecu_spn_get_val(4430)) << 0;

    /*
    7 1 byte Aftertreatment 2 Diesel Exhaust Fluid Tank Heater 4431 
    */
    tx_msg.Mxe.Data[6] |= j1939_ecu_spn_get_val(4431);

    /*
    8.1 5 bits Aftertreatment 2 Diesel Exhaust Fluid Tank 1 Heater Preliminary FMI 4432 
    */
    tx_msg.Mxe.Data[7] |= KEEP_BITS_5(j1939_ecu_spn_get_val(4432)) << 0;

    if (J1939_Send_Message(&tx_msg, Select_CAN_NODE_1) == RC_SUCCESS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

static bool prd_pgn_fun_64820(void)
{
    /*
        PGN 64820 Aftertreatment 2 SCR Reagant Tank 2 Information A2SCRRT2I 
        This message contains SCR reagent tank 2 information for aftertreatment system 2 (or bank 2).  The second tank for the 
        aftertreatment system is usually a smaller quick-thaw reagent tank located in series with tank 1. 
        Transmission Repetition Rate: 1 s 
        Data Length: 8 
        Extended Data Page: 0 
        Data Page: 0 
        PDU Format: 253 
        PDU Specific: 52 PGN Supporting Information:  
        Default Priority: 6 
        Parameter Group Number: 64820  (0x00FD34) 
        Start Position Length Parameter Name SPN 
    */
    J1939_MESSAGE tx_msg;
    memset(&tx_msg, 0, sizeof(tx_msg));

    tx_msg.Mxe.DataLength    = 8;
    tx_msg.Mxe.DataPage      = 0;
    tx_msg.Mxe.Res           = 0;
    tx_msg.Mxe.PDUFormat     = 253;
    tx_msg.Mxe.PDUSpecific   = 52;
    tx_msg.Mxe.Priority      = 6;
    tx_msg.Mxe.SourceAddress = 0x00;

    /*
    1 1 byte Aftertreatment 2 Diesel Exhaust Fluid Tank 2 Level 4433 
    2 1 byte Aftertreatment 2 Diesel Exhaust Fluid Tank 2 Temperature 4434 
    */
    tx_msg.Mxe.Data[0] |= j1939_ecu_spn_get_val(4433);
    tx_msg.Mxe.Data[1] |= j1939_ecu_spn_get_val(4434);

    /*
    3-4 2 bytes Aftertreatment 2 Diesel Exhaust Fluid Tank 2 Level 2 4435 
    */
    *(uint16_t *)(&tx_msg.Mxe.Data[2]) |= j1939_ecu_spn_get_val(4435);

    /*
    5.1 5 bits Aftertreatment 2 Diesel Exhaust Fluid Tank 2 Level Preliminary FMI 4436 
    */
    tx_msg.Mxe.Data[4] |= KEEP_BITS_5(j1939_ecu_spn_get_val(4436)) << 0;

    /*
    6.1 5 bits Aftertreatment 2 Diesel Exhaust Fluid Tank 2 Temperature Prelminary FMI 4437 
   */
    tx_msg.Mxe.Data[5] |= KEEP_BITS_5(j1939_ecu_spn_get_val(4437)) << 0;

    /*
    7 4 bits Aftertreatment 2 Diesel Exhaust Fluid Tank 2 Heater 4438 
    */
    tx_msg.Mxe.Data[6] |= KEEP_BITS_4(j1939_ecu_spn_get_val(4438)) << 0;

    /*
    8.1 5 bits Aftertreatment 2 Diesel Exhaust Fluid Tank 2 Heater Prelminary FMI 4439 
    */
    tx_msg.Mxe.Data[7] |= KEEP_BITS_5(j1939_ecu_spn_get_val(4439)) << 0;

    if (J1939_Send_Message(&tx_msg, Select_CAN_NODE_1) == RC_SUCCESS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void j1939_ecu_pgn_prd_task(void)
{
    uint16_t i;
    for (i = 0; i < SIZEOF_ARRAY(s_pgn_prd_l); i++)
    {
        if (s_pgn_prd_l[i].cnt < s_pgn_prd_l[i].period)
        {
            continue;
        }

        if (s_pgn_prd_l[i].en == false)
        {
            continue;
        }

        if (s_pgn_prd_l[i].cbk != NULL)
        {
            if (s_pgn_prd_l[i].cbk() == true)
            {
                s_pgn_prd_l[i].cnt = 0;
            }
        }
        else
        {
            s_pgn_prd_l[i].cnt = 0;
        }
    }
}

void j1939_ecu_pgn_prd_1ms(void)
{
    uint16_t i;

    for (i = 0; i < SIZEOF_ARRAY(s_pgn_prd_l); i++)
    {
        if (s_pgn_prd_l[i].cnt < s_pgn_prd_l[i].period)
        {
            s_pgn_prd_l[i].cnt++;
        }
    }
}

void j1939_ecu_pgn_prd_init(void)
{
    bsp_tim_reg_cbk_1ms(j1939_ecu_pgn_prd_1ms);
}

bool j1939_ecu_pgn_prd_cfg(uint16_t pgn, bool stts)
{
    uint16_t i;

    if (pgn == 0xFFFF) // 全部PGN都配置
    {
        for (i = 0; i < SIZEOF_ARRAY(s_pgn_prd_l); i++)
        {
            s_pgn_prd_l[i].en = stts;
        }
    }

    for (i = 0; i < SIZEOF_ARRAY(s_pgn_prd_l); i++)
    {
        if (s_pgn_prd_l[i].no == pgn)
        {
            s_pgn_prd_l[i].en = stts;
            return true;
        }
    }
    return false;
}
#if USE_J1939_ECU_PRD_SHELL == 1
// SHELL_EXPORT_CMD(属性, 命令名, 函数, 描述)
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0) | SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC),
                 prdpgn,
                 j1939_ecu_pgn_prd_cfg,
                 "prdpgn 65276 0:关闭PGN65276的输出");
#endif

#endif /* end of USE_J1939_ECU_PRD */
