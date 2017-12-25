/*
 * bsp.c
 *
 * Created: 11/3/2017 2:49:54 PM
 *  Author: raghu
 */ 
#include <asf.h>
#include "bsp.h"
#include "pinout.h"
#include "delay.h"

static uint8_t track_led_mode = 0;
static uint8_t counter_timer = 0;
/*
void config_track_led()
{
	
	struct tcc_config config_tcc;
	tcc_get_config_defaults(&config_tcc, TCC0);
	config_tcc.counter.clock_prescaler = TCC_CLOCK_PRESCALER_DIV2;
	config_tcc.counter.period = 0xFF;
	config_tcc.compare.wave_generation = TCC_WAVE_GENERATION_SINGLE_SLOPE_PWM;
	config_tcc.compare.wave_polarity[TRACK_LED_TCC_CHANNEL]  = TCC_WAVE_POLARITY_0;
	config_tcc.compare.match[TRACK_LED_TCC_CHANNEL]			 = 0;
	config_tcc.pins.enable_wave_out_pin[TRACK_LED_TCC_CHANNEL] = true;
	config_tcc.pins.wave_out_pin[TRACK_LED_TCC_WO]        = PIN_PA05F_TCC0_WO1;
	config_tcc.pins.wave_out_pin_mux[TRACK_LED_TCC_WO]    = PINMUX_PA05F_TCC0_WO1;
	
	tcc_init(&tcc_instance0, TCC0, &config_tcc);
	tcc_enable(&tcc_instance0);
	
}
*/
void init_track_led_timer()
{
	struct tc_config config_tc;
	tc_get_config_defaults(&config_tc);
	config_tc.counter_size = TC_COUNTER_SIZE_8BIT; //8
	config_tc.clock_source = GCLK_GENERATOR_0;
	config_tc.clock_prescaler = TC_CLOCK_PRESCALER_DIV1024; //64
	config_tc.count_direction = TC_COUNT_DIRECTION_UP;
	config_tc.counter_8_bit.period = 0xFF;
	tc_init(&tc_instance1, TC1, &config_tc);
	tc_enable(&tc_instance1);
}

//Track LED control
void tc_callback_track_led_control()
{
	
	if(counter_timer == TIMER_MULTIPLIER_10)
	{
		counter_timer = 0;
	}
	
	switch (track_led_mode)
	 {
		case 0  :
				if((counter_timer == TIMER_MULTIPLIER_0) || (counter_timer == TIMER_MULTIPLIER_1))
				{
					port_pin_toggle_output_level(TRACK_LED);
				}
				break;
		case 1  :
				if((counter_timer == TIMER_MULTIPLIER_0) || (counter_timer == TIMER_MULTIPLIER_1)||(counter_timer == TIMER_MULTIPLIER_2) || (counter_timer == TIMER_MULTIPLIER_3))
				{
					port_pin_toggle_output_level(TRACK_LED);
				} 
				break;
		case 2  :
				if((counter_timer == TIMER_MULTIPLIER_0) || (counter_timer == TIMER_MULTIPLIER_1)||(counter_timer == TIMER_MULTIPLIER_2) || (counter_timer == TIMER_MULTIPLIER_3) ||(counter_timer == TIMER_MULTIPLIER_4) || (counter_timer == TIMER_MULTIPLIER_5))
				{
					port_pin_toggle_output_level(TRACK_LED);
				}
				break;
		default :
				if((counter_timer == TIMER_MULTIPLIER_0) || (counter_timer == TIMER_MULTIPLIER_1))
				{
					port_pin_toggle_output_level(TRACK_LED);
				}
				break;
	 }
	counter_timer++;
	
	
}



//Callbacks
void config_callbacks_tc1()
{
	tc_register_callback(&tc_instance1, tc_callback_track_led_control ,TC_CALLBACK_OVERFLOW);
	tc_enable_callback(&tc_instance1, TC_CALLBACK_OVERFLOW);
}


