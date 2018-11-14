#pragma pack(1)

int volatile startFlag;

int16_t fnScreenOut[4];

int16_t fnInRHOut[2];

volatile int16_t MidlSunCalc;
volatile int16_t MidlWindCalc;

typedef struct eeCalSensor {
	uint8_t		Type;
	uint8_t		nInput;
	uint8_t		Output;
	uint8_t		Corr;
	uint16_t		U0;
	uint16_t		V0;
	uint16_t		U1;
	uint16_t		V1;

}eCalSensor;

typedef struct eeFullCal {
//        int16_t        	Port;
		eCalSensor	InTeplSens[cSTepl][cConfSSens];
        eCalSensor	MeteoSens[cConfSMetSens];
        } eFullCal;

/*-----------------------------------
                        Допуски
------------------------------------*/

typedef int16_t eSensLevel[4];

typedef struct eeLevel
		{
			eSensLevel InTeplSens[cSTepl][cConfSSens];
			eSensLevel MeteoSens[cConfSMetSens];
		}
		eLevel;

//-------------------------------------/

typedef struct  eeTimer
        {
		uchar		Zone[1];
        uint16_t    TimeStart;
        uint8_t    	TypeStart;
        uint8_t    	Rez1;
        uint16_t    TAir;
        uint16_t    TVentAir;
        uint16_t    CO2;

		uchar		TOptimal1;
		uchar		TOptimal2;

        uchar   	TPipe3;
        uchar   	TPipe4;

		uchar		MinTPipe5;
	
        uchar   	MinTPipe1;
        uchar   	MinTPipe2;

		uchar		MinOpenWin;
        uchar		Win;

		uint16_t	SIO;

		uchar		Screen[3];
		uchar		AHUVent;

		uchar		Light;
		uchar		ModeLight;

		uchar		MinTPipe3;
		uchar		RHAir_c;
		//uint16_t	TCool;
		uint16_t	MistRHstop;

        uchar   	MinTPipeAHU;		// richel
		uchar		XXX;			// richel

		uint16_t	Rez[7];
		uint16_t	crc;
        }
        eTimer;

typedef struct eeSensing {
				int16_t		Value;
				uchar	RCS;
/*
	0x01 - 1 - выключен
	0x02 - 1 - выход за пределы измеряемого диапазона
	0x04 - 1 - выход за пределы диапазона измерительного напряжения
	0x08 - 1 - превышена верхняя аварийная граница измерения 
	0x10 - 1 - превышена верхняя контрольная граница измерения
	0x20 - 1 - превышена нижняя контрольная граница измерения
	0x40 - 1 - превышена нижняя аварийная граница измерения
*/
				} eSensing;

typedef struct eeKontur {
				
				int16_t		Optimal;
				int16_t		MaxCalc;
				int16_t		MinTask;
				int16_t		MinCalc;

				int8_t		SError;
				int8_t		rez;
				int16_t		Priority;

//				int16_t		TempWeight;

				int16_t		SensValue;
				int16_t		Do;

				int8_t		RCS;
				int8_t		ExtRCS;

				int8_t		Status;
				int8_t		Rez1;
				int16_t		Rez[2];

//12*2
				} eKontur;

typedef struct eeClimTask {
				int16_t		TAir;
				int16_t		DoTHeat;
				int16_t		DoTVent;

				int16_t		NextTAir;
				int16_t		NextTVent;

				int16_t		RHAir;
				int16_t		DoRHAir;
	
				int16_t		CO2;
				int16_t		DoCO2;

				int8_t		Win;
				int16_t		SIO;
				
				uint16_t	MistRHstop;

				int8_t		AHUVent;

				int8_t		Screen[3];
				
				int8_t		Light;
				int8_t		ModeLight;

				int8_t		Status;

				// изменение 86.
				int16_t		TminAHU;

				// изменение 86.
				int16_t		Rez[9];   // 10
				} eClimTask; 

typedef struct eeNextTCalc {
				int16_t		DifTAirTDo;//Разница междуизмеренным и заданным
				int16_t		UpSR;//Повышение температуры теплицы солнцем	2
				int16_t		LowGlass;//Понижает стекло	4
				int16_t		LowOutWinWind;//Понижает ветер и внешняя температура	6
				int16_t		UpLight;//Повышает включение досветки	8
				int16_t		ICorrection;
				int16_t		dSumCalcF;//Понижают осадки	12

				int16_t		DiffCO2;
				int16_t		TVentCritery; //
				int16_t		PCorrection;

				int16_t		Critery;//Цель-изменить теплоноситель на	20
				int16_t		ICorrectionVent; // RH рукава ДЕРЖАТЬ
				
				int16_t		dSumCalc;//Приращение внешних влияний	24
				
				int16_t		PCorrectionVent;//Остаток от предыдущих расчетов	26

				int16_t		Rez[10];

				} eNextTCalc;
typedef struct eeMechanic {  //20
				uchar	RCS;
				int8_t	Position;
				} eMechanic;

typedef struct eeOtherCalc
				{
				int16_t			CorrScreen;
				int16_t			TaskCritery;
				int16_t			CriteryNow;
				int16_t			TimeSiod;
				int16_t			MeasDifPress;
				int16_t			Rez[10];
				} eOtherCalc;

