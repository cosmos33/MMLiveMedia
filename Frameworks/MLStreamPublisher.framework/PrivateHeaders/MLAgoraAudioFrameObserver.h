//
//  MLAgoraAudioFrameObserver.hpp
//  MomoChat
//
//  Created by wangqiangqiang on 2016/11/15.
//  Copyright © 2016年 wemomo.com. All rights reserved.
//

#ifndef MLAgoraAudioFrameObserver_hpp
#define MLAgoraAudioFrameObserver_hpp

#import <AgoraRtcKit/IAgoraMediaEngine.h>
#import <AgoraRtcKit/IAgoraRtcEngine.h>
#import <AgoraRtcKit/AgoraMediaBase.h>
#import <pthread.h>
#import "MomoConstructConfig.h"

using namespace agora;
using namespace agora::media;
@class MLAudioProcess;
@class MLSabineAudioEffect;
@class MLAudioProcessCacher;
@class MLPCMBuffer;
@class MLSoxAudioEffect;

class MLAgoraAudioFrameObserver : public agora::media::IAudioFrameObserver
{
public:
    MLAgoraAudioFrameObserver(id data, bool isHost = false);
    ~MLAgoraAudioFrameObserver();
    virtual bool onRecordAudioFrame(const char* channelId, AudioFrame& audioFrame);
    virtual bool onPlaybackAudioFrame(const char* channelId, AudioFrame& audioFrame);
    virtual bool onMixedAudioFrame(const char* channelId, AudioFrame& audioFrame);
    virtual bool onPlaybackAudioFrameBeforeMixing(const char* channelId, rtc::uid_t uid, AudioFrame& audioFrame);
    virtual int getObservedAudioFramePosition();
    virtual AudioParams getPlaybackAudioParams();
    virtual AudioParams getRecordAudioParams();
    virtual AudioParams getMixedAudioParams();

    void needSend(bool enable);
    
    // Audio process
    void setEQ(int eq);
    void setPitchShift(int pitchShift);
    void setAEFilter(int aeFilter);
    // Audio process
    void updateAudioLoopback(bool enable);
    // sabine process
    void initSabineAudioEffect(bool enable, int sampleRate, int channel);
    void setSabineAudioEffect(int type, int index, float value);
    void setSabineAudioEffectToDefault();
    //音效处理新接口
    void setAudioEffectAns(float inValue);
    void setAudioEffectReverb(int index, float inValue);
    void setAudioEffectPeqFliter(int inBand, float inFc, int onOff);
    void setAudioEffectPeqShelving(int inBand, float inFc, float inGain);
    void setAudioEffectPeqPeak(int inBand, float inFc, float inQ, float inGain);
    void pushOutsideAudioBuffer(MLPCMBuffer *audioBuffer, float maVolume, float exVolume);
    void setObserverEnable(bool enable);
    void cleanAllOutsideAudioFrame();
    //设置远端声音大小接口
    //volumeScale 为1则为取消设置用户音频。
    void setAdjustRemoteUser(unsigned int uid, float volumeScale);
    void setEarVolume(float volume);
    void initSoxAudioEffect(int sampleRate, int channel);
    void setSoxAudioCategory(int category);
protected:
    void copyAudioFrame(uint8_t* &audioBuffer, int& audioBufferSize, agora::media::IAudioFrameObserver::AudioFrame& audioFrame);
    
private:
    bool isHost_;
    __weak id data_;
    float playbackMixAudioPts_;
    float recordAudioPts_;
    bool isSending_;
    uint8_t *recordAudioBuffer_;
    int recordAudioBufferSize_;
    uint8_t *playbackAudioBuffer_;
    int playbackAudioBufferSize_;
    pthread_mutex_t bufferMutex;
    pthread_mutex_t adjustMutex;
    
    // Audio process
    int valueEQ;
    int valuePitchShift;
    int valueAEFilter;
    int soxAudioCategory;
    MLAudioProcess *kAudioProcess;
    // Audio process
    bool isAudioLoopBack;
    NSMutableArray *recordAudioFrame;
    int recordSampleRate;
    int playbackSampleRate;
    MLSabineAudioEffect *sabineLookbackAudioEffect;
    MLAudioProcessCacher *audioProcessCacher;
    MLSoxAudioEffect* soxAudioEffect;
    bool isInitSabineAudioEffect;
    bool isEnableSoxCategory;
    NSMutableData *audioProcessData;
    NSMutableArray *outsideAudioFrame;
    bool audioObserverEnable;
    NSMutableArray *outsidePlaybackAudioFrame;
    //std::map<unsigned int, float> mapAudioRemoteUser;
    NSMutableDictionary *adjustRemoteUserDictionary;
    float earVolume;
    float masterVolume;
    float externalVolume;
};

#endif /* MLAgoraAudioFrameObserver_hpp */
