//
//  MLLightingRenderBeautyFilter.h
//  MLVideoProcessing
//
//  Created by Naichuan on 2021/4/13.
//

#import <Foundation/Foundation.h>
#import <MetalPetal/MetalPetal.h>
#import <MLMediaFoundation/MLAudioPrism.h>
NS_ASSUME_NONNULL_BEGIN


@interface MLLightingRenderBeautyFilter : NSObject<MTIUnaryFilter>
@property (nonatomic, strong) MTIImage *inputImage;
@property (nonatomic, assign) BOOL disable;
@property (nonatomic, strong, nullable) MLAudioPrism *audioPrism;
@property (nonatomic, assign) int orientation;
@property (nonatomic, assign) BOOL useScaledLandmarks;
- (void)updateCVInfo:(id)cvInfo;


@property (nonatomic, assign) BOOL cartoonFaceMultipleFaceProcessEnable;
@property (nonatomic, assign) BOOL stylizeFaceMultipleFaceProcessEnable;
@end

NS_ASSUME_NONNULL_END
