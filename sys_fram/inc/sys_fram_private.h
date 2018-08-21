/*
 * sys_fram_private.h
 *
 *  Created on: Nov 27, 2016
 *      Author: ozgurbas
 */

#ifndef SYS_FRAM_PRIVATE_H_
#define SYS_FRAM_PRIVATE_H_

//#include <global_ex.h>
#include "global_top_level_includes.h"

#include "sys_fram_definitions.h"
#include "sys_fram_pubic__PRMTR_ATTR_LISTS_COMMON_ACQUISITION_INDEXES.h"

#include "spi.h"

u8	u8_sys_fram__main_state=def_u8_sys_fram__main_state__IDLE;
u8	u8_sys_fram__sub_state=def_u8_sys_fram__main_state__IDLE;
u8	u8_sys_fram__sub_2_state=def_u8_sys_fram__main_state__IDLE;

u8	u8_sys_fram__main_state_return=def_u8_sys_fram__main_state__IDLE;
u8	u8_sys_fram__sub_state_return=def_u8_sys_fram__main_state__IDLE;
u8	u8_sys_fram__sub_2_state_return=def_u8_sys_fram__main_state__IDLE;

u8	u8_sys_fram__main_state__at_FAIL=def_u8_sys_fram__main_state__IDLE;
u8	u8_sys_fram__sub_state__at_FAIL=def_u8_sys_fram__main_state__IDLE;
u8	u8_sys_fram__sub_2_state__at_FAIL=def_u8_sys_fram__main_state__IDLE;

u8	u8_sys_fram__down_counter_1=0;
u8	u8_sys_fram__down_counter_2=0;

//u8	u8_array_sys_fram__MEMORY[def_u16_FRAM_MEMORY_MIRROR_length];

u8	u8_array_sys_fram__RX_or_TX_DUMMY_BUFFER[def_u16_FRAM_MEMORY_MIRROR_length];

u8	u8_array_sys_fram__spi_RX_BUF[def_u16_FRAM_RX_BUF_length];

u8_byte u8_byte_sys_fram__IC_STATUS_REGISTER;

u8_byte u8_byte_sys_fram__SYSTEM_STATUS_REGISTER;

u8		u8_sys_fram__temp_1=0;
u16		u16_sys_fram__temp_1=0;

uint8_t*	u8_ptr_sys_fram__temp_1;

u16		u16_sys_fram__i;
u16		u16_sys_fram__j;



//u8_byte	u8_byte_sys_fram__SIGNALS_write_RAM_to_FRAM_verify_success_0;


//u16		u16_sys_fram__REQUESTED_LENGTH_of_WRITE_to_FRAM=0;
//u16		u16_sys_fram__REQUESTED_START_ADDRESS_of_WRITE_to_FRAM=0;
//
//u16		u16_sys_fram__REQUESTED_LENGTH_of_READ_from_FRAM=0;
//u16		u16_sys_fram__REQUESTED_START_ADDRESS_of_READ_from_FRAM=0;



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








//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[





////*
////***
////*****
////*******
////*********
////***********
////[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
////ONEMLI: KULLANIM DETAYLARI:
////tum RAM <<<===>>> FRAM transections lar sys_fram tarafından
//// parametre 1: "PRMTR_ATTR_LISTS_COMMON_ACQUISITION_INDEX"
//// parametre 2: R/W COMMAND
//
////olarak task arrayine cekilecek, circular olarak ve max length kontrolu ile,
////sonuclar ise fonskiyonun return ettigi RESULT_STATUS_INDEX parametresi ile talepte bulunan system tarafından takip edilebilecek.
//
////uint16_t	f_u16_sys_fram__GET_RAM_FRAM_TRANSFER_REQUEST_and_RETURN_RESULT_TRACKING_INDEX(
////		uint16_t 	f_in_u16__PRMTR_ATTR_LISTS_COMMON_ACQUISITION_INDEX,
////		uint16_t	f_in_u8__TRANSFER_DIRECTION,
////		)
//
////]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
////***********
////*********
////*******
////*****
////***
////*
//
//
//
//
//
////*
////***
////*****
////*******
////*********
////***********
////[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
//
////!!! PARALEL PARAMETRE OZELLIK ARRAYLERI ve BUNLARIN ORTAK ERISIM ENUM INDEX LERI:
//
////!!! ONEMLI NOT:PRMTR_ATTR_LISTS_COMMON_ACQUISITION_INDEX lerini, ATTRIBUTE LISTELERINE erişim fonksiyonları PARALEL olarak erişim icin kullanıcak!!!
////!!! BU ORTAK ERISIM LISTESI KULLANICI KILAVUZUNDAKI GOSTERILECEK PARAMETRE LISTESININ KARSILIGI OLUCAK,
////!!! TABI INDEXDEKI PARAMETRE NIN DISPLAY DE GOSTERILIP USER A KURCALITILMASI "PARAMETER_TYPE" ILE KONTROL EDILECEK.
//
//////ONEMLI: DİGER SİSTEMLERE RW FONKSİYONLARI İLE PUBLİC OLUCAK LİSTE BUDUR
//////BU ENUM "sys_fram_pubic__PRMTR_ATTR_LISTS_COMMON_ACQUISITION_INDEXES.h" e tasindi!!!
////enum
////{
////	//PARAMETER ATTRIBUTE PARALLEL CONSTANT ARRAY LIST COMMON ACQUISITION LIST
////	def_u16_enum__PRMTR_ATTR_LISTS_COMMON_ACQUISITION_INDEX__THE_LAST_USAGE_MODE__u8,
////	def_u16_enum__PRMTR_ATTR_LISTS_COMMON_ACQUISITION_INDEX__POWER_ON_RESET_COUNTER__u8
////};
//
//
//
//
////*
////***
////*****
////[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
//////FIKIR!!!
//////HIC "RESULT_TRACKING_INDEX" GIBI ALENGILLI ISLERE GEREK YOK,
//////sonucta her parametrenin bi erisim attr tabloları var,
////birde status register arrayi olsun, constant yerine ramde,
////talep isteyen buraya yazsın bitine, 0. R, 1. W
////sys_fram bu arrayi tarayıp gerekeni yapıp 6. R_OK, 7. W_OK bitlerini yaksın,
////boylece her request icin TRACKING_INDEX gibi bir is yukune gerek kalmaz!!! IYI FIKIR!!!
////0. R, 1. W bitleri dısardan set, icerde reset,
////6. R_OK, 7. W_OK bitleri ise icerde set, dirasda reset olucak,
////yani sys_ui ilgili parametrenin STATUS 6.btini sondurup, 0. bitini yakıcak, 6. bitin yanmasını beklicek.
////simple is beautiful!!!
//
//#define 	def_u16_sys_fram__LENGTH_OF_COMMON_ACQUISITION_INDEXES	2
//
//uint8_t		u8_array_sys_fram__TASK_STATUS[def_u16_sys_fram__LENGTH_OF_COMMON_ACQUISITION_INDEXES];
//
//uint16_t	u16_array_sys_fram__SCANNED_TRANSFER_REQUEST__INDEX_temp=0;
//
////]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
////*****
////***
////*
//
//const	uint16_t		const_u16_array_sys_fram__PRMTR_ATTR__FRAM_ADDRESSES[]=
//{
//		//buradaki liste bir oncekinden yapılan ilerleme ile iliskili olmak zorunda!!!
//		//parametre 1,2,3,4,5 orneginde 0 1 2 4 8 olmak zorunda!!!
//
//		//BURADA BİRDEN FAZLA AYNI ADRESİN BİTLERİNİN TANIMI İCİN SATIRLAR OLABİLİR!!!
//		//GORLDUGU GIBI FRAMDEKİ YERLESIM SIRASINDAN BAGIMSIZ OLABİLİYOR, DIKKAT ET!!!
//
//		//BURADA "FRAM_ADDR" enumarations daki REAL adres numaraları koyulacak!!!
//		def_FRAM_ADDR__THE_LAST_USAGE_MODE__u8,
//		def_FRAM_ADDR__POWER_ON_RESET_COUNTER__u8,
//
//		//8 ayrı flag icin 8 ayrı tanımlama:
//		def_FRAM_ADDR__USER_PREFERENCES_0,
//		def_FRAM_ADDR__USER_PREFERENCES_0,
//		def_FRAM_ADDR__USER_PREFERENCES_0,
//		def_FRAM_ADDR__USER_PREFERENCES_0,
//		def_FRAM_ADDR__USER_PREFERENCES_0,
//		def_FRAM_ADDR__USER_PREFERENCES_0,
//		def_FRAM_ADDR__USER_PREFERENCES_0,
//		def_FRAM_ADDR__USER_PREFERENCES_0,
//};
//
//const	uint8_t*		const_u8_ptr_array_sys_fram__PRMTR_ATTR__RAM_ADDRESSES[]=
//{
//		(uint8_t*)(&u8_sys_ui__THE_LAST_USAGE_MODE),
//		(uint8_t*)(&u8_sys_ui__POWER_ON_RESET_COUNTER),
//
//		//8 ayrı flag icin 8 ayrı tanımlama:
//		(uint8_t*)(&u8_u1_union_sys_ui__USER_PREFERENCES_0),
//		(uint8_t*)(&u8_u1_union_sys_ui__USER_PREFERENCES_0),
//		(uint8_t*)(&u8_u1_union_sys_ui__USER_PREFERENCES_0),
//		(uint8_t*)(&u8_u1_union_sys_ui__USER_PREFERENCES_0),
//		(uint8_t*)(&u8_u1_union_sys_ui__USER_PREFERENCES_0),
//		(uint8_t*)(&u8_u1_union_sys_ui__USER_PREFERENCES_0),
//		(uint8_t*)(&u8_u1_union_sys_ui__USER_PREFERENCES_0),
//		(uint8_t*)(&u8_u1_union_sys_ui__USER_PREFERENCES_0),
//};
//
////const	uint32_t		const_u32_array_sys_fram__PRMTR_ATTR__DISPLAY_TYPE[]=
////{
////		def_display_type__YES_NO,
////		def_display_type__ENABLE_DISABLE,
////		def_display_type__PERCENTAGE,
////};
//
//const	uint16_t		const_u16_array_sys_fram__PRMTR_ATTR__BYTE_LENGTH[]=
//{
//		1,
//		1,
//
//		//8 ayrı flag icin 8 ayrı tanımlama: USER_PREFERENCES_0
//		1,
//		1,
//		1,
//		1,
//		1,
//		1,
//		1,
//		1,
//
//		//100,		//tum hafıza mesela!!! !!! ONEMLI SONUC !!! : BOYLE BIRSEY OLAMAZ, ADRESS LINKLERI ERISIM FONKSIYONLARI ACISINDAN FISIKSEL DE HEM RAM HEM FRAM DE LINEAR DEGIL!!! AMA FLAXIBLE
//		//SADECE "def_u16_enum__PRMTR_ATTR_LISTS_COMMON_ACQUISITION_INDEX" ENUM UNU KOMPLE GEZ DENİLECEK RW FONKSİYONLARI YAZILABILIR.
//};
//
//
////[[[[[[[[[[[[[[[[[[[[
//////ONEMLI: bit erisimi fram in isi degil, ust sistem, byte structure larını tanımlayıp, read&modify&write yapacak!!! RFAM erisimi byte bazlı ise sys_fram de oyle olmak zorunda, baska haller mantıksız durumlara sebep oluyor,
//////byte length 0 iken de 1 ikende 1 byte okunması gibi!!!
////AMA BUNU HAKLILASTIRAN parametre index tablosu ile her turku parametreye ulasabilmek, bit icin byte da harcamadan!!!
////NASIL???
////HIMM: soyle ki; bitler icinde byte length bir olacak, yani okuma yazma islemleri degismeyecek, e ozaman menude set ve gosterim kalır,
////her bit icin paralel tablolarda yer isgal etmek??? ortak fonksiyon kullanımı icin degebilir.
//
//////TODO bit erisimi simdilk ertelendi, write da RWR uclemesi gerekecek, start upda regısterın cekilip bozulmadıgı, her RAM update de FRAM e basıldıgı zaman sorun yok.
//////eger byte length 0 ise bura isleme konulacak.
//////255 ise NOP icin kullanılacak.
////const	uint8_t		const_u8_array_sys_fram__PRMTR_ATTR__BIT_NUMBER[]=
////{
////		255,	//THE_LAST_USAGE_MODE
////		255,	//POWER_ON_RESET_COUNTER
////};
////]]]]]]]]]]]]]]]]]]]]
//
////mesela 1. bit, sadece admin yetkili demek
////mesela 2. bit, servis gorevlisi yetkili demek
//const	uint8_t		const_u8_array_sys_fram__PRMTR_ATTR__AUTHETICATION_LEVEL_BITS[]=
//{
//		1,		//THE_LAST_USAGE_MODE
//		1,		//POWER_ON_RESET_COUNTER
//
//		//8 ayrı flag icin 8 ayrı tanımlama: USER_PREFERENCES_0
//		1,
//		1,
//		1,
//		1,
//		1,
//		1,
//		1,
//		1,
//};
//
//
//#define 	def_u8_sys_fram__PARAMETER_TYPE__USER		1
//#define 	def_u8_sys_fram__PARAMETER_TYPE__SYSTEM		2
////note: menude kullanıciya system parameteresi acilmaması icin, mesela kullanim modu son hali yazıımın kullandıgı,
////kullanıciya kapalı parametre oldugu icin SYSTEM parametresi olarak menude pass gecilecek.
//
//const	uint8_t		const_u8_array_sys_fram__PRMTR_ATTR__PARAMETER_TYPE[]=
//{
//		def_u8_sys_fram__PARAMETER_TYPE__SYSTEM,		//THE_LAST_USAGE_MODE
//		def_u8_sys_fram__PARAMETER_TYPE__SYSTEM,		//POWER_ON_RESET_COUNTER
//
//		//8 ayrı flag icin 8 ayrı tanımlama: USER_PREFERENCES_0
//		def_u8_sys_fram__PARAMETER_TYPE__USER,
//		def_u8_sys_fram__PARAMETER_TYPE__USER,
//		def_u8_sys_fram__PARAMETER_TYPE__USER,
//		def_u8_sys_fram__PARAMETER_TYPE__USER,
//		def_u8_sys_fram__PARAMETER_TYPE__USER,
//		def_u8_sys_fram__PARAMETER_TYPE__USER,
//		def_u8_sys_fram__PARAMETER_TYPE__USER,
//		def_u8_sys_fram__PARAMETER_TYPE__USER,
//
//
//		def_u8_sys_fram__PARAMETER_TYPE__SYSTEM,
//};
//
////]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
////***********
////*********
////*******
////*****
////***
////*



