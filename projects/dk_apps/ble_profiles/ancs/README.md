BLE ANCS Client demo application {#ancs}
======================================================

## Overview

This application is a sample implementation for Apple Notification Center Service (ANCS) client.
It supports all the features of the Notification Consumer (NC) role provided by this service.

## Installation procedure

The project is located in the \b `projects/dk_apps/ble_profiles/ancs` folder.

To install the project follow the [General Installation and Debugging Procedure](@ref install_and_debug_procedure).

## Suggested configurable parameters

### Drop preexisting notifications

Upon connection the iOS device sends all pending notifications. By default, all of them are dropped
by the application and only notifications generated after the connection are processed. To also
process the notification events that were generated before the connection, set the following
configuration macro to 0.

~~~{.c}
#define CFG_DROP_PREEXISTING_NOTIFICATIONS      (1)
~~~

### Verbose logging

By default, the application will only print incoming notifications once all the data is received (attributes, application).
Verbose logging will enable more printouts for intermediate steps as they are being
executed, i.e. received notification information, reading attributes etc.

~~~{.c}
#define CFG_VERBOSE_LOG (0)
~~~

### Maximum length for "title" and "message" attributes

This configures the maximum number of received characters for the notification attributes "title" and "message".
It affects what is displayed as notification content.

~~~{.c}
#define CFG_TITLE_ATTRIBUTE_MAXLEN      (25)
#define CFG_MESSAGE_ATTRIBUTE_MAXLEN    (75)
~~~

### GPIO for K1 button

K1 button is used to trigger performing negative action on most recently received notification.
See section 'Manuual testing' for details.

Default value is suitable when running on ProDK rev. B and C for DA1468x or ProDK rev. A for
DA1469x or ProDK for DA1470x and GPIO's are defined during preprocessing.

~~~{sdk/config/boards/brd_prodk_da1469x.h}
/* KEY configuration section */
#define KEY1_PORT       (HW_GPIO_PORT_0)
#define KEY1_PIN        (HW_GPIO_PIN_6)
#define KEY1_MODE       (HW_GPIO_MODE_INPUT_PULLUP)
#define KEY1_FUNC       (HW_GPIO_FUNC_GPIO)
~~~

~~~{sdk/config/boards/brd_prodk_da14680.h}
/* KEY configuration section */
#define KEY1_PORT       (HW_GPIO_PORT_1)
#define KEY1_PIN        (HW_GPIO_PIN_6)
#define KEY1_MODE       (HW_GPIO_MODE_INPUT_PULLUP)
#define KEY1_FUNC       (HW_GPIO_FUNC_GPIO)
~~~

~~~{sdk/config/boards/brd_prodk_da1470x.h}
/* KEY configuration section */
#define KEY1_PORT       (HW_GPIO_PORT_1)
#define KEY1_PIN        (HW_GPIO_PIN_22)
#define KEY1_MODE       (HW_GPIO_MODE_INPUT_PULLUP)
#define KEY1_FUNC       (HW_GPIO_FUNC_GPIO)
~~~

### GPIO for K2 button (DA1470X only)

K2 button is used to trigger performing positive action on most recently received notification.

Default value is suitable when running on ProDK for DA1470x and GPIO's are defined during preprocessing.

~~~{sdk/config/boards/brd_prodk_da1470x.h}
/* KEY configuration section */
#define KEY2_PORT       (HW_GPIO_PORT_1)
#define KEY2_PIN        (HW_GPIO_PIN_23)
#define KEY2_MODE       (HW_GPIO_MODE_INPUT_PULLUP)
#define KEY2_FUNC       (HW_GPIO_FUNC_GPIO)
~~~

### Request timeout

Requests (either application or notification attributes) which take too long will be cancelled
automatically after specified time.

Default value is 10 seconds.

~~~{.c}
#define CFG_REQUEST_TIMEOUT_MS  (10000)
~~~

### Browse delay

A short delay is used before starting to browse for ANCS.

Default value is 1 second.

~~~{.c}
#define CFG_BROWSE_DELAY_MS  (1000)
~~~

## Manual testing

The application runs as Notification Consumer, thus it uses LE Peripheral role when started and starts
advertising. Advertising data contains Service Solicitation UUID for ANCS as defined by specification
(_7905f431-b5ce-4e99-a40f-4b1e122d00d0_) and device name (_Dialog ANCS Demo_) is located in
scan response.

Debug logs are output using serial port available when plafrom is connected to PC using USB2
connector (e.g. `/dev/ttyUSB0`).

1. Use iOS device for scan for devices and connect to _Dialog ANCS Demo_.
2. Due to security requirements of ANCS pairing will be triggered and should be accepted.
3. Once connected, any notification which already exist on iOS device will be retrieved and
   printed in logs.
4. Any new notification on iOS device will be retrieved and printed in logs from now on.
   Notifications can be created using various apps like Mail, Reminders, Calendars and many others.
5. K1 button can be used to perform so-called negative action on most recently received notification.
   This usually means that notification will be removed, but it depends on contents
   of notification.

Notification is printed in following form:

~~~
Notification from Reminders (com.apple.reminders)
        Category: Schedule
            Date: 20160127T125500
           Title: Reminder
         Message: sample reminder
~~~

All data is printed as received from iOS device, no additional processing is applied.

If verbose logging is enabled, some additional information will be also printed like "raw" events
received from iOS device.

## Known limitations

MTU values, connection parameters and device name are hardcoded at the moment, they can only be
modified by making changes in source code.
