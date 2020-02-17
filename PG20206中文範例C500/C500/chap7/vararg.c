#include <stdio.h>
#include <stdarg.h>

void msg_printf(const char *format, ...)
{
	va_list args;
	char buf[1024];

	va_start(args, format);
	vsprintf(buf, format, args);
	printf("°T®§ %s\n", buf);
	va_end(args);
}

int main(void)
{
	int n = 2003;

	msg_printf("hello, world. AD%d", n);
	msg_printf("hohoho");

	return 0;
}