typedef struct eeTepl	{

				uchar 		Cfg[2];

				eSensing	InTeplSens[cConfSSens];
				int16_t		DiskrSens[2];

				int8_t		ExtRCS;
				int8_t		RCS;
/*
	0х01 - 1 - нет задания температуры
	0х02 - 1 - нет измерения температуры
	0х04 - 1 - температура скорректирована по солнцу
	0х08 - 1 - температура 
*/
				eClimTask	AllTask;
				eOtherCalc	OtherCalc;

				eNextTCalc	NextTCalc;						
				eKontur		Kontur[cSWaterKontur+2];

				int8_t		SystemStatus;
				int8_t		ConnectionStatus;

				int8_t		SensingStatus;
				int8_t		RezStatus;

				int8_t		ScreenStatus;
				int8_t		SIOStatus;

				int8_t		LightStatus;
				int8_t		COStatus;

				uchar		tempParamHeat;  // new
				uchar		tempParamVent;  // new		//изменение 100 это теперь контрольная Т
				uint16_t 	tempHeat;  		// new
				uint16_t 	tempVent;  		// new		//изменение 100 это теперь контрольная Т

				uint16_t	Light50;
				uint16_t	Light100;
				uint16_t	CurrentStratSys;	// вывод в Мониторе убрали вместо страт сейчас RH по которому идет управление

				int16_t		RHParam;  		// new		// изменение 100 в Hot блок добавлено, но в Мониторе не понятно куда выводить
				uint16_t 	RHsens;  		// new

				int16_t 	DDWP;

				int16_t		Rez1[23];  // 26

				int16_t		MaxReqWater;
				int16_t		Rez[9];
				eMechanic	HandCtrl[cSHandCtrl];
				} eTepl;				


typedef struct eeHot {
//0
				uchar 		News;
			/*Блок пиема из ПК*/
				eSensing 	MeteoSensing[cConfSMetSens];
				int16_t		MaxReqWater;
				int16_t		HeatPower;
				int16_t		FullHeat;
//40
				int16_t		NextRHAirSens;
				int16_t		Vosx;
				int16_t		Zax;
/***************************************/
				int16_t		SumSun;
				uchar		Regs[5];
				uchar		Util;
//50
				uchar		isLight;
				uchar		blockCO2;

				uchar		Rez[4];
				int16_t		MidlSR;
				int16_t		MidlWind;
				int16_t		PozFluger;

				uint16_t 	Time;
				uint16_t 	Data;
				uchar 		Year;
				uchar 		Demo;
/***************************************/				
				eTepl 		Tepl[cSTepl];
				int16_t		Rez2[10];
/***************************************/
				} eHot;

/*-----------------------------------
        Параметры-соединение в иедино
------------------------------------*/
typedef struct eeConstMixVal
{
		int16_t     v_TimeMixVal;
        int16_t     v_PFactor;  /*Смесительный клапан - П-коэф разницы Т воды*/
        int16_t     v_IFactor;  /*Смесительный клапан - И-коэф разницы Т воды*/
		int8_t		v_MinTim;
		int8_t 		v_Type;

} eConstMixVal;
typedef struct eeConstMech
{
        eConstMixVal     ConstMixVal[cSRegCtrl];
		//int8_t			 LuftSm;


} eConstMech;

