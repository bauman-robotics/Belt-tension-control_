/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "cobs.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef union float_u
{
	float var;
	uint8_t var_ar[4];
} float_u;


/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t uart_send = 0;
double angle_f = 0.0f;

extern int32_t step_count;
uint8_t COBS_Buf[5] = {0};
uint8_t UART_TxBuf[15] = {0};
uint8_t UART_RxBuf[15] = {0};
float_u pack;
uint8_t flag_steps_present = 0;
float start_pozition = 0.0f;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM6_Init();
  MX_UART4_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	HAL_TIM_Base_Start_IT(&htim6);
	size_t send_num;
	

	//HAL_Delay(2000);
	uint8_t cont = 1;
	char ch = 0xFF;
	float_u start_pos;
	float start_position_f = 0.0f;
	uint32_t zero_count = 0;
	while(cont)
	{
			HAL_UART_Receive(&huart4, &ch, 1, 100);
			if(ch == 0) zero_count ++;
			if (zero_count > 200)
			{
					HAL_UART_Receive(&huart4, &UART_RxBuf, 6, 100);
					uint8_t temp[10];
					cobs_decode(UART_RxBuf, 6, temp);
				
				  //memcpy(&start_pozition, temp, sizeof(float));
					memcpy(&start_pozition, temp, 4);
					//start_pos.var_ar[0] = temp[0];
					//start_pos.var_ar[1] = temp[1];
					//start_pos.var_ar[2] = temp[2];
					//start_pos.var_ar[3] = temp[3];
					//start_position_f = start_pos.var;
				//if ((start_pozition >= -180) && (start_pozition <=180))
					cont = 0;
			}
	}
	
	
  while (1)
  { 
		if (HAL_GPIO_ReadPin(GPIOC, Pwr_on_Pin)) HAL_GPIO_WritePin(GPIOD, Red_led_Pin,1);
		else HAL_GPIO_WritePin(GPIOD, Red_led_Pin,0);

		//if ((uart_send == 1) && (HAL_GPIO_ReadPin(GPIOC, Pwr_on_Pin)))
		if (uart_send == 1)
		{
			HAL_GPIO_TogglePin(GPIOD, Orange_led_Pin);  // Orange_led 
			uart_send = 0;
			angle_f = (360.0f*step_count)/STEP_PER_REV;
			pack.var = angle_f;
			pack.var = start_pozition - angle_f ;
			COBS_Buf[0] = 'p';
			COBS_Buf[1] = pack.var_ar[0];
			COBS_Buf[2] = pack.var_ar[1];
			COBS_Buf[3] = pack.var_ar[2];
			COBS_Buf[4] = pack.var_ar[3];
			send_num = cobs_encode(COBS_Buf, 5, UART_TxBuf);
			UART_TxBuf[send_num] = 0;
			HAL_UART_Transmit(&huart4, UART_TxBuf, send_num + 1, 100);			
		}
		
		
		
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

