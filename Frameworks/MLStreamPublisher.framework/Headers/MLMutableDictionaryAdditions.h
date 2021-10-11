//
//  MLMutableDictionaryAdditions.h
//  MLStreamPublisher
//
//  Created by wangqiangqiang on 2018/5/4.
//

#import <Foundation/Foundation.h>

@interface NSMutableDictionary (Additions)

-(void)setObjectValue:(id)i forKey:(NSString*)key;
-(void)setStringValue:(NSString*)i forKey:(NSString*)key;
-(void)setBoolValue:(BOOL)i forKey:(NSString*)key;
-(void)setIntValue:(int)i forKey:(NSString*)key;
-(void)setIntegerValue:(NSInteger)i forKey:(NSString*)key;
-(void)setUnsignedIntegerValue:(NSUInteger)i forKey:(NSString*)key;
-(void)setCharValue:(char)c forKey:(NSString*)key;
-(void)setFloatValue:(float)i forKey:(NSString*)key;
-(void)setDoubleValue:(double)i forKey:(NSString*)key;
-(void)setLongLongValue:(long long)i forKey:(NSString*)key;

@end
