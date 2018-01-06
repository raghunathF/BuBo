/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# Minimal main function that starts with a call to system_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>
#include "spi_master.h"
#include "bsp.h"
#include "test.h"
#include "spi_control.h"
#include "buttons.h"
#include "main_control.h"
#include "PWM_capture.h"
#include "prog_test.h"

volatile uint8_t track_pointer = 0;
volatile uint8_t input_buttons = 0;
volatile bool interrupt_occured = false;


int main (void)
{
	
	system_init();
	system_interrupt_enable_global();
	
	//Initailise the timer for the delay
	delay_init();
	
	
	//Leds and buttons initialization
	init_led_buttons();
	//SPI initialization
	configure_spi();
	//Init buttons
	init_buttons();
	//Init Servo Pulse capture
	
	
	//Init_burp_box
	init_burp_box();
	
	//main_1();
	init_servo_capture();
	
	//test_volume_func();
	//test_record_func();
	//test_speaker_func();
	while(1)
	{
		//LED_on(PLAY_LED);
		//speaker_test();
		//LED_off(PLAY_LED);
		//delay_cycles_ms(1000);
		//test_led_on_off_toggle();
		//test_buttons();
		//test_track_led();
		
		//main_control_loop_1();
		//delay_cycles_ms(1);
		//event_counter(&servo_pulse_event);
	}
	
	/* Insert application code here, after the board has been initialized. */
}
