//=======================================================
//---- Проект 405---------
//=======================================================

#define GetSensConfig(nTepl,nSens)	GD.MechConfig[nTepl].RNum[nSens+SUM_NAME_INSENS]
#define GetInputConfig(nTepl,nSens)	GD.MechConfig[nTepl].RNum[nSens+SUM_NAME_INPUTS]
#define GetMetSensConfig(nSens)	GD.MechConfig[0].RNum[nSens+SUM_NAME_OUTSENS]

#define tpRELAY		1
#define tpLEVEL		2
#define tpSUM		3

/*Смещения датчиков в общем массиве*/
#define cSmOutTSens		0
#define cSmFARSens		1
#define cSmVWindSens	2
#define cSmDWindSens	3
#define cSmRainSens		4
#define cSmOutRHSens	5
#define cSmMainTSens	6
#define cSmPresureSens	8

#define cSmTSens1		0
#define cSmTSens2		1
#define cSmTSens3		2
#define cSmTSens4		3
#define cSmTSens5		4
#define cSmTSens6		5

#define cSmRHSens		6
#define cSmRHSens1		7
#define cSmRHSens2		8
#define cSmInLightSens	10

#define cSmT1AHUOutSens	14

#define cSmOverPSens	15   // датчик избыточного давления
#define cSmOverPSensAHU	16	 // датчик избыточного давления камеры AHU  // был датчик крыши

// 17 пропущенный датик это датчик положения Клапана циркуляции

#define cSmGlassSens	18
#define cSmCOSens		11
//#define cSmTCSens		1
#define cSmTAHUOutSens	20
#define cSmRHAHUOutSens	13

#define cSmWinNSens		21
#define cSmWinSSens		22
#define cSmScreenSens	23
#define cSmWaterSens	24
#define cSmAHUPipeSens	26

#define cConfSSystem		10
#define cConfSOutput		46  //46    // NEW LIGHT
#define cConfSInputs		7
#define cConfSSens			30
#define cConfSMetSens		11
#define cSHandCtrl			cConfSOutput
#define cSRegCtrl			25   // 24
#define cSDiskrCtrl			22	 // 22

#define SUM_NAME_INPUTS			(cConfSOutput)
#define SUM_NAME_INSENS			(SUM_NAME_INPUTS+cConfSInputs)
#define SUM_NAME_OUTSENS		(SUM_NAME_INSENS+cConfSSens)
#define SUM_NAME_CONF			(SUM_NAME_OUTSENS+cConfSMetSens)

#define MAX_SUM_RELAY	80

/*const char charTable[256] = {
        0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,
        0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,
        0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,
        0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,
        0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,
        0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x5B,0x5C,0x5D,0x5E,0x5F,
        0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,
        0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x7B,0x7C,0x7D,0x7E,0x7F,
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,
        0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F,
        0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA2,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF,
        0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB5,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF,
        0x41,0xA0,0x42,0xA1,0xE0,0x45,0xA3,0xA4,0xA5,0xA6,0x4B,0xA7,0x4D,0x48,0x4F,0xA8,
        0x50,0x43,0x54,0xA9,0xAA,0x58,0xE1,0xAB,0xAC,0xE2,0xAD,0xAE,0x62,0xAF,0xB0,0xB1,
        0x61,0xB2,0xB3,0xB4,0xE3,0x65,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0x6F,0xBE,
        0x70,0x63,0xBF,0x79,0xE4,0x78,0xE5,0xC0,0xC1,0xE6,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7};	*/

