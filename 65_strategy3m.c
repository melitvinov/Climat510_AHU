/**************************************************************************/
/*-*-*-*-*-*-*--Процедура установки границ для водных контуров--*-*-*-*-*-*/
/**************************************************************************/
int DefRH(char fnTepl)
{
	// изменеие 100. RH выводим как Theat
	//if ((!(*pGD_Hot_Tepl).AllTask.DoRHAir)||(!(*pGD_Hot_Tepl).InTeplSens[cSmRHSens].Value)) return 0;
	//return ((*pGD_Hot_Tepl).InTeplSens[cSmRHSens].Value-(*pGD_Hot_Tepl).AllTask.DoRHAir);
	if ((!(*pGD_Hot_Tepl).AllTask.DoRHAir)||(!(*pGD_Hot_Tepl).InTeplSens[cSmRHSens].Value)) return 0;
	return ((*pGD_Hot_Tepl).InTeplSens[cSmRHSens].Value-(*pGD_Hot_Tepl).AllTask.DoRHAir);

}

int DefOutAbsHum(void)
{
	if ((!GD.TControl.MeteoSensing[cSmOutTSens])||(!GD.TControl.MeteoSensing[cSmOutRHSens])) return 0;
	return AbsHum(GD.TControl.MeteoSensing[cSmOutTSens],GD.TControl.MeteoSensing[cSmOutRHSens]);
}

int DefAbsHum(void)
{
	if ((!pGD_Hot_Tepl->AllTask.DoRHAir)||(!pGD_Hot_Tepl->AllTask.DoTVent)) return 0;
	return AbsHum(pGD_Hot_Tepl->AllTask.DoTVent,pGD_Hot_Tepl->AllTask.DoRHAir);
}

int DefAbsHumSensor(int16_t sensorRH)
{
	if ((!pGD_Hot_Tepl->AllTask.DoRHAir)||(!pGD_Hot_Tepl->AllTask.DoTVent)) return 0;
	return AbsHum(pGD_Hot_Tepl->AllTask.DoTVent,sensorRH);
}

void SetNoWorkKontur(void)
{
	SetBit((*pGD_Hot_Tepl_Kontur).RCS,cbNoWorkKontur);
	(*pGD_TControl_Tepl_Kontur).PumpStatus=0;
	(*pGD_TControl_Tepl_Kontur).DoT=0;
}

void __sMinMaxWater(char fnKontur)
{	
//------------------------------------------------------------------------			
//Заполняем минимальные и максимальные границы для контуров а также опт температуру
//------------------------------------------------------------------------
	pGD_Hot_Tepl_Kontur->MaxCalc=pGD_Control_Tepl->c_MaxTPipe[fnKontur];	
//------------------------------------------------------------------------
//Для контуров начиная с третьего берем минимальные границы и опт. темп. из параметров
//------------------------------------------------------------------------

	//	if  ((GD.Hot.MidlSR<GD.TuneClimate.f_MinSun)&&(pGD_Hot_Tepl->AllTask.NextTAir-GD.TControl.OutTemp>GD.TuneClimate.f_DeltaOut))
//		SetBit(pGD_Hot_Tepl->Kontur[cSmKontur1].ExtRCS,cbBlockPumpKontur);

	if (fnKontur==cSmKontur4)
	{
		pGD_Hot_Tepl_Kontur->MinTask=pGD_Control_Tepl->c_MinTPipe[1];
		pGD_Hot_Tepl_Kontur->Optimal=pGD_Control_Tepl->c_OptimalTPipe[1];
		pGD_Hot_Tepl_Kontur->MinCalc=pGD_Hot_Tepl_Kontur->MinTask;
	}
//------------------------------------------------------------------------
//Если установлен минимум то насос должен быть всегда включен
//------------------------------------------------------------------------
	if(((*pGD_Hot_Tepl_Kontur).MinTask)||(YesBit((*(pGD_Hot_Hand_Kontur+cHSmPump)).RCS,cbManMech)))
		SetBit((*pGD_Hot_Tepl_Kontur).ExtRCS,cbBlockPumpKontur);					
//------------------------------------------------------------------------
//Ограничиваем минимум 
//------------------------------------------------------------------------
	ogrMin(&((*pGD_Hot_Tepl_Kontur).MinCalc),cMinAllKontur);		
//------------------------------------------------------------------------
//В виду особенностей работы 5 контура для него отдельные установки
//------------------------------------------------------------------------
	if ((*pGD_Hot_Tepl_Kontur).MinCalc>(*pGD_Hot_Tepl_Kontur).MaxCalc)
	{
		(*pGD_Hot_Tepl_Kontur).MinCalc=(*pGD_Hot_Tepl_Kontur).MaxCalc;
	}
	if(fnKontur==cSmKontur5)
	{

		if ((!(YesBit(pGD_Hot_Tepl->InTeplSens[cSmGlassSens].RCS,cbMinMaxVSens)))
			&&((pGD_Hot_Tepl->InTeplSens[cSmGlassSens].Value<GD.TuneClimate.c_DoMinIfGlass)))
		{
			IntY=pGD_Hot_Tepl->InTeplSens[cSmGlassSens].Value;
			CorrectionRule(GD.TuneClimate.c_DoMaxIfGlass,GD.TuneClimate.c_DoMinIfGlass,
				pGD_Hot_Tepl_Kontur->MaxCalc-cMin5Kontur,0);
			pGD_Hot_Tepl_Kontur->Do=pGD_Hot_Tepl_Kontur->MaxCalc-IntZ;
			SetBit((*pGD_Hot_Tepl_Kontur).ExtRCS,cbBlockPumpKontur);
							
		}
		if (YesBit(GD.TControl.bSnow,0x02))
		{
			IntY=GD.TControl.MeteoSensing[cSmOutTSens];
			CorrectionRule(GD.TuneClimate.c_CriticalSnowOut,c_SnowIfOut,
				pGD_Hot_Tepl_Kontur->MaxCalc-GD.TuneClimate.c_MinIfSnow,0);
			pGD_Hot_Tepl_Kontur->Do=pGD_Hot_Tepl_Kontur->MaxCalc-IntZ;
			SetBit((*pGD_Hot_Tepl_Kontur).ExtRCS,cbBlockPumpKontur);
		}	

		if ((pGD_TControl_Tepl->ScrExtraHeat)||(GD.Hot.Util==9))
		{
			SetBit((*pGD_Hot_Tepl_Kontur).ExtRCS,cbBlockPumpKontur);
			//pGD_TControl_Tepl_Kontur->DoT=(pGD_Hot_Tepl_Kontur->MaxCalc*10);
			pGD_Hot_Tepl_Kontur->Do=pGD_Hot_Tepl_Kontur->MaxCalc;
		}
//		else
//		if  (pGD_TControl_Tepl->LastScrExtraHeat)
//			pGD_TControl_Tepl_Kontur->DoT=pGD_TControl_Tepl->TempStart5;
						
//		pGD_TControl_Tepl->LastScrExtraHeat=pGD_TControl_Tepl->ScrExtraHeat;

		//ogrMin(&((*pGD_Hot_Tepl_Kontur).MinCalc),cMin5Kontur);
		ogrMin(&(pGD_Hot_Tepl_Kontur->Do),(*pGD_Hot_Tepl_Kontur).MinCalc);
		if (!YesBit((*pGD_Hot_Tepl_Kontur).ExtRCS,cbBlockPumpKontur))
		{
			pGD_Hot_Tepl_Kontur->Do=0;
			pGD_Hot_Tepl_Kontur->MaxCalc=0;
		}

	}
//	else
//	{
//		if (!pGD_Hot_Tepl_Kontur->Optimal)
//			pGD_Hot_Tepl_Kontur->Optimal=pGD_Hot_Tepl_Kontur->MinCalc+(pGD_Hot_Tepl_Kontur->MaxCalc-pGD_Hot_Tepl_Kontur->MinCalc)/2;
//	}
	
}

void CheckInRHSystem(void)
{
	//pGD_ConstMechanic->ConstMixVal[cHSmInRH].v_TimeMixVal;
	pGD_TControl_Tepl->Systems[cSysInRH].Max = pGD_Control_Tepl->InRHMax;
	pGD_TControl_Tepl->Systems[cSysInRH].Min = pGD_Control_Tepl->InRHMin;

	//pGD_TControl_Tepl->Systems[cSysInRH].Max = (pGD_Control_Tepl->InRHMax * pGD_ConstMechanic->ConstMixVal[cHSmInRH].v_TimeMixVal) / 100;
	//pGD_TControl_Tepl->Systems[cSysInRH].Min = (pGD_Control_Tepl->InRHMin * pGD_ConstMechanic->ConstMixVal[cHSmInRH].v_TimeMixVal) / 100;

//Меньше 12 градусов температура на улице - панель не запускать
//	if ((GD.TControl.MeteoSensing[cSmOutTSens]<1200)&&(GD.TControl.MeteoSensing[cSmOutTSens]))
//		pGD_TControl_Tepl->Systems[cSysMist].Max=0;

	pGD_TControl_Tepl->Systems[cSysInRH].RCS=0;
	if ((YesBit(pGD_Hot_Hand[cHSmInRH].RCS,cbManMech))||(!pGD_MechConfig->RNum[cHSmInRH]))
	{
		SetBit(pGD_TControl_Tepl->Systems[cSysInRH].RCS,cSysRHand);
		//pGD_TControl_Tepl->Systems[cSysInRH].Max=0;
	}

	pGD_TControl_Tepl->Systems[cSysInRH].Value = pGD_Hot_Hand[cHSmInRH].Position;

	if (pGD_TControl_Tepl->Systems[cSysInRH].Keep>pGD_TControl_Tepl->Systems[cSysInRH].Max)
		pGD_TControl_Tepl->Systems[cSysInRH].Keep=pGD_TControl_Tepl->Systems[cSysInRH].Max;

	if	(!pGD_TControl_Tepl->Systems[cSysInRH].RCS)
	{
		if (pGD_TControl_Tepl->Systems[cSysInRH].Keep<pGD_TControl_Tepl->Systems[cSysInRH].Max)
			 SetBit(pGD_TControl_Tepl->Systems[cSysInRH].RCS,cSysRUp);
		if (pGD_TControl_Tepl->Systems[cSysInRH].Keep>pGD_TControl_Tepl->Systems[cSysInRH].Min)
			 SetBit(pGD_TControl_Tepl->Systems[cSysInRH].RCS,cSysRDown);
	}
	pGD_TControl_Tepl->Systems[cSysInRH].Power=1000;//pGD_ConstMechanic->ConstMixVal[cHSmAHUPad].v_PFactor; // last
    //pGD_TControl_Tepl->Systems[cSysMist].Power=pGD_ConstMechanic->ConstMixVal[cHSmAHUPad].v_PFactor;
}

//Изменения от 26.04.2015
//Экран. установить минимумы, максимумы, возможность вверх, возможность вниз
void CheckScreenSystem(void)
{
#warning temporary constants later from params
// влияние влажности выключили !
	//pGD_TControl_Tepl->Systems[cSysScreen].Max=GD.TuneClimate.sc_RHMax;
	//if (pGD_TControl_Tepl->Systems[cSysScreen].Max>15)
	//	pGD_TControl_Tepl->Systems[cSysScreen].Max=15;


//	pGD_TControl_Tepl->Systems[cSysScreen].Max=pGD_TControl_Tepl->Screen[0].Value-90;   было убранно

	if (pGD_TControl_Tepl->Systems[cSysScreen].Max<0)
		pGD_TControl_Tepl->Systems[cSysScreen].Max=0;
	pGD_TControl_Tepl->Systems[cSysScreen].Min=0;

	pGD_TControl_Tepl->Systems[cSysScreen].RCS=0;

	pGD_TControl_Tepl->Systems[cSysScreen].Value=pGD_TControl_Tepl->Screen[0].Value;

	if (pGD_TControl_Tepl->Systems[cSysScreen].Keep>pGD_TControl_Tepl->Systems[cSysScreen].Max)
	//if (pGD_TControl_Tepl->Systems[cSysScreen].Keep<pGD_TControl_Tepl->Systems[cSysScreen].Max)
		pGD_TControl_Tepl->Systems[cSysScreen].Keep=pGD_TControl_Tepl->Systems[cSysScreen].Max;

	if	(!pGD_TControl_Tepl->Systems[cSysScreen].RCS)
	{
		if (pGD_TControl_Tepl->Systems[cSysScreen].Keep<pGD_TControl_Tepl->Systems[cSysScreen].Max)
			 SetBit(pGD_TControl_Tepl->Systems[cSysScreen].RCS,cSysRUp);
		if (pGD_TControl_Tepl->Systems[cSysScreen].Keep>pGD_TControl_Tepl->Systems[cSysScreen].Min)
			 SetBit(pGD_TControl_Tepl->Systems[cSysScreen].RCS,cSysRDown);
	}
	pGD_TControl_Tepl->Systems[cSysScreen].Power=1000;
}

//установить минимумы, максимумы, возможность вверх, возможность вниз для контура AHU
void CheckAHUPipeSystem(void)
{
	pGD_TControl_Tepl->Systems[cSysAHUPipe].Max=(*pGD_Hot_Tepl).Kontur[cSmKontur3].MaxCalc;

	pGD_TControl_Tepl->Systems[cSysAHUPipe].Min=(*pGD_Hot_Tepl).Kontur[cSmKontur3].MinCalc;

	pGD_TControl_Tepl->Systems[cSysAHUPipe].RCS=0;
	if ((YesBit(pGD_Hot_Hand[cHSmMixVal+cSmKontur3].RCS,cbManMech))||(!pGD_MechConfig->RNum[cHSmMixVal+cSmKontur3]))
	{
		SetBit(pGD_TControl_Tepl->Systems[cSysAHUPipe].RCS,cSysRHand);
//		pGD_TControl_Tepl->Systems[cSysUCValve].Max=0;
	}
	//pGD_TControl_Tepl->Systems[cSysUCValve].Value=pGD_Hot_Hand[cHSmUCValve].Position;

	if (pGD_TControl_Tepl->Systems[cSysAHUPipe].Keep>pGD_TControl_Tepl->Systems[cSysAHUPipe].Max)
		pGD_TControl_Tepl->Systems[cSysAHUPipe].Keep=pGD_TControl_Tepl->Systems[cSysAHUPipe].Max;

	if	(!pGD_TControl_Tepl->Systems[cSysAHUPipe].RCS)
	{
		if ((pGD_TControl_Tepl->Systems[cSysAHUPipe].Keep<pGD_TControl_Tepl->Systems[cSysAHUPipe].Max)&&(pGD_Hot_Hand[cHSmMixVal+cSmKontur3].Position!=100))
			 SetBit(pGD_TControl_Tepl->Systems[cSysAHUPipe].RCS,cSysRUp);
		if ((pGD_TControl_Tepl->Systems[cSysAHUPipe].Keep>pGD_TControl_Tepl->Systems[cSysAHUPipe].Min)&&(pGD_Hot_Hand[cHSmMixVal+cSmKontur3].Position))
			 SetBit(pGD_TControl_Tepl->Systems[cSysAHUPipe].RCS,cSysRDown);
	}
	pGD_TControl_Tepl->Systems[cSysAHUPipe].Power=-1000; // last
    //pGD_TControl_Tepl->Systems[cSysUCValve].Power=((int32_t)pGD_ConstMechanic->ConstMixVal[cHSmUCValve].v_PFactor)*1000/((long)pGD_TControl_Tepl->f_Power);
}


//установить минимумы, максимумы, возможность вверх, возможность вниз для клапана AHU
void CheckUCValveSystem(int Tmes, int Tset)			// отрабатывает
{
	pGD_TControl_Tepl->Systems[cSysUCValve].Max=(*pGD_Hot_Tepl).Kontur[cSmWindowUnW].MaxCalc;
	// изменение 96 если после коррекции минимума клапана он стал больше чем макс
	//открытия из параметров, то не корректируем
	if ((*pGD_Hot_Tepl).Kontur[cSmWindowUnW].MinCalc > pGD_Control_Tepl->f_MaxOpenUn)
		pGD_TControl_Tepl->Systems[cSysUCValve].Min = pGD_Control_Tepl->f_MaxOpenUn;
	else
		pGD_TControl_Tepl->Systems[cSysUCValve].Min = (*pGD_Hot_Tepl).Kontur[cSmWindowUnW].MinCalc;

	// изменение 98 если заданная температура больше чем измеренная на величину больше либо равную "Нижней аварийной границе" max ставим = 0
	if (Tset - Tmes > GD.TuneClimate.c_MaxDifTDown)
		pGD_TControl_Tepl->Systems[cSysUCValve].Max = 0;

	pGD_TControl_Tepl->Systems[cSysUCValve].RCS=0;
	if ((YesBit(pGD_Hot_Hand[cHSmUCValve].RCS,cbManMech))||(!pGD_MechConfig->RNum[cHSmUCValve]))
	{
		SetBit(pGD_TControl_Tepl->Systems[cSysUCValve].RCS,cSysRHand);
//		pGD_TControl_Tepl->Systems[cSysUCValve].Max=0;
	}
	pGD_TControl_Tepl->Systems[cSysUCValve].Value=pGD_Hot_Hand[cHSmUCValve].Position;

	if (pGD_TControl_Tepl->Systems[cSysUCValve].Keep>pGD_TControl_Tepl->Systems[cSysUCValve].Max)
		pGD_TControl_Tepl->Systems[cSysUCValve].Keep=pGD_TControl_Tepl->Systems[cSysUCValve].Max;

	if	(!pGD_TControl_Tepl->Systems[cSysUCValve].RCS)
	{
		if ((pGD_TControl_Tepl->Systems[cSysUCValve].Keep<pGD_TControl_Tepl->Systems[cSysUCValve].Max)
			&&((pGD_TControl_Tepl->Systems[cSysScreen].Keep>=pGD_TControl_Tepl->Systems[cSysScreen].Max)||(pGD_TControl_Tepl->Systems[cSysUCValve].Keep<10)))
			 SetBit(pGD_TControl_Tepl->Systems[cSysUCValve].RCS,cSysRUp);
		if (pGD_TControl_Tepl->Systems[cSysUCValve].Keep>pGD_TControl_Tepl->Systems[cSysUCValve].Min)
			 SetBit(pGD_TControl_Tepl->Systems[cSysUCValve].RCS,cSysRDown);
	}
	pGD_TControl_Tepl->Systems[cSysUCValve].Power=1000/((long)pGD_TControl_Tepl->f_Power); // last
    //pGD_TControl_Tepl->Systems[cSysUCValve].Power=((int32_t)pGD_ConstMechanic->ConstMixVal[cHSmUCValve].v_PFactor)*1000/((long)pGD_TControl_Tepl->f_Power);
}


