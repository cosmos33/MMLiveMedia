//
//  MMLiveEngine.h
//  Pods
//
//  Created by hrs on 2019/8/29.
//

#ifndef MMLiveEngine_h
#define MMLiveEngine_h
#import <Foundation/Foundation.h>
#import <MLVideoProcessing/MLCameraSource.h>
#import "MMCommonParam.h"

#pragma mark - MMLiveEngineDelegate

@class MMLiveEngine;
@protocol MMLiveEnginePusherDelegate <NSObject>

/**
推流器开始推流
*/
- (void)MMLiveEnginePusherStarting:(MMLiveEngine *)engine type:(MMLivePushType)type error:(NSError*)error;

/**
推流器停止推流
*/
- (void)MMLiveEnginePusherStopped:(MMLiveEngine *)engine type:(MMLivePushType)type error:(NSError*)error;

/**
推流器推流失败
*/
- (void)MMLiveEnginePusherFailed:(MMLiveEngine *)engine type:(MMLivePushType)type error:(NSError*)error;

/**
推流卡顿开始
*/
- (void)MMLiveEnginePusherBufferStart:(MMLiveEngine *)engine type:(MMLivePushType)type error:(NSError*)error;

/**
推流卡顿结束
*/
- (void)MMLiveEnginePusherBufferStopped:(MMLiveEngine *)engine type:(MMLivePushType)type error:(NSError*)error;

/**
推流数据到达cdn（经验值），只用于平滑切换的优化方案
*/
- (void)MMLiveEnginePusherReplaced:(MMLiveEngine *)engine type:(MMLivePushType)type error:(NSError*)error;

/**
用户自己加入频道
*/
- (void)MMLiveEnginePusher:(MMLiveEngine *)engine localDidJoinChannel:(NSString *)channel type:(MMLivePushType)type;

/**
其他用户加入频道
*/
- (void)MMLiveEnginePusher:(MMLiveEngine *)engine didMemberJoinChannel:(NSString *)channel withUid:(NSUInteger)uid type:(MMLivePushType)type;

/**
其他用户退出频道
*/
- (void)MMLiveEnginePusher:(MMLiveEngine *)engine MemberLeaveWithUserId:(NSString *)userId reason:(NSInteger)reason type:(MMLivePushType)type;

/**
用户离开频道
*/
- (void)MMLiveEnginePusherLocalDidLeaveChannel:(MMLiveEngine *)engine type:(MMLivePushType)type;

/**
其他用户掉线
*/
- (void)MMLiveEnginePusher:(MMLiveEngine *)engine didMemberOfflineWithUid:(NSString *)uid type:(MMLivePushType)type;

/**
收到其他用户第一帧视频
*/
- (void)MMLiveEnginePusher:(MMLiveEngine *)engine didReceivedFirstVideoFrameWithRemoteId:(NSString *)uid remoteView:(UIView *)remoteView type:(MMLivePushType)type;

/**
其他用户声音是否静音
*/
- (void)MMLiveEnginePusher:(MMLiveEngine *)engine didMemberAudioMuted:(BOOL)muted remoteUid:(NSUInteger)uid type:(MMLivePushType)type;

/**
其他用户画面是否关闭
*/
- (void)MMLiveEnginePusher:(MMLiveEngine *)engine didMemberVideoMuted:(BOOL)muted remoteUid:(NSUInteger)uid type:(MMLivePushType)type;

/**
连线错误
*/
- (void)MMLiveEnginePusher:(MMLiveEngine *)engine didOccurError:(RTCErrorCode)errorCode type:(MMLivePushType)type;

@end

@protocol MMLiveEnginePlayerDelegate <NSObject>

/**
播放器开始渲染
*/
- (void)MMLiveEnginePlayerStartRendering:(MMLiveEngine *)engine;

/**
播放器正常结束
*/
- (void)MMLiveEnginePlayerDidFinish:(MMLiveEngine *)engine;

/**
播放器播放错误
*/
- (void)MMLiveEnginePlayerFailed:(MMLiveEngine *)engine;

