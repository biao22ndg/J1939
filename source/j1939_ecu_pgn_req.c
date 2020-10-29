/* Attention, read head file at first. ****************************************/
/* Includes ------------------------------------------------------------------*/
#include "j1939_ecu_pgn_req.h"
#if USE_J1939_ECU_REQ == 1

#include <string.h>

#include "j1939.h"
#include "j1939_ecu_spn.h"

#if USE_J1939_ECU_REQ_SHELL == 1
#include "shell.h"
#endif

/* Constants -----------------------------------------------------------------*/
/* Define --------------------------------------------------------------------*/
/* Macro ---------------------------------------------------------------------*/
#ifndef SIZEOF_ARRAY
#define SIZEOF_ARRAY(val) (sizeof(val) / sizeof(val[0]))
#endif

/* Typedef -------------------------------------------------------------------*/
typedef void (*j1939_pgn_req_fun_t)(uint16_t max_len, uint16_t *tx_len, uint8_t *tx_dat_p);

typedef struct
{
    uint16_t            no;
    j1939_pgn_req_fun_t cbk;
    bool                en;
} j1939_pgn_req_t;

/* Function prototypes -------------------------------------------------------*/
static void req_pgn_cbk_65257(uint16_t max_len, uint16_t *tx_len, uint8_t *tx_dat_p);
static void req_pgn_cbk_49408(uint16_t max_len, uint16_t *tx_len, uint8_t *tx_dat_p);
static void req_pgn_cbk_49664(uint16_t max_len, uint16_t *tx_len, uint8_t *tx_dat_p);
static void req_pgn_cbk_54016(uint16_t max_len, uint16_t *tx_len, uint8_t *tx_dat_p);
static void req_pgn_cbk_64822(uint16_t max_len, uint16_t *tx_len, uint8_t *tx_dat_p);
static void req_pgn_cbk_64823(uint16_t max_len, uint16_t *tx_len, uint8_t *tx_dat_p);
static void req_pgn_cbk_64981(uint16_t max_len, uint16_t *tx_len, uint8_t *tx_dat_p);
static void req_pgn_cbk_65168(uint16_t max_len, uint16_t *tx_len, uint8_t *tx_dat_p);
static void req_pgn_cbk_65203(uint16_t max_len, uint16_t *tx_len, uint8_t *tx_dat_p);
static void req_pgn_cbk_65226(uint16_t max_len, uint16_t *tx_len, uint8_t *tx_dat_p);
static void req_pgn_cbk_65230(uint16_t max_len, uint16_t *tx_len, uint8_t *tx_dat_p);
static void req_pgn_cbk_65236(uint16_t max_len, uint16_t *tx_len, uint8_t *tx_dat_p);
static void req_pgn_cbk_65259(uint16_t max_len, uint16_t *tx_len, uint8_t *tx_dat_p);
static void req_pgn_cbk_65260(uint16_t max_len, uint16_t *tx_len, uint8_t *tx_dat_p);
static void req_pgn_cbk_65420(uint16_t max_len, uint16_t *tx_len, uint8_t *tx_dat_p);
static void req_pgn_cbk_65253(uint16_t max_len, uint16_t *tx_len, uint8_t *tx_dat_p);
static void req_pgn_cbk_65518(uint16_t max_len, uint16_t *tx_len, uint8_t *tx_dat_p);

/* Variables -----------------------------------------------------------------*/
static j1939_pgn_req_t s_pgn_req_l[] = {
    {49408, req_pgn_cbk_49408, true},
    {49664, req_pgn_cbk_49664, true},
    {54016, req_pgn_cbk_54016, true},
    {64822, req_pgn_cbk_64822, true},
    {64823, req_pgn_cbk_64823, true},
    {64981, req_pgn_cbk_64981, true},
    {65168, req_pgn_cbk_65168, true},
    {65203, req_pgn_cbk_65203, true},
    {65226, req_pgn_cbk_65226, true},
    {65230, req_pgn_cbk_65230, true},
    {65236, req_pgn_cbk_65236, true},
    {65259, req_pgn_cbk_65259, true},
    {65257, req_pgn_cbk_65257, true},
    {65259, req_pgn_cbk_65259, true},
    {65260, req_pgn_cbk_65260, true},
    {65420, req_pgn_cbk_65420, true},
    {65253, req_pgn_cbk_65253, true},
    {65518, req_pgn_cbk_65518, true},
};

/* Functions -----------------------------------------------------------------*/
static void req_pgn_cbk_65257(uint16_t max_len, uint16_t *tx_len, uint8_t *tx_dat_p)
{
    memset(tx_dat_p, 0, max_len);
    /*
    PGN 65257 Fuel Consumption (Liquid) LFC 
    Engine fuel consumption accumulators.  See PGN 64777 for alternate resolution. 
    Transmission Repetition Rate: On request 
    Data Length: 8 
    Extended Data Page: 0 
    Data Page: 0 
    PDU Format: 254 
    PDU Specific: 233 PGN Supporting Information:  
    Default Priority: 6 
    Parameter Group Number: 65257  (0x00FEE9) 
    Start Position Length Parameter Name SPN 
    1-4 4 bytes Engine Trip Fuel 182 
    5-8 4 bytes Engine Total Fuel Used 250 
    */
    *(uint32_t *)(&tx_dat_p[0]) |= j1939_ecu_spn_get_val_to_obd(182);
    *(uint32_t *)(&tx_dat_p[4]) |= j1939_ecu_spn_get_val_to_obd(250);
}

static void req_pgn_cbk_49408(uint16_t max_len, uint16_t *tx_len, uint8_t *tx_dat_p)
{
    memset(tx_dat_p, 0, max_len);
    /*
    5.7.21DIAGNOSTIC READINESS 2 (DM21)—Reports the diagnostic information relevant to a second PGN conveying
    diagnostic readiness.  See also (DM5, Sect. 5.7.5).
    Transmission Rate: On Request
    Data Length: 8 bytes
    Data Page: 0
    PDU Format: 193
    PDU Specific: Destination Address
    Default Priority: 6
    Parameter Group Number: 49408 (00C10016)
    Bytes: 1-2 Distance Travelled While MIL is Activated See 5.7.21.1
    Bytes: 3-8 Reserved for SAE Assignment
    */

    /*
    5.7.21.1 Distance Travelled While MIL is Activated—The kilometers accumulated while the MIL is activated.  See 
    the rollover clearing requirements defined in legislative documentation referenced in section 2.1.2 of this
    document.
    Data Length: 2 bytes
    Resolution: Offset:  0 km, 1 km/bit
    Data Range: 0 to 64255 km units
    Type: Measured
    Suspect Parameter Number: 3069
    Reference: 5.7.5
    */
    *(uint16_t *)(&tx_dat_p[0]) = j1939_ecu_spn_get_val_to_obd(3069);
}

