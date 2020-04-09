//
//  MLStreamConfiguration.h
//  MLStreamPublisher
//
//  Created by wangtao on 2020/4/8.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface MLStreamConfiguration : NSObject
typedef CGFloat (^MLGPUCollectFrequencyBlock)(void);

typedef int (^MLGPUUsageBlock)(void);

+ (MLStreamConfiguration *)defaultConfiguration;
//GPU采集频次控制 gpuCollectFrequency秒/次 0表示不采集，建议配置为1
@property (nonatomic, strong)MLGPUCollectFrequencyBlock GPUCollectFrequencyBlock;

//提供GPU使用率数据,可通过上传MLDeviceUtil返回
@property (nonatomic, strong)MLGPUUsageBlock GPUUsageBlock;
@end

NS_ASSUME_NONNULL_END
