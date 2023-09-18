//
//  TLDevice.h
//  ThermaLib
//
//  Copyright © 2016 Electronic Temperature Instruments Limited. All rights reserved.
//


#import <Foundation/Foundation.h>

@protocol TLSensor;
@protocol TLRemoteSettings;
@class TLDateStamp;

/**
 * @brief The connection method for the device
 **/
typedef NS_ENUM(NSInteger, TLTransport) {
    /// Bluetooth Low Energy connection
    TLTransportBluetoothLE,
    
    /// Indirect connection to an instrument via ETI Web Service - <b><i>devices using this transport are not supported by this version of ThermaLib</i></b>
    TLTransportCloudService,
    
    /// Simulated - internal use only - <b><i>reserved for internal use</i></b>
    TLTransportSimulated,
};

/// The kinds of quantity a sensor can measure
typedef NS_ENUM(NSInteger, TLGenericSensorType) {
    /// The generic sensor type is not (yet) known
    TLGenericSensorTypeUnknown = 0,
    /// temperature
    TLGenericSensorTypeTemperature = 1,
    /// humidity
    TLGenericSensorTypeHumidity = 2,
    /// acidity
    TLGenericSensorTypeAcidity = 3
};

/// The type of device
typedef NS_ENUM(NSInteger, TLDeviceType) {
    /// Type unknown
    TLDeviceTypeUnknown,
    /// BlueTherm One
    TLDeviceTypeBlueThermOne,
    /// ThermaQ Blue
    TLDeviceTypeThermaQBlue,
    /// ThermaPen Blue
    TLDeviceTypeThermaPenBlue,
    /// ThermaQ WiFi <i>- devices of this type are not supported by this version of ThermaLib</i>
    TLDeviceTypeThermaQWiFi,
    /// ThermaData WiFi <i>- devices of this type are not supported by this version of ThermaLib</i>
    TLDeviceTypeThermaDataWiFi,
    /// RayTemp Blue
    TLDeviceTypeRayTempBlue,
    /// TempTest Blue
    TLDeviceTypeTempTestBlue,
    /// Dishtemp Blue
    TLDeviceTypeDishTempBlue
};

/// Possible connection states
typedef NS_ENUM(NSInteger, TLDeviceConnectionState) {
    /// Connection state not (yet) known
    TLDeviceConnectionStateUnknown,
    /// When last tested, the device was eligible for connection.
    TLDeviceConnectionStateAvailable,
    /// A connection request has been issued but has not yet completed.
    TLDeviceConnectionStateConnecting,
    /// The device is connected to.
    TLDeviceConnectionStateConnected,
    /// A disconnection request has been made but has not yet completed.
    TLDeviceConnectionStateDisconnecting,
    /// The device has been disconnected
    TLDeviceConnectionStateDisconnected,
    /// The device is known to ThermaLib but is not available for connection
    TLDeviceConnectionStateUnavailable,
    /// The device is known to ThermaLib but it is not currenctly supported. An update of the app, the device, or both may be required.
    TLDeviceConnectionStateUnsupported,
    /// The device is known to ThermaLib but the app has not yet been registered to receive information about the device. A {@link #requestDeviceAccess} call is required.
    /// Currently only relevant for ThermaData and ThermaQ WiFi devices
    TLDeviceConnectionStateUnregistered
    
};

/// Possible disconnection reasons
typedef NS_ENUM(NSInteger, TLDeviceDisconnectionReason) {
    /// Unknown
    TLDeviceDisconnectionReasonUnknown,
    /// User disconnect
    TLDeviceDisconnectionReasonUser,
    /// No Internet
    TLDeviceDisconnectionReasonNoInternet,
    /// No Bluetooth
    TLDeviceDisconnectionReasonNoBluetooth,
    /// Authentication error
    TLDeviceDisconnectionReasonAuthenticationFailure,
    /// Unexpected
    TLDeviceDisconnectionReasonUnexpected,
    /// Device was deliberately shut down
    TLDeviceDisconnectionReasonDeviceShutDown,
};

