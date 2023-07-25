/*
 * Copyright Cypress Semiconductor Corporation, 2014-2018 All rights reserved.
 *
 * This software, associated documentation and materials ("Software") is
 * owned by Cypress Semiconductor Corporation ("Cypress") and is
 * protected by and subject to worldwide patent protection (UnitedStates and foreign), United States copyright laws and international
 * treaty provisions. Therefore, unless otherwise specified in a separate license agreement between you and Cypress, this Software
 * must be treated like any other copyrighted material. Reproduction,
 * modification, translation, compilation, or representation of this
 * Software in any other form (e.g., paper, magnetic, optical, silicon)
 * is prohibited without Cypress's express written permission.
 *
 * Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY
 * KIND, EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO,
 * NONINFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE. Cypress reserves the right to make changes
 * to the Software without notice. Cypress does not assume any liability
 * arising out of the application or use of Software or any product or
 * circuit described in the Software. Cypress does not authorize its
 * products for use as critical components in any products where a
 * malfunction or failure may reasonably be expected to result in
 * significant injury or death ("High Risk Product"). By including
 * Cypress's product in a High Risk Product, the manufacturer of such
 * system or application assumes all risk of such use and in doing so
 * indemnifies Cypress against all liability.
 *
 * Use of this Software may be limited by and subject to the applicable
 * Cypress software license agreement.
 *
 *
 */

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import "Constants.h"
//#import "LoggerHandler.h"
//#import "ResourceHandler.h"
#import "Utilities.h"


/*!
 *  @property CBDiscoveryDelegate
 *
 *  @discussion The delegate object that will receive events which use for UI updation.
 *
 */
@protocol cbDiscoveryManagerDelegate <NSObject>

/*!
 *  @method discoveryDidRefresh
 *
 *  @discussion This method invoke after a new peripheral found.
 */
- (void) discoveryDidRefresh;

/*!
 *  @method bluetoothStateUpdatedToState:
 *
 *  @discussion	 This will be invoked when the Bluetooth state changes.
 */
- (void) bluetoothStateUpdatedToState:(BOOL)state;

@end

@protocol cbCharacteristicManagerDelegate <NSObject>

@optional
/*!
 *  @method peripheral:didDiscoverCharacteristicsForService:error:
 *
 *  @param peripheral	The peripheral providing this information.
 *  @param service		The <code>CBService</code> object containing the characteristic(s).
 *	@param error		If an error occurred, the cause of the failure.
 *
 *  @discussion			This method returns the result of a @link discoverCharacteristics:forService: @/link call. If the characteristic(s) were read successfully,
 *						they can be retrieved via <i>service</i>'s <code>characteristics</code> property.
 */
- (void)peripheral:(CBPeripheral *)peripheral didDiscoverCharacteristicsForService:(CBService *)service error:(NSError *)error;

/*!
 *  @method peripheral:didUpdateValueForCharacteristic:error:
 *
 *  @param peripheral		The peripheral providing this information.
 *  @param characteristic	A <code>CBCharacteristic</code> object.
 *	@param error			If an error occurred, the cause of the failure.
 *
 *  @discussion				This method is invoked after a @link readValueForCharacteristic: @/link call, or upon receipt of a notification/indication.
 */
- (void)peripheral:(CBPeripheral *)peripheral didUpdateValueForCharacteristic:(CBCharacteristic *)characteristic error:(NSError *)error;

/*!
 *  @method peripheral:didWriteValueForCharacteristic:error:
 *
 *  @param peripheral		The peripheral providing this information.
 *  @param characteristic	A <code>CBCharacteristic</code> object.
 *	@param error			If an error occurred, the cause of the failure.
 *
 *  @discussion				This method returns the result of a {@link writeValue:forCharacteristic:type:} call, when the <code>CBCharacteristicWriteWithResponse</code> type is used.
 */
- (void)peripheral:(CBPeripheral *)peripheral didWriteValueForCharacteristic:(CBCharacteristic *)characteristic error:(NSError *)error;

/*!
 *  @method peripheral:didUpdateNotificationStateForCharacteristic:error:
 *
 *  @param peripheral		The peripheral providing this information.
 *  @param characteristic	A <code>CBCharacteristic</code> object.
 *	@param error			If an error occurred, the cause of the failure.
 *
 *  @discussion				This method returns the result of a @link setNotifyValue:forCharacteristic: @/link call.
 */
- (void)peripheral:(CBPeripheral *)peripheral didUpdateNotificationStateForCharacteristic:(CBCharacteristic *)characteristic error:(NSError *)error;

