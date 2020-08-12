//
//  TXILiveRoomDelegate.h
//  TXLiteAVSDK_Enterprise
//
//  Created by lijie on 2018/10/6.
//  Copyright © 2018年 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "TXILiveRoomDefine.h"
#import <VideoToolbox/VideoToolbox.h>
#import <UIKit/UIKit.h>

@protocol TXILiveRoomDelegate <NSObject>
@optional

/**
 * 发生错误事件的回调
 * @param userId 用户标识
 * @param errCode 错误标识
 * @param errMsg 描述信息
 */
- (void)onError:(UInt64)userId errCode:(TXILiveRoomErrorCode)errCode errMsg:(NSString *)errMsg;

/**
 * 发生警告事件的回调
 * @param userId 用户标识
 * @param warningCode 警告标识
 * @param warningMsg 描述信息
 */
- (void)onWarning:(UInt64)userId warningCode:(TXILiveRoomWarningCode)warningCode warningMsg:(NSString *)warningMsg;

/**
 * 普通事件的回调
 * @param userId 用户标识
 * @param eventId 事件标识
 * @param eventMsg 描述信息
 */
- (void)onEvent:(UInt64)userId eventId:(TXILiveRoomEventCode)eventId eventMsg:(NSString *)eventMsg;

/**
 * 统计状态的回调
 * @param roomName 房间号
 * @param statusArray 状态数组，array[TXILiveRoomStatus]
 * @note 每2秒回调一次，用于调试
 */
- (void)onStatus:(NSString *)roomName statusArray:(NSArray *)statusArray;

/**
 * 加入房间成功的回调
 * @param roomName 房间号
 * @note 对于大主播而言，则是创建并进入房间成功的回调
 */
- (void)onJoinRoomSuccess:(NSString *)roomName;

/**
 * 加入房间失败的回调
 * @param roomName 房间号
 * @param errCode 错误标识
 * @param errMsg 描述信息
 */
- (void)onJoinRoomFailed:(NSString *)roomName errCode:(TXILiveRoomErrorCode)errCode errMsg:(NSString *)errMsg;


/**
* 被 T 出房间
* @param roomName 房间号
* @param userId userId
*/
- (void)onKickOut:(NSString *)roomName userId:(UInt64)userId;

/**
 * 退出房间成功的回调
 * @param roomName 房间号
 */
- (void)onQuitRoomSuccess:(NSString *)roomName;

/**
 * 退出房间失败的回调
 * @param roomName 房间号
 * @param errCode 错误标识
 * @param errMsg 描述信息
 */
- (void)onQuitRoomFailed:(NSString *)roomName errCode:(TXILiveRoomErrorCode)errCode errMsg:(NSString *)errMsg;

/**
 * 跨房连麦的回调
 * @param userId 对端的主播标识
 * @param errCode 错误码 0: 成功  其他: 失败，含义请参考 TXILiveRoomErrorCode
 * @param errMsg 错误描述
 */
- (void)onConnectOtherRoom:(UInt64)userId errCode:(NSInteger)errCode errMsg:(NSString *)errMsg;

/**
 * 断开跨房连麦回调
 * @param errCode 错误码 0: 成功  其他: 失败，含义请参考 TXILiveRoomErrorCode
 * @param errMsg 错误描述
 */
- (void)onDisconnectOtherRoom:(NSInteger)errCode errMsg:(NSString *)errMsg;

/**
 * 主播进入房间的回调
 * @param roomName 房间号
 * @param userId 用户标识
 * @note 有新主播加入房间时(包括观众切换为主播时)产生
 */
- (void)onRoomBroadcasterIn:(NSString *)roomName userId:(UInt64)userId;

/**
 * 主播离开房间的回调
 * @param roomName 房间号
 * @param userId 用户标识
 * @param reason 原因
 * @note 有主播离开房间时(包括主播切换为观众时)产生
 */
- (void)onRoomBroadcasterOut:(NSString *)roomName userId:(UInt64)userId reason:(TXILiveRoomOfflineReason)reason;

/**
 * 主播mute/unmute视频的回调
 * @param roomName 房间号
 * @param userId 用户标识
 * @param muted YES：该用户已暂停发送其视频流  NO：该用户已恢复发送其视频流
 */
