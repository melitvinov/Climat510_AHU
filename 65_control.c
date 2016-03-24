/*------------------------------------------------*/
/**************************************************/
/*Подпрограммы математических алгоритмов "Ромашки"*/

/*					ЗАМЕЧАНИЯ:
В подпрограмме AllTaskAndCorrection строчка:
	ВНИМАНИЕ! Усреднение в показаниях датчика
В подпрограмме SetMinMaxOfWater стоит ограничение
на минимум 5 контура cMin5Cont	*/
/**************************************************/
/*------------------------------------------------*/

/*------------------------------------------
Вычисление значения задаваемой величины
--------------------------------------------*/
/*----------------------------------------*/

/*!
\brief Авария датчика температуры воздуха вентиляции в зависимости от выбранного значение в Параметрах управления
*/
/*void controlGetTempVentAlarm(char fnTepl)
{
		switch (pGD_Control_Tepl->sensT_vent)
		{
			case 0: // sensor temp 1
				if (pGD_Hot_Tepl->InTeplSens[cSmTSens1].RCS != 0)
				{
					__SetBitOutReg(fnTepl,cHSmAlarm,0,0);
					pGD_TControl_Tepl->bAlarm=100;
				}
			break;
			case 1: // sensor temp 2
				if (pGD_Hot_Tepl->InTeplSens[cSmTSens2].RCS != 0)
				{
					__SetBitOutReg(fnTepl,cHSmAlarm,0,0);
					pGD_TControl_Tepl->bAlarm=100;
				}

			break;
			case 2: // sensor temp 3
				if (pGD_Hot_Tepl->InTeplSens[cSmTSens3].RCS != 0)
				{
					__SetBitOutReg(fnTepl,cHSmAlarm,0,0);
					pGD_TControl_Tepl->bAlarm=100;
				}

			break;
			case 3: // sensor temp 4
				if (pGD_Hot_Tepl->InTeplSens[cSmTSens4].RCS != 0)
				{
					__SetBitOutReg(fnTepl,cHSmAlarm,0,0);
					pGD_TControl_Tepl->bAlarm=100;
				}

			break;
			case 4: // sensor temp 5
				if (pGD_Hot_Tepl->InTeplSens[cSmTSens5].RCS != 0)
				{
					__SetBitOutReg(fnTepl,cHSmAlarm,0,0);
					pGD_TControl_Tepl->bAlarm=100;
				}

			break;
			case 5: // sensor temp 6
				if (pGD_Hot_Tepl->InTeplSens[cSmTSens6].RCS != 0)
				{
					__SetBitOutReg(fnTepl,cHSmAlarm,0,0);
					pGD_TControl_Tepl->bAlarm=100;
				}

			break;
			case 6: // min
			{
				if ((pGD_Hot_Tepl->InTeplSens[cSmTSens1].RCS != 0)
					&&(pGD_Hot_Tepl->InTeplSens[cSmTSens2].RCS != 0)
					&&(pGD_Hot_Tepl->InTeplSens[cSmTSens3].RCS != 0)
					&&(pGD_Hot_Tepl->InTeplSens[cSmTSens4].RCS != 0)
					&&(pGD_Hot_Tepl->InTeplSens[cSmTSens5].RCS != 0)
					&&(pGD_Hot_Tepl->InTeplSens[cSmTSens6].RCS != 0))
				{
					__SetBitOutReg(fnTepl,cHSmAlarm,0,0);
					pGD_TControl_Tepl->bAlarm=100;
				}
			}
			break;
			case 7: // max
			{
				if ((pGD_Hot_Tepl->InTeplSens[cSmTSens1].RCS != 0)
					&&(pGD_Hot_Tepl->InTeplSens[cSmTSens2].RCS != 0)
					&&(pGD_Hot_Tepl->InTeplSens[cSmTSens3].RCS != 0)
					&&(pGD_Hot_Tepl->InTeplSens[cSmTSens4].RCS != 0)
					&&(pGD_Hot_Tepl->InTeplSens[cSmTSens5].RCS != 0)
					&&(pGD_Hot_Tepl->InTeplSens[cSmTSens6].RCS != 0))
				{
					__SetBitOutReg(fnTepl,cHSmAlarm,0,0);
					pGD_TControl_Tepl->bAlarm=100;
				}
			}
			break;
			case 8: // average
			{
				if ((pGD_Hot_Tepl->InTeplSens[cSmTSens1].RCS != 0)
					&&(pGD_Hot_Tepl->InTeplSens[cSmTSens2].RCS != 0)
					&&(pGD_Hot_Tepl->InTeplSens[cSmTSens3].RCS != 0)
					&&(pGD_Hot_Tepl->InTeplSens[cSmTSens4].RCS != 0)
					&&(pGD_Hot_Tepl->InTeplSens[cSmTSens5].RCS != 0)
					&&(pGD_Hot_Tepl->InTeplSens[cSmTSens6].RCS != 0))
				{
					__SetBitOutReg(fnTepl,cHSmAlarm,0,0);
					pGD_TControl_Tepl->bAlarm=100;
				}
			}
			break;
		}
}

/*!
\brief Авария датчика температуры воздуха обогрева в зависимости от выбранного значение в Параметрах управления
*/
/*void controlGetTempHeatAlarm(char fnTepl)
{
		switch (pGD_Control_Tepl->sensT_heat)
		{
			case 0: // sensor temp 1
				if (pGD_Hot_Tepl->InTeplSens[cSmTSens1].RCS != 0)
				{
					__SetBitOutReg(fnTepl,cHSmAlarm,0,0);
					pGD_TControl_Tepl->bAlarm=100;
				}
			break;
			case 1: // sensor temp 2
				if (pGD_Hot_Tepl->InTeplSens[cSmTSens2].RCS != 0)
				{
					__SetBitOutReg(fnTepl,cHSmAlarm,0,0);
					pGD_TControl_Tepl->bAlarm=100;
				}

			break;
			case 2: // sensor temp 3
				if (pGD_Hot_Tepl->InTeplSens[cSmTSens3].RCS != 0)
				{
					__SetBitOutReg(fnTepl,cHSmAlarm,0,0);
					pGD_TControl_Tepl->bAlarm=100;
				}

			break;
			case 3: // sensor temp 4
				if (pGD_Hot_Tepl->InTeplSens[cSmTSens4].RCS != 0)
				{
					__SetBitOutReg(fnTepl,cHSmAlarm,0,0);
					pGD_TControl_Tepl->bAlarm=100;
				}

			break;
			case 4: // sensor temp 5
				if (pGD_Hot_Tepl->InTeplSens[cSmTSens5].RCS != 0)
				{
					__SetBitOutReg(fnTepl,cHSmAlarm,0,0);
					pGD_TControl_Tepl->bAlarm=100;
				}

			break;
			case 5: // sensor temp 6
				if (pGD_Hot_Tepl->InTeplSens[cSmTSens6].RCS != 0)
				{
					__SetBitOutReg(fnTepl,cHSmAlarm,0,0);
					pGD_TControl_Tepl->bAlarm=100;
				}

			break;
			case 6: // min
			{
				if ((pGD_Hot_Tepl->InTeplSens[cSmTSens1].RCS != 0)
					&&(pGD_Hot_Tepl->InTeplSens[cSmTSens2].RCS != 0)
					&&(pGD_Hot_Tepl->InTeplSens[cSmTSens3].RCS != 0)
					&&(pGD_Hot_Tepl->InTeplSens[cSmTSens4].RCS != 0)
					&&(pGD_Hot_Tepl->InTeplSens[cSmTSens5].RCS != 0)
					&&(pGD_Hot_Tepl->InTeplSens[cSmTSens6].RCS != 0))
				{
					__SetBitOutReg(fnTepl,cHSmAlarm,0,0);
					pGD_TControl_Tepl->bAlarm=100;
				}
			}
			break;
			case 7: // max
			{
				if ((pGD_Hot_Tepl->InTeplSens[cSmTSens1].RCS != 0)
					&&(pGD_Hot_Tepl->InTeplSens[cSmTSens2].RCS != 0)
					&&(pGD_Hot_Tepl->InTeplSens[cSmTSens3].RCS != 0)
					&&(pGD_Hot_Tepl->InTeplSens[cSmTSens4].RCS != 0)
					&&(pGD_Hot_Tepl->InTeplSens[cSmTSens5].RCS != 0)
					&&(pGD_Hot_Tepl->InTeplSens[cSmTSens6].RCS != 0))
				{
					__SetBitOutReg(fnTepl,cHSmAlarm,0,0);
					pGD_TControl_Tepl->bAlarm=100;
				}
			}
			break;
			case 8: // average
			{
				if ((pGD_Hot_Tepl->InTeplSens[cSmTSens1].RCS != 0)
					&&(pGD_Hot_Tepl->InTeplSens[cSmTSens2].RCS != 0)
					&&(pGD_Hot_Tepl->InTeplSens[cSmTSens3].RCS != 0)
					&&(pGD_Hot_Tepl->InTeplSens[cSmTSens4].RCS != 0)
					&&(pGD_Hot_Tepl->InTeplSens[cSmTSens5].RCS != 0)
					&&(pGD_Hot_Tepl->InTeplSens[cSmTSens6].RCS != 0))
				{
					__SetBitOutReg(fnTepl,cHSmAlarm,0,0);
					pGD_TControl_Tepl->bAlarm=100;
				}
			}
			break;
		}
}

/*!
\brief Температура воздуха для вентиляци в зависимости от выбранного значение в Параметрах управления
@return int16_t Температура
*/
/*int16_t controlGetTempVent()
{
	int16_t	tempVent;
	int16_t temp = 0;
	int16_t i;
		switch (pGD_Control_Tepl->sensT_vent)
		{
			case 0: // sensor temp 1
				if (pGD_Hot_Tepl->InTeplSens[cSmTSens1].RCS == 0)
					tempVent = CURRENT_TEMP1_VALUE;
			break;
			case 1: // sensor temp 2
				if (pGD_Hot_Tepl->InTeplSens[cSmTSens2].RCS == 0)
					tempVent = CURRENT_TEMP2_VALUE;
			break;
			case 2: // sensor temp 3
				if (pGD_Hot_Tepl->InTeplSens[cSmTSens3].RCS == 0)
					tempVent = CURRENT_TEMP3_VALUE;
			break;
			case 3: // sensor temp 4
				if (pGD_Hot_Tepl->InTeplSens[cSmTSens4].RCS == 0)
					tempVent = CURRENT_TEMP4_VALUE;
			break;
			case 4: // sensor temp 5
				if (pGD_Hot_Tepl->InTeplSens[cSmTSens5].RCS == 0)
					tempVent = CURRENT_TEMP5_VALUE;
			break;
			case 5: // sensor temp 6
				if (pGD_Hot_Tepl->InTeplSens[cSmTSens6].RCS == 0)
					tempVent = CURRENT_TEMP6_VALUE;
			break;
			case 6: // min
			{
				for (i=0;i<6;i++)
				{
					if (pGD_Hot_Tepl->InTeplSens[i].RCS == 0)
					{
						temp = pGD_Hot_Tepl->InTeplSens[i].Value;
						return;
					}
				}
				for (i=0;i<6;i++)
				{
					if (pGD_Hot_Tepl->InTeplSens[i].RCS == 0)
					{
						if (temp > pGD_Hot_Tepl->InTeplSens[i].Value)
							temp = pGD_Hot_Tepl->InTeplSens[i].Value;
					}
				}
				tempVent = temp;
			}
			break;
			case 7: // max
			{
				for (i=0;i<6;i++)
				{
					if (pGD_Hot_Tepl->InTeplSens[i].RCS == 0)
					{
						temp = pGD_Hot_Tepl->InTeplSens[i].Value;
						return;
					}
				}
				for (i=0;i<6;i++)
				{
					if (pGD_Hot_Tepl->InTeplSens[i].RCS == 0)
					{
						if (temp < pGD_Hot_Tepl->InTeplSens[i].Value)
							temp = pGD_Hot_Tepl->InTeplSens[i].Value;
					}
				}
				tempVent = temp;
			}
			break;
			case 8: // average
			{
				int16_t count = 0;
				for (i=0;i<6;i++)
				{
					if (pGD_Hot_Tepl->InTeplSens[i].RCS == 0)
					{
						temp = temp + pGD_Hot_Tepl->InTeplSens[i].Value;
						count++;
					}
				}
				temp = temp / count;
				tempVent = temp;
			}
			break;
		}
		return tempVent;
}

/*!
\brief Температура воздуха для обогрева в зависимости от выбранного значение в Параметрах управления
@return int16_t Температура
*/
/*int16_t controlGetTempHeat()
{
	int16_t	tempHeat;
	int16_t temp = 0;
	int16_t i=0;
		switch (pGD_Control_Tepl->sensT_heat)
		{
			case 0: // sensor temp 1
				if (pGD_Hot_Tepl->InTeplSens[cSmTSens1].RCS == 0)
					tempHeat = CURRENT_TEMP1_VALUE;
			break;
			case 1: // sensor temp 2
				if (pGD_Hot_Tepl->InTeplSens[cSmTSens2].RCS == 0)
					tempHeat = CURRENT_TEMP2_VALUE;
			break;
			case 2: // sensor temp 3
				if (pGD_Hot_Tepl->InTeplSens[cSmTSens3].RCS == 0)
					tempHeat = CURRENT_TEMP3_VALUE;
			break;
			case 3: // sensor temp 4
				if (pGD_Hot_Tepl->InTeplSens[cSmTSens4].RCS == 0)
					tempHeat = CURRENT_TEMP4_VALUE;
			break;
			case 4: // sensor temp 5
				if (pGD_Hot_Tepl->InTeplSens[cSmTSens5].RCS == 0)
					tempHeat = CURRENT_TEMP5_VALUE;
			break;
			case 5: // sensor temp 6
				if (pGD_Hot_Tepl->InTeplSens[cSmTSens6].RCS == 0)
					tempHeat = CURRENT_TEMP6_VALUE;
			break;
			case 6: // min
			{
				for (i=0;i<6;i++)
				{
					if (pGD_Hot_Tepl->InTeplSens[i].RCS == 0)
					{
						temp = pGD_Hot_Tepl->InTeplSens[i].Value;
						return;
					}
				}
				for (i=0;i<6;i++)
				{
					if (pGD_Hot_Tepl->InTeplSens[i].RCS == 0)
					{
						if (temp > pGD_Hot_Tepl->InTeplSens[i].Value)
							temp = pGD_Hot_Tepl->InTeplSens[i].Value;
					}
				}
				tempHeat = temp;
			}
			break;
			case 7: // max
			{
				for (i=0;i<6;i++)
				{
					if (pGD_Hot_Tepl->InTeplSens[i].RCS == 0)
					{
						temp = pGD_Hot_Tepl->InTeplSens[i].Value;
						return;
					}
				}
				for (i=0;i<6;i++)
				{
					if (pGD_Hot_Tepl->InTeplSens[i].RCS == 0)
					{
						if (temp < pGD_Hot_Tepl->InTeplSens[i].Value)
							temp = pGD_Hot_Tepl->InTeplSens[i].Value;
					}
				}
				tempHeat = temp;
			}
			break;
			case 8: // average
			{
				int16_t count = 0;
				for (i=0;i<6;i++)
				{
					if (pGD_Hot_Tepl->InTeplSens[i].RCS == 0)
					{
						temp = temp + pGD_Hot_Tepl->InTeplSens[i].Value;
						count++;
					}
				}
				temp = temp / count;
				tempHeat = temp;
			}
			break;
		}
		return tempHeat;
}*/

