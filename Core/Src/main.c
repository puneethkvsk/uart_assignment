/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "string.h"

#include "flash_sector_h7.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define MAX_RECEVE_DATA_SIZE 10
#define BUFFER_SIZE			 2048
#define STRING_BUFFER_SIZE   1024
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart2_rx;

/* USER CODE BEGIN PV */
uint64_t flash_begin_address = 0x08060000;

uint8_t received_data[BUFFER_SIZE];
uint32_t buffer[STRING_BUFFER_SIZE];
uint8_t tx_data[STRING_BUFFER_SIZE];

uint16_t total_number_of_words = 0;
uint8_t local_count = 0;
volatile uint8_t data_reception_complete = 0;
uint8_t data_copying_complete = 0;
uint32_t receive_buffer_index = 0;
uint32_t main_buffer_index = 0;
uint32_t previous_received_data_size = 0;
uint32_t temp = 0;
uint32_t received_data_length = 0;
volatile uint8_t buf_overflow = 0;

uint32_t flash_tx_data;
uint32_t *flash_rx_data;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	/* Prevent unused argument(s) compilation warning */
	UNUSED(huart);
	UNUSED(Size);

	/* NOTE : This function should not be modified, when the callback is needed,
            the HAL_UARTEx_RxEventCallback can be implemented in the user file.
	 */
	temp = Size;

	if(Size != BUFFER_SIZE)
		data_reception_complete = 1;
	else if(Size == BUFFER_SIZE)
		buf_overflow = 1;
}
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
	MX_USART2_UART_Init();
	/* USER CODE BEGIN 2 */
	HAL_Delay(1000);
	HAL_UART_Transmit(&huart2, (uint8_t *)"Start\n", 6, 100);

