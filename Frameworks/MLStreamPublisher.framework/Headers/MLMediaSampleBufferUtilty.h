//
//  MLMediaSampleBufferUtilty.h
//  MomoChat
//
//  Created by wangqiangqiang on 2017/3/31.
//  Copyright © 2017年 wemomo.com. All rights reserved.
//

#import <AVFoundation/AVFoundation.h>

@interface MLMediaSampleBufferUtilty : NSObject

- (CMSampleBufferRef)createSampleBufferWithImageBuffer:(CVImageBufferRef)imageBuffer
                                             frameTime:(CMTime)time CF_RETURNS_NOT_RETAINED;

- (CMSampleBufferRef)createAudioSampleBufferWithData:(NSData *)data
                                        channelCount:(int)channels
                                          sampleRate:(int)sampleRate
                                           audioTime:(CMTime)time CF_RETURNS_NOT_RETAINED;

@end
