#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>

void my_putchar(char c) { write(1, &c, 1); }
void my_putstr(char*);
int numlen(unsigned long, int);
char* ConverBase(unsigned long, int);
int my_printf(char*, ...);

int main(void)
{
	int num = 125;
	int len;
    len = my_printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%!\n");
	my_printf("len my_printf - %d\n", len);
    my_printf("%c!\n", 'H');
    my_printf("%c%c%c%c%c!\n", 'H', 'e', 'l', 'l', 'o');
    my_printf("Hello %s!\n", "QWASAR.IO");
    my_printf("Hello %s %s!\n", "Mr", "Gaetan");
    len = my_printf("NULL STRING %s!\n", (char*)NULL);
	my_printf("len my_printf - %d\n", len);
    my_printf("%d!\n", 1337);
    my_printf("%d - %d - %d!\n", 2048, 0, -1337);
    my_printf("%o!\n", 100);
    my_printf("%u!\n", 1337);
    my_printf("%x!\n", 125);
    len = my_printf("%p!\n", NULL);
    my_printf("len my_printf - %d\n", len);
    len = my_printf("%p!\n", &num);
	my_printf("len my_printf - %d\n", len);

    len = printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%!\n");
	printf("len %d\n", len);
    printf("%c!\n", 'H');
    printf("%c%c%c%c%c!\n", 'H', 'e', 'l', 'l', 'o');
    printf("Hello %s!\n", "QWASAR.IO");
    printf("Hello %s %s!\n", "Mr", "Gaetan");
    len = printf("NULL STRING %s!\n", (char*)NULL);
	printf("len printf - %d\n", len);
    printf("%d!\n", 1337);
    printf("%d - %d - %d!\n", 2048, 0, -1337);
    printf("%o!\n", 100);
    printf("%u!\n", 1337);
    printf("%x!\n", 125);
    len = printf("%p!\n", NULL);
    printf("len printf - %d\n", len);
    len = printf("%p!\n", &num);
	printf("len printf - %d\n", len);
	return 0;
}

void my_putstr(char *c) {
  int i = 0;
  while (c[i] != '\0') {
    my_putchar(c[i]);
    i++;
  }
}

int numlen(unsigned long num, int base) {
    int count = 0;
	if (num == 0) return 1;
    while(num != 0) {
        num /= base;
        count++;
    }
    return count;
}

char* ConvertBase(unsigned long num, int base) {
    char Base[] = "0123456789abcdef";
    int numdigits = numlen(num, base);
    char buff[numdigits+1];
    int i = 0;
    do {
        buff[numdigits-1-i] = Base[num%base];
        num /= base;
        i++;
    } while(num!=0);
    buff[numdigits] = '\0';
    char* res = (char*)malloc(numdigits+1);
    strcpy(res, buff);
    return res;
}

int my_printf(char *format, ...)
{
	int d, len, i;
	char* str, *res;
	void* ptr;
    char c;
	va_list ap;
	va_start(ap, format);
	i = 0, len = 0;
	while (format[i] != '\0') {
		if (format[i] != '%') {
			len++;
			my_putchar(format[i]);
			i++;
		} else if (format[i] == '%') {
			if (format[i+1] != '\0') {
				i++;
				switch (format[i]) {
					case 'd':
						d = va_arg(ap, int);
						if (d < 0) {
							my_putchar('-');
                            d = -d;
							len++;
						}
						res = ConvertBase(d, 10);
						len += strlen(res);
						my_putstr(res);
                        free(res);
						i++;
						break;
					case 'o':
						d = va_arg(ap, unsigned int);
						res = ConvertBase(d, 8);
						len += strlen(res);
						my_putstr(res);
                        free(res);
						i++;
						break;
					case 'x':
						d = va_arg(ap, unsigned int);
						res = ConvertBase(d, 16);
						len += strlen(res);
						my_putstr(res);
                        free(res);
						i++;
						break;
					case 'u':
						d = va_arg(ap, unsigned int);
						res = ConvertBase(d, 10);
						len += strlen(res);
						my_putstr(res);
                        free(res);
						i++;
						break;
                    case 'c':
                        d = va_arg(ap, int);
						len++;
                        my_putchar((char)d);
                        i++;
                        break;
					case 's':
						str = va_arg(ap, char*);
                        void* ptr = str;
                        if (ptr == NULL) {
                            my_putstr("(null)");
							len += 6;
                            i++;
                            break;
                        }
						my_putstr(str);
						len += strlen(str);
						i++;
						break;
					case 'p':
						ptr = va_arg(ap, void*);
                        if (ptr==NULL) {
                            my_putstr("(nil)");
							len += 5;
                            i++;
                            break;
                        }
						my_putchar('0'); 
						my_putchar('x');
						res = ConvertBase((unsigned long)ptr, 16);
						len += strlen(res) + 2;
						my_putstr(res);
                        free(res);
						i++;
						break;
					default:
                        my_putchar(format[i]);
						len++;
						i++;
						break;
					}
			} else {
				break;
			}
		} 
	}
	va_end (ap);
	return len;
}