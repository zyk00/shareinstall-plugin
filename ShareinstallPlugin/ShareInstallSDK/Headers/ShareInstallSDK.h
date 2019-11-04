//
//  ShareInstallSDK.h
//  SHSmartInstallKit
//
//  Created by smyjw on 2017/11/24.
//  Copyright © 2017年 smyjw. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef void (^getInstallCallback)(NSString *jsonStr);

@protocol ShareInstallDelegate <NSObject>

/**
 * 安装时获取自定义h5页面参数（使用控制中心提供的渠道统计时，渠道编号也会返回给开发者）
 * @ param params 动态参数
 * @ return void
 */
- (void)getInstallParamsFromSmartInstall:(id) params withError: (NSError *) error;


/**
 * 唤醒时获取h5页面参数（如果是渠道链接，渠道编号会一起返回）
 * @ param type 链接类型（区分渠道链接和自定义分享h5链接）
 * @ param params 动态参数
 * @ return void
 */
- (void)getWakeUpParamsFromSmartInstall: (id) params withError: (NSError *) error;

@end

@interface ShareInstallSDK : NSObject

@property(nonatomic,copy)getInstallCallback installBlock;

+(instancetype)getInitializeInstance;
/**
 该方法可重复获取参数，如只需在首次获取参数，请自行判断，可设置一个标示位，不再重复调用
 getInstallCallBackBlock方法。
 **/
-(void)getInstallCallBackBlock:(getInstallCallback)callback;

+(void)setAppKey:(NSString *)appKey withDelegate:(id)delegate WithOptions:(NSDictionary *)launchOptions;

+(void)setAppKey:(NSString *)appKey withDelegate:(id)delegate WithOptions:(NSDictionary *)launchOptions clearCustomParams:(BOOL)customParams;

/**
 * 初始化ShareInstall SDK
 * @ param appKey 控制中心创建应用获取appKey
 * @ param launchOptions 该参数存储程序启动的原因
 * @ param delegate 委托方法(getInstallParamsFromSmartInstall和 getWakeUpParamsFromSmartInstall)所在的类的对象
 * @ param launchOptions App 启动参数
 * @ customParams BOOl值 如只需在首次安装启动获取参数，可将customParams设置为YES，不需要则设置为NO
 * @ param apptypeid App软件唯一识别符(接入方配置，若没有可填appkey)
 * @ param appcqid 接入方自己配置的渠道号 如：appstore,若没有可传空字符串
 * @ param appqid 接入方配置的渠道号后面+日期
 * @ return void
 */

+(void)setAppKey:(NSString *)appKey withDelegate:(id)delegate  clearCustomParams:(BOOL)customParams apptypeid:(NSString *)apptypeid appcqid:(NSString *)appcqid appqid:(NSString *)appqid WithOptions:(NSDictionary *)launchOptions;

/**
 * 初始化ShareInstall SDK(appkey会从Info.plist文件中获取,在Info.plist文件中配置appKey键值对，如下：<key>com.shareinstall.APP_KEY</key>
 <string>shareinstall 分配给应用的 appkey</string>)
 * @ param delegate 委托方法(getInstallParamsFromSmartInstall和 getWakeUpParamsFromSmartInstall)所在的类的对象
 * @ param launchOptions App 启动参数
 */
+(void)initWithDelegate:(id)delegate withOptions:(NSDictionary *)launchOptions;

/**
 * 处理 URL schemes
 * @ param URL 系统回调传回的URL
 * @ return bool URL是否被ShareInstall识别
 */
+(BOOL)handLinkURL:(NSURL *)URL;

/**
 * 通过 Universal Link 启动应用时会调用 application:(UIApplication *)application continueUserActivity:(NSUserActivity *)userActivity restorationHandler:(void(^)(NSArray * __nullable
 restorableObjects))restorationHandler ,在此方法中调用  [ShareInstallSDK continueUserActivity:userActivity]
 * @ param userActivity 存储了页面信息，包括url
 * @ return bool URL是否被ShareInstall识别
 */
+(BOOL)continueUserActivity:(NSUserActivity*)userActivity;

/**
 * 使用Shareinstall 控制中心提供的渠道统计时，在App用户注册完成后调用，可以统计渠道注册量。
 * @ param
 * @ return void
 */
+(void)reportRegister;

///**
// * v1.2.3 SDK新增打点统计方法
// * @ param actid  自定义事件id
// * @ param subactid 自定义事件下的参数
// * @ param materialid 自定义事件参数下的参数值
// * @ param type 展示传"show"、点击传"click"、关闭传"close"
// **/
//+(void)dotsStatisticalWithActid:(NSString *)actid subactid:(NSString *)subactid materialid:(NSString *)materialid type:(NSString *)type;

/**
 * v1.2.3 SDK新增打点统计方法
 * @ param actentryid  活动入口id，保证唯一性
 * @ param entrytype 站内传活动入口id对应的类型：分享收徒传share,活动内点击传actclick,进入活动传entry；站外不传
 * @ param visitplatform 站内不传 ；站外访问分享页的平台（如：weixin,weibo等）
 * @ param actid  自定义事件id
 * @ param subactid 自定义事件下的参数
 * @ param materialid 自定义事件参数下的参数值
 * @ param type 展示传"show"、点击传"click"、关闭传"close"
 **/
+(void)dotStatisticalWithActentryid:(NSString *)actentryid entrytype:(NSString *)entrytype visitplatform:(NSString *)visitplatform actid:(NSString *)actid subactid:(NSString *)subactid materialid:(NSString *)materialid type:(NSString *)type;

@end

