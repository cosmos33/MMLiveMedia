//
//  MMLiveRtcEngineKit.h
//  MomoLiveRoom
//
//  Created by chenyong on 2019/2/21.
//  Copyright © 2019年 momo. All rights reserved.
//
#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import <CoreMedia/CoreMedia.h>
#import "MMLiveRtcBase.h"
#import "MMLiveRtcCode.h"
#import "MMLiveMediaEngine.h"
NS_ASSUME_NONNULL_BEGIN
@class MMLiveRtcEngineKit;
@protocol MMLiveRtcEngineDelegate <NSObject>
@optional
#pragma mark SDK common delegates
/**
 *  The warning occurred in SDK. The APP could igonre the warning, and the SDK could try to resume automically.
 *
 *  @param engine      The engine kit
 *  @param warningCode The warning code
 */
- (void)rtcEngine:(MMLiveRtcEngineKit *_Nonnull)engine didOccurWarning:(MMLiveWarningCode)warningCode;
/**
 *  The error occurred in SDK. The SDK couldn't resume to normal state, and the app need to handle it.
 *
 *  @param engine    The engine kit
 *  @param errorCode The error code
 */
- (void)rtcEngine:(MMLiveRtcEngineKit *_Nonnull)engine didOccurError:(MMLiveErrorCode)errorCode;
/**
 *  The gotChannelsList occurred in SDK. The SDK couldn't resume to normal state, and the app need to handle it.
 *
 *  @param engine    The engine kit
 *  @param errorCode The error code
 */
- (void)rtcEngine:(MMLiveRtcEngineKit *_Nonnull)engine gotChannelsList:(NSArray*)list;
/**
 * when token is enabled, and specified token is invalid or expired, this function will be called.
 * APP should generate a new token and call renewToken() to refresh the token.
 * NOTE: to be compatible with previous version, ERR_TOKEN_EXPIRED and ERR_INVALID_TOKEN are also reported via onError() callback.
 * You should move renew of token logic into this callback.
 *  @param engine The engine kit
 */
- (void)rtcEngineRequestToken:(MMLiveRtcEngineKit * _Nonnull)engine;
//频道key将要过期需要新key
- (void)rtcEngine:(MMLiveRtcEngineKit * _Nonnull)engine tokenPrivilegeWillExpire:(NSString *_Nonnull)token;

/**
 *  Event of disconnected with server. This event is reported at the moment SDK loses connection with server.
 *  In the mean time SDK automatically tries to reconnect with the server until APP calls leaveChannel.
 *
 *  @param engine The engine kit
 */
- (void)rtcEngineConnectionDidInterrupted:(MMLiveRtcEngineKit * _Nonnull)engine;

/**
 *  Event of loss connection with server. This event is reported after the connection is interrupted and exceed the retry period (10 seconds by default).
 *  In the mean time SDK automatically tries to reconnect with the server until APP calls leaveChannel.
 *
 *  @param engine The engine kit
 */
- (void)rtcEngineConnectionDidLost:(MMLiveRtcEngineKit * _Nonnull)engine;

- (void)rtcEngine:(MMLiveRtcEngineKit *_Nonnull)engine didRemotePeerLost:(NSUInteger)uid;
/**
 *  Event of the user joined the channel.
 *
 *  @param engine  The engine kit
 *  @param channel The channel name
 *  @param uid     The remote user id
 *  @param elapsed The elapsed time (ms) from session beginning
 */
- (void)rtcEngine:(MMLiveRtcEngineKit *_Nonnull)engine didJoinChannel:(NSString *_Nonnull)channel withUid:(NSUInteger)uid elapsed:(NSInteger)elapsed;
/**
 *  Event of the user rejoined the channel
 *
 *  @param engine  The engine kit
 *  @param channel The channel name
 *  @param uid     The user id
 *  @param elapsed The elapsed time (ms) from session beginning
 */
