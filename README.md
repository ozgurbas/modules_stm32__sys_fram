# modules_stm32__sys_fram
stm32 fram driver, non blocking, state machine code module for,  unified parameter table drive for menu

code runs in device "http://www.aac-tr.com/web/asc340" succesfully on stm32f05.
collects requests of ohter code modules and process reuests in order.

after main code calls "f_sys_fram__STARTUP();" code starts run with
periodic call "f_sys_fram_MAIN_TASK_1ms_base();" at main loop.

