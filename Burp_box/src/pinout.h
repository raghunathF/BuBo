/*
 * pinout.h
 *
 * Created: 11/2/2017 12:42:35 PM
 *  Author: raghu
 */ 
#include <asf.h>

#ifndef PINOUT_H_
#define PINOUT_H_


//SPI

#define SPI_MOSI_PIN            PINMUX_PA30C_SERCOM1_PAD0
#define SPI_SCK_PIN				PINMUX_PA31C_SERCOM1_PAD1
#define SPI_SS_PIN				PIN_PA24
#define SPI_MISO_PIN			PINMUX_PA25C_SERCOM1_PAD3


//Inputs
//Buttons
#define NEXT_BUTTON				PIN_PA15
#define PLAY_BUTTON				PIN_PA04
#define RECORD_BUTTON			PIN_PA14

//Servo pulse
#define SERVO_PULSE				PIN_PA02

//Output
#define RECORD_LED				PIN_PA05 
#define PLAY_LED				PIN_PA08 
#define TRACK_LED				PIN_PA09 


#endif /* PINOUT_H_ */