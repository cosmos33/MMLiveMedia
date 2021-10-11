//
//  MLAgoraDelegateProxy.h
//  MomoChat
//
//  Created by YuAo on 11/8/16.
//  Copyright © 2016 wemomo.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AgoraRtcEngineKit/AgoraRtcEngineKit.h>

@interface MLAgoraDelegateProxy : NSProxy

@property (nonatomic,readonly) BOOL isCallingTargetMethod;

@property (atomic,weak,readonly) id<AgoraRtcEngineDelegate> target;

- (instancetype)initWithTarget:(id<AgoraRtcEngineDelegate>)target;

- (instancetype)init NS_UNAVAILABLE;

- (void)removeTarget;

@end

@interface MLAgoraDelegateProxy (AgoraRtcEngineDelegate) <AgoraRtcEngineDelegate>

@end
