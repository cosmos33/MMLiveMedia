//
//  MLPublisherError.h
//  MomoChat
//
//  Created by YuAo on 9/29/16.
//  Copyright © 2016 wemomo.com. All rights reserved.
//

//errcode//错误码（0:正常停止，1:网络错误,2:camera 错误，3:audio 错误，4：视频编码器错误，5:音频编码器错误）
typedef NS_ENUM(NSInteger, MLPublisherError) {
    MLPublisherErrorNone = 0,
    
    /*
     MLPublisherErrorNetworkFailure = 1,
     MLPublisherErrorVideoDeviceFailure = 2,
     MLPublisherErrorAudioDeviceFailure = 3,
     */
    MLPublisherErrorVideoEncoderFailure = 4,
    MLPublisherErrorAudioEncoderFailure = 5,
     
    
    MLPublisherErrorNetworkDelay = 6,

    MLPublisherErrorWeilaParameterInvalid = 7,
    MLPublisherErrorWeilaInstanceInitFailure = 8,
    MLPublisherErrorWeilaAPIInitFailure = 9,

    MLPublisherErrorNetworkFailure = 10,
    MLPublisherErrorRTMPInitFailure = 11,
    MLPublisherErrorRTMPNetworkFailure = 12,

    MLPublisherErrorStatusAlreadyStarted = 13, //iOS only

    MLPublisherErrorSentDataAbnormal = 14,

    MLPublisherErrorAgoraJoinChannelFail = 15,
    MLPublisherErrorAgoraNoPermission = 16,
    MLPublisherErrorAgoraInitVideo = 17,
    MLPublisherErrorAgoraStartCall = 18,
    MLPublisherErrorAgoraAdmError = 19,

    MLPublisherErrorSwithingToConference = 20,
    MLPublisherErrorSwithingAgoraToIJK = 21, //切换 AgoraPublisher  到 IJKPublisher
    MLPublisherErrorSwithingWeilaToIJK = 22, //切换 WeilaPublisher  到 IJKPublisher
    MLPublisherErrorSwithingConferenceTimeout = 23, //30秒连线失败 切换IJK
    MLPublisherErrorCreateH265EncoderFailed = 24, //265编码器创建失败重启265
    MLPublisherErrorSwithingTencentToIJK = 25, //切换 TencentPublisher  到 IJKPublisher
    MLPublisherErrorSwithingMrtcToIJK = 26, //切换 TencentPublisher  到 IJKPublisher

    //iOS only
    MLPublisherErrorAudioRender = 100,
    MLPublisherErrorAudioSampleRateChange = 101,
    MLPublisherErrorAudioRecordIsMute = 102,
    MLPublisherErrorAudioRecordMediaServerReset = 103,
    
    //Live Aid
    MLPublisherErrorDisconnectByMomo = 201,
    MLPublisherErrorDisconnectByLiveAid = 202,
    MLPublisherErrorDisconnectBySocketError = 203,
    MLPublisherErrorDisconnectByPlayFailed = 204,
    MLPublisherErrorDisconnectByPushStreamError = 205,
    MLPublisherErrorDisconnectByNetworkChange = 206,
    
    //声网进入房间失败错误码
    MLPublisherErrorAgoraAppidStateInvalid = 806,//不是有效的 APP ID
    MLPublisherErrorAgoraTokenStateInvalid = 808,//token失效
    MLPublisherErrorAgoraTokenStateExpired = 809,//token过期

    //微辣进入房间失败错误码，错误码9分拆如下
    MLPublisherErrorWeilaEnterRoomTimeout = 901, // 超时,10秒未收到微辣服务器返回结果
    MLPublisherErrorWeilaEnterRoomFailed = 902, // 无法连接微辣服务器
    MLPublisherErrorWeilaEnterRoomVerifyFailed = 903, // 微辣验证码错误
    MLPublisherErrorWeilaEnterRoomBadVersion = 904,  //微辣错误版本
    
    //正常关闭，和 MLPublisherErrorNone 一样处理，加error code 区分来源，
    MLPublisherErrorDebugNone = 2000,
    MLPublisherErrorOption = 2001,  // 开始推流前先停止推流 开始双推流结束
    MLPublisherErrorRelease = 2002, // 业务层不会调用 媒体层才会调
    MLPublisherErrorCheckType = 2003,   // querypub成功后 需要重置推流器(先stop)
    MLPublisherErrorDealloc = 2004, // 退出房间
    MLPublisherErrorKick = 2005,
    MLPublisherErrorEndBroadcast = 2006,
    MLPublisherErrorAudioInterrupt = 2007,
    MLPublisherErrorQuerypubFail = 2008,
    MLPublisherErrorEnterBackground = 2009,
    MLPublisherErrorEnterBackgroundMySelfConnecting = 2010,
    MLPublisherErrorStreamPublisherError = 2011,
    MLPublisherErrorGuestCloseConference = 2012,
    MLPublisherErrorIMConnectReset = 2013,  // 收到 MLPBDownUnit_Type_ChStreamURL(陌陌直播间更换流地址协议) im消息
    MLPublisherErrorIMConnectResetAlert = 2014, // 同2013
    MLPublisherErrorRoomProfile = 2015, // 没有调用
    MLPublisherErrorAudioInterruptEnd = 2016,   //音频打断结束
    MLPublisherErrorNetworkWarning = 2017,  //当前网络状况不佳
    MLPublisherErrorDropPacket = 2018,  //丢包
    MLPublisherErrorByHeartFaild = 2019,//心跳接口失败导致停止推流器
    
    //平滑切换相关的停止描述
    MLPublisherErrorLastPublisherBrokenPipe = 2200, //上一路流被踢掉
    MLPublisherErrorLastPublisherDelayStop = 2201, //延时停止上一路流
    MLPublisherErrorLastPublisherNOError = 2202, //出现快速切换时候，tempPub停止的错误码

    // 24小时房间
    MLPublisherErrorFulltimeHostOffline = 2100, // 主播下线
    //副播Slaver断开连线详细原因，2012被拆分以下各种情况
    MLPublisherErrorSlaverExit = 3001, // 副麦正常退出
    MLPublisherErrorSlaverRestartPlay = 3002, // 重新开播
    MLPublisherErrorSlaverActivityStop = 3003, // 应用生命周期停止
    MLPublisherErrorSlaverOnlineTimeout = 3004, // 连麦超时
    MLPublisherErrorSlaverNetworkError = 3005, // 网络错误
    MLPublisherErrorSlaverQuit = 3006, // 自己主动退出，不在频道 对应媒体返回是0
    MLPublisherErrorSlaverDropped = 3007, // 断线，不在频道 对应媒体返回是1
    MLPublisherErrorSlaverBecomeAudience = 3008, // 切换角色，还在频道 对应媒体返回是2
    MLPublisherErrorSlaverStartPubApiError = 3009, // 开始推流api错误
    MLPublisherErrorSlaverSmallWindowExit = 3010, // 小窗退出连麦
    MLPublisherErrorSlaverImHostRequestClose = 3011, // 主播请求退出
    MLPublisherErrorSlaverImHeartBeatStop = 3012, // 没有心跳断开
    MLPublisherErrorSlaverStreamPublisherError = 3013,//网络问题
    MLPublisherErrorSlaverExitRoom = 3014, // 副麦退出直播
    MLPublisherErrorSlaverAudioInterrupt = 3015, //音频被打断
    MLPublisherErrorSlaverEnterBackgroundOrForeground  = 3016, ///进入前后台
    MLPublisherErrorSlaverViolationKickOff = 3017, // 副麦被踢出房间
    MLPublisherErrorSlaverHostStopLive = 3018, // 主播关闭直播
    MLPublisherErrorSlaverStarRequestClose = 3019, // 主播请求关闭
    MLPublisherErrorSlaverMemExit = 3020, // 微辣退出
    MLPublisherErrorSlaverRestartMatch = 3021, // 重新匹配
    MLPublisherErrorSlaverReConnect = 3022, // 连线重试
    MLPublisherErrorFulltimePushingToCDN = 3054,//24小时房转推失败
    MLPublisherErrorSlaverUnknow = 3100, // 未知原因
    
    MLPublisherErrorAgentBase = 4000
};
