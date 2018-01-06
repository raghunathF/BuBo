/*
 * prog_test.c
 *
 * Created: 1/5/2018 2:32:03 PM
 *  Author: raghu
 */ 
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

/*
#include <asf.h>
#include "main_control.h"

#define CONF_EVENT_GENERATOR    EVSYS_ID_GEN_EIC_EXTINT_2
#define CONF_EVENT_USER         EVSYS_ID_USER_TC2_EVU

#define SERVO_PIN_EIC  PIN_PA02A_EIC_EXTINT2
#define SERVO_PIN_MUX  PINMUX_PA02A_EIC_EXTINT2
#define SERVO_EIC_LINE 2

struct tc_module               tc_servo_capture;
#define CONF_TC_MODULE TC2

#define VALID_MIN 900
#define VALID_MAX 1100

#define MIN_VALID_RAW_PULSE 280
#define MAX_VALID_RAW_PULSE 1220

#define US_600_COUNTER 300 //8*10^6/16 * 600*10-6 
#define COUNTER_GAP 50
#define TOTAL_DIVISIONS 18

#define UNDEFINED_COMMAND 20
void configure_timer()
{
	struct tc_config config_tc;
	tc_get_config_defaults(&config_tc);
	struct tc_events config_events;
	
	config_tc.enable_capture_on_channel[0] = true;
	config_tc.enable_capture_on_channel[1] = true;
	config_tc.counter_size = TC_COUNTER_SIZE_16BIT; //16
	config_tc.clock_source = GCLK_GENERATOR_0;
	config_tc.clock_prescaler = TC_CLOCK_PRESCALER_DIV16; //16
	//config_tc.count_direction = TC_COUNT_DIRECTION_UP;
	//config_tc.counter_8_bit.period = 0xFF;
	tc_init(&tc_servo_capture, CONF_TC_MODULE, &config_tc);
	tc_enable(&tc_servo_capture);
	
	tc_disable(&tc_servo_capture);
	config_events.generate_event_on_compare_channel[0]  = false;
	config_events.generate_event_on_compare_channel[1]  = false;
	
	config_events.generate_event_on_overflow = false;
	
	config_events.on_event_perform_action = true;
	config_events.invert_event_input = true;
	config_events.event_action = TC_EVENT_ACTION_PPW;
	tc_enable_events(&tc_servo_capture, &config_events);

	tc_enable(&tc_servo_capture);
}


uint8_t find_command(uint32_t calib_input)
{
	uint8_t command=0;
	int i =0;
	uint32_t temp;
	bool command_found = false;
	for(i=0;i<= TOTAL_DIVISIONS;i++)
	{
		temp = US_600_COUNTER + i*COUNTER_GAP;
		if((calib_input > temp-10)&&(calib_input < temp+10))
		{
			command = i;
			command_found = true;
			break;	
		}

	}
	if(command_found == false)
	{
		command = UNDEFINED_COMMAND;
	}
	return command;
}

void event_counter(struct events_resource *resource)
{
	static int  event_count = 0;
	static int  event_count_even = 0;
	static int  event_count_odd = 0;
	volatile static uint32_t timeperiod_capture_filter=0;
	volatile static uint32_t frequency_capture[100];
	volatile static uint32_t ontime_capture[100];
	volatile static uint32_t timeperiod_capture[100];
	static uint32_t timer_calib = 0 ;
	static bool calibration_init = false;
	volatile uint32_t raw_timer_capture = 0;
	volatile static uint32_t raw_timer_capture_even = 0;
	volatile uint32_t raw_timer_capture_odd = 0;
	volatile uint32_t raw_timer_capture_calib = 0;
	
	
	volatile static uint8_t servo_command_present=0;
	static uint8_t servo_command_previous= UNDEFINED_COMMAND;
	static uint8_t servo_command_previous_temp=0;
	static uint16_t count_new_command = 0;
	static bool init_filter = false;
	static bool waiting_update_value = true;

	if(events_is_interrupt_set(resource, EVENTS_INTERRUPT_DETECT))
	{
		//port_pin_toggle_output_level(LED_0_PIN);
		raw_timer_capture = tc_get_capture_value(&tc_servo_capture , TC_COMPARE_CAPTURE_CHANNEL_0 );
		
		if(calibration_init == false)
		{
			if(event_count%2 == 0)
			{
				raw_timer_capture_even = raw_timer_capture;
			}
			else
			{
				raw_timer_capture     = raw_timer_capture + raw_timer_capture_even;	
				if(init_filter == false)
				{
					timeperiod_capture_filter = raw_timer_capture;
					init_filter = true;
				}
				timeperiod_capture_filter = (timeperiod_capture_filter*9 + raw_timer_capture)/10;
				
			 }
			event_count++;
			
			if(event_count == 100)
			{
				event_count = 0;
				timer_calib = ((10000 * 1000)/ timeperiod_capture_filter) ;
				if(((timer_calib > VALID_MIN) & (timer_calib < VALID_MAX)) == true)
				{
					calibration_init = true;
				}
			}
		}
		else
		{
			if((raw_timer_capture > MIN_VALID_RAW_PULSE)&&(raw_timer_capture < MAX_VALID_RAW_PULSE ))
			{
				raw_timer_capture_calib = ((raw_timer_capture * timer_calib)/1000 );
				servo_command_present = find_command(raw_timer_capture_calib);
				if(waiting_update_value)
				{
					if(servo_command_present != servo_command_previous)
					{
						waiting_update_value = false;
						servo_command_previous_temp = servo_command_present;
					}
					
				}	
				else
				{
					if(servo_command_present == servo_command_previous_temp)
					{
						count_new_command++;
					}
					else
					{
						count_new_command = 0;
						waiting_update_value = true;
					}
					if(count_new_command > 5)
					{
						//Update a global here
						count_new_command = 0;
						servo_command_previous = servo_command_present;
						waiting_update_value = true;
					}
				}
			}

			
		}
		
		events_ack_interrupt(resource, EVENTS_INTERRUPT_DETECT);
		delay_cycles_ms(8);
	}
}

static void configure_event_interrupt(struct events_resource *resource,
struct events_hook *hook)
{
	//! [setup_12]
	events_create_hook(hook, event_counter);
	events_add_hook(resource, hook);
	events_enable_interrupt_source(resource, EVENTS_INTERRUPT_DETECT);
	
}

static void configure_event_user(struct events_resource *resource)
{
	//! [setup_5]
	events_attach_user(resource, CONF_EVENT_USER);
	//! [setup_5]
}
static void configure_event_channel(struct events_resource *resource)
{
	
	struct events_config config;

	events_get_config_defaults(&config);

	config.generator      = CONF_EVENT_GENERATOR;
	config.edge_detect    = EVENTS_EDGE_DETECT_BOTH;
	config.path           = EVENTS_PATH_SYNCHRONOUS;
	config.clock_source   = GCLK_GENERATOR_0;
	
	events_allocate(resource, &config);
	
}


void configure_exint(struct extint_chan_conf *resource)
{
	
	struct extint_events    config_events;
	struct extint_chan_conf		config_extint_chan;
	
	extint_chan_get_config_defaults(&config_extint_chan);
	config_extint_chan.gpio_pin           = SERVO_PIN_EIC;
	config_extint_chan.gpio_pin_mux       = SERVO_PIN_MUX;
	config_extint_chan.gpio_pin_pull      = EXTINT_PULL_DOWN;
	config_extint_chan.detection_criteria = EXTINT_DETECT_BOTH;
	
	config_events.generate_event_on_detect[2] = true;
	extint_enable_events(&config_events);
	
	extint_chan_set_config(SERVO_EIC_LINE, &config_extint_chan);
}

int main_1 (void)
{
	struct events_hook     hook;
	struct events_resource		  servo_pulse_event;
	struct extint_chan_conf config_extint_chan;
	
	//system_init();
	//system_interrupt_enable_global();
	
	configure_event_channel(&servo_pulse_event);
	configure_event_user(&servo_pulse_event);
	configure_event_interrupt(&servo_pulse_event, &hook);
	
	
	configure_timer();
	configure_exint(&config_extint_chan);
	//delay_cycles_ms(1000);
	
	while(1)
	{
		main_control_loop_1();
	}
	
	
}
*/