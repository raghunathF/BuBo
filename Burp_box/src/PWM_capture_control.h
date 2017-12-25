/*
 * PWM_capture_control.h
 *
 * Created: 12/25/2017 5:54:48 PM
 *  Author: raghu
 */ 


#ifndef PWM_CAPTURE_CONTROL_H_
#define PWM_CAPTURE_CONTROL_H_

#include <asf.h>

#define VOLUME_1		1
#define VOLUME_2		2
#define VOLUME_3		3
#define VOLUME_4		4
#define VOLUME_5		5

void burp_box_set_volume_track(uint8_t volume,uint8_t track_no);



#endif /* PWM_CAPTURE_CONTROL_H_ */