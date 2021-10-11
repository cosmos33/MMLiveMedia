//
//  MLMediaVideoRecorder.h
//  MomoChat
//
//  Created by lihao on 2019/11/8.
//  Copyright © 2019 wemomo.com. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class MLMediaVideoRecorder;


@protocol MLMediaVideoRecorderDelegate <NSObject>

- (void)mlMediaVideoRecorder:(MLMediaVideoRecorder *)recorder didReceivePCMData:(NSData *)pcmData sampleRate:(int)sampleRate channels:(int)channels;

@end

@interface MLMediaVideoRecorder : NSObject
@property (nonatomic, weak) id <MLMediaVideoRecorderDelegate> delegate;
@property (nonatomic, assign, readonly) BOOL isRecording;
@property (nonatomic, strong) NSURL *outputVideoURL;
@property (nonatomic, strong) NSURL *inputVideoURL;

- (void)setupRecorderWidth:(NSUInteger)recorderWidth height:(NSUInteger)recorderHeight recordBitrate:(NSUInteger)bitrate;
- (BOOL)startRecording;
- (void)stopRecordingWithCompletion:(void (^)(void))completionBlock;
- (void)writeVideoFrame:(CVPixelBufferRef)pixelBuffer;
- (void)writeAudioPacket:(NSDictionary *)audioPacket;
@end

NS_ASSUME_NONNULL_END
