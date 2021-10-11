//
//  MLGPUManager.h
//  MomoChat
//
//  Created by wangtao on 2019/8/16.
//  Copyright © 2019 wemomo.com. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface MLGPUManager : NSObject
@property (atomic, assign) NSUInteger gpu;

- (void)start;
- (void)stop;
@end

NS_ASSUME_NONNULL_END
