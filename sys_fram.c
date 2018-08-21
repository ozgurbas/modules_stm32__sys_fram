/*
 * sys_fram.c
 *
 *  Created on: Nov 27, 2016
 *      Author: ozgurbas
 */

#include	"sys_fram_private.h"

u8 f_u8_sys_fram__check_CRC_of__BL_xxx__and_REPAIR_and_return_STATUS(u16 u16_mI__start,u16 u16_mI__end_CRC_L);

extern void f_sys_driver__HAL_SPI_TxRxCpltCallback__of_SPI2(void);

//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
//diger SPI a DMA yetmedigi icin sadece SPI 1 DMA kullanıyor, bu yuzden fonksion burada.
u8 u8_sys_fram_flag_FRAM_SPI_DMA_TRANSECTION_COMPLETED=0;
//__weak void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
  /* Prevent unused argument(s) compilation warning */
  //UNUSED(hspi);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_SPI_TxRxCpltCallback should be implemented in the user file
   */

	  if(hspi->Instance==SPI1)
	  {
		  u8_sys_fram_flag_FRAM_SPI_DMA_TRANSECTION_COMPLETED=1;
		  //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET); 	//set NSS !!! devam eden komutlar icin burada kapatildi!!!
	  }
	  else if(hspi->Instance==SPI2)
	  {
		  f_sys_driver__HAL_SPI_TxRxCpltCallback__of_SPI2();
	  }
}
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]



//*
//***
//*****
//*******
//*********
//***********
//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[

//#define 	def_u16_sys_fram__LENGTH_OF_RW_REQUEST_ARRAY	50
//
////INPUTS:
//uint16_t	u16_array_sys_fram__COMMANDS_of_REQUESTS[def_u16_sys_fram__LENGTH_OF_RW_REQUEST_ARRAY];
//uint16_t	u16_array_sys_fram__COMMON_ACQUISITION_INDEXES_of_REQUESTS[def_u16_sys_fram__LENGTH_OF_RW_REQUEST_ARRAY];
//
////OUTPUTS:
//uint16_t	u16_array_sys_fram__RESULTS__of_REQUESTS[def_u16_sys_fram__LENGTH_OF_RW_REQUEST_ARRAY];
////parameter value applied to address value specified at PARALLEL array lists!!!
//
//uint16_t	u16_sys_fram__REQUEST_INDEX__NEXT_IMPLEMENTATION=0;		//arrayin basinda
//uint16_t	u16_sys_fram__REQUEST_INDEX__NEXT_ACCEPTANCE=0; 		//arrayin basinda
////senaryo
////acceptance ilerler, implemantation kovalar, esleninceye kadar kovalanir,
////acceptance ın bir fazlası implemantationsa red edilir!!!
////ornegin acceptance 50 ye kadar kabul eder,(ilerler ve ilerledigi yere koyar),
////50 den sonrası 0 adonus oldugu ve implementation a esit oldugu icin red edilir.
////burada her ilerleme mod def_u16_sys_fram__LENGTH_OF_RW_REQUEST_ARRAY ile kontrol edilerek duzeltilme isleminden gecicek
//
//uint16_t	f_u16_sys_fram__GET_RAM_FRAM_TRANSFER_REQUEST_and_RETURN_RESULT_TRACKING_INDEX(
//		uint16_t 	f_in_u16__PRMTR_ATTR_LISTS_COMMON_ACQUISITION_INDEX,
//		uint16_t	f_in_u8__TRANSFER_DIRECTION,
//		)
//{
//	uint16_t	RESULT_TRACKING_INDEX=0;
//
//	if(u16_sys_fram__REQUEST_INDEX__NEXT_ACCEPTANCE!=u16_sys_fram__REQUEST_INDEX__NEXT_IMPLEMENTATION) //is request buffer full?
//	{
//
//	}
//
////	if(f_in_u8__TRANSFER_DIRECTION==def_u8_enum__TRANSFER_DIRECTION__READ_FRAM_TO_RAM)
////	{
////
////	}
////	else //if(f_in_u8__TRANSFER_DIRECTION==def_u8_enum__TRANSFER_DIRECTION__WRITE_RAM_TO_FRAM)
////	{
////
////	}
//
//
//	return	RESULT_TRACKING_INDEX;
//}


////FIKIR!!!
////HIC "RESULT_TRACKING_INDEX" GIBI ALENGILLI ISLERE GEREK YOK,
////sonucta her parametrenin bi erisim attr tabloları var,
//birde status register arrayi olsun, constant yerine ramde,
//talep isteyen buraya yazsın bitine, 0. R, 1. W
//sys_fram bu arrayi tarayıp gerekeni yapıp 6. R_OK, 7. W_OK bitlerini yaksın,
//boylece her request icin TRACKING_INDEX gibi bir is yukune gerek kalmaz!!! IYI FIKIR!!!
//0. R, 1. W bitleri dısardan set, icerde reset,
//6. R_OK, 7. W_OK bitleri ise icerde set, dirasda reset olucak,
//yani sys_ui ilgili parametrenin STATUS 6.btini sondurup, 0. bitini yakıcak, 6. bitin yanmasını beklicek.
//simple is beautiful!!!



//uint8_t	f_u8_sys_fram__GET_RAM_FRAM_TRANSFER_REQUEST(
//		uint16_t 	f_in_u16__PRMTR_ATTR_LISTS_COMMON_ACQUISITION_INDEX,
//		uint16_t	f_in_u8__TRANSFER_DIRECTION
//		)
//{
//	uint8_t	u8_return_value=0;
//
//	if(f_in_u16__PRMTR_ATTR_LISTS_COMMON_ACQUISITION_INDEX<def_u16_sys_fram__LENGTH_OF_COMMON_ACQUISITION_INDEXES)
//	{
//		if(f_in_u8__TRANSFER_DIRECTION==def_u8_enum__TRANSFER_DIRECTION__READ_FRAM_TO_RAM)
//		{
//			u8_array_sys_fram__TASK_STATUS[f_in_u16__PRMTR_ATTR_LISTS_COMMON_ACQUISITION_INDEX]&=(255-64); 	//reset 	6. R_OK bit, bu silme bir onceki request i yapan baska bir sistemin beklemesini uzatabilir
//			u8_array_sys_fram__TASK_STATUS[f_in_u16__PRMTR_ATTR_LISTS_COMMON_ACQUISITION_INDEX]|=1;			//set 		0. R
//		}
//		else //if(f_in_u8__TRANSFER_DIRECTION==def_u8_enum__TRANSFER_DIRECTION__WRITE_RAM_TO_FRAM)
//		{
//			u8_array_sys_fram__TASK_STATUS[f_in_u16__PRMTR_ATTR_LISTS_COMMON_ACQUISITION_INDEX]&=(255-128); //reset 	7. W_OK bit, bu silme bir onceki request i yapan baska bir sistemin beklemesini uzatabilir
//			u8_array_sys_fram__TASK_STATUS[f_in_u16__PRMTR_ATTR_LISTS_COMMON_ACQUISITION_INDEX]|=2;			//set 		1. W
//		}
//
//		u8_return_value=def_u8_SUCCESS;
//	}
//	else
//	{
//		u8_return_value=def_u8_FAIL;
//	}
//
//	return	u8_return_value;
//}

//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
//***********
//*********
//*******
//*****
//***
//*