eNameASens code  NameSensConfig[cConfSSens+cConfSMetSens]={
		/*
		  П - Номер порта
		  В - Номер входа
		  Мин - минимальное измеряемое значение
		  Макс - максимальное измеряемое значение
		  НЭ1 - напряжение эталон1
		  НЭ2 - напряжение эталон2
		  ЗЭ1 - значение эталон1
		  ЗЭ2 - значение эталон2
		  НМин - минимальное напряжение
		  НМкс - максимальное напряжение
		  У - тип усреднения датчика*/
/*Название датчика												    Формат	Ед.изм	Тип датч	Т  Вых  Мин	  Макс       НЭ1	 НЭ2	ЗЭ1     ЗЭ2     НМин	НМкс     Усреднение Цифровой фильтр*/
//0
{"Tem\310 air1#Te\274\276 \263o\267\343\311xa 1",					SSpS0,  cuT,	cTypeAnal,	3,	0,	0,	  9900,		2930,	3230,	2000,	5000,	2000,	5000,	c3MidlSens,		50}, /* Температура воздуха 1*/
{"Tem\310 air2#Te\274\276 \263o\267\343\311xa 2",					SSpS0,	cuT,	cTypeAnal,	3,	0,	0,	  9900,		2930,	3230,	2000,	5000,	2000,	5000,	c3MidlSens,		50}, /* Температура контроль 2*/
{"Tem\310 air3#Te\274\276 \263o\267\343\311xa 3",					SSpS0,	cuT,	cTypeAnal,	3,	0,	0,	  9900,		2930,	3230,	2000,	5000,	2000,	5000,	c3MidlSens,		50}, /* Температура контроль 3*/
{"Tem\310 air4#Te\274\276 \263o\267\343\311xa 4",					SSpS0,	cuT,	cTypeAnal,	3,	0,	0,	  9900,		2930,	3230,	2000,	5000,	2000,	5000,	c3MidlSens,		50}, /* Температура контроль 4*/
{"Tem\310 air5#Te\274\276 \263o\267\343\311xa 5",					SSpS0,	cuT,	cTypeAnal,	3,	0,	0,	  9900,		2930,	3230,	2000,	5000,	2000,	5000,	c3MidlSens,		50}, /* Температура контроль 3*/
{"Tem\310 air6#Te\274\276 \263o\267\343\311xa 6",					SSpS0,	cuT,	cTypeAnal,	3,	0,	0,	  9900,		2930,	3230,	2000,	5000,	2000,	5000,	c3MidlSens,		50}, /* Температура контроль 4*/
//6
{"Humidit\311 1#B\273a\266\275oc\277\304 1",						SSpS0,  cuPr,	cTypeRH,	0,	0,	200,  9800,		878,	3097,	0,		7530,	800, 	5000,	cExpMidlSens,	1000}, /* Влажность воздуха 1*/
{"Humidit\311 2#B\273a\266\275oc\277\304 2",						SSpS0,  cuPr,	cTypeRH,	0,	0,	200,  9800,		878, 	3097,	0,		7530,	800, 	5000,	cExpMidlSens,	1000}, /* Влажность воздуха 2*/
{"Humidit\311 3#B\273a\266\275oc\277\304 3",						SSpS0,  cuPr,	cTypeRH,	0,	0,	200,  9800,		878,	3097,	0,		7530,	800, 	5000,	cExpMidlSens,	1000}, /* Влажность воздуха 3*/
{"CO2 AHU#CO2 AHU \311\310o\263e\275\304",							SSSS,   cuPpm,	cTypeRH,	0,	0,	100,  2000,		0,  	5000,	0,   	2000,	50,  	5000,	c3MidlSens,		80}, /*Концентрация СО2*/
//{"Humidit\311 4#B\273a\266\275oc\277\304 4",						SSpS0,  cuPr,	cTypeRH,	0,	0,	200,  9800,		878, 	3097,	0,		7530,	800, 	5000,	cExpMidlSens,	1000}, /* Влажность воздуха 2*/
{"Inside light#B\275\311\277 c\263e\277",							SSSS, 	cuBt,	cTypeAnal,	11,	0,	0,	  1500,		15,  	2250,	0,   	1000, 	0,   	5000,	c3MidlSens,		100}, /* Внутренний свет*/
{"CO2#CO2 \311\310o\263e\275\304",									SSSS,   cuPpm,	cTypeRH,	0,	0,	100,  2000,		0,  	5000,	0,   	2000,	50,  	5000,	cExpMidlSens,	80}, /*Концентрация СО2*/
//12
{"Tem\310 panel#Te\274\276 \276a\275e\273\270",						SSpS0,  cuT,	cTypeAnal,	3,	0,	1,	  9900,		2930,	3230,	2000,	5000,	2000,	5000,	c3MidlSens,		80}, /* Температура вход воздуха 1*/
{"Humidit AHU\311 3#B\273a\266\275oc\277\304  AHU",					SSpS0,  cuPr,	cTypeRH,	0,	0,	200,  9800,		878,	3097,	0,		7530,	800, 	5000,	cExpMidlSens,	1000}, /* Влажность воздуха AHU*/
//14
{"Tem\310 cool #Te\274\276 ox\273a\266\343e\275",					SSpS0,  cuT,	cTypeAnal,	3,	0,	1,	  9900,		2930,	3230,	2000,	5000,	2000,	5000,	c3MidlSens,		80}, /* Температура охлаждающей воды*/
{"Over\310ressure#\245\267\262\303\277 \343a\263\273e\275",			SSpS0,  cuPa,	cTypeAnal,	0,	0,	1,	  9900,		0,		3000,	0,		3000,	0,		5000,	c3MidlSens,		80}, /* Избыточное давление*/
//16
#ifdef RICHEL
{"Over\310ressure AHU#\245\267\262\303\277 AHU",					SSpS0,  cuPa,	cTypeAnal,	0,	0,	1,	  9900,		0,		3000,	0,		3000,	0,		5000,	c3MidlSens,		80},  /* Избыточное давление AHU*/
{"Position circ#Position circ",										SSSpS,	cuPr,	cTypeScreen,1,	0,	0,	  1000, 	0,		5000,	0,	  	1000, 	0,		5000,	c3MidlSens,		400}, /*Сокодвижение*/
//{"Position circ#Position circ",										SSSpS,	cuPr,	cTypeAnal,	1,	0,	0,	  1000, 	0,		5000,	0,	  	1000, 	0,		5000,	c3MidlSens,		400}, /*Положение циркл клапана*/
																	//SSSS,   cuT,	cTypeAnal,	3,	0,	0,	  1000,		2930,	3230,	2000,	5000,	2000,	5000,	c3MidlSens,		80}, /* Температура почвы*/
#endif
#ifdef KUBO
{"Tem\310 roof#Te\274\276 \272\310o\263\273\270",					SSpS0,  cuT,	cTypeAnal,	3,	0,	0,	  9900,		2930,	3230,	2000,	5000,	2000,	5000,	c3MidlSens,		80}, /* Температура кровли*/
{"Tem\310 soil#Te\274\276 \276o\300\263\303",						SSpS0,  cuT,	cTypeAnal,	3,	0,	1,	  9900,		2930,	3230,	2000,	5000,	2000,	5000,	c3MidlSens,		80}, /* Температура почвы*/
#endif
//{"Tem\310 soil#Te\274\276 \276o\300\263\303",						SSpS0,  cuT,	cTypeAnal,	3,	0,	1,	  9900,		2930,	3230,	2000,	5000,	2000,	5000,	c3MidlSens,		80}, /* Температура почвы*/
{"Tem\310 glass#Te\274\276 c\277e\272\273a",						SSpS0,  cuT,	cTypeAnal,	3,	0,	-2000,9900,		2930,	3230,	2000,	5000,	2000,	5000,	c3MidlSens,		80}, /* Температура стекла*/
{"Tem\310 in AHU#Te\274\276 \263xo\343a AHU",						SSpS0,	cuT,	cTypeAnal,	3,	0,	1,	  9900,		2930,	3230,	2000,	5000,	2000,	5000,	c3MidlSens,		80}, /* Т входа в AHU*/
{"Tem\310 out AHU#Te\274\276 \263\303xo\343a AHU",					SSpS0,	cuT,	cTypeAnal,	3,	0,	1,	  9900,		2930,	3230,	2000,	5000,	2000,	5000,	c3MidlSens,		80}, /*Т выхода из AHU*/
//21
{"N vent \310os#\250o\273o\266 \344\310a\274\311\264\270 C",		SSSpS,	cuPr,	cTypeFram,	1,	0,	0,	  1000, 	0,		5000,	0,	  	1000, 	0,		5000,	c3MidlSens,		400}, /*Сокодвижение*/
{"Rezerv#He \270c\276o\273\304\267",								SSSpS,	cuPr,	cTypeFram,	1,	0,	0,	  1000, 	0,		5000,	0,	  	1000, 	0,		5000,	c3MidlSens,		400}, /*Размер плода*/
{"Screen \310os#\250o\273o\266 \305\272\310a\275",					SSSpS,	cuPr,	cTypeScreen,1,	0,	0,	  1000, 	0,		5000,	0,	  	1000, 	0,		5000,	c3MidlSens,		400}, /*Сокодвижение*/
//20
{"Tem\310 \310i\310e1#Te\274\276 \272o\275\277\311\310a 1",			SSSpS,	cuT,	cTypeAnal,	3,	0,	10,	  1500,		2930,	3230,	200,	500,	2000,	5000,	c3MidlSens,		100}, /*Т прям контура1*/
{"Tem\310 \310i\310e2#Te\274\276 \272o\275\277\311\310a 2",			SSSpS,	cuT,	cTypeAnal,	3,	0,	10,	  1500,		2930,	3230,	200,	500,	2000,	5000,	c3MidlSens,		100}, /*Т прям контура2*/
{"Tem\310 \310i\310e3#Te\274\276 \272o\275\277\311\310a 3",			SSSpS,	cuT,	cTypeAnal,	3,	0,	10,	  1500,		2930,	3230,	200,	500,	2000,	5000,	c3MidlSens,		100}, /*Т прям контура3*/
{"Tem\310 \310i\310e4#Te\274\276 \272o\275\277\311\310a 4",			SSSpS,	cuT,	cTypeAnal,	3,	0,	10,	  1500,		2930,	3230,	200,	500,	2000,	5000,	c3MidlSens,		100}, /*Т прям контура4*/
{"Tem\310 \310i\310e5#Te\274\276 \272o\275\277\311\310a 5",			SSSpS,	cuT,	cTypeAnal,	3,	0,	10,	  1500,		2930,	3230,	200,	500,	2000,	5000,	c3MidlSens,		100}, /*Т прям контура5*/
{"Tem\310 \310i\310e6#Te\274\276 \272o\275\277\311\310a 6",			SSSpS,	cuT,	cTypeAnal,	3,	0,	10,	  1500,		2930,	3230,	200,	500,	2000,	5000,	c3MidlSens,		100}, /*Т прям контура6*/
//{"Tem\310 \310i\310e AHU#Te\274\276 \272o\275\277 AHU",				SSSpS,	cuT,	cTypeAnal,	3,	0,	10,	  1500,		2930,	3230,	200,	500,	2000,	5000,	c3MidlSens,		100}, /*Т контура AHU*/
//26
{"Tem\310 out#Te\274\276 \275a\310\311\266\275\307\307",			SSpS0,	cuT,	cTypeAnal,	3,	0,	-6000,9900,		2930,	3230,	2000,	5000,	2000,	5000,	c3MidlSens,		80},  /*Температура наружняя*/
{"FAR#\245\275\277e\275c\270\263\275oc\277\304 co\273\275\345a",	SSSS,	cuBt,	cTypeSun,	11,	0,	0,	  1500,		15,  	2250,	0,   	5000, 	0,   	5000,	c3MidlSens,		200}, /*Солнечная радиация*/
{"Wind s\310eed#C\272o\310oc\277\304 \263e\277\310a",				SSpS0,	cuMSec,	cTypeMeteo,	2,	0,	0,	  9900,		60,  	0,   	1,   	0,  	0,   	0,   	cNoMidlSens,	100}, /*Скорость ветра*/
{"Wind direct#Ha\276\310a\263\273 \263e\277\310a",					SSSi,	cuGr,	cTypeMeteo,	2,	0,	0,	  360, 		0,   	4520,	0,   	360, 	0,   	0,   	cNoMidlSens,	40},  /*Направление ветра*/
{"Rain#Oca\343\272\270",											SSSi,	cu,		cTypeRain,	0,	0,	0,    10,  		250, 	650, 	-10, 	10,  	0,   	5000,   cNoMidlSens,	20},  /*Осадки*/
{"Humidit\311 out#B\273a\266\275oc\277\304",						SSpS0,	cuPr,	cTypeAnal,	0,	0,	200,  9900,		800, 	5000,	0,   	0,   	0,   	5000,   c3MidlSens,		100}, /*Влажность наружняя*/
{"T from boil#Te\274\276 \276\310\307\274o\246",					SSSpS,	cuT,	cTypeAnal,	3,	0,	10,	  1500,		2930,	3230,	200,	500,	2000,	5000,	c3MidlSens,		100}, /*Температура воды прямой*/
{"T to boil#Te\274\276 o\262\310a\277\272\270",						SSSpS,	cuT,	cTypeAnal,	3,	0,	10,	  1500,		2930,	3230,	200,	500,	2000,	5000,	c3MidlSens,		100}, /*Температура воды обратной*/
{"P from boil#\340a\263\273e\275\270e \276\310\307\274o\246",		SSpS0,	cuPa,	cTypeAnal,	3,	0,	0,	  1500,		500, 	4500,	0,   	1464, 	0,   	5000,   c3MidlSens,		100}, /*Давление воды прямой*/
{"P to boil#\340a\263\273e\275\270e o\262\310a\277\272\270",		SSpS0,	cuPa,	cTypeAnal,	3,	0,	0,    1500,		500, 	4500,	0,   	1464, 	0,   	5000,   c3MidlSens,		100}, /*Давление воды обратной*/
{"Quantit\311#Pacxo\343",											SSSpS,	cuPa,	cTypeAnal,	0,	0,	0,    9000,		500, 	4500,	0,   	105, 	0,   	5000,   c3MidlSens,		100}, /*Резерв*/
        };

