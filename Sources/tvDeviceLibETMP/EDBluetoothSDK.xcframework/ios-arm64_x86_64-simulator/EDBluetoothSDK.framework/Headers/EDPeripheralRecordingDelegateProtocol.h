//
//  EDPeripheralRecordingDelegateProtocol.h
//  Eko Devices
//
//  Created by Tyler Crouch on 4/10/19.
//  Copyright © 2019 Eko Devices. All rights reserved.
//

#ifndef EDPeripheralRecordingDelegateProtocol_h
#define EDPeripheralRecordingDelegateProtocol_h

#import "EDAudioFilterChannel.h"

/**
 This protocol manages the recording of data from paired Eko peripherals.
 */

@protocol EDPeripheralRecordingDelegate <NSObject>
@optional

- (void) ekoPeripheralAudioRecordingCompleted: (NSData *)audioRecordingData audioFilterChannel: (EDAudioFilterChannel) audioFilterChannel;

- (void) ekoPeripheralECGRecordingCompleted: (NSData *)ECGRecordingData;

/**
 Triggered when user presses main button on Eko Duo twice in a row or rocks the up (+) and down (-) volume buttons on the Eko Core in quick succession.
 */
- (void) ekoPeripheralRecordingCommandRecieved;

- (void) ekoPeripheralE6recordingCommandReceived: (BOOL) isRecording;

@end

#endif /* EDPeripheralRecordingDelegateProtocol_h */