/// Temperature display unit
typedef NS_ENUM(NSInteger, TLDeviceUnit) {
    /// degrees Celsius
    TLDeviceUnitCelsius,
    /// degrees Fahrenheit
    TLDeviceUnitFahrenheit,
    /// relative humidity
    TLDeviceUnitRelativeHumidity,
    /// pH
    TLDeviceUnitPH,
    /// unit not (yet) known
    TLDeviceUnitUnknown
};


/**
 * @brief Device command types.
 *
 * NB These are currently only used for Bluetooth Low Energy devices, i.e. those for which
 * {@link TLDevice.transportType} is #TLTransportBluetoothLE.
 */
typedef NS_ENUM(NSInteger, TLDeviceCommandType) {
    /// requests the device takes a measurement immediately and transmits it
    TLDeviceCommandTypeMeasure,
    /// requests the device identifies itself, for example by flashing an LED
    TLDeviceCommandTypeIdentify,
    /// requests the device returns to factory settings, excluding trim values
    TLDeviceCommandTypeFactorySettings,
    /// requests the device returns to factory settings, including trim values
    TLDeviceCommandTypeFactoryReset
};


/// Possible notifications
typedef NS_ENUM(NSInteger, TLDeviceNotificationType) {
    /// None
    TLDeviceNotificationTypeNone = 0,
    /// button pressed on the device
    TLDeviceNotificationTypeButtonPressed = 1,
    /// device is about to shut down
    TLDeviceNotificationTypeShutdown = 2,
    ///device received an invalid setting
    TLDeviceNotificationTypeInvalidSetting = 3,
    /// device received an invalid command
    TLDeviceNotificationTypeInvalidCommand = 4,
    /// device requests host app to re-read all data
    TLDeviceNotificationTypeRefreshRequest = 5,
    /// communication error detected
    TLDeviceNotificationTypeCommunicationError = 6,
    /// Rremote device checkpoint event
    TLDeviceNotificationTypeCheckpoint = 7,
};

/**
 * @brief battery warning level
 *
 * Designed to correspond to the levels the battery LCD indicator would display. Apps can use this
 * to match their battery level displays to the physical device's display.
 *
 * See #batteryWarningLevel
 */
typedef NS_ENUM(NSInteger, TLBatteryWarningLevel) {
    /// The battery should be replaced immediately. Corresponds to an 'empty battery' indication on the device's physical display.
    TLBatteryWarningLevelCritical = 0,
    /// The battery should be replaced. Corresponds to a 'low battery' indication on the device's physical display.
    TLBatteryWarningLevelLow = 1,
    /// The battery charge is between that indicated by #TLBatteryWarningLevelLow and a notional, device-dependent 'half-full' level.
    TLBatteryWarningLevelHalf = 2,
    /// The battery charge is between that indicated by a notional, device-dependent 'half-full' level and fully-charged.
    TLBatteryWarningLevelFull = 3,
};


typedef NS_ENUM(NSInteger, TLDeviceFeature) {
    /**
     * @brief the device can be requested to switch itself off after a set period of time.
     *
     * Not available for all instruments.as
     *
     * @see {@link TLDevice.autoOffInterval}
     */
    TLDeviceFeatureAutoOff = 0x01,
    /**
     * @brief the SDK polls for device updates. Not used by this version of ThermaLib
     *
     * @see {@link TLDevice.pollInterval}
     */
    TLDeviceFeaturePolledDevice = 0x02,
    /**
     * @brief emissivity of the measured surface can be set. Currently only applies to {@link TLDeviceTypeRayTempBlue}
     *
     * @see {@link TLDevice.emissivity}
     */
    TLDeviceFeatureEmissivity = 0x04,
    /**
     * @brief the device has its own display. Most devices do, but the ThermaPen Blue, for example, doesn't.
     *
     * @see {@link TLSensor.readingAsDisplayed}
     */
    TLDeviceFeatureDisplay = 0x08,
    /**
     * @brief <b>(Cloud devices only)</b> the device settings will take effect on the actual instrument
     * some time after they are set locally. Not used by this version of ThermaLib.
     *
     */
    TLDeviceFeatureAsynchronousSettings = 0x10,
    /**
     * @brief The device has its own alarm indication, for example on the LCD display or LEDs.
     */
    TLDeviceFeatureAlarm = 0x20,
    /**
     * @brief The device has per-sensor settable high and low alarm levels, that are stored in its non-volatile memory.
     *
     * @see {@link TLSensor.highAlarm}, {@link TLSensor.lowAlarm}
     */
    TLDeviceFeatureSettableAlarms = 0x40,

    /**
     * @brief The device stores and reports on-device the maximum reading so far.
     *
     * @see {@link TLSensor.resetMax}
     */
    TLDeviceFeatureMaxReading = 0x80,
    /**
     * @brief The device reports and reports on-device the minimum reading so far.
     *
     * @see {@link TLSensor.resetMin}
     */
    TLDeviceFeatureMinReading = 0x100

};


