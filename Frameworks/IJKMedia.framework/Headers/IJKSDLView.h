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
- (void)ijkSDLGLView:(IJKSDLView *)view error:(NSError *)error;

@end;

@interface IJKSDLView : UIView

- (id) initWithFrame:(CGRect)frame;
- (void) display: (void *) overlay;
- (void) clearContent;

- (UIImage*)snapshotThreadSafe;
- (UIImage*)snapshot;
- (void)toggleGLPaused:(BOOL)paused;

@property(nonatomic,weak) id<IJKSDLGLViewDelegate>  delegate;
@property(nonatomic)        CGFloat  fps;
@property(nonatomic)        CGFloat  scaleFactor;
@property(nonatomic, assign) BOOL shouldStopGLInBackground;

@end

NS_ASSUME_NONNULL_END
