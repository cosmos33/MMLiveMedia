//
//  MLCVImageSegmenter.h
//  MLContractCV
//
//  Created by 杨乃川 on 2020/9/7.
//

#import <Foundation/Foundation.h>
#import <CoreVideo/CoreVideo.h>


NS_ASSUME_NONNULL_BEGIN

@interface MLCVImageSegmentationResult : NSObject<NSCopying>
@property (nonatomic,readonly) NSData *data;

@property (nonatomic,readonly) size_t width;

@property (nonatomic,readonly) size_t height;

@property (nonatomic,readonly) int format; // rgba8888
@end

@interface MLCVImageSegmenterOption : NSObject
@property (nonatomic, assign) float imageScale;
@property (nonatomic, assign) int orientation;
@end

@interface MLCVImageSegmenter : NSObject
+ (void)setLicenseURL:(NSURL *)url;
- (instancetype)init NS_UNAVAILABLE;
- (nullable instancetype)initWithModelURL:(NSURL *)modelURL error:(NSError **)error;

- (MLCVImageSegmentationResult *)segmentationResultForPixelBuffer:(CVPixelBufferRef)pixelbuffer option:(MLCVImageSegmenterOption *)option;
@end

NS_ASSUME_NONNULL_END
