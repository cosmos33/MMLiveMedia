//
//  MMLiveRtcBase.h
//  MomoLiveRoom
//
//  Created by chenyong on 2019/2/21.
//  Copyright © 2019年 momo. All rights reserved.
//

#ifndef MMLiveRtcBase_h
#define MMLiveRtcBase_h
#include <stdio.h>
#include <map>
#include <string>
#include <vector>
#define  TRANSINFO_LEN 2048


// network
typedef enum _MMLiveNetworkQuality{
    MMLiveNetworkQualityUnknown = 0,
    MMLiveNetworkQualityExcellent = 1,
    MMLiveNetworkQualityGood = 2,
    MMLiveNetworkQualityPoor = 3,
    MMLiveNetworkQualityBad = 4,
    MMLiveNetworkQualityVBad = 5,
    MMLiveNetworkQualityDown = 6,
}MMLiveNetworkQuality;


// video
typedef enum _MMLiveVideoStreamType{
    MMLiveVideoStreamTypeHigh = 0,
    MMliveVideoStreamTypeLow = 1,
}MMLiveVideoStreamType;


typedef enum _MMLiveVideoRemoteState{
    MMLiveVideoRemoteStateStopped = 0,
    MMLiveVideoRemoteStateRunning = 1,
    MMLiveVideoRemoteStateFrozen = 2,
}MMLiveVideoRemoteState;


typedef struct _MMLiveRtcRemoteVideoStats{
    uint32_t videoBitrate = 0;
    uint32_t videoFramerate = 0;
    uint64_t vReceiveSize = 0;
    uint64_t videoRenderCount = 0;
    int videowidth = 0;
    int videoheight = 0;
    
    int videoDelay = 0;
    float videoLost = 0;
    int videoPlayLag = 0;
    
    void *videoDelayEx = nullptr;
    
    bool videoMute = false;
} MMLiveRtcRemoteVideoStats;



typedef struct _MMLiveRtcRemoteAudioStats{
    
    uint32_t audioBitrate = 0;
    uint64_t aReceiveSize = 0;
    
    int audioDelay = 0;
    int audioLost = 0;
    bool audioMute = 0;

    int audioPlayLag = 0;
    // audio的缓冲
    int audioCache = 0;
    // expand的总数+empty的个数
    int expandCount = 0;
    //根据 连续N次DoExpand算法处理以后，每执行M次DoExpand算一次通道卡顿
    int expandCartonCount = 0;
    
    // 纯expand的总数
    int expandRealCount = 0;
    
} MMLiveRtcRemoteAudioStats;


typedef struct _MMLiveRtcRemoteStats{
    
    
    unsigned long uid = 0;;
    MMLiveRtcRemoteAudioStats audioStats;
    MMLiveRtcRemoteVideoStats videoStats;
    
} MMLiveRtcRemoteStats;


typedef struct _MMLiveRtcLocalVideoStats {
    
    int videoBitrate = 0;           //视频码率  编码
    int videoFramerate = 0;         //视频帧率
    uint32_t videowidth = 0;        //视频分辨率：宽
    uint32_t videoheight = 0;       //视频分辨率：高
    
    uint64_t vCaptureCount = 0;
    uint64_t vEncodeSize = 0;
    uint32_t vEncodeCount = 0;
    
    uint64_t vSendSize = 0;
    int64_t gopDuration = 0;
    
    int videoLost = 0;
    bool videoMute = false;
    
} MMLiveRtcLocalVideoStats;

typedef struct _MMLiveRtcLocalAudioStats{
    
    int64_t audioBitrate = 0;   //音频码率
    
    int64_t aCaptureSize = 0;
    uint64_t aEncodeSize = 0;
    int64_t aSendSize = 0;
    bool audioMute = false;
    int audioLost = 0;
    int64_t rtt_ms = 0;
    
    
} MMLiveRtcLocalAudioStats;



typedef struct _MMLiveChannelStats{

    _MMLiveChannelStats() {
        remoteStats.clear();
    }
    long txBytes = 0;
    long rxBytes = 0;
    
    long userCount = 0;
    
    std::string channelID = "";

    
    MMLiveRtcLocalVideoStats localVideoStats;
    MMLiveRtcLocalAudioStats localAudioStats;
    
    std::vector<MMLiveRtcRemoteStats> remoteStats;
    

} MMLiveChannelStats;


typedef  enum  _MMLiveClientRole{
    MMLiveRoleUnKnown = 0,
    MMLiveRoleBroadcaster = 1, //主播
    MMLiveRoleAudience = 2,//观众
}MMLiveClientRole;


typedef enum _MMLiveUserOfflineReason{
    MMLiveUserOfflineReasonQuit = 0,
    MMLiveUserOfflineReasonDropped = 1,
    MMLiveUserOfflineReasonBecomeAudience = 2,
}MMLiveUserOfflineReason;

typedef enum _MMLiveChannelProfile{
    MMLiveChannelProfileCommunication = 0,
    MMLiveChannelProfileLiveBroadcasting = 1,
    MMLiveChannelProfileGame = 2,
}MMLiveChannelProfile;

