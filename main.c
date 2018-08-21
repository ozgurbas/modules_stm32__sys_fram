/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
//#include <global_ex.h>
#include "global_top_level_includes.h"

#include "stm32f0xx_hal.h"
#include "crc.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */

#include	"type_definitions.h"

#include "sys_keyboard_public.h"
#include "sys_fram_public.h"
#include "sys_driver__public.h"

extern void f_sys_c2c__main_task_10ms_base(void);

extern uint8_t			u8_sys_ui__nvprm__IN_PULSE_TRAIN_MIN;
extern uint8_t			u8_sys_ui__nvprm__IN_PULSE_TRAIN_MAX;

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void Error_Handler(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

u32_u16_u8_u1 	u32_u16_u8_u1_SYSTICK__time_flags;
#define 	u1_flag_SYSTICK_1ms				u32_u16_u8_u1_SYSTICK__time_flags.u1.u1_8
#define 	u1_flag_SYSTICK_10ms			u32_u16_u8_u1_SYSTICK__time_flags.u1.u1_9
#define 	u1_flag_SYSTICK_100ms			u32_u16_u8_u1_SYSTICK__time_flags.u1.u1_10
#define 	u1_flag_SYSTICK_1000ms			u32_u16_u8_u1_SYSTICK__time_flags.u1.u1_11
#define 	u1_flag_SYSTICK_1HZ_TOGGLED		u32_u16_u8_u1_SYSTICK__time_flags.u1.u1_31

uint8_t 	u8_10_ms_counter;
uint8_t 	u8_100_ms_counter;
uint8_t 	u8_1000_ms_counter;

void f_SYSTICK__prepare_time_flags_at_out_of_INTERRUPT(void)
{
	u8_10_ms_counter++;
	if(u8_10_ms_counter>9)
	{
		u8_10_ms_counter=0;
		u1_flag_SYSTICK_10ms=1;
		u8_100_ms_counter++;
		if(u8_100_ms_counter>9)
		{
			u8_100_ms_counter=0;
			u1_flag_SYSTICK_100ms=1;
			u8_1000_ms_counter++;
			if(u8_1000_ms_counter>9)
			{
				u8_1000_ms_counter=0;
				u1_flag_SYSTICK_1000ms=1;

				if(u1_flag_SYSTICK_1HZ_TOGGLED==0)
				{
					u1_flag_SYSTICK_1HZ_TOGGLED=1;
				}
				else
				{
					u1_flag_SYSTICK_1HZ_TOGGLED=0;
				}
			}
		}
	}
}


u8 u8_buzzer_counter=0;

void f_buzzer_x_ms_bip_request(u8 x)
{
	HAL_GPIO_WritePin(pin_BUZZER_GPIO_Port, pin_BUZZER_Pin, GPIO_PIN_SET);
	u8_buzzer_counter=x;
}


//u8 	u8_main_1ms_flag=0;
//__weak void HAL_SYSTICK_Callback(void)
void HAL_SYSTICK_Callback(void)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_SYSTICK_Callback could be implemented in the user file
   */

	u1_flag_SYSTICK_1ms=1;
}


u8 	u8_main_i=0;

//EXTERNS:
//==============================================================
//extern uint8_t			u8_array_sys_ui__SEGMENT_DRIVE_BUFFER_l_36[36];
//extern u32_u16_u8_u1 	u32_u16_u8_u1_sys_ui__DP_BUFFER;

extern CRC_HandleTypeDef hcrc;
extern DMA_HandleTypeDef hdma_usart2_rx;

extern void f_sys_ui__STARTUP(void);
extern uint8_t 	f_u8_sys_c2c__UPDATE_DISPLAY(void);
extern void f_sys_ui__main_task_100ms_base(void);
//==============================================================

uint32_t		u32_1ms_measure_counter=0;

//uint8_t			u8_array_TEST__BUFFER[20];

