//
//  MMLiveContext.h
//  Pods
//
//  Created by hrs on 2019/9/6.
//

#ifndef MMLiveContext_h
#define MMLiveContext_h

#import <Foundation/Foundation.h>
#import "MLDomainAnalysis.h"

@interface MMLiveContextConfig : NSObject

//@property (nonatomic, strong) NSArray *biz_config;
//@property (nonatomic, strong) NSDictionary *comm;
@property (nonatomic, strong) NSDictionary *pushConfig;
@property (nonatomic, strong) NSDictionary *pullConfig;

@property (nonatomic, assign) NSUInteger push_log_count;
@property (nonatomic, assign) NSUInteger push_log_interval;
@property (nonatomic, assign) NSUInteger pull_log_count;
@property (nonatomic, assign) NSUInteger pull_log_interval;

@end

@interface MMLiveUserContext : NSObject
@property (nonatomic, copy) NSString *userId;
@property (nonatomic, copy) NSString *appId;
@property (nonatomic, copy) NSString *secret;
@property (nonatomic, copy) NSString *appVer;
@property (nonatomic, copy) NSString *sdkVer;
@property (nonatomic, copy) NSString *userAgent;
@property (nonatomic, assign) BOOL useMediaLog;
@property (nonatomic, assign) NSInteger reTryCount;
@property (nonatomic, strong) MMLiveContextConfig *mediaConfig;
@end

@interface MMLiveContext : NSObject

//获取是否使用medialog。媒体使用
+ (BOOL)getUseMediaLog;


/**
设置配置信息
@param appId 业务id
@param secret 秘钥
@param appVer app版本号
@param userId 用户id
@param completeHandler 回调 (errorCode: 0 - 成功, 1 - 参数异常, 2 - 缓存信息重复, 3 - 配置信息拉取失败, 4 - appid和secret校验失败)
*/
+ (void)setConfigWithAppId:(NSString *)appId
                    secret:(NSString *)secret
                    appVer:(NSString *)appVer
                    userId:(NSString *)userId
           completeHandler:(void (^)(int errorCode))completeHandler;

/**
清理配置信息
*/
+ (void)cleanConfig;

/**
判断appid和userid是否已配置
*/
+ (BOOL)isConfigInitedWithAppId:(NSString *)appId
                         userId:(NSString *)userId;

/**
 获取配置
 */
+ (MMLiveUserContext *)getUserContextWithUserId:(NSString *)userId appId:(NSString *)appId;

/**
开关域名解析功能
*/
+ (void)enableDomainAnalysis:(BOOL)enable;

/**
 设置自定义域名解析工具（不设置或置为nil时使用SDK内部域名解析方案）
*/
+ (void)setDomainAnalysis:(id <MLDomainAnalysis>)domainAnalysis;

/**
 拉取直播间config
*/
//+ (void)requestRoomContextWithUserContext:(MMLiveUserContext *)userContext roomId:(NSString *)roomId completeHandler:(void (^)(MMLiveUserContext *roomContext))completeHandler;

+ (NSString*) getSDKVersion;
@end
#endif /* MMLiveContext_h */
