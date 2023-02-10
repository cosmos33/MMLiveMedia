//
//  MLDanceActionDetector.h
//  MLVideoProcessing
//
//  Created by Naichuan on 2021/12/15.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class MMExpression,MMObjectFeature,MMBodyFeature;
@interface MLDanceActionDetector : NSObject
@property (nonatomic, copy, readonly) NSString *identifier;

- (instancetype)initWithDetectConfig:(NSDictionary *)config identifier:(NSString * _Nullable)identifier;

- (BOOL)successDetectActionWithImageSize:(CGSize)imageSize
                      expressionFeatures:(NSArray<MMExpression *> *)expressionFeatures
                                   objectFeatures:(NSArray<MMObjectFeature *> *)objectFeatures
                                     bodyFeatures:(NSArray<MMBodyFeature *> *)bodyFeatures;
@end

NS_ASSUME_NONNULL_END