// старый выриант
/*
void CheckMistSystem(void)
{
	int16_t	OutAbsH, InAbsH;
	pGD_TControl_Tepl->Systems[cSysMist].Max=30;
//Меньше 12 градусов температура на улице - панель не запускать
	if ((GD.TControl.MeteoSensing[cSmOutTSens]<1200)&&(GD.TControl.MeteoSensing[cSmOutTSens]))
		pGD_TControl_Tepl->Systems[cSysMist].Max=0;

//	OutAbsH=DefOutAbsHum();
//	InAbsH=DefAbsHum();
//	if ((OutAbsH)&&(InAbsH))
//	{
//		if (OutAbsH>InAbsH)
//			pGD_TControl_Tepl->SaveMaxMist--;
//		else
//			pGD_TControl_Tepl->SaveMaxMist++;
//		if (pGD_TControl_Tepl->SaveMaxMist>pGD_TControl_Tepl->Systems[cSysMist].Max)
//			pGD_TControl_Tepl->SaveMaxMist=pGD_TControl_Tepl->Systems[cSysMist].Max;
//		if (pGD_TControl_Tepl->SaveMaxMist<0)
//			pGD_TControl_Tepl->SaveMaxMist=0;
//		pGD_TControl_Tepl->Systems[cSysMist].Max=pGD_TControl_Tepl->SaveMaxMist;
//	}
//	else
//		pGD_TControl_Tepl->SaveMaxMist=pGD_TControl_Tepl->Systems[cSysMist].Max;

	pGD_TControl_Tepl->Systems[cSysMist].Min=0;

	if (pGD_TControl_Tepl->Systems[cSysUCValve].Value<30)
		pGD_TControl_Tepl->Systems[cSysMist].Max=0;

	pGD_TControl_Tepl->Systems[cSysMist].RCS=0;
	if ((YesBit(pGD_Hot_Hand[cHSmAHUPad].RCS,cbManMech))||(!pGD_MechConfig->RNum[cHSmAHUPad]))
	{
		SetBit(pGD_TControl_Tepl->Systems[cSysMist].RCS,cSysRHand);
//		pGD_TControl_Tepl->Systems[cSysMist].Max=0;
	}
	pGD_TControl_Tepl->Systems[cSysMist].Value=pGD_Hot_Hand[cHSmAHUPad].Position;

	if (pGD_TControl_Tepl->Systems[cSysMist].Keep>pGD_TControl_Tepl->Systems[cSysMist].Max)
		pGD_TControl_Tepl->Systems[cSysMist].Keep=pGD_TControl_Tepl->Systems[cSysMist].Max;

	if	(!pGD_TControl_Tepl->Systems[cSysMist].RCS)
	{
		if (pGD_TControl_Tepl->Systems[cSysMist].Keep<pGD_TControl_Tepl->Systems[cSysMist].Max)
			 SetBit(pGD_TControl_Tepl->Systems[cSysMist].RCS,cSysRUp);
		if (pGD_TControl_Tepl->Systems[cSysMist].Keep>pGD_TControl_Tepl->Systems[cSysMist].Min)
			 SetBit(pGD_TControl_Tepl->Systems[cSysMist].RCS,cSysRDown);
	}
	pGD_TControl_Tepl->Systems[cSysMist].Power=1000;//pGD_ConstMechanic->ConstMixVal[cHSmAHUPad].v_PFactor; // last
    //pGD_TControl_Tepl->Systems[cSysMist].Power=pGD_ConstMechanic->ConstMixVal[cHSmAHUPad].v_PFactor;
} */

void CheckMistSystemNew(char fnTepl)
{
	int16_t	OutAbsH, InAbsH;
	//pGD_TControl_Tepl->Systems[cSysMist].Max = 100;//pGD_ConstMechanic->ConstMixVal[cHSmAHUPad].v_TimeMixVal;

	//pGD_TControl_Tepl->Systems[cSysMist].Max = pGD_ConstMechanic->ConstMixVal[cHSmInRH].v_TimeMixVal;
//Меньше 12 градусов температура на улице - панель не запускать
	if ((GD.TControl.MeteoSensing[cSmOutTSens]<1200)&&(GD.TControl.MeteoSensing[cSmOutTSens]))
		pGD_TControl_Tepl->Systems[cSysMist].Max=0;

	// 66 другой расчет
	volatile int16_t vMistMax = pGD_Control_Tepl->MistMax;
	volatile int16_t vMaxCorrAHUrh = GD.TuneClimate.MaxCorrAHUrh*100;
	volatile int16_t vTOutAHU = pGD_Hot_Tepl->InTeplSens[cSmTAHUOutSens].Value;
	volatile int16_t vKeepTAHU = pGD_TControl_Tepl->TVentCritery;
	volatile int16_t vTAHUdelta = 0;
	//volatile int16_t vKeepRH = pGD_Hot_Tepl->AllTask. DoRHAir+500;				// RH теплицы Держать + 5 градус

	// изменеие 100. RH выводим как Theat
	//volatile int16_t vRHtepl = pGD_Hot_Tepl->InTeplSens[cSmRHSens].Value;
	volatile int16_t vRHtepl = getRH(fnTepl);

	// убираем это. Из задания убираем все. А точные настройки сделаем как диапазон работы дефицита водяного пара
	volatile int16_t vKeepRHstart = (*pGD_Hot_Tepl).AllTask.RHAir + (GD.TuneClimate.f_MistRHstart*100);
	volatile int16_t vKeepRHend = (*pGD_Hot_Tepl).AllTask.RHAir + (GD.TuneClimate.f_MistRHend*100);
	volatile int16_t MistRHstop = (*pGD_Hot_Tepl).AllTask.MistRHstop;

	volatile int16_t res;

	pGD_TControl_Tepl->Systems[cSysMist].Max = vMistMax;

	if (vTOutAHU > vKeepTAHU)
	{
		vTAHUdelta = vTOutAHU - vKeepTAHU;
		if (vTAHUdelta >= vMaxCorrAHUrh)
		{
			res = vMistMax;
			if (MistRHstop)
			{
				if ( (vRHtepl > vKeepRHstart)&&(vRHtepl < vKeepRHend) )
				{
					res = ((vRHtepl-vKeepRHstart) * MistRHstop) / (vKeepRHend - vKeepRHstart);
					if (pGD_TControl_Tepl->Systems[cSysMist].Max > res)
						pGD_TControl_Tepl->Systems[cSysMist].Max = pGD_TControl_Tepl->Systems[cSysMist].Max - res;
					else
					{
						pGD_TControl_Tepl->SaveMaxMist--;
						if (pGD_TControl_Tepl->SaveMaxMist < 0)
							pGD_TControl_Tepl->SaveMaxMist = 0;
						pGD_TControl_Tepl->Systems[cSysMist].Max=0;
						res = 0;
					}
				}
				if (vRHtepl >= vKeepRHend)
				{
					if (pGD_TControl_Tepl->Systems[cSysMist].Max > MistRHstop)
						pGD_TControl_Tepl->Systems[cSysMist].Max = pGD_TControl_Tepl->Systems[cSysMist].Max - MistRHstop;
					else
						pGD_TControl_Tepl->Systems[cSysMist].Max = 0;
					pGD_TControl_Tepl->SaveMaxMist = pGD_TControl_Tepl->Systems[cSysMist].Max;
					res = pGD_TControl_Tepl->Systems[cSysMist].Max;
				}
				if (vRHtepl < vKeepRHstart)
				{
					pGD_TControl_Tepl->SaveMaxMist++;
					if (pGD_TControl_Tepl->SaveMaxMist > pGD_TControl_Tepl->Systems[cSysMist].Max)
						pGD_TControl_Tepl->SaveMaxMist = pGD_TControl_Tepl->Systems[cSysMist].Max;
				}
			}
			else
			{
				pGD_TControl_Tepl->SaveMaxMist++;
				if (pGD_TControl_Tepl->SaveMaxMist > pGD_TControl_Tepl->Systems[cSysMist].Max)
					pGD_TControl_Tepl->SaveMaxMist = pGD_TControl_Tepl->Systems[cSysMist].Max;
			}
		}
		else
		{
			res = vMistMax;
			if (MistRHstop)
			{
				if ( (vRHtepl > vKeepRHstart)&&(vRHtepl < vKeepRHend) )
				{
					res = ((vRHtepl-vKeepRHstart) * MistRHstop) / (vKeepRHend - vKeepRHstart);
					if (pGD_TControl_Tepl->Systems[cSysMist].Max > res)
						pGD_TControl_Tepl->Systems[cSysMist].Max = pGD_TControl_Tepl->Systems[cSysMist].Max - res;
					else
					{
						pGD_TControl_Tepl->SaveMaxMist--;
						if (pGD_TControl_Tepl->SaveMaxMist < 0)
							pGD_TControl_Tepl->SaveMaxMist = 0;
						pGD_TControl_Tepl->Systems[cSysMist].Max=0;
						res = 0;
					}
				}
				if (vRHtepl >= vKeepRHend)
				{
					if (pGD_TControl_Tepl->Systems[cSysMist].Max > MistRHstop)
						pGD_TControl_Tepl->Systems[cSysMist].Max = pGD_TControl_Tepl->Systems[cSysMist].Max - MistRHstop;
					else
						pGD_TControl_Tepl->Systems[cSysMist].Max = 0;
					pGD_TControl_Tepl->SaveMaxMist = pGD_TControl_Tepl->Systems[cSysMist].Max;
					res = pGD_TControl_Tepl->Systems[cSysMist].Max;
				}
				if (vRHtepl < vKeepRHstart)
				{
					res = (vTAHUdelta * 100) / vMaxCorrAHUrh;
					pGD_TControl_Tepl->Systems[cSysMist].Max = res;
					if (res > vMistMax)
					{
						res = vMistMax;
						pGD_TControl_Tepl->Systems[cSysMist].Max = vMistMax;
					}
					if (res > pGD_TControl_Tepl->SaveMaxMist)
					{
						pGD_TControl_Tepl->SaveMaxMist++;
						if (pGD_TControl_Tepl->SaveMaxMist > res)
							pGD_TControl_Tepl->SaveMaxMist = res;
					}
					else
					{
						pGD_TControl_Tepl->SaveMaxMist--;
						if (pGD_TControl_Tepl->SaveMaxMist < res)
							pGD_TControl_Tepl->SaveMaxMist = res;
					}
				}
			}
			else
			{
				res = (vTAHUdelta * 100) / vMaxCorrAHUrh;
				pGD_TControl_Tepl->Systems[cSysMist].Max = res;
				if (res > vMistMax)
				{
					res = vMistMax;
					pGD_TControl_Tepl->Systems[cSysMist].Max = vMistMax;
				}
				if (res > pGD_TControl_Tepl->SaveMaxMist)
				{
					pGD_TControl_Tepl->SaveMaxMist++;
					if (pGD_TControl_Tepl->SaveMaxMist > res)
						pGD_TControl_Tepl->SaveMaxMist = res;

				}
				else
				{
					pGD_TControl_Tepl->SaveMaxMist--;
					if (pGD_TControl_Tepl->SaveMaxMist < res)
						pGD_TControl_Tepl->SaveMaxMist = res;
				}
			}
		}
	}
	else
	{
		pGD_TControl_Tepl->Systems[cSysMist].Max = 0;
		res = 0;
		if (pGD_TControl_Tepl->SaveMaxMist)
		pGD_TControl_Tepl->SaveMaxMist--;
		if (pGD_TControl_Tepl->SaveMaxMist < 0)
			pGD_TControl_Tepl->SaveMaxMist = 0;
	}
	// ---------

	// было
	/*
	if (getRHoutAHUSensor())
	{
		if (getRHoutAHUSensor() > 9500)
			pGD_TControl_Tepl->SaveMaxMist--;
		else
			pGD_TControl_Tepl->SaveMaxMist++;
		if (pGD_TControl_Tepl->SaveMaxMist>pGD_TControl_Tepl->Systems[cSysMist].Max)
			pGD_TControl_Tepl->SaveMaxMist=pGD_TControl_Tepl->Systems[cSysMist].Max;
		if (pGD_TControl_Tepl->SaveMaxMist<0)
			pGD_TControl_Tepl->SaveMaxMist=0;
		pGD_TControl_Tepl->Systems[cSysMist].Max=pGD_TControl_Tepl->SaveMaxMist;
	}
	else
		pGD_TControl_Tepl->SaveMaxMist=pGD_TControl_Tepl->Systems[cSysMist].Max;
*/

	pGD_TControl_Tepl->Systems[cSysMist].Min=0;
	if (pGD_TControl_Tepl->Systems[cSysUCValve].Value<30)	// минимальное открытие клапана для работы панели 30
	{
		pGD_TControl_Tepl->Systems[cSysMist].Max=0;
	}

	pGD_TControl_Tepl->Systems[cSysMist].RCS=0;
	if ((YesBit(pGD_Hot_Hand[cHSmAHUPad].RCS,cbManMech))||(!pGD_MechConfig->RNum[cHSmAHUPad]))
	{
		SetBit(pGD_TControl_Tepl->Systems[cSysMist].RCS,cSysRHand);
		pGD_TControl_Tepl->Systems[cSysMist].Max=0;
	}

	// было, зачем не понятно
	/*
	pGD_TControl_Tepl->Systems[cSysMist].Value=pGD_Hot_Hand[cHSmAHUPad].Position;

	if (pGD_TControl_Tepl->Systems[cSysMist].Keep>pGD_TControl_Tepl->Systems[cSysMist].Max)
		pGD_TControl_Tepl->Systems[cSysMist].Keep=pGD_TControl_Tepl->Systems[cSysMist].Max;
	*/

	// 66 изменение
	pGD_TControl_Tepl->Systems[cSysMist].Value = pGD_TControl_Tepl->SaveMaxMist;
	pGD_TControl_Tepl->Systems[cSysMist].Keep = res;
	// ------

	if	(!pGD_TControl_Tepl->Systems[cSysMist].RCS)
	{
		if (pGD_TControl_Tepl->Systems[cSysMist].Keep<pGD_TControl_Tepl->Systems[cSysMist].Max)
			 SetBit(pGD_TControl_Tepl->Systems[cSysMist].RCS,cSysRUp);
		if (pGD_TControl_Tepl->Systems[cSysMist].Keep>pGD_TControl_Tepl->Systems[cSysMist].Min)
			 SetBit(pGD_TControl_Tepl->Systems[cSysMist].RCS,cSysRDown);
	}
	pGD_TControl_Tepl->Systems[cSysMist].Power=1000;//pGD_ConstMechanic->ConstMixVal[cHSmAHUPad].v_PFactor; // last
    //pGD_TControl_Tepl->Systems[cSysMist].Power=pGD_ConstMechanic->ConstMixVal[cHSmAHUPad].v_PFactor;
}

int SysInTemp(int8_t fnSys)
{
	if (!pGD_TControl_Tepl->Systems[fnSys].Power) pGD_TControl_Tepl->Systems[fnSys].Power=1000;
	return (((int32_t)pGD_TControl_Tepl->Systems[fnSys].Keep)*10000/pGD_TControl_Tepl->Systems[fnSys].Power);
}

int MaxSysInTemp(int8_t fnSys)
{
	if (!pGD_TControl_Tepl->Systems[fnSys].Power) pGD_TControl_Tepl->Systems[fnSys].Power=1000;
	return (((int32_t)pGD_TControl_Tepl->Systems[fnSys].Max)*10000/pGD_TControl_Tepl->Systems[fnSys].Power);
}

void FinalCheckSys(int8_t fnSys)
{
	if (pGD_TControl_Tepl->Systems[fnSys].Max<0)
		pGD_TControl_Tepl->Systems[fnSys].Max=0;
	if (pGD_TControl_Tepl->Systems[fnSys].Keep>pGD_TControl_Tepl->Systems[fnSys].Max)
		pGD_TControl_Tepl->Systems[fnSys].Keep=pGD_TControl_Tepl->Systems[fnSys].Max;
	if (pGD_TControl_Tepl->Systems[fnSys].Keep<pGD_TControl_Tepl->Systems[fnSys].Min)
		pGD_TControl_Tepl->Systems[fnSys].Keep=pGD_TControl_Tepl->Systems[fnSys].Min;
}

char oldPosition = 0;

void valveSetOldPos(void)
{
	oldPosition = pGD_TControl_Tepl->Systems[cSysUCValve].Keep;
}

char valveGetOldPos(void)
{
	return oldPosition;
}

//uint16_t fInRH_Res = 0;

int KeepInRH(char fnTepl)
{
	if (!pGD_TControl_Tepl->Systems[cSysInRH].Keep) return 0;
	int16_t Res;
	int16_t RH1, RH2, RHset, RHmes;
	int16_t	OutAbsH, InAbsH;
	//pGD_ConstMechanic->ConstMixVal[cHSmInRH].v_TimeMixVal;

	pGD_TControl_Tepl->Systems[cSysInRH].Max = pGD_Control_Tepl->InRHMax;
	pGD_TControl_Tepl->Systems[cSysInRH].Min = pGD_Control_Tepl->InRHMin;
	//pGD_TControl_Tepl->Systems[cSysInRH].Max = (pGD_Control_Tepl->InRHMax * pGD_ConstMechanic->ConstMixVal[cHSmInRH].v_TimeMixVal) / 100;
	//pGD_TControl_Tepl->Systems[cSysInRH].Min = (pGD_Control_Tepl->InRHMin * pGD_ConstMechanic->ConstMixVal[cHSmInRH].v_TimeMixVal) / 100;


	//RH1 = getRH1AHUSensor();
	//RH2 = getRH2AHUSensor();
	RHmes = getRH(fnTepl)/100;
	RHset = DefAbsHum()/100;
	//RH1 = DefAbsHumSensor(RH1)/100;
	//RH2 = DefAbsHumSensor(RH2)/100;

	//fInRH_RH1 = RH1;
	//fInRH_RH2 = RH2;
 	//fInRH_RHset = RHset;

	//if ((RH1) && (RH2) && (RHset))
	if ((RHmes) && (RHset))
		Res = pGD_ConstMechanic->ConstMixVal[cHSmInRH].v_PFactor * (RHset - RHmes);
		//Res = (pGD_ConstMechanic->ConstMixVal[cHSmInRH].v_PFactor * (RHset - ((RH1 + RH2)/2) )) / pGD_ConstMechanic->ConstMixVal[cHSmInRH].v_IFactor;
	else
		return 0;
	//fInRH_Res = Res;  // потом убрать!
	if (Res < 0)
		{
			pGD_TControl_Tepl->Systems[cSysInRH].Keep = 0;
			return 0;
		}
	pGD_Hot_Hand[cHSmInRH].Position = Res;
	if (Res > pGD_TControl_Tepl->Systems[cSysInRH].Max)
		Res = pGD_TControl_Tepl->Systems[cSysInRH].Max;

	if ( (Res > 0) && (Res < pGD_TControl_Tepl->Systems[cSysInRH].Min) )
		Res = pGD_TControl_Tepl->Systems[cSysInRH].Min;
	if (GD.TuneClimate.CloseInRH_AHU > 0)
	{
		if (pGD_Hot_Hand[cHSmUCValve].Position > GD.TuneClimate.CloseInRH_AHU)
			Res = 0;
	}
	return Res;
}

