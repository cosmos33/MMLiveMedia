//
//  MLPlayerVideoDetail.h
//  MomoChat
//
//  Created by wangqiangqiang on 2018/3/8.
//  Copyright © 2018年 wemomo.com. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface MLPlayerVideoDetail : NSObject

@property (nonatomic, copy) NSString *urlID;
@property (nonatomic, assign) int provider;
@property (nonatomic, assign) int businessType;
@property (nonatomic, assign) int quality;
@property (nonatomic, assign) int expireSec;//超时时间
@property (nonatomic, copy) NSString *qualityTag;
@property (nonatomic, assign) int type;
@property (nonatomic, copy) NSString *url;
@property (nonatomic, strong) NSDate* expireTime;
@property (nonatomic, assign) BOOL isLive;
@property (nonatomic, assign) int logcol_intsec;
@property (nonatomic, assign) int logup_intsec;
@property (nonatomic, assign) int log_event_enable;
@property (nonatomic, assign) bool isMustUse;
@property (nonatomic, strong) NSDictionary *chaseDelayDictionary;
@property (nonatomic, assign) BOOL notManageAudioSession;
@property (nonatomic, assign) BOOL isFromChatRoom;
@property (nonatomic, copy) NSString *mediaConfig;
@property (nonatomic, assign) BOOL enableManagerView;

@end
