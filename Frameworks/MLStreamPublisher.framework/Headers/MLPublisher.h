#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <UIKit/UIKit.h>
#import <IJKMedia/IJKMedia.h>
#import "MLStreamMediaSource.h"
#import "MLMediaAPI.h"
#import "MLVideoCodecType.h"
#import "MLPublisherStatistic.h"
#import "MLPublisherOptions.h"
#import "MLPublisherError.h"
#import "MLAudioUnitController.h"
#import "MLServerTimeSynchronizer.h"
#import "MLPCMBuffer.h"
#import "MLPublisherCameraConfiguration.h"
#import "MLPublisherDefine.h"
#import "MLAudioEffectManager.h"
#import "MLMediaUtility.h"
#import "MLMediaLogger.h"
#import "MLAgoraConfiguration.h"
#import "MLMediaVideoRecorder.h"
#import "MLHCConfiguration.h"

FOUNDATION_EXPORT NSInteger const MLPublisherMaximumVideoCaptureFPS;

#define DELAY_FRAME_COUNT_TO_NOTIFY_PUBLISHER (30)
#define DELAY_TIME_TO_NOTIFY_PUBLISHER_RECEIVED_CDN (5)//预估数据到达cdn时间，单位S
#define MC_EFFECT  8
#define ELE_EFFECT  9
#define AEF_MUTE  11
#define MIN_RTMP_SEND_SZIE 1000 //1000字节
@class MLPublisher, FFRtmpWriter;
@class MLPublisherRemoteDisplay;
@class MLMediaViewController;

typedef void (^ScreenShotBlock)(UIImage *image);

typedef NS_ENUM(NSUInteger, MLAgoraPublisherOrientationMode) {
    MLAgoraPublisherOrientationModeAdaptative = 0,
    MLAgoraPublisherOrientationModeFixedLandscape = 1,
    MLAgoraPublisherOrientationModeFixedPortrait = 2,
};

@protocol MLStreamMediaDataConsumer;
@protocol MLPublisherDelegate <NSObject>

@optional
// 用户自己加入频道
- (void)publisher:(MLPublisher *)publisher hostDidJoinChannel:(NSString *)channel;
// 推流成功的扩展方法（only agora）
- (void)publisher:(MLPublisher *)publisher hostDidJoinChannel:(NSString *)channel withUid:(NSUInteger)uid elapsed:(NSUInteger)elapsed;
// 其他用户加入频道
- (void)publisher:(MLPublisher *)publisher didRemoteJoinChannel:(NSString *)channel withUid:(NSUInteger)uid;
// 推流器开始推流
- (void)publisherDidStartPublishing:(MLPublisher*)publisher error:(NSError*)error;
// rtmp推流器已经有数据发出
- (void)publisherDidStartRtmpPushPublishing:(MLPublisher*)publisher error:(NSError*)error;
// 推流器停止推流
- (void)publisherDidStopPublishing:(MLPublisher*)publisher error:(NSError*)error;
// 推流器推流失败
- (void)publisher:(MLPublisher *)publisher streamPublishingFailedWithError:(NSError*)error;
// 音乐播放失败
- (void)musicPlayerDidfailed:(MLPublisher*)publisher error:(NSError*)error;
// 音乐播放开始
- (void)musicPlayerDidStarted:(MLPublisher*)publisher error:(NSError*)error;
// 音乐播放完成
- (void)musicPlayerDidCompleted:(MLPublisher*)publisher error:(NSError*)error;
// 推流器声音被打断开始
- (void)publisherAudioInterruptBegin:(MLPublisher*)publisher error:(NSString*)error;
// 推流器声音被打断结束
- (void)publisherAudioInterruptEnd:(MLPublisher*)publisher error:(NSString*)error;
// Network condition warning - switch resolution/bitrate
- (void)publisherPushNetworkWarning:(MLPublisher*)publisher error:(NSString*)error;
// Network condition warning - drop packet
- (void)publisherPushDropPacket:(MLPublisher*)publisher error:(NSString*)error;
// Network report - up or down push level
- (BOOL)publisherPushLevelChange:(MLPublisher*)publisher
                  withEncodeSize:(CGSize)encodeSize
                withVideoBitrate:(int)videoBitrate;
// Get Capture Size
- (CGSize)publisherGetCaptureSize:(MLPublisher*)publisher;

// Update live API domain for log report
- (NSString *)publisherUpdateLiveAPIDomain:(MLPublisher *)publisher domainType:(MLMediaDomainTable)domainType;

- (CGPoint)publisherGetUserLocation:(MLPublisher *)publisher;

