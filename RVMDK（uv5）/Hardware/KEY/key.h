#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h" 

/*����ķ�ʽ��ͨ��ֱ�Ӳ����⺯����ʽ��ȡIO*/

#define Read_Door  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)//��ȡ�ſ���
#define Read_UpLevelingSwitch  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)//��ȡ��ƽ�㿪��
#define Read_DownLevelingSwitch  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)//��ȡ��ƽ�㿪��
#define Read_DownLimitSwitch  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)//��ȡ����λ����
#define Read_UpLimitSwitch  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)//��ȡ����λ����
#define Read_People  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)        //��ȡ�������Ƿ�����     
#define Read_Warning  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_6)       //��ȡ�ֶ��������Ȱ�ť�����ź�
#define KEY7  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)//��ȡ����1  L
#define KEY8  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_15)//��ȡ����1  L
#define KEY9  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_14)//��ȡ����1  L
#define KEY10  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_13)//��ȡ����1  L
#define KEY11  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_12)//��ȡ����1  L
#define KEY12  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_10)//��ȡ����1  L
#define KEY13  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)//��ȡ����1  L	

void KEY_Init(void);	//IO��ʼ��

#endif
