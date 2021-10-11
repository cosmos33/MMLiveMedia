//
//  PCMBuffer.h
//  MomoChat
//
//  Created by MOMO on 1/23/17.
//  Copyright © 2017 wemomo.com. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface MLPCMBuffer : NSObject
@property (nonatomic)  uint32_t offset;
@property (nonatomic, strong) NSData * _Nullable data;
- (instancetype _Nullable )initWithData:(NSData*_Nullable)data;
- (instancetype _Nullable )initWithBytes:(nullable const void *)bytes length:(NSUInteger)length;
@end

FOUNDATION_EXPORT int mixAudioSample(NSData * _Nullable masterSample, NSMutableArray * _Nullable slaverSamples, float masterVolume, float slaveVolume);

FOUNDATION_EXPORT void mixAudioBuffer(uint8_t * masterBuffer, int masterLength, float masterVolume,
                                      uint8_t * slaverBuffer, int slaverLength, float slaveVolume);
