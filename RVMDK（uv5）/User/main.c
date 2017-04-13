#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "timer.h"
#include "state.h"
#include "exti.h"
#include "math.h"

//��������״̬����(ȫ�ֱ���)
STATE_Typedef state = Level_Static;  //��ǰ����״̬

////���ݹ���״̬����
//STATE_BREAK state_breakdown=No_breakdown;     //��ʼ���޹���

u8 state_breakdown=0;

//��ǰ����(��ʼֵ)
u8 Floors = 3;

//�Źرմ���
u8 Door_closes=0;

//�ٶ�
float speed;

//�����½���־
//0Ϊ����
//1Ϊ�½�
//����Ϊ��ֹ
u8 Rise_Fall_FLAG = 2; //Ĭ�Ͼ�ֹ


////����״̬��־
//u8 BREAKDWON_FLAG;     

//��ʱ��2�������ı���ֵ������������������ٶ�
u32 TIME = 0;

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
		if(Read_DownLimitSwitch == 0)
			printf("�׵�״̬\r\n");
		if(Read_UpLimitSwitch == 0)
			printf("�嶥״̬\r\n");

		if(TIME == 0)
			speed = 0;
		else
			speed = (float)10000*HEIGHT/TIME;
		
		printf("��ǰ����:%d\r\n",Floors);
		
		if(Read_Door == 1)
				printf("�����Ŵ�\r\n");
		else
				printf("�����Źر�\r\n");
			
		if(Rise_Fall_FLAG == 0)
			printf("��������\r\n");
		else if(Rise_Fall_FLAG == 1)
			printf("�����½�\r\n");
		else
		{
			printf("�Ѿ�ͣ��\r\n");
			speed = 0;
		}
		
		printf("�����ٶ�Ϊ��%f\r\n",speed);
		printf("\r\n");
		
		LED0=1;
		delay_ms(100);
		LED0=0;
		delay_ms(100);
	}
}
