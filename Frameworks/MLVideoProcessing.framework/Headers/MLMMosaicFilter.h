//
//  MLMMosaicFilter.h
//  MLVideoProcessing
//
//  Created by Naichuan on 2022/10/9.
//

#import <Foundation/Foundation.h>
#import <FaceDecorationKitMetalPetal/FaceDecorationKitMetalPetal.h>
#import <MetalPetal/MetalPetal.h>

NS_ASSUME_NONNULL_BEGIN

@interface MLMMosaicFilter : NSObject<MTIUnaryFilter>
@property (nonatomic, assign) int lagFrameCountOfEnableState;

@property (nonatomic, assign) BOOL disable;
@end

NS_ASSUME_NONNULL_END
