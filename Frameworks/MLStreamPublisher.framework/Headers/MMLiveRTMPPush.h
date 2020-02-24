//
//  MMLiveRTMPPush.h
//  Pods
//
//  Created by hrs on 2020/2/6.
//

#ifndef MMLiveRTMPPush_h
#define MMLiveRTMPPush_h
#import <Foundation/Foundation.h>
#import "MMCommonProtocols.h"
#import "MMCommonParam.h"
@interface MMLiveRTMPPush : NSObject
@property (nonatomic, weak) id<MMLivePusherDelegate> delegate;
@property (nonatomic, readonly, strong) MMLiveMediaConfig *pusherConfig;
@property (nonatomic, strong) id sourceHandle;

- (instancetype) initWithUserConfig:(MMLiveUserConfig *)userConfig;

/**
* 开始推流
*
* @param config 推流媒体参数
*/
- (void) startPush:(MMLiveMediaConfig*) config;

/**
* 停止推流
*
*/
- (void) stopPush;
@end
#endif /* MMLiveRTMPPush_h */