- (void)rtcEngine:(MMLiveRtcEngineKit * _Nonnull)engine didRejoinChannel:(NSString * _Nonnull)channel withUid:(NSUInteger)uid elapsed:(NSInteger) elapsed;
/**
 *  The statistics of the call when leave channel
 *
 *  @param engine The engine kit
 *  @param stats  The statistics of the call, including duration, sent bytes and received bytes
 */
- (void)rtcEngine:(MMLiveRtcEngineKit *_Nonnull)engine didLeaveChannelWithStats:(MMLiveChannelStats *_Nonnull)stats;
/**
 *  Event of cient role change. only take effect under broadcasting mode
 *
 *  @param engine The engine kit
 *  @param oldRole the previous role
 *  @param newRole the new role
 */
- (void)rtcEngine:(MMLiveRtcEngineKit *_Nonnull)engine didClientRoleChanged:(MMLiveClientRole)oldRole newRole:(MMLiveClientRole)newRole;

/**
 *  The network quality of local user.
 *
 *  @param engine  The engine kit
 *  @param uid     The id of user
 *  @param txQuality The sending network quality
 *  @param rxQuality The receiving network quality
 */
- (void)rtcEngine:(MMLiveRtcEngineKit * _Nonnull)engine networkQuality:(NSUInteger)uid txQuality:(MMLiveNetworkQuality)txQuality rxQuality:(MMLiveNetworkQuality)rxQuality;
#pragma mark Remote user common delegates
/**
 *  Event of remote user joined
 *
 *  @param engine  The engine kit
 *  @param uid     The remote user id
 *  @param elapsed The elapsed time(ms) from the beginning of the session.
 */
- (void)rtcEngine:(MMLiveRtcEngineKit *_Nonnull)engine didJoinedOfUid:(NSUInteger)uid elapsed:(NSInteger)elapsed;
/**
 *  Event of remote user offlined
 *
 *  @param engine The engine kit
 *  @param uid    The remote user id
 *  @param reason Reason of user offline, quit, drop or became audience
 */
- (void)rtcEngine:(MMLiveRtcEngineKit *_Nonnull)engine didOfflineOfUid:(NSUInteger)uid reason:(MMLiveUserOfflineReason)reason;

/**
 *  receive custom data from remote user
 *
 *  @param engine The engine kit
 *  @param uid    The remote user id
 *  @param streamId The stream id
 *  @param data   The user defined data
 */
- (void)rtcEngine:(MMLiveRtcEngineKit * _Nonnull)engine receiveStreamMessageFromUid:(NSUInteger)uid streamId:(NSInteger)streamId data:(NSData * _Nonnull)data;

/**
 *  the local user has not received the data stream from the other user within 5 seconds.
 *
 *  @param engine The engine kit
 *  @param uid    The remote user id
 *  @param streamId The stream id
 *  @param error    The error code
 *  @param missed   The number of lost messages
 *  @param cached   The number of incoming cached messages when the data stream is interrupted
 */
- (void)rtcEngine:(MMLiveRtcEngineKit * _Nonnull)engine didOccurStreamMessageErrorFromUid:(NSUInteger)uid streamId:(NSInteger)streamId error:(NSInteger)error missed:(NSInteger)missed cached:(NSInteger)cached;

#pragma mark Local user delegates
/**
 * Notify application the state of microphone has changed.
 * true: Microphone is enabled.
 * false: Microphone is disabled.
 */
- (void)rtcEngine:(MMLiveRtcEngineKit *_Nonnull)engine didMicrophoneEnabled:(BOOL)enabled;

/**
 *  Event of the first audio frame is sent.
 *
 *  @param engine  The engine kit
 *  @param elapsed The elapsed time(ms) from the beginning of the session.
 */
- (void)rtcEngine:(MMLiveRtcEngineKit *_Nonnull)engine firstLocalAudioFrame:(NSInteger)elapsed;
/**
 *  Event of the first local frame starts rendering on the screen.
 *
 *  @param engine  The engine kit
 *  @param size    The size of local video stream
 *  @param elapsed The elapsed time(ms) from the beginning of the session.
 */
