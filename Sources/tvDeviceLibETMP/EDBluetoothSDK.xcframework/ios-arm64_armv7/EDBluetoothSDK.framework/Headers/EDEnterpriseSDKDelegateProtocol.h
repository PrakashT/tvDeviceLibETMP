//
//  EDEnterpriseSDKDelegateProtocol.h
//  EkoLiveStreamAPI
//
//  Created by John Zorko on 6/14/19.
//  Copyright © 2019 Eko. All rights reserved.
//

#ifndef EDEnterpriseSDKDelegateProtocol_h
#define EDEnterpriseSDKDelegateProtocol_h

@protocol EDEnterpriseSDKDelegate <NSObject>
- (void)startedLiveStream:(NSString *)streamID;
- (void)endedLiveStream:(NSString *)streamID;
- (void)failedLiveStream:(NSString *)streamID withError:(NSError *)error;
@end

#endif /* EDEnterpriseSDKDelegateProtocol_h */
