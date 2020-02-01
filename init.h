/* NOTICE: This must be included first! */
asm ("startup: .code16gcc\n"
     "call  bootmain\n"
     "mov   $0x4C,%ah\n"
     "int   $0x21\n");
