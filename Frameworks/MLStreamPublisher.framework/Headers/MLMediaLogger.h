//
//  MLMediaLogger.h
//  MomoChat
//
//  Created by wangqiangqiang on 2018/3/9.
//  Copyright © 2018年 wemomo.com. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef enum {
    MLMediaLogTypeAll        = -1,// 输出所有日志信息
    MLMediaLogTypeNone       = 0,// 不输出任何日志信息
    MLMediaLogTypeConference = 1,
    MLMediaLogTypePublisher  = 1 << 1,
    MLMediaLogTypePlayer     = 1 << 2,
    MLMediaLogTypeError      = 1 << 3,
} MLMediaLogType;


/**
 *  输出Debug信息，由全局level以及type控制是否输出console
 *
 *  @param type   类型
 *  @param format 格式
 *  @param ...    参数
 */
FOUNDATION_EXPORT void MLMediaLogWithType(MLMediaLogType type, NSString *format, ...);
