//
//  MLAudioEffectManager.h
//  MomoChat
//
//  Created by wangqiangqiang on 2017/9/25.
//  Copyright © 2017年 wemomo.com. All rights reserved.
//

#import <Foundation/Foundation.h>

@class MLAudioEffectManager;
@protocol MLAudioEffectManagerDelegete <NSObject>
@optional
- (void)audioEffectManager:(MLAudioEffectManager *)manager didAudioEffectFailed:(int)effectId;
- (void)audioEffectManager:(MLAudioEffectManager *)manager didAudioEffectFinish:(int)effectId;

@end

@interface MLAudioEffectManager : NSObject

@property (nonatomic, weak) id<MLAudioEffectManagerDelegete> delegate;

- (instancetype)initWithSampleRate:(int)sampleRate channel:(int)channel;

- (void)playEffectWithId:(int)effectId url:(NSString *)url loop:(BOOL)loop publish:(BOOL)publish;
- (void)stopEffectWithId:(int)effectId;
- (void)stopAllEffect;
//音效的音量取值范围为[0.0, 1.0],默认值为1.0
- (void)setEffectVolumeWithId:(int)effectId withVolume:(double)volume;
//获取指定数量的音效数据，返回YES表示可能进行了混音
- (BOOL)getPlaybackData:(NSData *)playbackData;
- (BOOL)getSendoutData:(NSData *)sendoutData;

@end
