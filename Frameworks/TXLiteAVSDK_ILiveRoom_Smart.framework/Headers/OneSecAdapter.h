//
//  OneSecAdapter.h
//  TXLiteAVDemo_ILiveRoom_Standard
//
//  Created by xiang zhang on 2018/10/25.
//  Copyright © 2018 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "TXILiveRoomDefine.h"
#import "TXILiveRoomDelegate.h"

NS_ASSUME_NONNULL_BEGIN
@protocol TXILiveRoomDelegateAdapter;
@protocol TXILiveRoomAudioDelegateAdapter;
@class TXILiveRoomAudioVolumeInfo;
@class OneSecAdapterParams;

@interface OneSecAdapter : NSObject
@property (nonatomic, weak) id<TXILiveRoomDelegateAdapter> delegate;
@property (nonatomic, weak) id<TXILiveRoomAudioDelegateAdapter> audioDelegate;
@property (nonatomic, weak) id<TXILiveRoomVideoRenderDelegate> videoRenderDelegate;
/**
 * 获取SDK版本信息
 */
+ (NSString *)getSDKVersionStr;

/**
 * 启用或禁用控制台日志打印
 * @param enabled 是否启用
 */
+ (void)setConsoleEnabled:(BOOL)enabled;

/**
 * 初始化实例
 * @param sdkAppId 应用标识
 * @param userId 用户标识
 */
- (instancetype)initWithSdkAppId:(UInt32)sdkAppId userId:(UInt64)userId;

#pragma mark - 房间逻辑

/**
 * 进入房间
 * @param params 进房参数
 * @param config 配置信息
 * @note 必须与quitRoom配对使用（不管进房是否成功）
 */
- (void)joinRoom:(OneSecAdapterParams *)params config:(TXILiveRoomConfig *)config;

/**
 * 离开房间
 */
- (void)quitRoom;

/**
 * 切换角色
 * @param role 角色
 * @note “主播”角色和“观众”角色互相切换，切换成功会通过onRoomRoleChanged回调通知，
 *        切换失败会抛 TXILiveRoomErrorSwitchRoleFailed 错误事件(不可恢复，此时需要上层调用 quitRoom)
 */
- (void)switchRole:(TXILiveRoomRole)role;

/**
 * 开启跨房连麦
 * @param roomName 对端的房间名称
 * @param userId 对端的主播标识
 */
- (void)connectOtherRoom:(NSString *)roomName userId:(UInt64)userId;

/**
 * 断开跨房连麦
 **/
- (void)disconnectOtherRoom;

/**
 * 暂停视频采集，并推送默认图片(TXILiveRoomConfig.pauseImg)
 * @note 一般用于App切后台时调用
 */
- (void)pause;

/**
 * 恢复视频采集
 * @note 一般用于App切回前台时调用，不会更改pause之前的状态，比如：之前设置了某个人静音，resume后仍然会静音
 */
- (void)resume;

/**
 * 发送数据流
 * @param streamId 数据流ID，取值范围为 1 ~ 10
 * @param data 待发送的数据
 * @param reliable YES: 接收方会在 5 秒内收到发送方所发送的数据，否则会收到 onStreamMessageError 回调获得相应报错信息。 NO: 接收方不保证收到，就算数据丢失也不会报错
 * @param ordered YES: 接收方 5 秒内会按照发送方发送的顺序收到数据包。 NO: 接收方不保证按照发送方发送的顺序收到数据包
 * @note 注意：发送数据流消息到房间内所有用户，房间内内每秒最多能发送 30 个包，且每个包最大为 1 KB。 每个客户端每秒最多能发送 8 KB 数据
 *       请将 reliable 和 ordered 同时设置为 YES 或 NO, 暂不支持交叉设置。
 *       有序性是指相同streamId的数据流一定跟发送方的顺序相同，强烈建议不同类型的消息使用不同的streamId，这样可以在要求有序的情况下减小消息时延
 */
- (BOOL)sendStreamMessage:(NSInteger)streamId data:(NSData *)data reliable:(BOOL)reliable ordered:(BOOL)ordered;

/**
 * 发送消息（消息大小不允许超过2K）
 * @param data 待发送的数据
 * @note data会封装到SEI中，跟着最近的一个视频帧发送出去，播放端在TXILiveRoomDelegate 里面的 onRecvMessage 接收消息
 */
- (BOOL)sendMessageEx:(NSData *)data;

