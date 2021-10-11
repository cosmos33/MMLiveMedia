//
//  MLJsonTool.h
//  CURLTest
//
//  Created by Hao.Li on 2019/9/2.
//  Copyright © 2019 Hao.Li. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface MLJsonTool : NSObject
/**
 将字典转为json字符串

 @param dic 字典
 @return json字符串
 */
+ (NSString *)dicConvertToJsonStr:(NSDictionary *)dic;

/**
 将json的data数据转为字典

 @param data json data
 @return 字典
 */
+ (NSDictionary *)jsonDataConvertToDic:(NSData *)data;
@end

NS_ASSUME_NONNULL_END
