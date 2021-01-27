//
//  MLFaceDetectorController.h
//  MomoChat
//
//  Created by YuAo on 7/26/16.
//  Copyright © 2016 wemomo.com. All rights reserved.
//

#import <MomoCV/MomoCV.h>
#import <MLContractCV/MLContractCV.h>
NS_ASSUME_NONNULL_BEGIN
@protocol MLBodyDetectoOption <NSObject>
@property (nonatomic, assign) float landmarksScale;
@end

@protocol MLBodyDetector <NSObject>
- (nullable instancetype)initWithModelURL:(NSURL *)url error:(NSError **)error;
- (NSArray<MMBodyFeature *> *)featuresInPixelBuffer:(CVPixelBufferRef)pixelBuffer options:(id<MLBodyDetectoOption>)options;
@end


@protocol MLImageSegmentResult <NSObject>

@property (nonatomic,readonly) NSData *data;

@property (nonatomic,readonly) size_t width;

@property (nonatomic,readonly) size_t height;

@property (nonatomic,readonly) int format; // rgba8888
@end

@protocol MLImageSegmentOption <NSObject>

@property (nonatomic, assign) float imageScale;
@property (nonatomic, assign) int orientation;
@end



@protocol MLImageSegmenter <NSObject>
- (nullable instancetype)initWithModelURL:(NSURL *_Nonnull)modelURL error:(NSError **_Nullable)error;

- (id <MLImageSegmentResult>_Nullable)segmentationResultForPixelBuffer:(CVPixelBufferRef)pixelbuffer option:(id <MLImageSegmentOption>_Nullable)option;
@end



@interface MLCVDetectorController : NSObject

+ (instancetype)sharedController;

+ (nullable MMFaceDetector *)makeFaceDetector;

+ (nullable MMObjectDetector *)makeObjectDetector;

+ (nullable id<MLBodyDetector>)makeBodyDetector NS_AVAILABLE(10_13, 11_0);

+ (nullable MMExpressionDetector *)makeExpressionDetector;

+ (nullable id <MLImageSegmenter>)makeImageSegmenter;

+ (nullable MMHandGestureDetector *)makeHandGestureDetector;

+ (nullable MMFaceAnimojiProcessor *)makeAnimojiDetector;

+ (nullable MLContractBeautyProcessor *)makeContractFaceProcessor;

+ (BOOL)canCreateContractFaceProcessor;

+ (BOOL)canCreateAnimojiDetector;

+ (BOOL)canCreateFaceDetector;

+ (BOOL)canCreateObjectDetector;

+ (BOOL)canCreateBodyDetector;

+ (BOOL)canCreateExpressionDetector;

+ (BOOL)canCreateImageSegmenter;

+ (BOOL)canCreateHandGestureDetector;
#if DEBUG
+ (BOOL)updateObjectDetectorModelWithURL:(NSURL *)url shouldValidate:(BOOL)shouldValidate; //file url
#endif


@property (nonatomic,readonly) BOOL shouldDetectFaces;

@property (nonatomic) BOOL faceBeautifierIsEnabled;
@property (nonatomic) BOOL hasFaceDecorations;
@property (nonatomic) BOOL faceBeautyCanUseLowFrequencyDetection;
@property (nonatomic) BOOL canUseLowFrequencyDetection;
@property (nonatomic) BOOL dokiEnable;
@property (nonatomic) BOOL shouldDetectBody;
@property (nonatomic) BOOL shouldDetectExpression;
@property (nonatomic) BOOL shouldSegmentImage;
@property (nonatomic) BOOL shouldDetectHandGesture;
@property (nonatomic) BOOL shouldDetectObject;
@property (nonatomic) BOOL shouldDetectAnimoji;
@property (nonatomic) BOOL shouldUse3DGame;
@property (nonatomic) NSUInteger handGestureType;

+ (void)installFaceDetector:(MMFaceDetector *)faceDetector;
+ (void)uninstallFaceDetector;

+ (void)installObjectDetector:(MMObjectDetector *)objectDetector;
+ (void)uninstallObjectDetector;

+ (void)installBodyDetector:(id<MLBodyDetector>)bodyDetector NS_AVAILABLE(10_13, 11_0);
+ (void)uninstallBodyDetector;

+ (void)installExpressionDetector:(MMExpressionDetector *)expressionDetector;
+ (void)uninstallExpressionDetector;

+ (void)installImageSegmenter:(id <MLImageSegmenter>)imageSegmenter;
+ (void)uninstallImageSegmenter;

+ (void)installHandGestureDetector:(MMHandGestureDetector *)handGestureDetector;
+ (void)uninstallHandGestureDetector;

+ (void)installAnimojiDetector:(MMFaceAnimojiProcessor *)animojiDetector;
+ (void)uninstallAnimojiDetector;

// process buffer & detect face
+ (void)installContractFaceProcessor:(MLContractBeautyProcessor *)faceProcessor;
+ (void)uninstallContratFaceProcessor;



+ (void)uninstallAllDetectors;

@end

NS_ASSUME_NONNULL_END

