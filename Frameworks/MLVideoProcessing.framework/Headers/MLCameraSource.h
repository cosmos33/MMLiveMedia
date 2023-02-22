//
//  MLCameraSource.h
//  MomoChat
//
//  Created by YuAo on 10/14/16.
//  Copyright © 2016 wemomo.com. All rights reserved.
//

@import Foundation;
#import <MLMediaFoundation/MLMediaFoundation.h>
#import <FaceDecorationKit/FaceDecorationKit.h>
@import AVFoundation;
#import <MLFilterKitMetalPetal/MLFilterKitMetalPetal.h>
#import <MomoCV/MomoCV.h>
#import "MLVideoProcessor.h"
#import "MLBeautySettings.h"
#import "MLMediaSource.h"
#import "MLColorEnhancement.h"
#import "MLRecordingRequest.h"

NS_ASSUME_NONNULL_BEGIN

typedef  NS_ENUM(NSUInteger, MLCameraSouceProcessorType){
    MLCameraSouceProcessorTypeGPUImage = 0,
    MLCameraSouceProcessorTypeMetalPetal
};

typedef NS_ENUM(NSUInteger, MLCameraSourceImageDetectOrientation) {
    MLCameraSourceImageDetectOrientationUp, //0
    MLCameraSourceImageDetectOrientationDown, // 180 deg rotation
    MLCameraSourceImageDetectOrientationLeft, // 90 deg CCW
    MLCameraSourceImageDetectOrientationRight // 90 deg CW
};

typedef NS_ENUM(NSUInteger, MLCameraSourceBeautyType) {
    MLCameraSourceBeautyTypeForOldMomoVersion = -1,
    MLCameraSourceBeautyTypeOld = 0,
    MLCameraSourceBeautyTypeDoki = 1,
    MLCameraSourceBeautyTypeByteDance = 2, // 90 deg CW
    MLCameraSourceBeautyTypeSelfDevelop = 3 // 自研美颜，用来替换抖音
};


typedef NS_OPTIONS(NSUInteger, MLCameraSourceDetectorOption){
    MLCameraSourceDetectorOptionNone = 0,
    MLCameraSourceDetectorOptionFace = 1 << 0,
    MLCameraSourceDetectorOptionBody = 1 << 1,
    MLCameraSourceDetectorOptionExpression = 1 << 2,
    MLCameraSourceDetectorOptionObject = 1 << 3,
    MLCameraSourceDetectorOptionSegmetation = 1 << 4,
    MLCameraSourceDetectorOptionHandGesture = 1 << 5,
    MLCameraSourceDetectorOptionAnimoji = 1 << 6,
    MLCameraSourceDetectorOptionTPBeautyProcessor = 1 << 7, //第三方美颜识别器，一定不能移除
    MLCameraSourceDetectorOptionAll = NSUIntegerMax,
};

typedef MLCameraSourceDetectorOption MLCameraSourceCVFeatureJSONOutputOption;

OBJC_EXTERN NSString *const kMLDecorationManagerDecorationFilterAddedNotification;

OBJC_EXTERN NSString *const kMLDecorationGridsFilterDidFinishAnimationNotification;

OBJC_EXTERN NSString *const kMLCameraSourceDanceDetectorReason_TIME_OUT;
OBJC_EXTERN NSString *const kMLCameraSourceDanceDetectorReason_USER;
OBJC_EXTERN NSString *const kMLCameraSourceDanceDetectorReason_DETECT_SUCCESS;

@interface MLCameraSourceVideoFrameBenchmark : NSObject <NSCopying>

