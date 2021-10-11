//
//  MLMediaCommonDefine.h
//  MLStreamPublisher
//
//  Created by hrs on 2019/11/28.
//

#ifndef MLMediaCommonDefine_h
#define MLMediaCommonDefine_h

typedef NS_ENUM(NSUInteger, MLPublisherOptionRoomMode) {
    MLPublisherOptionRoomModeUndefined = 0,
    MLPublisherOptionRoomModeVideoCommon = 111,
    MLPublisherOptionRoomModeVideoFriend = 112,
    MLPublisherOptionRoomModeVideoPK = 113,
    MLPublisherOptionRoomModeVideoEmcee = 114,
    MLPublisherOptionRoomModeVideoTruthOrDare = 116,
    MLPublisherOptionRoomModeDoubleIce = 118,
    MLPublisherOptionRoomModeDeskMateGame = 119,
    MLPublisherOptionRoomModeVideoAppraise = 120,
    MLPublisherOptionRoomModeVideoGroup = 121,
    MLPublisherOptionRoomModeVideoPerformance = 122,
    
    MLPublisherOptionRoomModeConnectModeTypePKRound = 130,
    MLPublisherOptionRoomModeArenaVideoConnectScreen = 131,
    MLPublisherOptionRoomModeArenaVideoSurvivor = 133,
    MLPublisherOptionRoomModeArenaVideoTakeCrown = 134,
    MLPublisherOptionRoomModeArenaVideoJoinedLive = 135,
    MLPublisherOptionRoomModeArenaVideoLord = 136,
    MLPublisherOptionRoomModeArenaExpressionBattle = 137,
    MLPublisherOptionRoomModeSnowBallFaght = 138,
    MLPublisherOptionRoomModeDeskMatePK = 139,
    MLPublisherOptionRoomModeTypeVideoTeamBattles = 151,
    MLPublisherOptionRoomModeTypeVideoPal = 152,
    MLPublisherOptionRoomModeTypeFTPal = 153,
    MLPublisherOptionRoomModeTypeMatchmaker=154,
    MLPublisherOptionRoomModeTypeGuinness = 155,
    MLPublisherOptionRoomModeTypeWedding = 156,
    MLPublisherOptionRoomModeCameraExtension = 191,
    MLPublisherOptionRoomModeCameraExtension2 = 192,
    MLPublisherOptionRoomModeWolfKillLive = 195,
    MLPublisherOptionRoomModeWorldCup = 196,
    MLPublisherOptionRoomModeQuestion = 197,
    
    MLPublisherOptionRoomModeRadioCommon = 211,
    MLPublisherOptionRoomModeRadioFriend = 212,
    MLPublisherOptionRoomModeRadioPK = 231,
    MLPublisherOptionRoomModeRadioFulltime = 252,
    MLPublisherOptionRoomModeRadioBlindDate = 253,
    MLPublisherOptionRoomModeRadioMakeFriend = 254,
    MLPublisherOptionRoomMondeRadioSingle = 255,
    MLPublisherOptionRoomMondeTogether = 256,
    MLPublisherOptionRoomModeRadioGame = 261,
    MLPublisherOptionRoomModeLiveSocialGame = 301,
    MLPublisherOptionRoomModeTogetherGame = 302
};

typedef enum{
    MLDomainLiveLog = 0,
    MLDomainLiveApi, 
    MLDomainLiveSla,
    MLDomainLiveMedia
}MLMediaDomainTable;

#endif /* MLMediaCommonDefine_h */
