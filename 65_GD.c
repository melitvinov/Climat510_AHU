#pragma pack(1)


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
                        �������
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
		uchar		Vent;

		uchar		Light;
		uchar		ModeLight;

		uchar		MinTPipe3;
		uchar		RHAir_c;

		uint16_t	Rez[10];
        }
        eTimer;

typedef struct eeSensing {
				int16_t		Value;
				uchar	RCS;
/*
	0x01 - 1 - ��������
	0x02 - 1 - ����� �� ������� ����������� ���������
	0x04 - 1 - ����� �� ������� ��������� �������������� ����������
	0x08 - 1 - ��������� ������� ��������� ������� ��������� 
	0x10 - 1 - ��������� ������� ����������� ������� ���������
	0x20 - 1 - ��������� ������ ����������� ������� ���������
	0x40 - 1 - ��������� ������ ��������� ������� ���������
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
				
				int16_t		DoPressure;

				int8_t		Vent;

				int8_t		Screen[3];
				
				int8_t		Light;
				int8_t		ModeLight;

				int8_t		Status;

				int16_t		Rez[10];
				} eClimTask; 

typedef struct eeNextTCalc {
				int16_t		DifTAirTDo;//������� ��������������� � ��������
				int16_t		UpSR;//��������� ����������� ������� �������	2
				int16_t		LowGlass;//�������� ������	4
				int16_t		LowOutWinWind;//�������� ����� � ������� �����������	6
				int16_t		UpLight;//�������� ��������� ��������	8
				int16_t		ICorrection;
				int16_t		dSumCalcF;//�������� ������	12

				int16_t		DiffCO2;//�������������� ����������� � ����������� �� ������������� ���������	14
				int16_t		TVentCritery;//�������� �����	16
				int16_t		PCorrection;//��������� ����������� ������� �� 1 ��������	18

				int16_t		Critery;//����-�������� ������������� ��	20
				int16_t		ICorrectionVent;//������� ����������� (��� �����������)	22
				
				int16_t		dSumCalc;//���������� ������� �������	24
				
				int16_t		PCorrectionVent;//������� �� ���������� ��������	26

				int16_t		CorrectionScreen; // ����� �������� ��

				int16_t		Rez[9];

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
	0�01 - 1 - ��� ������� �����������
	0�02 - 1 - ��� ��������� �����������
	0�04 - 1 - ����������� ��������������� �� ������
	0�08 - 1 - ����������� 
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

				int16_t		Rez1[32];

				int16_t		MaxReqWater;
				int16_t		Rez[9];
				eMechanic	HandCtrl[cSHandCtrl];
				} eTepl;				


typedef struct eeHot {
//0
				uchar 		News;
			/*���� ����� �� ��*/
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
        ���������-���������� � ������
------------------------------------*/
typedef struct eeConstMixVal
{
		int16_t     v_TimeMixVal;
        int16_t     v_PFactor;  /*������������ ������ - �-���� ������� � ����*/
        int16_t     v_IFactor;  /*������������ ������ - �-���� ������� � ����*/
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

/*-- ������ ����������� ������, ������ 130 ����*/
/*-----------------------------------
                ���������-������
------------------------------------*/
        int16_t     s_TStart[1];   /*����������� ������ - ������ �������� ������ ���*/
        int16_t     s_TEnd;   /*����������� ������ - ������ ������ ��*/
        int16_t     s_TConst;  /*����������� ������ - ������ ����������� ��*/
        int16_t     s_TVentConst;   /*��������������� - ������ �������� ������ ���*/

        int16_t     cool_PFactor;   /*��������������� - ������ ������ ��*/
        int16_t     s_RHConst;  /*��������������� - ������ ����������� ��*/
        int16_t     COPause;   /*������������ ��2 - ������ �������� ������ ���*/
        int16_t     f_SRFactor;   /*������������ ��2 - ������ ������ ��*/

        int16_t     s_CO2Const;  /*������������ ��2 - ������ ����������� ��*/
        int16_t     f_OutFactor;   /*������ 1_������� � �����- ������ �������� ������ ���*/
        int16_t     f_CorrTVentUp;   /*������ 1_������� � ��������� - ������ ������ ��*/
        int16_t     s_MinTPipeConst;/*������ 1_������� � ��������� - ������ ��������� ��*/

        int16_t     s_MinTPipe5;   /*�������_������� � �����- ������ �������� ������ ���*/
        int16_t     s_MinTPipe3;   /*�������_������� � ��������� - ������ ������ ��*/
        int16_t     s_MinOpenWinConst; /*�������_������� � ��������� - ������ ����������� ��*/
//30 ����
/*-----------------------------------
                ���������-��� ����������� ����������
------------------------------------*/
        int16_t     f_min_RHStart;
		int16_t		f_min_RHEnd;
		int16_t		f_max_RHStart;
        int16_t     f_max_RHEnd;
		int8_t		f_min_Cor;
        int8_t    	f_max_Cor;
//42 �����
/*-----------------------------------
                ���������-�������
------------------------------------*/
//64 �����
		int16_t		c_DoMinIfGlass;  /*������ 5 - ��� ���� ������ � ����� ������*/
		int16_t		f_CorrTVent;  /*������ 5 - ��� ������� �������*/
		int16_t		c_MinIfSnow;  /*������ 5 - ������� ������� ��� ������� ����������� ������*/

		int16_t		o_DeltaLight;
		int8_t		f_changeWindows;
		int8_t		f_only;
//74 �����
/*-----------------------------------
                ���������-������� �� �����
------------------------------------*/

		int8_t		f_MaxAngle;  /*������ 1 - (����-����)�������� ������ ���*/
		int8_t		c_MullDown;  /*������ 1 - (����-����)�������� ������ ���*/
		int8_t		f_DefOnUn;  /*������ 1 - (����-����)������ ��*/

		int8_t		c_5ExtrHeat;  /*������ 1 - (����-����)������ ��*/
        int16_t     c_CriticalSnowOut;  /*������ 1 - (����-����)����������� ��*/
		int16_t		c_DoMaxIfGlass;  /*������ 1 - ��������(����-����)�������� ������ ���*/


		int16_t		c_GlassStart;  /*������ 1 - (����-�������)�������� ������ ���*/
		int16_t		c_GlassEnd;  /*������ 1 - (����-�������)������ ��*/
        int16_t     c_GlassFactor;  /*������ 1 - (����-�������)����������� ��*/
/*������������ ���������*/
		int16_t		c_MaxDifTDown;  /*������ 1 - (����-������)�������� ������ ���*/
		int16_t		f_MinSun;  /*������ 1 - (����-������)������ ��*/
        int16_t     f_DeltaOut;  /*������ 1 - (����-������)����������� ��*/
/*______________________*/
		int16_t		c_SRStart;  /*������ 1 - ������ �������� ������ ���*/
		int16_t		c_SREnd;  /*������ 1 - ������ ������ ��*/
        int16_t     c_SRFactor;  /*������ 1 - ������ ��������� ��*/

		int16_t		c_OutStart;  /*������ 1 - (����-�����)�������� ������ ���*/
		int16_t		c_OutEnd;  /*������ 1 - (����-�����)������ ��*/
        int16_t     c_OutFactor;  /*������ 1 - (����-�����)����������� ��*/

		int16_t		c_WindStart;  /*������ 1 - ����� �������� ������ ���*/
//114 �����
		int16_t		c_WindEnd;  /*������ 1 - ����� ������ ��*/
        int16_t     c_WindFactor;  /*������ 1 - ����� ����������� ��*/

		int16_t		sc_GlassStart;  /*������ 1 - ������� �������� ������ ���*/
		int16_t		sc_GlassEnd;  /*������ 1 - ������� ������ ��*/
        int16_t     sc_GlassMax;  /*������ 1 - ������� ����������� ��*/

        int16_t     c_LightFactor;  /*������ 1 - �������� ��� ��������� ��������*/
        int16_t     c_ScreenFactor;  /*������ 1 - �������� ��� �������� ������*/
        int16_t     c_CloudFactor;  /*������ 1 - �������� ��� �������*/
//  100�������


/*-----------------------------------
                ���������-����������
------------------------------------*/
		uchar		f_S1MinDelta; /*������� - ������ �� ������ ������*/
		uchar		f_S1Level;
		uchar		f_S2MinDelta;
		uchar		f_S2Level;
		uchar		f_S3MinDelta;
		uchar		f_S3Level;
//+6
        int16_t     f_MinDelta;  /*������� - ��������� ���� ��� ������*/
		int16_t		c_MaxDifTUp;  /*������� - ������������ ����� ����� �����������*/
		int16_t		f_MinTime;  /*������� - ����������� ����� ����� �����������*/
        int16_t     f_StormWindOn; /*������� - ����� ��������� ����������� ������� ���*/
        int16_t     f_StormWind; /*������� - ����� ��������� ������������ ������� ���*/
        int16_t     f_WindStart;  /*������� - ����� �������� ������ ���*/
//154 �����
//+18
        int16_t     f_WindHold;  /*������� - ����� ���� ��������� �������� �������� ���*/
        int16_t     f_MinTFreeze;   /*������� - ����� ���� ��������� ���*/
//+22
        int16_t     f_MaxOpenRain;  /*������� - ��� ����� ��������� ��������� ��*/
        int8_t    	co_MaxTime; /*������� - ������ ������ ����������� ������� ���*/
		int8_t		co_MinTime;
/*-----------------------------------
                ���������-������� �� �������
------------------------------------*/

        int8_t		co_Impuls;       /*������� - (����-�����������)������� �� �������� ���*/
		int8_t		co_Dif;
		int16_t		f_StartCorrPow;  /*������� - ������ �������� ������ ���*/
		int16_t		f_EndCorrPow;  /*������� - ������ ������ ��*/
        int16_t     f_PowFactor;        /*������� - ������ ����������� ��*/
/*-----------------------------------
                ���������-CO2
-----------------------------------*/
		int16_t		reg_PFactor[2];/*��2 - ���� ����������������*/
/*-----------------------------------
                ���������-�����
------------------------------------*/
		int16_t		sc_ZSRClose; /*����� ���������� - ������ ��������� ���*/
		int16_t		sc_TSROpen;  /*����� ����������� - ������ ��������� ���*/
		int16_t		sc_TOutClose;/*����� ����������� - ����� ���� ��������� ���*/
		int16_t		sc_TVOutClose;/*����� ����������� - ����� ����� ��������� ���*/

		int16_t		sc_ZOutClose;/*����� ����������� - ����� �������� ������ ���*/
		int16_t		sc_TWindStart;/*����� ����������� - ����� ������ ��*/
        int16_t     sc_TVSRMaxOpen; /*����� ����������� - ����� ����������� � ���� ��*/
        int16_t     sc_TVSROpen;   /*����� ����������� - ������ ��������� ������������ ���� ���*/

		int16_t		f_WindFactor;/*����� - (����-����) ������ ��*/
		int16_t		sc_TFactor;/*����� - (����-����) ������������ ��*/
		int16_t		s_StartCorrPow;  /*������� - ������ �������� ������ ���*/
		int16_t		s_EndCorrPow;  /*������� - ������ ������ ��*/

        int16_t     s_PowFactor;        /*������� - ������ ����������� ��*/
        int16_t     sc_StartP2Zone;/*����� ��������� ������ ��*/
		int16_t		sc_StepS2Zone;/*����� ���������-���������� �����*/
		int16_t		sc_StepP2Zone;/*����� ���������-����� ����� �����������*/

        int16_t     sc_StartP1Zone;/*����� ��������� ������ ��*/
		int16_t		sc_StepS1Zone;/*����� ���������-���������� �����*/
		int16_t		sc_StepP1Zone;/*����� ���������-����� ����� �����������*/
		int16_t 	sc_MinDelta;/*����� ��������� ���� ��� ������*/
//214
/*-----------------------------------
                ���������- ����
------------------------------------*/
        int16_t		sio_TStart;/*���� - ����������,���� ����������� ������ ������� ��*/
		int16_t		sio_TStartFactor;/*���� - ��� ����������� ���������� ����������� �����*/
		int16_t		sio_TEnd;/*���� - ����������� ������ ������� ������ ��*/
		int16_t		sio_TEndFactor;/*���� - ��� ������� ��������������� ����������� �����*/
		int16_t		sio_TStop;/*���� - ��������,���� ����������� ������ ������� ��*/
        int16_t		sio_RHStart;/*���� - ����������,���� ��������� ������ ������� ��*/
		int16_t		sio_RHStartFactor;/*���� - ��� ����������� ���������� ����������� �����*/
		int16_t		sio_RHEnd;/*���� - ��������� ������ ������� ������ ��*/
		int16_t		sio_RHEndFactor;/*���� - ��� ������� ��������������� ����������� �����*/
		int16_t		sio_RHStop;/*���� - ��������,���� ��������� ������ ������� ��*/

		int16_t		ScaleRasx;/*���� - ����� ����� ����������� ��������*/

/*-----------------------------------
                ���������-�����������
-----------------------------------*/

		int16_t		vt_PFactor;/*����������� - ��������, ���� ��������������� ������*/
		int16_t		vt_WorkTime;/*����������� - ����� ������*/
		int16_t		vt_StopTime;/*����������� - ����� �����*/

/*-----------------------------------
                ���������-��������� �������
------------------------------------*/
		int16_t		vt_StartCalorifer;/*��������� ������� - ��������,���� ����������� ������ ��*/
		int16_t		vt_EndCalorifer;/*��������� ������� - ���������,���� ����������� ������ ��*/
/*-----------------------------------------
				��������� - �����
------------------------------------------*/
        int16_t     sc_dTStart;     /*����������� ���������� �������� ��������*/
        int16_t     sc_dTEnd;	    /*����������� ���������� �����*/
        int16_t     sc_dTSunFactor;	/*����������� ����������*/
/*-----------------------------------------
				��������� - ��������� �� ��������� ���������� �������
------------------------------------------*/

		int16_t		co_IFactor;
		int16_t		MinRainTime;
		int16_t		f_BlockFan;
		int16_t		sc_RHStart;
		int16_t		sc_RHEnd;
		int16_t		sc_RHMax;


		int16_t		v_MinFreeze;
		int16_t		l_SunOn50;
		int16_t		l_SunOn100;
		int16_t		l_PauseMode;
		int16_t		sc_PauseMode;

		int16_t 	l_SoftPauseMode;
		int16_t		o_TeplPosition;

		int16_t		c_RHStart;
		int16_t		c_RHEnd;
		int16_t		c_RHOnMin1;
		int16_t		c_RHOnMin2;

		int16_t		CorrectionScreen; // ����� �������� ��
		int16_t		ScreenCloseSpeed; // �������� �������� ������

	    int16_t     Rez[14];
//282
       }
        eTuneClimate;

typedef struct eeTeplControl
	   	{
       	int16_t     c_MaxTPipe[cSWaterKontur];   /*����������� ���������� ����������� ������1-5*/
        int16_t     f_MaxOpenUn;   /*�������_����������� ���������� ��������*/
        int16_t     f_MaxOpenOn;   /*�������_�������� ��� ��������� ��2*/
		int16_t 	c_MinTPipe[2];
		int16_t		c_DoPres;
		int16_t 	c_OptimalTPipe[2];
		int16_t		f_IFactor;
		int16_t		c_PFactor;  /*������ 1 - ��������(����-����)������ ��*/
        int16_t     c_IFactor; /*������������ �������� ��������*/
        int16_t     f_PFactor; /*������ 1 - ��������(����-����)�������� ��*/
		int8_t		vs_DegSt; //������� ��� ���������� ������� ������
		int8_t		vs_DegEnd; //������� ��� ���������� ������� ������
		int16_t		sc_TMaxOpen; // ����� �����������
		int16_t		sc_ZMaxOpen; // ����� ����������
		uint16_t	co_model;/*��2 - �����������(0-���������,1-������)*/
		uint16_t	sio_SVal;
		uint16_t	sLight;
		int8_t		sensT_heat;
		int8_t		sensT_vent;


		int16_t		Rez[19];
//+42 �����
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
        int16_t     		Rez[5];
	
	} eControl;

#ifdef AHU1
	typedef struct eeStrategy
		{
			int8_t 	 TUpRHUp;
			int8_t 	 TUpRHDown;
			int8_t 	 TDownRHUp;
			int8_t 	 TDownRHDown;
			int8_t 	 Optimal;
			uint16_t Power1;
			int8_t	 Point1;
			int16_t  Power2;
			int8_t 	 Point2;
		} eStrategy;
#else

typedef struct eeStrategy
	{
		int8_t TempPower;
		int8_t RHPower;
		int8_t OptimalPower;
		int8_t Economic;
		int8_t Powers;
		int8_t Separate;
		int8_t KonturHelp;
	} eStrategy;
#endif


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
		int32_t 		SaveIntegralVent;
		int32_t 		Integral;
		int16_t			TVentCritery;//Critery;
		int16_t			Critery;
		int32_t			IntegralVent;
		int32_t			SaveIntegral;
//24
		int16_t				qMaxKonturs;
		int16_t				qMaxOwnKonturs;
		int16_t				AbsMaxVent;
		int16_t				LastTVentCritery;
		int16_t				LastCritery;
		int16_t				IntVal[cSWaterKontur];
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
		int16_t				PowMaxKonturs;
		int16_t				PowOwnMaxKonturs;
		int16_t				TimeSIO;
		int8_t			Vent;
		int8_t			PrevNLight;//CorrScreen;
//137
		int8_t			OldPozOn;
		int8_t			OldPozUn;
		int16_t			TForControl;

		int16_t			nReset;
		int16_t			COPosition;
		
		int32_t			Rez3[2];
//141

//143
		int16_t			PauseSIO;
		int8_t			CurVal;
		int8_t			FazaSiod;
		eScreen			Screen[6];
		int8_t			OutFan;

		eRegsSettings	SetupRegs[2];
//161
		int16_t				PauseVent;
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
		int16_t				MaxDifT;//MidlTimeSens[2];
	
		int16_t				TPauseSIO;
//		eSensorD		SensorD;
		int8_t			FramUpdate[2];
		int8_t			PauseChangeLight;
		int8_t			NewLight;
		int16_t				COPause;
//		int16_t				Rez1[7];
		
		int8_t			NOwnKonturs;
		int8_t			CurrPower;
		int8_t			SnowTime;
		int16_t				s_Power;
		int16_t				ii_PFactor;
		int8_t			VentBlock;
		int16_t				f_Power;
		int16_t				f_NMinDelta;
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

/* ======== ���������� ���� ������=============*/
struct  eGData{
        uchar           SostRS;   /* �� ����������� ������������ � .asm*//*�� ����*/
        eHot            Hot;           /* �� ����������� ������������ News � .asm*//*�� ����*/
        eFanBlock		FanBlock[cSTepl][2];
        eControl        Control;
        eFullCal        Cal;
        eTimer          Timer[cSTimer];
		eConstMech		ConstMechanic[cSTepl];
		eStrategy		Strategy[cSTepl][cSStrategy];
		eMechConfig		MechConfig[cSTepl];
		eTuneClimate	TuneClimate;		
        eTControl       TControl;
        eLevel          Level;
        int16_t         uInTeplSens[cSTepl][cConfSSens];
        int16_t         uMeteoSens[cConfSMetSens];
        } GD;

eTimer xdata *pGD_Timer;
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
/*---!!!!��������!!!! �� �������� 
����� � ������� BlockEEP ������ ���������������
�� ������� ������ ������ � ������� AdrGD
�.� ������� �������� ������ ���� ������ ���������
� ��� ������������� � EEP ������ ���� � ����� AdrGD*/
        BlockEEP[0].AdrCopyRAM=&GD.Control.Tepl[0];
        BlockEEP[0].Size=sizeof(eTeplControl)*cSTepl+15;

		ClrDog;
        BlockEEP[1].AdrCopyRAM=&GD.Timer[0];
        BlockEEP[1].Size=(sizeof(eTimer)*cSTimer);
		ClrDog;
        BlockEEP[2].AdrCopyRAM=&GD.TuneClimate;
        BlockEEP[2].Size=(sizeof(eTuneClimate));

        BlockEEP[3].AdrCopyRAM=&GD.Strategy[0][0];
        BlockEEP[3].Size=(sizeof(eStrategy)*cSStrategy*cSTepl);

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
/* ������ �������� ������ */
        AdrGD[0/*cblHot*/].Adr=&GD.Hot;
        AdrGD[0].MaxSize=sizeof(eHot);
        AdrGD[1/*cblControl*/].Adr=&GD.Control;
        AdrGD[1].MaxSize=sizeof(eControl);
        AdrGD[2/*cblTimer*/].Adr=&GD.Timer[0];
        AdrGD[2].MaxSize=sizeof(eTimer)*cSTimer;
        AdrGD[3/*cblTuneClimate*/].Adr=&GD.TuneClimate;
        AdrGD[3].MaxSize=sizeof(eTuneClimate);
        AdrGD[4/*cblStrategy*/].Adr=&GD.Strategy[0];
        AdrGD[4].MaxSize=sizeof(eStrategy)*cSTepl*cSStrategy;
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
/* ��������� ����������� */

        GD.Control.rModification=cModification;
        GD.Control.rSInTeplSens=cConfSSens;
        GD.Control.rSMechanic=cSRegCtrl;
        ClrDog;
        GD.Control.rSTepl=GD.Control.ConfSTepl;//cNowSTepl;		
        GD.Control.rVersion=cVersion;
}
