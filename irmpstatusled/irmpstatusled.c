/**********************************************************************************************************  
    irmpstatusled: switch statusled on/off on IRMP Pico

    Copyright (C) 2014-2024 Joerg Riechardt

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <unistd.h>
#include <sys/un.h>
#include <errno.h>
#include <fcntl.h>

enum access {
	ACC_GET,
	ACC_SET,
	ACC_RESET
};

enum command {
	CMD_CAPS,
	CMD_ALARM,
	CMD_IRDATA,
	CMD_KEY,
	CMD_WAKE,
	CMD_REBOOT,
	CMD_IRDATA_REMOTE,
	CMD_WAKE_REMOTE,
	CMD_REPEAT,
	CMD_EEPROM_RESET,
	CMD_EEPROM_COMMIT,
	CMD_EEPROM_GET_RAW,
	CMD_HID_TEST,
	CMD_STATUSLED,
	CMD_EMIT,
	CMD_NEOPIXEL,
	CMD_MACRO,
	CMD_MACRO_REMOTE,
};

enum status {
	STAT_CMD,
	STAT_SUCCESS,
	STAT_FAILURE
};

enum report_id {
	REPORT_ID_IR = 1,
	REPORT_ID_CONFIG_IN = 2,
	REPORT_ID_CONFIG_OUT = 3,
	REPORT_ID_KBD = 4
};

static int irmpfd = -1;
uint8_t inBuf[64];
uint8_t outBuf[64];

static bool open_irmp(const char *devicename) {
	irmpfd = open(devicename, O_RDWR);
	if (irmpfd == -1) {
		printf("error opening irmp device: %s\n",strerror(errno));
		return false;
	}
	//printf("opened irmp device\n");
	return true;
}

static void read_irmp() {
	int retVal;
	retVal = read(irmpfd, inBuf, sizeof(inBuf));
	if (retVal < 0) {
	    printf("read error\n");
        } /*else {
                printf("read %d bytes:\n\t", retVal);
                for (int i = 0; i < retVal; i++)
                        printf("%02hhx ", inBuf[i]);
                puts("\n");
        }*/
} 

static void write_irmp() {
	int retVal;
	retVal = write(irmpfd, outBuf, sizeof(outBuf));
	if (retVal < 0) {
	    printf("write error\n");
        } /*else {
                printf("written %d bytes:\n\t", retVal);
                for (int i = 0; i < retVal; i++)
                        printf("%02hhx ", outBuf[i]);
                puts("\n");
        }*/
}

int main(int argc, char *argv[]) {
	
	uint8_t led_state;
	int opt = 0;
	char *dvalue = NULL;
	char *svalue = NULL;
	
	while ((opt = getopt(argc, argv, "d:s:")) != -1) {
	    switch (opt) {
	    case 'd':
		dvalue = optarg;
		break;
	    case 's':
		svalue = optarg;
		break;
	    default:
		break;
	    }
	}

	open_irmp(dvalue != NULL ? dvalue : "/dev/irmp_pico");
        outBuf[0] = REPORT_ID_CONFIG_OUT;
	outBuf[1] = STAT_CMD;

	if (svalue != NULL) {
	    outBuf[2] = ACC_SET;
	    outBuf[3] = CMD_STATUSLED;
	    led_state = strtoul(svalue, NULL, 0);
	    outBuf[4] = led_state;
	    write_irmp();
	    usleep(3000);
	    read_irmp();
	    while (inBuf[0] == REPORT_ID_KBD || inBuf[0] == REPORT_ID_IR)
		read_irmp();
	}
	
	if (irmpfd >= 0) close(irmpfd);
	return 0;
}
