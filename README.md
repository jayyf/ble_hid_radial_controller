# ble_hid_radial_controller
New ble hid device which is micorsoft defined in win10. The protocol is in this link
https://docs.microsoft.com/zh-cn/windows-hardware/design/component-guidelines/radial-controller-sample-report-descriptors

# Prerequisites
1. The project is based on SDK 12.3.0 ble_app_hids_keyboard demo.
2. SD: S130 2.0.1

# Setting up repository
1. Copy this directory to xx\nRF5_SDK_12.3.0_d7731ad\examples\ble_peripheral\.
2. Build and download to PCA10028 board.
3. Turn on win10 PC, and connect to the ble hid device.
4. Press the button 0, the PC would display the wheel if connected successfully.
