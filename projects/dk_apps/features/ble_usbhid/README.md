HoGP Device with USB HID dongle {#ble_usbhid}
=============================================

## Overview

The `ble_usbhid_device` (HoGP Device) application implements a HoGP Device compliant with HoGP
specification and can be used with any BLE device supporting HoGP Host (either Boot Host or Report
Host), e.g. PC or a smartphone.

Once connected to HoGP Host, the HoGP Device application will act as a keyboard and mouse combo.

    ,-- DK ---------------.           ,-- PC/smartphone ----.
    |                     |           |                     |
    |  ble_usbhid_device  | <= BLE => |    any HoGP Host    |
    |                     |           |                     |
    `---------------------'           `---------------------'

The `ble_usbhid_dongle` (USB HID Dongle) application implements parts of HoGP Report Host role which
are necessary to work with HoGP Device implementation of `ble_usbhid_device`. Its purpose is to act
as a bridge between HoGP Device and a non-BLE HID host supporting USB HID host. It is a plug & play
solution which works only with specific, preconfigured HoGP Device.

    ,-- DK ---------------.           ,-- DK ---------------.           ,-- PC/smartphone ----.
    |                     |           |                     |           |                     |
    |  ble_usbhid_device  | <= BLE => |   ble_usb_dongle    | <= USB => |    non-BLE device   |
    |                     |           |                     |           |                     |
    `---------------------'           `---------------------'           `---------------------'

## Installation procedure

HoGP Device project is located in the \b `projects/dk_apps/features/ble_usbhid/ble_usbhid_device` folder.

USB HID Dongle project is located in the \b `projects/dk_apps/features/ble_usbhid/ble_usbhid_dongle` folder.

To install both projects follow the [General Installation and Debugging Procedure](@ref install_and_debug_procedure).


## Profile Tuning Suite (PTS) testing

The HoGP Device application can be tested with PTS as a HID Device.

The USB HID Dongle application can be tested with PTS as generic BLE device.


## Limitations

### Connection Setup

1. In order for the USB protocol to operate seamlessly, it is advised to connect the USB HID Dongle
   directly from the daughterboard to the host, and not from the JLink port of the DK's motherboard.

2. As a best practise for seamless USB testing, it is also advised to power the BLE application part
   of the tests through the DK's motherboard (both applications).
   This can be achieved by keeping the daughterboard mounted on the DK motherboard,
   regardless of the USB connection to the host.

### USB HID Dongle

The USB HID Dongle only works with a single compatible device. The address of this device is pre-programmed in the dongle.
This is due to following limitations:

1. The dongle is a non-interactive device, depriving the user the choice of a HoGP device to connect to.
   Having a pre-programmed device address, the connection process is as quick as possible; there is
   no need to scan for compatible devices prior to connection and also there is no conflict
   if other compatible devices exist in the neighborhood.

2. The dongle does not have a full HID parser and thus it cannot parse and understand reports received from
   either device or host. It acts only as a bridge passing reports from one side to another. This
   translates to using the same report map over the USB-connected and the BLE-connected device.
   This is achieved by hard-coding the report map of the dongle to match the HoGP device's report map.


## Manual testing

### HoGP Device only

After startup, the device starts directed advertising to bonded host, if any, and then switches to
undirected advertising. The undirected advertising is enabled for 180 seconds. To enable it again,
press K1 button on the DK.

The advertising data contains *HID Service* UUID and *Generic HID* appearance. The scan response
contains *Dialog HoGP Device* name.

To remove the bonding information from the device, reset the device while holding K1 button pressed.

Once connected, the device acts as a keyboard and mouse combo with the following features:
- mouse cursor movement is simulated in a rhomb-shaped pattern
- key press is simulated by sending press and release of the Num Lock key (LED state should change on
  other keyboards connected to the same host)
- D2 LED is synchronized with the Caps Lock state of the host (LED can be toggled by pressing Caps Lock
  key on other keyboards connected to the same host)

\note The Num Lock and Caps Lock states synchronization depends on the host. The behaviour as described
above can be observed with Windows and Linux hosts, while OSX hosts do not seem to properly synchronize the key
states.

Testing procedure:
1. Flash the `ble_usbhid_device` application as described above.
2. Reset the DK
3. The device starts advertising; use a compatible PC or smartphone to scan and connect to the device.
4. Due to security requirements (encryption required) the device sends *Security Request* after
   connection is established with the host, to initiate pairing and enable encryption.
5. The device actions should be visible on the host after pairing:
   - check that the mouse cursor is moving as expected
   - check that Num Lock LED toggles every 1 second on host
   - check that Caps Lock key toggles D2 LED on DK
6. Disconnect the device (e.g. reset the DK)
7. The host should reconnect with the device and encryption should be enabled immediately without
   needing to pair both devices again.


### USB HID Dongle with HoGP Device

The procedure to setup HoGP Device is the same as in **HoGP Device only** scenario.

The USB HID Dongle device does not require any user interaction. Once run, it constantly scans for the
predefined device and automatically connects, once the matching device is found. If the connected device
is compatible with the dongle, the security and configuration is handled automatically, and the device
transfers all HID traffic from/to the HoGP Device to/from the connected USB HID host.

The address of the HoGP device that will connect to the dongle is written in the dongle's
`NVMS_PARAM` partition (see usage [here](@ref nvparam_script)) at an offset address of `0x40`, in the following format:

     len | name
    -----+----------------------- 
       1 | address type
         |     0x00 = public
         |     0x01 = random
       6 | device address

Alternatively, assuming the `NVMS_PARAM` partition starts at `0x00700000`, the above address can be written using `cli_programmer`,
e.g. the following command will setup the dongle to work with the device using a public address `80:EA:CA:AA:AA:AA`:

    ./binaries/cli_programmer gdbserver write_oqspi_bytes 0x00700040 0x00 0xAA 0xAA 0xAA 0xca 0xea 0x80

If no address is found on the flash (or the address type is invalid), the default BD address is used.

Testing procedure:
1. Flash the applications `ble_usbhid_device` and `ble_usbhid_dongle` as described above.
   \warning Make sure both applications are built with the same SDK core code.
2. Setup the HoGP device's DK address on the dongle DK as described above (optional).
3. Connect the dongle DK Daughterboard via USB to a compatible host. It should be enumerated as HID device.
4. Reset the HoGP device DK
5. When D2 LED is on, this indicates that the dongle DK is successfully connected to the device DK.
6. The same behaviour as in **HoGP Device only** scenario should be observed and verified on the host, which is now connected to the dongle.
7. Reset either of devices and the connection should be established again automatically.