/*----------------------------------------------------
                Находим нужную программу
------------------------------------------------------*/
int	JumpNext(int Now,int Next,char Check, char Mull)
	{
	long int var;
	if ((Check)&&((!Next)||(!Now)))
		return Now*Mull;
	IntZ=Next-Now;
    var=IntZ;
	var*=IntX;
	if (!IntY) return Now*Mull;
	var/=IntY;
	return(Now+var)*Mull;
	}

void TaskTimer(char fsmTime, char fnTeplTimer, char fnTeplLoad)
{
int8_t nTimer,sTimerNext,sTimerPrev,sTimerMin,sTimerMax;
int	MaxTimeStart,MinTimeStart,NextTimeStart,PrevTimeStart,tVal;
	eTimer xdata *pGD_CurrTimer;
	eTimer xdata *pGD_NextTimer;

	pGD_Hot_Tepl=&GD.Hot.Tepl[fnTeplLoad];
	(*pGD_Hot_Tepl).AllTask.TAir=0;
	IntZ=CtrTime+fsmTime;
	IntZ%=1440;
	MaxTimeStart=0;
	PrevTimeStart=0;
	NextTimeStart=1440;
	MinTimeStart=1440;
	sTimerNext=-1;
	sTimerPrev=-1;
	for (nTimer=0;nTimer<cSTimer;nTimer++) //20
	{
		if (!GD.Timer[nTimer].TimeStart) continue;
		if (GD.Timer[nTimer].Zone[0]!=fnTeplTimer+1) continue;

		if (GD.Timer[nTimer].TimeStart<MinTimeStart)
		{
			MinTimeStart=GD.Timer[nTimer].TimeStart;
			sTimerMin=nTimer;
		}
		if (GD.Timer[nTimer].TimeStart>MaxTimeStart)
		{
			MaxTimeStart=GD.Timer[nTimer].TimeStart;
			sTimerMax=nTimer;
		}
    	if ((GD.Timer[nTimer].TimeStart>=IntZ)&&(NextTimeStart>GD.Timer[nTimer].TimeStart))
		{
			NextTimeStart=GD.Timer[nTimer].TimeStart;
			sTimerNext=nTimer;
		}
    	if ((GD.Timer[nTimer].TimeStart<IntZ)&&(PrevTimeStart<GD.Timer[nTimer].TimeStart))
		{
			PrevTimeStart=GD.Timer[nTimer].TimeStart;
			sTimerPrev=nTimer;
		}
	}
	if (MinTimeStart==1440) return;

	if (sTimerNext<0) sTimerNext=sTimerMin;

	if (sTimerPrev<0) sTimerPrev=sTimerMax;

	pGD_CurrTimer=&GD.Timer[sTimerPrev];
	pGD_NextTimer=&GD.Timer[sTimerNext];

	IntX=CtrTime-GD.Timer[sTimerPrev].TimeStart;
	IntY=GD.Timer[sTimerNext].TimeStart-GD.Timer[sTimerPrev].TimeStart;
	if (IntY<0)
	{	IntY+=1440;}

	if (IntX<0)
	{	IntX+=1440;}

	if (fsmTime) 
	{
		(*pGD_Hot_Tepl).AllTask.NextTAir=JumpNext(pGD_CurrTimer->TAir,pGD_NextTimer->TAir,1,1);	
//Блокировка нулевой темепратуры вентиляции
		tVal=pGD_CurrTimer->TVentAir;
		if (!tVal) tVal=pGD_CurrTimer->TAir+100;
		(*pGD_Hot_Tepl).AllTask.NextTVent=JumpNext(tVal,pGD_NextTimer->TVentAir,1,1);
		(*pGD_Hot_Tepl).AllTask.Light=pGD_CurrTimer->Light;
		(*pGD_Hot_Tepl).AllTask.ModeLight=pGD_CurrTimer->ModeLight;
//		if (pGD_Hot_Tepl->InTeplSens[cSmRHSens])
//		(*pGD_Hot_Tepl).AllTask.NextRHAir=JumpNext(pGD_CurrTimer->RHAir,pGD_NextTimer->RHAir,1);	
		return;
	}


	(*pGD_Hot_Tepl).AllTask.TAir=JumpNext(pGD_CurrTimer->TAir,pGD_NextTimer->TAir,1,1);
	//Блокировка нулевой темепратуры вентиляции
	tVal=pGD_CurrTimer->TVentAir;
	if (!tVal) tVal=pGD_CurrTimer->TAir+100;
	(*pGD_Hot_Tepl).AllTask.DoTVent=JumpNext(tVal,pGD_NextTimer->TVentAir,1,1);
	(*pGD_Hot_Tepl).AllTask.DoTCool=JumpNext(pGD_CurrTimer->TCool,pGD_NextTimer->TCool,1,1);

	(*pGD_Hot_Tepl).AllTask.SIO=pGD_CurrTimer->SIO;
	(*pGD_Hot_Tepl).AllTask.RHAir=JumpNext(pGD_CurrTimer->RHAir_c,pGD_NextTimer->RHAir_c,1,100);
	(*pGD_Hot_Tepl).AllTask.CO2=JumpNext(pGD_CurrTimer->CO2,pGD_NextTimer->CO2,1,1);
	(*pGD_Hot_Tepl).Kontur[cSmKontur1].MinTask=JumpNext(pGD_CurrTimer->MinTPipe1,pGD_NextTimer->MinTPipe1,1,10);

	(*pGD_Hot_Tepl).Kontur[cSmKontur2].MinTask=JumpNext(pGD_CurrTimer->MinTPipe2,pGD_NextTimer->MinTPipe2,1,10);

	(*pGD_Hot_Tepl).Kontur[cSmKontur3].MinTask=JumpNext(pGD_CurrTimer->MinTPipe3,pGD_NextTimer->MinTPipe3,1,10);
	(*pGD_Hot_Tepl).Kontur[cSmKontur5].MinTask=JumpNext(pGD_CurrTimer->MinTPipe5,pGD_NextTimer->MinTPipe5,1,10);

	(*pGD_Hot_Tepl).Kontur[cSmKontur1].Optimal=JumpNext(pGD_CurrTimer->TOptimal1,pGD_NextTimer->TOptimal1,1,10);

	(*pGD_Hot_Tepl).Kontur[cSmKontur2].Optimal=JumpNext(pGD_CurrTimer->TOptimal2,pGD_NextTimer->TOptimal2,1,10);

	(*pGD_Hot_Tepl).Kontur[cSmWindowUnW].MinTask=JumpNext(((uchar)pGD_CurrTimer->MinOpenWin),((uchar)pGD_NextTimer->MinOpenWin),0,1);
	(*pGD_Hot_Tepl).AllTask.Win=pGD_CurrTimer->Win;
	(*pGD_Hot_Tepl).AllTask.Screen[0]=pGD_CurrTimer->Screen[0];
	(*pGD_Hot_Tepl).AllTask.Screen[1]=pGD_CurrTimer->Screen[1];
	(*pGD_Hot_Tepl).AllTask.Screen[2]=pGD_CurrTimer->Screen[2];
	(*pGD_Hot_Tepl).AllTask.AHUVent=pGD_CurrTimer->AHUVent;
	(*pGD_Hot_Tepl).Kontur[cSmAHUSpd].MinCalc=(*pGD_Hot_Tepl).AllTask.AHUVent;
//	(*pGD_Hot_Tepl).AllTask.Poise=pGD_CurrTimer->Poise;
	(*pGD_Hot_Tepl).Kontur[cSmKontur3].Do=JumpNext(pGD_CurrTimer->TPipe3,pGD_NextTimer->TPipe3,1,10);
	(*pGD_Hot_Tepl).Kontur[cSmKontur4].Do=JumpNext(pGD_CurrTimer->TPipe4,pGD_NextTimer->TPipe4,1,10);

}


