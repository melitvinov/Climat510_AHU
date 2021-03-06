#define NameSens(ns)       w_txt(NameASens[ns].Name)
#define EdSens(ns)         TxtEd(ns)


#define CURRENT_TEMP1_VALUE (pGD_Hot_Tepl->InTeplSens[cSmTSens1].Value)
#define CURRENT_TEMP2_VALUE (pGD_Hot_Tepl->InTeplSens[cSmTSens2].Value)
#define CURRENT_TEMP3_VALUE (pGD_Hot_Tepl->InTeplSens[cSmTSens3].Value)
#define CURRENT_TEMP4_VALUE (pGD_Hot_Tepl->InTeplSens[cSmTSens4].Value)
#define CURRENT_TEMP5_VALUE (pGD_Hot_Tepl->InTeplSens[cSmTSens5].Value)
#define CURRENT_TEMP6_VALUE (pGD_Hot_Tepl->InTeplSens[cSmTSens6].Value)

/*-------------------------------------------
		����� ������ ���������
-------------------------------------------- */
/*void PrintEd(char uEd) {
   switch(uEd){
   case cumV: w_txt("\274B");
        break;
   case cuPa: w_txt("\250a");
        break;
   case cuMSec: w_txt("\274/c");
        break;
   case cuGr: w_txt("\337");
        break;
   case cuT: w_txt("\337C");
        break;
   case cuPr: w_txt("%");
        break;
   case cuBt: w_txt("B\277");
        break;
   case cuDj: w_txt("\340\266");
        break;
   case cuMM: w_txt("\274\274");
        break;
   case cuPpm: w_txt("ppm");
        break;

   }
} */

#define	DS18B20_READ_ADDR	0x33
#define	DS18B20_SEND_ADDR	0x55
#define	DS18B20_CONVERTT	0x44
#define	DS18B20_READ_TEMP	0xBE
#define	DS18B20_SEND_EEPROM	0x4E
#define	DS18B20_FILL_EEPROM	0x48
#define	DS18B20_SKIP_ROM	0xCC

int32_t OldHotSun  = 0;

int16_t teplTmes[8][30];

int16_t getRH1AHUSensor(void)
{
	return pGD_Hot_Tepl->InTeplSens[cSmRHSens].Value;
}

int16_t getRH2AHUSensor(void)
{
	return pGD_Hot_Tepl->InTeplSens[cSmRHSens1].Value;
}

int16_t getRHoutAHUSensor(void)
{
	return pGD_Hot_Tepl->InTeplSens[cSmRHSens2].Value;
}

int16_t getCSmRHAHUOutSens(void)
{
	return pGD_Hot_Tepl->InTeplSens[cSmRHAHUOutSens].Value;
}

int16_t getTempSensor(char fnTepl, char sensor)
{
	if (pGD_Hot_Tepl->InTeplSens[sensor].RCS == 0)
	{
		teplTmes[fnTepl][sensor] = pGD_Hot_Tepl->InTeplSens[sensor].Value;
		return pGD_Hot_Tepl->InTeplSens[sensor].Value;
	}
	if (pGD_Hot_Tepl->InTeplSens[sensor].RCS != 0)
	{
		if (pGD_Hot_Tepl->InTeplSens[sensor].Value == 0)
			return 0;
		return teplTmes[fnTepl][sensor];
	}
}

int16_t getRHSensor(char fnTepl, char sensor)
{
	if (pGD_Hot_Tepl->InTeplSens[sensor].RCS == 0)
	{
		teplTmes[fnTepl][sensor] = pGD_Hot_Tepl->InTeplSens[sensor].Value;
		return pGD_Hot_Tepl->InTeplSens[sensor].Value;
	}
	if (pGD_Hot_Tepl->InTeplSens[sensor].RCS != 0)
	{
		if (pGD_Hot_Tepl->InTeplSens[sensor].Value == 0)
			return 0;
		return teplTmes[fnTepl][sensor];
	}
}

/*!
\brief ����������� ������� �� ������ AHU
@return int16_t �����������
*/
int16_t getTempOutAHU(char fnTepl)
{
	int16_t error = 0;
	int16_t temp = 0;
	temp = getTempSensor(fnTepl, cSmTAHUOutSens);
//	if ( temp != 0 )
//		error = 1;
//	if (error)
//		return GD.Hot.Tepl[fnTepl].tempVent;
}

/*!
\brief ����������� ������� �� ������ � ����� AHU
@return int16_t �����������
*/
int16_t getTempOutEndAHU(char fnTepl)
{
	int16_t error = 0;
	int16_t temp = 0;
	temp = getTempSensor(fnTepl, cSmT1AHUOutSens);
//	if ( temp != 0 )
//		error = 1;
//	if (error)
//		return GD.Hot.Tepl[fnTepl].tempVent;
}

/*!
\brief ����������� ������� ��� ��������� � ����������� �� ���������� �������� � ���������� ����������
@return int16_t �����������
*/
// �������� 100. ������ getTempVent ���������� ��� ������ �������� ��� ��������� �������� AHU
int16_t getRH(char fnTepl)
{
	int16_t ResRH;
	int16_t error = 0;
	int16_t temp = 0;
	int16_t i;
	int8_t calcType = 0;
	int8_t mask = 0;
	int8_t maskN = 0;
	int16_t max = 0;
	int16_t min = 5000;
	int16_t average = 0;
	char averageCount = 0;
	int16_t singleSensor = 0;
	calcType = GD.Control.Tepl[fnTepl].sensRH >> 6;
	mask = GD.Control.Tepl[fnTepl].sensRH << 2;
	mask = mask >> 2;
	error = 0;
	for (i=6;i<9;i++)
	{
		if ( (mask >> (i-6) & 1) && (getRHSensor(fnTepl, i)) )
		{
			temp = getRHSensor(fnTepl, i);
			if (min > temp)
				min = temp;
			if (max < temp)
				max = temp;
			average += temp;
			averageCount++;
			singleSensor = temp;
			maskN = (maskN >> 1) + 32;
			error = 1;
		} else maskN = (maskN >> 1);
	}
	average = average / averageCount;

	if (error)
	{
		GD.Hot.Tepl[fnTepl].RHsens = average;
		if (calcType & 1)
			GD.Hot.Tepl[fnTepl].RHsens = min;
		if (calcType >> 1 & 1)
			GD.Hot.Tepl[fnTepl].RHsens = max;
		return GD.Hot.Tepl[fnTepl].RHsens;
	}
}