static void req_pgn_cbk_49664(uint16_t max_len, uint16_t *tx_len, uint8_t *tx_dat_p)
{
    uint8_t idx = 0;
    uint8_t cnt = 0;
    uint8_t num = 0;

    memset(tx_dat_p, 0, max_len);
    /*
    5.7.20 MONITOR PERFORMANCE RATIO (DM20)—Legislated On-Board Diagnostics requirements (OBD II) specify
    that engine manufacturers must monitor all emission and OBD system related components throughout the
    expected life of the vehicle. Manufacturers are to monitor all components that impact engine emissions. If a
    diagnostic system determines there is a fault that may cause engine emissions to exceed their specified
    levels the manufacturer must illuminate the MIL. The monitor performance ratio indicates how often the
    manufacturer monitors the components as compared to the total number of opportunities to monitor the
    performance of the component.
    The ratio for each parameter is defined as the num divided by the den. The requirements for
    incrementing the num and den are defined on an individual monitor basis.
    Only the applicable Monitor Performance Ratios are required to be reported according to the regulations.
    However the Ignition Cycle Counter and the OBD Monitoring Conditions Encountered (e.g. CARB’s General
    Denominator) are required in all transmissions of DM20.
    Transmission Rate: On request
    Data Length: Variable
    Data page: 00
    PDU Format: 194
    PDU Specific: Destination Address
    Default Priority: 6
    Parameter Group Number: 49664 (00C20016)

    Definitions:
    a=Ignition Cycle Counter
    b=OBD Monitoring Conditions Encountered
    c=SPN which defines the monitor ratio being reported
    d=Monitor Ratio Numerator
    e=Monitor Ratio Denominator
    Message format shall be as follows: a,b,c,d,e,c,d,e,c,d,e,c,d,e,c,d,e,....etc. The transport protocol of SAE
    J1939-21 is used when DM20 requires more than 8 data bytes to convey response.
    The table that follows identifies some of the possible performance monitor ratios that a system may report. It
    contains an indication of those CARB required in their March 2003 OBD II document (California Code of
    Federal Regulation 1968.2).
    */

    /*
    Bytes 1-2 Ignition Cycle Counter See 5.7.20.1
    */
    /*
    5.7.20.1 Ignition Cycle Counter—The ignition cycle counter is defined as a single counter that defines the number
    of ignition cycles.  Requirements for incrementing the denominator are specified in the appropriate legisla-
    tive documents.
    Data Length: 2 bytes
    Resolution: 1/bit, offset=0
    Data Range: 0 to 65535
    Type: Measured
    Suspect Parameter Number: 3048
    Reference: 5.7.20
    */
    *(uint16_t *)(&tx_dat_p[0]) = j1939_ecu_spn_get_val_to_obd(3048);

    /*
    Bytes 3-4 OBD Monitoring Conditions Encountered See 5.7.20.2
    */
    /*
    5.7.20.2 OBD Monitoring Conditions Encountered—OBD Monitoring Conditions Encountered Counts displays the
    number of times that the vehicle has been operated in the specified OBD monitoring conditions (e.g. CARB
    defines this as the general denominator).
    Data Length: 2 bytes
    Resolution: 1/bit, offset=0
    Data Range: 0 to 65535
    Type: Status
    Suspect Parameter Number: 3049
    Reference: 5.7.20
    */
    *(uint16_t *)(&tx_dat_p[2]) = j1939_ecu_spn_get_val_to_obd(3049);

    /*
    Bytes 5-7 SPN of Applicable System Monitor See 5.7.20.3
    */
    /*
    5.7.20.3 SPN of Applicable System Monitor—This 3 byte field will contain the SPN of the system monitor for which
    Monitor ratio is being reported. All instances where the SPN appears in DM20 will be positioned as shown
    in Table 17. 
    Data Length: 3 bytes 
    Resolution: Not applicable
    Data Range: 0 to 524287
    Type: Status
    Suspect Parameter Number: 3066
    Reference: 5.7.20
    */
    *(uint32_t *)(&tx_dat_p[4]) = j1939_ecu_spn_get_val_to_obd(3066) & 0xFFFFFF;

    /*
    Bytes 8-9 Applicable System Monitor Numerator See 5.7.20.4
    */
    /*
    5.7.20.4 Applicable System Monitor Numerator—The number of times a vehicle has been operated such that all
    conditions necessary for the Applicable System Monitor to detect a malfunction have been encountered
    (e.g. CARB numerator requirements).
    Data Length: 2 bytes
    Resolution: 1/bit, offset=0
    Data Range: 0 to 65535
    Type: Status
    Suspect Parameter Number: 3067
    Reference: 5.7.20
    */
    *(uint16_t *)(&tx_dat_p[7]) = j1939_ecu_spn_get_val_to_obd(3067);

    /*
    Bytes 10-11 Applicable System Monitor Denominator See 5.7.20.5
    */
    /*
    5.7.20.5 Applicable System Monitor Denominator—The number of times a vehicle has been operated that consti-
    tutes a driving cycle where this Applicable System Monitor could be operated per regulatory requirements
    (e.g. CARB denominator requirements). 
    Data Length: 2 bytes
    Resolution: 1/bit, offset=0
    Data Range: 0 to 65535
    Type: Status
    Suspect Parameter Number: 3068
    Reference: 5.7.20
    */
    *(uint16_t *)(&tx_dat_p[9]) = j1939_ecu_spn_get_val_to_obd(3068);

    /*
    Byte n to z
    */
    /*
    start of data[11]
    */

    /*
    Row#    SPN#    CARB Required   Name
    1       3048        X           Ignition Cycle Counter
    2       3049        X           OBD Monitoring Conditions Encountered Counts
    3       3050        X           Catalyst 1 System Monitor
    4       3051        X           Catalyst 2 System Monitor
    5       3052                    Misfire Monitor
    6       3053        X           Evaporative System Monitor
    7       3054        X           Secondary Air System Monitor (AIR Monitor)
    8       3055                    Fuel System Monitor
    9       3056        X           Oxygen Sensor 1 Monitor
    10      3057        X           Oxygen Sensor 2 Monitor
    11      3058        X           EGR System Monitor
    12      3059                    Positive Crankcase Ventilation System Monitor
    13      3060                    Engine Cooling System Monitor
    14      3061                    Cold Start Emission Reduction Strategy System Monitor
    15      3062                    Air Conditioning System Component Monitor
    16      3063                    Direct Ozone Reduction Monitor
    17      3064                    Particulate Matter Trap Monitor
    18      3065                    Comprehensive Component Monitor
    */

    num = j1939_ecu_spn_iupr_get_num();
    cnt = 11;
    idx = 0;
    while (num--)
    {
        *(uint32_t *)&tx_dat_p[cnt] = j1939_ecu_spn_iupr_get_one(idx, 0);
        cnt += 3;
        *(uint16_t *)&tx_dat_p[cnt] = j1939_ecu_spn_iupr_get_one(idx, 1);
        cnt += 2;
        *(uint16_t *)&tx_dat_p[cnt] = j1939_ecu_spn_iupr_get_one(idx, 3);
        cnt += 2;
        idx++;
    }
}

