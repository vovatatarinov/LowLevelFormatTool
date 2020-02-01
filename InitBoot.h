/* NOTICE: This must be included first! */
/* It just setup a stack then call dosmain() and then hangs computer! */
/* Program should be loaded into CS=0x1000 IP=0x0000 */
/* SS = 0x2000 SP=0xFFFF BP=0xFFFF */
asm (".code16gcc\n"
     ".intel_syntax noprefix\n"
     ".include \"boot.asm\"\n"
     ".att_syntax prefix\n");