/*!
\brief ����������� ������� ��� ��������� � ����������� �� ���������� �������� � ���������� ����������
@return int16_t �����������
*/
// �������� 100. ������ getTempVent ���������� ��� ������ �������� ��� ��������� �������� AHU
int16_t getTempCont(char fnTepl)
{
	int16_t error = 0;
	int16_t temp = 0;
	int16_t i;
	int8_t calcType = 0;
	int8_t mask = 0;
	int8_t maskN = 0;
	int16_t max = 0;
	int16_t min = 5000;
	int16_t average = 0;
	char averageCount = 0;
	int16_t singleSensor = 0;
	calcType = GD.Control.Tepl[fnTepl].sensT_vent >> 6;
	mask = GD.Control.Tepl[fnTepl].sensT_vent << 2;
	mask = mask >> 2;
	error = 0;
	for (i=0;i<6;i++)
	{
		if ( (mask >> i & 1) && (getTempSensor(fnTepl, i)) )
		{
			temp = getTempSensor(fnTepl, i);
			if (min > temp)
				min = temp;
			if (max < temp)
				max = temp;
			average += temp;
			averageCount++;
			singleSensor = temp;
			maskN = (maskN >> 1) + 32;
			error = 1;
		} else maskN = (maskN >> 1);
	}
	average = average / averageCount;
	if (error)
	{
		GD.Hot.Tepl[fnTepl].tempParamVent=maskN+(calcType<<6);
		GD.Hot.Tepl[fnTepl].tempVent = average;
		if (calcType & 1)
			GD.Hot.Tepl[fnTepl].tempVent = min;
		if (calcType >> 1 & 1)
			GD.Hot.Tepl[fnTepl].tempVent = max;
		return GD.Hot.Tepl[fnTepl].tempVent;
	}
}

/*!
\brief ����������� ������� ��� �������� � ����������� �� ���������� �������� � ���������� ����������
@return int16_t �����������
*/
int16_t getTempHeat(char fnTepl)
{
	int16_t error = 0;
	int16_t temp = 0;
	int16_t i;
	int8_t calcType = 0;
	int8_t mask = 0;
	int8_t maskN = 0;
	int16_t max = 0;
	int16_t min = 5000;
	int16_t average = 0;
	int8_t averageCount = 0;
	int16_t singleSensor = 0;
	calcType = GD.Control.Tepl[fnTepl].sensT_heat >> 6;
	mask = GD.Control.Tepl[fnTepl].sensT_heat << 2;
	mask = mask >> 2;
	error = 0;
	for (i=0;i<6;i++)
	{
		if ( (mask >> i & 1) && (getTempSensor(fnTepl, i)) )
		{
			temp = getTempSensor(fnTepl, i);
			if (min > temp)
				min = temp;
			if (max < temp)
				max = temp;
			average += temp;
			averageCount++;
			singleSensor = temp;
			maskN = (maskN >> 1) + 32;
			error = 1;
		} else maskN = (maskN >> 1);
	}
	average = average / averageCount;
	if (error)
	{
		GD.Hot.Tepl[fnTepl].tempParamHeat=maskN+(calcType<<6);
		GD.Hot.Tepl[fnTepl].tempHeat = average;
		if (calcType & 1)
			GD.Hot.Tepl[fnTepl].tempHeat = min;
		if (calcType >> 1 & 1)
			GD.Hot.Tepl[fnTepl].tempHeat = max;
		return GD.Hot.Tepl[fnTepl].tempHeat;
	}
}

/*!
\brief ������ ������� ����������� ������� ���������� � ����������� �� ���������� �������� � ���������� ����������
*/
int8_t getTempVentAlarm(char fnTepl)
{
	int16_t error = 0;
	int16_t temp = 0;
	int16_t i;
	int8_t calcType = 0;
	int8_t mask = 0;
	int8_t maskN = 0;
	int16_t max = 0;
	int16_t min = 5000;
	int16_t average = 0;
	int8_t averageCount = 0;
	int16_t singleSensor = 0;
	calcType = GD.Control.Tepl[fnTepl].sensT_vent >> 6;
	mask = GD.Control.Tepl[fnTepl].sensT_vent << 2;
	mask = mask >> 2;
	error = 0;
	for (i=0;i<6;i++)
	{
		if ( (mask >> i & 1) && (getTempSensor(fnTepl, i)) )
		{
			temp = getTempSensor(fnTepl, i);
			if (min > temp)
				min = temp;
			if (max < temp)
				max = temp;
			average += temp;
			averageCount++;
			singleSensor = temp;
			maskN = (maskN >> 1) + 32;
			error = 1;
		} else maskN = (maskN >> 1);
	}
	return maskN;
}

/*!
\brief ������ ������� ����������� ������� �������� � ����������� �� ���������� �������� � ���������� ����������
*/
int8_t getTempHeatAlarm(char fnTepl)
{
	int16_t error = 0;
	int16_t temp = 0;
	int16_t i;
	int8_t calcType = 0;
	int8_t mask = 0;
	int8_t maskN = 0;
	int16_t max = 0;
	int16_t min = 5000;
	int16_t average = 0;
	int8_t averageCount = 0;
	int16_t singleSensor = 0;
	calcType = GD.Control.Tepl[fnTepl].sensT_heat >> 6;
	mask = GD.Control.Tepl[fnTepl].sensT_heat << 2;
	mask = mask >> 2;
	error = 0;
	for (i=0;i<6;i++)
	{
		if ( (mask >> i & 1) && (getTempSensor(fnTepl, i)) )
		{
			temp = getTempSensor(fnTepl, i);
			if (min > temp)
				min = temp;
			if (max < temp)
				max = temp;
			average += temp;
			averageCount++;
			singleSensor = temp;
			maskN = (maskN >> 1) + 32;
			error = 1;
		} else maskN = (maskN >> 1);
	}
	return maskN;
}

int16_t getRHsens(char fnTepl)
{
	int16_t error = 0;
	int16_t RH = 0;
	int16_t i;
	int8_t calcType = 0;
	int8_t mask = 0;
	int8_t maskN = 0;
	int16_t max = 0;
	int16_t min = 9900;
	int16_t average = 0;
	int8_t averageCount = 0;
	int16_t singleSensor = 0;
	calcType = GD.Control.Tepl[fnTepl].sensRH >> 6;
	mask = GD.Control.Tepl[fnTepl].sensRH << 2;
	mask = mask >> 2;
	error = 0;
	for (i=0;i<3;i++)
	{
		if ( (mask >> i & 1) && (getRHSensor(fnTepl, i+6)) )
		{
			RH = getRHSensor(fnTepl, i+6);
			if (min > RH)
				min = RH;
			if (max < RH)
				max = RH;
			average += RH;
			averageCount++;
			singleSensor = RH;
			maskN = (maskN >> 1) + 32;
			error = 1;
		} else maskN = (maskN >> 1);
	}
	average = average / averageCount;
	if (error)
	{
		GD.Hot.Tepl[fnTepl].RHParam=maskN+(calcType<<6);
		GD.Hot.Tepl[fnTepl].RHsens = average;
		if (calcType & 1)
			GD.Hot.Tepl[fnTepl].RHsens = min;
		if (calcType >> 1 & 1)
			GD.Hot.Tepl[fnTepl].RHsens = max;
		return GD.Hot.Tepl[fnTepl].RHsens;
	}
}

