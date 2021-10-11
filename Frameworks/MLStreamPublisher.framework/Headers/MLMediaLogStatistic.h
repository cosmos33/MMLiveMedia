//
//  MLMediaLogs.h
//  MomoChat
//
//  Created by wangqiangqiang on 2017/9/21.
//  Copyright © 2017年 wemomo.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MLMediaAPI.h"
#import "MMLiveContext.h"

@interface MLMediaLogStatistic : NSObject

@property (atomic, strong, readonly) id<MLMediaAPI> mediaAPI;
@property (atomic, strong, readonly) id<MLMediaAPI> logAdaptor;
@property (atomic, strong) MMLiveUserContext *userContext;

+ (void)registerMediaAPIClass:(Class<MLMediaAPI>)apiClass;
+ (void)registerLogAdaptorClass:(Class<MLMediaAPI>)logAdaptor;

+ (instancetype)shareInstance;

//兼容接口
- (void)uploadMediaLogWithEvent:(NSString *)event msg:(NSString *)msg liveAPIDomain:(NSString *)domain;

// 发送日志
- (void)uploadMediaLogWithEvent:(NSString *)event msg:(NSString *)msg liveAPIDomain:(NSString *)domain userContext:(MMLiveUserContext *)userContext;
- (void)uploadMediaLogWithEvent:(NSString *)event msg:(NSString *)msg liveAPIDomain:(NSString *)domain userContext:(MMLiveUserContext *)userContext pack:(BOOL)pack;//新增pack字段，为yes时，medialog打包，达到5条一起上传

//立即发送pack中缓存的所有log
- (void)uploadAllLogInPackagePromptlyWithLiveAPIDomain:(NSString *)domain userContext:(MMLiveUserContext *)userContext;
@end
