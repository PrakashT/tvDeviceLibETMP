//
//  EDWebSocket.h
//  EkoLiveStreamAPI
//
//  Created by John Zorko on 4/25/19.
//  Copyright © 2019 Eko. All rights reserved.
//

//#import "SocketRocket/SRWebSocket.h"
#import <SocketRocket/SocketRocket.h>

NS_ASSUME_NONNULL_BEGIN

@interface EDWebSocket : SRWebSocket

@property (nonatomic, strong) NSString *streamID;

- (instancetype)initWithURLRequest:(NSURLRequest *)request streamID:(NSString *)streamID;

@end

NS_ASSUME_NONNULL_END
