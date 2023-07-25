//
//  EDBluetooth.h
//  Eko Devices
//
//  Created by Tyler Crouch on 6/26/17.
//
//

// WARNING: THIS IS CLASS II MEDICAL DEVICE SOFTWARE. IF YOU EDIT THIS SOFTWARE YOU MUST FILE CHANGES MADE WITH FDA BEFORE RELEASING THE EDITED SOFTWARE TO THE PUBLIC.

// NOTE: Using breakpoints (or otherwise pausing software processes) while an Eko Peripheral is connected will likely cause
//       a buffer overflow to occur and as a result recording data may become corrupted. Additionally the data parser
//       will start outputting points at a much faster rate to deal with the bloated buffer.

//-------------------------------------------------------------------------------------------------

// Required frameworks
#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>

// Public headers
#import "EDBluetoothPeripheralInfo.h"
#import "EDMainsFilterType.h"
#import "EDBluetoothError.h"

@class EDOTAManager;
@class EDPeripheralMetaData;
@class EDDeviceProtocolManager;

//-------------------------------------------------------------------------------------------------
# pragma mark - Delegate Protocols
//-------------------------------------------------------------------------------------------------

/**
 This protocol alerts users when Eko peripherals are found during Bluetooth scans, connect/disconnect to this device, experience a frimware crash, and have changes in Bluetooth signal connection strength.
 Additionally the protocol can be used to learn when a user turns Bluetooth on / off on this device.
 */

#import "EDPeripheralConnectionDelegateProtocol.h"

/**
 This protocol is used to stream audio and/or ECG data points received from a paired Eko Peripheral.
 Additionally, this protocol alerts subscribers to interruptions to audio/ECG data streams.
 */
#import "EDPeripheralAuscultationDataDelegateProtocol.h"

//#import "EDPeripheralMedicalSensorDataDelegateProtocol.h"

/**
 This protocol manages the recording of data from paired Eko peripherals.
 */

#import "EDPeripheralRecordingDelegateProtocol.h"

/**
 Use this protocol to get notified when a paired Eko peripheral updates volume level, battery level, or filter modes.
 Also outputs the approximate audio playback completion percent of audio streamed to paired Eko peripheral.
 */

#import "EDPeripheralDeviceInfoDelegateProtocol.h"

/**
 Use this protocol to be notified of events from the Enterprise SDK i.e. LiveStreaming
 */

#import "EDEnterpriseSDKDelegateProtocol.h"

//-------------------------------------------------------------------------------------------------
# pragma mark - EDBluetoothLE Interface
//-------------------------------------------------------------------------------------------------

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
@interface EDBluetooth : NSObject
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

//-------------------------------------------------------------------------------------------------
# pragma mark - Debug
//-------------------------------------------------------------------------------------------------

/**
 Set static gain that is applied to the upsampled audio channel data. Will have no effect if
 upsampledFilterChannelDynamicGainBoostEnabled is true.
 */
@property (nonatomic, assign) float upsampledFilterChannelStaticGain;

/**
 Denote if dynamic gain boosting to the upsampled audio channel data is enabled. If it is not
 enabled then a static gain will be applied.
 */
@property (nonatomic, assign) BOOL upsampledFilterChannelDynamicGainBoostEnabled;

/**
 Denote upsampled audio channel data is constrained to a window after gain is applied to it.
 */
@property (nonatomic, assign) BOOL upsampledFilterChannelAmplitudeWindowingEnabled;

//-------------------------------------------------------------------------------------------------
# pragma mark - Peripheral Scanning
//-------------------------------------------------------------------------------------------------

/**
 Boolean denoting if a Bluetooth scan for nearby Eko peripherals is currently in progress.
 */
@property (nonatomic, assign, readonly, getter=isScanningForPeripherals) BOOL scanningForPeripherals;

//-------------------------------------------------------------------------------------------------

/**
 Array of all the Eko peripherals discovered in current BLE scanning session.
 Reset when new scan starts.
 */
@property (nonatomic, strong, readonly) NSMutableArray *discoveredPeripherals;

//-------------------------------------------------------------------------------------------------

/**
 Map of RSSI values. Key: peripheral UUID, Value: RSSI(decibels)
 */
@property (atomic, strong, readonly) NSMutableDictionary<NSUUID*, NSNumber*>*  rssiMap;

//-------------------------------------------------------------------------------------------------

/**
 Discovered Eko peripheral with largest RSSI value.
 */
