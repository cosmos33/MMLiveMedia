//
//  MLPlayerStatistic.h
//  MomoChat
//
//  Created by YuAo on 10/9/16.
//  Copyright © 2016 wemomo.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MLMediaAPI.h"
#import "MLPlayerStatistic.h"
#import "MMLiveContext.h"

static NSString * const MLPlayerP2pStatisticTypePullStart = @"v2.livePullStart";
static NSString * const MLPlayerP2pStatisticTypePullStop = @"v2.livePullStop";
static NSString * const MLPlayerP2pStatisticTypePullWatch = @"v2.livePullWatch";
static NSString * const MLPlayerP2pStatisticTypePeerPunch = @"v2.livePeerPunch";
static NSString * const MLPlayerP2pStatisticTypeShareStart = @"v2.liveShareStart";
static NSString * const MLPlayerP2pStatisticTypeShareStop = @"v2.liveShareStop";
static NSString * const MLPlayerP2pStatisticTypeSessionStart = @"v2.liveSessionStart";
static NSString * const MLPlayerP2pStatisticTypeSessionStop = @"v2.liveSessionStop";


@interface MLPlayerP2pStatistic : NSObject

@property (atomic,copy) NSString *roomID;
@property (atomic) int provider;
@property (atomic) int businessType;
@property (atomic) uint64_t sessionTime;
@property (nonatomic) MLPlayerIdentify playerIdentify;
@property (nonatomic, strong) MMLiveUserContext *userContext;

+ (uint64_t)currentTimestamp;

+ (void)registerMediaAPIClass:(Class<MLMediaAPI>)apiClass;
+ (void)registerLogAdaptorClass:(Class<MLMediaAPI>)apiClass;

//使用媒体中台初始化接口
- (instancetype)initWithAppId:(NSString *_Nonnull)appId
                       secret:(NSString *_Nonnull)secret
                    appVerNum:(NSString *_Nonnull)appVerNum
                       userId:(NSString *_Nonnull)userId;
// 通用日志发送接口
- (void) postLiveP2pLogWithType:(NSString*) type Source:(NSDictionary*) srcDict paramList:(NSArray<NSString*>*) orderList liveAPIDomain:(NSString *)domain;
- (void) postLiveP2pLogWithWatch:(NSString*)type value:(NSString*)value liveAPIDomain:(NSString *)domain;
- (void) postLiveP2pLogWithEventInfo:(NSString*)type value:(NSString*)value liveAPIDomain:(NSString *)domain;

//立即发送所有缓存的livepullstart和livepullstop日志
- (void)uploadAllLogInPackagePromptlyWithLiveAPIDomain:(NSString *)domain;
@end
