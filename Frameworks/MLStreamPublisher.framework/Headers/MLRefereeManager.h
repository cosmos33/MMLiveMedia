//
//  MLRefereeManager.h
//  Pods
//
//  Created by lihao on 2020/3/18.
//

#ifndef MLRefereeManager_h
#define MLRefereeManager_h

#import <Foundation/Foundation.h>
#import "MLDomainAnalysis.h"
#import "MMLiveHTTPDNSConfig.h"

@interface MLRefereeManager : NSObject
@property (nonatomic, assign) int faildTimeInterval;
@property (nonatomic, assign) int faildCountMax;
@property (nonatomic, assign) int refereeTimeInterval;
@property (nonatomic, strong) MMLiveHTTPDNSConfig *config;
@property (atomic, strong) id <MLDomainAnalysis> domainAnalysis;

+ (instancetype)shareManager;

/**
 获取域名解析的ip（所有中台网络请求均会调用）
 */
- (NSString *)getDomainAnalysis:(NSString *)domain;

/**
域名请求结束，返回请求成功或失败（每次请求结束后上报，之后走更新控制流程）
*/
- (void)domainRequestFinish:(NSString *)domain analysisIp:(NSString *)analysisIp success:(BOOL)success;

/**
开关域名解析功能
*/
- (void)enableDomainAnalysis:(BOOL)enable;

@end
#endif /* MMLiveContext_h */
