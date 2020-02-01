#ifndef DISK_H
#define DISK_H 
byte disknum;
word bytePerSec;

typedef struct diskinfo {
word size;
word info_flags;
dword cyl;
dword heads;
dword secPerTrack;
qword sectors;
word bytePerSec;
dword EDD;
} diskinfo;

typedef struct dapack {
    //EXAMPLE USAGE OF INT 13h
    /* 
    DAPACK:
	db	0x10
	db	0
    blkcnt:	dw	16		; int 13 resets this to # of blocks actually read/written
    db_add:	dw	0x7C00		; memory buffer destination address (0:7c00)
	dw	0		; in memory page zero
    d_lba:	dd	1		; put the lba to read in this spot
	dd	0		; more storage bytes only for big lba's ( > 4 bytes )
 
	mov si, DAPACK		; address of "disk address packet"
	mov ah, 0x42		; AL is unused
	mov dl, 0x80		; drive number 0 (OR the drive # with 0x80)
	int 0x13
    */
    byte size;
    byte reserved;
    word blkcnt;
    word offset;
    word segment;
    qword lba;
} dapack;

static bool checkExtendedDisk() {
	regs reg;
	reg.ax = 0x4100;
	reg.bx = 0x55AA;
	reg.dx = disknum;
	inter(0x13, &reg);
	if (reg.bx == 0xAA55)
		return true;
	return false;
}
static char getdisknum() {
	byte disknum;
	asm volatile("":"=d"(disknum));
	return disknum;
}

static void resetDisk() {
	regs reg;
	reg.ax = 0;
	reg.dx = disknum;
	inter(0x13, &reg);
}

static void readDiskParams(diskinfo* res) {
    res->size = 0x1E;
    regs reg;
    reg.ax = 0x4800;
    reg.dx = disknum;
    reg.si = (dword)res;
    inter(0x13, &reg);
    return;
}

static void formDapack(dapack* dpack, word blkcnt, word offset, word segment, qword lba) {
    dpack->size = 0x10;
    dpack->reserved = 0;
    dpack->blkcnt = blkcnt;
    dpack->offset = offset;
    dpack->segment = segment;
    dpack->lba = lba;
}

static void readDisk(dapack* dpack) {
    regs reg;
    reg.si = (dword)dpack;
    reg.ax = 0x4200;
    reg.dx = disknum;
    inter(0x13, &reg);

}

static void readSector(qword lba) {

word offset = (dword)defaultStr;
word segment = getCS();
dapack dpack;
formDapack(&dpack,1,offset, segment, lba);
readDisk(&dpack);

}

static void writeDisk(dapack* dpack) {
    regs reg;
    reg.si = (dword)dpack;
    reg.ax = 0x4300;
    reg.dx = disknum;
    inter(0x13, &reg);

}

static void writeSector(qword lba) {

word offset = (dword)defaultStr;
word segment = getCS();
dapack dpack;
formDapack(&dpack,1,offset, segment, lba);
writeDisk(&dpack);

}

#endif
