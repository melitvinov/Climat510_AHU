#define ADDRESS_FRAM_SUM	31000 //(sizeof(GD)+sizeof(eBlockEEP)*SUM_BLOCK_EEP)
//================= ������ 403 =====================
/*-------------------------------------------------
        �������� ������������ ��� ������ ����������
---------------------------------------------------*/
#ifndef STM32_UNIT
void init8051(void) {
        ClrDog;
        P2=0;
        TMOD=0x21;      /* ������������� 8 �������� T1 � 16 ����� T0 */
        TCON=0x55;      /* ������ �������� T0,T1 � �� ������ INT0,INT1 */
        IP=0x15;        /* ��������� PS,INT0,INT1 */
        TH0=0xff;
/* ������������ ����������������� ����� */
 /*        ET1=0;         ������ ���������� ������� 1*/
        SCON=0xF0;      /*����� 3 (9��� ����)*/
        TMOD=0x21;      /*������ 1 � ������������� , ������ 0 - 16 ����*/
        TH1=0xFD;       /*�������� 9600bps � ������� 11.059 ��� */
        TR1=1;          /*������ 1 - �������� ����*/
        PS=1;           /*��������� ����� ������*/
/*        ES=1;           �������� �������� ������ �����*/
/* ���������� ����1 �� ����� � �0-�7 �� ���� � ����2 �� ����� */
        Port1=0;
        adru=u_port1;
        adra=0;
        Port1=1;
        Port2=0;
        adru=u_port2;
        Port2=1;
        ClrDog;
}
#endif 

//=================================================
//          ������������ ������ � �������
//=================================================
// ------------------------------------------------
//               ������� �����
//-------------------------------------------------
void MemClr(void *pp1,uint32_t n) {
        char *p;
        p=pp1;
        while(n--) *p++=0;
        ClrDog;
		}
void MemCopy(char *pp1, char *pp2, uint32_t n) { //dest,source,number
        while(n--) *pp1++ = *pp2++;
        ClrDog;
		}

uchar   nBlEEP;

#ifndef STM32_UNIT
typedef struct eBlockEEP {
        int AdrCopyRAM;
        uint    Size;
        uint    CSum;
        char    Erase;
        };
		

int		AdrRAM;	  //int
#else
uchar*	AdrRAM;

#endif
	
uint    AdrEEP;
uint    SizeEEP;
char    WriteEEP;


uint16_t CalcRAMSum(uchar* fAddr,uint32_t fSize)
{
	uint tSum,i;
	tSum=0x0110;
	for (i = 0; i < fSize; i++)
	{
		tSum+=fAddr[i];
		tSum%=65000;
	}
	return tSum;
}


/* ���� � ���������� - �������� ������ � ������� ����������
   � ������ � EEPROM � ����������� ������*/
void    SetInSaveRam(void) {
    	uint16_t cSum;
    	uint16_t     vVal;
		uint8_t	nBlFRAM;
		if(!SizeEEP) return;
         AdrEEP=1;
         for(nBlFRAM=0; nBlFRAM < SUM_BLOCK_EEP; nBlFRAM++){
          ClrDog;
          vVal=AdrRAM-BlockEEP[nBlFRAM].AdrCopyRAM;
          if((vVal>=0)&&(vVal<BlockEEP[nBlFRAM].Size)){
              AdrEEP+=vVal;  /* ���� � ������� ��������� �����*/
              SendBlockFRAM((uint32_t)(AdrRAM)-(uint32_t)(BlockEEP[0].AdrCopyRAM),AdrRAM,SizeEEP);
              //I2C_Mem_Write(0,);
              cSum=CalcRAMSum(BlockEEP[nBlFRAM].AdrCopyRAM,BlockEEP[nBlFRAM].Size);
              //I2C_Mem_Write(0,);
              SendBlockFRAM(ADDRESS_FRAM_SUM+nBlFRAM*2,&cSum,2);
              BlockEEP[nBlFRAM].CSum=cSum;
              BlockEEP[nBlFRAM].Erase=2; /* �������� ������� �������*/
              ClrDog;
              return;
              }
          AdrEEP+=(BlockEEP[nBlFRAM].Size+2);
          }
     	//SendBlockFRAM(sizeof(GD),&BlockEEP,sizeof(BlockEEP));
}

/*------ �������� ����� ����� ����� CONTROL ---------------------------*/
char	TestRAM0(void) {
        ClrDog;
        uint16_t cSum;
    	RecvBlockFRAM(ADDRESS_FRAM_SUM,&BlockEEP[0].CSum,2);
        cSum=CalcRAMSum(BlockEEP[0].AdrCopyRAM,BlockEEP[0].Size);
        if(cSum!=BlockEEP[0].CSum) return 2;
/*���� ����� ����� �������, �� ���������� ������� ���������*/
        return 0;
}