#define cSKontur		11
#define cSWaterKontur	6


/*Константы смещения контуров*/
#define cSmKontur1		0
#define cSmKontur2		1
#define cSmKontur3		2
#define cSmKontur4		3
#define cSmKontur5		4
#define cSmKonturAHU	5
#define cSmWindowUnW	6
#define cSmAHUSpd		7
#define cSmUCValve		8
#define cSmAHURez		9
#define cSmScreen		10

/*----------------------------------*/

/*Константы смещения ручного управления и биты его*/
#define cHSmMixVal		0
#define cHSmWinN		6
#define cHSmWinS		7
#define cHSmWinN2		8
#define cHSmWinN3		9

#ifdef KUBO
	#define cHSmWinN4		10
#endif
#ifdef RICHEL
	#define cHSmUCOutValve	10
#endif


#define cHSmUCValve		11
#define cHSmAHUSpeed1	12
#define cHSmAHUSpeed2	13
#define cHSmScrTH		14
#define cHSmScrSH		15
#define cHSmScrV_S1		16
#define cHSmCO2			17
#define cHSmAHUPad		18
#define cHSmLight		19

#warning NEW Mech							!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! Изменение
#define cHSmInRH		20
#define cHSmAlarmVent	21
#define cHSmCO2request	22
#define cHSmHeaterCable	23				// new

