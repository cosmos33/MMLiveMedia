//
//  MMCommonParam2.h
//  Pods
//
//  Created by 巩玉林 on 2023/1/31.
//

#ifndef MMCommonParam2_h
#define MMCommonParam2_h

typedef NS_ENUM(NSInteger, MMLiveAudioEffectPreset) {
    MMLiveAudioEffectPresetOff = 0x00000000,
    MMLiveAudioEffectPresetRoomAcousticsKTV = 0x02010100,
    MMLiveAudioEffectPresetRoomAcousVocalConcer = 0x02010200,
    MMLiveAudioEffectPresetRoomAcousStudio = 0x02010300,
    MMLiveAudioEffectPresetRoomAcousPhonograph = 0x02010400,
    MMLiveAudioEffectPresetRoomAcousVirtualStereo = 0x02010500,
    MMLiveAudioEffectPresetRoomAcousSpatial = 0x02010600,
    MMLiveAudioEffectPresetRoomAcousEthereal = 0x02010700,
    MMLiveAudioEffectPresetRoomAcous3DVoice = 0x02010800,
    MMLiveAudioEffectPresetRoomAcousVirtualSurroundSound = 0x02010900,
    MMLiveAudioEffectPresetVoiceChangerEffectUncle = 0x02020100,
    MMLiveAudioEffectPresetVoiceChangerEffectOldMan = 0x02020200,
    MMLiveAudioEffectPresetVoiceChangerEffectBoy= 0x02020300,
    MMLiveAudioEffectPresetVoiceChangerEffectSister= 0x02020400,
    MMLiveAudioEffectPresetVoiceChangerEffectGirl = 0x02020500,
    MMLiveAudioEffectPresetVoiceChangerEffectPigKin = 0x02020600,
    MMLiveAudioEffectPresetVoiceChangerEffectHulk = 0x02020700,
    MMLiveAudioEffectPresetStyleTransformationRnb = 0x02030100,
    MMLiveAudioEffectPresetStyleTransformationPopular= 0x02030200,
    MMLiveAudioEffectPresetPitchCorrection = 0x02040100
};

typedef NS_ENUM(NSInteger, MMLiveVoiceBeautifierPreset) {
    MMLiveVoiceBeautifierPresetOff = 0x00000000,
    MMLiveVoiceBeautifierPresetChatBeautifierMagnetic = 0x01010100,
    MMLiveVoiceBeautifierPresetChatBeautifierFresh = 0x01010200,
    MMLiveVoiceBeautifierPresetChatBeautifierVitality = 0x01010300,
    MMLiveVoiceBeautifierPresetSingingBeautifier= 0x01020100,
    MMLiveVoiceBeautifierTimbreTransformationVigorous = 0x01030100,
    MMLiveVoiceBeautifierTimbreTransformationDeep = 0x01030200,
    MMLiveVoiceBeautifierTimbreTransformationMellow= 0x01030300,
    MMLiveVoiceBeautifierTimbreTransformationFalsetto= 0x01030400,
    MMLiveVoiceBeautifierTimbreTransformationFull = 0x01030500,
    MMLiveVoiceBeautifierTimbreTransformationClear = 0x01030600,
    MMLiveVoiceBeautifierTimbreTransformationResounding = 0x01030700,
    MMLiveVoiceBeautifierTimbreTransformatRinging= 0x01030800,
    MMLiveVoiceBeautifierUltraHighQuality = 0x01040100
};

typedef NS_ENUM(NSInteger, MMLiveVoiceConversionPreset) {
    MMLiveVoiceConversionPresetOff = 0x00000000,
    MMLiveVoiceConversionPresetNeutral = 0x03010100,
    MMLiveVoiceConversionPresetSweet = 0x03010200,
    MMLiveVoiceConversionPresetChangerSolid = 0x03010300,
    MMLiveVoiceConversionPresetChangerBass = 0x03010400
};

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
@property (nonatomic, assign) NSInteger videoBitrate; // 单位：bps

@end

@interface MMLiveRtcChannelMediaOptions : NSObject

@property(assign, nonatomic) BOOL publishCameraTrack;
@property(assign, nonatomic) BOOL publishMicrophoneTrack;
@property(assign, nonatomic) BOOL publishScreenCaptureVideo;
@property(assign, nonatomic) BOOL publishScreenCaptureAudio;
@property(assign, nonatomic) BOOL publishCustomAudioTrack;
@property(assign, nonatomic) BOOL publishCustomVideoTrack;
@property(assign, nonatomic) BOOL publishEncodedVideoTrack;
@property(assign, nonatomic) BOOL autoSubscribeAudio;
@property(assign, nonatomic) BOOL autoSubscribeVideo;

@end

#endif /* MMCommonParam2_h */
