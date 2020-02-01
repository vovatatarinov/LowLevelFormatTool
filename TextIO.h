#ifndef TEXTIO_H
#define TEXTIO_H

static void print_char(char c) {
    regs reg;
    reg.ax = (0x0E << 8) | c;
    reg.bx = 0;
    inter(0x10, &reg);
}
/*
static void print_char(char c) {
  asm volatile(".intel_syntax noprefix\n"
               ".include \"print_char.asm\"\n"
	       ".att_syntax prefix": :"a"(c):"bx");
}
*/
static void print(const char* str) {
    for (int i = 0; str[i] != '\0'; ++i)
        print_char(str[i]);
}

static void printNum(int n) {
    if (n == 0) {
        print_char('0');
        return;
    }
    if (n < 0) {
        n = (-n);
        print_char('-');
    }
    int i = 1;
    while (n / i > 0)
        i *= 10;
    i /= 10;
    while (i > 0) {
        char c = n / i;
        c |= ( (1 << 5) | (1 << 4) );
	print_char(c);
	n = n % i;
	i /= 10;
    }
}



static void printNumDouble(double a) {
    double b;
    bool neg=false; if (a<0) neg=true;
    if (neg) b=0-a; else b=a;
    dword cel=b;
    if (neg) print_char('-');
    printNum(cel);
    b=b-cel;
    print_char('.');
    for (int i=0; i<10;i++) {
        dword out;
        b=b*10;
        out=b;
        b=b-out;
        printNum(out);
    }

}
static void printNumHex(int n) {
    if (n < 0) {
        n = (-n);
        print_char('-');
    }
    print("0x");
    if (n == 0) {
        print_char('0');
        return;
    }
    int i = 1;
    while (n / i > 0)
        i *= 16;
    i /= 16;
    while (i > 0) {
        char c = n / i;
    if (c >= 10) {
            c -= 9;
            c |= (1 << 6);
        }
        else
            c |= ( (1 << 5) | (1 << 4) );

    print_char(c);
    n = n % i;
    i /= 16;
    }
}


#endif
