#include "as5048.h"
extern SPI_HandleTypeDef hspi1;

//float  angle_raw;
//	
//float  get_angle() {
//	static uint8_t ft = 0;
//	uint16_t angle_raw_16 = 0;
//	uint8_t Rx[2] = {0};
//	uint8_t Tx[2] = {0};
//	Tx[0]	= 0xff;
//	Tx[1]	= 0x3f;
//	if(!ft) {		
//		HAL_GPIO_WritePin(GPIOA, CS_A4_Pin, GPIO_PIN_RESET);  // CS on				
//		HAL_SPI_TransmitReceive(&hspi1, Tx, Rx, 1, 0x1000);			
//		HAL_GPIO_WritePin(GPIOA, CS_A4_Pin, GPIO_PIN_SET);  // CS off	
//		ft=1;
//	}
//	HAL_GPIO_WritePin(GPIOA, CS_A4_Pin, GPIO_PIN_RESET);  // CS on				
//	HAL_SPI_TransmitReceive(&hspi1, Tx, Rx, 1, 0x1000);
//	HAL_GPIO_WritePin(GPIOA, CS_A4_Pin, GPIO_PIN_SET);  // CS off	
//			
//	angle_raw_16 = ( (Rx[1] << 8 ) | Rx[0] ) & 0x3FFF;
//	angle_raw = (float)(angle_raw_16)*0.021973997;
//	return 	angle_raw;
//}	

uint16_t angle_raw_16 = 0;
uint16_t  get_angle_raw(void) {
	static uint8_t pr;
	//uint16_t angle_raw_16 = 0;
	uint8_t Rx[2] = {0};
	uint8_t Tx[2] = {0};
	Tx[0]	= 0xff;
	Tx[1]	= 0x3f;
	if(pr != 1) {		
		HAL_GPIO_WritePin(GPIOA, CS_A4_Pin, GPIO_PIN_RESET);  // CS on				
		HAL_SPI_TransmitReceive(&hspi1, Tx, Rx, 1, 10000);			
		HAL_GPIO_WritePin(GPIOA, CS_A4_Pin, GPIO_PIN_SET);  // CS off	
		pr=1;
	}
	HAL_GPIO_WritePin(GPIOA, CS_A4_Pin, GPIO_PIN_RESET);  // CS on				
	HAL_SPI_TransmitReceive(&hspi1, Tx, Rx, 1, 10000);
	HAL_GPIO_WritePin(GPIOA, CS_A4_Pin, GPIO_PIN_SET);  // CS off	
			
	angle_raw_16 = ( (Rx[1] << 8 ) | Rx[0] ) & 0x3FFF;
	//angle_raw = (float)(angle_raw_16)*0.021973997;
	return 	angle_raw_16;
}	
