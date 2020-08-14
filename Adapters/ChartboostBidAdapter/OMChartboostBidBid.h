// Copyright 2020 ADTIMING TECHNOLOGY COMPANY LIMITED
// Licensed under the GNU Lesser General Public License Version 3

#import <Foundation/Foundation.h>


NS_ASSUME_NONNULL_BEGIN

@interface OMChartboostBidBid : NSObject
+ (void)bidWithNetworkItem:(id)networkItem adFormat:(NSString*)format responseCallback:(void(^)(NSDictionary *bidResponseData))callback;

@end

NS_ASSUME_NONNULL_END