//	// Flash test
//	Flash_Erase_Sector(0x08060000);
//	flash_tx_data = (uint32_t)'\n' << 24 | (uint32_t)'N' << 16 | (uint32_t)'U' << 8 | (uint32_t)'P';
//	Flash_Write_Data(0x08060000, &flash_tx_data, 1);
////	Flash_Read_Data(0x08060000, flash_rx_data, 1);
//
//	Flash_Erase_Sector(0x08060000);
//	flash_tx_data = (uint32_t)'\n' << 24 | (uint32_t)'L' << 16 | (uint32_t)'E' << 8 | (uint32_t)'H';
//	Flash_Write_Data(0x08060000, &flash_tx_data, 1);

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */

	// Erase FLASH contents
	Flash_Erase_Sector(0x08060000);

	// Set array to NULL
	memset(received_data, '~', BUFFER_SIZE);

	// Trigger Receive DMA
	HAL_UARTEx_ReceiveToIdle_DMA(&huart2, received_data, BUFFER_SIZE);
	// Disable half transfer complete IRQ
	__HAL_DMA_DISABLE_IT(&hdma_usart2_rx, DMA_IT_HT);


	while (1)
	{
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
		while((received_data[receive_buffer_index + previous_received_data_size] != '~') && ((receive_buffer_index + previous_received_data_size) < BUFFER_SIZE))
		{
			// Save received uint8_t character in uint32_t variable
//			buffer[main_buffer_index] = ((uint32_t)((received_data[receive_buffer_index + previous_received_data_size + 3]) << 24)) |
//					((uint32_t)((received_data[receive_buffer_index + previous_received_data_size + 2]) << 16)) |
//					((uint32_t)((received_data[receive_buffer_index + previous_received_data_size + 1]) << 8)) |
//					(uint32_t)(received_data[receive_buffer_index + previous_received_data_size]);

//			uint8_t var_one = received_data[receive_buffer_index + previous_received_data_size + 3];
//			uint8_t var_two = received_data[receive_buffer_index + previous_received_data_size + 2];
//			uint8_t var_three = received_data[receive_buffer_index + previous_received_data_size + 1];
//			uint8_t var_four = received_data[receive_buffer_index + previous_received_data_size];

//			flash_tx_data = (uint32_t)((uint32_t)received_data[receive_buffer_index + previous_received_data_size + 3] << 24 | (uint32_t)received_data[receive_buffer_index + previous_received_data_size + 2] << 16 | (uint32_t)received_data[receive_buffer_index + previous_received_data_size + 1] << 8 | (uint32_t)received_data[receive_buffer_index + previous_received_data_size]);

//			flash_tx_data = (uint32_t)received_data[receive_buffer_index + previous_received_data_size + 3] << 24;
//			flash_tx_data |= (uint32_t)received_data[receive_buffer_index + previous_received_data_size + 2] << 16;
//			flash_tx_data |= (uint32_t)received_data[receive_buffer_index + previous_received_data_size + 1] << 8;
//			flash_tx_data |= (uint32_t)received_data[receive_buffer_index + previous_received_data_size];

//			flash_tx_data = (uint32_t)var_one << 24 | (uint32_t)var_two << 16 | (uint32_t)var_three << 8 | (uint32_t)var_four;

//			// Save received uint8_t character
//			buffer[receive_buffer_index] = received_data[receive_buffer_index + previous_received_data_size];


			flash_tx_data |= (uint32_t)received_data[receive_buffer_index + previous_received_data_size] << (8 * local_count);

			if(local_count == 3)
			{
				local_count = 0;

				// Read data from FLASH
				Flash_Read_Data(0x08060000, flash_rx_data, total_number_of_words);
				HAL_Delay(50);

				// Erase FLASH contents
				Flash_Erase_Sector(0x08060000);
				HAL_Delay(50);

				*(flash_rx_data + total_number_of_words) = flash_tx_data;
				total_number_of_words++;

				// Write data into FLASH
				Flash_Write_Data(0x08060000, flash_rx_data, total_number_of_words);
				HAL_Delay(50);

				flash_tx_data = 0;
			}
			else
				local_count++;

			// Increment receive_buffer_index
//			receive_buffer_index++;

			receive_buffer_index++;
//			main_buffer_index++;
		}

		if(flash_tx_data != 0)
		{
//			local_count = 0;

			// Read data from FLASH
			Flash_Read_Data(0x08060000, flash_rx_data, total_number_of_words);
			HAL_Delay(50);

			// Erase FLASH contents
			Flash_Erase_Sector(0x08060000);
			HAL_Delay(50);

			*(flash_rx_data + total_number_of_words) = flash_tx_data;
			total_number_of_words++;

			// Write data into FLASH
			Flash_Write_Data(0x08060000, flash_rx_data, total_number_of_words);
			HAL_Delay(50);

			flash_tx_data = 0;

		}

//		if(buf_overflow)
//		{
//			uint8_t i = 0;
//			while((received_data[i] != '\0'))
//			{
//				buffer[receive_buffer_index] = received_data[i];
//				i++;
//				receive_buffer_index++;
//			}
//		}

		if(data_reception_complete)
		{
			data_reception_complete = 0;

			data_copying_complete = 1;
			received_data_length = receive_buffer_index;

			receive_buffer_index = 0;
			main_buffer_index = 0;

			memset(received_data, '~', BUFFER_SIZE);
//			memset(buffer, '\0', BUFFER_SIZE);

			previous_received_data_size = temp;
			if(previous_received_data_size > BUFFER_SIZE)
				previous_received_data_size = previous_received_data_size - BUFFER_SIZE;
			else if(previous_received_data_size == BUFFER_SIZE)
				previous_received_data_size = 0;

			// Trigger Receive DMA
			HAL_UARTEx_ReceiveToIdle_DMA(&huart2, &received_data[0], BUFFER_SIZE);
			// Disable half transfer complete IRQ
			__HAL_DMA_DISABLE_IT(&hdma_usart2_rx, DMA_IT_HT);
		}

		if(data_copying_complete)
		{
			uint32_t i = 0;
			uint32_t count = 0;

			data_copying_complete = 0;

			// Read data from FLASH
			Flash_Read_Data(0x08060000, flash_rx_data, total_number_of_words);

			for(i=0;i<total_number_of_words*4;i+=4)
			{
				tx_data[i] = *(flash_rx_data + count) & 0xFF;
				tx_data[i+1] = *(flash_rx_data + count) & 0xFF00;
				tx_data[i+2] = *(flash_rx_data + count) & 0xFF0000;
				tx_data[i+3] = *(flash_rx_data + count) & 0xFF000000;

				count++;
			}

			HAL_UART_Transmit(&huart2, tx_data, i+3, 100);

//			memset(buffer, '~', BUFFER_SIZE);

			total_number_of_words = 0;

			// Erase FLASH contents
			Flash_Erase_Sector(0x08060000);
		}

		HAL_Delay(5);
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

	/** Supply configuration update enable
	 */
	HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

	/** Configure the main internal regulator output voltage
	 */
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

	while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;
	RCC_OscInitStruct.HSICalibrationValue = 64;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLM = 4;
	RCC_OscInitStruct.PLL.PLLN = 12;
	RCC_OscInitStruct.PLL.PLLP = 1;
	RCC_OscInitStruct.PLL.PLLQ = 4;
	RCC_OscInitStruct.PLL.PLLR = 2;
	RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
	RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
	RCC_OscInitStruct.PLL.PLLFRACN = 0;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
			|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
			|RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
	RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
	{
		Error_Handler();
	}
}