//*
//***
//*****
//*******
//*********
//***********
//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[

//PARAMETER_TABLE deki sıra artık onemli degil, "CODE_NAME" search ile index bulunacak!!!
//"CODE_NAME" terine sıralama enum kullanmak da muhtemel
//bilinen bi numarayı kodda aramak sacma,
//kullanıcıya kod adı vermek icin anlamlı olabilir,
//UI nin erisimi "CODE_NAME" i kullanabilir, ama kodu icinde parametre degisiklikleri icin enum kullanmak mantıklı!!!



//const PARAMETER	PARAMETER_TABLE_x[def_u16_sys_fram_NUMBER_of_PARAMETERS]=
//{
//		{}
//};


uint8_t			u8_sys_ui__POWER_ON_RESET_COUNTER;


extern uint8_t	u8_sys_ui__nvprm_LANGUAGE;

extern uint8_t			u8_sys_ui__nvprm_THE_LAST_USAGE_MODE;
extern uint8_t			u8_sys_ui__nvprm_THE_LAST_IO_STATES;

extern uint8_t			u8_sys_ui__nvprm__IN_1_ACT_CONF_at_POINT_MODE;
extern uint8_t			u8_sys_ui__nvprm__IN_2_ACT_CONF_at_POINT_MODE;
extern uint8_t			u8_sys_ui__nvprm__IN_3_ACT_CONF_at_POINT_MODE;
extern uint8_t			u8_sys_ui__nvprm__IN_4_ACT_CONF_at_POINT_MODE;

extern uint8_t			u8_sys_ui__nvprm__IN_1_ACT_CONF_at_JOGG_MODE;
extern uint8_t			u8_sys_ui__nvprm__IN_2_ACT_CONF_at_JOGG_MODE;
extern uint8_t			u8_sys_ui__nvprm__IN_3_ACT_CONF_at_JOGG_MODE;
extern uint8_t			u8_sys_ui__nvprm__IN_4_ACT_CONF_at_JOGG_MODE;

extern uint8_t			u8_sys_ui__nvprm__IN_PULSE_TRAIN_MIN;
extern uint8_t			u8_sys_ui__nvprm__IN_PULSE_TRAIN_MAX;

//extern int32_t			s32_sys_ui__nvprm_THE_LAST__PREVIOUS_X_POSITION;
//extern int32_t			s32_sys_ui__nvprm_THE_LAST__NOW_X_POSITION;
//extern int32_t			s32_sys_ui__nvprm_THE_LAST__TARGET_X_POSITION;

extern u8_u1_PREFERENCES_1	 	u8_sys_ui__nvprm_USER_PREFERENCES_1;
extern u8_u1_PREFERENCES_2	 	u8_sys_ui__nvprm_USER_PREFERENCES_2;
extern u8_u1_PREFERENCES_3	 	u8_sys_ui__nvprm_USER_PREFERENCES_3;
extern u8_u1_PREFERENCES_4	 	u8_sys_ui__nvprm_USER_PREFERENCES_4;

extern uint16_t	 	u16_sys_ui__nvprm_L64_ACC_12bits_R_WS;
extern uint16_t	 	u16_sys_ui__nvprm_L64_DEC_12bits_R_WS;
extern uint16_t	 	u16_sys_ui__nvprm_L64_MAX_SPEED_10bits_R_WR;
extern uint16_t	 	u16_sys_ui__nvprm_L64_MIN_SPEED_13bits_R_WS;
extern uint16_t	 	u16_sys_ui__nvprm_L64_FS_SPD_10bits_R_WR;

extern uint8_t	 	u8_sys_ui__nvprm_L64_TVAL_HOLD_7bits_R_WR;
extern uint8_t	 	u8_sys_ui__nvprm_L64_TVAL_RUN_7bits_R_WR;
extern uint8_t	 	u8_sys_ui__nvprm_L64_TVAL_ACC_7bits_R_WR;
extern uint8_t	 	u8_sys_ui__nvprm_L64_TVAL_DEC_7bits_R_WR;

extern uint8_t	 	u8_sys_ui__nvprm_L64_OCD_TH_4bits_R_WR;

extern uint8_t	 	u8_sys_ui__nvprm_L64_ALARM_EN_8bits_R_WS;


extern uint8_t	 	u8_sys_ui__nvprm_UNDO_MEMORY_INDEX__u8;
extern int32_t		s32_sys_ui__nvprm_UNDO_MEMORY_X_POSITIONS[5];

//extern int32_t		s32_sys_ui__nvprm_UNDO_MEMORY_0_X_POSITION;
//extern int32_t		s32_sys_ui__nvprm_UNDO_MEMORY_1_X_POSITION;
//extern int32_t		s32_sys_ui__nvprm_UNDO_MEMORY_2_X_POSITION;
//extern int32_t		s32_sys_ui__nvprm_UNDO_MEMORY_3_X_POSITION;
//extern int32_t		s32_sys_ui__nvprm_UNDO_MEMORY_4_X_POSITION;


extern uint16_t		u16_sys_ui__nvprm_DIVISOR_STEP_X__u16_0;
extern int32_t		s32_sys_ui__nvprm_DIVISOR_DEGREE_X__s32_0;

extern int32_t		s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[10];
extern uint8_t		u8_sys_ui__nvprm_THE_LAST_POINT_INDEX;
extern uint8_t		u8_sys_ui__nvprm_POINT_INDEX_START;
extern uint8_t		u8_sys_ui__nvprm_POINT_INDEX_END;

extern int32_t		s32_sys_ui__nvprm_ABS_POS__X__micro_degree__NOW_SEEN;
extern int32_t		s32_sys_ui__nvprm_ABS_POS__X__micro_degree__NOW__REAL;
extern int32_t		s32_sys_ui__nvprm_ABS_POS__X__micro_degree__PREVIOUS__SEEN;

extern int32_t		s32_sys_ui__nvprm_JOGG_COEFF_DEGREE_X;

extern int32_t		s32_sys_ui__nvprm_BACKLASH_DEGREE_X;

extern uint8_t	 	u8_sys_ui__nvprm_BREAK_OUTPUT_WAIT_TIME;


extern int32_t		s32_sys_ui__nvprm_SHORTCUT_PX_D1;
extern int32_t		s32_sys_ui__nvprm_SHORTCUT_PX_D2;
extern int32_t		s32_sys_ui__nvprm_SHORTCUT_PX_E3;
extern int32_t		s32_sys_ui__nvprm_SHORTCUT_PX_E4;

extern int32_t		s32_sys_ui__nvprm_SHORTCUT_FX_F1;
extern int32_t		s32_sys_ui__nvprm_SHORTCUT_FX_F2;
extern int32_t		s32_sys_ui__nvprm_SHORTCUT_FX_G3;
extern int32_t		s32_sys_ui__nvprm_SHORTCUT_FX_G4;

extern int32_t		s32_sys_ui__nvprm_CURRENT_POS_SET__DEGREE_X;

extern int32_t		s32_sys_ui__nvprm_MOTOR_MICRO_DEG_PER_STEP;

extern uint16_t		u16_sys_ui__nvprm_DIVISOR_RATIO_X;

extern int32_t		s32_sys_ui__nvprm_VERSION;

extern int32_t		s32_sys_ui__nvprm_RUN_WITH_CONSTANT_SPEED;


//*
//***
//*****
//*******
//*********
//***********
//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
enum
{
	//FRAM MAP
	//{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{
	//[0]=u8_sys_fram__temp_1;  //her acilista okunup bir arttırılıp geri yazılır,
	//power on reset counter dır aynı zamanda, rfam in okuma yazmasının calistigini test etmek icin de kullanılır.

	def_FRAM_ADDR__POWER_ON_RESET_COUNTER__u8,


