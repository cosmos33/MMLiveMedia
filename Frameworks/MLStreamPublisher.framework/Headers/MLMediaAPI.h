//
//  MLMediaAPI.h
//  MomoChat
//
//  change by wangqiangqiang
//  Copyright © 2016 wemomo.com. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol MLMediaAPI <NSObject>

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
