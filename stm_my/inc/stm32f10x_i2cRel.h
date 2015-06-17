//������������ ���� ������ � I2C
#include "STM32F10X_GPIO.h"


#define I2C_Rel             I2C2 //����� ����� I2C

#define REL_BASE_ADDRESS	0x40 //����� ���������� ����
#define MEM_BASE_ADDRESS	0xA0 //����� ���������� ������
//#define MEM_TYPE_EEPROM


//������������� I2C
void I2C_BLOCK_Configuration(void);
//������ �� EEPROM
void I2C_Mem_Read(uint8_t fAddrDev,uint16_t fAddrMem,uint8_t* fData,uint16_t fptrData);
//������ � EEPROM
void I2C_Mem_Write(uint8_t fAddrDev,uint16_t fAddrMem,uint8_t* fData,uint16_t fptrData);
//������ � ����
void I2C_Rel_Write(uint8_t pState, uint8_t NumRel);


//����������� ������ � I2C - �� �������

#define	I2C_TP_OUT		0
#define	I2C_TP_MEM		1
#define	I2C_TP_ADR		2

void I2CRel_MEM_Configuration(void);
void I2C_DMAMem_Transfer(uint8_t* I2CBuf,uint16_t I2CMemSize,uint32_t DMA_dir);
uint8_t I2C_MainLoad(uint8_t fAddrDev,uint16_t fAddrMem,uint8_t* fData,uint8_t fType, uint16_t fptrData, uint8_t fDir);
uint8_t I2CRel_Busy(void);