// 伴奏播放失败
- (void)effectPlayerDidfailed:(MLPublisher*)publisher effectId:(int)effectId error:(NSError*)error;
// 伴奏播放完成
- (void)effectPlayerDidCompleted:(MLPublisher*)publisher effectId:(int)effectId error:(NSError*)error;
// 其他用户退出频道
- (void)publisher:(MLPublisher *)publisher onMemberExitWithUserId:(NSString *)userId reason:(MLUserOfflineReason)reason;
// 用户离开频道
- (void)publisherDidLeaveChannel:(MLPublisher *)publisher;
// 频道key过期需要新key
- (void)publisherRequestChannelKey:(MLPublisher *)publisher;
// 频道key将要过期需要新key
- (void)publisherRequestChannelKeyWillExpire:(MLPublisher *)publisher;
// 连麦成功
- (void)publisher:(MLPublisher *)publisher onConnectionSuccessWithHostId:(NSString *)hostId guestId:(NSString *)guestId;
// 其他用户的视频丢失（only weila）
- (void)publisher:(MLPublisher *)publisher onRemoteVideoIsLostWithUserId:(NSString *)remoteUserId;
// 其它用户被踢出（only weila）
- (void)publisher:(MLPublisher *)publisher onKickedWithGuestId:(NSString *)guestId reason:(int)reason;
// 推流缓存开始
- (void)publisherBufferStart:(MLPublisher *)publisher;
// 推流缓存结束
- (void)publisherBufferEnd:(MLPublisher *)publisher;
// 恢复推流
- (void)onResumePublishing;
// 其他用户掉线
- (void)publisher:(MLPublisher *)publisher didOfflineOfUid:(NSString *)uid;
- (void)publisher:(MLPublisher *)publisher didOfflineOfUid:(NSString *)uid reason:(NSUInteger)reason;
//声网上报错误
- (void)publisher:(MLPublisher *)publisher didOccurError:(MLAgoraErrorCode)errorCode;
// 收到其他用户第一帧视频
- (void)publisher:(MLPublisher *)publisher didReceivedVideoForRemoteId:(NSString *)uid remoteView:(UIView *)remoteView;
// 上报声波大小
- (void)publisher:(MLPublisher *)publisher reportAudioVolumeIndicationOfSpeakers:(NSDictionary *)volumes;
// 其他用户声音是否静音
- (void)publisher:(MLPublisher *)publisher didRemoteAudioMuted:(BOOL)muted remoteUid:(NSUInteger)uid;
// 其他用户画面是否关闭
- (void)publisher:(MLPublisher *)publisher didRemoteVideoMuted:(BOOL)muted remoteUid:(NSUInteger)uid;
// 连线断开（only weila）
- (void)publisher:(MLPublisher *)publisher disconnectedWithErrorCode:(NSInteger)errCode;
//enable:YES设置主播身份，NO设置观众身份；code:声网设置角色返回值
- (void)publisher:(MLPublisher *)publisher setClientRoleAsBroadcast:(BOOL)enable code:(int)code;
/*收到消息（vela和声网的回调不一样，为了兼容两家使用声网的参数方式）,声网收到的消息是NSData，vela是NSString，声网的兼容性更好
 而且vela没有发送消息者的uid，在超过两个人的房间里使用不方便（自己拼uid的方式可以方便的伪造uid）
 */
- (void)publisher:(MLPublisher *)publisher recvStreamMessage:(NSString *)msg fromUID:(NSInteger)uid streamID:(NSInteger)sid;

- (void)publisher:(MLPublisher *)publisher localVideoSentFrameRate:(NSUInteger)fRate bitRate:(NSUInteger)bRate;

- (void)publisher:(MLPublisher *)publisher remoteVideoSentFrameRate:(NSUInteger)fRate bitRate:(NSUInteger)bRate remoteId:(NSInteger)uid;

- (void)publisher:(MLPublisher *)publisher localCameraOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer;

// 网络质量回调（only agora）
- (void)publisher:(MLPublisher *)publisher audioQualityOfUid:(NSUInteger)uid quality:(MLUserNetworkQuality)quality delay:(NSUInteger)delay lost:(NSUInteger)lost;
- (void)publisher:(MLPublisher *)publisher networkQuality:(NSUInteger)uid txQuality:(MLUserNetworkQuality)txQuality rxQuality:(MLUserNetworkQuality)rxQuality;
// 创建h265编码器失败
- (void)publisherCreateH265EncoderFailed:(MLPublisher *)publisher;

// 推流数据到达cdn（经验值），只用于平滑切换的优化方案
- (void)publisherDidReceivedCDN:(MLPublisher *)publisher frameCount:(NSUInteger)frameCount;

// 上传媒体日志成功（目前仅限于pushWatch）
- (void)publisherUploadMediaLogSuccess:(MLPublisher *)publisher;

// 上传媒体日志失败（目前仅限于pushWatch）
- (void)publisherUploadMediaLogFailed:(MLPublisher *)publisher;

// 重连服务器超时（目前仅微辣会回调）
- (void)publisherReconnectServerTimeout:(MLPublisher *)publisher;

//只有腾讯支持
- (void)publisherOnStartPublishCDNStream:(MLPublisher *)publisher err:(int)err errMsg:(NSString *)errMsg;

- (void)publisherOnStopPublishCDNStream:(MLPublisher *)publisher err:(int)err errMsg:(NSString *)errMsg;

- (void)publisherOnStartMixTranscoding:(MLPublisher *)publisher err:(int)err errMsg:(NSString *)errMsg;

- (void)publisherOnStopMixTranscoding:(MLPublisher *)publisher err:(int)err errMsg:(NSString *)errMsg;

- (void)publisher:(MLPublisher *)publisher changeEchoCancelStatus:(int)echoCancelStatus;//echoCancellation 0 打开回声消除,1 关闭回声消除
//混屏sei数组回调
- (void)pulisher:(MLPublisher *)publisher onUpdateTranscodeSeiData:(NSArray *)transcodeSei infoSeiData:(NSDictionary *)infoSei withCavasSize:(CGSize)size;

- (void)publisher:(MLPublisher *)publisher didReceiveSEI:(NSString *)sei;//udp下行观众端的sei

- (void)publisher:(MLPublisher *)publisher uid:(NSUInteger)uid didReceiveMsg:(NSString *)msg;//合唱数据回调

- (void)publisher:(MLPublisher *)publisher onSendMediaHeart:(NSString*)msg;//心跳回调上报

- (void)publisher:(MLPublisher *)publisher publisherStatisticMediaWatch:(NSMutableDictionary*)aParam; //中台心跳上报

