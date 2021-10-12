//
//  MLAgoraMetadataObserver.h
//  MLStreamPublisher
//
//  Created by MOMO on 2020/1/16.
//

#ifndef MLAgoraMetadataObserver_h
#define MLAgoraMetadataObserver_h

#import <AgoraRtcEngineKit/IAgoraMediaEngine.h>
#import <AgoraRtcEngineKit/IAgoraRtcEngine.h>

class MLAgoraMetadataObserver : public agora::rtc::IMetadataObserver
{
public:
    MLAgoraMetadataObserver(id data, unsigned int uid);
    ~MLAgoraMetadataObserver();
    virtual int getMaxMetadataSize();
    virtual bool onReadyToSendMetadata(Metadata &metadata);
    virtual void onMetadataReceived(const Metadata &metadata);
    
private:
     __weak id _data;
    unsigned int _uid;
    char _buffer[1024];
};



#endif /* MLAgoraMetadataObserver_h */