char ds18b20_ReadROM(void)
{
//  if (Second&1)
  {	
  //	w1_test();
	//if (ToLowTime<1) ToLowTime=1;
	//w1_check();
    w1reset();
    if (SendByte1W<4) return 1;
	SendByte1W=DS18B20_READ_ADDR;
  	w1_wr();
//	return 0;
  }	  
  for(ByteX=0;ByteX<8;ByteX++)
  {		
  	w1_rd();
	Buf1W[ByteX]=SendByte1W;
  }
//  w1reset();
  SendByte1W=8;
  CrcCalc();
//  Buf1W[7]=0;
  if (SendByte1W) return 2;
  return 0;		

}

void ds18b20_WriteROM(void)
{
  SendByte1W=DS18B20_SEND_ADDR;
  w1_wr();
  for(ByteX=0;ByteX<8;ByteX++)
  {
	SendByte1W=pBuf[ByteX];
  	w1_wr();
  }
}

void ds18b20_FillReg(void)
{
	w1reset();
//	if (SendByte1W<4) return 1;
	ds18b20_WriteROM();
	SendByte1W=DS18B20_SEND_EEPROM;
  	w1_wr();
	SendByte1W=0;
  	w1_wr();
	SendByte1W=0;
  	w1_wr();
	SendByte1W=0x7f;
  	w1_wr();

}

char ds18b20_ReadTemp(void)
{

  w1reset();	
//  if (SendByte1W<4) return 1;
  ds18b20_WriteROM();
  SendByte1W=DS18B20_READ_TEMP;
  w1_wr();
  for(ByteX=0;ByteX<9;ByteX++)
  {		
  	w1_rd();
	Buf1W[ByteX]=SendByte1W;
  }
  w1reset();
  SendByte1W=9;
  CrcCalc();
  if (SendByte1W) return 2;
  return 0;		
}


/*char ds18b20_Read(void)
{
  w1reset();	
  WriteROM1W();
  if (ReadData1W()) return 2;	
  return 0;		
}
*/
void ds18b20_ConvertTemp(void)
{

  w1reset();	 
//  ds18b20_WriteROM();
  SendByte1W=DS18B20_SKIP_ROM;
  w1_wr();
  SendByte1W=DS18B20_CONVERTT;
  w1_wr();
}



char SameSign(int Val1,int Val2)
{
	if (((Val1>0)&&(Val2>0))
	|| ((Val1<0)&&(Val2<0))) return 1;
	else
		return 0;
}

void SetPointersOnTepl(char fnTepl)
{
	pGD_Hot_Tepl=&GD.Hot.Tepl[fnTepl];
	pGD_TControl_Tepl=&GD.TControl.Tepl[fnTepl];
	pGD_Control_Tepl=&GD.Control.Tepl[fnTepl];
	pGD_Hot_Hand=&GD.Hot.Tepl[fnTepl].HandCtrl[0];
	pGD_ConstMechanic=&GD.ConstMechanic[fnTepl];	
	pGD_MechConfig=&GD.MechConfig[fnTepl];
	pGD_Level_Tepl=&GD.Level.InTeplSens[fnTepl];
	pGD_Strategy_Tepl=&GD.Strategy[fnTepl];
}



void SetPointersOnKontur(char fnKontur)
{
	pGD_Hot_Tepl_Kontur=&(pGD_Hot_Tepl->Kontur[fnKontur]);
	pGD_TControl_Tepl_Kontur=&(pGD_TControl_Tepl->Kontur[fnKontur]);
	pGD_Hot_Hand_Kontur=&(pGD_Hot_Hand[fnKontur]);
	pGD_Strategy_Kontur=&pGD_Strategy_Tepl[fnKontur];
	pGD_MechConfig_Kontur=&pGD_MechConfig->RNum[fnKontur];
	pGD_ConstMechanic_Mech=&pGD_ConstMechanic->ConstMixVal[fnKontur];
}

void MidlWindAndSr(void)
{
	if (startFlag)
	{
		if (startFlag < 0) startFlag = 0;
		return;
	}
	GD.TControl.SumSun+=((long int)GD.TControl.MeteoSensing[cSmFARSens]);
	if (GD.Control.MidlSunCalc)
	{
		//MidlSunCalc = (int)((((long int)MidlSunCalc)*(1000-o_MidlSRFactor)+((long int)GD.TControl.MeteoSensing[cSmFARSens])*o_MidlSRFactor)/1000);
		MidlSunCalc = (int)((((long int)MidlSunCalc)*(1000-o_MidlSRFactor)+((long int)GD.Hot.MeteoSensing[cSmFARSens].Value)*o_MidlSRFactor)/1000);

		//GD.Hot.MidlSR=(int)((((long int)GD.Hot.MidlSR)*(1000-o_MidlSRFactor)+((long int)GD.TControl.MeteoSensing[cSmFARSens])*o_MidlSRFactor)/1000);
		//if (MidlSunCalc != GD.Hot.MidlSR)
		GD.Hot.MidlSR = MidlSunCalc;


		//GD.Hot.MidlSR=(int)(GD.Hot.MidlSR);
	}
	else
	{
		GD.TControl.MidlSR=((((long int)GD.TControl.MidlSR)*(1000-o_MidlSRFactor))/1000
		+((long int)GD.TControl.MeteoSensing[cSmFARSens])*o_MidlSRFactor);
		GD.Hot.MidlSR=(int)(GD.TControl.MidlSR/1000);
	}

	if (GetMetSensConfig(cSmFARSens))
	{
		GD.Hot.SumSun=(int)((GD.TControl.SumSun*6)/1000);
	}
	if (GD.Control.MidlWindCalc)
	{
		//MidlWindCalc = (int)((((long int)MidlWindCalc)*(1000-o_MidlWindFactor)+((long int)GD.TControl.MeteoSensing[cSmVWindSens])*o_MidlWindFactor)/1000);
		MidlWindCalc = (int)((((long int)MidlWindCalc)*(1000-o_MidlWindFactor)+((long int)GD.Hot.MeteoSensing[cSmVWindSens].Value)*o_MidlWindFactor)/1000);
		GD.Hot.MidlWind = MidlWindCalc;
	}
	else
		GD.Hot.MidlWind=(int)((((long int)GD.Hot.MidlWind)*(1000-o_MidlWindFactor)+((long int)GD.TControl.MeteoSensing[cSmVWindSens])*o_MidlWindFactor)/1000);
}

void CheckMidlSr(void)
{
	if (GetMetSensConfig(cSmFARSens))
	{
		GD.Hot.SumSun=(int)((GD.TControl.SumSun*6)/1000);
		//GD.Hot.MidlSR=(int)(GD.TControl.MidlSR);//;/1000);
	}
}

