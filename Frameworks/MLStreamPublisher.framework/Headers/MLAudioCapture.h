//
//  MLAudioCapture.h
//  MomoChat
//
//  Created by wangqiangqiang on 2017/5/3.
//  Copyright © 2017年 wemomo.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

#pragma mark -- AudioCaptureNotification
/** compoentFialed will post the notification */
extern NSString *_Nullable const MLAudioComponentFailedToCreateNotification;

@class MLAudioCapture;
/** MLAudioCapture callback audioData */
@protocol MLAudioCaptureDelegate <NSObject>
- (void)captureOutputDidChangeSubtype:(nullable MLAudioCapture *)capture;
- (void)captureOutput:(nullable MLAudioCapture *)capture audioData:(nullable NSData*)audioData;
- (void)captureOutput:(nullable MLAudioCapture *)capture renderAudioData:(nullable NSData*)audioData;
@end

@interface MLAudioCapture : NSObject

#pragma mark - Attribute
///=============================================================================
/// @name Attribute
///=============================================================================

/** The delegate of the capture. captureData callback */
@property (nullable, nonatomic, weak) id<MLAudioCaptureDelegate> delegate;

/** The muted control callbackAudioData,muted will memset 0.*/
@property (nonatomic, assign) BOOL muted;

/** The running control start capture or stop capture*/
@property (nonatomic, assign) BOOL running;

/** is manager audio session*/
@property (nonatomic, assign) BOOL notManagerAudioSession;

/** is use vpio*/
@property (nonatomic, assign) BOOL useVpio;

/**is main queue*/

@property (nonatomic, assign) BOOL useMainQueue;

#pragma mark - Initializer
///=============================================================================
/// @name Initializer
///=============================================================================
- (nullable instancetype)init UNAVAILABLE_ATTRIBUTE;
+ (nullable instancetype)new UNAVAILABLE_ATTRIBUTE;

/**
 The designated initializer. Multiple instances with the same configuration will make the
 capture unstable.
 */
- (nullable instancetype)initWithAudioSampleRate:(int)sampleRate audioChannels:(int)numberOfChannels NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithAudioSampleRate:(int)sampleRate audioChannels:(int)numberOfChannels  useVpio:(BOOL)enable NS_DESIGNATED_INITIALIZER;

- (int)restartCapture;
- (void)copySampleBuffer:(CMSampleBufferRef)sampleBuffer;//hrs
@end
