//
//  TXILiveRoomDefine.h
//  TXLiteAVSDK_Enterprise
//
//  Created by lijie on 2018/10/6.
//  Copyright © 2018年 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

/**
 * 错误代码
 * 表示SDK遇到不可恢复的错误，需要上层干预
 */
typedef NS_ENUM(NSInteger, TXILiveRoomErrorCode) {
    TXILiveRoomErrorNone                        = 0,
    TXILiveRoomErrorUpVideoAuthFailed           = 11001,  // 没有上行视频权限（请检查privateMapKey）
    TXILiveRoomErrorDisconnect                  = 11002,  // 网络连接断开（已经重试若干次，请检测网络设置）
    TXILiveRoomErrorOpenCameraFailed            = 11003,  // 打开摄像头失败
    TXILiveRoomErrorOpenMicFailed               = 11004,  // 打开麦克风失败
    TXILiveRoomErrorUnsupportResolution         = 11005,  // 不支持的视频分辨率
    TXILiveRoomErrorUnsupportSamplerate         = 11006,  // 不支持的音频采样率
    
    TXILiveRoomErrorTimeout                     = 11100,  // 超时通用，比如：进房超时
    TXILiveRoomErrorSwitchRoleFailed            = 11101,  // 切换角色失败
    TXILiveRoomErrorSigExpired                  = 11102,  // 签名过期（初始进房、网络重连、切换角色都有可能出现签名过期），应该在上层退房重新走一遍进房流程
    TXILiveRoomErrorSigFailed                   = 11103,  // 签名错误（请检查privateMapKey是否正确）
    
    TXILiveRoomErrorAudioPlayEngineNotStart     = 11201,  // 音频播放引擎还未启动
    TXILiveRoomErrorMusicInvalid                = 11202,  // music文件无效：如果是本地文件，请检查文件是否有效；如果是在线文件，请检查是否联网或在线文件是否有效
    TXILiveRoomErrorMusicNotSupportSampleRate   = 11203,  // music音频采样率不支持
    TXILiveRoomErrorEffectInvalid               = 11204,  // 音效文件无效
    TXILiveRoomErrorEffectNotSupportSampleRate  = 11205,  // 音效音频采样率不支持
    
    
    /***** 跨房间连麦相关 *****/
    TXILiveRoomErrorConnReachMaxRetryTimes      = -102033, // 跨房间连麦重试次数耗尽
    TXILiveRoomErrorConnRoomTimeout             = -102034, // 跨房间连麦请求超时
    TXILiveRoomErrorConnRoomFailed              = -102044, // 跨房间连麦失败
    TXILiveRoomErrorConnRoomNotExist            = -102046, // 被连麦房间不存在
    TXILiveRoomErrorConnUserNotExist            = -102048, // 被连麦用户不存在
};

/**
 * 警告代码
 * 表示SDK遇到可恢复的错误，仅仅通知上层，方便调试
 */
typedef NS_ENUM(NSInteger, TXILiveRoomWarningCode) {
    TXILiveRoomWarningNone                = 0,
    TXILiveRoomWarningReconnect           = 12001,  // 网络断连, 已启动自动重连
    TXILiveRoomWarningNetBusy             = 12002,  // 网络状况不佳：上行带宽太小，上传数据受阻
    TXILiveRoomWarningHWAcceFailed        = 12003,  // 硬件编解码失败，采用软编解码
    TXILiveRoomWarningVideoEncodeFailed   = 12004,  // 视频编码失败
    TXILiveRoomWarningAudioEncodeFailed   = 12005,  // 音频编码失败
    TXILiveRoomWarningVideoDecodeFailed   = 12006,  // 视频解码失败
    TXILiveRoomWarningAudioDecodeFailed   = 12007,  // 音频解码失败
    TXILiveRoomWarningCameraNotAuthorized = 12008,  // 无摄像头采集权限
    TXILiveRoomWarningCameraOccupy        = 12009,  // 摄像头被占用
    TXILiveRoomWarningMICNotAuthorized    = 12010,  // 无麦克风采集权限
    TXILiveRoomWarningMICOccupy           = 12011,  // 麦克风被占用
    TXILiveRoomWarningInternalError       = 12012,  // 内部错误
};

