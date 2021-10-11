//
//  MLAudioCaptureManager.h
//  MLStreamPublisher
//
//  Created by chenyong on 2018/5/4.
//

#import <Foundation/Foundation.h>
/** MLAudioCaptureManagerDelegate callback onEvent */
typedef enum _EventType{
    MLAUDIO_RECORD_STARTED, //收到开始事件的时候，desc可以不关注
    MLAUDIO_RECORD_FINISHED,//收到完成事件的时候，desc是文件路径
    MLAUDIO_RECORD_ERROR    //收到错误事件的时候，desc是错误描述
}EventType;

@protocol MLAudioCaptureManagerDelegate <NSObject>
- (void)onEvent:(EventType)type  NSString:(NSString*)desc;
@end

@interface MLAudioCaptureManager : NSObject

@property (weak,nonatomic) id<MLAudioCaptureManagerDelegate> delegate;
/*
 设置降噪参数(有默认值，如果要修改则在start之前调用该接口)
 @param index 降噪模式   0:关闭降噪          1:轻微降噪              2:中等降噪             3:重度降噪
 @param value 降噪强度 0.0:关闭降噪数值 0.0-0.1:轻微降噪调节范围 0.1-0.2:中等降噪调节范围 0.2-0.3:重度降噪调节范围
 */
- (void)setNoiseReductionValue:(int)index value:(float)value;

- (void)start;

- (void)stop;

- (double)getFileDuration:(NSString*)path;
@end