@property (nonatomic, strong, readonly) CBPeripheral *discoveredPeripheralWithLargestRSSIValue;

//-------------------------------------------------------------------------------------------------

/**
 Largest RSSI value of a discovered Eko peripheral.
 */
@property (nonatomic, strong, readonly) NSNumber* largestDiscoveredPeripheralRSSIValue;

//-------------------------------------------------------------------------------------------------
# pragma mark - Peripheral Connection
//-------------------------------------------------------------------------------------------------

/**
 Boolean denoting if an Eko peripheral is currently paired with this device.
 */
@property (nonatomic, assign, readonly, getter=isPeripheralConnected) BOOL peripheralConnected;

//-------------------------------------------------------------------------------------------------

/**
 Boolean denoting if Bluetooth is powered on.
 If Bluetooth LE (Bluetooth Core Specification v 4.0+) is not available on this device then this will be NO.
 */
@property (nonatomic, assign, readonly, getter=isBluetoothPoweredOn) BOOL bluetoothPoweredOn;

//-------------------------------------------------------------------------------------------------

/**
 The state of the central manager. Useful for determining why Bluetooth may not be available.
 */
@property (nonatomic, assign, readonly) CBManagerState centralManagerState;

//-------------------------------------------------------------------------------------------------

/**
 Boolean denoting if Bluetooth LE (protocol 4.0+) is supported on this iOS device & if this application is authorized to use Bluetooth LE.
 */
@property (nonatomic, assign, readonly, getter=isBluetoothLowEnergyCapabilityAvailable) BOOL bluetoothLowEnergyCapabilityAvailable;

//-------------------------------------------------------------------------------------------------

/**
 Peripheral type of the Eko hardware connected with this device.
 If no peripheral is connected this will be set to "EDUnknownPeripheral".
 */
@property (nonatomic, assign, readonly) EDPeripheralType connectedPeripheralType;

//-------------------------------------------------------------------------------------------------

/**
 Signal quality level of connected Eko peripheral.
 */

@property (nonatomic, assign, readonly) EDSignalQualityType connectedPeripheralSignalQuality;

//-------------------------------------------------------------------------------------------------

/**
 Current filter mode of paired Eko peripheral. If no Duo or Core2 is paired value will be filterModeNotReported (0).
 */
@property (nonatomic, assign, readonly) EDDuoPeripheralFilterMode connectedPeripheralFilterMode __attribute__((deprecated("use ekoPeripheralOutputtedECGValue:filterChannel: instead.")));

@property (nonatomic, assign, readonly) EDDuoPeripheralFilterMode connectedEkoDuoFilterMode;
@property (nonatomic, assign, readonly) EDCore2PeripheralFilterMode connectedEkoCore2FilterMode;

//-------------------------------------------------------------------------------------------------

/**
 Battery level of connected Eko peripheral.
 */

@property (nonatomic, assign, readonly) int connectedPeripheralBatteryLevel;

//-------------------------------------------------------------------------------------------------

/**
 Volume level of connected Eko peripheral. 0 is the lowest possible setting, which is
 still audible(not muted)
 */

@property (nonatomic, assign, readonly) int connectedPeripheralVolumeLevel;

//-------------------------------------------------------------------------------------------------

/**
 Gets/Sets Active Noise Cancellation if the connected device is a Core2.
 */

@property (nonatomic, assign, readonly) BOOL isANCOn;

//-------------------------------------------------------------------------------------------------

/**
 Peripheral connected with this device.
 */

@property (nonatomic, strong, readonly) CBPeripheral *connectedPeripheral;

//-------------------------------------------------------------------------------------------------

/**
 Peripheral that this class is trying to connect to.
 */

@property (nonatomic, strong, readonly) CBPeripheral* connectingPeripheral;

//-------------------------------------------------------------------------------------------------

/**
 Last peripheral that connected with this device. Value stored in NSUserDefaults.
 */

@property (nonatomic, strong, readonly) CBPeripheral *lastConnectedPeripheral;

//-------------------------------------------------------------------------------------------------
# pragma mark - Functionality Context Variables
//-------------------------------------------------------------------------------------------------

/**
 Boolean denoting if recording of medical sensor data is currently in progress.
 */

@property (nonatomic, assign, readonly, getter=isRecording) BOOL recording;

//-------------------------------------------------------------------------------------------------

/**
 Boolean denoting if audio is being streamed to paired peripheral for playback.
 */

@property (nonatomic, assign, readonly, getter=isStreamingAudioToEkoPeripheral) BOOL streamingAudioToEkoPeripheral;

