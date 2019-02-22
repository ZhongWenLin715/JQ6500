/**
 * **********************************************************************
 * @file Jq6500.c
 * @author 旺财也爱IOT
 * @version V1.0
 * @date 2018.12.26
 * @brief jq6500语音模块 驱动函数文件.
 *
 * **********************************************************************
 * @note
 * 2019.1.30 重写底层.
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
//0x45	查询当前播放模式	返回值0 1 2 3 4对应(ALL FOL ONE RAM ONE_STOP)【7E 02 45 EF】
//0x46	查询当前软件版本	【7E 02 46 EF】
//0x47	查询TF卡的总文件数	【7E 02 47 EF】
//0x48	查询UDISK的总文件数	【7E 02 48 EF】
//0x49	查询FLASH的总文件数	【7E 02 49 EF】
//0x4B	查询TF卡的当前曲目	【7E 02 4B EF】
//0x4C	查询UDISK的当前曲目	【7E 02 4C EF】
//0x4D	查询FLASH的当前曲目	【7E 02 4D EF】
//0x50	查询的当前播放时间	【7E 02 50 EF】
//0x51	查询的当前播放歌曲总时间	【7E 02 51 EF】
//0x52	查询的当前播放歌曲名字	返回值为歌曲名字（SPIflsh不支持）【7E 02 52 EF】
//0x53	查询的当前文件夹的总文件夹数	【7E 02 53 EF】
void JQ6500_Init(void);//jq6500 IO初始化
u8 voice_SumCheck(u8 *Str,u8 len);//8位校验和
void JQ6500_Next(void);//下一曲
void JQ6500_Prev(void);//上一曲
void PlayNum(u8 nub);//jq6500语音模块指定曲目播放
void VolAdd(void);//音量+
void VolLess(void);//音量-
void Volume(u8 nub);//指定音量 音量范围0-30，设置00到1E
void PlayMode(u8 nub);//6种播放模式 00Normal/01Pop/02Rock/03Jazz/04Classic/05Base
void SelectDevice(u8 nub);//指定设备   0 U/1 TF/2 AUX/3 SLEEP/4 FLASH
void Sleep(void);//暂停播放 进入睡眠模式
void Peset(void);
void Play(void);//播放
void Pause(void);//暂停
void back_err(void);
void check_state(void);
void LoopMode(u8 nub);//5种循环播放模式 0 ALL/ 1 FOL/ 2 ONE/ 3 RAM/ 4 ONE_STOP
void JQ6500_voice_nub(u8 temp);
void JQ6500_voice_data(u32 data);//Jq6500数字播报(使用前请在.c文件中阅读详情)
#endif


