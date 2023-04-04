//
//  IJKVideoFrame.h


#import "IJKFrame.h"

@interface IJKVideoFrame : IJKFrame

@property (nonatomic) BOOL isKeyFrame;
@property (nonatomic, assign) int width;
@property (nonatomic, assign) int height;

@end
