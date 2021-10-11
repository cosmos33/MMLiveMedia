//
//  MLConferenceRole.h
//  MomoChat
//
//  Created by YuAo on 9/28/16.
//  Copyright © 2016 wemomo.com. All rights reserved.
//

typedef NS_ENUM(NSInteger, MLConferencePublisherRole) {
    MLConferencePublisherRoleNone = 0,
    MLConferencePublisherRoleMaster = 1,
    MLConferencePublisherRoleSlave = 2,
};

FOUNDATION_EXPORT NSString * MLConferencePublisherRoleGetDescription(MLConferencePublisherRole role);