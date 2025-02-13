/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
// FreeRTOS library
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef struct {
	uint8_t CMD_num;
	uint8_t CMD_args[8];
} APP_CMD_t;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define LED_ON 1
#define LED_TOUGLE 2
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
TaskHandle_t task1_handle = NULL;
TaskHandle_t task2_handle = NULL;
TaskHandle_t task3_handle = NULL;
TaskHandle_t task4_handle = NULL;

QueueHandle_t command_queue = NULL;
QueueHandle_t uart_write_queue = NULL;

TimerHandle_t led_timer;

char uart_msg[250] = { 0 };

char command_buffer[250];
uint32_t command_len = 0;
char rdata;

char menu[] = {" \
		\r\nLED_ON	    --> 1\
		\r\nLED_OFF	    --> 2\
		\r\nLED_TOUGLE	--> 3\
		\r\nType of your option here: "};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

static void task1_menu_display(void *parameters);
static void task2_cmd_handling(void *parameters);
static void task3_cmd_processing(void *parameters);
static void task4_uart_write(void *parameters);
void toggle_led( TimerHandle_t xTimer );
void led_toggle(void);
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

	BaseType_t status;

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
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

	// uart
	if (HAL_UART_Receive_IT(&huart2, &rdata, 1) != HAL_OK) {
		Error_Handler();
	}

	// create queue
	command_queue = xQueueCreate(10, sizeof(APP_CMD_t*));

	uart_write_queue = xQueueCreate(10, sizeof(char*));

	if ((command_queue != NULL) && (uart_write_queue != NULL)) {
		status = xTaskCreate(task1_menu_display, "Task-1", 500,
		NULL, 2, &task1_handle);

		configASSERT(status == pdPASS);

		status = xTaskCreate(task2_cmd_handling, "Task-2", 500,
		NULL, 2, &task2_handle);
		configASSERT(status == pdPASS);

		status = xTaskCreate(task3_cmd_processing, "Task-3", 500,
		NULL, 2, &task3_handle);
		configASSERT(status == pdPASS);

		status = xTaskCreate(task4_uart_write, "Task-4", 500,
		NULL, 2, &task4_handle);
		configASSERT(status == pdPASS);

		//start the freeRTOS scheduler
		vTaskStartScheduler();
	} else {
		sprintf(uart_msg, "Queue created failed\n\r");
		HAL_UART_Transmit(&huart2, uart_msg, sizeof(uart_msg), HAL_MAX_DELAY);
	}

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1) {
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
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
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

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
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pins : PD14 PD15 */
  GPIO_InitStruct.Pin = GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

static void task1_menu_display(void *parameters) {

	char *pdata = menu;
	while (1)
	{
		xQueueSend(uart_write_queue, pdata, portMAX_DELAY);
		xTaskNotifyWait(0, 0, NULL, portMAX_DELAY);
	}

}
static void task2_cmd_handling(void *parameters) {
//	uint8_t command_code = 0;
//
//	APP_CMD_t *new_cmd;
//	while (1) {
//		xTaskNotifyWait(0,0,NULL, portMAX_DELAY);
//		command_code = getCommandCode(command_buff);
//		new_cmd = (APP_CMD_t*)pvPortMalloc(sizeof(APP_CMD_t));
//		new_cmd->CMD_num = command_code;
//		getArguments(new_cmd->CMD_args);
//
//		// queue send
//		xQueueSend(command_queue, &new_cmd, portMAX_DELAY);
//	}

}
static void task3_cmd_processing(void *parameters) {

	APP_CMD_t *new_cmd;
	while (1) {
		xQueueReceive(command_queue, &new_cmd, portMAX_DELAY);
		if(new_cmd->CMD_num == LED_TOUGLE)
		{
			led_toggle();
		}else if(new_cmd->CMD_num == LED_ON)
		{
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);
		}else	// LED_OFF
		{
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
		}
	}

}
static void task4_uart_write(void *parameters) {
	char *buff = NULL;
	while (1) {
		xQueueReceive(uart_write_queue, &buff, portMAX_DELAY);
		HAL_UART_Transmit(&huart2, buff, sizeof(buff), HAL_MAX_DELAY);
	}

}

// uart callback function
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	command_buffer[command_len++] = (rdata & 0xff);
	BaseType_t pxHigherPriorityTaskWoken = pdFALSE;
	if (HAL_UART_Receive_IT(&huart2, &rdata, 1) != HAL_OK) {
		Error_Handler();
	}
	if(rdata == "\r")
	{
		// notify to task
		xTaskNotifyFromISR(task2_handle, 0, eNoAction, pxHigherPriorityTaskWoken);
		xTaskNotifyFromISR(task1_handle, 0, eNoAction, pxHigherPriorityTaskWoken);
	}
	if(pxHigherPriorityTaskWoken)
	{
		taskYIELD();
	}
}

void toggle_led_start( TimerHandle_t xTimer )
{
	HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
}

void toggle_led_stop( TimerHandle_t xTimer )
{
	xTimerStop(led_timer, portMAX_DELAY);
}

void led_toggle(void)
{
	// created sw timer
	led_timer = xTimerCreate("LED_TOGGLE", pdMS_TO_TICKS(200), pdTRUE, (void*)0, toggle_led_start);
	// start sw timer
	xTimerStart(led_timer, portMAX_DELAY);
}

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6) {
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
