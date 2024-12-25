/*
 * hpl_app.h
 *
 *  Created on: Jul 24, 2024
 *      Author: Sushant Thakur
 */

#ifndef APPLICATION_USER_STM32_WPAN_APP_HPL_APP_H_
#define APPLICATION_USER_STM32_WPAN_APP_HPL_APP_H_



/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
//#include "main.h"
//#include "app_common.h"
//#include "log_module.h"
//#include "ble.h"
//#include "app_ble.h"
//#include "host_stack_if.h"
//#include "ll_sys_if.h"
//#include "stm32_rtos.h"
//#include "otp.h"
//#include "stm32_timer.h"
//#include "stm_list.h"
//#include "advanced_memory_manager.h"
//#include "blestack.h"
//#include "nvm.h"
//#include "simple_nvm_arbiter.h"
//#include "p2p_server.h"
//#include "p2p_server_app.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#if 0
typedef struct {
	uint8_t  Receive_Serial_Number_Request_Header;
	uint16_t Receive_Serial_Number_Request_PayLoadLength;
	uint8_t  Receive_Serial_Number_Request_Action_Type;
	uint8_t  Receive_Serial_Number_Request_Command;
	uint8_t *Receive_Serial_Number_Request_PayLoad;
	uint16_t Receive_Serial_Number_Request_CRC;
	uint8_t  Send_Serila_Number_Request_Footer;
}Send_Serial_Number_Request_t;


/* USER CODE END PTD */


void Hpl_Send_Serial_Number_Request(Send_Serial_Number_Request_t *PayLoad, uint8_t PayLoadLength);

#endif

void Hpl_Send_Serial_Number_Request(uint8_t *PayLoad, uint8_t PayLoadLength);




#endif /* APPLICATION_USER_STM32_WPAN_APP_HPL_APP_H_ */
