//
//  MLLightingRenderBeautyFilter.h
//  MLVideoProcessing
//
//  Created by Naichuan on 2021/4/13.
//

#import <Foundation/Foundation.h>
#import <MetalPetal/MetalPetal.h>
#import <MLMediaFoundation/MLAudioPrism.h>
#import <MLContractCV/MLContractBeautySourceManager.h>
NS_ASSUME_NONNULL_BEGIN

@class MMFaceAdjustments;
@interface MLLightingRenderBeautyFilter : NSObject<MTIUnaryFilter>
@property (nonatomic, strong) MTIImage *inputImage;
@property (nonatomic, assign) BOOL disable;
@property (nonatomic, strong, nullable) MLAudioPrism *audioPrism;
@property (nonatomic, assign) int orientation;
@property (nonatomic, assign) BOOL useScaledLandmarks;
- (void)updateCVInfo:(id)cvInfo;

@property (nonatomic, assign) BOOL cartoonFaceEnable;
@property (nonatomic, assign) BOOL stylizeFaceEnable;

@property (nonatomic, assign) BOOL cartoonFaceMultipleFaceProcessEnable;
@property (nonatomic, assign) BOOL stylizeFaceMultipleFaceProcessEnable;

@property (nonatomic, strong, readonly) MMFaceAdjustments *adjustments;

- (void)addBeautyItems:(NSArray <MLContractBeautySourceItem *> *)items;
- (void)removeBeautyItems:(NSArray <MLContractBeautySourceItem *> *)items;
- (void)updateBeautyItem:(MLContractBeautySourceItem *)item key:(NSString*)key intensity:(float)intensity;
@end

NS_ASSUME_NONNULL_END