static void req_pgn_cbk_54016(uint16_t max_len, uint16_t *tx_len, uint8_t *tx_dat_p)
{
    memset(tx_dat_p, 0, max_len);

    /*
    5.7.19 CALIBRATION INFORMATION (DM19)—Provides information about the calibration to an interrogating Tool (see
    Figure 4).
    If DM19 is requested before computation of the Calibration Verification Number is complete then the
    responder shall send the Acknowledgement PGN with mode set to three to indicate that the tool should
    request DM19 at a later time.
    Transmission Rate: On request using PGN 59904 (See SAE J1939-21 PGN 59904).
    A NACK is required if PG is not supported.
    (See SAE J1939-21 PGN 59392)
    Data Length: 20 bytes
    Function: Provide information about the calibration to scan Tool
    Data page: 0
    PDU Format: 211
    PDU Specific: DA
    Default Priority: 7
    Parameter Group Number: 54016 (00D30016)
    Bytes 1-4: Calibration Verification Number See 5.7.19.1
    (Byte 1 is least significant byte)
    Bytes 5-20: Calibration ID See 5.7.19.2
    (Byte 5 is least significant byte)
    */

    /*
    5.7.19.1 Calibration Verification Number—Four-byte checksum of the entire calibration. Includes code and data.
    Excludes parameters that exist only  in RAM, nonvolatile parameters that change values during the life
    cycle of the module (hours of operation, miles, number of on/off cycles, freeze frame data, etc.), or
    nonemissions-related parameters that may be changed by the operator (offsets for real-time clocks, user
    selectable preferences, etc.). If the checksum is less than 4 bytes, it must be padded with 0016 (the 0016
    pad is placed in the most significant byte(s) when needed). The checksum algorithm shall be more robust
    than a two’s complement checksum.
    Data Length: 4 bytes
    Resolution: Not applicable
    Data Range: 0 to 4,294,967,295 (00 00 00 0016 to FF FF FF FF16)
    Type: Hexadecimal
    Suspect Parameter Number: 1634
    Reference: 5.7.19
    */
    *(uint32_t *)(&tx_dat_p[0]) |= j1939_ecu_spn_get_val_to_obd(1634);

    /*
    5.7.19.2 Calibration Identification—Sixteen-byte calibration identification number. Uniquely identifies the software
    installed in the control module. The calibration ID must be unique, but does not need to be 16 bytes long. If
    the Calibration ID is less than 16 bytes, those unused bytes are reported at the end of the calibration ID as
    0016 (the 0016 pad is placed in the least significant bytes of the Calibration Identifier when needed). The
    0016 if needed is added to the end of the ASCII character string for Calibration Identification.
    Data Length: 16 bytes
    Resolution: Not applicable
    Data Range: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 0016 
    to
    FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF16
    Type: ASCII
    Suspect Parameter Number: 1635
    Reference: 5.7.19   
    */
    memcpy(&tx_dat_p[4], (char *)j1939_ecu_spn_get_val_to_obd(1635), 16);
}

static void req_pgn_cbk_64981(uint16_t max_len, uint16_t *tx_len, uint8_t *tx_dat_p)
{
    memset(tx_dat_p, 0, max_len);
    /*
    PGN 64981 Electronic Engine Controller 5 EEC5 
    Engine related parameters 
    Transmission Repetition Rate: On request 
    Data Length: 8 
    Extended Data Page: 0 
    Data Page: 0 
    PDU Format: 253 
    PDU Specific: 213 PGN Supporting Information:  
    Default Priority: 6 
    Parameter Group Number: 64981  (0x00FDD5) 
    Start Position Length Parameter Name SPN 
    1-2 2 bytes Engine Turbocharger 1 Calculated Turbine Intake Temperature 2789 
    3-4 2 bytes Engine Turbocharger 1 Calculated Turbine Outlet Temperature 2790 
    5-6 2 bytes Engine Exhaust Gas Recirculation 1 (EGR1) Valve Control 2791 
    7.1 2 bits Engine Variable Geometry Turbocharger (VGT) Air Control Shutoff Valve 2792 
    7.3 2 bits Engine Fuel Control Control Mode 5323 
    7.5 2 bits Engine Variable Geometry Turbocharger 1 Control Mode 5457 
    8 1 byte Engine Variable Geometry Turbocharger (VGT) 1 Actuator Position 2795 
    */
    /*
    Pgn64981－电子发动机控制 5－EEC5
    传输循环率： 请求时
    数据长度： 8 字节
    数据页面： 0
    PDU 格式： 253
    PDU 特定： 213
    默认优先值： 6
    参数组数编号： 64981（00FDD516）
    起始位位置/字节 长度 SPN 定义 SPN
    */

    /*
    1-2 2 字节 估算涡轮增压器涡轮进气口温度 2789
    3-4 2 字节 估算涡轮增压器涡轮出气口温度 2790
    5-6 2 字节 废气再循环（EGR）阀控制 2791
    */
    *(uint16_t *)(&tx_dat_p[0]) |= j1939_ecu_spn_get_val_to_obd(2789);
    *(uint16_t *)(&tx_dat_p[2]) |= j1939_ecu_spn_get_val_to_obd(2790);
    *(uint16_t *)(&tx_dat_p[4]) |= j1939_ecu_spn_get_val_to_obd(2791);

    /*
    7.1 2 位 可变几何涡轮增压器（VGT）气体控制关闭阀 2792
    */
    *(uint16_t *)(&tx_dat_p[6]) |= KEEP_BITS_2(j1939_ecu_spn_get_val_to_obd(2792)) << 0;

    /*
    8 1 字节 VGT1 致动位置 2795
    */
    tx_dat_p[7] |= j1939_ecu_spn_get_val_to_obd(2795);
}
static void req_pgn_cbk_65168(uint16_t max_len, uint16_t *tx_len, uint8_t *tx_dat_p)
{
    memset(tx_dat_p, 0, max_len);
    /*
    PGN 65168 Engine Torque History ETH 
    NOTE - The torque history PGN is variable in length and may contain up to 125 torque history records.  Each torque 
    history record MUST BE 38 bytes in length.  Any unused bytes must be 0xFF. 
    
    The last six bytes of each record are not currently defined and shall be transmitted as “not available” (0xff).  In the first 
    record, these are byte positions 34-39. 
    Transmission Repetition Rate: On request 
    Data Length: Variable 
    Extended Data Page: 0 
    Data Page: 0 
    PDU Format: 254 
    PDU Specific: 144 PGN Supporting Information:  
    Default Priority: 6 
    Parameter Group Number: 65168  (0x00FE90) 
    Start Position Length Parameter Name SPN 
    */

    /*
    01 1 byte Number of Engine Torque History Records 1246 
    */
    tx_dat_p[0] |= j1939_ecu_spn_get_val_to_obd(1246);

    /*
    02-03 2 bytes Engine Power 1247 
    04-05 2 bytes Engine Peak Torque 1 1248 
    06-07 2 bytes Engine Peak Torque 2 1249 
    */
    *(uint16_t *)(&tx_dat_p[1]) |= j1939_ecu_spn_get_val_to_obd(1247);
    *(uint16_t *)(&tx_dat_p[3]) |= j1939_ecu_spn_get_val_to_obd(1248);
    *(uint16_t *)(&tx_dat_p[4]) |= j1939_ecu_spn_get_val_to_obd(1249);

    /*
    08 1 byte Calibration Record Start Month 1250 
    09 1 byte Calibration Record Start Day 1251 
    10 1 byte Calibration Record Start Year 1252 
    */
    tx_dat_p[7] |= j1939_ecu_spn_get_val_to_obd(1250);
    tx_dat_p[8] |= j1939_ecu_spn_get_val_to_obd(1251);
    tx_dat_p[9] |= j1939_ecu_spn_get_val_to_obd(1252);

    /*
    11-14 4 bytes Calibration Record Duration Time 1253 
    */
    *(uint32_t *)(&tx_dat_p[10]) |= j1939_ecu_spn_get_val_to_obd(1253);

    /*
    15.1 2 bits Torque Limiting Feature Status 1254 
    15.3 3 bits Engine Torque Limit Feature 1632 
    */
    tx_dat_p[14] |= KEEP_BITS_2(j1939_ecu_spn_get_val_to_obd(1254)) << 0;
    tx_dat_p[14] |= KEEP_BITS_3(j1939_ecu_spn_get_val_to_obd(1632)) << 2;

    /*
    16-17 2 bytes Transmission Gear Ratio 1 1255 
    18-19 2 bytes Engine Torque Limit 1, Transmission 1256 
    20-21 2 bytes Transmission Gear Ratio 2 1257 
    22-23 2 bytes Engine Torque Limit 2, Transmission 1258 
    24-25 2 bytes Transmission Gear Ratio 3 1259 
    26-27 2 bytes Engine Torque Limit 3, Transmission 1260 
    28-29 2 bytes Engine Torque Limit 4, Transmission 1261 
    30-31 2 bytes Engine Torque Limit 5, Switch 1262 
    32-33 2 bytes Engine Torque Limit 6, Axle Input 1263 
    */
    *(uint16_t *)(&tx_dat_p[15]) |= j1939_ecu_spn_get_val_to_obd(1255);
    *(uint16_t *)(&tx_dat_p[17]) |= j1939_ecu_spn_get_val_to_obd(1256);
    *(uint16_t *)(&tx_dat_p[19]) |= j1939_ecu_spn_get_val_to_obd(1257);
    *(uint16_t *)(&tx_dat_p[21]) |= j1939_ecu_spn_get_val_to_obd(1258);
    *(uint16_t *)(&tx_dat_p[23]) |= j1939_ecu_spn_get_val_to_obd(1259);
    *(uint16_t *)(&tx_dat_p[25]) |= j1939_ecu_spn_get_val_to_obd(1260);
    *(uint16_t *)(&tx_dat_p[27]) |= j1939_ecu_spn_get_val_to_obd(1261);
    *(uint16_t *)(&tx_dat_p[29]) |= j1939_ecu_spn_get_val_to_obd(1262);
    *(uint16_t *)(&tx_dat_p[31]) |= j1939_ecu_spn_get_val_to_obd(1263);
}

