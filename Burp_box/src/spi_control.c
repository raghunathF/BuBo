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
#include "PWM_capture_control.h"

void spi_write_global_erase()
{
	spi_transceive(wr_buffer_global_erase , rd_buffer , BUF_LENGTH);
}

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

void wait_burp_box_2()
{
	bool burp_box_busy = false;
	int count_delay= 0;
	interrupt_occured = false;
	while(burp_box_busy != true /*&& time_out != true*/ && interrupt_occured !=true )
	{
		delay_spi();
		count_delay++;
		if(count_delay > 16*3)
		{
			burp_box_busy = true;
			count_delay = 0;
		}
	}
	spi_write_stop();
}

void wait_burp_box(uint8_t operation)
{
	bool burp_box_busy = true;
	interrupt_occured = false;
	while(burp_box_busy == true /*&& time_out != true*/ && interrupt_occured !=true )
	{
		delay_cycles_ms(200);
		spi_transceive( wr_buffer_status_pointer , rd_buffer_3 ,BUF_LENGTH_3);
		switch(operation)
		{
			case RECORD_OPERATION:
				burp_box_busy = rd_buffer_3[2] & RECORD_READY_MASK;
				break;
				
			case PLAY_OPERATION:
				burp_box_busy = rd_buffer_3[2] & PLAY_READY_MASK;
				break;
			case ERASE_OPERATION:
				burp_box_busy = rd_buffer_3[2] & ERASE_READY_MASK;
				break;
			default:
			    break;
		}
		
	}
	spi_write_stop();
}

void burp_box_record(uint8_t track_no)
{
	LED_on(RECORD_LED);
	switch (track_no)
	{
		case TRACK_NO_1:	
		
			spi_transceive( wr_buffer_record_set_1 , rd_buffer_6 ,BUF_LENGTH_6);
			break;
		
		case TRACK_NO_2:
		
			spi_transceive( wr_buffer_record_set_2 , rd_buffer_6 ,BUF_LENGTH_6);
			break;
		
		case TRACK_NO_3:
		
			spi_transceive( wr_buffer_record_set_3 , rd_buffer_6 ,BUF_LENGTH_6);
			break;
		
		default:
			break;
	}
	
	//Wait till the operation is complete
	//wait_burp_box_2();
	wait_burp_box(RECORD_OPERATION);
	spi_write_apc(wr_apc_2_ideal);
	LED_off(RECORD_LED);
}

void burp_box_erase(uint8_t track_no)
{
	spi_write_stop();
	switch(track_no)
	{
		case TRACK_NO_1:
		     spi_transceive( wr_buffer_erase_set_1 , rd_buffer_6 ,BUF_LENGTH_6);
			 break;
			 
		case TRACK_NO_2:
			 spi_transceive( wr_buffer_erase_set_2 , rd_buffer_6 ,BUF_LENGTH_6);
			 break;
			 
	    case TRACK_NO_3:
			spi_transceive( wr_buffer_erase_set_3 , rd_buffer_6 ,BUF_LENGTH_6);
			 break;
			 
		default:
			 break;
	}
	//wait_burp_box_2();
	wait_burp_box(ERASE_OPERATION);
	spi_write_stop();
	//delay_cycles_ms(300);
}

void burp_box_play(uint8_t track_no)
{
	//time_out = false;
	//Clear interrupts
	LED_on(PLAY_LED);
	spi_write_clear_int();
	switch (track_no)
	{
		
		case TRACK_NO_1:
		
			spi_transceive( wr_buffer_play_set_1 , rd_buffer_6 ,BUF_LENGTH_6);
			break;
			
		case TRACK_NO_2:
		
			spi_transceive( wr_buffer_play_set_2 , rd_buffer_6 ,BUF_LENGTH_6);
			//Wait till the operation is complete
			break;
			
		case TRACK_NO_3:
		
			spi_transceive( wr_buffer_play_set_3 , rd_buffer_6 ,BUF_LENGTH_6);
			break;
		
		default:
			break;
	}
	
	//Wait till the operation is complete
	//LED_on(PLAY_LED);
	wait_burp_box(PLAY_OPERATION);
	LED_off(PLAY_LED);
}



