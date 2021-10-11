//
//  MLSabineAudioEffect.h
//  MomoChat
//
//  Created by wangqiangqiang on 2017/8/16.
//  Copyright © 2017年 wemomo.com. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface MLSabineAudioEffect : NSObject

@property (nonatomic, readonly) int sampleRate;
@property (nonatomic, readonly) int channel;

- (void)openWithSampleRate:(int)sampleRate channel:(int)channel frameLength:(int)frameLength;
- (void)close;
- (NSData *)processData:(NSData *)input;
- (BOOL)setAudioEffect:(int)type index:(int)index value:(float)value;
- (void)setAudioEffectToDefault;

//下面接口支持更灵活的参数设置

/*
 * @brief        设置降噪参数
 * @inValue      调节值，此处为具体调节值，根据降噪程度 inValue默认值0.2，具体可以根据以下范围微调
      0.0---关闭降噪数值
     (0.0-0.1)---轻微降噪调节范围
     (0.1-0.2)---中等降噪调节范围
     (0.2-0.9)---重度降噪调节范围
 * @usage: setAudioEffectAns(0.0);//表示设置降噪关闭
 */
- (void)setAudioEffectAns:(float)inValue;

/**
 * @brief        设置混响器各项参数
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
     MIX:0.0~1.0            默认值0.444,表示对应干音0.444，湿音0.556
     EARLYLEVEL:-70dB~0dB   默认值-20dB
     TAILLEVEL:-70~0dB      默认值-30dB
 * @usage: setAudioEffectReverb(1, 2.95);//表示设置混响时间2.95s
 */
- (void)setAudioEffectReverb:(int)index value:(float)inValue;

/**
 * @brief   设置高通滤波器和低通滤波器截止频率
 * @inBand  频带索引。0:高通滤波器,9:低通滤波器
 * @inFc    设置截止频率(单位Hz)
 * @onOff   低通滤波器、高通滤波器打开关闭标志。
 *            0x11    高通滤波打开，这时第一个频带0为高通滤波器
 *            0x10    高通滤波器不使用
 *            0x21    低通滤波器打开，这时最后一个频带为低通滤波器
 *            0x20    低通滤波器不使用
 * @usage:  setAudioEffectPeqFliter(0, 31.25, 0x10);//表示高通滤波器关闭
 */
- (void)setAudioEffectPeqFliter:(int)inBand frequence:(float)inFc onOff:(int)onOff;

/**
 * @brief   设置Low Shelving滤波器和High Shelving滤波器
 * @inBand  可以设置的值为：1 --> Low Shelving滤波器； 8 --> High Shelving滤波器。超出设置无效
 * @inFc    中心频率（单位：Hz）
 * @inGain  调节的增益，范围：-20dB~20dB，超出设置无效
 * @usage:  setAudioEffectPeqShelving(8, 62.5, 6);//表示High Shelving滤波器在62.5Hz处增益增加6dB
 */
- (void)setAudioEffectPeqShelving:(int)inBand frequence:(float)inFc gain:(float)inGain;

/**
 * @brief   设置Peak滤波器
 * @inBand  可以设置的值为: 2~7 超出设置无效
 * @inFc    中心频率（单位：Hz）
 * @inQ     Q值，中心频率与带宽的比值。值越小，影响的带宽越大、值越大，影响的带宽越小
 * @inGain  调节的增益，范围：-20dB~20dB，超出设置无效
 * @usage:  setAudioEffectPeqPeak(2, 125, 2, 6);//表示125Hz处增益增加6dB,Q值为2
 */
- (void)setAudioEffectPeqPeak:(int)inBand frequence:(float)inFc inQ:(float)inQ gain:(float)inGain;

@end
