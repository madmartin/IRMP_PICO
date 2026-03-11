## Die vier Wege bei yaVDR:
REPORT_ID_IR -> irmplircd → lircd2uinput → /dev/input/eventX → eventlircd → Kodi/VDR und  
REPORT_ID_KBD -> /dev/input/eventX → eventlircd → Kodi/VDR sowie  
REPORT_ID_IR -> vdr-plugin-irmp -> VDR  
REPORT_ID_KBD -> vdr-plugin-irmp4kbd -> VDR  
Für VDR darf nur einer der vier Wege aktiviert sein.

Für den ersten Weg braucht man eine irmp.map. 
Für den zweiten Weg braucht man eine kbd.map und eine .evmap.  
Für den dritten Weg dürfen weder irmplircd noch eventlircd laufen, sondern nur vdr-plugin-irmp.  
Für den vierten Weg dürfen weder irmplircd noch eventlircd laufen, sondern nur vdr-plugin-irmp4kbd.  
Für Kodi braucht man bei Weg drei und vier eine kbd.map fürs eeprom und eine passende keymap für Kodi.  