- (void)rtcEngine:(MMLiveRtcEngineKit *_Nonnull)engine firstLocalVideoFrameWithSize:(CGSize)size elapsed:(NSInteger)elapsed;

/**
 *  Event of finish audio mixing.
 *
 *  @param engine The engine kit
 */
- (void)rtcEngineLocalAudioMixingDidBegin:(MMLiveRtcEngineKit * _Nonnull)engine;

/**
 *  Event of finish audio mixing.
 *
 *  @param engine The engine kit
 */
- (void)rtcEngineLocalAudioMixingDidFinish:(MMLiveRtcEngineKit * _Nonnull)engine;

/**
 *  Event of finish audio mixing.
 *
 *  @param engine The engine kit
 */
- (void)rtcEngineLocalAudioMixingDidError:(MMLiveRtcEngineKit * _Nonnull)engine;


/**
 *  Event of finish audio effect.
 *
 *  @param engine The engine kit
 */
- (void)rtcEngineDidAudioEffectFinish:(MMLiveRtcEngineKit * _Nonnull)engine soundId:(NSInteger)soundId;
#pragma mark Remote user audio delegates
/**
 *  Event of remote user audio muted or unmuted
 *
 *  @param engine The engine kit
 *  @param muted  Muted or unmuted
 *  @param uid    The remote user id
 */
- (void)rtcEngine:(MMLiveRtcEngineKit *_Nonnull)engine didAudioMuted:(BOOL)muted byUid:(NSUInteger)uid;
/**
 *  Event of the first audio frame from remote user is received.
 *
 *  @param engine  The engine kit
 *  @param uid     The remote user id
 *  @param elapsed The elapsed time(ms) from the beginning of the session.
 */
- (void)rtcEngine:(MMLiveRtcEngineKit *_Nonnull)engine firstRemoteAudioFrameOfUid:(NSUInteger)uid elapsed:(NSInteger)elapsed;
/**
 *  The sdk reports who is active speaker in the channel
 *
 *  @param engine      The engine kit
 *  @param speakerUid  The speaker who is talking
 */
- (void)rtcEngine:(MMLiveRtcEngineKit * _Nonnull)engine activeSpeaker:(NSUInteger)speakerUid;
#pragma mark Remote user video delegates
/**
 *  Event of the first frame of remote user is decoded successfully.
 *
 *  @param engine  The engine kit
 *  @param uid     The remote user id
 *  @param size    The size of video stream
 *  @param elapsed The elapsed time(ms) from the beginning of the session.
 */
- (void)rtcEngine:(MMLiveRtcEngineKit *_Nonnull)engine firstRemoteVideoDecodedOfUid:(NSUInteger)uid size:(CGSize)size elapsed:(NSInteger)elapsed;
/**
 *  Event of the first frame of remote user is rendering on the screen.
 *
 *  @param engine  The engine kit
 *  @param uid     The remote user id
 *  @param size    The size of video stream
 *  @param elapsed The elapsed time(ms) from the beginning of the session.
 */
- (void)rtcEngine:(MMLiveRtcEngineKit * _Nonnull)engine firstRemoteVideoFrameOfUid:(NSUInteger)uid size:(CGSize)size elapsed:(NSInteger)elapsed;

/**
 *  Event of video size changed for local or remote user
 *
 *  @param engine  The engine kit
 *  @param uid     The user id
 *  @param size    The new size of video
 *  @param rotation  The new rotate of video
 */
- (void)rtcEngine:(MMLiveRtcEngineKit * _Nonnull)engine videoSizeChangedOfUid:(NSUInteger)uid size:(CGSize)size rotation:(NSInteger)rotation;
/**
 *  This callback indicates remote video stream state has changed.
 *
 *  @param engine  The engine kit
 *  @param uid     The user id
 *  @param state   Stopped // Default state, video is started or remote user disabled/muted video stream
 Running // Running state, remote video can be displayed normally
 Frozen  // Remote video is frozen, probably due to network issue.
 */
