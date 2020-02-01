#ifndef MEM_H
#define MEM_H

char defaultStr[16384];
 
static word getCS() {
    word cs;
    asm volatile("mov %%cs, %%ax":"=a"(cs));
    return cs;
}
#endif
