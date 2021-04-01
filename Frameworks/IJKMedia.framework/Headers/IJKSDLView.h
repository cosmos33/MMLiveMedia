//
//  IJKSDLView.h
//  IJKMedia
//
//  Created by Hao.Li on 2021/1/18.
//  Copyright © 2021 MOMO. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@class IJKSDLView;

@protocol IJKSDLGLViewDelegate <NSObject>
@optional
- (CVPixelBufferRef)ijkSDLGLView:(IJKSDLView *)view beautyFilter:(CVPixelBufferRef)oldBuffer;

@end;

@interface IJKSDLView : UIView

- (id) initWithFrame:(CGRect)frame;
- (void) display: (void *) overlay;
- (void) clearContent;

- (UIImage*) snapshot;
@property(nonatomic,weak) id<IJKSDLGLViewDelegate>  delegate;
@property(nonatomic)        CGFloat  fps;
@property(nonatomic)        CGFloat  scaleFactor;

@end

NS_ASSUME_NONNULL_END
