/*!
\brief ������� ������ � ������ � �� ����� �����
@param unsigned int startAddr ����� ������
@param unsigned int endAddr ����� �����
@return int 0 - ������ �������, 1 ������ �������
*/
#include "stm32f10x_Define.h"

#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

/*!
\brief ������� ������������ ����� ������ � �� ��������������� ����������
*/
typedef enum {
    KEY_UP      = 13,
    KEY_RIGHT   = 14,
    KEY_LEFT    = 12,
    KEY_DOWN    = 15,
    KEY_1       = 1,
    KEY_2_UP    = 2,
    KEY_3       = 3,
    KEY_4_LEFT  = 4,
    KEY_5       = 5,
    KEY_6_RIGHT = 6,
    KEY_7       = 7,
    KEY_8_DOWN  = 8,
    KEY_9       = 9,
    KEY_10      = 10,
    KEY_11      = 0
} KEY_PRESSED;


/*!
\brief ������������� ����������
*/
void Keyboard_Init(void);

/*!
\brief ������� ������ ����������
@return char 0 - ������ �� ������, 1 ������ ������
*/
char KeyboardProcess(void);

/*!
\brief ��������� ����� ������� ������
@param uchar 0 - ������ �� ������, 1 ������ ������
*/
void keyboardSetBITKL(uchar press);

/*!
\brief ������ ����� ������� �� ������
@return char 0 - ������ �� ������, 1 ������ ������
*/
uchar keyboardGetBITKL(void);

/*!
\brief ��������� ���� ������� ������
@param KEY_PRESSED ��� ������� ������
*/
void keyboardSetSIM(KEY_PRESSED key);

/*!
\brief ������ ���� ������� ������
@return KEY_PRESSED ��� ������� ������
*/
KEY_PRESSED keyboardGetSIM(void);

#endif
