//
//  MLAudioEditorManager.h
//  MLStreamPublisher
//
//  Created by chenyong on 2018/8/22.
//

#import <Foundation/Foundation.h>

@class MLAudioEditorManager;
@protocol MLAudioEditorManagerDelegate <NSObject>
//声音被打断开始
- (void)audioEditorManagerAudioInterruptBeg:(MLAudioEditorManager *)manager;
//声音被打断结束
- (void)audioEditorManagerAudioInterruptEnd:(MLAudioEditorManager *)manager;
//准备播放，此时可以获取播放时长
- (void)audioEditorManagerDidPlayerPrepared:(MLAudioEditorManager *)manager;
//播放完成
- (void)audioEditorManagerDidPlayerFinished:(MLAudioEditorManager *)manager;
//播放失败
- (void)audioEditorManagerDidPlayerFailed:(MLAudioEditorManager *)manager;
//试听结束
- (void)audioEditorManagerDidPlaybackFinished:(MLAudioEditorManager *)manager;
//试听失败
- (void)audioEditorManagerDidPlaybackFailed:(MLAudioEditorManager *)manager;
//生成文件成功通知
- (void)audioEditorManager:(MLAudioEditorManager *)manager
         genRecordFilePath:(NSString *)recordPath
            genMixFilePath:(NSString *)mixPath;
//生成文件失败
- (void)audioEditorManager:(MLAudioEditorManager *)manager genFilesFailed:(NSError *)error;

-(void)audioMixCurrentRate:(MLAudioEditorManager *)manager
                      rate:(double)rate;

//视频文件合成结束回调
-(void)audioMixFileFinished:(MLAudioEditorManager *)manager;
@end

@interface MLAudioEditorManager : NSObject

@property (nonatomic, weak) id<MLAudioEditorManagerDelegate> delegate;

//默认是否开启回声消除 YES:开启回声消除。NO:关闭回声消除
-(instancetype)initWithVpio:(BOOL)enable;

//开关耳返功能
- (void)enableLoopback:(BOOL)enable;

//获取文件总时长
- (double)getFileDuration:(NSString *)filePath;

//是否开启回声消除录制
- (void)enableEchoCancellation:(BOOL)enable;

/**
 1-人声混音（默认）
 2-人声+伴奏混音
 */
-(void)setAudioEffectMode:(int)type;

/**
 type: 1降噪, 2混响, 3均衡器(EQ)
 index和value参见sabine_effects.h定义的inIdx和inValue值
 */
- (void)setSabineAudioEffect:(int)type index:(int)index value:(float)value;

//用于降噪
- (void)setSabineAudioDenoise:(int)type index:(int)index value:(float)value;


//设置采集和混音文件路径
- (void)setRecordFilePath:(NSString *)recordPath andMixFilePath:(NSString *)mixPath;

/**开始播放
 * @str 音效文件地址
 * @pos 开始录制时间点 单位（s）
 * @preludeInSec 开始播放前奏时长 单位(s)
 */
- (void)startPlayerWithUrl:(NSString*)str pos:(NSTimeInterval)pos preludeInSec:(NSTimeInterval)preludeInSec;

//设置伴奏播放音量大小
- (void)setPlayerVolume:(double)value;

//设置试听人声大小[0.~1.0]
-(void)setPlayerRecordVolume:(double)value;

//获取文件播放总时长
- (double)getPlayerDuration;

//获取文件播放当前位置
- (double)getPlayerCurrentTime;

//暂停播放
- (void)pausePlayer;

//恢复播放
- (void)resumePlayer;

//停止播放
- (void)stopPlayer;

//开始录制音频
- (void)startRecord;

//暂停录制音频
- (void)pauseRecord:(NSTimeInterval)preludeInSec;

//恢复录制音频
- (void)resumeRecord;

//结束录制音频
- (void)stopRecord;

//开始试听
- (void)playbackStart;

//暂停试听
- (void)playbackPause;

//恢复试听
- (void)playbackResume;

//停止试听
- (void)playbackStop;

//获取试听总时长
- (double)getPlaybackDuration;

//获取试听播放当前位置
- (double)getPlaybackCurrentTime;

//设置回放伴奏音量大小
- (void)setPlaybackVolume:(double)value;

//设置回放伴奏音量大小[0.~1.0]
-(void)setPlaybackRecordVolume:(double)value;

//获取采集文件(可设置64000)
- (void)getRecordFilesWithBitrate:(int)bitrate;

/**试听播放位置
 * @value 试听播放的时间
 */
-(void)setPlayerSeek:(NSTimeInterval)value;

/**跳过前奏
 * @value 前奏时常
 */
-(void)jumpPreludes:(NSTimeInterval)value;

/** 设置声音音量递减
 * @inSec：距离结束多长时间开始进行音频递减
 * @value 文件结束后声音系数[0.0 ~ 1.0]
 */
-(void)setAudioAttenuation:(NSTimeInterval)inSec Volume:(float)value;

/*删除设置声音音量递减*/
-(void)delAudioAttenuation;

/** 视频合成校准
 * @value > 0  seek人声
 * @value < 0  seek音效
 */
-(void)audioCalibration:(NSTimeInterval)value;
@end