void MX_GPIO_Init__ek(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;

	GPIO_InitStruct.Pin = pin_IDC_B_1_Pin;
	HAL_GPIO_Init(pin_IDC_B_1_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = pin_IDC_B_2_Pin;
	HAL_GPIO_Init(pin_IDC_B_2_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = pin_IDC_B_3_Pin;
	HAL_GPIO_Init(pin_IDC_B_3_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = pin_IDC_B_4_Pin;
	HAL_GPIO_Init(pin_IDC_B_4_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = pin_IDC_B_5_Pin;
	HAL_GPIO_Init(pin_IDC_B_5_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = pin_IDC_B_6_Pin;
	HAL_GPIO_Init(pin_IDC_B_6_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = pin_IDC_B_7_Pin;
	HAL_GPIO_Init(pin_IDC_B_7_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = pin_IDC_B_8_Pin;
	HAL_GPIO_Init(pin_IDC_B_8_GPIO_Port, &GPIO_InitStruct);

}


u16	u16_pulse_train_up_counter=0xffff;
void f_task_1ms__create_pulse_train(void)
{
	if(u16_pulse_train_up_counter<500)
	{
		u16_pulse_train_up_counter++;


		//==============================================================================

		if(u16_pulse_train_up_counter==1)
		{
			HAL_GPIO_WritePin(pin_IDC_B_1_GPIO_Port, pin_IDC_B_1_Pin, GPIO_PIN_SET);
		}

		if(u16_pulse_train_up_counter==21)
		{
			HAL_GPIO_WritePin(pin_IDC_B_1_GPIO_Port, pin_IDC_B_1_Pin, GPIO_PIN_RESET);
		}

		if(u16_pulse_train_up_counter==41)
		{
			HAL_GPIO_WritePin(pin_IDC_B_1_GPIO_Port, pin_IDC_B_1_Pin, GPIO_PIN_SET);
		}

		if(u16_pulse_train_up_counter==61)
		{
			HAL_GPIO_WritePin(pin_IDC_B_1_GPIO_Port, pin_IDC_B_1_Pin, GPIO_PIN_RESET);
		}
//
//		//capture OK
//
//		u16_pulse_train_up_counter	uint16_t	68
//		u16_last_three_time_intervals_of_changes	uint16_t [3]	0x200000ec <u16_last_three_time_intervals_of_changes>
//			u16_last_three_time_intervals_of_changes[0]	uint16_t	22
//			u16_last_three_time_intervals_of_changes[1]	uint16_t	18
//			u16_last_three_time_intervals_of_changes[2]	uint16_t	22

		//==============================================================================

//			if(u16_pulse_train_up_counter==1)
//			{
//				HAL_GPIO_WritePin(pin_IDC_B_1_GPIO_Port, pin_IDC_B_1_Pin, GPIO_PIN_SET);
//			}
//
//			if(u16_pulse_train_up_counter==21)
//			{
//				HAL_GPIO_WritePin(pin_IDC_B_1_GPIO_Port, pin_IDC_B_1_Pin, GPIO_PIN_RESET);
//			}
//
//			if(u16_pulse_train_up_counter==41)
//			{
//				HAL_GPIO_WritePin(pin_IDC_B_1_GPIO_Port, pin_IDC_B_1_Pin, GPIO_PIN_SET);
//			}
//
//			if(u16_pulse_train_up_counter==61)
//			{
//				HAL_GPIO_WritePin(pin_IDC_B_1_GPIO_Port, pin_IDC_B_1_Pin, GPIO_PIN_RESET);
//			}
//
//			if(u16_pulse_train_up_counter==81)
//			{
//				HAL_GPIO_WritePin(pin_IDC_B_1_GPIO_Port, pin_IDC_B_1_Pin, GPIO_PIN_SET);
//			}
//
//			if(u16_pulse_train_up_counter==101)
//			{
//				HAL_GPIO_WritePin(pin_IDC_B_1_GPIO_Port, pin_IDC_B_1_Pin, GPIO_PIN_RESET);
//			}
//
//			//		//capture OK
//			//
//			//		u16_pulse_train_up_counter	uint16_t	68
//			//		u16_last_three_time_intervals_of_changes	uint16_t [3]	0x200000ec <u16_last_three_time_intervals_of_changes>
//			//			u16_last_three_time_intervals_of_changes[0]	uint16_t	22
//			//			u16_last_three_time_intervals_of_changes[1]	uint16_t	18
//			//			u16_last_three_time_intervals_of_changes[2]	uint16_t	22
//
//			hatta sonraki set reset de debugda cope atıldıgı goruldu!!! miss!!!

	}

}


u8 	u8_input1_filter_counter=0;
u8 	u8_input1_virtual_value=0;
u8 	u8_input1_virtual_value_previous=0;

u16	u16_input1_time_after_change_counter=0;

u16 u16_last_three_time_intervals_of_changes[3];
u16 u16_last_three_time_intervals_of_changes__CAPTURE[3];
u8  u8_index_of_time_intervals_of_changes=0;
u16	u16_no_change_counter=0;

u8 	u8_IDC_A_1_Pin_pulse_train_captured=0;
u8 	u8_IDC_A_1_Pin_pulse_train_refused=0;

void f_task_1ms__scan_pulse_train(void)
{
	//{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{
	if(	( (HAL_GPIO_ReadPin(pin_IDC_A_1_GPIO_Port,pin_IDC_A_1_Pin)) == GPIO_PIN_SET )
			&& (u8_input1_filter_counter<5) )
	{
		u8_input1_filter_counter++;
		if(u8_input1_filter_counter==5)
		{
			u8_input1_virtual_value=1;
		}
	}
	else if(	( (HAL_GPIO_ReadPin(pin_IDC_A_1_GPIO_Port,pin_IDC_A_1_Pin)) == GPIO_PIN_RESET )
			&& (u8_input1_filter_counter>0) )
	{
		u8_input1_filter_counter--;
		if(u8_input1_filter_counter==0)
		{
			u8_input1_virtual_value=0;
		}
	}

	//edges deteced with virtual values!!!
	if(
			( (u8_input1_virtual_value_previous==0) && (u8_input1_virtual_value==1) ) //rise detected!!! (fitre sayacın 0 a dusup tekrar 5 e cikmasini ister)
			||
			( (u8_input1_virtual_value_previous==1) && (u8_input1_virtual_value==0) ) //fall detected!!! (fitre sayacın 0 a dusup tekrar 5 e cikmasini ister)
			)
	{
		u16_no_change_counter=0;

		if(u8_index_of_time_intervals_of_changes==100)
		{
			//500ms silence sonrası ilk değişim!!!
			u8_index_of_time_intervals_of_changes=0;
			u16_input1_time_after_change_counter=0;
		}
		else
		{
			//onlem
			if(u8_index_of_time_intervals_of_changes>2) u8_index_of_time_intervals_of_changes=0;

			u16_last_three_time_intervals_of_changes[u8_index_of_time_intervals_of_changes]=u16_input1_time_after_change_counter;
			u8_index_of_time_intervals_of_changes++;
			u16_input1_time_after_change_counter=0;
		}
	}


	u8_input1_virtual_value_previous=u8_input1_virtual_value;


	if(u8_index_of_time_intervals_of_changes==3)
	{
		//analyse array values
		if(
				(u16_last_three_time_intervals_of_changes[0]>u8_sys_ui__nvprm__IN_PULSE_TRAIN_MIN) && (u16_last_three_time_intervals_of_changes[0]<u8_sys_ui__nvprm__IN_PULSE_TRAIN_MAX) &&
				(u16_last_three_time_intervals_of_changes[1]>u8_sys_ui__nvprm__IN_PULSE_TRAIN_MIN) && (u16_last_three_time_intervals_of_changes[1]<u8_sys_ui__nvprm__IN_PULSE_TRAIN_MAX) &&
				(u16_last_three_time_intervals_of_changes[2]>u8_sys_ui__nvprm__IN_PULSE_TRAIN_MIN) && (u16_last_three_time_intervals_of_changes[2]<u8_sys_ui__nvprm__IN_PULSE_TRAIN_MAX)
		)
		{
			//pulse train captured!!!

			u8_IDC_A_1_Pin_pulse_train_captured=1;

			//trigger clean at below!!!
			u16_no_change_counter=500;
		}
		else
		{

			u8_IDC_A_1_Pin_pulse_train_refused=1;
			//trigger clean at below!!!
			u16_no_change_counter=500;
		}


		u16_last_three_time_intervals_of_changes__CAPTURE[0]=u16_last_three_time_intervals_of_changes[0];
		u16_last_three_time_intervals_of_changes__CAPTURE[1]=u16_last_three_time_intervals_of_changes[1];
		u16_last_three_time_intervals_of_changes__CAPTURE[2]=u16_last_three_time_intervals_of_changes[2];
	}

	//long stability of signal resets buffer and index!!!
	u16_no_change_counter++;
	if(u16_no_change_counter>500)
	{
		u16_last_three_time_intervals_of_changes[0]=0;
		u16_last_three_time_intervals_of_changes[1]=0;
		u16_last_three_time_intervals_of_changes[2]=0;
		u8_index_of_time_intervals_of_changes=100;

		u16_no_change_counter=0;
	}

	u16_input1_time_after_change_counter++;

	//}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}

}

/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_SPI1_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();

  MX_SPI2_Init();

  MX_TIM2_Init();
  MX_TIM14_Init();
  MX_TIM16_Init();
  MX_CRC_Init();




  /* USER CODE BEGIN 2 */

  MX_GPIO_Init__ek();

//  HAL_GPIO_WritePin(pin_IDC_B_1_GPIO_Port, pin_IDC_B_1_Pin, GPIO_PIN_SET);
//  HAL_GPIO_WritePin(pin_IDC_B_1_GPIO_Port, pin_IDC_B_1_Pin, GPIO_PIN_RESET);

  HAL_GPIO_WritePin(pin_STP_n_reset_X_Y_Z_GPIO_Port, pin_STP_n_reset_X_Y_Z_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(pin_LED_1_GPIO_Port, pin_LED_1_Pin, GPIO_PIN_SET);
  HAL_Delay(500);
  HAL_GPIO_WritePin(pin_LED_2_GPIO_Port, pin_LED_2_Pin, GPIO_PIN_SET);
  //f_sys_spi_pA_H_startup();

  //test ok
//  HAL_GPIO_WritePin(pin_BUZZER_GPIO_Port, pin_BUZZER_Pin, GPIO_PIN_SET);
//  HAL_Delay(166);
//  HAL_GPIO_WritePin(pin_BUZZER_GPIO_Port, pin_BUZZER_Pin, GPIO_PIN_RESET);
//  HAL_Delay(166);
//  HAL_GPIO_WritePin(pin_BUZZER_GPIO_Port, pin_BUZZER_Pin, GPIO_PIN_SET);
//  HAL_Delay(166);
//  HAL_GPIO_WritePin(pin_BUZZER_GPIO_Port, pin_BUZZER_Pin, GPIO_PIN_RESET);
//  HAL_Delay(166);
//  HAL_GPIO_WritePin(pin_BUZZER_GPIO_Port, pin_BUZZER_Pin, GPIO_PIN_SET);
//  HAL_Delay(166);
//  HAL_GPIO_WritePin(pin_BUZZER_GPIO_Port, pin_BUZZER_Pin, GPIO_PIN_RESET);

  //f_sys_fram__STARTUP(); //ui triggers!!!
  f_sys_ui__STARTUP();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

	  //	  HAL_GPIO_WritePin(pin_LED_1_GPIO_Port, pin_LED_1_Pin, GPIO_PIN_SET);
	  //	  HAL_GPIO_WritePin(pin_LED_2_GPIO_Port, pin_LED_2_Pin, GPIO_PIN_RESET);
	  //	  HAL_Delay(500);
	  //	  HAL_GPIO_WritePin(pin_LED_1_GPIO_Port, pin_LED_1_Pin, GPIO_PIN_RESET);
	  //	  HAL_GPIO_WritePin(pin_LED_2_GPIO_Port, pin_LED_2_Pin, GPIO_PIN_SET);
	  //	  HAL_Delay(500);
	  //	  HAL_Delay(1);
	  	  //f_sys_spi_pA_H_task_xus();



	  	  //====================000=====================
		  if(u1_flag_SYSTICK_1ms==1)
		  {
			  u32_1ms_measure_counter++;

			  u1_flag_SYSTICK_1ms=0;
			  f_SYSTICK__prepare_time_flags_at_out_of_INTERRUPT();

			  f_sys_driver__main_task_1ms_base();
			  //f_sys_spi_pA_H_task_xus();

		  	  f_sys_keyboard_MAIN_TASK();
		  	  f_sys_fram_MAIN_TASK_1ms_base();

		  	  if(u8_buzzer_counter>0)
		  	  {
		  		  u8_buzzer_counter--;
		  		  if(u8_buzzer_counter==0)
		  		  {
		  			  HAL_GPIO_WritePin(pin_BUZZER_GPIO_Port, pin_BUZZER_Pin, GPIO_PIN_RESET);
		  		  }
		  	  }

		  	  //f_task_1ms__create_pulse_train(); //test icin sadece!!!

		  	  f_task_1ms__scan_pulse_train();
		  }

		  if(u1_flag_SYSTICK_10ms==1)
		  {
			  u1_flag_SYSTICK_10ms=0;

			  //f_sys_driver__main_task_1ms_base();

			  //f_sys_spi_pA_H_task_xus();

			  f_sys_c2c__main_task_10ms_base();
		  }

		  if(u1_flag_SYSTICK_100ms==1)
		  {
			  u1_flag_SYSTICK_100ms=0;
	//		  HAL_GPIO_WritePin(pin_LED_1_GPIO_Port, pin_LED_1_Pin, GPIO_PIN_RESET);
	//		  HAL_GPIO_WritePin(pin_LED_2_GPIO_Port, pin_LED_2_Pin, GPIO_PIN_RESET);

			  //f_sys_disp__main_task_100ms_base();
			  f_sys_ui__main_task_100ms_base();
		  }

		  if(u1_flag_SYSTICK_1000ms==1)
		  {
			  u1_flag_SYSTICK_1000ms=0;

			  HAL_GPIO_WritePin(pin_LED_1_GPIO_Port, pin_LED_1_Pin, u1_flag_SYSTICK_1HZ_TOGGLED);
			  HAL_GPIO_WritePin(pin_LED_2_GPIO_Port, pin_LED_2_Pin, u1_flag_SYSTICK_1HZ_TOGGLED);


			  //display test: OK!!! :)
//			  //[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
//			  for(u8_main_i=0;u8_main_i<35;u8_main_i++)
//			  {
//				  u8_array_sys_ui__SEGMENT_DRIVE_BUFFER_l_36[u8_main_i]=u8_array_sys_ui__SEGMENT_DRIVE_BUFFER_l_36[u8_main_i+1];
//			  }
//			  f_u8_sys_c2c__UPDATE_DISPLAY();
//			  //]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
		  }
		  //====================000=====================


  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
