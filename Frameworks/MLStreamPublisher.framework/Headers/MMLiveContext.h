//
//  MMLiveContext.h
//  Pods
//
//  Created by hrs on 2019/9/6.
//

#ifndef MMLiveContext_h
#define MMLiveContext_h

#import <Foundation/Foundation.h>

@interface MMLiveContextConfig : NSObject
@property (nonatomic, copy) NSDictionary *logConfig;
@property (nonatomic, copy) NSDictionary *pushConfig;
@property (nonatomic, copy) NSDictionary *pullConfig;

@property (nonatomic, strong, readonly) NSArray *pull_delay;
@property (nonatomic, strong, readonly) NSArray *pull_comm;
@property (nonatomic, strong, readonly) NSArray *pull_log;
@property (nonatomic, strong, readonly) NSString *focus_enable;
@property (nonatomic, strong, readonly) NSArray *push_drop;
@property (nonatomic, strong, readonly) NSArray *push_log;
@property (nonatomic, strong, readonly) NSArray *comm;
@end

@interface MMLiveUserContext : NSObject
@property (nonatomic, copy) NSString *userId;
@property (nonatomic, copy) NSString *appId;
@property (nonatomic, copy) NSString *secret;
@property (nonatomic, copy) NSString *appVer;
@property (nonatomic, copy) NSString *sdkVer;
@property (nonatomic, copy) NSString *userAgent;
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
 获取配置
 */
+ (MMLiveUserContext *)getUserContextWithUserId:(NSString *)userId appId:(NSString *)appId;
@end
#endif /* MMLiveContext_h */