//-------------------------------------------------------------------------------------------------

/**
 Boolean denoting if paired peripheral is playing back streamed audio.
 */

@property (nonatomic, assign, readonly, getter=isEkoPeripheralPlayingStreamedAudio) BOOL ekoPeripheralPlayingStreamedAudio;

//-------------------------------------------------------------------------------------------------

/**
 Total percent of audio data that has been streamed to connected peripheral for audio playback.
 */

@property (nonatomic, assign, readonly) float audioPlaybackStreamCompletionPercent;

//-------------------------------------------------------------------------------------------------
# pragma mark - Settings
//-------------------------------------------------------------------------------------------------

/**
 Boolean denoting if recording of medical sensor data is currently in progress.
 */

@property (nonatomic, assign, readonly) int audioSampleRate;

//-------------------------------------------------------------------------------------------------

/**
 Boolean denoting if recording of medical sensor data is currently in progress.
 */

@property (nonatomic, assign, readonly) int ECGSampleRate;

//-------------------------------------------------------------------------------------------------

/**
 Get recording completion percent with range: [0, 1].
 */

@property (nonatomic, assign, readonly) float recordingCompletionPercent;

//-------------------------------------------------------------------------------------------------

/**
 Get the duration of cached recording data.
 Can be used while recording is in progress to see how many seconds of data has already been captured.
 */

@property (nonatomic, assign, readonly) float recordedDataDuration;

/**
 Boolean denoting if library should log messages
 */
@property (nonatomic, assign) BOOL logMessages;   

//-------------------------------------------------------------------------------------------------

/**
 Wether or not the ECG signal will be inverted.
 */
@property (nonatomic, assign) BOOL invertECGSignal;

//-------------------------------------------------------------------------------------------------

/**
 Filter audio recieved from connected peripheral.
 Recorded data and outputted medical data points will be filtered.
 Filter does not apply to audio streamed from this device to connected peripheral.
 */

@property (nonatomic, assign, getter= isFilteringAudioRecievedFromConnectedPeripheral) BOOL filteringAudioRecievedFromConnectedPeripheral;

//-------------------------------------------------------------------------------------------------

/**
 Maximum desired duration of recordings. Recording will complete if this value is reached.
 Cannot be set while a recording is in progress. Rounded to nearest 1/500th second.
 */

@property (nonatomic, assign) int maximumRecordingDuration;

//-------------------------------------------------------------------------------------------------

/**
 Type of mains filter used to filter ECG data.
 */
@property (nonatomic, assign) EDMainsFilterType mainsFilterType;

//-------------------------------------------------------------------------------------------------

/**
 Use unfiltered data(for testing purposes only)
 */
@property (nonatomic, assign) BOOL useUnfilteredData;
//-------------------------------------------------------------------------------------------------
# pragma mark - OTA Manager
//-------------------------------------------------------------------------------------------------

@property (nonatomic, readonly, strong) EDOTAManager* otaManager;

//-------------------------------------------------------------------------------------------------
#pragma mark - Protocol Manager
//-------------------------------------------------------------------------------------------------
@property (nonatomic, strong) EDDeviceProtocolManager* protocolManager;

//-------------------------------------------------------------------------------------------------
# pragma mark - Library Methods
//-------------------------------------------------------------------------------------------------

+ (instancetype) sharedInstance;

//-------------------------------------------------------------------------------------------------
# pragma mark - Delegates
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------


/**
 Add EkoPeripheralConnectionDelegate. There can be many delegates of this type.
 */

- (void) addPeripheralConnectionDelegate: (id<EDPeripheralConnectionDelegate>)delegate;

//-------------------------------------------------------------------------------------------------

/**
 Remove EkoPeripheralConnectionDelegate. There can be many delegates of this type.
 */

- (void) removePeripheralConnectionDelegate: (id<EDPeripheralConnectionDelegate>)delegate;

//-------------------------------------------------------------------------------------------------

- (void) addPeripheralAuscultationDataDelegate: (id<EDPeripheralAuscultationDataDelegate>) delegate audioFilterChannel: (EDAudioFilterChannel) audioFilterChannel;
- (void) addPeripheralAuscultationDataDelegate: (id<EDPeripheralAuscultationDataDelegate>) delegate  audioFilterChannel: (EDAudioFilterChannel) audioFilterChannel audioResolution: (int) resolution;