	//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
	//FLIGHT_RECORD: yazılımın tum anlık calisma durumlarını ve kritik hata flaglerini tutar,
	//bura ayrı bir inceleme menusune sahip olucak, cihazlarda ne sıkıntı olustugunu izleyebilmek icin,
	//bu flagler kara kutu gibi kullanılacak, cihaz sıkıntılı durumlara dustugunde buralara olay flagi cakıp bırakacak,
	//bug takibi icin kullanılacak.


	//[1]:		CRITICAL_EVENTS_0
	//[2]:		CRITICAL_EVENTS_1
	//[3]:		CRITICAL_EVENTS_2		24 tane kritik event flag i 3x (2x4) displayde gosterilicek 0/1 olarak.
	def_FRAM_ADDR__CRITICAL_EVENT_FLAGS_0__u8,
	def_FRAM_ADDR__CRITICAL_EVENT_FLAGS_1__u8,
	def_FRAM_ADDR__CRITICAL_EVENT_FLAGS_2__u8,


	def_FRAM_ADDR__LANGUAGE__u8,
	def_FRAM_ADDR__RESERVED_1__u8,

	def_FRAM_ADDR__USER_PREFERENCES_1,
	def_FRAM_ADDR__USER_PREFERENCES_2,
	def_FRAM_ADDR__USER_PREFERENCES_3,
	def_FRAM_ADDR__USER_PREFERENCES_4,


	def_FRAM_ADDR__THE_LAST_USAGE_MODE__u8,
	def_FRAM_ADDR__THE_LAST_IO_STATES__u8,

	def_FRAM_ADDR__X__micro_degree__NOW_SEEN__s32_0,
	def_FRAM_ADDR__THE_LAST__PREVIOUS_X_POSITION__s32_1,
	def_FRAM_ADDR__THE_LAST__PREVIOUS_X_POSITION__s32_2,
	def_FRAM_ADDR__THE_LAST__PREVIOUS_X_POSITION__s32_3,

	def_FRAM_ADDR__X__micro_degree__NOW__REAL__s32_0,
	def_FRAM_ADDR__THE_LAST__NOW_X_POSITION__s32_1,
	def_FRAM_ADDR__THE_LAST__NOW_X_POSITION__s32_2,
	def_FRAM_ADDR__THE_LAST__NOW_X_POSITION__s32_3,

	def_FRAM_ADDR__X__micro_degree__PREVIOUS__SEEN__s32_0,
	def_FRAM_ADDR__THE_LAST__TARGET_X_POSITION__s32_1,
	def_FRAM_ADDR__THE_LAST__TARGET_X_POSITION__s32_2,
	def_FRAM_ADDR__THE_LAST__TARGET_X_POSITION__s32_3,

//	def_FRAM_ADDR__THE_LAST__SCANF_INDEX__u8,			//gereksiz
//	def_FRAM_ADDR__THE_LAST__PARAMETER_INDEX__u16_0,	//gereksiz
//	def_FRAM_ADDR__THE_LAST__PARAMETER_INDEX__u16_1,	//gereksiz


	def_FRAM_ADDR__L64_ACC_12bits_R_WS__u16_0,
	def_FRAM_ADDR__L64_ACC_12bits_R_WS__u16_1,

	def_FRAM_ADDR__L64_DEC_12bits_R_WS__u16_0,
	def_FRAM_ADDR__L64_DEC_12bits_R_WS__u16_1,

	def_FRAM_ADDR__L64_MAX_SPEED_10bits_R_WR__u16_0,
	def_FRAM_ADDR__L64_MAX_SPEED_10bits_R_WR__u16_1,

	def_FRAM_ADDR__L64_MIN_SPEED_13bits_R_WS__u16_0,
	def_FRAM_ADDR__L64_MIN_SPEED_13bits_R_WS__u16_1,

	def_FRAM_ADDR__L64_FS_SPD_10bits_R_WR__u16_0,
	def_FRAM_ADDR__L64_FS_SPD_10bits_R_WR__u16_1,

	def_FRAM_ADDR__L64_TVAL_HOLD_7bits_R_WR__u8,
	def_FRAM_ADDR__L64_TVAL_RUN_7bits_R_WR__u8,
	def_FRAM_ADDR__L64_TVAL_ACC_7bits_R_WR__u8,
	def_FRAM_ADDR__L64_TVAL_DEC_7bits_R_WR__u8,

	def_FRAM_ADDR__L64_OCD_TH_4bits_R_WR__u8,

	def_FRAM_ADDR__L64_ALARM_EN_8bits_R_WS__u8,



	def_FRAM_ADDR__UNDO_MEMORY_INDEX__u8,

	def_FRAM_ADDR__UNDO_MEMORY_0_X_POSITION__s32_0,
	def_FRAM_ADDR__UNDO_MEMORY_0_X_POSITION__s32_1,
	def_FRAM_ADDR__UNDO_MEMORY_0_X_POSITION__s32_2,
	def_FRAM_ADDR__UNDO_MEMORY_0_X_POSITION__s32_3,

	def_FRAM_ADDR__UNDO_MEMORY_1_X_POSITION__s32_0,
	def_FRAM_ADDR__UNDO_MEMORY_1_X_POSITION__s32_1,
	def_FRAM_ADDR__UNDO_MEMORY_1_X_POSITION__s32_2,
	def_FRAM_ADDR__UNDO_MEMORY_1_X_POSITION__s32_3,

	def_FRAM_ADDR__UNDO_MEMORY_2_X_POSITION__s32_0,
	def_FRAM_ADDR__UNDO_MEMORY_2_X_POSITION__s32_1,
	def_FRAM_ADDR__UNDO_MEMORY_2_X_POSITION__s32_2,
	def_FRAM_ADDR__UNDO_MEMORY_2_X_POSITION__s32_3,

	def_FRAM_ADDR__UNDO_MEMORY_3_X_POSITION__s32_0,
	def_FRAM_ADDR__UNDO_MEMORY_3_X_POSITION__s32_1,
	def_FRAM_ADDR__UNDO_MEMORY_3_X_POSITION__s32_2,
	def_FRAM_ADDR__UNDO_MEMORY_3_X_POSITION__s32_3,

	def_FRAM_ADDR__UNDO_MEMORY_4_X_POSITION__s32_0,
	def_FRAM_ADDR__UNDO_MEMORY_4_X_POSITION__s32_1,
	def_FRAM_ADDR__UNDO_MEMORY_4_X_POSITION__s32_2,
	def_FRAM_ADDR__UNDO_MEMORY_4_X_POSITION__s32_3,


	def_FRAM_ADDR__DIVISOR_STEP_X__u16_0,
	def_FRAM_ADDR__DIVISOR_STEP_X__u16_1,

	def_FRAM_ADDR__DIVISOR_DEGREE_X__s32_0,
	def_FRAM_ADDR__DIVISOR_DEGREE_X__s32_1,
	def_FRAM_ADDR__DIVISOR_DEGREE_X__s32_2,
	def_FRAM_ADDR__DIVISOR_DEGREE_X__s32_3,


	def_FRAM_ADDR__JOGG_COEFF_DEGREE_X__s32_0,
	def_FRAM_ADDR__JOGG_COEFF_DEGREE_X__s32_1,
	def_FRAM_ADDR__JOGG_COEFF_DEGREE_X__s32_2,
	def_FRAM_ADDR__JOGG_COEFF_DEGREE_X__s32_3,


	def_FRAM_ADDR__BACKLASH_DEGREE_X__s32_0,
	def_FRAM_ADDR__BACKLASH_DEGREE_X__s32_1,
	def_FRAM_ADDR__BACKLASH_DEGREE_X__s32_2,
	def_FRAM_ADDR__BACKLASH_DEGREE_X__s32_3,


	def_FRAM_ADDR__BREAK_OUTPUT_WAIT_TIME__u8,

	def_FRAM_ADDR__SHORTCUT_PX_D1__s32_0,
	def_FRAM_ADDR__SHORTCUT_PX_D1__s32_1,
	def_FRAM_ADDR__SHORTCUT_PX_D1__s32_2,
	def_FRAM_ADDR__SHORTCUT_PX_D1__s32_3,

	def_FRAM_ADDR__SHORTCUT_PX_D2__s32_0,
	def_FRAM_ADDR__SHORTCUT_PX_D2__s32_1,
	def_FRAM_ADDR__SHORTCUT_PX_D2__s32_2,
	def_FRAM_ADDR__SHORTCUT_PX_D2__s32_3,

	def_FRAM_ADDR__SHORTCUT_PX_E3__s32_0,
	def_FRAM_ADDR__SHORTCUT_PX_E3__s32_1,
	def_FRAM_ADDR__SHORTCUT_PX_E3__s32_2,
	def_FRAM_ADDR__SHORTCUT_PX_E3__s32_3,

	def_FRAM_ADDR__SHORTCUT_PX_E4__s32_0,
	def_FRAM_ADDR__SHORTCUT_PX_E4__s32_1,
	def_FRAM_ADDR__SHORTCUT_PX_E4__s32_2,
	def_FRAM_ADDR__SHORTCUT_PX_E4__s32_3,


	def_FRAM_ADDR__SHORTCUT_FX_F1__s32_0,
	def_FRAM_ADDR__SHORTCUT_FX_F1__s32_1,
	def_FRAM_ADDR__SHORTCUT_FX_F1__s32_2,
	def_FRAM_ADDR__SHORTCUT_FX_F1__s32_3,

	def_FRAM_ADDR__SHORTCUT_FX_F2__s32_0,
	def_FRAM_ADDR__SHORTCUT_FX_F2__s32_1,
	def_FRAM_ADDR__SHORTCUT_FX_F2__s32_2,
	def_FRAM_ADDR__SHORTCUT_FX_F2__s32_3,

	def_FRAM_ADDR__SHORTCUT_FX_G3__s32_0,
	def_FRAM_ADDR__SHORTCUT_FX_G3__s32_1,
	def_FRAM_ADDR__SHORTCUT_FX_G3__s32_2,
	def_FRAM_ADDR__SHORTCUT_FX_G3__s32_3,

	def_FRAM_ADDR__SHORTCUT_FX_G4__s32_0,
	def_FRAM_ADDR__SHORTCUT_FX_G4__s32_1,
	def_FRAM_ADDR__SHORTCUT_FX_G4__s32_2,
	def_FRAM_ADDR__SHORTCUT_FX_G4__s32_3,

	def_FRAM_ADDR__CURRENT_POS_SET__DEGREE_X__s32_0,
	def_FRAM_ADDR__CURRENT_POS_SET__DEGREE_X__s32_1,
	def_FRAM_ADDR__CURRENT_POS_SET__DEGREE_X__s32_2,
	def_FRAM_ADDR__CURRENT_POS_SET__DEGREE_X__s32_3,

	def_FRAM_ADDR__MOTOR_MICRO_DEG_PER_STEP__s32_0,
	def_FRAM_ADDR__MOTOR_MICRO_DEG_PER_STEP__s32_1,
	def_FRAM_ADDR__MOTOR_MICRO_DEG_PER_STEP__s32_2,
	def_FRAM_ADDR__MOTOR_MICRO_DEG_PER_STEP__s32_3,


