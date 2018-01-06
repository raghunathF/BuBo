/*
 * PWM_capture.h
 *
 * Created: 12/26/2017 5:22:29 PM
 *  Author: raghu
 */ 


#ifndef PWM_CAPTURE_H_
#define PWM_CAPTURE_H_

void init_servo_capture();
uint16_t get_servo_command();

#define CONF_EVENT_GENERATOR    EVSYS_ID_GEN_EIC_EXTINT_2
#define CONF_EVENT_USER         EVSYS_ID_USER_TC2_EVU

#define SERVO_PIN_EIC  PIN_PA02A_EIC_EXTINT2
#define SERVO_PIN_MUX  PINMUX_PA02A_EIC_EXTINT2
#define SERVO_EIC_LINE 2

#define SERVO_TC_2 TC2

#define VALID_MIN 900
#define VALID_MAX 1100

#define MIN_VALID_RAW_PULSE 280
#define MAX_VALID_RAW_PULSE 1220

#define US_600_COUNTER 300 //8*10^6/16 * 600*10-6
#define COUNTER_GAP 50
#define TOTAL_DIVISIONS 18

#define UNDEFINED_COMMAND 20

#endif /* PWM_CAPTURE_H_ */