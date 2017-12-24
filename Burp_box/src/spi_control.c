/*
 * CFile1.c
 *
 * Created: 11/6/2017 11:28:17 AM
 *  Author: raghu
 */ 
#include <asf.h>
#include "spi_control.h"
#include "spi_master.h"
#include "delay.h"
#include "bsp.h"

void spi_write_reset()
{
	spi_transceive(wr_buffer_reset , rd_buffer , BUF_LENGTH);
}

void spi_write_power_on()
{
	spi_transceive ( wr_buffer_power_on , rd_buffer , BUF_LENGTH);
}

void spi_write_clear_int()
{
	spi_transceive ( wr_buffer_clr_init , rd_buffer , BUF_LENGTH);
}

void spi_write_apc(uint8_t* write_apc)
{
	spi_transceive( write_apc , rd_buffer_3 ,BUF_LENGTH_3);
}

void spi_write_stop()
{
	spi_transceive(wr_buffer_stop,rd_buffer, BUF_LENGTH);
}

void delay_spi()
{
	delay_cycles_ms(100); //Datasheet specific
}

void init_burp_box()
{
	//Reset the device 
	spi_write_reset();
	delay_spi();
	
	//Power on the device
	spi_write_power_on();
	delay_spi();
	
	//Cleat Interrupt
	spi_write_clear_int();
	delay_spi();
	
	//Choose input
	spi_write_apc(wr_apc_2_ideal); //Volume init -- High 
	delay_spi();	
	
	//trackpointer -- Initialized to one
	track_pointer = 1;
}

void wait_burp_box()
{
	bool burp_box_busy = false;
	while(burp_box_busy != true /*&& time_out != true*/ && interrupt_occured !=true )
	{
		delay_spi();
		spi_transceive( wr_buffer_status_pointer , rd_buffer_3 ,BUF_LENGTH_4);
		burp_box_busy = rd_buffer_3[1] & 0x10;
	}
	spi_write_stop();
}

void burp_box_record(uint8_t track_no)
{
	
	switch (track_no)
	{
		case TRACK_NO_1:	
		
			spi_transceive( wr_buffer_record_set_1 , rd_buffer_6 ,BUF_LENGTH_6);
			break;
		
		case TRACK_NO_2:
		
			spi_transceive( wr_buffer_record_set_2 , rd_buffer_6 ,BUF_LENGTH_6);
			break;
		
		case TRACK_NO_3:
			spi_transceive( wr_buffer_record_set_2 , rd_buffer_6 ,BUF_LENGTH_6);
			break;
		
		default:
			break;
	}
	//Wait till the operation is complete
	wait_burp_box();
	
}

void burp_box_play(uint8_t track_no)
{
	//time_out = false;
	switch (track_no)
	{
		
		case TRACK_NO_1:
		
			spi_transceive( wr_buffer_play_set_1 , rd_buffer_6 ,BUF_LENGTH_6);
			break;
			
		case TRACK_NO_2:
		
			spi_transceive( wr_buffer_play_set_3 , rd_buffer_6 ,BUF_LENGTH_6);
			//Wait till the operation is complete
			break;
			
		case TRACK_NO_3:
		
			spi_transceive( wr_buffer_play_set_3 , rd_buffer_6 ,BUF_LENGTH_6);
			break;
		
		default:
			break;
	}
	
	//Wait till the operation is complete
	wait_burp_box();
}

void spi_main_loop_1(uint16_t input_buttons_servo)
{
	switch (input_buttons_servo)
	{	
		case IDEAL_STATE:
			break;
		case PLAY_BUTTON_PRESSED:
		
			spi_write_stop();
			LED_on(PLAY_LED);
			spi_write_apc(wr_apc_2_play_memory);
			spi_write_clear_int();
			burp_box_play(track_pointer);
			LED_off(PLAY_LED);
			spi_write_apc(wr_apc_2_ideal);
			break;
			
		case RECORD_BUTTON_PRESSED:
		
			spi_write_stop();
			LED_on(RECORD_LED);
			spi_write_apc(wr_apc_2_record_mic);
			burp_box_record(track_pointer);
			LED_off(RECORD_LED);
			spi_write_apc(wr_apc_2_ideal);
			break;
		
		case NEXT_BUTTON_PRESSED:
			spi_write_stop();
			track_pointer++;
			if(track_pointer > 3)
			{
				track_pointer = 1;
			}
			LED_track(track_pointer);
			break;
		
		default:
			break;
	}
}