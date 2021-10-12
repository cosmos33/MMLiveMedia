//
//  MLAgoraPlayer.h
//  MomoLive
//
//  Created by LiLingFeng on 9/8/16.
//  Copyright © 2016 wemomo.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MLPlayer.h"
#import "MLRawAudioFrame.h"
#import "MLPlayerStatistic.h"

/**
 声网SDK是多人视频会话技术，在声网中，一个频道中的人们可以互相通话和视频，每个人地位平等。当用于直播场景的时候，一个直播间就是一个频道，而主播是推送声音和视频，其余观众都只是接收声音和视频。连麦的时候，只有连麦观众和主播在推送声音和视频，其余观众则是接收他们两者的声音和视频。MLAgoraPlayer是从声网SDK中抽离出的播放行为，即观众端只接收声音和视频而无法推送的行为。
 外界通过初始化方法来设置频道ID和主播UID，连麦UID是通过监听是否有新的视频流来获取。当有新的视频流到来的时候认为是开始连麦，同时记录连麦者的UID，通过监听连麦者退出频道来认定连麦结束。因此连麦的逻辑是独立于外界的。
 
 自身实现功能：卡顿监测。
 */
@interface MLAgoraPlayer : NSObject <MLPlayer>
@property (nonatomic, weak) id<MLPlayerDelegate> delegate; // 播放器委托
@property (nonatomic, assign, readonly) BOOL isPlaying; // 是否正在播放所有视频流
@property (nonatomic, copy, readonly) NSString *channelID; // 频道ID
@property (nonatomic, assign, readonly) NSUInteger channelOwnerUID; // 频道创建者（主播）UID
@property (nonatomic, copy) StopCompleteBlock stopCompleteBlock;
@property (nonatomic, strong) MMLiveUserContext *userContext;

- (instancetype)initWithChannelID:(NSString *)channelID channelOwnerUID:(NSUInteger)uid inView:(UIView *)view;
- (void)play; // 播放所有视频流：如果是第一次播放，则会先进入频道再自动播放；如果是已进入频道，则播放先前暂停的视频流
- (void)pause; // 暂停播放所有视频流
- (void)stop; // 结束播放，离开频道
- (void)clean; // 清理资源
- (void)setMute:(BOOL)mute; // 禁音
- (void)recordAudio:(BOOL)enable; // 录音频
- (CGSize)getVideoSize;
- (void)seek:(NSTimeInterval)time;
- (void)setupStatisticWithRoomID:(NSString *)roomID videoDetail:(MLPlayerVideoDetail *)detail;

- (void)onRecordAudioFrame:(MLRawAudioFrame *)audioFrame;
- (void)onPlaybackAudioFrame:(MLRawAudioFrame *)audioFrame;
- (void)onPlaybackAudioFrameBeforeMixing:(unsigned int)uid audioFrame:(MLRawAudioFrame *)audioFrame;
- (void)updateTransferType:(NSInteger)transferType;
- (void)updateCdnIp:(NSString*)cdnip;
@property (nonatomic,strong,readonly) MLPlayerStatistic *statistic;

@end

@interface MLAgoraPlayer (MLPlayerStatisticDataProvider) <MLPlayerStatisticDataProvider>

@end
