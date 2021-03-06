#include "stm32f10x_Rootines.h"
#include "misc.h"
#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rtc.h"
#include "stm32f10x_i2c.h"
#include "stm32f10x_bkp.h"
#include "stm32f10x_pwr.h"
#include "stm32f10x_clock.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_iwdg.h"
#include "I2CSoft.h"


//uint8_t* mymac = 0x1FFFF7EE;

//uint8_t* mymac[6];
uint8_t mymac[6];

static unsigned char myip[4] = {192,168,1,231};

uint16_t* IWDG_Reset;
uint8_t KeyDelay;

//*********************************************************
#define MIN(a, b)          ({ typeof(a) _a = (a); typeof(b) _b = (b); _a < _b ? _a : _b; })

unsigned int MurmurHash2 ( const void * key, int len, unsigned int seed )
{
	// 'm' and 'r' are mixing constants generated offline.
	// They're not really 'magic', they just happen to work well.

	const unsigned int m = 0x5bd1e995;
	const int r = 24;

	// Initialize the hash to a 'random' value

	unsigned int h = seed ^ len;

	// Mix 4 bytes at a time into the hash

	const unsigned char * data = (const unsigned char *)key;

	while(len >= 4)
	{
		unsigned int k = *(unsigned int *)data;

		k *= m;
		k ^= k >> r;
		k *= m;

		h *= m;
		h ^= k;

		data += 4;
		len -= 4;
	}

	// Handle the last few bytes of the input array

	switch(len)
	{
	case 3: h ^= data[2] << 16;
	case 2: h ^= data[1] << 8;
	case 1: h ^= data[0];
	        h *= m;
	};

	// Do a few final mixes of the hash to ensure the last few
	// bytes are well-incorporated.

	h ^= h >> 13;
	h *= m;
	h ^= h >> 15;

	return h;
}

uint HAL_sys_read_sn(uint8_t *dst, uint8_t maxsize)
{
    const uint8_t *src = (const u8 *)0x1FFFF7E8;
    uint16_t i;

    for (i = 0; i < MIN(maxsize, 12U); i++)
        *dst++ = *src++;

    return i;
}

void netapp_get_macaddr()//(uint8_t *dst)
{
	uint8_t sn[12];
	uint16_t sn_size = HAL_sys_read_sn(sn, 12);

    uint32_t hash = MurmurHash2(sn, 12, 0);


    mymac[0] = 0x02;
    mymac[1] = 0x00;
    mymac[2] = hash;
    mymac[3] = hash >> 8;
    mymac[4] = hash >> 16;
    mymac[5] = hash >> 24;

//    dst[0] = 0x02;
//    dst[1] = 0x00;
//    dst[2] = hash;
//    dst[3] = hash >> 8;
//    dst[4] = hash >> 16;
//    dst[5] = hash >> 24;
}

//*********************************************************

void CheckWithoutPC(void)
{
	if (NMinPCOut>3)
	{
		NMinPCOut=0;
		USART_PC_Configuration(&GD.Control.NFCtr,AdrGD,&GD.SostRS,&NumBlock,9600);
		simple_server(AdrGD,&GD.SostRS,&NumBlock,GD.Control.IPAddr,mymac,&PORTNUM);
		//simple_client(AdrGD,&GD.SostRS,&NumBlock,GD.Control.cIPAddr,mymac,&PORTNUM);
		GD.TControl.Tepl[0].WithoutPC++;
	}
	NMinPCOut++;
}

void Init_STM32(void) {

		//I2CRel_MEM_Configuration();

		//I2C_BLOCK_Configuration();
		GPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB| RCC_APB2Periph_GPIOD| RCC_APB2Periph_GPIOC, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
		GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
		i2_fm_Init();

		ClrDog;
		ReadFromFRAM();
		ClrDog;

		InitLCD();
		ClrDog;


		USART_PC_Configuration(&GD.Control.NFCtr,AdrGD,&GD.SostRS,&NumBlock,9600);


		InitMainTimer();
		SETEA;

		// ��������� 105
		netapp_get_macaddr();

		Keyboard_Init();
		InitRTC();
	    PORTNUM=DEF_PORTNUM;

		simple_server(AdrGD,&GD.SostRS,&NumBlock,GD.Control.IPAddr, mymac ,&PORTNUM);


		w1Init();
		Init_MEAS_INPUT();
		Init_IWDG(&GD.TControl.Tepl[0].nReset);
		Check_IWDG();
		USART_OUT_Configuration(9600);

		//I2C_DMAMem_Transfer(I2C1_Buffer_Tx,8,DMA_DIR_PeripheralDST);
		//������
			GPIO_InitTypeDef GPIO_InitStructure;
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
			GPIO_Init(GPIOA, &GPIO_InitStructure);
			GPIO_WriteBit(GPIOA,GPIO_Pin_4,Bit_RESET);

		CheckInputConfig();
		InitIPCTimer();
}