typedef struct eeTuneClimate
        {

/*-- начало сохраняемых данных, размер 130 байт*/
/*-----------------------------------
                Параметры-солнце
------------------------------------*/
        int16_t     s_TStart[1];   /*Температура задана - солнце начинает влиять при*/
        int16_t     s_TEnd;   /*Температура задана - солнце влияет до*/
        int16_t     s_TConst;  /*Температура задана - солнце увеличивает на*/
        int16_t     s_TVentConst;   /*Влажностьзадана - солнце начинает влиять при*/
        int16_t     cool_PFactor;   /*Влажностьзадана - солнце влияет до*/
        int16_t     s_RHConst;  /*Влажностьзадана - солнце увеличивает на*/
        int16_t     COPause;   /*Концентрация СО2 - солнце начинает влиять при*/

        int16_t     f_SRFactor;   /*Концентрация СО2 - солнце влияет до*/

        int16_t     s_CO2Const;  /*Концентрация СО2 - солнце увеличивает на*/

        int16_t     f_OutFactor;   /*Контур 1_Минимум в прогр- солнце начинает влиять при*/
        int16_t     f_CorrTVentUp;		 // Клапан AHU - RHз - RHи увеличивает температуру вентиляции на

        int16_t     s_MinTPipeConst;/*Контур 1_Минимум в программе - солнце уменьшает на*/
        int16_t     s_MinTPipe5;   /*Фрамуги_Минимум в прогр- солнце начинает влиять при*/
        int16_t     s_MinTPipe3;   /*Фрамуги_Минимум в программе - солнце влияет до*/
        int16_t     s_MinOpenWinConst; /*Фрамуги_Минимум в программе - солнце увеличивает на*/
//30 байт
/*-----------------------------------
                Параметры-для температуры вентиляции
------------------------------------*/
        int16_t     f_min_RHStart;		// Клапан AHU - RHи - RHз начинает влиять на минимум при
		int16_t		f_min_RHEnd;		// Клапан AHU - RHи - RHз влияет на минимум до
		int16_t		f_max_RHStart;		// Клапан AHU - RHз - RHи начинает влиять на максимум при
        int16_t     f_max_RHEnd;		// Клапан AHU - RHз - RHи влияет на максимум до
		int8_t		f_min_Cor;			// Клапан AHU - RHи - RHз увеличивает минимум на
        int8_t    	f_max_Cor;			// Клапан AHU - RHз - RHи уменьшает максимум на
//42 байта
/*-----------------------------------
                Параметры-обогрев
------------------------------------*/
//64 байта
		int16_t		c_DoMinIfGlass;

		int16_t		f_CorrTVent;  		// Клапан AHU - RHи - RHз уменьшает температуру вентиляции на

		int16_t		c_MinIfSnow;

		int16_t		o_DeltaLight;
		int8_t		f_changeWindows;
		int8_t		f_only;
//74 байта
/*-----------------------------------
                Параметры-влияния на Тводы
------------------------------------*/

		int8_t		f_MaxAngle;  // Клапан AHU допустимое отклонение от датчика

		int8_t		c_MullDown;  /*Контур 1 - (Тзад-Тизм)начинает влиять при*/

		int8_t		f_DefOnUn;  // Клапан AHU			не используется

		int8_t		c_5ExtrHeat;  /*Контур 1 - (Тзад-Тизм)влияет до*/
        int16_t     c_CriticalSnowOut;  /*Контур 1 - (Тзад-Тизм)увеличивает на*/
		int16_t		c_DoMaxIfGlass;  /*Контур 1 - Динамика(Тзад-Тизм)начинает влиять при*/
		int16_t		c_GlassStart;  /*Контур 1 - (Тзад-Тстекла)начинает влиять при*/
		int16_t		c_GlassEnd;  /*Контур 1 - (Тзад-Тстекла)влияет до*/
        int16_t     c_GlassFactor;  /*Контур 1 - (Тзад-Тстекла)увеличивает на*/
		int16_t		c_MaxDifTDown;  /*Контур 1 - (Тзад-Тшатра)начинает влиять при*/

		int16_t		f_MinSun;      // Клапан AHU
        int16_t     f_DeltaOut;    // Клапан AHU
/*______________________*/
		int16_t		c_SRStart;  /*Контур 1 - солнце начинает влиять при*/
		int16_t		c_SREnd;  /*Контур 1 - солнце влияет до*/
        int16_t     c_SRFactor;  /*Контур 1 - солнце уменьшает на*/
		int16_t		c_OutStart;  /*Контур 1 - (Тзад-Твнеш)начинает влиять при*/
		int16_t		c_OutEnd;  /*Контур 1 - (Тзад-Твнеш)влияет до*/
        int16_t     c_OutFactor;  /*Контур 1 - (Тзад-Твнеш)увеличивает на*/
		int16_t		c_WindStart;  /*Контур 1 - ветер начинает влиять при*/
		int16_t		c_WindEnd;  /*Контур 1 - ветер влияет до*/
        int16_t     c_WindFactor;  /*Контур 1 - ветер увеличивает на*/

		int16_t		sc_deltaTstart;  /*Экран - Tизм-Тзад влияет при*/				// вместо  sc_GlassStart
		int16_t		sc_deltaTend;    /*Экран - Tизм-Тзад влияет до*/
        int16_t     sc_MaxOpenCorrect;    /*Экран - Tизм-Тзад уменьшает максимум из параметров на*/

		//int16_t		sc_GlassStart;  /*Контур 1 - фрамуги начинают влиять при*/              // не используется
		//int16_t		sc_GlassEnd;    /*Контур 1 - фрамуги влияют до*/						// не используется
        //int16_t     sc_GlassMax;    /*Контур 1 - фрамуги увеличивают на*/					// не используется

        int16_t     c_LightFactor;  /*Контур 1 - понизить при включении досветки*/
        int16_t     c_ScreenFactor;  /*Контур 1 - понизить при закрытом экране*/
        int16_t     c_CloudFactor;  /*Контур 1 - повысить при осадках*/
//  100байтНОВ


/*-----------------------------------
                Параметры-вентиляция
------------------------------------*/

        int16_t		f_AHU_T_SunStart; 	// Коррекция Т рукава при солнце при
        int16_t		f_AHU_T_SunEnd;		// Коррекция Т рукава при солнце до
        int16_t		f_AHU_T_SunCorr;	// Коррекция Т рукава при солнце на


		uchar		f_AHU_T_LightCorr;	// Коррекция Т рукава при вкл Досветки

        //uchar		f_S3MinDelta;	// Клапан AHU			не используется
		//uchar		f_S3Level;		// Клапан AHU			не используется

        //uchar     	f_AHU_T_LightCorr;	// Коррекция Т рукава при вкл Досветки
        uchar		f_S2Level;		// Клапан AHU			не используется


		int16_t		c_MaxDifTUp;  	// Клапан AHU
		int16_t		f_MinTime;  	// Клапан AHU минимальная пауза между включениями

        int16_t     f_StormWindOn; 	// Клапан AHU			не используется

        int16_t     f_StormWind; 	// Клапан AHU ветер закрывает
        int16_t     f_WindStart;  	// Фрамуги минимальный ветер при расчете
//154 байта
//+18
        int16_t     f_WindHold;  	// Клапан AHU заблокировать максимум на
        int16_t     f_MinTFreeze;  	// Клапан AHU внешняя температура закрыват при
        int16_t     f_MaxOpenRain;  // Клапан AHU при дожде допустимо открывать

        int8_t    	co_MaxTime;
		int8_t		co_MinTime;
/*-----------------------------------
                Параметры-влияние на фрамуги
------------------------------------*/

        int8_t		co_Impuls;       /*Фрамуги - (Тизм-Твентиляции)открыть на максимум при*/
		int8_t		co_Dif;

		int16_t		f_StartCorrPow;  	// Клапан AHU Твнещ начинает влиять при
		int16_t		f_EndCorrPow;		// Клапан AHU Твнеш влияет до
        int16_t     f_PowFactor;        // Клапан AHU Твнеш увеличивает открытие в

        int16_t		f_SunStart;			// Клапан AHU солнце начинает влиять при
        int16_t		f_SunEnd;			// Клапан AHU солнце влияет до
		int16_t		f_SunIncOutT;		// Клапан AHU солнце увеличивает Твнеш на

		int16_t		sc_TSROpen;			/*Экран термический - Солнце открывает при*/
		int16_t		sc_TOutClose;		/*Экран термический - Твнеш ночью открыват при*/
		int16_t		sc_TVOutClose;		/*Экран термический - Твнеш ночью закрывает при*/
		int16_t		sc_ZOutClose;		/*Экран термический - ветер начинает влиять при*/
		int16_t		sc_TWindStart;		/*Экран термический - ветер влияет до*/
        int16_t     sc_TVSRMaxOpen; 	/*Экран термический - ветер увеличивает Т внеш на*/
        int16_t     sc_ZSRClose;   		/*Экран затеняющий    Солнце разворачивает при*/

		int16_t		f_WindFactor;		/*Экран - (Тзад-Тизм) влияет до*/

		int16_t		sc_LineSunVol_notuse;		/* не используется  */
		int16_t		s_StartCorrPow;  	/*Фрамуги - Солнце начинает влиять при*/		// не используется
		int16_t		s_EndCorrPow;  		/*Фрамуги - Солнце влияет до*/					// не используется

        int16_t     s_PowFactor;        /*Фрамуги - Солнце увеличивает на*/
        int16_t     sc_StartP2Zone;		/*Экран закрывать шагами по*/
		int16_t		sc_StepS2Zone;		/*Экран закрывать-количество шагов*/
		int16_t		sc_StepP2Zone;		/*Экран закрывать-пауза между включениями*/

        int16_t     sc_StartP1Zone;		/*Экран открывать шагами по*/
		int16_t		sc_StepS1Zone;		/*Экран открывать-количество шагов*/
		int16_t		sc_StepP1Zone;		/*Экран открывать-пауза между включениями*/
		//int16_t 	sc_MinDelta;		/*Экран исполнять если шаг больше*/

		int8_t 		sc_MinDelta;		/*Экран исполнять если шаг больше*/

		int8_t 		ScreenCloseSpeed;		/*Экран исполнять если шаг больше*/
//214
/*-----------------------------------
                Параметры- СИОД
------------------------------------*/
        int16_t		sio_TStart;/*СИОД - включается,если температура больше задания на*/
		int16_t		sio_TStartFactor;/*СИОД - при минимальном превышении повторяется через*/
		int16_t		sio_TEnd;/*СИОД - температура больше задания влияет до*/
		int16_t		sio_TEndFactor;/*СИОД - при большом рассогласовании повторяется через*/
		int16_t		sio_TStop;/*СИОД - запрещен,если температура меньше задания на*/
        int16_t		sio_RHStart;/*СИОД - включается,если влажность меньше задания на*/
		int16_t		sio_RHStartFactor;/*СИОД - при минимальном превышении повторяется через*/
		int16_t		sio_RHEnd;/*СИОД - влажность меньше задания влияет до*/
		int16_t		sio_RHEndFactor;/*СИОД - при большом рассогласовании повторяется через*/
		int16_t		sio_RHStop;/*СИОД - запрещен,если влажность больше задания на*/

		int16_t		ScaleRasx;/*СИОД - пауза между включениями клапанов*/

/*-----------------------------------
                Параметры-Вентиляторы
-----------------------------------*/

		int16_t		vt_PFactor;/*Вентиляторы - включать, если рассогласование больше*/
		int16_t		vt_WorkTime;/*Вентиляторы - время работы*/
		int16_t		vt_StopTime;/*Вентиляторы - время паузы*/

/*-----------------------------------
                Параметры-воздушный обогрев
------------------------------------*/
		int16_t		vt_StartCalorifer;/*Воздушный обогрев - включать,если температура меньше на*/
		int16_t		vt_EndCalorifer;/*Воздушный обогрев - выключать,если температура больше на*/
/*-----------------------------------------
				Параметры - ОБЩИЕ
------------------------------------------*/
        int16_t     sc_dTStart;   /*Коэффициент усреднения солнечой радиации*/
        int16_t     sc_dTEnd;/*Коэффициент усреднения ветра*/
        int16_t     sc_dTSunFactor;/*Коэффициент упреждения*/
/*-----------------------------------------
				Параметры - коррекция по влажности темпеатуры задания
------------------------------------------*/

		int16_t		co_IFactor;
		int16_t		MinRainTime;
		int16_t		f_BlockFan;
		int16_t		sc_RHStart;     // не используется
		int16_t		sc_RHEnd;		// не используется
		int16_t		sc_RHMax;		// не используется


		int16_t		v_MinFreeze;
		int16_t		l_SunOn50;
		int16_t		l_SunOn100;
		int16_t		l_PauseMode;
		int16_t		sc_PauseMode;

		int16_t 	l_SoftPauseMode;
		int16_t		o_TeplPosition;

		// изменение 100. Вместо этого вводим коррекции
		uchar		AHUspeed_Tmin;
		uchar		AHUspeed_Tmax;
		uchar		AHUspeed_Corr;
		//uchar		fAHU_S1Level;
		//uchar		fAHU_S2Level;
		//uchar		fAHU_S3Level;
		uchar		fAHU_Offset1;		// не используется
		uchar		fAHU_Offset2;		// не используется
		uchar		fAHU_Offset3;		// не используется
		uchar		fAHU_Offset4;		// не используется

		uchar		fAHU_Sens1;
		uchar		fAHU_Sens2;
		uchar		fAHU_Sens3;
		uchar		fAHU_Sens4;

		uchar		fAHU_MaxOffset;

		int16_t		c_RHStart;		// Контур 1,2,3 RHизм - RHзад начинает влиять на минимум при
		int16_t		c_RHEnd;		// Контур 1,2,3 RHизм - RHзад влияет на минимум до
		int16_t		c_RHOnMin1;     // Контур 1
		int16_t		c_RHOnMin2;     // Контур 2
		int16_t		c_RHOnMin3;     // Контур 3

		uchar		fUC_Offset1;
		uchar		fUC_S1Level;
		uchar		fUC_Offset2;
		uchar		fUC_S2Level;
		uchar		fUC_Offset3;
		uchar		fUC_S3Level;
		uchar		fUC_Offset4;

		uchar		vAHU_MinTempr;
		uchar		vAHU_MaxTempr;

		//int16_t     CriteryLevel;
		int8_t		f_MistRHstart;		// Увлажнение панели. Превышение влажности при
		int8_t		f_MistRHend;		// Увлажнение панели. Превышение влажности до

		uchar		MaxAHUspeed;   		// коррекция скорости по ветру
		uchar		MaxAHUwindSpeed;    // максимальный ветер для коррекции скорости по ветру

		uchar		MaxCorrAHUrh;		// 66 изменение. температура при которой ругулятор увлажнения откроется на 100

		uchar		CloseInRH_AHU;      // 73 выключаем внутренее увлажнение если клапан открыт на указанную величину

//  new
		int8_t		sc_TCorrMin;		// Экран термический - (Tзад-Tизм) влияет на минимум ( до 10,типовое 2°C)
		int8_t		sc_TCorrMax;		// Экран термический - (Tзад-Tизм) влияет на минимум ( до 10,типовое 2°C)
		int8_t		sc_TMinOpenCorrect;	// Экран термический - (Tзад-Tизм) увеличивает минимум на ( до 100,типовое 100%)

		int8_t      sc_LineSunVol;

		//int8_t      Rez[1];

//280		
       }
        eTuneClimate;