//Initialize all the buttons and LEDS
void init_led_buttons()
{
	//LED_init
	struct port_config config_port_pin;
	port_get_config_defaults(&config_port_pin);
	config_port_pin.direction  = PORT_PIN_DIR_OUTPUT;
	//Record LED init
	port_pin_set_config(RECORD_LED, &config_port_pin);
	//Play LED init
	port_pin_set_config(PLAY_LED, &config_port_pin);
	//Track LED init
	port_pin_set_config(TRACK_LED, &config_port_pin);
	
	//Clear Play ,record and Track LED for the initial state
	port_pin_set_output_level(RECORD_LED,false);
	port_pin_set_output_level(PLAY_LED,false);
	port_pin_set_output_level(TRACK_LED,false);
	
	
	
	//Switches_init
	port_get_config_defaults(&config_port_pin);
	config_port_pin.input_pull = PORT_PIN_PULL_DOWN;
	config_port_pin.direction  = PORT_PIN_DIR_INPUT;
	
	//Record button init
	port_pin_set_config(RECORD_BUTTON, &config_port_pin);
	/*
	//Play button init
	port_pin_set_config(PLAY_BUTTON, &config_port_pin);
	//Next button init
	port_pin_set_config(NEXT_BUTTON, &config_port_pin);
	*/
	
	init_track_led_timer();
	config_callbacks_tc1();
	
	
}
//Switch on LED
void LED_on(uint8_t LED_pin_no)
{
	//LED on 
	port_pin_set_output_level(LED_pin_no,true);
}

//Switch off the LED
void LED_off(uint8_t LED_pin_no)
{
	//LED off
	port_pin_set_output_level(LED_pin_no,false);
}


//Toggle the LED
void LED_toggle(uint8_t LED_pin_no)
{
	//LED toggle
	port_pin_toggle_output_level(LED_pin_no);
}

//Track LED 
void LED_track(uint8_t track_no)
{
	//Lock the resource 
	track_led_mode = track_no; // Should make this atomic , never seen these problems , slow operation so should not be a problem
	counter_timer = 0;
	port_pin_set_output_level(TRACK_LED,false);
	delay_cycles_ms(100);
	
	//Unlock the resource
	
}

uint8_t check_input_buttons(void)
{
	enum buttons_state buttons_pressed ;
	volatile uint32_t in_reg = 0;
	buttons_pressed = NO_BUTTONS_PRESSED;
	//Software debounce
	PortGroup *const port_base = port_get_group_from_gpio_pin(RECORD_LED);
	
	in_reg = port_base->IN.reg & MASK_BUTTONS;
	if( in_reg == NO_BUTTONS_PRESSED)
	{
		return buttons_pressed;
	}
	else
	{
		//check if the button still pressed
		delay_cycles_ms(125);
		in_reg = port_base->IN.reg & MASK_BUTTONS;
		if( in_reg == NO_BUTTONS_PRESSED)
		{
			return buttons_pressed;
		}
		else
		{
			switch(in_reg)
			{
				case RECORD_PRESSED:
					buttons_pressed = R_PRESS;
					in_reg  = 0;
					break;
				default:
					break;
			}
			in_reg = port_base->IN.reg & MASK_BUTTONS;
			return buttons_pressed;
		}
		
		
	}
}


/*
uint8_t check_input_buttons(void)
{
	enum buttons_state buttons_pressed ;
	volatile uint32_t in_reg = 0;
	
	//Software debounce
	PortGroup *const port_base = port_get_group_from_gpio_pin(RECORD_LED);

	 in_reg = port_base->IN.reg & MASK_BUTTONS;
	 if( in_reg == NO_BUTTONS_PRESSED)
	 {
		 return buttons_pressed;
	 }
	 else
	 {
		 //check if the button still pressed 
		 delay_cycles_ms(125);
		 in_reg = port_base->IN.reg & MASK_BUTTONS;
		 if( in_reg == NO_BUTTONS_PRESSED)
		 {
			 return buttons_pressed;
		 }
		 else
		 {
			 switch(in_reg)
			 {
				 case NEXT_PRESSED:
								buttons_pressed = N_PRESS;
								in_reg  = 0;
								break;
				 case PLAY_PRESSED:
								buttons_pressed = P_PRESS;
								in_reg  = 0;
								break;
				 case RECORD_PRESSED:
								buttons_pressed = R_PRESS;
								in_reg  = 0;
								break;
				 case NEXT_PLAY_PRESSED:
								buttons_pressed = N_P_PRESS;
								in_reg  = 0;
								break;
				 case NEXT_RECORD_PRESSED:
								buttons_pressed = N_R_PRESS;
								in_reg  = 0;
								break;
				 case PLAY_RECORD_PRESSED:
								buttons_pressed = R_P_PRESS;
								in_reg  = 0;
								break;
				 case ALL_PRESSED:
								buttons_pressed = N_P_R_PRESS;
								in_reg  = 0;
								break;
				 default:
								break;
			 }
			 in_reg = port_base->IN.reg & MASK_BUTTONS;
			 return buttons_pressed;
		 }
		 
			
	 }
}

*/