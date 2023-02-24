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
#if __has_include(<NSTimerWeakTarget/NSTimer+WeakTarget.h>)
#import <NSTimerWeakTarget/NSTimer+WeakTarget.h>
#else
#import <NSTimer+WeakTarget/NSTimer+WeakTarget.h>
#endif
#import <MLMediaFoundation/MLMediaFoundation.h>
#import <MLFilterKitMetalPetal/MLFilterKitMetalPetal.h>
#import <CXBeautyKit/CXBeautyKit.h>
@class MLContractBeautySourceItem;

@interface MLMetalPetalVideoProcessor : NSObject<MLVideoProcessor>
@property (nonatomic, strong, readonly) MLAudioPrism <FDKAudioPrism>*audioPrism;
@property (nonatomic, copy) CXBeautyConfiguration *deepBeautyConfiguration;
@property (nonatomic, copy) NSArray <MLMetalPetalNativeViewItem *>*viewItems;
@property (nonatomic, assign) int warpType;
@property (nonatomic, assign) int preferredFrameRate;
@property (nonatomic, assign) BOOL shouldSkipBeautyProcess;
@property (nonatomic, assign) int orientation;
@property (nonatomic, assign) BOOL lr_cartoonMultiEnable;
@property (nonatomic, assign) BOOL lr_stylizeMultiEnable;
@property (nonatomic, assign) BOOL useEngineBeauty;

- (void)setWebGLFilterConfig:(NSDictionary *)config;
- (void)processingCVPixelBuffer:(CVPixelBufferRef)pixelBuffer atTime:(CMTime)frameTime options:(MLVideoProcessorOptions *)options completion:(void (^)(CVPixelBufferRef))completion;

- (void)addBeautyItems:(NSArray <MLContractBeautySourceItem *> *)items;
- (void)removeBeautyItems:(NSArray <MLContractBeautySourceItem *> *)items;
- (void)updateBeautyItem:(MLContractBeautySourceItem *)item key:(NSString*)key intensity:(float)intensity;
@end