int KeepUCValve(char prevPosition)
{
	int16_t tempKeep;
	int16_t newKeep;
	int8_t delta = 0;
	tempKeep = pGD_TControl_Tepl->Systems[cSysUCValve].Keep;

	if ((tempKeep>=GD.TuneClimate.f_MaxOpenRain)&&(GD.TControl.bSnow))
	{
		tempKeep=GD.TuneClimate.f_MaxOpenRain;
		return tempKeep;
	}

	if (tempKeep > prevPosition )  // клапан открывается
	{
		delta = tempKeep - prevPosition;
	if (prevPosition <= GD.TuneClimate.fUC_S1Level)  // если Процент открытия менее первого уровня
	{
		if (delta > GD.TuneClimate.fUC_Offset1)
			return prevPosition + GD.TuneClimate.fUC_Offset1;
		else
			return tempKeep;
	}
	if ((prevPosition >= GD.TuneClimate.fUC_S1Level) && (prevPosition <= GD.TuneClimate.fUC_S2Level))  // если Процент открытия менее второго уровня
	{
		if (delta > GD.TuneClimate.fUC_Offset2)
			return prevPosition + GD.TuneClimate.fUC_Offset2;
		else
			return tempKeep;
	}
	if ((prevPosition >= GD.TuneClimate.fUC_S2Level) && (prevPosition <= GD.TuneClimate.fUC_S3Level))  // если Процент открытия менее второго уровня
	{
		if (delta > GD.TuneClimate.fUC_Offset3)
			return prevPosition + GD.TuneClimate.fUC_Offset3;
		else
			return tempKeep;
	}
	if (prevPosition >= GD.TuneClimate.fUC_S3Level)  // если Процент открытия более последнего третьего уровня
	{
		if (delta > GD.TuneClimate.fUC_Offset4)
			return prevPosition + GD.TuneClimate.fUC_Offset4;
		else
			return tempKeep;
	}
	}
	else		// клапан закрывается
	{
		delta = prevPosition - tempKeep;
		if (prevPosition <= GD.TuneClimate.fUC_S1Level)  // если Процент открытия менее первого уровня
		{
			if (delta > GD.TuneClimate.fUC_Offset1)
				return prevPosition - GD.TuneClimate.fUC_Offset1;
			else
				return tempKeep;
		}
		if ((prevPosition >= GD.TuneClimate.fUC_S1Level) && (prevPosition <= GD.TuneClimate.fUC_S2Level))  // если Процент открытия менее второго уровня
		{
			if (delta > GD.TuneClimate.fUC_Offset2)
				return prevPosition - GD.TuneClimate.fUC_Offset2;
			else
				return tempKeep;
		}
		if ((prevPosition >= GD.TuneClimate.fUC_S2Level) && (prevPosition <= GD.TuneClimate.fUC_S3Level))  // если Процент открытия менее второго уровня
		{
			if (delta > GD.TuneClimate.fUC_Offset3)
				return prevPosition - GD.TuneClimate.fUC_Offset3;
			else
				return tempKeep;
		}
		if (prevPosition >= GD.TuneClimate.fUC_S3Level)  // если Процент открытия более последнего третьего уровня
		{
			if (delta > GD.TuneClimate.fUC_Offset4)
				return prevPosition - GD.TuneClimate.fUC_Offset4;
			else
				return tempKeep;
		}
	}

/*	GD.TuneClimate.fAHU_S1Level;
	GD.TuneClimate.fAHU_S2Level;
	GD.TuneClimate.fAHU_S3Level;

	GD.TuneClimate.fAHU_Offset1;
	GD.TuneClimate.fAHU_Offset2;
	GD.TuneClimate.fAHU_Offset3;
	GD.TuneClimate.fAHU_Offset4;
*/

//	//return pGD_TControl_Tepl->Systems[cSysUCValve].Keep;
//	return 0;
}

int KeepFanSystem(char fnTepl)
{
	int8_t mode = 0;
	volatile int16_t newKeep;
	volatile int16_t delta = 0;
	volatile int16_t minT = 0;
	volatile int16_t maxT = 0;
	volatile int8_t minSpeed = 0;
	volatile int8_t maxSpeed = 0;
	volatile int16_t miT = 0;
	volatile int16_t maT = 0;
	volatile int16_t tempKeep = 0;
	volatile int16_t windSpeed = 0;
	volatile int16_t windDirect = 0;
	volatile int16_t greenHousePos = 0;
	volatile int16_t PosFluger = 0;
	volatile int16_t MaxSpeedAHUwind = 0;
	volatile int16_t MinWindSpeed = 0;
	volatile int16_t MaxWindSpeed = 0;
	volatile int16_t deltaSpeedWind = 0;
	volatile float windSpeedCalc = 0;
	volatile int16_t zone = 10;
	volatile int16_t deltaW = 0;
	minSpeed = GD.Hot.Tepl[fnTepl].AllTask.AHUVent;
	maxSpeed = GD.Control.Tepl[fnTepl].f_MaxAHUSpd;
	minT = GD.TuneClimate.vAHU_MinTempr * 100;
	maxT = GD.TuneClimate.vAHU_MaxTempr * 100;
	miT = getTempOutAHU(fnTepl);
	maT = getTempOutEndAHU(fnTepl);
	volatile int16_t Tout = 0;
	volatile int16_t ToutTask = 0;
	Tout = getTempOutAHU(fnTepl) / 100;
	ToutTask = GD.Hot.Tepl[fnTepl].NextTCalc.TVentCritery / 100;
	MinWindSpeed = GD.TuneClimate.f_WindStart;
	MaxSpeedAHUwind = GD.TuneClimate.MaxAHUspeed;
	MaxWindSpeed = GD.TuneClimate.MaxAHUwindSpeed;
	windSpeed = GD.TControl.MeteoSensing[cSmVWindSens] / 100;
	windDirect = GD.TControl.MeteoSensing[cSmDWindSens];
	greenHousePos = GD.TuneClimate.o_TeplPosition;

	// изменение 100
	volatile int16_t Theat = getTempHeat(fnTepl);
	volatile int16_t Tcont = getTempCont(fnTepl);
	volatile int16_t minSpeedT = GD.TuneClimate.AHUspeed_Tmin * 100;
	volatile int16_t maxSpeedT = GD.TuneClimate.AHUspeed_Tmax * 100;
	volatile int16_t maxSpeedTcorr = GD.TuneClimate.AHUspeed_Corr;

	if ((minT != 0) && (maxT != 0))
		mode = 1;
	if ((windSpeed > 0) && (MaxSpeedAHUwind > 0))
	{
		if (GD.Hot.MidlWind<GD.TuneClimate.f_WindStart)
			mode = 0;
		mode = 2;
	}
	switch (mode)
	{
		case 0:
		{
			tempKeep = minSpeed;

			// расчет без коррекций
			//if (Tout > ToutTask)
			//	tempKeep = Tout * (minSpeed * 1.5) / ToutTask;
			//else
			//	tempKeep = minSpeed;

			// было так v1
			//tempKeep = pGD_TControl_Tepl->Systems[cSysAHUSpeed].Keep + pGD_Hot_Tepl->AllTask.AHUVent;
			break;
		}
		case 1:
		{
			if ((minT != 0) && (maxT != 0))	// если работает коррекция по двум датчикам в рукаве
			{
				delta = miT - maT;
				if (delta < 0) delta = delta * -1;
				tempKeep = delta * maxSpeed / maxT;
				if (tempKeep > maxSpeed) tempKeep = maxSpeed;
				if (tempKeep < minSpeed) tempKeep = minSpeed;
			}
			break;
		}
		case 2:
		{
			//if (tempKeep > maxSpeed) tempKeep = maxSpeed;
			//if (tempKeep <= 0)
			//	{
			//		tempKeep = minSpeed;
			//	}
			//if (GD.Hot.MidlWind<GD.TuneClimate.f_WindStart) return tempKeep;

			if ((windSpeed > 0) && (MaxSpeedAHUwind > 0))
			{
				if (greenHousePos != windDirect)
				{
					if (greenHousePos > windDirect)
						PosFluger = greenHousePos - windDirect;
					else
						PosFluger = windDirect - greenHousePos;
				}
				else
					PosFluger = windDirect;


				tempKeep = 0;
				if (PosFluger <= 180)
				{
					if (greenHousePos > windDirect)
						zone = 1;
					else
						zone = 0;

					if (PosFluger > 90)
						PosFluger = 90 - (PosFluger - 90);
				} else
				{
					if (greenHousePos > windDirect)
						zone = 0;
					else
						zone = 1;

					PosFluger = PosFluger - 180;
					if (PosFluger > 90)
						PosFluger = 90 - (PosFluger - 90);
				}
				if (windSpeed >= MinWindSpeed)// && (windSpeed <= MaxWindSpeed))
				{
					if (MaxWindSpeed < windSpeed)
						MaxWindSpeed = 	windSpeed;

					windSpeedCalc = PosFluger * windSpeed / 90;   // скорость ветра от текущей позиции флугера и скорости ветра
					tempKeep = windSpeedCalc * MaxSpeedAHUwind / MaxWindSpeed;   // увеличение скорости на вычесленный процент
					deltaW = tempKeep;
					tempKeep = minSpeed + tempKeep;
				}
				if (windSpeed < MinWindSpeed)
					tempKeep = minSpeed;
				if (windSpeed > MaxWindSpeed)
					tempKeep = MaxSpeedAHUwind + minSpeed;
				if (zone != fnTepl)
					tempKeep = minSpeed - deltaW; // теперь уменьшаем скорость
			}
			break;
		}
	}
// провки в мониторе, Т контроля вместо Источника для Т вент
	// изменение 100. коррекция скорости вент по Т и Тконтр
	if ((Theat>0)&&(Tcont>0)&&(minSpeedT)&&(maxSpeedT)&&(maxSpeedTcorr))
	{
		if (Theat >= Tcont)
			Theat = Theat - Tcont;
		else if (Tcont > Theat)
			Theat = Tcont - Theat;
		if ((Theat >= minSpeedT) && (Theat <= maxSpeedT))
		{
			IntY = Theat;
			CorrectionRule(minSpeedT, maxSpeedT, maxSpeedTcorr,0);
			tempKeep = tempKeep + IntZ;
		} else if (Theat > minSpeedT)
			tempKeep = tempKeep + maxSpeedTcorr;
	}
	// -----------------------------


	// итоговая проверка на мин и мак скорость
	// в зависимости от того открыт ли клапан в зоне в которую дует ветер
	if (zone)		// инвертируем зоны
		zone = 0;
	else
		zone = 1;
	if (GD.TControl.Tepl[zone].Systems[cSysUCValve].Keep)
	{
		if (tempKeep > maxSpeed) tempKeep = maxSpeed;
		if (tempKeep <= 0) tempKeep = minSpeed;
		if (MaxSpeedAHUwind == 0)   // если усл коррекции скорости по ветру выкл то мин скорость как в задании
			if (tempKeep < minSpeed) tempKeep = minSpeed;
	}
	else
	{
		if ((minSpeedT==0)&&(maxSpeedT==0)&&(maxSpeedTcorr==0)) // коментарии для проверки
			tempKeep = minSpeed;
		else
			{
				if (tempKeep > maxSpeed) tempKeep = maxSpeed;
				if (tempKeep <= 0) tempKeep = minSpeed;
			}
	}
	return tempKeep;
}


/*int KeepFanSystem(char fnTepl)
{
	volatile int16_t tempKeep;
	volatile int16_t newKeep;
	volatile int16_t delta = 0;
	volatile int16_t minT = 0;
	volatile int16_t maxT = 0;
	volatile int8_t minSpeed = 0;
	volatile int8_t maxSpeed = 0;
	volatile int16_t miT = 0;
	volatile int16_t maT = 0;

	minSpeed = GD.Hot.Tepl[fnTepl].AllTask.AHUVent;
	maxSpeed = GD.Control.Tepl[fnTepl].f_MaxAHUSpd;
	minT = GD.TuneClimate.vAHU_MinTempr * 100;
	maxT = GD.TuneClimate.vAHU_MaxTempr * 100;
	miT = getTempOutAHU(fnTepl);
	maT = getTempOutEndAHU(fnTepl);
	//delta = getTempOutAHU(fnTepl);
	//delta = delta - getTempOutEndAHU(fnTepl);
	delta = miT - maT;
	if (delta < 0) delta = delta * -1;
	tempKeep = delta * maxSpeed / maxT;
=======
>>>>>>> c94f40d9df5cc1c12caf50d8af8a24b3f094d399
	if (tempKeep > maxSpeed) tempKeep = maxSpeed;
	if (MaxSpeedAHUwind == 0)   // если усл коррекции скорости по ветру выкл то мин скорость как в задании
		if (tempKeep < minSpeed) tempKeep = minSpeed;
	return tempKeep;
<<<<<<< HEAD

	//return pGD_TControl_Tepl->Systems[cSysAHUSpeed].Keep+pGD_Hot_Tepl->AllTask.AHUVent;
} */

int KeepScreenSystem(void)
{
	return pGD_TControl_Tepl->Screen[0].Value-pGD_TControl_Tepl->Systems[cSysScreen].Keep;
}


int KeepMistSystem(void)
{
	return pGD_TControl_Tepl->Systems[cSysMist].Keep;
}

int KeepAHUPipeSystem(void)
{
	return pGD_TControl_Tepl->Systems[cSysAHUPipe].Keep;
}

void CheckFanSystem(void)
{
//	pGD_TControl_Tepl->Systems[cSysAHUSpeed].Max=pGD_Control_Tepl->f_MaxAHUSpd-pGD_Hot_Tepl->AllTask.AHUVent;
//	if (pGD_TControl_Tepl->Systems[cSysAHUSpeed].Max>60-pGD_Hot_Tepl->AllTask.AHUVent)
//		pGD_TControl_Tepl->Systems[cSysAHUSpeed].Max=60-pGD_Hot_Tepl->AllTask.AHUVent;
		//(*pGD_TControl_Tepl).PrevMaxWinOnW;
//	IntY=GD.Hot.MidlSR;
//	CorrectionRule(0,300,pGD_TControl_Tepl->Systems[cSysAHUSpeed].Max,0);
//	pGD_TControl_Tepl->Systems[cSysAHUSpeed].Max=IntZ;
//	pGD_TControl_Tepl->Systems[cSysAHUSpeed].Min=0;

	pGD_TControl_Tepl->Systems[cSysAHUSpeed].RCS=0;
	if ((YesBit(pGD_Hot_Hand[cHSmAHUSpeed1].RCS,cbManMech))||(!pGD_MechConfig->RNum[cHSmAHUSpeed1]))
	{
		SetBit(pGD_TControl_Tepl->Systems[cSysAHUSpeed].RCS,cSysRHand);
//		pGD_TControl_Tepl->Systems[cSysAHUSpeed].Max=0;
	}
	pGD_TControl_Tepl->Systems[cSysAHUSpeed].Value=pGD_Hot_Hand[cHSmAHUSpeed1].Position;

	if (pGD_TControl_Tepl->Systems[cSysAHUSpeed].Keep>pGD_TControl_Tepl->Systems[cSysAHUSpeed].Max)
		pGD_TControl_Tepl->Systems[cSysAHUSpeed].Keep=pGD_TControl_Tepl->Systems[cSysAHUSpeed].Max;

	if	(!pGD_TControl_Tepl->Systems[cSysAHUSpeed].RCS)
	{
		if (pGD_TControl_Tepl->Systems[cSysAHUSpeed].Keep<pGD_TControl_Tepl->Systems[cSysAHUSpeed].Max)
			 SetBit(pGD_TControl_Tepl->Systems[cSysAHUSpeed].RCS,cSysRUp);
		if (pGD_TControl_Tepl->Systems[cSysAHUSpeed].Keep>pGD_TControl_Tepl->Systems[cSysAHUSpeed].Min)
			 SetBit(pGD_TControl_Tepl->Systems[cSysAHUSpeed].RCS,cSysRDown);
	}
	pGD_TControl_Tepl->Systems[cSysAHUSpeed].Power=1000;//pGD_ConstMechanic->ConstMixVal[cHSfmAHUSpeed1].v_PFactor;  // last
    //pGD_TControl_Tepl->Systems[cSysAHUSpeed].Power=pGD_ConstMechanic->ConstMixVal[cHSmAHUSpeed1].v_PFactor;
}

void SetPrioritySystem(int8_t fnSys, int8_t fPrior,int8_t Up)
{
	pGD_TControl_Tepl->Systems[fnSys].Prior=0;
	if ((Up)&&(YesBit(pGD_TControl_Tepl->Systems[fnSys].RCS,cSysRUp)))
		pGD_TControl_Tepl->Systems[fnSys].Prior=fPrior;
	if ((!Up)&&(YesBit(pGD_TControl_Tepl->Systems[fnSys].RCS,cSysRDown)))
		pGD_TControl_Tepl->Systems[fnSys].Prior=fPrior;
}