/*------ �������� ����� ����� ��� � ��� ������ return 2 --*/
char TestRAM(void) {
    	uint8_t nBlFRAM;
        for(nBlFRAM=0; nBlFRAM < SUM_BLOCK_EEP; nBlFRAM++){
          ClrDog;
 /*---���� ������� ����� ����� ���������� �����----*/
          RecvBlockFRAM(ADDRESS_FRAM_SUM+nBlFRAM*2,&BlockEEP[nBlFRAM].CSum,2);
          if(BlockEEP[nBlFRAM].CSum!=CalcRAMSum(BlockEEP[nBlFRAM].AdrCopyRAM,BlockEEP[nBlFRAM].Size)) return 2;
          }
		  return 0;
}

/*-- �������������� �� EEPROM, � ��� ������ ���������� � EEPROM------*/
void	TestFRAM(char EraseBl) {
	    uint16_t cSum;
	    uint8_t nBlFRAM;
        for(nBlFRAM=0;nBlFRAM < SUM_BLOCK_EEP; nBlFRAM++){
        	RecvBlockFRAM(BlockEEP[nBlFRAM].AdrCopyRAM-(uint32_t)(BlockEEP[0].AdrCopyRAM),BlockEEP[nBlFRAM].AdrCopyRAM,BlockEEP[nBlFRAM].Size);
        	//I2C_Mem_Read(0,

        	RecvBlockFRAM(ADDRESS_FRAM_SUM+nBlFRAM*2,&BlockEEP[nBlFRAM].CSum,2);
            cSum=CalcRAMSum(BlockEEP[nBlFRAM].AdrCopyRAM,BlockEEP[nBlFRAM].Size);
          ClrDog;
          if(CalcRAMSum(BlockEEP[nBlFRAM].AdrCopyRAM,BlockEEP[nBlFRAM].Size)!=BlockEEP[nBlFRAM].CSum || (EraseBl==(nBlFRAM+10))) {
/* ���� �������� ����� ����� ���, �� ��������� EEPROM */
           InitGD(5);
           SendBlockFRAM(BlockEEP[nBlFRAM].AdrCopyRAM-(uint32_t)(BlockEEP[0].AdrCopyRAM),BlockEEP[nBlFRAM].AdrCopyRAM,BlockEEP[nBlFRAM].Size);
           cSum=CalcRAMSum(BlockEEP[nBlFRAM].AdrCopyRAM,BlockEEP[nBlFRAM].Size);
           SendBlockFRAM(ADDRESS_FRAM_SUM+nBlFRAM*2,&cSum,2);
           BlockEEP[nBlFRAM].CSum=cSum;
           BlockEEP[nBlFRAM].Erase=0; //++
//           RecvBlockFRAM(ADDRESS_FRAM_SUM+nBlFRAM*2,&BlockEEP[nBlFRAM].CSum,2);
           } //else {BlockEEP[nBlFRAM].Erase=3;}
/* ������������ ����� ����� ��� ����� ������������� */
          }
    	//SendBlockFRAM(sizeof(GD),&BlockEEP,sizeof(BlockEEP));
}

/*-- ���� ������ � �� � ���� NumBlock ,
     ���� ���������� ����� ���� ���� �������� ----*/
void ReWriteFRAM(void) {
		uint16_t cSum;
         ClrDog;
         ByteX=NumBlock-1;
         SendBlockFRAM(BlockEEP[ByteX].AdrCopyRAM-(uint32_t)(BlockEEP[0].AdrCopyRAM),BlockEEP[ByteX].AdrCopyRAM,BlockEEP[ByteX].Size);
         cSum=CalcRAMSum(BlockEEP[ByteX].AdrCopyRAM,BlockEEP[ByteX].Size);
         SendBlockFRAM(ADDRESS_FRAM_SUM+ByteX*2,&cSum,2);
         BlockEEP[ByteX].CSum=cSum;
     	//SendBlockFRAM(sizeof(GD),&BlockEEP,sizeof(BlockEEP));

}/*------------------------------------------------
        ������������ � ��������� ������ ��� ������ "����"
        � �����������
TipRes
0-������ �����-��� ������� � �������� Control
1-������ ���� � ��� �������
2-������������� RAM - GD
10+2-������������� EEP- ���������
10+1-������������� EEP- ����������
10+0-������������� EEP- ���������
--------------------------------------------------*/
void TestMem(uchar TipReset) {
	   ClrDog;
       InitBlockEEP();  /*������������ � GD */
	   ButtonReset();
//	   TipReset=2;
/*------ �������� ����� ����� ����� CONTROL ---------------------------*/
       if(TipReset>5) InitGD(5);
       if((!Menu) && TestRAM0()) TipReset=2;
       if(!TipReset) return;
/*------ �������� ����� ����� ���  -------------------------------*/
       ClrDog;
       if((TipReset==1)&& TestRAM()) TipReset++;
       if (TipReset<2) return;
       Menu=0;
       ClrDog;
/*-- �������������� �� EEPROM, � ��� ������ ���������� � EEPROM------*/
	   TestFRAM(TipReset);
       ClrDog;
       ButtonReset();
       GetRTC();
}



