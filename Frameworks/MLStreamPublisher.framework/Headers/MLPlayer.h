//
//  MLPlayer.h
//  MomoLive
//
//  Created by LiLingFeng on 9/18/16.
//  Copyright © 2016 wemomo.com. All rights reserved.
//

#ifndef MLPlayer_h
#define MLPlayer_h

#import <UIKit/UIKit.h>
#import "MLPlayerVideoDetail.h"
#import "MLMediaCommonDefine.h"
//#include "MLPublisherDefine.h"
//#import "MLPublisherOptions.h"
/*
自定义错误码：1，打开网络流10s  没打开，超时错误；6，网络流打开成功，播放过程中超过20s 没收到视频错误；7，打开流失败，DNS解析失败；8，打开流失败，DNS解析成功；9，打开流失败，流地址非rtmp或http 形式
        10: 播放器音频与视频缓冲，相差超过20s，定义为内部错误，原因未知。 操作: 重启播放器；
        11: 播放器音频解码过程中出现pts 无效情况，可能会引起 类型10错误。  暂无操作；
        12: iOS 硬解码失败
        13: 暂定网络错误
 
 ffmpeg 错误：
 AVERROR_BSF_NOT_FOUND = -1179861752
 AVERROR_BUG = -558323010
 AVERROR_DECODER_NOT_FOUND = -1128613112
 AVERROR_DEMUXER_NOT_FOUND = -1296385272
 AVERROR_ENCODER_NOT_FOUND = -1129203192
 AVERROR_EOF = -541478725
 AVERROR_EXIT = -1414092869
 AVERROR_FILTER_NOT_FOUND = -1279870712
 AVERROR_INVALIDDATA = -1094995529
 AVERROR_MUXER_NOT_FOUND = -1481985528
 AVERROR_OPTION_NOT_FOUND = -1414549496
 AVERROR_PATCHWELCOME = -1163346256
 AVERROR_PROTOCOL_NOT_FOUND = -1330794744
 AVERROR_STREAM_NOT_FOUND = -1381258232
 AVERROR_BUG2 = -541545794
 AVERROR_UNKNOWN = -1313558101
 */
typedef enum {
    noError = 0,
    pullTimeOut = 1,
} PullStopErrorCode;

typedef enum {
    PullUser_UserOffline_Quit = 0,
    PullUser_UserOffline_Dropped = 1,
    PullUser_UserOffline_BecomeAudience = 2,
} PullUserOfflineReason;

typedef enum {
    PullConference_Type_Agora = 0,
    PullConference_Type_Weila = 1,
} PullConferenceType;

@protocol MLPlayer;

@protocol MLPlayerDelegate <NSObject>
@optional
- (void)playerStartRendering:(id<MLPlayer>)player; //播放器开始渲染
- (void)playerDidFinish:(id<MLPlayer>)player; //播放正常结束
- (void)playerFailed:(id<MLPlayer>)player; //播放失败
- (void)playerStartStalling:(id<MLPlayer>)player; //播放卡顿开始
- (void)playerEndStalling:(id<MLPlayer>)player; //播放卡顿结束
- (void)player:(id<MLPlayer>)player didRecvUserInfo:(NSDictionary *)seiInfo; //视频流中收到其他业务的信息
- (void)player:(id<MLPlayer>)player didRecvUserInfoForScreens:(NSDictionary *)info; //视频流中收到其他业务的信息
- (void)player:(id<MLPlayer>)player didVideoSizeChanged:(CGSize)videoSize;
- (void)isPreparedToPlay:(id<MLPlayer>)player;
- (void)player:(id<MLPlayer>)player didRecvTS:(NSInteger)ts;
- (void)player:(id<MLPlayer>)player hostDidJoinChannel:(NSString *)channel;
- (void)player:(id<MLPlayer>)player didRemoteJoinChannel:(NSString*)channel withUid:(NSUInteger)uid;
- (void)player:(id<MLPlayer>)player didRemoteOfflineOfUid:(NSUInteger)uid reason:(PullUserOfflineReason)reason;
- (void)player:(id<MLPlayer>)player reportAudioVolumeIndicationOfSpeakers:(NSDictionary *)volumes;
- (void)player:(id<MLPlayer>)player streamPlayerFailedWithError:(NSError*)error;
- (CVPixelBufferRef)player:(id<MLPlayer>)player preprocessPixelbuffer:(CVPixelBufferRef)oldPixelbuffer;
- (void)conferencePlayer:(id<MLPlayer>)player didReceivedVideoForRemoteId:(NSString *)uid remoteView:(UIView *)remoteView;
- (NSString *)playerUpdateLiveAPIDomain:(id<MLPlayer>)player domainType:(MLMediaDomainTable)domainType;
- (CGPoint)playerGetUserLocation:(id<MLPlayer>)player;
- (void)conferencePlayer:(id<MLPlayer>)player didReceiveSEI:(NSString *)sei;
- (MLPublisherOptionRoomMode)playerGetCurrentRoomMode:(id<MLPlayer>)player;
- (void)conferencePlayerOnConnectionDidBanned:(id<MLPlayer>)player;
- (void)conferencePlayer:(id<MLPlayer>)player uid:(NSInteger)uid didReceiveMsg:(NSString *)msg;
@end

typedef void (^StopCompleteBlock)(BOOL finished);

@protocol MLPlayer <NSObject>
@property (nonatomic, weak, readwrite) id<MLPlayerDelegate> delegate; // 委托
@property (nonatomic, readonly) BOOL isPlaying; // 是否正在播放
@property (nonatomic, copy) StopCompleteBlock stopCompleteBlock;
@property (nonatomic, assign) BOOL enableReportAudioVolume; // SDK拉流上报声音大小回调

- (void)play; // 播放
- (void)pause; // 暂停
- (void)stop; // 结束
- (void)stopWithErrorCode:(PullStopErrorCode)errCode;
- (void)clean; // 清理资源
- (void)setMute:(BOOL)mute; // 禁音
- (void)recordAudio:(BOOL)enable; // 录音频
- (void)resetRenderFrame:(CGRect)frame;
- (CGSize)getVideoSize;
- (void)seek:(NSTimeInterval)time;
- (void) setPlayerConfigWithString:(NSString*)config; //观众端追延迟参数
- (void)setAudioPlaybackVolume:(float)volume;
- (void)setMediaConfig:(NSString *)mediaConfig;
@optional
// 获取播放器接收数据
- (long)getPlayerReceiveSize;
- (UIImage *)snapShot;
- (void)updateTransferType:(NSInteger)transferType;
- (void)updateCdnIp:(NSString*)cdnip;
@end

#endif /* MLPlayer_h */
