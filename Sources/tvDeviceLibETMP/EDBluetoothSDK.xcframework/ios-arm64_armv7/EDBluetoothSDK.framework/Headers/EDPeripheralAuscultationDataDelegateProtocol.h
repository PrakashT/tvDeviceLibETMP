//
//  EDPeripheralAuscultationDataDelegateProtocol.h
//  Eko Devices
//
//  Created by Tyler Crouch on 4/10/19.
//  Copyright © 2019 Eko Devices. All rights reserved.
//

#ifndef EDPeripheralAuscultationDataDelegateProtocol_h
#define EDPeripheralAuscultationDataDelegateProtocol_h

#import "EDAudioFilterChannel.h"
//#import "../../../Data Sampling/EDAudioFilterChannel.h"

@protocol EDPeripheralAuscultationDataDelegate <NSObject>
@optional

/**
 The connected Eko peripheral has reset its decoders and begun a new stream of audio & ECG data values.
 Due to the nature of ADPCM decoding, it will take a few seconds for outputted audio and ECG values to lock on to the true audio / ECG values.
 Outputted values will start near zero and then iteratively get closer to the real audio / ECG values while the decoder calibrates to the new stream.
 Any filters that use previous values to filter new values should be reset when this method is called.
 */
- (void) ekoPeripheralResetMedicalDataStream;

/**
 Medical sensor data parsing buffers are overflowing. The buffers are at capacity and will overwrite data that has yet to be outputted / recorded in order to store newly recieved data.
 Consider stopping recording if this happens and / or calling resetMedicalSensorDataBuffers to clear the buffers. This should not happen in normal use.
 */
- (void) ekoPeripheralMedicalDataBufferOverflow;

/**
 Output the most recent audio parsed from paired Eko peripheral.
 */
- (void) ekoPeripheralOutputtedAudioValue: (short) audioValue audioFilterChannel: (EDAudioFilterChannel) audioFilterChannel audioResolution: (short) audioResolution;

- (void) ekoPeripheralOutputtedECGValue: (short) ECGValue __attribute__((deprecated("use ekoPeripheralOutputtedECGValue:filterChannel: instead.")));
/**
 Output the most recent ECG value parsed from paired Eko peripheral.
 Sample rate of this output is equal to ECGSampleRate / self.outputtedECGResolution.
 */
- (void) ekoPeripheralOutputtedECGValue: (short) ECGValue filterChannel: (EDAudioFilterChannel) filterChannel;

/**
 Output the most recent audio and ECG values parsed from paired Eko peripheral.
 This method is called when the ECG and audio output sample rates sync up and two samples taken at the same time become available.
 */
- (void) ekoPeripheralOutputtedECGValue: (short) ECGValue audioValue: (short) audioValue audioFilterChannel: (EDAudioFilterChannel) audioFilterChannel audioResolution: (short) audioResolution;

@end

#endif /* EDPeripheralAuscultationDataDelegateProtocol_h */