/**
 * 事件代码
 * 表示SDK相关的事件，用于上层选择性监听或者调试
 * tips：音频的编码默认使用的硬编码器，音频的解码默认使用的硬解码器
 */
typedef NS_ENUM(NSInteger, TXILiveRoomEventCode) {
    TXILiveRoomEventNone                         = 0,      // 无需关心的事件
    TXILiveRoomEventConnectSucc                  = 13001,  // 连接服务器成功
    TXILiveRoomEventOpenCameraSucc               = 13002,  // 打开摄像头成功
    TXILiveRoomEventStartVideoHardWareEncoder    = 13003,  // 视频硬编码器启动
    TXILiveRoomEventStartVideoSoftWareEncoder    = 13004,  // 视频软编码器启动
    TXILiveRoomEventStartVideoHardWareDecoder    = 13005,  // 视频硬解码器启动
    TXILiveRoomEventStartVideoSoftWareDecoder    = 13006,  // 视频软解码器启动
    TXILiveRoomEventReqVideoAuthSucc             = 13007,  // 请求上行视频位成功（被允许上行视频数据）
    TXILiveRoomEventResolutionChanged            = 13008,  // 视频分辨率改变
    TXILiveRoomEventVideoBitrateChanged          = 13009,  // 视频码率改变（指上行QOS调控）
    TXILiveRoomEventRenderFirstFrame             = 13010,  // 渲染首个视频帧(IDR)
    TXILiveRoomEventStartPlayAudioFrame          = 13011,  // 播放首个音频帧
    TXILiveRoomEventVideoPlayLag                 = 13012,  // 当前视频播放出现卡顿
    TXILiveRoomEventServerAddrChanged            = 13013,  // 服务器地址发生变更：ip+port
    TXILiveRoomEventServerTypeChanged            = 13014,  // 接入服务器类型变更
};

/**
 * 状态信息
 * 定时回调，方便用户调试
 */