- (void)publisherOnChangeStreamUrl:(MLPublisher *)publisher;//改变推流地址回调

- (void)publisher:(MLPublisher *)publisher onReportDetailData:(NSMutableDictionary *)stats;

- (BOOL)publisherVadDownGrade:(MLPublisher *)publisher;//获取vad是否执行.NO 执行vad yes不执行vad

- (BOOL)publisherOnConnectionDidBanned:(MLPublisher *)publisher;//声网踢人回调

// 获取源数据
- (CVPixelBufferRef)publisher:(MLPublisher *)publisher rawData:(CVPixelBufferRef)rawdata;

- (void)publisher:(MLPublisher *)publisher didRemoteVideoSizeChanged:(NSUInteger)uid size:(CGSize)size;

- (void)publisher:(MLPublisher *)publisher rtmpStreamingAgoraFailed:(NSUInteger)errcode;

@end

@protocol MLConferenceVideoDelegate <NSObject>

@optional
- (void)publisher:(MLPublisher *)publisher onRemoteConferenceVideoFrame:(CMSampleBufferRef)sampleBuffer userId:(uint32_t)uid;
- (void)publisher:(MLPublisher *)publisher onRemoteConferenceAudioFrame:(CMSampleBufferRef)sampleBuffer userId:(uint32_t)uid;
- (void)publisher:(MLPublisher *)publisher onConferenceAudioPacket:(NSData *)data audioInfo:(NSDictionary *)audioInfo;
- (void)publisher:(MLPublisher *)publisher onConferenceRecordAudioPacket:(NSData *)data channel:(int)channel sampleRate:(int)sampleRate;

@end

@interface MLPublisher : NSObject <IJKEncoderDelegate, MLStreamMediaDataConsumer> {
    int mAudioInterruptFlag;
}

//媒体中台
@property (nonatomic, strong) NSString *mediaAppid;
@property (nonatomic, strong) NSString *mediaSecret;
@property (nonatomic, strong) NSString *mediaAppVerNum;
@property (nonatomic, strong) NSString *mediaMomoId;
@property (nonatomic, strong) MMLiveUserContext *userContext;

// Audio process
@property (nonatomic) int  valueEQ;          // -4 - 4(0, disable)
@property (nonatomic) int  valuePitchShift;  // -10 - 10(0, disable)，说话声音pitch的参数
@property (nonatomic) int  valueAEFilter;  //0 原声 1 小怪兽 2 papi酱 3 变形金刚 4 机器人  5:女变男 6:男变女 7:娃娃音 8:mc 9:ELE_EFFECT 10:小黄人 11:静音(AEF_MUTE) 12:礼物机器人
// Audio process

// Chase delay
@property (nonatomic) int  enablePushWarning;
@property (nonatomic) int  enablePushDrop;
@property (nonatomic) int  enablePushBitrateChange;
@property (nonatomic) int  pushCacheNormal;
@property (nonatomic) int  pushCacheWarning;
@property (nonatomic) int  pushCacheGrowMax;
@property (nonatomic) int  pushCacheCheckInterval;
@property (nonatomic) int  pushLevelChangeMax;
@property (nonatomic) int  pushLevelChangeScaling;
@property (nonatomic) int  networkWarningInterval;
//IJK drop
@property (nonatomic) int ijk_drop_status;
@property (nonatomic) int ijk_drop_warning;
@property (nonatomic) int ijk_drop_normal;
// Chase delay

@property (nonatomic) uint64_t lastAudioCalcTime;
@property (nonatomic) uint64_t lastVideoCalcTime;
@property (nonatomic) uint64_t lastFrameCalcTime;
@property (nonatomic) uint64_t lastAudioSentBytes;
@property (nonatomic) uint64_t lastVideoSentBytes;
@property (nonatomic) uint64_t lastFrameSentCount;
@property (nonatomic) uint64_t totalFrameSentCount;

@property (nonatomic) uint64_t valueTS;
@property (nonatomic) uint64_t valueP2pTS;

@property (nonatomic, assign) CGSize videoSize;
//编码大小，编码器会使用该参数编码
@property (nonatomic, assign) CGSize encodeSize;

@property (nonatomic, weak) MLMediaViewController *mediaController;
@property (nonatomic, strong) IJKAACEncoder *aacEncoder;
@property (nonatomic, strong) IJKFdkAACEncoder *fdkAAcEncoder;
@property (nonatomic, strong) FFRtmpWriter *rtmpWriter;
@property (nonatomic, strong) IJKAudioFilterPipeline * apipeline;

@property (nonatomic) MLVideoCodecType codecType;

@property (nonatomic) BOOL findFirstKeyFrame;
@property (nonatomic) BOOL isEnableDynamicBitrate;
@property (nonatomic) NSInteger bitrateAdapterMaxDuration;
@property (nonatomic) NSInteger bitrateAdapterMinDuration;
@property (nonatomic) int currentBitrate;
@property (nonatomic) int targetFps;
@property (nonatomic) int currentFps;
@property (nonatomic) int gopDuration;
@property (nonatomic) uint64_t firstKeyFrameTS;
@property (nonatomic) uint64_t lastFrameTimestampInMs;
@property (nonatomic) uint64_t nextFrameTimestampInMs;
@property (nonatomic) uint64_t  lastAdjustTime;

@property (nonatomic) BOOL  pauseEncoder;
@property (nonatomic, copy) NSString *hostSdkID;

@property (nonatomic, weak) id<MLPublisherDelegate> delegate;

@property (nonatomic, weak) id<MLConferenceVideoDelegate> confDelegate;

@property (strong) IJKAudioPlayerController * musicPlayer;

