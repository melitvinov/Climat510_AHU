
//#define DEBUG

//#define DEMO  // ������ �������� ����� ���������, ���� ���� ������������ ������� ������� �� 100%
#define AHU
//#define AGAPOVSKIY_DOUBLE_VALVE
//#define SIO_PAUSE	1

#include "stm32f10x_Define.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_RS485.h"
#include "stm32f10x_RS485Master.h"
#include "stm32f10x_LCD240x64.h"
#include "stm32f10x_Rootines.h"
#include "stm32f10x_i2cRel.h"
#include "stm32f10x_dma.h"
#include "405_EngRus.c"
#include "65_const.c"
#include "405_ClimDef.c"
#include "405_ConfigEnRuSR.c"

#define cConfSTepl		2
//#define BIGLCD
#ifdef AHU
#define cModification	16+4
#else
#define cModification	16
#endif

/*����������� �� �����������*/

#define NumCtr          1

#define cDefLanguage	1

#define DEF_PORTNUM         2012

#ifndef cLightDelay
	#define cLightDelay		40
#endif


//#define cSMech			12

#define cSTepl			8


#ifdef DEBUG
uint16_t SumAnswers=0;
char DEBUG_Buf1[4]={4,5,6,7};
char DEBUG_Buf2[4]={0,1,2,3};
#endif


uint16_t InitSystems[cSTepl][10]={
//����1
{5, //���������
2, //����������
1, //�����
#ifdef AHU
2,
#else
0, //UltraClima
#endif
2, //��2
6, //��������
5, //����
1, //�����������
0, //������ 1
0},//������ 2

//����2
{5, //���������
2, //����������
1, //�����
0, //UltraClima
2, //��2
6, //��������
5, //����
1, //�����������
0, //������ 1
0},//������ 2

//����3
{5, //���������
2, //����������
1, //�����
0, //UltraClima
2, //��2
6, //��������
5, //����
1, //�����������
0, //������ 1
0},//������ 2

//����4
{5, //���������
2, //����������
1, //�����
0, //UltraClima
2, //��2
6, //��������
5, //����
1, //�����������
0, //������ 1
0},//������ 2

//����5
{5, //���������
2, //����������
1, //�����
0, //UltraClima
2, //��2
6, //��������
5, //����
1, //�����������
0, //������ 1
0},//������ 2

//����6
{5, //���������
2, //����������
1, //�����
0, //UltraClima
2, //��2
6, //��������
5, //����
1, //�����������
0, //������ 1
0},//������ 2

//����7
{5, //���������
2, //����������
1, //�����
0, //UltraClima
2, //��2
6, //��������
5, //����
1, //�����������
0, //������ 1
0},//������ 2

//����8
{5, //���������
2, //����������
1, //�����
0, //UltraClima
2, //��2
6, //��������
5, //����
1, //�����������
0, //������ 1
0},//������ 2

};