/***************************************************************************//**
 * @brief  Setting MEASUREMENTS
 ******************************************************************************/



/***************************************************************************//**
 * @brief  Setting DATA pins to input mode
 ******************************************************************************/
void Keyboard_Init(void)
{
	KEYB_STARTUP;
	GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = KEYB_OUT;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(PORT_KEYB_OUT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = KEYB_IN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(PORT_KEYB_IN, &GPIO_InitStructure);

}


char CheckKeyboardSTM()
{
	int i;
	uint16_t sendB;
    uint16_t u16Temp=0;
	Keyboard_Init();
	if(KeyDelay>1) {KeyDelay--;return 0;}

	for (i=0;i<16;i++)
	{

		//GPIO_Write(PORT_KEYB_OUT, u16Temp);
	    u16Temp = GPIO_ReadOutputData(PORT_KEYB_OUT)&(~KEYB_OUT);
	    u16Temp |=  0x000f&~(1<<(i%4));//����������� ���� ����� �� 0xff ����� ��������������
	    GPIO_Write(PORT_KEYB_OUT, u16Temp);
		NOP;NOP;

		sendB=i/4;
		sendB=0x01<<sendB;
		u16Temp= GPIO_ReadInputData(PORT_KEYB_IN)&KEYB_IN;
		if (!(u16Temp&sendB))
		{
			SIM=i; BITKL=1;
			KeyDelay=4;
			return 1;
		}

	}
	return 0;
}

void InitIPCTimer(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

    RCC->APB1ENR |= RCC_APB1Periph_TIM3;


    TIM3->PSC = 8000-1; // Clock prescaler;

    TIM3->ARR = 50;//33 // Auto reload value
    TIM3->SR = 0; // Clean interrups & events flag

    TIM3->DIER = TIM_DIER_UIE; // Enable update interrupts

    /* NVIC_SetPriority & NVIC_EnableIRQ defined in core_cm3.h */
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 10;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 10;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    TIM3->EGR = TIM_EGR_UG;
    TIM3->CR1 |= TIM_CR1_CEN; // Enable timer
}

void TIM3_IRQHandler(void)
{

	Reg48ToI2C();

	TIM3->SR=0;

}

void InitMainTimer(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

    RCC->APB1ENR |= RCC_APB1Periph_TIM2;

    TIM2->PSC = 8000-1; // Clock prescaler;

    TIM2->ARR = 100; // Auto reload value
    TIM2->SR = 0; // Clean interrups & events flag

    TIM2->DIER = TIM_DIER_UIE; // Enable update interrupts

    /* NVIC_SetPriority & NVIC_EnableIRQ defined in core_cm3.h */
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    TIM2->EGR = TIM_EGR_UG;
    TIM2->CR1 |= TIM_CR1_CEN; // Enable timer
}

void TIM2_IRQHandler(void)
{
	//SumAnswers=IntCount;
/*	CLREA;
	Mes=IntCount;
	//SumAnswers++;
	//nPort=0;
	GPIOB->ODR=(GPIOB->ODR&(~0x100))|((nPort%2)<<8);
	nPort>>=1;
	GPIOA->ODR=(GPIOA->ODR&(~0x800))|((nPort%2)<<11);
	nPort>>=1;
	GPIOA->ODR=(GPIOA->ODR&(~0x700))|((nPort%8)<<8);
	IntCount=0;
	SETEA;
	ReadyIZ=1;*/
	CheckKeyboardSTM();
	//Reg48ToI2C();
	//SendCharPC(22);
	/*if (Second%2)
		GPIO_WriteBit(GPIOC, GPIO_Pin_9, Bit_SET);
	else
		GPIO_WriteBit(GPIOC, GPIO_Pin_9, Bit_RESET);*/
	TIM2->SR=0;

}

static void wait_for_write_completion(void)
{
    while (! (RTC->CRL & RTC_CRL_RTOFF));
}


void InitRTC(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_PWREN | RCC_APB1ENR_BKPEN;	// power to the rtc and backup registers

	// if rtc config has gone (magic mismatch), do reinit
	if (BKP->DR1 != 0xA5A6 || !(RCC->BDCR & RCC_BDCR_RTCEN))
	{
		PWR->CR |= PWR_CR_DBP;  // allow access to RTC and backup registers
		wait_for_write_completion();
		RTC->CRL |= RTC_CRL_CNF;    // enter config mode
		wait_for_write_completion();

		RCC->BDCR |= RCC_BDCR_BDRST;    // start resetting backup domain
		RCC->BDCR &= ~RCC_BDCR_BDRST;   // stop resetting backup domain :-)

		RCC->BDCR |= RCC_BDCR_LSEON;     // start xtal and wait to stabilize
		while (! (RCC->BDCR & RCC_BDCR_LSERDY));

		RCC->BDCR |= RCC_BDCR_RTCSEL_LSE;
		RCC->BDCR |= RCC_BDCR_RTCEN;

		while (! (RTC->CRL & RTC_CRL_RSF));

		// 1 second period
		RTC->PRLL = 0x7FFF;
		RTC->PRLH = 0;
		wait_for_write_completion();

		uint32_t timestamp = (11*60+55)*60; // here: 1st January 2000 11:55:00
		RTC->CNTL = timestamp;
		RTC->CNTH = timestamp >> 16;
		wait_for_write_completion();

		RTC->CRL &= ~RTC_CRL_CNF;    // exit config mode
		wait_for_write_completion();

		BKP->DR1 = 0xA5A6;
		PWR->CR &= ~PWR_CR_DBP;  // forbid access to backup registers
	}
}

int GetRTCSecond(void)
{
	uint32_t t;
	while ( ( t = RTC_GetCounter() ) != RTC_GetCounter() ) { ; }

	return t % 60;
}


#define PORT1WIRE	GPIOB
#define PIN1WIRE	GPIO_Pin_12

void w1Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = PIN1WIRE;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(PORT1WIRE, &GPIO_InitStructure);
}