static void req_pgn_cbk_65203(uint16_t max_len, uint16_t *tx_len, uint8_t *tx_dat_p)
{
    memset(tx_dat_p, 0, max_len);
    /*
    PGN 65203 Fuel Information (Liquid) LFI 
    Transmission Repetition Rate: On request 
    Data Length: 8 
    Extended Data Page: 0 
    Data Page: 0 
    PDU Format: 254 
    PDU Specific: 179 PGN Supporting Information:  
    Default Priority: 7 
    Parameter Group Number: 65203  (0x00FEB3) 
    Start Position Length Parameter Name SPN 
    1-4 4 bytes Total Engine PTO Governor Fuel Used 1028 
    5-6 2 bytes Trip Average Fuel Rate 1029 
    7-8 2 bytes Flexible Fuel Percentage 5458 
    */
    *(uint32_t *)(&tx_dat_p[0]) |= j1939_ecu_spn_get_val_to_obd(1028);
    *(uint16_t *)(&tx_dat_p[4]) |= j1939_ecu_spn_get_val_to_obd(1029);
    *(uint16_t *)(&tx_dat_p[6]) |= j1939_ecu_spn_get_val_to_obd(5458);
}

static void req_pgn_cbk_65226(uint16_t max_len, uint16_t *tx_len, uint8_t *tx_dat_p)
{
    uint8_t i   = 0;
    uint8_t num = 0;
    memset(tx_dat_p, 0, max_len);
    /*
    ACTIVE DIAGNOSTIC TROUBLE CODES (DM1)—The information communicated is limited to the currently active
    diagnostic trouble codes preceded by the diagnostic lamp status. Both are used to notify other components
    on the network of the diagnostic condition of the transmitting electronic component. The data contains the
    lamp status and a list of diagnostic codes and occurrence counts for currently active diagnostic trouble
    codes. This is all DTCs including those that are emissions related.
    The currently defined lamps (Malfunction Indicator Lamp, Red Stop Lamp, Amber Warning Lamp, and
    Protect Lamp) are associated with DTCs. If the transmitting electronic component does not have active
    DTCs, then the lamp status from  that component will indicate that the lamps should be off. However, the
    component controlling the actual lamp illumination must consider the status from all components that use
    these lamps before changing the state of the lamps. 
    There may be applications that require additional lamp definitions to accomplish their function (e.g. a lamp
    that indicates when cruise control is actively controlling would require a separate lamp in another PG).
    Transmission Rate: A DM1 message is transmitted whenever a DTC becomes an active fault
    and at a normal update rate of only once per second thereafter. If a fault
    has been active for 1 second or longer, and then becomes inactive, a
    DM1 message shall be transmitted to  reflect this state change. If a
    different DTC changes state within the 1 second update period, a new
    DM1 message is transmitted to reflect this new DTC. To prevent a high
    message rate due to intermittent faults that have a very high frequency, it
    is recommended that no more than one state change per DTC per second
    be transmitted. Thus a DTC that becomes active/inactive twice within a 1
    second interval, such as shown in Example Case 1, would have one
    message identifying the DTC becoming active, and one at the next
    periodic transmission identifying it being inactive. This message is sent
    only when there is an active DTC existing or in response to a request.
    Note that this Parameter Group  will require using the “multipacket
    Transport” Parameter Group (reference SAE J1939-21) when more than
    one active DTC exists.
    Data Length: Variable
    Data page: 0
    PDU Format: 254
    PDU Specific: 202
    Default Priority: 6
    Parameter Group Number: 65226 (00FECA16)
    ......
    NOTE—When the occurrence count is not available it should be set to all ones.
    */

    /*
    Byte: 1 
    bits 8-7 Malfunction Indicator Lamp Status See 5.7.1.1
    bits 6-5 Red Stop Lamp Status See 5.7.1.2
    bits 4-3 Amber Warning Lamp Status See 5.7.1.3
    bits 2-1 Protect Lamp Status See 5.7.1.4

    字节1：灯状态
    8～7 位 故障指示灯状态
    6～5 位 红色停止灯状态
    4～3 位 琥珀色警告灯状态
    2～1 位 保护灯状态

    5.7.1.1 Malfunction Indicator Lamp—A lamp used to relay only emissions-related trouble code information. This
    lamp is only illuminated when there is an emission-related trouble code active.
    00 Lamp Off
    01 Lamp On
    Type: Status
    Suspect Parameter Number: 1213
    Reference: 5.7.1, 5.7.2, 5.7.6 and 5.7.12

    5.7.1.2 Red Stop Lamp—This lamp is used to relay trouble code information that is of a severe enough condition
    that it warrants stopping the vehicle.
    00 Lamp Off
    01 Lamp On
    Type: Status
    Suspect Parameter Number: 623
    Reference: 5.7.1, 5.7.2, 5.7.6 and 5.7.12

    5.7.1.3 Amber Warning Lamp—This lamp is used to relay trouble code information that is reporting a problem with
    the vehicle system but the vehicle need not be immediately stopped.
    00 Lamp Off
    01 Lamp On
    Type: Status
    Suspect Parameter Number: 624
    Reference: 5.7.1, 5.7.2, 5.7.6 and 5.7.12

    5.7.1.4 Protect Lamp—This lamp is used to relay trouble code information that is reporting a problem with a vehi-
    cle system that is most probably not electronic subsystem related. For instance, engine coolant tempera-
    ture is exceeding its prescribed temperature range.
    00 Lamp Off
    01 Lamp On
    Type: Status
    Suspect Parameter Number: 987
    Reference: 5.7.1, 5.7.2, 5.7.6 and 5.7.12
    */
    tx_dat_p[0] |= KEEP_BITS_2(j1939_ecu_spn_get_val_to_obd(1213)) << 0;
    tx_dat_p[0] |= KEEP_BITS_2(j1939_ecu_spn_get_val_to_obd(623)) << 2;
    tx_dat_p[0] |= KEEP_BITS_2(j1939_ecu_spn_get_val_to_obd(624)) << 4;
    tx_dat_p[0] |= KEEP_BITS_2(j1939_ecu_spn_get_val_to_obd(987)) << 6;

    /*
    Byte: 2 
    bits 8-7 Reserved for SAE assignment Lamp Status
    bits 6-5 Reserved for SAE assignment Lamp Status
    bits 4-3 Reserved for SAE assignment Lamp Status
    bits 2-1 Reserved for SAE assignment Lamp Status

    字节2：
    8～7 位 预留以用来表示 SAE 任务灯状态
    6～5 位 预留以用来表示 SAE 任务灯状态
    4～3 位 预留以用来表示 SAE 任务灯状态
    2～1 位 预留以用来表示 SAE 任务灯状态
    */
    num = j1939_ecu_spn_dtc_get_num();

    if (num == 0)
    {
        tx_dat_p[1] = 0;
    }
    else
    {
        tx_dat_p[1] = 0x01 << 6;
    }

    /*
    Byte: 3 bits 8-1 SPN, 8 least significant bits of SPN See 5.7.1.5
                            (most significant at bit 8)
    Byte: 4 bits 8-1 SPN, second byte of SPN See 5.7.1.5 
                            (most significant at bit 8)
    Byte: 5 bits 8-6 SPN, 3 most significant bits See 5.7.1.5
                            (most significant at bit 8)
            bits 5-1 FMI 
                            (most significant at bit 5) See 5.7.1.6
    Byte: 6 bit  8   SPN Conversion Method See 5.7.1.7
            bits 7-1 Occurrence Count See 5.7.1.8

    字节： 3 8～1 位 SPN，SPN 的低 8 位有效位（最高有效位为第 8 位）
    字节： 4 8～1 位 SPN，SPN 的第 2 个字节（最高有效位为第 8 位）
    字节： 5 8～6 位 SPN，有效位中的高 3 位（最高有效位为第 8 位）
             5～1 位 FMI(最高有效位为第 5 位)
    字节： 6 8    位 未知参数编号的转化方式
             7～1 位 发生次数
    */

    for (i = 0; i < num; i++)
    {
        *(uint32_t *)&tx_dat_p[2 + i * 4] = j1939_ecu_spn_dtc_get_one(i);
    }
}