- (void)rtcEngine:(MMLiveRtcEngineKit * _Nonnull)engine remoteVideoStateChangedOfUid:(NSUInteger)uid state:(MMLiveVideoRemoteState)state;
/**
 *  Event of remote user video muted or unmuted
 *
 *  @param engine The engine kit
 *  @param muted  Muted or unmuted
 *  @param uid    The remote user id
 */
- (void)rtcEngine:(MMLiveRtcEngineKit *_Nonnull)engine didVideoMuted:(BOOL)muted byUid:(NSUInteger)uid;




#pragma mark Stream publish delegates
- (void)rtcEngine:(MMLiveRtcEngineKit * _Nonnull)engine streamPublishedWithUrl:(NSString * _Nonnull)url errorCode:(MMLiveErrorCode)errorCode;

- (void)rtcEngine:(MMLiveRtcEngineKit * _Nonnull)engine streamUnpublishedWithUrl:(NSString * _Nonnull)url;

- (void)rtcEngineTranscodingUpdated:(MMLiveRtcEngineKit * _Nonnull)engine;

/**
 * This callback is triggered when receiving audio packet from remote user
 * It implies the network statistics of audio packet
 *
 * @param uid                 The UID of the remote user
 * @param delay               The end to end delay(ms) from the remote user to local client
 * @param lost                The packet lost rate
 * @param rxKBitRate          The receive audio KBps from remote user
 */
- (void)rtcEngine:(MMLiveRtcEngineKit * _Nonnull)engine audioTransportStatsOfUid:(NSUInteger)uid delay:(NSUInteger)delay lost:(NSUInteger)lost rxKBitRate:(NSUInteger)rxKBitRate;

/**
 * This callback is triggered when receiving video packet from remote user
 * It implies the network statistics of video packet
 *
 * @param uid                 The UID of the remote user
 * @param delay               The end to end delay(ms) from the remote user to local client
 * @param lost                The packet lost rate
 * @param rxKBitRate          The receive video KBps from remote user
 */
- (void)rtcEngine:(MMLiveRtcEngineKit * _Nonnull)engine videoTransportStatsOfUid:(NSUInteger)uid delay:(NSUInteger)delay lost:(NSUInteger)lost rxKBitRate:(NSUInteger)rxKBitRate;



/**
 *  Statistics of rtc engine status. Updated every two seconds.
 *
 *  @param engine The engine kit
 *  @param stats  The statistics of rtc status, including duration, sent bytes and received bytes 日志的统一出口
 */
- (void)rtcEngine:(MMLiveRtcEngineKit * _Nonnull)engine reportRtcStats:(MMLiveChannelStats * _Nonnull)stats;

/**
 *  The sdk reports the volume of a speaker.
 *
 *  @param engine      The engine kit
 *  @param speakers    NSDictionary value:volume  key:uid
 */
- (void)rtcEngine:(MMLiveRtcEngineKit *_Nonnull)engine reportAudioVolume:(NSDictionary * _Nonnull)speakers;


- (void)rtcEngine:(MMLiveRtcEngineKit *_Nonnull)engine didLog:(NSUInteger)type body:(NSString * _Nonnull)body;


- (void)rtcEngine:(MMLiveRtcEngineKit *_Nonnull)engine event:(NSString*)event  body:(NSString * _Nonnull)body;

- (void)rtcEngine:(MMLiveRtcEngineKit *_Nonnull)engine didReceiveSEI:(NSString *_Nonnull)sei;

- (void)rtcEngine:(MMLiveRtcEngineKit *_Nonnull)engine didKickedOutWithSessionId:(NSString *_Nonnull)channel operUserId:(NSUInteger)operid  uid:(NSUInteger)uid reason:(NSInteger)reason;//signal