#define cHSmPump		24
#define cHSmVent		30
#define cHSmHeat		31
#define cHSmDiodLight	32				// new
#define cHSmSIOPump		33
#define cHSmSIOVals		34
#define cHSmAHUPump		35
#define cHSmAlarm		36
#define cHSmRegs		37


#warning new mech

#define cHSmRegs1		38
#define cHSmRegs2		39
#define cHSmRegs3		40
#define cHSmRegs4		41



#define cHSmAlarmVentPosition	47

#define cHSmLight50		48
#define cHSmLight100	49


typedef struct  eeNameConfig
        {
        char Name[30];
        char Tip;
        char Min;
        char Max;
        } eNameConfig;

eNameConfig NameOutputConfig[cConfSOutput]={
/*0 Клапан 1*/ 			{"Mixing valve 1#C\274ec \272\273a\276a\275 1",tpRELAY,0,MAX_SUM_RELAY},
/*1 Клапан 2*/			{"Mixing valve 2#C\274ec \272\273a\276a\275 2",tpRELAY,0,MAX_SUM_RELAY},
/*2 Клапан 3*/			{"Mixing valve 3#C\274ec \272\273a\276a\275 3",tpRELAY,0,MAX_SUM_RELAY},
/*3 Клапан 4*/ 			{"Mixing valve 4#C\274ec \272\273a\276a\275 4",tpRELAY,0,MAX_SUM_RELAY},
/*4 Клапан 5*/			{"Mixing valve 5#C\274ec \272\273a\276a\275 5",tpRELAY,0,MAX_SUM_RELAY},
/*5 Клапан AHU*/		{"Rezerv#He \270c\276o\273\304\267",tpRELAY,0,MAX_SUM_RELAY},

/*10 Фрамуга СЕВЕР*///	{"Rezerv#He \270c\276o\273\304\267",tpRELAY,0,MAX_SUM_RELAY},

/*6 Фрамуга СЕВЕР*/		{"Window 1#\252\310a\274\311\264a 1",tpRELAY,0,MAX_SUM_RELAY},
///*7 Фрамуга ЮГ*/		{"Window SOUTH#\252\310a\274\311\264a \260\241",tpRELAY,0,MAX_SUM_RELAY},
/*7 Фрамуга ЮГ*/		{"Rezerv#He \270c\276o\273\304\267",tpRELAY,0,MAX_SUM_RELAY},
/*8 Фрамуга СЕВЕР*/		{"Window 2#\252\310a\274\311\264a 2",tpRELAY,0,MAX_SUM_RELAY},
/*9 Фрамуга СЕВЕР*/		{"Window 3#\252\310a\274\311\264a 3",tpRELAY,0,MAX_SUM_RELAY},

#ifdef RICHEL
/*10 Circulation valve*/{"Circ valve#Circ valve",tpRELAY,0,MAX_SUM_RELAY},
#endif
#ifdef KUBO
/*10 Фрамуга СЕВЕР*/	{"Window 4#\252\310a\274\311\264a 4",tpRELAY,0,MAX_SUM_RELAY},
#endif

/*11 Клапан UC*/		{"AHU valve#AHU \272\273a\276a\275",tpRELAY,0,MAX_SUM_RELAY},
/*12 Скорость AHU*/		{"AHU speed 1#C\272o\310oc\277\304 AHU 1",tpRELAY,0,MAX_SUM_RELAY},
/*13 Скорость AHU*/		{"AHU speed 2#C\272o\310oc\277\304 AHU 2",tpRELAY,0,MAX_SUM_RELAY},
/*14 Экран*/			{"Screen thermal#\257\272\310a\275 \277e\310\274\270\300",tpRELAY,0,MAX_SUM_RELAY},
/*15  Экран затеняющ*/	{"Screen shade#\257\272\310a\275 \267e\277e\275",tpRELAY,0,MAX_SUM_RELAY},
/*16  Верт. экран 1*/	{"Screen vert#\257\272\310a\275 \263e\310\277",tpRELAY,0,MAX_SUM_RELAY},
/*17 СО2 дозатор*/		{"CO2 valve#CO2 \272\273a\276a\275",tpRELAY,0,MAX_SUM_RELAY},
/*18 Клапан панели*/	{"AHU Pad valve#K\273a\276a\275\303 \276a\275e\273\270",tpRELAY,0,MAX_SUM_RELAY},
/*19 Досветка */		{"Lighting#\340oc\263e\277\272a",tpRELAY,0,MAX_SUM_RELAY},
/*20 ВнутрУвлаж*/		{"Internal RH#B\275\311\277  \311\263\273a\266\275e\275\270e",tpRELAY,0,MAX_SUM_RELAY},
/*21 Резерв*/			{"Rezerv#He \270c\276o\273\304\267",tpRELAY,0,MAX_SUM_RELAY},
/*22 Резерв*/			{"Rezerv#He \270c\276o\273\304\267",tpRELAY,0,MAX_SUM_RELAY},
/*23 Резерв*/			{"Rezerv#He \270c\276o\273\304\267",tpRELAY,0,MAX_SUM_RELAY},

/*24 Насос 1*/			{"Heat \310um\310 1#Hacoc 1",tpRELAY,0,MAX_SUM_RELAY},
/*25 Насос 2*/			{"Heat \310um\310 2#Hacoc 2",tpRELAY,0,MAX_SUM_RELAY},
/*26 Насос 3*/			{"Heat \310um\310 3#Hacoc 3",tpRELAY,0,MAX_SUM_RELAY},
/*27 Насос 4*/			{"Heat \310um\310 4#Hacoc 4",tpRELAY,0,MAX_SUM_RELAY},
/*28 Насос 5*/			{"Heat \310um\310 5#Hacoc 5",tpRELAY,0,MAX_SUM_RELAY},
/*29 Насос 6*/			{"Heat \310um\310 6#Hacoc 6",tpRELAY,0,MAX_SUM_RELAY},
/*30 Вентиляторы*/		{"Rezerv#He \270c\276o\273\304\267",tpRELAY,0,MAX_SUM_RELAY},
/*31 Нагреватель*/		{"Rezerv#He \270c\276o\273\304\267",tpRELAY,0,MAX_SUM_RELAY},
/*32 Охладитель*/		{"Rezerv#He \270c\276o\273\304\267",tpRELAY,0,MAX_SUM_RELAY},
///*33 Насос СИО*/		{"Misting \310um\310#Hacoc C\245O",tpRELAY,0,MAX_SUM_RELAY},
/*33 Насос СИО*/		{"Rezerv#He \270c\276o\273\304\267",tpRELAY,0,MAX_SUM_RELAY},

///*34 Клапан СИО*/		{"Mist valve start#K\273a\276a\275\303 C\245O",tpRELAY,0,MAX_SUM_RELAY},
///*35 Клапан  AHU*/		{"Mist AHU pump#Hacoc y\263\273 AHU",tpRELAY,0,MAX_SUM_RELAY},
/*34 Клапан СИО*/		{"Rezerv#He \270c\276o\273\304\267",tpRELAY,0,MAX_SUM_RELAY},
/*35 Насос  AHU*/		{"Mist AHU pump#Hacoc y\263\273 AHU",tpRELAY,0,MAX_SUM_RELAY},


/*36 Авария*/			{"Alarm#A\263a\310\270\307",tpRELAY,0,MAX_SUM_RELAY},

/*37 Регулятор 1*/		{"Regulator 1#Pe\264\311\273\307\277o\310 1",tpRELAY,0,MAX_SUM_RELAY},
/*38 Регулятор 2*/		{"Regulator 2#Pe\264\311\273\307\277o\310 2",tpRELAY,0,MAX_SUM_RELAY},
/*39 Регулятор 3*/		{"Regulator 3#Pe\264\311\273\307\277o\310 3",tpRELAY,0,MAX_SUM_RELAY},
/*40 Регулятор 4*/		{"Regulator 4#Pe\264\311\273\307\277o\310 4",tpRELAY,0,MAX_SUM_RELAY},
/*41 Регулятор 5 */		{"Regulator 5#Pe\264\311\273\307\277o\310 5",tpRELAY,0,MAX_SUM_RELAY},

/*42 Регулятор 1*/		{"Rezerv#He \270c\276o\273\304\267",tpRELAY,0,MAX_SUM_RELAY},
/*43 Регулятор 1*/		{"Rezerv#He \270c\276o\273\304\267",tpRELAY,0,MAX_SUM_RELAY},
/*44 Регулятор 1*/		{"Rezerv#He \270c\276o\273\304\267",tpRELAY,0,MAX_SUM_RELAY},
/*45 Регулятор 1*/		{"Rezerv#He \270c\276o\273\304\267",tpRELAY,0,MAX_SUM_RELAY},
};


