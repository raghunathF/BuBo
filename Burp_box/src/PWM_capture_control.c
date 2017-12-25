/*
 * PWM_capture_control.c
 *
 * Created: 12/25/2017 5:53:51 PM
 *  Author: raghu
 */ 
#include <asf.h>

#include "PWM_capture_control.h"
#include "spi_control.h"
/*
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


void burp_box_set_volume_track(uint8_t volume,uint8_t track_no)
{
	change_volume(volume);
	burp_box_play(track_no);
}
*/