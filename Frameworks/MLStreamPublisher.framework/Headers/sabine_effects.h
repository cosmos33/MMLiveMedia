#ifndef AEF_H
#define AEF_H

#include "Platform.h"

typedef struct SabineEffect SabineEffect;
enum MODE {
	DENOISE_MODE = 1,
	REVERB_MODE = 2,
	EQ_MODE = 3
};
#ifdef  __cplusplus
extern "C" {
#endif
    /**
     * @brief       创建效果器
     * @inFs        采样率
     * @inChannels  通道数，mono = 1，stereo = 2
     * @nFrameSize  帧长，PCM样点数，1个PCM对应2byte.
     * @Return      效果器实例
     */
    SabineEffect* SabineEffectOpen(OsInt32 inFs, OsInt32 inChannels, OsInt32 nFrameSize);
    
    /**
     * @brief       销毁效果器
     * @inEffect    效果器实例
     */
    void SabineEffectClose(SabineEffect* inEffect);
    
    /**
     * @brief       实时效果器处理
     * @inEffect    效果器实例
     * @ioPcm       输入输出buf
     * @inLen       输入帧采样数目 = 输出帧采样数目 
     */
    void SabineEffectProcess(SabineEffect* inEffect, OsInt16* ioPcm, OsInt32 inLen);

	/**
	* @brief        设置效果器各项参数
	* @inEffect     效果器算法实例
	* @nMode        指定效果器模式
	1---DENOISE_MODE     降噪
	2---REVERB_MODE      混响
	3---EQ_MODE          EQ
	* @inIdx        索引值，此处关联指定Mode下的详细索引
	* @inValue      调节值，此处为具体调节值
	* @usage:

	Mode(DENOISE_MODE/REVERB_MODE/EQ_MODE)
	|
	|---denoise
	|   |
	|   |-- inIdx   降噪模式提供四个降噪程度调节，inIdx默认值1，设定说明如下
	|   |       |
	|   |       |---0       关闭降噪
	|   |       |---1       轻微降噪
	|   |       |---2       中等降噪
	|   |       |---3       重度降噪
	|   |
	|   |-- inValue 根据降噪程度 inValue默认值0.2，具体可以根据以下范围微调
	|           |
	|           |---0.0            关闭降噪数值
	|           |---(0.0-0.1)      轻微降噪调节范围
	|           |---(0.1-0.2)      中等降噪调节范围
	|           |---(0.2-0.3)      重度降噪调节范围
	|
	|   <case1> 关闭降噪
	|           SabineEffectSet(inEffect,DENOISE_MODE,0,0.0);
	|
	|---reverb
	|   |
	|   |-- inIdx   混响模式提供四个接口调节，如下
	|   |       |
	|   |       |---1       混响大小调节索引/Users/lookpoi/Desktop/FM/sabineDAF/sabineDAF
	|   |       |---2       混响深度调节索引
	|   |       |---3       混响增益调节索引
	|   |       |---4       回声时间调节索引
	|   |
	|   |-- inValue 对应混响接口索引下的具体调节值，inValued的默认值为0.5 0.5 0 0，调节范围均为(0.0-1.0）
	|
	|   <case2> 设定混响增益程度为0.05
	|           SabineEffectSet(inEffect,REVERB_MODE,3,0.05);
	|
	|---Eq
	|
	|-- inIdx   均衡器提供10段band索引调节
	|       |
	|       |---0       31.25Hz
	|       |---1       62.5Hz
	|       |---2       125.0Hz
	|       |---3       250.0Hz
	|       |---4       500.0Hz
	|       |---5       1KHz
	|       |---6       2KHz
	|       |---7       4KHz
	|       |---8       8KHz
	|       |---9       16KHz
	|
	|-- inValue 对应均衡器接口索引下的具体调节值，范围：-20dB~20dB，单位dB，超出范围设置无效

	<case 3> 设定1KHz处band增益为8dB
	SabineEffectSet(inEffect,EQ_MODE,4,8);

	[usage]
	<case1>
	SabineEffectSet(inEffect,DENOISE_MODE,0,0.0);
	<case2>
	SabineEffectSet(inEffect,REVERB_MODE,3,0.05);
	<case3>
	SabineEffectSet(inEffect,EQ_MODE,4,8);
	*/

	void SabineEffectSet(SabineEffect* inEffect, OsInt16 nMode, OsInt32 inIdx, OsFloat inValue);

/***********************************************************************************************************************************/

	/*
	* @brief        设置降噪参数
	* @inEffect     效果器算法实例
	* @inValue      调节值，此处为具体调节值，根据降噪程度 inValue默认值0.2，具体可以根据以下范围微调
                    0.0---关闭降噪数值
                    (0.0-0.1)---轻微降噪调节范围
                    (0.1-0.2)---中等降噪调节范围
	                (0.2-0.9)---重度降噪调节范围
	* @usage:       SabineEffectSet_ans(inEffect,0.0);//表示设置降噪关闭
	*/
    void SabineEffectSet_ans(SabineEffect* inEffect, OsFloat inValue);

	/**
	* @brief        设置混响器各项参数
	* @inRerverb    效果器算法实例
	* @inIdx        参数索引
	                0---ROOMSIZE          房间大小
	                1---REVTIME           混响时间
	                2---DAMPING           控制早期反射和衰减，值越大，混响越弱
	                3---INPUTBANDWIDTH    控制tone,值越小，混响越响亮
	                4---MIX               控制干/湿声比例,干声较小时，声音听起来更远，干声较大时，人声离麦克风更近。
	                5---EARLYLEVEL        控制早期反射增益，建议-20dB左右
	                6---TAILLEVEL         控制混响拖尾增益，可以将混响扩展，建议-22dB
	* @inValue      参数索引对应的参数值
	                ROOMSIZE:1m~66m        默认值66m
	                REVTIME:0.1s~30s       默认值8s
	                DAMPING:0.0~1.0        默认值0.1
	                INPUTBANDWIDTH:0.0~1.0 默认值0.75
	                MIX:0.0~1.0            默认值1,表示对应干音100%，湿音0%,此时无混响
	                EARLYLEVEL:-70dB~0dB   默认值-20dB
	                TAILLEVEL:-70~0dB      默认值-30dB
	* @usage:       SabineEffectSet_reverb(inEffect,1,2.95);//表示设置混响时间2.95s
	*/
	void SabineEffectSet_reverb(SabineEffect* inEffect, OsInt32 inIdx, OsFloat inValue);

	/************************************************************************/
	/*							PEQ调节一览    

	/* 均衡器初始化10段频率(非固定可以变动)： 31.25, 62.5, 125, 250, 500, 1000, 2000, 4000, 8000, 16000 Hz	
	/*  inFc  :  31.25Hz 62.5Hz		      125Hz	  250Hz				   500Hz	    1000Hz
	/* 	inBand:  0         1			   2	    3				    8		      9 
	/*	inGain:	 X        6db			  -6db	   0db				   6db			 12db
	/*  inQ   :  X		   X			   2		2					2			  X
	/*	mode  : 高通 + Low Sh3elving +  调节频点1 + 调节频点2 + ...  + High Shelving + 低通														
	/*																		
	/*  注: 均衡器10段频率可任意设置 50hz 900hz,频带索引对应mode类型不可动。																	
	/************************************************************************/

	/**
	* @brief   设置高通滤波器和低通滤波器截止频率
	*
	* @inEq	   参量均衡器实例
	* @inBand  频带索引。0:高通滤波器,9:低通滤波器
	* @inFc	   设置截止频率(单位Hz)
	* @param   低通滤波器、高通滤波器打开关闭标志。
	*			0x11	高通滤波打开，这时第一个频带0为高通滤波器
	*           0x10	高通滤波器不使用
	*			0x21	低通滤波器打开，这时最后一个频带为低通滤波器
	*			0x20	低通滤波器不使用
	* @usage:   SabineEffectSet_peq_fliter(inEffect,0,31.25,0x10);//表示高通滤波器关闭
	*/
	void SabineEffectSet_peq_fliter(SabineEffect* inEffect, OsInt32 inBand, OsFloat inFc, OsInt16 on_off);
	/**
	* @brief   设置Low Shelving滤波器和High Shelving滤波器
	* @inEq    参量均衡器实例
	* @inBand  可以设置的值为：1 --> Low Shelving滤波器； 8 --> High Shelving滤波器。超出设置无效
	* @inFc    中心频率（单位：Hz）
	* @inGain  调节的增益，范围：-20dB~20dB，超出设置无效
	* @usage:  SabineEffectSet_peq_Shelving(inEffect,8,62.5,6);//表示High Shelving滤波器在62.5Hz处增益增加6dB
	*/
	void SabineEffectSet_peq_Shelving(SabineEffect* inEffect, OsInt32 inBand, OsFloat inFc, OsFloat inGain);
	/**
	* @brief   设置Peak滤波器
	* @inEq    参量均衡器实例
	* @inBand  可以设置的值为: 2~7 超出设置无效
	* @inFc    中心频率（单位：Hz）
	* @inQ     Q值，中心频率与带宽的比值。值越小，影响的带宽越大、值越大，影响的带宽越小
	* @inGain  调节的增益，范围：-20dB~20dB，超出设置无效
	* @usage:  SabineEffectSet_peq_peak(inEffect,2,125,2,6);//表示125Hz处增益增加6dB,Q值为2
	*/
	void SabineEffectSet_peq_peak(SabineEffect* inEffect, OsInt32 inBand, OsFloat inFc, OsFloat inQ, OsFloat inGain);
	
	/**
	* @brief       重置效果器
	* @inEffect    效果器实例
	* @NOTICE	   为了保证内部算法系数能在新旧两个版本中无冲突，当已经使用了新版本set接口后，如果想回退到旧版本，需要手动调用本接口reset恢复旧版本系数。
	*/
	void SabineEffectReset(SabineEffect* inEffect);
	/**
	* @brief       重置效果器_新版本
	* @inEffect    效果器实例
	* @NOTICE:     为了兼任旧版本接口，当需要调用新版本来处理时需要手动调用该reset_NEW来刷新一下内部算法系数。
	*/
	void SabineEffectReset_NEW(SabineEffect* inEffect);
	/**
	* @brief       获取效果器版本号
	* @inEffect    效果器实例
	*/
    long GetADFVersion();
	/**
	* @brief       效果器ByPass开关
	* @inEffect    效果器实例
	* @inIdx       索引值，此处关联指定Mode下的详细索引
				   1---DENOISE_MODE     降噪
				   2---REVERB_MODE      混响
			       3---EQ_MODE          EQ
	* @inValue     对应索引效果器控制开关，0关 1开,默认关闭。
	* @usage:	   SabineEffectByPass（pSabineEffect,1,1）表示降噪模式开启旁通器，此时降噪失效
				   SabineEffectByPass（pSabineEffect,1,0）表示降噪模式关闭旁通器，此时降噪激活
	**/
	void SabineEffectByPass(SabineEffect* inEffect,int16_t inIdx, int16_t on_off);
#ifdef  __cplusplus
}
#endif

#endif