//
//  EDDataFormatter.h
//  Eko Devices
//
//  Created by Tyler Crouch on 7/27/17.
//
//

#import <Foundation/Foundation.h>

@interface EDDataFormatter : NSObject

//------------------------------------------------------------------------------
# pragma mark - Data Conversion
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

/**
 Convert signed short [-32768, 32767] to float [-1, 1]. [-32768, -1] --> [-32767, 0] --> [-1, 0] or [0, 32767] --> [0, 1].
 */

+ (float) convertShortToFloat: (short) value;

//------------------------------------------------------------------------------

/**
 Round number to nearest increment.
 */

+ (float) roundNumber: (float) number toNearestIncrement: (float) increment;

//------------------------------------------------------------------------------

/**
 Convert hex string to binary string.
 */

+ (NSString*)hexToBinary: (NSString*)hexString;

//------------------------------------------------------------------------------
# pragma mark - WAV File Formatting
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

/**
 Check to see if object is valid WAV data.
 */

+ (BOOL) isValidWAVData: (NSData*) WAVData;

//------------------------------------------------------------------------------

/**
 Check header of inputted data to see if it is of WAV file format.
 */

+ (BOOL) containsValidWAVHeader: (NSData*) WAVData;

//------------------------------------------------------------------------------

/**
 Check header of inputted data to see if it is of WAV file format.
 */

+ (int) getSampleRateFromWAVData: (NSData*) WAVData;

//------------------------------------------------------------------------------

/**
 Check duration of WAV data.
 */

+ (float) getDurationOfWAVData: (NSData*) WAVData;

//------------------------------------------------------------------------------

/**
 Format date into string. Does not include time.
 */

+ (NSString*) getFormattedDateStringFromDate: (NSDate*) date;

//------------------------------------------------------------------------------

/**
 Format date into time string. Does not include date.
 */

+ (NSString*) getFormattedTimeStringFromDate: (NSDate*) date;

//------------------------------------------------------------------------------

/**
 Format date into string. Does include date and time.
 */

+ (NSString*) getFormattedDateAndTimeStringFromDate: (NSDate*) date;

@end
