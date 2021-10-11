//
//  MLPublisherStatistics.h
//  MomoChat
//
//  Created by YuAo on 9/27/16.
//  Copyright © 2016 wemomo.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MLVideoCodecType.h"
#import "MLMediaAPI.h"
#import "MLConferencePublisherRole.h"
#import "MLPublisherError.h"
#import "MLPublisherOptions.h"
#import "MLPublisherDefine.h"
#import "MMLiveContext.h"

@class FFRtmpWriter;


typedef NS_ENUM(NSInteger, MLPublisherIdentifyReportType) {
    MLPublisherIdentifyReportTypeEvent = 0,
    MLPublisherIdentifyReportTypeWatch,
};

typedef NS_ENUM(NSInteger, MLPublisherMMRTCMsgType) {
    MMRTCMsgTypeUnKown = 0,
    MMRTCMsgTypePushStart,
    MMRTCMsgTypePushWatch,
    MMRTCMsgTypePullWatch,
    MMRTCMsgTypePushStop,
    MMRTCMsgTypeReconnect,

    MMRTCMsgTypeLogin = 6,
    MMRTCMsgTypeOnLogin,
    MMRTCMsgTypeHeart,
    MMRTCMsgTypeJoin,
    MMRTCMsgTypeOnJoin,
    MMRTCMsgTypeLeave = 11,
    MMRTCMsgTypeOnLeave,
    MMRTCMsgTypePeerJoin,
    MMRTCMsgTypePeerLeave,
    MMRTCMsgTypeAddUrl,
    MMRTCMsgTypeRemoveUrl = 16,
    MMRTCMsgTypeTranscoding,
    MMRTCMsgTypeLocalAudioMute,
    MMRTCMsgTypeRemoteAudioMute,
    MMRTCMsgTypeLocalVideoMute,
    MMRTCMsgTypeRemoteVideoMute = 21,
    MMRTCMsgTypeReJoin,
    MMRTCMsgTypeOnReJoin,
    MMRTCMsgTypeStartPK,
    MMRTCMsgTypeOnStartPK = 25,
    MMRTCMsgTypeStopPK,
    MMRTCMsgTypeOnStopPK,
    MMRTCMsgTypePeerLost,
    MMRTCMsgTypeKeyExpired,
    MMRTCMsgTypeKeyUpdate,
    MMRTCMsgTypeChangeRole,
    MMRTCMsgTypeOnChangeRole = 32,
    MMRTCMsgTypeOnKicked,
};

@interface MLPublisherStatisticOptions : NSObject

@property (nonatomic,copy) NSString *roomID;
@property (nonatomic) int provider;
@property (nonatomic) uint64_t sessionTime;
@property (nonatomic) NSTimeInterval packageCollectionInterval;
@property (nonatomic) NSInteger reportPackageCountThreshold;
@property (nonatomic) NSString *publisherType;
@property (nonatomic) MLPublisherIdentify publisherIdentify;
@property (nonatomic,copy) NSString *serviceType;
@property (nonatomic) NSString *userID;
@property (nonatomic,copy) NSString * sessionId;
@property (nonatomic) int system_fps;
@property (nonatomic) int useMediaLog;
@property (nonatomic, assign) NSInteger businessType;
@property (nonatomic, assign) NSInteger avFlag;
@end

@protocol MLPublisherStatisticAuxiliaryDataProvider <NSObject>

- (size_t)writerSentDataSize;

- (size_t)writerMuxDataSize;

- (uint64_t)writerCachedDataDuration;

@optional

- (uint64_t)writerFirstDTSTimestamp;

- (uint64_t)writerLastDTSTimestamp;


- (uint64_t)writerSentVideoFrameRate;

- (uint64_t)writerSentVideoBitrate; //Kb

- (uint64_t)writerSentAudioBitrate; //Kb

- (uint64_t)writerVideoFreezeCount;

- (NSInteger) roomType;

- (NSInteger) roomMode;

- (size_t)readerRecvDataSize;

- (size_t)readerRecvAudioDataSize;

- (size_t)readerRecvVideoDataSize;

- (NSString *)getLianmaiDetailData;

- (size_t)readerRecvAudioLostTimeInMs;

- (size_t)readerVideoRenderCount;

- (NSString *)getUpdatedLiveAPIDomain:(MLMediaDomainTable)domainType;

- (int32_t)getGOPDuration;

- (CGSize)getCaptureSize;