#define cSmDHeat		0
#define cSmDVent		1
#define cSmDLight50		2
#define cSmDLight100	3
#define cSmRainDiskr	4
#define cSmDCO2			5
#define cSmDLight		6


eNameConfig NameInputConfig[cConfSInputs]={
/*0 Авария отопления*/ 			{"Heating alarm#A\263a\310\270\307 o\277o\276\273e\275",tpLEVEL,0,MAX_SUM_RELAY},
/*1 Авария вентиляции*/			{"Vent alarm#A\263a\310\270\307 \263e\275\277\270\273",tpLEVEL,0,MAX_SUM_RELAY},
/*2 Досветка 50%*/				{"Light 50%#50% \343oc\263e\277",tpLEVEL,0,MAX_SUM_RELAY},
/*3 Досветка 100%*/ 			{"Light 100%#100% \343oc\263e\277",tpLEVEL,0,MAX_SUM_RELAY},
///*4 Осадки*/					{"Rain#Oca\343\272\270",tpLEVEL,0,MAX_SUM_RELAY},
/*4 Осадки*/					{"Rezerv#He \270c\276o\273\304\267",tpLEVEL,0,MAX_SUM_RELAY},
/*5 Авария СО2*/				{"CO2 alarm#A\263a\310\270\307 CO2",tpLEVEL,0,MAX_SUM_RELAY},
/*6 Авария света*/				{"Light alarm#A\263a\310\270\307 \343oc\263e\277",tpLEVEL,0,MAX_SUM_RELAY}
};

