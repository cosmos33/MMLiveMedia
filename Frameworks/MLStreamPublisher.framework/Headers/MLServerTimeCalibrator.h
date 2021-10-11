//
//  MLServerTimeCalibration.h
//  MLStreamPublisher
//
//  Created by Zhangzd on 2018/12/19.
//
#import <Foundation/Foundation.h>
//#import "MLPublisherOptions.h"
#import "MLMediaAPI.h"

#ifndef MLServerTimeCalibration_h
#define MLServerTimeCalibration_h


@class MLServerTimeCalibrator;

@protocol MLServerTimeCalibrationDelegate <NSObject>

- (void)publisherTimeCalibrationSuccess:(MLServerTimeCalibrator *)statistic;
- (void)publisherTimeCalibrationFailed:(MLServerTimeCalibrator *)statistic;

@end

@interface MLServerTimeCalibrator : NSObject

@property (nonatomic, weak) id<MLServerTimeCalibrationDelegate> delegate;

+ (void)registerMediaAPIClass:(Class<MLMediaAPI>)apiClass;

+ (instancetype)instance;

- (instancetype)init;
- (void)startTimeCalibrator;
- (void)startTimeCalibratorWithUrl:(NSString *)reportUrl dictionary:(NSDictionary*)dictionary;  //自定义参数
- (NSString *)getBindUrl;
- (UInt64)timeCalibtatorWithMilliTime:(UInt64)milliTime;
- (UInt64)timeCalibtatorWithSecTime:(UInt64)secTime;
- (SInt64)getCalibtatorTimeDeltaMS;
@end

#endif /* MLServerTimeCalibration_h */
