// Copyright 2020 ADTIMING TECHNOLOGY COMPANY LIMITED
// Licensed under the GNU Lesser General Public License Version 3

#import <Foundation/Foundation.h>
#import "OMInterstitialCustomEvent.h"
#import "OMHyBigInterstitialClass.h"
#import "OMHyBidClass.h"

NS_ASSUME_NONNULL_BEGIN

@interface OMHyBidInterstitial : NSObject<OMInterstitialCustomEvent,HyBidInterstitialAdDelegate>

@property (nonatomic, copy) NSString *pid;
@property (nonatomic, strong) HyBidInterstitialAd *fullscreenVideoAd;
@property (nonatomic, assign) BOOL isReady;
@property (nonatomic, assign) BOOL isMediation;
@property (nonatomic, weak) id<interstitialCustomEventDelegate> delegate;
@property (nonatomic, weak) id<HyBidDelegate> bidDelegate;

- (instancetype)initWithParameter:(NSDictionary*)adParameter;
- (void)loadAd;
- (BOOL)isReady;
- (void)show:(UIViewController*)vc;

@end

NS_ASSUME_NONNULL_END