- (BOOL)getVideoMuteStatus;

- (BOOL)getAudioMuteStatus;

- (long)getJoinChannelDuration;

- (long)getFirstAudioRenderTime;

- (int)getVideoEncodeType;

- (long)getAudioTotalPlaylag;

- (NSString *)getServerIP;

- (NSString *)getSDKVersion;

- (uint64_t)writerUserSetVideoBitrate;

- (uint64_t)writerUserSetAudioBitrate;

- (int)writerAudioMicVolume;

- (size_t)writerSentAudioSize;

- (size_t)writerSentVideoSize;

- (size_t)writerAudioEncodeSize; //声网/微辣/腾讯使用此接口获取，ijk实现此接口会导致错误

- (int)getRtpStatus;

- (uint64_t)writeraudioDynamicBitrate;

- (int)getUdpLinkStatus;

- (NSString*)getPublisherType;

- (NSString *)getObjectDetectInfo;

- (int)getObjectWebViewInfo;

- (BOOL)getChannelKeyStatus;

- (int)writerAudioSendDuration;

- (CGPoint)getUserLocation;

- (NSString*)getCDNPullUrl;

- (int)publisherRenderApi;

@end

@class MLPublisherStatistic;

@protocol MLPublisherStatisticDelegate <NSObject>

@optional
- (void)publisherStatisticSentDataAbnormal:(MLPublisherStatistic *)statistic;
//only weila use
- (void)publisherStatisticAudioCaptureAbnormal:(MLPublisherStatistic *)statistic;
- (void)publisherStatisticUploadLogSuccess:(MLPublisherStatistic *)statistic;
- (void)publisherStatisticUploadLogFailed:(MLPublisherStatistic *)statistic;
- (void)publisherStatisticCheckEncoderStatus:(int)encodeFps input:(int)inputFps interval:(NSTimeInterval)interval;
- (void)publisherStatisticPushWatchStatus:(MLPublisherStatistic *)statistic body:(NSString*)body;
- (void)publisherStatisticMediaWatch:(MLPublisherStatistic *)statistic param:(NSMutableDictionary*)aParam;

@end

@interface MLPublisherStatistic : NSObject

@property (atomic, strong,readonly) id<MLMediaAPI> mediaAPI;
@property (atomic, strong,readonly) id<MLMediaAPI> logAdaptor;
@property (nonatomic, strong) MMLiveUserContext *userContext;

@property (nonatomic,weak) id<MLPublisherStatisticDelegate> delegate;

+ (void)registerMediaAPIClass:(Class<MLMediaAPI>)apiClass;
+ (void)registerLogAdaptorClass:(Class<MLMediaAPI>)logAdaptorClass;

- (instancetype)initWithOptions:(MLPublisherStatisticOptions *)options;

@property (nonatomic,readonly) BOOL didSendPushStartStatistic;

@property (nonatomic,readonly) BOOL didEncodeAudioAndVideoFrame;

@property (nonatomic) BOOL didPushSuccess;

@property (nonatomic) BOOL watchEventsEnabled;

@property (atomic,copy) NSString *publisherType;

@property (nonatomic, assign) int publisherErrorNo; // 推流错误码

@property (atomic,weak) id<MLPublisherStatisticAuxiliaryDataProvider> auxiliaryDataProvider;

- (void)markCapturedVideoFrame;

- (void)markCapturedVideoSize:(CGSize)videoSize;
- (void)updateEncodeVideoSize:(CGSize)videoSize;

- (void)markEncodedVideoFrameWithDataSize:(size_t)size;
- (void)markEncodedVideoFrameWithTotalDataSize:(size_t)size encodeCount:(size_t)encodeCount;
- (void)markCapturedAudioFrameWithSampleSize:(size_t)size;
- (void)markCapturedAudioFrameWithTotalSize:(size_t)size;//记录音频累计采集大小,现在只有腾讯使用
- (void)markEncodedAudioFrameWithDataSize:(size_t)size;
- (void)markEncodedAudioFrameWithTotalSize:(size_t)size;

