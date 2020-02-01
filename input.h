#ifndef INPUT_H
#define INPUT_H

static char input() {
    char c;
    while ( !kbhit() );
    c = kb_read();
    print_char(c);
    return c;
}

static bool isdigit(char c) {
	if ( (unsigned char)(c - '0') > 9 )
		return false;
	return true;
}

static bool isspace(char c) {
    if (c == ' ' || c == '\t')
        return true;
    return false;
}

static int atoi(const char* string)
{
 if(!string) return 0;
 int result = 0;
 
 //пропускаем пробельные символы
 while(*string == ' ' || *string == '\t' ) string++;
 
 // получаем знак числа
 bool bNegativeSign = (*string == '-');
 
 if(bNegativeSign || *string=='+') string++;
 
 while(*string) {
   if( (*string < '0' || *string> '9') ) break;
   result = result * 10 + (*string - '0');
   string++;
 }
return ( bNegativeSign ? -result : result );
}

static double atod(char* s)
{
       double val, power, rtn;
       int i, sign;
       for (i = 0; isspace(s[i]); i++);
       sign = (s[i] == '-') ? -1 : 1;
       if (s[i] == '+' || s[i] == '-') ++i;
       for (val = 0.0; isdigit(s[i]); ++i) {
           val = 10.0 * val + (s[i] - '0');
       }
       if (s[i] == '.') {
           ++i;
       }
       for (power = 1.0; isdigit(s[i]); ++i) {
           val = 10.0 * val + (s[i] - '0');
           power *= 10.0;
       }
       rtn = (sign * val / (power));

       // Next work on exponent
       if (s[i] == 'e') {
           int j, esign; 
           int eval = 0;
           
           for (j = i + 1; isspace(s[j]); ++j);
           esign = (s[j] == '-') ? -1 : 1;
           if (s[j] == '+' || s[j] == '-') ++j;
           for (; isdigit(s[j]); ++j) {
               eval = 10 * eval + (s[j] - '0');
           }
           
           int l;
           for (l = 0; l < eval; l++) {
               (esign >= 0) ? (rtn *= 10) : (rtn /= 10);
           }
       }

       // Finally return the solution
       return rtn;
}

static void inputStr(char* str) {
	char c;
	int i = 0;
	for(;;) {
     	c = input();
     	if (c == '\r')
     		break;
     	if (c == '\b') {
     		if (i > 0) {
     			print(" \b");
     		    --i;
     		    continue;
        }
        else {
          print(" ");
          i = 0;
          continue;
        }
     	}
    	str[i] = c;
    	++i; 
    }
    str[i] = '\0';
    print_char('\n');
}

static bool cmpstr(const char* s1, const char* s2) {
    while (1) {
        if (*s1 != *s2)
            return false;
        if (*s1 == '\0')
            return true;
        s1++;
        s2++;
    }
}
#endif