- (void)onRoomVideoMuted:(NSString *)roomName userId:(UInt64)userId muted:(BOOL)muted;

/**
 * 主播mute/unmute音频的回调
 * @param roomName 房间号
 * @param userId 用户标识
 * @param muted YES：该用户已暂停发送其音频流  NO：该用户已恢复发送其音频流
 */
- (void)onRoomAudioMuted:(NSString *)roomName userId:(UInt64)userId muted:(BOOL)muted;

/**
 * 切换角色成功的回调
 * @param roomName 房间号
 * @param oldRole 切换前的角色
 * @param newRole 切换后的角色
 */
- (void)onRoomRoleChanged:(NSString *)roomName oldRole:(TXILiveRoomRole)oldRole newRole:(TXILiveRoomRole)newRole;

/**
* QoSx 下发的视频参数
* @param roomName 房间号
* @param fps 帧率
* @param bitrate 码率
*/
- (void)onRoomVideoQosChanged:(NSString *)roomName fps:(NSInteger)fps bitrate:(NSInteger)bitrate;
/**
 * 收到自定义消息
 * @param roomName 房间号
 * @param userId 用户标识
 * @param msg 自定义消息
 * @note 该消息由 sendMessageEx 发送
 */
- (void)onRecvMessage:(NSString *)roomName userId:(UInt64)userId msg:(NSData *)msg;

/**
 * 收到数据流消息
 * @param roomName 房间号
 * @param userId 用户标识
 * @param streamId 数据流ID
 * @param message 消息数据
 * @note 该消息由 sendStreamMessage 发送
 */
- (void)onRecvStreamMessage:(NSString *)roomName userId:(UInt64)userId streamId:(NSInteger)streamId message:(NSData *)message;

/**
 * 接收对方数据流消息错误的回调
 * @param roomName 房间号
 * @param userId 用户标识
 * @param streamId 数据流ID
 * @param errCode 错误码，当前版本为-1
 * @param missed 丢失的消息数量
 */
- (void)onStreamMessageError:(NSString *)roomName userId:(UInt64)userId streamId:(NSInteger)streamId errCode:(NSInteger)errCode missed:(NSInteger)missed;

/// @name 旁路转推和混流回调

- (void)onStartPublishCDNStream:(int)err errMsg:(NSString *)errMsg;

- (void)onStopPublishCDNStream:(int)err errMsg:(NSString *)errMsg;

- (void)onSetMixTranscodingConfig:(int)err errMsg:(NSString *)errMsg;

- (void)onClearMixTranscodingConfig:(int)err errMsg:(NSString *)errMsg;

@end


/**
 * 音频相关回调
 * <！！！注意！！！> 回调函数是在SDK内部线程同步抛出来的，请不要做耗时操作<！！！注意！！！>
 * 提示：请按需定义相关函数实现，减少不必要的性能损耗
 */
@protocol TXILiveRoomAudioDelegate <NSObject>
@optional

/**
 * 原始声音的回调
 * @see audioFrame
 * @note 此接口回调的音频数据可修改
 */
- (BOOL)onRecordAudioFrame:(TXILiveRoomAudioFrame *)audioFrame;

/**
 * 播放声音的回调，如果您的自定义数据需要播放，请把数据放在data里面
 * @see audioFrame
 * @note 此接口回调的音频数据可修改
 */
- (BOOL)onPlaybackAudioFrame:(TXILiveRoomAudioFrame *)audioFrame;


/**
 * 播放端的声音回调
 * @param userId     用户标识
 * @see audioFrame
 * @note 此接口回调的音频数据不可修改
 */
- (BOOL)onPlayPcmData:(UInt64)userId audioFrame:(TXILiveRoomAudioFrame *)audioFrame;

@end

@protocol TXILiveRoomVideoRenderDelegate <NSObject>

@optional
/**
 * 视频渲染对象回调
 * @param pixelBuffer   渲染图像
 * @return              返回YES则SDK不再显示；返回NO则SDK渲染模块继续渲染
 */
- (BOOL)onPreRenderPixelBuffer:(CVPixelBufferRef)pixelBuffer userId:(UInt64)userId;

@end