	def_FRAM_ADDR__DIVISOR_RATIO_X__u16_0,
	def_FRAM_ADDR__DIVISOR_RATIO_X__u16_1,

	def_FRAM_ADDR__VERSION__s32_0,
	def_FRAM_ADDR__VERSION__s32_1,
	def_FRAM_ADDR__VERSION__s32_2,
	def_FRAM_ADDR__VERSION__s32_3,

	def_FRAM_ADDR__RUN_WITH_CONSTANT_SPEED__s32_0,
	def_FRAM_ADDR__RUN_WITH_CONSTANT_SPEED__s32_1,
	def_FRAM_ADDR__RUN_WITH_CONSTANT_SPEED__s32_2,
	def_FRAM_ADDR__RUN_WITH_CONSTANT_SPEED__s32_3,



	def_FRAM_ADDR__POINT_MEMORY_1_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_1_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_1_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_1_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_2_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_2_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_2_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_2_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_3_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_3_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_3_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_3_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_4_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_4_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_4_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_4_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_5_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_5_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_5_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_5_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_6_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_6_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_6_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_6_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_7_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_7_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_7_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_7_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_8_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_8_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_8_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_8_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_9_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_9_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_9_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_9_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_10_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_10_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_10_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_10_X_POSITION__s32_3,




	def_FRAM_ADDR__POINT_MEMORY_11_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_11_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_11_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_11_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_12_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_12_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_12_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_12_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_13_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_13_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_13_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_13_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_14_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_14_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_14_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_14_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_15_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_15_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_15_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_15_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_16_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_16_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_16_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_16_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_17_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_17_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_17_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_17_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_18_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_18_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_18_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_18_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_19_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_19_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_19_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_19_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_20_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_20_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_20_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_20_X_POSITION__s32_3,




	def_FRAM_ADDR__POINT_MEMORY_21_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_21_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_21_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_21_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_22_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_22_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_22_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_22_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_23_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_23_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_23_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_23_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_24_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_24_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_24_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_24_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_25_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_25_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_25_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_25_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_26_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_26_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_26_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_26_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_27_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_27_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_27_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_27_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_28_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_28_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_28_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_28_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_29_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_29_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_29_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_29_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_30_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_30_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_30_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_30_X_POSITION__s32_3,



	def_FRAM_ADDR__POINT_MEMORY_31_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_31_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_31_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_31_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_32_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_32_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_32_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_32_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_33_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_33_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_33_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_33_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_34_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_34_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_34_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_34_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_35_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_35_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_35_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_35_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_36_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_36_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_36_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_36_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_37_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_37_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_37_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_37_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_38_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_38_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_38_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_38_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_39_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_39_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_39_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_39_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_40_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_40_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_40_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_40_X_POSITION__s32_3,



	def_FRAM_ADDR__POINT_MEMORY_41_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_41_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_41_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_41_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_42_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_42_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_42_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_42_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_43_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_43_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_43_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_43_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_44_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_44_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_44_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_44_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_45_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_45_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_45_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_45_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_46_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_46_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_46_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_46_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_47_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_47_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_47_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_47_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_48_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_48_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_48_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_48_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_49_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_49_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_49_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_49_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_50_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_50_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_50_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_50_X_POSITION__s32_3,


	def_FRAM_ADDR__POINT_MEMORY_51_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_51_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_51_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_51_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_52_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_52_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_52_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_52_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_53_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_53_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_53_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_53_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_54_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_54_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_54_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_54_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_55_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_55_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_55_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_55_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_56_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_56_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_56_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_56_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_57_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_57_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_57_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_57_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_58_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_58_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_58_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_58_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_59_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_59_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_59_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_59_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_60_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_60_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_60_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_60_X_POSITION__s32_3,




	def_FRAM_ADDR__POINT_MEMORY_61_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_61_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_61_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_61_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_62_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_62_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_62_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_62_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_63_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_63_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_63_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_63_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_64_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_64_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_64_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_64_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_65_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_65_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_65_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_65_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_66_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_66_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_66_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_66_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_67_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_67_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_67_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_67_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_68_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_68_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_68_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_68_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_69_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_69_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_69_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_69_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_70_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_70_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_70_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_70_X_POSITION__s32_3,




	def_FRAM_ADDR__POINT_MEMORY_71_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_71_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_71_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_71_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_72_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_72_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_72_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_72_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_73_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_73_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_73_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_73_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_74_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_74_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_74_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_74_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_75_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_75_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_75_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_75_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_76_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_76_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_76_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_76_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_77_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_77_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_77_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_77_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_78_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_78_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_78_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_78_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_79_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_79_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_79_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_79_X_POSITION__s32_3,

	def_FRAM_ADDR__POINT_MEMORY_80_X_POSITION__s32_0,
	def_FRAM_ADDR__POINT_MEMORY_80_X_POSITION__s32_1,
	def_FRAM_ADDR__POINT_MEMORY_80_X_POSITION__s32_2,
	def_FRAM_ADDR__POINT_MEMORY_80_X_POSITION__s32_3,  //son 445!!!

	def_FRAM_ADDR__THE_LAST_POINT_INDEX__u8,
	def_FRAM_ADDR__POINT_INDEX_START__u8,
	def_FRAM_ADDR__POINT_INDEX_END__u8,  //son 448!!!

	def_FRAM_ADDR__IN_1_ACT_CONF_at_POINT_MODE__u8,
	def_FRAM_ADDR__IN_2_ACT_CONF_at_POINT_MODE__u8,
	def_FRAM_ADDR__IN_3_ACT_CONF_at_POINT_MODE__u8,
	def_FRAM_ADDR__IN_4_ACT_CONF_at_POINT_MODE__u8,

	def_FRAM_ADDR__IN_1_ACT_CONF_at_JOGG_MODE__u8,
	def_FRAM_ADDR__IN_2_ACT_CONF_at_JOGG_MODE__u8,
	def_FRAM_ADDR__IN_3_ACT_CONF_at_JOGG_MODE__u8,
	def_FRAM_ADDR__IN_4_ACT_CONF_at_JOGG_MODE__u8,

	def_FRAM_ADDR__IN_PULSE_TRAIN_MIN__u8,
	def_FRAM_ADDR__IN_PULSE_TRAIN_MAX__u8

	//dikkat!!! FRAM de 512 byte yer var, burası max 511 olabilir !!!

};
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
//***********
//*********
//*******
//*****
//***
//*