/**
播放器开始缓冲
*/
- (void)MMLiveEnginePlayerStartBuffer:(MMLiveEngine *)engine;

/**
播放器结束缓冲
*/
- (void)MMLiveEnginePlayerEndBuffer:(MMLiveEngine *)engine;

/**
播放器收到透传sei
*/
- (void)MMLiveEnginePlayer:(MMLiveEngine *)engine didRecvUserInfo:(NSDictionary *)seiInfo;

/**
播放器开始准备播放
 */
- (void)MMLiveEnginePlayerDidStartPrepare:(MMLiveEngine *)engine;

/**
播放器收到视频流size变化
*/
- (void)MMLiveEnginePlayer:(MMLiveEngine *)engine didChangeSize:(CGSize)size;


@end


@protocol MLStreamMediaDataConsumer;
@interface MMLiveEngine : NSObject <MLStreamMediaDataConsumer>

/**
设置配置信息
@param appId 业务id
@param secret 秘钥
@param appVer app版本号
@param userId 用户id
@param completeHandler 回调 (errorCode: 0 - 成功, 1 - 参数异常, 2 - 缓存信息重复, 3 - 配置信息拉取失败, 4 - appid和secret校验失败)
*/
+ (void)setConfigWithAppId:(NSString *)appId
                    secret:(NSString *)secret
                    appVer:(NSString *)appVer
                    userId:(NSString *)userId
           completeHandler:(void (^)(int errorCode))completeHandler;

/**
清理配置信息
*/
+ (void)cleanConfig;

#pragma mark - 预览

@property (nonatomic, readonly) id sourceHandle;
/**
* 设置使能视频外部采集
*
* @param enable YES 打开SDK外部采集， NO SDK自采集
*/
- (void) setEnableExternalCapture:(BOOL)enable;

/**
* 设置预览大小
*
* @param width 预览宽
* @param height 预览高
*/
- (void) setPreviewSize:(NSInteger)width height:(NSInteger)height;

/**
* 选择渲染方式
*
* @param renderMode 0 GPU渲染,1 metal 渲染
*/
- (void) setRenderMode:(MMLiveRenderMode)renderMode;

/**
* 开始预览
*
* @param cameraId 0 代表前置摄像头 ，1 代表后置摄像头
* @param view 预览视图
*/
- (void) startPreview:(NSInteger)cameraId view:(UIView*)view;

/**
* 停止预览
*
*/
- (void) stopPreview;

/**
* 切换前后摄像头
*
*/
- (int) switchCamera;

#pragma mark - 美颜特效

/**
* 使能水印功能
*
* @param enable YES 打开水印 NO关闭水印。
*/
- (void) setWatermarkEnabled:(BOOL)enable;

/**
* 设置磨皮等级
*
* @param level 0～1。
*/
- (void) setSmoothSkinLevel:(CGFloat)level;

/**
* 设置美白等级
*
* @param level 0～1。
*/
- (void) setWhitenSkinLevel:(CGFloat)level;

/**
* 设置大眼级别
*
* @param level 大眼级别，level 0～1。。
*/
- (void) setEyeScaleLevel:(CGFloat)level;

/**
* 设置瘦脸级别
*
* @param level 大脸级别，level 0～1。。
*/
- (void) setFaceScaleLevel:(CGFloat)level;

/**
* 设置削脸
*
* @param level 大脸级别，level -0.5 ~ 0.5。
*/
- (void) setFaceWidthLevel:(CGFloat)level;

/**
* 设置下巴
*
* @param level 下巴级别，level -0.5 ~ 0.5。
*/
- (void) setChinLengthLevel:(CGFloat)level;

/**
* 设置鼻子
*
* @param level 鼻子大小级别，level -0.5 ~ 0.5。
*/
- (void) setNoseSizeLevel:(CGFloat)level;

/**
* 设置嘴唇厚度
*
* @param level 嘴唇厚度级别，level -0.5 ~ 0.5。
*/
- (void) setLipThicknessLevel:(CGFloat)level;