void f_sys_fram__LOAD_DEFAULT_VALUES_of__BL_setup(void)
{
//	u8 dummy;
//	u8_array_sys_fram__MEMORY[def_u16_mI__BL_setup__preferences_0]=def_u8_DEFAULT_value_of__BL_setup__preferences_0;
//	u8_array_sys_fram__MEMORY[def_u16_mI__BL_setup__preferences_1]=def_u8_DEFAULT_value_of__BL_setup__preferences_1;
//	u8_array_sys_fram__MEMORY[def_u16_mI__BL_setup__preferences_2]=def_u8_DEFAULT_value_of__BL_setup__preferences_2;
//	u8_array_sys_fram__MEMORY[def_u16_mI__BL_setup__preferences_3]=def_u8_DEFAULT_value_of__BL_setup__preferences_3;
//
//	dummy=f_u8_sys_fram__check_CRC_of__BL_xxx__and_REPAIR_and_return_STATUS(def_u16_mI__BL_setup__preferences_0,def_u16_mI__BL_setup__CRC16_L);
}


void f_sys_fram__HW_INIT(void)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET); 	//set NSS

	HAL_GPIO_WritePin(GPIOC, pin_FRAM_not_WP_Pin, GPIO_PIN_SET); 	//write enabled.
}

//void f_sys_fram__CLEAN__MEMORY(void)
//{
//	u16 i;
//
//	for(i=0;i<def_u16_FRAM_MEMORY_MIRROR_length;i++)
//	{
//		u8_array_sys_fram__MEMORY[i]=0;
//	}
//}

void f_sys_fram__CLEAN__RX_or_TX_DUMMY_BUFFER(void)
{
	u16 i;

	for(i=0;i<def_u16_FRAM_MEMORY_MIRROR_length;i++)
	{
		u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER[i]=0;
	}
}

void f_sys_fram__LOG_FAILURE(void)
{
	u8_sys_fram__main_state__at_FAIL=u8_sys_fram__main_state;
	u8_sys_fram__sub_state__at_FAIL=u8_sys_fram__sub_state;
	u8_sys_fram__sub_2_state__at_FAIL=u8_sys_fram__sub_2_state;
}


//u8 f_u8_sys_fram__check_CRC_of__BL_xxx__and_REPAIR_and_return_STATUS(u16 u16_mI__start,u16 u16_mI__end_CRC_L)
//{
//	u16 check_sum_temp=0x55AA;	//sıfıra sıfır koruması.
//	u16 mI;
//
//	if(
//			(u16_mI__start>=u16_mI__end_CRC_L)
//			||
//			(u16_mI__end_CRC_L>=(def_u16_mI__END-1))
//			)
//	{
//		return 3; //def_u8_refused;
//	}
//
//	for(mI=u16_mI__start;mI<u16_mI__end_CRC_L;mI++)
//	{
//		check_sum_temp+=u8_array_sys_fram__MEMORY[mI];
//	}
//
//	mI=u8_array_sys_fram__MEMORY[u16_mI__end_CRC_L+1];
//	mI<<=8;
//	mI+=u8_array_sys_fram__MEMORY[u16_mI__end_CRC_L];
//
//	if(check_sum_temp==mI)
//	{
//		return def_u8_SUCCESS;
//	}
//	else
//	{
//		//repair;
//		u8_array_sys_fram__MEMORY[u16_mI__end_CRC_L]=(u8)(check_sum_temp);
//		check_sum_temp>>=8;
//		u8_array_sys_fram__MEMORY[u16_mI__end_CRC_L+1]=(u8)(check_sum_temp);
//
//		return def_u8_FAIL;
//	}
//}

void f_sys_fram__STARTUP(void)
{
	u8_sys_fram__main_state=def_u8_sys_fram__main_state__STARTUP;
	u8_sys_fram__sub_state=def_u8_sys_fram__sub_state_of_STARTUP__INIT_HW;

	u8_sys_fram__down_counter_1=100;

	u8_byte_sys_fram__IC_STATUS_REGISTER.byte=0;

	for(u16_sys_fram__i=0;u16_sys_fram__i<def_u16_sys_fram_NUMBER_of_PARAMETERS;u16_sys_fram__i++)
	{
		u8_array_PARAMETER_COMMAND_FLAGS[u16_sys_fram__i].byte=0;
	}
}

