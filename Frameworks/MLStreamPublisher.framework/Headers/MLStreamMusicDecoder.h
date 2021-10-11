//
//  MLStreamMusicDecoder.h
//  testAudioStream
//
//  Created by MOMO on 2019/1/2.
//  Copyright © 2019年 MOMO. All rights reserved.
//

#ifndef MLStreamMusicDecoder_h
#define MLStreamMusicDecoder_h

#import <Foundation/Foundation.h>

@class MLStreamMusicDecoder;
@protocol MLStreamMusicDecoderDelegate <NSObject>

@optional
- (void)streamMusicDecoder:(MLStreamMusicDecoder *)decoder didError:(NSError *)error;

@end

@interface MLStreamMusicDecoder : NSObject

@property (nonatomic, readonly, getter=isFinished) BOOL isFinished;
@property (nonatomic, readonly) NSData *endOfFileSentry;
@property (nonatomic, weak) id<MLStreamMusicDecoderDelegate> delegate;

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
#endif /* MLStreamMusicDecoder_h */