void AllTaskAndCorrection(void)
{
	
	IntY=GD.Hot.MidlSR;//MeteoSens[cSmFARSens].Value;
	/*Установка и коррекция по солнцу температуры обогрева*/
	(*pGD_Hot_Tepl).AllTask.DoTHeat=(*pGD_Hot_Tepl).AllTask.TAir;
	IntX=CorrectionRule(GD.TuneClimate.s_TStart[0],GD.TuneClimate.s_TEnd,
		GD.TuneClimate.s_TConst,cbCorrTOnSun);	
	SetBit((*pGD_Hot_Tepl).RCS,IntX);
	ClrDog;
	(*pGD_Hot_Tepl).AllTask.DoTHeat+=IntZ;
			/*Коррекция прогноза*/
	(*pGD_Hot_Tepl).AllTask.NextTAir+=IntZ;
	if ((*pGD_Hot_Tepl).AllTask.DoTVent)
	{
		CorrectionRule(GD.TuneClimate.s_TStart[0],GD.TuneClimate.s_TEnd,
			GD.TuneClimate.s_TVentConst,0);	
		(*pGD_Hot_Tepl).AllTask.DoTVent+=IntZ;
		(*pGD_Hot_Tepl).AllTask.NextTVent+=IntZ;
	}
	else
	{
		(*pGD_Hot_Tepl).AllTask.DoTVent=(*pGD_Hot_Tepl).AllTask.DoTHeat+100;
		(*pGD_Hot_Tepl).AllTask.NextTVent=(*pGD_Hot_Tepl).AllTask.NextTAir+100;
	}
//	if ((*(pGD_Hot_Hand+cHSmScrTH)).Position)
//		(*pGD_Hot_Tepl).AllTask.NextRezTAir=(*pGD_Hot_Tepl).AllTask.NextTAir-GD.TuneClimate.sc_DoTemp;
	/*---------------------------------------------------*/
	/*Установка и коррекция по солнцу заданной влажности*/
	if ((*pGD_Hot_Tepl).AllTask.RHAir)
		{
		(*pGD_Hot_Tepl).AllTask.DoRHAir=(*pGD_Hot_Tepl).AllTask.RHAir;
		IntX=CorrectionRule(GD.TuneClimate.s_TStart[0],GD.TuneClimate.s_TEnd,
			GD.TuneClimate.s_RHConst,cbCorrRHOnSun);	
		SetBit((*pGD_Hot_Tepl).RCS,IntX);
		(*pGD_Hot_Tepl).AllTask.DoRHAir-=IntZ;
			/*Коррекция прогноза*/
//		(*pGD_Hot_Tepl).AllTask.NextRHAir-=IntZ;		
		}
	/*---------------------------------------------------*/
	/*Установка и коррекция по солнцу заданной концентрации СО2*/
	if ((*pGD_Hot_Tepl).AllTask.CO2)
		{
//ОПТИМИЗАЦИЯ
		(*pGD_Hot_Tepl).AllTask.DoCO2=(*pGD_Hot_Tepl).AllTask.CO2;
		IntX=CorrectionRule(GD.TuneClimate.s_TStart[0],GD.TuneClimate.s_TEnd,
			GD.TuneClimate.s_CO2Const,cbCorrCO2OnSun);	
		SetBit((*pGD_Hot_Tepl).RCS,IntX);
		(*pGD_Hot_Tepl).AllTask.DoCO2+=IntZ;
		}
	/*---------------------------------------------------*/
	/*Установка и коррекция по солнцу минимальной температуры в контурах 1,2 и 3*/


	if ((*pGD_Hot_Tepl).Kontur[cSmKontur1].MinTask)         // NEW
		{
			IntX=CorrectionRule(GD.TuneClimate.s_TStart[0],GD.TuneClimate.s_TEnd,
				GD.TuneClimate.s_MinTPipeConst,0/*cbCorrMinTaskOnSun*/);
	//		SetBit((*pGD_Hot_Tepl).Kontur[cSmKontur1].RCS,IntX);
			(*pGD_Hot_Tepl).Kontur[cSmKontur1].MinCalc=(*pGD_Hot_Tepl).Kontur[cSmKontur1].MinTask-IntZ;
			IntY=DefRH();//MeteoSens[cSmFARSens].Value;

			IntX=CorrectionRule(GD.TuneClimate.c_RHStart,GD.TuneClimate.c_RHEnd,
				GD.TuneClimate.c_RHOnMin1,0/*cbCorrMinTaskOnSun*/);
	//		SetBit((*pGD_Hot_Tepl).Kontur[cSmKontur1].RCS,IntX);
			(*pGD_Hot_Tepl).Kontur[cSmKontur1].MinCalc+=IntZ;

		}
		(*pGD_Hot_Tepl).Kontur[cSmKontur2].MinCalc=(*pGD_Hot_Tepl).Kontur[cSmKontur2].MinTask;
		if ((*pGD_Hot_Tepl).Kontur[cSmKontur2].MinTask)
		{
			IntY=DefRH();//MeteoSens[cSmFARSens].Value;

			IntX=CorrectionRule(GD.TuneClimate.c_RHStart,GD.TuneClimate.c_RHEnd,
			GD.TuneClimate.c_RHOnMin2,0/*cbCorrMinTaskOnSun*/);
	//		SetBit((*pGD_Hot_Tepl).Kontur[cSmKontur1].RCS,IntX);
			(*pGD_Hot_Tepl).Kontur[cSmKontur2].MinCalc+=IntZ;
		}
		(*pGD_Hot_Tepl).Kontur[cSmKontur3].MinCalc=(*pGD_Hot_Tepl).Kontur[cSmKontur3].MinTask;
		if ((*pGD_Hot_Tepl).Kontur[cSmKontur3].MinTask)
		{
			IntY=DefRH();//MeteoSens[cSmFARSens].Value;

			IntX=CorrectionRule(GD.TuneClimate.c_RHStart,GD.TuneClimate.c_RHEnd,
			GD.TuneClimate.c_RHOnMin3,0/*cbCorrMinTaskOnSun*/);
	//		SetBit((*pGD_Hot_Tepl).Kontur[cSmKontur1].RCS,IntX);
			(*pGD_Hot_Tepl).Kontur[cSmKontur3].MinCalc+=IntZ;
		}

//******************
		if ((*pGD_Hot_Tepl).Kontur[cSmKontur5].MinTask)
		{
			IntX=CorrectionRule(GD.TuneClimate.s_TStart[0],GD.TuneClimate.s_TEnd,
				GD.TuneClimate.s_MinTPipe5,0/*cbCorrMinTaskOnSun*/);
			(*pGD_Hot_Tepl).Kontur[cSmKontur5].MinCalc=(*pGD_Hot_Tepl).Kontur[cSmKontur5].MinTask+IntZ;
		}
//*******************



/*	if ((*pGD_Hot_Tepl).Kontur[cSmKontur1].MinTask)					// OLD
	{	
		IntX=CorrectionRule(GD.TuneClimate.s_TStart[0],GD.TuneClimate.s_TEnd,
			GD.TuneClimate.s_MinTPipeConst,0);
		(*pGD_Hot_Tepl).Kontur[cSmKontur1].MinCalc=(*pGD_Hot_Tepl).Kontur[cSmKontur1].MinTask-IntZ;
	}
	(*pGD_Hot_Tepl).Kontur[cSmKontur2].MinCalc=(*pGD_Hot_Tepl).Kontur[cSmKontur2].MinTask;
	if ((*pGD_Hot_Tepl).Kontur[cSmKontur3].MinTask)
	{	
		IntX=CorrectionRule(GD.TuneClimate.s_TStart[0],GD.TuneClimate.s_TEnd,
			GD.TuneClimate.s_MinTPipe3,0);	
		(*pGD_Hot_Tepl).Kontur[cSmKontur3].MinCalc=(*pGD_Hot_Tepl).Kontur[cSmKontur3].MinTask-IntZ;
	}
	if ((*pGD_Hot_Tepl).Kontur[cSmKontur5].MinTask)
	{	
		IntX=CorrectionRule(GD.TuneClimate.s_TStart[0],GD.TuneClimate.s_TEnd,
			GD.TuneClimate.s_MinTPipe5,0);
		(*pGD_Hot_Tepl).Kontur[cSmKontur5].MinCalc=(*pGD_Hot_Tepl).Kontur[cSmKontur5].MinTask+IntZ;
	}
*/

//	(*pGD_Hot_Tepl).AllTask.DoPressure=(*pGD_Control_Tepl).c_DoPres;
	/*-------------------------------------------------------------*/

	/*Установка и коррекция по солнцу минимального положения подветренных фрамуг*/
	if ((*pGD_Hot_Tepl).Kontur[cSmWindowUnW].MinTask)
	{	
		(*pGD_Hot_Tepl).Kontur[cSmWindowUnW].MinCalc=(*pGD_Hot_Tepl).Kontur[cSmWindowUnW].MinTask;
		IntX=CorrectionRule(GD.TuneClimate.s_TStart[0],GD.TuneClimate.s_TEnd,
			GD.TuneClimate.s_MinOpenWinConst,0/*cbCorrMinTaskOnSun*/);	
		SetBit((*pGD_Hot_Tepl).Kontur[cSmWindowUnW].RCS,IntX);
		(*pGD_Hot_Tepl).Kontur[cSmWindowUnW].MinCalc+=IntZ;
	}
	/*----------------------------------------------------------------*/
		IntY=DefRH();
		CorrectionRule(GD.TuneClimate.f_min_RHStart,GD.TuneClimate.f_min_RHEnd,
			GD.TuneClimate.f_CorrTVent,0);
		(*pGD_Hot_Tepl).AllTask.NextTVent-=IntZ;
		(*pGD_Hot_Tepl).AllTask.DoTVent-=IntZ;
		IntY=-IntY;

		CorrectionRule(GD.TuneClimate.f_max_RHStart,GD.TuneClimate.f_max_RHEnd,
			GD.TuneClimate.f_CorrTVentUp,0);
		(*pGD_Hot_Tepl).AllTask.NextTVent+=IntZ;
		(*pGD_Hot_Tepl).AllTask.DoTVent+=IntZ;

//	Установка темпеатуры вентилирования
//	(*pGD_Hot_Tepl).AllTask.DoTVent=(*pGD_Hot_Tepl).AllTask.NextTAir;//GD.TControl.Tepl[0].SensHalfHourAgo;//(*pGD_Hot_Tepl).AllTask.DoTHeat;//+GD.TuneClimate.d_TempVent;
//	Коррекция по влажности темпеатуры задания

//	IntY=DefRH();
	//(*pGD_Hot_Tepl).InTeplSens[cSmRHSens].Value-(*pGD_Hot_Tepl).AllTask.DoRHAir;
	//if ((!(*pGD_Hot_Tepl).AllTask.DoRHAir)||(!(*pGD_Hot_Tepl).InTeplSens[cSmRHSens].Value)) IntY=0;

//		Если влажность повышенная,то...
//	IntX=CorrectionRule(GD.TuneClimate.t_UpRHStart,GD.TuneClimate.t_UpRHEnd,
//		GD.TuneClimate.t_UpRHTFactor,cbCorrTAirUpOnRH);	
//	(*pGD_Hot_Tepl).AllTask.DoTHeat-=IntZ;
//	(*pGD_Hot_Tepl).AllTask.NextTAir-=IntZ;
//	IntY=-IntY;
//		Если влажность пониже,то...
//	IntX=CorrectionRule(GD.TuneClimate.t_DownRHStart,GD.TuneClimate.t_DownRHEnd,
//		GD.TuneClimate.t_DownRHTFactor,cbCorrTAirDownOnRH);	
//	(*pGD_Hot_Tepl).AllTask.DoTHeat+=IntZ;
//	(*pGD_Hot_Tepl).AllTask.NextTAir+=IntZ;
	ClrDog;
	/*--------------------------------------------------------------*/

}
void SetIfReset(void)
{

	for(ByteX=0;ByteX<cSWaterKontur;ByteX++)
	{
		SetPointersOnKontur(ByteX);
		pGD_TControl_Tepl_Kontur->DoT=pGD_TControl_Tepl_Kontur->SensValue*10;//((long int)pGD_Hot_Tepl->InTeplSens[ByteX+cSmWaterSens].Value)*100;		
		pGD_TControl_Tepl_Kontur->PumpPause=cPausePump;
		pGD_TControl_Tepl_Kontur->PumpStatus=1;
	}
//	pGD_TControl_Tepl->Kontur[cSmWindowUnW+GD.Hot.PozFluger].DoT=(((*(pGD_Hot_Hand+cHSmWinS)).Position))*10;
//	pGD_TControl_Tepl->Kontur[cSmWindowUnW+1-GD.Hot.PozFluger].DoT=(((*(pGD_Hot_Hand+cHSmWinN)).Position))*10;

}

