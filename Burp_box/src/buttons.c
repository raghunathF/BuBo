/*
 * buttons.c
 *
 * Created: 12/22/2017 10:29:54 AM
 *  Author: raghu
 */ 

#include <asf.h>
#include "buttons.h"
#include "bsp.h"


#define EXTINT_FLAG_STATUS   0x40001810UL
#define EXTINT_FLAG_CLEAR    0x4000180BUL
#define MASK_FLAG_BUTTONS    0x000000E0UL
#define DEBOUNCE_DELAY       125

void enable_buttons()
{
	extint_chan_enable_callback(PLAY_BUTTON_EIC_LINE,EXTINT_CALLBACK_TYPE_DETECT);
	/*
	extint_chan_enable_callback(RECORD_BUTTON_EIC_LINE,EXTINT_CALLBACK_TYPE_DETECT);
	*/
	extint_chan_enable_callback(NEXT_BUTTON_EIC_LINE,EXTINT_CALLBACK_TYPE_DETECT);
	
}
	
void disable_buttons()
{
	extint_chan_disable_callback(PLAY_BUTTON_EIC_LINE,EXTINT_CALLBACK_TYPE_DETECT);
	//extint_chan_disable_callback(RECORD_BUTTON_EIC_LINE,EXTINT_CALLBACK_TYPE_DETECT);
	extint_chan_disable_callback(NEXT_BUTTON_EIC_LINE,EXTINT_CALLBACK_TYPE_DETECT);
	
}

void config_extint_channel_burp_box()
{
	struct extint_chan_conf config_extint_chan;
	
	//--Play
	extint_chan_get_config_defaults(&config_extint_chan);
	config_extint_chan.gpio_pin           = PLAY_BUTTON_EIC;
	config_extint_chan.gpio_pin_mux       = PLAY_BUTTON_MUX;
	config_extint_chan.gpio_pin_pull      = EXTINT_PULL_DOWN;
	config_extint_chan.detection_criteria = EXTINT_DETECT_FALLING;
	extint_chan_set_config(PLAY_BUTTON_EIC_LINE, &config_extint_chan);
	/*
	//--Record
	extint_chan_get_config_defaults(&config_extint_chan);
	config_extint_chan.gpio_pin           = RECORD_BUTTON_EIC;
	config_extint_chan.gpio_pin_mux       = RECORD_BUTTON_MUX;
	config_extint_chan.gpio_pin_pull      = EXTINT_PULL_DOWN;
	config_extint_chan.detection_criteria = EXTINT_DETECT_FALLING;
	extint_chan_set_config(RECORD_BUTTON_EIC_LINE, &config_extint_chan);
	*/
	//--Next
	extint_chan_get_config_defaults(&config_extint_chan);
	config_extint_chan.gpio_pin           = NEXT_BUTTON_EIC;
	config_extint_chan.gpio_pin_mux       = NEXT_BUTTON_MUX;
	config_extint_chan.gpio_pin_pull      = EXTINT_PULL_DOWN;
	config_extint_chan.detection_criteria = EXTINT_DETECT_FALLING;
	extint_chan_set_config(NEXT_BUTTON_EIC_LINE, &config_extint_chan);
	
}


void clear_interrupts_flags()
{
	uint8_t* write_clear_interrupts_flags = EXTINT_FLAG_STATUS;
	uint8_t  write_clear_flags = 0xFF;
	*write_clear_interrupts_flags = write_clear_flags;
}

uint8_t  read_interrupt_flag_status()
{
	volatile uint8_t read_status_1 = 0;
	volatile uint8_t* check_interrupt_flag_status = NULL;
	check_interrupt_flag_status =  EXTINT_FLAG_STATUS;
	read_status_1 = *check_interrupt_flag_status;
	//read_status = (read_status & MASK_FLAG_BUTTONS);
	return read_status_1;	
}

void play_pressed_callback()
{
	//check what all interrupt flags are high
	uint8_t read_status = 0;
	delay_cycles_ms(DEBOUNCE_DELAY);
	read_status = read_interrupt_flag_status();
	switch(read_status)
	{
		case PLAY_BUTTON_CLICKED:
			//global variable update
			input_buttons = P_PRESS;
			break;
		case ALL_BUTTONS_CLICKED:
			//global variable update
			input_buttons = N_P_R_PRESS;
			break;
		default:
			input_buttons = NO_BUTTONS_PRESSED;
			break;
	}

	interrupt_occured = true;
	//Clear the interrupt flags
	clear_interrupts_flags();
}

/*
void record_pressed_callback()
{
	//check what all interrupt flags are high
	uint8_t read_status = 0;
	delay_cycles_ms(DEBOUNCE_DELAY);
	read_status = read_interrupt_flag_status();
	
	switch(read_status)
	{
		case RECORD_BUTTON_CLICKED:
			//global variable update
			input_buttons = R_PRESS;
			break;
		case ALL_BUTTONS_CLICKED:
			//global variable update
			input_buttons = N_P_R_PRESS;
			break;
		default:
			input_buttons = NO_BUTTONS_PRESSED;
			break;
	}

	interrupt_occured = true;
	//Clear the interrupt flags
	clear_interrupts_flags();
}
*/
void next_pressed_callback()
{
	//check what all interrupt flags are high
	uint8_t read_status = 0;
	delay_cycles_ms(DEBOUNCE_DELAY);
	read_status = read_interrupt_flag_status();
	
	switch(read_status)
	{
		case NEXT_BUTTON_CLICKED:
			//global variable update
			input_buttons = N_PRESS;
			break;
		case ALL_BUTTONS_CLICKED:
				//global variable update
				input_buttons = N_P_PRESS;
			break;
		default:
			input_buttons = NO_BUTTONS_PRESSED;
			break;
	}

	interrupt_occured = true;
	//Clear the interrupt flags
	clear_interrupts_flags();
}

void config_extint_callbacks_burp_box()
{
	extint_register_callback(play_pressed_callback, PLAY_BUTTON_EIC_LINE, EXTINT_CALLBACK_TYPE_DETECT);
	/*
	extint_register_callback(record_pressed_callback, RECORD_BUTTON_EIC_LINE, EXTINT_CALLBACK_TYPE_DETECT);
	*/
	extint_register_callback(next_pressed_callback, NEXT_BUTTON_EIC_LINE, EXTINT_CALLBACK_TYPE_DETECT);

}

void config_buttons_inputs()
{
	struct port_config config_port_pin;
	port_get_config_defaults(&config_port_pin);
	config_port_pin.direction = PORT_PIN_DIR_INPUT;
	port_pin_set_config(RECORD_BUTTON, &config_port_pin);
	port_pin_set_config(NEXT_BUTTON, &config_port_pin);
	port_pin_set_config(PLAY_BUTTON, &config_port_pin);
}
void init_buttons()
{
	//config_buttons_inputs();
	config_extint_channel_burp_box();
	config_extint_callbacks_burp_box();
	enable_buttons();
}