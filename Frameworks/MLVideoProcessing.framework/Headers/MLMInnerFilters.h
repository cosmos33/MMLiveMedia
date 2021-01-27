//
//  MLMInnerFilters.h
//  MLVideoProcessing
//
//  Created by 杨乃川 on 2020/8/11.
//

#import <Foundation/Foundation.h>
#import <MetalPetal/MetalPetal.h>
NS_ASSUME_NONNULL_BEGIN


@interface MLMInnerSaturationFilter: NSObject<MTIUnaryFilter>
@property (nonatomic, assign) float saturation;
@property (nonatomic, assign) BOOL disable;
@end

@interface MLMInnerUSMFilter: NSObject<MTIUnaryFilter>
@property (nonatomic, assign) float radius;
@property (nonatomic, assign) float threshold;
@property (nonatomic, assign) float scale;
@property (nonatomic, assign) BOOL disable;
@end


@interface MLMInnerContrastFilter : NSObject<MTIUnaryFilter>
@property (nonatomic, assign) float contrast;
@property (nonatomic, assign) BOOL disable;
@end

@interface MLMInnerColorLookupFilter : NSObject <MTIUnaryFilter>
@property (nonatomic, assign) BOOL disable;
@property (nonatomic, strong) MTIImage *inputColorLookupTable;
@property (nonatomic, assign) float intensity;
@end


@interface MLMInnerFilters : NSObject

@end

NS_ASSUME_NONNULL_END
