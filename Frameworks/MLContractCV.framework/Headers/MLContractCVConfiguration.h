//
//  MLContractCVConfig.h
//  MLContractCV
//
//  Created by 杨乃川 on 2020/9/15.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface MLContractCVConfiguration : NSObject
// auth
@property(nonatomic, copy, class) NSString *licensePath;
@property(nonatomic, copy, class) NSString *modelDirectoryPath;


// metal
@property (nonatomic, copy, class) NSString *metalLibraryName;
@property (nonatomic, readonly, class) NSBundle *libraryBundle;
@property (nonatomic, readonly, class) NSURL *libraryURL;
@end

NS_ASSUME_NONNULL_END
