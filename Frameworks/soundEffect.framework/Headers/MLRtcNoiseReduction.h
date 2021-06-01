//
//  RtcNoiseReduction.h
//  RtcNoiseReduction
//
//  Created by hrs on 2019/6/26.
//  Copyright © 2019 hrs. All rights reserved.
//

#ifndef RtcNoiseReduction_h
#define RtcNoiseReduction_h
#import <Foundation/Foundation.h>
enum rtcNsLevel {
    kNsOff = 0,
    kNsLow,
    kNsModerate,
    kNsHigh,
    kNsVeryHigh
};
@interface MLRtcNoiseReduction: NSObject
/*
 * samplerate Valid values are 8000, 16000, 32000 and 48000.
 * channel Valid values are 1, 2. The default is 1.
 * mode Valid modes are 0 ("quality"), 1 ("low bitrate"), 2 ("aggressive"), and 3
 * ("very aggressive"). The default mode is 0.
 */
- (int)createWebRtcNs:(int)samplerate channels:(int)channel;

- (NSData*)RtcNs_process:(NSData*)inputData level:(enum rtcNsLevel)nslevel;

- (void)RtcNs_free;
@end
#endif /* RtcNoiseReduction_h */