// Remove delegate with specific audio / ECG filter channel
- (void) removePeripheralAuscultationDataDelegate: (id<EDPeripheralAuscultationDataDelegate>) delegate;

/**
 Add EDPeripheralDeviceInfoDelegate. There can be many delegates of this type.
 */

- (void) addPeripheralDeviceInfoDelegate: (id<EDPeripheralDeviceInfoDelegate>)delegate;

//-------------------------------------------------------------------------------------------------

/**
 Remove EDPeripheralDeviceInfoDelegate.
 */

- (void) removePeripheralDeviceInfoDelegate: (id<EDPeripheralDeviceInfoDelegate>)delegate;

//-------------------------------------------------------------------------------------------------

/**
 Add EkoPeripheralRecordingDelegate. There can be many delegates of this type.
 */

- (void) addPeripheralRecordingDelegate: (id<EDPeripheralRecordingDelegate>) delegate audioFilterChannel: (EDAudioFilterChannel) audioFilterChannel;

/**
 Add EkoEnterpriseSDKDelegate. There can be many delegates of this type.
 */

- (void) addEnterpriseSDKDelegate: (id<EDEnterpriseSDKDelegate>) delegate;
- (void) removeEnterpriseSDKDelegate: (id<EDEnterpriseSDKDelegate>) delegate;

//-------------------------------------------------------------------------------------------------

/**
 Remove EkoPeripheralRecordingDelegate.
 */

- (void) removePeripheralRecordingDelegate: (id<EDPeripheralRecordingDelegate>)delegate;

//-------------------------------------------------------------------------------------------------
# pragma mark - Utility
//-------------------------------------------------------------------------------------------------

/**
 Purge all buffer data to remove all the latency that may have built up while decoding data.
 This will also cancel any ongoing recordings to avoid those recordings losing data that was in the purged buffers.
 */

- (void) resetMedicalSensorDataBuffers;

//-------------------------------------------------------------------------------------------------

/**
 Purge the value used to set the lastConnectedPeripheral property from NSUserDefaults.
 */

- (void) forgetLastConnectedPeripheral;

//-------------------------------------------------------------------------------------------------

/**
 Returns the maximum volume level for the type of Eko peripheral type specified.
 */

- (int) getMaximumVolumeLevelForPeripheralType: (EDPeripheralType) peripheralType;

//-------------------------------------------------------------------------------------------------

/**
 Returns the name the type of Eko peripheral type specified.
 */
- (NSString *) getNameOfPeripheralType: (EDPeripheralType) peripheralType;

//-------------------------------------------------------------------------------------------------

/**
 Total duration of time that an Eko peripheral has been paired/connected. Attempting to connect to a new peripheral will reset this value.
 */

- (float) connectionDuration;

//-------------------------------------------------------------------------------------------------

/**
 Returns the EDPeripheralType for a CBPeripheral
 */
- (EDPeripheralType) getEDPeripheralTypeForPeripheral: (CBPeripheral*) peripheral;

//-------------------------------------------------------------------------------------------------

/**
 Returns the meta-data for the perpheral e.g. fw version etc.
 */
- (EDPeripheralMetaData*) getMetadataForPeripheral: (CBPeripheral*) peripheral;

//-------------------------------------------------------------------------------------------------
# pragma mark - BLE : Scanning
//-------------------------------------------------------------------------------------------------

/**
 Start Bluetooth scan for nearby Eko Peripherals that are currently not connected to any device.
 Resets the discoveredPeripherals property.
 All unique Eko peripherals detected will be added to the discoveredPeripherals property.
 */

- (BOOL) startScanningForEkoPeripherals: (NSError**)error;

//-------------------------------------------------------------------------------------------------

/**
 Stop Bluetooth scan for nearby Eko Peripherals that are currently not connected to any device.
 */

- (void) stopScanningForEkoPeripherals;

//-------------------------------------------------------------------------------------------------
# pragma mark - BLE : Pairing
//-------------------------------------------------------------------------------------------------

/**
 Connect to specified Eko peripheral.
 */

- (BOOL) connectEkoPeripheral: (CBPeripheral *)peripheral error: (NSError**)error;

//-------------------------------------------------------------------------------------------------

/**
 Cancel connection to Eko peripheral.
 */

- (void) cancelEkoPeripheralConnection;

//-------------------------------------------------------------------------------------------------
# pragma mark - BLE : Connected Peripheral Commands
//-------------------------------------------------------------------------------------------------