/**********************************************************************/
/*-*-*-*-*--Нахождение прогнозируемого изменения температуры--*-*-*-*-*/
/**********************************************************************/
void __cNextTCalc(char fnTepl)
{
	int	xdata CalcAllKontur;

	if(!(*pGD_Hot_Tepl).AllTask.NextTAir) return;


	if (bWaterReset[fnTepl]) 
	{	
		SetIfReset();
	}
#warning task 61
/*Расчитываем Тизмерения-Тзадания*/
	/*
	pGD_Level_Tepl[cSmTSens1][cSmUpAlarmLev]=0;
	pGD_Level_Tepl[cSmTSens2][cSmUpAlarmLev]=0;
	pGD_Level_Tepl[cSmTSens3][cSmUpAlarmLev]=0;
	pGD_Level_Tepl[cSmTSens4][cSmUpAlarmLev]=0;
	pGD_Level_Tepl[cSmTSens5][cSmUpAlarmLev]=0;
	pGD_Level_Tepl[cSmTSens6][cSmUpAlarmLev]=0;
	pGD_Level_Tepl[cSmTSens1][cSmDownAlarmLev]=0;
	pGD_Level_Tepl[cSmTSens2][cSmDownAlarmLev]=0;
	pGD_Level_Tepl[cSmTSens3][cSmDownAlarmLev]=0;
	pGD_Level_Tepl[cSmTSens4][cSmDownAlarmLev]=0;
	pGD_Level_Tepl[cSmTSens5][cSmDownAlarmLev]=0;
	pGD_Level_Tepl[cSmTSens6][cSmDownAlarmLev]=0;
	if (GD.TuneClimate.c_MaxDifTUp)
	{
		pGD_Level_Tepl[cSmTSens1][cSmUpAlarmLev]=(*pGD_Hot_Tepl).AllTask.DoTHeat+GD.TuneClimate.c_MaxDifTUp;
		pGD_Level_Tepl[cSmTSens2][cSmUpAlarmLev]=(*pGD_Hot_Tepl).AllTask.DoTHeat+GD.TuneClimate.c_MaxDifTUp;
		pGD_Level_Tepl[cSmTSens3][cSmUpAlarmLev]=(*pGD_Hot_Tepl).AllTask.DoTHeat+GD.TuneClimate.c_MaxDifTUp;
		pGD_Level_Tepl[cSmTSens4][cSmUpAlarmLev]=(*pGD_Hot_Tepl).AllTask.DoTHeat+GD.TuneClimate.c_MaxDifTUp;
		pGD_Level_Tepl[cSmTSens5][cSmUpAlarmLev]=(*pGD_Hot_Tepl).AllTask.DoTHeat+GD.TuneClimate.c_MaxDifTUp;
		pGD_Level_Tepl[cSmTSens6][cSmUpAlarmLev]=(*pGD_Hot_Tepl).AllTask.DoTHeat+GD.TuneClimate.c_MaxDifTUp;
	}
	if (GD.TuneClimate.c_MaxDifTDown)
	{
		pGD_Level_Tepl[cSmTSens1][cSmDownAlarmLev]=(*pGD_Hot_Tepl).AllTask.DoTHeat-GD.TuneClimate.c_MaxDifTDown;
		pGD_Level_Tepl[cSmTSens2][cSmDownAlarmLev]=(*pGD_Hot_Tepl).AllTask.DoTHeat-GD.TuneClimate.c_MaxDifTDown;
		pGD_Level_Tepl[cSmTSens3][cSmDownAlarmLev]=(*pGD_Hot_Tepl).AllTask.DoTHeat-GD.TuneClimate.c_MaxDifTDown;
		pGD_Level_Tepl[cSmTSens4][cSmDownAlarmLev]=(*pGD_Hot_Tepl).AllTask.DoTHeat-GD.TuneClimate.c_MaxDifTDown;
		pGD_Level_Tepl[cSmTSens5][cSmDownAlarmLev]=(*pGD_Hot_Tepl).AllTask.DoTHeat-GD.TuneClimate.c_MaxDifTDown;
		pGD_Level_Tepl[cSmTSens6][cSmDownAlarmLev]=(*pGD_Hot_Tepl).AllTask.DoTHeat-GD.TuneClimate.c_MaxDifTDown;
	}
	*/
	(*pGD_Hot_Tepl).NextTCalc.DifTAirTDo=(*pGD_Hot_Tepl).AllTask.NextTAir-getTempHeat(fnTepl);
/**********************************************/
/*СУПЕР АЛГОРИТМ ДЛЯ РАСЧЕТА*/
	pGD_Hot_Tepl->AllTask.Rez[0]=getTempHeat(fnTepl);
	IntX=(*pGD_Hot_Tepl).AllTask.DoTHeat-getTempHeat(fnTepl);

/**********************************************/	
/*Вычиляем увеличение от солнечной радиации*/
	IntY=GD.Hot.MidlSR;
	if ((!YesBit(pGD_Hot_Tepl->InTeplSens[cSmInLightSens].RCS,cbNoWorkSens)))
		IntY=pGD_Hot_Tepl->InTeplSens[cSmInLightSens].Value;

	CorrectionRule(GD.TuneClimate.c_SRStart,GD.TuneClimate.c_SREnd,
		GD.TuneClimate.c_SRFactor,0);	
	(*pGD_Hot_Tepl).NextTCalc.UpSR=IntZ;
/*Вычиляем увеличение от разницы температуры задания и стекла*/	
	IntY=(*pGD_Hot_Tepl).AllTask.NextTAir-(*pGD_Hot_Tepl).InTeplSens[cSmGlassSens].Value;
	CorrectionRule(GD.TuneClimate.c_GlassStart,GD.TuneClimate.c_GlassEnd,
		GD.TuneClimate.c_GlassFactor,0);	
	(*pGD_Hot_Tepl).NextTCalc.LowGlass=IntZ;

	ClrDog;
/*Вычисляем корректировки ветра фрамуг и разницы между температурой задания
и внешней температуры соответственно*/		
/*Ветер и фрамуги увеличивают эту разницу*/
	IntY=GD.Hot.MidlWind;
	CorrectionRule(GD.TuneClimate.c_WindStart,GD.TuneClimate.c_WindEnd,
		GD.TuneClimate.c_WindFactor,0);	
	IntY=(*pGD_Hot_Tepl).AllTask.NextTAir-GD.TControl.MeteoSensing[cSmOutTSens]-IntZ;
	CorrectionRule(GD.TuneClimate.c_OutStart,GD.TuneClimate.c_OutEnd,
		GD.TuneClimate.c_OutFactor,0);
	(*pGD_Hot_Tepl).NextTCalc.LowOutWinWind+=IntZ;
	
//	if (YesBit((*pGD_Hot_Tepl).DiskrSens[0],cSmLightDiskr))
		(*pGD_Hot_Tepl).NextTCalc.UpLight=(((long)GD.TuneClimate.c_LightFactor)*((*(pGD_Hot_Hand+cHSmLight)).Position))/100;
//******************** NOT NEEDED
//	IntY=1;
//	IntY<<=fnTepl;
//	if (YesBit(GD.Hot.isLight,IntY))
//		(*pGD_Hot_Tepl).NextTCalc.UpLight=GD.TuneClimate.c_LightFactor;
//********************************************************

/*Считаем сумму поправок*/
	(*pGD_Hot_Tepl).NextTCalc.dSumCalc=
		+(*pGD_Hot_Tepl).NextTCalc.UpSR
		-(*pGD_Hot_Tepl).NextTCalc.LowGlass
		-(*pGD_Hot_Tepl).NextTCalc.LowOutWinWind
		+(*pGD_Hot_Tepl).NextTCalc.UpLight;

//		-(*pGD_Hot_Tepl).NextTCalc.LowRain;
	if (GD.TControl.bSnow)
		(*pGD_Hot_Tepl).NextTCalc.dSumCalc-=GD.TuneClimate.c_CloudFactor;
/*********************************************************************
******* СЧИТАЕМ СУММУ ВЛИЯНИЙ ДЛЯ ФРАМУГ *******************************
***********************************************************************/
	pGD_Hot_Tepl->NextTCalc.dSumCalcF=0;
/*Вычиляем увеличение от солнечной радиации*/
	IntY=GD.Hot.MidlSR;
/*if work on internal light sensor, then change IntY*/

	if ((!YesBit(pGD_Hot_Tepl->InTeplSens[cSmInLightSens].RCS,cbNoWorkSens)))
		IntY=pGD_Hot_Tepl->InTeplSens[cSmInLightSens].Value;

	CorrectionRule(GD.TuneClimate.c_SRStart,GD.TuneClimate.c_SREnd,
		GD.TuneClimate.f_SRFactor,0);	
	pGD_Hot_Tepl->NextTCalc.dSumCalcF+=IntZ;

	ClrDog;
/*Вычисляем корректировки ветра фрамуг и разницы между температурой задания
и внешней температуры соответственно*/		
/*Ветер и фрамуги увеличивают эту разницу*/
	IntY=GD.Hot.MidlWind;
	CorrectionRule(GD.TuneClimate.c_WindStart,GD.TuneClimate.c_WindEnd,
		GD.TuneClimate.f_WindFactor,0);	
	IntY=(*pGD_Hot_Tepl).AllTask.NextTAir-GD.TControl.MeteoSensing[cSmOutTSens]-IntZ;
	CorrectionRule(GD.TuneClimate.c_OutStart,GD.TuneClimate.c_OutEnd,
		GD.TuneClimate.f_OutFactor,0);
	pGD_Hot_Tepl->NextTCalc.dSumCalcF+=IntZ;
/*********************************************************************
***********************************************************************
***********************************************************************/



	IntY=(*pGD_Hot_Tepl).NextTCalc.DifTAirTDo;
	if ((GD.TuneClimate.c_MullDown>10)&&(IntY<0)&&(GD.TuneClimate.c_MullDown<30))
		IntY=(((long)IntY)*GD.TuneClimate.c_MullDown)/10;
	(*pGD_Hot_Tepl).NextTCalc.PCorrection=((int)((((long)(IntY))*((long)pGD_Control_Tepl->c_PFactor))/100));
	if (pGD_TControl_Tepl->StopI<2)
	 	(*pGD_TControl_Tepl).Integral+=((((long)(pGD_Hot_Tepl->NextTCalc.DifTAirTDo))*((long)pGD_Control_Tepl->c_IFactor))/10);
	if ((*pGD_TControl_Tepl).Integral>2000000)
		(*pGD_TControl_Tepl).Integral=2000000;
	if ((*pGD_TControl_Tepl).Integral<-2000000)
		(*pGD_TControl_Tepl).Integral=-2000000;
	if (!pGD_Control_Tepl->c_IFactor)
		(*pGD_TControl_Tepl).Integral=0;

	(*pGD_Hot_Tepl).NextTCalc.ICorrection=(int)(pGD_TControl_Tepl->Integral/100);			

	(*pGD_TControl_Tepl).Critery=(*pGD_Hot_Tepl).NextTCalc.PCorrection+(*pGD_Hot_Tepl).NextTCalc.ICorrection-(*pGD_Hot_Tepl).NextTCalc.dSumCalc;
	CalcAllKontur=__sCalcTempKonturs();
	(*pGD_TControl_Tepl).Critery-=CalcAllKontur;
//	(*pGD_Hot_Tepl).NextTCalc.dNextTCalc=CalcAllKontur;
	if (pGD_TControl_Tepl->StopI>4)
	{
		(*pGD_TControl_Tepl).Integral=(*pGD_TControl_Tepl).SaveIntegral;	
	}
//	IntY=(*pGD_Hot_Tepl).NextTCalc.DifTAirTDo;
	(*pGD_TControl_Tepl).SaveIntegral=(*pGD_TControl_Tepl).Integral;
	if ((pGD_TControl_Tepl->StopI>3)&&(abs(IntY)<cResetDifTDo))
	{

//		CorrectionRule(0,200,1000,0);
//		IntZ--;
		if ((*pGD_TControl_Tepl).Critery>cResetCritery)
		{
			(*pGD_TControl_Tepl).SaveIntegral
				=cResetCritery+CalcAllKontur
				-(*pGD_Hot_Tepl).NextTCalc.PCorrection+(*pGD_Hot_Tepl).NextTCalc.dSumCalc;
		    (*pGD_TControl_Tepl).SaveIntegral*=100;
		}
//		IntY=-IntY;
//		CorrectionRule(0,200,1000,0);
//		IntZ--;
		if ((*pGD_TControl_Tepl).Critery<-cResetCritery)
		{
			(*pGD_TControl_Tepl).SaveIntegral
				=-cResetCritery+CalcAllKontur
				-(*pGD_Hot_Tepl).NextTCalc.PCorrection+(*pGD_Hot_Tepl).NextTCalc.dSumCalc;
		    (*pGD_TControl_Tepl).SaveIntegral*=100;
		}
	} 
	if ((pGD_TControl_Tepl->StopI>3)&&(!SameSign(IntY,(*pGD_TControl_Tepl).Critery)))
	{
			(*pGD_TControl_Tepl).SaveIntegral
				=IntY+CalcAllKontur
				-(*pGD_Hot_Tepl).NextTCalc.PCorrection+(*pGD_Hot_Tepl).NextTCalc.dSumCalc;
		    (*pGD_TControl_Tepl).SaveIntegral*=100;		
	}
	if (!(*pGD_TControl_Tepl).Critery)
	{
		(*pGD_TControl_Tepl).Critery=1;
		if ((*pGD_Hot_Tepl).NextTCalc.DifTAirTDo<0)
			(*pGD_TControl_Tepl).Critery=-1;

	}	
	pGD_Hot_Tepl->NextTCalc.Critery=(*pGD_TControl_Tepl).Critery;

/******************************************************************
		Далее расчет критерия для фрамуг
*******************************************************************/
	IntY=(*pGD_Hot_Tepl).AllTask.DoTVent-getTempVent(fnTepl);

	(*pGD_Hot_Tepl).NextTCalc.PCorrectionVent=((int)((((long)(IntY))*((long)pGD_Control_Tepl->f_PFactor))/100));
 	(*pGD_TControl_Tepl).IntegralVent+=((((long)(IntY))*((long)pGD_Control_Tepl->f_IFactor))/10);
//	if (!pGD_Control_Tepl->f_IFactor)
//		(*pGD_TControl_Tepl).IntegralVent=0;

	(*pGD_Hot_Tepl).NextTCalc.ICorrectionVent=(int)(pGD_TControl_Tepl->IntegralVent/100);
	IntX=(*pGD_Hot_Tepl).NextTCalc.PCorrectionVent+(*pGD_Hot_Tepl).NextTCalc.ICorrectionVent;//+(*pGD_Hot_Tepl).NextTCalc.dSumCalcF;

	//Проверка на максимум расчета пока константа + 3 градуса
	int tempPipe3 = GD.Control.Tepl[fnTepl].tempPipe3 * 100;
	//if (pGD_Hot_Tepl->AllTask.DoTVent+300<IntX)  // old
	if (pGD_Hot_Tepl->AllTask.DoTVent+tempPipe3<IntX)
	{
		//pGD_TControl_Tepl->IntegralVent=pGD_Hot_Tepl->AllTask.DoTVent+300-(*pGD_Hot_Tepl).NextTCalc.PCorrectionVent;//-(*pGD_Hot_Tepl).NextTCalc.dSumCalcF; 		// old
		pGD_TControl_Tepl->IntegralVent=pGD_Hot_Tepl->AllTask.DoTVent+tempPipe3-(*pGD_Hot_Tepl).NextTCalc.PCorrectionVent;//-(*pGD_Hot_Tepl).NextTCalc.dSumCalcF;
		pGD_TControl_Tepl->IntegralVent*=100;
		//IntX=pGD_Hot_Tepl->AllTask.DoTVent+300;	// old
		IntX=pGD_Hot_Tepl->AllTask.DoTVent+tempPipe3;
	}
	//Проверка на мминимум расчета пока константа 14 градусов
	int minMinPipeTemp = GD.Timer[fnTepl].MinTPipe3 * 100;
	if (minMinPipeTemp < 1400) minMinPipeTemp = MINPIPETEMPER;
	if (minMinPipeTemp > IntX)
	//if (1400>IntX)
	{
		//pGD_TControl_Tepl->IntegralVent=1400-(*pGD_Hot_Tepl).NextTCalc.PCorrectionVent;//-(*pGD_Hot_Tepl).NextTCalc.dSumCalcF;  old
		pGD_TControl_Tepl->IntegralVent=minMinPipeTemp-(*pGD_Hot_Tepl).NextTCalc.PCorrectionVent;//-(*pGD_Hot_Tepl).NextTCalc.dSumCalcF;
		pGD_TControl_Tepl->IntegralVent*=100;
		//IntX=1400; // old
		IntX=minMinPipeTemp;
	}
	pGD_TControl_Tepl->TVentCritery=IntX;
	(*pGD_Hot_Tepl).NextTCalc.TVentCritery=(*pGD_TControl_Tepl).TVentCritery;

	//Расчет влажности рукава по заданию влажности воздуха- пока запишем в интегральную поправку
	(*pGD_Hot_Tepl).NextTCalc.ICorrectionVent=AbsHum(pGD_Hot_Tepl->AllTask.DoTVent,pGD_Hot_Tepl->AllTask.DoRHAir);
	(*pGD_Hot_Tepl).NextTCalc.ICorrectionVent=RelHum(pGD_TControl_Tepl->TVentCritery,(*pGD_Hot_Tepl).NextTCalc.ICorrectionVent);
	if ((*pGD_Hot_Tepl).NextTCalc.ICorrectionVent>9500)
		(*pGD_Hot_Tepl).NextTCalc.ICorrectionVent=9500;

}



