
/** @file
 * @defgroup 
 * @{
 * @ingroup 
 * @brief TWI Sensor Example main file.
 *
 * This file contains the source code for a sample application using TWI.
 *
 */

#include <stdio.h>
#include "boards.h"
#include "app_util_platform.h"
#include "app_error.h"
#include "nrf_drv_twi.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "nrf_delay.h"
#include "register map.h"


/* TWI instance ID. */
#if TWI0_ENABLED
#define TWI_INSTANCE_ID     0
#elif TWI1_ENABLED
#define TWI_INSTANCE_ID     1
#endif


/* Number of possible TWI addresses. */
 #define TWI_ADDRESSES      127

/* TWI instance. */
static const nrf_drv_twi_t m_twi = NRF_DRV_TWI_INSTANCE(TWI_INSTANCE_ID);

/**
 * @brief TWI initialization.
 */
void twi_init (void)
{
    ret_code_t err_code;
    const nrf_drv_twi_config_t twi_config = {
       .scl                = 3,
       .sda                = 4,
       .frequency          = NRF_DRV_TWI_FREQ_100K,
       .interrupt_priority = APP_IRQ_PRIORITY_HIGH,
       .clear_bus_init     = false
    };

    err_code = nrf_drv_twi_init(&m_twi, &twi_config, NULL, NULL);
    APP_ERROR_CHECK(err_code);

    nrf_drv_twi_enable(&m_twi);
}


/**
 * @brief Function for main application entry.
 */

uint32_t read_register(uint8_t reg, uint8_t * p_data, uint32_t length)
{
    uint32_t err_code;
    err_code = nrf_drv_twi_tx(&m_twi, BH1790GLC_ADDRESS, &reg, 1, false);
    if(err_code != NRF_SUCCESS) return err_code;

    
    err_code = nrf_drv_twi_rx(&m_twi, BH1790GLC_ADDRESS, p_data, length);
    if(err_code != NRF_SUCCESS) return err_code;
    return err_code;
}

uint32_t write_register(uint8_t reg_address, uint8_t data)
{
    ret_code_t err_code; 
    uint8_t buffer_send[2] = {reg_address, data};
		
    err_code = nrf_drv_twi_tx(&m_twi, BH1790GLC_ADDRESS, buffer_send, sizeof(buffer_send), true);
    APP_ERROR_CHECK(err_code);
	
}

uint16_t led_on;
uint16_t led_off;
uint8_t LEDdata[4];

void BH1790GLC_Init();
void	BH1790GLC_Config();

int main(void)
{
		
    ret_code_t err_code;
    uint8_t address;
    uint8_t sample_data;
    bool detected_device = false;

    APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
    NRF_LOG_DEFAULT_BACKENDS_INIT();

     twi_init();
		
	 BH1790GLC_Init();
   BH1790GLC_Config();
	
	for(;;)
	{
		err_code = read_register(DATAOUT_LEDOFF_LOW_BYTE,LEDdata,4);
		
		led_on= LEDdata[3]<<8|LEDdata[2];
		led_off = LEDdata[1]<<8|LEDdata[0];
		
		NRF_LOG_RAW_INFO("LED On: %d\r\n",led_on);
		NRF_LOG_RAW_INFO("LED_Off: %d\r\n",led_off);
		NRF_LOG_FLUSH();
		nrf_delay_ms(25);
	}
}


void BH1790GLC_Init()
{
		ret_code_t err_code;
		uint8_t regAddress;
		uint8_t data[3];
	
		err_code = read_register(PART_ID,&regAddress,sizeof(regAddress));
	
		if(err_code!=NRF_SUCCESS)
		{
			NRF_LOG_RAW_INFO("BH1790GLC inaccessible\r\n");
		}
		APP_ERROR_CHECK(err_code);
		NRF_LOG_RAW_INFO("BH1790GLC Part ID: %X", regAddress);
		
		if (regAddress != BH1790GLC_PID_VAL) {
    NRF_LOG_RAW_INFO("BH1790GLC not found");
		
	err_code =read_register(MANUFACTURER_ID, &regAddress, sizeof(regAddress));
	if (err_code != NRF_SUCCESS) {
    NRF_LOG_RAW_INFO("Can't access BH1790GLC");
  }
	APP_ERROR_CHECK(err_code);
	NRF_LOG_RAW_INFO("BH1790GLC MANUFACTURER ID Value = 0x",regAddress);
  
  if (regAddress != BH1790GLC_MID_VAL) {
    NRF_LOG_RAW_INFO("BH1790GLC not found");
  }
}
	
}

void BH1790GLC_Config()
{
	ret_code_t err_code;
	err_code = write_register (MEAS_CONTROL1,MEAS_CONTROL1_DATA);
	APP_ERROR_CHECK(err_code);
	err_code = write_register (MEAS_CONTROL2,MEAS_CONTROL2_DATA);
	APP_ERROR_CHECK(err_code);
	err_code=write_register(MEAS_START,MEAS_START_MEAS_ST);
	APP_ERROR_CHECK(err_code);
	
}
