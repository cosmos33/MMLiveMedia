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
@end

#endif /* MLSoxAudioEffect_h */
