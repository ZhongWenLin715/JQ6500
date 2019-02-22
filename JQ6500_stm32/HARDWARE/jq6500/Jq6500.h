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
 * 2019.1.30 ��д�ײ�.
 *
 * **********************************************************************
 */
#ifndef __JQ6500_H
#define __JQ6500_H	 
#include "sys.h"
#define voice_busy   PBin(5)

#define CMD_NEXT 			0X01
#define CMD_PREV			0X02
#define CMD_VOL_ADD			0X04
#define CMD_VOL_LESS		0X05
#define CMD_SLEDDP			0x0A
#define CMD_RESET			0X0C
#define CMD_PLAY			0X0D
#define CMD_PAUSE			0X0E
#define CMD_BACK_ERR		0X40
#define CMD_CHECK_SATE		0x42
#define CMD_CHECK_VOL		0X43
#define CMD_CHECK_EQ		0X44
//0x45	��ѯ��ǰ����ģʽ	����ֵ0 1 2 3 4��Ӧ(ALL FOL ONE RAM ONE_STOP)��7E 02 45 EF��
//0x46	��ѯ��ǰ����汾	��7E 02 46 EF��
//0x47	��ѯTF�������ļ���	��7E 02 47 EF��
//0x48	��ѯUDISK�����ļ���	��7E 02 48 EF��
//0x49	��ѯFLASH�����ļ���	��7E 02 49 EF��
//0x4B	��ѯTF���ĵ�ǰ��Ŀ	��7E 02 4B EF��
//0x4C	��ѯUDISK�ĵ�ǰ��Ŀ	��7E 02 4C EF��
//0x4D	��ѯFLASH�ĵ�ǰ��Ŀ	��7E 02 4D EF��
//0x50	��ѯ�ĵ�ǰ����ʱ��	��7E 02 50 EF��
//0x51	��ѯ�ĵ�ǰ���Ÿ�����ʱ��	��7E 02 51 EF��
//0x52	��ѯ�ĵ�ǰ���Ÿ�������	����ֵΪ�������֣�SPIflsh��֧�֣���7E 02 52 EF��
//0x53	��ѯ�ĵ�ǰ�ļ��е����ļ�����	��7E 02 53 EF��
void JQ6500_Init(void);//jq6500 IO��ʼ��
u8 voice_SumCheck(u8 *Str,u8 len);//8λУ���
void JQ6500_Next(void);//��һ��
void JQ6500_Prev(void);//��һ��
void PlayNum(u8 nub);//jq6500����ģ��ָ����Ŀ����
void VolAdd(void);//����+
void VolLess(void);//����-
void Volume(u8 nub);//ָ������ ������Χ0-30������00��1E
void PlayMode(u8 nub);//6�ֲ���ģʽ 00Normal/01Pop/02Rock/03Jazz/04Classic/05Base
void SelectDevice(u8 nub);//ָ���豸   0 U/1 TF/2 AUX/3 SLEEP/4 FLASH
void Sleep(void);//��ͣ���� ����˯��ģʽ
void Peset(void);
void Play(void);//����
void Pause(void);//��ͣ
void back_err(void);
void check_state(void);
void LoopMode(u8 nub);//5��ѭ������ģʽ 0 ALL/ 1 FOL/ 2 ONE/ 3 RAM/ 4 ONE_STOP
void JQ6500_voice_nub(u8 temp);
void JQ6500_voice_data(u32 data);//Jq6500���ֲ���(ʹ��ǰ����.c�ļ����Ķ�����)
#endif


