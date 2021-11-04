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
- (void)updateCVInfo:(id)cvInfo;
@end

NS_ASSUME_NONNULL_END