/*!
 *  @method peripheral:didDiscoverDescriptorsForCharacteristic:error:
 *
 *  @param peripheral		The peripheral providing this information.
 *  @param characteristic	A <code>CBCharacteristic</code> object.
 *	@param error			If an error occurred, the cause of the failure.
 *
 *  @discussion				This method returns the result of a @link discoverDescriptorsForCharacteristic: @/link call. If the descriptors were read successfully,
 *							they can be retrieved via <i>characteristic</i>'s <code>descriptors</code> property.
 */
- (void)peripheral:(CBPeripheral *)peripheral didDiscoverDescriptorsForCharacteristic:(CBCharacteristic *)characteristic error:(NSError *)error;

/*!
 *  @method peripheral:didUpdateValueForDescriptor:error:
 *
 *  @param peripheral		The peripheral providing this information.
 *  @param descriptor		A <code>CBDescriptor</code> object.
 *	@param error			If an error occurred, the cause of the failure.
 *
 *  @discussion				This method returns the result of a @link readValueForDescriptor: @/link call.
 */
-(void)peripheral:(CBPeripheral *)peripheral didUpdateValueForDescriptor:(CBDescriptor *)descriptor error:(NSError *)error;

@end


//@interface CyCBManager : NSObject
//{
//
//}
//
//@property (strong,nonatomic)  id<cbCharacteristicManagerDelegate> cbCharacteristicDelegate;
//@property (nonatomic, assign) id<cbDiscoveryManagerDelegate>           cbDiscoveryDelegate;
//
///*!
// *  @property myPeripheral
// *
// *  @discussion Current Connected Peripheral.
// *
// */
//@property (nonatomic, retain)CBPeripheral		*myPeripheral;
//
///*!
// *  @property myService
// *
// *  @discussion  The selected Service.
// *
// */
//@property (nonatomic, retain)CBService			*myService;
//
///*!
// *  @property myCharacteristic
// *
// *  @discussion  The selected Characteristic.
// *
// */
//@property (nonatomic, retain)CBCharacteristic   *myCharacteristic;
//
///*!
// *  @property foundPeripherals
// *
// *  @discussion  All discovered peripherals while scanning.
// *
// */
//@property (retain, nonatomic) NSMutableArray    *foundPeripherals;
//
///*!
// *  @property foundServices
// *
// *  @discussion All available services of connected peripheral..
// *
// */
//@property (retain, nonatomic) NSMutableArray    *foundServices;
//
///*!
// *  @property serviceUUIDDict
// *
// *  @discussion  Dictionary contains all listed Known services from pList (ServiceUUIDPlist).
// *
// */
//@property (retain, nonatomic) NSMutableDictionary      *serviceUUIDDict;
//
///*!
// *  @property characteristicProperties
// *
// *  @discussion  Properties of characteristic .
// *
// */
//@property (retain,nonatomic) NSMutableArray *characteristicProperties;
//
///*!
// *  @property characteristicDescriptors
// *
// *  @discussion  Descriptors of characteristic .
// *
// */
//@property (retain,nonatomic) NSArray  *characteristicDescriptors;
//
///*!
// *  @property bootLoaderFilesArray
// *
// *  @discussion  Firmware files selected for device upgrade.
// *
// */
//@property (retain, nonatomic) NSArray *bootloaderFileArray;
//
//@property (retain, nonatomic) NSData *bootloaderSecurityKey;
//@property (nonatomic) ActiveApp bootloaderActiveApp;
//
//+ (id)sharedManager;
//
///*								Actions										*/
///****************************************************************************/
///*!
// *  @method startScanning
// *
// *  @discussion  To scans for peripherals that are advertising services.
// *
// */
//- (void) startScanning;
//
///*!
// *  @method stopScanning
// *
// *  @discussion  To stop scanning for peripherals.
// *
// */
//- (void) stopScanning;
//
///*!
// *  @method refreshPeripherals
// *
// *  @discussion	  Clear all listed peripherals and services.Also check the status of Bluetooth and alert the user if it is turned Off,
// *
// */
//- (void) refreshPeripherals;
//
///*!
// *  @method connectPeripheral:completionHandler
// *
// *  @discussion	 Establishes a local connection to a peripheral.
// *
// */
//- (void) connectPeripheral:(CBPeripheral*)peripheral completionHandler:(void (^)(BOOL success, NSError *error))completionHandler;
//
///*!
// *  @method disconnectPeripheral:
// *
// *  @discussion	 Cancels an active or pending local connection to a peripheral.
// *
// */
//- (void) disconnectPeripheral:(CBPeripheral*)peripheral;
//
//@end
