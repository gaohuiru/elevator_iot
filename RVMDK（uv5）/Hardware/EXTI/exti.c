#include "exti.h"
#include "delay.h" 
#include "led.h" 
#include "key.h"
#include "state.h"
#include "timer.h"
#include "stdio.h"
	
//����״̬��������state.c�ﶨ�壩
extern STATE_Typedef state;  //��ǰ����״̬

//���ݹ���״̬����(��state.c�ﶨ�壩
extern u8 state_breakdown;

//��ǰ����(��state.c�ﶨ�壩	
extern u8 Floors;

//�����Źرմ�������state.c�ﶨ�壩
extern u8 Door_closes;

//�����½���־(��state.c�ﶨ�壩
extern u8 Rise_Fall_FLAG;

//��ʱ��2�������ı���ֵ������������������ٶ�(��state.c�ﶨ�壩
extern u32 TIME;

//�ⲿ�жϳ�ʼ������
//��ʼ��PE1~2,PE1~2Ϊ�ж�����.
void EXTIX_Init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	
	KEY_Init(); //������Ӧ��IO�ڳ�ʼ��
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ��SYSCFGʱ��
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource1);//PE1 ���ӵ��ж���1
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource2);//PE2 ���ӵ��ж���2
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource0);//PE0 ���ӵ��ж���0
	
	/* ����EXTI_Line1,2,3*/
	EXTI_InitStructure.EXTI_Line = EXTI_Line1 | EXTI_Line2 | EXTI_Line0;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; //���ش���
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//�ж���ʹ��
  EXTI_Init(&EXTI_InitStructure);//����
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;//�ⲿ�ж�1
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//��ռ���ȼ�1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;//�ⲿ�ж�2
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//��ռ���ȼ�1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����	  

	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;//�ⲿ�ж�0
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//��ռ���ȼ�1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;//�����ȼ�3
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����	
}

//�ⲿ�ж�1�������(A)
void EXTI1_IRQHandler(void)
{
	if(Read_UpLevelingSwitch == 1)
	{
		//�����ش���
		if(Read_DownLevelingSwitch == 0 && state == Rise_Two) //�жϵ�ǰ����״̬�ǲ�������2
			state = Rise_Three;                    //��ʱ����״̬ת��Ϊ����3
		if(Read_DownLevelingSwitch == 1 && state == Fall_Three) //�жϵ�ǰ����״̬�ǲ����½�3
		{
			state = Level_Dynamic;                 //��ʱ����״̬ת��Ϊƽ���˶�
			TIM_Cmd(TIM3,ENABLE);                  //ʹ�ܶ�ʱ��3
//			TIM4->CNT=0;                           //���㶨ʱ��4�ļ�����
//			TIM_Cmd(TIM4,DISABLE);                 //�رն�ʱ��4
			
			if(Rise_Fall_FLAG == 0)
				Floors++;                            //������1
			else if(Rise_Fall_FLAG == 1)
				Floors--;                            //������1
		}
	}
	else
//�жϵ�ǰ����״̬�ǲ���ƽ�㾲ֹ��ƽ���˶����½�1
//�½�1ָ���Ǹ�����������ж�
	{
		//�½��ش��� 
		if(Read_DownLevelingSwitch == 1 && (state == Level_Static || state == Level_Dynamic || state == Fall_One)) 
		{
			if(state == Level_Static && Read_Door == 1)                     //�ж��Ƿ��ǿ���״̬�¿�ʼ���й���
					state_breakdown |=1<<2;
				
			state = Rise_One;                      //��ǰ����״̬ת��Ϊ����1
			Rise_Fall_FLAG = 0;                    //��������
//			TIM_Cmd(TIM4,ENABLE);                  //ʹ�ܶ�ʱ��4
			
			TIM5->CNT=0;                             //���㶨ʱ��5�ļ�����
			TIM_Cmd(TIM5,DISABLE);                   //�رն�ʱ��5	
			
			Door_closes=0;                            //�Źرմ�����0
		}
		if(Read_DownLevelingSwitch == 0 && state == Fall_One) //�жϵ�ǰ����״̬�ǲ����½�1
		{
			TIM3->CNT=0;                           //���㶨ʱ��3�ļ�����
		  TIM_Cmd(TIM3,DISABLE);                 //ȥʹ�ܶ�ʱ��3
			state = Fall_Two;                      //��ʱ����״̬ת��Ϊ�½�2
			 
		}
	}
	EXTI_ClearITPendingBit(EXTI_Line1);        //���LINE1�ϵ��жϱ�־λ 
}