typedef struct eeTeplControl
	   	{
       	int16_t     c_MaxTPipe[cSWaterKontur];   /*Максимально допустимая температура Контур1-5*/
        int16_t     f_MaxOpenUn;   /*Фрамуги_Максимально допустимое открытие*/
        int16_t     f_MaxAHUSpd;   /*Фрамуги_Максимум при подкормке СО2*/
		int16_t 	c_MinTPipe[2];
		int16_t		c_DoPres;
		int16_t 	c_OptimalTPipe[2];
		int16_t		f_IFactor;
		int16_t		c_PFactor;  /*Контур 1 - Динамика(Тзад-Тизм)влияет до*/
        int16_t     c_IFactor; /*Интегральная поправка контуров*/
        int16_t     f_PFactor; /*Контур 1 - Динамика(Тзад-Тизм)понижает на*/
		int8_t		vs_DegSt; //Градусы для вычисления позиции экрана
		int8_t		vs_DegEnd; //Градусы для вычисления позиции экрана
		int16_t		sc_TMaxOpen;
		int16_t		sc_ZMaxOpen;
		uint16_t	co_model;/*СО2 - исполнитель(0-регулятор,1-клапан)*/
		uint16_t	sio_SVal;
		uint16_t	sLight;
		int8_t		sensT_heat;
		int8_t		sensT_vent;
		uint16_t	tempPipe3;
		uint16_t	InRHMax;
		uint16_t	InRHMin;
		uint16_t    MistMax;
		uint16_t    PresMax;

		// изменеие 100. Добавляем два новых параметра
		int16_t		sensRH;

		// изменеие 104. Делаем расчет влажности выключаемым
		int16_t		DDWP_RH_OnOff;


		int16_t		Rez[11];  //12

		uint16_t 	crc;


//+42 байта
		} eTeplControl;


