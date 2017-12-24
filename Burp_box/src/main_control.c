/*
 * main_control.c
 *
 * Created: 12/21/2017 4:51:49 PM
 *  Author: raghu
 */ 
#include <asf.h>
#include "main_control.h"
#include "spi_control.h"
void main_control_loop_1()
{
	uint16_t button_input = 0;
	uint16_t servo_input = 0;
	uint16_t overall_input = 0;
	//enum buttons_state button_input;
	//button_input  = check_input_buttons();
	//Servo input -- here
	overall_input = input_buttons ;//|| servo_input ;
	spi_main_loop_1(overall_input); 
}