#warning set new strategy
// NEW
void PutCritery(int16_t dT, int16_t dRH)
{
	if ((dT>=0)&&(dRH>=0))   // strat1
	{
		SetPrioritySystem(cSysUCValve,pGD_Strategy_Tepl->StratAHUvalve1[0],pGD_Strategy_Tepl->StratAHUvalve1[1]);
		SetPrioritySystem(cSysScreen,pGD_Strategy_Tepl->StratTermoScreen1[0],pGD_Strategy_Tepl->StratTermoScreen1[1]);
		SetPrioritySystem(cSysAHUPipe,pGD_Strategy_Tepl->StratKontur3_1[0],pGD_Strategy_Tepl->StratKontur3_1[1]);
		SetPrioritySystem(cSysMist,pGD_Strategy_Tepl->StratPressReg1[0],pGD_Strategy_Tepl->StratPressReg1[1]);
		SetPrioritySystem(cSysAHUSpeed,pGD_Strategy_Tepl->StratAHUspeed1[0],pGD_Strategy_Tepl->StratAHUspeed1[1]);
		SetPrioritySystem(cSysInRH,pGD_Strategy_Tepl->StratInRH1[0],pGD_Strategy_Tepl->StratInRH1[1]);
	}
	if ((dT>=0)&&(dRH<0))	// strat2
	{
		SetPrioritySystem(cSysAHUPipe,pGD_Strategy_Tepl->StratKontur3_2[0],pGD_Strategy_Tepl->StratKontur3_2[1]);
		SetPrioritySystem(cSysMist,pGD_Strategy_Tepl->StratPressReg2[0],pGD_Strategy_Tepl->StratPressReg2[1]);
		SetPrioritySystem(cSysUCValve,pGD_Strategy_Tepl->StratAHUvalve2[0],pGD_Strategy_Tepl->StratAHUvalve2[1]);
		SetPrioritySystem(cSysScreen,pGD_Strategy_Tepl->StratTermoScreen2[0],pGD_Strategy_Tepl->StratTermoScreen2[1]);
		SetPrioritySystem(cSysAHUSpeed,pGD_Strategy_Tepl->StratAHUspeed2[0],pGD_Strategy_Tepl->StratAHUspeed2[1]);
		SetPrioritySystem(cSysInRH,pGD_Strategy_Tepl->StratInRH2[0],pGD_Strategy_Tepl->StratInRH2[1]);
	}
	if ((dT<0)&&(dRH>=0))	// strat3
	{
		SetPrioritySystem(cSysMist,pGD_Strategy_Tepl->StratPressReg3[0],pGD_Strategy_Tepl->StratPressReg3[1]);
		SetPrioritySystem(cSysAHUPipe,pGD_Strategy_Tepl->StratKontur3_3[0],pGD_Strategy_Tepl->StratKontur3_3[1]);
		SetPrioritySystem(cSysUCValve,pGD_Strategy_Tepl->StratAHUvalve3[0],pGD_Strategy_Tepl->StratAHUvalve3[1]);
		SetPrioritySystem(cSysScreen,pGD_Strategy_Tepl->StratTermoScreen3[0],pGD_Strategy_Tepl->StratTermoScreen3[1]);
		SetPrioritySystem(cSysAHUSpeed,pGD_Strategy_Tepl->StratAHUspeed3[0],pGD_Strategy_Tepl->StratAHUspeed3[1]);
		SetPrioritySystem(cSysInRH,pGD_Strategy_Tepl->StratInRH3[0],pGD_Strategy_Tepl->StratInRH3[1]);
	}
	if ((dT<0)&&(dRH<0))	// strat4
	{
		SetPrioritySystem(cSysUCValve,pGD_Strategy_Tepl->StratAHUvalve4[0],pGD_Strategy_Tepl->StratAHUvalve4[1]);
		SetPrioritySystem(cSysScreen,pGD_Strategy_Tepl->StratTermoScreen4[0],pGD_Strategy_Tepl->StratTermoScreen4[1]);
		SetPrioritySystem(cSysAHUPipe,pGD_Strategy_Tepl->StratKontur3_4[0],pGD_Strategy_Tepl->StratKontur3_4[1]);
		SetPrioritySystem(cSysMist,pGD_Strategy_Tepl->StratPressReg4[0],pGD_Strategy_Tepl->StratPressReg4[1]);
		SetPrioritySystem(cSysAHUSpeed,pGD_Strategy_Tepl->StratAHUspeed4[0],pGD_Strategy_Tepl->StratAHUspeed4[1]);
		SetPrioritySystem(cSysInRH,pGD_Strategy_Tepl->StratInRH4[0],pGD_Strategy_Tepl->StratInRH4[1]);
	}
/*void PutCritery(int16_t dT, int16_t dRH)
{
	if ((dT>=0)&&(dRH>=0))
	{
		SetPrioritySystem(cSysUCValve,pGD_Strategy_Tepl->StratAHUvalve1[0],SYS_GO_UP);
		SetPrioritySystem(cSysScreen,pGD_Strategy_Tepl->StratTermoScreen1[0],SYS_GO_UP);
		SetPrioritySystem(cSysAHUPipe,pGD_Strategy_Tepl->StratKontur3_1[0],SYS_GO_DOWN);
		SetPrioritySystem(cSysMist,pGD_Strategy_Tepl->StratPressReg1[0],SYS_GO_UP);
		SetPrioritySystem(cSysAHUSpeed,pGD_Strategy_Tepl->StratAHUspeed1[0],SYS_GO_UP);
	}
	if ((dT>=0)&&(dRH<0))
	{
		SetPrioritySystem(cSysAHUPipe,pGD_Strategy_Tepl->StratKontur3_2[0],SYS_GO_DOWN);
		SetPrioritySystem(cSysMist,pGD_Strategy_Tepl->StratPressReg2[0],SYS_GO_UP);
		SetPrioritySystem(cSysUCValve,pGD_Strategy_Tepl->StratAHUvalve2[0],SYS_GO_UP);
		SetPrioritySystem(cSysScreen,pGD_Strategy_Tepl->StratTermoScreen2[0],SYS_GO_UP);
		SetPrioritySystem(cSysAHUSpeed,pGD_Strategy_Tepl->StratAHUspeed2[0],SYS_GO_UP);
	}
	if ((dT<0)&&(dRH>=0))
	{
		SetPrioritySystem(cSysMist,pGD_Strategy_Tepl->StratPressReg3[0],SYS_GO_DOWN);
		SetPrioritySystem(cSysAHUPipe,pGD_Strategy_Tepl->StratKontur3_3[0],SYS_GO_UP);
		SetPrioritySystem(cSysUCValve,pGD_Strategy_Tepl->StratAHUvalve3[0],SYS_GO_DOWN);
		SetPrioritySystem(cSysScreen,pGD_Strategy_Tepl->StratTermoScreen3[0],SYS_GO_DOWN);
		SetPrioritySystem(cSysAHUSpeed,pGD_Strategy_Tepl->StratAHUspeed3[0],SYS_GO_DOWN);
	}
	if ((dT<0)&&(dRH<0))
	{
		SetPrioritySystem(cSysUCValve,pGD_Strategy_Tepl->StratAHUvalve4[0],SYS_GO_DOWN);
		SetPrioritySystem(cSysScreen,pGD_Strategy_Tepl->StratTermoScreen4[0],SYS_GO_DOWN);
		SetPrioritySystem(cSysAHUPipe,pGD_Strategy_Tepl->StratKontur3_4[0],SYS_GO_UP);
		SetPrioritySystem(cSysMist,pGD_Strategy_Tepl->StratPressReg4[0],SYS_GO_DOWN);
		SetPrioritySystem(cSysAHUSpeed,pGD_Strategy_Tepl->StratAHUspeed4[0],SYS_GO_DOWN);
	}*/
}


int8_t GetOffSet(int8_t fnSys)
{
	switch (fnSys)
	{
		case cSysRailPipe: 	//1
			return cHSmMixVal+cSmKontur1;
		case cSysHeadPipe: 	//2
			return cHSmMixVal+cSmKontur2;
		case cSysAHUPipe: 	//0
			return cHSmMixVal+cSmKonturAHU;
//		case cSysTHose: //3
//			return cSmScreen;
		case cSysAHUSpeed:  //7
			return cHSmAHUSpeed1;
		case cSysUCValve: 	//8
 			return cHSmUCValve;
		case cSysScreen:  	//10
			return cHSmScrTH;
		case cSysInRH:  	//9
			return cHSmInRH;
	}

/*
#define cSmKonturRail		0
#define cSmKonturHead		1
#define cSmKonturAHU		2
#define cSmKonturSide		3
#define cSmKontur5		4
#define cSmKontur6	5
#define cSmWindowUnW	6
#define cSmAHUSpd		7
#define cSmUCValve		8
#define cSmAHURez		9
#define cSmScreen		10
в
#define cSysAHUPipe			0
#define cSysRailPipe		1
#define cSysHeadPipe		2
#define cSysSidePipe		3
#define cSysUCValve			4
#define cSysScreen			5
#define cSysAHUSpeed		6
#define cSysMist			7
*/
}

uint8_t fnMSysOut[8];
uint8_t fnMPriorOut[8];
int8_t fnMKeepOut[8][8];
int16_t fnMKeepParamOut[8][5];
int8_t fnMKeepErrorOut[8];


int8_t TakeForSys(int16_t fnCritery, char fnTepl)
{
	int16_t fnSys,fnMSys,fnMPrior;
	int32_t CriterNew;
	fnMSys=-1;
	fnMPrior=0;
	for (fnSys=0;fnSys<cSUCSystems;fnSys++)
	{
		if (pGD_TControl_Tepl->Systems[fnSys].Prior>fnMPrior)
		{
			fnMPrior=pGD_TControl_Tepl->Systems[fnSys].Prior;
			fnMSys=fnSys;
		}
	}
	if (fnMSys<0)
	{
		pGD_TControl_Tepl->StopVentI++;
		if (pGD_TControl_Tepl->StopVentI>cMaxStopI) pGD_TControl_Tepl->StopVentI=cMaxStopI;
		//fnMKeepErrorOut[fnTepl] = 1;  // вывод стратегии
		//fnMSysOut[fnTepl] = 0;     // вывод стратегии
		//fnMPriorOut[fnTepl] = 0;	 // вывод стратегии
		pGD_Hot_Tepl->CurrentStratSys = 0;
		GD.Hot.Tepl[fnTepl].CurrentStratSys = 0;
		return -1;
	}
	//pGD_TControl_Tepl->Systems[fnMSys].Keep+=((int32_t)CriterNew)*pGD_TControl_Tepl->Systems[fnMSys].Power/10000; // так было
	//fnMKeepErrorOut[fnTepl] = 0;  // есть активная система   // вывод стратегии
	pGD_TControl_Tepl->StopVentI=0;
	if (pGD_TControl_Tepl->Systems[fnMSys].Power/1000 == 0)
		pGD_TControl_Tepl->Systems[fnMSys].Power = 1000;

	pGD_TControl_Tepl->Systems[fnMSys].Keep = SetPID(((int32_t)fnCritery)*pGD_TControl_Tepl->Systems[fnMSys].Power/1000, GetOffSet(fnMSys),pGD_TControl_Tepl->Systems[fnMSys].Max, pGD_TControl_Tepl->Systems[fnMSys].Min); // last

	/*if (fnMSys == cSysUCValve)     // вывод стратегии
	{
		fnMKeepParamOut[fnTepl][0] = (int32_t)fnCritery;
		fnMKeepParamOut[fnTepl][1] = 1;//pGD_TControl_Tepl->Systems[fnMSys].Power/1000;
		fnMKeepParamOut[fnTepl][2] = GetOffSet(fnMSys);
		fnMKeepParamOut[fnTepl][3] = pGD_TControl_Tepl->Systems[fnMSys].Max;
		fnMKeepParamOut[fnTepl][4] = pGD_TControl_Tepl->Systems[fnMSys].Min;
	}
	*/
	GD.Hot.Tepl[fnTepl].CurrentStratSys = fnMSys * 10;   // вывод в hot блок текущей системы
	//fnMKeepOut[fnTepl][fnMSys] = pGD_TControl_Tepl->Systems[fnMSys].Keep;    // вывод стратегии
	for (fnSys=0;fnSys<cSUCSystems;fnSys++)
	{
		if ((fnSys==cSysRailPipe)||(fnSys==cSysHeadPipe))
			continue;
		if (fnSys!=fnMSys)
			KeepPID(pGD_TControl_Tepl->Systems[fnSys].Keep,((int32_t)fnCritery)*pGD_TControl_Tepl->Systems[fnSys].Power/1000, GetOffSet(fnSys));
	}
	pGD_Hot_Tepl->Kontur[cSmWindowUnW].SError=pGD_TControl_Tepl->Systems[cSysUCValve].Power/1000;  // NEW
	//fnMSysOut[fnTepl] = fnMSys;        // вывод стратегии
	//fnMPriorOut[fnTepl] = fnMPrior;    // вывод стратегии
}

//Для расчета критерия на базе текущих положений увлажнения, скорости вентиляторов, фрамуг
long __MechToVentTemp(void)
{
	//Расчет критерия из положения клапана УК
/*	LngY=pGD_Hot_Hand[cHSmUCValve].Position;
	LngY*=1000;
	if (pGD_ConstMechanic->ConstMixVal[cHSmUCValve].v_PFactor)
		LngY/=pGD_ConstMechanic->ConstMixVal[cHSmUCValve].v_PFactor;
	else
		LngY/=1000;
	LngY*=((long)pGD_TControl_Tepl->f_Power);
	LngY/=100;
*/
	LngX=SysInTemp(cSysUCValve);
	//Расчет критерия из положения увлажнения
/*	LngY=pGD_Hot_Hand[cHSmAHUPad].Position;
	LngY*=10000;
	if (pGD_ConstMechanic->ConstMixVal[cHSmAHUPad].v_PFactor)
		LngY/=pGD_ConstMechanic->ConstMixVal[cHSmAHUPad].v_PFactor;
	else
		LngY/=1000;*/
	LngX+=SysInTemp(cSysMist);
	//Расчет критерия из скорости вентилятора
/*	LngY=pGD_Hot_Hand[cHSmAHUSpeed1].Position;
	LngY*=10000;
	if (pGD_ConstMechanic->ConstMixVal[cHSmAHUSpeed1].v_PFactor)
		LngY/=pGD_ConstMechanic->ConstMixVal[cHSmAHUSpeed1].v_PFactor;
	else
		LngY/=1000;*/
	LngX+=SysInTemp(cSysAHUSpeed);

	return LngX;
}

//Для расчета максимального критерия на базе текущих положений увлажнения, скорости вентиляторов, фрамуг
long __MaxMechToVentTemp(void)
{
	return MaxSysInTemp(cSysUCValve)+MaxSysInTemp(cSysMist)+MaxSysInTemp(cSysAHUSpeed);

}


/*************************************************************************/
/*-*-*-*-*-*-*-*--Процедура установки границ для экрана--*-*-*-*-*-*-*-*-*/
/*************************************************************************/
/*void __sMinMaxScreen(void)
{	
	if (!pGD_TControl_Tepl->Kontur[cSmScreen].Separate)
	{
		SetBit(pGD_Hot_Tepl->Kontur[cSmScreen].RCS,cbNoWorkKontur);
		return;	
	}
	if (!pGD_TControl_Tepl->Screen[0].Mode)
	{
		(*pGD_TControl_Tepl).Kontur[cSmScreen].DoT=0;
		return;
	}
	if (YesBit(pGD_TControl_Tepl->RCS1,cbSCCorrection))
		pGD_Hot_Tepl->Kontur[cSmScreen].MaxCalc=GD.TuneClimate.sc_TFactor;	
	IntY=GD.TControl.OutTemp;
	CorrectionRule(GD.TuneClimate.s_StartCorrPow,GD.TuneClimate.s_EndCorrPow,
		(GD.TuneClimate.s_PowFactor-1000),0);
	(*pGD_TControl_Tepl).s_Power=GD.TuneClimate.s_PowFactor-IntZ;		
	if (GD.TuneClimate.s_PowFactor<1000) (*pGD_TControl_Tepl).s_Power=1000;

} */

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*************************************************************************/
/*-*-*-*-*-*-*-*--Процедура установки границ для фрамуг--*-*-*-*-*-*-*-*-*/
/*************************************************************************/
void __sMinMaxWindows(char fnTepl)
{	
	int	t_max;
//-------------------------------------------------------	
//Проверяем работу по заданию
//------------------------------------------------------
    


	if(((*pGD_Hot_Tepl).AllTask.Win<2))//||(YesBit(pGD_TControl_Tepl->Calorifer,0x02))) //Добавлено для блокировки фрамуг кондиционером
	{
//--------------------------------------------------------------------------------
//Если установлен режим работы по минимому то минимум должен совпасть с максимумом
//--------------------------------------------------------------------------------
		if((*pGD_Hot_Tepl).AllTask.Win)
		{
			(*pGD_Hot_Tepl).Kontur[cSmWindowUnW].MaxCalc=(*pGD_Hot_Tepl).Kontur[cSmWindowUnW].MinCalc;
			pGD_Hot_Tepl->Kontur[cSmWindowUnW].Status=cSFollowProg;
			//pGD_Hot_Tepl->Kontur[cSmWindowOnW].Status=cSFollowProg;
		}
		else
		{
			MemClr(&(*pGD_Hot_Tepl).Kontur[cSmWindowUnW].Optimal,sizeof(eKontur));
		}
//--------------------------------------------------------------------------------
//Стираем все накопленные данные
//--------------------------------------------------------------------------------
		//(*pGD_TControl_Tepl).Kontur[cSmWindowOnW].DoT=0;
		(*pGD_TControl_Tepl).Kontur[cSmWindowUnW].DoT=0;
		return;
	}
	//pGD_Hot_Tepl->Kontur[cSmWindowOnW].Status=cSOn;
	pGD_Hot_Tepl->Kontur[cSmWindowUnW].Status=cSOn;



	IntY=DefRH(fnTepl);
	CorrectionRule(GD.TuneClimate.f_min_RHStart,GD.TuneClimate.f_min_RHEnd,
		((int)GD.TuneClimate.f_min_Cor),0);
	ogrMin(&(pGD_Hot_Tepl->Kontur[cSmWindowUnW].MinCalc),IntZ);

	IntY=GD.TControl.MidlSR;// MeteoSensing[cSmOutTSens];
	CorrectionRule(GD.TuneClimate.f_SunStart,GD.TuneClimate.f_SunEnd,
		(GD.TuneClimate.f_SunIncOutT),0);

	IntY=GD.TControl.MeteoSensing[cSmOutTSens]+IntZ;

	CorrectionRule(GD.TuneClimate.f_StartCorrPow,GD.TuneClimate.f_EndCorrPow,
		(GD.TuneClimate.f_PowFactor-1000),0);
	(*pGD_TControl_Tepl).f_Power=GD.TuneClimate.f_PowFactor-IntZ;		
	if (GD.TuneClimate.f_PowFactor<1000) (*pGD_TControl_Tepl).f_Power=1000;


	t_max=pGD_Control_Tepl->f_MaxOpenUn;
	if ((t_max>GD.TuneClimate.f_MaxOpenRain)&&(GD.TControl.bSnow))
	{
		pGD_Hot_Tepl->Kontur[cSmWindowUnW].Status=cSWRain;
		t_max=GD.TuneClimate.f_MaxOpenRain;
	}
		//--------------------------------------------------------------------------------
//Максимум рассчитываем по внешней температуре
//--------------------------------------------------------------------------------
	IntY=GD.TControl.MeteoSensing[cSmOutTSens];
	CorrectionRule(GD.TuneClimate.f_MinTFreeze,GD.TuneClimate.f_MinTFreeze+f_MaxTFreeze,200,0);
	IntX=IntZ;

//--------------------------------------------------------------------------------
//Если не хотим чтобы открывалась подветренная сторона устанавливаем максимальный ветер в 0 
//--------------------------------------------------------------------------------
//	if (YesBit(GD.Hot.MeteoSens[cSmOutTSens].RCS,cbMinMaxVSens))
//		IntX=100;
//--------------------------------------------------------------------------------
//  Коррекция работы фраму по ветру
//--------------------------------------------------------------------------------
	IntY=GD.Hot.MidlWind;
	CorrectionRule(GD.TuneClimate.f_StormWind-f_StartWind,GD.TuneClimate.f_StormWind,100,0);
//В IntZ - ограничение по ветру

	if (IntZ>pGD_TControl_Tepl->OldPozUn)
	{	
		pGD_TControl_Tepl->UnWindStorm=GD.TuneClimate.f_WindHold;
		pGD_TControl_Tepl->OldPozUn=IntZ;
	}
	if (pGD_TControl_Tepl->UnWindStorm>0)
	{
		pGD_TControl_Tepl->UnWindStorm--;
		IntZ=pGD_TControl_Tepl->OldPozUn;
	}

//	if (!(GD.TuneClimate.f_MaxWind)) IntZ=100;
	if (IntX>100)
	{
		IntY=100-IntZ;
		IntX-=100;
	}
	else
	{
		IntY=IntX-IntZ;
		IntX=0;
	}
//	IntY=t_max-IntX-IntZ;

	ogrMin(&IntY,0);
	ogrMax(&IntY,t_max);

    (*pGD_Hot_Tepl).Kontur[cSmWindowUnW].MaxCalc=IntY;//(*pGD_TControl_Tepl).PrevMaxWinUnW;  
/*--------------------------------------------------------------------------------
//Проверяем было ли отличие от предыдущего максимума хотя бы на один шаг
//--------------------------------------------------------------------------------
    if ((IntY>=(*pGD_TControl_Tepl).PrevMaxWinUnW+ByteW)
		||(IntY<=(*pGD_TControl_Tepl).PrevMaxWinUnW-ByteW))
	{
		(*pGD_Hot_Tepl).Kontur[cSmWindowUnW].MaxCalc=(IntY/ByteW)*ByteW;
		(*pGD_TControl_Tepl).PrevMaxWinUnW=(*pGD_Hot_Tepl).Kontur[cSmWindowUnW].MaxCalc;
	}
	if ((IntY==0)||(IntY==100))
	{
		(*pGD_Hot_Tepl).Kontur[cSmWindowUnW].MaxCalc=IntY;
		(*pGD_TControl_Tepl).PrevMaxWinUnW=IntY;
	}*/
//--------------------------------------------------------------------------------
//Максимум для наветренной стороны 
//--------------------------------------------------------------------------------

/*    if ((IntY>=(*pGD_TControl_Tepl).PrevMaxWinOnW+ByteW)
		||(IntY<=(*pGD_TControl_Tepl).PrevMaxWinOnW-ByteW))
	{
		(*pGD_Hot_Tepl).Kontur[cSmWindowOnW].MaxCalc=(IntY/ByteW)*ByteW;
		(*pGD_TControl_Tepl).PrevMaxWinOnW=(*pGD_Hot_Tepl).Kontur[cSmWindowOnW].MaxCalc;
	}
	if ((IntY==0)||(IntY==100))
	{
		(*pGD_Hot_Tepl).Kontur[cSmWindowOnW].MaxCalc=IntY;
		(*pGD_TControl_Tepl).PrevMaxWinOnW=IntY;
	}
*/
//	if (YesBit((*(pGD_Hot_Hand+cHSmWinN+1-GD.Hot.PozFluger)).RCS,(cbNoMech+cbManMech)))
    if (pGD_Hot_Tepl->Kontur[cSmWindowUnW].Status<20)
    {
    	if (pGD_TControl_Tepl->Kontur[cSmWindowUnW].DoT/10==pGD_Hot_Tepl->Kontur[cSmWindowUnW].MaxCalc)
    		pGD_Hot_Tepl->Kontur[cSmWindowUnW].Status=cSReachMax;
    	if (pGD_TControl_Tepl->Kontur[cSmWindowUnW].DoT/10==pGD_Hot_Tepl->Kontur[cSmWindowUnW].MinCalc)
    		pGD_Hot_Tepl->Kontur[cSmWindowUnW].Status=cSReachMin;
    }

	if 	(YesBit((*(pGD_Hot_Hand+cHSmUCValve)).RCS,cbManMech))
	{
		SetBit(pGD_Hot_Tepl->Kontur[cSmWindowUnW].RCS,cbNoWorkKontur);
		(*pGD_TControl_Tepl).Kontur[cSmWindowUnW].DoT=0;
		(*pGD_Hot_Tepl).Kontur[cSmWindowUnW].MaxCalc=0;
		(*pGD_Hot_Tepl).Kontur[cSmWindowUnW].MinCalc=0;
		(*pGD_Hot_Tepl).Kontur[cSmWindowUnW].Status=cSWHand;
	}

	if (YesBit(pGD_Hot_Tepl->DiskrSens[0],cSmDVent))
	{
		(*pGD_Hot_Tepl).Kontur[cSmWindowUnW].Status=cSAlrExternal;
	}
	if (YesBit(pGD_TControl_Tepl->MechBusy[cHSmUCValve].RCS,cMSAlarm)) pGD_Hot_Tepl->Kontur[cSmWindowUnW].Status=cSAlrNoCtrl;

}

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/