typedef struct eeControl
	{
        uchar 		  	rModification;
        uchar 		  	rSInTeplSens;
        uchar   		rSMechanic;
        uchar   		rSTepl;
        uchar	  		rVersion;
		eTeplControl	Tepl[cSTepl];
		uchar   		NFCtr;
		uint8_t			IPAddr[4];
		uchar			ConfSTepl;
		int8_t			Language;
		int8_t			Read1W;
		int8_t			Write1W;
		uint8_t			Screener;
		uint8_t			Cod;
	//	uint8_t			Saverez;

		uint8_t			MidlSunCalc;
		uint8_t			MidlWindCalc;
		int8_t     		Rez[8];
		//int16_t     		Rez[5];
	
	} eControl;

#ifdef AHU1
	typedef struct eeStrategy
		{
			int8_t 	 TUpRHUp;// Startegy when TAir>Tset and RHAir>RHSet+deadband
			int8_t 	 TUpRHDown;// Strategy when TAir>Tset and RHAir<RHSet-deadband
			int8_t 	 TDownRHUp;// Strategy when TAir<Tset and RHAir>RHSet+deadband
			int8_t 	 TDownRHDown;// Strategy when TAir<Tset and RHAir<RHSet-deadband
			int8_t 	 Optimal;// Strategy when TAir>Tset and |RHAir-RHSet| in deadband, so most optimal strategy
			uint16_t Power1;//Power in Point 1 position
			int8_t	 Point1;//Value of the point in System scale
			int16_t  Power2;//Power in Point 2 possition
			int8_t 	 Point2;//Value of point 2 in System scale
			int8_t	 TypeControl; //Type of attachment (To THeat or TVent)
		} eStrategy;
#else

