//
//  MLRawAudioFrame.h
//  MomoChat
//
//  Created by wangqiangqiang on 2016/12/7.
//  Copyright © 2016年 wemomo.com. All rights reserved.
//

#import <Foundation/Foundation.h>

#define k_IJKM_KEY_SAMPLE_RATE    @"sample_rate"
#define k_IJKM_KEY_CHANNELS       @"channels"

/**
 获取声网SDK回调的PCM数据
 */
@interface MLRawAudioFrame : NSObject

@property (nonatomic, strong) NSData *data;
@property (nonatomic) float pts;
@property (nonatomic) int channels;
@property (nonatomic) int sampleRate;

- (instancetype)initWithBytes:(void *)bytes pts:(float)pts length:(int)length channels:(int)channels sampleRate:(int)sampleRate;

@end