@property (nonatomic) float micVolume;
@property (nonatomic) float musicVolume;
@property (nonatomic) float earVolume;  //耳返音量

@property (nonatomic, weak, readonly) UIView *containerView;
@property (nonatomic, strong) UIView *localView;

@property (nonatomic, strong) IJKVideoEncoder *videoEncoder;

// Dual Stream Mode
@property (nonatomic) BOOL                        dualEnable;
@property (nonatomic) CGSize                      dualEncodeSize;
@property (nonatomic) int                         dualVideoBitrate;
@property (nonatomic) int                         dualVideoFrameRate;
@property (nonatomic, strong) IJKVideoEncoder     *dualH264Encoder;
@property (nonatomic, strong) MLMediaUtilityScale *dualScale;
// Dual Stream Mode End

// Media Config Push
@property (nonatomic) int                          mcp_enable_vbr_limit;
@property (nonatomic) int                          mcp_enableVBR;
@property (nonatomic) int                          mcp_adapt_br_step; // bps
@property (nonatomic) int                          mcp_adapt_br_min;  // bps
@property (nonatomic) int                          mcp_adapt_fr_min;  // fps
@property (nonatomic, strong) NSArray              *mcp_adapt_size;

@property (nonatomic) int                          mcp_audio_high_quality;
@property (nonatomic) int                          mcp_enable_audio_media_headset;//连线高音质（视频）开关
@property (nonatomic) int                          mcp_enable_weila_audio_media_headset;//微辣高音质开关
@property (nonatomic) int                          mcp_enable_tx_audio_media_headset;//腾讯高音质开关
@property (nonatomic) int                          mcp_enable_auto_control_denosie_level; //音频降噪自调节开关，0-关，1-开
@property (nonatomic) int                          mcp_vad_detect_select; //0-vad，1-soundwav
@property (nonatomic) int                          mcp_mmrtc_audio_level;//0-4 for mmrtc audio
// Media Config Push End
@property (nonatomic) int                          mcp_adapt_denoise_level;//调节降噪等级
@property (nonatomic) int                          mcp_fdk_aac;//调节降噪等级
@property (nonatomic) int                          mcp_media_im_log_enable;//标记im上报媒体日志的开关
@property (nonatomic) int                          mcp_enable_min_bitrate;//要不要设置码率自适应中的最低码率(目前就agora有效)
@property (nonatomic) int                          mcp_set_min_bitrate_percent;//最低码率的百分比,例如mediaConfig中给的是50，最低下降到设置码率的50%
@property (nonatomic) int                          mcp_sox_category_enable;//sox 音效开关
//Media Config
@property (nonatomic) int                          mcp_startup_expand;
@property (nonatomic) int                          mcp_expandIn_carton;
@property (nonatomic) int                          mcp_push_data_warning;

@property (nonatomic, assign) BOOL                 mcp_update_video_dts;
@property (nonatomic) int                          mcp_enable_B_encode;//控制开关B帧编码，0 代表关闭B帧编码，1 代码打开B帧编码
@property (nonatomic) int                          mcp_hevc_drop_rasl;//控制开关，hevc open gop 的情况下 是否丢弃rasl
@property (nonatomic) int                          mcp_agora_enable_B_encode;//声网控制开关B帧编码，0 代表关闭B帧编码，1 代码打开B帧编码
@property (nonatomic) int                          mcp_disable_weila_ANS;//微辣关闭降噪
@property (nonatomic) int                          mcp_disable_weila_AEC;//微辣降低回声消除
@property (nonatomic) int                          mcp_ijk_audio_profile;//IJK 音频v2编码,0 aac_lc\1 aac_he_v1 \2 aac_he_v2
@property (nonatomic) int                          mcp_agora_audio_profile;//声网转推音频profile,0 aac_lc\1 aac_he_v1 \2 aac_he_v2
@property (nonatomic) int                          mcp_transcode_bitrate;//微辣降低回声消除
// Mute Status
@property (nonatomic) BOOL                         video_mute;
@property (nonatomic) BOOL                         audio_mute;
// Mute Status End

// dynamic framerate
@property (nonatomic, assign) BOOL enableDynamicFramerate;
@property (nonatomic, assign) int dynamicFramerate;
@property (nonatomic, assign) int dynamicLastFramerate;
@property (nonatomic, assign) int dynamicLastBitrate;
@property (nonatomic, assign) NSTimeInterval lastDynamicVideoTime;

@property (nonatomic) NSInteger cameraPos;
@property (nonatomic) NSInteger videoFramerate;
@property (nonatomic) NSInteger videoBitrate;
@property (nonatomic) NSInteger audioBitrate;
@property (nonatomic) double audioTargetSamplerate;
@property (nonatomic) NSInteger audioChannels;
@property (nonatomic) NSInteger audioFormat;

@property (atomic) MLPublisherStatus publisherStatus;

@property (nonatomic) BOOL isStartPublish;
@property (nonatomic) BOOL isFirstVideoFrame;
@property (nonatomic) NSUInteger firstVideoPts;
@property (nonatomic) CMTime firstVideoClockTime;

@property (nonatomic) BOOL isBuffering;

@property (nonatomic, copy) NSString *publishPath;

@property (nonatomic, strong) IJKAudioOutput *audioOutput;

//Reporter
@property (nonatomic) uint64_t maxBufferStartTimestampInMs;

@property (nonatomic, readonly) NSString *publisherType;

//use isEnableLoopbackAudio to enable or disable loopback audio
@property (nonatomic, assign) BOOL isEnableLoopbackAudio;
@property (nonatomic, assign, getter=isLoopbackAudio, setter=setIsLoopbackAudio:) BOOL isLoopbackAudio;