@property (atomic,readonly) NSTimeInterval faceDetectionInterval;
@property (atomic,readonly) NSTimeInterval bodyDetectionInterval;
@property (atomic,readonly) NSTimeInterval expressionDetectionInterval;
@property (atomic,readonly) NSTimeInterval objectDetectionInterval;
@property (atomic,readonly) NSTimeInterval imageSegmentationInterval;
@property (atomic,readonly) NSTimeInterval handGestureInterval;
@property (atomic,readonly) NSTimeInterval cpuProcessingInterval;
@property (atomic,readonly) NSTimeInterval gpuProcessingInterval;
@property (atomic, readonly) NSTimeInterval metalProcessingInterval;
@property (atomic,readonly) float faceThinAmount;
@property (atomic,readonly) float skinWhitenAmount;
@property (atomic,readonly) float eyeBigAmount;
@property (atomic,readonly) float skinSmoothAmount;
@property (atomic,readonly) NSUInteger faceCount;
@property (atomic,readonly) CGRect faceRect;
@property (atomic, copy, readonly) NSArray *eulerAngles;//[0]roll, [1]yaw, [2]pitch
@property (atomic,readonly) CGPoint focusPoint;
@property (atomic,readonly) CGPoint exposurePoint;
@property (atomic,readonly) float ISO;
@property (atomic, copy, readonly) NSString *lutName;
@property (atomic, readonly) float lutIntensity;
@property (nonatomic, copy, readonly) NSString *objectDetectInfo;

@end

@class MLCameraSource, CXBeautyConfiguration, MMFaceFeature,MMObjectFeature, MMBodyFeature, MMExpression,MMHandFeature, MLContractBeautySourceItem;

@protocol MLCameraSourceRawVideoSampleBufferOutputDelegate <NSObject>

- (void)cameraSource:(MLCameraSource *)cameraSource didOutputVideoSampleBuffer:(CMSampleBufferRef)sampleBuffer;

@end

@interface MLCameraSourceSaveFaceFeatureOptions : NSObject

@property (nonatomic, assign) int uploadUserFeature;
@property (nonatomic, assign) BOOL uploadAsynchronously;
@property (nonatomic, assign) BOOL useFeatureStrict;
@property (nonatomic, assign) int uploadFeatureVersion;
@property (nonatomic, assign) int sampleSkipFrameCount;
@property (nonatomic, copy) NSArray  *uploadFeatureEulerAngles;


@end


@interface MLCameraSourceAnalyticsImage : NSObject <NSCopying>

@property (nonatomic,copy,readonly) NSData *data;

@property (nonatomic,copy,readonly) NSString *identifier;

@end

@interface MLCameraSourceAnalyticsParameters : NSObject <NSCopying>

@property (nonatomic,copy,readonly) NSDictionary *dictionaryRepresentation;

- (void)updateURL:(NSURL *)URL forImage:(MLCameraSourceAnalyticsImage *)image;

- (void)updateResourceIdentifier:(NSString *)resourceIdentifier forImage:(MLCameraSourceAnalyticsImage *)image;

@end

@protocol MLCameraSourceAnalyticsDelegate <NSObject>

- (void)cameraSource:(MLCameraSource *)cameraSource logEventWithParameters:(MLCameraSourceAnalyticsParameters *)parameters images:(NSArray<MLCameraSourceAnalyticsImage *> *)images;

@end
@protocol MLCameraSourceFeatureDetectionDelegate <NSObject>

- (void)cameraSource:(MLCameraSource *)cameraSource
        faceFeatures:(NSArray <MMFaceFeature *> * _Nullable )faceFeatures
      objectFeatures:(NSArray <MMObjectFeature *> * _Nullable)objectFeatures
   facialExpressions:(NSArray <MMFacialExpression  *> *_Nullable)facialExpressions
         exporesions:(NSArray <MMExpression  *> *_Nullable)exporesions
        bodyFeatures:(NSArray <MMBodyFeature *> *_Nullable)bodyFeatures
        handFeatures:(NSArray <MMHandFeature *> *_Nullable)handFeatures;

- (void)cameraSource:(MLCameraSource *)cameraSource faceFeatureVideoInfo:(id)info timeStamp:(CMTime)time;

