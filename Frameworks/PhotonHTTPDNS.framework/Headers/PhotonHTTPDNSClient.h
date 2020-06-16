//
//  PhotonHTTPDNS.h
//  MMDNSDemo
//
//  Created by Bruce on 2018/9/20.
//  Copyright © 2018年 Bruce. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "PhotonHTTPDNSConfigProtocol.h"
NS_ASSUME_NONNULL_BEGIN
@interface PhotonHTTPDNSClient : NSObject

/**
设置HTTPDNS,在startAutoRequest之前调用
*/
+ (void)initHTTPDNSWithConfig:(id<PhotonHTTPDNSConfigProtocol>)config;

/**
 在initHTTPDNSWithConfig方法之后 startAutoRequest之前调用
 */
+ (void)shouldConsolLog:(BOOL)en;

/**
那些请求走自动的httpdns接入,在startAutoRequest之前调用.
@param domainList 设置支持走自动处理httpdns的请求
*/
+ (void)setRequestDomainFilter:(nullable NSSet *)domainList;

+ (void)supportWKWebview;

/// 开启自动请求
+ (void)startEnableAutoRequest;


+ (BOOL)autoEnableHTTPDNS;
/**
 获取可用的连接host

 @param host 原请求的host
 @return 真实请求使用的ip
 */
+ (NSString *)getIPbyHost:(nullable NSString *)host;

/**
 获取可用的连接host
 
 @param host 原请求的host
 @return 真实请求使用的ip列表
 */
+ (NSArray *)getIPsbyHost:(nullable NSString *)host;

/**
 连接成功后调用，通知DNS模块
 @param mainDomain 最初请求的域名
 @param succeedDomain 在请求成功时使用的域名
 @param successedPort 请求成功时使用的port
 */
+ (void)requestSucceedForDomain:(nullable NSString *)mainDomain andSucceedDomain:(nullable NSString *)succeedDomain andSuccessedPort:(NSInteger)successedPort;

/**
 连接失败后调用，通知DNS模块
 @param mainDomain 最初请求的域名
 @param failedDomain 在请求失败时使用的域名
 @param failedPort 请求失败时使用的port
 */
+ (void)requestFailedForDomain:(nullable NSString *)mainDomain andFailedDomain:(nullable NSString *)failedDomain andFailedPort:(NSInteger)failedPort;


/**
服务端针对域名指定下发使用的连接ip和域名地址
@parameter main_domain 主域名
@parameter address 服务端下发的连接地址，格式 host:port
*/

+ (void)storeCustomIpByDomain:(nullable NSString *)mainDomain address:(nullable NSString *)address;
/**
服务端针对域名指定下发使用的连接ip和域名地址
@parameter main_domain 主域名
@parameter ip 服务端下发的连接地址
@parameter port 服务端下发的连接地址
*/

+ (void)storeCustomIpByDomain:(nullable NSString *)mainDomain ip:(nullable NSString *)ip port:(NSInteger)port;

/**
服务端针对域名指定下发使用的连接ip和域名地址
@parameter main_domain 主域名
@parameter addressList 服务端下发的连接地址集合，格式[address,address,...],其中address格式为 host:port
*/

+ (void)storeCustomIpsByDomain:(nullable NSString *)mainDomain addressList:(nullable NSArray *)addressList;


@end
NS_ASSUME_NONNULL_END
