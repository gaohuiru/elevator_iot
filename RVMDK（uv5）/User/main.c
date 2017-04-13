#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "timer.h"
#include "state.h"
#include "exti.h"
#include "math.h"

int main(void)
{ 
	delay_init(168);  //��ʼ����ʱ����
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	LED_Init();				//��ʼ��LED�˿� 
	EXTIX_Init();     //��ʼ���ⲿ�ж�
	
	TIM2_Int_Init(pow(2,32)-1,8400-1);      //��ʱ��ʱ��84M����Ƶϵ��8400������84M/8400=10Khz�ļ���Ƶ�� 	
	TIM3_Int_Init(10000-1,8400-1);      //��ʱ��ʱ��84M����Ƶϵ��8400������84M/8400=10Khz�ļ���Ƶ�ʣ�����10000��Ϊ1s 
	TIM4_Int_Init(20000-1,8400-1);      //������ͣ�ݳ����趨ʱ��
	TIM5_Int_Init(40000-1,8400-1);      //ƽ������ʱ����ֵ
	TIM7_Int_Init(40000-1,8400-1);      //��ʱ�俪��ʱ����ֵ
	
	uart_init(9600);
	
	printf("\r\n Welcome to use STM32F407 \r\n");
 
	while(1)
	{
		Normal_state();
		Running_door_open();
		Out_Speed();
		Open_Close_Door();
		Warning();
		State_Breakdown();
		
		LED0=1;
		delay_ms(100);
		LED0=0;
		delay_ms(100);
	}
}
