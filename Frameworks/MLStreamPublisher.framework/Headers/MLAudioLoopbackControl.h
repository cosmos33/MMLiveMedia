//
//  MLAudioLoopbackControl.h
//  MomoChat
//
//  Created by YuAo on 11/3/16.
//  Copyright © 2016 wemomo.com. All rights reserved.
//

#import <Foundation/Foundation.h>

FOUNDATION_EXPORT BOOL MLAudioLoopbackEnabled(void);
FOUNDATION_EXPORT void MLAudioLoopbackSetEnabled(BOOL enabled);

FOUNDATION_EXPORT NSString * const MLAudioLoopbackSettingChangedNotification;
