configure and monitor IRMP Pico

Usage:
irmpconfig [/dev/hidraw1]

program and read the eeprom (wakeups, macros, irdata, keys, repeat and capabilities)
reset wakeups, macros, irdata, keys, repeat, alarm and eeprom
set and get the alarm
reboot the device
send IR
monitor (read) IRMP Pico, stop with ^C

put the udev rule from irmplircd into your udev rules directory, then you don't need to give a device