static void req_pgn_cbk_65230(uint16_t max_len, uint16_t *tx_len, uint8_t *tx_dat_p)
{
    memset(tx_dat_p, 0, max_len);
    /*
    5.7.5 DIAGNOSTIC READINESS 1 (DM5)—Reports the diagnostics information that relates to diagnostic readiness.
    Transmission Rate: On request using PGN 59904 See SAE J1939-21
    A NACK is required if PG is not supported 
    (see SAE J1939-21 PGN 59392)
    Data Length: 8 bytes
    Data page: 0
    PDU Format: 254
    PDU Specific: 206
    Default Priority: 6
    Parameter Group Number: 65230 (00FECE16)
    */

    /*
    Byte: 
    1 Active Trouble Codes See 5.7.5.1
    2 Previously Active Diagnostic Trouble Codes See 5.7.5.2
    3 OBD Compliance See 5.7.5.3
    4 Continuously Monitored Systems Support/Status See 5.7.5.4

    5.7.5.1 Active Trouble Codes—Identifies the number of active trouble codes that are present in a specific control-
    ler. If no DTCs are active, this field should be set to zero.
    Data Length: 1 byte
    Resolution: 1 trouble code/bit
    Data Range: 0 to 240
    Type: Measured
    Suspect Parameter Number: 1218
    Reference: 5.7.5

    5.7.5.2 Previously Active Diagnostic Trouble Codes—Identifies the number of previously active trouble codes that
    are present in a specific controller. If no DTCs have been previously active, this field should be set to zero.
    Data Length: 1 byte
    Resolution: 1 trouble code/bit
    Data Range: 0 to 240
    Type: Measured
    Suspect Parameter Number: 1219
    Reference: 5.7.5

    5.7.5.3 OBD Compliance—Identifies the OBD compliance capability of  the responding controller. Identifies the
    requirements level to which the controller was built.
    Data Length: 1 byte
    Resolution: See below
    Data Range: 0 to 240
    Type: Measured
    Suspect Parameter Number: 1220
    Reference: 5.7.5
    Value Description
    00 Reserved for assignment by SAE
    01 OBD II (California Air Resources Board)
    02 OBD (Federal, EPA)
    03 OBD and OBD II
    04 OBD I
    05 Not intended to meet OBD II requirements
    06-240 Reserved for assignment by SAE

    5.7.5.4 Continuously Monitored Systems Support/Status—Identifies the continuously monitored system support
    and status.
    Data Length: 1 byte
    Resolution: See below
    Data Range: Bit mapped, see below
    Type: Measured
    Suspect Parameter Number: 1221
    Reference: 5.7.5
    
    8 Reserved for assignment by SAE
    7 Comprehensive component monitoring status
    6 Fuel System monitoring status
    5 Misfire monitoring status
        Where each status bit (bits 7, 6, 5) is interpreted:
        0 = test complete, not supported
        1 = test not complete
    4 Reserved for assignment by SAE
    3 Comprehensive component monitoring support
    2 Fuel system monitoring support
    1 Misfire monitoring support
        Where each supported bit (bits 3, 2, 1) is interpreted:
        0 = test not supported by this controller
        1 = test supported by this controller
    NOTE—Notice that a bit set to zero can mean test not supported. This is different than the typical J1939
    use of the value 1 to indicate not available.
    */
    tx_dat_p[0] |= j1939_ecu_spn_get_val_to_obd(1218);
    tx_dat_p[1] |= j1939_ecu_spn_get_val_to_obd(1219);
    tx_dat_p[2] |= j1939_ecu_spn_get_val_to_obd(1220);
    tx_dat_p[3] |= j1939_ecu_spn_get_val_to_obd(1221);

    /*
    5-6 Non-continuously Monitored Systems Support See 5.7.5.5
    7-8 Non-continuously Monitored Systems Status See 5.7.5.6

    5.7.5.5 Non-continuously Monitored Systems Support—Identifies the non-continuously monitored systems sup-
    port.
    Data Length: 2 bytes (sent as a magnitude; therefore it is byte swapped)
    Resolution: See below
    Data Range: Bit mapped, see below
    Type: Measured
    Suspect Parameter Number: 1222
    Reference: 5.7.5

    Byte 5 
    8 EGR system monitoring Support
    7 Oxygen sensor heater monitoring Support
    6 Oxygen sensor monitoring Support
    5 A/C system refrigerant monitoring Support
    4 Secondary air system monitoring Support
    3 Evaporative system monitoring Support
    2 Heated catalyst monitoring Support
    1 Catalyst monitoring Support
    
    Byte 6 
    8-2 Reserved for assignment by SAE
    1   Cold start aid system monitoring Support
        Where each bit is interpreted:
        0 = test not supported by this controller
        1 = test supported by this controller
    NOTE—The "Non-continuously Monitored Systems Support" parameter is in the Intel Format (byte-
    swapped format). Also notice that a bit set to zero means test not supported. This is different than the typi-
    cal J1939 use of the value 1 to indicate not available.

    5.7.5.6 Non-continuously Monitored Systems Status—Identifies the non-continuously monitored systems status.
    Each bit identifies whether a particular test is complete for a given controller.
    Data Length: 2 bytes (sent as a magnitude; therefore it is byte swapped)
    Resolution: See below
    Data Range: Bit mapped, see below
    Type: Measured
    Suspect Parameter Number: 1223
    Reference: 5.7.5
    Byte 7 
    8 EGR system monitoring Status
    7 Oxygen sensor heater monitoring Status
    6 Oxygen sensor monitoring Status
    5 A/C system refrigerant monitoring Status
    4 Secondary air system monitoring Status
    3 Evaporative system monitoring Status
    2 Heated catalyst monitoring Status
    1 Catalyst monitoring Status

    Byte 8 
    8-2 Reserved for assignment by SAE
    1   Cold start aid system monitoring Status
        Where each bit is interpreted:
        0 = test complete, or not supported
        1 = test not complete
    NOTE—The "Non-continuously Monitored Systems Status" parameter is in the Intel Format (byte-swapped
    format). Also notice that a bit set to zero can mean  test not supported. This is different than the typical
    J1939 use of the value 1 to indicate not available.
    */
    *(uint16_t *)(&tx_dat_p[4]) |= j1939_ecu_spn_get_val_to_obd(1222);
    *(uint16_t *)(&tx_dat_p[6]) |= j1939_ecu_spn_get_val_to_obd(1223);
}

