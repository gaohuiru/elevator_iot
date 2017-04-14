#include "stdio.h"
#include "state.h"
#include "key.h"

//��������״̬����(ȫ�ֱ���)
STATE_Typedef state = Level_Static;  //��ǰ����״̬

//���ݹ���״̬����
u8 state_breakdown=0;               //��ʼ���޹���

//��ǰ����(��ʼֵ)
u8 Floors = 3;

//�Źرմ���
u8 Door_closes=0;

//�����ٶ�
float speed;

//�����½���־
//0Ϊ����
//1Ϊ�½�
//2Ϊ����ͣ��(ƽ�㾲ֹ)    3Ϊ������ͣ��
u8 Rise_Fall_FLAG = 2; //Ĭ�Ͼ�ֹ
    
//��ʱ��2�������ı���ֵ������������������ٶ�
u32 TIME = 0;

void Normal_state()
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
		else if(Rise_Fall_FLAG == 2)
		{
			printf("�Ѿ�����ͣ��\r\n");
			speed = 0;
		}
		else
		{
			printf("������ͣ��\r\n");
			speed = 0;
		}
		
		printf("�����ٶ�Ϊ��%f\r\n",speed);
		printf("\r\n");
}

void Out_Speed()                         //�жϵ����Ƿ���
{
	if(speed>MAX_SPEED)
		state_breakdown |=1<<3;
}
   
void Open_Close_Door()                  //�жϵ����ſ��ش����Ƿ񳬹��趨����ֵ
{
	if(Door_closes>MAX_DOOR_CLOSE)
		state_breakdown |=1<<6;
}

void Warning()                         //�жϵ����Ƿ񴥷��ֶ������ź�
{
	if(Read_warning == 1)
			state_breakdown |=1<<7;
}

void State_Breakdown()                 //���ֹ����ж�
{
// printf("%d\r\n",state_breakdown);
	 if((state_breakdown & 1) != 0)
	 {
		 if(Read_People==1)
			 printf("������ͣ��(����)����\r\n");
		 else printf("������ͣ��(����)����\r\n");
	 }
	 if((state_breakdown & 1<<1) != 0)
	 {
		 if(Read_People==1)
			 printf("�����п���(����)����\r\n");
		 else printf("�����п���(����)����\r\n");
	 }
	 if((state_breakdown & 1<<2) != 0)
		 printf("����״̬�¿�ʼ���й���\r\n");
	 if((state_breakdown & 1<<3) != 0)
		 printf("���ݳ���\r\n");
	 if((state_breakdown & 1<<4) != 0)
		 printf("ƽ������\r\n");
	 if((state_breakdown & 1<<5) != 0)
		 printf("��ʱ�俪�Ź���\r\n");
	 if((state_breakdown & 1<<6) != 0)
		 printf("���������Ź���\r\n");
	 if((state_breakdown & 1<<7) != 0)
		 printf("�ֶ�����\r\n");
}