//�ⲿ�ж�2�������(B)
void EXTI2_IRQHandler(void)
{
	if(Read_DownLevelingSwitch == 1)
	{
		//�����ش���
		if(Read_UpLevelingSwitch == 1 && state == Rise_Three) //�жϵ�ǰ����״̬�ǲ�������3           
		{
			state = Level_Dynamic;                //��ʱ����״̬ת��Ϊƽ���˶�
//			TIM4->CNT=0;                          //���㶨ʱ��4�ļ�����
//			TIM_Cmd(TIM4,DISABLE);                //�رն�ʱ��4
			TIM_Cmd(TIM3,ENABLE);                 //ʹ�ܶ�ʱ��3
			
			TIM_Cmd(TIM2,DISABLE);                //�رն�ʱ��2
			TIME = TIM2->CNT;                     //��ȡ��ʱ��2�ļ�����
			
			if(Rise_Fall_FLAG == 0)
				Floors++;                           //������1
			else if(Rise_Fall_FLAG == 1)
				Floors--;                            //������1
		}
		if(Read_UpLevelingSwitch == 0 && state == Fall_Two) //�жϵ�ǰ����״̬�ǲ����½�2
		{
			TIM_Cmd(TIM2,DISABLE);                //�رն�ʱ��2
			TIME = TIM2->CNT;                     //��ȡ��ʱ��2�ļ�����

			state = Fall_Three;                   //��ʱ����״̬ת��Ϊ�½�3
		}
	}
	else
	{
		//�½��ش��� 
		if(Read_UpLevelingSwitch==0 && state == Rise_One) //�жϵ�ǰ����״̬�ǲ�������1
		{
			TIM3->CNT=0;                          //���㶨ʱ��3�ļ�����
			TIM_Cmd(TIM3,DISABLE);                //�رն�ʱ��3
			TIM2->CNT=0;                          //���㶨ʱ��2�ļ�����
			TIM_Cmd(TIM2,ENABLE);                 //�򿪶�ʱ��2����ʼ��ʱ

			state = Rise_Two;                    	//��ʱ����״̬ת��Ϊ����2
		}
//�жϵ�ǰ����״̬�ǲ���ƽ�㾲ֹ��ƽ���˶�������1
//����1ָ���Ǹ�����������ж�
		if(Read_UpLevelingSwitch==1 && (state == Level_Static || state == Level_Dynamic || state == Rise_One)) 
		{
			TIM2->CNT=0;                          //���㶨ʱ��2�ļ�����
			TIM_Cmd(TIM2,ENABLE);                 //�򿪶�ʱ��2����ʼ��ʱ
		
			if(state == Level_Static && Read_Door == 1)   //�ж��Ƿ��ǿ���״̬�¿�ʼ���й���
				state_breakdown |=1<<2;
			
			state = Fall_One;                     //��ʱ����״̬ת��Ϊ�½�1
			Rise_Fall_FLAG = 1;                    //�����½�
			
//		TIM_Cmd(TIM4,ENABLE);                  //ʹ�ܶ�ʱ��4
			
			TIM5->CNT=0;                             //���㶨ʱ��5�ļ�����
			TIM_Cmd(TIM5,DISABLE);                   //�رն�ʱ��5	
			
			Door_closes=0;                            //�Źرմ�����0
		}
	}
	EXTI_ClearITPendingBit(EXTI_Line2);       //���LINE2�ϵ��жϱ�־λ 
}

void EXTI0_IRQHandler(void)                 //�ſ���״̬����   ƽ�����˹���
{
	if(Read_Door == 0)                        //�Źر�
	{
		printf("�Ź�\r\n");
		state_breakdown &=~(1<<5);
		TIM7->CNT=0;                             //���㶨ʱ��7�ļ�����
		TIM_Cmd(TIM7,DISABLE);                   //�رն�ʱ��7		
		
		if(Rise_Fall_FLAG == 2)                  //ƽ�㾲ֹ
		{
			Door_closes++;                            //�ſ��ش�����һ
			if(Read_People==1)                       //����״̬
				TIM_Cmd(TIM5,ENABLE);                  //ʹ�ܶ�ʱ��5
		}
	}
	else                                        //�Ŵ�
		{
			printf("�ſ�\r\n");
			TIM_Cmd(TIM7,ENABLE);                   //ʹ�ܶ�ʱ��7
			if(Rise_Fall_FLAG == 0 || Rise_Fall_FLAG == 1)
				state_breakdown |=1<<1;
			
	//		Door_close++;                            //�ſ��ش�����һ			            
	
			TIM5->CNT=0;                             //���㶨ʱ��5�ļ�����
			TIM_Cmd(TIM5,DISABLE);                   //�رն�ʱ��5	
		}
		EXTI_ClearITPendingBit(EXTI_Line0);       //���LINE0�ϵ��жϱ�־λ 		
}