/*************************************************************************/
/*-*-*-*-*-*-*-*-*--Процедура начальных установок для контура--*-*-*-*-*-*/
/*************************************************************************/
void __sInitKontur(char fnKontur)
{
//	char tTepl1;
//------------------------------------------------------------------------
//Определяем работает может ли работать контур
//------------------------------------------------------------------------
	pGD_Hot_Tepl_Kontur->Status=0;
	if (!(*pGD_TControl_Tepl_Kontur).Separate)
	{
		SetNoWorkKontur();
		return;	
	}
//------------------------------------------------------------------------
//Устанавливаем минимум и максимум
//------------------------------------------------------------------------

//------------------------------------------------------------------------
//Диагностика работы контура (выявляем ошибки не позволяющиее работать контуру)
//------------------------------------------------------------------------
	ByteY=0;
		pGD_Hot_Tepl_Kontur->SensValue=pGD_TControl_Tepl_Kontur->SensValue;
		if(!pGD_Control_Tepl->c_MaxTPipe[fnKontur])
		{
			pGD_Hot_Tepl_Kontur->Status=cSWNoMax;
			ByteY++;
		}
		if (((YesBit((*(pGD_Hot_Hand_Kontur+cHSmPump)).RCS,cbManMech))
			&&(!((*(pGD_Hot_Hand_Kontur+cHSmPump)).Position))))
		{
			pGD_Hot_Tepl_Kontur->Status=cSWHand;
			ByteY++;
		}

		if (ByteY)
		{
			SetNoWorkKontur();
			return;
		}	
//		{
//			SetNoWorkKontur();
//			return;
//		}	
		if (!(*pGD_Hot_Tepl_Kontur).SensValue)
		{
			pGD_Hot_Tepl_Kontur->Status=cSAlrNoSens;
			SetBit((*pGD_Hot_Tepl_Kontur).RCS,cbNoSensKontur);			
			SetNoWorkKontur();
			return;	
		}
		__sMinMaxWater(fnKontur);

	for(ByteY=0;ByteY<8;ByteY++)
		((char*)(&(pGD_Hot_Tepl_Kontur->Optimal)))[ByteY]=((char*)(&(GD.Hot.Tepl[pGD_TControl_Tepl_Kontur->MainTepl].Kontur[fnKontur].Optimal)))[ByteY];
	(*pGD_TControl_Tepl_Kontur).DoT=GD.TControl.Tepl[pGD_TControl_Tepl_Kontur->MainTepl].Kontur[fnKontur].DoT;
	(*pGD_TControl_Tepl_Kontur).PumpStatus=GD.TControl.Tepl[pGD_TControl_Tepl_Kontur->MainTepl].Kontur[fnKontur].PumpStatus;
		//GD.TControl.Tepl[cSmTeplB].Kontur[fnKontur].SErr=GD.TControl.Tepl[cSmTeplA].Kontur[fnKontur].SErr;
	if (pGD_TControl_Tepl_Kontur->DoT)
		pGD_Hot_Tepl_Kontur->Status=cSOn;

	if (YesBit(GD.Hot.Tepl[pGD_TControl_Tepl_Kontur->MainTepl].Kontur[fnKontur].ExtRCS,cbBlockPumpKontur))
	{
		pGD_Hot_Tepl_Kontur->Status=cSBlPump;
		SetBit((*pGD_Hot_Tepl_Kontur).ExtRCS,cbBlockPumpKontur);					
	}
	if (pGD_TControl_Tepl_Kontur->DoT/10==pGD_Hot_Tepl_Kontur->MaxCalc)
		pGD_Hot_Tepl_Kontur->Status=cSReachMax;

	if (pGD_TControl_Tepl_Kontur->DoT/10==pGD_Hot_Tepl_Kontur->MinCalc)
		pGD_Hot_Tepl_Kontur->Status=cSReachMin;

	if (pGD_Hot_Tepl_Kontur->Do)
		pGD_Hot_Tepl_Kontur->Status=cSFollowProg;

	if (pGD_Hot_Tepl_Kontur->MinCalc>pGD_Hot_Tepl_Kontur->MaxCalc-100)
		pGD_Hot_Tepl_Kontur->Status=cSWNoRange;
	if ((pGD_Hot_Tepl_Kontur->SensValue<pGD_Hot_Tepl_Kontur->MaxCalc-50)&&(pGD_Hot_Hand_Kontur->Position==100))
		pGD_Hot_Tepl_Kontur->Status=cSWNoHeat;
	if (YesBit(pGD_Hot_Hand_Kontur->RCS,cbManMech))
		pGD_Hot_Tepl_Kontur->Status=cSWHand;
	if (YesBit(pGD_Hot_Tepl->DiskrSens[0],cSmDHeat))
		pGD_Hot_Tepl_Kontur->Status=cSAlrExternal;


//	if (pGD_TControl_Tepl->Critery>0)
//		ClrBit(GD.Hot.Tepl[pGD_TControl_Tepl_Kontur->MainTepl].Kontur[fnKontur].RCS,cbMinusCritery);
//	if (pGD_TControl_Tepl->Critery<0)
//		ClrBit(GD.Hot.Tepl[pGD_TControl_Tepl_Kontur->MainTepl].Kontur[fnKontur].RCS,cbPlusCritery);

}
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/

/*************************************************************************/
/*-*-*-*-*-*--Процедура определения нерегулируемости для контура-*-*-*-*-*/
/*************************************************************************/
void __sRegulKontur(char fnKontur)
{

//------------------------------------------------------------------------
//Контура с выключенными насосами не участвуют в расчете или если не установлена аварийная граница	
//------------------------------------------------------------------------
#ifdef DEMO
	(*pGD_TControl_Tepl_Kontur).SErr=0;
	return;
#endif
	if ((!(*pGD_TControl_Tepl_Kontur).PumpStatus))
	{
		(*pGD_TControl_Tepl_Kontur).SErr=0;
		return;
	}
//------------------------------------------------------------------------
//Подсчет нерегулирумости для контура	
//------------------------------------------------------------------------

	IntX=(((*pGD_TControl_Tepl_Kontur).DoT/10))-pGD_TControl_Tepl_Kontur->SensValue;
	if (((IntX<0)&&(IntX>(-cErrKontur)))||((IntX<cErrKontur)&&(IntX>0)))
		IntX=0;
	LngX=IntX;

	if ((!IntX)||(!SameSign(IntX,pGD_TControl_Tepl_Kontur->SErr)))//(LngX*((long)((*pGD_TControl_Tepl_Kontur).SErr)))<0)))
		(*pGD_TControl_Tepl_Kontur).SErr=0;
	(*pGD_TControl_Tepl_Kontur).SErr+=IntX;

//------------------------------------------------------------------------
//Если общий, то взять нерегулируемость из теплицы А	
//------------------------------------------------------------------------
//	if (YesBit((*pGD_Hot_Tepl_Kontur).RCS,cbAndKontur))
	if	((&(pGD_TControl_Tepl_Kontur->SErr))!=(&GD.TControl.Tepl[pGD_TControl_Tepl_Kontur->MainTepl].Kontur[fnKontur].SErr));
		pGD_TControl_Tepl_Kontur->SErr=0;
//------------------------------------------------------------------------
//Проверяем на контрольную границу	
//------------------------------------------------------------------------
	if (((*pGD_TControl_Tepl_Kontur).SErr>=v_ControlMidlWater)||
		((*pGD_TControl_Tepl_Kontur).SErr<=-v_ControlMidlWater))
		SetBit((*pGD_Hot_Tepl_Kontur).ExtRCS,cbCtrlErrKontur);

//------------------------------------------------------------------------
//Проверяем на аварийную границу	
//------------------------------------------------------------------------

	if ((*pGD_TControl_Tepl_Kontur).SErr>=v_AlarmMidlWater)
	{
		SetBit((*pGD_Hot_Tepl_Kontur).ExtRCS,cbAlarmErrKontur);
		(*pGD_TControl_Tepl_Kontur).SErr=v_AlarmMidlWater;
	}
	if ((*pGD_TControl_Tepl_Kontur).SErr<=-v_AlarmMidlWater)
	{
		SetBit((*pGD_Hot_Tepl_Kontur).ExtRCS,cbAlarmErrKontur);
		(*pGD_TControl_Tepl_Kontur).SErr=-v_AlarmMidlWater;
	}
//------------------------------------------------------------------------
//Устанавливаем нерегулируемость в процентах со знаком
//------------------------------------------------------------------------
	
	IntY=(*pGD_TControl_Tepl_Kontur).SErr;
	CorrectionRule(v_ControlMidlWater,v_AlarmMidlWater,100,0);
	(*pGD_Hot_Tepl_Kontur).SError=(char)IntZ;
	if ((IntZ>cv_ResetMidlWater)&&(YesBit(pGD_TControl_Tepl->MechBusy[fnKontur].RCS,cMSBlockRegs)))
		SetBit((*pGD_Hot_Tepl_Kontur).ExtRCS,cbResetErrKontur);
	IntY=-IntY;
	CorrectionRule(v_ControlMidlWater,v_AlarmMidlWater,100,0);
	(*pGD_Hot_Tepl_Kontur).SError+=(char)IntZ;
	if ((IntZ>cv_ResetMidlWater)&&(YesBit(pGD_TControl_Tepl->MechBusy[fnKontur].RCS,cMSBlockRegs)))
		SetBit((*pGD_Hot_Tepl_Kontur).ExtRCS,cbResetErrKontur);


	
}
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/****************************************************************************/
/*Процедура опредления возможно ли работать экраном в данных условиях*/
/****************************************************************************/
/*void __sWorkableScreen(void)
{
//------------------------------------------------------------------------
//Если надо охлаждать
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//Установить возможности регулирования
//------------------------------------------------------------------------
	if (pGD_Hot_Tepl_Kontur->Do<pGD_Hot_Tepl_Kontur->MaxCalc)
		SetBit(pGD_Hot_Tepl_Kontur->ExtRCS,cbReadyRegDownKontur);
	else
		SetBit(pGD_Hot_Tepl_Kontur->RCS,cbYesMaxKontur);
//------------------------------------------------------------------------
//Если надо нагревать
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//Установить возможности регулирования
//------------------------------------------------------------------------
	if (pGD_Hot_Tepl_Kontur->Do>pGD_Hot_Tepl_Kontur->MinCalc)
		SetBit(pGD_Hot_Tepl_Kontur->ExtRCS,cbReadyRegUpKontur);
	else
		SetBit(pGD_Hot_Tepl_Kontur->RCS,cbYesMinKontur);


	
}  */
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/



/****************************************************************************/
/*Процедура опредления возможно ли работать фрамугами в данных условиях*/
/****************************************************************************/
/*void __sWorkableWindow(void)
{
//------------------------------------------------------------------------
//Если надо охлаждать
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//Установить возможности регулирования
//------------------------------------------------------------------------
	if ((pGD_Hot_Tepl->Kontur[cSmWindowUnW].Do<pGD_Hot_Tepl->Kontur[cSmWindowUnW].MaxCalc)
	  ||(pGD_Hot_Tepl->Kontur[cSmWindowOnW].Do<pGD_Hot_Tepl->Kontur[cSmWindowOnW].MaxCalc))
	  SetBit(pGD_Hot_Tepl->Kontur[cSmWindowUnW].ExtRCS,cbReadyRegDownKontur);
	else
		SetBit(pGD_Hot_Tepl->Kontur[cSmWindowUnW].RCS,cbYesMaxKontur);

//------------------------------------------------------------------------
//Если надо нагревать
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//Установить возможности регулирования
//------------------------------------------------------------------------
	if ((pGD_Hot_Tepl->Kontur[cSmWindowUnW].Do>pGD_Hot_Tepl->Kontur[cSmWindowUnW].MinCalc)
	  ||(pGD_Hot_Tepl->Kontur[cSmWindowOnW].Do>pGD_Hot_Tepl->Kontur[cSmWindowOnW].MinCalc))
		SetBit(pGD_Hot_Tepl->Kontur[cSmWindowUnW].ExtRCS,cbReadyRegUpKontur);
	else
		SetBit(pGD_Hot_Tepl->Kontur[cSmWindowUnW].RCS,cbYesMinKontur);

	
}
  */
/*************************************************************************/
/*-*-*-*-*-*-*-*-*--Потенциальный приоритет для контура--*-*-*-*-*-*-*-*-*/
/*************************************************************************/
/*#warning don't use now
void __sPotentialPosibilityKontur(char fInv)
{	
	int* pRealPower;
	pRealPower=&(pGD_TControl_Tepl_Kontur->RealPower[fInv]);
//------------------------------------------------------------------------
//Приоритет по температуре воздуха в теплице
//------------------------------------------------------------------------
	
//------------------------------------------------------------------------
//Приоритет по влажности воздуха в теплице
//------------------------------------------------------------------------
	IntY=10;//(int)pGD_Strategy_Kontur->RHPower;
	IntX=-DefRH();

	IntZ=(int)(((long)IntY)*IntX/1000);
//------------------------------------------------------------------------
//Приоритет по оптимальный температуре
//------------------------------------------------------------------------
	IntX=0;
	if ((*pGD_Hot_Tepl_Kontur).Optimal)
	{
		IntX=((*pGD_Hot_Tepl_Kontur).Optimal-(*pGD_Hot_Tepl_Kontur).Do);
//------------------------------------------------------------------------
//Если контур выключен то оптимальня температура сравнивается с минимумом контура
//------------------------------------------------------------------------
		IntY=0;//(int)pGD_Strategy_Kontur->OptimalPower;
		IntX=(int)(((long)IntY*IntX/100));
	}
	
//------------------------------------------------------------------------
//Приоритет с экономичностью
//------------------------------------------------------------------------
	
	(*pRealPower)=pGD_Strategy_Kontur->TempPower+IntX+IntZ;
	if ((*pRealPower)<1) (*pRealPower)=1; 
	if (!fInv)
	{
		(*pRealPower)=100-pGD_Strategy_Kontur->TempPower-IntX-IntZ;
		if ((*pRealPower)<1) (*pRealPower)=1; 
	}	
}
*/

int16_t getValueKonturStrategy(int16_t dT, int16_t dRH, int16_t dSystem)
{
	if ((dT>=0)&&(dRH>=0))
	{
		switch (dSystem)
		{
			case cSmKontur1: // reil
				return pGD_Strategy_Tepl->StratKontur1_1[0];
				//return pGD_Strategy_Kontur->StratKontur1_1[0];
			case cSmKontur2: // head
				return pGD_Strategy_Tepl->StratKontur2_1[0];
			//case cSmKontur3: // pipe
			//	return pGD_Strategy_Kontur->StratKontur3_1[0];
		}
	}
	if ((dT>=0)&&(dRH<0))
	{
		switch (dSystem)
		{
			case cSmKontur1: //0
				return pGD_Strategy_Tepl->StratKontur1_2[0];
			case cSmKontur2: //1
				return pGD_Strategy_Tepl->StratKontur2_2[0];
			//case cSmKontur3:  //2
			//	return pGD_Strategy_Kontur->StratKontur3_2[0];
		}
	}
	if ((dT<0)&&(dRH>=0))
	{
		switch (dSystem)
		{
			case cSmKontur1: //0
				return pGD_Strategy_Tepl->StratKontur1_3[0];
			case cSmKontur2: //1
				return pGD_Strategy_Tepl->StratKontur2_3[0];
			//case cSmKontur3:  //2
			//	return pGD_Strategy_Kontur->StratKontur3_3[0];
		}
	}
	if ((dT<0)&&(dRH<0))
	{
		switch (dSystem)
		{
			case cSmKontur1: //0
				return pGD_Strategy_Tepl->StratKontur1_4[0];
			case cSmKontur2: //1
				return pGD_Strategy_Tepl->StratKontur2_4[0];
			//case cSmKontur3:  //2
			//	return pGD_Strategy_Kontur->StratKontur3_4[0];
		}
	}
	return 0;
}

//void SetPriorityHeating(int16_t dT, int16_t dRH, int *dRealPower, int16_t kontur)
//{
//	int res =0;
//	res = getValueKonturStrategy(dT, dRH, kontur);
//	*dRealPower = res;
//}

int SetPriorityHeating(int16_t dT, int16_t dRH, int16_t kontur)
{
	int res =0;
	res = getValueKonturStrategy(dT, dRH, kontur);
	return res;
}

