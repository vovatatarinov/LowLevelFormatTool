#include "InitBoot.h"
#include "int.h"
#include "mem.h"
#include "inter.h"
#include "disk.h"
#include "reboot.h"
#include "vga_font.h"
#include "vga.h"
#include "TextIO.h"
#include "keyboard.h"
#include "math.h"
#include "fpu.h"
#include "input.h"

static void printDiskParams(diskinfo* info) {
    print("\r\n\r\n********DISK params********\r\nInfo pack size: ");
    printNum(info->size);
    print("\r\nInfo flags: ");
    printNum(info->info_flags);
    print("\r\nCylinders: ");
    printNum(info->cyl);
    print("\r\nHeads: ");
    printNum(info->heads);
    print("\r\nSectors per track: ");
    printNum(info->secPerTrack);
    print("\r\nSectors: ");
    printNum(info->sectors);
    print("\r\nBytes per sector: ");
    printNum(info->bytePerSec);
    print("\r\nExtended disk params: ");
    printNum(info->EDD);
    print("\r\nDisk size: ");
    qword size = (info->bytePerSec) * (info->sectors);
    printNum(size);
}

static void fill00() {
    char* IOstr = defaultStr + bytePerSec;
    print("\r\nWe will format DISK with 0x00 bytes.\r\n");
    print("DISK number is ");
    printNum(disknum);
    resetDisk();
    diskinfo info;
    readDiskParams(&info);
    print("\r\nSectors: ");
    printNum(info.sectors);
    print("\r\nAre you sure? \r\nThis operation will destroy ALL DATA!\r\n[Type \"YES\" to continue.]> ");
    inputStr(IOstr);
    if (!cmpstr("YES", IOstr))
        return;
    for (int i = 0; i < bytePerSec; ++i)
        defaultStr[i] = 0x00;
    for (qword i = 0; i < info.sectors; ++i) {
        print("\r\nSector: ");
        printNum(i + 1);
        double p = (i + 1) / (double)info.sectors;
        p *= 100;
        int intp = p;
        print("    Formated: ");
        printNum(intp);
        print("%");
        writeSector(i);
    }
}

static void fillFF() {
    char* IOstr = defaultStr + bytePerSec;
    print("\r\nWe will format DISK with 0xFF bytes.\r\n");
    print("DISK number is ");
    printNum(disknum);
    resetDisk();
    diskinfo info;
    readDiskParams(&info);
    print("\r\nSectors: ");
    printNum(info.sectors);
    print("\r\nAre you sure? \r\nThis operation will destroy ALL DATA!\r\n[Type \"YES\" to continue.]> ");
    inputStr(IOstr);
    if (!cmpstr("YES", IOstr))
        return;
    for (int i = 0; i < bytePerSec; ++i)
        defaultStr[i] = 0xFF;
    for (qword i = 0; i < info.sectors; ++i) {
        print("\r\nSector: ");
        printNum(i + 1);
        double p = (i + 1) / (double)info.sectors;
        p *= 100;
        int intp = p;
        print("    Formated: ");
        printNum(intp);
        print("%");
        writeSector(i);
    }
}

static void terminal() {
    print("\r\nYou can\r\n1. Start 0x00 filling."
          "\r\n2. Start 0xFF filling."
          "\r\n3. Return back."
          "\r\n4. Restart machine."
          "\r\nInput number[default 3]: ");
    inputStr(defaultStr);
    if (cmpstr("", defaultStr) || cmpstr("3", defaultStr)) {
        asm volatile("jmp 0x0100"::"d"(disknum));
    }
    else if (cmpstr("1", defaultStr))
        fill00();
    else if (cmpstr("2", defaultStr))
        fillFF();
    else if (cmpstr("4", defaultStr))
        reboot();
    else
        print("\r\nSome error occur.");

}

extern void bootmain(void)
{
	disknum = getdisknum();
    vga_off();
    finit();
    print("Low level formating tool by Tatarinov, 2020.\r\n");
    print("\r\nWe use disk: ");
    printNum(disknum);
    print("\r\nYou can change the disk [Empty for default disk]: ");
    inputStr(defaultStr);
    if (!cmpstr("", defaultStr)) {
        disknum = atoi(defaultStr);
    }
    print("\r\nWe use disk: ");
    printNum(disknum);
    resetDisk();
    if (!checkExtendedDisk()) {
    	print("\r\nSorry. Disk error.\r\n[Press ENTER]");
    	inputStr(defaultStr);
        asm volatile("jmp 0x0100"::"d"(disknum));
    }
    diskinfo info; 
    readDiskParams(&info);
    bytePerSec = info.bytePerSec;
    printDiskParams(&info);
    
    while(1) {
        terminal();
    }

    return;
}