typedef struct eeStrategy
	{
	int8_t StratAHUvalve1[2];  		// T>Tset, RH>RHset. Клапан AHU
	int8_t StratAHUvalve2[2];		// T>Tset, RH<RHset. Клапан AHU
	int8_t StratAHUvalve3[2];		// T<Tset, RH>RHset. Клапан AHU
	int8_t StratAHUvalve4[2];		// T<Tset, RH<RHset. Клапан AHU

	int8_t StratKontur1_1[2]; 		// T>Tset, RH>RHset. Контур 1		RailPipe
	int8_t StratKontur1_2[2];		// T>Tset, RH<RHset. Контур 1
	int8_t StratKontur1_3[2];		// T<Tset, RH>RHset. Контур 1
	int8_t StratKontur1_4[2];		// T<Tset, RH<RHset. Контур 1

	int8_t StratKontur2_1[2];		// T>Tset, RH>RHset. Контур 2		HeadPipe
	int8_t StratKontur2_2[2];		// T>Tset, RH<RHset. Контур 2
	int8_t StratKontur2_3[2];		// T<Tset, RH>RHset. Контур 2
	int8_t StratKontur2_4[2];		// T<Tset, RH<RHset. Контур 2

	int8_t StratKontur3_1[2];		// T>Tset, RH>RHset. Контур 3		AHUPipe
	int8_t StratKontur3_2[2];		// T>Tset, RH<RHset. Контур 3
	int8_t StratKontur3_3[2];		// T<Tset, RH>RHset. Контур 3
	int8_t StratKontur3_4[2];		// T<Tset, RH<RHset. Контур 3

	int8_t StratTermoScreen1[2];	// T>Tset, RH>RHset. Экран термический
	int8_t StratTermoScreen2[2];	// T>Tset, RH<RHset. Экран термический
	int8_t StratTermoScreen3[2];	// T<Tset, RH>RHset. Экран термический
	int8_t StratTermoScreen4[2];	// T<Tset, RH<RHset. Экран термический

	int8_t StratAHUspeed1[2];		// T>Tset, RH>RHset. Скорость AHU
	int8_t StratAHUspeed2[2];		// T>Tset, RH<RHset. Скорость AHU
	int8_t StratAHUspeed3[2];		// T<Tset, RH>RHset. Скорость AHU
	int8_t StratAHUspeed4[2];		// T<Tset, RH<RHset. Скорость AHU

	int8_t StratPressReg1[2];		// T>Tset, RH>RHset. Регулятор давления  // увлажнение		Mist
	int8_t StratPressReg2[2];		// T>Tset, RH<RHset. Регулятор давления
	int8_t StratPressReg3[2];		// T<Tset, RH>RHset. Регулятор давления
	int8_t StratPressReg4[2];		// T<Tset, RH<RHset. Регулятор давления

	int8_t StratInRH1[2];			// T>Tset, RH>RHset. Внутренние увлажнение
	int8_t StratInRH2[2];			// T>Tset, RH<RHset. Внутренние увлажнение
	int8_t StratInRH3[2];			// T<Tset, RH>RHset. Внутренние увлажнение
	int8_t StratInRH4[2];			// T<Tset, RH<RHset. Внутренние увлажнение

//	int8_t TempPower;
//	int8_t RHPower;
//	int8_t OptimalPower;
//	int8_t Economic;
//	int8_t Powers;
//	int8_t Separate;
//	int8_t KonturHelp;

	} eStrategy;
#endif

typedef struct eeSystems
	{
		int16_t		Max;
		int16_t		Min;
		int16_t		Opt;
		int16_t		Prior;
		int16_t		Power;
		int16_t		Keep;
		int16_t		Value;
		uint16_t	RCS;
		uint16_t	Time;
		uint16_t	tTime;
	} eSystems;

typedef struct eeRegsSettings
	{
		int16_t				IntVal;
		int16_t				Stop;
		int16_t				Work;
		int8_t				On;
		int16_t				Pause;
		
	} eRegsSettings;

typedef struct eeScreen
	{
		int16_t				Value;
		int8_t				Mode;
		int8_t				OldMode;
		int16_t				Pause;
		int16_t				PauseMode;
//		int16_t				TimeChangeMode;
//		int16_t				TempStart;
	} eScreen;

/*typedef struct eeSensorD
	{
		int16_t				SumD;
		int16_t				ChangeD;
		int16_t				LastChangeD;
		int16_t				LastTAir;
		int16_t				Past3D;
		int16_t				Past2D;
		int16_t				Past1D;
		int16_t				Past3DTDo;
		int16_t				Past2DTDo;
		int16_t				Past1DTDo;

	} eSensorD;	*/
	typedef struct eeMechBusy
		{
			int				TimeSetMech;
			int				TimeRealMech;
			int				PauseMech;
			char			RCS;
			eSensing*		Sens;
			int				PrevDelta;
			int				PrevTask;
			int16_t			CalcTim;
			int8_t			TryMes;
			int8_t			TryMove;


		} eMechBusy;
	
typedef struct eeTControlKontur
	{
		int16_t				LastDoT;
		int16_t				RealPower[2];
		int16_t 			SErr;
		int16_t 			DoT;
		int32_t 			CalcT;
		int8_t				PumpStatus;
		int8_t				MainTepl;
		int16_t				TPause;
		int8_t				Manual;
		int8_t				Separate;
		int16_t				SensValue;
		int8_t				NAndKontur;
		int8_t				PumpPause;
	} eTControlKontur;
		
