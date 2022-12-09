//
//  MLAgoraVideoFrameObserver.hpp
//  MomoChat
//
//  Created by wangqiangqiang on 2016/11/15.
//  Copyright © 2016年 wemomo.com. All rights reserved.
//

#ifndef MLAgoraVideoFrameObserver_hpp
#define MLAgoraVideoFrameObserver_hpp

#import <AgoraRtcKit/IAgoraMediaEngine.h>
#import <AgoraRtcKit/IAgoraRtcEngine.h>
using namespace agora;

class MLAgoraVideoFrameObserver : public agora::media::IVideoFrameObserver
{
public:
    MLAgoraVideoFrameObserver(id data, bool isHost = false);
    ~MLAgoraVideoFrameObserver();
    virtual bool onCaptureVideoFrame(VideoFrame& videoFrame);
    virtual bool onPreEncodeVideoFrame(VideoFrame& videoFrame);
    virtual bool onSecondaryCameraCaptureVideoFrame(VideoFrame& videoFrame);
    virtual bool onSecondaryPreEncodeCameraVideoFrame(VideoFrame& videoFrame);
    virtual bool onScreenCaptureVideoFrame(VideoFrame& videoFrame);
    virtual bool onPreEncodeScreenVideoFrame(VideoFrame& videoFrame);
    virtual bool onMediaPlayerVideoFrame(VideoFrame& videoFrame, int mediaPlayerId);
    virtual bool onSecondaryScreenCaptureVideoFrame(VideoFrame& videoFrame);
    virtual bool onSecondaryPreEncodeScreenVideoFrame(VideoFrame& videoFrame);
    virtual bool onRenderVideoFrame(const char* channelId, rtc::uid_t remoteUid, VideoFrame& videoFrame);
    virtual bool onTranscodedVideoFrame(VideoFrame& videoFrame);
    
private:
    bool isHost_;
    __weak id data_;
};

#endif /* MLAgoraVideoFrameObserver_hpp */
