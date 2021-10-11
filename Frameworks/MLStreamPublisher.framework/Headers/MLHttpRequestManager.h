//
//  MLHttpRequestManager.h
//  CURLTest
//
//  Created by Hao.Li on 2019/9/2.
//  Copyright © 2019 Hao.Li. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN



typedef NS_ENUM(NSUInteger, MLHttpRequestManagerPostMode) {
    MLHttpRequestManagerPostModeForm = 0,
    MLHttpRequestManagerPostModeJson,
};

typedef void (^SuccessHandle)(NSDictionary *result);
typedef void (^FailureHandle)(NSError *error);

@interface MLHttpRequestManager : NSObject
/**
 获取单例的manager实例

 @return manager实例
 */
+ (instancetype)shareManager;

/**
 get请求

 @param requestURL 请求地址
 @param parameters 请求参数
 @param userAgentString UA
 @param retryCount 请求重试次数
 @param success 请求成功回调
 @param failure 请求失败回调
 */
- (void)GET:(NSString *)requestURL
 parameters:(NSDictionary *)parameters
  userAgent:(NSString *)userAgentString
 retryCount:(int)retryCount
    success:(SuccessHandle)success
    failure:(FailureHandle)failure;

/**
 post请求
 
 @param requestURL 请求地址
 @param parameters 请求参数
 @param userAgentString UA
 @param retryCount 请求重试次数
 @param success 请求成功回调
 @param failure 请求失败回调
 */
- (void)POST:(NSString *)requestURL
        mode:(MLHttpRequestManagerPostMode)mode
  parameters:(NSDictionary *)parameters
   userAgent:(NSString *)userAgentString
  retryCount:(int)retryCount
     success:(SuccessHandle)success
     failure:(FailureHandle)failure;

@end

NS_ASSUME_NONNULL_END