int abs(int f_in)
{
	if (f_in<0) return (-f_in);
	return f_in;
}

void ogrMin(int16_t *f_in,int16_t f_gr)
{
	if ((*f_in)<f_gr) 
		(*f_in)=f_gr;
}

void ogrMax(int16_t *f_in,int16_t f_gr)
{
	if ((*f_in)>f_gr) 
		(*f_in)=f_gr;
}

/*char CheckSeparate (char fnTepl, char fnKontur)
{
	char t2;
	char t1;
	GD.TControl.Tepl[fnTepl].Kontur[fnKontur].NAndKontur=0;
	if (!GD.MechConfig[fnTepl][fnKontur])
		return 0;
	for (t2=0;t2<cSTepl;t2++)
		if (GD.MechConfig[t2][fnKontur]==GD.MechConfig[fnTepl][fnKontur]) 
		{
			t1|=(1<<GD.MechConfig[t2][fnKontur]);
			GD.TControl.Tepl[fnTepl].Kontur[fnKontur].NAndKontur++;
		}
	return t1;
}
*/
char CheckSeparate (char fnKontur)
{
	char t2;
	char t1;
	pGD_TControl_Tepl_Kontur->NAndKontur=0;
	if (!(*pGD_MechConfig_Kontur))
		return 0;
	t1=0;
	for (t2=0;t2<cSTepl;t2++)
		if (GD.MechConfig[t2].RNum[fnKontur]==(*pGD_MechConfig_Kontur)) 
		{
			t1|=(1<<t2);
			pGD_TControl_Tepl_Kontur->NAndKontur++;
		}
	return t1;
}

char CheckMain(char fnTepl)
{
	char tTepl;
	tTepl=0;
	while(tTepl<cSTepl)
	{
		if (((*pGD_TControl_Tepl_Kontur).Separate>>tTepl)&1)
			return tTepl;
		tTepl++;
	}
	return fnTepl;
}



