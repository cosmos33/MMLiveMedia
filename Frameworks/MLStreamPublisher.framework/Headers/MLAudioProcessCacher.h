//
//  MLAudioProcessCacher.h
//  MomoChat
//
//  Created by wangqiangqiang on 2017/9/14.
//  Copyright © 2017年 wemomo.com. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface MLAudioProcessCacher : NSObject

- (instancetype)initWithFrameLength:(int)frameLength;
//返回数据长度是frameLength的倍数
- (NSData *)processAudioData:(NSData *)inputData;

@end
