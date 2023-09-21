//
//  MLContractBeautyProcessor.h
//  MLContractCV
//
//  Created by 杨乃川 on 2021/1/12.
//

#import <Foundation/Foundation.h>
#import "MLContractBeautySourceManager.h"


NS_ASSUME_NONNULL_BEGIN
@class MMFaceFeature;
@interface MLContractBeautyProcessorOption : NSObject
@property (nonatomic, assign) int orientation;
@property (nonatomic, assign) float landmarkScale;
@end


@interface MLContractBeautyProcessor : NSObject

// 去除美妆漂浮、消耗性能，默认关闭
+ (void)enhanceByteDacneMakeUp:(BOOL)enhance;

// set before initialization
// 0,default GLES2.0; 1, GLES3.0
+ (void)renderingAPI:(int)apiVer;

// 设置证书path
+ (void)setLicenseURL:(NSURL *)url;

// 启动低人脸检测帧数间隔，默认关闭
+ (void)lowFaceDetectInterval:(BOOL)open;

- (instancetype)init NS_UNAVAILABLE;
- (nullable instancetype)initWithModelDirectory:(NSURL *)modelDir error:(NSError **)error;
- (nullable instancetype)initWithModelDirectory:(NSURL *)modelDir faceDetectFrameInterval:(int)interval error:(NSError **)error;

@end


@interface MLContractBeautyProcessor(Process)
- (CVPixelBufferRef)processPixelBuffer:(CVPixelBufferRef)inputPixelBuffer;
- (CVPixelBufferRef)processPixelBuffer:(CVPixelBufferRef)inputPixelBuffer option:(nullable MLContractBeautyProcessorOption *)option;
- (NSArray <MMFaceFeature *>*)processedFaceFeature;
- (void)skipBeautyProcess:(BOOL)skip; //default NO;

@end


@interface MLContractBeautyProcessor(Beauty)

- (void)addBeautyItems:(NSArray <MLContractBeautySourceItem *> *)items;
- (void)removeBeautyItems:(NSArray <MLContractBeautySourceItem *> *)items;
- (void)updateBeautyItem:(MLContractBeautySourceItem *)item key:(NSString*)key intensity:(float)intensity;


/*
 nodes [absolute paths]
 */
- (void)addComposeNodes:(NSArray <NSString *> *)nodes;
- (void)removeComposeNodes:(NSArray <NSString *> *)nodes;
- (void)updateNode:(NSString *)node key:(NSString *)key intensity:(float)intensity;

- (void)addLutFilterNode:(NSString *)nodePath;
- (void)removeLutFilterNode:(NSString *)nodePath;
- (void)updateFilter:(NSString *)nodePath intensity:(float)intensity;


@end

@interface MLContractBeautyProcessor (Debug)

- (void)setupComposeNode:(NSString*)path key:(NSString*)key;
- (void)updateComposeNode:(NSString*)path key:(NSString*)key intensity:(float)intensity;

@end

NS_ASSUME_NONNULL_END
