// Copyright 2020 ADTIMING TECHNOLOGY COMPANY LIMITED
// Licensed under the GNU Lesser General Public License Version 3

#ifndef OMPangleNativeClass_h
#define OMPangleNativeClass_h
#import <UIKit/UIKit.h>
#import "OMPangleClass.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, BUProposalSize) {
    BUProposalSize_Banner600_90,
    BUProposalSize_Banner600_100,
    BUProposalSize_Banner600_150,
    BUProposalSize_Banner600_260,
    BUProposalSize_Banner600_286,
    BUProposalSize_Banner600_300,
    BUProposalSize_Banner600_388,
    BUProposalSize_Banner600_400,
    BUProposalSize_Banner600_500,
    BUProposalSize_Feed228_150,
    BUProposalSize_Feed690_388,
    BUProposalSize_Interstitial600_400,
    BUProposalSize_Interstitial600_600,
    BUProposalSize_Interstitial600_900,
    BUProposalSize_DrawFullScreen
};


typedef NS_ENUM(NSInteger, BUAdSlotAdType) {
    BUAdSlotAdTypeUnknown       = 0,
    BUAdSlotAdTypeBanner        = 1,       // banner ads
    BUAdSlotAdTypeInterstitial  = 2,       // interstitial ads
    BUAdSlotAdTypeSplash        = 3,       // splash ads
    BUAdSlotAdTypeSplash_Cache  = 4,       // cache splash ads
    BUAdSlotAdTypeFeed          = 5,       // feed ads
    BUAdSlotAdTypePaster        = 6,       // paster ads
    BUAdSlotAdTypeRewardVideo   = 7,       // rewarded video ads
    BUAdSlotAdTypeFullscreenVideo = 8,     // full-screen video ads
    BUAdSlotAdTypeDrawVideo     = 9,       // vertical (immersive) video ads
};

typedef NS_ENUM(NSInteger, BUAdSlotPosition) {
    BUAdSlotPositionTop = 1,
    BUAdSlotPositionBottom = 2,
    BUAdSlotPositionFeed = 3,
    BUAdSlotPositionMiddle = 4, // for interstitial ad only
    BUAdSlotPositionFullscreen = 5,
};

typedef NS_ENUM(NSInteger, BUPlayerPlayState) {
    BUPlayerStateFailed    = 0,
    BUPlayerStateBuffering = 1,
    BUPlayerStatePlaying   = 2,
    BUPlayerStateStopped   = 3,
    BUPlayerStatePause     = 4,
    BUPlayerStateDefalt    = 5
};

@interface BUSize : NSObject

// width unit pixel.
@property (nonatomic, assign) NSInteger width;

// height unit pixel.
@property (nonatomic, assign) NSInteger height;

- (NSDictionary *)dictionaryValue;

@end

@interface BUSize (BU_SizeFactory)
+ (instancetype)sizeBy:(BUProposalSize)proposalSize;
@end

@interface BUAdSlot : NSObject

/// required. The unique identifier of a native ad.
@property (nonatomic, copy) NSString *ID;

/// required. Ad type.
@property (nonatomic, assign) BUAdSlotAdType AdType;

/// required. Ad display location.
@property (nonatomic, assign) BUAdSlotPosition position;

/// Accept a set of image sizes, please pass in the BUSize object.
@property (nonatomic, strong) NSMutableArray<BUSize *> *imgSizeArray;

/// required. Image size.
@property (nonatomic, strong) BUSize *imgSize;

/// Icon size.
@property (nonatomic, strong) BUSize *iconSize;

/// Maximum length of the title.
@property (nonatomic, assign) NSInteger titleLengthLimit;

/// Maximum length of description.
@property (nonatomic, assign) NSInteger descLengthLimit;

/// Whether to support deeplink.
@property (nonatomic, assign) BOOL isSupportDeepLink;

/// Native banner ads and native interstitial ads are set to 1, other ad types are 0, the default is 0.
@property (nonatomic, assign) BOOL isOriginAd;

- (NSDictionary *)dictionaryValue;

@end



@interface BUImage : NSObject <NSCoding>

// image address URL
@property (nonatomic, copy) NSString *imageURL;

// image width
@property (nonatomic, assign) float width;

// image height
@property (nonatomic, assign) float height;

- (instancetype)initWithDictionary:(NSDictionary *)dic;

