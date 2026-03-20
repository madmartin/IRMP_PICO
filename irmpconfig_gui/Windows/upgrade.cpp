/*
 * Copyright (C) 2020 Joerg Riechardt
 *
 * Copyright (C) 2011  Black Sphere Technologies Ltd.
 * Originally written by Gareth McMullin <gareth@blacksphere.co.nz>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifdef WIN32
#   include <stdio.h>
#else
#   include <unistd.h>
#endif
#include "upgrade.h"
#include <algorithm>

#define LOAD_ADDRESS 0x8002000

int upgrade(const char* firmwarefile, char* print, char* printcollect, FXGUISignal* guisignal);

void Upgrade::set_firmwarefile(const char* pfirmwarefile) {
	firmwarefile = pfirmwarefile;
}

void Upgrade::set_print(char* pprint) {
	print = pprint;
}

void Upgrade::set_printcollect(char* pprintcollect) {
	printcollect = pprintcollect;
}

void Upgrade::set_signal(FXGUISignal* pguisignal) {
	guisignal = pguisignal;
}

FXint Upgrade::run() {
	upgrade(firmwarefile, print, printcollect, guisignal);
  return 0;
}

struct libusb_device * find_dev()
{
	struct libusb_device *dev, **devs, *found = NULL;
	int ret;
	ret = libusb_get_device_list(NULL, &devs);
	if(ret < 0) {
		printf("error getting device list(): %s\n", libusb_error_name(ret));
		return NULL;
	}

	for (int i=0; (dev=devs[i]) != NULL; i++) {
		struct libusb_device_descriptor desc;
		if(libusb_get_device_descriptor(dev, &desc) < 0) {
			printf("couldn't get device descriptor\n");
			continue;
		}

		/* Check for vendor ID */
		if (desc.idVendor != 0x2e8a)
			continue;

		/* Check for product ID */
		if (desc.idProduct == 0x0003) {
			libusb_ref_device(dev);
			found = dev;
			break;
		}
	}

	libusb_free_device_list(devs, 1);
	return found;
}

struct usb_dfu_descriptor {
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint8_t bmAttributes;
	uint16_t wDetachTimeout;
	uint16_t wTransferSize;
	uint16_t bcdDFUVersion;
} __attribute__ ((__packed__)) ;

libusb_device_handle * get_dfu_interface(struct libusb_device *dev, uint16_t *wTransferSize)
{
	int ret;
	struct libusb_interface_descriptor *iface;
	libusb_device_handle *handle = NULL;
	struct libusb_config_descriptor *config;

	// bNumConfigurations = 1, bNumInterfaces = 1, num_altsetting = 1
	if(libusb_get_config_descriptor(dev, 0, &config) != LIBUSB_SUCCESS) {
		printf("couldn't get config descriptor\n");
		return NULL;
	}
	iface = (libusb_interface_descriptor*)&config->interface[0].altsetting[0];
	if((iface->bInterfaceClass == 0xFE) && (iface->bInterfaceSubClass = 1)) { // for safety only
		struct usb_dfu_descriptor *dfu_function = (struct usb_dfu_descriptor*)iface->extra;
		*wTransferSize = dfu_function->wTransferSize;
		ret = libusb_open(dev, &handle);
		if(ret < 0) {
			printf("error opening device: %s\n", libusb_error_name(ret));
			libusb_unref_device(dev);
			goto error;
		}
		ret = libusb_claim_interface(handle, 0);
		if (ret != LIBUSB_SUCCESS) {
			printf("error claiming interface: %s\n", libusb_error_name(ret));
			libusb_close(handle);
			handle = NULL;
			goto error;
		}
	}
error:
	libusb_free_config_descriptor(config);
	return handle;
}

uint8_t * get_firmware(const char *firmwarefile, int *firmwareSize, char* print)
{
	FILE *fpFirmware;
	uint8_t *fw_buf;
	char printbuf[512];

	fpFirmware = fopen (firmwarefile, "rb");
	if(fpFirmware == NULL) {
		printf("error opening firmware file: %s\n",firmwarefile);
		return NULL;
	} else {
		printf("opened firmware file %s\n", firmwarefile);
#ifndef WIN32
		sprintf(print, "opened firmware file %s\n", firmwarefile);
#else
		FXCP1252Codec codec;
		FXString utfstring=codec.mb2utf(firmwarefile);
		sprintf(print, "opened firmware file %s\n", utfstring.text());
#endif
	}

	if((fseek(fpFirmware, 0, SEEK_END) != 0) || ((*firmwareSize = ftell(fpFirmware)) < 0) ||
							(fseek(fpFirmware, 0, SEEK_SET) != 0)) {
		printf("error determining firmware size\n");
		fclose(fpFirmware);
		return NULL;
	}

	fw_buf = (uint8_t*)malloc(*firmwareSize);
	if (fw_buf == NULL) {
		fclose(fpFirmware);
		printf("error allocating memory\n");
		return NULL;
	}

	if(fread(fw_buf,*firmwareSize,1,fpFirmware) != 1) {
		printf("read firmware error\n");
		fclose(fpFirmware);
		free(fw_buf);
		return NULL;
	} else {
		printf("read %d bytes of firmware\n", *firmwareSize);
		sprintf(printbuf, "read %d bytes of firmware\n", *firmwareSize);
		strcat(print, printbuf);
	}

	fclose(fpFirmware);
	return fw_buf;
}

int upgrade(const char* firmwarefile, char* print, char* printcollect, FXGUISignal* guisignal)
{
#ifdef WIN32
	sprintf(print, "The Pico is switched into mass storage device mode.\nIn your file manager drag and drop the firmware file *.uf2 onto the newly appeared mass storage device.\nThen press buttons 'Re-Scan devices' and 'Connect'.\n");
	strcat(printcollect, print);
	guisignal->signal();
	//Sleep(2000);

	//sprintf(print, "C:/msys64/home/Jörg/irmpconfig_gui/picotool load -v -x %s", firmwarefile);
	//sprintf(print, "/c/msys64/home/Jörg/irmpconfig_gui/picotool.exe");
	//sprintf(print, "C:\\msys64\\home\\Jörg\\irmpconfig_gui\\picotool.exe"); // funktioniert in cmd, aber nicht hier
	/*strcat(printcollect, "print");
	guisignal->signal();

	int status = system(print);
	printf("status: %s\n", status ? "error" : "OK");
	if (status != 0) return 0;

	sprintf(print, "\n");
	strcat(printcollect, print);
	guisignal->signal();

	sprintf(print, "=== Firmware Upgrade successful! ===\n");
	strcat(printcollect, print);
	guisignal->signal();*/

	return 1;
#else
	usleep(2000000);

	sprintf(print, "/usr/local/bin/picotool load -v -x %s", firmwarefile);
	strcat(printcollect, print);
	guisignal->signal();

	int status = system(print);
	printf("status: %s\n", status ? "error" : "OK");
	if (status != 0) return 0;

	sprintf(print, "\n");
	strcat(printcollect, print);
	guisignal->signal();


	sprintf(print, "=== Firmware Upgrade successful! ===\n");
	strcat(printcollect, print);
	guisignal->signal();

	return 1;
#endif
}
