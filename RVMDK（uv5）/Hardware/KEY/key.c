#include "key.h"
#include "delay.h" 

//������ʼ������
void KEY_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	// GPIO Periph clock enable 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOE, ENABLE);		
	
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_13; //��Ӧ����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;//2M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOC13
	
	GPIO_InitStructure.GPIO_Pin = 	GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_8
	                |GPIO_Pin_10|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
 	GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIOEP0��1��2��3��4��5��6��8��10��12��13��14��15
}

