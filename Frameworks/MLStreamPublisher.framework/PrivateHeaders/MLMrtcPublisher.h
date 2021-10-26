//
//  MLMrtcPublisher.h
//  MLStreamPublisher
//
//  Created by wangqiangqiang on 2019/3/12.
//

#import "MLPublisher.h"
#import "MLRawAudioFrame.h"

NS_ASSUME_NONNULL_BEGIN

@interface MLMrtcPublisher : MLPublisher
- (void)onRecordAudioFrame:(MLRawAudioFrame *)audioFrame;
- (void)onPlaybackAudioFrame:(MLRawAudioFrame *)audioFrame;
@end

@interface MLMrtcPublisher (MLPublisherStatisticAuxiliaryDataProvider) <MLPublisherStatisticAuxiliaryDataProvider>

@end
NS_ASSUME_NONNULL_END