- (void)markFaceDetectionFinishedWithDuration:(NSTimeInterval)duration;
- (void)markCPUVideoProcessingFinishedWithDuration:(NSTimeInterval)duration;
- (void)markGPUVideoProcessingFinishedWithDuration:(NSTimeInterval)duration;
- (void)markBodyDetectFinishedWithDuration:(NSTimeInterval)duration;
- (void)markExpressDetectFinishedWithDuration:(NSTimeInterval)duration;
- (void)markObjDetectFinishedWithDuration:(NSTimeInterval)duration;
- (void)markimageSegFinishedWithDuration:(NSTimeInterval)duration;
- (void)markValueSmoothing:(float)smoothing;
- (void)markValueWhiten:(float)whiten;
- (void)markValueBigEye:(float)bigEye;
- (void)markValueThinFace:(float)thinFace;
- (void)markValueUseDoki:(BOOL)useDoki;
- (void)markValueUseFaceCount:(NSInteger)faceCount;
- (void)markValueIOS:(float)ISO;
- (void)markValueFaceRect:(CGRect)faceRect;
- (void)markValuefocusPoint:(CGPoint)focusPoint;
- (void)markValueExposurePoint:(CGPoint)exposurePoint;
- (void)markValueLutName:(NSString *)lutName;
-(void)markValueCameraParams:(NSString *)cameraParams;
- (void)markValueEulerAngles:(NSArray *)eulerAngles;
- (void)markValueMetalProcessingInterval:(NSInteger)metalProcessingInterval;
- (void)markValueLutIntensity:(float)lutIntensity;

- (void)updateLocalDNS:(NSString *)localDNS;
- (void)useV3LogType:(BOOL)useV3Type andUserRole:(int)userRole;

- (void)sendPushStartStatisticWithStreamWriter:(FFRtmpWriter *)writer
                                     codecType:(MLVideoCodecType)codecType
                                    publishURL:(NSURL *)publishURL
                         auxiliaryDataProvider:(id<MLPublisherStatisticAuxiliaryDataProvider>)auxiliaryDataProvider
                              withCDNVideoSize:(CGSize)CDNVideoSize;

- (void)sendPushStartStatisticWithConferenceServer:(NSString *)conferenceServer
                                    conferenceRole:(MLConferencePublisherRole)conferenceRole
                                         codecType:(MLVideoCodecType)codecType
                                        publishURL:(NSURL *)publishURL
                             auxiliaryDataProvider:(id<MLPublisherStatisticAuxiliaryDataProvider>)auxiliaryDataProvider
                                  withCDNVideoSize:(CGSize)CDNVideoSize;

- (void)sendPushStartStatisticWithAgoraSessionID:(NSString *)sessionID
                                  conferenceRole:(MLConferencePublisherRole)conferenceRole
                                      publishURL:(NSURL *)publishURL
                             auxiliaryDataProvider:(id<MLPublisherStatisticAuxiliaryDataProvider>)auxiliaryDataProvider
                                withCDNVideoSize:(CGSize)CDNVideoSize;

- (void)sendV3PushStartStatisticWithConferenceRole:(MLConferencePublisherRole)conferenceRole
                                        publishURL:(NSURL *)publishURL
                             auxiliaryDataProvider:(id<MLPublisherStatisticAuxiliaryDataProvider>)auxiliaryDataProvider
                                  withCDNVideoSize:(CGSize)CDNVideoSize;

- (void)sendV3PullStartStatisticWithAuxiliaryDataProvider:(id<MLPublisherStatisticAuxiliaryDataProvider>)auxiliaryDataProvider;

- (void)sendPushStopStatisticWithErrorCode:(MLPublisherError)errorCode
                                publishURL:(NSURL *)publishURL
                              publishCDNIP:(NSString *)cdnIP;

- (void)sendV3PushStopStatisticWithErrorCode:(MLPublisherError)errorCode
                                  publishURL:(NSURL *)publishURL;

- (void)sendV3PullStopStatisticWithErrorCode:(MLPublisherError)errorCode;

- (void)sendStartAdjustingBitrateStatistic;
- (void)sendStopAdjustingBitrateStatistic;

- (void)sendConferenceStartStatisticWithRole:(MLConferencePublisherRole)role
                                  withUserID:(NSInteger)userID;
- (void)sendConferenceStopStatisticWithErrorCode:(NSInteger)errorCode
                                  totalBytesSend:(size_t)send
                              totalBytesReceived:(size_t)received
                                      withUserID:(NSInteger)userID;

- (void)sendConfRenderStartStatisticWithUserID:(long long)userID;
- (void)sendConfRenderStopStatisticWithUserID:(long long)userID reason:(int)reason;