void f_sys_fram_MAIN_TASK_1ms_base(void)
{
	//===================================================
	if(u8_sys_fram__down_counter_1>0)
	{
		u8_sys_fram__down_counter_1--;
	}
	//===================================================
	if(u8_sys_fram__down_counter_2>0)
	{
		u8_sys_fram__down_counter_2--;
	}
	//===================================================


	//=================================================================================================
//	if(u8_sys_fram__main_state==def_u8_sys_fram__main_state__WAIT_REQUEST)
//	{
//		//FRAM e read ve write requestler adil paylastirilacak, bi biri bi digeri.
//		if(u8_sys_fram__sub_state==0)
//		{
//			if(u8_sys_fram__sub_2_state==0)
//			{
//				if(def_u1_sys_fram__SIGNAL_IN__copy__RAM_to_FRAM__setup==1)
//				{
//					u16_sys_fram__REQUESTED_LENGTH_of_WRITE_to_FRAM=def_u16_sys_fram__LENGTH_of__BL_setup;
//					u16_sys_fram__REQUESTED_START_ADDRESS_of_WRITE_to_FRAM=def_u16_mI__BL_setup__preferences_0;
//					u8_sys_fram__main_state=def_u8_sys_fram__main_state__WRITE;
//					u8_sys_fram__sub_state=0;
//					u8_sys_fram__sub_2_state=0;
//					def_u1_sys_fram__SIGNAL_OUT__write_RAM_to_FRAM__verify_success__setup=0;
//					def_u1_sys_fram__SIGNAL_IN__copy__RAM_to_FRAM__setup=0;
//
//					u8_sys_fram__main_state_return=def_u8_sys_fram__main_state__WAIT_REQUEST;
//					u8_sys_fram__sub_state_return=u8_sys_fram__sub_state;
//					u8_sys_fram__sub_2_state_return=1;
//				}
//				else	//hicbir write request yoksa:
//				{
//					//return point from
//					u8_sys_fram__sub_state=1;
//					u8_sys_fram__sub_2_state=0;
//
//					//TODO check verification, give error message!!!
//				}
//
//			}
//			else //if(u8_sys_fram__sub_2_state==1)
//			{
//				u8_sys_fram__sub_state=1;
//				u8_sys_fram__sub_2_state=0;
//			}
//		}
//		else
//		{
//			u8_sys_fram__sub_state=0;
//		}
//	}
	//=================================================================================================
	//else
	if(u8_sys_fram__main_state==def_u8_sys_fram__main_state__SCAN_TRANSFER_REQUESTS)
	{

		//u8_array_PARAMETER_COMMAND_FLAGS[0].flags.W_

		for(u16_sys_fram__i=0;u16_sys_fram__i<def_u16_sys_fram_NUMBER_of_PARAMETERS;u16_sys_fram__i++)
		{

			if(u8_array_PARAMETER_COMMAND_FLAGS[u16_sys_fram__i].flags.R_REQUEST==1)
			{
				u16_sys_fram__CAPTURED_COMMAND_REQUEST__TABLE_INDEX=u16_sys_fram__i; 	//capture request index!!!

				//read oncelikli
				u8_sys_fram__main_state=def_u8_sys_fram__main_state__READ;
				u8_sys_fram__sub_state=0;
				u8_sys_fram__sub_2_state=0;

				u8_sys_fram__main_state_return=def_u8_sys_fram__main_state__SCAN_TRANSFER_REQUESTS;
				//u8_sys_fram__sub_state_return;
				//u8_sys_fram__sub_2_state_return;

				u8_array_PARAMETER_COMMAND_FLAGS[u16_sys_fram__CAPTURED_COMMAND_REQUEST__TABLE_INDEX].flags.R_ERROR=0;
				u8_array_PARAMETER_COMMAND_FLAGS[u16_sys_fram__CAPTURED_COMMAND_REQUEST__TABLE_INDEX].flags.R_OK=0;

				u16_sys_fram__i=def_u16_sys_fram_NUMBER_of_PARAMETERS;	//exit from for loop
			}
			else if(u8_array_PARAMETER_COMMAND_FLAGS[u16_sys_fram__i].flags.W_REQUEST==1)
			{
				u16_sys_fram__CAPTURED_COMMAND_REQUEST__TABLE_INDEX=u16_sys_fram__i; 	//capture request index!!!

				//write
				u8_sys_fram__main_state=def_u8_sys_fram__main_state__WRITE;
				u8_sys_fram__sub_state=def_u8_sys_fram__sub_state_of_WRITE__WREN_Set_write_enable_latch;
				u8_sys_fram__sub_2_state=0;

				u8_sys_fram__main_state_return=def_u8_sys_fram__main_state__SCAN_TRANSFER_REQUESTS;
				//u8_sys_fram__sub_state_return;
				//u8_sys_fram__sub_2_state_return;

				u8_array_PARAMETER_COMMAND_FLAGS[u16_sys_fram__CAPTURED_COMMAND_REQUEST__TABLE_INDEX].flags.W_ERROR=0;
				u8_array_PARAMETER_COMMAND_FLAGS[u16_sys_fram__CAPTURED_COMMAND_REQUEST__TABLE_INDEX].flags.W_OK=0;

				u16_sys_fram__i=def_u16_sys_fram_NUMBER_of_PARAMETERS;	//exit from for loop
			}

		}
		//toplam startup "u32_1ms_measure_counter	uint32_t	411"
		if(u8_sys_fram__main_state==def_u8_sys_fram__main_state__SCAN_TRANSFER_REQUESTS)		//state ayni, senkronize olmus ram rom
		{
			if(def_u1_sys_fram__SIGNAL_OUT__STARTUP_READ__FRAM_to_RAM__READY==0)
			{	//21 parametre read "u32_1ms_measure_counter	uint32_t	105	", parametre basina 5 ms, yeterli!!!
				def_u1_sys_fram__SIGNAL_OUT__STARTUP_READ__FRAM_to_RAM__READY=1;	//ust sistemlerin bekletilmesi bu parametre ile yapılacak!!!
			}
		}

	}
	//=================================================================================================
	else if(u8_sys_fram__main_state==def_u8_sys_fram__main_state__READ)
	{
		if(u8_sys_fram__sub_2_state==0)
		{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); 	//reset NSS
			u8_sys_fram_flag_FRAM_SPI_DMA_TRANSECTION_COMPLETED=0;

			//FRAM COMMAND:
			u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER[0]=def_u8_sys_fram__Opcode__READ_Read_memory_data;

			//FRAM ADDRESS:
			u16_sys_fram__temp_1=PARAMETER_TABLE[u16_sys_fram__CAPTURED_COMMAND_REQUEST__TABLE_INDEX].u16_FRAM_ADDRESS;

			//adress bit ittirme.
			if(u16_sys_fram__temp_1>255)
			{
				u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER[0]|=0x08; //bit 3 = address bit 8
			}
			u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER[1]=(u8)(u16_sys_fram__temp_1);


			//HAL_StatusTypeDef HAL_SPI_TransmitReceive_DMA(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size)
			if(HAL_SPI_TransmitReceive_DMA(&hspi1, (uint8_t*)u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER, (uint8_t *)u8_array_sys_fram__spi_RX_BUF, 2) != HAL_OK)
			{
				// Transfer error in transmission process
				//Error_Handler();
				f_sys_fram__LOG_FAILURE();
				u8_sys_fram__main_state=def_u8_sys_fram__main_state__FAIL;
			}
			else
			{
				u8_sys_fram__sub_2_state=1;
				u8_sys_fram__down_counter_1=100;
			}
		}
		else if(u8_sys_fram__sub_2_state==1)
		{
			if(u8_sys_fram__down_counter_1==0)
			{
				//failed at spi transection!!!
				//todo sys_fram: log failure
				f_sys_fram__LOG_FAILURE();
				u8_sys_fram__main_state=def_u8_sys_fram__main_state__FAIL;
			}
			else if(u8_sys_fram_flag_FRAM_SPI_DMA_TRANSECTION_COMPLETED==1)
			{
				//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET); 	//set NSS
				u8_sys_fram__sub_state=def_u8_sys_fram__sub_state_of_WRITE__verify_data;
				u8_sys_fram__sub_2_state=2;
			}
		}
		else if(u8_sys_fram__sub_2_state==2)
		{
			//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); 	//reset NSS
			u8_sys_fram_flag_FRAM_SPI_DMA_TRANSECTION_COMPLETED=0;

			f_sys_fram__CLEAN__RX_or_TX_DUMMY_BUFFER();

			//HAL_StatusTypeDef HAL_SPI_TransmitReceive_DMA(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size)
			if(
					HAL_SPI_TransmitReceive_DMA(&hspi1,
							(uint8_t *)(u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER),
							(uint8_t *)(PARAMETER_TABLE[u16_sys_fram__CAPTURED_COMMAND_REQUEST__TABLE_INDEX].u8_ptr_RAM_ADDRESS),
							(uint16_t )(PARAMETER_TABLE[u16_sys_fram__CAPTURED_COMMAND_REQUEST__TABLE_INDEX].u16_BYTE_LENGTH)) != HAL_OK)
			{
				// Transfer error in transmission process
				//Error_Handler();
				f_sys_fram__LOG_FAILURE();
				u8_sys_fram__main_state=def_u8_sys_fram__main_state__FAIL;
			}
			else
			{
				u8_sys_fram__sub_2_state=3;
				u8_sys_fram__down_counter_1=100;
			}
		}
		else if(u8_sys_fram__sub_2_state==3)
		{
			if(u8_sys_fram__down_counter_1==0)
			{
				//failed at spi transection!!!
				//todo sys_fram: log failure
				f_sys_fram__LOG_FAILURE();
				u8_sys_fram__main_state=def_u8_sys_fram__main_state__FAIL;
			}
			else if(u8_sys_fram_flag_FRAM_SPI_DMA_TRANSECTION_COMPLETED==1)
			{
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET); 	//set NSS

				u8_array_PARAMETER_COMMAND_FLAGS[u16_sys_fram__CAPTURED_COMMAND_REQUEST__TABLE_INDEX].flags.R_OK=1; 		//R_OK signal pulled high
				u8_array_PARAMETER_COMMAND_FLAGS[u16_sys_fram__CAPTURED_COMMAND_REQUEST__TABLE_INDEX].flags.R_REQUEST=0; 	//R signal pulled low

				u8_sys_fram__main_state=u8_sys_fram__main_state_return;
				u8_sys_fram__sub_state=u8_sys_fram__sub_state_return;
				u8_sys_fram__sub_2_state=u8_sys_fram__sub_2_state_return;
			}
		}

	}
	//=================================================================================================
	else if(u8_sys_fram__main_state==def_u8_sys_fram__main_state__WRITE)
	{

		if(u8_sys_fram__sub_state==def_u8_sys_fram__sub_state_of_WRITE__WREN_Set_write_enable_latch)
		{
			if(u8_sys_fram__sub_2_state==0)
			{
//				if(u8_sys_fram__down_counter_1==0)
//				{
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); 	//reset NSS
					u8_sys_fram_flag_FRAM_SPI_DMA_TRANSECTION_COMPLETED=0;

					u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER[0]=def_u8_sys_fram__Opcode__WREN_Set_write_enable_latch;

					//HAL_StatusTypeDef HAL_SPI_TransmitReceive_DMA(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size)
					if(HAL_SPI_TransmitReceive_DMA(&hspi1, (uint8_t*)u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER, (uint8_t *)u8_array_sys_fram__spi_RX_BUF, 1) != HAL_OK)
					{
						// Transfer error in transmission process
						//Error_Handler();
						f_sys_fram__LOG_FAILURE();
						u8_sys_fram__main_state=def_u8_sys_fram__main_state__FAIL;
					}
					else
					{
						u8_sys_fram__sub_2_state=1;
						u8_sys_fram__down_counter_1=100;
					}
//				}
			}
			else if(u8_sys_fram__sub_2_state==1)
			{
				if(u8_sys_fram__down_counter_1==0)
				{
					//failed at spi transection!!!
					//todo sys_fram: log failure
					f_sys_fram__LOG_FAILURE();
					u8_sys_fram__main_state=def_u8_sys_fram__main_state__FAIL;
				}
				else if(u8_sys_fram_flag_FRAM_SPI_DMA_TRANSECTION_COMPLETED==1)
				{
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET); 	//set NSS

					u8_sys_fram__sub_state=def_u8_sys_fram__sub_state_of_WRITE__write_data;
					u8_sys_fram__sub_2_state=0;
				}

			}
		}
		else if(u8_sys_fram__sub_state==def_u8_sys_fram__sub_state_of_WRITE__write_data)
		{
			if(u8_sys_fram__sub_2_state==0)
			{


				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); 	//reset NSS
				u8_sys_fram_flag_FRAM_SPI_DMA_TRANSECTION_COMPLETED=0;

				//FRAM COMMAND:
				u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER[0]=def_u8_sys_fram__Opcode__WRITE_Write_memory_data;

				//FRAM ADDRESS:
				u16_sys_fram__temp_1=PARAMETER_TABLE[u16_sys_fram__CAPTURED_COMMAND_REQUEST__TABLE_INDEX].u16_FRAM_ADDRESS;

				//adress bit ittirme.
				if(u16_sys_fram__temp_1>255)
				{
					u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER[0]|=0x08; //bit 3 = address bit 8
				}
				u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER[1]=(u8)(u16_sys_fram__temp_1);


				//HAL_StatusTypeDef HAL_SPI_TransmitReceive_DMA(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size)
				if(HAL_SPI_TransmitReceive_DMA(&hspi1, (uint8_t*)u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER, (uint8_t *)u8_array_sys_fram__spi_RX_BUF, 2) != HAL_OK)
				{
					// Transfer error in transmission process
					//Error_Handler();
					f_sys_fram__LOG_FAILURE();
					u8_sys_fram__main_state=def_u8_sys_fram__main_state__FAIL;
				}
				else
				{
					u8_sys_fram__sub_2_state=1;
					u8_sys_fram__down_counter_1=100;
				}
			}
			else if(u8_sys_fram__sub_2_state==1)
			{
				if(u8_sys_fram__down_counter_1==0)
				{
					//failed at spi transection!!!
					//todo sys_fram: log failure
					f_sys_fram__LOG_FAILURE();
					u8_sys_fram__main_state=def_u8_sys_fram__main_state__FAIL;
				}
				else if(u8_sys_fram_flag_FRAM_SPI_DMA_TRANSECTION_COMPLETED==1)
				{
					//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET); 	//set NSS
					u8_sys_fram__sub_2_state=2;
				}
			}
			else if(u8_sys_fram__sub_2_state==2)
			{
				//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); 	//reset NSS
				u8_sys_fram_flag_FRAM_SPI_DMA_TRANSECTION_COMPLETED=0;


				//HAL_StatusTypeDef HAL_SPI_TransmitReceive_DMA(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size)
				if(
						HAL_SPI_TransmitReceive_DMA(&hspi1,
								(uint8_t *)(PARAMETER_TABLE[u16_sys_fram__CAPTURED_COMMAND_REQUEST__TABLE_INDEX].u8_ptr_RAM_ADDRESS),
								(uint8_t *)u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER,
								(uint16_t )(PARAMETER_TABLE[u16_sys_fram__CAPTURED_COMMAND_REQUEST__TABLE_INDEX].u16_BYTE_LENGTH)) != HAL_OK)
				{
					// Transfer error in transmission process
					//Error_Handler();
					f_sys_fram__LOG_FAILURE();
					u8_sys_fram__main_state=def_u8_sys_fram__main_state__FAIL;
				}
				else
				{
					u8_sys_fram__sub_2_state=3;
					u8_sys_fram__down_counter_1=100;
				}
			}
			else if(u8_sys_fram__sub_2_state==3)
			{
				if(u8_sys_fram__down_counter_1==0)
				{
					//failed at spi transection!!!
					//todo sys_fram: log failure
					f_sys_fram__LOG_FAILURE();
					u8_sys_fram__main_state=def_u8_sys_fram__main_state__FAIL;
				}
				else if(u8_sys_fram_flag_FRAM_SPI_DMA_TRANSECTION_COMPLETED==1)
				{
					if((uint16_t )(PARAMETER_TABLE[u16_sys_fram__CAPTURED_COMMAND_REQUEST__TABLE_INDEX].u16_BYTE_LENGTH)<=def_u16_FRAM_RX_BUF_length)
					{
						//verify buffer "u8_array_sys_fram__spi_RX_BUF" a bağımlı.
						HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET); 	//set NSS
						u8_sys_fram__sub_state=def_u8_sys_fram__sub_state_of_WRITE__verify_data;
						u8_sys_fram__sub_2_state=0;
					}
					else
					{
						f_sys_fram__LOG_FAILURE();
						u8_sys_fram__main_state=def_u8_sys_fram__main_state__FAIL;
					}
				}
			}
		}
		else //if(u8_sys_fram__sub_state==def_u8_sys_fram__sub_state_of_WRITE__verify_data)
		{
			if(u8_sys_fram__sub_2_state==0)
			{
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); 	//reset NSS
				u8_sys_fram_flag_FRAM_SPI_DMA_TRANSECTION_COMPLETED=0;

				//FRAM COMMAND:
				u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER[0]=def_u8_sys_fram__Opcode__READ_Read_memory_data;

				//FRAM ADDRESS:
				u16_sys_fram__temp_1=PARAMETER_TABLE[u16_sys_fram__CAPTURED_COMMAND_REQUEST__TABLE_INDEX].u16_FRAM_ADDRESS;

				//adress bit ittirme.
				if(u16_sys_fram__temp_1>255)
				{
					u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER[0]|=0x08; //bit 3 = address bit 8
				}
				u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER[1]=(u8)(u16_sys_fram__temp_1);


				//HAL_StatusTypeDef HAL_SPI_TransmitReceive_DMA(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size)
				if(HAL_SPI_TransmitReceive_DMA(&hspi1, (uint8_t*)u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER, (uint8_t *)u8_array_sys_fram__spi_RX_BUF, 2) != HAL_OK)
				{
					// Transfer error in transmission process
					//Error_Handler();
					f_sys_fram__LOG_FAILURE();
					u8_sys_fram__main_state=def_u8_sys_fram__main_state__FAIL;
				}
				else
				{
					u8_sys_fram__sub_2_state=1;
					u8_sys_fram__down_counter_1=100;
				}
			}
			else if(u8_sys_fram__sub_2_state==1)
			{
				if(u8_sys_fram__down_counter_1==0)
				{
					//failed at spi transection!!!
					//todo sys_fram: log failure
					f_sys_fram__LOG_FAILURE();
					u8_sys_fram__main_state=def_u8_sys_fram__main_state__FAIL;
				}
				else if(u8_sys_fram_flag_FRAM_SPI_DMA_TRANSECTION_COMPLETED==1)
				{
					//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET); 	//set NSS
					u8_sys_fram__sub_state=def_u8_sys_fram__sub_state_of_WRITE__verify_data;
					u8_sys_fram__sub_2_state=2;
				}
			}
			else if(u8_sys_fram__sub_2_state==2)
			{
				//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); 	//reset NSS
				u8_sys_fram_flag_FRAM_SPI_DMA_TRANSECTION_COMPLETED=0;

				f_sys_fram__CLEAN__RX_or_TX_DUMMY_BUFFER();

				//HAL_StatusTypeDef HAL_SPI_TransmitReceive_DMA(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size)
				if(
						HAL_SPI_TransmitReceive_DMA(&hspi1,
								(uint8_t *)(u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER),
								(uint8_t *)(u8_array_sys_fram__spi_RX_BUF),
								(uint16_t )(PARAMETER_TABLE[u16_sys_fram__CAPTURED_COMMAND_REQUEST__TABLE_INDEX].u16_BYTE_LENGTH)) != HAL_OK)
				{
					// Transfer error in transmission process
					//Error_Handler();
					f_sys_fram__LOG_FAILURE();
					u8_sys_fram__main_state=def_u8_sys_fram__main_state__FAIL;
				}
				else
				{
					u8_sys_fram__sub_2_state=3;
					u8_sys_fram__down_counter_1=100;
				}
			}
			else if(u8_sys_fram__sub_2_state==3)
			{
				if(u8_sys_fram__down_counter_1==0)
				{
					//failed at spi transection!!!
					//todo sys_fram: log failure
					f_sys_fram__LOG_FAILURE();
					u8_sys_fram__main_state=def_u8_sys_fram__main_state__FAIL;
				}
				else if(u8_sys_fram_flag_FRAM_SPI_DMA_TRANSECTION_COMPLETED==1)
				{
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET); 	//set NSS

					//compare R&W arrays
					u8_sys_fram__temp_1=1;
					//u16_sys_fram__j=u16_sys_fram__REQUESTED_START_ADDRESS_of_WRITE_to_FRAM;
					u8_ptr_sys_fram__temp_1=(uint8_t *)(PARAMETER_TABLE[u16_sys_fram__CAPTURED_COMMAND_REQUEST__TABLE_INDEX].u8_ptr_RAM_ADDRESS);
					for(u16_sys_fram__i=0;u16_sys_fram__i<(uint16_t )(PARAMETER_TABLE[u16_sys_fram__CAPTURED_COMMAND_REQUEST__TABLE_INDEX].u16_BYTE_LENGTH);u16_sys_fram__i++)
					{
						if(u8_array_sys_fram__spi_RX_BUF[u16_sys_fram__i]!=	*u8_ptr_sys_fram__temp_1)
						{
							u8_sys_fram__temp_1=0;
						}
						//u16_sys_fram__j++;
						u8_ptr_sys_fram__temp_1++;
					}

					if(u8_sys_fram__temp_1==1)
					{
						u8_array_PARAMETER_COMMAND_FLAGS[u16_sys_fram__CAPTURED_COMMAND_REQUEST__TABLE_INDEX].flags.W_OK=1; 		//W_OK signal pulled high
						u8_array_PARAMETER_COMMAND_FLAGS[u16_sys_fram__CAPTURED_COMMAND_REQUEST__TABLE_INDEX].flags.W_REQUEST=0; 	//W signal pulled low
					}

					u8_sys_fram__main_state=u8_sys_fram__main_state_return;
					u8_sys_fram__sub_state=u8_sys_fram__sub_state_return;
					u8_sys_fram__sub_2_state=u8_sys_fram__sub_2_state_return;
				}
			}



		}
	}

	//=================================================================================================
	else if(u8_sys_fram__main_state==def_u8_sys_fram__main_state__READ_STATUS_and_RETURN)
	{
		if(u8_sys_fram__sub_state==0)
		{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); 	//reset NSS
			u8_sys_fram_flag_FRAM_SPI_DMA_TRANSECTION_COMPLETED=0;

			u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER[0]=def_u8_sys_fram__Opcode__RDSR_Read_Status_Register;

			//HAL_StatusTypeDef HAL_SPI_TransmitReceive_DMA(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size)
			if(HAL_SPI_TransmitReceive_DMA(&hspi1, (uint8_t*)u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER, (uint8_t *)u8_array_sys_fram__spi_RX_BUF, 1) != HAL_OK)
			{
				// Transfer error in transmission process
				//Error_Handler();
				f_sys_fram__LOG_FAILURE();
				u8_sys_fram__main_state=def_u8_sys_fram__main_state__FAIL;
			}
			else
			{
				u8_sys_fram__sub_state=1;
				u8_sys_fram__down_counter_1=100;
			}
		}
		else if(u8_sys_fram__sub_state==1)
		{
			if(u8_sys_fram__down_counter_1==0)
			{
				//failed at spi transection!!!
				//todo sys_fram: log failure
				f_sys_fram__LOG_FAILURE();
				u8_sys_fram__main_state=def_u8_sys_fram__main_state__FAIL;
			}
			else if(u8_sys_fram_flag_FRAM_SPI_DMA_TRANSECTION_COMPLETED==1)
			{
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET); 	//set NSS

				u8_byte_sys_fram__IC_STATUS_REGISTER.byte=u8_array_sys_fram__spi_RX_BUF[1];
				u8_sys_fram__main_state=u8_sys_fram__main_state_return;
				u8_sys_fram__sub_state=u8_sys_fram__sub_state_return;
				u8_sys_fram__sub_2_state=u8_sys_fram__sub_2_state_return;
			}
		}

	}	//end of "if(u8_sys_fram__main_state==def_u8_sys_fram__main_state__READ_STATUS_and_RETURN)"
	//=================================================================================================
	else if(u8_sys_fram__main_state==def_u8_sys_fram__main_state__STARTUP)
	{
		if(u8_sys_fram__sub_state==def_u8_sys_fram__sub_state_of_STARTUP__INIT_HW)
		{
			if(u8_sys_fram__down_counter_1==0)
			{
				f_sys_fram__HW_INIT();

				u8_sys_fram__sub_state=def_u8_sys_fram__sub_state_of_STARTUP__WREN_Set_write_enable_latch;
				u8_sys_fram__sub_2_state=0;
				u8_sys_fram__down_counter_1=100;
			}
		}
		else if(u8_sys_fram__sub_state==def_u8_sys_fram__sub_state_of_STARTUP__WREN_Set_write_enable_latch)
		{
			if(u8_sys_fram__sub_2_state==0)
			{
				if(u8_sys_fram__down_counter_1==0)
				{
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); 	//reset NSS
					u8_sys_fram_flag_FRAM_SPI_DMA_TRANSECTION_COMPLETED=0;

					u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER[0]=def_u8_sys_fram__Opcode__WREN_Set_write_enable_latch;

					//HAL_StatusTypeDef HAL_SPI_TransmitReceive_DMA(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size)
					if(HAL_SPI_TransmitReceive_DMA(&hspi1, (uint8_t*)u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER, (uint8_t *)u8_array_sys_fram__spi_RX_BUF, 1) != HAL_OK)
					{
						// Transfer error in transmission process
						//Error_Handler();
						f_sys_fram__LOG_FAILURE();
						u8_sys_fram__main_state=def_u8_sys_fram__main_state__FAIL;
					}
					else
					{
						u8_sys_fram__sub_2_state=1;
						u8_sys_fram__down_counter_1=100;
					}
				}
			}
			else if(u8_sys_fram__sub_2_state==1)
			{
				if(u8_sys_fram__down_counter_1==0)
				{
					//failed at spi transection!!!
					//todo sys_fram: log failure
					f_sys_fram__LOG_FAILURE();
					u8_sys_fram__main_state=def_u8_sys_fram__main_state__FAIL;
				}
				else if(u8_sys_fram_flag_FRAM_SPI_DMA_TRANSECTION_COMPLETED==1)
				{
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET); 	//set NSS

					u8_sys_fram__sub_state=def_u8_sys_fram__sub_state_of_STARTUP__WRSR_Write_Status_Register;
					u8_sys_fram__sub_2_state=0;
				}

			}

		}
		else if(u8_sys_fram__sub_state==def_u8_sys_fram__sub_state_of_STARTUP__WRSR_Write_Status_Register)
		{
			if(u8_sys_fram__sub_2_state==0)
			{
				if(u8_sys_fram__down_counter_1==0)
				{
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); 	//reset NSS
					u8_sys_fram_flag_FRAM_SPI_DMA_TRANSECTION_COMPLETED=0;

					u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER[0]=def_u8_sys_fram__Opcode__WRSR_Write_Status_Register;
					u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER[1]=0;

					//HAL_StatusTypeDef HAL_SPI_TransmitReceive_DMA(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size)
					if(HAL_SPI_TransmitReceive_DMA(&hspi1, (uint8_t*)u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER, (uint8_t *)u8_array_sys_fram__spi_RX_BUF, 2) != HAL_OK)
					{
						// Transfer error in transmission process
						//Error_Handler();
						f_sys_fram__LOG_FAILURE();
						u8_sys_fram__main_state=def_u8_sys_fram__main_state__FAIL;
					}
					else
					{
						u8_sys_fram__sub_2_state=1;
						u8_sys_fram__down_counter_1=100;
					}
				}
			}
			else if(u8_sys_fram__sub_2_state==1)
			{
				if(u8_sys_fram__down_counter_1==0)
				{
					//failed at spi transection!!!
					//todo sys_fram: log failure
					f_sys_fram__LOG_FAILURE();
					u8_sys_fram__main_state=def_u8_sys_fram__main_state__FAIL;
				}
				else if(u8_sys_fram_flag_FRAM_SPI_DMA_TRANSECTION_COMPLETED==1)
				{
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET); 	//set NSS

					//read status & return here.
					u8_sys_fram__main_state=def_u8_sys_fram__main_state__READ_STATUS_and_RETURN;
					u8_sys_fram__sub_state=0;
					u8_sys_fram__sub_2_state=0;

					u8_sys_fram__main_state_return=def_u8_sys_fram__main_state__STARTUP;
					u8_sys_fram__sub_state_return=def_u8_sys_fram__sub_state_of_STARTUP__check_status_register;
					u8_sys_fram__sub_2_state_return=0;
				}
			}
		}
		else if(u8_sys_fram__sub_state==def_u8_sys_fram__sub_state_of_STARTUP__check_status_register)
		{
			if(u8_byte_sys_fram__IC_STATUS_REGISTER.byte==0)  	//sıfır yazıldı, sıfır bekleniyor. (hersey unprotected).
			{
				u8_sys_fram__sub_state=def_u8_sys_fram__sub_state_of_STARTUP__test_read_inc_write_read;
				u8_sys_fram__sub_2_state=0;
			}
			else
			{
				f_sys_fram__LOG_FAILURE();
				u8_sys_fram__main_state=def_u8_sys_fram__main_state__FAIL;
			}
		}
		else if(u8_sys_fram__sub_state==def_u8_sys_fram__sub_state_of_STARTUP__test_read_inc_write_read)
		{
			if(u8_sys_fram__sub_2_state==0)
			{
				if(u8_sys_fram__down_counter_1==0)
				{
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); 	//reset NSS
					u8_sys_fram_flag_FRAM_SPI_DMA_TRANSECTION_COMPLETED=0;

					u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER[0]=def_u8_sys_fram__Opcode__READ_Read_memory_data;
					u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER[1]=0;
					u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER[2]=0;

					//HAL_StatusTypeDef HAL_SPI_TransmitReceive_DMA(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size)
					if(HAL_SPI_TransmitReceive_DMA(&hspi1, (uint8_t*)u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER, (uint8_t *)u8_array_sys_fram__spi_RX_BUF, 3) != HAL_OK)
					{
						// Transfer error in transmission process
						//Error_Handler();
						f_sys_fram__LOG_FAILURE();
						u8_sys_fram__main_state=def_u8_sys_fram__main_state__FAIL;
					}
					else
					{
						u8_sys_fram__sub_2_state=1;
						u8_sys_fram__down_counter_1=100;
					}
				}
			}
			else if(u8_sys_fram__sub_2_state==1)
			{
				if(u8_sys_fram__down_counter_1==0)
				{
					//failed at spi transection!!!
					//todo sys_fram: log failure
					f_sys_fram__LOG_FAILURE();
					u8_sys_fram__main_state=def_u8_sys_fram__main_state__FAIL;
				}
				else if(u8_sys_fram_flag_FRAM_SPI_DMA_TRANSECTION_COMPLETED==1)
				{
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET); 	//set NSS
					u8_sys_fram__sub_2_state=2;
				}
			}
			else if(u8_sys_fram__sub_2_state==2)
			{
				u8_array_sys_fram__spi_RX_BUF[2]++;
				u8_sys_fram__temp_1=u8_array_sys_fram__spi_RX_BUF[2];

				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); 	//reset NSS
				u8_sys_fram_flag_FRAM_SPI_DMA_TRANSECTION_COMPLETED=0;

				u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER[0]=def_u8_sys_fram__Opcode__WREN_Set_write_enable_latch;

				//HAL_StatusTypeDef HAL_SPI_TransmitReceive_DMA(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size)
				if(HAL_SPI_TransmitReceive_DMA(&hspi1, (uint8_t*)u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER, (uint8_t *)u8_array_sys_fram__spi_RX_BUF, 1) != HAL_OK)
				{
					// Transfer error in transmission process
					//Error_Handler();
					f_sys_fram__LOG_FAILURE();
					u8_sys_fram__main_state=def_u8_sys_fram__main_state__FAIL;
				}
				else
				{
					u8_sys_fram__sub_2_state=3;
					u8_sys_fram__down_counter_1=100;
				}
			}
			else if(u8_sys_fram__sub_2_state==3)
			{
				if(u8_sys_fram__down_counter_1==0)
				{
					//failed at spi transection!!!
					//todo sys_fram: log failure
					f_sys_fram__LOG_FAILURE();
					u8_sys_fram__main_state=def_u8_sys_fram__main_state__FAIL;
				}
				else if(u8_sys_fram_flag_FRAM_SPI_DMA_TRANSECTION_COMPLETED==1)
				{
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET); 	//set NSS
					u8_sys_fram__sub_2_state=4;
				}
			}
			else if(u8_sys_fram__sub_2_state==4)
			{
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); 	//reset NSS
				u8_sys_fram_flag_FRAM_SPI_DMA_TRANSECTION_COMPLETED=0;

				u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER[0]=def_u8_sys_fram__Opcode__WRITE_Write_memory_data;
				u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER[1]=0;
				u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER[2]=u8_sys_fram__temp_1;
