
/*
 * Module:   TRTCStatistics @ TXLiteAVSDK
 *
 * Function: 腾讯云视频通话功能的质量统计相关接口
 *
 */
///@addtogroup TRTCCloudDef_ios
///@{

/// 自己本地的音视频统计信息
@interface TRTCLocalStatistics : NSObject

/// 视频宽度
@property (nonatomic, assign) uint32_t  width;

/// 视频高度
@property (nonatomic, assign) uint32_t  height;

/// 帧率（fps）
@property (nonatomic, assign) uint32_t  frameRate;

/// 视频发送码率（Kbps）
@property (nonatomic, assign) uint32_t  videoBitrate;

/// 音频采样率（Hz）
@property (nonatomic, assign) uint32_t  audioSampleRate;

/// 音频发送码率（Kbps）
@property (nonatomic, assign) uint32_t  audioBitrate;

/// 流类型（大画面 | 小画面 | 辅路画面）
@property (nonatomic, assign) TRTCVideoStreamType  streamType;
@end


/// 远端成员的音视频统计信息
@interface TRTCRemoteStatistics : NSObject

/// 用户 ID，指定是哪个用户的视频流
@property (nonatomic, retain) NSString* userId;

///【字段含义】音频流的总丢包率（％）
/// audioPacketLoss 代表音频流历经“主播 => 云端 => 观众”这样一条完整的传输链路后，最终在观众端统计到的丢包率。
/// audioPacketLoss 越小越好，丢包率为0即表示该路音频流的所有数据均已经完整地到达了观众端。
///如果出现了 downLoss == 0 但 audioPacketLoss != 0 的情况，说明该路音频流在“云端=>观众”这一段链路上没有出现丢包，但是在“主播=>云端”这一段链路上出现了不可恢复的丢包。
@property(nonatomic, assign) uint32_t audioPacketLoss;

///【字段含义】该路视频流的总丢包率（％）
/// videoPacketLoss 代表该路视频流历经“主播 => 云端 => 观众”这样一条完整的传输链路后，最终在观众端统计到的丢包率。
/// videoPacketLoss 越小越好，丢包率为0即表示该路视频流的所有数据均已经完整地到达了观众端。
///如果出现了 downLoss == 0 但 videoPacketLoss != 0 的情况，说明该路视频流在“云端=>观众”这一段链路上没有出现丢包，但是在“主播=>云端”这一段链路上出现了不可恢复的丢包。
@property(nonatomic, assign) uint32_t videoPacketLoss;

/// 视频宽度
@property (nonatomic, assign) uint32_t  width;

/// 视频高度
@property (nonatomic, assign) uint32_t  height;

/// 接收帧率（fps）
@property (nonatomic, assign) uint32_t  frameRate;

/// 视频码率（Kbps）
@property (nonatomic, assign) uint32_t  videoBitrate;

/// 音频采样率（Hz）
@property (nonatomic, assign) uint32_t  audioSampleRate;

/// 音频码率（Kbps）
@property (nonatomic, assign) uint32_t  audioBitrate;

/// 播放时延（ms）
@property (nonatomic, assign) uint32_t  jitterBufferDelay;

/// 端对端延迟（ms）
/// 该字段为全链路延迟统计，链路包含：采集->编码->网络传输->接收->缓冲->解码->播放
/// 延迟以 audio 为基准进行计算。需要本地和远端均为8.5版本以上时才生效
/// 若远端用户为低版本，对应延迟会回调为0，此时代表无效值
@property (nonatomic, assign) uint32_t  point2PointDelay;

/// 音频播放卡顿累计时长（ms）
@property (nonatomic, assign) uint32_t  audioTotalBlockTime;

/// 音频播放卡顿率，音频卡顿的累计时长占音频总播放时长的百分比 (%)
@property (nonatomic, assign) uint32_t  audioBlockRate;

/// 视频播放卡顿累计时长（ms）
@property (nonatomic, assign) uint32_t  videoTotalBlockTime;

/// 音频播放卡顿率，视频卡顿累计时长占视频总播放时长的百分比（%）
@property (nonatomic, assign) uint32_t  videoBlockRate;

///【字段含义】该路音视频流的总丢包率（％）
///已废弃，不推荐使用；建议使用 audioPacketLoss、videoPacketLoss 替代
@property(nonatomic, assign) uint32_t finalLoss __attribute__((deprecated("Use audioPacketLoss and videoPacketLoss instead.")));

///【字段含义】视频流类型（高清大画面|低清小画面|辅流画面）
@property (nonatomic, assign) TRTCVideoStreamType  streamType;

@end


/// 统计数据
@interface TRTCStatistics : NSObject

/// C -> S 上行丢包率（％），
/// 该值越小越好，例如，丢包率为 0 表示网络很好，
/// 丢包率为 30@% 则意味着 SDK 向服务器发送的数据包中会有 30@% 丢失在上行传输中。
@property (nonatomic, assign) uint32_t  upLoss;

/// S -> C 下行丢包率（％），
/// 该值越小越好，例如，丢包率为0表示网络很好，
/// 丢包率为 30@% 则意味着 SDK 向服务器发送的数据包中会有 30@% 丢失在下行传输中。
@property (nonatomic, assign) uint32_t  downLoss;

/// 当前 App 的 CPU 使用率（％）
@property (nonatomic, assign) uint32_t  appCpu;

/// 当前系统的 CPU 使用率（％）
@property (nonatomic, assign) uint32_t  systemCpu;

/// 延迟（毫秒），
/// 指 SDK 到腾讯云服务器的一次网络往返时间，该值越小越好。
/// 一般低于50ms的 rtt 相对理想，而高于100ms的 rtt 会引入较大的通话延时。
/// 由于数据上下行共享一条网络连接，所以 local 和 remote 的 rtt 相同。
@property (nonatomic, assign) uint32_t  rtt;

/// 总接收字节数（包含信令及音视频）
@property (nonatomic, assign) uint64_t  receivedBytes;

/// 总发送字节数（包含信令及音视频）
@property (nonatomic, assign) uint64_t  sentBytes;

/// 自己本地的音视频统计信息，可能有主画面、小画面以及辅路画面等多路的情况，因此是一个数组
@property (nonatomic, strong) NSArray<TRTCLocalStatistics*>*  localStatistics;

///远端成员的音视频统计信息，可能有主画面、小画面以及辅路画面等多路的情况，因此是一个数组
@property (nonatomic, strong) NSArray<TRTCRemoteStatistics*>* remoteStatistics;
@end
///@}