@property (nonatomic, strong) MLPublisherStatistic *statistic;
@property (nonatomic, strong) AudioController* audioController;

@property (nonatomic) BOOL isAudioRecording;
@property (nonatomic, copy) NSDictionary *audioCodecContext;

@property (nonatomic, readonly) NSMutableDictionary *smVideoPlayerDict;
//连线用户小窗
@property (nonatomic, strong) NSMutableDictionary *remoteViewDict;
//default is YES
@property (nonatomic, assign) BOOL  muteAudioWhileEnterBackground;

@property (nonatomic, strong) IJKVideoEncoder *encoderForSei;
@property (nonatomic, copy) NSDictionary *userInfo;
@property (nonatomic, copy) NSDictionary *connectSeiDict;
@property (nonatomic, strong) NSLock *connectSeiLock;
@property (nonatomic, readonly, assign) MLPublisherType pushType; // 推流器类型
@property (nonatomic, getter=isConnectMode, assign) BOOL connectMode; // 交友模式的推流器
//静音管理
@property (nonatomic, assign) BOOL enableAudioMuted;
//是否是纯音频模式
@property (nonatomic, assign) BOOL isAudioOnlyPublisher;
//是否开启音量大小回调
@property (nonatomic, assign) BOOL enableReportAudioVolume;
//单位是ms
@property (nonatomic, assign) int audioLevelReportInterval;

@property (nonatomic, strong) NSMutableDictionary *optionSet;
//连线是否重连（目前只有声网在使用）
@property (nonatomic, assign) BOOL enableConferenceReconnect;
//获取连线对方视频数据
@property (nonatomic, assign) BOOL enableConferenceVideoFrame;
//音效播放
@property (nonatomic, strong) MLAudioEffectManager *audioEffectManager;
@property (nonatomic, strong) NSMutableDictionary *audioEffectsDict;
//是否正在播放音乐伴奏
@property (nonatomic, assign) BOOL isMusicPlaying;
//是否暂停音乐伴奏
@property (nonatomic, assign) BOOL isMusicPaused;
//是否是第二个推流
@property (nonatomic, assign) BOOL isSecondPublisher;
//是否是播主互连
@property (nonatomic, assign) BOOL isPublisherConnect;
//是否获取连线主播声音
@property (nonatomic, assign) BOOL isGetConferenceRecordAudio;
@property (nonatomic, assign) BOOL isFulltimeModeRadio; // 24小时房间类型
//设置连麦混屏背景地址
@property (nonatomic, copy) NSString *conferenceBackgroundImage;
//是否是游戏连线推流器
@property (nonatomic, assign) BOOL isGamePublisher;
//是否是声网微辣跨直播间连线推流器
@property (nonatomic, assign) BOOL isAcrossConnectPublisher;
//有效部分推流宽高
@property (nonatomic, assign) CGSize validVideoSize;
//连麦混屏后推cdn的码率
@property (nonatomic, assign) NSInteger mixerBitrate;
//是否是横屏直播普通推流支持
@property (nonatomic, assign) BOOL isOrientationLandscape;
//是否是同步流观看
@property (nonatomic, assign) BOOL isConferencePlayer;
//是否使用声网的scenario模式
@property (nonatomic, assign) BOOL useAudioScenario;
//是否开启赛宾音效，YES开启，默认NO
@property (nonatomic, assign) BOOL enableSabineAudioEffect;
//0 原音;1 剧院;2 地下室;3 浴室;4 办公室;5 ktv;6 录音室;7 new_ktv
@property (nonatomic, assign) int  soxAudioCategory;
//声网配置，需要在startPublishingWithOptions之前设置
@property (nonatomic, strong) MLAgoraConfiguration *agoraConfig;
//横竖屏配置，需要在startPublishingWithOptions之前设置
@property (nonatomic, assign) MLAgoraPublisherOrientationMode agoraOrientationMode;
//设置SDK日志位置
@property (nonatomic, copy) NSString *sdkLogFilePath;
//连线音频编码参数(声网、微辣)
@property (nonatomic, assign) int audioProfileLevel;
//推流视频帧计数
@property (nonatomic) BOOL  isReceivedCDN;
@property (nonatomic) int64_t writeOutVideoFramesNumber;

//是否开启平滑切换
@property (nonatomic, assign) BOOL isSmoothSwitchMode;
@property (nonatomic, assign) NSInteger delayTimeToReceivedCDN;
@property (nonatomic, assign) BOOL isReadyConference;
@property (nonatomic, assign) CMTime firstPublishVideoTime;
@property (nonatomic, copy) BOOL (^shouldPresentPixelBufferWaitUntilDoneHandler)(MLPublisher *publisher, CGSize pixelBufferSize, dispatch_block_t completion);
@property (nonatomic, assign)  long preFrameCount;
@property (nonatomic, assign)  long currentFrameCount;
@property (nonatomic, assign)  bool isUdpUpLink;//判断是否udp
@property (nonatomic, assign)  long realTimeBitRate;//单位kbps
@property (nonatomic, assign)  BOOL isInsertSei;
@property (nonatomic, assign)  BOOL isRealBackOrForground;

@property (nonatomic, assign)  BOOL isInsertConferenceSei; //打开卖上发送sei的功能
@property (nonatomic, assign) int insertSeiInterval; //插入sei的频率，单位ms
@property (nonatomic, assign) BOOL isEnableVideo;//开关视频功能，NO 关闭 YES 打开
@property (nonatomic, assign) BOOL isEnableAudio;//开关音频功能，NO 关闭 YES 打开
/// 录屏工具
@property (nonatomic, strong) MLMediaVideoRecorder *videoRecorder;
@property (nonatomic, copy) ScreenShotBlock shotBlock;