- (void)rtcEngine:(MMLiveRtcEngineKit * _Nonnull)engine receiveStreamMessageFromUid:(NSUInteger)uid streamId:(NSInteger)streamId str:(NSString * _Nonnull)str;
@end




#pragma mark - MMLiveRtcEngineKit
@interface MMLiveRtcEngineKit : NSObject
-(instancetype) init __attribute__((unavailable("init not available, call sharedEngineWithAppId instead")));
/**
 *@param audioChannels config audio channels(在sharedEngineWithAppId之前调用生效)
 */
+ (void) setEngineAudioConfigurationWithLevel:(uint32_t)audioLevel;
/**
 *  Initializes the LiveRtcEngineKit object.
 *  @param appId The appId is issued to the application developers by Agora.
 *  @param delegate The MMLiveRtcEngineDelegate
 *  @return an object of MMLiveRtcEngineKit class
 */
+ (instancetype _Nonnull)sharedEngineWithAppId:(NSString * _Nonnull)appId
                                      delegate:(id<MMLiveRtcEngineDelegate> _Nullable)delegate;
+ (void)destroy;

/**
 *  Get the version of Live SDK.
 *  @return string, sdk version
 */
+ (NSString * _Nonnull)getSdkVersion;

#pragma mark Common methods
/*lets user getchannellist,the call back rtcEngine:gotChannelsList willworks*/
- (int)getChannelList:(NSUInteger)uid;


- (int)setExpandCartonParams:(NSInteger)startupExpand
              expandInCarton:(NSInteger)expandInCarton;

/**
 *  Create an open UDP socket to the MMLiveRtcEngineKit cloud service to join a channel.
 Users in the same channel can talk to each other with same appId.
 Users using different appIds cannot call each other.
 The method is asynchronous.
 *
 *  @param token        token generated by APP using sign certificate.
 *  @param channelId       Joining in the same channel indicates those clients have entered in one room.
 *  @param info              Optional, this argument can be whatever the programmer likes personally.
 *  @param uid               Optional, this argument is the unique ID for each member in one channel.
 If not specified, or set to 0, the SDK automatically allocates an ID, and the id could be gotten in onJoinChannelSuccess.
 *   the callback rtcEngine:didJoinChannel:withUid:elapsed: will works.
 *  @return 0 when executed successfully, and return negative value when failed.
 */
- (int)joinChannelByToken:(NSString * _Nullable)token
                channelId:(NSString * _Nonnull)channelId
                     info:(NSString * _Nullable)info
                      uid:(NSUInteger)uid;

/**
 *  Create connect with the signal server that is designed by client.
 *
 *  @param ip        Server ip.
 *  @param port      Server port
 *  @param sslPort   Server sslPort
 *  @return 0 when executed successfully, and return negative value when failed.
 */
- (int)createConnectWithSignalServer:(NSString * _Nullable)ip
                                  port:(NSUInteger)port
                               sslPort:(NSUInteger)sslPort;
/**
 *  lets the user leave a channel, i.e., hanging up or exiting a call.
 After joining a channel, the user must call the leaveChannel method to end the call before joining another one.
 *  @return 0 if executed successfully, or return negative value if failed.
 */
- (int)leaveChannel;

/**
 *  Set the role of user: such as broadcaster, audience
 *  @param role the role of client
 *  @return 0 when executed successfully. return negative value if failed.
 */
- (int)setClientRole:(MMLiveClientRole)role;

/**
 *  Set the mode for server
 *  @param mode the business type
 *  @return 0 when executed successfully. return negative value if failed.
 */
- (int)setRoomMode:(uint32_t)mode;

/**
 *  Set the channel profile: such as communication, live broadcasting
 *  @param profile the channel profile
 *  @return 0 when executed successfully. return negative value if failed.
 */
- (int)setChannelProfile:(MMLiveChannelProfile)profile;

