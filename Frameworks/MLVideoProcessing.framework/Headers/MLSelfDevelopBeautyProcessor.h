//
//  MLSelfDevelopBeautyProcessor.h
//  MLVideoProcessing
//
//  Created by wxs on 2021/8/18.
//

#import <Foundation/Foundation.h>
#import <LightningRender/XEngineRender.h>
#import <MLContractCV/MLContractBeautySourceManager.h>
#import <MLMediaFoundation/MLAudioPrism.h>

NS_ASSUME_NONNULL_BEGIN

@interface MLSelfDevelopBeautyProcessor : NSObject

@property (nonatomic, assign) CGFloat preScale;
@property (nonatomic, strong, nullable) MLAudioPrism *audioPrism;

+ (instancetype)sharedInstance;

- (void)addBeautyItems:(NSArray <MLContractBeautySourceItem *> *)items;
- (void)removeBeautyItems:(NSArray <MLContractBeautySourceItem *> *)items;
- (void)updateBeautyItem:(MLContractBeautySourceItem *)item key:(NSString*)key intensity:(float)intensity;

// 处理PixelBuffer
// @params inputPixelBuffer
// @return CVPixelBufferRef
- (CVPixelBufferRef)processPixelBuffer:(CVPixelBufferRef)inputPixelBuffer;

- (void)updateCVInfo:(XEngineCVInfo *)cvInfo;

@end

NS_ASSUME_NONNULL_END
