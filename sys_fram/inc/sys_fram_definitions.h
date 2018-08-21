/*
 * sys_fram_definitions.h
 *
 *  Created on: Nov 27, 2016
 *      Author: ozgurbas
 */

#ifndef SYS_FRAM_DEFINITIONS_H_
#define SYS_FRAM_DEFINITIONS_H_

//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
#define	def_u8_sys_fram__main_state__IDLE										0
#define	def_u8_sys_fram__main_state__STARTUP									1
#define	def_u8_sys_fram__main_state__WAIT_REQUEST								2
#define	def_u8_sys_fram__main_state__READ										3
#define	def_u8_sys_fram__main_state__WRITE										4
#define	def_u8_sys_fram__main_state__ERASING									5
#define	def_u8_sys_fram__main_state__FAIL										6

#define	def_u8_sys_fram__main_state__READ_STATUS_and_RETURN						100

#define	def_u8_sys_fram__main_state__SCAN_TRANSFER_REQUESTS						200

//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
#define	def_u8_sys_fram__sub_state_of_WRITE__WREN_Set_write_enable_latch		0
#define	def_u8_sys_fram__sub_state_of_WRITE__write_data							1
#define	def_u8_sys_fram__sub_state_of_WRITE__verify_data						2
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]


//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
#define	def_u8_sys_fram__sub_state_of_STARTUP__INIT_HW							0
#define	def_u8_sys_fram__sub_state_of_STARTUP__WREN_Set_write_enable_latch		1
#define	def_u8_sys_fram__sub_state_of_STARTUP__WRSR_Write_Status_Register		2
#define	def_u8_sys_fram__sub_state_of_STARTUP__check_status_register			3
#define	def_u8_sys_fram__sub_state_of_STARTUP__test_read_inc_write_read			4

#define	def_u8_sys_fram__sub_state_of_STARTUP__FULL_READ__FRAM_to_RAM			100
#define	def_u8_sys_fram__sub_state_of_STARTUP__CONTROL_MEMORY_BLOCK_CHECKSUMS	101
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]


#include 	"sys_fram_default_vaules.h"


//@@@mark: 000: parametre eklenince arttırılacak def:
#define 	def_u16_sys_fram_NUMBER_of_PARAMETERS			138


typedef struct
{
	uint8_t b0:1;
	uint8_t b1:1;
	uint8_t b2:1;
	uint8_t b3:1;
	uint8_t b4:1;
	uint8_t b5:1;
	uint8_t USER_ACCESSIBLE:1;	//read only parameters de bu bit sıfır olacak
	uint8_t WRITABLE:1;			//user access 1 degilse admin sadece erisebilicek
} type_u8_p_PERMISSIONS;

#define 	def_p_PERM__W				0x80
#define 	def_p_PERM__USER_ACCESS		0x40


typedef struct
{
	const uint8_t 	u8_array_CODE_NAME_l4[4]; 					//ex: "1001" (search name & numeric keyboard name)
	const uint16_t 	u16_2dim_array_DISPLAY_NAMES_16seg[2][5];	//iki dilde displaye yazılacak isim.
	const uint16_t	u16_FRAM_ADDRESS;							//framdeki ardess
	const uint8_t*	u8_ptr_RAM_ADDRESS;							//ramdeki parametrenin ilk byte ının adresi
	const uint16_t 	u16_BYTE_LENGTH;							//byte lenght sıfır ise, bit number devreye girer
	const uint8_t	u8_BIT_NUMBER;
	const uint8_t	u8_TYPE;									//LSB: NOT_SYSTEM or USER parameter,	high nibble variable type( bool, en_dis, yes_no, signed, un signed vs vs
	const int32_t	s32_MIN;
	const int32_t	s32_MAX;
	const int32_t	s32_DEFAULT;
	const uint8_t	u8_DOT_POSITION;
	//const type_u8_p_PERMISSIONS	u8_PERMISSIONS; todo: struct icinde struct constant ilkleme yemedi, sonra bak
	const uint8_t	u8_PERMISSIONS;

	//TODO: bit sayısı ve bit offset ile 1 ile 8 bit arası parametrelerde desteklenebilir.

}PARAMETER;




enum
{
	def_p_type__UNDEFINED,		//guvenlik icin eklendi
	def_p_type__bool,
	def_p_type__yes_no,
	def_p_type__en_dis,
	def_p_type__u8,
	def_p_type__s8,
	def_p_type__u16,
	def_p_type__s16,
	def_p_type__u32,
	def_p_type__s32,

	def_p_type__u8_binary,
};


