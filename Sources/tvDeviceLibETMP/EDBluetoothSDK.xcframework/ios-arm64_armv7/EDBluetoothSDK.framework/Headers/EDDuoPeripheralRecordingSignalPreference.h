//
//  EDDuoPeripheralRecordingSignalPreference.h
//  Eko Devices
//
//  Created by Tyler Crouch on 3/19/18.
//

#ifndef DDuoPeripheralRecordingSignalPreference_h
#define DDuoPeripheralRecordingSignalPreference_h

typedef NS_ENUM (NSInteger,  EDDuoPeripheralRecordingSignalPreference){
    
    recordAudioOnly = 0,
    recordECGOnly = 1,
    recordAudioAndECG = 2,
    
};

#endif /* EDDuoPeripheralRecordingSignalPreference_h */