int16_t w1reset()
{
	uint16_t timeout,fRes=0;
	PORT1WIRE->BSRR|=PIN1WIRE;
	for(timeout=0;timeout<10;timeout++);
	PORT1WIRE->BRR|=PIN1WIRE;
	for(timeout=0;timeout<450;timeout++);
	PORT1WIRE->BSRR|=PIN1WIRE;
	PORT1WIRE->CRH=PORT1WIRE->CRH&0xFFF0FFFF;
	PORT1WIRE->CRH|=0x80000;
	for(timeout=0;timeout<8;timeout++);
	for(timeout=0;timeout<200;timeout++)
	{
		if  (!(PORT1WIRE->IDR&PIN1WIRE))
		{
			fRes++;

		}
	//	else if (fRes) break;

	}
	PORT1WIRE->CRH=PORT1WIRE->CRH&0xFFF0FFFF;
	PORT1WIRE->CRH|=0x70000;
	PORT1WIRE->BSRR|=PIN1WIRE;
	SendByte1W=fRes;

}

void w1_check()
{
	uint16_t timeout;
	ToHiTime=0;
	ToLowTime=0;
	PORT1WIRE->BSRR|=PIN1WIRE;
	for(timeout=0;timeout<10;timeout++);
	PORT1WIRE->BRR|=PIN1WIRE;
	for(timeout=0;timeout<200;timeout++)
	{
		if  ((PORT1WIRE->IDR&PIN1WIRE))
		{
			ToLowTime++;

		}
		else break;
	}
	PORT1WIRE->BSRR|=PIN1WIRE;
	for(timeout=0;timeout<200;timeout++)
	{
		if  (!(PORT1WIRE->IDR&PIN1WIRE))
		{
			ToHiTime++;

		}
		else break;
	}
}

