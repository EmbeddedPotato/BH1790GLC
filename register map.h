/*
  _____  ______ _____ _____  _____ _______ ______ _____        __  __          _____  
 |  __ \|  ____/ ____|_   _|/ ____|__   __|  ____|  __ \      |  \/  |   /\   |  __ \ 
 | |__) | |__ | |  __  | | | (___    | |  | |__  | |__) |     | \  / |  /  \  | |__) |
 |  _  /|  __|| | |_ | | |  \___ \   | |  |  __| |  _  /      | |\/| | / /\ \ |  ___/ 
 | | \ \| |___| |__| |_| |_ ____) |  | |  | |____| | \ \      | |  | |/ ____ \| |     
 |_|  \_\______\_____|_____|_____/   |_|  |______|_|  \_\     |_|  |_/_/    \_\_|  

*/
        



 
#define BH1790GLC_ADDRESS      				(0x5B)    
#define BH1790GLC_MID_VAL             (0xE0)
#define BH1790GLC_PID_VAL             (0x0D)

#define RDY                     (1 << 7)
#define LED_LIGHTING_FREQ_128HZ (0 << 2)
#define RCYCLE_32HZ             (1 << 0)

#define LED_EN_00               (0 << 6)
#define LED_ON_TIME_03MS       (0 << 2)
#define LED_CURRENT_06MA        (11 << 0)

#define MANUFACTURER_ID     (0x0F)
#define PART_ID             (0x10)

#define MEAS_CONTROL1       (0x41)
#define MEAS_CONTROL2				(0x42)
#define MEAS_START					(0x43)

#define DATAOUT_LEDOFF      (0x54)

// Config Registers 

#define MEAS_START_MEAS_ST   	1
#define MEAS_CONTROL1_DATA   (RDY | LED_LIGHTING_FREQ_128HZ | RCYCLE_32HZ)
#define MEAS_CONTROL2_DATA   (LED_EN_00 | LED_ON_TIME_03MS |LED_CURRENT_06MA)
#define MEAS_START_DATA      (MEAS_START_MEAS_ST)

#define DATAOUT_LEDOFF_LOW_BYTE  0x54
#define DATAOUT_LEDOFF_HIGH_BYTE 0x55
#define DATAOUT_LEDON_LOW_BYTE   0x56
#define DATAOUT_LEDOn_HIGH_BYTE  0x57