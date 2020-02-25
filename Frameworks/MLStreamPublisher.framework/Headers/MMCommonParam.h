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

typedef NS_ENUM(NSInteger, MMLivePlayerStatus) {
    MMLivePlayerStatusPlaying = 0, //播放中
    MMLivePlayerStatusBuffering, //播放加载中
    MMLivePlayerStatusStopped, //播放停止
    MMLivePlayerStatusFinished, //播放结束
    MMLivePlayerStatusFailed, //播放错误
};

typedef enum{
    MMLiveEngineTypePlay = 1,
    MMLiveEngineTypePush = 2,
    MMLiveEngineTypeNone = 3,
}MMLiveEngineType;

typedef enum{
    MMLiveRTCClientRoleBroadcaster = 1,
    MMLiveRTCClientRoleAudience = 2,
}MMLiveRTCClientRole;

typedef enum{
    MMLivePushTypeConfNONE = 0,
    MMLivePushTypeConfAG = 1,
    MMLivePushTypeConfTX = 2,
    MMLivePushTypeConfWL = 3,
    MMLivePushTypeConfMM = 4,
}MMLivePushType;

typedef enum{
    MMLiveAEFilterYUYIN = 0,// 原声
    MMLiveAEFilterET    = 1,// 小怪兽
    MMLiveAEFilterPaPi  = 2,// papi酱
    MMLiveAEFilterTransformer = 3,// 变形金刚
    MMLiveAEFilterRobot = 4,//机器人
    MMLiveAEFilterMan   = 5,//女变男
    MMLiveAEFilterWoman = 6,//男变女
    MMLiveAEFilterBaby  = 7,//娃娃音
    MMLiveAEFilterMC    = 8,//mc
    MMLiveAEFilterELE   = 9,//ELE_EFFECT
    MMLiveAEFilterMinions = 10,//小黄人
    MMLiveAEFilterMute  = 11,//静音
    MMLiveAEFilterGiftRobot = 12,//礼物机器人
}MMLiveAEFilter;

typedef NS_ENUM(NSUInteger, RTCErrorCode)
{
    RTCErrorCodeNone                    = 0,
    RTCErrorCodeInvalidAppId            = 1,
    RTCErrorCodeInvalidChannelName      = 2,
    RTCErrorCodeInvalidChannelKey       = 3,
    RTCErrorCodeJoinChannelRejected     = 4,
    RTCErrorCodeChannelKeyExpired       = 5,
    RTCErrorCodeStartCall               = 6,
    RTCErrorCodeEngineUnavailable       = 7 //底层引擎因为一些原因导致不可用
};

@interface MMLiveUserConfig : NSObject
@property (nonatomic, copy) NSString *appId;
@property (nonatomic, copy) NSString *userId;
@property (nonatomic, copy) NSString *roomId;
@property (nonatomic) NSInteger provider;
@property (nonatomic) NSInteger businessType;
@end

@interface MMLiveRoomParams : NSObject
@property (nonatomic) MMLivePushType linkType;
@property (nonatomic, copy) NSString *confId;
@property (nonatomic) MMLiveRTCClientRole role;
@property (nonatomic) BOOL isHost;
@property (nonatomic, copy) NSString *channelKey;
@end

@interface MMLiveLinkMember : NSObject
@property (nonatomic, copy) NSString *userId;
@property (nonatomic, assign) CGRect rect;
@property (nonatomic) CGFloat volume;
@property (nonatomic) int muteFlag;
@property (nonatomic) int offLineFlag;
@end

@interface MMLiveSei : NSObject
@property (nonatomic, copy) NSString *userId;
@property (nonatomic, strong) UIColor* color;
@property (nonatomic) CGSize canvasSize;
@property (nonatomic, strong) NSArray<MMLiveLinkMember*>* transcodingMembers;
@property (nonatomic, strong) NSArray<MMLiveLinkMember*>* infoMembers;
@property (nonatomic, copy) NSString *extString;
@end

@interface MMLiveMediaConfig : NSObject
@property (nonatomic) NSInteger videoFPS;
@property (nonatomic) CGSize videoEncodeSize;
@property (nonatomic) CGFloat videoBitRate;
@property (nonatomic) CGFloat audioBitRate;
@property (nonatomic) CGFloat audioSampleRate;
@property (nonatomic) NSInteger audioChannels;
@property (nonatomic, copy) NSString *url;
@end

#endif /* MMCommonParam_h */
