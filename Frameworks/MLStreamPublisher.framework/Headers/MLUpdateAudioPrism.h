//
//  MLUpdateAudioPrism.h
//  MomoChat
//
//  Created by wangqiangqiang on 2017/3/15.
//  Copyright © 2017年 wemomo.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MLRawAudioFrame.h"

@interface MLUpdateAudioPrism : NSObject

+ (void)onAudioRecordFrame:(MLRawAudioFrame *)audioFrame;
+ (void)onAudioRecordFrameAgoraHighQuality:(MLRawAudioFrame *)audioFrame;
+ (void)onAudioPlaybackFrame:(MLRawAudioFrame *)audioFrame;

@end