#define SUM_NAME_PARS 24
code struct  eNameParUpr
        {
        char Name[30];
		char Ed;
        }
NameParUpr[SUM_NAME_PARS]={
/*0 Клапан 1*/ 			{"Max \310i\310e 1#Ma\272c \272o\275\277\311\310 1",SSSpS},
/*1 Клапан 2*/			{"Max \310i\310e 2#Ma\272c \272o\275\277\311\310 2",SSSpS},
/*2 Клапан 3*/			{"Max \310i\310e 3#Ma\272c \272o\275\277\311\310 3",SSSpS},
/*3 Клапан 4*/ 			{"Max \310i\310e 4#Ma\272c \272o\275\277\311\310 4",SSSpS},
/*4 Клапан 5*/			{"Max \310i\310e 5#Ma\272c \272o\275\277\311\310 5",SSSpS},
/*5 Клапан AHU*/		{"Max \310i\310e AHU#Ma\272c \272o\275\277 AHU",SSSpS},
/*6 Фрамуга СЕВЕР*/		{"Max vent UnW#Ma\272c \344\310a\274 \276o\343\263",SSSS},
///*7 Фрамуга ЮГ*/		{"Max vent OnW#Ma\272c \344\310a\274 \275a\263",SSSS},
/*7 Фрамуга ЮГ*/		{"Rezerv#He \270c\276o\273\304\267",SSSS},

/*8 Минимум контура 3*/	{"Min tem\310 \310i\310e 3#M\270\275 \272o\275\277\311\310 3",SSSpS},
/*9 Минимум контура 4*/	{"Min tem\310 \310i\310e 4#M\270\275 \272o\275\277\311\310 4",SSSpS},
/*10 Держать разн. давл*/{"Diff \310ressure#Pa\267\275\270\345a \343a\263\273",SSSpS},
/*11 Оптимум контура 3*/{"O\310timal \310i\310e3#O\276\277\270\274\311\274 \272o\275\277 3",SSSpS},
/*12 Оптимум контура 4*/{"O\310timal \310i\310e4#O\276\277\270\274\311\274 \272o\275\277 4",SSSpS},
/*13 И- поправка вент*/	{"Vent I-band#\252\310a\274\311\264\270 \245-\272o\305\344",SSpS0},
/*14 П- поправка отопл*/{"Heat P-band#Te\276\273o \250-\272o\305\344",SSpS0},
/*15 И- поправка отопл*/{"Heat I-band#Te\276\273o \245-\272o\305\344",SSpS0},
/*16 П- поправка вент*/	{"Vent P-band#\252\310a\274\311\264\270 \250-\272o\305\344",SSpS0},
/*17 Нет*/				{"Unused#He \270c\276o\273\304\267\311e\274",SSSS},
/*18 Экран*/			{"Max screen T#Ma\272c \305\272\310a\275 T",SSSS},
/*19  Экран затеняющ*/	{"Max screen S#Ma\272c \305\272\310a\275 \244",SSSS},
/*20  CO2*/				{"CO2 type#T\270\275 CO2",SSSS},
/*21  SIO*/				{"SIO#\SIO",SSSS},
/*22  Досветка*/		{"Light#\Light",SSSS},
/*23  T heat*/			{"T heat vent#T heat vent",SSSS},

};


eNameConfig NameSystemConfig[cConfSSystem]={
/*0 Система отопления*/ 			{"Heating system",tpSUM,0,MAX_SUM_RELAY},
/*1 Система вентиляции*/			{"Ventilation system",tpSUM,0,MAX_SUM_RELAY},
/*2 Система зашторивания*/			{"Screening system",tpSUM,0,MAX_SUM_RELAY},
/*3 Система ультраклима*/ 			{"UltraClima system",tpSUM,0,MAX_SUM_RELAY},
/*4 Система СО2*/					{"CO2 system",tpSUM,0,MAX_SUM_RELAY},
/*5 Система досвечивания*/			{"Lighting system",tpSUM,0,MAX_SUM_RELAY},
/*6 Система СИОД*/					{"Misting system",tpSUM,0,MAX_SUM_RELAY},
/*7 Система рециркуляции*/			{"Fans&Heaters",tpSUM,0,MAX_SUM_RELAY},
/*8 Резерв1*/						{"Rezerved",tpSUM,0,MAX_SUM_RELAY},
/*9 Резерв2*/						{"Rezerved",tpSUM,0,MAX_SUM_RELAY}
};


