//
//  WUNSTimerTargetLifecycleTracker.h
//  NSTimer+WeakTarget
//
//  Created by YuAo on 3/12/13.
//  Copyright (c) 2013 YuAo. All rights reserved.
//

#import <Foundation/Foundation.h>

@class MLWUNSTimerProxyTarget;

@interface MLWUNSTimerTargetLifecycleTracker : NSObject

- (id)initWithTimerProxyTarget:(MLWUNSTimerProxyTarget *)proxyTarget;

@end