void w1_wr()
{
	uint16_t timeout;
	uint8_t i;
	for(i=0;i<8;i++)
	{
		PORT1WIRE->BRR|=PIN1WIRE;
		for(timeout=0;timeout<3;timeout++);
		if ((SendByte1W>>i)&0x01)
			PORT1WIRE->BSRR|=PIN1WIRE;
		for(timeout=0;timeout<90;timeout++);
		PORT1WIRE->BSRR|=PIN1WIRE;
		for(timeout=0;timeout<25;timeout++);
	}

}
void w1_rd()
{
	uint8_t i;
	uint16_t timeout,fRes=0,fShortTime,fLongTime;
	SendByte1W=0;
	fShortTime=45;
	fLongTime=0;
	for(i=0;i<8;i++)
	{
		fRes=0;
		PORT1WIRE->BRR|=PIN1WIRE;
//����������� ����� 0 ������
		for(timeout=0;timeout<3;timeout++);
		PORT1WIRE->CRH=PORT1WIRE->CRH&0xFFF0FFFF;
		PORT1WIRE->CRH|=0x80000;		PORT1WIRE->BSRR|=PIN1WIRE;
		//for(timeout=0;timeout<5;timeout++)
		for(timeout=0;timeout<20;timeout++)
		{
			if  ((PORT1WIRE->IDR&PIN1WIRE))
			{
				fRes++;
			}
		}
		for(timeout=0;timeout<20;timeout++);
		if (fRes>7)//�� 2-� �� 8-��
			SendByte1W|=(0x01<<i);
		PORT1WIRE->CRH=PORT1WIRE->CRH&0xFFF0FFFF;
		PORT1WIRE->CRH|=0x70000;
		PORT1WIRE->BSRR|=PIN1WIRE;
		for(timeout=0;timeout<15;timeout++);
		if (fRes<fShortTime) fShortTime=fRes;
		if (fRes>fLongTime) fLongTime=fRes;
	}
	ToHiTime=fShortTime;
	ToLowTime=fLongTime;


}
void CrcCalc()
{
	unsigned char *mas;
	unsigned char Len;
	unsigned char i,dat,crc,fb,st_byt;
	mas=Buf1W;
	Len=SendByte1W;
	  st_byt=0; crc=0;
	  do{
	    dat=mas[st_byt];
	    for( i=0; i<8; i++) {  // ������� ����� � �����
	      fb = crc ^ dat;
	      fb &= 1;
	      crc >>= 1;
	      dat >>= 1;
	      if( fb == 1 ) crc ^= 0x8c; // �������
	    }
	    st_byt++;
	  } while( st_byt < Len ); // ������� ������ � �������
	  SendByte1W=crc;
}

void Reg48ToI2C()
{
uint16_t i;
//	for (i=0;i<8;i++)
//		I2C_Rel_Write(OutR[i],i);
	SendIPC(&GD.Hot.Tepl[0].ConnectionStatus);
}

void OutReg()
{
}

void SendBlockFRAM(uint16_t fStartAddr,uint8_t* AdrBlock,uint16_t sizeBlock)
{
	uint16_t CSum;
	uint16_t i,fSS;
	//I2C_Mem_Write(0,fStartAddr,AdrBlock,sizeBlock);
	for (i=0;i<sizeBlock/2000+1;i++)
	{
		ClrDog;
		fSS=2000;
		if (i==sizeBlock/2000)
			fSS=sizeBlock%2000;
		fm_Write(fStartAddr+i*2000,AdrBlock+i*2000,fSS,&CSum);
	}

//	I2C_MainLoad(0,AdrBlock,AdrBlock,I2C_TP_MEM,sizeBlock,I2C_Direction_Transmitter);
}

void RecvBlockFRAM(uint16_t fStartAddr,uint8_t* AdrBlock,uint16_t sizeBlock)
{
	uint16_t CSum;
	uint16_t i,fSS;

	//I2C_Mem_Read(0,fStartAddr,AdrBlock,sizeBlock);
	//I2C_MainLoad(0xA0,0,AdrBlock,I2C_TP_MEM,sizeBlock,I2C_Direction_Receiver);
	for (i=0;i<sizeBlock/2000+1;i++)
	{
		ClrDog;
		fSS=2000;
		if (i==sizeBlock/2000)
			fSS=sizeBlock%2000;

		fm_Read(fStartAddr+i*2000,AdrBlock+i*2000,fSS,&CSum);
	}
}


void WriteToFRAM()
{
	char i;
	uint16_t fsizeSend;
	int tTepl;
	ClrDog;
    InitBlockEEP();  /*������������ � GD */
	SendBlockFRAM((uint32_t)(&GD.TControl)-(uint32_t)(BlockEEP[0].AdrCopyRAM),(uchar*)(&GD.Hot),sizeof(GD.Hot));
	ClrDog;
	SendBlockFRAM((uint32_t)(&GD.TControl)-(uint32_t)(BlockEEP[0].AdrCopyRAM)+sizeof(GD.Hot),(uchar*)(&GD.TControl),sizeof(eTControl));
//	SendBlockFRAM(0,(uchar*)(&GD),sizeof(GD));
	ClrDog;
//	SendBlockFRAM(sizeof(GD),&BlockEEP,sizeof(BlockEEP));
}

