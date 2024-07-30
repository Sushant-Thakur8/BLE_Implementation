/*
 * hpl_app.c
 *
 *  Created on: Jul 24, 2024
 *      Author: Sushant Thakur
 */


#include "HPL_App.h"
#include "log_module.h"

/* Global variables ----------------------------------------------------------*/
/* USER CODE BEGIN GV */
volatile bool isMeterSerialNumberReceived = false; // Tells whether the serial number is received
volatile uint8_t Send_Serial_Number_Request_Packet[11] = {0xAB, 0x00, 0x09, 0x01, 0x0A, 0xFF, 0xFF, 0xFF, 0x01, 0x14, 0xBA};
static uint8_t Locally_Stored_Serial_Number[9] = {0x09,'H','P','L','-','N','O','S','M'};
 uint8_t Meter_Serial_Number_Received[9];
 uint8_t instWBMBuffer[26] = {0x7E, 0xB0, 0x14, 0xDB, 0x7E, 0x12, 0x00, 0x6B, 0x0D, 0x1B, 0xD8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		 	 	 	 	 	  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x33, 0xF8, 0x7E};
/* USER CODE END GV */





#if 0
void Hpl_Receive_Serial_Number_Request(Send_Serial_Number_Request_t *PayLoad, uint8_t PayLoadLength)
{
	Send_Serial_Number_Request_t *HPL_PayLoad = (Send_Serial_Number_Request_t *)PayLoad;

	HPL_PayLoad->Send_Serial_Number_Request_Header = PayLoad[i]
}
#endif


void Hpl_Send_Serial_Number_Request(uint8_t *PayLoad, uint8_t PayLoadLength)
{
	/* <<< Comment by @Sushant on //24-07-2024 >>>
	 * This API will send the data over UART to Meter
	 * This API will call the UART function to send the data, There will be a callback for the data once transmitted
	 * This callback for transmit will return the number of bytes transmitted
	 * Now we have to use a software timer, this timer will wait for the data to be received , the data reception will be interrupt based
	 * so for the interrupt to be raised there will be a timer which will wait for a certain period and if it do not receive anything it will
	 * display a hardcoded name for the BLE device "HPL-NOSM".
	 * In both the cases the flag will be set to isMeterSerialNumberReceived to true .
	 */
	LOG_INFO_APP("Inside the serial Number Request \r \n");
	for(int i = 0 ; i < PayLoadLength ; i ++ ) {
		LOG_INFO_APP("%02x:",PayLoad[i]);
	}
	LOG_INFO_APP("\n \r");
	memset(Meter_Serial_Number_Received, 0, sizeof(Meter_Serial_Number_Received)/sizeof(uint8_t));

	memcpy(Meter_Serial_Number_Received, Locally_Stored_Serial_Number, 9);

	isMeterSerialNumberReceived = true;

}
