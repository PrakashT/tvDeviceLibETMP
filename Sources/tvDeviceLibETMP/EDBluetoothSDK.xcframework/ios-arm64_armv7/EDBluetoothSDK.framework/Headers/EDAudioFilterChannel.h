//
//  EDAudioFilterChannel.h
//  Eko Devices
//
//  Created by Tyler Crouch on 4/9/19.
//  Copyright © 2019 Eko Devices. All rights reserved.
//

#ifndef EDAudioFilterChannel_h
#define EDAudioFilterChannel_h

typedef NS_ENUM (NSInteger,  EDAudioFilterChannel){
    
    EDAudioFilterChannelUnfilteredData,
    EDAudioFilterChannelFilteredData,
    EDAudioFilterChannelUpsampled8kHzAudioPlayerData,
    
};

#endif /* EDAudioFilterChannel_h */
