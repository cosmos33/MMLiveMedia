//
//  MLVolcEngineVideoSink.h
//  MLStreamPublisher
//
//  Created by gongyulin on 2023/5/5.
//

#ifndef MLVolcEngineVideoSink_h
#define MLVolcEngineVideoSink_h

#import <Foundation/Foundation.h>
#import <VolcEngineRTC/VolcEngineRTC.h>

@protocol MLVideoSinkDelegate <NSObject>

- (void)renderPixelBuffer:(CVPixelBufferRef _Nullable )pixelBuffer userId:(NSString *_Nullable)userId;

@end

@interface MLVolcEngineVideoSink : NSObject <ByteRTCVideoSinkDelegate>

@property (nonatomic, weak) id<MLVideoSinkDelegate> _Nullable delegate;
@property (nonatomic, strong) NSString * _Nullable userId;

- (int)getRenderElapse;

- (void)renderPixelBuffer:(CVPixelBufferRef _Nonnull)pixelBuffer rotation:(ByteRTCVideoRotation)rotation contentType:(ByteRTCVideoContentType)contentType extendedData:(NSData * _Nullable)extendedData;

@end

#endif /* MLVolcEngineVideoSink_h */