//PARAMETER_COMMAND_FLAGS
typedef union
{
	uint8_t byte;

	struct
	{
		uint8_t R_ERROR:1;		//bit 0
		uint8_t R_OK:1;
		uint8_t R_BUSY:1;
		uint8_t R_REQUEST:1;
		uint8_t W_ERROR:1;
		uint8_t W_OK:1;
		uint8_t W_BUSY:1;
		uint8_t W_REQUEST:1;	//bit 7
	} flags;


}  u8_PARAMETER_COMMAND;

enum
{
	def_PRM_TABLE_POS__LANGUAGE__u8,							//	{1,0,0,0, 	{ {___D,___I,___L,___ ,___ }, 	{___L,___A,___N,___G,___U}, }, 	def_PRM_TABLE_POS__LANGUAGE__u8,							(uint8_t*)(&u8_sys_ui__nvprm_LANGUAGE),							1,				0,				def_p_type__u8,			0,			1,			1,				255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__USER_PREFERENCES_1,						//	{1,0,0,1, 	{ {___T,___R,___C,___H,___1 }, 	{___P,___R,___F,___R,___1}, }, 	def_PRM_TABLE_POS__USER_PREFERENCES_1,						(uint8_t*)(&u8_sys_ui__nvprm_USER_PREFERENCES_1),				1,				0,				def_p_type__u8_binary,	0,			255,		0,				255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__USER_PREFERENCES_2,						//	{1,0,0,2, 	{ {___T,___R,___C,___H,___2 }, 	{___P,___R,___F,___R,___2}, }, 	def_PRM_TABLE_POS__USER_PREFERENCES_2,						(uint8_t*)(&u8_sys_ui__nvprm_USER_PREFERENCES_2),				1,				0,				def_p_type__u8_binary,	0,			255,		0,				255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__USER_PREFERENCES_3,						//	{1,0,0,3, 	{ {___T,___R,___C,___H,___3 }, 	{___P,___R,___F,___R,___3}, }, 	def_PRM_TABLE_POS__USER_PREFERENCES_3,						(uint8_t*)(&u8_sys_ui__nvprm_USER_PREFERENCES_3),				1,				0,				def_p_type__u8_binary,	0,			255,		0,				255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__USER_PREFERENCES_4,						//	{1,0,0,4, 	{ {___T,___R,___C,___H,___4 }, 	{___P,___R,___F,___R,___4}, }, 	def_PRM_TABLE_POS__USER_PREFERENCES_4,						(uint8_t*)(&u8_sys_ui__nvprm_USER_PREFERENCES_4),				1,				0,				def_p_type__u8_binary,	0,			255,		0,				255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__THE_LAST_USAGE_MODE__u8,					//	{2,0,0,0, 	{ {___S,___N,___M,___O,___D},	{___L,___T,___M,___O,___D}, }, 	def_PRM_TABLE_POS__THE_LAST_USAGE_MODE__u8,					(uint8_t*)(&u8_sys_ui__nvprm_THE_LAST_USAGE_MODE),				1,				0,				def_p_type__u8,			0,			15,			0,				255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__THE_LAST_IO_STATES__u8,					//	{2,0,0,1, 	{ {___S,___N,___ ,___I,___O},	{___L,___T,___ ,___I,___O}, }, 	def_PRM_TABLE_POS__THE_LAST_IO_STATES__u8,					(uint8_t*)(&u8_sys_ui__nvprm_THE_LAST_IO_STATES),				1,				0,				def_p_type__u8_binary,	0,			255,		0,				255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__X__micro_degree__NOW_SEEN__s32_0,		//	{2,0,0,2, 	{ {___O,___N,___C,___,___X},	{___P,___R,___V,___,___X}, }, 	def_FRAM_ADDR__X__micro_degree__NOW_SEEN__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_ABS_POS__X__micro_degree__NOW_SEEN),			4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(0),						},
	def_PRM_TABLE_POS__X__micro_degree__NOW__REAL__s32_0,		//	{2,0,0,3, 	{ {___S,___M,___D,___,___X},	{___N,___O,___W,___,___X}, }, 	def_FRAM_ADDR__X__micro_degree__NOW__REAL__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_ABS_POS__X__micro_degree__NOW__REAL),			4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(0),						},
	def_PRM_TABLE_POS__X__micro_degree__PREVIOUS__SEEN__s32_0,	//	{2,0,0,4, 	{ {___H,___D,___F,___,___X},	{___T,___R,___T,___,___X}, }, 	def_FRAM_ADDR__X__micro_degree__PREVIOUS__SEEN__s32_0,	(uint8_t*)(&s32_sys_ui__nvprm_ABS_POS__X__micro_degree__PREVIOUS__SEEN),	4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(0),						},
	def_PRM_TABLE_POS__IN_1_ACT_CONF_at_POINT_MODE__u8,
	def_PRM_TABLE_POS__IN_2_ACT_CONF_at_POINT_MODE__u8,
	def_PRM_TABLE_POS__IN_3_ACT_CONF_at_POINT_MODE__u8,
	def_PRM_TABLE_POS__IN_4_ACT_CONF_at_POINT_MODE__u8,
	def_PRM_TABLE_POS__IN_1_ACT_CONF_at_JOGG_MODE__u8,
	def_PRM_TABLE_POS__IN_2_ACT_CONF_at_JOGG_MODE__u8,
	def_PRM_TABLE_POS__IN_3_ACT_CONF_at_JOGG_MODE__u8,
	def_PRM_TABLE_POS__IN_4_ACT_CONF_at_JOGG_MODE__u8,
	def_PRM_TABLE_POS__IN_PULSE_TRAIN_MIN__u8,
	def_PRM_TABLE_POS__IN_PULSE_TRAIN_MAX__u8,
	def_PRM_TABLE_POS__L64_ACC_12bits_R_WS__u16_0,				//	{3,0,0,0, 	{ {___H,___Z,___L,___I,___X},	{___A,___C,___C,___,___X}, }, 	def_PRM_TABLE_POS__L64_ACC_12bits_R_WS__u16_0,				(uint8_t*)(&u16_sys_ui__nvprm_L64_ACC_12bits_R_WS),				2,				0,				def_p_type__u16,		0,			10,			0,				255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__L64_DEC_12bits_R_WS__u16_0,				//	{3,0,0,1, 	{ {___Y,___V,___S,___I,___X},	{___D,___E,___C,___,___X}, }, 	def_PRM_TABLE_POS__L64_DEC_12bits_R_WS__u16_0,				(uint8_t*)(&u16_sys_ui__nvprm_L64_DEC_12bits_R_WS),				2,				0,				def_p_type__u16,		0,			10,			0,				255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__L64_MAX_SPEED_10bits_R_WR__u16_0,		//	{3,0,0,2, 	{ {___Y,___K,___S,___H,___X},	{___M,___X,___S,___P,___X}, }, 	def_PRM_TABLE_POS__L64_MAX_SPEED_10bits_R_WR__u16_0,		(uint8_t*)(&u16_sys_ui__nvprm_L64_MAX_SPEED_10bits_R_WR),		2,				0,				def_p_type__u16,		0,			10,			0,				255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__L64_MIN_SPEED_13bits_R_WS__u16_0,		//	{3,0,0,3, 	{ {___D,___S,___K,___H,___X},	{___M,___N,___S,___P,___X}, }, 	def_PRM_TABLE_POS__L64_MIN_SPEED_13bits_R_WS__u16_0,		(uint8_t*)(&u16_sys_ui__nvprm_L64_MIN_SPEED_13bits_R_WS),		2,				0,				def_p_type__u16,		0,			10,			0,				255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__L64_FS_SPD_10bits_R_WR__u16_0,			//	{3,0,0,4, 	{ {___F,___S,___S,___P,___X},	{___F,___S,___S,___P,___X}, }, 	def_PRM_TABLE_POS__L64_FS_SPD_10bits_R_WR__u16_0,			(uint8_t*)(&u16_sys_ui__nvprm_L64_FS_SPD_10bits_R_WR),			2,				0,				def_p_type__u16,		0,			10,			0,				255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__L64_TVAL_HOLD_7bits_R_WR__u8,			//	{3,0,0,5, 	{ {___T,___T,___M,___A,___X},	{___H,___L,___D,___C,___X}, }, 	def_PRM_TABLE_POS__L64_TVAL_HOLD_7bits_R_WR__u8,			(uint8_t*)(&u8_sys_ui__nvprm_L64_TVAL_HOLD_7bits_R_WR),			1,				0,				def_p_type__u8,			0,			10,			0,				255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__L64_TVAL_RUN_7bits_R_WR__u8,				//	{3,0,0,6, 	{ {___C,___L,___S,___A,___X},	{___R,___U,___N,___C,___X}, }, 	def_PRM_TABLE_POS__L64_TVAL_RUN_7bits_R_WR__u8,				(uint8_t*)(&u8_sys_ui__nvprm_L64_TVAL_RUN_7bits_R_WR),			1,				0,				def_p_type__u8,			0,			10,			0,				255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__L64_TVAL_ACC_7bits_R_WR__u8,				//	{3,0,0,7, 	{ {___H,___Z,___L,___A,___X},	{___A,___C,___C,___C,___X}, }, 	def_PRM_TABLE_POS__L64_TVAL_ACC_7bits_R_WR__u8,				(uint8_t*)(&u8_sys_ui__nvprm_L64_TVAL_ACC_7bits_R_WR),			1,				0,				def_p_type__u8,			0,			10,			0,				255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__L64_TVAL_DEC_7bits_R_WR__u8,				//	{3,0,0,8, 	{ {___Y,___V,___S,___A,___X },	{___D,___E,___C,___C,___X}, }, 	def_PRM_TABLE_POS__L64_TVAL_DEC_7bits_R_WR__u8,				(uint8_t*)(&u8_sys_ui__nvprm_L64_TVAL_DEC_7bits_R_WR),			1,				0,				def_p_type__u8,			0,			10,			0,				255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__L64_OCD_TH_4bits_R_WR__u8,				//	{3,0,0,9, 	{ {___A,___S,___A,___L,___X},	{___O,___C,___D,___L,___X}, }, 	def_PRM_TABLE_POS__L64_OCD_TH_4bits_R_WR__u8,				(uint8_t*)(&u8_sys_ui__nvprm_L64_OCD_TH_4bits_R_WR),			1,				0,				def_p_type__u8,			0,			10,			0,				255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__L64_ALARM_EN_8bits_R_WS__u8,				//	{3,0,1,0, 	{ {___A,___L,___R,___M,___X},	{___A,___L,___R,___M,___X}, }, 	def_PRM_TABLE_POS__L64_ALARM_EN_8bits_R_WS__u8,				(uint8_t*)(&u8_sys_ui__nvprm_L64_ALARM_EN_8bits_R_WS),			1,				0,				def_p_type__u8_binary,	0,			10,			0,				255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__UNDO_MEMORY_INDEX__u8,					//	{4,0,0,0, 	{ {___G,___H,___I,___N,___D }, 	{___U,___M,___I,___N,___D}, }, 	def_PRM_TABLE_POS__UNDO_MEMORY_INDEX__u8,					(uint8_t*)(&u8_sys_ui__nvprm_UNDO_MEMORY_INDEX__u8),			1,				0,				def_p_type__u8,			0,			4,			0,				255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__UNDO_MEMORY_0_X_POSITION__s32_0,			//	{4,0,0,1, 	{ {___G,___H,___ ,___ ,___1},	{___U,___M,___ ,___ ,___1}, }, 	def_PRM_TABLE_POS__UNDO_MEMORY_0_X_POSITION__s32_0,			(uint8_t*)(&s32_sys_ui__nvprm_UNDO_MEMORY_0_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__UNDO_MEMORY_1_X_POSITION__s32_0,			//	{4,0,0,2, 	{ {___G,___H,___ ,___ ,___2},	{___U,___M,___ ,___ ,___2}, }, 	def_PRM_TABLE_POS__UNDO_MEMORY_1_X_POSITION__s32_0,			(uint8_t*)(&s32_sys_ui__nvprm_UNDO_MEMORY_1_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__UNDO_MEMORY_2_X_POSITION__s32_0,			//	{4,0,0,3, 	{ {___G,___H,___ ,___ ,___3},	{___U,___M,___ ,___ ,___3}, }, 	def_PRM_TABLE_POS__UNDO_MEMORY_2_X_POSITION__s32_0,			(uint8_t*)(&s32_sys_ui__nvprm_UNDO_MEMORY_2_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__UNDO_MEMORY_3_X_POSITION__s32_0,			//	{4,0,0,4, 	{ {___G,___H,___ ,___ ,___4},	{___U,___M,___ ,___ ,___4}, }, 	def_PRM_TABLE_POS__UNDO_MEMORY_3_X_POSITION__s32_0,			(uint8_t*)(&s32_sys_ui__nvprm_UNDO_MEMORY_3_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__UNDO_MEMORY_4_X_POSITION__s32_0,			//	{4,0,0,5, 	{ {___G,___H,___ ,___ ,___5},	{___U,___M,___ ,___ ,___5}, }, 	def_PRM_TABLE_POS__UNDO_MEMORY_4_X_POSITION__s32_0,			(uint8_t*)(&s32_sys_ui__nvprm_UNDO_MEMORY_4_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__DIVISOR_STEP_X__u16_0,					//	{5,0,0,0, 	{ {___D,___V,___A,___D,___M},	{___D,___V,___S,___T,___P}, }, 	def_PRM_TABLE_POS__DIVISOR_STEP_X__u16_0,					(uint8_t*)(&u16_sys_ui__nvprm_DIVISOR_STEP_X__u16_0),			2,				0,				def_p_type__u16,		0,			10,			0,				255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__DIVISOR_DEGREE_X__s32_0,					//	{5,0,0,1, 	{ {___D,___V,___D,___R,___C},	{___D,___V,___D,___G,___R}, }, 	def_PRM_TABLE_POS__DIVISOR_DEGREE_X__s32_0,					(uint8_t*)(&s32_sys_ui__nvprm_DIVISOR_DEGREE_X__s32_0),			4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_1_X_POSITION__s32,		//	{6,0,0,0, 	{ {___N,___H,___ ,___ ,___0},	{___P,___M,___ ,___ ,___0}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_0_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_0_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_2_X_POSITION__s32,		//	{6,0,0,1, 	{ {___N,___H,___ ,___ ,___1},	{___P,___M,___ ,___ ,___1}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_1_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_1_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_3_X_POSITION__s32,		//	{6,0,0,2, 	{ {___N,___H,___ ,___ ,___2},	{___P,___M,___ ,___ ,___2}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_2_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_2_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_4_X_POSITION__s32,		//	{6,0,0,3, 	{ {___N,___H,___ ,___ ,___3},	{___P,___M,___ ,___ ,___3}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_3_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_3_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_5_X_POSITION__s32,		//	{6,0,0,4, 	{ {___N,___H,___ ,___ ,___4},	{___P,___M,___ ,___ ,___4}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_4_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_4_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_6_X_POSITION__s32,		//	{6,0,0,5, 	{ {___N,___H,___ ,___ ,___5},	{___P,___M,___ ,___ ,___5}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_5_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_5_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_7_X_POSITION__s32,		//	{6,0,0,6, 	{ {___N,___H,___ ,___ ,___6},	{___P,___M,___ ,___ ,___6}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_6_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_6_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_8_X_POSITION__s32,		//	{6,0,0,7, 	{ {___N,___H,___ ,___ ,___7},	{___P,___M,___ ,___ ,___7}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_7_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_7_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_9_X_POSITION__s32,		//	{6,0,0,8, 	{ {___N,___H,___ ,___ ,___8},	{___P,___M,___ ,___ ,___8}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_8_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_8_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_10_X_POSITION__s32,		//	{6,0,0,9, 	{ {___N,___H,___ ,___ ,___9},	{___P,___M,___ ,___ ,___9}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_9_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_9_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_11_X_POSITION__s32,		//	{6,0,0,0, 	{ {___N,___H,___ ,___ ,___0},	{___P,___M,___ ,___ ,___0}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_0_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_0_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_12_X_POSITION__s32,		//	{6,0,0,1, 	{ {___N,___H,___ ,___ ,___1},	{___P,___M,___ ,___ ,___1}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_1_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_1_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_13_X_POSITION__s32,		//	{6,0,0,2, 	{ {___N,___H,___ ,___ ,___2},	{___P,___M,___ ,___ ,___2}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_2_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_2_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_14_X_POSITION__s32,		//	{6,0,0,3, 	{ {___N,___H,___ ,___ ,___3},	{___P,___M,___ ,___ ,___3}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_3_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_3_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_15_X_POSITION__s32,		//	{6,0,0,4, 	{ {___N,___H,___ ,___ ,___4},	{___P,___M,___ ,___ ,___4}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_4_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_4_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_16_X_POSITION__s32,		//	{6,0,0,5, 	{ {___N,___H,___ ,___ ,___5},	{___P,___M,___ ,___ ,___5}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_5_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_5_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_17_X_POSITION__s32,		//	{6,0,0,6, 	{ {___N,___H,___ ,___ ,___6},	{___P,___M,___ ,___ ,___6}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_6_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_6_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_18_X_POSITION__s32,		//	{6,0,0,7, 	{ {___N,___H,___ ,___ ,___7},	{___P,___M,___ ,___ ,___7}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_7_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_7_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_19_X_POSITION__s32,		//	{6,0,0,8, 	{ {___N,___H,___ ,___ ,___8},	{___P,___M,___ ,___ ,___8}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_8_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_8_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_20_X_POSITION__s32,		//	{6,0,0,9, 	{ {___N,___H,___ ,___ ,___9},	{___P,___M,___ ,___ ,___9}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_9_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_9_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_21_X_POSITION__s32,		//	{6,0,0,0, 	{ {___N,___H,___ ,___ ,___0},	{___P,___M,___ ,___ ,___0}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_0_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_0_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_22_X_POSITION__s32,		//	{6,0,0,1, 	{ {___N,___H,___ ,___ ,___1},	{___P,___M,___ ,___ ,___1}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_1_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_1_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_23_X_POSITION__s32,		//	{6,0,0,2, 	{ {___N,___H,___ ,___ ,___2},	{___P,___M,___ ,___ ,___2}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_2_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_2_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_24_X_POSITION__s32,		//	{6,0,0,3, 	{ {___N,___H,___ ,___ ,___3},	{___P,___M,___ ,___ ,___3}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_3_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_3_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_25_X_POSITION__s32,		//	{6,0,0,4, 	{ {___N,___H,___ ,___ ,___4},	{___P,___M,___ ,___ ,___4}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_4_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_4_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_26_X_POSITION__s32,		//	{6,0,0,5, 	{ {___N,___H,___ ,___ ,___5},	{___P,___M,___ ,___ ,___5}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_5_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_5_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_27_X_POSITION__s32,		//	{6,0,0,6, 	{ {___N,___H,___ ,___ ,___6},	{___P,___M,___ ,___ ,___6}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_6_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_6_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_28_X_POSITION__s32,		//	{6,0,0,7, 	{ {___N,___H,___ ,___ ,___7},	{___P,___M,___ ,___ ,___7}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_7_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_7_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_29_X_POSITION__s32,		//	{6,0,0,8, 	{ {___N,___H,___ ,___ ,___8},	{___P,___M,___ ,___ ,___8}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_8_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_8_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_30_X_POSITION__s32,		//	{6,0,0,9, 	{ {___N,___H,___ ,___ ,___9},	{___P,___M,___ ,___ ,___9}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_9_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_9_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_31_X_POSITION__s32,		//	{6,0,0,0, 	{ {___N,___H,___ ,___ ,___0},	{___P,___M,___ ,___ ,___0}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_0_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_0_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_32_X_POSITION__s32,		//	{6,0,0,1, 	{ {___N,___H,___ ,___ ,___1},	{___P,___M,___ ,___ ,___1}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_1_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_1_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_33_X_POSITION__s32,		//	{6,0,0,2, 	{ {___N,___H,___ ,___ ,___2},	{___P,___M,___ ,___ ,___2}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_2_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_2_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_34_X_POSITION__s32,		//	{6,0,0,3, 	{ {___N,___H,___ ,___ ,___3},	{___P,___M,___ ,___ ,___3}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_3_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_3_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_35_X_POSITION__s32,		//	{6,0,0,4, 	{ {___N,___H,___ ,___ ,___4},	{___P,___M,___ ,___ ,___4}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_4_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_4_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_36_X_POSITION__s32,		//	{6,0,0,5, 	{ {___N,___H,___ ,___ ,___5},	{___P,___M,___ ,___ ,___5}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_5_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_5_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_37_X_POSITION__s32,		//	{6,0,0,6, 	{ {___N,___H,___ ,___ ,___6},	{___P,___M,___ ,___ ,___6}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_6_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_6_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_38_X_POSITION__s32,		//	{6,0,0,7, 	{ {___N,___H,___ ,___ ,___7},	{___P,___M,___ ,___ ,___7}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_7_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_7_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_39_X_POSITION__s32,		//	{6,0,0,8, 	{ {___N,___H,___ ,___ ,___8},	{___P,___M,___ ,___ ,___8}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_8_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_8_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_40_X_POSITION__s32,		//	{6,0,0,9, 	{ {___N,___H,___ ,___ ,___9},	{___P,___M,___ ,___ ,___9}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_9_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_9_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_41_X_POSITION__s32,		//	{6,0,0,0, 	{ {___N,___H,___ ,___ ,___0},	{___P,___M,___ ,___ ,___0}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_0_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_0_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_42_X_POSITION__s32,		//	{6,0,0,1, 	{ {___N,___H,___ ,___ ,___1},	{___P,___M,___ ,___ ,___1}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_1_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_1_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_43_X_POSITION__s32,		//	{6,0,0,2, 	{ {___N,___H,___ ,___ ,___2},	{___P,___M,___ ,___ ,___2}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_2_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_2_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_44_X_POSITION__s32,		//	{6,0,0,3, 	{ {___N,___H,___ ,___ ,___3},	{___P,___M,___ ,___ ,___3}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_3_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_3_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_45_X_POSITION__s32,		//	{6,0,0,4, 	{ {___N,___H,___ ,___ ,___4},	{___P,___M,___ ,___ ,___4}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_4_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_4_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_46_X_POSITION__s32,		//	{6,0,0,5, 	{ {___N,___H,___ ,___ ,___5},	{___P,___M,___ ,___ ,___5}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_5_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_5_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_47_X_POSITION__s32,		//	{6,0,0,6, 	{ {___N,___H,___ ,___ ,___6},	{___P,___M,___ ,___ ,___6}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_6_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_6_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_48_X_POSITION__s32,		//	{6,0,0,7, 	{ {___N,___H,___ ,___ ,___7},	{___P,___M,___ ,___ ,___7}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_7_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_7_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_49_X_POSITION__s32,		//	{6,0,0,8, 	{ {___N,___H,___ ,___ ,___8},	{___P,___M,___ ,___ ,___8}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_8_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_8_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_50_X_POSITION__s32,		//	{6,0,0,9, 	{ {___N,___H,___ ,___ ,___9},	{___P,___M,___ ,___ ,___9}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_9_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_9_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_51_X_POSITION__s32,		//	{6,0,0,0, 	{ {___N,___H,___ ,___ ,___0},	{___P,___M,___ ,___ ,___0}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_0_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_0_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_52_X_POSITION__s32,		//	{6,0,0,1, 	{ {___N,___H,___ ,___ ,___1},	{___P,___M,___ ,___ ,___1}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_1_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_1_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_53_X_POSITION__s32,		//	{6,0,0,2, 	{ {___N,___H,___ ,___ ,___2},	{___P,___M,___ ,___ ,___2}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_2_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_2_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_54_X_POSITION__s32,		//	{6,0,0,3, 	{ {___N,___H,___ ,___ ,___3},	{___P,___M,___ ,___ ,___3}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_3_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_3_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_55_X_POSITION__s32,		//	{6,0,0,4, 	{ {___N,___H,___ ,___ ,___4},	{___P,___M,___ ,___ ,___4}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_4_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_4_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_56_X_POSITION__s32,		//	{6,0,0,5, 	{ {___N,___H,___ ,___ ,___5},	{___P,___M,___ ,___ ,___5}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_5_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_5_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_57_X_POSITION__s32,		//	{6,0,0,6, 	{ {___N,___H,___ ,___ ,___6},	{___P,___M,___ ,___ ,___6}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_6_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_6_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_58_X_POSITION__s32,		//	{6,0,0,7, 	{ {___N,___H,___ ,___ ,___7},	{___P,___M,___ ,___ ,___7}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_7_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_7_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_59_X_POSITION__s32,		//	{6,0,0,8, 	{ {___N,___H,___ ,___ ,___8},	{___P,___M,___ ,___ ,___8}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_8_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_8_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_60_X_POSITION__s32,		//	{6,0,0,9, 	{ {___N,___H,___ ,___ ,___9},	{___P,___M,___ ,___ ,___9}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_9_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_9_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_61_X_POSITION__s32,		//	{6,0,0,0, 	{ {___N,___H,___ ,___ ,___0},	{___P,___M,___ ,___ ,___0}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_0_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_0_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_62_X_POSITION__s32,		//	{6,0,0,1, 	{ {___N,___H,___ ,___ ,___1},	{___P,___M,___ ,___ ,___1}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_1_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_1_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_63_X_POSITION__s32,		//	{6,0,0,2, 	{ {___N,___H,___ ,___ ,___2},	{___P,___M,___ ,___ ,___2}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_2_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_2_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_64_X_POSITION__s32,		//	{6,0,0,3, 	{ {___N,___H,___ ,___ ,___3},	{___P,___M,___ ,___ ,___3}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_3_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_3_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_65_X_POSITION__s32,		//	{6,0,0,4, 	{ {___N,___H,___ ,___ ,___4},	{___P,___M,___ ,___ ,___4}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_4_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_4_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_66_X_POSITION__s32,		//	{6,0,0,5, 	{ {___N,___H,___ ,___ ,___5},	{___P,___M,___ ,___ ,___5}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_5_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_5_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_67_X_POSITION__s32,		//	{6,0,0,6, 	{ {___N,___H,___ ,___ ,___6},	{___P,___M,___ ,___ ,___6}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_6_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_6_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_68_X_POSITION__s32,		//	{6,0,0,7, 	{ {___N,___H,___ ,___ ,___7},	{___P,___M,___ ,___ ,___7}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_7_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_7_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_69_X_POSITION__s32,		//	{6,0,0,8, 	{ {___N,___H,___ ,___ ,___8},	{___P,___M,___ ,___ ,___8}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_8_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_8_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_70_X_POSITION__s32,		//	{6,0,0,9, 	{ {___N,___H,___ ,___ ,___9},	{___P,___M,___ ,___ ,___9}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_9_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_9_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_71_X_POSITION__s32,		//	{6,0,0,0, 	{ {___N,___H,___ ,___ ,___0},	{___P,___M,___ ,___ ,___0}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_0_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_0_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_72_X_POSITION__s32,		//	{6,0,0,1, 	{ {___N,___H,___ ,___ ,___1},	{___P,___M,___ ,___ ,___1}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_1_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_1_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_73_X_POSITION__s32,		//	{6,0,0,2, 	{ {___N,___H,___ ,___ ,___2},	{___P,___M,___ ,___ ,___2}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_2_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_2_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_74_X_POSITION__s32,		//	{6,0,0,3, 	{ {___N,___H,___ ,___ ,___3},	{___P,___M,___ ,___ ,___3}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_3_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_3_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_75_X_POSITION__s32,		//	{6,0,0,4, 	{ {___N,___H,___ ,___ ,___4},	{___P,___M,___ ,___ ,___4}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_4_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_4_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_76_X_POSITION__s32,		//	{6,0,0,5, 	{ {___N,___H,___ ,___ ,___5},	{___P,___M,___ ,___ ,___5}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_5_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_5_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_77_X_POSITION__s32,		//	{6,0,0,6, 	{ {___N,___H,___ ,___ ,___6},	{___P,___M,___ ,___ ,___6}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_6_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_6_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_78_X_POSITION__s32,		//	{6,0,0,7, 	{ {___N,___H,___ ,___ ,___7},	{___P,___M,___ ,___ ,___7}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_7_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_7_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_79_X_POSITION__s32,		//	{6,0,0,8, 	{ {___N,___H,___ ,___ ,___8},	{___P,___M,___ ,___ ,___8}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_8_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_8_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__POINT_MEMORY_80_X_POSITION__s32,		//	{6,0,0,9, 	{ {___N,___H,___ ,___ ,___9},	{___P,___M,___ ,___ ,___9}, }, 	def_PRM_TABLE_POS__POINT_MEMORY_9_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_9_X_POSITION),		4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
	def_PRM_TABLE_POS__THE_LAST_POINT_INDEX__u8,				//	{6,6,0,0, 	{ {___S,___N,___N,___K,___T},	{___L,___T,___P,___N,___T}, }, 	def_FRAM_ADDR__THE_LAST_POINT_INDEX__u8,					(uint8_t*)(&u8_sys_ui__nvprm_THE_LAST_POINT_INDEX)
	def_PRM_TABLE_POS__POINT_INDEX_START__u8,
	def_PRM_TABLE_POS__POINT_INDEX_END__u8,
	def_PRM_TABLE_POS__JOGG_COEFF_DEGREE_X__s32_0,
	def_PRM_TABLE_POS__BACKLASH_DEGREE_X__s32_0,
	def_PRM_TABLE_POS__BREAK_OUTPUT_WAIT_TIME__u8,
	def_PRM_TABLE_POS__SHORTCUT_PX_D1__s32_0,
	def_PRM_TABLE_POS__SHORTCUT_PX_D2__s32_0,
	def_PRM_TABLE_POS__SHORTCUT_PX_E3__s32_0,
	def_PRM_TABLE_POS__SHORTCUT_PX_E4__s32_0,
	def_PRM_TABLE_POS__SHORTCUT_FX_F1__s32_0,
	def_PRM_TABLE_POS__SHORTCUT_FX_F2__s32_0,
	def_PRM_TABLE_POS__SHORTCUT_FX_G3__s32_0,
	def_PRM_TABLE_POS__SHORTCUT_FX_G4__s32_0,
	def_PRM_TABLE_POS__CURRENT_POS_SET__DEGREE_X__s32_0,
	def_PRM_TABLE_POS__RUN_WITH_CONSTANT_SPEED__s32_0,
	def_PRM_TABLE_POS__MOTOR_MICRO_DEG_PER_STEP__s32_0,
	def_PRM_TABLE_POS__DIVISOR_RATIO_X__u16_0,
	def_PRM_TABLE_POS__VERSION__s32_0,
};





