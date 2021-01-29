//
//  MLCVFaceFeature.h
//  MLContractCV
//
//  Created by Naichuan on 2021/1/20.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <GLKit/GLKit.h>
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
@property (readonly) NSUInteger pointCount;

@property (nonatomic, readonly) const simd_float2 *points NS_RETURNS_INNER_POINTER;

@property (nonatomic, copy, readonly) NSArray<NSValue *> *pointValues;

@property (nonatomic, readonly) CGSize imageSize;

@property (nonatomic, readonly) const simd_float2 *normalizedPoints NS_RETURNS_INNER_POINTER;

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)initWithPoints:(const simd_float2[_Nonnull])points count:(NSUInteger)count imageSize:(CGSize)imageSize;

@end



@interface MLCVFaceFeature: NSObject

@property (nonatomic,readonly,copy) NSArray<NSValue *> *landmarks;

@property (nonatomic, assign) CGFloat rollAngle;

@property (nonatomic, assign) CGRect bounds;

@property (nonatomic, assign) double pitch;
@property (nonatomic, assign) double yaw;
@property (nonatomic, assign) double roll;

@property (nonatomic, assign) CGSize imageSize;

@property (nonatomic,readonly) NSInteger trackingIdentifier;

@property (nonatomic,readonly) NSDictionary *metadata;

@property (nonatomic,readonly) int quality;

- (MLCVFaceLandmark2D *)landmarksOfType:(MLCVFaceLandmarks2DType)type NS_SWIFT_NAME(landmarks(ofType:));

- (MLCVFaceFeature *)faceFeatureByUpdatingLandmarksOfType:(MLCVFaceLandmarks2DType)type landmarks:(MLCVFaceLandmark2D *)landmarks NS_SWIFT_NAME(updatingLandmarks(ofType:landmarks:));

@end


@interface MLCVFaceFeature (ThreeDimensional)

@property (nonatomic,readonly) GLKMatrix3 cameraMatrix;
@property (nonatomic,readonly) GLKMatrix3 rotationMatrix;

@property (nonatomic,readonly) GLKVector3 rotationVector;
@property (nonatomic,readonly) GLKVector3 translationVector;

@property (nonatomic,readonly) GLKMatrix4 projectionMatrix;

@property (nonatomic,readonly) GLKMatrix4 modelViewMatrix;

@end

@interface MLCVFaceFeature (FaceRigFeature)

@property (nonatomic,readonly) GLKVector3 facerigEulerVector;

@property (nonatomic,readonly) NSArray <NSNumber *> *facerigStates;

@end

@interface MLCVFaceFeature (Deprecated)

@property (nonatomic,readonly,copy) NSArray<NSValue *> *landmarks; //NSValue of CGPoints

@property (nonatomic,readonly,copy) NSArray<NSValue *> *landmarks96; //NSValue of CGPoints

@property (nonatomic,readonly,copy) NSArray<NSValue *> *landmarks68;

@property (nonatomic,readonly,copy) NSArray<NSValue *> *landmarks87;

@property (nonatomic,readonly,copy) NSArray<NSValue *> *landmarks104;

@property (nonatomic,readonly,copy) NSArray<NSValue *> *landmarks137;

@property (nonatomic,readonly,copy) NSArray<NSValue *> *landmarks240;

@end

FOUNDATION_EXPORT NSString * const MLCVFaceFeatureErrorDomain;

typedef NS_ERROR_ENUM(MLCVFaceFeatureErrorDomain, MLCVFaceFeatureError) {
    MLCVFaceFeatureErrorInvalidJSONObject = 1
};

@interface MLCVFaceFeature (JSON)

- (nullable instancetype)initWithJSONRepresentation:(id)JSONObject error:(NSError **)error;

- (id)JSONRepresentation;

@end

NS_ASSUME_NONNULL_END

