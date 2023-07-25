//
//  EDConstants.h
//  Eko Devices
//
//  Created by Tyler Crouch on 6/26/17.
//
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "EDMainsFilterType.h"
#import "EDDuoPeripheralRecordingSignalPreference.h"

/**
 Connection options for EDBLEManager
 */
typedef NS_OPTIONS(NSInteger, EDBLEManagerConnectionPolicy) {
  /*
   When foregrounded try to connect to last connected peripheral
   */
  EDBLEManagerConnectionPolicyAutoConnectInForeground =  1 << 0,
  /*
   On disconnect initiate re-connect to peripheral, unless it was initiated by
   the user.
   */
  EDBLEManagerConnectionPolicyAutoReconnect = 1 << 1
};

@interface EDConstants : NSObject

//------------------------------------------------------------------------------

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ Constants +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

//------------------------------------------------------------------------------

/**
 Should the application log messages.
 */

extern const BOOL EDLogEnabled;

//------------------------------------------------------------------------------

/**
 Should the application output API call logs (logEnabled must be true as well).
 API call log messages are pretty verbose and frequent.
 */

extern const BOOL EDLogServerAPIMessages;

/**
 Should the application output BLE logs (logEnabled must be true as well).
 BLE log messages are pretty verbose and frequent.
 */

extern const BOOL EDLogBLEMessages;

//------------------------------------------------------------------------------

/**
 Maximum number of allowable PIN entry attempts.
 */

extern const int EDMaximumNumberOfPINEntryAttempts;

//------------------------------------------------------------------------------

/**
 The graphical resolution of audio rolling plots. 1 = graph every point, 2 = graph every other point, etc..
 */

extern const int EDAudioRollingPlotResolution;

//------------------------------------------------------------------------------

/**
 The graphical resolution of ECG rolling plots. 1 = graph every point, 2 = graph every other point, etc..
 */

extern const int EDECGRollingPlotResolution;

//------------------------------------------------------------------------------

/**
 The graphical resolution of audio buffer plots. 1 = graph every point, 2 = graph every other point, etc..
 */

extern const int EDAudioBufferPlotResolution;

//------------------------------------------------------------------------------

/**
 The graphical resolution of ECG buffer plots. 1 = graph every point, 2 = graph every other point, etc..
 */

extern const int EDECGBufferPlotResolution;


//------------------------------------------------------------------------------

// +-+-+-+-+-+-+-+-+-+-+-+-+- Default Constant Values -+-+-+-+-+-+-+-+-+-+-+-+-+

//------------------------------------------------------------------------------

/**
 The minimum allowed gain for rolling audio plots.
 */

extern const float EDMinimumAudioGraphGain;

//------------------------------------------------------------------------------

/**
 The maximum allowed gain for rolling audio plots.
 */

extern const float EDMaximumAudioGraphGain;

//------------------------------------------------------------------------------

/**
 The default highlighted state alpha value.
 */

extern const float EDDefaultHighlightedStateAlpha;

//------------------------------------------------------------------------------

/**
 The default selected state alpha value.
 */

extern const float EDDefaultSelectedStateAlpha;

//------------------------------------------------------------------------------

/**
 Default plot signal selection preference
 */

extern const BOOL defaultPlotSignalSelectionPreference;

//------------------------------------------------------------------------------

/**
 Should recorded / realtime audio play from users device.
 */

extern const BOOL EDDefaultPlayAudioFromDeviceSpeakerPreference;

//------------------------------------------------------------------------------

/**
 Live stream should be started when available
 */

extern const BOOL EDDefaultAutomaticallyStartLiveStreamPreference;


//------------------------------------------------------------------------------

/**
 Default maximum duration for recordings.
 */

extern const float EDDefaultMaximumRecordingDurationPreference;

//------------------------------------------------------------------------------

/**
 Should ECG signal be inverted by default
 */

extern const BOOL EDDefaultInvertECGSignalPreference;

//------------------------------------------------------------------------------

/**
 Should quick record be enabled by default.
 */

extern const BOOL EDDefaultQuickRecordPreference;

//------------------------------------------------------------------------------

/**
 Default type of mains filter used for filtering ECG signals. Used when no stored filtering preference is found.
 */

extern const EDMainsFilterType EDDefaultMainsFilterType;

//------------------------------------------------------------------------------

/**
 Default type of mains filter used for filtering ECG signals. Used when no stored filtering preference is found.
 */

//extern const EDDuoPeripheralRecordingSignalPreference EDDefaultDuoPeripheralRecordingSignalPreference;

//------------------------------------------------------------------------------

/**
 Default height of a top header view.
 */

extern const float EDDefaultHeaderViewHeight;

/**
 Default type of mains filter used for filtering ECG signals. Used when no stored filtering preference is found.
 */

extern const EDDuoPeripheralRecordingSignalPreference EDDefaultDuoPeripheralRecordingSignalPreference;

@end