- (NSDictionary *)dictionaryValue;

@end


@interface BUMaterialMeta : NSObject <NSCoding>

/// interaction types supported by ads.
@property (nonatomic, assign) BUInteractionType interactionType;

/// material pictures.
@property (nonatomic, strong) NSArray<BUImage *> *imageAry;

/// ad logo icon.
@property (nonatomic, strong) BUImage *icon;

/// ad headline.
@property (nonatomic, copy) NSString *AdTitle;

/// ad description.
@property (nonatomic, copy) NSString *AdDescription;

/// ad source.
@property (nonatomic, copy) NSString *source;

/// text displayed on the creative button.
@property (nonatomic, copy) NSString *buttonText;

/// display format of the in-feed ad, other ads ignores it.
@property (nonatomic, assign) BUFeedADMode imageMode;

/// Star rating, range from 1 to 5.
@property (nonatomic, assign) NSInteger score;

/// Number of comments.
@property (nonatomic, assign) NSInteger commentNum;

/// ad installation package size, unit byte.
@property (nonatomic, assign) NSInteger appSize;

/// video duration
@property (nonatomic, assign) NSInteger videoDuration;

/// media configuration parameters.
@property (nonatomic, copy) NSDictionary *mediaExt;

- (instancetype)initWithDictionary:(NSDictionary *)dict error:(NSError * __autoreleasing *)error;

@end

@interface BUDislikeWords : NSObject <NSCoding>
@property (nonatomic, copy, readonly) NSString *dislikeID;
@property (nonatomic, copy, readonly) NSString *name;
@property (nonatomic, assign, readonly) BOOL isSelected;
@property (nonatomic, copy,readonly) NSArray<BUDislikeWords *> *options;

- (instancetype)initWithDictionary:(NSDictionary *)dict error:(NSError **)error;
@end


@protocol BUNativeAdDelegate;




/**
 Abstract ad slot containing ad data loading, response callbacks.
 BUNativeAd currently supports native ads.
 Native ads include in-feed ad (multiple ads, image + video), general native ad (single ad, image + video), native banner ad, and native interstitial ad.
 Support interstitial ad, banner ad, splash ad, rewarded video ad, full-screen video ad.
 */
@interface BUNativeAd : NSObject

/**
 Ad slot description.
 */
@property (nonatomic, strong, readwrite, nullable) BUAdSlot *adslot;

/**
 Ad slot material.
 */
@property (nonatomic, strong, readonly, nullable) BUMaterialMeta *data;

/**
 The delegate for receiving state change messages.
 The delegate is not limited to viewcontroller.
 The delegate can be set to any object which conforming to <BUNativeAdDelegate>.
 */
@property (nonatomic, weak, readwrite, nullable) id<BUNativeAdDelegate> delegate;

/**
 required.
 Root view controller for handling ad actions.
 Action method includes is 'presentViewController'.
 */
@property (nonatomic, weak, readwrite) UIViewController *rootViewController;

/**
 Initializes native ad with ad slot.
 @param slot : ad slot description.
               including slotID,adType,adPosition,etc.
 @return BUNativeAd
 */
- (instancetype)initWithSlot:(BUAdSlot *)slot;

/**
 Register clickable views in native ads view.
 Interaction types can be configured on Pangle Audience Network.
 Interaction types include view video ad details page, make a call, send email, download the app, open the webpage using a browser,open the webpage within the app, etc.
 @param containerView : required.
                        container view of the native ad.
 @param clickableViews : optional.
                        Array of views that are clickable.
 */
- (void)registerContainer:(__kindof UIView *)containerView
       withClickableViews:(NSArray<__kindof UIView *> *_Nullable)clickableViews;

/**
 Unregister ad view from the native ad.
 */
- (void)unregisterView;

/**
 Actively request nativeAd datas.
 */
- (void)loadAdData;

@end


@protocol BUVideoAdViewDelegate;


@interface BUVideoAdView : UIView

@property (nonatomic, weak, nullable) id<BUVideoAdViewDelegate> delegate;
/**
required. Root view controller for handling ad actions.
 **/
@property (nonatomic, weak, readwrite) UIViewController *rootViewController;

/**
 Whether to allow pausing the video by clicking, default NO. Only for draw video(vertical video ads).
 **/
@property (nonatomic, assign) BOOL drawVideoClickEnable;

/**
 material information.
 */
