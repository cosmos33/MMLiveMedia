//
//  MMLiveRTMPPush.h
//  Pods
//
//  Created by hrs on 2020/2/6.
//

#ifndef MMLiveRTMPPush_h
#define MMLiveRTMPPush_h
#import <Foundation/Foundation.h>
#import "MMCommonParam.h"
#import <CoreMedia/CoreMedia.h>
@class MMLiveRTMPPush;
#pragma mark - MMLiveRTCDelegate
@protocol MMLiveRTMPPushDelegate <NSObject>

@optional
/**
推流器开始推流
*/
- (void)MMLiveRTMPPushStarting:(MMLiveRTMPPush*)pusher error:(NSError*)error;

/**
推流器停止推流
*/
- (void)MMLiveRTMPPushStopped:(MMLiveRTMPPush*)pusher error:(NSError*)error;

/**
推流器推流失败
*/
- (void)MMLiveRTMPPushFailed:(MMLiveRTMPPush*)pusher error:(NSError*)error;

/**
推流卡顿开始
*/
- (void)MMLiveRTMPPushBufferStart:(MMLiveRTMPPush*)pusher error:(NSError*)error;

/**
推流卡顿结束
*/
- (void)MMLiveRTMPPushBufferStopped:(MMLiveRTMPPush*)pusher error:(NSError*)error;

/**
推流数据到达cdn（经验值），只用于平滑切换的优化方案
*/
- (void)MMLiveRTMPPushReplaced:(MMLiveRTMPPush*)pusher error:(NSError*)error;

/**
音乐播放失败
*/
- (void)MMLiveRTMPPushMusicPlayFailed:(MMLiveRTMPPush*)pusher error:(NSError*)error;

/**
音乐播放完成
*/
- (void)MMLiveRTMPPushMusicPlayCompleted:(MMLiveRTMPPush*)pusher error:(NSError*)error;

/**
推流码率和分辨率变化
*/
- (BOOL)MMLiveRTMPPushLevelChange:(MMLiveRTMPPush*)pusher encodeSize:(CGSize)encodeSize videoBitrate:(int)videoBitrate;

/**
伴奏播放失败
*/
- (void)MMLiveRTMPPushEffectPlayFailed:(MMLiveRTMPPush*)pusher effectId:(int)effectId error:(NSError*)error;

/**
伴奏播放完成
*/
- (void)MMLiveRTMPPushEffectPlayCompleted:(MMLiveRTMPPush*)pusher effectId:(int)effectId error:(NSError*)error;

/**
推流地址变化
*/
- (void)MMLiveRTMPPushDidChangeStreamUrl:(MMLiveRTMPPush*)pusher;

/**
获取采集大小
*/
- (CGSize)MMLiveRTMPPushGetCaptureSize:(MMLiveRTMPPush*)pusher;

// 获取源数据
- (CVPixelBufferRef)MMLiveRTMPPush:(MMLiveRTMPPush *)publisher rawData:(CVPixelBufferRef)rawdata;

- (void)MMLiveRTMPPush:(MMLiveRTMPPush *)publisher  publisherStatisticMediaWatch:(NSMutableDictionary*)aParam;

@end


@protocol MLStreamMediaSource;
@interface MMLiveRTMPPush : NSObject
@property (nonatomic, weak) id<MMLiveRTMPPushDelegate> delegate;
@property (nonatomic, readonly, strong) MMLiveMediaConfig *pusherConfig;
@property (nonatomic, strong) MMLiveUserConfig *userConfig;
/**
* MMLiveSource的输出结点
* 把MMLiveRTMPPush 的sourceHandle 添加 到MMLiveSource，才可以进行预览和推流
*/
@property (nonatomic, strong) id sourceHandle;

- (instancetype)initWithUserConfig:(MMLiveUserConfig *)userConfig;

/**
* 用户传入自己图像
*
* @param sampleBuffer 传入的图像
* @return YES 代表传入成功， NO 代表传入失败
*/
- (BOOL)pushExternalVideoSampleBuffer:(CMSampleBufferRef)sampleBuffer;

/**
* 用户传入自己音频
*
* @param sampleBuffer 传入的音频
* @return YES 代表传入成功， NO 代表传入失败
*/
- (BOOL)pushExternalAudioSampleBuffer:(CMSampleBufferRef)sampleBuffer;

- (void)mediaSource:(id<MLStreamMediaSource>)source didOutputVideoSampleBuffer:(CMSampleBufferRef)sampleBuffer;
/**
* 开始推流
*
* @param config 推流媒体参数
*/
- (int)startPush:(MMLiveMediaConfig*) config;

/**
* 停止推流
*
*/
- (void)stopPush;

/**
* 打开平滑切换功能，默认关闭
*
* @param enable YES 打开 NO 关闭
*/
- (void)enableStreamReplace:(BOOL)enable;

/**
* 准备入会功能，默认关闭
*
* @param enable YES 打开 NO 关闭
*/
- (void)enableReadyConference:(BOOL)enable;

/**
* 平滑切换RTC 音频传到iIJK
*
* @param data 连线的音频数据
*/
- (void)pushConferenceAudioPacket:(NSData *)data audioInfo:(NSDictionary *)audioInfo;

//是否开启音量大小回调
- (void)setAudioVolumeIndication:(BOOL)enable interval:(int)interval;

/**
* 实时的获取推流的上行码率
*
* @return 上行码率,单位kbps (建议获取间隔不要小于2s)
*/
- (long) getRealTimePushBitRate;

- (NSDictionary *) getPushWatchInfo;

- (void)setBusinessType:(NSInteger)businessType;

@end
#endif /* MMLiveRTMPPush_h */
