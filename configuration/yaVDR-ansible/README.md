## The four ways in yaVDR:
REPORT_ID_IR -> irmplircd → lircd2uinput → /dev/input/eventX → eventlircd → Kodi/VDR and  
REPORT_ID_KBD -> /dev/input/eventX → eventlircd → Kodi/VDR and  
REPORT_ID_IR -> vdr-plugin-irmp -> VDR  
REPORT_ID_KBD -> vdr-plugin-irmp4kbd -> VDR  
Only one of the four paths may be activated for VDR.  

For the first way, you need an irmp.map.  
For the second way, you need a kbd.map and an .evmap.  
For the third way, neither irmplircd nor eventlircd should be running, only vdr-plugin-irmp.  
For the fourth way, neither irmplircd nor eventlircd should be running, only vdr-plugin-irmp4kbd.  
For Kodi with third or fourth way you need a kbd.map for the eeprom and a suitable keymap for Kodi.  