//*
//***
//*****
//*******
//*********
//***********
//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
const PARAMETER	PARAMETER_TABLE[def_u16_sys_fram_NUMBER_of_PARAMETERS]=
{
		//onemlı OZET:
		//!!!!!!!!!!!!!!!!!!!!!!
		//!!!!!!!!!!!!!!!!!!!!!!
		//!!!!!!!!!!!!!!!!!!!!!!
		//("CODE_NAME" i sadece UI kullanacak!!! search functions ile!!!)
		//CODE name parametrelerin sıralama ve gruplamaları icin bagimsiz bir alan olucak, hicbir sıralama kosulları ile iliskisi yok, (DOKUMANTASYON "1.1.2.1" GİBİ TERİMLERLE GRUPLANABİLİCEK)
		//kullanıcı erisirken "CODE_NAME" i tuslayip parametreye erisicek (search fonksiyonları uzerinden),
		//yazılım erisirken ise, enum sırali liste uzerinden erisicek,
		//yeni parametre eklenirken, enum ile iliskili yere eklenecek, CODE da iliskili parametre grubuna uygun sallanacak.

		//SONUC: parametre FRAM ve RAM adresleri bagimziz oldu, UI nin erisim koduda bagimsiz oldu. MISS!!!

		//ONEMLİ SONUC!!! FRAM BİT ERİSİMİ COK GEREKLİ DEGİL HATTA SACMA, acilista degerler RAM e cekilirse, ram de update edileni geri FRAM e yazılırsa,
		//FRAM de bit erişimine gerek kalmaz!!! bit bit icin u8 yada u32 yazilir oda FRAM erisimi byte bazlı oldugu icin anlamsiz degil!!!
		//SADECE DISPLAY icin anlamli!!!
		//O DA SOYLE ANLAMSIZLASICAK,
		//MESELA PREFERENCES BİR BYTE EKRANDA 8 TANE 0/1 OLARAK AYARLANACAK, TYPE BINARY VS İLE,
		//BITLERİN ANLAMLARINA KULLANICI siemens deki gibi kılavuzdan bakacak!!!
		//IYI FIKIR!!! ır suru sacma display isinden kurtulunur!!!
		//budurumda ekran 8 li gosterime musait oldugundan binary ayar byte bazli olacak
		//!!!!!!!!!!!!!!!!!!!!!!
		//!!!!!!!!!!!!!!!!!!!!!!
		//!!!!!!!!!!!!!!!!!!!!!!

		//"CODE_NAME" i en son sallamak daha mantıklı


		//COOOK ONEMLI!!!
		//" sys_fram_definitions.h" deki
//		def_PRM_TABLE_POS__X__micro_degree__NOW_SEEN__s32_0
//		def_PRM_TABLE_POS__X__micro_degree__NOW__REAL__s32_0
//		def_PRM_TABLE_POS__X__micro_degree__PREVIOUS__SEEN__s32_0
//		def_PRM_TABLE_POS__THE_LAST_USAGE_MODE__u8
//		def_PRM_TABLE_POS__UNDO_MEMORY_INDEX__u8
//		def_PRM_TABLE_POS__UNDO_MEMORY_0_X_POSITION__s32_0
//		def_PRM_TABLE_POS__THE_LAST_POINT_INDEX__u8

		//kod icinde kullanıldıgı icin burayla (PARAMETER_TABLE) paralel olmak zorunda!!!, yada serach ile bulunarak işlenecek.


		//CODE_NAME	//NAME LANG TR					//NAME LANG EN					FRAM_ADDRESS											RAM_ADDRESS																	BYTE_LENGTH		u8_BIT_NUMBER	TYPE						MIN			MAX			s32_DEFAULT								u8_DOT_POSITION			u8_PERMISSIONS
		{ {1,0,0,0}, 	{ {___D,___I,___L,___ ,___ }, 	{___L,___A,___N,___G,___U}, }, 	def_FRAM_ADDR__LANGUAGE__u8,							(uint8_t*)(&u8_sys_ui__nvprm_LANGUAGE),										1,				0,				def_p_type__u8,			0,			1,			0,										255,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {1,0,0,1}, 	{ {___T,___R,___C,___H,___1 }, 	{___P,___R,___F,___R,___1}, }, 	def_FRAM_ADDR__USER_PREFERENCES_1,						(uint8_t*)(&u8_sys_ui__nvprm_USER_PREFERENCES_1),							1,				0,				def_p_type__u8_binary,	0,			255,		16,										255,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {1,0,0,2}, 	{ {___T,___R,___C,___H,___2 }, 	{___P,___R,___F,___R,___2}, }, 	def_FRAM_ADDR__USER_PREFERENCES_2,						(uint8_t*)(&u8_sys_ui__nvprm_USER_PREFERENCES_2),							1,				0,				def_p_type__u8_binary,	0,			255,		0,										255,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {1,0,0,3}, 	{ {___T,___R,___C,___H,___3 }, 	{___P,___R,___F,___R,___3}, }, 	def_FRAM_ADDR__USER_PREFERENCES_3,						(uint8_t*)(&u8_sys_ui__nvprm_USER_PREFERENCES_3),							1,				0,				def_p_type__u8_binary,	0,			255,		0,										255,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {1,0,0,4}, 	{ {___T,___R,___C,___H,___4 }, 	{___P,___R,___F,___R,___4}, }, 	def_FRAM_ADDR__USER_PREFERENCES_4,						(uint8_t*)(&u8_sys_ui__nvprm_USER_PREFERENCES_4),							1,				0,				def_p_type__u8_binary,	0,			255,		0,										255,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {2,0,0,0}, 	{ {___S,___N,___M,___O,___D},	{___L,___T,___M,___O,___D}, }, 	def_FRAM_ADDR__THE_LAST_USAGE_MODE__u8,					(uint8_t*)(&u8_sys_ui__nvprm_THE_LAST_USAGE_MODE),							1,				0,				def_p_type__u8,			0,			15,			0,										255,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {2,0,0,1}, 	{ {___S,___N,___ ,___I,___O},	{___L,___T,___ ,___I,___O}, }, 	def_FRAM_ADDR__THE_LAST_IO_STATES__u8,					(uint8_t*)(&u8_sys_ui__nvprm_THE_LAST_IO_STATES),							1,				0,				def_p_type__u8_binary,	0,			255,		0,										255,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {2,0,0,2}, 	{ {___O,___N,___C,___,___X},	{___P,___R,___V,___,___X}, }, 	def_FRAM_ADDR__X__micro_degree__NOW_SEEN__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_ABS_POS__X__micro_degree__NOW_SEEN),			4,				0,				def_p_type__s32,		-999999900,	999999900,	0,										2,					(0),						},
		{ {2,0,0,3}, 	{ {___S,___M,___D,___,___X},	{___N,___O,___W,___,___X}, }, 	def_FRAM_ADDR__X__micro_degree__NOW__REAL__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_ABS_POS__X__micro_degree__NOW__REAL),			4,				0,				def_p_type__s32,		-999999900,	999999900,	0,										2,					(0),						},
		{ {2,0,0,4}, 	{ {___H,___D,___F,___,___X},	{___T,___R,___T,___,___X}, }, 	def_FRAM_ADDR__X__micro_degree__PREVIOUS__SEEN__s32_0,	(uint8_t*)(&s32_sys_ui__nvprm_ABS_POS__X__micro_degree__PREVIOUS__SEEN),	4,				0,				def_p_type__s32,		-999999900,	999999900,	0,										2,					(0),						},
		{ {2,0,1,1}, 	{ {___N,___K,___T ,___I,___1},	{___P,___N,___T ,___I,___1}, }, def_FRAM_ADDR__IN_1_ACT_CONF_at_POINT_MODE__u8,			(uint8_t*)(&u8_sys_ui__nvprm__IN_1_ACT_CONF_at_POINT_MODE),					1,				0,				def_p_type__u8_binary,	0,			11,		def_u8_INPUT_ACTION__INCREMENT_INDEX,		255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {2,0,1,2}, 	{ {___N,___K,___T ,___I,___2},	{___P,___N,___T ,___I,___2}, }, def_FRAM_ADDR__IN_2_ACT_CONF_at_POINT_MODE__u8,			(uint8_t*)(&u8_sys_ui__nvprm__IN_2_ACT_CONF_at_POINT_MODE),					1,				0,				def_p_type__u8_binary,	0,			11,		def_u8_INPUT_ACTION__GOTO_START_INDEX_POS,	255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {2,0,1,3}, 	{ {___N,___K,___T ,___I,___3},	{___P,___N,___T ,___I,___3}, }, def_FRAM_ADDR__IN_3_ACT_CONF_at_POINT_MODE__u8,			(uint8_t*)(&u8_sys_ui__nvprm__IN_3_ACT_CONF_at_POINT_MODE),					1,				0,				def_p_type__u8_binary,	0,			11,		def_u8_INPUT_ACTION__GO,					255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {2,0,1,4}, 	{ {___N,___K,___T ,___I,___4},	{___P,___N,___T ,___I,___4}, }, def_FRAM_ADDR__IN_4_ACT_CONF_at_POINT_MODE__u8,			(uint8_t*)(&u8_sys_ui__nvprm__IN_4_ACT_CONF_at_POINT_MODE),					1,				0,				def_p_type__u8_binary,	0,			11,		def_u8_INPUT_ACTION__RESET_POS,				255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {2,0,2,1}, 	{ {___J,___O,___G ,___I,___1},	{___J,___O,___G ,___I,___1}, }, def_FRAM_ADDR__IN_1_ACT_CONF_at_JOGG_MODE__u8,			(uint8_t*)(&u8_sys_ui__nvprm__IN_1_ACT_CONF_at_JOGG_MODE),					1,				0,				def_p_type__u8_binary,	0,			11,		def_u8_INPUT_ACTION__RUN_FORWARD,			255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {2,0,2,2}, 	{ {___J,___O,___G ,___I,___2},	{___J,___O,___G ,___I,___2}, }, def_FRAM_ADDR__IN_2_ACT_CONF_at_JOGG_MODE__u8,			(uint8_t*)(&u8_sys_ui__nvprm__IN_2_ACT_CONF_at_JOGG_MODE),					1,				0,				def_p_type__u8_binary,	0,			11,		def_u8_INPUT_ACTION__RUN_REWERSE,			255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {2,0,2,3}, 	{ {___J,___O,___G ,___I,___3},	{___J,___O,___G ,___I,___3}, }, def_FRAM_ADDR__IN_3_ACT_CONF_at_JOGG_MODE__u8,			(uint8_t*)(&u8_sys_ui__nvprm__IN_3_ACT_CONF_at_JOGG_MODE),					1,				0,				def_p_type__u8_binary,	0,			11,		def_u8_INPUT_ACTION__STEP_FORWARD,			255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {2,0,2,4}, 	{ {___J,___O,___G ,___I,___4},	{___J,___O,___G ,___I,___4}, }, def_FRAM_ADDR__IN_4_ACT_CONF_at_JOGG_MODE__u8,			(uint8_t*)(&u8_sys_ui__nvprm__IN_4_ACT_CONF_at_JOGG_MODE),					1,				0,				def_p_type__u8_binary,	0,			11,		def_u8_INPUT_ACTION__STEP_REWERSE,			255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {2,2,2,1}, 	{ {___P,___T,___M ,___I,___N},	{___P,___T,___M ,___I,___N}, }, def_FRAM_ADDR__IN_PULSE_TRAIN_MIN__u8,					(uint8_t*)(&u8_sys_ui__nvprm__IN_PULSE_TRAIN_MIN),							1,				0,				def_p_type__u8_binary,	20,			200,		40,										255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {2,2,2,2}, 	{ {___P,___T,___M ,___A,___X},	{___P,___T,___M ,___A,___X}, }, def_FRAM_ADDR__IN_PULSE_TRAIN_MAX__u8,					(uint8_t*)(&u8_sys_ui__nvprm__IN_PULSE_TRAIN_MAX),							1,				0,				def_p_type__u8_binary,	20,			200,		90,										255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {3,0,0,0}, 	{ {___H,___Z,___L,___I,___X},	{___A,___C,___C,___,___X}, }, 	def_FRAM_ADDR__L64_ACC_12bits_R_WS__u16_0,				(uint8_t*)(&u16_sys_ui__nvprm_L64_ACC_12bits_R_WS),							2,				0,				def_p_type__u16,		0,			100,		8,										255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {3,0,0,1}, 	{ {___Y,___V,___S,___I,___X},	{___D,___E,___C,___,___X}, }, 	def_FRAM_ADDR__L64_DEC_12bits_R_WS__u16_0,				(uint8_t*)(&u16_sys_ui__nvprm_L64_DEC_12bits_R_WS),							2,				0,				def_p_type__u16,		0,			100,		8,										255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {3,0,0,2}, 	{ {___Y,___K,___S,___H,___X},	{___M,___X,___S,___P,___X}, }, 	def_FRAM_ADDR__L64_MAX_SPEED_10bits_R_WR__u16_0,		(uint8_t*)(&u16_sys_ui__nvprm_L64_MAX_SPEED_10bits_R_WR),					2,				0,				def_p_type__u16,		0,			200,		40,										255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {3,0,0,3}, 	{ {___D,___S,___K,___H,___X},	{___M,___N,___S,___P,___X}, }, 	def_FRAM_ADDR__L64_MIN_SPEED_13bits_R_WS__u16_0,		(uint8_t*)(&u16_sys_ui__nvprm_L64_MIN_SPEED_13bits_R_WS),					2,				0,				def_p_type__u16,		0,			4102,		0,										255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {3,0,0,4}, 	{ {___F,___S,___S,___P,___X},	{___F,___S,___S,___P,___X}, }, 	def_FRAM_ADDR__L64_FS_SPD_10bits_R_WR__u16_0,			(uint8_t*)(&u16_sys_ui__nvprm_L64_FS_SPD_10bits_R_WR),						2,				0,				def_p_type__u16,		0,			1023,		1023,									255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},

#ifdef		def_code_sw__DEFAULT_PARAMETERS_FOR__motor_86BHH65_270E_32A
		//bu cin motorda diger lead shine e gore akım biraz dusuk oldugundan,
		//akım parametrelerinin 50 olması motoru cok fazla ısıtıyor, 50 nin uzerinde surucu sogutucusu da cok ciddi ısınıyor.
		//kalkıs durus 50, run 40, tutma 30(sogusun diye) olucak
		//hız icin ise, 80 bu motorda torkun oldugu, elle tutulabilen yerler, hız kırk olacak,
		//efendi efendi dur kalk icin ise ivmeler 8 olacak.
		//motor pdf de seri baglantı paralel baglantı tork aynı!!! bu onemlı,
		//fakat seride 1.9 A, paralelde 3.8 A vermis

		//paralel denencek, seri hızlanınca dimdik aşagı dogru torku olduruyor,
		//paralelde tork hızlanmada sabit gibi.


		//https://openbuilds.com/threads/series-or-parallel-motor-winding-here-is-the-difference.802/
