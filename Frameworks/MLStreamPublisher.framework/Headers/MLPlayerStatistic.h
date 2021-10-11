//
//  MLPlayerStatistic.h
//  MomoChat
//
//  Created by YuAo on 10/9/16.
//  Copyright © 2016 wemomo.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <IJKMedia/IJKMedia.h>
#import "MLMediaAPI.h"
#import "MLMediaCommonDefine.h"
#import "MMLiveContext.h"

//@import IJKMedia;
@protocol MLPlayerStatisticDataProvider;

typedef NS_ENUM(NSInteger, MLPlayerIdentify) {
    MLPlayerIdentifyLive = 0,
    MLPlayerIdentifyVod,
};
typedef NS_ENUM(NSInteger, MLPlayerIdentifyReportType) {
    MLPlayerIdentifyReportTypeEvent = 0,
    MLPlayerIdentifyReportTypeWatch,
};

@protocol MLPlayerStatisticDomainProvider <NSObject>

- (NSString *)getUpdatedLiveAPIWithDomainType:(MLMediaDomainTable)domainType;

@end
@interface MLPlayerStatisticOptions : NSObject

@property (nonatomic,copy) NSString *roomID;
@property (nonatomic) int provider;
@property (nonatomic) int businessType;

@property (nonatomic) uint64_t sessionTime;

@property (nonatomic) NSTimeInterval packageCollectionInterval;
@property (nonatomic) NSInteger reportPackageCountThreshold;
@property (nonatomic) int system_fps;

@property (nonatomic) MLPlayerIdentify playerIdentify;
@property (nonatomic) BOOL useMediaLog;

@property (nonatomic, weak, readwrite) id<MLPlayerStatisticDomainProvider> delegate; // 委托

@property (nonatomic, weak, readwrite) id<MLPlayerStatisticDataProvider> dataProvider;
@end

@protocol MLPlayerStatisticDataProvider <NSObject>

- (size_t)playerReceivedDataSize;

- (size_t)playerAudioReceivedSize;
- (size_t)playerVideoReceivedSize;
- (size_t)playerVideoDecodedCount;
- (size_t)playerAudioDecodedSize;
- (size_t)playerVideoRenderedCount;
- (size_t)playerAudioRenderedSize;

- (size_t)playerVideoCacheDuration;
- (size_t)playerAudioCacheDuration;

- (size_t)playerReceivedAudioBitrate;
- (size_t)playerReceivedVideoBitrate;
- (size_t)playerVideoFrameRate;

- (uint64_t)playerPlaybackDelay;
- (uint64_t)playerAudioSampleRate;

- (float)playerSpeedRate;
- (CGSize)playerVideoSize;

- (int)getObjectWebViewInfo;

- (NSString *)getPlayerCdnIp;

- (size_t)getAudioPacketDuration;
- (size_t)getAudioPacketLength;
- (BOOL)playerVideoCodecHevc;
- (CGPoint)getUserLocation;
- (int)playerRenderApi;
@end

@interface MLPlayerStatistic : NSObject

+ (uint64_t)currentTimestamp;

@property (atomic, strong,readonly) id<MLMediaAPI> mediaAPI;
@property (atomic, strong,readonly) id<MLMediaAPI> logAdaptor;
@property (nonatomic, strong) MMLiveUserContext *userContext;

@property (nonatomic) BOOL watchEventsEnabled;

@property (nonatomic, assign) int firstVideoReceivedTime;
@property (nonatomic, assign) int firstAudioReceivedTime;
@property (nonatomic, assign) int firstVideoDecodedTime;
@property (nonatomic, assign) int firstAudioDecodedTime;
@property (nonatomic, assign) int firstVideoRenderedTime;
@property (nonatomic, assign) int firstAudioRenderedTime;
@property (nonatomic, assign) int firstVideoCacheTime;
@property (nonatomic, assign) int firstAudioCacheTime;
@property (atomic,copy) NSString *proxyServerIp;
@property (atomic,weak) id<MLPlayerStatisticDomainProvider> delegate;


+ (void)registerMediaAPIClass:(Class<MLMediaAPI>)apiClass;
+ (void)registerLogAdaptorClass:(Class<MLMediaAPI>)logAdaptorClass;