@optional
- (void)cameraSource:(MLCameraSource *)cameraSource danceActionDetectorSuccess:(NSDictionary *)info;
- (void)cameraSource:(MLCameraSource *)cameraSource danceActionDetectorRemoved:(NSDictionary *)info;
@end


@protocol MLCameraSourceFeatureDetectionJSONDelegate <NSObject>

- (void)cameraSource:(MLCameraSource *)cameraSource featureJSON:(NSDictionary *)info;

@end





@interface MLCameraSource : NSObject <MLMediaSource>

+ (nullable MLCameraSource *)activeCameraSource;

@property (nonatomic, strong) MLCameraSourceSaveFaceFeatureOptions *saveFaceOptions;
@property (nonatomic,readonly,nullable) NSArray *currentFaceFeatures;

@property (nonatomic,weak) id<MLCameraSourceRawVideoSampleBufferOutputDelegate> rawVideoSampleBufferOutputDelegate;

@property (nonatomic,weak) id<MLCameraSourceAnalyticsDelegate> analyticsDelegate;
@property (nonatomic, weak) id<MLCameraSourceFeatureDetectionDelegate> featureDetectionDelegate;
@property (nonatomic) NSTimeInterval minimumAnalyticsInterval;

@property (nonatomic,strong,readonly) MLCamera *camera;

@property (nonatomic,strong,readonly) MLAudioPrism *audioPrism;

 @property (nonatomic, assign) MLCameraSourceImageDetectOrientation imageDetectOrientation;

@property (nonatomic, assign) NSUInteger faceDetectSkipCount; // default 1, no skip

@property (nonatomic, copy) MMFaceDetectOptions *faceDetectOptions;

//webGL使用字段：1.enableWebGLFilter是否开启游戏滤镜；2.GetWebGameBuffer获取游戏buffer
@property (nonatomic, assign) BOOL enableWebGLFilter;
@property (nonatomic, copy) CVPixelBufferRef (^GetWebGameBuffer)(void);
- (void)setCVFeatureJSONOutputDelegate:(id<MLCameraSourceFeatureDetectionJSONDelegate>)delegate outputOption:(MLCameraSourceCVFeatureJSONOutputOption)option andFrameSkipCount:(uint)skipCount;
- (MLCameraSourceDetectorOption)currentAllowedDetectors;

- (instancetype)init NS_UNAVAILABLE;

- (id)initWithSessionPreset:(NSString *)sessionPreset cameraPosition:(AVCaptureDevicePosition)cameraPosition;

- (id)initWithSessionPreset:(NSString *)sessionPreset cameraPosition:(AVCaptureDevicePosition)cameraPosition processorType:(MLCameraSouceProcessorType)processorType;

// Camera Controls
- (void)startCapturing;
- (void)stopCapturing;

- (void)rotateCamera;

// default , front YES,  back camera NOT support, return value: can be setted or not
- (BOOL)mirrorVideo:(BOOL)enable;


- (void)changeCameraVideoOrientation:(AVCaptureVideoOrientation)orientation;

@property (nonatomic) AVCaptureVideoStabilizationMode preferredVideoStabilizationMode;

@property (nonatomic) NSInteger videoCaptureDeviceFrameRate;

@property (nonatomic) float videoZoomFactor;

@property (nonatomic) BOOL audioOutputEnabled;

@property (nonatomic,readonly) CGSize outputVideoFrameSize;

@property (nonatomic, assign) MLCameraSourceDetectorOption detectorOption;
// Effect Controls
@property (nonatomic, assign) BOOL beautyDisable;

@property (nonatomic) CGRect cropRegion;

@property (nonatomic) CGFloat outputScale;

@property (nonatomic) CGFloat preScale;

@property (nonatomic,copy,nullable) MLBeautySettings *beautySettings;
@property (nonatomic,copy,nullable) MLFilterDescriptor *filterDescriptor;
@property (nonatomic, assign) float lookUpTableFilterIntensity;

@property (nonatomic) BOOL watermarkEnabled;

@property (nonatomic, assign) int dokiWarpType;