//		Series Advantages
//
//		    Decreased motor heating for fixed voltage drive
//		    Decreased power draw for fixed voltage drive
//
//		Series Disadvantages
//
//		    Decreased output torque for fixed voltage drive
//		    Decreased speed range due to large R / L time constant
//
//			Parallel Advantages:
//
//			    Greatly improved high speed performance.
//			    Improved mechanical power output from an increase in available torque at higher speeds
//
//			Parallel Disadvantages:
//
//			    Dramatically increased power dissipation in the motor and the drive circuit

		//sonuc COOOOOOK iyi, sabit hızda motoru mermere koyamicagım kadar takırtı vardı,
		//parale de ise kalkısdaki gibi sabit hızda sarsıntısız yuruyor, motoru mermere koyunca, tiz az bi ses geliyor sadece.
		//tork ise coil basına dusen akım yarıya indiginden yarı tork olmalı.
		//https://www.designworldonline.com/improving-high-speed-performance-of-hybrid-stepper-motors/?cn-reloaded=1
		//deki grafik gibi,
		//fakat tam hızda bile(40) elle tutulanıyor rotor.
		//dur kalkda daha smooth oldu.
		//coil akımları yarıya indigi icin motor ısınma yok, surucu ısınma eskisi gibi, akım aynı oldugundan.
		//simdi hız artabilir. ermanın orada test edilir.
		//defaultlar garantiler durumda kalsın calismayı.
		//OLEY BE!!!
		//EK NOT: 50 de motor ısınmıyor ama surucu sogutucu biraz ısınıyor!!! 30 bekleme kesin!!!

		{ {3,0,0,5}, 	{ {___T,___T,___M,___A,___X},	{___H,___L,___D,___C,___X}, }, 	def_FRAM_ADDR__L64_TVAL_HOLD_7bits_R_WR__u8,			(uint8_t*)(&u8_sys_ui__nvprm_L64_TVAL_HOLD_7bits_R_WR),						1,				0,				def_p_type__u8,			10,			100,		30,				255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {3,0,0,6}, 	{ {___C,___L,___S,___A,___X},	{___R,___U,___N,___C,___X}, }, 	def_FRAM_ADDR__L64_TVAL_RUN_7bits_R_WR__u8,				(uint8_t*)(&u8_sys_ui__nvprm_L64_TVAL_RUN_7bits_R_WR),						1,				0,				def_p_type__u8,			10,			100,		40,				255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {3,0,0,7}, 	{ {___H,___Z,___L,___A,___X},	{___A,___C,___C,___C,___X}, }, 	def_FRAM_ADDR__L64_TVAL_ACC_7bits_R_WR__u8,				(uint8_t*)(&u8_sys_ui__nvprm_L64_TVAL_ACC_7bits_R_WR),						1,				0,				def_p_type__u8,			10,			100,		50,				255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {3,0,0,8}, 	{ {___Y,___V,___S,___A,___X },	{___D,___E,___C,___C,___X}, }, 	def_FRAM_ADDR__L64_TVAL_DEC_7bits_R_WR__u8,				(uint8_t*)(&u8_sys_ui__nvprm_L64_TVAL_DEC_7bits_R_WR),						1,				0,				def_p_type__u8,			10,			100,		50,				255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
#else
		//evdeki ufak motor
		{ {3,0,0,5}, 	{ {___T,___T,___M,___A,___X},	{___H,___L,___D,___C,___X}, }, 	def_FRAM_ADDR__L64_TVAL_HOLD_7bits_R_WR__u8,			(uint8_t*)(&u8_sys_ui__nvprm_L64_TVAL_HOLD_7bits_R_WR),						1,				0,				def_p_type__u8,			0,			12,			9,				255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {3,0,0,6}, 	{ {___C,___L,___S,___A,___X},	{___R,___U,___N,___C,___X}, }, 	def_FRAM_ADDR__L64_TVAL_RUN_7bits_R_WR__u8,				(uint8_t*)(&u8_sys_ui__nvprm_L64_TVAL_RUN_7bits_R_WR),						1,				0,				def_p_type__u8,			0,			12,			9,				255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {3,0,0,7}, 	{ {___H,___Z,___L,___A,___X},	{___A,___C,___C,___C,___X}, }, 	def_FRAM_ADDR__L64_TVAL_ACC_7bits_R_WR__u8,				(uint8_t*)(&u8_sys_ui__nvprm_L64_TVAL_ACC_7bits_R_WR),						1,				0,				def_p_type__u8,			0,			12,			9,				255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {3,0,0,8}, 	{ {___Y,___V,___S,___A,___X },	{___D,___E,___C,___C,___X}, }, 	def_FRAM_ADDR__L64_TVAL_DEC_7bits_R_WR__u8,				(uint8_t*)(&u8_sys_ui__nvprm_L64_TVAL_DEC_7bits_R_WR),						1,				0,				def_p_type__u8,			0,			12,			9,				255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
#endif

		{ {3,0,0,9}, 	{ {___A,___S,___A,___L,___X},	{___O,___C,___D,___L,___X}, }, 	def_FRAM_ADDR__L64_OCD_TH_4bits_R_WR__u8,				(uint8_t*)(&u8_sys_ui__nvprm_L64_OCD_TH_4bits_R_WR),						1,				0,				def_p_type__u8,			0,			15,			15,				255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {3,0,1,0}, 	{ {___A,___L,___R,___M,___X},	{___A,___L,___R,___M,___X}, }, 	def_FRAM_ADDR__L64_ALARM_EN_8bits_R_WS__u8,				(uint8_t*)(&u8_sys_ui__nvprm_L64_ALARM_EN_8bits_R_WS),						1,				0,				def_p_type__u8_binary,	0,			10,			0,				255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {4,0,0,0}, 	{ {___G,___H,___I,___N,___D }, 	{___U,___M,___I,___N,___D}, }, 	def_FRAM_ADDR__UNDO_MEMORY_INDEX__u8,					(uint8_t*)(&u8_sys_ui__nvprm_UNDO_MEMORY_INDEX__u8),						1,				0,				def_p_type__u8,			0,			4,			0,				255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {4,0,0,1}, 	{ {___G,___H,___ ,___ ,___1},	{___U,___M,___ ,___ ,___1}, }, 	def_FRAM_ADDR__UNDO_MEMORY_0_X_POSITION__s32_0,			(uint8_t*)(&s32_sys_ui__nvprm_UNDO_MEMORY_X_POSITIONS[0]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {4,0,0,2}, 	{ {___G,___H,___ ,___ ,___2},	{___U,___M,___ ,___ ,___2}, }, 	def_FRAM_ADDR__UNDO_MEMORY_1_X_POSITION__s32_0,			(uint8_t*)(&s32_sys_ui__nvprm_UNDO_MEMORY_X_POSITIONS[1]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {4,0,0,3}, 	{ {___G,___H,___ ,___ ,___3},	{___U,___M,___ ,___ ,___3}, }, 	def_FRAM_ADDR__UNDO_MEMORY_2_X_POSITION__s32_0,			(uint8_t*)(&s32_sys_ui__nvprm_UNDO_MEMORY_X_POSITIONS[2]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {4,0,0,4}, 	{ {___G,___H,___ ,___ ,___4},	{___U,___M,___ ,___ ,___4}, }, 	def_FRAM_ADDR__UNDO_MEMORY_3_X_POSITION__s32_0,			(uint8_t*)(&s32_sys_ui__nvprm_UNDO_MEMORY_X_POSITIONS[3]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {4,0,0,5}, 	{ {___G,___H,___ ,___ ,___5},	{___U,___M,___ ,___ ,___5}, }, 	def_FRAM_ADDR__UNDO_MEMORY_4_X_POSITION__s32_0,			(uint8_t*)(&s32_sys_ui__nvprm_UNDO_MEMORY_X_POSITIONS[4]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {5,0,0,0}, 	{ {___D,___V,___D,___R,___C},	{___D,___V,___D,___G,___R}, }, 	def_FRAM_ADDR__DIVISOR_DEGREE_X__s32_0,					(uint8_t*)(&s32_sys_ui__nvprm_DIVISOR_DEGREE_X__s32_0),						4,				0,				def_p_type__s32,		1,			9999999,	3600000,		2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {5,0,0,1}, 	{ {___D,___V,___A,___D,___M},	{___D,___V,___S,___T,___P}, }, 	def_FRAM_ADDR__DIVISOR_STEP_X__u16_0,					(uint8_t*)(&u16_sys_ui__nvprm_DIVISOR_STEP_X__u16_0),						2,				0,				def_p_type__u16,		1,			1000,		72,				255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,0,1}, 	{ {___N,___H,___ ,___ ,___1},	{___P,___M,___ ,___ ,___1}, }, 	def_FRAM_ADDR__POINT_MEMORY_1_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[0]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	10000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,0,2}, 	{ {___N,___H,___ ,___ ,___2},	{___P,___M,___ ,___ ,___2}, }, 	def_FRAM_ADDR__POINT_MEMORY_2_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[1]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	20000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,0,3}, 	{ {___N,___H,___ ,___ ,___3},	{___P,___M,___ ,___ ,___3}, }, 	def_FRAM_ADDR__POINT_MEMORY_3_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[2]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	30000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,0,4}, 	{ {___N,___H,___ ,___ ,___4},	{___P,___M,___ ,___ ,___4}, }, 	def_FRAM_ADDR__POINT_MEMORY_4_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[3]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	40000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,0,5}, 	{ {___N,___H,___ ,___ ,___5},	{___P,___M,___ ,___ ,___5}, }, 	def_FRAM_ADDR__POINT_MEMORY_5_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[4]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	50000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,0,6}, 	{ {___N,___H,___ ,___ ,___6},	{___P,___M,___ ,___ ,___6}, }, 	def_FRAM_ADDR__POINT_MEMORY_6_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[5]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	60000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,0,7}, 	{ {___N,___H,___ ,___ ,___7},	{___P,___M,___ ,___ ,___7}, }, 	def_FRAM_ADDR__POINT_MEMORY_7_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[6]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	70000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,0,8}, 	{ {___N,___H,___ ,___ ,___8},	{___P,___M,___ ,___ ,___8}, }, 	def_FRAM_ADDR__POINT_MEMORY_8_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[7]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	80000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,0,9}, 	{ {___N,___H,___ ,___ ,___9},	{___P,___M,___ ,___ ,___9}, }, 	def_FRAM_ADDR__POINT_MEMORY_9_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[8]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	90000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,1,0}, 	{ {___N,___H,___ ,___1,___0},	{___P,___M,___ ,___1,___0}, }, 	def_FRAM_ADDR__POINT_MEMORY_10_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[9]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	100000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,1,1}, 	{ {___N,___H,___ ,___1 ,___1},	{___P,___M,___ ,___1 ,___1}, }, 	def_FRAM_ADDR__POINT_MEMORY_11_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[10]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	110000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,1,2}, 	{ {___N,___H,___ ,___1 ,___2},	{___P,___M,___ ,___1 ,___2}, }, 	def_FRAM_ADDR__POINT_MEMORY_12_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[11]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	120000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,1,3}, 	{ {___N,___H,___ ,___1 ,___3},	{___P,___M,___ ,___1 ,___3}, }, 	def_FRAM_ADDR__POINT_MEMORY_13_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[12]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	130000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,1,4}, 	{ {___N,___H,___ ,___1 ,___4},	{___P,___M,___ ,___1 ,___4}, }, 	def_FRAM_ADDR__POINT_MEMORY_14_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[13]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	140000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,1,5}, 	{ {___N,___H,___ ,___1 ,___5},	{___P,___M,___ ,___1 ,___5}, }, 	def_FRAM_ADDR__POINT_MEMORY_15_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[14]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	150000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,1,6}, 	{ {___N,___H,___ ,___1 ,___6},	{___P,___M,___ ,___1 ,___6}, }, 	def_FRAM_ADDR__POINT_MEMORY_16_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[15]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	160000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,1,7}, 	{ {___N,___H,___ ,___1 ,___7},	{___P,___M,___ ,___1 ,___7}, }, 	def_FRAM_ADDR__POINT_MEMORY_17_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[16]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	170000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,1,8}, 	{ {___N,___H,___ ,___1 ,___8},	{___P,___M,___ ,___1 ,___8}, }, 	def_FRAM_ADDR__POINT_MEMORY_18_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[17]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	180000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,1,9}, 	{ {___N,___H,___ ,___1 ,___9},	{___P,___M,___ ,___1 ,___9}, }, 	def_FRAM_ADDR__POINT_MEMORY_19_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[18]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	190000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,2,0}, 	{ {___N,___H,___ ,___2 ,___0},	{___P,___M,___ ,___2 ,___0}, }, 	def_FRAM_ADDR__POINT_MEMORY_20_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[19]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	200000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,2,1}, 	{ {___N,___H,___ ,___2 ,___1},	{___P,___M,___ ,___2 ,___1}, }, 	def_FRAM_ADDR__POINT_MEMORY_21_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[20]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	210000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,2,2}, 	{ {___N,___H,___ ,___2 ,___2},	{___P,___M,___ ,___2 ,___2}, }, 	def_FRAM_ADDR__POINT_MEMORY_22_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[21]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	220000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,2,3}, 	{ {___N,___H,___ ,___2 ,___3},	{___P,___M,___ ,___2 ,___3}, }, 	def_FRAM_ADDR__POINT_MEMORY_23_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[22]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	230000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,2,4}, 	{ {___N,___H,___ ,___2 ,___4},	{___P,___M,___ ,___2 ,___4}, }, 	def_FRAM_ADDR__POINT_MEMORY_24_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[23]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	240000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,2,5}, 	{ {___N,___H,___ ,___2 ,___5},	{___P,___M,___ ,___2 ,___5}, }, 	def_FRAM_ADDR__POINT_MEMORY_25_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[24]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	250000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,2,6}, 	{ {___N,___H,___ ,___2 ,___6},	{___P,___M,___ ,___2 ,___6}, }, 	def_FRAM_ADDR__POINT_MEMORY_26_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[25]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	260000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,2,7}, 	{ {___N,___H,___ ,___2 ,___7},	{___P,___M,___ ,___2 ,___7}, }, 	def_FRAM_ADDR__POINT_MEMORY_27_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[26]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	270000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,2,8}, 	{ {___N,___H,___ ,___2 ,___8},	{___P,___M,___ ,___2 ,___8}, }, 	def_FRAM_ADDR__POINT_MEMORY_28_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[27]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	280000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,2,9}, 	{ {___N,___H,___ ,___2 ,___9},	{___P,___M,___ ,___2 ,___9}, }, 	def_FRAM_ADDR__POINT_MEMORY_29_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[28]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	290000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,3,0}, 	{ {___N,___H,___ ,___3 ,___0},	{___P,___M,___ ,___3 ,___0}, }, 	def_FRAM_ADDR__POINT_MEMORY_30_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[29]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	300000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,3,1}, 	{ {___N,___H,___ ,___3 ,___1},	{___P,___M,___ ,___3 ,___1}, }, 	def_FRAM_ADDR__POINT_MEMORY_31_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[30]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	310000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,3,2}, 	{ {___N,___H,___ ,___3 ,___2},	{___P,___M,___ ,___3 ,___2}, }, 	def_FRAM_ADDR__POINT_MEMORY_32_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[31]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	320000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,3,3}, 	{ {___N,___H,___ ,___3 ,___3},	{___P,___M,___ ,___3 ,___3}, }, 	def_FRAM_ADDR__POINT_MEMORY_33_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[32]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	330000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,3,4}, 	{ {___N,___H,___ ,___3 ,___4},	{___P,___M,___ ,___3 ,___4}, }, 	def_FRAM_ADDR__POINT_MEMORY_34_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[33]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	340000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,3,5}, 	{ {___N,___H,___ ,___3 ,___5},	{___P,___M,___ ,___3 ,___5}, }, 	def_FRAM_ADDR__POINT_MEMORY_35_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[34]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	350000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,3,6}, 	{ {___N,___H,___ ,___3 ,___6},	{___P,___M,___ ,___3 ,___6}, }, 	def_FRAM_ADDR__POINT_MEMORY_36_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[35]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	360000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,3,7}, 	{ {___N,___H,___ ,___3 ,___7},	{___P,___M,___ ,___3 ,___7}, }, 	def_FRAM_ADDR__POINT_MEMORY_37_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[36]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	370000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,3,8}, 	{ {___N,___H,___ ,___3 ,___8},	{___P,___M,___ ,___3 ,___8}, }, 	def_FRAM_ADDR__POINT_MEMORY_38_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[37]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	380000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,3,9}, 	{ {___N,___H,___ ,___3 ,___9},	{___P,___M,___ ,___3 ,___9}, }, 	def_FRAM_ADDR__POINT_MEMORY_39_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[38]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	390000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,4,0}, 	{ {___N,___H,___ ,___4 ,___0},	{___P,___M,___ ,___4 ,___0}, }, 	def_FRAM_ADDR__POINT_MEMORY_40_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[39]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	400000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,4,1}, 	{ {___N,___H,___ ,___4 ,___1},	{___P,___M,___ ,___4 ,___1}, }, 	def_FRAM_ADDR__POINT_MEMORY_41_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[40]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	410000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,4,2}, 	{ {___N,___H,___ ,___4 ,___2},	{___P,___M,___ ,___4 ,___2}, }, 	def_FRAM_ADDR__POINT_MEMORY_42_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[41]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	420000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,4,3}, 	{ {___N,___H,___ ,___4 ,___3},	{___P,___M,___ ,___4 ,___3}, }, 	def_FRAM_ADDR__POINT_MEMORY_43_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[42]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	430000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,4,4}, 	{ {___N,___H,___ ,___4 ,___4},	{___P,___M,___ ,___4 ,___4}, }, 	def_FRAM_ADDR__POINT_MEMORY_44_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[43]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	440000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,4,5}, 	{ {___N,___H,___ ,___4 ,___5},	{___P,___M,___ ,___4 ,___5}, }, 	def_FRAM_ADDR__POINT_MEMORY_45_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[44]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	450000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,4,6}, 	{ {___N,___H,___ ,___4 ,___6},	{___P,___M,___ ,___4 ,___6}, }, 	def_FRAM_ADDR__POINT_MEMORY_46_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[45]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	460000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,4,7}, 	{ {___N,___H,___ ,___4 ,___7},	{___P,___M,___ ,___4 ,___7}, }, 	def_FRAM_ADDR__POINT_MEMORY_47_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[46]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	470000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,4,8}, 	{ {___N,___H,___ ,___4 ,___8},	{___P,___M,___ ,___4 ,___8}, }, 	def_FRAM_ADDR__POINT_MEMORY_48_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[47]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	480000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,4,9}, 	{ {___N,___H,___ ,___4 ,___9},	{___P,___M,___ ,___4 ,___9}, }, 	def_FRAM_ADDR__POINT_MEMORY_49_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[48]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	490000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,5,0}, 	{ {___N,___H,___ ,___5 ,___0},	{___P,___M,___ ,___5 ,___0}, }, 	def_FRAM_ADDR__POINT_MEMORY_50_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[49]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	500000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,5,1}, 	{ {___N,___H,___ ,___5 ,___1},	{___P,___M,___ ,___5 ,___1}, }, 	def_FRAM_ADDR__POINT_MEMORY_51_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[50]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	510000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,5,2}, 	{ {___N,___H,___ ,___5 ,___2},	{___P,___M,___ ,___5 ,___2}, }, 	def_FRAM_ADDR__POINT_MEMORY_52_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[51]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	520000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,5,3}, 	{ {___N,___H,___ ,___5 ,___3},	{___P,___M,___ ,___5 ,___3}, }, 	def_FRAM_ADDR__POINT_MEMORY_53_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[52]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	530000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,5,4}, 	{ {___N,___H,___ ,___5 ,___4},	{___P,___M,___ ,___5 ,___4}, }, 	def_FRAM_ADDR__POINT_MEMORY_54_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[53]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	540000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,5,5}, 	{ {___N,___H,___ ,___5 ,___5},	{___P,___M,___ ,___5 ,___5}, }, 	def_FRAM_ADDR__POINT_MEMORY_55_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[54]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	550000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,5,6}, 	{ {___N,___H,___ ,___5 ,___6},	{___P,___M,___ ,___5 ,___6}, }, 	def_FRAM_ADDR__POINT_MEMORY_56_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[55]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	560000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,5,7}, 	{ {___N,___H,___ ,___5 ,___7},	{___P,___M,___ ,___5 ,___7}, }, 	def_FRAM_ADDR__POINT_MEMORY_57_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[56]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	570000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,5,8}, 	{ {___N,___H,___ ,___5 ,___8},	{___P,___M,___ ,___5 ,___8}, }, 	def_FRAM_ADDR__POINT_MEMORY_58_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[57]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	580000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,5,9}, 	{ {___N,___H,___ ,___5 ,___9},	{___P,___M,___ ,___5 ,___9}, }, 	def_FRAM_ADDR__POINT_MEMORY_59_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[58]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	590000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,6,0}, 	{ {___N,___H,___ ,___6 ,___0},	{___P,___M,___ ,___6 ,___0}, }, 	def_FRAM_ADDR__POINT_MEMORY_60_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[59]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	600000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,6,1}, 	{ {___N,___H,___ ,___6 ,___1},	{___P,___M,___ ,___6 ,___1}, }, 	def_FRAM_ADDR__POINT_MEMORY_61_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[60]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	610000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,6,2}, 	{ {___N,___H,___ ,___6 ,___2},	{___P,___M,___ ,___6 ,___2}, }, 	def_FRAM_ADDR__POINT_MEMORY_62_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[61]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	620000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,6,3}, 	{ {___N,___H,___ ,___6 ,___3},	{___P,___M,___ ,___6 ,___3}, }, 	def_FRAM_ADDR__POINT_MEMORY_63_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[62]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	630000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,6,4}, 	{ {___N,___H,___ ,___6 ,___4},	{___P,___M,___ ,___6 ,___4}, }, 	def_FRAM_ADDR__POINT_MEMORY_64_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[63]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	640000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,6,5}, 	{ {___N,___H,___ ,___6 ,___5},	{___P,___M,___ ,___6 ,___5}, }, 	def_FRAM_ADDR__POINT_MEMORY_65_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[64]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	650000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,6,6}, 	{ {___N,___H,___ ,___6 ,___6},	{___P,___M,___ ,___6 ,___6}, }, 	def_FRAM_ADDR__POINT_MEMORY_66_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[65]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	660000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,6,7}, 	{ {___N,___H,___ ,___6 ,___7},	{___P,___M,___ ,___6 ,___7}, }, 	def_FRAM_ADDR__POINT_MEMORY_67_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[66]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	670000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,6,8}, 	{ {___N,___H,___ ,___6 ,___8},	{___P,___M,___ ,___6 ,___8}, }, 	def_FRAM_ADDR__POINT_MEMORY_68_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[67]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	680000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,6,9}, 	{ {___N,___H,___ ,___6 ,___9},	{___P,___M,___ ,___6 ,___9}, }, 	def_FRAM_ADDR__POINT_MEMORY_69_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[68]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	690000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,7,0}, 	{ {___N,___H,___ ,___7 ,___0},	{___P,___M,___ ,___7 ,___0}, }, 	def_FRAM_ADDR__POINT_MEMORY_70_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[69]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	700000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,7,1}, 	{ {___N,___H,___ ,___7 ,___1},	{___P,___M,___ ,___7 ,___1}, }, 	def_FRAM_ADDR__POINT_MEMORY_71_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[70]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	710000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,7,2}, 	{ {___N,___H,___ ,___7 ,___2},	{___P,___M,___ ,___7 ,___2}, }, 	def_FRAM_ADDR__POINT_MEMORY_72_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[71]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	720000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,7,3}, 	{ {___N,___H,___ ,___7 ,___3},	{___P,___M,___ ,___7 ,___3}, }, 	def_FRAM_ADDR__POINT_MEMORY_73_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[72]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	730000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,7,4}, 	{ {___N,___H,___ ,___7 ,___4},	{___P,___M,___ ,___7 ,___4}, }, 	def_FRAM_ADDR__POINT_MEMORY_74_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[73]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	740000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,7,5}, 	{ {___N,___H,___ ,___7 ,___5},	{___P,___M,___ ,___7 ,___5}, }, 	def_FRAM_ADDR__POINT_MEMORY_75_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[74]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	750000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,7,6}, 	{ {___N,___H,___ ,___7 ,___6},	{___P,___M,___ ,___7 ,___6}, }, 	def_FRAM_ADDR__POINT_MEMORY_76_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[75]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	760000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,7,7}, 	{ {___N,___H,___ ,___7 ,___7},	{___P,___M,___ ,___7 ,___7}, }, 	def_FRAM_ADDR__POINT_MEMORY_77_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[76]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	770000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,7,8}, 	{ {___N,___H,___ ,___7 ,___8},	{___P,___M,___ ,___7 ,___8}, }, 	def_FRAM_ADDR__POINT_MEMORY_78_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[77]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	780000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,7,9}, 	{ {___N,___H,___ ,___7 ,___9},	{___P,___M,___ ,___7 ,___9}, }, 	def_FRAM_ADDR__POINT_MEMORY_79_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[78]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	790000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,0,8,0}, 	{ {___N,___H,___ ,___8 ,___0},	{___P,___M,___ ,___8 ,___0}, }, 	def_FRAM_ADDR__POINT_MEMORY_80_X_POSITION__s32_0,		(uint8_t*)(&s32_sys_ui__nvprm_POINT_MEMORY_X_POSITIONS[79]),					4,				0,				def_p_type__s32,		-9999999,	9999999,	800000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,6,0,0}, 	{ {___S,___N,___N,___K,___T},	{___L,___T,___P,___N,___T}, }, 	def_FRAM_ADDR__THE_LAST_POINT_INDEX__u8,					(uint8_t*)(&u8_sys_ui__nvprm_THE_LAST_POINT_INDEX),								1,				0,				def_p_type__u8,			1,			80,			1,				255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,6,0,1}, 	{ {___N,___K,___B,___S,___L},	{___P,___N,___S,___T,___R}, }, 	def_FRAM_ADDR__POINT_INDEX_START__u8,						(uint8_t*)(&u8_sys_ui__nvprm_POINT_INDEX_START),								1,				0,				def_p_type__u8,			1,			80,			1,				255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {6,6,0,2}, 	{ {___N,___K,___B,___I,___T},	{___P,___N,___S,___T,___P}, }, 	def_FRAM_ADDR__POINT_INDEX_END__u8,							(uint8_t*)(&u8_sys_ui__nvprm_POINT_INDEX_END),									1,				0,				def_p_type__u8,			1,			80,			80,				255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {7,0,0,0}, 	{ {___D,___R,___T,___C,___R},	{___J,___O,___G,___C,___O}, }, 	def_FRAM_ADDR__JOGG_COEFF_DEGREE_X__s32_0,				(uint8_t*)(&s32_sys_ui__nvprm_JOGG_COEFF_DEGREE_X),							4,				0,				def_p_type__s32,		1,			1000,		100,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {7,0,0,1}, 	{ {___S,___A,___L,___G,___I},	{___B,___K,___L,___S,___H}, }, 	def_FRAM_ADDR__BACKLASH_DEGREE_X__s32_0,				(uint8_t*)(&s32_sys_ui__nvprm_BACKLASH_DEGREE_X),							4,				0,				def_p_type__s32,		0,			50000,		10000,			2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {7,0,0,2}, 	{ {___F,___B,___K,___Z,___M }, 	{___B,___W,___T,___T,___M}, }, 	def_FRAM_ADDR__BREAK_OUTPUT_WAIT_TIME__u8,				(uint8_t*)(&u8_sys_ui__nvprm_BREAK_OUTPUT_WAIT_TIME),						1,				0,				def_p_type__u8,			2,			60,			10,				255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {8,0,0,0}, 	{ {___P,___X,___ ,___E,___1},	{___P,___X,___ ,___E,___1}, }, 	def_FRAM_ADDR__SHORTCUT_PX_D1__s32_0,					(uint8_t*)(&s32_sys_ui__nvprm_SHORTCUT_PX_D1),								4,				0,				def_p_type__s32,		0,			9999,		5001,			255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {8,0,0,1}, 	{ {___P,___X,___ ,___E,___2},	{___P,___X,___ ,___E,___2}, }, 	def_FRAM_ADDR__SHORTCUT_PX_D2__s32_0,					(uint8_t*)(&s32_sys_ui__nvprm_SHORTCUT_PX_D2),								4,				0,				def_p_type__s32,		0,			9999,		5000,			255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {8,0,0,2}, 	{ {___P,___X,___ ,___F,___3},	{___P,___X,___ ,___F,___3}, }, 	def_FRAM_ADDR__SHORTCUT_PX_E3__s32_0,					(uint8_t*)(&s32_sys_ui__nvprm_SHORTCUT_PX_E3),								4,				0,				def_p_type__s32,		0,			9999,		6000,			255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {8,0,0,3}, 	{ {___P,___X,___ ,___F,___4},	{___P,___X,___ ,___F,___4}, }, 	def_FRAM_ADDR__SHORTCUT_PX_E4__s32_0,					(uint8_t*)(&s32_sys_ui__nvprm_SHORTCUT_PX_E4),								4,				0,				def_p_type__s32,		0,			9999,		9000,			255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {8,0,0,4}, 	{ {___F,___X,___ ,___G,___1},	{___F,___X,___ ,___G,___1}, }, 	def_FRAM_ADDR__SHORTCUT_FX_F1__s32_0,					(uint8_t*)(&s32_sys_ui__nvprm_SHORTCUT_FX_F1),								4,				0,				def_p_type__s32,		0,			9999,		1001,			255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {8,0,0,5}, 	{ {___F,___X,___ ,___G,___2},	{___F,___X,___ ,___G,___2}, }, 	def_FRAM_ADDR__SHORTCUT_FX_F2__s32_0,					(uint8_t*)(&s32_sys_ui__nvprm_SHORTCUT_FX_F2),								4,				0,				def_p_type__s32,		0,			9999,		9000,			255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {8,0,0,6}, 	{ {___F,___X,___ ,___H,___3},	{___F,___X,___ ,___H,___3}, }, 	def_FRAM_ADDR__SHORTCUT_FX_G3__s32_0,					(uint8_t*)(&s32_sys_ui__nvprm_SHORTCUT_FX_G3),								4,				0,				def_p_type__s32,		0,			9999,		3001,			255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {8,0,0,7}, 	{ {___F,___X,___ ,___H,___4},	{___F,___X,___ ,___H,___4}, }, 	def_FRAM_ADDR__SHORTCUT_FX_G4__s32_0,					(uint8_t*)(&s32_sys_ui__nvprm_SHORTCUT_FX_G4),								4,				0,				def_p_type__s32,		0,			9999,		3000,			255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {9,0,0,0}, 	{ {___S,___P,___A,___Y,___R},	{___C,___P,___S,___E,___T}, }, 	def_FRAM_ADDR__CURRENT_POS_SET__DEGREE_X__s32_0,	 	(uint8_t*)(&s32_sys_ui__nvprm_CURRENT_POS_SET__DEGREE_X),					4,				0,				def_p_type__s32,		-9999999,	9999999,	0,				2,					(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {9,0,0,1}, 	{ {___S,___B,___T,___H,___Z},	{___C,___N,___S,___T,___S}, }, 	def_FRAM_ADDR__RUN_WITH_CONSTANT_SPEED__s32_0,			(uint8_t*)(&s32_sys_ui__nvprm_RUN_WITH_CONSTANT_SPEED),						4,				0,				def_p_type__s32,		0,			15625,		1000,			255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {9,1,0,0}, 	{ {___M,___M,___D,___P,___S},	{___M,___M,___D,___P,___S}, }, 	def_FRAM_ADDR__MOTOR_MICRO_DEG_PER_STEP__s32_0,	 		(uint8_t*)(&s32_sys_ui__nvprm_MOTOR_MICRO_DEG_PER_STEP),					4,				0,				def_p_type__s32,		28125,		450000,		112500,			255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {9,1,0,1}, 	{ {___D,___V,___O,___R,___N},	{___D,___V,___R,___T,___O}, }, 	def_FRAM_ADDR__DIVISOR_RATIO_X__u16_0,					(uint8_t*)(&u16_sys_ui__nvprm_DIVISOR_RATIO_X),								2,				0,				def_p_type__u16,		1,			500,		360,			255,				(def_p_PERM__W+def_p_PERM__USER_ACCESS),						},
		{ {9,9,9,9}, 	{ {___V,___R,___S,___N,___ },	{___V,___R,___S,___N,___} , }, 	def_FRAM_ADDR__VERSION__s32_0,							(uint8_t*)(&s32_sys_ui__nvprm_VERSION),										4,				0,				def_p_type__s32,		1,			9999999,	180605,			255,				(0),						},

		// toplam 125 parametre, +3 =128

		//@@@revision: 2018_03_22_16_01: input action conf. parameters:
		//icin + 8 =136

		//COOOK ONEMLI!!!
		//" sys_fram_definitions.h" deki
