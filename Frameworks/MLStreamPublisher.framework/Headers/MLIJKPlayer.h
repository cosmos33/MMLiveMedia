//
//  MLIJKPlayer.h
//  MomoChat
//
//  Created by LiLingFeng on 9/27/16.
//  Copyright © 2016 wemomo.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MLPlayer.h"
#import "MMLiveContext.h"

typedef enum {
    MLIJKPlayerAudioEffectClose = 0, //关闭音效
    MLIJKPlayerAudioEffect3D = 1, //3D音效
    MLIJKPlayerAudioEffectHIFI = 2 //HIFI音效
} MLIJKPlayerAudioEffect;

@class MLPlayerStatistic;

FOUNDATION_EXPORT void MLIJKPlayerOverrideVideoURLString(NSString *url);
FOUNDATION_EXPORT NSString * MLIJKPlayerOverridedVideoURLString(void);
FOUNDATION_EXPORT void MLIJKPlayerUseHardVideoCoder(BOOL enable);
FOUNDATION_EXPORT void MLIJKPlayerUseAudioUnitRender(BOOL enable);

typedef void (^StopCompleteBlock)(BOOL finished);

@interface MLIJKPlayer : NSObject <MLPlayer>
/// 播放器委托
@property (nonatomic, weak) id<MLPlayerDelegate> delegate;
/// 是否正在播放
@property (nonatomic, assign, readonly) BOOL isPlaying;
@property (nonatomic, assign) int playbackErrorNo; // 播放错误码
@property (nonatomic, assign) int playbackAdditionInfo; // 某些错误会有额外信息
@property (nonatomic, copy) StopCompleteBlock stopCompleteBlock;
@property (nonatomic, strong, readonly) MLPlayerVideoDetail *detail;
@property (nonatomic, strong) MMLiveUserContext *userContext;

/**
 唯一初始化方法
 
 @param detail 视频的信息详情
 @param view 视频的容器视图
 @param playback 播放时刻等小视频需要设置为YES，默认为NO
 @param onlyAudio 纯音频播放
 */

- (instancetype)initWithDetail:(MLPlayerVideoDetail *)detail
            videoConfiguration:(NSInteger)videoConfiguration
                        inView:(UIView *)view
                      playback:(BOOL)playback
                     onlyAudio:(BOOL)onlyAudio
                         appId:(NSString *)appId
                        secret:(NSString *)secret
                     appVerNum:(NSString *)appVerNum
                        userId:(NSString *)userId;

- (instancetype)initWithDetail:(MLPlayerVideoDetail *)detail videoConfiguration:(NSInteger)videoConfiguration inView:(UIView *)view playback:(BOOL)playback onlyAudio:(BOOL)onlyAudio;

- (instancetype)initWithDetail:(MLPlayerVideoDetail *)detail videoConfiguration:(NSInteger)videoConfiguration inView:(UIView *)view playback:(BOOL)playback;

- (instancetype)initWithURL:(NSURL *)URL videoConfiguration:(NSInteger)videoConfiguration renderView:(UIView *)view;

- (instancetype)initWithURL:(NSURL *)URL videoConfiguration:(NSInteger)videoConfiguration renderView:(UIView *)view playback:(BOOL)enable;

/// 不要同时把音视频disable了
- (instancetype)initWithURL:(NSURL *)URL videoConfiguration:(NSInteger)videoConfiguration renderView:(UIView *)view playback:(BOOL)enable disableAudio:(BOOL)disableAudio disableVideo:(BOOL)disableVideo;

- (instancetype)initWithURL:(NSURL *)URL videoConfiguration:(NSInteger)videoConfiguration renderView:(UIView *)view playback:(BOOL)enable autoPlay:(BOOL)autoplay;

- (void)setupStatisticWithRoomID:(NSString *)roomID;

- (void)setLiveSource:(NSString*)source;

/// 播放
- (void)play;
/// 暂停
- (void)pause;
/// 停止
- (void)stop;
- (void)stopWithErrorCode:(PullStopErrorCode)errCode;

- (void)seek:(NSTimeInterval)time;

/// 设置循环播放次数
/// @param loop 循环次数，默认1，设为0表示无限循环
- (void)setLoop:(int)loop;

/// 清空资源
- (void)clean;
/// 禁音
- (void)setMute:(BOOL)mute;
/// 录音频
- (void)recordAudio:(BOOL)enable;
/// 开关音频回调
- (void)switchAudioCallback:(BOOL)enable;
- (void)switchOriginAudioCallback:(BOOL)enable;

- (CGSize)getVideoSize;

- (NSDictionary *)getPullWatch;

- (BOOL)isVideoToolboxOpen;

- (BOOL)isPrepared;
- (NSTimeInterval)getFileDurationInSec;
- (NSTimeInterval)getCurrentPlaybackTimeInSec;
//set audio playback volume (0 ~ 1.0)
- (void)setAudioPlaybackVolume:(float)volume;

//打开多音轨，默认不打开
- (void)openAudioTracks:(BOOL)enable;
//设置播放的音轨，默认是1，只有打开多音轨才支持设置，如双音轨可设置1、2
- (void)setAudioTrackIndex:(int)index;
- (void)setMaxBufferCache:(int)max_buffer_cache;
- (void)setDynamicBuffer:(BOOL)enable;
- (void)updateTransferType:(NSInteger)transferType;
- (void)updateCdnIp:(NSString*)cdnip;
- (void)startTimeCalibrator;
- (SInt64)getCalibtatorTimeDeltaMS;
@property (nonatomic,strong,readonly) MLPlayerStatistic *statistic;

//设置追帧延迟
- (void)setLowerLatency:(Boolean)enable
               withBase:(int)base
       withSpeedTrigger:(int)speed_trigger
        withDropTrigger:(int)drop_trigger
          withSpeedRate:(double)speed_rate;

- (void)updatePlayerDelayConfigWithString:(NSString *)delayConfig;

- (void)setPlayerAudioEffect:(MLIJKPlayerAudioEffect)effect;
@end

#import "MLPlayerStatistic.h"

@interface MLIJKPlayer (MLPlayerStatisticDataProvider) <MLPlayerStatisticDataProvider>

@end