static void req_pgn_cbk_65236(uint16_t max_len, uint16_t *tx_len, uint8_t *tx_dat_p)
{
    uint8_t i   = 0;
    uint8_t num = 0;
    memset(tx_dat_p, 0, max_len);
    /*
    EMISSIONS-RELATED ACTIVE DIAGNOSTIC TROUBLE CODES (DM12)—The information communicated is limited
    to the currently active emission-related diagnostic  trouble codes preceded by the diagnostic lamp status.
    Both are used to notify other components on the network of the diagnostic condition of the transmitting
    electronic component. The data contains the lamp  status and a list of diagnostic codes and occurrence
    counts for currently active emission-related diagnostic trouble codes.
    Transmission Rate: On request using PGN 59904 See SAE J1939-21
    A NACK is required if PG is not supported 
    (see SAE J1939-21 PGN 59392)
    Data Length: Variable
    Data page: 0
    PDU Format: 254
    PDU Specific: 212
    Default Priority: 6
    Parameter Group Number: 65236 (00FED416)
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
    bits 5-1 FMI See 5.7.1.6
    (most significant at bit 5)
    Byte: 6 bit 8 SPN Conversion Method See 5.7.1.7
    bits 7-1 Occurrence Count See 5.7.1.8
    NOTE—When the occurrence count is not available it should be set to all ones.
    */

    /*
    Byte: 1 
    bits 8-7 Malfunction Indicator Lamp Status See 5.7.1.1
    bits 6-5 Red Stop Lamp Status See 5.7.1.2
    bits 4-3 Amber Warning Lamp Status See 5.7.1.3
    bits 2-1 Protect Lamp Status See 5.7.1.4

    字节1：灯状态
    8～7 位 故障指示灯状态
    6～5 位 红色停止灯状态
    4～3 位 琥珀色警告灯状态
    2～1 位 保护灯状态

    5.7.1.1 Malfunction Indicator Lamp—A lamp used to relay only emissions-related trouble code information. This
    lamp is only illuminated when there is an emission-related trouble code active.
    00 Lamp Off
    01 Lamp On
    Type: Status
    Suspect Parameter Number: 1213
    Reference: 5.7.1, 5.7.2, 5.7.6 and 5.7.12

    5.7.1.2 Red Stop Lamp—This lamp is used to relay trouble code information that is of a severe enough condition
    that it warrants stopping the vehicle.
    00 Lamp Off
    01 Lamp On
    Type: Status
    Suspect Parameter Number: 623
    Reference: 5.7.1, 5.7.2, 5.7.6 and 5.7.12

    5.7.1.3 Amber Warning Lamp—This lamp is used to relay trouble code information that is reporting a problem with
    the vehicle system but the vehicle need not be immediately stopped.
    00 Lamp Off
    01 Lamp On
    Type: Status
    Suspect Parameter Number: 624
    Reference: 5.7.1, 5.7.2, 5.7.6 and 5.7.12

    5.7.1.4 Protect Lamp—This lamp is used to relay trouble code information that is reporting a problem with a vehi-
    cle system that is most probably not electronic subsystem related. For instance, engine coolant tempera-
    ture is exceeding its prescribed temperature range.
    00 Lamp Off
    01 Lamp On
    Type: Status
    Suspect Parameter Number: 987
    Reference: 5.7.1, 5.7.2, 5.7.6 and 5.7.12
    */
    tx_dat_p[0] |= KEEP_BITS_2(j1939_ecu_spn_get_val_to_obd(1213)) << 0;
    tx_dat_p[0] |= KEEP_BITS_2(j1939_ecu_spn_get_val_to_obd(623)) << 2;
    tx_dat_p[0] |= KEEP_BITS_2(j1939_ecu_spn_get_val_to_obd(624)) << 4;
    tx_dat_p[0] |= KEEP_BITS_2(j1939_ecu_spn_get_val_to_obd(987)) << 6;

    /*
    Byte: 2 
    bits 8-7 Reserved for SAE assignment Lamp Status
    bits 6-5 Reserved for SAE assignment Lamp Status
    bits 4-3 Reserved for SAE assignment Lamp Status
    bits 2-1 Reserved for SAE assignment Lamp Status

    字节2：
    8～7 位 预留以用来表示 SAE 任务灯状态
    6～5 位 预留以用来表示 SAE 任务灯状态
    4～3 位 预留以用来表示 SAE 任务灯状态
    2～1 位 预留以用来表示 SAE 任务灯状态
    */
    num = j1939_ecu_spn_dtc_get_num();

    if (num == 0)
    {
        tx_dat_p[1] = 0;
    }
    else
    {
        tx_dat_p[1] = 0x01 << 6;
    }

    /*
    Byte: 3 bits 8-1 SPN, 8 least significant bits of SPN See 5.7.1.5
                            (most significant at bit 8)
    Byte: 4 bits 8-1 SPN, second byte of SPN See 5.7.1.5 
                            (most significant at bit 8)
    Byte: 5 bits 8-6 SPN, 3 most significant bits See 5.7.1.5
                            (most significant at bit 8)
            bits 5-1 FMI 
                            (most significant at bit 5) See 5.7.1.6
    Byte: 6 bit  8   SPN Conversion Method See 5.7.1.7
            bits 7-1 Occurrence Count See 5.7.1.8

    字节： 3 8～1 位 SPN，SPN 的低 8 位有效位（最高有效位为第 8 位）
    字节： 4 8～1 位 SPN，SPN 的第 2 个字节（最高有效位为第 8 位）
    字节： 5 8～6 位 SPN，有效位中的高 3 位（最高有效位为第 8 位）
             5～1 位 FMI(最高有效位为第 5 位)
    字节： 6 8    位 未知参数编号的转化方式
             7～1 位 发生次数
    */

    for (i = 0; i < num; i++)
    {
        *(uint32_t *)&tx_dat_p[2 + i * 4] = j1939_ecu_spn_dtc_get_one(i);
    }
}

