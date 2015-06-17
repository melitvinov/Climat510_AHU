/*============================================
        ---������ 324 � 17.11.2003
        --- ������ F319 ---
        ���� "k_main.c"
        ������� ���� ���������
----------------------------------------------*/
#include "keyboard.h"

//++++++FullCheck ++++
int  DestSize;
int  DestAdr;
//char xdata	DestBuffer[7000];
//char* DestAdrBuf;
//char	BufCheckByte;

/*char PlaceBuf(void) {
int  i;
char xdata *p1;
char xdata *p2;
if (BufCheckByte != 55) return 0; //;��������� �����
p1=(char xdata *)DestAdr;
p2=(char xdata *)&DestBuffer[0];
for (i=0;i < (DestSize-1);i++) {
    *(p1++)=*(p2++);
    }
return 1;
}
*/
//;------FullCheck------------------


main()
{
    char    timeDog;
    keyboardSetBITKL(0);
    //BITKL=0;

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
    w_txt("\252\245TO F405 (c)APL&DAL");
    Delay(1000000);
    ClrDog;
    Video();
    ClrDog;
    GD.Hot.News|=bKlTest;
    ByteX=1;
    GD.SostRS=OUT_UNIT;
    KeyboardProcess();
	if (keyboardGetBITKL())
        ByteX=6;
    ClrDog;
    TestMem(ByteX);
    Second=38;
    ClrDog;
    ClrDog;  /* ���������� ���������� RS � T0 �� init8051()*/
    ClearAllAlarms();
start:

    if (not) {
        if (!ton_t--) {
            ton_t=ton; not--; Sound;
        }
    }
    if (!not && nReset) {
        ton=(nReset--)+2;not=80;
    }

    if (!timeDog--) {
        timeDog=7;ClrDog;
    }

    if (GD.SostRS == (uchar)IN_UNIT) {  /*���� ������� ���� � �� */
        /*--���� ������ 0�� � ������� ������� �� ���������� ����� */
//            if(PlaceBuf()) {
#ifdef STM32_UNIT
        NMinPCOut=0;
#endif
        if (!NumBlock && (GD.Hot.News&0x80)) SetRTC();
        ClrDog;
        /*-- ���� ������ � �� � ���� NumBlock, ���������� � EEPROM ------*/
        if (NumBlock) ReWriteFRAM();
//				}
        GD.SostRS=OUT_UNIT;
        keyboardSetSIM(105);
    }
    if (bSec) {
#ifdef STM32_UNIT
        if (Second==58) {
            CheckWithoutPC();
            CheckInputConfig();
        }
        CheckRSTime();
#endif
#ifndef NOTESTMEM

        if (GD.SostRS==OUT_UNIT) TestMem(0);
#endif
        bSec=0;
        ClrDog;
        Control();
        ClrDog;
        B_video=1;
        if (!(Second%9))
            Measure();
    }
	if (keyboardGetBITKL()) {
        ClrDog;
        GD.Hot.News|=bOperator;
        if (Menu) GD.Hot.News|=bEdit;
        KeyBoard();
        B_video=1;
    }
    //CheckReadyMeasure();
    if (B_video) {
        ClrDog;
        GMenu();
        ClrDog;
        Video();
        ClrDog;
        B_video=0;
    }
    simple_servercycle(); //���������� � ���������� ����������

    goto start;
}
