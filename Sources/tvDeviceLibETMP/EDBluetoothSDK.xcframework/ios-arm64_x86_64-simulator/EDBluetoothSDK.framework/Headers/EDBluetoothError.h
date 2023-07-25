//
//  EDBluetoothError.h
//  Eko Devices
//
//  Created by Tyler Crouch on 8/16/18.
//

#import <Foundation/Foundation.h>

/**
 Bluetooth error types.
 */
typedef NS_ENUM(NSInteger, EDBluetoothErrorType){
    /*
     Bluetooth is off or unavailable.
     **/
    EDUnavailableBluetoothError,
    
    /*
     Internal SDK error occured. SDK is not functioning correctly.
     This error should not occur. If it does then the peripheral may not be supported by this SDK.
     **/
    EDInternalBluetoothError,
    
    /*
     Bad input.
     **/
    EDBadInputBluetoothError,
    
    /*
     Not connected to a peripheral. This operation requires a peripheral to be already connected.
     **/
    EDNoConnectedPeripheralBluetoothError,
    
    /*
     Software is already connecting to inputted peripheral.
     **/
    EDAlreadyConnectingToPeripheralBluetoothError,
    
    /*
     Software is already connected to inputted peripheral.
     **/
    EDAlreadyConnectedToPeripheralBluetoothError,
    
    /*
     Currently recording audio data. This operation cannot be completed while recording is in progress.
     **/
    EDRecordingInProgressBluetoothError,
    
    /*
     Audio is currently being streamed to the connected Eko peripheral for playback. This operation cannot be completed while audio playback is in progress.
     **/
    EDAudioPlaybackInProgressBluetoothError,
    
    /*
     Software does not support the inputted peripheral.
     **/
    EDUnsupportedPeripheralBluetoothError,
};

@interface EDBluetoothError : NSError

+ (NSError *) errorWithCode: (int) code description: (NSString*) description;
+ (int) codeForErrorType: (EDBluetoothErrorType) errorType;
+ (NSString *) descriptionForErrorType: (EDBluetoothErrorType) errorType;

@end
