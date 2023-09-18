//
//  ThermaLib.h
//  ThermaLib
//
//  Copyright © 2016 Electronic Temperature Instruments Limited. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "TLDevice.h"


// The below use @param documentors for clarity to document members of the corresponding NSNotification object.
// the pragmas are to eliminate the warnings this non-standard use of @param would otherwise generate
//
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"

/**
 * @brief Notification that a new device is discovered during a scan.
 * @param object The {@link TLDevice} that was discovered.
 * @param userInfo NSDictionary containing:
 *
 * Key           | Value
 * ------------- | -------------
 * ThermaLibNotificationTimestampKey  | Notification timestamp as an NSDate *
 */
FOUNDATION_EXPORT NSString *const ThermaLibNewDeviceFoundNotificationName;

/**
 * @brief Notification that the device sent a protocol notification.
 * @param object The {@link TLDevice.h TLDevice} that sent the notification.
 * @param userInfo NSDictionary containing:
 *
 * Key           | Value
 * ------------- | -------------
 * ThermaLibNotificationTimestampKey  | Notification timestamp as an NSDate *
 * ThermaLibNotificationReceivedNotificationTypeKey  | Notification timestamp as an NSDate *
 */
FOUNDATION_EXPORT NSString *const ThermaLibNotificationReceivedNotificationName;


/**
 * @brief User info dictionary key for any notifications with a timestamp.
 *
 * This is sent with all notifications and is used in notification's userInfo dictionary. This key identifies the value
 * holds the timestamp. The timestamp is represented by an NSDate *.
 * notification / reading was sent.
 **/
FOUNDATION_EXPORT NSString *const ThermaLibNotificationTimestampKey;

/**
 * @brief User info dictionary key for the TLDeviceNotificationType.
 *
 * @details This is used in notification's userInfo dictionary for ThermaLibNotificationReceivedNotificationName
 * @see ThermaLibNotificationReceivedNotificationName
 */
FOUNDATION_EXPORT NSString *const ThermaLibNotificationReceivedNotificationTypeKey;

/**
 * @brief User info dictionary key for TLTransport.
 *
 * @details Used where the {@link TLTransport} is passed in the userInfo NSDictionary as an NSNumber wrapping the TLTransport as an NSInteger
 */
FOUNDATION_EXPORT NSString *const ThermaLibNotificationTransportTypeKey;

/**
 * @brief User info dictionary key for Service Reachability.
 *
 * @details Used where the service reachability is passed in the userInfo NSDictionary as an NSNumber wrapping a BOOL value
 */
FOUNDATION_EXPORT NSString *const ThermaLibNotificationServiceReachabilityKey;

/**
 * @brief User info dictionary key for Failure reason text
 *
 * @details Used whereever a textual reason is expected in the userInfo of the notification
 */
FOUNDATION_EXPORT NSString *const ThermaLibNotificationFailureReasonKey;

/**
 * @brief Notification that a device sent battery level notification
 *
 * @param object The {@link TLDevice.h TLDevice} that sent the notification.
 * @param userInfo NSDictionary containing:
 *
 * Key           | Value
 * ------------- | -------------
 * ThermaLibNotificationTimestampKey  | Notification timestamp as an NSDate *
 *
 */
FOUNDATION_EXPORT NSString *const ThermaLibBatteryLevelNotificationName;

/**
 * @brief Notification that an update was received for the device
 *
 * @details This may be the result of a read request or a write request
 * @param object The {@link TLDevice.h TLDevice} that was updated.
 * @param userInfo NSDictionary with keys and values:
 *
 * Key           | Value
 * ------------- | -------------
 * ThermaLibNotificationTimestampKey  | Notification timestamp as an NSDate *
 */
FOUNDATION_EXPORT NSString *const ThermaLibDeviceUpdatedNotificationName;


