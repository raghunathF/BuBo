/*
 * bsp.h
 *
 * Created: 11/3/2017 2:49:35 PM
 *  Author: raghu
 */ 


#ifndef BSP_H_
#define BSP_H_

void init_led_buttons();
void LED_track(uint8_t track_no);
void LED_on(uint8_t LED_pin_no);
void LED_off(uint8_t LED_pin_no);
void LED_toggle(uint8_t LED_pin_no);
uint8_t check_input_buttons(void);


struct tc_module tc_instance1;
#define TRACK_LED_TCC_CHANNEL 1
#define TRACK_LED_TCC_WO 1

#define MASK_BUTTONS	0x0000C010

#define NEXT_PRESSED	0x00008000
#define RECORD_PRESSED	0x00004000
#define PLAY_PRESSED    0x00000010

#define NEXT_PLAY_PRESSED      0x00008010
#define NEXT_RECORD_PRESSED	   0x0000C000
#define PLAY_RECORD_PRESSED    0x00004010
#define ALL_PRESSED		       0x0000C010

#define TIMER_MULTIPLIER       7

#define TIMER_MULTIPLIER_0     TIMER_MULTIPLIER*0
#define TIMER_MULTIPLIER_1	   TIMER_MULTIPLIER*1
#define TIMER_MULTIPLIER_2     TIMER_MULTIPLIER*2
#define TIMER_MULTIPLIER_3	   TIMER_MULTIPLIER*3
#define TIMER_MULTIPLIER_4     TIMER_MULTIPLIER*4
#define TIMER_MULTIPLIER_5     TIMER_MULTIPLIER*5
#define TIMER_MULTIPLIER_6     TIMER_MULTIPLIER*6
#define TIMER_MULTIPLIER_7     TIMER_MULTIPLIER*7
#define TIMER_MULTIPLIER_8     TIMER_MULTIPLIER*8
#define TIMER_MULTIPLIER_9     TIMER_MULTIPLIER*9
#define TIMER_MULTIPLIER_10    TIMER_MULTIPLIER*10

enum buttons_state{ NO_BUTTONS_PRESSED=0, N_PRESS=1, R_PRESS=2,P_PRESS=3 , N_R_PRESS=4,N_P_PRESS=5,R_P_PRESS=6,N_P_R_PRESS =7 }; 

#endif /* BSP_H_ */