//
//  MLMediaAPI.h
//  MomoChat
//
//  change by wangqiangqiang
//  Copyright © 2016 wemomo.com. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol MLMediaAPI <NSObject>

/**
    推流日志上传接口
     aParam：请求参数
     publisherIdentify：推流场景，参见MLPublisherOptions.h中MLPublisherIdentify
     reportType：推流日志类型，参见MLPublisherStatistic.h中MLPublisherIdentifyReportType
     domain：如果参数不为空使用该域名
     aTarget：回调对象
     ok：请求成功回调
     err：请求错误回调
     fail：请求失败回调
 **/
- (void)postPublisherLogWithParam:(NSMutableDictionary *)aParam
                publisherIdentify:(NSInteger)publisherIdentify
              publisherReportType:(NSInteger)publisherReportType
                    liveAPIDomain:(NSString *)domain
                           target:(id)aTarget
                               ok:(SEL)okSelector
                              err:(SEL)errSelector
                             fail:(SEL)failSelector;

/**
    播放日志上传接口
     aParam：请求参数
     playerIdentify：播放场景，参见MLPlayerStatistic.h中MLPlayerIdentify
     reportType：播放日志类型，参见MLPlayerIdentifyReportType中playerReportType
     domain：如果参数不为空使用该域名
     aTarget：回调对象
     ok：请求成功回调
     err：请求错误回调
     fail：请求失败回调
 **/
- (void)postPlayerLogWithParam:(NSMutableDictionary *)aParam
                playerIdentify:(NSInteger)playerIdentify
              playerReportType:(NSInteger)playerReportType
                 liveAPIDomain:(NSString *)domain
                        target:(id)aTarget
                            ok:(SEL)okSelector
                           err:(SEL)errSelector
                          fail:(SEL)failSelector;


/**
    p2p日志上传接口
     aParam：请求参数
     domain：如果参数不为空使用该域名
     aTarget：回调对象
     ok：请求成功回调
     err：请求错误回调
     fail：请求失败回调
 **/
- (void)postP2PLogWithParam:(NSMutableDictionary *)aParam
              liveAPIDomain:(NSString *)domain
                     target:(id)aTarget
                         ok:(SEL)okSelector
                        err:(SEL)errSelector
                       fail:(SEL)failSelector;


/**
    ts校准接口
     aParam：请求参数
     domain：如果参数不为空使用该域名
     aTarget：回调对象
     ok：请求成功回调
     err：请求错误回调
     fail：请求失败回调
 **/
- (void)postTimeCalibrationWithParam:(NSMutableDictionary *)aParam
                             postUrl:(NSString *)url
                              target:(id)aTarget
                                  ok:(SEL)okSelector
                                 err:(SEL)errSelector
                                fail:(SEL)failSelector;

- (void)postRequestWithParam:(NSMutableDictionary *)aParam
                         url:(NSString *)url
                      target:(id)aTarget
                          ok:(void (^)(NSDictionary *result))okBlock
                        fail:(void (^)(NSDictionary *result))failBlock
                         err:(void (^)(NSError *error))errBlock;


- (void)postRequestWithParam:(NSString *)requestUrl
                  dynamicKey:(NSString *)dynamicKey
                   channelID:(NSString *)channelID
                       appID:(NSString*)appID
                      target:(id)aTarget
                          ok:(void (^)(NSDictionary *result))okBlock
                        fail:(void (^)(NSDictionary *result))failBlock
                         err:(void (^)(NSError *error))errBlock;

- (void)postLiveLogWithType:(NSString *)type
                       body:(NSString *)body
              forRoomWithID:(NSString *)roomID
                   provider:(NSInteger)provider
               businessType:(NSInteger)businessType
                sessionTime:(uint64_t)sessionTime
              publisherType:(NSString *)publisherType
          publisherIdentify:(NSInteger)publisherIdentify
                 reportType:(NSInteger)reportType
                serviceType:(NSString *)serviceType
              liveAPIDomain:(NSString *)domain
                     target:(id)aTarget
                         ok:(SEL)okSelector
                        err:(SEL)errSelector
                       fail:(SEL)failSelector;


- (void)postLiveLogWithType:(NSString *)type
                       body:(NSString *)body
              forRoomWithID:(NSString *)roomID
                   provider:(NSInteger)provider
               businessType:(NSInteger)businessType
                sessionTime:(uint64_t)sessionTime
             playerIdentify:(NSInteger)playerIdentify
                 reportType:(NSInteger)reportType
              liveAPIDomain:(NSString *)domain;

- (void)liveLogWihtType:(NSString*)type
                 roomId:(NSString*)roomid
               provider:(int)provider
           businessType:(NSInteger)businessType
            sessionTime:(uint64_t)time
                   body:(NSString*) body
                    url:(NSString*)url
          liveAPIDomain:(NSString *)domain;
@end
