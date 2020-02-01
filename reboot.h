#ifndef REBOOT_H
#define REBOOT_H

static void reboot() {
	  asm volatile(".intel_syntax noprefix\n"
               ".include \"reboot.asm\"\n"
               ".att_syntax prefix\n");
}

#endif
