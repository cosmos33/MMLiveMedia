//
//  AudioUnitController.h
//  MomoChat
//
//  Created by MOMO on 9/28/16.
//  Copyright © 2016 wemomo.com. All rights reserved.
//

#import <AudioToolbox/AudioToolbox.h>
#import <AVFoundation/AVFoundation.h>

@protocol MLAudioUnitDelegate <NSObject>
- (void)onDeliverRecorderData:(UInt32)outNumberFrames ioData:(AudioBufferList *)ioData;
- (void)onAudioUnitRenderDataError:(OSStatus)error instance:(void*)instance;
@end

@interface AudioController : NSObject

@property (nonatomic, weak) id<MLAudioUnitDelegate> delegate;
@property (nonatomic, assign, readonly) BOOL audioChainIsBeingReconstructed;
@property (nonatomic, assign) AudioUnit rioUnit;
@property (nonatomic, assign) double realSampleRate;
@property (nonatomic, assign) double realChannel;
@property (atomic, assign) BOOL isStopped;
@property (nonatomic, assign, readonly) OSType componentSubType;
@property (nonatomic, assign) BOOL recoryFromInterruption;
@property (nonatomic, assign) BOOL isSpeakerphone;
@property (nonatomic, assign, readonly) BOOL isDisableIOAudioUnitBus1;

/*
 * componentSubType: kAudioUnitSubType_XXX
 */
- (id)initWithDelegate:(id<MLAudioUnitDelegate>)delegate
      targetSampleRate:(double)targetSampleRate
         targetChannel:(int)targetChannel
      componentSubType:(OSType)componentSubType
          isConference:(BOOL)enable
        isSpeakerphone:(BOOL)speakerphone
        disableInputIO:(BOOL)disableInputIO;

+ (double)trySetWithTargetSampleRate:(double)targetSampleRate;
+ (BOOL)isHeadsetPluggedIn;
+ (BOOL)isBluetoothConnected;
+ (BOOL)needToUseRemoteIOForBetterQuality;
+ (BOOL)setCategory:(NSString *)category mode:(NSString *)mode withOptions:(AVAudioSessionCategoryOptions)options;

- (OSStatus)startIOUnit;
- (double)sessionSampleRate;
- (void)enableEchoCancellation:(BOOL)isEnable;
- (void)shutdownPlayAndRecord;

- (void)setRecordVolume:(float)volume;
@end