//				u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER[3]='A';	//def_u16_mI__device_model_0
//				u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER[4]='C';
//				u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER[5]='S';
//				u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER[6]='3';
//				u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER[7]='4';
//				u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER[8]='0';
//				u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER[9]='1';
//				u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER[10]='0';
//				u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER[11]='2';

				//HAL_StatusTypeDef HAL_SPI_TransmitReceive_DMA(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size)
				//if(HAL_SPI_TransmitReceive_DMA(&hspi1, (uint8_t*)u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER, (uint8_t *)u8_array_sys_fram__spi_RX_BUF, 12) != HAL_OK)
				if(HAL_SPI_TransmitReceive_DMA(&hspi1, (uint8_t*)u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER, (uint8_t *)u8_array_sys_fram__spi_RX_BUF, 3) != HAL_OK)
				{
					// Transfer error in transmission process
					//Error_Handler();
					f_sys_fram__LOG_FAILURE();
					u8_sys_fram__main_state=def_u8_sys_fram__main_state__FAIL;
				}
				else
				{
					u8_sys_fram__sub_2_state=5;
					u8_sys_fram__down_counter_1=100;
				}
			}
			else if(u8_sys_fram__sub_2_state==5)
			{
				if(u8_sys_fram__down_counter_1==0)
				{
					//failed at spi transection!!!
					//todo sys_fram: log failure
					f_sys_fram__LOG_FAILURE();
					u8_sys_fram__main_state=def_u8_sys_fram__main_state__FAIL;
				}
				else if(u8_sys_fram_flag_FRAM_SPI_DMA_TRANSECTION_COMPLETED==1)
				{
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET); 	//set NSS
					u8_sys_fram__sub_2_state=6;
				}
			}
			else if(u8_sys_fram__sub_2_state==6)
			{
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); 	//reset NSS
				u8_sys_fram_flag_FRAM_SPI_DMA_TRANSECTION_COMPLETED=0;

				u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER[0]=def_u8_sys_fram__Opcode__READ_Read_memory_data;
				u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER[1]=0;
				u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER[2]=0;
				u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER[3]=0;
				u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER[4]=0;
				u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER[5]=0;
				u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER[6]=0;
				u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER[7]=0;
				u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER[8]=0;
				u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER[9]=0;

				//HAL_StatusTypeDef HAL_SPI_TransmitReceive_DMA(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size)
				//if(HAL_SPI_TransmitReceive_DMA(&hspi1, (uint8_t*)u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER, (uint8_t *)u8_array_sys_fram__spi_RX_BUF, 12) != HAL_OK)
				if(HAL_SPI_TransmitReceive_DMA(&hspi1, (uint8_t*)u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER, (uint8_t *)u8_array_sys_fram__spi_RX_BUF, 3) != HAL_OK)
				{
					// Transfer error in transmission process
					//Error_Handler();
					f_sys_fram__LOG_FAILURE();
					u8_sys_fram__main_state=def_u8_sys_fram__main_state__FAIL;
				}
				else
				{
					u8_sys_fram__sub_2_state=7;
					u8_sys_fram__down_counter_1=100;
				}
			}
			else if(u8_sys_fram__sub_2_state==7)
			{
				if(u8_sys_fram__down_counter_1==0)
				{
					//failed at spi transection!!!
					//todo sys_fram: log failure
					f_sys_fram__LOG_FAILURE();
					u8_sys_fram__main_state=def_u8_sys_fram__main_state__FAIL;
				}
				else if(u8_sys_fram_flag_FRAM_SPI_DMA_TRANSECTION_COMPLETED==1)
				{
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET); 	//set NSS

					if(
							(u8_sys_fram__temp_1==u8_array_sys_fram__spi_RX_BUF[2]) //&&	//successfull read&increment&write&check
//							('A'==u8_array_sys_fram__spi_RX_BUF[3]) &&
//							('C'==u8_array_sys_fram__spi_RX_BUF[4]) &&
//							('S'==u8_array_sys_fram__spi_RX_BUF[5]) &&
//							('3'==u8_array_sys_fram__spi_RX_BUF[6]) &&
//							('4'==u8_array_sys_fram__spi_RX_BUF[7]) &&
//							('0'==u8_array_sys_fram__spi_RX_BUF[8])
						)
					{
						//u8_sys_fram__main_state=; aman dikkat!!!
						u8_sys_fram__sub_state=def_u8_sys_fram__sub_state_of_STARTUP__FULL_READ__FRAM_to_RAM;
						u8_sys_fram__sub_2_state=0;
					}
					else
					{
						f_sys_fram__LOG_FAILURE();
						u8_sys_fram__main_state=def_u8_sys_fram__main_state__FAIL;
					}
				}
			}
		}

		//*
		//***
		//*****
		//*******
		//*********
		//***********
		//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[

		//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
		//***********
		//*********
		//*******
		//*****
		//***
		//*

		//@@@mark: def_u8_sys_fram__sub_state_of_STARTUP__FULL_READ__FRAM_to_RAM
		else if(u8_sys_fram__sub_state==def_u8_sys_fram__sub_state_of_STARTUP__FULL_READ__FRAM_to_RAM)
		{
			//sadece task flagler islenip SCAN e bırakılacak,
			//fakat bu bitenen kadar bu parametreleri kullanan sistemler bekletilmeli
			//scan in bosa cikmasi ile burada isaretlenen bir parametre silinecek!!!

//			f_u8_sys_fram__GET_RAM_FRAM_TRANSFER_REQUEST(def_u16_enum__PRMTR_ATTR_LISTS_COMMON_ACQUISITION_INDEX__THE_LAST_USAGE_MODE__u8,def_u8_enum__TRANSFER_DIRECTION__READ_FRAM_TO_RAM);
//			f_u8_sys_fram__GET_RAM_FRAM_TRANSFER_REQUEST(def_u16_enum__PRMTR_ATTR_LISTS_COMMON_ACQUISITION_INDEX__POWER_ON_RESET_COUNTER__u8,def_u8_enum__TRANSFER_DIRECTION__READ_FRAM_TO_RAM);


			//butun parametreler ram e kopya.
			//for(u16_sys_fram__i=0;u16_sys_fram__i<def_u16_sys_fram_NUMBER_of_PARAMETERS;u16_sys_fram__i++)	//aman ha sıc olur tanımsız adreslerle!!!
			for(u16_sys_fram__i=0;u16_sys_fram__i<def_u16_sys_fram_NUMBER_of_PARAMETERS;u16_sys_fram__i++)
			{
				u8_array_PARAMETER_COMMAND_FLAGS[u16_sys_fram__i].byte=0;
				u8_array_PARAMETER_COMMAND_FLAGS[u16_sys_fram__i].flags.R_REQUEST=1;
			}

			def_u1_sys_fram__SIGNAL_OUT__STARTUP_READ__FRAM_to_RAM__READY=0;
			u8_sys_fram__main_state=def_u8_sys_fram__main_state__SCAN_TRANSFER_REQUESTS;

		}

		//*
		//***
		//*****
		//*******
		//*********
		//***********
		//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
