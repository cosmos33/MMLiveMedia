//
//  MLPublisherDefine.h
//  MomoChat
//
//  Created by wangqiangqiang on 2017/11/14.
//  Copyright © 2017年 wemomo.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "MLPublisherError.h"
#import "MLMediaCommonDefine.h"

//三挡不同的清晰度
static CGSize const MLCameraPreferredSizeLow = {352.0, 640.0};
static CGSize const MLCameraPreferredSizeNormal = {528.0, 960.0};
static CGSize const MLCameraPreferredSizeHigh = {704.0, 1280.0};

typedef NS_ENUM(NSInteger, MLPublisherStatus) {
    MLPublisherStatusStopped = 0,
    MLPublisherStatusStarting,
    MLPublisherStatusStarted,
    MLPublisherStatusPause,
    MLPublisherStatusStopping,
};

typedef NS_ENUM(NSInteger, MLUserOfflineReason) {
    MLUserOffline_Quit = 0,
    MLUserOffline_Dropped = 1,
    MLUserOffline_BecomeAudience = 2,
};

typedef NS_ENUM(NSInteger, MLUserNetworkQuality) {
    MLUserNetwork_Quality_Unknown = 0,
    MLUserNetwork_Quality_Excellent = 1,
    MLUserNetwork_Quality_Good = 2,
    MLUserNetwork_Quality_Poor = 3,
    MLUserNetwork_Quality_Bad = 4,
    MLUserNetwork_Quality_VBad = 5,
    MLUserNetwork_Quality_Down = 6,
};

typedef NS_ENUM(NSUInteger, MLPublisherType) {
    MLPublisherTypeStream  = 0,
    MLPublisherTypeAgora   = 1,
    MLPublisherTypeWeila   = 2,
    MLPublisherTypeTencent = 3,
    MLPublisherTypeMrtc    = 4,
    MLPublisherTypeUnknown = NSUIntegerMax
};

typedef NS_ENUM(NSUInteger, MLAgoraErrorCode)
{
    MLAgoraErrorCodeNone                    = 0,
    MLAgoraErrorCodeInvalidAppId            = 1,
    MLAgoraErrorCodeInvalidChannelName      = 2,
    MLAgoraErrorCodeInvalidChannelKey       = 3,
    MLAgoraErrorCodeJoinChannelRejected     = 4,
    MLAgoraErrorCodeChannelKeyExpired       = 5,
    MLAgoraErrorCodeStartCall               = 6,
    MLAgoraErrorCodeEngineUnavailable       = 7 //底层引擎因为一些原因导致不可用
};

typedef enum{
    MLClientRoleBroadcaster = 1,
    MLClientRoleRoleAudience = 2,
}MLPubliserClientRole;

FOUNDATION_EXPORT NSInteger const MLPublisherMaximumVideoCaptureFPS;

FOUNDATION_EXPORT void MLPublisherDispatchSynchronouslyOnMainQueue(void (^action)(void));
FOUNDATION_EXPORT void MLPublisherDispatchAsynchronouslyOnMainQueue(void (^action)(void));

FOUNDATION_EXPORT NSString *MLPublisherStatusGetDescription(MLPublisherStatus status);
FOUNDATION_EXPORT NSString *GetPublisherErrorCodeDesc(MLPublisherError errorCode);

FOUNDATION_EXPORT NSString * const MLPublisherTypeNonConference;
FOUNDATION_EXPORT NSString * const MLPublisherTypeConferenceMaster;
FOUNDATION_EXPORT NSString * const MLPublisherTypeConferenceSlave;
FOUNDATION_EXPORT NSString * const MLPublisherTypeConferenceMixMaster;
FOUNDATION_EXPORT NSString * const MLPublisherTypeConferenceAudience;
FOUNDATION_EXPORT NSString * const MLPublisherTypeConferencePlayer;
FOUNDATION_EXPORT NSString * const MLPublisherTypeAgoraMaster;
FOUNDATION_EXPORT NSString * const MLPublisherTypeAgoraSlave;
FOUNDATION_EXPORT NSString * const MLPublisherTypeAgoraMixMaster;
FOUNDATION_EXPORT NSString * const MLPublisherTypeAgoraAudience;
FOUNDATION_EXPORT NSString * const MLPublisherTypeAgoraPlayer;
FOUNDATION_EXPORT NSString * const MLPublisherPostConferenceAudioPacket;
FOUNDATION_EXPORT NSString * const MLPublisherTypeTencentMaster;
FOUNDATION_EXPORT NSString * const MLPublisherTypeTencentSlave;
FOUNDATION_EXPORT NSString * const MLPublisherTypeTencentMixMaster;
FOUNDATION_EXPORT NSString * const MLPublisherTypeTencentAudience;
FOUNDATION_EXPORT NSString * const MLPublisherTypeTencentPlayer;
FOUNDATION_EXPORT NSString * const MLPublisherTypeTMrtcMaster;
FOUNDATION_EXPORT NSString * const MLPublisherTypeMrtcSlave;
FOUNDATION_EXPORT NSString * const MLPublisherTypeMrtcMixMaster;
FOUNDATION_EXPORT NSString * const MLPublisherTypeMrtcAudience;
FOUNDATION_EXPORT NSString * const MLPublisherTypeMrtcPlayer;