void ReadFromFRAM()
{
	char i;
	uint16_t fsizeSend;
	ClrDog;
    InitBlockEEP();  /*������������ � GD */
	RecvBlockFRAM((uint32_t)(&GD.TControl)-(uint32_t)(BlockEEP[0].AdrCopyRAM),(uchar*)(&GD.Hot),sizeof(GD.Hot));
//	ClrDog;
	RecvBlockFRAM((uint32_t)(&GD.TControl)-(uint32_t)(BlockEEP[0].AdrCopyRAM)+sizeof(GD.Hot),(uchar*)(&GD.TControl),sizeof(GD.TControl));
	//RecvBlockFRAM(0,(uchar*)(&GD),sizeof(GD));
//	RecvBlockFRAM(0,(uchar*)(&GD),sizeof(GD));

//	RecvBlockFRAM(sizeof(GD),&BlockEEP,sizeof(BlockEEP));

}

void SetRTC(void) {
		eDateTime	fDateTime;
        fDateTime.sec=Second;
        fDateTime.min=CtrTime%60;
        fDateTime.hour=CtrTime/60;
        fDateTime.mday=CtrData&0xff;
        fDateTime.month=CtrData>>8;
        fDateTime.year=CtrYear+2000;
        ClrDog;
        WriteDateTime(&fDateTime);
}

void GetRTC(void) {

		eDateTime	fDateTime;
        ReadDateTime(&fDateTime); //CtrTime=0;

		 //Second=DateTime.Sec&0x0F;
		 //Second+=(DateTime.Sec>>4)*10;
         CtrTime=fDateTime.min;
		 CtrTime+=fDateTime.hour*60;
         CtrData=fDateTime.mday;
		 CtrData+=fDateTime.month<<8;
         CtrYear=fDateTime.year-2000;
         NowDayOfWeek=fDateTime.wday;
}



void CopyEEP()
{
/*	if (WriteEEP)
	{
		I2C_MainLoad(0xA0,AdrEEP+sizeof(GD)+sizeof(BlockEEP),AdrRAM,I2C_TP_MEM,SizeEEP,I2C_Direction_Transmitter);
		while (I2CRel_Busy());
	}
	else
	{
		I2C_MainLoad(0xA0,AdrEEP+sizeof(GD)+sizeof(BlockEEP),AdrRAM,I2C_TP_MEM,SizeEEP,I2C_Direction_Receiver);
		while (I2CRel_Busy());

	}*/
}

void CalcEEPSum()
{
/*	uint16_t tSum,i;
	tSum=0x0110;
//	EEPROM_WaitForNVM();
	for (i = 0; i < SizeEEP; i++)
	{
		tSum+=EEPROM(AdrEEP+i);
		tSum%=65000;
	}
	if (WriteEEP)
	{
		FLASH_ProgramHalfWord(FLASH_ST_ADDR+AdrEEP+SizeEEP,tSum);
//		EEPROM(AdrEEP+SizeEEP)=tSum/256;
//		EEPROM(AdrEEP+SizeEEP+1)=tSum%256;
/*		if ((SizeEEP+AdrEEP+1)%EEPROM_PAGESIZE)
		{
			EEPROM_AtomicWritePage((SizeEEP+AdrEEP)/32);
			ClrDog;
			EEPROM_WaitForNVM();
		}
		EEPROM_AtomicWritePage((SizeEEP+AdrEEP+1)/32);
		EEPROM_WaitForNVM();

	}
	tSum-=FLASH_DATA(AdrEEP+SizeEEP);
//	tSum-=FLASH_DATA(AdrEEP+SizeEEP+1);
	ContSum=tSum;*/
}


void Init_MEAS_INPUT()
{
	 GPIO_InitTypeDef GPIO_InitStructure;
	 EXTI_InitTypeDef EXTI_InitStructure;
	 NVIC_InitTypeDef NVIC_InitStructure;

	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);

	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_Init(GPIOB, &GPIO_InitStructure);

	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	 GPIO_Init(GPIOB, &GPIO_InitStructure);

	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;
	 GPIO_Init(GPIOA, &GPIO_InitStructure);

	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

	 NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	 NVIC_Init(&NVIC_InitStructure);

	 // ��������� ����������:
	 GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource9);

	 EXTI_InitStructure.EXTI_Line = EXTI_Line9;
	 EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	 EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	 EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	 EXTI_Init(&EXTI_InitStructure);


}

