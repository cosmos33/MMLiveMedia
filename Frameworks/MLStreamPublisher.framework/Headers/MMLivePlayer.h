//
//  MMLivePlayer.h
//  Pods
//
//  Created by hrs on 2019/8/29.
//

#ifndef MMLivePlayer_h
#define MMLivePlayer_h
#import <Foundation/Foundation.h>
#import "MMCommonParam.h"

@class MMLivePlayer;
@protocol MMLivePlayerDelegate <NSObject>

@optional
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

/**
开始准备播放
 */
- (void)MMLivePlayerDidStartPrepare:(MMLivePlayer *)player;

/**
视频流size变化
*/
- (void)MMLivePlayer:(MMLivePlayer *)player didChangeSize:(CGSize)size;


@end

@interface MMLivePlayer : NSObject

/**
*  用户配置信息
*/
@property (nonatomic, strong) MMLiveUserConfig *userConfig;

/**
*  播放器回调
*/
@property (nonatomic, weak) id <MMLivePlayerDelegate> delegate;

/**
*  播放器初始化
*
* userConfig 相关的房间信息，目前对直播观看支持友好
*/
- (instancetype)initWithUserConfig:(MMLiveUserConfig *)userConfig;

/**
*  获取播放器状态
*/
- (MMLivePlayerStatus)getPlayStatus;

/**
*  设置播放view
*
* @param view  播放器渲染的父view
*/
- (void)setPlayerView:(UIView *)view;

/**
 *  移除视频渲染的view
 */
- (void)removePlayerView;

/**
*  启动从指定 URL 播放 音视频流
*
* @param url 完整的 URL（如果播放的是本地视频文件，这里传本地视频文件的完整路径）
*/
- (int)startPlay:(NSString *)url;

/**
* 停止播放音视频流
*/
- (int)stopPlay;

/**
*  设置音量
*
* @param volume 音量大小，取值范围0~1
*/
- (void)setVolume:(int)volume;

/**
*  设置静音
*/
- (void)setMute:(BOOL)enable;

/**
 设置追帧延迟
 @param enable 是否开启追延迟
 @param base 追延迟的base
 @param speedTrigger 慢丢的触发点
 @param dropTrigger 快丢的触发点
 @param speedRate 满丢速度
 */
- (void)setLowerLatencyEnable:(BOOL)enable
                         base:(int)base
                 speedTrigger:(int)speedTrigger
                  dropTrigger:(int)dropTrigger
                    speedRate:(double)speedRate;

/**
*  设置暂停播放
*
*/
- (void)pausePlay;

/**
*  恢复播放(暂停以后恢复使用)
*
*/
- (void)resumePlay;

/**
*  设置退后台是否停止渲染，在退后台之前设置
*
* @param shouldStopGLInBackground  YES 退后台停止播放;NO 退后台不停止播放
*/
- (void)setShouldStopGLInBackground:(BOOL)shouldStopGLInBackground ;

/**
*  设置是否停止渲染
*
* @param paused  YES 停止播放;NO 恢复渲染
*/
- (void)toggleGLPaused:(BOOL)paused;
@end

#endif /* MMLivePlayer_h */