static void req_pgn_cbk_65259(uint16_t max_len, uint16_t *tx_len, uint8_t *tx_dat_p)
{
    uint8_t cnt = 0;
    uint8_t num = 0;
    char *  str = NULL;
    memset(tx_dat_p, 0, max_len);
    /*
    PGN 65259 Component Identification CI 
    NOTE - The make, model, serial number and unit number fields in this message are optional and separated by an AS
    “*”.  It is not necessary to include all fields; however, the delimiter (“*”) is always required. 
    
    Field: 
    a Make 
    Delimiter (ASCII “*”) 
    b Model 
    Delimiter (ASCII “*”) 
    c Serial number 
    Delimiter (ASCII “*”) 
    d Unit number (Power unit) 
    Delimiter (ASCII “*”) 
    
    These examples are permitted uses: 
    
    aaaaa*b...b*c...c*d...d* 
    *b...b*** 
    *b...b**d...d* 
    Transmission Repetition Rate: On request 
    Data Length: Variable 
    Extended Data Page: 0 
    Data Page: 0 
    PDU Format: 254 
    PDU Specific: 235 PGN Supporting Information:  
    Default Priority: 6 
    Parameter Group Number: 65259  (0x00FEEB) 
    Start Position Length Parameter Name SPN 
    a Variable - up to 5 
    bytes followed by 
    an "*" delimiter 
    Make 586 
    b Variable - up to 
    200 bytes 
    followed by an "*" 
    delimiter 
    Model 587 
    c Variable - up to 
    200 bytes 
    followed by an "*" 
    delimiter 
    Serial Number 588 
    d Variable - up to 
    200 bytes 
    followed by an "*" 
    delimiter 
    Unit Number (Power Unit) 233 
    */

    /*
    5.3.25 成分鉴定
    传输循环率： 请求中
    数据长度： 可变
    数据页面： 0
    PDU 格式： 254
    PDU 指定： 235
    默认优先值： 6
    参数组数编号： 65259（00FEEB16）
    域：
    a 制作 5.2.5.90    分隔符（ASCII“*”）
    b 模式 5.2.5.91    分隔符（ASCII“*”）
    c 序列号 5.2.5.92    分隔符（ASCII“*”）
    d 单位数（能量单位） 5.2.5.92    分隔符（ASCII“*”）
    注意    在消息中，制作方式，模式，序列号和单位数域是自由选择的和被一个 ASCII“*”所分开。
    没有必要包括所有的域；然而，分隔符（ASCII“*”）总是被要求。
    
    元件型号的相应代码，该代码在美国货车运输业联盟的车辆保养报告系统（ATA／VMRS）中定义。
    如果 ATA／VMRS 型号代码少于 5 个字符，建议使用空格（ASCⅡ32）填充剩余的字符。
    元件型号。数据长度：可变
    元件序列号。数据长度：可变
    */
    cnt = 0;

    /* Make 586 */
    str = (char *)j1939_ecu_spn_get_val_to_obd(586);
    num = strlen(str);
    memcpy(&tx_dat_p[cnt], str, num);
    cnt += num;
    tx_dat_p[cnt++] = '*';

    /* Model 587 */
    str = (char *)j1939_ecu_spn_get_val_to_obd(587);
    num = strlen(str);
    memcpy(&tx_dat_p[cnt], str, num);
    cnt += num;
    tx_dat_p[cnt++] = '*';

    /* Serial Number 588 */
    str = (char *)j1939_ecu_spn_get_val_to_obd(588);
    num = strlen(str);
    memcpy(&tx_dat_p[cnt], str, num);
    cnt += num;
    tx_dat_p[cnt++] = '*';

    /* Unit Number (Power Unit) 233 */
    str = (char *)j1939_ecu_spn_get_val_to_obd(233);
    num = strlen(str);
    memcpy(&tx_dat_p[cnt], str, num);
}

static void req_pgn_cbk_65260(uint16_t max_len, uint16_t *tx_len, uint8_t *tx_dat_p)
{
    memset(tx_dat_p, 0, max_len);
    /*
    PGN 65260 Vehicle Identification VI 
    Byte: 1-n Vehicle Identification Number 
    Delimiter (ASCII “*”) 
    Transmission Repetition Rate: On request 
    Data Length: Variable 
    Extended Data Page: 0 
    Data Page: 0 
    PDU Format: 254 
    PDU Specific: 236 PGN Supporting Information:  
    Default Priority: 6 
    Parameter Group Number: 65260  (0x00FEEC) 
    Start Position Length Parameter Name SPN 
    1 Variable - up to 
    200 bytes 
    followed by an "*" 
    delimiter 
    Vehicle Identification Number 237 
    */
    memcpy(tx_dat_p, (char *)j1939_ecu_spn_get_val_to_obd(237), 17);
}

static void req_pgn_cbk_65420(uint16_t max_len, uint16_t *tx_len, uint8_t *tx_dat_p)
{
    memset(tx_dat_p, 0, max_len);
    /*
    4.2.3 Commanded Address (PGN 65240)
    A network interconnection CA, a bridge for example, or a diagnostic or scan tool may command another CA
    (Commanded CA) to use a given source address with the Commanded Address Message. The
    Commanded Address message may be used to instruct a CA with a specific NAME to use a specific
    source address (Figures A9 and A10 in appendix A). Upon receipt of a Commanded Address message
    containing its own NAME, a CA should respond in either of two ways: it may accept by initiating an address
    claim procedure using the new address provided in the Commanded Address message or ignore the
    command by sending no response. If the commanded address is successfully claimed, future
    transmissions from the CA should use the commanded address until another Commanded Address
    message is received or, through power-up or address contention, another address claim process is
    completed. If the Commanded CA elects to receive the Commanded Address message and cannot change
    to the commanded address, it should ignore the commanded address. A state transition diagram
    describing the process for handling a commanded address is presented in Appendix D, Figure D3. Note
    that if the Commanded CA does not accept the commanded address, an operator or technician may have
    to modify the CA’s source address or NAME through alternate means for the network to operate. If the
    source address or NAME is modified, the CA must re-issue an Address Claim before originating
    transmissions on the network. An ECU manufacturer may elect not to accept Commanded Address
    messages from CAs other than service tools or bridges. Further, ECU manufacturers may require some
    type of security verification process before accepting a Commanded Address message.
    The Commanded Address message contains 9 bytes of data and should be sent using the Broadcast
    Announce Mode (BAM) of the transport protocol (SAE J1939-21) and should be sent to the global address
    (255). CAs designed to support the Commanded Address message must also support the BAM form of the
    Transport Protocol.
    4.2.3.1 Commanded Address Message
    Transmission rate: As required
    Acknowledgement: See Figures A9 and A10 in Appendix A
    Data length: 9 bytes
    Data page: 0
    PDU format: 254
    PDU specific: 216
    Default priority: 6
    Parameter group number: 65240 (00FED816)
    NAME of Commanded Address Target
    Byte: 1 Bits 8-1 Least significant byte of Identity Number See 4.1.1.11
    Byte: 2 Bits 8-1 Second byte of Identity Number See 4.1.1.11
    Byte: 3 Bits 8-6 Least significant 3 bits of Manufacturer Code See 4.1.1.10
    Bits 5-1 Most significant 5 bits of Identity Number See 4.1.1.11
    Byte: 4 Bits 8-1 Most significant 8 bits of Manufacturer Code See 4.1.1.10
    Byte: 5 Bits 8-4 Function Instance See 4.1.1.8
    Bits 3-1 ECU Instance See 4.1.1.9
    Byte: 6 Bits 8-1 Function See 4.1.1.7
    Byte: 7 Bits 8-2 Vehicle System See 4.1.1.5
    Bit 1 Reserved See 4.1.1.6
    Byte: 8 Bit 8 Arbitrary Address Capable See 4.1.1.2
    Bits 7-5 Industry Group See 4.1.1.3
    Bits 4-1 Vehicle System Instance See 4.1.1.4
    Address Assignment
    Byte: 9 Bits 8-1 New source address See 4.2.3.2
    */

    /*
    4.2.3.1 命令地址消息
    传送接收速率： 依照要求
    应答： 参见附录 A 图 A9 和 A10 数据长度： 9 字节
    数据页： 0
    协议数据单元格式： 254
    特定协议数据单元： 216
    默认优先权： 6
    参数群编号： 65420（00FED816）
    命令地址对象的名字
    字节:1 位8 – 1 ID编号的最低字节 见4.1.1.11
    字节:2 位8 – 1 ID编号的第二字节 见4.1.1.11
    字节:3 位8 – 6 制造商代码的低3位 见4.1.1.10
    位5 – 1 ID编号的最高5位 见4.1.1.11
    字节:4 位8 – 1 制造商代码的高8位 见4.1.1.10
    字节:5 位8 – 4 功能实例 见4.1.1.8
    位3 – 1 ECU实例 见4.1.1.9
    字节:6 位8 – 1 功能 见4.1.1.7
    字节:7 位8 – 2 车辆系统 见4.1.1.5
    位1 保留 见4.1.1.6
    字节:8 位8 地址仲裁能力 见4.1.1.2
    位7 – 5 工业组 见4.1.1.3
    位4 – 1 车辆系统实例 见4.1.1.4
    地址分配
    字节:9 位8 – 1 新源地址 见4.2.3.2
    */
}