/**
 * @brief Notification of device disconnection
 *
 * @param object The {@link TLDevice.h TLDevice} that was disconnected.
 *              NOTE that after disconnection,no information that would normally require a connection,
 *              including the serial number, will be accessible, so any information required after
 *              disconnection must be cached by the client. {@link TLDevice#deviceName} will be preserved.
 * @param userInfo NSDictionary containing:
 *
 * Key           | Value
 * ------------- | -------------
 * ThermaLibNotificationTimestampKey  | Notification timestamp as an NSDate *
 * ThermaLibDeviceDisconnectionNotificationReasonKey  | NSNumber whose integerValue is a {@link TLDeviceDisconnectionReason}
 */
FOUNDATION_EXPORT NSString *const ThermaLibDeviceDisconnectionNotificationName;


/**
 * @brief User info dictionary key for the reason for the device disconnection.
 *
 * @details This is used as a key in the notification's userInfo dictionary for ThermaLibDeviceDisconnectionNotificationName.
 *      The corresponding value is an NSNumber whose integerValue is eqquivalent to a {@link TLDeviceDisconnectionReason}
 * @see ThermaLibDeviceDisconnectionNotificationName
 **/
FOUNDATION_EXPORT NSString *const ThermaLibDeviceDisconnectionNotificationReasonKey;

/**
 * @brief Notification of the completion of a service connection request..
 *
 * @param object an NSString * containing the key to be used in subsequent #requestAccessToDevice calls. Note that
 * this should be persisted, for example via NSUserDefaults, and subsequently reused in calls to #connectToService,
 * if access to device is to be persistent between client app sessions. If the connection failed, or a key is not required for this transport, this will be nil.
 * NB This notification does not say which {@link TLTransport} it refers to.
 *
 * For multiple-transport usages, listen instead for {@link ThermaLibServiceConnectionSucceededNotificationName},
 * {@link ThermaLibServiceConnectionFailedNotificationName}
 *
 * @param userInfo NSDictionary, only present if the connection request failed, containing:
 *
 * Key                                      | Value
 * ---------------------------------------- | -------------
 * ThermaLibNotificationFailureReasonKey    | an NSString * with a textual description of the reason for failure. May be nil if a reason cannot be supplied.
 **/
FOUNDATION_EXPORT NSString *const ThermaLibServiceConnectedNotificationName;

/**
 * @brief Notification of the result of a service connection failure.
 *
 * @param object If successful, and the request is to a service that requires a key, this be an NSString contraining the key to be used in subsequent #requestAccessToDevice calls. Note that
 * this should be persisted, for example via NSUserDefaults, and subsequently reused in calls to #connectToService, Otherwise, this will be nil. *
 * @param userInfo NSDictionary containing:
 *
 * Key                                      | Value
 * ---------------------------------------- | -------------
 * ThermaLibNotificationTransportTypeKey    | NSNumber * wrapping {@link TLTransport} as an NSInteger
 * ThermaLibNotificationFailureReasonKey    | an NSString * with a textual description of the reason for failure. May be nil if a reason cannot be supplied
 **/
FOUNDATION_EXPORT NSString *const ThermaLibServiceConnectionFailedNotificationName;

/**
 * @brief Notification of the result of a service connection success.
 *
 * @param object if request is to a service that requires a key, this be an NSString contraining the key to be used in subsequent #requestAccessToDevice calls. Note that
 * this should be persisted, for example via NSUserDefaults, and subsequently reused in calls to #connectToService
 * @param userInfo NSDictionary containing:
 *
 * Key                                      | Value
 * ---------------------------------------- | -------------
 * ThermaLibNotificationTransportTypeKey    | NSNumber * wrapping {@link TLTransport} as an NSInteger
 **/
FOUNDATION_EXPORT NSString *const ThermaLibServiceConnectionSucceededNotificationName;

/**
 * @brief Notification that a service's reachability has changed.
 *
 * @param object unused
 * @param userInfo NSDictionary containing:
 *
 * Key                                      | Value
 * ---------------------------------------- | -------------
 * ThermaLibNotificationTimestampKey        | Notification timestamp as an NSDate *
 * ThermaLibNotificationTransportTypeKey    | NSNumber * wrapping {@link TLTransport} as an NSInteger
 * ThermaLibNotificationReachabilityKey     | NSNumber * wrapping new reachability as a BOOL
 */
