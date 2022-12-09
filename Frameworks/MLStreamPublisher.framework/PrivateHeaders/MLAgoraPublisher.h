#import "MLPublisher.h"
#import "MLRawAudioFrame.h"

@interface MLAgoraPublisher : MLPublisher

- (instancetype)initWithContentView:(UIView *)view inputVideoSize:(CGSize)inputVideoSize isHost:(BOOL)isHost;
- (void)onRecordAudioFrame:(MLRawAudioFrame *)audioFrame;
- (void)onRecordAudioSize:(unsigned int)dataSize;
- (void)onPlaybackAudioFrame:(MLRawAudioFrame *)audioFrame;
- (void)onPlaybackAudioFrameBeforeMixing:(unsigned int)uid audioFrame:(MLRawAudioFrame *)audioFrame;
- (void)onRenderVideoFrame:(unsigned int)uid videoFrame:(YUV420PFrame)videoFrame;
- (NSString *)onRequestSEI:(unsigned int*)seiLength;
- (void)onReceiveSEI:(NSString *_Nonnull)sei;
@end

@interface MLAgoraPublisher (MLPublisherStatisticAuxiliaryDataProvider) <MLPublisherStatisticAuxiliaryDataProvider>

@end