/*------------------------------------------------------*/
void    SetMixValvePosition(void)
{
	int16_t	*IntVal;
	ClrDog;
	for (ByteX=0;ByteX<cSWaterKontur;ByteX++)
	{
		SetPointersOnKontur(ByteX);
		if (YesBit((*(pGD_Hot_Hand_Kontur+cHSmMixVal)).RCS,(/*cbNoMech+*/cbManMech))) continue;
		if (!pGD_TControl_Tepl_Kontur->PumpStatus)
		{
			(*(pGD_Hot_Hand_Kontur+cHSmMixVal)).Position=0;
			continue;
		}
		ogrMin(&(pGD_TControl_Tepl_Kontur->TPause),0);// (*pGD_TControl_Tepl).Kontur[ByteX].TPause=0;	
		if (YesBit(pGD_TControl_Tepl->MechBusy[ByteX].RCS,cMSBusyMech)) continue;
		if (pGD_TControl_Tepl_Kontur->TPause) 
		{
			pGD_TControl_Tepl_Kontur->TPause--;
			continue;
		}
		pGD_TControl_Tepl_Kontur->TPause=cMinPauseMixValve;
		
		IntX=pGD_Hot_Tepl_Kontur->Do-pGD_TControl_Tepl_Kontur->SensValue;
		//(*IntVal)=(*IntVal)+IntX;

		(*(pGD_Hot_Hand_Kontur+cHSmMixVal)).Position=SetPID(IntX,cHSmMixVal+ByteX,100,0);

	}
}



void	DoPumps(void)
{
	for(ByteX=0;ByteX<cSWaterKontur;ByteX++)
	{
		if (!(YesBit((*(pGD_Hot_Hand+cHSmPump+ByteX)).RCS,(/*cbNoMech+*/cbManMech))))
			(*(pGD_Hot_Hand+cHSmPump+ByteX)).Position=pGD_TControl_Tepl->Kontur[ByteX].PumpStatus;
	}

}

void	DoVentCalorifer(void)
{

}

void	DoLights(void)
{
	if (YesBit((*(pGD_Hot_Hand+cHSmLight)).RCS,(/*cbNoMech+*/cbManMech))) return;
//	pGD_Hot_Hand[cHSmLight].Position=0;
	pGD_Hot_Hand[cHSmLight].Position=pGD_TControl_Tepl->LightValue;
}

/*void	DoPoisen(void)
{
	if (YesBit((*(pGD_Hot_Hand+cHSmPoise)).RCS,(cbManMech))) return;
	pGD_Hot_Hand[cHSmPoise].Position=0;
		if (pGD_Hot_Tepl->AllTask.Poise)
			pGD_Hot_Hand[cHSmPoise].Position=1;
} */

void 	SetSensOnMech(void)
{
	for (ByteX=0;ByteX<cSRegCtrl;ByteX++)
		pGD_TControl_Tepl->MechBusy[ByteX].Sens=0;
	pGD_TControl_Tepl->MechBusy[cHSmWinN].Sens=&pGD_Hot_Tepl->InTeplSens[cSmWinNSens];
	pGD_TControl_Tepl->MechBusy[cHSmWinS].Sens=&pGD_Hot_Tepl->InTeplSens[cSmWinSSens];
	pGD_TControl_Tepl->MechBusy[cHSmScrTH].Sens=&pGD_Hot_Tepl->InTeplSens[cSmScreenSens];
/*	if ((YesBit((*(pGD_Hot_Hand+cHSmWinS)).RCS,(cbManMech))))
	{
	if 	((pGD_TControl_Tepl->FramUpdate[1])&&(abs((char)(pGD_Hot_Tepl->InTeplSens[cSmWinSSens].Value)-(*(pGD_Hot_Hand+cHSmWinS)).Position)>GD.TuneClimate.f_MaxAngle))
		{
			(*(pGD_Hot_Hand+cHSmWinS)).Position=(char)pGD_Hot_Tepl->InTeplSens[cSmWinSSens].Value;
			SetBit((*(pGD_Hot_Hand+cHSmWinS)).RCS,cbResetMech);
		}
		pGD_TControl_Tepl->Kontur[cSmWindowUnW+GD.Hot.PozFluger].DoT=(((*(pGD_Hot_Hand+cHSmWinS)).Position))*10;
	}
	if ((YesBit((*(pGD_Hot_Hand+cHSmWinN)).RCS,(cbManMech))))
	{
		if 	((pGD_TControl_Tepl->FramUpdate[0])&&(abs((char)(pGD_Hot_Tepl->InTeplSens[cSmWinNSens].Value)-(*(pGD_Hot_Hand+cHSmWinN)).Position)>GD.TuneClimate.f_MaxAngle))
		{
			(*(pGD_Hot_Hand+cHSmWinN)).Position=(char)pGD_Hot_Tepl->InTeplSens[cSmWinNSens].Value;
			SetBit((*(pGD_Hot_Hand+cHSmWinN)).RCS,cbResetMech);
		}
		pGD_TControl_Tepl->Kontur[cSmWindowUnW+1-GD.Hot.PozFluger].DoT=(((*(pGD_Hot_Hand+cHSmWinN)).Position))*10;
	}
*/
}

