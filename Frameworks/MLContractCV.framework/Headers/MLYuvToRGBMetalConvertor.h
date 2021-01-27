//
//  MLYuvToRGBMetalConvertor.h
//  MLContractCV
//
//  Created by 杨乃川 on 2021/1/12.
//

#import <Foundation/Foundation.h>
#import <CoreVideo/CoreVideo.h>
NS_ASSUME_NONNULL_BEGIN

@interface MLYuvToRGBMetalConvertor : NSObject
@property (nonatomic, assign) CGSize outputBufferSize;
- (CVPixelBufferRef)convertedPixelBufferWithInputPixelBuffer:(CVPixelBufferRef)inputPixelBuffer;
@end

NS_ASSUME_NONNULL_END
