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

volatile uint8_t track_pointer = 0;
volatile uint8_t input_buttons = 0;
volatile bool interrupt_occured = false;

int main (void)
{
	system_init();
	
	//Initailise the timer for the delay
	delay_init();
	
	//Leds and buttons initialization
	//init_led_buttons();
	
	//SPI initialization
	//configure_spi();
	
	//Init buttons
	init_buttons();
	
	//Init_burp_box
	//init_burp_box();
	
	while(1)
	{
		//speaker_test();
		//test_led_on_off_toggle();
		//test_but	tons();
		main_control_loop_1();
	}
	
	/* Insert application code here, after the board has been initialized. */
}
