//
//  MLDictionaryAdditions.h
//  MLStreamPublisher
//
//  Created by wangqiangqiang on 2018/5/4.
//

#import <Foundation/Foundation.h>

@interface NSDictionary (Additions)

- (BOOL)getBoolValueForKey:(NSString *)key defaultValue:(BOOL)defaultValue;
- (int)getIntValueForKey:(NSString *)key defaultValue:(int)defaultValue;
- (NSInteger)getIntegerValueForKey:(NSString *)key defaultValue:(NSInteger)defaultValue;
- (NSUInteger)getUnsignedIntegerValueForKey:(NSString *)key defaultValue:(NSUInteger)defaultValue;
- (float)getFloatValueForKey:(NSString*)key defaultValue:(float)defaultValue;
- (double)getDoubleValueForKey:(NSString*)key defaultValue:(double)defaultValue;
- (long long)getLongLongValueForKey:(NSString *)key defaultValue:(long long)defaultValue;
- (NSString *)getStringValueForKey:(NSString *)key defaultValue:(NSString *)defaultValue;

- (NSDictionary*)getDictionaryForKey:(NSString*)key;
- (NSArray*)getArrayForKey:(NSString*)key;
@end
