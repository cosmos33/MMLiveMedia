//
//  MMLiveRtcCode.h
//  MomoLiveRoom
//
//  Created by chenyong on 2019/2/27.
//  Copyright © 2019年 momo. All rights reserved.
//

#ifndef MMLiveCodeDescription_h
#define MMLiveCodeDescription_h
#define MMLiveServerErrorCodeBase 520
typedef enum _MMLiveWarningCode{
    
}MMLiveWarningCode;

typedef enum _MMLiveErrorCode{
    MMLiveErrorCodeCreateRoom = 500,            //可能没有了
    MMLiveErrorCodeReJoinRoom,
    MMLiveErrorCodeMeidiaServer,
    MMLiveErrorCodeGetServerInfo,
    MMLiveErrorCodePKReStartTimesOver,
    MMLiveErrorCodeVideoEncoderCreated,
}MMLiveErrorCode;


typedef enum _MMLogCode{
    MMRTCLogUnKnown = 0,
    MMRTCLogPushStart = 1,
    MMRTCLogPushStop,
    MMRTCLogPushWatch,
    MMRTCLogPullWatch,
    MMRTCLogReconnect,
    MMRTCLogMsgLogin = 11,
    MMRTCLogMsgonLogin,
    MMRTCLogMsgHeart,
    MMRTCLogMsgJoin,
    MMRTCLogMsgOnJoin,
    MMRTCLogMsgLeave,
    MMRTCLogMsgOnLeave,
    MMRTCLogMsgPeerJoin,
    MMRTCLogMsgPeerLeave,
    MMRTCLogMsgAddUrl,
    MMRTCLogMsgRemoveUrl = 21,
    MMRTCLogMsgTranscoding,
    MMRTCLogMsgLocalAudioMute,
    MMRTCLogMsgRemoteAudioMute,
    MMRTCLogMsgLocalVideoMute,
    MMRTCLogMsgRemoteVideoMute,
    MMRTCLogMsgReJoin,
    MMRTCLogMsgOnReJoin,
    MMRTCLogMsgStartPK,
    MMRTCLogMsgOnStartPK,
    MMRTCLogMsgStopPK = 31,
    MMRTCLogMsgOnStopPK,
    MMRTCLogMsgPeerLost,
    MMRTCLogMsgKeyExpired,
    MMRTCLogMsgKeyUpdate,
    MMRTCLogMsgChangeRole,
    MMRTCLogMsgOnChangeRole,
    MMRTCLogMsgOnLicked
}MMLogCode;

typedef enum _MMReconnectType{
    MMErrorTcp = 0,
    MMErrorTls,
    MMErrorApp,
    
}MMReconnectType;

typedef enum _MMReconnectApp{
    MMAppUninit = 0,
    MMAppSocketCreate,
    MMAppRecvLen,
    MMAppSSlNull,
    MMAppHeart,
    MMAppTlsConnect,
    
}MMReconnectApp;

#endif /* MMLiveCodeDescription_h */
