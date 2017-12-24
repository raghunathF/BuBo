/*
 * spi_master.h
 *
 * Created: 11/2/2017 11:37:54 AM
 *  Author: raghu
 */ 

struct spi_module spi_master_instance;
struct spi_slave_inst slave;


void speaker_test();
void configure_spi(void);
void spi_transceive (uint8_t* wr_buffer , uint8_t* rd_buffer ,uint8_t buff_length);

#define SPI_MODULE              SERCOM1
#define SPI_SERCOM_MUX_SETTING  SPI_SIGNAL_MUX_SETTING_D
