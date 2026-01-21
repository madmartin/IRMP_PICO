Set statusled on IRMP Pico.  
For use in vdr-plugin-statusleds.

Usage:  
irmpstatusled [-d device] -s led_state

Examples:  
switch the statusled on:  irmpstatusled -d /dev/hidraw1 -s 1  
switch the statusled off: irmpstatusled -d /dev/hidraw1 -s 0  

put the udev rule from configuration into your udev rules directory, then you don't need to give a device  

vdr + vdr-plugin-statusleds + irmpstatusled:  
vdr -P'statusleds --irmpstatusled_path=/path/to/irmpstatusled'  
this will turn the led on, when vdr starts; it will turn the led off, when vdr stops; it will make the led blink during recording  
for systemd add a line to the vdr service ExecStop=/path/to/irmpstatusled -s 0  