/// The `TLDevice` protocol encapsulates a device independently of the underlying connection type e.g. Bluetooth
@protocol TLDevice <NSObject>

/// The manufacturer name of the device
@property (strong, nonatomic, readonly) NSString *manufacturerName;

/// The serial number of the device
@property (strong, nonatomic, readonly) NSString *serialNumber;

/// The model number of the device
@property (strong, nonatomic, readonly) NSString *modelNumber;

/// The protocol version of the device, if available, or a 0-length NSString
@property (strong, nonatomic, readonly) NSString *protocolVersion;

/// The hardware version of the device, if available, or a 0-length NSString
@property (strong, nonatomic, readonly) NSString *hardwareVersion;

/// The software revision of the device, if available, or a 0-length NSString
@property (strong, nonatomic, readonly) NSString *softwareRevision;

/// The firmware revision of the device, if available, or a 0-length NSString
@property (strong, nonatomic, readonly) NSString *firmwareRevision;

/// The transport type of the device e.g. Bluetooth
@property (assign, nonatomic, readonly) TLTransport transportType;

/**
 * @brief The device name.
 *
 * Note that for most devices this will be the same as the device name advertised at the Bluetooth level. However,
 * for devices of type {@link TLDeviceTypeDishTempBlue} this method will instead report
 * <pre>"<serial number> DishTemp Blue"</pre>, in order to uniquely identify the device, and be consistent with other
 * devices supported by ThermaLib.
 *
 */
@property (strong, nonatomic, readonly) NSString *deviceName;

/// The device type.
@property (assign, nonatomic, readonly) TLDeviceType deviceType;

/**
 * @brief Array of {@link TLDeviceCommandType} values, specifying the commands available to this device that are not implemented by other methods.
 *
 * @see {@link TLDeviceCommandType}, {@link TLDevice#isSupportedCommand:}
 */
@property (nonatomic, readonly) NSArray *availableCommands;

/// data timestamp. best estimate of the time when the current device/sensor data was collected.
@property (nonatomic, readonly) NSDate *dataTimestamp;

/// if true, alarm values are counted as in-bounds by the convenience computations offered by TLSensor.
/**
 * @brief determines whether readings that exactly match alarm settings are to count as in-bounds.
 *
 * If true, readings that exactly match alarm settings are counted as limits, i.e. (as in everyday usage) they do not indicate
 * an alarm condition. Otherwise such values are counted as out-of-bounds.
 */
@property (assign, nonatomic) BOOL alarmSettingsAreLimits;

/**
 * @brief <b>(Cloud Devices Only)"</b> Defines how oftern ThermaLib requests updated information
 * for the device. Not used in this variant of ThermaLib.
 *
 */
@property (readwrite, nonatomic, assign) NSUInteger pollInterval;

/**
 * @brief The features that this device has.
 *
 * This is a bitwise OR of the values defined in #TLDeviceFeature.
 */
@property (assign, nonatomic, readonly) NSInteger features;

/**
 * @brief The device identifier
 *
 * For Bluetooth devices, this is a UUID assigned by iOS at discovery time.
 * Only use this identifier for Bluetooth devices if you are sure it meets your requirements in terms of scope and stability.
 * (See https://developer.apple.com/reference/corebluetooth/cbperipheral/1518935-identifier). For a globally unique and stable identifier, use TLDevice.serialNumber once known.
 */