/**
* 设置指定素材滤镜特效
*
* @param filter 滤镜的lookup图片
* @param identifier 滤镜的唯一标示号
*/
- (void) setFilter:(MLFilterDescriptor *)filter withIdentifier:(int)identifier;

/**
* 设置指定素材滤镜特效的强度
*
* @param intensityValue 滤镜特效的强度
*/
- (void) setFilterintensity:(CGFloat) intensityValue;

/**
* 添加贴纸
*
* @param decoration 贴纸的描述
* @param identifier 贴纸的唯一标示号
*/
- (void) setSticker:(FDKDecoration*)decoration withIdentifier:(NSString *)identifier;

/**
* 去除贴纸
*
* @param identifier 贴纸的唯一标示号
*/
- (void) removeStickerWithIdentifier:(NSString *)identifier;;

/**
* 添加手势
*
* @param decoration 手势资源描述
*/
- (void) addGesture:(NSArray<MLObjectTriggeredDecoration *> *)decoration ;

/**
* 去除手势
*
* @param decoration 手势资源描述
*/
- (void) removeGesture:(MLObjectTriggeredDecoration*) decoration;

#pragma mark - 设置
@property (nonatomic, weak) id<MMLiveEnginePusherDelegate> pusherDelegate;
@property (nonatomic, readonly, strong) MMLiveMediaConfig *pusherConfig;
@property (nonatomic, readonly, copy) NSString *rtmpURL;
@property (nonatomic, strong) MMLiveUserConfig* userConfig;
- (instancetype)initUserConfig:(MMLiveUserConfig *)config engineType:(MMLiveEngineType)type;

#pragma mark - RTMP
/**
* 开始推流
*
* @param config 推流媒体参数
*/
- (int) startPush:(MMLiveMediaConfig*) config;

/**
* 停止推流
*
*/
- (void) stopPush;

#pragma mark - RTC

/**
* 设置rtc的角色
*
*@param role 角色
*/
- (void) setClientRole:(MMLiveRTCClientRole) role;

/**
* 更新rtc 动态key
*
*@param channelKey key的内容
*/
- (void) updateChannelKey:(NSString*) channelKey;

/**
* 禁用本地音频
*
*@param audioMute YES 禁用 NO 打开
*/
- (void) setLocalAudioMute:(BOOL) audioMute;

/**
* 禁用本地视频
*
*@param videoMute YES 禁用 NO 打开
*/
- (void) setLocalVideoMute:(BOOL) videoMute;

/**
是否禁止所有的远端音频
@param audioMute 静音开关
*/
- (void)setAllRemoteAudioMute:(BOOL)audioMute;

/**
是否禁止所有的远端视频
@param videoMute 远端视频禁用开关
*/
- (void)setAllRemoteVideoMute:(BOOL)videoMute;

/**
禁止远端某个uid音频
@param mute 静音开关
@param userId 用户id
*/
- (void)setRemoteAudioStreamMute:(BOOL)mute forUser:(NSString *)userId;

/**
禁止远端某个uid视频
@param mute 视频禁用开关
@param userId 用户id
*/
- (void)setRemoteVideoStreamMute:(BOOL)mute forUser:(NSString *)userId;

/**
发起跨房pk
@param roomId 房间id
@param userId 用户id
*/
- (void)accrossOtherRoomWithRoomId:(NSString *)roomId userId:(NSString *)userId;

/**
结束跨房pk
@param roomid 房间id
*/
- (void)unaccrossOtherRoom:(NSString *)roomid;

/**
* 进入房间
*
*/
- (int) enterRoom:(MMLiveMediaConfig *)config roomParams:(MMLiveRoomParams*) roomParams;

/**
* 退出房间
*
*/
- (void) leaveRoom;

/**
* 设置转推布局和sei
*
*@param sei 转推布局
*/
- (void) setLinkSei:(MMLiveSei*)sei;

#pragma mark - 切换推流器

/**
* 打开平滑切换功能，默认关闭
*
* @param enable YES 打开 NO 关闭
*/
- (void) enableStreamReplace:(BOOL) enable;