void __WorkableKontur(char fnKontur, char fnTepl)
{

//------------------------------------------------------------------------
//Внимание - нерегулируемость из-за ручного управления
//------------------------------------------------------------------------
		if (YesBit((*(pGD_Hot_Hand_Kontur+cHSmMixVal)).RCS,/*(cbNoMech+*/cbManMech))
			SetBit((*pGD_Hot_Tepl_Kontur).ExtRCS,cbAlarmErrKontur);

		IntY=GD.Hot.Tepl[pGD_TControl_Tepl_Kontur->MainTepl].HandCtrl[cHSmMixVal+fnKontur].Position;
	//------------------------------------------------------------------------
//Установить возможности регулирования
//------------------------------------------------------------------------
		if (((*pGD_Hot_Tepl_Kontur).Do<(*pGD_Hot_Tepl_Kontur).MaxCalc)
#ifndef DEMO
		  &&(!(YesBit((*pGD_Hot_Tepl_Kontur).ExtRCS,cbAlarmErrKontur)))
#endif
		  &&((*pGD_TControl_Tepl_Kontur).PumpStatus)
#ifndef DEMO
		  &&((IntY<100))
#endif
//Для защиты от перегрева рукава
		  &&((fnKontur!=cSmKontur3)||(pGD_Hot_Tepl->InTeplSens[cSmTAHUOutSens].Value-pGD_Hot_Tepl->AllTask.DoTHeat<200)))
//Конец защиты от перегрева рукава
			SetBit((*pGD_Hot_Tepl_Kontur).ExtRCS,cbReadyRegUpKontur);
//------------------------------------------------------------------------
//Установить бит возможности работы насосом
//------------------------------------------------------------------------
		if ((!(*pGD_TControl_Tepl_Kontur).PumpStatus)&&(pGD_TControl_Tepl->Critery>0)&&(fnKontur<cSmKontur5))
		{
			if  ((GD.Hot.MidlSR<GD.TuneClimate.f_MinSun)&&(pGD_Hot_Tepl->AllTask.NextTAir-GD.TControl.MeteoSensing[cSmOutTSens]>GD.TuneClimate.f_DeltaOut)||
			((getTempHeat(fnTepl)-(*pGD_Hot_Tepl).AllTask.DoTHeat)<0)&&(((pGD_Control_Tepl->c_PFactor%100)<90)||(pGD_TControl_Tepl->StopVentI>0)))
			{
				SetBit((*pGD_Hot_Tepl_Kontur).ExtRCS,cbReadyPumpKontur);
		    	if ((pGD_TControl_Tepl_Kontur->NAndKontur==1)&&(!pGD_TControl_Tepl->qMaxOwnKonturs)) pGD_TControl_Tepl_Kontur->RealPower[1]+=100;
			}
		}
//------------------------------------------------------------------------
//Если надо охлаждать и включен насос
//------------------------------------------------------------------------
		if (pGD_TControl_Tepl_Kontur->PumpStatus)
		{
//------------------------------------------------------------------------
//Установить возможности регулирования
//------------------------------------------------------------------------
			if (((*pGD_Hot_Tepl_Kontur).Do>(*pGD_Hot_Tepl_Kontur).MinCalc)
#ifndef DEMO
		  		&&(!(YesBit((*pGD_Hot_Tepl_Kontur).ExtRCS,cbAlarmErrKontur)))
				&&(IntY>0))
#endif
				SetBit((*pGD_Hot_Tepl_Kontur).ExtRCS,cbReadyRegDownKontur);
//------------------------------------------------------------------------
//Установить возможности работы насосом
//------------------------------------------------------------------------
			if ((!(YesBit((*pGD_Hot_Tepl_Kontur).ExtRCS,cbReadyRegDownKontur)))
		  	&&(!(YesBit((*pGD_Hot_Tepl_Kontur).ExtRCS,cbBlockPumpKontur)))
		  	&&(!pGD_TControl_Tepl_Kontur->PumpPause)&&(pGD_TControl_Tepl->Critery<0)&&(!IntY)&&(GD.TControl.MeteoSensing[cSmOutTSens]>500))
				SetBit((*pGD_Hot_Tepl_Kontur).ExtRCS,cbReadyPumpKontur);
		}
  
	if ((YesBit(pGD_Hot_Tepl_Kontur->ExtRCS,cbReadyRegDownKontur))&&(pGD_TControl_Tepl->Critery<0))
			SetBit(pGD_Hot_Tepl_Kontur->ExtRCS,cbReadyRegsKontur);
	if ((YesBit(pGD_Hot_Tepl_Kontur->ExtRCS,cbReadyRegUpKontur))&&(pGD_TControl_Tepl->Critery>0))
			SetBit(pGD_Hot_Tepl_Kontur->ExtRCS,cbReadyRegsKontur);

		
}
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/


/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/


/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/

/*************************************************************************/
/*-Процедура определения приоритетов с возможностями и подсчета их суммы-*/
/*************************************************************************/
void __sRealPosibilityKonturs(char fnKontur,long* fMinMax)
{
	ByteZ=0;

//------------------------------------------------------------------------
//Если контур не участвует в управлении то пропускаем 
//------------------------------------------------------------------------


	if (!(YesBit((*pGD_Hot_Tepl_Kontur).ExtRCS,(cbReadyRegUpKontur+cbReadyPumpKontur))))
		pGD_TControl_Tepl_Kontur->RealPower[1]=0;
	if (!(YesBit((*pGD_Hot_Tepl_Kontur).ExtRCS,(cbReadyRegDownKontur+cbReadyPumpKontur))))
		pGD_TControl_Tepl_Kontur->RealPower[0]=0;

	if	(!(YesBit((*pGD_Hot_Tepl_Kontur).ExtRCS,(cbReadyPumpKontur+cbReadyRegsKontur)))) 
		return;//ByteZ;

	


//------------------------------------------------------------------------
//Если надо охлаждать то меняем знак экономического приоритета для того 
//чтобы он в положительной оси отображал желание рабоать, а в отрицательной - нежелание
//------------------------------------------------------------------------
//	if (pGD_TControl_Tepl->Critery<0)	

	
//------------------------------------------------------------------------
//Меняем приоритеты регулирующих контуров в зависимости от нерегулируемости 
//------------------------------------------------------------------------

	if	(YesBit(pGD_Hot_Tepl_Kontur->ExtRCS,cbReadyRegsKontur))
	{
		if (pGD_TControl_Tepl_Kontur->NAndKontur==1)
		{
			pGD_TControl_Tepl->NOwnKonturs++;
		}
//------------------------------------------------------------------------
//Ищем максимальный приоритет контуров и запоминаем его номер
//------------------------------------------------------------------------
	}

			
	if (fMinMax[0]<(*pGD_TControl_Tepl_Kontur).RealPower[pGD_TControl_Tepl->CurrPower])
	{
		fMinMax[0]=(*pGD_TControl_Tepl_Kontur).RealPower[pGD_TControl_Tepl->CurrPower];	
		pGD_TControl_Tepl->nMaxKontur=fnKontur;
	}		
	if ((fMinMax[1]<(*pGD_TControl_Tepl_Kontur).RealPower[pGD_TControl_Tepl->CurrPower])
		&&(!YesBit((*pGD_Hot_Tepl_Kontur).ExtRCS,cbReadyPumpKontur)))
	{
		fMinMax[1]=(*pGD_TControl_Tepl_Kontur).RealPower[pGD_TControl_Tepl->CurrPower];	
	}
	if ((fMinMax[2]<(*pGD_TControl_Tepl_Kontur).RealPower[pGD_TControl_Tepl->CurrPower])
		&&(pGD_TControl_Tepl_Kontur->NAndKontur==1)&&(!YesBit((*pGD_Hot_Tepl_Kontur).ExtRCS,cbReadyPumpKontur)))
	{
		fMinMax[2]=(*pGD_TControl_Tepl_Kontur).RealPower[pGD_TControl_Tepl->CurrPower];	

	}		

//------------------------------------------------------------------------
//Если есть отрицательные приоритеты то их надо установить в 0 
//------------------------------------------------------------------------


//------------------------------------------------------------------------
//Если работаем насосами то надо сбросить приоритет
//------------------------------------------------------------------------



}
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*************************************************************************/
/*-*-*-*-*--Процедура распределения критерия на данный контур--*-*-*-*-*-*/
/*************************************************************************/
long __sRaspKontur(void)
{	
	if ((!pGD_TControl_Tepl->qMaxKonturs)||(!YesBit(pGD_Hot_Tepl_Kontur->RCS,cbGoMax))) return 0;

	pGD_TControl_Tepl->StopI=0;

	LngY=pGD_TControl_Tepl->Critery;
	LngY=LngY/pGD_TControl_Tepl->qMaxKonturs;

	LngY=LngY*50;//((long)pGD_ConstMechanic->ConstMixVal[cSmKontur1].Power);
	LngY=LngY/50;//((long)pGD_Strategy_Kontur->Powers);

	return LngY;
}
long __sRaspOwnKontur(void)
{	
	if ((!pGD_TControl_Tepl->qMaxOwnKonturs)||(!YesBit(pGD_Hot_Tepl_Kontur->RCS,cbGoMaxOwn))) return 0;
	LngY=pGD_TControl_Tepl->Critery;
	LngY=LngY/pGD_TControl_Tepl->qMaxOwnKonturs;

	LngY=LngY*50;//((long)pGD_ConstMechanic->ConstMixVal[cSmKontur1].Power);
	LngY=LngY/50;//((long)pGD_Strategy_Kontur->Powers);


	return LngY;
}

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
long __TempToVent1(void)
{	
	LngY=100*((long)pGD_TControl_Tepl->TVentCritery);
	LngY=LngY/50;
	LngY=LngY*30;
	LngY/=((long)pGD_TControl_Tepl->f_Power);

	return LngY;
}
long __VentToTemp1(long sVent)
{	
	LngY=sVent*((long)pGD_TControl_Tepl->f_Power);
	LngY/=30;
	LngY*=50;//((long)pGD_ConstMechanic->ConstMixVal[cHSmWinN].Power);
	return LngY/100;
}



/*************************************************************************/
/*-*-*-*-*-*-*-*-*--Процедура завершающей проверки фрамуг--*-*-*-*-*-*-*-*/
/*************************************************************************/
void __sLastCheckWindow(void)
{
	int16_t	xdata	DoUn=0;
	int16_t xdata	DoOn=0;
	int16_t xdata	tDo;
//	long xdata	tCalc;

	int16_t xdata	MinUn;
	int16_t xdata	MinOn;
	int16_t xdata	MaxUn;
	int16_t xdata	MaxOn;
	int16_t	xdata 	tMaximum;
	int16_t	xdata 	tSLevel;
	

//	MinOn=pGD_Hot_Tepl->Kontur[cSmAHUSpd].MinCalc;
	MinUn=pGD_Hot_Tepl->Kontur[cSmWindowUnW].MinCalc;
//	MaxOn=pGD_Hot_Tepl->Kontur[cSmAHUSpd].MaxCalc;
	MaxUn=pGD_Hot_Tepl->Kontur[cSmWindowUnW].MaxCalc;

/*	tDo=pGD_TControl_Tepl->Kontur[cSmWindowUnW].DoT;//+pGD_TControl_Tepl->Kontur[cSmAHUSpd].DoT;

	IntY=(*pGD_TControl_Tepl).Kontur[cSmWindowUnW].CalcT;
	if (IntY<0) IntY=0;
	tSLevel=GD.TuneClimate.f_S3MinDelta;
	if (tDo<GD.TuneClimate.f_S3Level)
		tSLevel=GD.TuneClimate.f_S2MinDelta;
	if (tDo<GD.TuneClimate.f_S2Level)
		tSLevel=GD.TuneClimate.f_S1MinDelta;
	if (tDo<GD.TuneClimate.f_S1Level)
		tSLevel=GD.TuneClimate.f_MinDelta;

	if (IntY-tDo>tSLevel)
		tDo+=tSLevel;
	else
		if (tDo-IntY>tSLevel)
			tDo-=tSLevel;
		else
			tDo=IntY;

	DoUn=tDo;*/

/*	IntY=GD.TuneClimate.f_DefOnUn;
//	if (MaxUn<IntY) IntY=MaxUn;
	if (tDo<IntY)
	{
		DoUn=tDo;
		DoOn=0;
	}
	else
	{
	    tDo-=IntY;
		DoUn=IntY+tDo/2;
		DoOn=tDo/2;
	}
	if (DoUn>MaxUn)
		DoOn+=DoUn-MaxUn;
	if (DoOn>MaxOn)
		DoUn+=DoOn-MaxOn;
*/

/*	DoUn=(*pGD_TControl_Tepl).Kontur[cSmWindowUnW].CalcT;
//	if (DoOn<MinOn)
//		DoOn=MinOn;
	if (DoUn<MinUn)  
		DoUn=MinUn;

	if (DoUn>MaxUn) 
		DoUn=MaxUn;
//	if (DoOn>MaxOn)
//		DoOn=MaxOn;

/*   	IntY=CURRENT_TEMP_VALUE-(*pGD_Hot_Tepl).AllTask.DoTVent;
	if (((DoUn==MaxUn)&&(IntY>0))
	|| ((DoUn==MinUn)&&(IntY<0)))
*/
	pGD_TControl_Tepl->Kontur[cSmWindowUnW].DoT=DoUn;

	//pGD_TControl_Tepl->Kontur[cSmAHUSpd].DoT=DoOn;

	//pGD_Hot_Tepl->Kontur[cSmWindowUnW].Do=(*pGD_TControl_Tepl).Kontur[cSmWindowUnW].CalcT;  // было так
	pGD_Hot_Tepl->Kontur[cSmWindowUnW].Do=pGD_TControl_Tepl->Systems[cSysUCValve].Keep;  // last

//	IntX=pGD_Hot_Tepl->InTeplSens[].Value
//	SetPID()
	//pGD_Hot_Tepl->Kontur[cSmAHUSpd].Do=(DoOn);

}
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/



/*************************************************************************/
/*-*-*-*-*-*-*-*-*--Процедура завершающей проверки экрана--*-*-*-*-*-*-*-*/
/*************************************************************************/
/*void __sLastCheckScreen(void)
{
	pGD_TControl_Tepl->Kontur[cSmScreen].DoT-=pGD_TControl_Tepl->Kontur[cSmScreen].CalcT/100;	
	pGD_Hot_Tepl_Kontur->Do=(int)(pGD_TControl_Tepl_Kontur->DoT/10);		
	if ((*pGD_Hot_Tepl_Kontur).Do<(*pGD_Hot_Tepl_Kontur).MinCalc)
	{
		pGD_Hot_Tepl_Kontur->Do=pGD_Hot_Tepl_Kontur->MinCalc;
		pGD_TControl_Tepl_Kontur->DoT=(pGD_Hot_Tepl_Kontur->Do)*10;
	}
	if (pGD_Hot_Tepl_Kontur->Do>pGD_Hot_Tepl_Kontur->MaxCalc)
	{
		pGD_Hot_Tepl_Kontur->Do=pGD_Hot_Tepl_Kontur->MaxCalc;
		pGD_TControl_Tepl_Kontur->DoT=(pGD_Hot_Tepl_Kontur->Do)*10;
	}

} */
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*****************************************************************************/
/*Процедура преобразования значений температуры в температуру первого контура*/
/*****************************************************************************/
long __sThisToFirst(int in)
{
//	if (YesBit(pGD_Hot_Tepl_Kontur->RCS,cbScreenKontur)) return 0;
	return(((((long)in)*((long)50/*pGD_Strategy_Kontur->Powers*/))/50));
/********************************************************************
-----------Работа автонастройки временно приостановлена--------------
*********************************************************************
*1000/pGD_TControl_Tepl->sac_MomentMull)*1000/pGD_TControl_Tepl->sac_LongMull[0]);	
*********************************************************************/
}

/**************************************************************************/
/*-*-*-*-*-*-*-*-*--Процедура завершающей проверки контура--*-*-*-*-*-*-*-*/
/**************************************************************************/
void __sLastCheckKontur(char fnKontur,int* fnCorCritery)
{
	int OldDoT;
	long TempDo;	
	*fnCorCritery=0;



	if(YesBit((*pGD_Hot_Tepl_Kontur).ExtRCS,cbBlockPumpKontur)) 
		(*pGD_TControl_Tepl_Kontur).PumpStatus=1;
	
	if	(!(*pGD_TControl_Tepl_Kontur).PumpStatus)
	{
/*		if((*pGD_TControl_Tepl_Kontur).DoT)
			(*fnCorCritery)+=((int)((*pGD_TControl_Tepl_Kontur).DoT/100)-GD.Hot.Tepl[fnTepl].AllTask.DoTHeat/10);*/
		(*pGD_TControl_Tepl_Kontur).DoT=0;
		(*pGD_Hot_Tepl_Kontur).Do=0;
		return;
				
	}
	//SetBit((*pGD_Hot_Tepl_Kontur).RCS,cbOnPumpKontur);
	
	if ((*pGD_TControl_Tepl_Kontur).Manual) return;

	
	if ((!SameSign(pGD_TControl_Tepl->Critery,pGD_TControl_Tepl_Kontur->SErr))
		&&(YesBit((*pGD_Hot_Tepl_Kontur).ExtRCS,cbResetErrKontur)))
	{
		OldDoT=pGD_TControl_Tepl_Kontur->DoT;
		pGD_Hot_Tepl_Kontur->Do=((pGD_TControl_Tepl_Kontur->SensValue));
		ogrMin(&(pGD_Hot_Tepl_Kontur->Do),(*pGD_Hot_Tepl_Kontur).MinCalc);
		ogrMax(&(pGD_Hot_Tepl_Kontur->Do),(*pGD_Hot_Tepl_Kontur).MaxCalc);
		TempDo=pGD_Hot_Tepl_Kontur->Do*10;
		pGD_TControl_Tepl_Kontur->SErr=0;
		pGD_TControl_Tepl->Integral-=__sThisToFirst((int)((OldDoT-TempDo)))*100;
	//	(*pGD_TControl_Tepl).SaveIntegral-=__sThisToFirst((int)((OldDoT-TempDo)))*100;
		pGD_TControl_Tepl_Kontur->DoT=TempDo;
		return;
	}
	if ((!(*pGD_TControl_Tepl_Kontur).DoT)&&((*pGD_TControl_Tepl_Kontur).LastDoT<5000))
		 (*pGD_TControl_Tepl_Kontur).DoT=(*pGD_TControl_Tepl_Kontur).LastDoT;
	(*pGD_TControl_Tepl_Kontur).DoT=(*pGD_TControl_Tepl_Kontur).DoT+(int)((*pGD_TControl_Tepl_Kontur).CalcT);
	(*pGD_Hot_Tepl_Kontur).Do=((*pGD_TControl_Tepl_Kontur).DoT/10);

	if ((*pGD_Hot_Tepl_Kontur).Do<=(*pGD_Hot_Tepl_Kontur).MinCalc)
	{
		(*pGD_TControl_Tepl_Kontur).DoT=((((*pGD_Hot_Tepl_Kontur).MinCalc)))*10;
	}
	if ((*pGD_Hot_Tepl_Kontur).Do>=(*pGD_Hot_Tepl_Kontur).MaxCalc)
	{
		(*pGD_TControl_Tepl_Kontur).DoT=((((*pGD_Hot_Tepl_Kontur).MaxCalc)))*10;
	}
//	if ((*pGD_Hot_Tepl_Kontur).Do<pGD_Hot_Tepl->AllTask.DoTHeat/10)
//		(*pGD_Hot_Tepl_Kontur).Do=(*pGD_Hot_Tepl_Kontur).MinCalc;//GD.Hot.Tepl[fnTepl].AllTask.DoTHeat/10;

//	(*fnCorCritery)+=((*pGD_Hot_Tepl_Kontur).Do-((*pGD_TControl_Tepl_Kontur).DoT/10));
	(*pGD_Hot_Tepl_Kontur).Do=((*pGD_TControl_Tepl_Kontur).DoT/10);

	(*pGD_TControl_Tepl_Kontur).LastDoT=(*pGD_TControl_Tepl_Kontur).DoT;

}
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/


