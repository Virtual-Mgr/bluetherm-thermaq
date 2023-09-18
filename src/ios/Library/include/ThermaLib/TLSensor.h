//
//  TLSensor.h
//  ThermaLib
//
//  Copyright © 2016 Electronic Temperature Instruments Limited. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "TLRange.h"
#import "TLDevice.h"

@class TLDateStamp;

/// Possible sensor types
typedef NS_ENUM(NSInteger, TLSensorType) {
    /// Unknown
    TLSensorTypeUnknown,
    /// Internal Thermistor
    TLSensorTypeInternalThermistor,
    /// External Thermistor
    TLSensorTypeExternalThermistor,
    /// External Thermistor Connector
    TLSensorTypeExternalThermistorConnector,
    /// Infrared Sensor Type 1
    TLSensorTypeInfraredType1,
    /// K Thermocouple
    TLSensorTypeKThermocouple,
    /// T Thermocouple
    TLSensorTypeTThermocouple,
    /// PT1000 (NOT YET SUPPORTED)
    TLSensorTypePT1000,
    /// pH Sensor (NOT YET SUPPORTED)
    TLSensorTypePHSensor,
    /// Humidity Temperature
    TLSensorTypeHumidityTemperature,
    /// Humidity
    TLSensorTypeHumidity,
    /// Moisture Sensor (NOT YET SUPPORTED)
    TLSensorTypeMoistureSensor,
    /// Fixed Type K Thermocouple
    TLSensorTypeKThermocoupleFixed,
    /// DIshTemp Blue sensor
    TLSensorTypeDishTempBlue
};

/// The `TLSensor` protocol encapsulates a sensor in a way that is independent of the underlying connection type of the device
@protocol TLSensor <NSObject>

/// Device that the sensor is part of
@property (weak, nonatomic, readonly) id<TLDevice> device;

/**
 * @brief Most recent available reading.
 *
 * The reading is represented in units given by #readingUnit, and will
 * depend on the generic type (temperature, humidity etc.) of the sensor,
 * given by #genericType.
 */
@property (assign, nonatomic, readonly) float reading;

/**
 * @brief maximum reading, as reported by the device. Only applicable to
 * cloud devices at present
 *
 * The reading is represented in units given by #readingUnit, and will
 * depend on the generic type (temperature, humidity etc.) of the sensor,
 * given by #genericType.
 */
@property   (assign, nonatomic, readonly) float maxReading;

/**
 * @brief minimum reading, as reported by the device. Only applicable to
 * cloud devices at present
 *
 * The reading is represented in units given by #readingUnit, and will
 * depend on the generic type (temperature, humidity etc.) of the sensor,
 * given by #genericType.
 */
@property   (assign, nonatomic, readonly) float minReading;


/// The type of sensor
@property (assign, nonatomic, readonly) TLSensorType type;

/// The sensor's index (1-based)
@property (assign, nonatomic, readonly) NSUInteger index;

/// the effective range of the sensor
@property (strong, nonatomic, readonly) TLRange *range;

/// Whether the high alarm has been breached
@property (nonatomic, readonly) BOOL highAlarmBreached;

/// Whether the low alarm has been breached
@property (nonatomic, readonly) BOOL lowAlarmBreached;

/// Whether the sensor reading is outside its recognized range
@property (nonatomic, readonly) BOOL outOfRange;

/**
 @brief The unit corresponding to the value returned by TLSensor.reading.
 
 Note: This unit is fixed for a given {@link TLGenericSensorType}, and is not to be confused with {@link TLSensor.displayUnit}.
 
 For example, for temperature sensors, this attribute is always a reading in Celsius, even though the device itself (and the client app,
 if required) may display Fahrenheit.
 */
@property (assign, readonly) TLDeviceUnit readingUnit;

/**
 @brief Indicates whether the physical device would be signalling a high alarm for the currently-held latest reading
 
 Some devices do not themselves signal alarm conditions. Seel {@link TLDeviceFeatureAlarm}. For those that do, this attribute is provided so that apps can, if required, match the indicators on the physical device.
 */
@property (assign, nonatomic, readonly) BOOL highAlarmSignalled;

/**
@brief Indicates whether the physical device would be signalling a low alarm for the currently-held latest reading

Some devices do not themselves signal alarm conditions. Seel {@link TLDeviceFeatureAlarm}. For those that do, this attribute is provided so that apps can, if required, match the indicators on the physical device.
*/
@property (assign, nonatomic, readonly) BOOL lowAlarmSignalled;

/**
 @brief Best-effort estimate of when the current reading was measured by the device.
 
 Note that the supported Bluetooth instruments do not report measurement time themselves. This attribute represents the time at which the iOS-generated Bluetooth characteristic update notification was received by the app.
 Depending on CPU load, this may be later than the time at which the device sent the reading over the air.
 */
@property (nonatomic, readonly) NSDate *readingTimestamp;

/// Whether the sensor currently has a fault
@property (assign, nonatomic, readonly, getter=isFault) BOOL fault;

/// The temperature at which the high alarm should trigger
@property (assign, nonatomic) float highAlarm;

/// Whether the high alarm is activated
@property (assign, nonatomic) BOOL highAlarmEnabled;

/// The temperature at which the low alarm should trigger
@property (assign, nonatomic) float lowAlarm;

/// Whether the low alarm is activated
@property (assign, nonatomic) BOOL lowAlarmEnabled;

/// Whether the sensor is enabled or not (Note: not all sensors can be disabled on all device types)
@property (assign, nonatomic, getter=isEnabled) BOOL enabled;

/// The sensor's name
@property (strong, nonatomic) NSString *name;

/// The date that the trim value was set - read-only, changes when the trim value is set
@property (strong, nonatomic, readonly) TLDateStamp *trimSetDate;

/**
 * @brief Current trim value set on the sensor.
 *
 * The trim value allows a limited degree of user-level recalibration of sensors, and is only
 * currently available for Bluetooth Low Energy instruments
 */
@property (assign, nonatomic) float trimValue;

/**
 * @brief The display unit for the sensor.
 *
 * If the device the sensor is attached to has a physical display, this will reflect the units in which readings for
 * this sensor will be shown on the device itself. Note that in some cases, for example the ThermaPen Blue,
 * the device stores a unit setting even though it has no physical display.
 *
 * This attribute may be used, at the client app's discretion, to match the the app's display of readings with
 * that of the actual device.
 *
 * Not to be confused with {@link TLSensor.readingUnit}, which specifies the unit of {@link TLSensor.reading}
 */
@property (readonly, assign) TLDeviceUnit displayUnit;

// methods

/**
 * @brief Reset the running maximum value to the current reading
 *
 *  Not applicable to all devices. Seel {@link TLDeviceFeature}
 */
-(void) resetMax;

/**
 * @brief Reset the running minimum value to the current reading
 *
 *  Not applicable to all devices. Seel {@link TLDeviceFeature}
 */
-(void) resetMin;


/**
 * @brief The generic type of the sensor.
 *
 * @see {@link TLGenericSensorType}.
 */
@property (assign, readonly)TLGenericSensorType genericType;

/**
 * @brief How the device would display the current reading.
 *
 * This is provided so that if necessary client apps can ensure that they present reading values exactly
 * as they appear on the instrument's display, if it has one.
 */
@property (readonly, nonatomic) NSString *readingAsDisplayed;


@end
