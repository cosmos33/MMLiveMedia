//
//  MMLiveRTMPPush.h
//  Pods
//
//  Created by hrs on 2020/2/6.
//

#ifndef MMLiveRTMPPush_h
#define MMLiveRTMPPush_h
#import <Foundation/Foundation.h>
#import "MMCommonParam.h"
@class MMLiveRTMPPush;
#pragma mark - MMLiveRTCDelegate
@protocol MMLiveRTMPPushDelegate <NSObject>

/**
推流器开始推流
*/
- (void)MMLiveRTMPPushStarting:(MMLiveRTMPPush*)pusher type:(MMLivePushType)type error:(NSError*)error;

/**
推流器停止推流
*/
- (void)MMLiveRTMPPushStopped:(MMLiveRTMPPush*)pusher type:(MMLivePushType)type error:(NSError*)error;

/**
推流器推流失败
*/
- (void)MMLiveRTMPPushFailed:(MMLiveRTMPPush*)pusher type:(MMLivePushType)type error:(NSError*)error;

/**
推流卡顿开始
*/
- (void)MMLiveRTMPPushBufferStart:(MMLiveRTMPPush*)pusher type:(MMLivePushType)type error:(NSError*)error;

/**
推流卡顿结束
*/
- (void)MMLiveRTMPPushBufferStopped:(MMLiveRTMPPush*)pusher type:(MMLivePushType)type error:(NSError*)error;

/**
推流数据到达cdn（经验值），只用于平滑切换的优化方案
*/
- (void)MMLiveRTMPPushReplaced:(MMLiveRTMPPush*)pusher type:(MMLivePushType)type error:(NSError*)error;


@end
@interface MMLiveRTMPPush : NSObject
@property (nonatomic, weak) id<MMLiveRTMPPushDelegate> delegate;
@property (nonatomic, readonly, strong) MMLiveMediaConfig *pusherConfig;
@property (nonatomic, strong) id sourceHandle;

- (instancetype) initWithUserConfig:(MMLiveUserConfig *)userConfig;

/**
* 开始推流
*
* @param config 推流媒体参数
*/
- (int) startPush:(MMLiveMediaConfig*) config;

/**
* 停止推流
*
*/
- (void) stopPush;
@end
#endif /* MMLiveRTMPPush_h */