FOUNDATION_EXPORT NSString *const ThermaLibServiceReachabilityChangedNotificationName;

/**
 * @brief Notification that a device was deleted.
 *
 * @param object The {@link TLDevice.h TLDevice} that was deleted.
 * @param userInfo NSDictionary containing:
 *
 * Key           | Value
 * ------------- | -------------
 * ThermaLibNotificationTimestampKey  | Notification timestamp as an NSDate *
 */
FOUNDATION_EXPORT NSString *const ThermaLibDeviceDeletedNotificationName;

/**
 * @brief Notification that the RSSI value for a device has been updated.
 *
 * @details The new level can be read from the device object sent with the notification.
 * @param object The {@link TLDevice.h TLDevice} that sent the updated value.
 * @param userInfo NSDictionary containing:
 *
 * Key           | Value
 * ------------- | -------------
 * ThermaLibNotificationTimestampKey  | Notification timestamp as an NSDate *
 * ThermaLibRSSINotificationKey | the RSSI value as an NSNumber *
 */

FOUNDATION_EXPORT NSString *const ThermaLibRSSINotificationName;

/**
 * @brief User info dictionary key for the new RSSI value.
 *
 * @details This is used in notification's userInfo dictionary for ThermaLibRSSINotificationName
 * @see ThermaLibRSSINotificationName
 **/
FOUNDATION_EXPORT NSString *const ThermaLibRSSINotificationKey;

/**
 * @brief Notification that an updated sensor reading was received.
 *
 * @param object The {@link TLSensor.h TLSensor} whose reading was updated.
 * @param userInfo NSDictionary containing:
 *
 * Key           | Value
 * ------------- | -------------
 * ThermaLibNotificationTimestampKey  | Notification timestamp as an NSDate *
 */
FOUNDATION_EXPORT NSString *const ThermaLibSensorUpdatedNotificationName;

/**
 * @brief Notification that a scan was completed
 *
 * @param object not used
 * @param userInfo NSDictionary containing:
 *
 * Key           | Value
 * ------------- | -------------
 * ThermaLibNotificationTransportTypeKey  | Transport type of the completed scan, as an NSNumber (->NSInteger)
 */
FOUNDATION_EXPORT NSString *const ThermaLibScanCompletedNotificationName;

#pragma clang diagnostic pop

/**
 * @brief The `ThermaLib` class is the main access point for the library
 *
 */
@interface ThermaLib : NSObject

/// singleton accessor
+ (instancetype)sharedInstance;

/**
 * @brief ThermaLib version
 *
 * @return the version string for this version of the library. May contain arbitrary characters.
 */
-(NSString *) versionNumber;

/// Current bluetooth availability
- (BOOL)isBluetoothAvailable;

/// Start scan for ThermaQ devices
- (void)startDeviceScan;

/**
 * @brief Start restricted scan
 *
 * starts a device scan restricted to devices of a given transport, for example
 * only Bluetooth LE devices, or only Cloud Service devices.
 *
 * @param transport only scan for devices that communicate over this transport
 */
-(void)startDeviceScanWithTransport: (TLTransport)transport;

/**
 * @brief Start restricted scan and discover devices cached within iOS
 *
 * starts a device scan restricted to devices of a given transport, and optionally
 * discovers devices with which iOS has cached connections.
 *
 * @param transport only scan for devices that communicate over this transport
 * @param retrieveSystemConnections if YES then will additionally discover devices with which
 *          iOS has a cached connection with. Currently this parameter only has an effect for
 *          Bluetooth LE devices (Except the DishTemp Blue).
 *          (iOS uses a shared connection architecture, and so be aware that
 *          devices retrieved in this way may be connected to by other apps at the same time.)
 */
-(void)startDeviceScanWithTransport: (TLTransport)transport retrieveSystemConnections:(BOOL)retrieveSystemConnections;

/// Stops all running scans
- (void)stopDeviceScan;

/**
 * @brief ThermaLib's list of known-about devices
 */
- (NSArray<id<TLDevice>> *)deviceList;

/**
 * @brief The list of currently-supported transports
 */
- (NSArray *) supportedTransports;