/*-------------------------------------------
		�������� ������ ��� ��������
--------------------------------------------
void CheckDigitMidl(eSensing *ftemp,char fdelta)
{
	if ((!fdelta)||(YesBit(ftemp->RCS,cbNotGoodSens)))
		ClrBit(ftemp->RCS,cbNotGoodSens);
	else
	{
		if ((Mes>ftemp->Value+fdelta)||(Mes<(ftemp->Value)-fdelta)) 
		{
			SetBit(ftemp->RCS,cbNotGoodSens);
			Mes=ftemp->Value;
		}
	}
	
}

void CheckSensLevs(char full,char met)
{
	int16_t 		*uS;
	eNameASens 	*nameS;
	eSensing 	*valueS;
	int16_t			*llS;
	int16_t			*lS;
	int16_t			*levelS;
	SetPointersOnTepl(nSensTeplNow);
	uS=&GD.uInTeplSens[nSensTeplNow][ByteX];	
	nameS=&NamesSensConfig[ByteX];
	valueS=&(pGD_Hot_Tepl->InTeplSens[ByteX]);
	llS=&(pGD_TControl_Tepl->LastLastInTeplSensing[ByteX]);
	lS=&(pGD_TControl_Tepl->LastInTeplSensing[ByteX]);
	levelS=pGD_Level_Tepl[ByteX];
	if (met)
	{
		uS=&GD.uMeteoSens[ByteX];	
		nameS=&NamesOfSens[ByteX+cSInTeplSens];
		valueS=&GD.Hot.MeteoSens[ByteX];
		llS=&GD.TControl.LastLastMeteoSensing[ByteX];
		lS=&GD.TControl.LastMeteoSensing[ByteX];
		levelS=GD.Level.MeteoSens[ByteX];
	}
	if (full)
	{

		if(((*uS)<nameS->uMin)&&(nameS->uMin)||((*uS)>nameS->uMax)&&(nameS->uMax))
			SetBit(valueS->RCS,cbMinMaxUSens);				
	}
	if (Mes < nameS->Min) 
	{
		if ((nameS->TypeSens==cTypeSun)||(nameS->TypeSens==cTypeRain))
			Mes=nameS->Min;
		else
		{
			SetBit(valueS->RCS,cbMinMaxVSens);
			Mes=0;          
		}
	}
	if (Mes > nameS->Max)
	{
		if ((nameS->TypeSens==cTypeRain)||(nameS->TypeSens==cTypeRH)||(nameS->TypeSens==cTypeFram))
			Mes=nameS->Max;
		else
		{
			SetBit(valueS->RCS,cbMinMaxVSens);
			Mes=0;          
		}		
	}
//	CheckDigitMidl(valueS,nameS->DigitMidl);
	switch (nameS->TypeMidl)
	{ 
		case cNoMidlSens:				
			break;
		case c2MidlSens:
			(*llS)=0;
		case c3MidlSens:
			IntX=(*llS);       
			IntY=(*lS);
			(*llS)=IntY;
        	(*lS)=Mes;
			IntZ=0;
        	if(Mes) IntZ++;
        	if(IntX) IntZ++;
			if(IntY) IntZ++;
			if (IntZ) Mes=(Mes+IntX+IntY)/IntZ;

			break;
		case cExpMidlSens:
			
			IntY=(*llS);
			IntZ=0;
			if (IntY) IntZ++;
			if (Mes) IntZ++;
			if (IntZ) (*llS)=(Mes+IntY)/IntZ;
			else {(*llS)=0;(*lS)=0;}
			if ((abs((*lS)-(*pGD_Hot_Tepl).AllTask.DoTHeat))>(abs((Mes)-(*pGD_Hot_Tepl).AllTask.DoTHeat)))
				(*lS)=Mes;
			Mes=(int)((((long int)(*lS))*(1000-cKExpMidl)+((long int)Mes)*cKExpMidl)/1000);
			(*lS)=Mes;
			break;
	}
	valueS->Value=Mes;
	if (nameS->TypeSens==cTypeFram)
	{
		if (pGD_TControl_Tepl->MechBusy[nSensor-cSmWinNSens+cHSmWinN].PauseMech>89) return;
		pGD_TControl_Tepl->FramUpdate[nSensor-cSmWinNSens]=1; 
	}
	ClrBit(valueS->RCS,(cbDownAlarmSens+cbUpAlarmSens));
	if ((levelS[cSmDownCtrlLev])&&(Mes <= levelS[cSmDownCtrlLev])) 
		SetBit(valueS->RCS,cbDownCtrlSens);
    if ((levelS[cSmUpCtrlLev])&&(Mes >= levelS[cSmUpCtrlLev])) 
    	SetBit(valueS->RCS,cbUpCtrlSens);
	if ((levelS[cSmDownAlarmLev])&&(Mes <= levelS[cSmDownAlarmLev])) 
	{
		SetBit(valueS->RCS,cbDownAlarmSens);
		return;
	}
    if ((levelS[cSmUpAlarmLev])&&(Mes >= levelS[cSmUpAlarmLev])) 
	{
    	SetBit(valueS->RCS,cbUpAlarmSens);
        return;
    }
}
/*-------------------------------------------
		��������� �� �������
--------------------------------------------



void  Calibr(void){
	eSensing	*fSens;
	eNameASens	*fNameSens;
	int16_t		*fuSens;
	eCalSensor	*fCalSens;
	char		met=0;

	ByteY=0;
	switch (nSensAreaNow)
	{
		case cWaterSensing:
		{
				ByteY=cSmWaterSens;		
				nSensor+=cSmWaterSens;
		}
		case cInSensing:
		{
			fSens=&GD.Hot.Tepl[nSensTeplNow].InTeplSens[nSensor];
			fuSens=&GD.uInTeplSens[nSensTeplNow][nSensor];
			fCalSens=&GD.Cal.InTeplSens[nSensTeplNow][nSensor];
			fNameSens=&NamesSensConfig[nSensor];
			met=0;
			break;
		}
		case cOutSensing:
		{
			fSens=&GD.Hot.MeteoSens[nSensor];
			fuSens=&GD.uMeteoSens[nSensor];
			fCalSens=&GD.Cal.MeteoSens[nSensor];
			fNameSens=&NamesSensConfig[nSensor+cSInTeplSens];
			met=1;
			break;
		}
	}		
	fSens->RCS=(fSens->RCS&(cbNotGoodSens+cbDownAlarmSens+cbUpAlarmSens));
	switch (fNameSens->TypeSens) 
	{
		case cTypeMeteo:
		{
       	    LngX=MesINT1/256; 
			if(LngX<0) 
			LngX=256+LngX;
			Mes=MesINT1&255;
		    fuSens[0]=Mes;
        	fuSens[1]=LngX;
			if(Mes) 
			{
				fSens[1].Value=LngX*360/Mes;
			   	Mes=12700/Mes;
			}
		    if(fSens[1].Value>360)
				fSens[1].Value=0;		
		    ByteX=nSensor;
			CheckSensLevs(0,1);
			fSens[1].RCS=(fSens[1].RCS&cbNotGoodSens);
		    ByteX=nSensor+1;
			Mes=fSens[1].Value;
			CheckSensLevs(0,1);
			return;
		}
		case cTypeFram:
		case cTypeSun:
		case cTypeRain:
		case cTypeAnal:
		case cTypeRH:
		{
//#ifndef BIGLCD
			if (fCalSens->Input>10)
			{
//			    if (Second<3) return;
			//	w1_test();
				if (ToLowTime<1) ToLowTime=1;
//				for(ByteW=0;ByteW<7;ByteW++)
				pBuf=(char*)(&fCalSens->U0);
//				//Buf1W[0]=0x28;
//				SendByte1W=7;
//				CrcCalc();
//				Buf1W[7]=SendByte1W;

				if (ds18b20_ReadTemp()) Mes=0;
				else
				{
					(*((char*)&Mes))=Buf1W[0];
					(*(((char*)&Mes)+1))=Buf1W[1];
//					Mes=(uint)(Buf1W[0])+((int)Buf1W[1])*256;
					Mes=(Mes*10);
						//Mes+=((int)(((char)fCalSens->nInput)))*16;
					if (fNameSens->Frm==SSpS0)
						Mes=(((long)Mes)*10/16);
					else
						Mes=(Mes/16);
					
				}
//				ds18b20_ConvertTemp();
				//ds18b20_FillReg();

				ByteX=nSensor;				
				CheckSensLevs(0,met);
//				for(ByteW=0;ByteW<7;ByteW++)
//					Buf1W[ByteW]=((char*)(fCalSens->uCal))[ByteW];
					//Buf1W[0]=0x28;
//				SendByte1W=7;
//				CrcCalc();
//				Buf1W[7]=SendByte1W;


				return;
			}
//#endif
			ClrDog;
	    	Mes=(int)((long int)Mes*(long int)1000/(long int)GD.Cal.Port);
        	fuSens[0]=Mes;
			if(Mes>5000) 
			Mes=0;
        	LngX=((long)fCalSens->V1-(long)fCalSens->V0)
        		*((long)Mes-(long)fCalSens->U0);
        	Mes=(int16_t)(LngX/((long)fCalSens->U1-(long)fCalSens->U0));
        	Mes=Mes+fCalSens->V0;
			ByteX=nSensor;
			if (fCalSens->Input==7)
			{
				Mes=0;
				if (YesBit(RegLEV,cSmRain))
					Mes=10;
			}
			CheckSensLevs(1,met);
			return;
		}
	}
}
/*------------------------------------------

---------------------------------------------

void GenerateTypeSensing(void)
{
	if (nSensArea==cWaterSensing)
	{
	  nSensTepl++;
	  nSensTepl%=cSTepl;
	  if (!nSensTepl)
	  {
	    nSensArea=cInSensing;
	    nSensTepl=nSensTeplSave;
	    nSensTepl++;
	    nSensTepl%=(cSTepl+2);
		if (nSensTepl==cSTepl)
		{
			nSensArea=cOutSensing;
		}
		if (nSensTepl==cSTepl+1)
		{
			ds18b20_ConvertTemp();
			nSensArea=cMissSensing;
		}
	  }
	  return;
	}
    nSensArea=cWaterSensing;
	nSensTeplSave=nSensTepl;
    nSensTepl=0;
		
}

void SetSensorOn(void)
{
	if(CalPort) 
	{
		nPort=(nPortSave-1)*8+SaveChar-1;
	    nInput=SaveChar;
		return;
	}
	if ((!FalseIZ)&&(nSensAreaNow!=cMissSensing))
	    Calibr();
	nSensor=nNextSensor;
	nSensTeplNow=nSensTepl;
	nSensAreaNow=nSensArea;
	while(1)
	{	
		if (!nNextSensor)
			GenerateTypeSensing();
		ByteX=cSmWaterSens;
		ByteY=0;

		switch (nSensArea)
		{
			case cWaterSensing:
			{
 				ByteX=cSInTeplSens-cSmWaterSens;
				ByteY=cSmWaterSens;
			}
			case cInSensing:
			{
				nNextSensor++;
				nNextSensor%=ByteX;
				if ((!GD.Cal.InTeplSens[nSensTepl][ByteY+nNextSensor].Input))
				{
					GD.uInTeplSens[nSensTepl][ByteY+nNextSensor]=0;				
			        GD.Hot.Tepl[nSensTepl].InTeplSens[ByteY+nNextSensor].RCS=0;
		        	SetBit(GD.Hot.Tepl[nSensTepl].InTeplSens[ByteY+nNextSensor].RCS,cbNoWorkSens);
		        	GD.Hot.Tepl[nSensTepl].InTeplSens[ByteY+nNextSensor].Value=0;
 
					continue;
				}
		       	nPort=(GD.Cal.InTeplSens[nSensTepl][ByteY+nNextSensor].Input-1);//*8+GD.Cal.InTeplSens[nSensTepl][ByteY+nNextSensor].nInput-1;
       			nInput=0;//GD.Cal.InTeplSens[nSensTepl][ByteY+nNextSensor].nInput-1;
				nTypeSens=NamesSensConfig[ByteY+nNextSensor].TypeSens;

				break;
			}	  
			case cOutSensing:
			{
				nNextSensor++;
				nNextSensor%=cSMeteoSens;

				if (!GD.Cal.MeteoSens[nNextSensor].Input)
				{	
					GD.uMeteoSens[nNextSensor]=0;
					GD.Hot.MeteoSens[nNextSensor].RCS=0;
		        	SetBit(GD.Hot.MeteoSens[nNextSensor].RCS,cbNoWorkSens);
				
					continue;
				}
		       	nPort=(GD.Cal.MeteoSens[nNextSensor].Input-1);//*8+GD.Cal.MeteoSens[nNextSensor].nInput-1;
       			nInput=0;//GD.Cal.MeteoSens[nNextSensor].nInput-1;
				nTypeSens=NamesOfSens[cSInTeplSens+nNextSensor].TypeSens;
				break;
			}
			case cMissSensing:
			{
				nNextSensor++;
				nNextSensor%=3;
				break;
			}
			default:
			{
				nSensArea=cInSensing;
				break;
			}

		}
		break;
	}
}

void CheckReadyMeasure(void)
{
   if(ReadyIZ) 
	{
		SetSensorOn();
        ClrDog;
        FalseIZ=0;
        ReadyIZ=0;
    }
}
*/
void SetResRam(void)
{
	GD.Hot.News|=bResRam;	
}
void InitGD(char fTipReset) {
		eCalSensor xdata *eCS;
        ClrDog;
        SIM=100;
		NDat=0;
		if (fTipReset>2)
			MemClr(&GD.Hot,(sizeof(eHot)));
        MemClr(&GD.Control,sizeof(eControl)
                +sizeof(eFullCal)
                +sizeof(eLevel)
                +sizeof(eTimer)*cSTimer);

ClrDog; 
        //MemClr(&GD.ConstMechanic[0],sizeof(eTuneClimate)+sizeof(eTControl)+sizeof(eStrategy)*cSStrategy*cSTepl+sizeof(eConstMech)*cSTepl+sizeof(eMechConfig)*cSTepl);   // NEW strat
		MemClr(&GD.ConstMechanic[0],sizeof(eTuneClimate)+sizeof(eTControl)+sizeof(eStrategy)*cSTepl+sizeof(eConstMech)*cSTepl+sizeof(eMechConfig)*cSTepl);
        MemClr(&GD.uInTeplSens[0][0],sizeof(uint16_t)*(cConfSMetSens+cSTepl*cConfSSens));
ClrDog;

		GD.Timer[0].crc = 0xAA;

        /* ��������� ������ �� ��������� */
        GD.Hot.Year=01;
        GD.Hot.Data=257;
        GD.Hot.Time=8*60;
        GD.Hot.News|=bReset;
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
		Y_menu=0;
        x_menu=0;
	//	TimeReset=3;

        /* ��������� ���� �� ��������� */
		for (IntX=0;IntX<(sizeof(NameConst)/3);IntX++)
			GD.TuneClimate.s_TStart[IntX]=NameConst[IntX].StartZn;


		GD.Control.NFCtr=NumCtr;
		GD.Control.IPAddr[0]=192;
		GD.Control.IPAddr[1]=168;
		GD.Control.IPAddr[2]=1;
		GD.Control.IPAddr[3]=66;//100+NumCtr;

		GD.Control.Read1W=9;
		GD.Control.Write1W=4;
		GD.Control.ConfSTepl=cConfSTepl;
		GD.Control.Language=cDefLanguage;
		GD.Control.Cod=111;
		GD.Control.Screener=40;
		GD.Control.MidlSunCalc = 1;
		GD.Control.MidlWindCalc = 1;

        GD.Control.NFCtr=NumCtr;

        for(ByteX=0;ByteX<cConfSMetSens;ByteX++) {
			eCS=&GD.Cal.MeteoSens[ByteX];
           	eCS->V0=NameSensConfig[ByteX+cConfSSens].vCal[0];
           	eCS->V1=NameSensConfig[ByteX+cConfSSens].vCal[1];
           	eCS->U0=NameSensConfig[ByteX+cConfSSens].uCal[0];
           	eCS->U1=NameSensConfig[ByteX+cConfSSens].uCal[1];
           	eCS->Type=NameSensConfig[ByteX+cConfSSens].TypeInBoard;
           	eCS->Output=NameSensConfig[ByteX+cConfSSens].Output;
			//eCS->Input=OutPortsAndInputs[ByteX][0];
			//eCS->nInput=OutPortsAndInputs[ByteX][1];
			}

        for (ByteX=0;ByteX<cSTepl;ByteX++)
		{
			SetPointersOnTepl(ByteX);
			for (IntX=0;IntX<sizeof(eStrategy);IntX++)
				(*((&(pGD_Strategy_Tepl[0].StratAHUvalve1[0]))+IntX)) = DefStrategy[IntX];

			bWaterReset[ByteX]=1;
			for (IntX=0;IntX<SUM_NAME_CONF;IntX++)
				pGD_MechConfig->RNum[IntX]=MechC[ByteX][IntX];
			for (IntX=0;IntX<cConfSSystem;IntX++)
				pGD_MechConfig->Systems[IntX]=InitSystems[ByteX][IntX];

		    for (IntX=0;IntX<cSRegCtrl;IntX++)
			{
				//pGD_TControl_Tepl->MechBusy[IntX].BlockRegs=1;
				pGD_TControl_Tepl->MechBusy[IntX].PauseMech=300;
				pGD_TControl_Tepl->MechBusy[IntX].Sens=0;
			}
		    for (IntX=0;IntX<(sizeof(DefControl)/2);IntX++)
				pGD_Control_Tepl->c_MaxTPipe[IntX]=DefControl[IntX];
		    for (IntX=0;IntX<cSRegCtrl;IntX++)
			{
				pGD_ConstMechanic->ConstMixVal[IntX].v_TimeMixVal=DefMechanic[0];
				pGD_ConstMechanic->ConstMixVal[IntX].v_MinTim=(char)DefMechanic[3];
				pGD_ConstMechanic->ConstMixVal[IntX].v_PFactor=DefMechanic[1];
				pGD_ConstMechanic->ConstMixVal[IntX].v_IFactor=DefMechanic[2];
				//pGD_ConstMechanic->ConstMixVal[IntX].Power=(char)DefMechanic[3];
			}
// ������������� ��������� ����������
	        for(ByteY=0;ByteY<cConfSSens;ByteY++)
			{
				eCS=&GD.Cal.InTeplSens[ByteX][ByteY];
    	       	eCS->V0=NameSensConfig[ByteY].vCal[0];
        	   	eCS->V1=NameSensConfig[ByteY].vCal[1];
           		eCS->U0=NameSensConfig[ByteY].uCal[0];
           		eCS->U1=NameSensConfig[ByteY].uCal[1];
				eCS->Output=NameSensConfig[ByteY].Output;
				eCS->Type=NameSensConfig[ByteY].TypeInBoard;
				//eCS->nInput=InPortsAndInputs[ByteX][ByteY][1];
			}
		}
 ClrDog;
/* ������� ������� ������*/
       // GD.Cal.Port=1437;
	    nReset=25;
        GD.SostRS=OUT_UNIT;
}


