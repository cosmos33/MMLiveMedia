//
//  MLVideoCodecType.h
//  MomoChat
//
//  Created by YuAo on 9/27/16.
//  Copyright © 2016 wemomo.com. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, MLVideoCodecType) {
    MLVideoCodecTypeVTB = 0,
    MLVideoCodecTypeX264 = 1,
    MLVideoCodecTypeVTB265 = 2,
};

FOUNDATION_EXPORT NSString * MLVideoCodecTypeGetDescription(MLVideoCodecType type);
