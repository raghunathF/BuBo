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



static uint8_t rd_buffer[BUF_LENGTH];
static uint8_t rd_buffer_4[BUF_LENGTH_4];
static uint8_t rd_buffer_6[BUF_LENGTH_6];
static uint8_t rd_buffer_3[BUF_LENGTH_3];

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
static uint8_t wr_buffer_record_set_1[BUF_LENGTH_6] = { 0x81,0x00,0x15,0x00,0xE0,0x00 };
static uint8_t wr_buffer_record_set_2[BUF_LENGTH_6] = { 0x81,0x00,0x15,0x00,0xE0,0x00 };
static uint8_t wr_buffer_record_set_3[BUF_LENGTH_6] = { 0x81,0x00,0x15,0x00,0xE0,0x00 };

//Play
static uint8_t wr_buffer_play[BUF_LENGTH]         = { 0x40,0x00 };
//Play-set
static uint8_t wr_buffer_play_set_1[BUF_LENGTH_6]   = { 0x80,0x00,0x15,0x00,0xE0,0x00 };
static uint8_t wr_buffer_play_set_2[BUF_LENGTH_6]   = { 0x80,0x00,0x15,0x00,0xE0,0x00 };
static uint8_t wr_buffer_play_set_3[BUF_LENGTH_6]   = { 0x80,0x00,0x15,0x00,0xE0,0x00 };

//APC --write
static uint8_t wr_apc_2_ideal[BUF_LENGTH_3] = { 0x65,0x40,0x04 };
static uint8_t wr_apc_2_play_memory[BUF_LENGTH_3] = { 0x65,0x40,0x04 };
static uint8_t wr_apc_2_play_mic[BUF_LENGTH_3] = { 0x65,0x40,0x04 };
static uint8_t wr_apc_2_play_analogIn[BUF_LENGTH_3] = { 0x65,0x40,0x04 };
static uint8_t wr_apc_2_record_mic[BUF_LENGTH_3] = {0x65,0x41,0x04};
static uint8_t wr_apc_2_record_analogIn[BUF_LENGTH_3] = {0x65,0x01,0x04};


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
enum control_states{ IDEAL_STATE = 0, NEXT_BUTTON_PRESSED=1, RECORD_BUTTON_PRESSED=2, PLAY_BUTTON_PRESSED=3}; 


extern volatile uint8_t track_pointer; 
extern volatile bool interrupt_occured;


void init_burp_box();
void spi_main_loop_1(uint16_t input_buttons_servo);
