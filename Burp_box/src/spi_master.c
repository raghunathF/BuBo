/*
 * spi_master.c
 *
 * Created: 11/2/2017 11:38:14 AM
 *  Author: raghu
 */ 
#include <asf.h>
#include "spi_master.h"
#include "pinout.h"
#include "bsp.h"
#include "spi_control.h"

volatile bool transrev_complete_spi_master = false;

void init_spi()
{
	struct spi_config config_spi_master;
	struct spi_slave_inst_config slave_dev_config;
	
	spi_slave_inst_get_config_defaults(&slave_dev_config);
	slave_dev_config.ss_pin = SPI_SS_PIN;
	spi_attach_slave(&slave, &slave_dev_config);
	spi_get_config_defaults(&config_spi_master);

	config_spi_master.mux_setting = SPI_SERCOM_MUX_SETTING;
	
	//! [mux_setting]
	config_spi_master.data_order  = SPI_DATA_ORDER_LSB;
	config_spi_master.pinmux_pad0 = SPI_MOSI_PIN;
	config_spi_master.pinmux_pad1 = SPI_SCK_PIN;
	config_spi_master.pinmux_pad2 = PINMUX_UNUSED;
	config_spi_master.pinmux_pad3 = SPI_MISO_PIN;
	
	spi_init(&spi_master_instance, SPI_MODULE, &config_spi_master);
	spi_enable(&spi_master_instance);

}

static void callback_spi_master( struct spi_module *const module)
{
	//! [callback_var]
	transrev_complete_spi_master = true;
	//! [callback_var]
}

void configure_spi_master_callbacks(void)
{
	//! [reg_callback]
	spi_register_callback(&spi_master_instance, callback_spi_master,SPI_CALLBACK_BUFFER_TRANSCEIVED);
	spi_enable_callback(&spi_master_instance, SPI_CALLBACK_BUFFER_TRANSCEIVED);
	//! [en_callback]
}

//! [configure_spi]
void configure_spi(void)
{
	init_spi();
	configure_spi_master_callbacks();

}

void spi_transceive (uint8_t* wr_buffer , uint8_t* rd_buffer ,uint8_t buff_length)
{
	spi_select_slave(&spi_master_instance, &slave, true);
	spi_transceive_buffer_job(&spi_master_instance, wr_buffer ,rd_buffer , buff_length);
	while (!transrev_complete_spi_master)
	{
	}
	transrev_complete_spi_master = false;
	spi_select_slave(&spi_master_instance, &slave, false);
}
/*
#define BUF_LENGTH  2 
static uint8_t wr_buffer_reset[BUF_LENGTH] =
{
	0x03,0x00
};
static uint8_t rd_buffer_reset[BUF_LENGTH];

void spi_transceive (uint8_t* wr_buffer , uint8_t* rd_buffer ,uint8_t buff_length)
{
	//spi_select_slave(&spi_master_instance, &slave, false);
	spi_select_slave(&spi_master_instance, &slave, true);
	spi_transceive_buffer_job(&spi_master_instance, wr_buffer_reset ,rd_buffer_reset , BUF_LENGTH);
	while (!transrev_complete_spi_master)
	{
	}
	//Debug _LED
	LED_on(RECORD_LED);
	delay_cycles_ms(2000);
	LED_off(RECORD_LED);
	delay_cycles_ms(2000);
	transrev_complete_spi_master = false;
	spi_select_slave(&spi_master_instance, &slave, false);
}
*/
/*
static uint8_t rd_buffer[BUF_LENGTH];
static uint8_t rd_buffer_4[BUF_LENGTH_4];
static uint8_t rd_buffer_6[BUF_LENGTH_6];
static uint8_t rd_buffer_3[BUF_LENGTH_3];
*/
//! [buffer]

