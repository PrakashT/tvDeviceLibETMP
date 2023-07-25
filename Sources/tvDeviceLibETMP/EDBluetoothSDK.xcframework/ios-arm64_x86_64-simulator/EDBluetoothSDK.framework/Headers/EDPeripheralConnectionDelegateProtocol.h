//
//  EDPeripheralConnectionDelegateProtocol.h
//  EDBluetooth
//
//  Created by Tyler Crouch on 2/6/19.
//  Copyright © 2019 Eko Devices. All rights reserved.
//

#ifndef EDPeripheralConnectionDelegateProtocol_h
#define EDPeripheralConnectionDelegateProtocol_h

/**
 This protocol alerts users when Eko peripherals are found during Bluetooth scans, connect/disconnect to this device, experience a frimware crash, and have changes in Bluetooth signal connection strength.
 Additionally the protocol can be used to learn when a user turns Bluetooth on / off on this device.
 */

@protocol EDPeripheralConnectionDelegate <NSObject>
@optional

/**
 Notify delegate when Bluetooth powers on or off.
 */
- (void) bluetoothEnabled: (BOOL)enabled;

/**
 Output Eko peripherals discovered by Bluetooth scan.
 */
- (void) discoveredEkoPeripheral: (CBPeripheral *)peripheral RSSI: (NSNumber *)RSSI;

/**
 Output Eko peripheral that just connected with this device.
 */
- (void) connectedToEkoPeripheral: (CBPeripheral *)peripheral;

/**
 Output Eko peripheral that just failed to connect with this device.
 */
- (void) failedToConnectWithEkoPeripheral: (CBPeripheral *)peripheral error: (NSError *)error;

/**
 Output bonding error
 */
- (void) bondingFailedWithPeripheral: (CBPeripheral*) peripheral;

/**
 Output Eko peripheral that just disconnected with this device.
 */
- (void) disconnectedFromEkoPeripheral: (CBPeripheral *)peripheral error: (NSError *)error;

/**
 This method is triggered whenever the Bluetooth communication with a connected peripheral becomes interrupted and subsequently data is lost.
 In progress recordings will be canceled and captured data will be outputted immidiately after this is called to avoid creating recordings with missing data.
 */
- (void) ekoPeripheralBluetoothPacketLost;

/**
 Advertises signal quality state as calculated by internal SDK metrics, only called at this time when signal quality changes from good to poor or vice versa.
 */
- (void) connectedPeripheralSignalQualityChanged: (EDSignalQualityType)signalQuality;

/**
 If no Bluetooth packets are recieved from a connected peripheral for an extended period of time then the firmware on the peripheral may have crashed and this action block will be executed.
 After calling this method, the library will disconnect from the peripheral as the peripheral will no longer respond to commands or output data.
 */
- (void) ekoPeripheralFirmwareCrashed;

@end

#endif /* EDPeripheralConnectionDelegateProtocol_h */