/**
* 平滑切换
*
*/
- (void) switchPusherType;

#pragma mark - 播放器
@property (nonatomic, weak) id<MMLiveEnginePlayerDelegate> playerDelegate;

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
* 渲染 View add 在设置的这个view上。
*
* @param view 播放器渲染的父 view
*/
- (void) setPlayerView:(UIView*) view;

/**
 *  移除视频渲染的view
 */
- (void)removePlayerView;

/**
* 启动从指定 URL 播放 音视频流
*
* @param url 完整的 URL（如果播放的是本地视频文件，这里传本地视频文件的完整路径）
*/
- (void) startPlay:(NSString*)url;

/**
* 停止播放音视频流
*
*/
- (void) stopPlay;

/**
* 设置静音
*/
- (void) setMute:(BOOL) enable;

/**
* 设置音量
*
* @param volume 音量大小，取值范围0~1
*/
- (void) setVolume:(int) volume;

/**
* 获取播放器的状态
*
* return MMLivePlayerStatus 枚举状态
*/
- (MMLivePlayerStatus) getPlayStatus;

#pragma mark - 音频

/**
* 开启音频耳返
*
* @param enable YES 开启耳返，NO 关闭耳返
*/
- (void) setEarPhoneMonitor:(BOOL) enable;

#pragma mark - 背景音乐

/**
* 设置播放背景音乐
*
* @param url 音乐地址
* @param loopback 是否循环 YES 循环 NO 不循环
* @param repeatCount 循环次数
*/
- (void) playMusicWithUrl:(NSString*) url loopback:(BOOL) loopback repeatCount:(int)repeatCount;

/**
* 停止音乐播放
*
*/
- (void) stopMusic;

/**
* 暂停音乐播放
*
*/
- (void) pauseMusic;

/**
* 恢复音乐播放
*
*/
- (void) resumeMusic;

/**
* seek播放位置
*
* @param pos 播放位置 单位ms
*/
- (void) seekMusic:(NSInteger)pos;

/**
* 获取当前播放位置 单位ms
*
*/
- (NSInteger) musicCurrentPosition;

/**
* 获取播放文件总长度 单位ms
*
*/
- (NSInteger) musicDuration;

/**
* 设置音乐播放的pitch
*
* @param value 设置音频pitch
*/
- (void) setMusicPitch:(NSInteger)value;

#pragma mark - 音效

/**
* 设置播放音效
*
* @param effectid 音效id
* @param url 播放地址
* @param loopEnable 是否循环播放
* @param publishEnable 是否推送到远端
*/
- (void) playEffect:(NSInteger)effectid url:(NSString*)url loopEnable:(BOOL) loopEnable publishEnable:(BOOL)publishEnable;

/**
* 停止某个音效的声音
*
*@param effectid 音效标识
*/
- (void) stopEffect:(NSInteger)effectid;

/**
* 停止所有音效播放
*
*/
- (void) stopAllEffect;

/**
* 设置某个音效的声音
*
*@param effectid 音效标识
*@param volume 音量大小
*/
- (void) setEffectVolumeWithId:(NSInteger)effectid volume:(CGFloat)volume;

/**
* 设置所有音效的声音
*
*@param volume 音量大小
*/
- (void) setEffectsVolume:(CGFloat)volume;

#pragma mark - 语音特效

/**
* 设置语音EQ
*
* @param value -4 - 4(0, disable)
*/
- (void) setEqValue:(NSInteger)value;

/**
* 设置语音声音pitch的参数
*
* @param value 说话声音pitch的参数
*/
- (void) setPitchValue:(NSInteger)value;

/**
* 设置语音特效
*
* @param value 特效枚举
*/
- (void) setAeFilterValue:(MMLiveAEFilter) value;

/**
* 设置语音降噪
*
* @param level 0 - 4(0, disable)
*/
- (void) setDenoiseLevel:(NSInteger)level;

@end
#endif /* MMLiveEngine_h */
