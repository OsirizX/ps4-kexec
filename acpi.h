/*
 * ps4-kexec - a kexec() implementation for Orbis OS / FreeBSD
 *
 * Copyright (C) 2015-2016 shuffle2 <godisgovernment@gmail.com>
 * Copyright (C) 2015-2016 Hector Martin "marcan" <marcan@marcan.st>
 *
 * This code is licensed to you under the 2-clause BSD license. See the LICENSE
 * file for more information.
 */

#ifndef ACPI_H
#define ACPI_H

#include "acpi_io.h"

#define PACKED __attribute__((packed))

typedef struct PACKED PCI_DEVICE {
    u32    vendorId : 16, deviceId : 16;
    u32    command : 16, status : 16;
    u32    revisionId : 8, progIF : 8, subclass : 8, classCode : 8;
    u32    cacheLineSize : 8, latencyTimer : 8, headerType : 8, BIST : 8;
    //SEE: https://wiki.osdev.org/PCI#Configuration_Space
} PCI_DEVICE;

typedef struct PACKED PCI_DEVICE_TYPE0 {
    struct PCI_DEVICE common;
    union {
    	struct {
		u32    bar0;
    		u32    bar1;
    		u32    bar2;
    		u32    bar3;
    		u32    bar4;
    		u32    bar5;
	};
	u32 bar[6];
    };
    u32    cardbusCISpointer;
    u32    subsystemVendorId : 16, subsystemId : 16;
    u32    expansionROMbaseAddress;
    u32    capabilitiesPointer : 8, reserved0 : 24;
    u32    reserved1;
    u32    interruptLine : 8,  interruptPIN : 8, minGrant : 8, maxLatency : 8;
    //SEE: https://wiki.osdev.org/PCI#Configuration_Space
} PCI_DEVICE_TYPE0; //sizeof(struct PCI_DEVICE_TYPE0)=0x40 bytes

static inline void udelaymsec(unsigned int umsec) {
    u64 later = rdtsc() + umsec;
    while (((s64)(later - rdtsc())) > 0);
}

void fix_acpi_tables(void *map_base, u64 phys_base);

#define PA_TO_DM(x) (((uintptr_t)x) | kern.dmap_base)

void disableMSI(u64 MSICapabilityRegAddr);
void disablePM(u64 PMCapabilityRegAddr);

#endif