/**
 *  Renew token, refresh the new key into agora engine. APP should call this API when SDK reports error ERR_TOKEN_EXPIRED.
 *
 *  @param token new token
 *
 *  @return 0 when executed successfully. return negative value if failed.
 */
- (int)renewToken:(NSString * _Nonnull)token;

- (int)setVideoResolution: (CGSize)size andFrameRate: (NSInteger)frameRate bitrate: (NSInteger) bitrate;
#pragma mark Video methods
/**
 *  Set up the remote video view. The video canvus is initialized with video display setting. It could be called after receiving the remote video streams to configure the video settings.
 *  @param remote the canvas is composed of view and uid.
 *  @return 0 when executed successfully. return negative value if failed.
 */
- (int)setupRemoteVideo:(MMLiveRtcVideoCanvas * _Nonnull)canvas;
/**
 *  set video profile, including resolution, fps, kbps
 *
 *  @param profile enumeration definition about the video resolution, fps and max kbps
 *
 *  @return 0 when executed successfully. return negative value if failed.
 */
- (int)setVideoEncoderConfiguration:(MMLiveVideoEncoderConfiguration *_Nonnull)config;
/**
 *  Configure display setting of remote view. And it could be called mutiple times during a call.
 *
 *  @param uid  The user id of remote view.
 *  @param mode There are Hidden(1), Fit(2) and Adaptive(3) mode. Please take a look at definition of enum AgoraVideoRenderMode
 *
 *  @return 0 when executed successfully. return negative value if failed.
 */
- (int)setRemoteRenderMode:(NSUInteger)uid mode:(MMLiveVideoRenderMode)mode;
/**
 *  Enable / disable sending local video streams to the network.
 *
 *  @param mute YES: stop sending local video stream to the network, NO: start sending local video stream.
 *
 *  @return 0 when executed successfully. return negative value if failed.
 */
- (int)muteLocalVideoStream:(BOOL)mute;
/**
 *  Enables / disables playing all remote callers’ video streams.
 *
 *  @param mute YES: stop playing, NO: start playing.
 *
 *  @return 0 when executed successfully. return negative value if failed.
 */
- (int)muteAllRemoteVideoStreams:(BOOL)mute;
/**
 *  Enable / disable a remote user's video stream
 *
 *  @param uid  The remote user id
 *  @param mute YES: discard the video stream from remote user, NO: start receiving remote video stream.
 *
 *  @return 0 when executed successfully. return negative value if failed.
 */
- (int)muteRemoteVideoStream:(NSUInteger)uid mute:(BOOL)mute;

- (void)setSei:(NSString *)sei;

- (int)startChannelMediaRelay:(NSUInteger)uid channelid:(NSString*)channelid;
- (int)stopChannelMediaRelay:(NSUInteger)uid channelid:(NSString*)channelid;

#pragma mark Audio methods

/**
 * As Audio is enabled by default when join the channel, this method is used to disable and re-enable local audio,
 * for e.g., disable microphone to stop audio capturing, but can still playback remote audio.
 * After local audio is enabled or disabled, \ref onMicrophoneEnabled() event will be notified.
 * @param enabled
 * @return int
 * true: re-enable local audio, start audio capturer
 * false: disable local audio, stop audio capturer
 */
- (int)enableLocalAudio:(BOOL)enabled;

/**
 *  Enable / Disable speaker of device
 *
 *  @param enableSpeaker YES: Switches to speakerphone. NO: Switches to headset.
 *
 *  @return 0 when executed successfully. return negative value if failed.
 */
- (int)setEnableSpeakerphone:(BOOL)enableSpeaker;

/**
 *  test if the speakerphone is enabled or not.
 *
 *  @return YES when speakerphone is enabled. NO when speakerphone is not enabled.
 */
- (BOOL)isSpeakerphoneEnabled;