typedef struct eeTControlTepl
	{
		eTControlKontur	Kontur[cSKontur];
		int16_t 		LastLastInTeplSensing[cConfSSens];
		int16_t 		LastInTeplSensing[cConfSSens];
		uint8_t 		TimeInTepl[cConfSSens];
		eSystems		Systems[cSUCSystems];
		int32_t 		SaveIntegralVent;
		int32_t 		Integral;
		int16_t			TVentCritery; // Т рукава ДЕРЖАТЬ;
		int16_t			Critery;
		int32_t			IntegralVent;
		int32_t			SaveIntegral;
//24
		int16_t			qMaxKonturs;
		int16_t			qMaxOwnKonturs;
		int16_t			AbsMaxVent;
		int16_t			LastTVentCritery;
		int16_t			LastCritery;
		int32_t			IntVal[cSRegCtrl];
//36
//		int16_t				PrevSig[cSWaterKontur];
//46
		eMechBusy		MechBusy[cSRegCtrl];
//126
		int8_t			WindWin[2];

//		int8_t			PausePump;//[cSWaterKontur];
		int8_t			ModeLight;
		int8_t			nMaxKontur;
//131
//		int8_t			NumLight;
		int16_t			PowMaxKonturs;
		int16_t			PowOwnMaxKonturs;
		int16_t			TimeSIO;
		int8_t			SaveMaxMist;
		int8_t			PrevNLight;//CorrScreen;
//137
		int8_t			OldPozOn;
		int8_t			OldPozUn;
		int16_t			TForControl;

		int16_t			nReset;
		int16_t			COPosition;
		
		int16_t			InRHMode;
		int16_t			InRHStatus;


		int32_t			Rez3[1];	// 2

//141

//143
		int16_t			PauseSIO;
		int8_t			CurVal;
		int8_t			FazaSiod;
		eScreen			Screen[6];
		int8_t			OutFan;

		eRegsSettings	SetupRegs[2];
//161
		int16_t			PauseVent;
		int8_t			Calorifer;
//164
		int8_t			StopI;
		int8_t			StopVentI;


		int16_t			SensHalfHourAgo;
		int16_t			SensHourAgo;
		int16_t			TimeSumSens;
		int32_t			SumSens;
		int16_t			LightPauseMode;
		int8_t			LightMode;
		int8_t			OldLightMode;
		int32_t			SumFAR;
		int8_t			DifLightMode;
		int8_t			RCS1;
		int16_t			LightExtraPause;
		int16_t			TempStart5;//sac_Integral2;
		int8_t			LastScrExtraHeat;
		int8_t			WithoutPC;
		int8_t			LightValue;
		int8_t			CurrPozFluger;
		int8_t			CurrPozFlugerTime;
		int8_t			UnWindStorm;
		int8_t			OnWindStorm;
		int8_t			ScrExtraHeat;//sac_fram;

//		int32_t			Functional;
		int32_t			RealPower;//MidlSens[2];
		int16_t			MaxDifT;//MidlTimeSens[2];
	
		int16_t			TPauseSIO;
//		eSensorD		SensorD;
		int8_t			FramUpdate[2];
		int8_t			PauseChangeLight;
		int8_t			NewLight;
		int16_t			COPause;
//		int16_t				Rez1[7];
		
		int8_t			NOwnKonturs;
		int8_t			CurrPower;
		int8_t			SnowTime;
		int16_t			s_Power;
		int16_t			ii_PFactor;
		int8_t			VentBlock;
		int16_t			f_Power;
		int16_t			f_NMinDelta;
		int8_t			bAlarm;
		int8_t			NAndKontur;
		int8_t			Alarms[MAX_ALARMS];
	} eTControlTepl;

typedef struct eeTControl
	{
		eTControlTepl	Tepl[cSTepl];
//		int16_t 		LastLastMeteoSensing[cConfSMetSens];
		int16_t 		MeteoSensing[cConfSMetSens];
		uint8_t 		TimeMeteoSensing[cConfSMetSens];
		int32_t			SumSun;
		int8_t			PrevPozFluger;
		int8_t			Delay;
		int32_t			MidlSR;
		int16_t			Data;
//		int16_t			OutTemp;
//		int8_t			OutPause;
//		int16_t			OutSR;
//		int8_t			OutSRPause;
		int16_t			NowRasx;
		int32_t			FullVol;
		int8_t			bSnow;
		uint8_t			NowCod;
		uchar			tCodTime;
	} eTControl;	



typedef struct eeMechConfig{
		uint16_t 	Systems[cConfSSystem];
		uint16_t 	RNum[SUM_NAME_CONF];
	} eMechConfig;



typedef struct eeFanBlock
			{
				uint16_t		Speed;
				uint8_t   		NFans;
				eFanData 		FanData[MAX_FAN_COUNT];

			} eFanBlock;



#define CtrTime	GD.Hot.Time
#define CtrData	GD.Hot.Data
#define CtrYear	GD.Hot.Year

/* ======== Глобальный блок данных=============*/
struct  eGData{
        uchar           SostRS;   /* не передвигать использовано в .asm*//*Не буду*/
        eHot            Hot;           /* не передвигать использовано News в .asm*//*Не буду*/
        eFanBlock		FanBlock[cSTepl][2];
        eControl        Control;
        eFullCal        Cal;
        eTimer          Timer[cSTimer];
		eConstMech		ConstMechanic[cSTepl];
		//eStrategy		Strategy[cSTepl][cSStrategy]; // NEW strat
		eStrategy		Strategy[cSTepl];
		eMechConfig		MechConfig[cSTepl];
		eTuneClimate	TuneClimate;		
        eTControl       TControl;
        eLevel          Level;
        int16_t         uInTeplSens[cSTepl][cConfSSens];
        int16_t         uMeteoSens[cConfSMetSens];
        } GD;

