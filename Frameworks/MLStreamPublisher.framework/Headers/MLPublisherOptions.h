//
//  MLPublisherOptions.h
//  MomoChat
//
//  Created by YuAo on 9/28/16.
//  Copyright © 2016 wemomo.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MLVideoCodecType.h"
#import "MLConferencePublisherRole.h"
#import "MLMediaCommonDefine.h"

/*
 
 - (void)startPublishingWithPublishPath:(nullable NSString *)path
 videoBitrate:(NSUInteger)videobr
 videoFramerate:(NSUInteger)videofr
 audioBitrate:(NSUInteger)audiobr
 audioSamplerate:(NSUInteger)audiosr
 statisticReportCount:(NSInteger)statisticcount
 statisticSec:(NSInteger)statisticsec
 logEventEnable:(NSInteger)logEventEnable
 userID:(nullable NSString*)userid
 roomID:(nullable NSString*)roomid
 provider:(int)provider
 sessionTime:(uint64_t)sessiontime
 codecType:(NSInteger)codectype
 bitrateAdapter:(NSInteger)bitrate_adaptive
 adaptiveCachMax:(NSInteger)adaptive_cachMax
 adaptiveCachMin:(NSInteger)adaptive_cachMin
 isHost:(BOOL)ishost
 confServer:(nullable NSString *)confServer
 confSecurityId:(nullable NSString *)confSecurityId
 confSessionId:(nullable NSString *)confSessionId
 confUserId:(nullable NSString *)confUserId
 maxBufferStartTimestampInMs:(uint64_t)maxBufferStartTimestampInMs;
*/
#ifdef __cplusplus
#define ML_EXTERN extern "C" __attribute__((visibility ("default")))
#else
#define ML_EXTERN extern __attribute__((visibility ("default")))
#endif

ML_EXTERN NSString *const kMLPublisherOption_RoomType; // option type NSNumber,default -1
ML_EXTERN NSString *const kMLPublisherOption_RoomMode; // option type NSNumber,default -1,1=视频场,2=音频场(纯音频连麦)

FOUNDATION_EXPORT void MLPublisherOverrideVideoURLString(NSString *url);

typedef NS_ENUM(NSInteger, MLPublisherIdentify) {
    MLPublisherIdentifyNone = 0,    // pushlisher 类型 默认 不输出日志
    MLPublisherIdentifyMomo,        //  momo日志
    MLPublisherIdentifyWerwolf,     // 狼人杀app 使用 主要用于区分log上报
    MLPublisherIdentifyFriendVideo, //好友快聊
    MLPublisherIdentifyExternal     //业务方(狼人杀， 快聊， 派单等)
};

@interface MLPublisherOptions : NSObject <NSCopying>

@property (nonatomic,readonly,copy) NSDictionary *dictionary;
@property (nonatomic,copy) NSDictionary *chaseDelay;
@property (nonatomic) int networkWarningInterval;

//rtmp推流地址
@property (nonatomic, copy) NSString *publishURLString;
//flv拉流地址（仅在SDK UDP下行，且从CDN回源数据的场景才设置该字段）
@property (nonatomic, copy) NSString *pullURLString;
//flv回源主播uid（仅在SDK UDP下行，且从CDN回源数据的场景才设置该字段）
@property (nonatomic) NSUInteger broadcasterUserId;

//视频 上传码率
@property (nonatomic) NSUInteger videoBitrate;
//视频帧速，每秒x帧
@property (nonatomic) NSUInteger videoFrameRate;
//音频 上传码率
@property (nonatomic) NSUInteger audioBitrate;
//音频 采样率
@property (nonatomic) NSUInteger audioSampleRate;
//上行，每x秒收集一次日志
@property (nonatomic) NSTimeInterval statisticPackageCollectionInterval;
//上行，每满多少条日志上传一次。小于等于0不上传并且不收集。结束时上传一次
@property (nonatomic) NSInteger statisticReportPackageCountThreshold;
//watch上传开关
@property (nonatomic) BOOL watchStatisticEnabled;
//启用V3日志
@property (nonatomic) BOOL useV3Log;

@property (nonatomic,readonly,copy) NSString *userID;
@property (nonatomic,readonly,copy) NSString *roomID;
@property (nonatomic,readonly) NSInteger provider;

@property (nonatomic,readonly) uint64_t sessionTime;
@property (nonatomic) MLVideoCodecType codecType;

@property (nonatomic,readonly) BOOL adaptiveBitrateEnabled;
@property (nonatomic,readonly) NSInteger bitrateAdaptMaximumCacheDuration;
@property (nonatomic,readonly) NSInteger bitrateAdaptMinimumCacheDuration;

@property (nonatomic,readonly,copy) NSString *conferenceServer;
@property (nonatomic,readonly,copy) NSString *conferenceSecurityID;
@property (nonatomic,copy) NSString *conferenceSessionID;
@property (nonatomic,copy) NSString *conferenceUserID;

@property (nonatomic,readonly) NSInteger maximumBufferStartDuration;

@property (nonatomic,readonly) BOOL isUseHighQualityAudio;

@property (nonatomic) MLPublisherIdentify publisherIdentify;
@property (nonatomic,copy) NSString *serviceType;   //业务方(狼人杀， 快聊， 派单等)
@property (nonatomic,assign) NSInteger businessType;   //用于区分业务
@property (nonatomic,assign) NSInteger avFlag;   //用于区分音视频 1-视频 2-音频
//@property (nonatomic, readonly) MLBroadcasterResolutionLevel resolutionLevel;

@property (nonatomic, copy) NSString *dynamicKeyAppID;
@property (nonatomic, copy) NSString *dynamicKey;
@property (nonatomic, copy) NSString *privateMapKey;
@property (nonatomic, copy) NSString *userSign; //腾讯进房key

- (instancetype)initWithRoomID:(NSString *)roomID
                        userID:(NSString *)userID
                   isRoomOwner:(BOOL)isRoomOwner
          radioHighAudioEnable:(BOOL)highAudioEnable
                    dictionary:(NSDictionary *)dictionary;

//使用默认配置，如需修改参数，直接调用参数属性修改
- (instancetype)initWithRoomID:(NSString *)roomID
                        userID:(NSString *)userID;

- (instancetype)initWithRoomID:(NSString *)roomID
                        userID:(NSString *)userID
                      provider:(int)provider
                  businessType:(int)businessType;
@end