#ifdef depreciated_STARTUP_READ
		//memory link artık linear degil!!! eskisi IPAL oldu!!!
		else if(u8_sys_fram__sub_state==def_u8_sys_fram__sub_state_of_STARTUP__FULL_READ__FRAM_to_RAM)
		{
//			if(u8_sys_fram__down_counter_1==0)
//			{
//				u8_sys_fram__sub_state=def_u8_sys_fram__sub_state_of_STARTUP__WRITE_CORRUPTED_MEMORY_BLOCK_WITH_DEFAULTS;
//			}

			if(u8_sys_fram__sub_2_state==0)
			{
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); 	//reset NSS
				u8_sys_fram_flag_FRAM_SPI_DMA_TRANSECTION_COMPLETED=0;

				u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER[0]=def_u8_sys_fram__Opcode__READ_Read_memory_data;
				u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER[1]=0;

				//HAL_StatusTypeDef HAL_SPI_TransmitReceive_DMA(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size)
				if(HAL_SPI_TransmitReceive_DMA(&hspi1, (uint8_t*)u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER, (uint8_t *)u8_array_sys_fram__spi_RX_BUF, 2) != HAL_OK)
				{
					// Transfer error in transmission process
					//Error_Handler();
					f_sys_fram__LOG_FAILURE();
					u8_sys_fram__main_state=def_u8_sys_fram__main_state__FAIL;
				}
				else
				{
					u8_sys_fram__sub_2_state=1;
					u8_sys_fram__down_counter_1=100;
				}
			}
			else if(u8_sys_fram__sub_2_state==1)
			{
				if(u8_sys_fram__down_counter_1==0)
				{
					//failed at spi transection!!!
					//todo sys_fram: log failure
					f_sys_fram__LOG_FAILURE();
					u8_sys_fram__main_state=def_u8_sys_fram__main_state__FAIL;
				}
				else if(u8_sys_fram_flag_FRAM_SPI_DMA_TRANSECTION_COMPLETED==1)
				{
					//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET); 	//set NSS  >>> komut devam ediyor!!! NSS kalicak!!!
					u8_sys_fram__sub_2_state=2;
				}
			}
			else if(u8_sys_fram__sub_2_state==2)
			{
				//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); 	//reset NSS >>> zaten yapılık geldi!!!
				u8_sys_fram_flag_FRAM_SPI_DMA_TRANSECTION_COMPLETED=0;

				f_sys_fram__CLEAN__RX_or_TX_DUMMY_BUFFER();
				f_sys_fram__CLEAN__MEMORY();

				//HAL_StatusTypeDef HAL_SPI_TransmitReceive_DMA(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size)
				if(HAL_SPI_TransmitReceive_DMA(&hspi1, (uint8_t*)u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER, (uint8_t *)u8_array_sys_fram__MEMORY, def_u16_FRAM_MEMORY_MIRROR_length) != HAL_OK)
				{
					// Transfer error in transmission process
					//Error_Handler();
					f_sys_fram__LOG_FAILURE();
					u8_sys_fram__main_state=def_u8_sys_fram__main_state__FAIL;
				}
				else
				{
					u8_sys_fram__sub_2_state=3;
					u8_sys_fram__down_counter_1=200;
				}
			}
			else if(u8_sys_fram__sub_2_state==3)
			{
				if(u8_sys_fram__down_counter_1==0)
				{
					//failed at spi transection!!!
					//todo sys_fram: log failure
					f_sys_fram__LOG_FAILURE();
					u8_sys_fram__main_state=def_u8_sys_fram__main_state__FAIL;
				}
				else if(u8_sys_fram_flag_FRAM_SPI_DMA_TRANSECTION_COMPLETED==1)
				{
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET); 	//set NSS
					u8_sys_fram__sub_state=def_u8_sys_fram__sub_state_of_STARTUP__CONTROL_MEMORY_BLOCK_CHECKSUMS;
					u8_sys_fram__sub_2_state=0;
				}
			}
		}
		else if(u8_sys_fram__sub_state==def_u8_sys_fram__sub_state_of_STARTUP__CONTROL_MEMORY_BLOCK_CHECKSUMS)
		{
			if(u8_sys_fram__sub_2_state==0)
			{
				//setup block
				if(f_u8_sys_fram__check_CRC_of__BL_xxx__and_REPAIR_and_return_STATUS(def_u16_mI__BL_setup__preferences_0,def_u16_mI__BL_setup__CRC16_L)!=def_u8_SUCCESS)
				{
					f_sys_fram__LOAD_DEFAULT_VALUES_of__BL_setup();
					def_u1_sys_fram__SIGNAL_IN__copy__RAM_to_FRAM__setup=1;
				}


				//buradan çıkmaya izin vardır, cunku kullanılan RAM degerleri artık guvenilirdir.
				//gerekli olanlarda fram e yazılacaktır.
				//tum sistem FRAM mirrorundan calismaya baslayacaktir.

				u8_sys_fram__main_state=def_u8_sys_fram__main_state__WAIT_REQUEST;
				u8_sys_fram__sub_state=0;
				u8_sys_fram__sub_2_state=0;
			}
		}
#endif

		//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
		//***********
		//*********
		//*******
		//*****
		//***
		//*





//		else
//		{
//			u8_sys_fram__sub_state=def_u8_sys_fram__sub_state_of_STARTUP__INIT_HW;
//		}
	} 	//end of "if(u8_sys_fram__main_state==def_u8_sys_fram__main_state__STARTUP)"
	//=================================================================================================


	//=================================================================================================


	//=================================================================================================


	//=================================================================================================
	else if(u8_sys_fram__main_state==def_u8_sys_fram__main_state__FAIL)
	{
		//while(1); 	//debug trap @ development.

		//TODO burada ust sistemi bilgilendirip beklemek daha mantikli!!!
		f_sys_fram__STARTUP();
	}
	//=================================================================================================

}
