typedef struct regs
{
  word ax;
  word bx;
  word cx;
  word dx;
  word si;
  word di;
} regs; 

extern void inter(char num, regs* reg) {
  asm volatile(".intel_syntax noprefix\n"
  	           "lea di, [intnum]\n"
  	           "mov [di], al\n"
  	           ".att_syntax prefix\n": :"a"(num):"di");

  asm volatile(".byte	0xcd\n" //int opcode
               "intnum: .byte 0\n":"=a"(reg->ax),"=b"(reg->bx),"=c"(reg->cx),"=d"(reg->dx),"=S"(reg->si),"=D"(reg->di)
                :"a"(reg->ax),"b"(reg->bx),"c"(reg->cx),"d"(reg->dx),"S"(reg->si),"D"(reg->di));
}