void EXTI9_5_IRQHandler(void) {
   if (EXTI_GetITStatus(EXTI_Line9) != RESET) {
	   IntCount++;
   }
   // �� ���� � ���, �� �� �����:

   EXTI_ClearITPendingBit(EXTI_Line9);
}


void Init_IWDG(uint16_t* fIWDG_Reset)
{
	IWDG_Reset=fIWDG_Reset;
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	IWDG_SetPrescaler(IWDG_Prescaler_32);
	IWDG_SetReload(65000);
	IWDG_ReloadCounter();
#ifndef DEBUG
	IWDG_Enable();
#endif
}

void Check_IWDG(void)
{
//	if (RCC_GetFlagStatus(RCC_FLAG_IWDGRST) != RESET)
	{
		(*IWDG_Reset)++;
//		RCC_ClearFlag();
	}

}

void CheckDigitMidl(eSensing *ftemp,int16_t* Mes, int16_t* ValueS, uint8_t* tPause, uint16_t tFilter)
{
	if (((*Mes<*ValueS+tFilter)&&(*Mes>*ValueS-tFilter))||(*tPause>30)||(!*ValueS))
		*tPause=0;
	else
	{
		*Mes=*ValueS;
		if (*tPause<120) (*tPause)++;
	}

/*	if ((YesBit(ftemp->RCS,cbNotGoodSens)))
		ClrBit(ftemp->RCS,cbNotGoodSens);
	else
	{
		if ((*Mes>*ValueS+50)||(*Mes<*ValueS-50))
		{
			SetBit(ftemp->RCS,cbNotGoodSens);
			*Mes=*ValueS;
		}
	}*/
}


void CheckSensLevsNew(char fnTepl,uint8_t fnSens,char full,char met,int16_t Mes)
{
	int16_t 		*uS;
	eNameASens 	*nameS;
	eSensing 	*valueS;
	int16_t			*llS;
	int16_t			*lS;
	int16_t			*levelS;
	uint8_t			*tPause;
	uS=&GD.uInTeplSens[fnTepl][fnSens];
	nameS=&NameSensConfig[fnSens];
	SetPointersOnTepl(fnTepl);
	valueS=&(pGD_Hot_Tepl->InTeplSens[fnSens]);
	llS=&(pGD_TControl_Tepl->LastLastInTeplSensing[fnSens]);
	lS=&(pGD_TControl_Tepl->LastInTeplSensing[fnSens]);
	levelS=pGD_Level_Tepl[fnSens];
	tPause=&pGD_TControl_Tepl->TimeInTepl[fnSens];
	if (met)
	{
		uS=&GD.uMeteoSens[fnSens];
		nameS=&NameSensConfig[fnSens+cConfSSens];
		valueS=&GD.Hot.MeteoSensing[fnSens];
		//llS=&GD.TControl.LastLastMeteoSensing[fnSens];
		//lS=&GD.TControl.LastMeteoSensing[fnSens];
		levelS=GD.Level.MeteoSens[fnSens];
		tPause=&GD.TControl.TimeMeteoSensing[fnSens];
	}
	if (full)
	{
		if(((*uS)<nameS->uMin)||((*uS)>nameS->uMax))
			SetBit(valueS->RCS,cbMinMaxUSens);
	}
	if (Mes < nameS->Min)
	{
		if ((nameS->TypeSens==cTypeSun)||(nameS->TypeSens==cTypeRain)||(nameS->TypeSens==cTypeFram)||(nameS->TypeSens==cTypeScreen))
			Mes=nameS->Min;
		else
		{
			SetBit(valueS->RCS,cbMinMaxVSens);
			Mes=0;
		}
	}
	if (Mes > nameS->Max)
	{
		if ((nameS->TypeSens==cTypeRain)||(nameS->TypeSens==cTypeRH)||(nameS->TypeSens==cTypeFram)||(nameS->TypeSens==cTypeScreen))
			Mes=nameS->Max;
		else
		{
			SetBit(valueS->RCS,cbMinMaxVSens);
			Mes=0;
		}
	}
	switch (nameS->TypeMidl)
	{
		case cNoMidlSens:
			break;
		case c2MidlSens:
			(*llS)=0;
		case c3MidlSens:
			if (met) break;
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
			if (!(*lS)) (*lS)=Mes;
			Mes=(int)((((long int)(*lS))*(1000-cKExpMidl)+((long int)Mes)*cKExpMidl)/1000);
			(*lS)=Mes;
			break;
	}
	if (!met)
		CheckDigitMidl(valueS,&Mes,&valueS->Value,tPause,nameS->DigitMidl);
	if (nameS->TypeSens==cTypeFram)
	{
		if(!YesBit(pGD_TControl_Tepl->MechBusy[fnSens-cSmWinNSens+cHSmWinN].RCS,cMSBusyMech))
			SetBit(pGD_TControl_Tepl->MechBusy[fnSens-cSmWinNSens+cHSmWinN].RCS,cMSFreshSens);

	}
	if (nameS->TypeSens==cTypeScreen)
	{
		if(!YesBit(pGD_TControl_Tepl->MechBusy[cHSmScrTH].RCS,cMSBusyMech))
			SetBit(pGD_TControl_Tepl->MechBusy[cHSmScrTH].RCS,cMSFreshSens);

	}
	valueS->Value=Mes;
	//ClrBit(valueS->RCS,(cbDownAlarmSens+cbUpAlarmSens));				// task 61
	/*if ((levelS[cSmDownCtrlLev])&&(Mes <= levelS[cSmDownCtrlLev]))
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
    */
}

