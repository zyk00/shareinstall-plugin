//
//  ShareInstallApiManager.m
//  HBuilder
//
//  Created by tivon on 2019/7/26.
//  Copyright © 2019 smyjw. All rights reserved.
//

#import "ShareInstallApiManager.h"
#import "PDRCoreAppFrame.h"
#import "H5WEEngineExport.h"
#import "PDRToolSystemEx.h"
// 扩展插件中需要引入需要的系统库
#import <LocalAuthentication/LocalAuthentication.h>

@interface ShareInstallApiManager ()

@property (nonatomic, copy)NSString *wakeupId;
@property (nonatomic, copy)NSString *wakeUpJson;
@property (nonatomic, assign)BOOL isRegister;

@end

@implementation ShareInstallApiManager

/*
 * WebApp启动时触发
 * 需要在PandoraApi.bundle/feature.plist/注册插件里添加autostart值为true，global项的值设置为true
 */
- (void) onAppStarted:(NSDictionary*)options{
    NSLog(@"5+ WebApp启动时触发");
//    [ShareInstallSDK setAppKey:@"AHBKFRHFH26BE6" withDelegate:self WithOptions:options];
    [ShareInstallSDK initWithDelegate:self withOptions:options];
}

-(void)registerWakeUpHandler:(PGMethod*)command{
    
    NSString* cbId = command.arguments.firstObject;
    self.wakeupId = cbId;
    
    self.isRegister = YES;
    if (self.wakeUpJson.length != 0) {
        [self toCallback:self.wakeupId withReslut:self.wakeUpJson];
        self.wakeUpJson = nil;
    }
}
-(void)getInstall:(PGMethod*)command{
    NSString* cbId = command.arguments.firstObject;
    [[ShareInstallSDK getInitializeInstance] getInstallCallBackBlock:^(NSString *jsonStr) {
        PDRPluginResult *result = [PDRPluginResult resultWithStatus:PDRCommandStatusOK messageAsString:jsonStr];
        [self toCallback:cbId withReslut:[result toJSONString]];
    }];
}
-(void)reportRegister:(PGMethod*)command{
    
    [ShareInstallSDK reportRegister];
    
}
-(void)clearAppGetInfoListener:(PGMethod*)command{

}
- (void)getWakeUpParamsFromSmartInstall: (id) params withError: (NSError *) error{
    
    NSString *wakeUpDicResult = @"";
    if ([params isKindOfClass:[NSString class]]) {
        wakeUpDicResult = params;
    }
    if ([params isKindOfClass:[NSDictionary class]]) {
        wakeUpDicResult = [self convertToJsonData:params];
    }
    
    PDRPluginResult *result = [PDRPluginResult resultWithStatus:PDRCommandStatusOK messageAsString:wakeUpDicResult];
    
    if (self.isRegister) {
        [self toCallback:self.wakeupId withReslut:[result toJSONString]];
        self.wakeUpJson = nil;
    }
    else {
        self.wakeUpJson = [result toJSONString];
    }
}
-(void)dotStatistical:(PGMethod*)command{
    
}

+(void)universalLinkHandler:(NSURL *)url{
    
    if (url) {
        if ([url isKindOfClass:[NSURL class]]) {
            NSUserActivity *activity = [[NSUserActivity alloc]initWithActivityType:NSUserActivityTypeBrowsingWeb];
            activity.webpageURL = url;
            [ShareInstallSDK continueUserActivity:activity];
        }
    }
    
}
+(void)schemeUrlHandler:(NSURL *)url{
    
    if (url) {
        if ([url isKindOfClass:[NSURL class]]) {
            [ShareInstallSDK handLinkURL:url];
        }
    }
    
}

-(NSString *)convertToJsonData:(NSDictionary *)dict{
    
    NSError *error;
    
    NSData *jsonData = [NSJSONSerialization dataWithJSONObject:dict options:NSJSONWritingPrettyPrinted error:&error];
    
    NSString *jsonString;
    
    {
        
        jsonString = [[NSString alloc]initWithData:jsonData encoding:NSUTF8StringEncoding];
        
    }
    
    NSMutableString *mutStr = [NSMutableString stringWithString:jsonString];
    
    NSRange range = {0,jsonString.length};
    
    //去掉字符串中的空格
    
    [mutStr replaceOccurrencesOfString:@" " withString:@"" options:NSLiteralSearch range:range];
    
    NSRange range2 = {0,mutStr.length};
    
    //去掉字符串中的换行符
    
    [mutStr replaceOccurrencesOfString:@"\n" withString:@"" options:NSLiteralSearch range:range2];
    
    return mutStr;
    
}

@end
