//
//  MMCommonProtocols.h
//  MLStreamPublisher
//
//  Created by hrs on 2020/2/10.
//

#ifndef MMCommonProtocols_h
#define MMCommonProtocols_h
#import <Foundation/Foundation.h>
#pragma mark - MMlivePlayerDelegate
@class MMLivePlayer;
@protocol MMLivePlayerDelegate <NSObject>
/**
开始渲染
*/
- (void)MMLivePlayerStartRendering:(MMLivePlayer *)player;

/**
正常结束
*/
- (void)MMLivePlayerDidFinish:(MMLivePlayer *)player;

/**
播放错误
*/
- (void)MMLivePlayerFailed:(MMLivePlayer *)player;

/**
开始缓冲
*/
- (void)MMLivePlayerStartBuffer:(MMLivePlayer *)player;

/**
结束缓冲
*/
- (void)MMLivePlayerEndBuffer:(MMLivePlayer *)player;

/**
收到透传sei
*/
- (void)MMLivePlayer:(MMLivePlayer *)player didRecvUserInfo:(NSDictionary *)seiInfo;
@end


#pragma mark - MMLivePusherDelegate
@protocol MMLivePusherDelegate <NSObject>

/**
推流器开始推流
*/
- (void)MMLivePusherDidStartPushing:(id)pusher error:(NSError*)error;

/**
推流器停止推流
*/
- (void)MMLivePusherDidStopPushing:(id)pusher error:(NSError*)error;

/**
推流器推流失败
*/
- (void)MMLivePusherFailed:(id)pusher error:(NSError*)error;

/**
推流卡顿开始
*/
- (void)MMLivePusherStartBuffer:(id)pusher error:(NSError*)error;

/**
推流卡顿结束
*/
- (void)MMLivePusherStopBuffer:(id)pusher error:(NSError*)error;

/**
用户自己加入频道
*/
- (void)MMLivePusher:(id)pusher hostDidJoinChannel:(NSString *)channel;

/**
其他用户加入频道
*/
- (void)MMLivePusher:(id)pusher didRemoteJoinChannel:(NSString *)channel withUid:(NSUInteger)uid;

/**
rtmp推流器已经有数据发出
*/
- (void)MMLivePusherDidStartRtmpPushing:(id)pusher error:(NSError*)error;

/**
其他用户退出频道
*/
- (void)MMLivePusher:(id)pusher memberExitWithUserId:(NSString *)userId reason:(NSInteger)reason;

/**
用户离开频道
*/
- (void)MMLivePusherDidLeaveChannel:(id)pusher;

/**
连麦成功
*/
- (void)MMLivePusher:(id)pusher connectionSuccessWithHostId:(NSString *)hostId guestId:(NSString *)guestId;

/**
其他用户掉线
*/
- (void)MMLivePusher:(id)pusher didOfflineOfUid:(NSString *)uid;

/**
收到其他用户第一帧视频
*/
- (void)MMLivePusher:(id)pusher didReceivedVideoForRemoteId:(NSString *)uid remoteView:(UIView *)remoteView;

/**
其他用户声音是否静音
*/
- (void)MMLivePusher:(id)pusher didRemoteAudioMuted:(BOOL)muted remoteUid:(NSUInteger)uid;

/**
其他用户画面是否关闭
*/
- (void)MMLivePusher:(id)pusher didRemoteVideoMuted:(BOOL)muted remoteUid:(NSUInteger)uid;

/**
推流数据到达cdn（经验值），只用于平滑切换的优化方案
*/
- (void)MMLivePusherDidReceivedCDN:(id)pusher frameCount:(NSUInteger)frameCount;
@end

#endif /* MMCommonProtocols_h */