/**
 *  Set default audio route to Speakerphone
 *
 *  @param defaultToSpeaker YES: default to speakerphone. NO: default to earpiece for voice chat, speaker for video chat.
 *
 *  @return 0 when executed successfully. return negative value if failed.
 */
- (int)setDefaultAudioRouteToSpeakerphone:(BOOL)defaultToSpeaker;

/**
 *  set audio profile and scenario
 *  including sample rate, bit rate, mono/stereo, speech/music codec
 *
 *  @param profile enumeration definition about the audio's samplerate, bitrate, mono/stereo, speech/music codec
 *  @param scenario enumeration definition about the audio scenario
 *
 *  @return 0 when executed successfully. return negative value if failed.
 */
- (int)setAudioProfile:(MMLiveAudioProfile)profile;

/**
 *  deprecated, use setAudioProfile:scenario: insted
 */
- (int)setHighQualityAudioParametersWithFullband:(BOOL)fullband
                                          stereo:(BOOL)stereo
                                     fullBitrate:(BOOL)fullBitrate __deprecated;

/**
 * adjust recording signal volume
 *
 * @param [in] volume range from 0 to 400
 *
 * @return return 0 if success or an error code
 */
- (int)adjustRecordingSignalVolume:(NSInteger)volume;

/**
 * adjust playback signal volume
 *
 * @param [in] volume range from 0 to 400
 *
 * @return return 0 if success or an error code
 */
- (int)adjustPlaybackSignalVolume:(NSInteger)volume;

/**
 *  Sets the speakerphone volume. The speaker volume could be adjust by MPMusicPlayerController and other iOS API easily.
 *
 *  @param volume between 0 (lowest volume) to 255 (highest volume).
 *
 *  @return 0 when executed successfully. return negative value if failed.
 */
- (int)setSpeakerphoneVolume:(NSUInteger)volume __deprecated;

/**
 *  Enables to report to the application about the volume of the speakers.
 *
 *  @param interval Specifies the time interval between two consecutive volume indications.
 <=0: Disables volume indication.
 >0 : The volume indication interval in milliseconds. Recommandation: >=200ms.
 *  @param smooth   The smoothing factor. Recommended: 3.
 *
 *  @return 0 when executed successfully. return negative value if failed.
 */
- (int)enableAudioVolumeIndication:(NSInteger)interval
                            smooth:(NSInteger)smooth;

/**
 *  Mutes / Unmutes local audio.
 *
 *  @param mute true: Mutes the local audio. false: Unmutes the local audio.
 *
 *  @return 0 when executed successfully. return negative value if failed.
 */
- (int)muteLocalAudioStream:(BOOL)mute;

- (int)muteRemoteAudioStream:(NSUInteger)uid mute:(BOOL)mute;

/**
 *  Mutes / Unmutes local message.
 *
 *  @param mute true: Mutes the local message. false: Unmutes the local message.
 *
 *  @return 0 when executed successfully. return negative value if failed.
 */
- (int)muteLocalMessageStream:(BOOL)mute;

- (int)muteRemoteMessageStream:(NSUInteger)uid mute:(BOOL)mute;

/**
 *  Mutes / Unmutes all remote audio.
 *
 *  @param mute true: Mutes all remote received audio. false: Unmutes all remote received audio.
 *
 *  @return 0 when executed successfully. return negative value if failed.
 */
- (int)muteAllRemoteAudioStreams:(BOOL)mute;

- (int)enableInEarMonitoring:(BOOL)enabled;
/**
 * Set the audio ears back's volume and effect
 * @param [in] volume
 *        set volume of audio ears back, in the range of [0.0~1.0], default value is 0.5
 *
 * @return return 0 if success or an error code
 */
- (int)setInEarMonitoringVolume:(float)volume;
#pragma mark Audio mixing
- (int)startAudioMixing:(NSString *  _Nonnull)filePath
               loopback:(BOOL)loopback
                replace:(BOOL)replace
                  cycle:(NSInteger)cycle;
