/*
 * IncFile1.h
 *
 * Created: 12/22/2017 10:30:21 AM
 *  Author: raghu
 */ 


#ifndef BUTTONS_H_
#define BUTTONS_H_

//--Play
#define PLAY_BUTTON_EIC           PIN_PA04A_EIC_EXTINT4
#define PLAY_BUTTON_MUX           PINMUX_PA04A_EIC_EXTINT4
#define PLAY_BUTTON_EIC_LINE      4

/*
//--Record
#define RECORD_BUTTON_EIC           PIN_PA14A_EIC_EXTINT11
#define RECORD_BUTTON_MUX           PINMUX_PA14A_EIC_EXTINT11
#define RECORD_BUTTON_EIC_LINE      
*/

//-Next
#define NEXT_BUTTON_EIC           PIN_PA15A_EIC_EXTINT1
#define NEXT_BUTTON_MUX           PINMUX_PA15A_EIC_EXTINT1
#define NEXT_BUTTON_EIC_LINE      1

#define PLAY_BUTTON_CLICKED       0x10
//#define RECORD_BUTTON_CLICKED     0x20	
#define NEXT_BUTTON_CLICKED       0x02
#define ALL_BUTTONS_CLICKED       0x12

extern volatile uint8_t input_buttons;
extern volatile bool interrupt_occured;

void init_buttons();
#endif /* INCFILE1_H_ */