/**
 * @brief USART2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART2_UART_Init(void)
{

	/* USER CODE BEGIN USART2_Init 0 */

	/* USER CODE END USART2_Init 0 */

	/* USER CODE BEGIN USART2_Init 1 */

	/* USER CODE END USART2_Init 1 */
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 2400;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart2.Init.ClockPrescaler = UART_PRESCALER_DIV1;
	huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_UART_Init(&huart2) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_UARTEx_SetTxFifoThreshold(&huart2, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_UARTEx_SetRxFifoThreshold(&huart2, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_UARTEx_DisableFifoMode(&huart2) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN USART2_Init 2 */

	/* USER CODE END USART2_Init 2 */

}

/**
 * Enable DMA controller clock
 */
static void MX_DMA_Init(void)
{

	/* DMA controller clock enable */
	__HAL_RCC_DMA1_CLK_ENABLE();

	/* DMA interrupt init */
	/* DMA1_Stream0_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DMA1_Stream0_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA1_Stream0_IRQn);

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	/* USER CODE BEGIN MX_GPIO_Init_1 */
	/* USER CODE END MX_GPIO_Init_1 */

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB, LED_GREEN_Pin|LED_RED_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(USB_FS_PWR_EN_GPIO_Port, USB_FS_PWR_EN_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin : B1_Pin */
	GPIO_InitStruct.Pin = B1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : RMII_MDC_Pin RMII_RXD0_Pin RMII_RXD1_Pin */
	GPIO_InitStruct.Pin = RMII_MDC_Pin|RMII_RXD0_Pin|RMII_RXD1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	/*Configure GPIO pins : RMII_REF_CLK_Pin RMII_CRS_DV_Pin */
	GPIO_InitStruct.Pin = RMII_REF_CLK_Pin|RMII_CRS_DV_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pins : LED_GREEN_Pin LED_RED_Pin */
	GPIO_InitStruct.Pin = LED_GREEN_Pin|LED_RED_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/*Configure GPIO pin : RMII_TXD1_Pin */
	GPIO_InitStruct.Pin = RMII_TXD1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
	HAL_GPIO_Init(RMII_TXD1_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : STLK_VCP_RX_Pin STLK_VCP_TX_Pin */
	GPIO_InitStruct.Pin = STLK_VCP_RX_Pin|STLK_VCP_TX_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	/*Configure GPIO pin : USB_FS_PWR_EN_Pin */
	GPIO_InitStruct.Pin = USB_FS_PWR_EN_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(USB_FS_PWR_EN_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pin : USB_FS_OVCR_Pin */
	GPIO_InitStruct.Pin = USB_FS_OVCR_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(USB_FS_OVCR_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pin : USB_FS_ID_Pin */
	GPIO_InitStruct.Pin = USB_FS_ID_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF10_OTG1_HS;
	HAL_GPIO_Init(USB_FS_ID_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : RMII_TX_EN_Pin RMII_TXD0_Pin */
	GPIO_InitStruct.Pin = RMII_TX_EN_Pin|RMII_TXD0_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

	/*Configure GPIO pin : LED_YELLOW_Pin */
	GPIO_InitStruct.Pin = LED_YELLOW_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LED_YELLOW_GPIO_Port, &GPIO_InitStruct);

	/* USER CODE BEGIN MX_GPIO_Init_2 */
	/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  Period elapsed callback in non blocking mode
 * @note   This function is called  when TIM4 interrupt took place, inside
 * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
 * a global variable "uwTick" used as application time base.
 * @param  htim : TIM handle
 * @retval None
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	/* USER CODE BEGIN Callback 0 */

	/* USER CODE END Callback 0 */
	if (htim->Instance == TIM4) {
		HAL_IncTick();
	}
	/* USER CODE BEGIN Callback 1 */

	/* USER CODE END Callback 1 */
}

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