@property (nonatomic) NSInteger businessType;
@property (nonatomic) NSInteger backgroundStatus;

@property (nonatomic, assign) float masterVolume;
@property (nonatomic, assign) float externalVolume;

//连线小窗裁剪尺寸
@property (nonatomic, assign) CGRect linkWindowClipRect;
@property (nonatomic, assign, readonly) BOOL linkWindowClipRectValid;
// Initialization and teardown
- (instancetype)initWithContentView:(UIView *)view inputVideoSize:(CGSize)inputVideoSize isHost:(BOOL)isHost NS_REQUIRES_SUPER;
// 提前传入appid可以先创建连麦引擎
- (instancetype)initWithContentView:(UIView *)view
                     inputVideoSize:(CGSize)inputVideoSize
                             isHost:(BOOL)isHost
                              appId:(NSString *)appId
                         channelKey:(NSString *)channelKey;
//使用中台日志
- (instancetype)initWithContentView:(UIView *)view
                     inputVideoSize:(CGSize)inputVideoSize
                             isHost:(BOOL)isHost
                              appId:(NSString *_Nullable)appId
                             secret:(NSString *_Nullable)secret
                          appVerNum:(NSString *_Nullable)appVerNum
                             userId:(NSString *_Nullable)userId;

- (void)setPublisherOptions:(NSDictionary*)options;
- (void)setMediaConfig:(NSString *)mediaConfig;
- (NSInteger)roomType;
- (void)setRoomMode:(MLPublisherOptionRoomMode)roomMode;
- (NSInteger)roomMode;

- (void)startPublishingWithOptions:(MLPublisherOptions *)options NS_REQUIRES_SUPER;

- (void)updatePublishingWithOptions:(MLPublisherOptions *)options ;

- (void)installAudioNotificationObservers;

- (void)stopPublishing:(MLPublisherError)code;

- (void)processAudioBuffer:(CMSampleBufferRef)audioBuffer;
- (void)processRenderAudioBuffer:(NSData *)audioBuffer;
- (void)processVideoBuffer:(CVPixelBufferRef)renderTarget atTime:(CMTime)frameTime;
- (void)recorderProcessVideoBuffer:(CVPixelBufferRef)renderTarget;

- (void)releasePublisher;

- (void)playMusicWithUrl:(NSString *)url;
//loopback是否伴奏只是本地播放，YES是只是本地播放，NO本地远端都能听到，只有连麦时候起作用
- (void)playMusicWithUrl:(NSString *)url loopback:(BOOL)loopback;
//目前只有声网支持循环播放，repeat: 循环的次数，-1: 无限循环
- (void)playMusicWithUrl:(NSString *)url loopback:(BOOL)loopback repeat:(NSInteger)repeat;
//hrs 增加一个设置音效调节的pitch接口
- (void)setValueMusicPitchShift:(int)valueMusicPitchShift;
//hrs 增加一个获取音效调节的pitch接口
- (int)getValueMusicPitchShift;
- (void)seekValueMusic:(int)pos;//hrs 增加背景音频seek的方法,单位ms
- (void)stopMusic;
- (void)pauseMusic;
- (void)resumeMusic;
- (NSTimeInterval)musicCurrentPosition;
- (NSTimeInterval)musicDuration;
//internal use, do not call from outside
- (bool)isNetworkAddress:(NSString*)url;
- (void)musicPlaybackEnded;
- (void)mixAudioSampleInPlace:(NSData *)masterSample slaverSamples:(NSMutableArray *)slaverSamples;
- (void)mixAudioSampleInPlace:(NSData *)masterSample slaverSamples:(NSMutableArray *)slaverSamples masterVolume:(float)masterVolume slaveVolume:(float)slaveVolume;
- (int)mixMusicSampleInPlace:(NSData *)masterSample slaverSamples:(NSMutableArray *)slaverSamples;
- (int)mixWeilaMusicSampleInPlace:(NSData *)masterSample slaverSamples:(NSMutableArray *)slaverSamples;
- (void)createVideoEncoder;
- (void)destroyVideoEncoder;

- (void)setVideoBitrateAndResetVideoEncoder:(NSInteger)bitrate;//bps
- (void)setVideoParamsAndResetVideoEncoder:(NSDictionary *)params;
- (void)resetVideoEncoder;
- (void)changeVideoSize:(CGSize)videoSize bitrate:(int)bitrate; //bitrate（bps）

- (void)adjustBitrate;
- (void)triggerPushFocus:(int32_t)autoMode withPos:(CGPoint)pos;

//LogInfo Reporter
- (void)updateQueueBufferState;

- (uint64_t)getEncodedVideoBufferDurationInMs;
- (void)pushBufferingStartWithDurationMs:(uint64_t)durationMs;
- (void)pushBufferingStop;

- (BOOL)isReadyToPublish;
- (BOOL)isEncodingVideo;
- (void)updateLocalViewWithFrame:(CGRect)frame;

//enterBackground will pause publishing
- (void)enterBackground;
//enterForeground will resume publishing
- (void)enterForeground;
- (void)conferenceResume;
- (void)updateAudioLoopbackSetting;
// Get push statistics(cpu/mem/delay...) for debug display on screen
- (NSString *)getPushWatch;

/**
 type: 1降噪, 2混响, 3均衡器(EQ)
 index和value参见sabine_effects.h定义的inIdx和inValue值
 */
