# modules_stm32__sys_fram
stm32 fram driver, non blocking, state machine code module for,  unified parameter table drive for menu

code runs in device "http://www.aac-tr.com/web/asc340" succesfully on stm32f05.
collects requests of ohter code modules and process reuests in order.

after main code calls "f_sys_fram__STARTUP();" code starts run with
periodic call "f_sys_fram_MAIN_TASK_1ms_base();" at main loop.

example request from other modules:

at request state
				u8_array_PARAMETER_COMMAND_FLAGS[u16_sys_ui__CODE_MATCH__INDEX].flags.W_OK=0;
				u8_array_PARAMETER_COMMAND_FLAGS[u16_sys_ui__CODE_MATCH__INDEX].flags.W_REQUEST=1;
next state wait for OK signal:

		else if(u8_sys_ui__sub1_state==3)			//WAIT FRAM WRITE state
		{
			if(u16_sys_ui__down_time_counter_1==0)
			{
				//error
				f_sys_ui__WRITE_MESSAGE_error_TO_L0();
				u16_sys_ui__down_time_counter_1=10;
				u8_sys_ui__sub1_state=4;
			}
			else if(u8_array_PARAMETER_COMMAND_FLAGS[u16_sys_ui__CODE_MATCH__INDEX].flags.W_OK==1)
			{
				//ok
				f_sys_ui__WRITE_MESSAGE_ok_TO_L0();
				u16_sys_ui__down_time_counter_1=10;
				u8_sys_ui__sub1_state=4;
			}
		}

      