eKontur xdata *pGD_Hot_Tepl_Kontur; 
eTControlKontur xdata *pGD_TControl_Tepl_Kontur; 
eMechanic xdata *pGD_Hot_Hand_Kontur; 
eTeplControl xdata *pGD_Control_Tepl; 
eTepl xdata *pGD_Hot_Tepl; 
eTControlTepl xdata *pGD_TControl_Tepl; 
eConstMech xdata *pGD_ConstMechanic;
eMechanic xdata *pGD_Hot_Hand; 
eStrategy xdata *pGD_Strategy_Tepl;
eStrategy xdata *pGD_Strategy_Kontur;
eMechConfig	xdata *pGD_MechConfig;
uint16_t	xdata *pGD_MechConfig_Kontur;
eConstMixVal xdata	*pGD_ConstMechanic_Mech;
eMechBusy xdata *MBusy;
eSensLevel xdata *pGD_Level_Tepl;
typedef struct eeBlockEEP {
        uchar*		AdrCopyRAM;
        uint16_t    Size;
        uint16_t    CSum;
        int8_t    	Erase;
        } eBlockEEP;

eBlockEEP  BlockEEP[SUM_BLOCK_EEP];


void InitBlockEEP(void){
/*---!!!!ВНИМАНИЕ!!!! По глупости 
номер в массиве BlockEEP должен соответствовать
на единицу меньше номеру в массиве AdrGD
т.е порядки структур должны быть строго одинаковы
и все несохраняеьые в EEP должны быть в конце AdrGD*/
        BlockEEP[0].AdrCopyRAM=&GD.Control.Tepl[0];
        BlockEEP[0].Size=sizeof(eTeplControl)*cSTepl+15;

		ClrDog;
        BlockEEP[1].AdrCopyRAM=&GD.Timer[0];
        BlockEEP[1].Size=(sizeof(eTimer)*cSTimer);
		ClrDog;
        BlockEEP[2].AdrCopyRAM=&GD.TuneClimate;
        BlockEEP[2].Size=(sizeof(eTuneClimate));

        //BlockEEP[3].AdrCopyRAM=&GD.Strategy[0][0];	// NEW strat
        //BlockEEP[3].Size=(sizeof(eStrategy)*cSStrategy*cSTepl);   // NEW strat
        BlockEEP[3].AdrCopyRAM=&GD.Strategy[0];
        BlockEEP[3].Size=(sizeof(eStrategy)*cSTepl);

        BlockEEP[4].AdrCopyRAM=&GD.MechConfig[0];
        BlockEEP[4].Size=(sizeof(eMechConfig)*cSTepl);

        BlockEEP[5].AdrCopyRAM=&GD.Cal;
        BlockEEP[5].Size=sizeof(eCalSensor)*cSTepl*cConfSSens;

        BlockEEP[6].AdrCopyRAM=&GD.Cal.MeteoSens;
        BlockEEP[6].Size=sizeof(eCalSensor)*cConfSMetSens;

        BlockEEP[7].AdrCopyRAM=&GD.ConstMechanic[0];
        BlockEEP[7].Size=(sizeof(eConstMech)*cSTepl);
}
void ButtonReset(void) {
/* адреса передачи данных */
        AdrGD[0/*cblHot*/].Adr=&GD.Hot;
        AdrGD[0].MaxSize=sizeof(eHot);
        AdrGD[1/*cblControl*/].Adr=&GD.Control;
        AdrGD[1].MaxSize=sizeof(eControl);
        AdrGD[2/*cblTimer*/].Adr=&GD.Timer[0];
        AdrGD[2].MaxSize=sizeof(eTimer)*cSTimer;
        AdrGD[3/*cblTuneClimate*/].Adr=&GD.TuneClimate;
        AdrGD[3].MaxSize=sizeof(eTuneClimate);
        AdrGD[4/*cblStrategy*/].Adr=&GD.Strategy[0];
        //AdrGD[4].MaxSize=sizeof(eStrategy)*cSTepl*cSStrategy;   // NEW strat
        AdrGD[4].MaxSize=sizeof(eStrategy)*cSTepl;
        AdrGD[5/*cblMechConfig*/].Adr=&GD.MechConfig[0];
        AdrGD[5].MaxSize=sizeof(eMechConfig)*cSTepl;
        AdrGD[6/*cblCal*/].Adr=&GD.Cal;
        AdrGD[6/*cblCal*/].MaxSize=sizeof(eFullCal);
        AdrGD[7/*cblCal*/].Adr=&GD.Cal.MeteoSens;
        AdrGD[7/*cblCal*/].MaxSize=sizeof(eFullCal);
        AdrGD[8/*cblMechanic*/].Adr=&GD.ConstMechanic[0];
        AdrGD[8/*cblCal*/].MaxSize=sizeof(eConstMech)*cSTepl;
        ClrDog;
        AdrGD[9/*cblLevel*/].Adr=&GD.Level;
        AdrGD[9/*cblCal*/].MaxSize=sizeof(eLevel);
        AdrGD[10/*cblHot*/].Adr=&GD.Hot;
        AdrGD[10/*cblCal*/].MaxSize=sizeof(eHot);
        AdrGD[11/*cblHot*/].Adr=&GD.TControl;
        AdrGD[11/*cblCal*/].MaxSize=sizeof(eTControl);
/* параметры контроллера */

        GD.Control.rModification=cModification;
        GD.Control.rSInTeplSens=cConfSSens;
        GD.Control.rSMechanic=cSRegCtrl;
        ClrDog;
        GD.Control.rSTepl=GD.Control.ConfSTepl;//cNowSTepl;		
        GD.Control.rVersion=cVersion;
}