int CorrectionRule(int fStartCorr,int fEndCorr, int fCorrectOnEnd, int fbSet)
{
	if ((IntY<=fStartCorr)||(fStartCorr==fEndCorr))
	{
		IntZ=0;
		return 0;
	}
	if (IntY>fEndCorr)	
		IntZ=fCorrectOnEnd;	
	else
		IntZ=(int)((((long)(IntY-fStartCorr))*fCorrectOnEnd)/(fEndCorr-fStartCorr));
	return fbSet;
}

//var MaxH:array [1..SKof] of T2Byte=(
//520,557,595,637,680,757,779,828,883,
//941,1002,1067,1136,1208,1284,1365,1450,1539,1632,
//1732,1835,1944,2060,2181,2307,2440,2579,2726,2910);

uint16_t GetMaxH(uint16_t vmT)
{
	volatile uint16_t res;
	volatile uint16_t resM;
	volatile uint16_t resM1;
	uint16_t MaxH[] = {520,557,595,637,680,757,779,828,883,
			941,1002,1067,1136,1208,1284,1365,1450,1539,1632,
			1732,1835,1944,2060,2181,2307,2440,2579,2726,2910};
	volatile uint16_t sot;
	//sot = vmT mod 100;
	//vmT = vmT div 100;

	if (vmT > 2910)  // ��������� ������� �������, ����� ��������� ��������� ����������
		vmT = 2910;

	sot = vmT % 100;
	vmT = vmT / 100;

	if (vmT<1)  // ��������� ������� �������
		return 0;

	//else return MaxH[vmT]+(MaxH[vmT+1]-MaxH[vmT])*sot / 100;
	//res = MaxH[vmT]+(MaxH[vmT+1]-MaxH[vmT])*sot / 100;
	resM = MaxH[vmT];
	resM1 = MaxH[vmT+1];
	res = resM+(resM1-resM)*sot / 100;
	//else return MaxH[vmT]+(MaxH[vmT+1]-MaxH[vmT])*sot / 100;
	return res;
}

