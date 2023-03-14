//
//  FFRtmpWriter.h

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
typedef enum _RTMPAudioProfile{
    RTMP_AAC_LC_Profile = 0,
    RTMP_AAC_HE_Profile,
    RTMP_AAC_HE_v2_Profile
}RTMPAudioProfile;

typedef struct send_history{
    int bytes_input;
    int bytes_output;
    int bytes_dropped;
    int audio_bytes_output;
    int video_send_fps;
    int64_t start_timeMs;
    int64_t durationMs;
}send_history;


@protocol FFRtmpWriterDelegate <NSObject>
- (void) writeFailedWithError:(NSError*)error;
- (void) writeDropPacketsWithCache:(int32_t)lastDuration cache:(int32_t)curDuration audioDrop:(int32_t)aPackets videoDrop:(int32_t)vPackets;
- (void) netwowkSendTooSlow:(int64_t)elapsedTimeMs;
@end

@interface FFRtmpWriter : NSObject

@property (nonatomic, copy) NSString *uuid;
@property (nonatomic) dispatch_queue_t conversionQueue;
@property (nonatomic, strong, readonly) NSString *streamPath;
@property(nonatomic, weak) id<FFRtmpWriterDelegate> delegate;
@property(nonatomic) BOOL isEnableDynamicBitrate;
@property(nonatomic, assign) BOOL isRealtimeSend;
//丢帧逻辑
@property(nonatomic, assign) BOOL dropPacketFlag;
@property(nonatomic, assign) int32_t cacheWarning;
@property(nonatomic, assign) int32_t cacheNormal;
@property(nonatomic, assign) BOOL enableFLVDynamicUpdateParams;


- (instancetype) initWithStreamPath:(NSString *)path serverTime:(int64_t)serverTime;

- (void) addVideoStreamWithWidth:(int)width height:(int)height bitrate:(int)vBitrate;
- (void) addVideoStreamWithWidth:(int)width height:(int)height bitrate:(int)vBitrate useHevc:(BOOL)enable;
- (void) addAudioStreamWithSampleRate:(int)sampleRate channels:(int)channelNum bitrate:(int)aBitrate;
- (void) addAudioStreamWithSampleRate:(int)sampleRate channels:(int)channelNum bitrate:(int)aBitrate profile:(RTMPAudioProfile)profile;
- (void) setAudioSpecificConfig:(NSData*)data;

- (BOOL) prepareForWriting:(NSError**)error;

- (void) processEncodedData:(NSData*)data presentationTimestamp:(CMTime)pts streamIndex:(NSUInteger)streamIndex isKeyFrame:(BOOL)isKeyFrame; // TODO refactor this

- (void) processEncodedData:(NSData*)data
      presentationTimestamp:(CMTime)pts
            decodeTimestamp:(CMTime)dts
                streamIndex:(NSUInteger)streamIndex
                 isKeyFrame:(BOOL)isKeyFrame;

- (void) processEncodedData:(NSData*)data
      presentationTimestamp:(CMTime)pts
            decodeTimestamp:(CMTime)dts
                streamIndex:(NSUInteger)streamIndex
                 isKeyFrame:(BOOL)isKeyFrame
                      width:(int)width
                     height:(int)height;

- (BOOL) finishWriting:(NSError**)error;
-(void)setVideoExtradata:(NSData *) extradata;
- (void)setVideoOpenGop:(BOOL)videoOpenGop;
-(int)videoStreamIdx;
-(int)audioStreamIdx;
- (NSString*)getIpAddr;
- (long)getMuxSize;
- (long)getSendSize;
- (uint64_t)getTcpConnectTime;
- (uint64_t)getSendDataTime;

- (int32_t)getCacheDurationInMs;
- (int32_t)getAudioCacheDurationInMs;
- (int32_t)getVideoCachePacket;
- (int32_t)getAudioCachePacket;
- (long) getBufferLen;

- (uint64_t)getFirstDtsInMs;
- (uint64_t)getLatestDtsInMs;
- (uint64_t)getTotalSendOutBytes;
- (uint64_t)getTotalVideoSendInBytes;
- (uint64_t)getTotalAudioSendInBytes;

- (int)getAudioSendDuration;
- (int)getVideoSentPackets;
- (send_history *)getHistoryInfo;
- (NSUInteger)getPacketQueueCount;
- (int64_t)getInputTotalBytes;

@end
