//
//  MMCommonProtocols.h
//  MLStreamPublisher
//
//  Created by hrs on 2020/2/10.
//

#ifndef MMCommonProtocols_h
#define MMCommonProtocols_h
#import <Foundation/Foundation.h>
#import "MMCommonParam.h"
#pragma mark - MMLiveEngineDelegate

@class MMLiveEngine;
@protocol MMLiveEngineDelegate <NSObject>

/**
推流器开始推流
*/
- (void)MMLiveEnginePushStarting:(MMLiveEngine *)engine type:(MMLivePushType)type error:(NSError*)error;

/**
推流器停止推流
*/
- (void)MMLiveEnginePushStopped:(MMLiveEngine *)engine type:(MMLivePushType)type error:(NSError*)error;

/**
推流器推流失败
*/
- (void)MMLiveEnginePushFailed:(MMLiveEngine *)engine type:(MMLivePushType)type error:(NSError*)error;

/**
推流卡顿开始
*/
- (void)MMLiveEngineBufferStart:(MMLiveEngine *)engine type:(MMLivePushType)type error:(NSError*)error;

/**
推流卡顿结束
*/
- (void)MMLiveEngineBufferStopped:(MMLiveEngine *)engine type:(MMLivePushType)type error:(NSError*)error;

/**
推流数据到达cdn（经验值），只用于平滑切换的优化方案
*/
- (void)MMLiveEnginePushReplaced:(MMLiveEngine *)engine type:(MMLivePushType)type error:(NSError*)error;

/**
用户自己加入频道
*/
- (void)MMLiveEngine:(MMLiveEngine *)engine hostDidJoinChannel:(NSString *)channel type:(MMLivePushType)type;

/**
其他用户加入频道
*/
- (void)MMLiveEngine:(MMLiveEngine *)engine didMemberJoinChannel:(NSString *)channel withUid:(NSUInteger)uid type:(MMLivePushType)type;

/**
其他用户退出频道
*/
- (void)MMLiveEngine:(MMLiveEngine *)engine MemberLeaveWithUserId:(NSString *)userId reason:(NSInteger)reason type:(MMLivePushType)type;

/**
用户离开频道
*/
- (void)MMLiveEnginehostDidLeaveChannel:(MMLiveEngine *)engine type:(MMLivePushType)type;

/**
其他用户掉线
*/
- (void)MMLiveEngine:(MMLiveEngine *)engine didMemberOfflineWithUid:(NSString *)uid type:(MMLivePushType)type;

/**
收到其他用户第一帧视频
*/
- (void)MMLiveEngine:(MMLiveEngine *)engine didReceivedFirstVideoFrameWithRemoteId:(NSString *)uid remoteView:(UIView *)remoteView type:(MMLivePushType)type;

/**
其他用户声音是否静音
*/
- (void)MMLiveEngine:(MMLiveEngine *)engine didMemberAudioMuted:(BOOL)muted remoteUid:(NSUInteger)uid type:(MMLivePushType)type;

/**
其他用户画面是否关闭
*/
- (void)MMLiveEngine:(MMLiveEngine *)engine didMemberVideoMuted:(BOOL)muted remoteUid:(NSUInteger)uid type:(MMLivePushType)type;

/**
连线错误
*/
- (void)MMLiveEngine:(MMLiveEngine *)engine didOccurError:(RTCErrorCode)errorCode type:(MMLivePushType)type;

/**
开始渲染
*/
- (void)MMLiveEnginePlayStartRendering:(MMLiveEngine *)engine;

/**
正常结束
*/
- (void)MMLiveEnginePlayDidFinish:(MMLiveEngine *)engine;

/**
播放错误
*/
- (void)MMLiveEnginePlayFailed:(MMLiveEngine *)engine;

/**
开始缓冲
*/
- (void)MMLiveEnginePlayStartBuffer:(MMLiveEngine *)engine;

/**
结束缓冲
*/
- (void)MMLiveEnginePlayEndBuffer:(MMLiveEngine *)engine;

/**
收到透传sei
*/
- (void)MMLiveEngine:(MMLiveEngine *)engine didRecvPlayUserInfo:(NSDictionary *)seiInfo;

/**
开始准备播放
 */
- (void)MMLiveEnginePlayDidStartPrepare:(MMLiveEngine *)engine;

/**
视频流size变化
*/
- (void)MMLiveEngine:(MMLiveEngine *)engine didChangePlaySize:(CGSize)size;


@end

#endif /* MMCommonProtocols_h */
