#ifndef FPU_H
#define FPU_H

static void finit() {
	asm volatile("finit");
} 

#endif