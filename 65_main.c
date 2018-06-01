/*============================================
        ---Проект 324 с 17.11.2003
		--- Проект F319 ---
        Файл "k_main.c"
        Главный цикл программы
----------------------------------------------*/
//++++++FullCheck ++++
int  DestSize;
int	 DestAdr;
//char xdata	DestBuffer[7000];
//char* DestAdrBuf;
//char	BufCheckByte;

/*char PlaceBuf(void) {
int  i;
char xdata *p1;
char xdata *p2;
if (BufCheckByte != 55) return 0; //;неудачный прием
p1=(char xdata *)DestAdr;
p2=(char xdata *)&DestBuffer[0];
for (i=0;i < (DestSize-1);i++) {
	*(p1++)=*(p2++);
	}
return 1;
}
*/
//;------FullCheck------------------


//char volatile konturMax[6];
//char volatile mecPosArray[7];
//char volatile framMaxUn;
//char volatile framMaxOn;
//char volatile coModel;
//char volatile modelLight;
//char volatile sensHeat;
//char volatile sensVent;

/*
        int16_t     f_MaxOpenUn;   //Фрамуги_Максимально допустимое открытие
        int16_t     f_MaxAHUSpd;   //Фрамуги_Максимум при подкормке СО2
		int16_t 	c_MinTPipe[2];
		int16_t		c_DoPres;
		int16_t 	c_OptimalTPipe[2];
		int16_t		f_IFactor;
		int16_t		c_PFactor;  //Контур 1 - Динамика(Тзад-Тизм)влияет до
        int16_t     c_IFactor;  //Интегральная поправка контуров
        int16_t     f_PFactor;  //Контур 1 - Динамика(Тзад-Тизм)понижает на
		int8_t		vs_DegSt;   //Градусы для вычисления позиции экрана
		int8_t		vs_DegEnd;  //Градусы для вычисления позиции экрана
		int16_t		sc_TMaxOpen;
		int16_t		sc_ZMaxOpen;
		uint16_t	co_model;   //СО2 - исполнитель(0-регулятор,1-клапан)
		uint16_t	sio_SVal;
		uint16_t	sLight;
		int8_t		sensT_heat;
		int8_t		sensT_vent;
		uint16_t	tempPipe3;
		uint16_t	InRHMax;
		uint16_t	InRHMin;
*/

/*void loadKontur(char tCTepl)
{
	GD.Control.Tepl[tCTepl].c_MaxTPipe[0] = 600;
	GD.Control.Tepl[tCTepl].c_MaxTPipe[1] = 900;
	GD.Control.Tepl[tCTepl].c_MaxTPipe[2] = 600;
	GD.Control.Tepl[tCTepl].c_MaxTPipe[3] = 500;
	GD.Control.Tepl[tCTepl].c_MaxTPipe[4] = 1100;
	GD.Control.Tepl[tCTepl].c_MaxTPipe[5] = 600;

	GD.Control.Tepl[tCTepl].f_MaxOpenUn = 100;
	GD.Control.Tepl[tCTepl].f_MaxAHUSpd = 100;

	GD.Control.Tepl[tCTepl].c_MinTPipe[0] = 0;
	GD.Control.Tepl[tCTepl].c_MinTPipe[1] = 0;
	GD.Control.Tepl[tCTepl].c_MinTPipe[2] = 0;

	GD.Control.Tepl[tCTepl].c_DoPres = 0;

	GD.Control.Tepl[tCTepl].c_OptimalTPipe[0] = 0;
	GD.Control.Tepl[tCTepl].c_OptimalTPipe[1] = 0;
	GD.Control.Tepl[tCTepl].c_OptimalTPipe[2] = 250;

	GD.Control.Tepl[tCTepl].f_IFactor = 800;
	GD.Control.Tepl[tCTepl].c_PFactor = 300;
	GD.Control.Tepl[tCTepl].c_IFactor = 500;
	GD.Control.Tepl[tCTepl].f_PFactor = 300;
	GD.Control.Tepl[tCTepl].vs_DegSt = 90;
	GD.Control.Tepl[tCTepl].vs_DegEnd = 100;
	GD.Control.Tepl[tCTepl].sc_TMaxOpen = 100;
	GD.Control.Tepl[tCTepl].sc_ZMaxOpen = 10;
	GD.Control.Tepl[tCTepl].co_model = 1;
	GD.Control.Tepl[tCTepl].sio_SVal = 4;
	GD.Control.Tepl[tCTepl].sLight = 1;
	GD.Control.Tepl[tCTepl].sensT_heat = 1;
	GD.Control.Tepl[tCTepl].sensT_vent = 1;
	GD.Control.Tepl[tCTepl].tempPipe3 = 0;
	GD.Control.Tepl[tCTepl].InRHMax = 0;
	GD.Control.Tepl[tCTepl].InRHMin = 0;
}

void checkConfig()
{
	char volatile tCTepl,sys;
	char volatile checkMech, checkKontur;
	for (tCTepl=0;tCTepl<4;tCTepl++)
	{
		checkMech = 0;
		checkKontur = 0;
		for (sys=0;sys<6;sys++)
		{
		  if (GD.Control.Tepl[tCTepl].c_MaxTPipe[sys] > 1300)   // темп заданная в мониторе *10
		   	checkKontur = 1;
		}
		//ClrDog;
		//for (sys=0;sys<6;sys++)
		//{
	    //    if (GD.Hot.Tepl[tCTepl].HandCtrl[cHSmScrTH+sys].RCS == 0)
	    //    	checkMech = 1;
		//}
		//ClrDog;
        //if (GD.Hot.Tepl[tCTepl].HandCtrl[cHSmLight].RCS == 0)
        //	checkMech = 1;

    	//if (checkMech == 1)
    	//{
    		//GD.Hot.Tepl[tCTepl].newsZone = 0x0A;
    	//	loadMech(tCTepl);
    		//repeatNews[tCTepl] = 4;
    	//} else
    	//{
    	//	saveMech(tCTepl);
    	//}
    	ClrDog;
    	if (checkKontur == 1)
    	{
    		//GD.Hot.Tepl[tCTepl].newsZone = 0x0F;
    		loadKontur(tCTepl);
    		//repeatNews[tCTepl] = 4;
    	}// else
    	//{
    	//	saveKontur(tCTepl);
    	//}
    	//ClrDog;
    	//if (repeatNews[tCTepl])
    	//	repeatNews[tCTepl]--;
    	//if (repeatNews[tCTepl] <= 0)
    	//	GD.Hot.Tepl[tCTepl].newsZone = 0;
	}

}
*/

