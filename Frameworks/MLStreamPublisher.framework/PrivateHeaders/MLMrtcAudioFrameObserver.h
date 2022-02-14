//
//  MLMrtcAudioFrameObserver.h
//  MLStreamPublisher
//
//  Created by zhangzd on 2019/4/3.
//
#ifndef MLMrtcAudioFrameObserver_h
#define MLMrtcAudioFrameObserver_h

#import <pthread.h>
#import <MomoRtcEngineKit/MMLiveRtcBase.h>
#import <MomoRtcEngineKit/MMLiveRtcEngineKit.h>

@class MLAudioProcess;
@class MLSabineAudioEffect;
@class MLAudioProcessCacher;
@class MLPCMBuffer;
@class MLSoxAudioEffect;

class MLMrtcAudioFrameObserver : public MMAudioFrameObserver
{
public:
    MLMrtcAudioFrameObserver( id data, bool isHost = false);
    ~MLMrtcAudioFrameObserver();
public:
    virtual bool onRecordAudioFrame(AudioFrame& audioFrame);
    virtual bool onPlaybackAudioFrame(AudioFrame& audioFrame);
    virtual bool onMixedAudioFrame(AudioFrame& audioFrame);
    virtual bool onPlaybackAudioFrameBeforeMixing(unsigned int uid, AudioFrame& audioFrame) ;
public:
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
    void setAudioMicVolume(float volume);
protected:
    void copyAudioFrame(uint8_t* &audioBuffer, int& audioBufferSize, AudioFrame& audioFrame);
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
    float audioMicVolume;
    float masterVolume;
    float externalVolume;
};

#endif /* MLMrtcAudioFrameObserver_h */
