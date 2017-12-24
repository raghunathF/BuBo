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