volatile char crc;
volatile char crc1;
volatile char size;
volatile char numB;

char CheckSumMain(void)
{
  char Bl;
  switch (numB)
  {
	  case 2:
	  {
		  Bl = 0;
		  break;
	  }
	  case 4:
	  {
		  Bl = 1;
		  break;
	  }
	  case 6:
	  {
		  Bl = 2;
		  break;
	  }
  }

  int i;
  char res = 0;
  volatile int8_t r =0;
  for (i=0; i<cSHandCtrl; i++)
  {
	  r = GD.Hot.Tepl[Bl].HandCtrl[i].RCS;
	  res = res + r;
	  r = GD.Hot.Tepl[Bl].HandCtrl[i].Position;
	  res = res + r;
  }
  return res;
}

main()
{
char    timeDog;
		BITKL=0;

#ifndef STM32_UNIT
        init8051();
#else
        ClrAllOutIPCDigit();
		Init_STM32();
#endif

		ClrDog;
	#ifdef SumRelay48
		//Reg48ToI2C();
		//OutRelay88();
	#else
		#ifdef SumRelay40
			OutRelay40();
		#else
			OutRelay24();
		#endif
	#endif
        InitLCD();

        ClrDog;
#ifdef SumExtCG
  		SendFirstScreen(1);
#endif
        clear_d();
        ClrDog;
        Menu=0;
		EndInput=0;
        nReset=3;
        //w_txt("\252\245TO F405 (c)APL&DAL");
        w_txt("ФИТО F405 (c)APL&DAL");	// NEW disp
        ClrDog;
        Video();
        ClrDog;
        GD.Hot.News|=bKlTest;
        ByteX=1;
        GD.SostRS=OUT_UNIT;
        //KeyDelay=0;
        CheckKeyboardSTM();
        if (BITKL)
        	ByteX=6;
        ClrDog;
        TestMem(ByteX);
		Second=38;
        ClrDog;
        ClrDog;  /* разрешение прерываний RS и T0 из init8051()*/
        ClearAllAlarms();
        UDPSendDataInit();
        AHUPadInit();
        InRHInit();
        //initCheckConfig();
        startFlag = 5;
start:

   if (not) {
        if(!ton_t--) { ton_t=ton; not--; Sound;}
        }
   if(!not && nReset)
   	   {
	   	   ton=(nReset--)+2;
	   	   not=80;
   	   }
   if (!timeDog--) { timeDog=7;ClrDog; }

   if(GD.SostRS == (uchar)IN_UNIT) {  /*Если приняли блок с ПК */
            /*--Если запись 0бл и признак времени то установить время */
//            if(PlaceBuf()) {
#ifdef STM32_UNIT
	   	   	   NMinPCOut=0;
#endif
	   	   	if(!NumBlock && (GD.Hot.News&bInClock)) SetRTC();	// NEW
	   	   	    //if(!NumBlock && (GD.Hot.News&0x80)) SetRTC();
            	ClrDog;
            /*-- Была запись с ПК в блок NumBlock, переписать в EEPROM ------*/

            	//checkConfig();

            	if ( (NumBlock == 0) && (size == 92) )
            	{
            		crc1 = 55-CheckSumMain();
            		if (crc != crc1)
            			ReadFromFRAM();
            	}

            	if ( GD.Timer[0].crc != 0xAA )
            		ReadBlockFRAM(1);

            	if ( GD.Control.Tepl[0].crc != 0xAA )
            		ReadBlockFRAM(0);

            	if (NumBlock)
            		ReWriteFRAM();

//				}
            GD.SostRS=OUT_UNIT;
            SIM=105;
            }
   if(bSec) {

#ifdef STM32_UNIT
	   if (Second==58)
	   {
		   //volatile ress;
		   //ress = GetDDWP(2200, 8000);
		  // ress = GetDDWP(2300, 7000);
		   //ress = GetDDWP(2000, 6000);

		   UDPStartSend();
		   CheckWithoutPC();
	   	   CheckInputConfig();
	   }

		CheckRSTime();
#endif
#ifndef NOTESTMEM

        if(GD.SostRS==OUT_UNIT) TestMem(0);
#endif
        bSec=0;
        ClrDog;
        Control();
        ClrDog;
        B_video=1;
        if (!(Second%9))
        {
        	Measure();
   	      	UDPSend();
        }
       // IMOD_WriteOutput(0,1,0xf0f0f0f0);

   	   }
   if(BITKL) {
        ClrDog;
        GD.Hot.News|=bOperator;
        if (Menu) GD.Hot.News|=bEdit;
        KeyBoard();
        B_video=1;
        }
   //CheckReadyMeasure();
   if(B_video) {
        ClrDog;
        GMenu();
        ClrDog;
        Video();
        ClrDog;
        B_video=0;
        }
   simple_servercycle(); //Перенесено в прерывание клавиатуры

goto start;
}
