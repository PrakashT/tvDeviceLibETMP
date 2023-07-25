//
//  EDBluetoothPeripheralInfo.h
//  Eko Devices
//
//  Created by Tyler Crouch on 3/12/18.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>

//-------------------------------------------------------------------------------------------------
# pragma mark - Constants
//-------------------------------------------------------------------------------------------------

/**
 Audio sample rate of Eko peripherals.
 */
extern UInt32 const EDAudioSampleRate;

/**
 ECG sample rate of Eko peripherals.
 */
extern UInt32 const EDECGSampleRate;

/**
 This value approximately cooresponds to the amplitude of 1 mV.
 Range of value is the same as a short [-32768, 32767]. Format is a float to increase significant figures.
 */
extern const float EDOneMillivoltECGSignalAmplitude;

/**
 Amount of time in seconds that must pass without a single packet dropped for the connection
 to the paired peripheral to be considered a "strong signal".
 */
extern const float EDStrongSignalDuration;

//-------------------------------------------------------------------------------------------------
# pragma mark - Enumerators
//-------------------------------------------------------------------------------------------------

/**
 Types of Eko peripherals.
 */
typedef NS_ENUM (int,  EDPeripheralType){
    EDUnknownPeripheral = -1,
    EDEkoCorePeripheral = 1,
    EDEkoDuoPeripheral  = 2,
    EDEkoCore2DFU = 3,
    EDEkoCore2Data = 4
};

/**
 Levels of signal quality
 */
typedef NS_ENUM (int, EDSignalQualityType) {
    EDUnknownSignalQuality = -1,
    EDStrongSignalQuality  = 1,
    EDWeakSignalQuality    = 2,
};

/**
Eko Duo filter modes.
 */
typedef NS_ENUM (int, EDDuoPeripheralFilterMode) {
    EDDuoUnknownFilterMode = -1,
    EDDuoDiaphragmFilterMode,
    EDDuoBellFilterMode,
    EDDuoMidrangeFilterMode,
    EDDuoExtendedFilterMode
};

/**
Eko Core2 filter modes.
 */
typedef NS_ENUM (int, EDCore2PeripheralFilterMode) {
    EDCore2UnknownFilterMode = -1,
    EDCore2WideFilterMode,
    EDCore2CardiacFilterMode,
    EDCore2PulmonaryFilterMode
};

//-------------------------------------------------------------------------------------------------
# pragma mark - Utility Methods
//-------------------------------------------------------------------------------------------------

@interface EDBluetoothPeripheralInfo : NSObject

/**
 Get maximum volume level for inputted peripheral type.
 */
+ (int) getMaximumVolumeLevelForPeripheralType: (EDPeripheralType) peripheralType;

/**
 Get firmware version string for inputted peripheral.
 */
+ (NSString *) getFirmwareVersionStringForPeripheral: (CBPeripheral*) peripheral;

/**
 Get major firmware version for inputted peripheral.
 */
+ (int) getMajorFirmwareVersionForPeripheral: (CBPeripheral*) peripheral;

/**
 Get minor firmware version for inputted peripheral.
 */
+ (int) getMinorFirmwareVersionForPeripheral: (CBPeripheral*) peripheral;

// Note: moved to EDBLEManager
///**
// Get ED peripheral type for inputted peripheral.
// */
//+ (EDPeripheralType) getEDPeripheralTypeForPeripheral: (CBPeripheral*) peripheral;

/**
 Get name of inputted peripheral type.
 */
+ (NSString *) getNameOfPeripheralType: (EDPeripheralType) peripheralType;

/**
 Get name of Duo filter mode.
 */
+ (NSString *) getNameOfDuoFilterMode: (EDDuoPeripheralFilterMode) filterMode;

/**
 Get name of Core2 filter mode.
 */
+ (NSString *) getNameOfCore2FilterMode: (EDCore2PeripheralFilterMode) filterMode;

@end