uint16_t code MechC[cSTepl][SUM_NAME_CONF]={
{	/* ������� 1*/
	9,	//������ 1
	12,	//������ 2
	15,	//������ 3
	18,	//������ 4
	21,	//������ 5

	1,	//������� �����
	0,	//������� ��
	0,	//�����
	0,	//����� �������������� �����
	0,	//����� ������������ ������
	0,	//����� ������������ ������
	0,	//����� ������������ ������
	0,	//����� ������������ ������

	33,	//��2
	0,  //��������� ��������
	0,  //������
	11,	//����� 1
	14,	//����� 2

	17,	//����� 3
	20,  //����� 4
	23,	//����� 5
	7,	//����������
	0,	//�����������

	24,	//����� ����
	8,	//������ �������� ����
	35,  //��������
	0,  //���������� ����
	0,

	0,
	0,
	0,
	0,
	37,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
},

{	/* ������� 2*/
	0,	//������ 1
	0,	//������ 2
	0,	//������ 3
	0,	//������ 4
	0,	//������ 5

	0,	//������� �����
	0,	//������� ��
	0,	//�����
	0,	//����� �������������� �����
	0,	//����� ������������ ������
	0,	//����� ������������ ������
	0,	//����� ������������ ������
	0,	//����� ������������ ������

	0,	//��2
	0,  //��������� ��������
	0,  //������
	0,	//����� 1
	0,	//����� 2

	0,	//����� 3
	0,  //����� 4
	0,	//����� 5
	0,	//����������
	0,	//�����������

	0,	//����� ����
	0,	//������ �������� ����
	0,  //��������
	0,  //���������� ����
	0,

	0,
	0,
	0,
	0,
	0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
},

{	/* ������� 3*/
	0,	//������ 1
	0,	//������ 2
	0,	//������ 3
	0,	//������ 4
	0,	//������ 5

	0,	//������� �����
	0,	//������� ��
	0,	//�����
	0,	//����� �������������� �����
	0,	//����� ������������ ������
	0,	//����� ������������ ������
	0,	//����� ������������ ������
	0,	//����� ������������ ������

	0,	//��2
	0,  //��������� ��������
	0,  //������
	0,	//����� 1
	0,	//����� 2

	0,	//����� 3
	0,  //����� 4
	0,	//����� 5
	0,	//����������
	0,	//�����������

	0,	//����� ����
	0,	//������ �������� ����
	0,  //��������
	0,  //���������� ����
	0,

	0,
	0,
	0,
	0,
	0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
},

{	/* ������� 4*/
	0,	//������ 1
	0,	//������ 2
	0,	//������ 3
	0,	//������ 4
	0,	//������ 5

	0,	//������� �����
	0,	//������� ��
	0,	//�����
	0,	//����� �������������� �����
	0,	//����� ������������ ������
	0,	//����� ������������ ������
	0,	//����� ������������ ������
	0,	//����� ������������ ������

	0,	//��2
	0,  //��������� ��������
	0,  //������
	0,	//����� 1
	0,	//����� 2

	0,	//����� 3
	0,  //����� 4
	0,	//����� 5
	0,	//����������
	0,	//�����������

	0,	//����� ����
	0,	//������ �������� ����
	0,  //��������
	0,  //���������� ����
	0,

	0,
	0,
	0,
	0,
	0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
},
{	/* ������� 5*/
	0,	//������ 1
	0,	//������ 2
	0,	//������ 3
	0,	//������ 4
	0,	//������ 5

	0,	//������� �����
	0,	//������� ��
	0,	//�����
	0,	//����� �������������� �����
	0,	//����� ������������ ������
	0,	//����� ������������ ������
	0,	//����� ������������ ������
	0,	//����� ������������ ������

	0,	//��2
	0,  //��������� ��������
	0,  //������
	0,	//����� 1
	0,	//����� 2

	0,	//����� 3
	0,  //����� 4
	0,	//����� 5
	0,	//����������
	0,	//�����������

	0,	//����� ����
	0,	//������ �������� ����
	0,  //��������
	0,  //���������� ����
	0,

	0,
	0,
	0,
	0,
	0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
},
{	/* ������� 6*/
	0,	//������ 1
	0,	//������ 2
	0,	//������ 3
	0,	//������ 4
	0,	//������ 5

	0,	//������� �����
	0,	//������� ��
	0,	//�����
	0,	//����� �������������� �����
	0,	//����� ������������ ������
	0,	//����� ������������ ������
	0,	//����� ������������ ������
	0,	//����� ������������ ������

	0,	//��2
	0,  //��������� ��������
	0,  //������
	0,	//����� 1
	0,	//����� 2

	0,	//����� 3
	0,  //����� 4
	0,	//����� 5
	0,	//����������
	0,	//�����������

	0,	//����� ����
	0,	//������ �������� ����
	0,  //��������
	0,  //���������� ����
	0,

	0,
	0,
	0,
	0,
	0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
},
{	/* ������� 7*/
		0,	//������ 1
		0,	//������ 2
		0,	//������ 3
		0,	//������ 4
		0,	//������ 5

		0,	//������� �����
		0,	//������� ��
		0,	//�����
		0,	//����� �������������� �����
		0,	//����� ������������ ������
		0,	//����� ������������ ������
		0,	//����� ������������ ������
		0,	//����� ������������ ������

		0,	//��2
		0,  //��������� ��������
		0,  //������
		0,	//����� 1
		0,	//����� 2

		0,	//����� 3
		0,  //����� 4
		0,	//����� 5
		0,	//����������
		0,	//�����������

		0,	//����� ����
		0,	//������ �������� ����
		0,  //��������
		0,  //���������� ����
		0,

		0,
		0,
		0,
		0,
		0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
},
	{	/* ������� 8*/
			0,	//������ 1
			0,	//������ 2
			0,	//������ 3
			0,	//������ 4
			0,	//������ 5

			0,	//������� �����
			0,	//������� ��
			0,	//�����
			0,	//����� �������������� �����
			0,	//����� ������������ ������
			0,	//����� ������������ ������
			0,	//����� ������������ ������
			0,	//����� ������������ ������

			0,	//��2
			0,  //��������� ��������
			0,  //������
			0,	//����� 1
			0,	//����� 2

			0,	//����� 3
			0,  //����� 4
			0,	//����� 5
			0,	//����������
			0,	//�����������

			0,	//����� ����
			0,	//������ �������� ����
			0,  //��������
			0,  //���������� ����
			0,

			0,
			0,
			0,
			0,
			0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	}
};




//#define SumRelay40
#define SumRelay48

#define cNumValSiodMax	4
#define cNumValSiodDef	2

#define cnLight			5
#define VIN
//#define DEMO

/*------------------------------------------*/
#include "65_GD.c"
#include "405_Memory.c"
//#include "405_Clock.c"
#include "65_Subr.c"
#include "405_Display.c"
#include "65_screen.c"
#include "65_strategy3m.c"
#include "65_siod.c"
#include "65_control.c"
#include "405_menu.c"
#include "65_main.c"
#include "src/stm32f10x_LCD240x64.c"
#include "src/stm32f10x_Rootines.c"
#include "src/SPI.c"
#include "src/enc28j60.c"
#include "src/ip_arp_udp_tcp.c"
#include "src/simple_server.c"
