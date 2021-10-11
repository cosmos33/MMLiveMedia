//
//  MLAudioFilePlayer.h
//  Pods
//
//  Created by zhangzd on 2018/11/12.
//
#import <Foundation/Foundation.h>
#import "MLPlayer.h"

#ifndef MLAudioFilePlayer_h
#define MLAudioFilePlayer_h

@interface MLAudioFilePlayer : NSObject 
@property (nonatomic, assign) BOOL isStartRecord;
@property (nonatomic, weak) id<MLPlayerDelegate> delegate;

-(instancetype)initWithUrl:(NSString *)url sampleRate:(Float64)sampleRate channels:(int)channels pos:(NSTimeInterval)pos preludeInSec:(NSTimeInterval)preludeInSec;

-(NSTimeInterval)seek:(NSTimeInterval)pos;

-(NSTimeInterval)getFileDurationInSec;

-(NSTimeInterval)getCurrentPlaybackTimeInSec;

-(NSData *)getAccompanyLen:(size_t)accompanyLen;

-(NSString *)startRecord;

-(void)stopRecord;
@end
#endif /* MLAudioFilePlayer_h */