uint16_t GetDDWP(uint16_t vT, uint16_t vH)
{
	uint16_t res;
	res = GetMaxH(vT)*(10000-vH) / 10000;
	return res;
	/*int16_t TEMP[] = {800,900,1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000,2100,2200,2300,2400,2500,2600,2700,2800,2900,3000};

	int16_t DDWP[][23]={{4000},{50,53,56,60,64,68,72,77,82,87,92,98,104,110,117,124,131,138,146,155,163,173,182},
						{4500},{46,49,52,55,59,62,66,71,75,80,85,90,95, 101,107,113,120,127,134,142,150,158,167},
						{5000},{41,44,47,50,53,57,60,64,68,72,77,82,87,92,97,103,109,115,122,129,136,144,152},
						{5500},{37,40,42,45,48,51,54,58,61,65,69,73,78,83,87,93,98,104,110,116,123,129,137},
						{6000},{33,35,38,40,43,45,48,51,55,58,62,65,69,73,78,82,87,92,98,103,109,115,121},
						{6500},{29,31,33,35,37,40,42,45,48,51,54,57,61,64,68,72,76,81,85,90,95,101,106},
						{7000},{25,26,28,30,32,34,36,39,41,43,46,49,52,55,58,62,65,69,73,77,82,86,91},
						{7500},{21,22,24,25,27,28,30,32,34,36,38,41,43,46,49,51,54,58,61,64,68,72,76},
						{8000},{17,18,19,20,21,23,24,26,27,29,31,33,35,37,39,41,44,46,49,52,54,58,61},
						{8500},{12,13,14,15,16,17,18,19,20,22,23,24,26,28,29,31,33,35,37,39,41,43,46},
						{9000},{8,9,9,10,11,11,12,13,14,14,15,16,17,18,19,21,22,23,24,26,27,29,30},
						{9500},{04,04,05,05,05,06,06,06,07,07,8,8,9,9,10,10,11,12,12,13,14,14,15},
						{9900},{01,01,01,01,01,01,01,01,01,01,02,02,02,02,02,02,02,02,02,03,03,03,03}};
	uint32_t deltaT;
	uint32_t deltaRH;
	uint32_t deltaMes;
	uint32_t resI_T;
	uint32_t resI_RH;

	uint32_t res;
	for (int i=0;i<13;i++)
	{
		if (vH > DDWP[i][0])
			resI_RH = i;
	}
	for (int i=0;i<23;i++)
	{
		if (vT > TEMP[i])
			resI_T = i;
	}
	deltaT = TEMP[resI_T+1] - TEMP[resI_T];
	deltaRH = DDWP[resI_RH][0] - DDWP[resI_RH+1][0];
	deltaRH = DDWP[resI_RH][resI_T] - DDWP[resI_RH+1][resI_T+1];
	deltaMes = TEMP[resI_T+1] - vT;

	res = DDWP[resI_RH+1][resI_T+1]


	for (int i=0;i<13;i++)
	{
		if (vH > DDWP[i][0])
			resI_RH = i;
	}
	for (int i=0;i<13;i++)
	{
		if (vH > DDWP[i][0])
		{

		}
	}

	if (vH == 0)
	 return 0;
 else
	 return GetMaxH(vT)*(10000-vH) / 10000;		*/
}

uint16_t GetRH_DDWP(uint16_t vT, uint16_t vD)
{
	uint16_t mxH;
	//Result:=0;
	if ((vT==0) || (vD==0)) return;
	mxH = GetMaxH(vT);
	if (mxH > 0)
	return 10000 - ((vD*10000) / mxH);

	//return (10000 - vD*10000) / mxH;
}

