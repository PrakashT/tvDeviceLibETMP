//
//  EDPeripheralDeviceInfoDelegateProtocol.h
//  EDBluetooth
//
//  Created by Tyler Crouch on 3/18/19.
//  Copyright © 2019 Eko Devices. All rights reserved.
//

#ifndef EDPeripheralDeviceInfoDelegateProtocol_h
#define EDPeripheralDeviceInfoDelegateProtocol_h

/**
 Use this protocol to get notified when a paired Eko peripheral updates volume level, battery level, or filter modes.
 Also outputs the approximate audio playback completion percent of audio streamed to paired Eko peripheral.
 */

@protocol EDPeripheralDeviceInfoDelegate <NSObject>
@optional
/**
 Output the approximate audio playback completion percent of audio streamed to paired Eko peripheral. Because of BLE data transmission times this value is not going
 to be perfectly in sync with the real playback completion percent of paired peripheral.
 */
- (void) ekoPeripheralAudioPlaybackCompletionPercent: (float)completionPercent;

/**
 Output updated battery level of paired Eko peripheral.
 */
- (void) ekoPeripheralUpdatedBatteryLevel: (int)batteryLevel;

/**
 Output updated volume level of paired Eko peripheral.
 */
- (void) ekoPeripheralUpdatedVolumeLevel: (int)volumeLevel;

/**
 Output updated filter mode of paired Eko Duo peripheral.
 */
- (void) ekoPeripheralUpdatedFilterMode: (EDDuoPeripheralFilterMode)filterMode;

/**
 Output peripheral metadata
 */
- (void) ekoPeripheralDidUpdatePeripheralMetadata: (EDPeripheralMetaData*) metadata;

/**
 Output ANC state
 */
- (void) ekoPeripheralDidUpdateANCState: (BOOL) isANCOn;

/**
 Output updated filter mode of paired Eko Core2 peripheral.
 */
- (void) ekoPeripheralUpdatedCore2FilterMode: (EDCore2PeripheralFilterMode)filterMode;


@end

#endif /* EDPeripheralDeviceInfoDelegateProtocol_h */