/**
 * 开启纯音频模式下发送 SEI 能力
 * 若使用纯音频推流，调用该接口设定为YES，才能够通过 sendMessageEx 发送消息
 * @param enable YES-开启 NO-关闭
 */
- (void)enableAudioMessage:(BOOL) enable;

#pragma mark - 日志相关

/**
 * 设置自定义日志文件路径
 *
 * SDK 运行产生的 log 将会写入到该文件中，需保证该文件可写
 *
 * 建议：
 * joinRoom之前调用此接口，quitRoom之后再对文件进行操作
 *
 * @param filePath 文件路径
 */
- (void)setLogPath:(NSString *)filePath;

#pragma mark - 视频相关

/**
 * 开始视频采集及预览
 * @param frontCamera YES:前置摄像头 NO:后置摄像头
 * @param view 预览控件所在的父控件
 */
- (void)startPreview:(BOOL)frontCamera view:(UIView *)view;

/**
 * 停止视频采集及预览
 */
- (void)stopPreview;

/**
 * 控制视频上行
 * @param mute YES:不发送 NO:发送
 * @note 该函数仅仅控制发送，不会去做停止采集等其他操作
 */
- (void)muteLocalVideo:(BOOL)mute;

/**
 * 发送自定义的SampleBuffer
 * 内部有简单的帧率控制，发太快会自动丢帧；超时则会重发最后一帧
 * @param sampleBuffer 视频数据
 * @note 相关属性设置请参考 TXILiveRoomConfig，autoSampleBufferSize优先级高于sampleBufferSize
 * @property sampleBufferSize，设置输出分辨率，如果此分辨率不等于sampleBuffer中数据分辨率则会对视频数据做缩放
 * @property autoSampleBufferSize，输出分辨率等于输入分辨率，即sampleBuffer中数据的实际分辨率
 */
- (void)sendVideoSampleBuffer:(CMSampleBufferRef)sampleBuffer;

/**
 * 设置自定义视频数据(SampleBuffer)的编码参数
 * @param sampleBufferSize 视频分辨率，如果此分辨率不等于sampleBuffer中数据分辨率则会对视频数据做缩放
 * @param videoBitrate 视频码率，单位：kbps
 * @note 相关属性设置请参考 TXILiveRoomConfig，autoSampleBufferSize优先级高于sampleBufferSize
 */
- (void)setCustomVideoParam:(CGSize)sampleBufferSize videoBitrate:(int)videoBitrate;

/**
 * 开始渲染对方画面
 * @param userId 对方的用户标识
 * @param view 渲染控件所在的父控件
 */
- (void)startRemoteRender:(UInt64)userId view:(UIView *)view;

/**
 * 停止渲染对方画面
 * @param userId 对方的用户标识
 * @note 同时停止拉取对方的视频流数据
 */
- (void)stopRemoteRender:(UInt64)userId;

/**
 * 停止所有远端画面的渲染
 * @note 同时停止拉取所有远端的视频流数据
 */
- (void)stopAllRemoteRender;

/**
 * 停止拉取对方的视频流
 * @param userId 对方的用户标识
 * @param mute YES:停止拉取 NO:继续拉取
 */
- (void)muteRemoteVideo:(UInt64)userId mute:(BOOL)mute;

/**
 * 停止拉取所有远端的视频流
 * @param mute YES:停止拉取 NO:继续拉取
 */
- (void)muteAllRemoteVideo:(BOOL)mute;

/**
 * 设置远端渲染回调
 * @param mute YES:停止拉取 NO:继续拉取
 */
- (void)setVideoRenderDelegate:(UInt64)userId videoRenderDelegate:(id<TXILiveRoomVideoRenderDelegate>)videoRenderDelegate;

/**
 *  开启大小画面双路编码模式
 *
 * 如果当前用户是房间中的主要角色（比如主播、老师、主持人等），并且使用 PC 或者 Mac 环境，可以开启该模式。
 * 开启该模式后，当前用户会同时输出【高清】和【低清】两路视频流（但只有一路音频流）。
 * 对于开启该模式的当前用户，会占用更多的网络带宽，并且会更加消耗 CPU 计算资源。
 *
 * 对于同一房间的远程观众而言：
 * - 如果有些人的下行网络很好，可以选择观看【高清】画面
 * - 如果有些人的下行网络不好，可以选择观看【低清】画面
 *
 * @note 双路编码开启后，会消耗更多的 CPU 和 网络带宽，所以对于 iMac、Windows 或者高性能 Pad 可以考虑开启，但请不要在手机端开启。
 *
 * @param enable 是否开启小画面编码
 */
