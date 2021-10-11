//
//  MLMediaAPIAdaptor.h
//  MomoChat
//
//  Created by YuAo on 8/18/16.
//  Copyright © 2016 wemomo.com. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MLMediaAPI.h"
#import "MMLiveContext.h"

@interface MLLogCacheModel : NSObject

@end

@interface MLMediaLogAdaptor : NSObject <MLMediaAPI>
@property (nonatomic, strong) MMLiveUserContext *userContext;
+ (NSMutableArray<MLLogCacheModel *> *)cacheArray;
+ (Class<MLMediaAPI>) getMediaLogAdaptor;
@end
