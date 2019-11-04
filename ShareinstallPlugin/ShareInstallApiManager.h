//
//  ShareInstallApiManager.h
//  HBuilder
//
//  Created by tivon on 2019/7/26.
//  Copyright © 2019 smyjw. All rights reserved.
//

#include "PGPlugin.h"
#include "PGMethod.h"
#import <Foundation/Foundation.h>
#import "ShareInstallSDK.h"

@interface ShareInstallApiManager : PGPlugin<ShareInstallDelegate>

+(void)universalLinkHandler:(NSURL *)url;
+(void)schemeUrlHandler:(NSURL *)url;

-(void)registerWakeUpHandler:(PGMethod*)command;
-(void)getInstall:(PGMethod*)command;
-(void)reportRegister:(PGMethod*)command;
-(void)clearAppGetInfoListener:(PGMethod*)command;
-(void)dotStatistical:(PGMethod*)command;

@end
