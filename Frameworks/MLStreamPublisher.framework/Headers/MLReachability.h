//
//  MLReachability.h
//  MLStreamPublisher
//
//  Created by wangqiangqiang on 2018/5/4.
//

#import <Foundation/Foundation.h>

typedef enum : NSInteger
{
    MLNotReachable = 0,
    MLReachableViaWiFi,
    MLReachableViaWWAN
} MLNetworkStatus;

#pragma mark IPv6 Support
//Reachability fully support IPv6.  For full details, see ReadMe.md.


extern NSString *kMLReachabilityChangedNotification;

@interface MLReachability : NSObject

/*!
 * Use to check the reachability of a given host name.
 */
+ (instancetype)reachabilityWithHostName:(NSString *)hostName;

/*!
 * Use to check the reachability of a given IP address.
 */
+ (instancetype)reachabilityWithAddress:(const struct sockaddr *)hostAddress;

/*!
 * Checks whether the default route is available. Should be used by applications that do not connect to a particular host.
 */
+ (instancetype)reachabilityForInternetConnection;


#pragma mark reachabilityForLocalWiFi
//reachabilityForLocalWiFi has been removed from the sample.  See ReadMe.md for more information.
//+ (instancetype)reachabilityForLocalWiFi;

/*!
 * Start listening for reachability notifications on the current run loop.
 */
- (BOOL)startNotifier;
- (void)stopNotifier;

- (MLNetworkStatus)currentReachabilityStatus;

/*!
 * WWAN may be available, but not active until a connection has been established. WiFi may require a connection for VPN on Demand.
 */
- (BOOL)connectionRequired;

/*!
 * to get human readable network type by specific reachability instance
 */
+ (NSString *)networkConnectionTypeWithReachablitiy:(MLReachability *)reachability;

/*!
 * to get human readable network type
 */
+ (NSString *)networkConnectionType;

@end
