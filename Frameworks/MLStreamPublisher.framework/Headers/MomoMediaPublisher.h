//
//  MomoMediaEngine.h
//  Pods
//
//  Created by hrs on 2019/8/29.
//

#ifndef MomoMediaEngine_h
#define MomoMediaEngine_h
#import <Foundation/Foundation.h>
#import "MomoMediaContext.h"

typedef NS_ENUM(NSUInteger, MomoMediaPublisherLinkType) {
    MomoMediaPublisherLinkTypeDefault,
    MomoMediaPublisherLinkTypeAgora,
};

@class MomoMediaPublisher;
@protocol MomoMediaPublisherDelegate <NSObject>

@optional
// 推流器开始推流
- (void)MomoMediaEngineDidStartPublishing:(MomoMediaPublisher*)publisher error:(NSError*)error;
// 推流器停止推流
- (void)MomoMediaEngineDidStopPublishing:(MomoMediaPublisher*)publisher error:(NSError*)error;
// 推流器推流失败
- (void)MomoMediaEnginePublishingFailed:(MomoMediaPublisher *)publisher error:(NSError*)error;
// 推流卡顿开始
- (void)MomoMediaEnginePublishingStartBuffer:(MomoMediaPublisher*)publisher error:(NSError*)error;
// 推流卡顿结束
- (void)MomoMediaEnginePublishingEndBuffer:(MomoMediaPublisher *)publisher error:(NSError*)error;
// 用户自己加入频道
- (void)MomoMediaEnginePublisher:(MomoMediaPublisher *)publisher hostDidJoinChannel:(NSString *)channel;
// 其他用户加入频道
- (void)MomoMediaEnginePublisher:(MomoMediaPublisher *)publisher didRemoteJoinChannel:(NSString *)channel withUid:(NSUInteger)uid;
// rtmp推流器已经有数据发出
- (void)MomoMediaEnginePublisherDidStartRtmpPushPublishing:(MomoMediaPublisher *)publisher error:(NSError*)error;
// 其他用户退出频道
- (void)MomoMediaEnginePublisher:(MomoMediaPublisher *)publisher onMemberExitWithUserId:(NSString *)userId reason:(NSInteger)reason;
// 用户离开频道
- (void)MomoMediaEnginePublisherDidLeaveChannel:(MomoMediaPublisher *)publisher;
// 连麦成功
- (void)MomoMediaEnginePublisher:(MomoMediaPublisher *)publisher onConnectionSuccessWithHostId:(NSString *)hostId guestId:(NSString *)guestId;
// 其他用户掉线
- (void)MomoMediaEnginePublisher:(MomoMediaPublisher *)publisher didOfflineOfUid:(NSString *)uid;
- (void)MomoMediaEnginePublisher:(MomoMediaPublisher *)publisher didOfflineOfUid:(NSString *)uid reason:(NSUInteger)reason;
//声网上报错误
- (void)MomoMediaEnginePublisher:(MomoMediaPublisher *)publisher didOccurError:(NSError*)error;
// 收到其他用户第一帧视频
- (void)MomoMediaEnginePublisher:(MomoMediaPublisher *)publisher didReceivedVideoForRemoteId:(NSString *)uid remoteView:(UIView *)remoteView;
// 其他用户声音是否静音
- (void)MomoMediaEnginePublisher:(MomoMediaPublisher *)publisher didRemoteAudioMuted:(BOOL)muted remoteUid:(NSUInteger)uid;
// 其他用户画面是否关闭
- (void)MomoMediaEnginePublisher:(MomoMediaPublisher *)publisher didRemoteVideoMuted:(BOOL)muted remoteUid:(NSUInteger)uid;
// 推流数据到达cdn（经验值），只用于平滑切换的优化方案
- (void)MomoMediaEnginePublisherDidReceivedCDN:(MomoMediaPublisher *)publisher frameCount:(NSUInteger)frameCount;
@end

@interface MomoMediaPublishConfiguration : NSObject
//分辨率
@property(nonatomic, assign) CGSize videoEncodeSize;
//帧率
@property(nonatomic, assign) int videoFPS;
//视频编码码率（单位bps）
@property(nonatomic, assign) int videoBitRate;
@property(nonatomic, assign) BOOL enableAutoBitRate;
@property(nonatomic, assign) int videoBitRateMax;
@property(nonatomic, assign) int videoBitRateMin;
//码率（音频）
@property(nonatomic, assign) int audioSampleRate;
//音频声道数
@property(nonatomic, assign) int audioChannels;
//音频编码码率(单位bps)
@property(nonatomic, assign) int audioBitRate;
//耳返
@property(nonatomic, assign) BOOL enableAudioPreview;
//噪声抑制
@property(nonatomic, assign) BOOL enableNAS;

@end

@protocol MLStreamMediaDataConsumer;
@interface MomoMediaPublisher : NSObject <MLStreamMediaDataConsumer>

@property (nonatomic, weak) id<MomoMediaPublisherDelegate> delegate;

//当前的推流状态,1为正在推流,0位推流结束.
@property (nonatomic, assign) BOOL isPushing;

@property(nonatomic,readonly) NSString *rtmpURL;

//可以动态的设置耳返
@property(nonatomic, assign) BOOL enableAudioPreview;

//初始化推流器,如果通过setupOnContainerView设置view,此处的view设置为nil
- (instancetype)initWithMomoMediaPublisher:(UIView *)view inputVideoSize:(CGSize)inputVideoSize;

//设置预览
- (void)setupOnContainerView:(UIView *)containerView;
//设置推流参数
- (void)setPublishConfig:(MomoMediaPublishConfiguration*)config;
//设置推流地址
- (void)startPublish:(NSString*)rtmpURL;
//停止推流
- (void)stopPublish;

- (void)setMute:(BOOL)bEnable;//设置静音

- (void)pausePublish;//退后台调用该接口

- (void)resumePublish;//回前台恢复推流调用该接口

- (void)updateLocalViewWithFrame:(CGRect)frame;

/// 设置连麦类型
/// @param linkType 连麦类型
/// @param appId 第三方连麦sdk的appid
- (void)setLinkType:(MomoMediaPublisherLinkType)linkType appId:(NSString *)appId;

/// 设置加入房间的配置信息
/// @param isHost 是否为主播
/// @param channelName 连麦房间id
/// @param userId 连麦用户id
/// @param channelKey 用户认证信息
- (void)setJoinParamsIsHost:(BOOL)isHost channelName:(NSString *)channelName userId:(long)userId channelKey:(NSString *)channelKey;

/// 关闭本地视频分送
/// @param mute 是否关闭本地视频发送
- (void)muteLocalVideo:(BOOL)mute;

/// 更新sdk动态key
/// @param channelKey sdk动态key
- (void)updateChannelKey:(NSString *)channelKey;

/// 更新连线SEI
/// @param info SEI信息
- (void)updateSeiDataForConnectWithSeiDict:(NSDictionary *)info;

@end
#endif /* MomoMediaEngine_h */