/**
 Stream WAV audio to connected peripheral starting at specified time.
 Inputted time will be automatically rounded to nearest 4000th of a second.
 Audio must have 44 byte header and consist of 16 bit mono PCM samples at a 4 kHz sample rate.
 */

- (BOOL) streamAudioToConnectedPeripheral: (NSData *)audioData startTime: (NSTimeInterval)startTime error: (NSError**)error;

//-------------------------------------------------------------------------------------------------

/**
 Stop streaming WAV audio to connected peripheral.
 */

- (void) stopStreamingAudioToConnectedPeripheral;

//-------------------------------------------------------------------------------------------------

/**
 Set filter mode of connected Eko peripheral. Only supports Eko Duo or Core2 peripheral.
 */
- (BOOL) setConnectedEkoPeripheralFilterMode: (EDDuoPeripheralFilterMode)filterMode error: (NSError**)error __attribute__((deprecated("use ekoPeripheralOutputtedECGValue:filterChannel: instead.")));

- (BOOL) setConnectedEkoDuoFilterMode: (EDDuoPeripheralFilterMode)filterMode error: (NSError**)error;
- (BOOL) setConnectedEkoCore2FilterMode: (EDCore2PeripheralFilterMode)filterMode error: (NSError**)error;

//-------------------------------------------------------------------------------------------------

/**
 Set volume of connected Eko peripheral.
 */

- (BOOL) setConnectedEkoPeripheralVolumeLevel: (int)volumeLevel error: (NSError**)error;

/**
 Set Automatic Noise Cancellation on or off of connected Eko Core2 peripheral.
 */

- (BOOL) setConnectedEkoPeripheral2ANC: (BOOL)anc error: (NSError**)error;

//-------------------------------------------------------------------------------------------------
# pragma mark - Recording Medical Sensor Data
//-------------------------------------------------------------------------------------------------

/**
 Start recording data recieved from connected Eko peripheral.
 */

- (BOOL) startRecordingData: (NSError**)error;

//-------------------------------------------------------------------------------------------------

/**
 Stop recording data recieved from connected Eko peripheral.
 */

- (void) stopRecordingData;

//-------------------------------------------------------------------------------------------------

/**
Send recording flag to connected Core2 peripheral.
*/

- (void)sendEkoPeripheralRecordingFlagValue: (BOOL)flag;

//-------------------------------------------------------------------------------------------------

/**
 Delete data recorded data.
 */

- (void) deleteRecordingData;

//-------------------------------------------------------------------------------------------------

/**
 Get recording completion percent with range: [0, 1].
 */

- (float) recordingCompletionPercent;

//-------------------------------------------------------------------------------------------------

/**
 Get the duration of cached recording data.
 Can be used while recording is in progress to see how many seconds of data has already been captured.
 */

- (float) recordedDataDuration;

//-------------------------------------------------------------------------------------------------

/**
 Get audio recording object. Only available after recording completes.
 */

- (NSData*) getAudioRecordingDataForFilterChannel: (EDAudioFilterChannel) audioFilterChannel;

//-------------------------------------------------------------------------------------------------

- (NSData*) getECGRecording __attribute__((deprecated("use ekoPeripheralOutputtedECGValue:filterChannel: instead.")));
/**
 Get ECG recording object. Only available after recording completes.
 */

- (NSData*) getECGRecordingForFilterChannel: (EDAudioFilterChannel) filterChannel;

//-------------------------------------------------------------------------------------------------
# pragma mark - Enterprise SDK - LiveStream
//-------------------------------------------------------------------------------------------------

/**
 Setup Enterprise SDK
 */
- (void)setupEnterpriseSDKWithURL:(NSURL *)url key:(NSString *)key secret:(NSString *)secret;

//-------------------------------------------------------------------------------------------------

/**
 Create new LiveStream. successBlock returns stream ID
 */
- (void)newLiveStreamWithSuccess:(void (^)(NSString *))successBlock failure:(void (^)(NSError *))failureBlock;

//-------------------------------------------------------------------------------------------------

/**
 Retrieve previously created LiveStream given the stream ID.
 */
- (void)getLiveStreamWithID:(NSString *)streamID success:(void (^)(NSString *))successBlock failure:(void (^)(NSError *))failureBlock;

//-------------------------------------------------------------------------------------------------

/**
 Delete previously created LiveStream given the stream ID.
 */
- (void)deleteLiveStreamWithID:(NSString *)streamID success:(void (^)(NSString *))successBlock failure:(void (^)(NSError *))failureBlock;

//-------------------------------------------------------------------------------------------------

@end
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
