//
//  MGSGamer.h
//  MGSSDK-Demo
//
//  Created by 杨乃川 on 2020/7/30.
//  Copyright © 2020 杨乃川. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreVideo/CoreVideo.h>
#import <GLKit/GLKit.h>
#import <MetalPetal/MetalPetal.h>

/*
(0,0);tl
 -|--------|-
  |        |
  |        |
  |        |
 -|--------|-
           (1,1);br
 */


NS_ASSUME_NONNULL_BEGIN

@interface MGSGameFilter : NSObject<MTIUnaryFilter>

@property (nonatomic, strong) MTIImage *inputGameImage;

// `backgrundImageURL` will be the first priority
// once the `backgrundImageURL` is setted, `backgroundImage` will be ignored
@property (nonatomic, copy) NSURL *backgrundImageURL;

// will be ignored when `backgrundImageURL` is setted
@property (nonatomic, strong) MTIImage *backgroundImage;

- (void)updateWithConfig:(NSDictionary *)config;
@end

NS_ASSUME_NONNULL_END