//!!!Оптимизация
void ClearAllAlarms(void)
{
	char fnAlr;
	char fnTepl;
	for (fnTepl=0;fnTepl<cSTepl;fnTepl++)
		for (fnAlr=0;fnAlr<cSRegCtrl;fnAlr++)
		{
			ClrBit(GD.TControl.Tepl[fnTepl].MechBusy[fnAlr].RCS,cMSAlarm);
			GD.TControl.Tepl[fnTepl].MechBusy[fnAlr].TryMove=0;
			GD.TControl.Tepl[fnTepl].MechBusy[fnAlr].TryMes=0;
		}
		for (fnAlr=0;fnAlr<MAX_ALARMS;fnAlr++)
			GD.TControl.Tepl[fnTepl].Alarms[fnAlr];
}

void SetAlarm(void)
{
	char fnTepl;
	for (fnTepl=0;fnTepl<GD.Control.ConfSTepl;fnTepl++)
	  __SetBitOutReg(fnTepl,cHSmAlarm,1,0);
	for (fnTepl=0;fnTepl<GD.Control.ConfSTepl;fnTepl++)
	{
		SetPointersOnTepl(fnTepl);	
		pGD_TControl_Tepl->bAlarm=0;
		if ((YesBit(pGD_Hot_Tepl->RCS,(cbNoTaskForTepl+cbNoSensingTemp+cbNoSensingOutT)))
			//||(YesBit(pGD_Hot_Tepl->InTeplSens[cSmTSens].RCS,(cbUpAlarmSens+cbDownAlarmSens+cbMinMaxVSens)))
			||(YesBit(pGD_Hot_Tepl->InTeplSens[cSmWaterSens].RCS,(cbUpAlarmSens+cbDownAlarmSens+cbMinMaxVSens))))
		{
			__SetBitOutReg(fnTepl,cHSmAlarm,0,0);
			pGD_TControl_Tepl->bAlarm=100;
		}
		if (getTempHeatAlarm(fnTepl) == 0)
		{
			__SetBitOutReg(fnTepl,cHSmAlarm,0,0);
			pGD_TControl_Tepl->bAlarm=100;
		}

		if (getTempVentAlarm(fnTepl) == 0)
		{
			__SetBitOutReg(fnTepl,cHSmAlarm,0,0);
			pGD_TControl_Tepl->bAlarm=100;
		}

		for(ByteX=0;ByteX<cConfSSens;ByteX++)
		{
			if (YesBit(pGD_Hot_Tepl->InTeplSens[ByteX].RCS,(cbUpAlarmSens+cbDownAlarmSens+cbMinMaxVSens)))
			{
				__SetBitOutReg(fnTepl,cHSmAlarm,0,0);
				pGD_TControl_Tepl->bAlarm=100;
			}
		}
	}
	for(ByteX=0;ByteX<cConfSMetSens;ByteX++)
		if (YesBit(GD.Hot.MeteoSensing[ByteX].RCS,(cbUpAlarmSens+cbDownAlarmSens+cbMinMaxVSens)))
		{
			__SetBitOutReg(cSmZone1,cHSmAlarm,0,0);
			GD.TControl.Tepl[cSmZone1].bAlarm=100;
		}

}

void SetDiskr(char fnTepl)
{
	int	nLight;
	char tMaxLight;
/*
	if (!(YesBit((*(pGD_Hot_Hand+cHSmAHUSpeed1)).RCS,cbManMech)))
		(*(pGD_Hot_Hand+cHSmAHUSpeed1)).Position=(*pGD_Hot_Tepl).Kontur[cSmKontur4].Do/10;
	if (!(YesBit((*(pGD_Hot_Hand+cHSmAHUSpeed2)).RCS,cbManMech)))
		(*(pGD_Hot_Hand+cHSmAHUSpeed2)).Position=(*pGD_Hot_Tepl).Kontur[cSmKontur4].Do/10;
*/
	ByteY=0;
	for (ByteX=0;ByteX<5;ByteX++)
	{
		if (YesBit(((*(pGD_Hot_Hand+cHSmAHUPad)).Position),(0x02<<ByteX)))
		{
			ByteY++;
			__SetBitOutReg(fnTepl,cHSmAHUPad,0,ByteX);
		}
	}
	if (!(YesBit((*(pGD_Hot_Hand+cHSmAHUPump)).RCS,cbManMech)))
	{
		if (ByteY)
			(*(pGD_Hot_Hand+cHSmAHUPump)).Position=1;
		else
			(*(pGD_Hot_Hand+cHSmAHUPump)).Position=0;

	}

	for(ByteX=cHSmPump;ByteX<cHSmRegs;ByteX++)
	{
		if ((ByteX==cHSmSIOVals)||(ByteX==cHSmLight)) continue;
		__SetBitOutReg(fnTepl,ByteX,1,0);
		if (YesBit((*(pGD_Hot_Hand+ByteX)).Position,0x01))
			__SetBitOutReg(fnTepl,ByteX,0,0);
		if (((ByteX==cHSmHeat)||(ByteX==cHSmVent))&&(YesBit((*(pGD_Hot_Hand+ByteX)).Position,0x02)))
			__SetBitOutReg(fnTepl,ByteX,0,1);
	}




	nLight=0;
	if (((uchar)((*(pGD_Hot_Hand+cHSmLight)).Position))>100) (*(pGD_Hot_Hand+cHSmLight)).Position=100;
	if ((pGD_Hot_Tepl->AllTask.DoTHeat)||(YesBit((*(pGD_Hot_Hand+cHSmLight)).RCS,cbManMech)))
	{
		nLight=(*(pGD_Hot_Hand+cHSmLight)).Position;
		nLight=(nLight-50)/10+2;
		if (nLight<1) nLight=1;
	}
	fLightOn=0;
	if (nLight>1)
	{
		__SetBitOutReg(fnTepl,cHSmLight,0,0);
		fLightOn=1;
	}
	tMaxLight=8;

	switch(pGD_Control_Tepl->sLight)
	{
		case 2:
			if (nLight==7) nLight=0x04;
			else
				if (nLight>1) nLight=0x02;
				else
					if (nLight==1) nLight=0x01;
			break;
		case 1:
			if (nLight==7) nLight=1;
			else nLight=0;
			break;
		case 8:
			if (nLight!=1) nLight=0; 
			break;
		case 6:
			break;
		case 12: case 13: case 14: case 15: case 16: case 17: case 18:
			tMaxLight=pGD_Control_Tepl->sLight-10;
			if (fLightPause>cLightDelay*8) fLightPause=cLightDelay*8;
			if (fLightPause<0) fLightPause=0;
			if (fLightOn)
			{
				nLight=~(0xff<<(fLightPause/cLightDelay));
				fLightPause++;
			}
			else
			{
				nLight=~(0xff>>(fLightPause/cLightDelay));
				fLightPause--;
			}

			break;
		default:
			nLight=0;
			break;
	}

	for (ByteX=0;ByteX<tMaxLight;ByteX++)
	{
		if (YesBit(nLight,(0x01<<ByteX)))
			__SetBitOutReg(fnTepl,cHSmLight,0,ByteX+1);

	}



/*	if (YesBit((*(pGD_Hot_Hand+cHSmVent)).Position,0x01))
		__SetBitOutReg(fnTepl,cHSmVent,0,0);
	if (YesBit((*(pGD_Hot_Hand+cHSmHeat)).Position,0x01))
		__SetBitOutReg(fnTepl,cHSmHeat,0,0);*/
ClrDog;
	ByteX=1;
    if (pGD_Control_Tepl->co_model==2) ByteX=2;

	if ((pGD_TControl_Tepl->SetupRegs[0].On)
		&&(pGD_Control_Tepl->co_model))
		__SetBitOutReg(fnTepl,cHSmCO2,0,ByteX);
	for (ByteX=0;ByteX<4;ByteX++)
	{
		IntX=1;
		IntX<<=ByteX;
		if (YesBit((*(pGD_Hot_Hand+cHSmSIOVals)).Position,IntX))
			__SetBitOutReg(fnTepl,cHSmSIOVals,0,ByteX);
	}
#ifdef AGAPOVSKIY_DOUBLE_VALVE
	if (YesBit((*(pGD_Hot_Hand+cHSmSIOVals)).Position,0x02))
		__SetBitOutReg(fnTepl,cHSmAHUPump,0,0);
#endif AGAPOVSKIY_DOUBLE_VALVE
	for (ByteX=0;ByteX<5;ByteX++)
	{
		if (GD.Hot.Regs[ByteX])
			__SetBitOutReg(fnTepl,ByteX+cHSmRegs,0,0);
	}
}

//long count = 0;