static void req_pgn_cbk_65253(uint16_t max_len, uint16_t *tx_len, uint8_t *tx_dat_p)
{
    memset(tx_dat_p, 0, max_len);

    /*
    PGN 65253 Engine Hours, Revolutions HOURS 
    Transmission Repetition Rate: On request 
    Data Length: 8 
    Extended Data Page: 0 
    Data Page: 0 
    PDU Format: 254 
    PDU Specific: 229 PGN Supporting Information:  
    Default Priority: 6 
    Parameter Group Number: 65253  (0x00FEE5) 
    Start Position Length Parameter Name SPN 
    1-4 4 bytes Engine Total Hours of Operation 247 
    5-8 4 bytes Engine Total Revolutions 249 
    */
    *(uint32_t *)(&tx_dat_p[0]) |= j1939_ecu_spn_get_val_to_obd(247);
    *(uint32_t *)(&tx_dat_p[4]) |= j1939_ecu_spn_get_val_to_obd(249);
}

static void req_pgn_cbk_64822(uint16_t max_len, uint16_t *tx_len, uint8_t *tx_dat_p)
{
    memset(tx_dat_p, 0, max_len);

    /*
    PGN 64822 Aftertreatment 2 Diesel Exhaust Fluid Information A2DEFI 
    Sensor Information which measures temperature, concentration, and conductivity of the diesel exhaust fluid of the 
    aftertreatment 2 system. 
    Transmission Repetition Rate: 1 s 
    Data Length: 8 
    Extended Data Page: 0 
    Data Page: 0 
    PDU Format: 253 
    PDU Specific: 54 PGN Supporting Information:  
    Default Priority: 6 
    Parameter Group Number: 64822  (0x00FD36) 
    Start Position Length Parameter Name SPN 
    1 1 byte Aftertreatment 2 Diesel Exhaust Fluid Temperature 2 4420 
    2 1 byte Aftertreatment 2 Diesel Exhaust Fluid Concentration 4421 
    3 1 byte Aftertreatment 2 Diesel Exhaust Fluid Conductivity 4422 
    4.1 5 bits Aftertreatment 2 Diesel Exhaust Fluid Temperature 2 Preliminary FMI 4423 
    5.1 5 bits Aftertreatment 2 Diesel Exhaust Fluid Properties Preliminary FMI 4424 
    6.1 4 bits Aftertreatment 2 Diesel Exhaust Fluid Type 4425 
     */
    *(uint8_t *)(&tx_dat_p[0]) |= j1939_ecu_spn_get_val_to_obd(4420);
    *(uint8_t *)(&tx_dat_p[1]) |= j1939_ecu_spn_get_val_to_obd(4421);
    *(uint8_t *)(&tx_dat_p[2]) |= j1939_ecu_spn_get_val_to_obd(4422);
    *(uint8_t *)(&tx_dat_p[3]) |= j1939_ecu_spn_get_val_to_obd(4423);
    *(uint8_t *)(&tx_dat_p[4]) |= j1939_ecu_spn_get_val_to_obd(4424);
    *(uint8_t *)(&tx_dat_p[5]) |= j1939_ecu_spn_get_val_to_obd(4425);
}

static void req_pgn_cbk_64823(uint16_t max_len, uint16_t *tx_len, uint8_t *tx_dat_p)
{
    memset(tx_dat_p, 0, max_len);

    /*
    PGN 64823 Aftertreatment 2 SCR Service Information A2SCRSI 
    This message contains SCR service information for aftertreatment system 2 (or bank 2). 
    Transmission Repetition Rate: On request 
    Data Length: 8 
    Extended Data Page: 0 
    Data Page: 0 
    PDU Format: 253 
    PDU Specific: 55 PGN Supporting Information:  
    Default Priority: 8 
    Parameter Group Number: 64823  (0x00FD37) 
    Start Position Length Parameter Name SPN 
    1-2 2 bytes Aftertreatment 2 Diesel Exhaust Fluid Average Consumption 4417 
    3-4 2 bytes Aftertreatment 2 SCR Commanded Catalyst Diesel Exhaust Fluid Consumption 4418 
    5 1 byte Aftertreatment 2 SCR Conversion Efficiency 4419 
      */
    *(uint16_t *)(&tx_dat_p[0]) |= j1939_ecu_spn_get_val_to_obd(4417);
    *(uint16_t *)(&tx_dat_p[2]) |= j1939_ecu_spn_get_val_to_obd(4418);
    *(uint8_t *)(&tx_dat_p[4]) |= j1939_ecu_spn_get_val_to_obd(4419);
}

static void req_pgn_cbk_65518(uint16_t max_len, uint16_t *tx_len, uint8_t *tx_dat_p)
{
    memset(tx_dat_p, 0, max_len);
}

bool j1939_req_pgn_cbk(uint16_t pgn, uint16_t max_len, uint16_t *tx_len, uint8_t *tx_dat_p)
{
    uint16_t i;

    // 查找PGN
    for (i = 0; i < SIZEOF_ARRAY(s_pgn_req_l); i++)
    {
        if (pgn == s_pgn_req_l[i].no)
        {
            if (s_pgn_req_l[i].en == false)
            {
                return false;
            }
            else
            {
                s_pgn_req_l[i].cbk(max_len, tx_len, tx_dat_p);
                return true;
            }
        }
    }
    return false;
}

bool j1939_ecu_pgn_req_init(void)
{
    j1939_reg_req_pgn_cbk(j1939_req_pgn_cbk);
    return true;
}

bool j1939_ecu_pgn_req_cfg(uint16_t pgn, bool stts)
{
    uint16_t i;

    if (pgn == 0xFFFF) // 全部PGN都配置
    {
        for (i = 0; i < SIZEOF_ARRAY(s_pgn_req_l); i++)
        {
            s_pgn_req_l[i].en = stts;
        }
    }

    for (i = 0; i < SIZEOF_ARRAY(s_pgn_req_l); i++)
    {
        if (s_pgn_req_l[i].no == pgn)
        {
            s_pgn_req_l[i].en = stts;
            return true;
        }
    }
    return false;
}
#if USE_J1939_ECU_REQ_SHELL == 1
// SHELL_EXPORT_CMD(属性, 命令名, 函数, 描述)
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0) | SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC),
                 reqpgn,
                 j1939_ecu_pgn_req_cfg,
                 "prdpgn 65276 0:关闭PGN65276的输出");
#endif

#endif /* end of USE_J1939_ECU_REQ */