/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/

int __sCalcTempKonturs(void)
{
	int SumTemp=0;
		for(ByteX=0;ByteX<cSWaterKontur-2;ByteX++)
		{
		    SetPointersOnKontur(ByteX);
			if 	(ByteX==cSmKontur3) continue;
			if (pGD_TControl_Tepl_Kontur->DoT)
				SumTemp+=__sThisToFirst(pGD_TControl_Tepl_Kontur->DoT)-pGD_Hot_Tepl->AllTask.DoTHeat;
			else
				if ((pGD_TControl_Tepl_Kontur->LastDoT<5000)&&(pGD_TControl_Tepl_Kontur->LastDoT>pGD_Hot_Tepl->AllTask.DoTHeat))
					 SumTemp+=__sThisToFirst(pGD_TControl_Tepl_Kontur->LastDoT)-pGD_Hot_Tepl->AllTask.DoTHeat;
		}
	return SumTemp;
	}


#ifdef AHU1
void __InitAHUSystem(int16_t DifT,int16_t DifH)
{
	pGD_TControl_Tepl->Systems[cSysAHUPipe].Value=pGD_Hot_Tepl->InTeplSens[cSmAHUPipeSens].Value;

	pGD_TControl_Tepl->Systems[cSysRailPipe].Value=pGD_Hot_Tepl->InTeplSens[cSmRailPipeSens].Value;

	pGD_TControl_Tepl->Systems[cSysHeadPipe].Value=pGD_Hot_Tepl->InTeplSens[cSmHeadPipeSens].Value;

	pGD_TControl_Tepl->Systems[cSysSidePipe].Value=pGD_Hot_Tepl->InTeplSens[cSmSidePipeSens].Value;

	pGD_TControl_Tepl->Systems[cSysUCValve].Value=pGD_Hot_Hand[cHSmUCValve].Position;

	pGD_TControl_Tepl->Systems[cSysScreen].Value=pGD_Hot_Hand[cHSmScrTH].Position;

	pGD_TControl_Tepl->Systems[cSysAHUSpeed].Value=pGD_Hot_Hand[cHSmAHUSpeed1].Position;

	//pGD_TControl_Tepl->Systems[cSysMist].Value=pGD_Hot_Hand[cHSmAHUSpeed1].Position;



	for (ByteX=0;ByteX<cSUCSystems;ByteX++)
	{
		//Calculation of Min and Max
		pGD_TControl_Tepl->Systems[ByteX].Max=pGD_Control_Tepl->cMaxSystem[ByteX];
		pGD_TControl_Tepl->Systems[ByteX].Opt=pGD_Control_Tepl->cOptSystem[ByteX];
		pGD_TControl_Tepl->Systems[ByteX].Min=pGD_Control_Tepl->cMinSystem[ByteX];

		if (pGD_TControl_Tepl->Systems[ByteX].Keep>pGD_TControl_Tepl->Systems[ByteX].Max)
			pGD_TControl_Tepl->Systems[ByteX].Keep=pGD_TControl_Tepl->Systems[ByteX].Max;

		if (ByteX<cSPipeSystems)
		{
			if (!pGD_TControl_Tepl->Systems[ByteX].Min) pGD_TControl_Tepl->Systems[ByteX].Min=pGD_Hot_Tepl->AllTask.DoTHeat;

		}

		if (pGD_TControl_Tepl->Systems[ByteX].Keep<pGD_TControl_Tepl->Systems[ByteX].Min)
			pGD_TControl_Tepl->Systems[ByteX].Keep=pGD_TControl_Tepl->Systems[ByteX].Min;

		pGD_TControl_Tepl->Systems[ByteX].Time=pGD_Strategy_Tepl[ByteX].Time;
		//Calculation of current power
		if (pGD_Strategy_Tepl[ByteX].Point2-pGD_Strategy_Tepl[ByteX].Point1)
			pGD_TControl_Tepl->Systems[ByteX].Power=pGD_Strategy_Tepl[ByteX].Power1+((pGD_TControl_Tepl->Systems[ByteX].Keep-pGD_Strategy_Tepl[ByteX].Point1)*(pGD_Strategy_Tepl[ByteX].Power2-pGD_Strategy_Tepl[ByteX].Power1))/(pGD_Strategy_Tepl[ByteX].Point2-pGD_Strategy_Tepl[ByteX].Point1);
		if (pGD_TControl_Tepl->Systems[ByteX].Keep>=pGD_Strategy_Tepl[ByteX].Point2)
			pGD_TControl_Tepl->Systems[ByteX].Power=pGD_Strategy_Tepl[ByteX].Power2;
		if (pGD_TControl_Tepl->Systems[ByteX].Keep<=pGD_Strategy_Tepl[ByteX].Point1)
			pGD_TControl_Tepl->Systems[ByteX].Power=pGD_Strategy_Tepl[ByteX].Power1;
		//Calculation of system delay
		if (pGD_TControl_Tepl->Systems[ByteX].tTime>pGD_TControl_Tepl->Systems[ByteX].Time)
			pGD_TControl_Tepl->Systems[ByteX].tTime=pGD_TControl_Tepl->Systems[ByteX].Time;
		if ((DifT>=0)&&(DifH>=0))
			pGD_TControl_Tepl->Systems[ByteX].Prior=pGD_Strategy_Tepl[ByteX].TUpRHUp;
		if ((DifT>=0)&&(DifH<0))
			pGD_TControl_Tepl->Systems[ByteX].Prior=pGD_Strategy_Tepl[ByteX].TUpRHDown;
		if ((DifT<0)&&(DifH>=0))
			pGD_TControl_Tepl->Systems[ByteX].Prior=pGD_Strategy_Tepl[ByteX].TDownRHUp;
		if ((DifT<0)&&(DifH<0))
			pGD_TControl_Tepl->Systems[ByteX].Prior=pGD_Strategy_Tepl[ByteX].TDownRHDown;
		if (pGD_TControl_Tepl->Systems[ByteX].tTime)
		{
			pGD_TControl_Tepl->Systems[ByteX].tTime--;
			pGD_TControl_Tepl->Systems[ByteX].Prior=0;
		}

	}
}

void __MinMaxAHUSystem(void)
{

}

void __RegulAHUSystem(void)
{
	for (ByteX=0;ByteX<cSUCSystems;ByteX++)
	{
		if ((pGD_TControl_Tepl->Systems[ByteX].Prior>0)&&(pGD_TControl_Tepl->Systems[ByteX].Keep>=pGD_TControl_Tepl->Systems[ByteX].Max))
			pGD_TControl_Tepl->Systems[ByteX].Prior=0;
		if ((pGD_TControl_Tepl->Systems[ByteX].Prior<0)&&(pGD_TControl_Tepl->Systems[ByteX].Keep<=pGD_TControl_Tepl->Systems[ByteX].Min))
			pGD_TControl_Tepl->Systems[ByteX].Prior=0;

	}
}

void __CheckMaxSystem(void)
{
	int16_t MaxPrior=0;
	int8_t	nSyst=-1;
	for (ByteX=0;ByteX<cSUCSystems;ByteX++)
	{
		if (abs(pGD_TControl_Tepl->Systems[ByteX].Prior)>MaxPrior)
		{
			MaxPrior=pGD_TControl_Tepl->Systems[ByteX].Prior;
			nSyst=ByteX;
		}
	}
	pGD_TControl_Tepl->MaxSystem=nSyst;
}

void __SendCritery(int16_t *Crit)
{
	int16_t tFreeCrit;
	int8_t tSign;
	if (pGD_TControl_Tepl->MaxSystem>=0)
	{
		if (pGD_TControl_Tepl->Systems[pGD_TControl_Tepl->MaxSystem].Prior>0)
			tSign=1;
		if (pGD_TControl_Tepl->Systems[pGD_TControl_Tepl->MaxSystem].Prior<0)
			tSign=-1;
		pGD_TControl_Tepl->Systems[pGD_TControl_Tepl->MaxSystem].Keep+=tSign*(*Crit)*pGD_TControl_Tepl->Systems[pGD_TControl_Tepl->MaxSystem].Power/1000;
		(*Crit)=0;
	}
	if (pGD_TControl_Tepl->Systems[pGD_TControl_Tepl->MaxSystem].Keep>pGD_TControl_Tepl->Systems[pGD_TControl_Tepl->MaxSystem].Max)
	{
		(*Crit)=(pGD_TControl_Tepl->Systems[pGD_TControl_Tepl->MaxSystem].Max-pGD_TControl_Tepl->Systems[pGD_TControl_Tepl->MaxSystem].Keep)
				*1000/pGD_TControl_Tepl->Systems[pGD_TControl_Tepl->MaxSystem].Power;
		pGD_TControl_Tepl->Systems[pGD_TControl_Tepl->MaxSystem].Keep=pGD_TControl_Tepl->Systems[pGD_TControl_Tepl->MaxSystem].Max;
	}
	if (pGD_TControl_Tepl->Systems[pGD_TControl_Tepl->MaxSystem].Keep<pGD_TControl_Tepl->Systems[pGD_TControl_Tepl->MaxSystem].Min)
	{
		(*Crit)=(pGD_TControl_Tepl->Systems[pGD_TControl_Tepl->MaxSystem].Min-pGD_TControl_Tepl->Systems[pGD_TControl_Tepl->MaxSystem].Keep)
				*1000/pGD_TControl_Tepl->Systems[pGD_TControl_Tepl->MaxSystem].Power;
		pGD_TControl_Tepl->Systems[pGD_TControl_Tepl->MaxSystem].Keep=pGD_TControl_Tepl->Systems[pGD_TControl_Tepl->MaxSystem].Min;
	}

}

#endif

// вывод значений критерия
uint16_t	CriterT1Out[8];
uint16_t CriterT2Out[8];
uint16_t CriterT3Out[8];

void TakeCriterForOut(int16_t Criter1, int16_t Criter2, int16_t Criter3, char fnTepl)
{
	CriterT1Out[fnTepl] = Criter1;
	CriterT2Out[fnTepl] = Criter2;
	CriterT3Out[fnTepl] = Criter3;
}

