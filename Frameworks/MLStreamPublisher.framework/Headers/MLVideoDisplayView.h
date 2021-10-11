//
//  MLVideoGLDisplayView.h
//
//  MLVideoDisplayView.m
//  MLStreamPublisher
//
//  Created by wangqiangqiang on 2021/1/28.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, MLVideoDisplayScalingMode) {
    MLVideoDisplayScalingModeResizeAspectFill,
    MLVideoDisplayScalingModeResizeAspectFit,
    MLVideoDisplayScalingModeResize
};

@interface MLVideoDisplayView : UIView

@property (nonatomic, assign) MLVideoDisplayScalingMode scalingMode;

@property (nonatomic) BOOL benchmarkEnabled;

- (BOOL)presentPixelBuffer:(CVPixelBufferRef)pixelBuffer;

@end

NS_ASSUME_NONNULL_END
