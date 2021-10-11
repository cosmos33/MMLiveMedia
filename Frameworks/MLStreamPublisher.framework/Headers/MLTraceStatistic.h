//
//  MLTraceStatistic.h
//  MLStreamPublisher
//
//  Created by hrs on 2020/6/16.
//

#ifndef MLTraceStatistic_h
#define MLTraceStatistic_h
#import "MMLiveContext.h"
@interface MLTraceStatistic : NSObject

+ (instancetype)shareInstance;

// 发送日志
- (void)uploadTraceLogWithEvent:(NSString *)event msg:(NSString *)msg liveAPIDomain:(NSString *)domain userContext:(MMLiveUserContext *)userContext;
@end

#endif /* MLTraceStatistic_h */