void DoMechanics(char fnTepl) 
{
	char fErr;
	int TimeVol = 0;
	ClrDog;
//	if (count <= 50000 * 3)
//	{
//		count++;
//		GD.TControl.Tepl[fnTepl].Systems[cSysUCValve].Keep = 0;
//	}


	for(ByteX=cHSmMixVal;ByteX<cHSmPump;ByteX++)
	{
		SetPointersOnKontur(ByteX);
//		pGD_Hot_Hand_Kontur=pGD_Hot_Hand+ByteX;  // было убрано !!!

		//MBusy=&(pGD_TControl_Tepl->MechBusy[ByteX]);
		MBusy = &GD.TControl.Tepl[fnTepl].MechBusy[ByteX];

		MBusy=&(  pGD_TControl_Tepl->MechBusy[ByteX]);

		if(pGD_Hot_Hand_Kontur->Position>100)
			pGD_Hot_Hand_Kontur->Position=100;
		if(pGD_Hot_Hand_Kontur->Position<0)
			pGD_Hot_Hand_Kontur->Position=0;

		if ((ByteX==cHSmAHUSpeed1))
		{
//			Sound;
			SetOutIPCReg(pGD_Hot_Hand_Kontur->Position,mtRS485,GD.MechConfig[fnTepl].RNum[ByteX],&fErr,&GD.FanBlock[fnTepl][0].FanData[0]);
			continue;
		}
/*		GD.FanBlock[fnTepl][0].FanData[0].ActualSpeed=fnTepl*5;
		GD.FanBlock[fnTepl][0].FanData[1].ActualSpeed=fnTepl*5+1;
		GD.FanBlock[fnTepl][1].FanData[1].ActualSpeed=fnTepl*5+2;
		GD.FanBlock[fnTepl][1].FanData[2].ActualSpeed=fnTepl*5+3;
*/
		if ((ByteX==cHSmAHUSpeed2))
		{
//			Sound;
			SetOutIPCReg(pGD_Hot_Hand_Kontur->Position,mtRS485,GD.MechConfig[fnTepl].RNum[ByteX],&fErr,&GD.FanBlock[fnTepl][1].FanData[0]);
			continue;
		}


		if ((ByteX==cHSmCO2)&&(pGD_Control_Tepl->co_model==1)) continue;

		if (ByteX==cHSmAHUPad) continue;

		__SetBitOutReg(fnTepl,ByteX,1,0);
		__SetBitOutReg(fnTepl,ByteX,1,1);

		ClrBit(MBusy->RCS,cMSBusyMech);
		ByteY=0;
		if ((!YesBit(MBusy->RCS,cMSAlarm))&&(MBusy->Sens)&&(!YesBit(MBusy->Sens->RCS,cbNoWorkSens))&&(GD.TuneClimate.f_MaxAngle))   // TuneClimate.f_MaxAngle - о
		{
			MBusy->PauseMech=10;
			if (YesBit(MBusy->RCS,cMSFreshSens))
			{
				MBusy->PauseMech=0;
				ClrBit(MBusy->RCS,cMSFreshSens);
//				if ((MBusy->PrevDelta>10)&&(MBusy->Sens->Value-MBusy->PrevTask>10))
//					MBusy->CalcTime=(((long)MBusy->CalcTime)*MBusy->PrevDelta/(MBusy->Sens->Value-MBusy->PrevTask));
				//(MBusy->PrevPosition-MBusy->CurrPosition)
				if 	(MBusy->TryMove>4)
				{
					SetBit(MBusy->RCS,cMSAlarm);
					continue;
				}
				if (MBusy->PrevTask==pGD_Hot_Hand_Kontur->Position*10)
				{
					IntY=GD.TuneClimate.f_MaxAngle*10;
					ogrMax(&IntY,50);
					ogrMin(&IntY,10);
					if (abs(MBusy->Sens->Value-MBusy->PrevTask)>IntY)
					{
							MBusy->TryMes++;
							if (MBusy->TryMes>4)
							{
								MBusy->TryMes=0;
								MBusy->TryMove+=(abs(MBusy->Sens->Value-MBusy->PrevTask)/IntY);
							}
							else continue;
					}


					LngX=MBusy->Sens->Value;
					LngX*=pGD_ConstMechanic_Mech->v_TimeMixVal;//MBusy->CalcTime;
					LngX/=1000;

					if (abs(MBusy->Sens->Value-MBusy->PrevTask)<=IntY)
					{
						MBusy->TryMove=0;
						if (MBusy->PrevDelta>10)
						{
							MBusy->TimeRealMech++;
						}
						if (MBusy->PrevDelta<-10)
						{
							MBusy->TimeRealMech--;
						}
					}
					else
					{
						MBusy->TimeRealMech=(int)LngX;
					}
				}
				MBusy->PrevTask=pGD_Hot_Hand_Kontur->Position*10;
			}
			//else return;
		}
//Выход из паузы при блокировке на крайних положениях
		if(YesBit(MBusy->RCS,cMSBlockRegs)
			&&((pGD_Hot_Hand_Kontur->Position>0)||(MBusy->TimeSetMech>0))
			&&((pGD_Hot_Hand_Kontur->Position<100)||(MBusy->TimeSetMech<pGD_ConstMechanic_Mech->v_TimeMixVal)))
		{
			ClrBit(MBusy->RCS,cMSBlockRegs);
			MBusy->TimeRealMech=MBusy->TimeSetMech;
			ByteY++;			
		}
//Расчет

		if((!MBusy->PauseMech)||(YesBit(pGD_Hot_Hand_Kontur->RCS,cbManMech)))
			{
			LngX=pGD_Hot_Hand_Kontur->Position;
			LngX*=pGD_ConstMechanic_Mech->v_TimeMixVal;
			LngX/=100;
			MBusy->TimeSetMech=(int)(LngX);
/*			if (YesBit(pGD_Hot_Hand_Kontur->RCS,cbResetMech))
			{	
				MBusy->TimeRealMech=MBusy->TimeSetMech;
				ClrBit(pGD_Hot_Hand_Kontur->RCS,cbResetMech);
				ByteY++;
			}*/
			if (!YesBit(pGD_Hot_Hand_Kontur->RCS,cbManMech))
				{
				if (!pGD_Hot_Hand_Kontur->Position)
					{
					SetBit(MBusy->RCS,cMSBlockRegs);

					TimeVol = pGD_ConstMechanic_Mech->v_TimeMixVal/4;
					if (MBusy->TimeRealMech + TimeVol <= pGD_ConstMechanic_Mech->v_TimeMixVal)
						MBusy->TimeRealMech+=TimeVol;
					//MBusy->TimeRealMech+=pGD_ConstMechanic_Mech->v_TimeMixVal/4;
					}
				if (pGD_Hot_Hand_Kontur->Position==100)
					{
					SetBit(MBusy->RCS,cMSBlockRegs);

					TimeVol = pGD_ConstMechanic_Mech->v_TimeMixVal/4;
					if (MBusy->TimeRealMech - TimeVol > 0)
						MBusy->TimeRealMech-=TimeVol;
					//MBusy->TimeRealMech-=pGD_ConstMechanic_Mech->v_TimeMixVal/4;

					}
				}
			}
		//if (MBusy->TimeRealMech > MBusy->TimeSetMech)
		//	MBusy->TimeRealMech = MBusy->TimeSetMech;
		if (MBusy->TimeSetMech>MBusy->TimeRealMech)
			{
			if (MBusy->TimeRealMech < MBusy->TimeSetMech)
				MBusy->TimeRealMech++; else
				MBusy->TimeRealMech = MBusy->TimeSetMech;
			__SetBitOutReg(fnTepl,ByteX,0,1);
			SetBit(MBusy->RCS,cMSBusyMech);
			//SetBit(pGD_Hot_Hand_Kontur->RCS,cbBusyMech);
			ByteY++;
			}
		if (MBusy->TimeSetMech<MBusy->TimeRealMech)
			{
			if (MBusy->TimeRealMech > 0)
				MBusy->TimeRealMech--;
			__SetBitOutReg(fnTepl,ByteX,0,0);
			SetBit(MBusy->RCS,cMSBusyMech);
			//SetBit(pGD_Hot_Hand_Kontur->RCS,cbBusyMech);
			ByteY++;
			}
		if(ByteY) 
			{
			IntY=(int)pGD_ConstMechanic_Mech->v_MinTim;
/*			if ((ByteX==cHSmWinN)||(ByteX==cHSmWinS))
			{
				ogrMin(&IntY,90);
				pGD_TControl_Tepl->FramUpdate[ByteX-cHSmWinN]=0;
			}*/
			ogrMin(&IntY,5);
			MBusy->PauseMech=IntY;			
			if(YesBit(MBusy->RCS,cMSBlockRegs))
				MBusy->PauseMech=150;
			}
	//	if (GD.Hot.Hand) continue;
		if(MBusy->PauseMech) 
		{
			MBusy->PauseMech--;
//			if (!(YesBit(MBusy->RCS,cMSBlockRegs)))
//				SetBit(pGD_Hot_Hand_Kontur->RCS,cbBusyMech);

		}
		ogrMin(&(MBusy->PauseMech),0);// MBusy->PauseMech=0;
		
	}
}

void SetMeteo(void)
{
	uint16_t tMes,i;
	for (i=0;i<cConfSMetSens;i++)
	{
		tMes=GD.Hot.MeteoSensing[i].Value;
		if (((tMes<=GD.TControl.MeteoSensing[i]+NameSensConfig[cConfSSens+i].DigitMidl)&&(tMes>=GD.TControl.MeteoSensing[i]-NameSensConfig[cConfSSens+i].DigitMidl))||(GD.TControl.TimeMeteoSensing[i]>20))
		{
			GD.TControl.TimeMeteoSensing[i]=0;
			GD.TControl.MeteoSensing[i]=tMes;
		}
		else if (GD.TControl.TimeMeteoSensing[i]<30) GD.TControl.TimeMeteoSensing[i]++;
	}
	if (GD.TControl.Tepl[0].SnowTime>=GD.TuneClimate.MinRainTime)
			GD.TControl.bSnow=!GD.TControl.bSnow;
	if (((GD.TControl.MeteoSensing[cSmRainSens]<cMinRain)&&(GD.TControl.bSnow))
		||((GD.TControl.MeteoSensing[cSmRainSens]>cMinRain)&&(!GD.TControl.bSnow)))
	{
		GD.TControl.Tepl[0].SnowTime++;
//		GD.TControl.Tepl[0].SnowTime=10;
	}
	else
		GD.TControl.Tepl[0].SnowTime=0;

	if  ((GD.TControl.MeteoSensing[cSmOutTSens]<c_SnowIfOut)&&(GD.TControl.bSnow))
			SetBit(GD.TControl.bSnow,0x02);
	GD.TControl.Tepl[0].SumSens+=GD.TControl.MeteoSensing[cSmFARSens];//GD.Hot.MeteoSens[cSmFARSens].Value;
	GD.TControl.Tepl[0].TimeSumSens++;
	if (GD.TControl.Tepl[0].TimeSumSens>=15)
	{
		GD.TControl.Tepl[0].SensHourAgo=GD.TControl.Tepl[0].SensHalfHourAgo;
		GD.TControl.Tepl[0].SensHalfHourAgo=GD.TControl.Tepl[0].SumSens/GD.TControl.Tepl[0].TimeSumSens;
		GD.TControl.Tepl[0].SumSens=0;
		GD.TControl.Tepl[0].TimeSumSens=0;
	}
}
void SetLighting(void)
{
	char bZad;
	if (!(pGD_MechConfig->RNum[cHSmLight])) return;

	IntZ=0;

//Pause for light switch on/off
	pGD_TControl_Tepl->LightPauseMode--;
	if ((pGD_TControl_Tepl->LightPauseMode<0)||(pGD_TControl_Tepl->LightPauseMode>GD.TuneClimate.l_PauseMode))
		pGD_TControl_Tepl->LightPauseMode=0;

	ClrDog;
	bZad=0;
	if (pGD_TControl_Tepl->LightPauseMode) bZad=1;

	if ((pGD_Hot_Tepl->AllTask.ModeLight<2))//&&(!bZad))
	{ 		
		pGD_TControl_Tepl->LightMode=pGD_Hot_Tepl->AllTask.ModeLight*pGD_Hot_Tepl->AllTask.Light;
		bZad=1;
	}		

	if (!bZad)
	{
		if (GD.Hot.Zax-60>GD.Hot.Time) pGD_TControl_Tepl->LightMode=0;
		if (GD.TControl.Tepl[0].SensHalfHourAgo<GD.TuneClimate.l_SunOn50)
		{
			IntY=GD.Hot.MidlSR;
			CorrectionRule(GD.TuneClimate.l_SunOn100,GD.TuneClimate.l_SunOn50,50,0);
			pGD_TControl_Tepl->LightMode=100-IntZ;
		}

	}
	if (pGD_TControl_Tepl->LightMode!=pGD_TControl_Tepl->OldLightMode)	
	{
		if (!(((int)pGD_TControl_Tepl->LightMode)*((int)pGD_TControl_Tepl->OldLightMode)))
		{
			pGD_TControl_Tepl->DifLightMode=pGD_TControl_Tepl->LightMode-pGD_TControl_Tepl->OldLightMode;
			pGD_TControl_Tepl->LightPauseMode=GD.TuneClimate.l_PauseMode;
//			pGD_TControl_Tepl->LightExtraPause=o_DeltaTime;
		}
		else
		{
			pGD_TControl_Tepl->LightPauseMode=GD.TuneClimate.l_SoftPauseMode;
		}
	}
	pGD_TControl_Tepl->OldLightMode=pGD_TControl_Tepl->LightMode;
	
//	pGD_TControl_Tepl->LightExtraPause--;
//	if (pGD_TControl_Tepl->LightExtraPause>0) return; 
//	pGD_TControl_Tepl->LightExtraPause=0;	 
	pGD_TControl_Tepl->LightValue=pGD_TControl_Tepl->LightMode;		

}

