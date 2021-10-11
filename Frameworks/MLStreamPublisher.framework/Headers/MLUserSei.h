//
//  MLUserSei.h
//  MomoChat
//
//  Created by MOMO on 12/21/16.
//  Copyright © 2016 wemomo.com. All rights reserved.
//

#ifndef MLUserSei_h
#define MLUserSei_h

#include <stdio.h>
 
/*
 为了方便播放器检查出自定义的SEI内容，并且不破坏SEI协议，新增uuid，和json 长度字段，并且内存排列如下：
 16bytes_uuid | 2bytes_json_payload_big_endian_len   |  json_payload
 微辣uuid 定义如下
 uint8_t uuid[16] = {'m', 'o', 'm', 'o',
 'a', '9', 'a', '4',
 '2', '7', 'd', '1’,
 'w', 'e', 'i', 'l',
 };
 
 声网uuid定义如下
 uint8_t uuid[16] = {'m', 'o', 'm', 'o',
 'a', '9', 'a', '4',
 '2', '7', 'd', '1’,
 'a', 'r', 'g', 'o',
 };
 
 uuid 前12个字节(uuid[0]-uuid[11])固定，后四个字节（uuid[12]-uuid[15]）厂商自定义，
 播放器只检查并比较前12字节，来确定有无定义SEI即可。
 payload_len 改成2bytes而不是4bytes长度，目的是为了避免h264 协议遇到连续的3bytes 0x00，插入0x03的问题。
 */

static const size_t  JSON_PAYLOAD_SIZE = 2;
static const size_t  UUID_SIZE         = 16;
static const size_t  FIXED_UUID_SIZE   = UUID_SIZE - 4;
static const size_t  USER_DEFINE_DATA_HEADER_SIZE          = UUID_SIZE+JSON_PAYLOAD_SIZE;
//static const uint8_t weila_uuid[UUID_SIZE]                 = "momoa9a427d1weil";
//static const uint8_t agro_uuid[UUID_SIZE]                  = "momoa9a427d1argo";
static const uint8_t USER_DEFINE_SEI_UUID[FIXED_UUID_SIZE] = {'m','o','m','o','a','9','a','4','2','7','d','1'};
static const uint8_t MOMO_IOS_UUID[UUID_SIZE] = {'m','o','m','o','a','9','a','4','2','7','d','1','m','i','o','s'};
static const uint8_t IJK_DEFINE_SEI_UUID[UUID_SIZE] = {'m','o','m','o','a','9','a','4','2','7','d','1','f','a','k','e'};

#define MAX_SEI_PAYLOAD_SIZE (2048)
typedef struct {
    uint8_t uuid[UUID_SIZE];
    uint16_t payload_size;
    uint8_t payload[MAX_SEI_PAYLOAD_SIZE];
} UserSeiData;

// sei key
static NSString *const MLUserSeiHasKey = @"has"; // 声网普通连麦
static NSString *const MLUserSeiPosKey = @"pos"; // 微辣普通连麦
static NSString *const MLUserSeiConfKey = @"conf"; // 交友模式
static NSString *const MLUserSeiInfoKey = @"info";
static NSString *const MLUserSeiBgrgbKey = @"bgrgb";
static NSString *const MLUserSeiAlphaKey = @"alpha";
static NSString *const MLUserSeiCanvasKey = @"canvas";
static NSString *const MLUserSeiRenderModeKey = @"renderMode";
static NSString *const MLUserSeiRatioTransformerKey = @"ratio_transformer";
static NSString *const MLUserSeiCtypKey = @"ctyp"; // 1 普通 2 交友 3 pk模式 4 主持
static NSString *const MLUserSeiCropKey = @"crop";
static NSString *const MLUserSeiMidKey = @"mid";
static NSString *const MLUserSeiVerKey = @"ver";
static NSString *const MLUserSeiIDKey = @"id";
static NSString *const MLUserSeiTsKey = @"ts";
static NSString *const MLUserSeiXKey = @"x";
static NSString *const MLUserSeiYKey = @"y";
static NSString *const MLUserSeiZKey = @"z";
static NSString *const MLUserSeiWKey = @"w";
static NSString *const MLUserSeiHKey = @"h";
static NSString *const MLUserSeiCuidsKey = @"cuids";
static NSString *const MLUserSeiInvKey = @"inv";
static NSString *const MLUserSeiMuKey = @"mu";
static NSString *const MLUserSeiOlKey = @"ol";
static NSString *const MLUserSeiVoKey = @"vo";
static NSString *const MLUserSeiPKMuKey = @"pkmu";
#endif /* MLUserSei_h */
