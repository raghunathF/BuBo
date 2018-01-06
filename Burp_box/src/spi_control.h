/*
 * spi_control.h
 *
 * Created: 11/6/2017 11:29:08 AM
 *  Author: raghu
 */ 

#include <asf.h>

//void init_burp_box();
	
#define TRACK_NO_1						1
#define TRACK_NO_2						2
#define TRACK_NO_3						3

#define RECORD_OPERATION				1
#define PLAY_OPERATION					2
#define ERASE_OPERATION					3

#define RECORD_READY_MASK						0x08
#define PLAY_READY_MASK							0x04
#define ERASE_READY_MASK						0x02
#define SPI_READY_MASK							0x01


#define BUFFER_RESET_LENGTH				2
#define BUFFER_POWER_LENGTH				2
#define BUFFER_CLEAR_INIT_LENGTH		2
#define BUFFER_INPUT_LENGTH				2

#define SPI_RESET		{0x03,0x00}
#define SPI_CLEAR_INIT	{0x04,0x00}
#define SPI_POWER_ON    {0x01,0x00}
#define SPI_INPUT       {0x01,0x00}


#define BUF_LENGTH 2
#define BUF_LENGTH_4 4
#define BUF_LENGTH_6 6
#define BUF_LENGTH_3 3
#define SLAVE_SELECT_PIN CONF_MASTER_SS_PIN
//Track --1
#define START_ADD_1_L		0x10
#define START_ADD_1_H		0x00
#define END_ADD_1_L			0x37
#define END_ADD_1_H			0x00

//Track -2
#define START_ADD_2_L		0x38
#define START_ADD_2_H		0x00
#define END_ADD_2_L			0x5F
#define END_ADD_2_H			0x00

//Track --3
#define START_ADD_3_L		0x60
#define START_ADD_3_H		0x00
#define END_ADD_3_L			0x87
#define END_ADD_3_H			0x00

//LED Flasing -- Global Erase
#define LOOP_2 3
#define LOOP_1_START 200
#define LOOP_1_END   800

static uint8_t rd_buffer[BUF_LENGTH];
static uint8_t rd_buffer_4[BUF_LENGTH_4];
static uint8_t rd_buffer_6[BUF_LENGTH_6];
static uint8_t rd_buffer_3[BUF_LENGTH_3];


//Servo Pulses
#define FUTURE_USE 0x0000
//Play
#define TRACK_1_VOLUME_1 0x0100
#define TRACK_1_VOLUME_2 0x0200
#define TRACK_1_VOLUME_3 0x0300
#define TRACK_2_VOLUME_1 0x0400
#define TRACK_2_VOLUME_2 0x0500
#define TRACK_2_VOLUME_3 0x0600
#define TRACK_3_VOLUME_1 0x0700
#define TRACK_3_VOLUME_2 0x0800
#define TRACK_3_VOLUME_3 0x0900
//Record
#define TRACK_1_RECORD_MIC   0x0A00
#define TRACK_1_RECORD_ANAIN 0x0B00
#define TRACK_2_RECORD_MIC   0x0C00
#define TRACK_2_RECORD_ANAIN 0x0D00
#define TRACK_3_RECORD_MIC   0x0E00
#define TRACK_3_RECORD_ANAIN 0x0F00
//FeedThrough
#define FT_MIC   0x1000
#define FT_ANAIN 0x1100
//Help 
#define REPEAT_HELP 0x1200
#define UNDEFINED 0x1400

#define TRACK_1 1
#define TRACK_2 2
#define TRACK_3 3


//Initialization
static uint8_t wr_buffer_reset[BUF_LENGTH]     =  {	0x03,0x00 };
static uint8_t wr_buffer_clr_init[BUF_LENGTH]  = { 0x04,0x00 };
static uint8_t wr_buffer_power_on[BUF_LENGTH]  ={ 0x01,0x00 };
static uint8_t wr_buffer_check_mem[BUF_LENGTH] = { 0x49,0x00 };
static uint8_t wr_buffer_gerase[BUF_LENGTH]    =    { 0x43,0x00 };

//STOP
static uint8_t wr_buffer_stop[BUF_LENGTH]         = { 0x02,0x00 };

//Record
static uint8_t wr_buffer_record[BUF_LENGTH]       = { 0x41,0x00 };
	
//Record-set
static uint8_t wr_buffer_record_set_1[BUF_LENGTH_6] = { 0x81,0x00,START_ADD_1_L,START_ADD_1_H,END_ADD_1_L,END_ADD_1_H };
static uint8_t wr_buffer_record_set_2[BUF_LENGTH_6] = { 0x81,0x00,START_ADD_2_L,START_ADD_2_H,END_ADD_2_L,END_ADD_2_H  };
static uint8_t wr_buffer_record_set_3[BUF_LENGTH_6] = { 0x81,0x00,START_ADD_3_L,START_ADD_3_H,END_ADD_3_L,END_ADD_3_H  };