- (void)enableEncSmallVideoStream:(BOOL)enable videoSize:(CGSize)videoSize videoFps:(uint32_t)videoFps videoBitrate:(uint32_t)videoBitrate;

/**
 *  选定观看指定 uid 的大画面还是小画面
 *
 * 此功能需要该 uid 通过 enableEncSmallVideoStream 提前开启双路编码模式。
 * 如果该 uid 没有开启双路编码模式，则此操作将无任何反应。
 *
 * @param userId 用户 ID
 * @param type 视频流类型，即选择看大画面还是小画面
 */
- (void)setRemoteVideoStreamType:(UInt64)userId type:(TXILiveRoomStreamType)type;

/**
 * 设定观看方优先选择的视频质量
 *
 * 低端设备推荐优先选择低清晰度的小画面。
 * 如果对方没有开启双路视频模式，则此操作无效。
 *
 * @param type 默认观看大画面还是小画面
 */
- (void)setPriorRemoteVideoStreamType:(TXILiveRoomStreamType)type;

#pragma mark - 音频相关

/**
 * 发送自定义的音频数据（PCM格式）
 * @param data PCM格式的音频数据
 * @param len 数据长度，2048 或者 4096
 * @note 目前SDK只支持16位采样的PCM编码；如果是单声道，请保证传入的PCM长度为2048；如果是双声道，请保证传入的PCM长度为4096
 */
- (void)sendCustomPCMData:(unsigned char *)data len:(unsigned int)len;

/**
 * 设置发送静音数据
 * @param mute YES:静音 NO:非静音
 */
- (void)muteLocalAudio:(BOOL)mute;

/**
 * 设置声音播放模式
 * @param mode 播放模式(扬声器、听筒)
 */
- (void)setAudioMode:(TXILiveRoomAudioMode)mode;

/**
 * 设置指定用户是否静音
 * @param userId 对方的用户标识
 * @param mute YES:静音 NO:非静音
 */
- (void)muteRemoteAudio:(UInt64)userId mute:(BOOL)mute;

/**
 * 设置所有远端用户是否静音
 * @param mute YES:静音 NO:非静音
 */
- (void)muteAllRemoteAudio:(BOOL)mute;

/**
 * 设置所有远端用户声音大小回调频率
 * @param interval 时间间隔，为了保证性能，这里建议至少 >= 100 ms, < 100ms 不回调数据
 */
- (void)setAudioVolumeIndication:(NSInteger)interval;

/**
 * 设置耳返
 * @param enabled YES 开启耳返 NO 关闭耳返
 */
- (void)enableAudioPreview:(BOOL)enabled;

/**
 * 设置最终播放音量，
 * @param volume  [0,1];
 * @return ,如果设置成功则返回0；否则返回小于0的错误码。
 */
- (int)setPlaybackVolume:(float)volume;


/**
 * 设置音量类型
 * @param type TXILiveRoomAudioVolumeTypeMedia TXILiveRoomAudioVolumeTypeCommunication
 */
- (void)setVolumeType:(TXILiveRoomAudioVolumeType)type;

/**
 * expand block 统计相关
 *
*/
- (void)setAudioExpandBlockThreshold:(NSInteger)audioExpandBlockThreshold;
- (void)setAudioExpandCountPerBlock:(NSInteger)audioExpandCountPerBlock;


#pragma mark - BGM相关
/**
 * 设置BGM
 * @param url 音乐文件路径
 * @param loopback 是否伴奏只是本地播放，YES是只是本地播放，NO本地远端都能听到，支持循环播放
 * @param repeat   循环的次数，-1: 无限循环
 */
- (void)playMusicWithUrl:(NSString *)url
                loopback:(BOOL)loopback
                  repeat:(NSInteger)repeat;

/**
 * 停止播放背景音乐
 */
- (void)stopMusic;

/**
 * 暂停播放背景音乐
 */
- (void)pauseMusic;

/**
 * 恢复播放背景音乐
 */
- (void)resumeMusic;

/**
 * 设置麦克风的音量大小
 * @param volume 音量大小，1为正常音量，建议值为0~1，如果需要调大音量可以设置更大的值
 */
- (void)setMicVolume:(float)volume;

