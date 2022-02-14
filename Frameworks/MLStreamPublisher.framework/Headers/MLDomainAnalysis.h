//
//  MLDomainAnalysis.h
//  Pods
//
//  Created by lihao on 2020/3/18.
//


#import <Foundation/Foundation.h>

@protocol MLDomainAnalysis <NSObject>
/**
 获取域名解析的ip（所有中台网络请求均会调用）
 */
- (NSString *)getDomainAnalysis:(NSString *)domain;

/**
 域名请求结束，返回请求成功或失败（每次请求结束后上报，之后走更新控制流程）
*/
- (void)domainRequestFinish:(NSString *)domain analysisIp:(NSString *)analysisIp success:(BOOL)success;

@end