@property (nonatomic, assign) BOOL dokiBeautyEnable;

@property (nonatomic) MLCameraSourceBeautyType beautyType; // 0 old, 1 new, 2 douyin, 3 自研（对标抖音）

@property (nonatomic) NSUInteger dokiSkinSmoothingVersion; // default is 0;

@property (nonatomic, copy)  CXBeautyConfiguration*dokiConfiguration;

@property (nonatomic, strong) MLColorEnhancement *colorEnhancement;


- (void)addDecoration:(FDKDecoration *)decoration duration:(NSTimeInterval)duration positionType:(NSInteger)positionType;

- (void)addDecoration:(FDKDecoration *)decoration withIdentifier:(NSString *)identifier;

- (void)removeDecorationWithIdentifier:(NSString *)identifier;

- (NSArray<NSString *> *)decorationIdentifiers;

- (FDKDecoration *)decorationWithIdentifier:(NSString *)identifier;

- (void)updateMergeConfiguration:(NSDictionary *)config;

@property (nonatomic,copy) NSArray<MLObjectTriggeredDecoration *> *objectTriggeredDecorations;

@property (nonatomic, copy) NSArray <MLMetalPetalNativeViewItem *> *renderedViewItems;

// Benchmarking
@property (atomic,copy) MLCameraSourceVideoFrameBenchmark *currentVideoFrameBenchmark;

// feedback
// for pixel
@property (nonatomic, copy, nullable) void (^faceBoundsFeedback)(CGRect faceBounds, CGSize bufferSize) ;

@property (nonatomic, assign) CGPoint exposurePoint;
@property (nonatomic, assign) CGPoint focusPoint;

- (void)updateISO:(float)iso; // [20 ~ 1000]
- (void)updateWhiteBalanceTemperature:(float)temper andTint:(float)tint;// temper [3300~4300], tint [-15, 15]
- (void)updateBiasOffset:(float)biasOffset; // [-2, 2]

- (void)addRecordingRequest:(MLRecordingRequest *)request error:(NSError **)error  completion:(void(^)(NSURL  *_Nullable localURL, NSError   *_Nullable error))completionHandler;
- (void)deleteRecordFileWithURL:(NSURL *)url error:(NSError **)error;


- (void)addBeautyItems:(NSArray <MLContractBeautySourceItem *> *)items;
- (void)removeBeautyItems:(NSArray <MLContractBeautySourceItem *> *)items;
- (void)updateBeautyItem:(MLContractBeautySourceItem *)item key:(NSString*)key intensity:(float)intensity;
- (void)enableEnhanceByteDanceMakeUp:(BOOL)enable;

- (void)useByteDanceLowFaceDetectInterval:(BOOL)open;

- (void)setLipsSegmentEnable:(BOOL)lipsSegmentEnable;
- (void)setBigModelEnable:(BOOL)bigModelEnable;

- (void)lightingRenderOn:(BOOL)onOrOff;
@property (nonatomic,readonly) BOOL isLightningRenderOn;

- (NSString *)cameraParams;

// gridsEffectControl
- (void)addDeactiveGrids:(NSArray <NSNumber *>*)indexes animationDuration:(float)duration;
- (void)resetAllGridsToDeactive;


- (void)removeDeactiveGrids:(NSArray <NSNumber *>*)indexes; // no animation

- (void)skipBeauty:(BOOL)skip;

- (void)setupCameraPreset:(NSString *)preset postion:(AVCaptureDevicePosition)position;

// default no
- (void)cartoonFaceMultipleFaceProcessEnable:(BOOL)enable;
// default no
- (void)stylizeFaceMultipleFaceProcessEnable:(BOOL)enable;


/// debug
@property (nonatomic, assign, nullable) CVPixelBufferRef bufferToProcess_debug;
@end

@interface MLCameraSource (Analytics)

- (void)markBeautySettingsAdjustmentDone;

@end

NS_ASSUME_NONNULL_END