/**
 * Sets the list of supported transports. This would normally be called once only, before
 * ThermaLib is used for the first time.
 */
- (void) setSupportedTransports:(NSArray *) transports;

/// Checks whether the given transport is supported
- (BOOL) isTransportSupported:(TLTransport) transport;

/// The number of devices in ThermaLib's list of known devices.
- (int) deviceCount;

/// The number of devices of a given transport type in ThermaLib's list
- (int) deviceCountForTransport:(TLTransport) transport;

/// The number of devices in ThermaLib's list that are in a given connection state
- (int) deviceCountForConnectionState:(enum TLDeviceConnectionState) connectionState;

/// The number of devices in ThermaLib's list of a given transport and in a given connection state.
- (int) deviceCountForConnectionState:(enum TLDeviceConnectionState) connectionState
                            transport:(TLTransport) transport;

/**
 * @brief search for a device of a given identifier in ThermaLib's list.
 *
 * @param identifier The identifier to search for
 * @return The device if found in ThermaLib's list, otherwise nil.
 * @deprecated Since identifiers are only guaranteed to be unique for a given {@link TLTransport},
 * use #deviceWithIdentifier:transport: instead.
 */
- (id<TLDevice>)deviceWithIdentifier:(NSString *)identifier __attribute__((deprecated));

/**
 * @brief search for a device of a given identifier and transport type in ThermaLib's list.
 *
 * @param identifier The identifier to search for
 * @param transport the transport.
 *
 * @return the TLDevice object if it exists, otherwise nil
 */
- (id<TLDevice>)deviceWithIdentifier:(NSString *)identifier transport:(TLTransport)transport;

/**
 * @brief Request connection to a device for reading data and changing settings.
 *
 * @param device The device to connect to
 */
- (void)connectToDevice:(id<TLDevice>)device;

/**
 * @brief Request disconnection from a device
 *
 * @param device The device to disconnect from
 */
- (void)disconectFromDevice:(id<TLDevice>)device;

/// Sublist of #deviceList containing only those that are connected
- (NSArray<id<TLDevice>> *)connectedDevices;

/**
 * @brief Removes a device from the list of discovered devices
 *
 * The device will be re-added if it is rediscovered by a subsequent scan.
 *
 * @param device The device to remove
 */
- (void)removeDevice:(id<TLDevice>)device;

/**
 * @brief Removes all devices from the list of discovered devices
 *
 * Equivalent to calling {@link removeDevice} for all discovered devices
 *
 * @param device The device to remove
 */
- (void)removeAllDevices;

/**
 * @brief Tests the reachability of a service. (Cloud devices only)
 * @param transport transport type to test
 * 
 * @return true if the service is reachable (say, via the internet) or the transport does
 * not require a service connection (such as Bluetooth LE). Otherwise returns false.
 */
-(BOOL) isServiceReachableForTransport:(TLTransport) transport;

/**
 * @brief Requests that a connection be established for the service associated with
 * the given transport.
 *
 * @param transport the transport to be connected.
 * @param appKey the key to use to connect. If this is nil, a new key will be allocated internally.
 * This is an asynchronous call.
 *
 */
-(void)connectToService:(TLTransport) transport usingKey:(NSString *)appKey;


/**
 * @brief Create a TLDevice object with the given name, identifier and transport type.
 * @param name the name to be associated with the newly-created device
 * @param identifier the identifier for the new device. (Device identifiers are unique for a given transport type
 * @param transport the transport type
 *
 * @return the newly created device, or nil on failure, for example if a device object already exists with the
 *          same identifier and transport
 */
- (id<TLDevice>) createDeviceWithName:(NSString *)name identifier:(NSString *)identifier transport:(TLTransport) transport;


/**
 * @brief tests whether the service is connected for a given transport. 
 *
 * @param transport The transport type
 */
-(BOOL) isServiceConnected: (TLTransport)transport;

@end

#ifdef THERMALIB_CLOUD
#import "ThermaLib_Cloud.h"
#endif

#ifdef THERMALIB_MONITOR
#import "ThermaLib_Monitor.h"
#endif
