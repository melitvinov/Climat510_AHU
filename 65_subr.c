#include "keyboard.h"

#define NameSens(ns)       w_txt(NameASens[ns].Name)
#define EdSens(ns)         TxtEd(ns)


#define CURRENT_TEMP1_VALUE (pGD_Hot_Tepl->InTeplSens[cSmTSens1].Value)
#define CURRENT_TEMP2_VALUE (pGD_Hot_Tepl->InTeplSens[cSmTSens2].Value)
#define CURRENT_TEMP3_VALUE (pGD_Hot_Tepl->InTeplSens[cSmTSens3].Value)
#define CURRENT_TEMP4_VALUE (pGD_Hot_Tepl->InTeplSens[cSmTSens4].Value)

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
	GD.TControl.SumSun+=((long int)GD.TControl.MeteoSensing[cSmFARSens]);
	GD.TControl.MidlSR=((((long int)GD.TControl.MidlSR)*(1000-o_MidlSRFactor))/1000
		+((long int)GD.TControl.MeteoSensing[cSmFARSens])*o_MidlSRFactor);
	GD.Hot.MidlSR=(int)(GD.TControl.MidlSR/1000);
	if (GetMetSensConfig(cSmFARSens))
	{
		GD.Hot.SumSun=(int)((GD.TControl.SumSun*6)/1000);
	}
	GD.Hot.MidlWind=(int)((((long int)GD.Hot.MidlWind)*(1000-o_MidlWindFactor)+((long int)GD.TControl.MeteoSensing[cSmVWindSens])*o_MidlWindFactor)/1000);

}

void CheckMidlSr(void)
{
	if (GetMetSensConfig(cSmFARSens))
	{
		GD.Hot.SumSun=(int)((GD.TControl.SumSun*6)/1000);
	}
	GD.Hot.MidlSR=(int)(GD.TControl.MidlSR/1000);


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
        keyboardSetSIM(100);
		NDat=0;
		if (fTipReset>2) MemClr(&GD.Hot,(sizeof(eHot)));
        MemClr(&GD.Control,sizeof(eControl)
                +sizeof(eFullCal)
                +sizeof(eLevel)
                +sizeof(eTimer)*cSTimer);
ClrDog; 
        MemClr(&GD.ConstMechanic[0],sizeof(eTuneClimate)+sizeof(eTControl)+sizeof(eStrategy)*cSStrategy*cSTepl+sizeof(eConstMech)*cSTepl+sizeof(eMechConfig)*cSTepl);
        MemClr(&GD.uInTeplSens[0][0],sizeof(uint16_t)*(cConfSMetSens+cSTepl*cConfSSens));
ClrDog;
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

#warning !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! IP
		GD.Control.NFCtr=NumCtr;
		GD.Control.IPAddr[0]=192;
		GD.Control.IPAddr[1]=168;
		GD.Control.IPAddr[2]=1;
		GD.Control.IPAddr[3]=100+NumCtr;

		GD.Control.Read1W=9;
		GD.Control.Write1W=4;
		GD.Control.ConfSTepl=cConfSTepl;
		GD.Control.Language=cDefLanguage;
		GD.Control.Cod=111;
		GD.Control.Screener=40;

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
			for (IntX=0;IntX<cSStrategy;IntX++)
			{
				for (ByteY=0;ByteY<sizeof(eStrategy);ByteY++)
					(*((&(pGD_Strategy_Tepl[IntX].TempPower))+ByteY))=(*((&DefStrategy[IntX].TempPower)+ByteY));
			}

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
/* ������������� ��������� ���������� */
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

void WindDirect(void)
{
	GD.Hot.PozFluger&=1;
	if (GD.TuneClimate.o_TeplPosition==180) 
	{
		GD.Hot.PozFluger=0;
		return;
	}
	if (GD.Hot.MidlWind<GD.TuneClimate.f_WindStart) return;
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
{	uint16_t nBit,nByte,Mask;
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