void speaker_test()
{
			/*
	        //--Find the device ID
			spi_select_slave(&spi_master_instance, &slave, true);
			spi_transceive_buffer_job(&spi_master_instance,  wr_buffer_dev_id,rd_buffer_3,BUF_LENGTH_3);
			while (!transrev_complete_spi_master) 
			{
			}
			transrev_complete_spi_master = false;
			spi_select_slave(&spi_master_instance, &slave, false);
			delay_cycles_ms(200);
			*/
			/*
			//--Reset
			spi_select_slave(&spi_master_instance, &slave, true);
			spi_transceive_buffer_job(&spi_master_instance, wr_buffer_reset,rd_buffer,BUF_LENGTH);
			while (!transrev_complete_spi_master) 
			{
			}
			transrev_complete_spi_master = false;
			spi_select_slave(&spi_master_instance, &slave, false);
			delay_cycles_ms(200);
			
			
			//--Power-on the SPI
			spi_select_slave(&spi_master_instance, &slave, true);
			spi_transceive_buffer_job(&spi_master_instance, wr_buffer_power_on,rd_buffer,BUF_LENGTH);
			while (!transrev_complete_spi_master) 
			{
			}
			transrev_complete_spi_master = false;
			spi_select_slave(&spi_master_instance, &slave, false);
			delay_cycles_ms(200);
			
			
			//--Global erase
			spi_select_slave(&spi_master_instance, &slave, true);
			spi_transceive_buffer_job(&spi_master_instance, wr_buffer_gerase,rd_buffer,BUF_LENGTH);
			while (!transrev_complete_spi_master)
			{
			}
			transrev_complete_spi_master = false;
			spi_select_slave(&spi_master_instance, &slave, false);
			delay_cycles_ms(200);
			
			
			//--Write APC-2
			spi_select_slave(&spi_master_instance, &slave, true);
			spi_transceive_buffer_job(&spi_master_instance, wr_apc_2_ideal, rd_buffer_4,BUF_LENGTH_3);
			while (!transrev_complete_spi_master)
			{
			}
			transrev_complete_spi_master = false;
			spi_select_slave(&spi_master_instance, &slave, false);
			delay_cycles_ms(200);
			
			/*
			//--Read APC
			spi_select_slave(&spi_master_instance, &slave, true);
			spi_transceive_buffer_job(&spi_master_instance, rd_apc, rd_buffer_4,BUF_LENGTH_4);
			while (!transrev_complete_spi_master)
			{
			}
			transrev_complete_spi_master = false;
			spi_select_slave(&spi_master_instance, &slave, false);
			delay_cycles_ms(200);
			
			
			delay_cycles_ms(3000);
			
			//--Check Memory 
			spi_select_slave(&spi_master_instance, &slave, true);
			spi_transceive_buffer_job(&spi_master_instance, wr_buffer_check_mem,rd_buffer,BUF_LENGTH);
			while (!transrev_complete_spi_master)
			{
			}
			transrev_complete_spi_master = false;
			spi_select_slave(&spi_master_instance, &slave, false);
		    delay_cycles_ms(200);
			
			*/
			
			//--Clear INIT
			spi_select_slave(&spi_master_instance, &slave, true);
			spi_transceive_buffer_job(&spi_master_instance, wr_buffer_clr_init,rd_buffer,BUF_LENGTH);
			while (!transrev_complete_spi_master)
			{
			}
			transrev_complete_spi_master = false;
			spi_select_slave(&spi_master_instance, &slave, false);
			
			
			delay_cycles_ms(200);
			/*
			//Check the record pointer
			spi_select_slave(&spi_master_instance, &slave, true);
			spi_transceive_buffer_job(&spi_master_instance, wr_buffer_rec_pointer,rd_buffer_4,BUF_LENGTH_4);
			while (!transrev_complete_spi_master)
			{
			}
			transrev_complete_spi_master = false;
			spi_select_slave(&spi_master_instance, &slave, false);
			
			*/
			/*
			//--Record for sometime 
			spi_select_slave(&spi_master_instance, &slave, true);
			spi_transceive_buffer_job(&spi_master_instance, wr_buffer_record,rd_buffer,BUF_LENGTH);
			while (!transrev_complete_spi_master)
			{
			}
			transrev_complete_spi_master = false;
			spi_select_slave(&spi_master_instance, &slave, false);
			*/
			
			//--Record-2
			delay_cycles_ms(200);
			spi_select_slave(&spi_master_instance, &slave, true);
			spi_transceive_buffer_job(&spi_master_instance, wr_buffer_record_set_1,rd_buffer_6,BUF_LENGTH_6);
			while (!transrev_complete_spi_master)
			{
			}
			transrev_complete_spi_master = false;
			spi_select_slave(&spi_master_instance, &slave, false);
			
			//Wait for 12 seconds 
			delay_cycles_ms(6000);
			
			
			//Send stop command
			
			spi_select_slave(&spi_master_instance, &slave, true);
			spi_transceive_buffer_job(&spi_master_instance, wr_buffer_stop,rd_buffer,BUF_LENGTH);
			while (!transrev_complete_spi_master)
			{
			}
			transrev_complete_spi_master = false;
			spi_select_slave(&spi_master_instance, &slave, false);
			
			
			/*
			
			delay_ms(100);
			//Check the record pointer
			spi_select_slave(&spi_master_instance, &slave, true);
			spi_transceive_buffer_job(&spi_master_instance, wr_buffer_rec_pointer,rd_buffer_4,BUF_LENGTH_4);
			while (!transrev_complete_spi_master)
			{
			}
			transrev_complete_spi_master = false;
			spi_select_slave(&spi_master_instance, &slave, false);
			
			delay_ms(200);
			//Check the play_back pointer
			spi_select_slave(&spi_master_instance, &slave, true);
			spi_transceive_buffer_job(&spi_master_instance, wr_buffer_play_pointer,rd_buffer_4,BUF_LENGTH_4);
			while (!transrev_complete_spi_master)
			{
			}
			transrev_complete_spi_master = false;
			spi_select_slave(&spi_master_instance, &slave, false);
			
			*/			
			delay_cycles_ms(300);
			
			//Play the recorded
			spi_select_slave(&spi_master_instance, &slave, true);
			spi_transceive_buffer_job(&spi_master_instance, wr_buffer_play_set_1,rd_buffer_6,BUF_LENGTH_6);
			while (!transrev_complete_spi_master)
			{
			}
			transrev_complete_spi_master = false;
			spi_select_slave(&spi_master_instance, &slave, false);
			
			
			/*
			//--Play
			spi_select_slave(&spi_master_instance, &slave, true);
			spi_transceive_buffer_job(&spi_master_instance,  wr_buffer_play,rd_buffer,BUF_LENGTH);
			while (!transrev_complete_spi_master)
			{
			}
			transrev_complete_spi_master = false;
			spi_select_slave(&spi_master_instance, &slave, false);
			delay_cycles_ms(200);
			*/
		
			delay_cycles_ms(6000);
			
			//--Send stop command
			spi_select_slave(&spi_master_instance, &slave, true);
			spi_transceive_buffer_job(&spi_master_instance, wr_buffer_stop,rd_buffer,BUF_LENGTH);
			while (!transrev_complete_spi_master)
			{
			}
			transrev_complete_spi_master = false;
			spi_select_slave(&spi_master_instance, &slave, false);
				
}
