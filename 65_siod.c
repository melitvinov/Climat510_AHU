#define cSIOFazaPump	1
#define cSIOFazaVal		2
#define cSIOFazaPause	3
#define cSIOFazaEnd		4


void SetUpSiod(char fnTepl)
{
	char nMas;
	if (!pGD_Control_Tepl->sio_SVal) return;
	pGD_Hot_Tepl->OtherCalc.TimeSiod=pGD_TControl_Tepl->TimeSIO;
	for (nMas=0;nMas<GD.Control.ConfSTepl;nMas++)
	{
	  if (nMas==fnTepl) continue;
	  if (GD.TControl.Tepl[nMas].FazaSiod) return;
	}
	if (!pGD_Hot_Tepl->AllTask.SIO) return;
	if (pGD_TControl_Tepl->PauseSIO<1440)
		pGD_TControl_Tepl->PauseSIO++;	
 
	IntX=0;
	if ((((pGD_Hot_Tepl->InTeplSens[cSmRHSens].Value-pGD_Hot_Tepl->AllTask.DoRHAir)>GD.TuneClimate.sio_RHStop)
		||(pGD_Hot_Tepl->InTeplSens[cSmRHSens].Value>9600))
		&&(pGD_Hot_Tepl->AllTask.DoRHAir)) return;
	if ((pGD_Hot_Tepl->AllTask.DoTHeat-CURRENT_TEMP_VALUE)>GD.TuneClimate.sio_TStop) return;
	if (((CURRENT_TEMP_VALUE-pGD_Hot_Tepl->AllTask.DoTHeat)<GD.TuneClimate.sio_TStart)
		&&(((pGD_Hot_Tepl->AllTask.DoRHAir-pGD_Hot_Tepl->InTeplSens[cSmRHSens].Value)<GD.TuneClimate.sio_RHStart)
		||(!pGD_Hot_Tepl->InTeplSens[cSmRHSens].Value))) return;	

	IntY=CURRENT_TEMP_VALUE-pGD_Hot_Tepl->AllTask.DoTHeat;
	CorrectionRule(GD.TuneClimate.sio_TStart,GD.TuneClimate.sio_TEnd,GD.TuneClimate.sio_TStartFactor-GD.TuneClimate.sio_TEndFactor,0);
	IntX=(int)(GD.TuneClimate.sio_TStartFactor-IntZ);

	IntY=pGD_Hot_Tepl->AllTask.DoRHAir-pGD_Hot_Tepl->InTeplSens[cSmRHSens].Value;
	CorrectionRule(GD.TuneClimate.sio_RHStart,GD.TuneClimate.sio_RHEnd,GD.TuneClimate.sio_RHStartFactor-GD.TuneClimate.sio_RHEndFactor,0);
	IntZ=GD.TuneClimate.sio_RHStartFactor-IntZ;
	if ((pGD_Hot_Tepl->InTeplSens[cSmRHSens].Value)&&(pGD_Hot_Tepl->AllTask.DoRHAir))
		if (IntX>IntZ) 
			IntX=IntZ;
	if (pGD_TControl_Tepl->PauseSIO<IntX) return;
	if (YesBit(RegLEV,cSmSIONo)) return;
	pGD_TControl_Tepl->FazaSiod=cSIOFazaPump;
	pGD_TControl_Tepl->TimeSIO+=pGD_Hot_Tepl->AllTask.SIO;
	pGD_TControl_Tepl->PauseSIO=0;
	pGD_TControl_Tepl->CurVal=0;
}
void DoSiod(void)
{
	char NSIO;
	
	if (!(YesBit((*(pGD_Hot_Hand+cHSmSIOPump)).RCS,cbManMech)))
		(*(pGD_Hot_Hand+cHSmSIOPump)).Position=0;
	else return;
	if (!(YesBit((*(pGD_Hot_Hand+cHSmSIOVals)).RCS,cbManMech)))
		(*(pGD_Hot_Hand+cHSmSIOVals)).Position=0;
	else return;			

	NSIO=pGD_Control_Tepl->sio_SVal;
	if (cNumValSiodMax<pGD_Control_Tepl->sio_SVal)
		NSIO=cNumValSiodMax;

	switch(pGD_TControl_Tepl->FazaSiod)
	{
	case cSIOFazaVal:
		IntX=1;
		IntX<<=(pGD_TControl_Tepl->CurVal%4);
		SetBit((*(pGD_Hot_Hand+cHSmSIOVals)).Position,IntX);
		if (!pGD_TControl_Tepl->TPauseSIO)	pGD_TControl_Tepl->TPauseSIO=pGD_Hot_Tepl->AllTask.SIO;	
	case cSIOFazaPause:
		if (!pGD_TControl_Tepl->TPauseSIO)	
		{
			pGD_TControl_Tepl->TPauseSIO=sio_ValPause;
			pGD_TControl_Tepl->CurVal++;
		}	
	case cSIOFazaPump:
		(*(pGD_Hot_Hand+cHSmSIOPump)).Position=1;
		if (!pGD_TControl_Tepl->TPauseSIO)	pGD_TControl_Tepl->TPauseSIO=sio_ValPause;
		break;

	case cSIOFazaEnd:
		pGD_TControl_Tepl->FazaSiod=0;
		return;

	default: return;	
	}
	if(--pGD_TControl_Tepl->TPauseSIO)	return;	
	if ((pGD_TControl_Tepl->FazaSiod==cSIOFazaPause)&&(pGD_TControl_Tepl->CurVal<NSIO)) pGD_TControl_Tepl->FazaSiod=cSIOFazaVal;
	else pGD_TControl_Tepl->FazaSiod++;

}
