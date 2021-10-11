//
//  MLSimpleMusicDecoder.h
//  MomoChat
//
//  Created by wang.guijie on 10/13/16.
//  Copyright © 2016 wemomo.com. All rights reserved.
//

#import <Foundation/Foundation.h>

@class MLSimpleMusicDecoder;
@protocol MLSimpleMusicDecoderDelegate <NSObject>

@optional
- (void)simpleMusicDecoder:(MLSimpleMusicDecoder *)decoder didError:(NSError *)error;

@end

@interface MLSimpleMusicDecoder : NSObject

@property (nonatomic, readonly, getter=isFinished) BOOL isFinished;
@property (nonatomic, readonly) NSData *endOfFileSentry;
@property (nonatomic, weak) id<MLSimpleMusicDecoderDelegate> delegate;

- (instancetype)initDecoderWithMusicFileUrl:(NSString *)url outSampleRate:(Float64)outSampleRate outChannel:(int)outChannel;
- (void)start;
- (NSData*)getDecodedAudioSample;
- (void)stop_async;
- (NSTimeInterval)duration;

//hrs 增加一个设置音效调节的pitch接口
- (void)setValueMusicPitchShift:(int)valueMusicPitchShift;
//hrs 增加一个获取音效调节的pitch接口
- (int)getValueMusicPitchShift;
- (void)seekValueMusic:(int)pos;
-(NSTimeInterval)getCurrentTime;
@end
