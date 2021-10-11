//
//  MLFPSManager.h
//  CADisplayLinkDemo
//
//  Created by wangtao on 2019/5/20.
//  Copyright © 2019 wangtao. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface MLFPSManager : NSObject
@property (atomic, assign) NSUInteger fps;
@property (atomic, assign) NSUInteger fps5;

- (void)start;
- (void)stop;
@end

NS_ASSUME_NONNULL_END