@interface TXILiveRoomStatus : NSObject
@property (nonatomic, assign) UInt64 userId;                // 用户标识，如果是自己，表示上行统计，其他则是下行统计
@property (nonatomic, assign) NSInteger appCpu;             // 应用所占cpu，单位：1%
@property (nonatomic, assign) NSInteger sysCpu;             // 系统所占cpu，单位：1%
@property (nonatomic, assign) NSInteger rtt;                // rtt，单位：ms
@property (nonatomic, assign) NSInteger videoFps;           // 视频帧率（推流：编码帧率；播放：渲染帧率）
@property (nonatomic, assign) NSInteger videoWidth;         // 视频宽度
@property (nonatomic, assign) NSInteger videoHeight;        // 视频高度
@property (nonatomic, assign) NSInteger videoGop;           // 当前视频GOP，也就是每两个关键帧(I帧)间隔时长，单位：s
@property (nonatomic, assign) NSInteger netspeed;           // 网络速率，单位：kbps （推流：音视频编码码率之和-主动丢包码率；播放：音视频下载速度之和）
@property (nonatomic, assign) NSInteger videoBitrate;       // 视频码率，单位：kbps （推流：视频编码码率；播放：视频下载速度）
@property (nonatomic, assign) NSInteger audioBitrate;       // 音频码率，单位：kbps （推流：音频编码码率；播放：音频下载速度）
@property (nonatomic, assign) NSInteger audioTotalBytes;    // 音频累计字节数（推流：发送统计；播放：接收统计）
@property (nonatomic, assign) NSInteger videoTotalBytes;    // 视频累计字节数（推流：发送统计；播放：接收统计）
@property (nonatomic, assign) NSInteger audioCaptureBytes;  // 音频累计采集字节数
@property (nonatomic, assign) NSInteger audioEncodeBytes;   // 上行音频累计编码字节数
@property (nonatomic, assign) NSInteger videoEncodeBytes;   // 上行视频累计编码字节数
@property (nonatomic, assign) NSInteger audioCacheDuration; // 下行播放端音频缓存时长，单位：ms
@property (nonatomic, assign) NSInteger videoCacheDuration; // 下行播放端视频缓存时长，单位：ms
@property (nonatomic, assign) NSInteger videoJitterCacheFrames;  // 下行播放端视频抗抖动缓冲帧数
@property (nonatomic, assign) NSInteger videoDecoderCacheFrames; // 下行播放端视频解码器缓冲帧数
@property (nonatomic, assign) NSInteger avRecvTimeInterval; // 下行播放端音视频网络收包时间间隔，单位：ms
@property (nonatomic, assign) NSInteger avPlayTimeInterval; // 下行播放端音视频播放时间间隔，单位：ms
@property (nonatomic, assign) NSInteger videoUpCacheFrames; // 上行视频堆积帧数
@property (nonatomic, assign) NSInteger audioUpCacheFrames; // 上行音频堆积帧数
@property (nonatomic, assign) NSInteger audioBlockCnt;      // 下行播放端音频空窗期，统计周期内 累计空窗时长，单个空窗要大于20ms  单位ms
@property (nonatomic, assign) NSInteger audioExpandCnt;
@property (nonatomic, assign) NSInteger audioExpandBlockCnt;
@property (nonatomic, strong) NSString  *serverAddr;        // 服务器地址: ip+port
@property (nonatomic, assign) NSInteger audioLossRate;      // 【已废弃】音频丢包率（恢复前），单位：1/100
@property (nonatomic, assign) NSInteger videoLossRate;      // 【已废弃】视频丢包率（恢复前），单位：1/100
@property (nonatomic, assign) NSInteger upLossRate;         // 上行发送通道的丢包率，即网络丢包率，单位：1/100
@property (nonatomic, assign) NSInteger audioFecRatio;      // 音频FEC比例，单位：1/100
@property (nonatomic, assign) NSInteger videoFecRatio;      // 视频FEC比例，单位：1/100
@property (nonatomic, assign) NSInteger videoRecvFPS;       // 视频帧网络接收帧率
@property (nonatomic, assign) NSInteger videoFramesDrop;    // 因为晚到而被丢弃的视频帧数
@end

@interface TXILiveRoomUserAVStatistic : NSObject
@property (nonatomic, assign) UInt64 userId;                // 用户标识，如果是自己，表示上行统计，其他则是下行统计
@property (nonatomic, assign) NSInteger audioTotalBytes;    // 音频累计字节数（主播：发送，观众：拉流）
@property (nonatomic, assign) NSInteger videoTotalBytes;    // 视频累计字节数（主播：发送，观众：拉流）
@end

@interface TXILiveRoomAVStatistic : NSObject
@property (nonatomic, assign) NSInteger audioCapTotalBytes;                 // 音频采集累计字节数
@property (nonatomic, assign) NSInteger audioEncTotalBytes;                 // 音频编码累计字节数
@property (nonatomic, assign) NSInteger videoEncTotalBytes;                 // 视频编码累计字节数
@property (nonatomic, assign) NSInteger videoEncFrameTotalCount;            // 视频编码累计帧数
@property(nonatomic, copy) NSArray<TXILiveRoomUserAVStatistic *> * userAVStatistics; // 每个用户的音视频统计
@end


/**
 * 视频分辨率，宽 x 高
 */
