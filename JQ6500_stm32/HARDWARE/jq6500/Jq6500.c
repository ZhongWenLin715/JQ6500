/**
 * **********************************************************************
 * @file Jq6500.c
 * @author ����Ҳ��IOT
 * @version V1.0
 * @date 2018.12.26
 * @brief jq6500����ģ�� ���������ļ�.
 *
 * **********************************************************************
 * @note
 * 2019.2.20 �Ż�����.
 *
 * **********************************************************************
 */
#include "jq6500.h"
#include "delay.h"
#include "usart.h"

static uint8_t data[4]; 
//jq6500 IO��ʼ�� æµ���
void JQ6500_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PB�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				 //PB.5 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD ; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.5

}

//8λУ���
uint8_t voice_SumCheck(uint8_t *Str,uint8_t len)
{
	u16 xorsum=0;
	uint8_t i;
	for(i=0;i<len;i++)
	{
		xorsum=xorsum+(*Str++);
	}
	return ((uint8_t)(xorsum&0x00ff));
}
void Basic_control(uint8_t cmd)
{
	uint8_t * p = NULL;
	p = data;
    *p++ = 0x7E;
	*p++ = 0x02;
    *p++ = cmd;
    *p++ = 0xEF;
	UART3_Send_Data(data, 4);
}

//��һ��
void JQ6500_Next(void)
{
	Basic_control(CMD_NEXT);
}

//��һ��
void JQ6500_Prev(void)
{
	Basic_control(CMD_PREV);
}

//����+
void VolAdd(void)
{
	Basic_control(CMD_VOL_ADD);
}

//����-
void VolLess(void)
{
	Basic_control(CMD_VOL_LESS);
}

//��ͣ���� ����˯��ģʽ
void Sleep(void)
{
	Basic_control(CMD_SLEDDP);
}

//����
void Peset(void)
{
	Basic_control(CMD_RESET);
}

//����
void Play(void)
{
	Basic_control(CMD_PLAY);
}

//��ͣ
void Pause(void)
{
	Basic_control(CMD_PAUSE);
}

//���ش���
void back_err(void)
{
	Basic_control(CMD_BACK_ERR);
}

//��ѯ״̬
void check_state(void)
{
	Basic_control(CMD_CHECK_SATE);
}

//��ѯ����
void check_vol(void)
{
	Basic_control(CMD_CHECK_SATE);
}

//jq6500����ģ��ָ����Ŀ����
void PlayNum(uint8_t nub)
{
	uint8_t temp[6]={0x7e,0x04,0x03,0x00,0x01,0xEF};	
	temp[3]=nub/256;
	temp[4]=nub%256;
	UART3_Send_Data(temp,6);
}
//ָ������ ������Χ0-30������00��1E
void Volume(uint8_t nub)
{
	uint8_t temp[5]={0x7e,0x03,0x06,0x15,0xef};	
	temp[3]=nub;
	UART3_Send_Data(temp,5);
}
//6�ֲ���ģʽ 00Normal/01Pop/02Rock/03Jazz/04Classic/05Base
void PlayMode(uint8_t nub)
{
	uint8_t temp[5]={0x7e,0x03,0x07,0x01,0xef};	
	temp[3]=nub;
	UART3_Send_Data(temp,5);
}
//ָ���豸   0 U/1 TF/2 AUX/3 SLEEP/4 FLASH
void SelectDevice(uint8_t nub)
{
	uint8_t temp[5]={0x7e,0x03,0x09,0x01,0xef};	
	temp[3]=nub;
	UART3_Send_Data(temp,5);
}

//5��ѭ������ģʽ 0 ALL/ 1 FOL/ 2 ONE/ 3 RAM/ 4 ONE_STOP
void LoopMode(uint8_t nub)
{
	uint8_t temp[5]={0x7e,0x03,0x11,0x00,0xef};	
	temp[3]=nub;
	UART3_Send_Data(temp,5);
}
void JQ6500_voice_nub(uint8_t temp)
{
	switch(temp)
	{
		case 0:PlayNum(1);break;	
		case 1:PlayNum(2);break;
		case 2:PlayNum(3);break;
		case 3:PlayNum(4);break;
		case 4:PlayNum(5);break;
		case 5:PlayNum(6);break;
		case 6:PlayNum(7);break;
		case 7:PlayNum(8);break;
		case 8:PlayNum(9);break;
		case 9:PlayNum(10);break;
		default :break;
	}
}
//Jq6500���ֲ��� 
/*
* ʹ�ô˺����������밴�����·�ʽ ��¼
* ��һ������ 0
* �ڶ������� 1
*  ........
* ��ʮһ������ ʮ
* ��ʮ�������� ��
* ��ʮ�������� ��
* ��ʮ�������� ǧ
* ��ʮ�������� ��
*/  
void JQ6500_voice_data(u32 data)
{
	uint8_t temp_valu[6];
	temp_valu[0]=data/1000000;
	if(data==0)
	{
		JQ6500_voice_nub(0);
		return;
	}
	if(temp_valu[0]!=0)
	{
		JQ6500_voice_nub(temp_valu[0]);
		PlayNum(15);//��
	}
	
	temp_valu[1]=data/100000%10;
	if(temp_valu[1]!=0)
	{
		JQ6500_voice_nub(temp_valu[1]);
		PlayNum(14);//ǧ
	}
	else if(temp_valu[0]!=0)
	{
		JQ6500_voice_nub(temp_valu[1]);//0
	}
	
	temp_valu[2]=data/10000%10;
	if(temp_valu[2]!=0)
	{
		JQ6500_voice_nub(temp_valu[2]);
		PlayNum(13);//��
	}
	else if(temp_valu[1]!=0)
	{
		JQ6500_voice_nub(temp_valu[2]);//0
	}

	temp_valu[3]=data/1000%10; 
	if(temp_valu[3]!=0)
	{
		JQ6500_voice_nub(temp_valu[3]);
		PlayNum(11);//ʮ
	}
	else if(temp_valu[2]!=0)
	{
		JQ6500_voice_nub(temp_valu[3]);//0
	}
	
	temp_valu[4]=data/100%10;
	if(temp_valu[4]!=0)
	{
		JQ6500_voice_nub(temp_valu[4]);
	}
	//С��λ
	temp_valu[5]=data/10%10;
	if(temp_valu[5]!=0)
	{
		PlayNum(12);
		JQ6500_voice_nub(temp_valu[5]);
	}
}


