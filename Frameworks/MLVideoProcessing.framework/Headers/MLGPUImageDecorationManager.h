//
//  MLPublisherDecorationManager.h
//  MomoLive
//
//  Created by YuAo on 7/22/16.
//  Copyright © 2016 wemomo.com. All rights reserved.
//

#import <MomoCV/MomoCV.h>
#import <FaceDecorationKit/FaceDecorationKit.h>
#import <FaceDecorationKitGPUImage/FaceDecorationKitGPUImage.h>
#import <GPUImage/GPUImage.h>
#import <MLMediaFoundation/MLMediaFoundation.h>

@class MLObjectTriggeredDecoration;

@interface MLAudioPrism (FDK) <FDKAudioPrism>

@end
OBJC_EXTERN NSString *const kMLDecorationManagerDecorationFilterAddedNotification;
@interface MLGPUImageDecorationManager : NSObject

@property (nonatomic,strong) MLAudioPrism *audioPrism;

- (instancetype)initWithFilterPipeline:(GPUImageFilterPipeline *)filterPipeline;

- (void)addDecoration:(FDKDecoration *)decoration duration:(NSTimeInterval)duration positionType:(NSInteger)positionType;

- (void)addDecoration:(FDKDecoration *)decoration withIdentifier:(NSString *)identifier;

- (void)removeDecorationWithIdentifier:(NSString *)identifier;

- (FDKDecoration *)decorationWithIdentifier:(NSString *)identifier;

- (NSArray<NSString *> *)decorationIdentifiers;

- (void)setFaceFeatures:(NSArray<MMFaceFeature *> *)faceFeatures
         objectFeatures:(NSArray<MMObjectFeature *> *)objectFeatures
      facialExpressions:(NSArray <MMFacialExpression *> *)facialExpressions
imageSegmentationResult:(MMImageSegmentationResult *)imageSegmentationResult
         inputFrameSize:(CGSize)inputFrameSize;

@property (nonatomic,copy) NSArray<MLObjectTriggeredDecoration *> *objectTriggeredDecorations;

@end