#define SUM_NAME_TIMER 24
code struct  eNameTimer {
        char Name[30];
		char Frm;
        char Index;
        }

NameTimer[SUM_NAME_TIMER]={
/*Формат	Индекс	*/
{"Zone number#Ho\274e\310 \267o\275\303", 		oS,  		0}, 
{"Time start#B\310e\274\307 c\277a\310\277a",			SSdSS,  	1}, 
{"Type start#T\270\276 c\277a\310\277a",			SS,  	3},
{"Heat tem\310#Te\274\276 o\277o\276\273e\275\270\307",	SSpS0,  	5}, 
{"Vent tem\310#Te\274\276 \263e\275\277\270\273\307\345\270\270",	SSpS0,  	7}, 
{"Humidit\311#B\273a\266\275oc\277\304",			SS,		29},
{"CO2 level#\251\310o\263e\275\304 CO2",			SSSS,  	9},
{"Light \310ower#\250\310o\345e\275\277 \343oc\263e\277\272\270",		SSS,	26},
{"Light mode#Pe\266\270\274 \343oc\263e\277\272\270",			oS,		27},
 
{"Min tem\310 \310i\310e1#M\270\275 \272o\275\277\311\310 1",		SS,		16},
{"Min tem\310 \310i\310e2#M\270\275 \272o\275\277\311\310 2",		SS,		17},
{"Min tem\310 \310i\310e3#M\270\275 \272o\275\277\311\310 3",		SS,		28},
{"Min tem\310 \310i\310e5#M\270\275 \272o\275\277\311\310 5",		SS,		15},

{"O\310timal \310i\310e1#O\276\277\270\274\311\274 \272o\275\277\311\3101",		SS,		11}, 
{"O\310timal \310i\310e2#O\276\277\270\274\311\274 \272o\275\277\311\3102",		SS,		12},
 
{"Tem\310 \310i\310e 3#Te\274\276 \272o\275\277\311\310a 3",			SS,		13}, 
{"Tem\310 \310i\310e 4#Te\274\276 \272o\275\277\311\310a 4",			SS,		14}, 

{"Vent mode#Pe\266\270\274 \344\310a\274\311\264",			oS,		19},
{"Min vent \310os#M\270\275 \344\310a\274\311\264",		SS,		18}, 

{"Mist \310ulse#Pac\276\303\273\307\277\304 C\245O",			SSSS,  	20},

{"T screen mode#Pe\266\270\274 \305\272\310a\275 T",	oS,		22}, 
{"S screen mode#Pe\266\270\274 \305\272\310a\275 \244",	oS,		23}, 
{"V screen mode#Pe\266\270\274 \305\272\310a\275 B",	oS,		24}, 
{"Fans mode#Pe\266\270\274 \263e\275\277\270\273\307\277o\310",			oS,		25}, 
};

#define SUM_NAME_STRAT 64
code struct  eNameStrat {
        char Name[30];
		char Frm;
        char Index;
        }

