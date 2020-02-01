all:
	/usr/local/cross-i686-elf/bin/i686-elf-gcc -std=gnu99 -Os -nostdlib -m32 -march=i386 -ffreestanding \
    -o main.com -Wl,--nmagic,--script=com.ld main.c
asm:
	/usr/local/cross-i686-elf/bin/i686-elf-gcc -std=gnu99 -Os -nostdlib -m32 -march=i386 -ffreestanding \
    -o main.S -S -Wl,--nmagic,--script=com.ld main.c