/**
 * 设置背景音乐的音量大小
 * @param volume 音量大小，1为正常音量，建议值为0~1，如果需要调大背景音量可以设置更大的值
 */
- (void)setMusicVolume:(float)volume;

/**
 * 获取音乐时长
 * @return 音乐时长（ms）
 */
- (NSInteger)getMusicDuration;

/**
 * 获取音乐当前播放时间
 * @return 音乐时长（ms）
 */
- (NSInteger)getMusicCurrentPosition;

/**
 * 指定音乐播放位置
 * @return 操作是否成功。0 表示成功。
 */
- (NSInteger)setMusicPosition:(NSInteger)position;

/**
 * 指定音乐的音调
 * @return 操作是否成功。0 表示成功。
 */
- (int)setMusicPitch:(NSInteger)pitch;


#pragma mark - 音效相关
/**
 * 播放 effectId 的音效
 * @param effectId 音效Id
 * @param url 音效文件路径
 * @param loop 音效是否循环
 */
- (void)playEffectWithId:(int)effectId url:(NSString *)url loop:(BOOL)loop publish:(BOOL)publish;

/**
 * 停止 effectId 的音效
 * @param effectId 音效Id
 */
- (void)stopEffectWithId:(int)effectId;

/**
 * 停止所有的音效
 */
- (void)stopAllEffect;

/**
 * 设置所有音效的声音大小
 * @param volume 1为正常音量，建议值为0~1
 */
- (int)setEffectsVolume:(float)volume;

/**
 * 设置指定 effectId 音效的音量大小
 * @param effectId 音效Id
 * @param volume 1为正常音量，建议值为0~1
 */
- (int)setVolumeOfEffect:(int)effectId
              withVolume:(float)volume;

#pragma mark - 本地混流相关
/**
 * 设定本地混流配置
 * 目前最多支持两路混合
 * @param config
 */
- (void)setLocalMixConfig:(TXILiveRoomLocalMixConfig *)config;

/**
 * 清除本地混流配置
 */
- (void)clearLocalMixConfig;

#pragma mark - 旁路相关
- (void)startPublishCDNStream:(NSString *)url;
- (void)stopPublishCDNStream;
- (void)setMixTranscodingConfig:(TXILiveRoomTranscodingConfig *)config;
- (void)clearMixTranscodingConfig;

#pragma mark - 音视频数据统计相关
- (TXILiveRoomAVStatistic*)getAVStatistic;
@end


@protocol TXILiveRoomDelegateAdapter <TXILiveRoomDelegate>
@end


/**
 * 音频相关回调
 * <！！！注意！！！> 回调函数是在SDK内部线程同步抛出来的，请不要做耗时操作<！！！注意！！！>
 * 提示：请按需定义相关函数实现，减少不必要的性能损耗
 */
@protocol TXILiveRoomAudioDelegateAdapter <TXILiveRoomAudioDelegate>
@optional
/**
 * 播放器多路声音大小回调回调
 * @param speakers   播放者对象列表，包括userId 和 volume
 */
- (void)onReportAudioVolumeIndicationOfSpeakers:(NSArray<TXILiveRoomAudioVolumeInfo *> * _Nonnull)speakers;

/**
 * 音乐开始播放回调
 */
- (void)onMusicPlayBegin;

/**
 * 音乐完成播放回调
 */
- (void)onMusicPlayFinish;

/**
 * 音乐播放错误回调
 */
- (void)onMusicPlayError:(TXILiveRoomErrorCode)error;

/**
 * effectId 音效播放完成回调
 */
- (void)onEffectPlayFinish:(int)effectId;

/**
 * effectId 音效播放错误回调
 */
- (void)onEffectPlayError:(int)effectId error:(TXILiveRoomErrorCode)error;
@end

@interface TXILiveRoomAudioVolumeInfo : NSObject
@property (nonatomic,assign) UInt64 userId;
@property (nonatomic,assign) CGFloat volume;
@end

/**
 * TXILiveRoomParams 用于进房，其他参数用于混流
 */
@interface OneSecAdapterParams : TXILiveRoomParams
@property (nonatomic, assign) UInt32 appId;
@property (nonatomic, assign) UInt32 sdkAppId;
@property (nonatomic, assign) UInt32 bizId;
@property (nonatomic, assign) UInt64 userId;
@property (nonatomic, copy) NSData *userSig;
@end

NS_ASSUME_NONNULL_END
