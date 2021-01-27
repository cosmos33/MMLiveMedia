//
//  MLSkinWhitenFilter.h
//  MLVideoProcessing
//
//  Created by 杨乃川 on 2021/1/4.
//

#import <Foundation/Foundation.h>
#import <MetalPetal/MetalPetal.h>
NS_ASSUME_NONNULL_BEGIN

@interface MLSkinWhitenFilter : NSObject<MTIUnaryFilter>
- (void)skinWhitenLevel:(int)level; // 0 , old; 1 new doki2.0
@property (nonatomic, assign) BOOL disable;
@property (nonatomic, assign) float whiten;
@property (nonatomic, assign) float rosy;
@end

NS_ASSUME_NONNULL_END
