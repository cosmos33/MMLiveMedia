//
//  MMCommonParam.h
//  MLStreamPublisher
//
//  Created by hrs on 2020/2/6.
//

#ifndef MMCommonParam_h
#define MMCommonParam_h
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

typedef enum {
    MMLivePlayerStatusPlaying = 0, //播放中
    MMLivePlayerStatusBuffering = 1, //播放加载中
    MMLivePlayerStatusStopped = 2, //播放停止
    MMLivePlayerStatusFinished = 3, //播放结束
    MMLivePlayerStatusFailed = 4, //播放错误
}MMLivePlayerStatus;

typedef enum {
    MMLiveEngineTypeNone = 0,//设置engine 暂时不具备功能
    MMLiveEngineTypePlay = 1,//设置engine 是播放器功能
    MMLiveEngineTypePush = 2,//设置engine 是rtmp推流或者rtc功能
}MMLiveEngineType;

typedef enum {
    MMLiveRTCClientRoleBroadcaster = 0,//连线的角色是主播或者副播
    MMLiveRTCClientRoleAudience    = 1,   //连线的角色是观众
}MMLiveRTCClientRole;

typedef enum {
    MMLivePushTypeConfNONE = 0,
    MMLivePushTypeConfAG   = 1,//连线供应商 声网
    MMLivePushTypeConfTX   = 2,//连线供应商 腾讯
    MMLivePushTypeConfWL   = 3,//连线供应商 三体
    MMLivePushTypeConfMM   = 4,//连线供应商 陌陌
}MMLivePushType;

typedef enum {
    MMLiveAEFilterOriginal    = 0,// 原声
    MMLiveAEFilterET          = 1,// 小怪兽
    MMLiveAEFilterPaPi        = 2,// papi酱
    MMLiveAEFilterTransformer = 3,// 变形金刚
    MMLiveAEFilterRobot       = 4,//机器人
    MMLiveAEFilterMan         = 5,//女变男
    MMLiveAEFilterWoman       = 6,//男变女
    MMLiveAEFilterBaby        = 7,//娃娃音
    MMLiveAEFilterMC          = 8,//mc
    MMLiveAEFilterELE         = 9,//ELE_EFFECT
    MMLiveAEFilterMinions     = 10,//小黄人
    MMLiveAEFilterMute        = 11,//静音
    MMLiveAEFilterGiftRobot   = 12,//礼物机器人
}MMLiveAEFilter;

typedef enum {
    RTCErrorCodeNone                    = 0,
    RTCErrorCodeInvalidAppId            = 1,
    RTCErrorCodeInvalidChannelName      = 2,
    RTCErrorCodeInvalidChannelKey       = 3,
    RTCErrorCodeJoinChannelRejected     = 4,
    RTCErrorCodeChannelKeyExpired       = 5,
    RTCErrorCodeStartCall               = 6,
    RTCErrorCodeEngineUnavailable       = 7 //底层引擎因为一些原因导致不可用
}RTCErrorCode;

typedef enum {
    MMLiveRenderModeGPUImage   = 0,//特效处理使用GPU
    MMLiveRenderModeMetalPetal = 1,//特效处理使用metal
}MMLiveRenderMode;

@interface MMLiveUserConfig : NSObject
@property (nonatomic, copy) NSString *appId;
@property (nonatomic, copy) NSString *userId;
@property (nonatomic, copy) NSString *roomId;
@property (nonatomic) NSInteger provider;
@property (nonatomic) NSInteger businessType;
@end

@interface MMLiveRoomParams : NSObject
@property (nonatomic) MMLivePushType linkType;//推流类型
@property (nonatomic, copy) NSString *confId;//供应商appid
@property (nonatomic) MMLiveRTCClientRole role;//角色
@property (nonatomic) BOOL isHost;//YES 主播 能够转推CDN；NO副播 不会转推
@property (nonatomic, copy) NSString *userId;//连线用户ID
@property (nonatomic, copy) NSString *channel;//连线房间ID
@property (nonatomic, copy) NSString *channelKey;//连线进房的密钥
@end

@interface MMLiveLinkMember : NSObject
@property (nonatomic, copy) NSString *userId;//连线布局某个用户的uid
@property (nonatomic, assign) CGRect rect;//连线布局某个用户的frame
@property (nonatomic) CGFloat volume;//该用户的音量状态
@property (nonatomic) int muteFlag;//该用户的静音状态
@property (nonatomic) int offLineFlag;//该用户的离线状态
@end

@interface MMLiveTranscoding : NSObject
@property (nonatomic, copy) NSString *userId;//主播的uid
@property (nonatomic, strong) UIColor* color;//背景颜色
@property (nonatomic) CGSize canvasSize;//转推画布大小
@property (nonatomic, assign) NSInteger videoBitrate;//转推视频码率
@property (nonatomic, strong) NSArray<MMLiveLinkMember*>* transcodingMembers;//转推cdn的布局
@property (nonatomic, strong) NSArray<MMLiveLinkMember*>* infoMembers;//观众端有效流的布局
@property (nonatomic, copy) NSString *extString;//透传sei
@end

@interface MMLiveMediaConfig : NSObject
@property (nonatomic) NSInteger videoFPS;//推流的帧率
@property (nonatomic) CGSize videoEncodeSize;//视频编码尺寸
@property (nonatomic) CGFloat videoBitRate;//视频编码码率
@property (nonatomic) CGFloat audioBitRate;//音频编码码率
@property (nonatomic) CGFloat audioSampleRate;//音频采样率
@property (nonatomic) NSInteger audioChannels;//音频声道
@property (nonatomic, copy) NSString *url;//推流地址
@end

#endif /* MMCommonParam_h */
