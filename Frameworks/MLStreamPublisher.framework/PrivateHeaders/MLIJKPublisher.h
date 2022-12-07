#import "MLPublisher.h"
#if !TARGET_IPHONE_SIMULATOR
@interface MLIJKPublisher : MLPublisher<FFRtmpWriterDelegate>
#else
@interface MLIJKPublisher : MLPublisher
#endif
- (void)processEncodeVideoFrame:(NSData *)videoData
                        videoPts:(NSUInteger)pts
                      videoParam:(NSData *)paramData
                           isKey:(BOOL)isKey;

@end


@interface MLIJKPublisher (MLPublisherStatisticAuxiliaryDataProvider) <MLPublisherStatisticAuxiliaryDataProvider>

@end
