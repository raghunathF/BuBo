/*
 * test.c
 *
 * Created: 11/3/2017 6:48:37 PM
 *  Author: raghu
 */ 

#include <asf.h>
#include "bsp.h"
#include "delay.h"
#include "pinout.h"
#include "spi_control.h"
#include "PWM_capture_control.h"

void test_track_led()
{
	int i =0;
	for(i=0 ; i<20 ; i++)
	{
		LED_track(i%3);
		delay_cycles_ms(10000);
	}
}

void test_led_on_off_toggle()
{
	int i =0;
	for(i=0 ; i<20 ; i++)
	{
		if(i%2==0)
		{
			LED_off(RECORD_LED);
			LED_toggle(PLAY_LED);
			delay_cycles_ms(2000);
			LED_on(RECORD_LED);
			LED_toggle(PLAY_LED);
			delay_cycles_ms(2000);
		}
		else
		{
			LED_on(PLAY_LED);
			LED_toggle(RECORD_LED);
			delay_cycles_ms(2000);
			LED_off(PLAY_LED);
			LED_toggle(RECORD_LED);
			delay_cycles_ms(2000);
		}
		
	}
}



void test_buttons()
{
	volatile int i =0;
	i = check_input_buttons();
	//LED_track(i%3);
}


void test_volume_func()
{
	int i =0;
	int j =0;
	for(i=1; i<=3 ; i++)
	{
		for(j=1;j<=5;j++)
		{
			burp_box_set_volume_track(j,i);
			delay_cycles_ms(1000);
		}		
	}
}


void test_record_func()
{
	int i =0;
	int j =0;
	
	for(i =1 ; i<=3 ; i++)
	{
		for(j=1 ; j<=2 ; j++ )
		{
			burp_box_set_record_input(j,i);
			delay_cycles_ms(1000);
			burp_box_set_volume_track(5,i);
		}
		
	}
	
}

void test_speaker_func()
{
	int i=0;
	for(i=2;i<=2;i++)
	{
		burp_box_set_speaker(i);
		delay_cycles_ms(10000);
	}
}