void  CalibrNew(char nSArea,char nTepl, char nSens,int16_t Mes){
	eSensing	*fSens;
	eNameASens	*fNameSens;
	int16_t		*fuSens;
	eCalSensor	*fCalSens;
	char		met=0;
	if (nSArea)
	{
		fSens=&GD.Hot.Tepl[nTepl].InTeplSens[nSens];
		fuSens=&GD.uInTeplSens[nTepl][nSens];
		fCalSens=&GD.Cal.InTeplSens[nTepl][nSens];
		fNameSens=&NameSensConfig[nSens];
		met=0;
	}
	else
	{
		fSens=&GD.Hot.MeteoSensing[nSens];
		fuSens=&GD.uMeteoSens[nSens];
		fCalSens=&GD.Cal.MeteoSens[nSens];
		fNameSens=&NameSensConfig[nSens+cConfSSens];
		met=1;
	}
	fSens->RCS=(fSens->RCS&(cbNotGoodSens+cbDownAlarmSens+cbUpAlarmSens));

	switch (fNameSens->TypeSens)
	{
		case cTypeFram:
		case cTypeScreen:
		case cTypeSun:
		case cTypeRain:
		case cTypeAnal:
		case cTypeRH:
		case cTypeMeteo:
		{
			ClrDog;
	    	//Mes=(int)((long int)Mes*(long int)1000/(long int)GD.Cal.Port);
        	fuSens[0]=Mes;
//			if(Mes>5000)
//				Mes=0;
        	LngX=((long)fCalSens->V1-(long)fCalSens->V0)
        		*((long)Mes-(long)fCalSens->U0);
        	Mes=(int16_t)(LngX/((long)fCalSens->U1-(long)fCalSens->U0));
        	Mes=Mes+fCalSens->V0;
			ByteX=nSensor;
			CheckSensLevsNew(nTepl,nSens,1,met,Mes);
			return;
		}
	}
}

void Measure()
{
	char tTepl,nSens;
	volatile uint16_t	tSensVal;
	int nModule;
	int8_t ErrModule = 0;

	for (tTepl=0;tTepl<cSTepl;tTepl++)
	{
		tSensVal=GetInIPC(GD.MechConfig[tTepl].RNum[48],&ErrModule);
		if ((ErrModule>=0) && (tSensVal > 4600))
			GD.Hot.Tepl[tTepl].Light50 = 10;
		else
			GD.Hot.Tepl[tTepl].Light50 = 0;

		tSensVal=GetInIPC(GD.MechConfig[tTepl].RNum[49],&ErrModule);
		if ((ErrModule>=0) && (tSensVal > 4600))
			GD.Hot.Tepl[tTepl].Light100 = 10;
		else
			GD.Hot.Tepl[tTepl].Light100 = 0;

        for(nSens=0;nSens<cConfSSens;nSens++)
		{
        	tSensVal=GetInIPC(GetSensConfig(tTepl,nSens),&ErrModule);
        	if (ErrModule<0)
        	{
        		GD.Hot.Tepl[tTepl].InTeplSens[nSens].RCS=cbNoWorkSens;
        		GD.Hot.Tepl[tTepl].InTeplSens[nSens].Value=0;
        		GD.uInTeplSens[tTepl][nSens]=0;
        		continue;
        	}
        	if (ErrModule>=iMODULE_MAX_ERR)
        	{
        		GD.Hot.Tepl[tTepl].InTeplSens[nSens].RCS=cbNoWorkSens;
        		GD.Hot.Tepl[tTepl].InTeplSens[nSens].Value=0;
        		GD.uInTeplSens[tTepl][nSens]=0;
        		NVIC_SystemReset();   // ������� ��� ���������� �������� �� ������� ������ �����
        		continue;
        		//        		tSensVal=0;
        	}
        	CalibrNew(1,tTepl,nSens,tSensVal);
        	saveAHUOutTemp[tTepl] = GD.Hot.Tepl[tTepl].InTeplSens[cSmTAHUOutSens].Value;
		}

	}
	volatile sen;
    for(nSens=0;nSens<cConfSMetSens;nSens++)
    {
    	sen = nSens;

    	if ((GetMetSensConfig(nSens) == 0)&&(GD.Hot.MeteoSensing[nSens].Value > 0))
    	{
    		GD.TControl.MeteoSensing[nSens] = GD.Hot.MeteoSensing[nSens].Value;
    	}

    	tSensVal=GetInIPC(GetMetSensConfig(nSens),&ErrModule);
    	if (ErrModule<0)
        {
    		GD.Hot.MeteoSensing[nSens].RCS=cbNoWorkSens;
    		GD.uMeteoSens[nSens]=0;
        	continue;
        }

    	if (ErrModule>=iMODULE_MAX_ERR) tSensVal=0;
    	CalibrNew(0,0,nSens,tSensVal);
    }
}