- (void)setSabineAudioEffect:(int)type index:(int)index value:(float)value;
- (void)setSabineAudioEffectToDefault;
//音效处理新接口
- (void)setAudioEffectAns:(float)inValue;
- (void)setAudioEffectReverb:(int)index value:(float)inValue;
- (void)setAudioEffectPeqFliter:(int)inBand frequence:(float)inFc onOff:(int)onOff;
- (void)setAudioEffectPeqShelving:(int)inBand frequence:(float)inFc gain:(float)inGain;
- (void)setAudioEffectPeqPeak:(int)inBand frequence:(float)inFc inQ:(float)inQ gain:(float)inGain;

//set user define info into h264 sei, to bypass CDN to player
//if you don't need to send user info anymore, just set to nil
- (void)setSeiUserInfo:(NSDictionary *)info;

//For internal use ONLY
- (NSData *)seiStrToSeiData:(NSString *)seiStr;
- (NSString *)gernerateSeiStr:(NSString *)masterId info:(NSDictionary *)info;
- (NSData *)getExtraSeiDataWithEncryptUserId:(NSString *)encryptUserId;

- (void)appendSeiDataToVideoStreamData:(IJKVideoFrame *)videoFrame encryptUserId:(NSString *)encryptUserId;
//双推流时推送的音频数据
- (void)pushConferenceAudioPacket:(NSData *)data audioInfo:(NSDictionary *)audioInfo;

//私有方法内部调用
- (void)stopPublishingWithCompletionCode:(MLPublisherError)code;
/// 更新 连线sei
- (void)updateSeiDataForConnectWithSeiDict:(NSDictionary *)seiDict;

//连麦接口接口封装
// if YES mute, or NO unmute
- (void)muteLocalAudio:(BOOL)mute;
- (void)muteLocalVideo:(BOOL)mute;
- (void)muteAllRemoteAudio:(BOOL)mute;
- (void)muteAllRemoteVideo:(BOOL)mute;
- (void)muteRemoteAudioStream:(NSUInteger)uid mute:(BOOL)mute;
- (void)muteRemoteVideoStream:(NSUInteger)uid mute:(BOOL)mute;

// 观看大小流切换开关，配合muteRemoteVideoStream使用
- (void)muteRemoteDualVideoStream:(NSUInteger)uid mute:(BOOL)mute;

// only used for upload log
- (void)setClientAsAudience:(BOOL)enable;
//encryption mode, can be:"aes-128-xts" "aes-256-xts",default is "aes-128-xts". specify NULL will use default mode.
- (void)setEncryptionSecret:(NSString *)secret withMode:(NSString *)encryptionMode;
- (void)setAgoraSdkAppID:(NSString *)appID withChannelKey:(NSString *)channelKey;
- (void)setSdkAppID:(NSString *)appID withChannelKey:(NSString *)channelKey;
- (void)renewChannelKey:(NSString *)channelKey;
// if YES for game, or NO for live
- (void)enableCommMode:(BOOL)enable;
- (void)enableSoftAEC:(BOOL)enable;
- (void)enableRemoteIO:(BOOL)enable;

- (void)playEffectWithId:(int)effectId url:(NSString *)url loop:(BOOL)loop pitch:(double)pitch pan:(double)pan gain:(double)gain;
//publish为YES远端能听到为NO只能本地听到
- (void)playEffectWithId:(int)effectId url:(NSString *)url loop:(BOOL)loop publish:(BOOL)publish;
- (void)playEffectWithId:(int)effectId url:(NSString *)url loop:(BOOL)loop;
- (void)stopEffectWithId:(int)effectId;
- (void)stopAllEffect;
//音效的音量取值范围为[0.0, 1.0],默认值为1.0
- (void)setEffectVolumeWithId:(int)effectId withVolume:(double)volume;
- (void)setEffectsVolume:(double)volume;
//设置连线播放是外放还是听筒，返回0成功否则失败
- (int)setConferencePlaybackSpeakerphone:(BOOL)enable;
// change client role, if YES as broadcast ,or NO as audience
- (void)setClientRoleAsBroadcast:(BOOL)enable;
- (MLPubliserClientRole)getClientRole;
- (void)pushExternalAudioBuffer:(MLPCMBuffer *)audioBuffer;
/**
            合入外部音频
 @param audioBuffer 音频数据
 @param masterVolume 主播音量大小 取值范围 [ 0.f～1.0f ]
 @param externalVolume 外部音频音量大小 取值范围 [ 0.f～1.0f ]
 */
- (void)pushExternalAudioBuffer:(MLPCMBuffer *)audioBuffer masterVolume:(float)masterVolume externalVolume:(float)externalVolume;


// Dual Stream Mode
- (int)enableDualStreamMode:(BOOL)enable
             withEncodeSize:(CGSize)encodeSize
           withVideoBitrate:(int)videoBitrate
         withVideoFrameRate:(int)videoFrameRate;

//发送连线文本消息,微辣不需要创建直接发送
- (int)createDataStream:(NSInteger*)streamId reliable:(BOOL)reliable ordered:(BOOL)ordered;
- (int)sendStreamMessage:(NSInteger)streamId msg:(NSString *)msg;
//声网音频回调开关
- (void)audioObserverCallBackEnable:(BOOL)enable;
//设置声网远端渲染布局
- (void)setupRemoteVideo:(MLAgoraRtcVideoCanvas *)canvas;
//设置远端视频的大小流
- (void)setRemoteVideoQuality:(long long)userId type:(MLAgoraVideoStreamType)streamType;
/**
 调整远端用户的音量
 volumeScale音频加强系数0.～2.0之间0.～1.0 为声音减弱  >1.0为声音加强
 **/