typedef NS_ENUM(NSInteger, TXILiveRoomVideoResolution) {
    TXILIVEROOM_VIDEO_RESOLUTION_TYPE_360_640  = 0,
    TXILIVEROOM_VIDEO_RESOLUTION_TYPE_540_960  = 1,
    TXILIVEROOM_VIDEO_RESOLUTION_TYPE_720_1280 = 2,
    TXILIVEROOM_VIDEO_RESOLUTION_TYPE_640_360  = 3,
    TXILIVEROOM_VIDEO_RESOLUTION_TYPE_960_540  = 4,
    TXILIVEROOM_VIDEO_RESOLUTION_TYPE_1280_720 = 5,
    TXILIVEROOM_VIDEO_RESOLUTION_TYPE_320_480  = 6,
    TXILIVEROOM_VIDEO_RESOLUTION_TYPE_180_320  = 7,
    TXILIVEROOM_VIDEO_RESOLUTION_TYPE_270_480  = 8,
    TXILIVEROOM_VIDEO_RESOLUTION_TYPE_320_180  = 9,
    TXILIVEROOM_VIDEO_RESOLUTION_TYPE_480_270  = 10,
    TXILIVEROOM_VIDEO_RESOLUTION_TYPE_240_320  = 11,
    TXILIVEROOM_VIDEO_RESOLUTION_TYPE_360_480  = 12,
    TXILIVEROOM_VIDEO_RESOLUTION_TYPE_480_640  = 13,
    TXILIVEROOM_VIDEO_RESOLUTION_TYPE_320_240  = 14,
    TXILIVEROOM_VIDEO_RESOLUTION_TYPE_480_360  = 15,
    TXILIVEROOM_VIDEO_RESOLUTION_TYPE_640_480  = 16,
    TXILIVEROOM_VIDEO_RESOLUTION_TYPE_480_480  = 17,
    TXILIVEROOM_VIDEO_RESOLUTION_TYPE_270_270  = 18,
    TXILIVEROOM_VIDEO_RESOLUTION_TYPE_160_160  = 19,
};

/**
 * 手机Home键方向
 */
typedef NS_ENUM(NSInteger, TXILiveRoomHomeOrientation) {
    TXILiveRoomHomeOrientationRight = 0,
    TXILiveRoomHomeOrientationDown  = 1,
    TXILiveRoomHomeOrientationLeft  = 2,
    TXILiveRoomHomeOrientationUp    = 3,
};

/**
 * 视频显示模式
 */
typedef NS_ENUM(NSInteger, TXILiveRoomVideoRenderMode) {
    TXILiveRoomVideoRenderModeHidden = 0,  // 图像铺满屏幕，超出显示视窗的视频部分将被截掉
    TXILiveRoomVideoRenderModeFit    = 1,  // 图像长边填满屏幕，短边区域会被填充黑色
};

/**
 * 美颜风格
 */
typedef NS_ENUM(NSInteger, TXILiveRoomBeautyStyle) {
    TXILiveRoomBeautyStyleSmooth = 0, // 光滑
    TXILiveRoomBeautyStyleNature = 1, // 自然
    TXILiveRoomBeautyStylePiTu   = 2, // pitu美颜, 需要企业版SDK
};

/**
 * 音频采样率
 */
typedef NS_ENUM(NSInteger, TXILiveRoomAudioSampleRate) {
    TXILiveRoomAudioSampleRate16000 = 16000,
    TXILiveRoomAudioSampleRate32000 = 32000,
    TXILiveRoomAudioSampleRate44100 = 44100,
    TXILiveRoomAudioSampleRate48000 = 48000,
};

/**
 * 音频编码质量
 */
typedef NS_ENUM(NSInteger, TXILiveRoomAudioEncQuality) {
    TXILiveRoomAudioEncQualitySpeechStandard           =   1,   ///< 未开放使用。设定后与 TXILiveRoomAudioEncQualityMusicStandard 相同
    TXILiveRoomAudioEncQualityMusicStandard            =   2,   ///< 采样率 48khz、单声道、编码码率 50 kbps
    TXILiveRoomAudioEncQualityMusicHigh                =   3,   ///< 采样率 48khz、双声道、编码码率 128 kbps
};

