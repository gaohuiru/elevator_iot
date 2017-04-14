#ifndef __MAIN_H
#define __MAIN_H	 

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

//����һ��ö�ٱ�����ʾ��������״̬
typedef enum
{
	Level_Dynamic = 0x00,
	Level_Static,
	Rise_One,
	Rise_Two,
	Rise_Three,
	Fall_One,
	Fall_Two,
	Fall_Three
}STATE_Typedef;

//�ܲ���
#define MAX_Floor 3
//ÿ��¥�ĸ߶�(��)
#define HEIGHT 3

//������������ٶ� (m/s)
#define MAX_SPEED 2

//�ſ��ش�����ֵ
#define MAX_DOOR_CLOSE 10

void Normal_state(void);
//void Running_door_open(void);
void Out_Speed(void);
void Warning(void);
void Open_Close_Door(void);
void State_Breakdown(void);

#endif
