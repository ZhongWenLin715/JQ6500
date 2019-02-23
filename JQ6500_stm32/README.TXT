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
 * 2019.2.20 优化代码.
 *
 * **********************************************************************
 */
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


/******************************************/
使用JQ6500_voice_data(u32 data)请遵循以下方式
//Jq6500数字播报 
/*
* 使用此函数语音必须按照以下方式 烧录
* 第一条语音 0
* 第二条语音 1
*  ........
* 第十一条语音 十
* 第十二条语音 点
* 第十三条语音 百
* 第十四条语音 千
* 第十五条语音 万
*/  