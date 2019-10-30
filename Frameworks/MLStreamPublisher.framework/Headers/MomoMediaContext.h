//
//  MomoMediaContext.h
//  Pods
//
//  Created by hrs on 2019/9/6.
//

#ifndef MomoMediaContext_h
#define MomoMediaContext_h

#import <Foundation/Foundation.h>

@interface MomoMediaContext : NSObject

#pragma mark - getter
/**
 获取当前sdk版本号

 @return 当前sdk版本号
 */
+ (NSString *_Nonnull)sdkVersion;

/**
 获取当前设置的user id

 @return user id
 */
+ (NSString *_Nullable)userID;

/**
 获取当前设置的app id

 @return app id
 */
+ (NSString *_Nullable)appid;

/**
 获取当前设置的app秘钥

 @return app秘钥
 */
+ (NSString *_Nullable)secret;

/**
 获取当前设置的app私有版本号（注意：是私有版本号，非appsStore显示的公开版本）

 @return app私有版本号
 */
+ (NSString *_Nullable)appVerNum;

/// 获取当前设置的room id
+ (NSString *_Nullable)roomID;

/// 获取当前设置的主播cdn供应商
+ (int)provider;

/// 获取当前设置的主播业务类型
+ (int)businessType;

/// 获取当前设置的观众room id
+ (NSString *_Nullable)guestRoomID;

/// 获取当前设置的观众cdn供应商
+ (int)guestProvider;

/// 获取当前设置的观众业务类型
+ (int)guestBusinessType;

#pragma mark - public method
/**
 初始化sdk

 @param appId app唯一标识
 @param secret app对应的sdk秘钥
 @param appVerNum app私有版本号（注意：是私有版本号，公开版本号无需设置，sdk内自动读取工程配置）
 @param userId 用户id
 */
+ (void)initSDKWithAppId:(NSString *_Nonnull)appId
                  secret:(NSString *_Nonnull)secret
               appVerNum:(NSString *_Nonnull)appVerNum
                  userId:(NSString *_Nonnull)userId
             resultBlock:(void(^ _Nullable)(BOOL success))resultBlock;

/// 设置主播日志信息
/// @param roomId 房间号
/// @param provider cdn供应商
/// @param businessType 业务类型
+ (void)updateConfigWithRoomId:(NSString *_Nullable)roomId provider:(int)provider businessType:(int)businessType;

/// 设置观众日志信息
/// @param roomId 房间号
/// @param provider cdn供应商
/// @param businessType 业务类型
+ (void)updateGuestConfigWithRoomId:(NSString *_Nullable)roomId provider:(int)provider businessType:(int)businessType;

/// 清理config
+ (void)uninitConfig;

@end
#endif /* MomoMediaContext_h */
