//
//  MLLianmaiStats.h
//  MomoChat
//
//  Created by MOMO on 2017/10/16.
//  Copyright © 2017年 wemomo.com. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface MLLianmaiStats : NSObject

@property (nonatomic, assign) uint64_t userID;

@property (nonatomic) long long preRecvAudioBytes;
@property (nonatomic) long long preRecvVideoBytes;
@property (nonatomic) long long recvAudioBytes;//total audio size
@property (nonatomic) long long recvVideoBytes;//total video size
@property (nonatomic) long long lastExpandCount;
@property (nonatomic) long long lastExpandCartonCount;
@property (nonatomic) BOOL      findFirstKey;
@property (nonatomic) BOOL      fpsDone;
@property (nonatomic) BOOL      muteAudio;
@property (nonatomic) BOOL      muteVideo;
@property (nonatomic) int       fps;
@property (nonatomic) int       gopDuration;
@property (nonatomic) int       videoWidth;
@property (nonatomic) int       videoHeight;
@property (nonatomic) int       videoBitrate;
@property (nonatomic) int       videoDelay;
@property (nonatomic) int       videoLost;
@property (nonatomic) int       audioBitrate;
@property (nonatomic) int       audioDelay;
@property (nonatomic) int       audioLost;
@property (nonatomic) long long expandCount;
@property (nonatomic) long long expandCartonCount;


@property (nonatomic) long      audioTotalPlaylag;      //一次统计周期内卡顿次数
@property (nonatomic) long      videoTotalPlaylag;      //一次统计周期内卡顿次数
@property (nonatomic) uint64_t  lastTS;
@property (nonatomic) uint64_t  firstKeyTS;
@property (nonatomic) int       videoDelayEx;

@property (nonatomic) int       lianmaiDelay;
@property (nonatomic) long      audioLastTotalPlaylag;      //前一次统计周期内卡顿次数,为解决当前自研音频卡顿计算错误的问题，仅用在自研SDK
- (instancetype)initWithUserID:(uint64_t)userID;

@end
