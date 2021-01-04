//
//  MLSoxAudioEffect.h
//  soxSoundEffects
//
//  Created by MOMO on 2019/1/8.
//  Copyright © 2019年 MOMO. All rights reserved.
//

#ifndef MLSoxAudioEffect_h
#define MLSoxAudioEffect_h
typedef NS_ENUM(NSInteger, MLAudioCatogeryType) {
    MLAudioCatogeryTypeYuanYin    = 0,
    MLAudioCatogeryTypeJuYuan     = 1,
    MLAudioCatogeryTypeDiXiaShi   = 2,
    MLAudioCatogeryTypeYuShi      = 3,
    MLAudioCatogeryTypeBanGongShi = 4,
    MLAudioCatogeryTypeKTV        = 5,
    MLAudioCatogeryTypeLuYinShi   = 6,
    MLAudioCatogeryTypeNEWKTV     = 7
};

typedef NS_ENUM(NSInteger, MLAudioEffectType) {
    MLAudioEffectTypeYuanYin    = 0,
    MLAudioEffectTypeElec       = 1
};

@interface MLSoxAudioEffect : NSObject

@property (nonatomic, readonly) int sampleRate;
@property (nonatomic, readonly) int channel;

- (void)openWithSampleRate:(int)sampleRate channel:(int)channel frameLength:(int)frameLength;
- (void)setAudioEffectType:(MLAudioEffectType)type;
- (void)setAudioCatogeryType:(MLAudioCatogeryType)type;//0 原音;1 剧院;2 地下室;3 浴室;4 办公室;5 ktv;6 录音室
- (void)close;
- (NSData *)processEffectData:(NSData *)input;
- (NSData *)processCatogeryData:(NSData *)input;
- (NSData *)processViperEffect:(NSData *)input;

/**
* @brief        设置混响器各项参数
* @inIdx        参数索引
                0---roomScale           房间大小
                1---reverberance        混响大小
                2---damping              衰减
                3---wetGain               湿声增益
                4---dryWetRation       干湿比
                5---preDelay              延迟
* @inValue      参数索引对应的参数值
                roomScale:1~66        默认值66
                reverberance :0~30              默认值8
                damping:0.0~1.0            默认值0.1
                wetGain:-10~10              默认值0
                dryWetRation:0.0~1.0                 干湿比   默认为1
                preDelay:0~100               默认值0
* @usage:       SabineEffectSet_reverb(inEffect,1,2.95);//表示设置混响时间2.95s
*/
- (void)setReverbEffect:(int)index value:(float)value;

/**
* @brief        设置均衡器各项参数
* @inIdx        参数索引
                0       31.25Hz
                1       62.5Hz
                2       125.0Hz
                3       250.0Hz
                4       500.0Hz
                5       1KHz
                6       2KHz
                7       4KHz
                8       8KHz
                9       16KHz
* @inValue      对应均衡器接口索引下的具体调节值，范围：-20dB~20dB，单位dB
* @usage:       setEqEffect(inEffect,5,10);//设定1KHz处band增益为10dB
*/
- (void)setEqEffect:(int)index value:(float)value;

/**
* @brief        设置均衡器各项参数
* @inFc        中心频率,单位HZ
* @bandwidth      带宽范围
*/
- (void)setBandPassEffect:(int)inFc value:(int)bandwidth;

/**
* @brief        设置增益各项参数
* @gainValue     设置增益，范围：-20dB~20dB，单位dB
*/
- (void)setGainEffect:(int)gainValue;

/**
* @enable        enable 1 打开3D音效效果，0 关闭3D音效效果
*/
- (void)setEnableAudioEffect3D:(BOOL)enable;

/**
* @enable        enable 1 打开音乐增强效果，0 关闭音乐增强效果
*/
- (void)setEnableMusicBoost:(BOOL)enable;

/**
* @enable        enable 1 打开语音增强效果，0 关闭语音增强效果
*/
- (void)setEnableVoiceBoost:(BOOL)enable;

/**
* @enable        enable 1 打开语音增强效果，0 关闭语音增强效果
*/
- (void)setEnableMusicBoost3D:(BOOL)enable;

/**
* @enable        enable 1 打开HIFI效果，0 关闭HIFI效果
*/
- (void)setEnableHIFIEffect:(BOOL)enable;

/**
* @enable        enable 1 打开HIFI增强版效果，0 关闭HIFI效果
* 主要用于不插耳机时的HIFI音效
*/
- (void)setEnableHIFIEnhanceEffect:(BOOL)enable;

- (void)closeAllEffect;
@end

#endif /* MLSoxAudioEffect_h */
