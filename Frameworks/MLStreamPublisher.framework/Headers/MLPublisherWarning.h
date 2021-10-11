//
//  MLPublisherWarning.h
//  MomoChat
//
//  Created by MOMO on 2017/12/4.
//  Copyright © 2017年 wemomo.com. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef enum : NSUInteger {
    MLPublisherPushLevel352_1 = 0,
    MLPublisherPushLevel352_2,
    MLPublisherPushLevel528,
    MLPublisherPushLevel720,
    MLPublisherPushLevelOther = 100
} MLPublisherPushLevel;

@interface MLPublisherWarning : NSObject

- (instancetype)initWithCacheNormal:(int)cacheNormal
                   withCacheWarning:(int)cacheWarning
                   withCacheGrowMax:(int)cacheGrowMax
                  withCheckInterval:(int)checkInterval;

- (void)updateWithSentBytes:(int64_t)sentBytes
            withEncodeCache:(int32_t)encodeCache
                withSentDTS:(uint64_t)sentDTS
          withTargetBitrate:(NSInteger)targetBitrate;

- (void)resetWarningStatus;

- (BOOL)checkWarningStatus;

- (BOOL)checkDropStatus:(BOOL)isKeyFrame
            withDropDTS:(uint64_t)dropDTS
            encoderBFrame:(BOOL)exists;

// > 0, network good - could choose to increase bitrate
// < 0, network bad  - could choose to decrease bitrate
// = 0, nothing to do
- (int)checkResetStatus:(int)pushLevelChangeCount
            withScaling:(int)scaling;

// return current real sent bitrate(bps)
- (int)getCurrentBitrate;

- (NSInteger)getCurrentPushLevelWithEncodeSize:(CGSize)encodeSize
                                   withBitrate:(NSInteger)bitrate;

- (NSInteger)getTargetPushLevelWithCurrentBitrate:(int)currentBitrate;

@end