@property (strong, nonatomic, readonly) NSString *deviceIdentifier;

/// The string representation of the generic device type, for example "ThermaPen Blue"
@property (strong, nonatomic, readonly) NSString *deviceTypeName;

/**
 * @brief Array of TLSensor objects representing the sensors attached to the device
 *
 * Note, will not be populated until TLDevice.ready is set to YES
 */
@property (strong, nonatomic, readonly) NSArray<id<TLSensor>> *sensors;

/**
 * @brief The last RSSI reported by the device
 *
 * @see TLDevice.updateRSSI
 */
@property (strong, nonatomic, readonly) NSNumber *rssi;

/**
 *@brief Current battery level.
 *
 * For all devices except the DishTemp Blue, this is a notional percentage of full charge. For the DishTemp Blue device, which reports battery level in a different way,
 * this attribute should be ignored.
 */
@property (assign, nonatomic, readonly) NSInteger batteryLevel;

/**
 * @brief The battery warning level.
 *
 * Different devices have different battery types, with different discharge characteristics. There is therefore no single rule that correlates .batteryLevel with the need to replace.
 * This method has been provided to give the most reliable indication available of battery condition, and the value returned will in general reflect the battery condition icon on
 * the device's display, if it has one.
 */
@property (assign, nonatomic, readonly) TLBatteryWarningLevel batteryWarningLevel;

/// The connection state of the device
@property (assign, nonatomic, readonly) TLDeviceConnectionState connectionState;

/// <b>(Cloud Devices Only)"</b> Returns the device's next transmission time. Not relevant to this release of ThermaLib
@property (nonatomic, readonly) NSDate * nextTransmissionTime;

/// <b>(Cloud Devices Only)"</b> Returns the device's last transmission time. Not relevant to this release of ThermaLib
@property (nonatomic, readonly) NSDate * lastTransmissionTime;

/// <b>(Cloud Devices Only)"</b> Returns the time the device's settings were last changed. Not relevant to this release of ThermaLib
@property (nonatomic, readonly) NSDate * settingsLastChangedTime;

/// Whether the device is ready. Implies that the device is connected and all settings have been read and processed. A device's attributes should only be regarded as up to date and reliable if this attribute is YES.
@property (assign, nonatomic, readonly, getter=isReady) BOOL ready;

/// Whether the user has requested that the device be disconnected, to contrast with unexpected disconnections
@property (assign, nonatomic, readonly) BOOL userRequestedDisconnect;

/// whether the device is connected at the Bluetooth level. Note that even when a device is connected, the state of attributes presented by this API should be regarded as undefined if .ready is set to NO.
@property (assign, readonly, getter=isConnected) BOOL connected;

/// number of sensors the device can physically accommodate.
@property (assign, readonly) NSInteger maxSensorCount;

/// suppoerted commands. Array of NSNumber to be interpreted as TLDeviceCommandType
@property (strong, nonatomic, readonly) NSArray *supportedCommands;

/**
 * @brief the sensor at the given index
 *
 * @param index index of the sensor. <i>Note that index is 1-based, in contrast to the Android version of the library, which is 0-based.</i>
 */
- (id<TLSensor>)sensorAtIndex:(NSUInteger)index;

/**
 * @brief whether the given sensor is enabled
 *
 * @param index index of the sensor <i>Note that index is 1-based, in contrast to the Android version of the library, which is 0-based.</i>
 */
- (BOOL)isSensorEnabledAtIndex:(NSUInteger)index;

/// request that that the RSSI value be read from the device
- (void)updateRssi;

/**
 * @brief send a command to the device
 *
 * @param command command to send
 */
- (void)sendCommand:(TLDeviceCommandType)command;

/// Requests that all data is re-requested. This is an asynchronous call, which on completion will cause one of the notifications specified in ThermaLIb.h to be sent.
- (void)refresh;

#ifdef THERMALIB_CLOUD
/// sends settings that have not so far been sent. Only effective for WiFi devices - in other cases, property
/// settings are immediate.

- (void)commitSettings;
#endif