@property (nonatomic, strong, readwrite, nullable) BUMaterialMeta *materialMeta;

/**
 Set your Video autoPlayMode when you support CustomMode
 if support CustomMode , default autoplay Video
 **/
@property (nonatomic, assign) BOOL supportAutoPlay;


- (instancetype)initWithMaterial:(BUMaterialMeta *)materialMeta;

/**
 Resume to the corresponding time.
 */
- (void)playerSeekToTime:(CGFloat)time;

/**
 Support configuration for pause button.
 @param playImg : the image of the button
 @param playSize : the size of the button. Set as cgsizezero to use default icon size.
 */
- (void)playerPlayIncon:(UIImage *)playImg playInconSize:(CGSize)playSize;

@end

@protocol BUVideoAdViewDelegate <NSObject>

@optional

/**
 This method is called when videoadview failed to play.
 @param error : the reason of error
 */
- (void)videoAdView:(BUVideoAdView *)videoAdView didLoadFailWithError:(NSError *_Nullable)error;

/**
 This method is called when videoadview playback status changed.
 @param playerState : player state after changed
 */
- (void)videoAdView:(BUVideoAdView *)videoAdView stateDidChanged:(BUPlayerPlayState)playerState;

/**
 This method is called when videoadview end of play.
 */
- (void)playerDidPlayFinish:(BUVideoAdView *)videoAdView;

/**
 This method is called when videoadview is clicked.
 */
- (void)videoAdViewDidClick:(BUVideoAdView *)videoAdView;

/**
 This method is called when videoadview's finish view is clicked.
 */
- (void)videoAdViewFinishViewDidClick:(BUVideoAdView *)videoAdView;

/**
 This method is called when another controller has been closed.
 @param interactionType : open appstore in app or open the webpage or view video ad details page.
 */
- (void)videoAdViewDidCloseOtherController:(BUVideoAdView *)videoAdView interactionType:(BUInteractionType)interactionType;

@end

@protocol BUNativeAdDelegate <NSObject>

@optional

/**
 This method is called when native ad material loaded successfully.
 */
- (void)nativeAdDidLoad:(BUNativeAd *)nativeAd;

/**
 This method is called when native ad materia failed to load.
 @param error : the reason of error
 */
- (void)nativeAd:(BUNativeAd *)nativeAd didFailWithError:(NSError *_Nullable)error;

/**
 This method is called when native ad slot has been shown.
 */
- (void)nativeAdDidBecomeVisible:(BUNativeAd *)nativeAd;

/**
 This method is called when another controller has been closed.
 @param interactionType : open appstore in app or open the webpage or view video ad details page.
 */
- (void)nativeAdDidCloseOtherController:(BUNativeAd *)nativeAd interactionType:(BUInteractionType)interactionType;

/**
 This method is called when native ad is clicked.
 */
- (void)nativeAdDidClick:(BUNativeAd *)nativeAd withView:(UIView *_Nullable)view;

/**
 This method is called when the user clicked dislike reasons.
 Only used for dislikeButton in BUNativeAdRelatedView.h
 @param filterWords : reasons for dislike
 */
- (void)nativeAd:(BUNativeAd *_Nullable)nativeAd dislikeWithReason:(NSArray<BUDislikeWords *> *_Nullable)filterWords;
@end


@interface BUNativeAdRelatedView : NSObject

/**
 Need to actively add to the view in order to deal with the feedback and improve the accuracy of ad.
 */
@property (nonatomic, strong, readonly, nullable) UIButton *dislikeButton;

/**
 Promotion label.Need to actively add to the view.
 */
@property (nonatomic, strong, readonly, nullable) UILabel *adLabel;

/**
 Ad logo.Need to actively add to the view.
 */
@property (nonatomic, strong, readonly, nullable) UIImageView *logoImageView;
/**
 Ad logo + Promotion label.Need to actively add to the view.
 */
@property (nonatomic, strong, readonly, nullable) UIImageView *logoADImageView;

/**
 Video ad view. Need to actively add to the view.
 */
@property (nonatomic, strong, readonly, nullable) BUVideoAdView *videoAdView;

/**
 Refresh the data every time you get new datas in order to show ad perfectly.
 */
- (void)refreshData:(BUNativeAd *)nativeAd;

@end

NS_ASSUME_NONNULL_END

#endif /* OMPangleNativeClass_h */