/**
 * 声音播放模式
 */
typedef NS_ENUM(NSInteger, TXILiveRoomAudioMode) {
    TXILiveRoomAudioModeSpeakerphone  =   0,   // 扬声器
    TXILiveRoomAudioModeEarpiece      =   1,   // 听筒
};

/**
 * 场景
 */
typedef NS_ENUM(NSInteger, TXILiveRoomScenario) {
    TXILiveRoomScenarioChat        = 1, // 聊天室
    TXILiveRoomScenarioLive        = 2, // 直播
};

/**
 * 房间角色
 * 大主播和小主播(或者副麦)的角色都是”主播“，其他则是”观众“
 * 注意：主播可以收发语音/视频流，而观众只能接收语音/视频，无法发送
 */
typedef NS_ENUM(NSInteger, TXILiveRoomRole) {
    TXILiveRoomRoleBroadcaster     = 1, // 主播
    TXILiveRoomRoleAudience        = 2, // 观众
};

/**
 * 音视频通话的通话能力权限位
 * 建议这样填：
 * 大主播：TXIliveRoomAuthBitsDefaul
 * 小主播/观众：TXIliveRoomAuthBitsJoinRoom | TXIliveRoomAuthBitsSendAudio | TXIliveRoomAuthBitsRecvAudio | TXIliveRoomAuthBitsSendCameraVideo | TXIliveRoomAuthBitsRecvCameraVideo | TXIliveRoomAuthBitsSendScreenVideo | TXIliveRoomAuthBitsRecvScreenVideo
 *
 */
typedef NS_ENUM(NSInteger, TXIliveRoomAuthBits) {
    TXIliveRoomAuthBitsDefaul             = -1,          // 所有权限
    TXIliveRoomAuthBitsCreateRoom         = 0x00000001,  // 创建房间权限。
    TXIliveRoomAuthBitsJoinRoom           = 0x00000002,  // 加入房间的权限。
    TXIliveRoomAuthBitsSendAudio          = 0x00000004,  // 发送音频的权限。
    TXIliveRoomAuthBitsRecvAudio          = 0x00000008,  // 接收音频的权限。
    TXIliveRoomAuthBitsSendCameraVideo    = 0x00000010,  // 发送摄像头视频(也就是来至摄像头设备AVCameraDevice或外部视频捕获设备AVExternalCapture的视频)的权限。
    TXIliveRoomAuthBitsRecvCameraVideo    = 0x00000020,  // 接收摄像头视频(也就是来至摄像头设备AVCameraDevice或外部视频捕获设备AVExternalCapture的视频)的权限。
    TXIliveRoomAuthBitsSendScreenVideo    = 0x00000040,  // 发送屏幕视频(也就是捕获计算机屏幕画面所得到的视频)的权限。
    TXIliveRoomAuthBitsRecvScreenVideo    = 0x00000080,  // 接收屏幕视频(也就是捕获计算机屏幕画面所得到的视频)的权限。
};

/**
 * 自定义采集模式
 */
typedef NS_ENUM(NSInteger, TXILiveRoomCustomModeType) {
    TXILiveRoomCustomModeTypeNone         = 0,  // 默认，客户使用SDK提供的音视频采集
    TXILiveRoomCustomModeTypeAudio        = 1,  // 客户自定义音频采集
    TXILiveRoomCustomModeTypeVideo        = 2,  // 客户自定义视频采集
};

/**
 * 主播退房原因
 * onRoomBroadcasterOut会带上对应的值
 */
typedef NS_ENUM(NSInteger, TXILiveRoomOfflineReason) {
    TXILiveRoomOfflineReasonQuit            = 0,  // 主播主动离开（包括切换角色为观众）
    TXILiveRoomOfflineReasonDropped         = 1,  // 主播掉线超时
    TXILiveRoomOfflineReasonKicked          = 2,  // 主播被踢
};

