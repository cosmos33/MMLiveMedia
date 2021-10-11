//
//  MLMediaUtility.h
//  MomoChat
//
//  Created by MOMO on 2017/9/27.
//  Copyright © 2017年 wemomo.com. All rights reserved.
//

#import <Foundation/Foundation.h>

#define getTimestampInMs() ((uint64_t)([[NSDate date] timeIntervalSince1970] * 1000LL))
#define getTimestampInSec() ((uint64_t)([[NSDate date] timeIntervalSince1970]))

FOUNDATION_EXPORT CGRect MLMediaMakeRectWithAspectRatioFillRect(CGSize aspectRatio, CGRect boundingRect);

FOUNDATION_EXPORT CGRect MLMediaMakeRectWithAspectRatioInsideRect(CGSize aspectRatio, CGRect boundingRect);

FOUNDATION_EXPORT uint64_t MLGetCurrentTimestampInMilliseconds(void);

FOUNDATION_EXPORT uint64_t MLGetCurrentTimestampInSeconds(void);

FOUNDATION_EXPORT void printMem(const uint8_t *mem, size_t size, const char *format, int num_in_line);

FOUNDATION_EXPORT void printMemHex(const uint8_t *mem, size_t size);

FOUNDATION_EXPORT void printMemChar(const uint8_t *mem, size_t size);

@interface MLMediaUtility : NSObject

+ (CGFloat)getAppCpuUsage;

+ (CGFloat)getDeviceCpuUsage;

// Return MBytes
+ (CGFloat)getAppMemUsage;

+ (unsigned long long)getPhysMemory;

// Return MBytes
+ (CGFloat)getDeviceMemAvailable;

// 0 - 100
+ (int)getBatteryPercentage;

// full/charging/uncharged
+ (NSString *)getBatteryStatus;

+ (NSString *)getLocalDNSServerIP;

+ (int)checkDeviceLowPowerMode;

+ (id)safeObjectAtIndex:(NSArray*)array index:(NSUInteger)index;

+ (NSString *)getIPAddress:(BOOL)preferIPv4;

+ (NSString *)getPublisherInfo;

+ (NSString *)getVadStatusInfo;

+ (void)setVadStatus:(int)enableAutoControl vadDetect:(int)vadDetect denoiseLevel:(int)denoiseLevel isVadDownGrade:(BOOL)isVadDownGrade;

+ (void)setSDKVersion:(int)publisherType version:(NSString*)sdkversion;
+(BOOL)isSimuLator;
// Scale
//+ (CVPixelBufferRef)resizePixelBuffer:(CVPixelBufferRef)src_buffer
//                           scaleWidth:(int)scale_width
//                          scaleHeight:(int)scale_height;

@end


@interface MLMediaUtilityScale : NSObject

- (instancetype)initWithScaleSize:(CGSize)scaleSize;
- (CVPixelBufferRef)resizePixelBuffer:(CVPixelBufferRef)srcBuffer
                        withScaleSize:(CGSize)scaleSize CF_RETURNS_NOT_RETAINED;

@end


//判断系统版本号（用于适配xcode11，替换@available方法）
#define SystemVersionAvailable(x)  [UIDevice currentDevice].systemVersion.floatValue >= x

//UI操作判断是否主线程(同步)
#define UICheckMainThreadSync(code)     if (![NSThread isMainThread]) { dispatch_sync(dispatch_get_main_queue(), ^{ code }); } else { code }
//UI操作判断是否主线程(异步)
#define UICheckMainThreadAsync(code)     if (![NSThread isMainThread]) { dispatch_async(dispatch_get_main_queue(), ^{ code }); } else { code }