/**
 * @brief Resets a device by wiping any stored data in the sdk.
 * @deprecated Reserved for internal use only
 */
- (void)reset __deprecated_msg("Reserved for internal use only");


/**
 * @brief Check to see whether the device has a specific feature.
 *
 * @param feature The feature to check
 * @return BOOL if the device has the specific feature
 */
-(BOOL) hasFeature:(TLDeviceFeature) feature;

-(BOOL) isSupportedCommand:(TLDeviceCommandType) commandType;

/**
 * @brief (Deprecated) The temperature unit the device is using.
 *
 * Prefer TLDevice.temperatureDisplayUnit
 */
@property (assign, nonatomic) TLDeviceUnit unit;

/**
 * @brief The unit the device is using to display temperatures. The latest device ranges support mixed sensor types. This attribute is retained for backward compatibility, but will report the unit in which the device will report temperatures only.
 */
@property (assign, nonatomic) TLDeviceUnit temperatureDisplayUnit;

/**
 * @brief The interval between measurements recorded by the device (in seconds).
 *
 * Note: for DishTemp Blue devices (see {@link TLDeviceType}) the measurement interval is fixed at 1 second, and assigning to this attribute will have no effect.
 * For other Bluetooth LE devices the measurement and transmission intervals are locked together, so assigning or reading one will have the same
 * effect as assigning or reading the other.
 */
@property (assign, nonatomic) NSInteger measurementInterval;

/**
 * @brief The interval between transmissions from the device to the host (in seconds)
 *
 * Note: for DishTemp Blue devices (see {@link TLDeviceType}) the transmission interval may be set, but is defined as a write-only attribute by the device. Writing to the attribute
 * will have the expected effect, but reading it will return the value -1
 *
 * For other Bluetooth LE devices the measurement and transmission intervals are locked together, so assigning or reading one will have the same
 * effect as assigning or reading the other.
 *
 * For devices other than the DishTemp Blue, a measurement/transmission interval of 0 means don't transmit at a fixed interval. In this case measurements are obtained
 * by a) pressing a button on the unit, which will cause an iOS notification of type {@link ThermaLibNotificationReceivedNotificationName} to be delivered to the app,
 * or b) the app sending a command of type {@link TLDeviceCommandTypeMeasure} using {@link TLDevice.sendCommand:}
 */
@property (assign, nonatomic) NSInteger transmissionInterval;

/**
 * @brief The time internal for switching the device off (in minutes). Note that a value of 0 means that the device will not automatically switch itself off.
 *
 * Not all devices support this feature. See {@link TLDeviceFeatureAutoOff}, TLDevice.hasFeature:
 *
 */
@property (assign, nonatomic) NSInteger autoOffInterval;

/**
 * @brief The emissivity of the surface being measured, in the range [0.1, 1]. <i>Currently RayTemp Blue devices only</i>
 * @see {@link TLDeviceFeatureEmissivity}, TLDevice.hasFeature
 */
@property (assign, nonatomic) float emissivity;

#ifdef THERMALIB_CLOUD
/// the last settings reported by the device. Only used currently for cloud devices
@property (nonatomic, readonly) id<TLRemoteSettings> remoteSettings;
#endif

/**
 * @brief The current display unit for the given generic sensor type.
 *
 * The unit configured for display of readings of that generic type.
 *
 * <i>This does not affect the unit in which #reading is represented, which
 * is fixed for a given generic sensor type, i.e. for temperature sensors,
 * #reading will always be the temperature in degrees Celsius.</i>
 *
 * @param genericType The generic sensor type
 * @return TLDeviceUnit The display unit for the specified generic sensor type.
 */
-(TLDeviceUnit)displayUnitForGenericSensorType:(TLGenericSensorType)genericType;

/**
 * @brief Sets the unit for the given generic sensor type. (Currently alternative values are only available for temperature sensors.)
 *
 * This currently is used only for setting the Temperature unit.
 * @param genericType The generic sensor type
 * @param unit The unit for the specified generic sensor type.
 */
-(void)setDisplayUnitForGenericSensorType:(TLGenericSensorType)genericType
                                     unit:(TLDeviceUnit)unit;




@end