/**
 * 视频流类型
 */
typedef NS_ENUM(NSInteger, TXILiveRoomStreamType) {
    TXILiveRoomStreamTypeBig    = 0,    //大流
    TXILiveRoomStreamTypeSmall  = 1,    //小流
};

/**
 * 音量类型
 */
typedef NS_ENUM(NSInteger, TXILiveRoomAudioVolumeType) {
    TXILiveRoomAudioVolumeTypeCommunication = 0,    //通话音量
    TXILiveRoomAudioVolumeTypeMedia         = 1,    //媒体音量
    TXILiveRoomAudioVolumeTypeAuto          = 2,    //自动切换，麦上通话，麦下媒体
};


/**
 * 混流输出视频编码格式
 */
typedef NS_ENUM(NSInteger, TXILiveRoomMixVideoCodecType) {
    TXILiveRoomMixOutputVideoCodecTypeDefault = 0,    // 默认，264
    TXILiveRoomMixOutputVideoCodecTypeH264    = 1,    // 264
    TXILiveRoomMixOutputVideoCodecTypeH265    = 2,    // 265
};

/**
 * 进房参数
 */
@interface TXILiveRoomParams : NSObject
@property (nonatomic, strong) NSString             *roomName;      // 房间名称，最长长度为64字节。以下为支持的字符集范围（共 89 个字符）：
                                                                   // a-z，A-Z，0-9，space，!#$%&，()+，-，:;<=.，>?@[]，^_，{|}，~
@property (nonatomic, assign) TXIliveRoomAuthBits  privateMap;     // 权限位，默认为：TXIliveRoomAuthBitsDefaul
@property (nonatomic, strong) NSData               *privateMapKey; // 权限位加密串，详见：https://cloud.tencent.com/document/product/647/17275
@property (nonatomic, assign) TXILiveRoomScenario  roomScenario;   // 场景，默认 TXILiveRoomScenarioLive
@property (nonatomic, assign) TXILiveRoomRole      roomRole;       // 房间角色，默认 TXILiveRoomRoleAudience
@end


/**
 * 配置信息
 */
@interface TXILiveRoomConfig : NSObject

// 客户自定义采集模式，如果是音视频都是自定义采集，那么设置：
// customModeType = (TXILiveRoomCustomModeTypeAudio | TXILiveRoomCustomModeTypeVideo)
@property(nonatomic, assign) int customModeType;

/**
 * 发送自定义CMSampleBuffer的输出分辨率
 * 当设置此属性时，videoResolution自动失效
 * @warn 此值设置需与源SampleBuffer的画面比例一致，否则会引起画面变形
 * @warn 调用sendVideoSampleBuffer必须设置此值，或者设置autoSampleBufferSize＝YES
 */
@property(nonatomic, assign) CGSize sampleBufferSize;

// 设置YES时，调用sendVideoSampleBuffer输出分辨率等于输入分辨率, 默认值为NO
@property (nonatomic, assign) BOOL autoSampleBufferSize;

// Home键所在方向，用来切换横竖屏推流
@property (nonatomic, assign) TXILiveRoomHomeOrientation homeOrientation;

// 视频的渲染模式
@property (nonatomic, assign) TXILiveRoomVideoRenderMode renderMode;

// 视频采集帧率
@property (nonatomic, assign) int videoFps;

// 视频上行码率，单位：kbps
@property (nonatomic, assign) int videoBitrate;

// 视频分辨率
@property (nonatomic, assign) TXILiveRoomVideoResolution videoResolution;

// 音频编码参数
@property (nonatomic, assign) TXILiveRoomAudioEncQuality audioEncQuality;

// 播放器视频卡顿报警阈值，默认800，单位毫秒，
// 只有渲染间隔超过这个阈值的卡顿才会有 TXILiveRoomEventVideoPlayLag 通知
@property (nonatomic, assign) int videoBlockThreshold;