//		def_PRM_TABLE_POS__X__micro_degree__NOW_SEEN__s32_0
//		def_PRM_TABLE_POS__X__micro_degree__NOW__REAL__s32_0
//		def_PRM_TABLE_POS__X__micro_degree__PREVIOUS__SEEN__s32_0
//		def_PRM_TABLE_POS__THE_LAST_USAGE_MODE__u8
//		def_PRM_TABLE_POS__UNDO_MEMORY_INDEX__u8
//		def_PRM_TABLE_POS__UNDO_MEMORY_0_X_POSITION__s32_0
//		def_PRM_TABLE_POS__THE_LAST_POINT_INDEX__u8

		//kod icinde kullanıldıgı icin burayla (PARAMETER_TABLE) paralel olmak zorunda!!!, yada serach ile bulunarak işlenecek.

};


//bu array "PARAMETER_TABLE" ile paralel calisir!!!
u8_PARAMETER_COMMAND 	u8_array_PARAMETER_COMMAND_FLAGS[def_u16_sys_fram_NUMBER_of_PARAMETERS];
uint16_t	u16_sys_fram__CAPTURED_COMMAND_REQUEST__TABLE_INDEX=0;




//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
//***********
//*********
//*******
//*****
//***
//*



#endif /* SYS_FRAM_PRIVATE_H_ */
