//
//  MLAgoraVideoFrameObserver.hpp
//  MomoChat
//
//  Created by wangqiangqiang on 2016/11/15.
//  Copyright © 2016年 wemomo.com. All rights reserved.
//

#ifndef MLAgoraVideoFrameObserver_hpp
#define MLAgoraVideoFrameObserver_hpp

#import <AgoraRtcEngineKit/IAgoraMediaEngine.h>
#import <AgoraRtcEngineKit/IAgoraRtcEngine.h>

class MLAgoraVideoFrameObserver : public agora::media::IVideoFrameObserver
{
public:
    MLAgoraVideoFrameObserver(id data, bool isHost = false);
    ~MLAgoraVideoFrameObserver();
    virtual bool onCaptureVideoFrame(VideoFrame& videoFrame);
    virtual bool onRenderVideoFrame(unsigned int uid, VideoFrame& videoFrame);
private:
    bool isHost_;
    __weak id data_;
};

#endif /* MLAgoraVideoFrameObserver_hpp */