/*NameStrat[SUM_NAME_STRAT]={
{"T>Tset,RH>RHset.AHUvalve#T>Tset,RH>RHset.AHU valve", 			SS,		0},
{"T>Tset,RH<RHset.AHUvalve#T>Tset,RH<RHset.AHU valve", 			SS,		1},
{"T<Tset,RH>RHset.AHUvalve#T<Tset,RH>RHset.AHU valve", 			SS,		2},
{"T<Tset,RH<RHset.AHUvalve#T<Tset,RH<RHset.AHU valve", 			SS,		3},

{"T>Tset, RH>RHset. RailPipe#T>Tset, RH>RHset. Kontur1", 				SS,		4},
{"T>Tset, RH<RHset. RailPipe#T>Tset, RH<RHset. Kontur1", 				SS,		5},
{"T<Tset, RH>RHset. RailPipe#T<Tset, RH>RHset. Kontur1", 				SS,		6},
{"T<Tset, RH<RHset. RailPipe#T<Tset, RH<RHset. Kontur1", 				SS,		7},

{"T>Tset, RH>RHset. HeadPipe#T>Tset, RH>RHset. Kontur2", 				SS,		8},
{"T>Tset, RH<RHset. HeadPipe#T>Tset, RH<RHset. Kontur2", 				SS,		9},
{"T<Tset, RH>RHset. HeadPipe#T<Tset, RH>RHset. Kontur2", 				SS,		10},
{"T<Tset, RH<RHset. HeadPipe#T<Tset, RH<RHset. Kontur2", 				SS,		11},

{"T>Tset, RH>RHset. AHUPipe#T>Tset, RH>RHset. Kontur3", 				SS,		12},
{"T>Tset, RH<RHset. AHUPipe#T>Tset, RH<RHset. Kontur3", 				SS,		13},
{"T<Tset, RH>RHset. AHUPipe#T<Tset, RH>RHset. Kontur3", 				SS,		14},
{"T<Tset, RH<RHset. AHUPipe#T<Tset, RH<RHset. Kontur3", 				SS,		15},

{"T>Tset, RH>RHset. TScreen#T>Tset, RH>RHset. Termo screen", 		SS,		16},
{"T>Tset, RH<RHset. TScreen#T>Tset, RH<RHset. Termo screen", 		SS,		17},
{"T<Tset, RH>RHset. TScreen#T<Tset, RH>RHset. Termo screen", 		SS,		18},
{"T<Tset, RH<RHset. TScreen#T<Tset, RH<RHset. Termo screen", 		SS,		19},

{"T>Tset, RH>RHset. AHU speed#T>Tset, RH>RHset. AHU speed", 			SS,		20},
{"T>Tset, RH<RHset. AHU speed#T>Tset, RH<RHset. AHU speed", 			SS,		21},
{"T<Tset, RH>RHset. AHU speed#T<Tset, RH>RHset. AHU speed", 			SS,		22},
{"T<Tset, RH<RHset. AHU speed#T<Tset, RH<RHset. AHU speed", 			SS,		23},

{"T>Tset, RH>RHset. Mist#T>Tset, RH>RHset. Mist", 						SS,		24},
{"T>Tset, RH<RHset. Mist#T>Tset, RH<RHset. Mist", 						SS,		25},
{"T<Tset, RH>RHset. Mist#T<Tset, RH>RHset. Mist", 						SS,		26},
{"T<Tset, RH<RHset. Mist#T<Tset, RH<RHset. Mist", 						SS,		27},
};*/
NameStrat[SUM_NAME_STRAT]={
{"AHUvalve 1#AHU valve 1", 			SS,		0},
{"Way AHUvalve 1#Way AHUvalve 1",	SS,		1},
{"AHUvalve 2#AHU valve 2", 			SS,		2},
{"Way AHUvalve 2#Way AHUvalve 2",	SS,		3},
{"AHUvalve 3#AHU valve 3", 			SS,		4},
{"Way AHUvalve 3#Way AHUvalve 3",	SS,		5},
{"AHUvalve 4#AHU valve 4", 			SS,		6},
{"Way AHUvalve 4#Way AHUvalve 4",	SS,		7},

{"RailPipe 1#RailPipe 1",			SS,		8},
{"Way RailPipe 1#Way RailPipe 1",	SS,		9},
{"RailPipe 2#RailPipe 2",			SS,		10},
{"Way RailPipe 2#Way RailPipe 2",	SS,		11},
{"RailPipe 3#RailPipe 3",			SS,		12},
{"Way RailPipe 3#Way RailPipe 3",	SS,		13},
{"RailPipe 4#RailPipe 4",			SS,		14},
{"Way RailPipe 4#Way RailPipe 4",	SS,		15},

{"HeadPipe 1#HeadPipe 1",			SS,		16},
{"Way HeadPipe 1#Way HeadPipe 1",	SS,		17},
{"HeadPipe 2#Kontur2 2",			SS,		18},
{"Way HeadPipe 2#Way HeadPipe 2",	SS,		19},
{"HeadPipe 3#Kontur2 3",			SS,		20},
{"Way HeadPipe 3#Way HeadPipe 3",	SS,		21},
{"HeadPipe 4#Kontur2 4",			SS,		22},
{"Way HeadPipe 4#Way HeadPipe 4",	SS,		23},

{"AHUPipe 1#AHUPipe 1", 			SS,		24},
{"Way AHUPipe 1#Way AHUPipe 1",		SS,		25},
{"AHUPipe 2#Kontur3 2", 			SS,		26},
{"Way AHUPipe 2#Way AHUPipe 2",		SS,		27},
{"AHUPipe 3#Kontur3 3", 			SS,		28},
{"Way AHUPipe 3#Way AHUPipe 3",		SS,		29},
{"AHUPipe 4#Kontur3 4", 			SS,		30},
{"Way AHUPipe 4#Way AHUPipe 4",		SS,		31},

{"Termo screen 1#Termo screen 1",	SS,		32},
{"Way TScreen 1#Way TScreen 1",		SS,		33},
{"Termo screen 2#Termo screen 2",	SS,		34},
{"Way TScreen 2#Way TScreen 2",		SS,		35},
{"Termo screen 3#Termo screen 3",	SS,		36},
{"Way TScreen 3#Way TScreen 3",		SS,		37},
{"Termo screen 4#Termo screen 4",	SS,		38},
{"Way TScreen 4#Way TScreen 4",		SS,		39},

{"AHU speed 1#AHU speed 1", 		SS,		40},
{"WayAHUspeed 1#WayAHUspeed1",	    SS,		41},
{"AHU speed 2#AHU speed 2", 		SS,		42},
{"WayAHUspeed 2#WayAHUspeed2",		SS,		43},
{"AHU speed 3#AHU speed 3", 		SS,		44},
{"WayAHUspeed3#WayAHUspeed3",		SS,		45},
{"AHU speed 4#AHU speed 4", 		SS,		46},
{"WayAHUspeed4#WayAHUspeed4",		SS,		47},

{"Mist 1#Mist 1", 					SS,		48},
{"Way Mist 1#Way Mist 1",			SS,		49},
{"Mist 2#Mist 2", 					SS,		50},
{"Way Mist 2#Way Mist 2",			SS,		51},
{"Mist 3#Mist 3", 					SS,		52},
{"Way Mist 3#Way Mist 3",			SS,		53},
{"Mist 4#Mist 4", 					SS,		54},
{"Way Mist 4#Way Mist 4",			SS,		55},

{"InRH 1#InRH 1", 					SS,		56},
{"Way InRH 1#Way InRH 1",			SS,		57},
{"InRH 2#InRH 2", 					SS,		58},
{"Way InRH 2#Way InRH 2",			SS,		59},
{"InRH 3#InRH 3", 					SS,		60},
{"Way InRH 3#Way InRH 3",			SS,		61},
{"InRH 4#InRH 4", 					SS,		62},
{"Way InRH 4#Way InRH 4",			SS,		63},
};



//----------------------------------------


