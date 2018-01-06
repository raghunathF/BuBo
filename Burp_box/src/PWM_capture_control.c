/*
 * PWM_capture_control.c
 *
 * Created: 12/25/2017 5:53:51 PM
 *  Author: raghu
 */ 
#include <asf.h>

#include "PWM_capture_control.h"
#include "spi_control.h"
#include "bsp.h"



void change_rec_mode(uint8_t rec_mode)
{
	spi_write_stop();
	switch(rec_mode)
	{
		case IDEAL_STATE:
			spi_write_apc(wr_apc_2_ideal);
			break;
		case MIC:
			spi_write_apc(wr_apc_2_record_mic);
			break;
		case ANALOG_IN:
			spi_write_apc(wr_apc_2_record_analogIn);
			break;
		default:
			break;
	}
	spi_write_stop();
}

void change_volume(uint8_t volume)
{
	spi_write_stop();
	switch (volume)
	{
		case VOLUME_1:
			spi_write_apc(wr_apc_2_volume_1);
			break;
		case VOLUME_2:
			spi_write_apc(wr_apc_2_volume_2);
			break;
		case VOLUME_3:
			spi_write_apc(wr_apc_2_volume_3);
			break;
		case VOLUME_4:
			spi_write_apc(wr_apc_2_volume_4);
			break;
		case VOLUME_5:
			spi_write_apc(wr_apc_2_volume_5);
			break;
		default:
			break;
	}
	spi_write_stop();
}

void change_input(uint8_t input)
{
	spi_write_stop();
	switch (input)
	{
		case IDEAL_STATE:
			spi_write_apc(wr_apc_2_ideal);
			break;
		case MIC:
			spi_write_apc(wr_apc_2_speaker_mic_analogIn);
			break;
		case ANALOG_IN:
			spi_write_apc(wr_apc_2_speaker_analogIn);
			break;
		
		default:
			break;
	}
	delay_cycles_ms(200);
	spi_write_stop();
}


void burp_box_set_record_input(uint8_t rec_mode,uint8_t track_no)
{
	if(track_pointer != track_no)
	{
		track_pointer = track_no;
		LED_track(track_no - 1);
	}
	
	burp_box_erase(track_no);
	change_rec_mode(rec_mode);
	burp_box_record(track_no);
	change_rec_mode(IDEAL_STATE);
}

void burp_box_set_speaker(uint8_t input)
{
	change_input(input);
}


void burp_box_set_volume_track(uint8_t volume,uint8_t track_no)
{
	if(track_pointer != track_no)
	{
		track_pointer = track_no;
		LED_track(track_no - 1);
	}
	change_volume(volume);
	burp_box_play(track_no);
}
