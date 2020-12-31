//
//  IJKAudioEncoder.h


#import "IJKEncoder.h"


typedef enum _AudioProfile{
    AAC_LC_Profile = 0,
    AAC_HE_Profile,
    AAC_HE_v2_Profile
}AudioProfile;
@interface IJKAudioEncoder : IJKEncoder

@property (nonatomic) NSUInteger sampleRate;
@property (nonatomic) NSUInteger channels;
@property (nonatomic) AudioProfile profile;

- (instancetype) initWithBitrate:(NSUInteger)bitrate sampleRate:(NSUInteger)sampleRate channels:(NSUInteger)channels;
- (instancetype) initWithBitrate:(NSUInteger)bitrate sampleRate:(NSUInteger)sampleRate channels:(NSUInteger)channels profile:(AudioProfile)profile;

@end