- (void)adjustRemoteUser:(long long)userId volumeScale:(float)volumeScale;

//以下方法平台在用，目前只支持声网
//设置播放声音大小（0~100），
- (int)adjustPlaybackSignalVolume:(NSInteger)volume;
- (int)setupLocalVideo:(MLAgoraRtcVideoCanvas * _Nullable)local;
- (int)switchCamera;
- (int)startPreview;
- (int)stopPreview;

//清除外部音频源的buffer
- (void)cleanAllOutsideAudioFrame;

//设置音乐的音调,目前只支持声网
- (void)setMusicMixingPitch:(int)pitch;
//更新混屏背景图片
- (void)updateConferenceBackgroundImage:(NSString *_Nullable)conferenceBackgroundImage;
//新的PK接口（目前只有微辣支持）
- (void)accrossOtherRoom:(long long)roomID userID:(long long)usrID;
- (void)unaccrossOtherRoom:(long long)roomID;
- (void)forceUnaccrossOtherRoom:(long long)roomID;
- (void)updateCanvasSize:(CGSize)size;
- (int)enableWebSdkInteroperability:(BOOL)enabled;//打开与 Web SDK 的互通,0: 方法调用成功,小于 0: 方法调用失败.现在只有声网实现了
- (int)setEnableWebSdkInteroperability:(BOOL)enabled;//支持任何时候打开与 Web SDK 的互通，现在只有声网实现了
//
- (nullable NSString *)connectSessionId;

- (void)disableMixGuessVideoWithUserId:(uint64_t)userId;

- (void)setRestartWithURL:(nonnull NSString *)publishURL;

- (void)startTimeCalibrator;

- (SInt64)getCalibtatorTimeDeltaMS;
- (BOOL)headsetPlugging;

- (nullable NSString *)getSDKVersion;

- (nullable NSString *)getPublusherInfo;

- (void)audioDeviceRouteChange:(BOOL)isHeadSet;

- (void)setDenoiseLevel:(int)level;//设置降噪等级 0 关闭降噪 1 ~ 4 分别以此提高降噪等级

- (BOOL)useAudioFilter;//是否使用声音滤镜：判断valueAEFilter1-7为声音滤镜，10为补充的小黄人声音滤镜，12为声音礼物滤镜

- (BOOL)useAudioProcess;//是否处理声音，包括固定的filter、调整EQ、调整pitch，满足任意一个即返回YES

- (void)setSoxAudioCategoryName:(NSString*)name;

- (void)startRTCPublish:(MLPublisherOptions *)options;

- (void)enterRTCRoom:(NSString*)userid roomid:(NSString*)roomid;

- (void)leaveRTCRoom;

- (void)destroyRTCEngine;

- (nullable NSString *)publisherGetMediaLogDomain;
/// 开始录屏
/// @param inputFilePath 输入的音频/视频文件地址
/// @param outputFilePath 输出的录屏视频文件地址
- (void)startVideoRecordWithInputFilePath:(NSString *_Nullable)inputFilePath outputFilePath:(NSString *_Nonnull)outputFilePath;

/// 开始录屏
/// @param outputFilePath 输出的录屏视频文件地址
- (void)startVideoRecordWithOutputFilePath:(NSString *_Nonnull)outputFilePath;

/// 停止录屏
/// @param completed 停止完成
- (void)stopVideoRecord:(void (^)(void))completed;

/// 获取当前视频帧
/// @param shotBlock 截图回调
- (void)shotCurrentPublisherFrame:(ScreenShotBlock)shotBlock;

- (void)setExpandCartonWithExpand:(int)startupExpand expandInCarton:(int)expandInCarton;

- (void)mediaSource:(id<MLStreamMediaSource>)source didOutputVideoSampleBuffer:(CMSampleBufferRef)sampleBuffer;

- (void)mediaSource:(id<MLStreamMediaSource>)source didOutputAudioSampleBuffer:(CMSampleBufferRef)sampleBuffer ;

- (void)mediaSource:(id<MLStreamMediaSource>)source didOutputVideoPreviewSampleBuffer:(CMSampleBufferRef)sampleBuffer;

- (void)mediaSource:(id<MLStreamMediaSource>)source didOutputVideoCodecSampleBuffer:(CMSampleBufferRef)sampleBuffer;

- (void)mediaSource:(id<MLStreamMediaSource>)source didRenderAudioData:(NSData*)sampleBuffer ;

- (void)setPreviewView:(UIView *)view videoSize:(CGSize)size;

- (void)setPreviewView:(UIView *)view;

- (void)updatePushDropConfig:(NSDictionary *)dropConfig;

/** 设置声网重连几次停止推流器

 @param mediaConnectCounts设置重连次数.
 */
- (void)setAgoraConnectCounts:(NSInteger)agoraConnectCounts;

/** 设置Tx重连几次停止推流器

@param mediaConnectCounts设置重连次数.
*/
- (void)setTxConnectCounts:(NSInteger)txConnectCounts;


/**
    合唱设置本地混流
 @param users 混流信息 MLHCRoomLocalMixUser
 
 */
- (void)updateHCDataForMixWithConfigArray:(NSArray*)users;

/**
    清除本地合流信息
 */
- (void)clearHCDataForMixConfig;

- (void)senMessageWithData:(NSString *)msg;

- (void)setBusinessType:(NSInteger)businessType;
- (void)setAvFlag:(NSInteger)avFlag;

/**
    忽略错误码，添加后返回该错误码不报错（腾讯/微辣）
 @param errcode 错误码值
 */
- (void)ignorePublisherErrcode:(NSUInteger)errcode;

- (BOOL)isForceUDPPlayMode;
@end