- (void)sendPushStartStatisticWithLiveAid:(NSString *)staticsInfo;
- (void)sendPushWatchStatisticWithLiveAid:(NSArray *)staticsInfos;
- (void)sendPushStopStatisticWithLiveAidErrorCode:(MLPublisherError)errorCode;

- (void)sendPushBitrateChangeStatisticWithBitrate:(NSInteger)newBitrate;

- (BOOL)buffering;
- (void)sendBufferStartStatisticWithBufferDuration:(uint64_t)bufferDuration;
- (void)sendBufferStopStatistic;

- (void)sendDropStartStatisticWithVideoCache:(int32_t)vCache
                             withVideoPacket:(int32_t)vPacket
                              withAudioCache:(int32_t)aCache
                             withAudioPacket:(int32_t)aPacket;
- (void)sendDropStopStatisticWithVideoCache:(int32_t)vCache
                            withVideoPacket:(int32_t)vPacket
                             withAudioCache:(int32_t)aCache
                            withAudioPacket:(int32_t)aPacket
                         withDropVideoCount:(int32_t)dropVideoCount;

- (void)sendLevelChangeStatisticWithVideoCache:(int32_t)vCache
                               withVideoPacket:(int32_t)vPacket
                                withAudioCache:(int32_t)aCache
                               withAudioPacket:(int32_t)aPacket
                               withLevelChange:(NSString *)levelChange
                                  withNewWidth:(int32_t)newWidth
                                 withNewHeight:(int32_t)newHeight
                                withNewBitrate:(int32_t)newBitrate
                               withRealBitrate:(int32_t)realBitrate
                                withCurBitrate:(int32_t)curBitrate
                              withNewFramerate:(int32_t)newFramerate;

- (void)sendNetworkWarningStatisticWithVideoCache:(int32_t)vCache
                                  withVideoPacket:(int32_t)vPacket
                                   withAudioCache:(int32_t)aCache
                                  withAudioPacket:(int32_t)aPacket;

- (void)sendFocusStatisticWithAutoMode:(int32_t)autoMode
                               withPos:(CGPoint)pos;

- (void)sendDropStatisticWithCache:(int32_t)lastDuration
                             cache:(int32_t)curDuration
                         audioDrop:(int32_t)aPackets
                         videoDrop:(int32_t)vPackets;

- (void)sendRestartStatisticWithNewUrl:(NSURL *)newUrl
                                oldUrl:(NSURL *)oldUrl;

- (void)pause;
- (void)resume;

// Get push statistics(cpu/mem/delay...) dictionary
- (NSDictionary *)getPushWatchStatistic;
- (void)setSystem_fps:(int)system_fps;
- (size_t)getWriterSentDataSize;//获取发送数据的总量

- (void)sendMomoRtcPushStartWithContent:(NSString *)content;
- (void)sendMomoRtcPushWatchWithContent:(NSString *)content;
- (void)sendMomoRtcPullWatchWithContent:(NSString *)content;
- (void)sendMomoRtcPushStopWithContent:(NSString *)content;
- (void)sendMomoRtcReConnectWithContent:(NSString *)content;
- (void)sendMomoRtcMsgWithContent:(MLPublisherMMRTCMsgType)type content:(NSString *)content;
- (void)postRequestWithParam:(NSString*)requestUrl
                  dynamicKey:(NSString *)dynamicKey
                   channelID:(NSString *)channelID
                       appID:(NSString*)appID
                      target:(id)aTarget
                          ok:(void (^)(NSDictionary *result))okBlock
                        fail:(void (^)(NSDictionary *result))failBlock
                         err:(void (^)(NSError *error))errBlock;

- (void) setSentLogFilter:(NSUInteger)sentLogFilter;
- (void) setSentMrtcLogFilter:(NSUInteger)sentMrtcLogFilter;

- (void)setRoomID:(NSString *)roomID;
- (void)setUserId:(NSString *)userId;
- (void)setBusinessType:(NSInteger)businessType;
- (void)setAvFlag:(NSInteger)avFlag;
- (void)setSendDataAbnormalWarning:(int)sendDataAbnormalWarning;
@end


@interface MLPublisherSendSpeedUpdater : NSObject

- (void)startUpdateWithDataProvider:(id<MLPublisherStatisticAuxiliaryDataProvider>)dataProvider callback:(void (^)(size_t sentBytesPerSecond, NSString *description))callback;

- (void)stopUpdate;

@end
