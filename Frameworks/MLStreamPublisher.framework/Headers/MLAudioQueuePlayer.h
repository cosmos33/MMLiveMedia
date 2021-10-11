//
//  MLAudioQueuePlayer.h
//  MLStreamPublisher
//
//  Created by chenyong on 2018/8/21.
//

#import <Foundation/Foundation.h>

typedef void (*AudioQueueCallback) (void *userdata, uint8_t *stream, int len);
typedef struct MLAudioSpec
{
    int freq;                       /**< DSP frequency -- samples per second */
    uint8_t channels;               /**< Number of channels: 1 mono, 2 stereo */
    uint8_t silence;                /**< Audio buffer silence value (calculated) */
    uint16_t samples;               /**< Audio buffer size in samples recommend 512 */
    uint32_t size;                  /**< Audio buffer size in bytes (calculated) */
    AudioQueueCallback callback;
    void *userdata;
} MLAudioSpec;

@interface MLAudioQueuePlayer : NSObject

- (id)initWithAudioSpec:(MLAudioSpec *)aSpec;

- (void)play;
- (void)pause;
- (void)flush;
- (void)stop;
- (void)close;
- (void)setPlaybackRate:(float)playbackRate;
- (void)setPlaybackVolume:(float)playbackVolume;
- (double)get_latency_seconds;

@property (nonatomic, readonly) MLAudioSpec spec;

@end
