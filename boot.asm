cli
mov ax, cs
mov es,ax
mov ds, ax
mov ss, ax
mov sp, 0xFFFF
mov bp, 0xFFFF
sti
call bootmain

hang:
cli
hlt
jmp hang
