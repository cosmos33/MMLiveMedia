//
//  MLServerTimeSynchronizer.h
//  MomoChat
//
//  Created by YuAo on 11/10/16.
//  Copyright © 2016 wemomo.com. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface MLServerTimeSynchronizer : NSObject

+ (instancetype)synchronizer;

- (instancetype)init NS_UNAVAILABLE;

- (void)calibrateWithServerTimestamp:(NSTimeInterval)serverTimestamp;

- (NSTimeInterval)estimatedCurrentServerTimestamp;

@property (nonatomic,readonly,copy) NSDate *lastCalibratedTime;

@end
