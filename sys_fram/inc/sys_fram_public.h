/*
 * sys_fram_public.h
 *
 *  Created on: Nov 27, 2016
 *      Author: ozgurbas
 */

#ifndef SYS_FRAM_PUBLIC_H_
#define SYS_FRAM_PUBLIC_H_

#include "sys_fram_definitions.h"

extern void f_sys_fram_MAIN_TASK_1ms_base(void);
extern void f_sys_fram__STARTUP(void);


extern const PARAMETER	PARAMETER_TABLE[def_u16_sys_fram_NUMBER_of_PARAMETERS];
extern u8_PARAMETER_COMMAND 	u8_array_PARAMETER_COMMAND_FLAGS[def_u16_sys_fram_NUMBER_of_PARAMETERS];

extern u8_byte u8_byte_sys_fram__SYSTEM_STATUS_REGISTER;

#endif /* SYS_FRAM_PUBLIC_H_ */