uint16_t AbsHum(uint16_t fTemp, uint16_t fRH)
{
	volatile float tT,tRH, tRez;
	tT=fTemp/100;
	tRH=fRH/100;
	tRez=((0.000002*tT*tT*tT*tT)+(0.0002*tT*tT*tT)+(0.0095*tT*tT)+( 0.337*tT)+4.9034)*tRH;
	return tRez;
}

uint16_t RelHum(uint16_t fTemp, uint16_t AbsRH)
{
	volatile float tT,tRH, tRez;
	//tT=(fTemp/100) + (fTemp%100);
	tT = fTemp;
	tT /= 100;
	tRH=AbsRH*100;
	tRez=tRH/((0.000002*tT*tT*tT*tT)+(0.0002*tT*tT*tT)+(0.0095*tT*tT)+( 0.337*tT)+4.9034);
	return tRez;
}

void KeepPID(uint16_t fKeep,uint16_t fDelta,uint8_t fNMech)
{
	int32_t	*IntVal;
	ClrDog;

	IntVal=&(pGD_TControl_Tepl->IntVal[fNMech]);

	IntX=fDelta;

	LngY=pGD_ConstMechanic->ConstMixVal[fNMech].v_PFactor;

	LngY=LngY*IntX;//(*IntVal);

	IntY=(int16_t)(LngY/10000);

	(*IntVal)=(fKeep-IntY)*100;

}


int16_t	SetPID(uint16_t fDelta,uint8_t fNMech,int16_t fMax, int16_t fMin)
{
	int32_t	*IntVal;
	ClrDog;

//	if (YesBit(pGD_Hot_Hand[fNMech].RCS,(/*cbNoMech+*/cbManMech))) continue;
	IntVal=&(pGD_TControl_Tepl->IntVal[fNMech]);

	IntX=fDelta;
		//(*IntVal)=(*IntVal)+IntX;
	LngY=pGD_ConstMechanic->ConstMixVal[fNMech].v_PFactor;
	LngY=LngY*IntX;//(*IntVal);
	IntY=(int16_t)(LngY/10000);
		//if (!IntY) continue;
	LngX=(*IntVal)/100;
		//IntZ=(*(pGD_Hot_Hand_Kontur+cHSmMixVal)).Position;
	LngX+=IntY;
	if (LngX>fMax)
	{
		(*IntVal)=(fMax-IntY)*100;
		LngX=fMax;
	}
	else
		if (LngX<fMin)
		{
			(*IntVal)=(fMin-IntY)*100;
			LngX=fMin;
		}
		else
			(*IntVal)+=(int32_t)((((long)IntX)*pGD_ConstMechanic->ConstMixVal[fNMech].v_IFactor)/100);

	if (!pGD_ConstMechanic->ConstMixVal[fNMech].v_IFactor)
		*IntVal=0;

	return LngX;
}

// ����������� ����� ������������ ��������� �������
void WindDirect(void)
{
	GD.Hot.PozFluger&=1;
	if (GD.TuneClimate.o_TeplPosition==180) 
	{
		GD.Hot.PozFluger=0;
		return;
	}
	//if (GD.Hot.MidlWind<GD.TuneClimate.f_WindStart) return;
	if (MidlWindCalc < GD.TuneClimate.f_WindStart) return;
	IntZ=GD.TControl.MeteoSensing[cSmDWindSens]+GD.TuneClimate.o_TeplPosition;
	IntZ%=360;
	GD.TControl.Tepl[0].CurrPozFluger=GD.Hot.PozFluger;
	if ((!GD.Hot.PozFluger)&&(IntZ
		>(90+f_DeadWindDirect))
		&&(IntZ<(270-f_DeadWindDirect)))
		GD.TControl.Tepl[0].CurrPozFluger=1;
	if ((GD.Hot.PozFluger)&&((IntZ
		<(90-f_DeadWindDirect))
		||(IntZ>(270+f_DeadWindDirect))))
		GD.TControl.Tepl[0].CurrPozFluger=0;
	if (GD.Hot.PozFluger!=GD.TControl.Tepl[0].CurrPozFluger)
	{
		GD.TControl.Tepl[0].CurrPozFlugerTime++;
		if (GD.TControl.Tepl[0].CurrPozFlugerTime<5)
			return;
		GD.Hot.PozFluger=GD.TControl.Tepl[0].CurrPozFluger;
	}
	GD.TControl.Tepl[0].CurrPozFlugerTime=0;
}



/*void _SetBitOutReg(char fnTepl,char fnMech,char fnBit,char fnclr,char fnSm)
{	char nBit,nByte,Mask;
	nBit=BitMech[fnTepl][fnMech][fnBit]&0x0F;
	if(!nBit) return;
	Mask=1;
	Mask<<=(nBit-1+fnSm);
	nByte=BitMech[fnTepl][fnMech][fnBit]/16;
	if (fnclr)
		OutR[nByte]&=(~Mask);		
	else	
		OutR[nByte]|=Mask;
	
}*/

void SetRelay(uint16_t nRelay)
{
char bRelay;
	if (GetIPCComMod(nRelay))
	{
		SetOutIPCDigit(1,nRelay,&bRelay);
		return;
	}
	if(!(nRelay--)) return;
	bRelay=1;
	bRelay<<=(nRelay % 8);
	if (nRelay>79) return;
	OutR[nRelay / 8] |=bRelay;
}
//----------------------------------------
void ClrRelay(uint16_t nRelay)
{
char bRelay;
	if (GetIPCComMod(nRelay))
	{
		SetOutIPCDigit(0,nRelay,&bRelay);
		return;
	}
	if(!(nRelay--)) return;
	bRelay=1;
	bRelay<<=(nRelay % 8);
	OutR[nRelay / 8] &=~(bRelay);
}

char TestRelay(uint16_t nRelay)
{
char bRelay;
	if (GetIPCComMod(nRelay)) return GetOutIPCDigit(nRelay,&bRelay);
	if(!(nRelay--)) return 0;
	bRelay=1;
	bRelay<<=(nRelay % 8);
	if (OutR[nRelay / 8] & bRelay) return 1;
	else return 0;
}


void __SetBitOutReg(char fnTepl,char fnMech,char fnclr,char fnSm)
{
	uint16_t nBit,nByte,Mask;

	if (fnTepl==-1) 
	  nBit=fnMech;
	else
	  nBit=GD.MechConfig[fnTepl].RNum[fnMech];
	if(!nBit) return;
	if (GetIPCComMod(nBit))
	{
		SetOutIPCDigit(!fnclr,nBit+fnSm,&Mask);
		return;
	}
	nBit--;
	nBit+=fnSm;
	nByte=nBit>>3;
	nBit=nBit&7;
	Mask=1;
	Mask<<=nBit;
	if (nByte>10) return;
	if (fnclr)
		OutR[nByte]&=(~Mask);		
	else	
		OutR[nByte]|=Mask;
	
}