void global_erase_LED_flashing()
{
	int i =0;
	int j =0;
	
	for(j=0;j<LOOP_2;j++)
	{
		for(i=LOOP_1_START;i<LOOP_1_END;i = i+2)
		{
			LED_off(PLAY_LED);
			LED_off(RECORD_LED);
			delay_cycles_us(i);
			LED_on(RECORD_LED);
			LED_on(PLAY_LED);
			delay_cycles_us(LOOP_1_END-i);
		}
	}
	LED_off(PLAY_LED);
	LED_off(RECORD_LED);
}


void burp_box_global_erase()
{
	bool burp_box_busy = true;
	LED_on(PLAY_LED);
	LED_on(RECORD_LED);
	
	spi_write_global_erase();
	
	while(burp_box_busy == true)
	{
		delay_cycles_ms(200);
		spi_transceive( wr_buffer_status_pointer , rd_buffer_3 ,BUF_LENGTH_3);
		burp_box_busy = rd_buffer_3[2] & ERASE_READY_MASK;
	}
	
	spi_write_stop();
	
	LED_off(PLAY_LED);
	LED_off(RECORD_LED);
	//2 Seconds
	global_erase_LED_flashing();
}

void spi_main_loop_1(uint16_t input_buttons_servo)
{
	switch (input_buttons_servo)
	{	
		
		case PLAY_BUTTON_PRESSED:
			spi_write_stop();
			//LED_on(PLAY_LED);
			spi_write_apc(wr_apc_2_play_memory);
			spi_write_clear_int();
			burp_box_play(track_pointer);
			//LED_off(PLAY_LED);
			spi_write_apc(wr_apc_2_ideal);
			interrupt_occured = false;
			break;
			
		case RECORD_BUTTON_PRESSED:
			burp_box_erase(track_pointer);
			//LED_on(RECORD_LED);
			spi_write_apc(wr_apc_2_record_mic);
			burp_box_record(track_pointer);
			//LED_off(RECORD_LED);
			spi_write_apc(wr_apc_2_ideal);
			interrupt_occured = false;
			break;
		
		case NEXT_BUTTON_PRESSED:
			spi_write_stop();
			track_pointer++;
			if(track_pointer > 3)
			{
				track_pointer = 1;
			}
			LED_track(track_pointer-1);
			interrupt_occured = false;
			break;
		case N_P_PRESSED:
			spi_write_stop();
			track_pointer = TRACK_NO_1;
			burp_box_global_erase();
			global_erase_LED_flashing();
			LED_track(track_pointer-1);
			interrupt_occured = false;
			break;
		case FUTURE_USE:
			break;
		case TRACK_1_VOLUME_1:
			burp_box_set_volume_track(VOLUME_1,TRACK_1);
			break;
		case TRACK_1_VOLUME_2:
			burp_box_set_volume_track(VOLUME_3,TRACK_1);
			break;
		case TRACK_1_VOLUME_3:
			burp_box_set_volume_track(VOLUME_5,TRACK_1);
			break;
		case TRACK_2_VOLUME_1:
			burp_box_set_volume_track(VOLUME_1,TRACK_2);
			break;
		case TRACK_2_VOLUME_2:
			burp_box_set_volume_track(VOLUME_3,TRACK_2);
			break;
		case TRACK_2_VOLUME_3:
			burp_box_set_volume_track(VOLUME_5,TRACK_2);
			break;
		case TRACK_3_VOLUME_1:
			burp_box_set_volume_track(VOLUME_1,TRACK_3);
			break;
		case TRACK_3_VOLUME_2:
			burp_box_set_volume_track(VOLUME_3,TRACK_3);
			break;
		case TRACK_3_VOLUME_3:
			burp_box_set_volume_track(VOLUME_5,TRACK_3);
			break;
		case TRACK_1_RECORD_MIC:
			break;
		case TRACK_1_RECORD_ANAIN:
			break;
		case TRACK_2_RECORD_MIC:
			break;
		case TRACK_2_RECORD_ANAIN:
			break;
		case TRACK_3_RECORD_MIC:
			break;
		case TRACK_3_RECORD_ANAIN:
			break;
		case FT_MIC:
			break;
		case FT_ANAIN:
			break;
		case REPEAT_HELP:
			break;
		case UNDEFINED:
			break;
		
		default:
			break;
	}
}