//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
//FM25L04B
//4-Kbit(512×8)Serial (SPI) F-RAM

#define def_u16_FRAM_RX_BUF_length		120
#define def_u16_FRAM_MEMORY_MIRROR_length		512

//DIKKAT BU ENUM "PARAMETER_TABLE" ile paralel olmak zorunda!!!
enum
{
	//enumeration for firmware parameter access indexes
	def_u16_enum__PARAMETER_TABLE_INDEX__LANGUAGE__u8,
	def_u16_enum__PARAMETER_TABLE_INDEX__THE_LAST_USAGE_MODE__u8

};

#define 	def_u16_sys_fram__LENGTH_of__BL_setup		(def_u16_mI__BL_setup__CRC16_H + 1 - def_u16_mI__BL_setup__preferences_0)

//#if 	(def_u16_mI__END >= ( def_u16_FRAM_MEMORY_MIRROR_length-1) )
//yemedi.
//#endif





//Table 1. Opcode commands
//WREN Set write enable latch 0000 0110b
#define 	def_u8_sys_fram__Opcode__WREN_Set_write_enable_latch	0x06

//WRDI Write disable 0000 0100b
#define 	def_u8_sys_fram__Opcode__WRDI_Write_disable				0x04

//RDSR Read Status Register 0000 0101b
#define 	def_u8_sys_fram__Opcode__RDSR_Read_Status_Register		0x05

//WRSR Write Status Register 0000 0001b
#define 	def_u8_sys_fram__Opcode__WRSR_Write_Status_Register		0x01

//READ Read memory data 0000 A011b		>>> buradaki A: adresin 8. biti(255. den sonrası)
#define 	def_u8_sys_fram__Opcode__READ_Read_memory_data			0x03

//WRITE Write memory data 0000 A010b	>>> buradaki A: adresin 8. biti(255. den sonrası)
#define 	def_u8_sys_fram__Opcode__WRITE_Write_memory_data		0x02


//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]


//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[


//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#define	def_u1_sys_fram__SIGNAL_OUT__STARTUP_READ__FRAM_to_RAM__READY			u8_byte_sys_fram__SYSTEM_STATUS_REGISTER.bits.b0

#endif /* SYS_FRAM_DEFINITIONS_H_ */
