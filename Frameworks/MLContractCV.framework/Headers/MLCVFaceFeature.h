//
//  MLCVFaceFeature.h
//  MLContractCV
//
//  Created by Naichuan on 2021/1/20.
//

#import <Foundation/Foundation.h>

#import <simd/simd.h>

NS_ASSUME_NONNULL_BEGIN


/*
 
 @protocol FDKFaceLandmarks2D <NSObject>

 @property (nonatomic, readonly) const simd_float2 *points NS_RETURNS_INNER_POINTER;
 @property (nonatomic, readonly) const simd_float2 *normalizedPoints NS_RETURNS_INNER_POINTER;
 @property (nonatomic, copy, readonly) NSArray<NSValue *> *pointValues;


 @end

 @protocol FDKFaceFeature <NSObject>

 @optional
 @property (readonly) NSArray<NSValue *> *landmarks;

 @property (readonly) CGFloat rollAngle;

 @property (readonly) CGRect bounds;

 @property (readonly) double roll;

 - (id<FDKFaceLandmarks2D>)landmarksOfType:(int)type;

 @end
 
 */

typedef NS_ENUM(NSInteger, MLCVFaceLandmarks2DType) {
    MLCVFaceLandmarks2DType68,
    MLCVFaceLandmarks2DType96,
    MLCVFaceLandmarks2DType104,
    MLCVFaceLandmarks2DType137,
    MLCVFaceLandmarks2DType240
};


@interface MLCVFaceLandmark2D: NSObject

@property (nonatomic, readonly) const simd_float2 *points NS_RETURNS_INNER_POINTER;
@property (nonatomic, readonly) const simd_float2 *normalizedPoints NS_RETURNS_INNER_POINTER;
@property (nonatomic, copy, readonly) NSArray<NSValue *> *pointValues;
- (instancetype)initWithLandmarks:(simd_float2 *)landmarks imageSize:(CGSize)imageSize NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;

@property (nonatomic, assign) int pointCount;

@end



@interface MLCVFaceFeature: NSObject
@property (nonatomic, assign) simd_float2 *inner_points;

@property (nonatomic,readonly,copy) NSArray<NSValue *> *landmarks;

@property (nonatomic, assign) CGFloat rollAngle;

@property (nonatomic, assign) CGRect bounds;

@property (nonatomic, assign) double pitch;
@property (nonatomic, assign) double yaw;
@property (nonatomic, assign) double roll;

@property (nonatomic, assign) CGSize imageSize;

- (MLCVFaceLandmark2D *)landmarksOfType:(MLCVFaceLandmarks2DType)type;

@end

NS_ASSUME_NONNULL_END

