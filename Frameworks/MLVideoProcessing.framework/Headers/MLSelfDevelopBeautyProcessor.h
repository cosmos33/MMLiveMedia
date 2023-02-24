//
//  MLSelfDevelopBeautyProcessor.h
//  MLVideoProcessing
//
//  Created by wxs on 2021/8/18.
//

#import <Foundation/Foundation.h>
#import <LightningRender/XEngineRender.h>

#import <MLMediaFoundation/MLAudioPrism.h>

NS_ASSUME_NONNULL_BEGIN

@interface MLSelfDevelopBeautyProcessor : NSObject

@property (nonatomic, assign) CGFloat preScale;
@property (nonatomic, strong, nullable) MLAudioPrism *audioPrism;
@property (nonatomic, assign) int orientation;
@property (nonatomic, assign) BOOL useScaledLandmarks;

+ (instancetype)sharedInstance;



// 处理PixelBuffer
// @params inputPixelBuffer
// @return CVPixelBufferRef
- (CVPixelBufferRef)processPixelBuffer:(CVPixelBufferRef)inputPixelBuffer;

- (void)updateCVInfo:(XEngineCVInfo *)cvInfo;


@end

NS_ASSUME_NONNULL_END