typedef enum _MMLiveMediaType{
    MMLiveMediaTypeNone = 0,
    MMLiveMediaTypeAudioOnly = 1,
    MMLiveMediaTypeVideoOnly = 2,
    MMLiveMediaTypeAudioAndVideo = 3,
}MMLiveMediaType;

typedef struct _MMLiveRtcAudioVolumeInfo{
    unsigned long uid;
    int8_t volume;
}MMLiveRtcAudioVolumeInfo;

typedef struct _MMLiveVideoEncoderConfiguration{
    int width;
    int height;
    int frameRate;
    int bitrate;
    int minbitrate;
    int orientationMode;
}MMLiveVideoEncoderConfiguration;

typedef enum _MMLiveVideoRenderMode{
    /**
     Hidden(1): If the video size is different than that of the display window, crops the borders of the video (if the video is bigger) or stretch the video (if the video is smaller) to fit it in the window.
     */
    MMLiveVideoRenderModeHidden = 1,
    
    /**
     MMLiveVideoRenderModeFit(2): If the video size is different than that of the display window, resizes the video proportionally to fit the window.
     */
    MMLiveVideoRenderModeFit = 2,
    
    /**
     MMLiveVideoRenderModeAdaptive(3)：If both callers use the same screen orientation, i.e., both use vertical screens or both use horizontal screens, the AgoraVideoRenderModeHidden mode applies; if they use different screen orientations, i.e., one vertical and one horizontal, the AgoraVideoRenderModeFit mode applies.
     */
    MMLiveVideoRenderModeAdaptive = 3,
}MMLiveVideoRenderMode;

typedef struct _MMLiveRtcVideoCanvas{
    unsigned long uid;
    void * _Nullable view;
    MMLiveVideoRenderMode renderMode;
}MMLiveRtcVideoCanvas;


typedef enum _MMLiveQualityLimitationReason{
    MMLiveLimitationReasonNone = 0,  // The bitrate and/or frame rate is not limited.
    MMLiveLimitationReasonBandwidth = 1,  // The bitrate and/or frame rate is primarily limited due to congestion cues during bandwidth estimation.
}MMLiveQualityLimitationReason;



typedef enum _MMLiveAudioProfile{
    MMLiveAudioProfileDefault = 0,
    MMLiveAudioProfileSpeechStandard = 1,
    MMLiveAudioProfileMusicStandard = 2,
    MMLiveAudioProfileMusicStandardStereo = 3,
    MMLiveAudioProfileMusicHighQuality = 4,
    MMLiveAudioProfileMusicHighQualityStereo = 5,
}MMLiveAudioProfile;

typedef enum _MMLiveVideoCodecProfileType{
    MMLiveVideoCodecProfileTypeBaseLine = 66,
    MMLiveVideoCodecProfileTypeMain = 77,
    MMLiveVideoCodecProfileTypeHigh = 100,
}MMLiveVideoCodecProfileType;

typedef struct _MMLiveVideoImage{
    _MMLiveVideoImage(){
        posx = 0;
        posy = 0;
        width = 0;
        height = 0;
    }
    std::string url;
    unsigned long posx;
    unsigned long posy;
    unsigned long width;
    unsigned long height;
}MMLiveVideoImage;

//目前只支持48000
typedef enum _MMLiveAudioSampleRateType{
    MMLiveAudioSampleRateType32000 = 32000,
    MMLiveAudioSampleRateType44100 = 44100,
    MMLiveAudioSampleRateType48000 = 48000,
}MMLiveAudioSampleRateType;

typedef struct _MMLiveTranscodingUser{
    unsigned long uid;
    double posx;
    double posy;
    double width;
    double height;
    int zOrder; //optional, [0, 100] //0 (default): bottom most, 100: top most
    double alpha;
    int aMute;
    int vMute;
}MMLiveTranscodingUser;

typedef struct _MMLiveTranscoding{
    _MMLiveTranscoding(){
        width = 540;
        height = 960;
        videoBitrate = 1000 * 1024;
        videoFramerate = 30;
        lowLatency = true;
        videoGop = 1;
        videoCodecProfile = MMLiveVideoCodecProfileTypeHigh;
        
        audioBitrate = 64 * 1024;
        audioChannels = 1;
        audioSampleRate = MMLiveAudioSampleRateType48000;
        
        watermark = NULL;
        backgroundImage = NULL;
        actived = true;
        memset(transcodingExtraInfo, 0, TRANSINFO_LEN);
    }
    
    double width;
    double height;
    int videoBitrate;
    int videoFramerate;
    bool lowLatency;
    bool actived;
    int videoGop;
    MMLiveVideoCodecProfileType  videoCodecProfile;
    
    int audioBitrate;
    int audioChannels;
    MMLiveAudioSampleRateType audioSampleRate;
    
    MMLiveVideoImage * _Nullable watermark;
    MMLiveVideoImage * _Nullable backgroundImage;
    
    std::map<unsigned long, MMLiveTranscodingUser> transcodingUserMap;
    char transcodingExtraInfo[TRANSINFO_LEN];
    std::string url;
    std::string channelid;
    std::string uid;
}MMLiveTranscoding;

#endif /* MMLiveRtcBase_h */
