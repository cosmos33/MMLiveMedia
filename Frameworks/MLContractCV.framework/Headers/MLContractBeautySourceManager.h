//
//  MLContractBeautySourceManager.h
//  Pods
//
//  Created by Bean on 2021/1/20.
//

typedef enum {
    MLContractBeautySourceCompose = 0,
    MLContractBeautySourceFilter = 1
} MLContractBeautySourceItemType;

@class MLContractBeautySourceItem;
@class MLContractBeautySourceGroupItem;

@interface MLContractBeautySourceRootModel : NSObject

@property (nonatomic, strong, readonly) MLContractBeautySourceGroupItem *beautySourceGroupItem;
@property (nonatomic, strong, readonly) MLContractBeautySourceGroupItem *reshapeSourceGroupItem;
@property (nonatomic, strong, readonly) MLContractBeautySourceGroupItem *makeupSourceGroupItem;
@property (nonatomic, strong, readonly) MLContractBeautySourceGroupItem *filterSourceGroupItem;
@property (nonatomic, strong, readonly) MLContractBeautySourceGroupItem *makeupStyleSourceGroupItem;

@end

@interface MLContractBeautySourceGroupItem : NSObject

@property (nonatomic, assign, readonly) BOOL hasSubGroups;
@property (nonatomic, strong, readonly) NSString *groupName;
@property (nonatomic, strong, readonly) NSArray<MLContractBeautySourceGroupItem *> *subGroupsArray;
@property (nonatomic, strong, readonly) NSArray<MLContractBeautySourceItem *> *itemsArray;

@end

@interface MLContractBeautySourceItem : NSObject

@property (nonatomic, strong, readonly) NSString *name;
@property (nonatomic, strong, readonly) NSString *identifier;
@property (nonatomic, strong, readonly) NSString *keyForMakeup;
@property (nonatomic, strong, readonly) NSString *keyForFilter;
@property (nonatomic, assign, readonly) MLContractBeautySourceItemType type;

@end

@interface MLContractBeautySourceManager : NSObject

+ (BOOL)configSourcePath:(NSString *)sourcePath;
+ (BOOL)configSourcePath:(NSString *)sourcePath forceReload:(BOOL)forceReload;
+ (NSString *)sourcePathForIdentifier:(NSString *)identifier;
+ (MLContractBeautySourceRootModel *)beautySourceTotalInfos;
+ (MLContractBeautySourceItem *)beautySourceItemByIdentifier:(NSString *)identifier keyForMakeup:(NSString *)keyForMakeup keyForFilter:(NSString *)keyForFilter;

@end