/*************************************************************************/
/*-*-*-*-*-*-*-*-*--Процедура начальных установок для контура--*-*-*-*-*-*/
/*************************************************************************/
void __sCalcKonturs(void)
{
	long MinMaxPowerReg[3];
	long xdata temp;
	int	 OldCrit;
	int16_t	CriterT,CriterRH;
	char isFram;
	char fnTepl,tTepl;
	
	for(fnTepl=0;fnTepl<cSTepl;fnTepl++)
	{
		SetPointersOnTepl(fnTepl);

//		if(!(*pGD_Hot_Tepl).AllTask.NextTAir) return;

//Определение направления нагрев аили охлаждени
		pGD_TControl_Tepl->CurrPower=0;
		if (pGD_TControl_Tepl->Critery>0)
			pGD_TControl_Tepl->CurrPower=1;
// Отключить, если нет задания
		if(!pGD_Hot_Tepl->AllTask.DoTHeat) continue;
// Расчет минимумов и максимумов контуров
		for(ByteX=0;ByteX<cSWaterKontur;ByteX++)
		{
			SetPointersOnKontur(ByteX);
			ClrDog;
			__sInitKontur(ByteX);
		}
//		__sMinMaxScreen();
// Расчет минимумов и максимумов фрамуг 
		__sMinMaxWindows(fnTepl);
#ifdef AHU1
		__InitAHUSystems();
#endif
	}
// Заново считаем 
	for(fnTepl=0;fnTepl<cSTepl;fnTepl++)
	{
		SetPointersOnTepl(fnTepl);

		MinMaxPowerReg[2]=0;
		MinMaxPowerReg[1]=0;
		MinMaxPowerReg[0]=0;
		(*pGD_TControl_Tepl).nMaxKontur=-1;
		ClrDog;
		(*pGD_TControl_Tepl).NOwnKonturs=0;
		if(!GD.Hot.Tepl[fnTepl].AllTask.DoTHeat) continue;
		for(ByteX=0;ByteX<cSWaterKontur;ByteX++)
		{
			SetPointersOnKontur(ByteX);
			__sRegulKontur(ByteX);
			pGD_TControl_Tepl_Kontur->Manual=0;
			ClrDog;
			if ((ByteX==cSmKontur3)||(ByteX==cSmKonturAHU)) continue;
			if 	(YesBit(pGD_Hot_Tepl_Kontur->RCS,cbNoWorkKontur)) continue;
			if 	(pGD_Hot_Tepl_Kontur->Do)
			{
				pGD_TControl_Tepl_Kontur->PumpStatus=1;
				pGD_TControl_Tepl_Kontur->Manual=1;
				pGD_TControl_Tepl_Kontur->DoT=(pGD_Hot_Tepl_Kontur->Do*10);
				continue;
			}
			pGD_Hot_Tepl_Kontur->Do=(pGD_TControl_Tepl_Kontur->DoT/10);
			ClrDog;
			//__sPotentialPosibilityKontur(0);//Приоритет в случае охлаждения   // NEW strat
			//SetPriorityHeating(-1,DefRH(),&pGD_TControl_Tepl_Kontur->RealPower[0], ByteX);
			// 46 именение было 0 и 1 стало 1 и 0
			pGD_TControl_Tepl_Kontur->RealPower[1] = SetPriorityHeating(-1,DefRH(fnTepl),ByteX);

			//__sPotentialPosibilityKontur(1);//Приоритет в случае нагрева
			//SetPriorityHeating(1,DefRH(),&pGD_TControl_Tepl_Kontur->RealPower[1], ByteX);

			pGD_TControl_Tepl_Kontur->RealPower[0] = SetPriorityHeating(1,DefRH(fnTepl),ByteX);
			ClrDog;

			__WorkableKontur(ByteX,fnTepl);
			__sRealPosibilityKonturs(ByteX,MinMaxPowerReg);
			(*pGD_Hot_Tepl_Kontur).Priority=(int)(pGD_TControl_Tepl_Kontur->RealPower[pGD_TControl_Tepl->CurrPower]);
			pGD_TControl_Tepl->PowMaxKonturs=MinMaxPowerReg[1];
			pGD_TControl_Tepl->PowOwnMaxKonturs=MinMaxPowerReg[2];
		}

//		if ((GD.TControl.PrevPozFluger!=GD.Hot.PozFluger)&&(GD.TuneClimate.f_changeWindows))
//		{
//			temp=(*pGD_TControl_Tepl).Kontur[cSmWindowOnW].DoT;				
//			(*pGD_TControl_Tepl).Kontur[cSmWindowOnW].DoT=(*pGD_TControl_Tepl).Kontur[cSmWindowUnW].DoT;
//			(*pGD_TControl_Tepl).Kontur[cSmWindowUnW].DoT=temp;
//			
//		}
//		(*pGD_Hot_Tepl).Kontur[cSmWindowOnW].Do=((*pGD_TControl_Tepl).Kontur[cSmWindowOnW].DoT/10);			

//		__sWorkableWindow();
				
//		pGD_TControl_Tepl->Kontur[cSmWindowUnW].CalcT=0;

		pGD_Hot_Tepl->Kontur[cSmWindowUnW].Optimal=pGD_TControl_Tepl->f_NMinDelta;	
//Работа Т-вентиляции
		CheckScreenSystem();
		CheckAHUPipeSystem();
		CheckUCValveSystem(getTempHeat(fnTepl), GD.Hot.Tepl[fnTepl].AllTask.DoTHeat);
		CheckFanSystem();
		CheckInRHSystem();

//		CheckMistSystem(); 					// убрал временно вернуть
		CheckMistSystemNew(fnTepl);
//		CriterT=getTempVent(fnTepl)-GD.Hot.Tepl[fnTepl].AllTask.DoTVent;
//		CriterRH=DefRH();
//#warning Only f check
//		if (pGD_Strategy_Tepl[cSmKontur3].TempPower==22)
		//{
			//GD.Hot.Tepl[fnTepl].InTeplSens[cSmTAHUOutSens].Value
			//GD.uInTeplSens[fnTepl][cSmTAHUOutSens]
			//TakeCriterForOut(GD.Hot.Tepl[fnTepl].InTeplSens[cSmTAHUOutSens].Value,GD.Hot.Tepl[fnTepl].NextTCalc.TVentCritery, GD.Hot.Tepl[fnTepl].AllTask.DoTVent, fnTepl);
			TakeCriterForOut(pGD_Hot_Tepl->InTeplSens[cSmTAHUOutSens].Value,GD.Hot.Tepl[fnTepl].NextTCalc.TVentCritery, GD.Hot.Tepl[fnTepl].AllTask.DoTVent, fnTepl);

			CriterT = pGD_Hot_Tepl->InTeplSens[cSmTAHUOutSens].Value-GD.Hot.Tepl[fnTepl].NextTCalc.TVentCritery;  // было на 20 апреля

			//CriterT = GD.Hot.Tepl[fnTepl].InTeplSens[cSmTAHUOutSens].Value - GD.Hot.Tepl[fnTepl].NextTCalc.TVentCritery;
			//CriterRH=(*pGD_Hot_Tepl).InTeplSens[cSmRHAHUOutSens].Value-(*pGD_Hot_Tepl).NextTCalc.ICorrectionVent;  // старый коммент


			CriterRH = pGD_Hot_Tepl->InTeplSens[cSmRHAHUOutSens].Value-(*pGD_Hot_Tepl).NextTCalc.ICorrectionVent;
			//CriterRH = GD.Hot.Tepl[fnTepl].InTeplSens[cSmTAHUOutSens].Value-(*pGD_Hot_Tepl).NextTCalc.ICorrectionVent;

		//}

		(*pGD_TControl_Tepl).Kontur[cSmWindowUnW].CalcT=pGD_Hot_Tepl->NextTCalc.TVentCritery-__MechToVentTemp();
#warning check GD.Hot.Tepl[fnTepl].AllTask.DoTVent
		//if ((getTempVent(fnTepl)!=0) && (GD.Hot.Tepl[fnTepl].AllTask.DoTVent !=0))
		// изменеие 100. Вместо getTempVent делаем getTempHeat
		//if ((getTempVent(fnTepl)!=0) && (GD.Hot.Tepl[fnTepl].AllTask.DoTVent !=0) && (getTempOutAHU(fnTepl)!=0) )
		if ((getTempHeat(fnTepl)!=0) && (GD.Hot.Tepl[fnTepl].AllTask.DoTVent !=0) && (getTempOutAHU(fnTepl)!=0) )
		{
				PutCritery(CriterT,CriterRH); // first
		}
		//PutCritery((GD.Hot.Tepl[fnTepl].AllTask.DoTVent - getTempVent(fnTepl)),DefRH());  //last
		//PutCritery((*pGD_TControl_Tepl).Kontur[cSmWindowUnW].CalcT,DefRH());  // было так
#warning check GD.Hot.Tepl[fnTepl].AllTask.DoTVent
		pGD_TControl_Tepl->AbsMaxVent=__MaxMechToVentTemp();
		// изменеие 100. Вместо getTempVent делаем getTempHeat
		//if ((getTempVent(fnTepl)!=0) && (GD.Hot.Tepl[fnTepl].AllTask.DoTVent !=0) && (getTempOutAHU(fnTepl)!=0) )
		if ((getTempHeat(fnTepl)!=0) && (GD.Hot.Tepl[fnTepl].AllTask.DoTVent !=0) && (getTempOutAHU(fnTepl)!=0) )
			TakeForSys(CriterT,fnTepl);  // first
		//TakeForSys(GD.Hot.Tepl[fnTepl].AllTask.DoTVent - getTempVent(fnTepl));  // last
		//TakeForSys((*pGD_TControl_Tepl).Kontur[cSmWindowUnW].CalcT);  // было так
		//if ((((int32_t)pGD_TControl_Tepl->Kontur[cSmWindowUnW].CalcT)*pGD_Hot_Tepl->NextTCalc.TVentCritery)<=0)
		//	pGD_TControl_Tepl->StopVentI=0;  // изначально было потом убрали

//!!

//		if ((((int32_t)pGD_TControl_Tepl->Kontur[cSmWindowUnW].CalcT)*pGD_Hot_Tepl->NextTCalc.TVentCritery)<=0)
//			pGD_TControl_Tepl->StopVentI=0;  // это Дима закоментил
		FinalCheckSys(cSysUCValve);
		FinalCheckSys(cSysMist);
		FinalCheckSys(cSysAHUSpeed);
		FinalCheckSys(cSysAHUPipe);
		FinalCheckSys(cSysScreen);
// END Работа Т-вентиляции

		  
		__sLastCheckWindow();

		pGD_TControl_Tepl->qMaxKonturs=0;
		pGD_TControl_Tepl->qMaxOwnKonturs=0;

		for(ByteX=0;ByteX<cSWaterKontur;ByteX++)
		{
			SetPointersOnKontur(ByteX);
			if 	(YesBit(pGD_Hot_Tepl_Kontur->RCS,cbNoWorkKontur)) continue;
			if	((pGD_TControl_Tepl_Kontur->RealPower[pGD_TControl_Tepl->CurrPower]>=pGD_TControl_Tepl->PowMaxKonturs)&&(pGD_TControl_Tepl->PowMaxKonturs))
			{
				SetBit(pGD_Hot_Tepl_Kontur->RCS,cbGoMax);
				pGD_TControl_Tepl->qMaxKonturs++;			
			}
			if	((pGD_TControl_Tepl_Kontur->RealPower[pGD_TControl_Tepl->CurrPower]>=pGD_TControl_Tepl->PowOwnMaxKonturs)
				&&(pGD_TControl_Tepl->PowOwnMaxKonturs)&&(pGD_TControl_Tepl_Kontur->NAndKontur==1))
			{
				SetBit(pGD_Hot_Tepl_Kontur->RCS,cbGoMaxOwn);
				pGD_TControl_Tepl->qMaxOwnKonturs++;			
			}
		}	
	}
	GD.TControl.PrevPozFluger=GD.Hot.PozFluger;

	//Очень длинный расчет, поэтому проверим измерения
//	CheckReadyMeasure();	
	//------------------------------------------------
	for(fnTepl=0;fnTepl<cSTepl;fnTepl++)
	{
		SetPointersOnTepl(fnTepl);

//		if (!pGD_TControl_Tepl->qMaxOwnKonturs)
//			pGD_TControl_Tepl->StopI=2;
		if(!pGD_Hot_Tepl->AllTask.DoTHeat) continue;

		if ((pGD_TControl_Tepl->nMaxKontur>=0)&&(YesBit((*pGD_Hot_Tepl).Kontur[pGD_TControl_Tepl->nMaxKontur].ExtRCS,cbReadyPumpKontur))
		&&(!YesBit(pGD_Hot_Tepl->Kontur[pGD_TControl_Tepl->nMaxKontur].RCS,cbPumpChange)))
		{
			ByteY=0;
			pGD_TControl_Tepl->qMaxKonturs=0;
			pGD_TControl_Tepl->qMaxOwnKonturs=0;
			if (pGD_TControl_Tepl->Critery<0)
			{
				for (tTepl=0;tTepl<cSTepl;tTepl++)
				{
					ClrDog;
					if (!((*pGD_TControl_Tepl).Kontur[pGD_TControl_Tepl->nMaxKontur].Separate&(1<<tTepl))) continue;

					if ((!(YesBit(GD.Hot.Tepl[tTepl].Kontur[pGD_TControl_Tepl->nMaxKontur].ExtRCS,cbReadyPumpKontur)))
					&&((!GD.TControl.Tepl[tTepl].NOwnKonturs)||(pGD_TControl_Tepl->NOwnKonturs)))
						ByteY=1;
				}
			}
			if (!ByteY)
			{
				for (tTepl=0;tTepl<cSTepl;tTepl++)
				{
					if (!((*pGD_TControl_Tepl).Kontur[pGD_TControl_Tepl->nMaxKontur].Separate&(1<<tTepl))) continue;
					GD.TControl.Tepl[tTepl].Kontur[pGD_TControl_Tepl->nMaxKontur].PumpStatus=1-pGD_TControl_Tepl->Kontur[pGD_TControl_Tepl->nMaxKontur].PumpStatus;	
					GD.TControl.Tepl[tTepl].Kontur[pGD_TControl_Tepl->nMaxKontur].PumpPause=cPausePump;
					SetBit(GD.Hot.Tepl[tTepl].Kontur[pGD_TControl_Tepl->nMaxKontur].RCS,cbPumpChange);
				}		
			}
		}
		
	}		
	ClrDog;	
//	CheckReadyMeasure();
	for(ByteX=0;ByteX<cSWaterKontur;ByteX++)
	{

		for (fnTepl=0;fnTepl<cSTepl;fnTepl++)
		{
			ClrDog;
			SetPointersOnTepl(fnTepl);
			SetPointersOnKontur(ByteX);
			pGD_TControl_Tepl->RealPower=0;
			if 	(YesBit(pGD_Hot_Tepl_Kontur->RCS,cbNoWorkKontur)) continue;
			pGD_TControl_Tepl->NAndKontur=pGD_TControl_Tepl_Kontur->NAndKontur;
			GD.TControl.Tepl[pGD_TControl_Tepl_Kontur->MainTepl].RealPower+=__sRaspKontur();
//			if ((!pGD_TControl_Tepl->NOwnKonturs)&&(pGD_TControl_Tepl_Kontur->RealPower))
//			{
//				pGD_TControl_Tepl->NAndKontur=1;
//				GD.TControl.Tepl[pGD_TControl_Tepl_Kontur->MainTepl].RealPower=__sRaspKontur();
//				break;
//			}
		}
		for (fnTepl=0;fnTepl<cSTepl;fnTepl++)
		{
			SetPointersOnTepl(fnTepl);
			SetPointersOnKontur(ByteX);
			if (YesBit(pGD_Hot_Tepl_Kontur->RCS,cbNoWorkKontur)) continue;
			if (pGD_TControl_Tepl_Kontur->NAndKontur==1) continue;
			LngY=(GD.TControl.Tepl[pGD_TControl_Tepl_Kontur->MainTepl].RealPower);
			ByteW=(GD.TControl.Tepl[pGD_TControl_Tepl_Kontur->MainTepl].NAndKontur);
			LngY/=ByteW;
			ClrDog;

			OldCrit=pGD_TControl_Tepl->Critery;
			// 52 изменеие
			// было
		    if (pGD_TControl_Tepl->NOwnKonturs)
			  pGD_TControl_Tepl->Critery=pGD_TControl_Tepl->Critery-__sThisToFirst((int)((LngY)));
			// стало
			/*if (GD.TuneClimate.CriteryLevel != 0)
			{
			  int CritM;
			  CritM = -1 * GD.TuneClimate.CriteryLevel * 100;
			  if ( pGD_TControl_Tepl->Critery-__sThisToFirst((int)((LngY)) ) <= CritM )
			  {
			    (*pGD_TControl_Tepl).Critery = CritM;
			  }
			  else
			  {
			    if (pGD_TControl_Tepl->NOwnKonturs)
				  pGD_TControl_Tepl->Critery=pGD_TControl_Tepl->Critery-__sThisToFirst((int)((LngY)));
			  }
			}*/
			// стало
			if (!SameSign(OldCrit,pGD_TControl_Tepl->Critery))
				pGD_TControl_Tepl->Critery=0;
			pGD_TControl_Tepl_Kontur->CalcT=LngY;
			__sLastCheckKontur(ByteX,&IntY);
			ClrDog;	

			if ((pGD_Hot_Tepl->MaxReqWater<pGD_Hot_Tepl_Kontur->Do)&&(ByteX<cSWaterKontur))
				pGD_Hot_Tepl->MaxReqWater=pGD_Hot_Tepl_Kontur->Do;
//			pGD_TControl_Tepl->KonturIntegral+=__sThisToFirst(IntY);
		}

	}
ClrDog;
//	CheckReadyMeasure();	
	for (fnTepl=0;fnTepl<cSTepl;fnTepl++)
	{
		SetPointersOnTepl(fnTepl);
		for(ByteX=0;ByteX<cSWaterKontur;ByteX++)
		{
			SetPointersOnKontur(ByteX);
			ClrDog;
			if (YesBit(pGD_Hot_Tepl_Kontur->RCS,cbNoWorkKontur)) continue;
			if (pGD_TControl_Tepl_Kontur->NAndKontur!=1) continue;
			pGD_TControl_Tepl_Kontur->CalcT=__sRaspOwnKontur();
			__sLastCheckKontur(ByteX,&IntY);	
//			if ((((long)IntY)*pGD_TControl_Tepl->Critery)<0) IntY=0;
			if ((pGD_Hot_Tepl->MaxReqWater<pGD_Hot_Tepl_Kontur->Do)&&(ByteX<cSWaterKontur))
				pGD_Hot_Tepl->MaxReqWater=pGD_Hot_Tepl_Kontur->Do;
//			pGD_TControl_Tepl->KonturIntegral+=__sThisToFirst(IntY);
		}
		if ((!pGD_TControl_Tepl->NOwnKonturs)) pGD_TControl_Tepl->StopI++;
		else
	   		pGD_TControl_Tepl->StopI=0;
		if (pGD_TControl_Tepl->StopI>cMaxStopI) pGD_TControl_Tepl->StopI=cMaxStopI;
	}
	
}
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*************************************************************************/
/*-*-*-*-*-*-*-*-*--Процедура начальных установок для контура--*-*-*-*-*-*/
/*************************************************************************/
void __sMechScreen(void)
{
	char xdata fnTepl;
	for(fnTepl=0;fnTepl<cSTepl;fnTepl++)
	{
		SetPointersOnTepl(fnTepl);
		if(pGD_TControl_Tepl->Screen[0].Value)
		{
			pGD_Hot_Tepl->OtherCalc.CorrScreen=pGD_Hot_Tepl->Kontur[cSmScreen].Do;//IntZ
		}

		// расчеты экранов
		SetPosScreen(cTermHorzScr,fnTepl);
		SetPosScreen(cSunHorzScr,fnTepl);
		SetPosScreen(cTermVertScr1,fnTepl);
	}
}

//Процедура делает установку фрамуги по разным датчикам температуры по сравнению с головным
//Изменения от 13.05.2014
int16_t __SetIntWin(uint8_t fSens,uint8_t fNFram,uint16_t fOffset,uint16_t fStartPoint, char fnTepl)
{
	int16_t* IntVal;


	if (!fStartPoint)
		return 0;

	if ((fSens>20)||(fSens<=1))
		IntZ=0;
	else
	{
		if (pGD_Hot_Tepl->InTeplSens[cSmTSens1+fSens-1].RCS == 0)
			IntX=pGD_Hot_Tepl->InTeplSens[cSmTSens1+fSens-1].Value-getTempHeat(fnTepl);
		IntZ=SetPID(IntX,fNFram,GD.TuneClimate.fAHU_MaxOffset,-GD.TuneClimate.fAHU_MaxOffset);
	}
	IntZ+=(fStartPoint-fOffset);
	if (IntZ>100) IntZ=100;
	if (IntZ<0) IntZ=0;
	return IntZ;

}
//Процедура устанавливает регулировку ведущей фрамуги от давления
//Изменения от 13.05.2014
int16_t __SetWinPress(uint16_t DoPres,uint8_t fNFram,uint16_t fOffset)
{
	int16_t* IntVal;


//#warning то сейчас из-за этого фрамуга постоянно прыгает вниз-вверх. И похоже разбегается. Может Серега был и прав – дело реально в прошивке может быть

	// надо протестить
	if (!(pGD_Hot_Tepl->Kontur[cSmWindowUnW].Do))
		return 0;

	IntX=(pGD_Hot_Tepl->InTeplSens[cSmOverPSens].Value-DoPres)/10;
	IntZ=SetPID(IntX,fNFram,100,0);

	if (IntZ<fOffset)
		IntZ=fOffset;
	if (IntZ>100) IntZ=100;
	if (IntZ<0) IntZ=0;
	return IntZ;

}


/*
int16_t __SetPad(char fnTepl)
{
	int16_t* IntVal;


	if (!(pGD_Hot_Tepl->AllTask.DoTCool))
		return 0;
#warning CHECK THIS
	IntX=getTempHeat(fnTepl)-pGD_Hot_Tepl->AllTask.DoTCool;
	IntZ=SetPID(IntX,cHSmAHUPad,pGD_TControl_Tepl->Systems[cSysMist].Max,0);
	return IntZ;

}
*/

//Процедура устанавливает регулировку фрамуг от головного клапана
//Изменения от 13.05.2014
void __sMechWindows(void)
{
	char xdata WindWin[2];
	char xdata fnTepl;
	char UCprevPosition;
//Оптимизация
	
	for(fnTepl=0;fnTepl<cSTepl;fnTepl++)
	{
		SetPointersOnTepl(fnTepl);
		UCprevPosition = pGD_Hot_Tepl->HandCtrl[cHSmUCValve].Position;

		if (!(YesBit(pGD_Hot_Tepl->HandCtrl[cHSmUCValve].RCS,cbManMech)))
			pGD_Hot_Tepl->HandCtrl[cHSmUCValve].Position=KeepUCValve(UCprevPosition);//;pGD_TControl_Tepl->Systems[cSysUCValve].Keep);//valveGetOldPos());//pGD_Hot_Tepl->Kontur[cSmWindowUnW].Do;
		//valveSetOldPos();
#warning Only f check
		//if (pGD_Strategy_Tepl[cSmKontur3].TempPower==22)
		pGD_Hot_Tepl->Kontur[cSmKontur3].Do=KeepAHUPipeSystem();
		pGD_TControl_Tepl->Kontur[cSmKontur3].DoT=pGD_Hot_Tepl->Kontur[cSmKontur3].Do*10;


		if (!(YesBit((*(pGD_Hot_Hand+cHSmAHUSpeed1)).RCS,(/*cbNoMech+*/cbManMech))))
			(*(pGD_Hot_Hand+cHSmAHUSpeed1)).Position=KeepFanSystem(fnTepl);//(*pGD_Hot_Tepl).AllTask.AHUVent;//pGD_Hot_Tepl->Kontur[cSmAHUSpd].Do;
		if (!(YesBit((*(pGD_Hot_Hand+cHSmAHUSpeed2)).RCS,(/*cbNoMech+*/cbManMech))))
			(*(pGD_Hot_Hand+cHSmAHUSpeed2)).Position=KeepFanSystem(fnTepl);//(*pGD_Hot_Tepl).AllTask.AHUVent;//pGD_Hot_Tepl->Kontur[cSmAHUSpd].Do;


		// было изменение 92
		//if (!(YesBit(pGD_Hot_Tepl->HandCtrl[cHSmWinN].RCS,cbManMech)))
		//{
		//	volatile int16_t vPresMax = pGD_Control_Tepl->PresMax * 100;
		//	pGD_Hot_Tepl->HandCtrl[cHSmWinN].Position=__SetWinPress(vPresMax,cHSmWinN,pGD_Hot_Tepl->HandCtrl[cHSmUCValve].Position/3);
		//}
		//  стало
		volatile int16_t vPresMax = pGD_Control_Tepl->PresMax * 100;
		pGD_Hot_Tepl->HandCtrl[cHSmWinN].Position=__SetWinPress(vPresMax,cHSmWinN,pGD_Hot_Tepl->HandCtrl[cHSmUCValve].Position/3);
		// -----------

		if (!(YesBit(pGD_Hot_Tepl->HandCtrl[cHSmWinN2].RCS,cbManMech)))
			pGD_Hot_Tepl->HandCtrl[cHSmWinN2].Position=__SetIntWin(GD.TuneClimate.fAHU_Sens2,cHSmWinN2,GD.TuneClimate.fAHU_Offset2,pGD_Hot_Tepl->HandCtrl[cHSmWinN].Position, fnTepl);
		if (!(YesBit(pGD_Hot_Tepl->HandCtrl[cHSmWinN3].RCS,cbManMech)))
			pGD_Hot_Tepl->HandCtrl[cHSmWinN3].Position=__SetIntWin(GD.TuneClimate.fAHU_Sens3,cHSmWinN3,GD.TuneClimate.fAHU_Offset3,pGD_Hot_Tepl->HandCtrl[cHSmWinN].Position, fnTepl);
		if (!(YesBit(pGD_Hot_Tepl->HandCtrl[cHSmWinN4].RCS,cbManMech)))
			pGD_Hot_Tepl->HandCtrl[cHSmWinN4].Position=__SetIntWin(GD.TuneClimate.fAHU_Sens4,cHSmWinN4,GD.TuneClimate.fAHU_Offset4,pGD_Hot_Tepl->HandCtrl[cHSmWinN].Position, fnTepl);

		if (!(YesBit(pGD_Hot_Tepl->HandCtrl[cHSmAHUPad].RCS,cbManMech)))
			pGD_Hot_Tepl->HandCtrl[cHSmAHUPad].Position=KeepMistSystem();
			//pGD_Hot_Tepl->HandCtrl[cHSmAHUPad].Position=__SetPad(fnTepl);/*KeepMistSystem();*/

		if (!(YesBit(pGD_Hot_Tepl->HandCtrl[cHSmInRH].RCS,cbManMech)))
			pGD_Hot_Tepl->HandCtrl[cHSmInRH].Position=KeepInRH(fnTepl);

	}
}
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/



void DecPumpPause(void)
{
	for (ByteX=0;ByteX<cSWaterKontur;ByteX++)
	{
		SetPointersOnKontur(ByteX);
		if (((*(pGD_Hot_Hand_Kontur+cHSmMixVal)).Position<100)&&((*(pGD_Hot_Hand_Kontur+cHSmMixVal)).Position>0))
		{
			pGD_TControl_Tepl_Kontur->PumpPause=cPausePump;
			if (pGD_TControl_Tepl_Kontur->DoT>4000) 
				pGD_TControl_Tepl_Kontur->PumpPause+=cPausePump;
		}
		if (pGD_TControl_Tepl_Kontur->PumpPause>0) 
		{
			pGD_TControl_Tepl_Kontur->PumpPause--;
//			SetBit(pGD_Hot_Tepl->ExtRCS,cbPausePumpTepl);
		}
		else	pGD_TControl_Tepl_Kontur->PumpPause=0;	
	}
	

}


