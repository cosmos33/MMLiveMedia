//
//  MLMetalPetalVideoProcessor.h
//  FaceDecorationKit
//
//  Created by 杨乃川 on 2018/1/3.
//

#import <Foundation/Foundation.h>
#import "MLVideoProcessor.h"
#import <MetalPetal/MetalPetal.h>
#import <FaceDecorationKitMetalPetal/FaceDecorationKitMetalPetal.h>
#import <FaceDecorationKitMomoCV/FaceDecorationKitMomoCV.h>
#import <MLWeakTargetTimer/MLWeakTargetTimer.h>
#import <MLMediaFoundation/MLMediaFoundation.h>
#import <MLFilterKitMetalPetal/MLFilterKitMetalPetal.h>
#import <CXBeautyKit/CXBeautyKit.h>

@interface MLMetalPetalVideoProcessor : NSObject<MLVideoProcessor>
@property (nonatomic, strong, readonly) MLAudioPrism <FDKAudioPrism>*audioPrism;
@property (nonatomic, copy) CXBeautyConfiguration *deepBeautyConfiguration;
@property (nonatomic, copy) NSArray <MLMetalPetalNativeViewItem *>*viewItems;
@property (nonatomic, assign) int warpType;

- (void)setWebGLFilterConfig:(NSDictionary *)config;
- (void)processingCVPixelBuffer:(CVPixelBufferRef)pixelBuffer atTime:(CMTime)frameTime options:(MLVideoProcessorOptions *)options completion:(void (^)(CVPixelBufferRef))completion;
@end
