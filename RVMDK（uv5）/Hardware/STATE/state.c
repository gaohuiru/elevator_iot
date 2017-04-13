#include "state.h"
#include "key.h"


//���ݹ���״̬����(��main.c�ﶨ�壩
extern u8 state_breakdown;   

//�����½���־(��main.c�ﶨ�壩
extern u8 Rise_Fall_FLAG;

//�����Źرմ�������main.c�ﶨ�壩
extern u8 Door_closes;

//�����ٶ�(��main.c�ж���)
extern float speed;

void Running_door_open()
{
	if(Rise_Fall_FLAG==0 || Rise_Fall_FLAG==1)  //�жϵ����Ƿ�Ϊ����״̬
	{
		if(Read_Door == 1)                      //�����Ŵ�    
		{	
			state_breakdown |=1<<1;
			/* if(Read_People==0)                  //����״̬
				printf("�����п��ţ����ˣ�����\r\n");
			else printf("�����п��ţ����ˣ�����\r\n"); */
		}
	}
}

void Out_Speed()
{
	if(speed>MAX_SPEED)
		state_breakdown |=1<<3;
		/* printf("���ݳ���\r\n") */
}

void Open_Close_Door()
{
	if(Door_closes>MAX_DOOR_CLOSE)
		state_breakdown |=1<<6;
}

void Warning()
{
	if(Read_warning == 1)
			state_breakdown |=1<<7;
}

void State_Breakdown()
{
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


