//
//  FCUUID.h
//
//  Created by Fabio Caccamo on 26/06/14.
//  Copyright © 2016 Fabio Caccamo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

extern NSString *const FCUUIDsOfUserDevicesDidChangeNotification;

@interface FCUUID : NSObject
{
    NSMutableDictionary *_uuidForKey;
    NSString *_uuidForSession;
    NSString *_uuidForInstallation;
    NSString *_uuidForVendor;
    NSString *_uuidForDevice;
    NSString *_uuidsOfUserDevices;
    BOOL _uuidsOfUserDevices_iCloudAvailable;
    NSString *_sharedAccessGroup;
    NSString *_uuidForDeviceShared;
    BOOL _thisDeviceOnly;
}

+(NSString *)uuid;
+(NSString *)uuidForKey:(id<NSCopying>)key;
+(NSString *)uuidForSession;
+(NSString *)uuidForInstallation;
+(NSString *)uuidForVendor;
+(NSString *)uuidForDevice;
+(NSString *)uuidForDeviceMigratingValue:(NSString *)value commitMigration:(BOOL)commitMigration;
+(NSString *)uuidForDeviceMigratingValueForKey:(NSString *)key commitMigration:(BOOL)commitMigration;
+(NSString *)uuidForDeviceMigratingValueForKey:(NSString *)key service:(NSString *)service commitMigration:(BOOL)commitMigration;
+(NSString *)uuidForDeviceMigratingValueForKey:(NSString *)key service:(NSString *)service accessGroup:(NSString *)accessGroup commitMigration:(BOOL)commitMigration;
+(NSArray *)uuidsOfUserDevices;
+(NSArray *)uuidsOfUserDevicesExcludingCurrentDevice;

+(BOOL)uuidValueIsValid:(NSString *)uuidValue;

// Shared device UUID across multiple apps using a shared keychain access group.
// Both apps must have the same Keychain Sharing entitlement with a matching access group.
// Call setSharedKeychainAccessGroup: before using any shared UUID methods.

// When YES, device UUIDs (uuidForDevice and uuidForDeviceShared) are stored with
// kSecAttrAccessibleAfterFirstUnlockThisDeviceOnly, preventing them from being
// copied to other devices via backup or migration. Defaults to NO.
// In this mode the NSUserDefaults copy of uuidForDevice is read only while the keychain
// cannot be read (e.g. background launch before the first unlock after a reboot), never
// when the keychain item is absent. Device UUID getters can return nil while the keychain
// cannot be read and no local copy exists; nothing is cached or written in that state.
// Call before first UUID access.
+(void)setThisDeviceOnly:(BOOL)thisDeviceOnly;

// Configures the shared keychain access group used for cross-app UUID sharing.
+(void)setSharedKeychainAccessGroup:(NSString *)accessGroup;

// Returns the existing shared device UUID, or nil if none has been created yet.
// Always reads fresh from the keychain (no caching), so it reflects writes from other apps.
+(NSString *)existingSharedDeviceUUID;

// Returns the shared device UUID, creating a new one if none exists.
+(NSString *)uuidForDeviceShared;

// Migrates a value to the shared device UUID ONLY if no shared UUID exists yet.
// If a shared UUID already exists, it is returned unchanged.
// Returns the resulting shared device UUID.
+(NSString *)uuidForDeviceSharedMigratingValue:(NSString *)value;

@end