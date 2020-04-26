//
//  MMLiveMediaEngine.h
//  MomoRtcEngineKit
//
//  Created by chenyong on 2019/3/13.
//  Copyright © 2019年 momo. All rights reserved.
//

#ifndef MMLiveMediaEngine_h
#define MMLiveMediaEngine_h
#include <string.h>
class MMAudioFrameObserver
{
public:
    enum AUDIO_FRAME_TYPE {
        FRAME_TYPE_PCM16 = 0,  //PCM 16bit little endian
    };
    struct AudioFrame {
        AUDIO_FRAME_TYPE type;
        int samples;  //number of samples in this frame
        int bytesPerSample;  //number of bytes per sample: 2 for PCM16
        int channels;  //number of channels (data are interleaved if stereo)
        int samplesPerSec;  //sampling rate
        void* buffer;  //data buffer
        int64_t renderTimeMs;
    };
public:
    virtual bool onRecordAudioFrame(AudioFrame& audioFrame) = 0;
    virtual bool onPlaybackAudioFrame(AudioFrame& audioFrame) = 0;
    virtual bool onMixedAudioFrame(AudioFrame& audioFrame) = 0;
    virtual bool onPlaybackAudioFrameBeforeMixing(unsigned int uid, AudioFrame& audioFrame) = 0;
};

class MMVideoFrameObserver
{
public:
  enum VIDEO_FRAME_TYPE {
    FRAME_TYPE_YUV420 = 0,  //YUV 420 format
  };
  struct VideoFrame {
    VIDEO_FRAME_TYPE type;
    int width;  //width of video frame
    int height;  //height of video frame
    int yStride;  //stride of Y data buffer
    int uStride;  //stride of U data buffer
    int vStride;  //stride of V data buffer
    void* yBuffer;  //Y data buffer
    void* uBuffer;  //U data buffer
    void* vBuffer;  //V data buffer
    int rotation; // rotation of this frame (0, 90, 180, 270)
    int64_t renderTimeMs;
  };
public:
  virtual bool onCaptureVideoFrame(VideoFrame& videoFrame) = 0;
  virtual bool onRenderVideoFrame(unsigned int uid, VideoFrame& videoFrame) = 0;
};

//class MMMediaEngine
//{
//public:
//    virtual void release() = 0;
//    virtual int registerAudioFrameObserver(MMAudioFrameObserver* observer) = 0;
////    virtual int registerVideoFrameObserver(IVideoFrameObserver* observer) = 0;
////    virtual int registerVideoRenderFactory(IExternalVideoRenderFactory* factory) = 0;
//    virtual int pushAudioFrame(MMAudioFrameObserver::AudioFrame *frame, bool wrap = false){ return -1; }
//};
#endif /* MMLiveMediaEngine_h */