- (instancetype)initWithOptions:(MLPlayerStatisticOptions *)options;
- (void)sendPlayPreparedStatisticWithReceivedDataSize:(size_t)size;
- (void)sendPlayInitStatisticWithURL:(NSURL *)URL;
- (void)sendHttpDetectorWithHttpDetector:(HttpDetecter *)httpDetecter httpReconnectTimes:(int)httpReconnectTimes;
- (void)sendSeekWithHttpDetector:(HttpDetecter *)httpDetecter httpReconnectTimes:(int)httpReconnectTimes;

- (void)sendPlayStartedStatisticWithURL:(NSURL *)URL
                          serverAddress:(NSString *)serverAddress
                 streamMetaReceivedTime:(uint64_t)streamMetaReceivedTime
                       tcpConnectedTime:(uint64_t)tcpConnectedTime
                 firstVideoReceivedTime:(uint64_t)firstVideoReceivedTime
                  firstVideoDecodedTime:(uint64_t)firstVideoDecodedTime
                 firstVideoRenderedTime:(uint64_t)firstVideoRenderedTime
                 firstAudioReceivedTime:(uint64_t)firstAudioReceivedTime
                  firstAudioDecodedTime:(uint64_t)firstAudioDecodedTime
                 firstAudioRenderedTime:(uint64_t)firstAudioRenderedTime
                            streamCount:(size_t)streamCount
                                 useVTB:(BOOL)useVTB
                                  cdnIp:(NSString *)cdnIp
                               clientIp:(NSString *)clientIp
                           dataProvider:(id<MLPlayerStatisticDataProvider>)dataProvider;
- (void)setPullStartSlot:(NSString *)pullStartSlot;
- (void)sentPullWatchLogs;
- (void)sentBufferStopLogs;
- (void)sendPlayStoppedStatisticWithReason:(NSInteger)reason
                                   playURL:(NSURL *)playURL
                                 playCDNIP:(NSString *)cdnIP
                                  stopTime:(uint64_t)stopTime
                        receivePacketCount:(uint64_t)receivePacketCount
                          decodeFrameCount:(uint64_t)decodeFrameCount
                                    isH265:(BOOL)isH265;

- (void)sendBufferStartStatistic:(int64_t*)cache;
- (void)sendBufferStopStatistic;

- (void)sendFastStartStatistic;
- (void)sendFastStopStatistic;

// Chase latency
- (void)sendDropFrameStartStatistic;
- (void)sendDropFrameStopStatistic;
- (void)sendBufferDropWithAudioCache:(NSInteger)preAudioCache videoCache:(NSInteger)preVideoCache;
// Chase latency end

- (NSDictionary *)getPullWatchStatistic;
- (void)updateLocalDNS:(NSString *)localDNS;
- (void)updateBusinessType:(int)businessType;
- (void)setLiveSource:(NSString*)source;

- (void)sendSecondaryStreamPlayStartedStatisticWithURL:(NSURL *)URL
                                         serverAddress:(NSString *)serverAddress
                                streamMetaReceivedTime:(uint64_t)streamMetaReceivedTime
                                      tcpConnectedTime:(uint64_t)tcpConnectedTime
                                firstVideoReceivedTime:(uint64_t)firstVideoReceivedTime
                                 firstVideoDecodedTime:(uint64_t)firstVideoDecodedTime
                                firstVideoRenderedTime:(uint64_t)firstVideoRenderedTime
                                firstAudioReceivedTime:(uint64_t)firstAudioReceivedTime
                                 firstAudioDecodedTime:(uint64_t)firstAudioDecodedTime
                                firstAudioRenderedTime:(uint64_t)firstAudioRenderedTime
                                           streamCount:(size_t)streamCount
                                              streamID:(NSString *)streamID
                                          dataProvider:(id<MLPlayerStatisticDataProvider>)dataProvider;
- (void)sendSecondaryStreamPlayStoppedStatisticWithReason:(NSInteger)reason streamID:(NSString *)streamID;

- (void)sendStreamToConferenceRefetchDurationStatisticWithDuration:(NSTimeInterval)duration;
- (void)sendStreamToConferenceRefetchFailedStatisticWithDuration:(NSTimeInterval)duration;
- (void)sendPlayerUpdateMaxBufferStatistic:(int)value;
- (void)updateTransferType:(NSInteger)transferType;
- (void)updateCdnIp:(NSString*)cdnip;
- (void)updateCurrentGop:(uint64_t)gop;
- (void)markErrSeiRenderCount;
- (void)markTotalReceiveSize:(size_t)receiveSize;
- (void)setSystem_fps:(int)system_fps;
@end