- (int)stopAudioMixing;
- (int)pauseAudioMixing;
- (int)resumeAudioMixing;
/*set audio playback volume (0 ~ 1.0), default value is 0.5*/
- (int)setAudioMixingVolume:(float)volume;
/*get audio duration in ms*/
- (int64_t)getAudioMixingDuration;
/*get audio position in ms*/
- (int64_t)getAudioMixingCurrentPosition;
/*set audio position in ms*/
- (int)setAudioMixingPosition:(NSInteger)pos;
/** Set the audio pitch of the mixing file playback.
 By default, the pitch is always 0 when you start the audio mixing process.
 You can only use this method to change the pitch when audio mixing is started.
 If audio mixing is not started, this method will do nothing.
 
 @param pitch the pitch value, [-12, 12]
 
 @return * 0: Success. * <0: Failure.
 */
- (int)setAudioMixingPitch:(NSInteger)pitch;
#pragma mark Audio effect
/*get audio playback volume (0 ~ 1.0)*/
- (float)getEffectsVolume;
/*set audio effect volume (0 ~ 1.0), default value is 0.5*/
- (int)setEffectsVolume:(float)volume;
/*set audio effect volume (0 ~ 1.0), default value is 0.5*/
- (int)setVolumeOfEffect:(int)soundId
              withVolume:(float)volume;
- (int)playEffect:(int)soundId
         filePath:(NSString * _Nullable)filePath
        loopCount:(int)loopCount
            pitch:(int)pitch
              pan:(double)pan
             gain:(double)gain
          publish:(BOOL)publish;
- (int)stopEffect:(int)soundId;
- (int)stopAllEffects;
- (int)pauseEffect:(int)soundId;
- (int)pauseAllEffects;
- (int)resumeEffect:(int)soundId;
- (int)resumeAllEffects;

- (void)forwardDownlinkAudio:(NSUInteger)uid Enable:(BOOL) enable;

#pragma mark audio processing
- (int)setChannelNum:(int)num;
- (int)setAudioAECEnable:(BOOL)enable;
- (int)setAudioAECLevel:(int)level;
- (int)setAudioAGCEnable:(BOOL)enable;
- (int)setAudioANSEnable:(BOOL)enable;
#pragma mark Stream publish
- (int)addPublishStreamUrl:(NSString * _Nonnull)url transcodingEnabled:(BOOL) transcodingEnabled;
- (int)removePublishStreamUrl:(NSString * _Nonnull)url;
- (int)setLiveTranscoding:(MMLiveTranscoding *_Nullable) transcoding;
#pragma mark Other methods
/**
 *  Specify sdk parameters
 *  @param options sdk options in json format.
 */
- (int)setParameters:(NSString * _Nonnull)options;

- (NSString * _Nullable)getParameter:(NSString * _Nonnull)parameter
                                args:(NSString * _Nullable)args;

/**
 *  Specifies the SDK output log file.
 *  @param filePath The full file path of the log file.
 *  @return 0 when executed successfully. return negative value if failed.
 */
- (int)setLogFile:(NSString * _Nonnull)filePath;

/**
 *  Specifiy the log level of output
 *  @param filter The log level
 *  @return 0 when executed successfully. return negative value if failed.
 */
- (int)setLogFilter:(NSUInteger)filter;

#pragma mark media external methods
- (int)registerAudioFrameObserver:(MMAudioFrameObserver*)observer;
- (int)registerVideoFrameObserver:(MMVideoFrameObserver*)observer;
- (int)processVideoFrame:(CMSampleBufferRef)sampleBuffer;
- (int)processAudioFrame:(MMAudioFrameObserver::AudioFrame *)frame;
- (int)processMessage:(int64_t)pts;
- (int)sendStreamMessage:(NSInteger)streamId msg:(NSString *)msg;
@property(weak,nonatomic)id<MMLiveRtcEngineDelegate> delegate;
@end

NS_ASSUME_NONNULL_END
