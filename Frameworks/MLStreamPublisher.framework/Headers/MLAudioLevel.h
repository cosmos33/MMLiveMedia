//
//  MLAudioLevel.h
//  MomoChat
//
//  Created by wangqiangqiang on 2017/7/14.
//  Copyright © 2017年 wemomo.com. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface MLAudioLevel : NSObject

@property (nonatomic, assign, readonly) int currentLevel;  //[0, 9]

- (void)computeLevel:(NSData *)data;

@end