void SetTepl(char fnTepl)
{
/***********************************************************************
--------------Вычисление изменения показаний датчика температуры-------
************************************************************************/

/***********************************************************************/
	if(!(*pGD_Hot_Tepl).AllTask.NextTAir)
		SetBit((*pGD_Hot_Tepl).RCS,cbNoTaskForTepl);
	if(!getTempHeat(fnTepl))
		SetBit((*pGD_Hot_Tepl).RCS,cbNoSensingTemp);
//	if(!(*pGD_Hot_Tepl).RCS)
	{	
		AllTaskAndCorrection();
		LaunchCalorifer();

		__cNextTCalc(fnTepl);

		DecPumpPause();
		SetUpSiod(fnTepl);
		InitScreen(cTermHorzScr,fnTepl);
		InitScreen(cSunHorzScr,fnTepl);
		InitScreen(cTermVertScr1,fnTepl);
		SetReg(cHSmCO2,
			pGD_Hot_Tepl->AllTask.DoCO2,pGD_Hot_Tepl->InTeplSens[cSmCOSens].Value);

		pGD_Hot_Tepl->OtherCalc.MeasDifPress=GD.TControl.MeteoSensing[cSmPresureSens]-GD.TControl.MeteoSensing[cSmPresureSens+1];
		if (!pGD_Hot_Tepl->OtherCalc.MeasDifPress) pGD_Hot_Tepl->OtherCalc.MeasDifPress=1;
		if ((!GD.TControl.MeteoSensing[cSmPresureSens])||(!GD.TControl.MeteoSensing[cSmPresureSens+1]))
			pGD_Hot_Tepl->OtherCalc.MeasDifPress=0;
//		SetReg(cHSmPressReg,
//			pGD_Hot_Tepl->AllTask.DoPressure,pGD_Hot_Tepl->OtherCalc.MeasDifPress);

		LaunchVent();

		SetLighting();
	}
}
//Есть место для оптимизации!!!!!!!!!!!!!!!!!!!!
void SubConfig(char fnTepl)
{
	SetPointersOnTepl(fnTepl);
	for (ByteX=0;ByteX<cHSmPump;ByteX++)
	{
		SetPointersOnKontur(ByteX);
		if  (ByteX<cSKontur)
		{
			pGD_TControl_Tepl_Kontur->Separate=CheckSeparate(ByteX);
			pGD_TControl_Tepl_Kontur->MainTepl=CheckMain(fnTepl);
			
			pGD_Hot_Hand_Kontur->RCS=
				GD.Hot.Tepl[pGD_TControl_Tepl_Kontur->MainTepl].HandCtrl[ByteX].RCS;
			pGD_Hot_Hand_Kontur->Position=
				GD.Hot.Tepl[pGD_TControl_Tepl_Kontur->MainTepl].HandCtrl[ByteX].Position;
			if (ByteX<cSWaterKontur)
			{
				ByteY=ByteX+cHSmPump;
				pGD_TControl_Tepl_Kontur->SensValue=pGD_Hot_Tepl->InTeplSens[ByteX+cSmWaterSens].Value;
				pGD_Hot_Hand[ByteY].RCS=
					GD.Hot.Tepl[pGD_TControl_Tepl_Kontur->MainTepl].HandCtrl[ByteY].RCS;
				pGD_Hot_Hand[ByteY].Position=
					GD.Hot.Tepl[pGD_TControl_Tepl_Kontur->MainTepl].HandCtrl[ByteY].Position;
				pGD_TControl_Tepl_Kontur->SensValue=
					GD.TControl.Tepl[pGD_TControl_Tepl_Kontur->MainTepl].Kontur[ByteX].SensValue;
			}
		}

	}

}
void Configuration(void)
{
	char tTepl;
	for (tTepl=0;tTepl<cSTepl;tTepl++)
		SubConfig(tTepl);
}
#ifdef Vitebsk
void	TransferWaterToBoil(void)
{
	IntX=GD.Hot.MaxReqWater/100; //Делаем запас на 5 градусов
//	IntX=IntX/100;
	IntX++;
//	IntY=0;
	switch(IntX)
	{
		case 0:
		case 1:
		case 2:
		case 3: IntY=1; break;
		case 4:
		case 5:
		case 6: IntY=IntX-2; break;
		case 7: IntY=0; break;
		case 8:
		case 9:
		case 10: IntY=IntX-3; break;
		default: IntY=7;
	}

	if (YesBit(IntY,0x01))
	__SetBitOutReg(0,cHSmRegs+4,0,0);
	if (YesBit(IntY,0x02))
	__SetBitOutReg(0,cHSmRegs+4,0,1);
	if (YesBit(IntY,0x04))
	__SetBitOutReg(0,cHSmRegs+4,0,2);
//	GD.Hot.Demon=IntY;

}
#endif
/*------------------------------------------------
        Управлюща программа
        Вариант "Ромашка"
        Создана от 14.04.04
--------------------------------------------------*/

void Control(void) 
	{
char tCTepl,ttTepl;
	Configuration();
	SetDiskrSens();
	if (DemoMode!=9)
		DemoMode=0;
	if (!DemoMode)
	{
		ClrAllOutIPCDigit();
		OutR[0]=0;
		OutR[1]=0;
		OutR[2]=0;
		OutR[3]=0;
		OutR[4]=0;
		OutR[5]=0;
		OutR[6]=0;
		OutR[7]=0;
		OutR[8]=0;
		OutR[9]=0;
		OutR[10]=0;
		SetAlarm();
		for (tCTepl=0;tCTepl<cSTepl;tCTepl++)
		{
			SetPointersOnTepl(tCTepl);
			SetSensOnMech();
			DoMechanics(tCTepl);
			SetDiskr(tCTepl);
			DoSiod();
			DoPumps();
//			CheckReadyMeasure();
			DoVentCalorifer();
			DoLights();
//			DoPoisen();
			RegWorkDiskr(cHSmCO2);
//			RegWorkDiskr(cHSmPressReg);
#ifdef Vitebsk
			TransferWaterToBoil();
#endif
		}
		ResumeOutIPCDigit();
		
	}
//	if (Second==12)
//	{
		//CLREA;
//		while(1);
//	}
//		GD.Cal.InTeplSens[0][0].U0=0;
	if ((!Menu)&&(ProgReset))
	{
		ProgReset=0;
		TestMem(2);
	}

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
/*--------------------------------------------------------
если минута */

		for (tCTepl=0;tCTepl<cSTepl;tCTepl++)
		{
			SetPointersOnTepl(tCTepl);
			SetMixValvePosition();
		}
		if (Second==20)
		{
	        InitLCD();
//	        GD.Control.ConfSTepl=10;
    	    ClrDog;
			SetMeteo();
		}
		if ((Second==40)||(GD.TControl.Delay))
		{
			if (GD.SostRS==WORK_UNIT)
			{
			   GD.TControl.Delay=1;
			}
			else
			{
			    PORTNUM=0;
				vNFCtr=0;
				CheckMidlSr();
				GD.TControl.Delay=0;
				for (tCTepl=0;tCTepl<cSTepl;tCTepl++)
				{
					MemClr(&GD.Hot.Tepl[tCTepl].ExtRCS,(
						sizeof(char)*2+sizeof(eClimTask)+sizeof(eOtherCalc)+
						sizeof(eNextTCalc)+sizeof(eKontur)*cSKontur+20));
					IntZ=((GD.Hot.Time+o_DeltaTime)%(24*60));
					TaskTimer(1,tCTepl,tCTepl);
					ttTepl=tCTepl;
					while ((!GD.Hot.Tepl[tCTepl].AllTask.NextTAir)&&(ttTepl))
					{
						TaskTimer(1,--ttTepl,tCTepl);
					}
					IntZ=GD.Hot.Time;
					ClrDog;
					TaskTimer(0,ttTepl,tCTepl);
					SetPointersOnTepl(tCTepl);
					SetTepl(tCTepl);
				}
//------------------------------------------------
				__sCalcKonturs();
				__sMechWindows();
				__sMechScreen();
				for (tCTepl=0;tCTepl<cSTepl;tCTepl++)
				{
					if (GD.Hot.MaxReqWater<GD.Hot.Tepl[tCTepl].MaxReqWater)
						GD.Hot.MaxReqWater=GD.Hot.Tepl[tCTepl].MaxReqWater;
					bWaterReset[tCTepl]=0;
//					GD.TControl.Tepl[tCTepl].Sensor[0].SumD=0;
//					GD.TControl.Tepl[tCTepl].Sensor[0].SumD=0;
				}
			}
		}
    vNFCtr=GD.Control.NFCtr;
    PORTNUM=DEF_PORTNUM;
//	ToHiTime=GD.Control.Read1W;
//	ToLowTime=GD.Control.Write1W;
  	MaskRas=bRasxod;

  	if (TecPerRas > 2305) {
        TecPerRas=2305;
        GD.TControl.NowRasx=0;
        }
   	else {
        IntX=PastPerRas;
        if (TecPerRas>IntX) IntX=TecPerRas;
		GD.TControl.NowRasx=(long)GD.TuneClimate.ScaleRasx*(long)23040/(long)IntX/100;
        }
	GD.TControl.FullVol+=Volume;
	if ((!GD.TControl.MeteoSensing[cSmMainTSens])||(!GD.TControl.MeteoSensing[cSmMainTSens+1]))
	{
		GD.Hot.HeatPower=(int)(((long)GD.TControl.NowRasx)*(GD.TControl.MeteoSensing[cSmMainTSens]-GD.TControl.MeteoSensing[cSmMainTSens+1])/100);
		GD.Hot.FullHeat=(int)((GD.TControl.FullVol*GD.TuneClimate.ScaleRasx/100)*(GD.TControl.MeteoSensing[cSmMainTSens]-GD.TControl.MeteoSensing[cSmMainTSens+1])/1000);
	}	
	Volume=0;
	if( Second < 60) return;

	WriteToFRAM();
	MidlWindAndSr();
	WindDirect();
//	ReadFromFRAM();
	//while(1);
/*    if(GD.TControl.tCodTime) GD.TControl.tCodTime--; else {
		GD.TControl.NowCod=0;
#ifdef SumExtCG
		SendFirstScreen(GD.Control.Screener);
#endif
	}
*/
#ifndef NOTESTMEM
	if ((!Menu)&&(GD.SostRS==OUT_UNIT))
		TestMem(1);
#endif
	
	ClrDog;
	Second=0;
//	w1_test();
//	ds18b20_ConvertTemp();

	if(TimeReset)
		TimeReset--;
	if(TimeReset<0)
		TimeReset=1;
	GD.Hot.Time++;
	GetRTC();
	not=220;ton=10;
/*	if ((bNight)&&(GD.Hot.Time>=GD.Hot.Vosx)&&(GD.Hot.Time<GD.Hot.Zax))
	{
		MemClr(&GD.TControl.Tepl[cSmTeplA].MidlSensDN,12);
	}
*/	bNight=1;
	if ((GD.Hot.Time>=GD.Hot.Vosx)&&(GD.Hot.Time<GD.Hot.Zax))
		bNight=0;
/*	if((GD.Arx[0].Date!=GD.Hot.Data)&&(GD.Hot.Time>GD.Hot.Vosx)) 
		{
		
//		SdvArx();
//		GD.Arx[0].Date=GD.Hot.Data;

		}
*/
	if(GD.Hot.Time>=24*60)      /*новые сутки*/
		{
		GD.Hot.Time=0;
		GD.Hot.Data++;
		ByteX=GD.Hot.Data/256;  /* это месц */
		if (ByteX<=0) {ByteX=1;GD.Hot.Data=1;}
		if ((GD.Hot.Data%256)>Mon[ByteX-1]) 
			{
			if((++ByteX)>12) 
				{
				GD.Hot.Year++;
				ByteX=1;
				}
			GD.Hot.Data=(int)ByteX*256+1;
			}
		}
	if(GD.TControl.Data!=GD.Hot.Data)      /*новые сутки*/
	{
		for (tCTepl=0;tCTepl<cSTepl;tCTepl++)
		{
//			GD.TControl.Tepl[tCTepl].Functional=1;
			GD.TControl.Tepl[tCTepl].TimeSIO=0;
		}
		GD.TControl.SumSun=0;
		GD.TControl.Data=GD.Hot.Data;
		GD.TControl.FullVol=0;
	}
}