//Play
static uint8_t wr_buffer_play[BUF_LENGTH]         = { 0x40,0x00 };
//Play-set
static uint8_t wr_buffer_play_set_1[BUF_LENGTH_6]   = { 0x80,0x00,START_ADD_1_L,START_ADD_1_H,END_ADD_1_L,END_ADD_1_H };
static uint8_t wr_buffer_play_set_2[BUF_LENGTH_6]   = { 0x80,0x00,START_ADD_2_L,START_ADD_2_H,END_ADD_2_L,END_ADD_2_H };
static uint8_t wr_buffer_play_set_3[BUF_LENGTH_6]   = { 0x80,0x00,START_ADD_3_L,START_ADD_3_H,END_ADD_3_L,END_ADD_3_H };

//Erase
static uint8_t wr_buffer_erase[BUF_LENGTH]           = { 0x42,0x00 };
//Erase-set
static uint8_t wr_buffer_erase_set_1[BUF_LENGTH_6]   = { 0x82,0x00,START_ADD_1_L,START_ADD_1_H,END_ADD_1_L,END_ADD_1_H };
static uint8_t wr_buffer_erase_set_2[BUF_LENGTH_6]   = { 0x82,0x00,START_ADD_2_L,START_ADD_2_H,END_ADD_2_L,END_ADD_2_H };
static uint8_t wr_buffer_erase_set_3[BUF_LENGTH_6]   = { 0x82,0x00,START_ADD_3_L,START_ADD_3_H,END_ADD_3_L,END_ADD_3_H };
//Global Erase
static uint8_t wr_buffer_global_erase[BUF_LENGTH]    = { 0x43,0x00 };




//APC --write
static uint8_t wr_apc_2_ideal[BUF_LENGTH_3] = { 0x65,0x40,0x04 };
static uint8_t wr_apc_2_play_memory[BUF_LENGTH_3] = { 0x65,0x40,0x04 };
static uint8_t wr_apc_2_play_mic[BUF_LENGTH_3] = { 0x65,0x40,0x04 };
static uint8_t wr_apc_2_play_analogIn[BUF_LENGTH_3] = { 0x65,0x40,0x04 };
static uint8_t wr_apc_2_record_mic[BUF_LENGTH_3] = {0x65,0x40,0x04};
static uint8_t wr_apc_2_record_analogIn[BUF_LENGTH_3] = {0x65,0x07,0x04};
static uint8_t wr_apc_2_speaker_analogIn[BUF_LENGTH_3] = {0x65,0x00,0x04};
static uint8_t wr_apc_2_speaker_mic_analogIn[BUF_LENGTH_3] = {0x65,0x13,0x04};


//APC--Change Volume 
static uint8_t wr_apc_2_volume_5[BUF_LENGTH_3] = { 0x65,0x40,0x04 };
static uint8_t wr_apc_2_volume_4[BUF_LENGTH_3] = { 0x65,0x43,0x04 };
static uint8_t wr_apc_2_volume_3[BUF_LENGTH_3] = { 0x65,0x45,0x04 };
static uint8_t wr_apc_2_volume_2[BUF_LENGTH_3] = { 0x65,0x46,0x04 };
static uint8_t wr_apc_2_volume_1[BUF_LENGTH_3] = { 0x65,0x47,0x04 };
//Read APC
static uint8_t rd_apc[BUF_LENGTH_4]               = {0x44,0x00,0x00,0x00};
//Read Playback pointer
static uint8_t wr_buffer_play_pointer[BUF_LENGTH_4] ={0x06,0x00,0x00,0x00};
//Read Record Pointer
static uint8_t wr_buffer_rec_pointer[BUF_LENGTH_4] ={ 0x08,0x00,0x00,0x00 };
//Read Device ID
static uint8_t wr_buffer_dev_id[BUF_LENGTH_3] ={ 0x09,0x00,0x00 };
//Read Status Pointer
static uint8_t wr_buffer_status_pointer[BUF_LENGTH_3] = {0x05,0x00,0x00};
	
//Control States
enum control_states{ IDEAL_STATE = 0x1400, NEXT_BUTTON_PRESSED=1, RECORD_BUTTON_PRESSED=2, PLAY_BUTTON_PRESSED=3,N_P_PRESSED = 4,ALL_BUTTONS_PRESSED = 7}; 


extern volatile uint8_t track_pointer; 
extern volatile bool interrupt_occured;


void burp_box_erase(uint8_t track_no);
void burp_box_record(uint8_t track_no);
void burp_box_play(uint8_t track_no);
void spi_write_stop();
void spi_write_apc(uint8_t* write_apc);
void init_burp_box();
void spi_main_loop_1(uint16_t input_buttons_servo);