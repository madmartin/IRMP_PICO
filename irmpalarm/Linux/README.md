Set alarm time on and get alarm time from IRMP Pico.
For use in VDRs shutdown script and commands.conf.

Usage:
irmpIRalarm [-d device] -s alarmtime -a

Examples:
set alarm time 1 hour ahead, 3600 sec: irmpIRalarm -d /dev/hidraw1 -s 3600
get alarm time: irmpIRalarm -d /dev/hidraw2 -a
set & get (136 years ahead ;-)): irmpIRalarm -d /dev/hidraw0 -s 0xFFFFFFFF -a

shutdown script (pointed to by the --shutdown line in vdr.conf):
irmpIRalarm [-d /dev/hidraw0] -s $2
irmpIRalarm [-d /dev/hidraw0] -s $(($2 -300))

commands.conf:
irmpIRalarm [-d /dev/hidraw2] -a

put the udev rule from configuration into your udev rules directory, then you don't need to give a device
