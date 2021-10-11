//
//  MLAgoraConfiguration.h
//  CXBeautyKit
//
//  Created by wangqiangqiang on 2018/4/17.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, MLAgoraChannelProfile) {
    MLAgoraChannelProfileCommunication = 0,
    MLAgoraChannelProfileLiveBroadcasting = 1,
    MLAgoraChannelProfileGame = 2,
};

typedef NS_ENUM(NSUInteger, MLAgoraRenderMode) {
    MLAgoraRenderModeHidden = 1,
    MLAgoraRenderModeFit = 2,
    MLAgoraRenderModeAdaptive = 3,
};

typedef NS_ENUM(NSInteger, MLAgoraOrientationMode) {
    MLAgoraOrientationModeAdaptative = 0,
    MLAgoraOrientationModeFixedLandscape = 1,
    MLAgoraOrientationModeFixedPortrait = 2,
};

typedef NS_ENUM(NSUInteger, MLAgoraClientRole)
{
    MLAgoraClientRoleBroadcaster  = 1,
    MLAgoraClientRoleAudience     = 2
};

typedef NS_ENUM(NSInteger, MLAgoraAudioProfile) {
    // sample rate, bit rate, mono/stereo, speech/music codec
    MLAgoraAudioProfileDefault = 0,                // use default settings
    MLAgoraAudioProfileSpeechStandard = 1,         // 32Khz, 18kbps, mono, speech
    MLAgoraAudioProfileMusicStandard = 2,          // 48Khz, 50kbps, mono, music
    MLAgoraAudioProfileMusicStandardStereo = 3,    // 48Khz, 50kbps, stereo, music
    MLAgoraAudioProfileMusicHighQuality = 4,       // 48Khz, 128kbps, mono, music
    MLAgoraAudioProfileMusicHighQualityStereo = 5, // 48Khz, 192kbps, stereo, music
};

typedef NS_ENUM(NSInteger, MLAgoraAudioScenario) {
    MLAgoraAudioScenarioDefault = 0,
    MLAgoraAudioScenarioChatRoomEntertainment = 1,
    MLAgoraAudioScenarioEducation = 2,
    MLAgoraAudioScenarioGameStreaming = 3,
    MLAgoraAudioScenarioShowRoom = 4,
    MLAgoraAudioScenarioChatRoomGaming = 5
};

typedef NS_ENUM(NSInteger, MLAgoraVideoStreamType) {
    MLAgoraVideoStreamTypeHigh = 0,
    MLAgoraVideoStreamTypeLow = 1,
};

typedef NS_ENUM(NSUInteger, MLAgoraVideoRenderMode)
{
    MLAgoraVideoRenderHidden     =  1,
    MLAgoraVideoRenderFit        =  2,
    MLAgoraVideoRenderAdaptive   =  3
};

//声网渲染布局
@interface MLAgoraRtcVideoCanvas : NSObject

@property (nonatomic, strong) UIView                    *view;
@property (nonatomic, assign) NSUInteger                uid;
@property (nonatomic, assign) MLAgoraVideoRenderMode    renderMode;

@end

//请确保每个参数配置正确
@interface MLAgoraConfiguration : NSObject

@property (nonatomic, assign) MLAgoraChannelProfile     channelProfile;             //通信模式，默认是1
@property (nonatomic, assign) MLAgoraRenderMode         localRenderMode;            //本地渲染模式，默认是1
@property (nonatomic, assign) MLAgoraOrientationMode    orientationMode;            //远端渲染模式，默认是0
@property (nonatomic, assign) MLAgoraClientRole         clientRole;                 //用户加入房间的角色，默认是1
@property (nonatomic, assign) MLAgoraAudioProfile       audioProfile;               //音频的音质级别，默认是0
@property (nonatomic, assign) MLAgoraAudioScenario      audioScenario;              //音频的使用场景，默认是0
@property (nonatomic, assign) int                       videoFrameWidth;            //视频的宽，默认352
@property (nonatomic, assign) int                       videoFrameHeight;           //视频的高，默认640
@property (nonatomic, assign) int                       videoFrameRate;             //视频的帧率,默认15帧
@property (nonatomic, assign) int                       videoFrameBitrate;          //视频的码率,默认500kbps
@property (nonatomic, assign) int                       initVideoFrameBitrate;      //启动码率,默认0不使用

@property (nonatomic, assign) BOOL                      enableManagerView;          //是否管理远端小窗，默认是NO
@property (nonatomic, assign) BOOL                      enableVideo;                //是否启动视频，默认是YES
@property (nonatomic, assign) BOOL                      enableVideoQuality;         //视频流畅度，默认是NO
@property (nonatomic, assign) BOOL                      enableHardwareDecode;       //是否使用硬解码，默认是YES
//当前只有声网支持这个设置，vpio的话，没有回声问题，音质会略差；remoteio音质会好，但是主播不带耳机可能会有回声问题。这两个是互斥的
@property (nonatomic, assign) BOOL                      useRemoteio;                //使用remoteio，默认是NO
@property (nonatomic, assign) BOOL                      useVpio;                    //使用vpio，默认是YES
@property (nonatomic, assign) BOOL                      enableFastHeadsetMonitor;   //开启监听插入耳机使用Remoteio，否则使用Vpio，默认是NO
@property (nonatomic, assign) BOOL                      useAudioScenario;           //默认是NO
@property (nonatomic, assign) BOOL                      keepAudioSession;           //默认是YES
@property (nonatomic, assign) BOOL                      nonAudioMixable;            //默认是NO
@property (nonatomic, assign) BOOL                      enableSpeakerPhone;         //进入频道前设置是否外放，默认是YES
@property (nonatomic, assign) BOOL                      useExternalVideo;           //是否使用外部视频，不使用声网视频采集，默认是YES
@property (nonatomic, assign) BOOL                      useAgoraEnhance;            //是否使用声网美颜，默认是NO

@property (nonatomic, assign) NSUInteger                 minBitrate;                //动态码率最低码率 kbps

@property (nonatomic, strong) NSString                  *logFilePath;               //日志写入完整地址，默认为nil
@property (nonatomic, assign) NSInteger                 logFilter;                  //日志写入级别，默认是0

@property (nonatomic, readonly) NSMutableDictionary     *dict;                      //初始化记录。
@end