void CheckInputConfig()
{
	char tTepl,nSens;
	TIModulConf tTempConf;
	tTempConf.Corr=0;
	tTempConf.Output=0;
	tTempConf.Type=0;
	tTempConf.V1=0;
	tTempConf.V2=0;
	tTempConf.U1=0;
	tTempConf.U2=0;

	for (tTepl=0;tTepl<cSTepl;tTepl++)
        for(nSens=0;nSens<cConfSInputs;nSens++)
        {
        	tTempConf.Input=GetInputConfig(tTepl,nSens)%100;
        	UpdateInIPC(GetInputConfig(tTepl,nSens),&tTempConf);
        }
	for (tTepl=0;tTepl<cSTepl;tTepl++)
        for(nSens=0;nSens<cConfSSens;nSens++)
        	UpdateInIPC(GetSensConfig(tTepl,nSens),&GD.Cal.InTeplSens[tTepl][nSens]);
    for(nSens=0;nSens<cConfSMetSens;nSens++)
    	UpdateInIPC(GetMetSensConfig(nSens),&GD.Cal.MeteoSens[nSens]);

}

void SetDiskrSens(void)
{
	char fnTepl,nSens,nErr;
	nErr = 0;
	int res = 0;
	for (fnTepl=0;fnTepl<cSTepl;fnTepl++)
	{
		SetPointersOnTepl(fnTepl);
		for (nSens=0;nSens<cConfSInputs;nSens++)
		{
//			if (GetDiskrIPC(GetInputConfig(fnTepl,nSens),&nErr))
//				pGD_Hot_Tepl->DiskrSens[0]|=1<<nSens;

			/*res = GetDiskrIPC(GD.MechConfig[fnTepl].RNum[48],&nErr);
			if (res == 1)
				GD.Hot.Tepl[fnTepl].Light50 = 10;
			else
				GD.Hot.Tepl[fnTepl].Light50 = 0;

			res = GetDiskrIPC(GD.MechConfig[fnTepl].RNum[49],&nErr);
			if (res == 1)
				GD.Hot.Tepl[fnTepl].Light100 = 10;
			else
				GD.Hot.Tepl[fnTepl].Light100 = 0;*/


			/*if (pGD_Hot_Tepl->DiskrSens[0] == 4)
				if (pGD_Hot_Tepl->DiskrSens[1] == 1)
					GD.Hot.Tepl[fnTepl].Light50 = 10;
				else
					GD.Hot.Tepl[fnTepl].Light50 = 0;*/
		}
		/*tSensVal=GetInIPC(GD.MechConfig[tTepl].RNum[49],&ErrModule);
		if ((ErrModule>=0) && (tSensVal > 3500))
			GD.Hot.Tepl[tTepl].Light100 = 10;
		else
			GD.Hot.Tepl[tTepl].Light100 = 0;
*/


/*		if (YesBit(RegLEV,(cSmLightLev1<<fnTepl)))
			SetBit(pGD_Hot_Tepl->DiskrSens[0],cSmLightDiskr);
*/
	}

}