// App切后台后的推流帧率，最小值为1，最大值为20，默认5
@property (nonatomic, assign) int pauseFps;

// App切后台后的推流图片，图片最大尺寸不能超过1280*720
@property (nonatomic, strong) UIImage *pauseImg;

// 转推 codectype
@property (nonatomic, assign) TXILiveRoomMixVideoCodecType cdnVideoCodecType;
@end

@interface TXILiveRoomAudioFrame : NSObject
@property (nonatomic, strong) NSData *audioData;                          //音频数据
@property (nonatomic, assign) TXILiveRoomAudioSampleRate audioSampleRate; //采样率
@property (nonatomic, assign) int audioChannels;                          //声道数
@property (nonatomic, assign) int audioSamples;                           //当前frame采样点个数
@property (nonatomic, assign) UInt64 timestamp;                           //时间戳
@end


// 用于指定每一路视频画面的具体摆放位置
@interface TXILiveRoomMixUser : NSObject
// userId所在的roomId（跨房连麦需要特别注意）
@property(nonatomic, copy) NSString * roomId;
/// 参与混流的userId
@property(nonatomic, assign) long userId;
/// 图层位置x坐标（绝对像素值）
@property(nonatomic, assign) int x;
/// 图层位置y坐标（绝对像素值）
@property(nonatomic, assign) int y;
/// 图层位置宽度（绝对像素值）
@property(nonatomic, assign) int width;
/// 图层位置高度（绝对像素值）
@property(nonatomic, assign) int height;
/// 图层层次 （1-15） 不可重复
@property(nonatomic, assign) int zOrder;
/// 是否静音音频
@property(nonatomic, assign) bool isMuteAudio;
@end


@interface TXILiveRoomTranscodingConfig : NSObject
@property(nonatomic, assign) int videoWidth;       ///< 视频分辨率：宽
@property(nonatomic, assign) int videoHeight;      ///< 视频分辨率：高
@property(nonatomic, assign) int videoBitrate;     ///< 视频码率
@property(nonatomic, assign) int videoFramerate;   ///< 视频帧率
@property(nonatomic, assign) int videoGOP;         ///< 视频GOP，单位秒
@property(nonatomic, assign) TXILiveRoomMixVideoCodecType videoCodecType;   ///< 视频转码codec
@property(nonatomic, assign) bool enableBFrame;     ///< 视频输出是否加B帧，false 关闭 true 打开

@property(nonatomic, assign) int audioSampleRate;  ///< 音频采样率 48000
@property(nonatomic, assign) int audioBitrate;     ///< 音频码率   64K
@property(nonatomic, assign) int audioChannels;    ///< 声道数     2

@property(nonatomic, copy) NSString * backgroundPicUrl; ///< 背景图URL

@property(nonatomic, copy) NSString * mixExtraInfo; ///< SEI信息
@property(nonatomic, copy) NSArray<TXILiveRoomMixUser *> * mixUsers; ///< 混流配置
@end


// 用于指定每一路视频画面的具体摆放位置
@interface TXILiveRoomLocalMixUser : NSObject
/// 参与混流的userId
@property(nonatomic, assign) UInt64 userId;
/// 图层位置坐标以及大小，左上角为坐标原点(0,0) （绝对像素值）
@property(nonatomic, assign) CGRect rect;
@end


@interface TXILiveRoomLocalMixConfig : NSObject
@property(nonatomic, assign) BOOL onlyMixAudio;    ///< 仅混音频，开启之后，不会自动混合视频
@property(nonatomic, assign) int videoWidth;       ///< 视频分辨率：宽
@property(nonatomic, assign) int videoHeight;      ///< 视频分辨率：高
@property(nonatomic, copy) NSArray<TXILiveRoomLocalMixUser *> * mixUsers; ///< 混流配置
@end

