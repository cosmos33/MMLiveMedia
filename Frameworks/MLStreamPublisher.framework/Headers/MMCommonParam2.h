//
//  MMCommonParam2.h
//  Pods
//
//  Created by 巩玉林 on 2023/1/31.
//

#ifndef MMCommonParam2_h
#define MMCommonParam2_h

typedef NS_ENUM(NSInteger, MMLiveVideoFrameRate) {
    MMLiveVideoFrameRateFps1 = 1,
    MMLiveVideoFrameRateFps7 = 7,
    MMLiveVideoFrameRateFps10 = 10,
    MMLiveVideoFrameRateFps15 = 15,
    MMLiveVideoFrameRateFps24 = 24,
    MMLiveVideoFrameRateFps30 = 30,
    MMLiveVideoFrameRateFps60 = 60,
};

@interface MMLiveScreenCaptureParameters : NSObject

@property (nonatomic, assign) BOOL captureAudio;
@property (nonatomic, assign) NSInteger captureSignalVolume;
@property (nonatomic, assign) BOOL captureVideo;
@property (nonatomic, assign) CGSize captureVideoSize;
@property (nonatomic, assign) MMLiveVideoFrameRate frameRate;
@property (nonatomic, assign) NSInteger videoBitrate;

@end

#endif /* MMCommonParam2_h */
