#include "tistdtypes.h"
#include "uart.h"
//#include "debug.h"
#include "sdc_debug.h"
#include "device.h"

// Debug print function (could use stdio or maybe UART)

#define uart_ready(uart) (uart->LSR & 0x20)
#define uart_send(uart,c) uart->THR = c

int putchar(int c)
{
	while (!uart_ready(UART0)) ;
	uart_send(UART0, c);
	return c;
}

int uart_write(char *c)
{
	while (*c) {
		putchar(*c);
		c++;
	}
}

int print(char *c)
{
	while (*c) {
		if (*c == '\r') {
			uart_write(CR);
		} else if (*c == '\n') {
			uart_write(NEWLINE);
		} else
			putchar(*c);
		c++;
	}
}

int print_hex(unsigned int value)
{
	int v = 0, dig, i;
	print(GRAY);
	for (i = 7; i >= 0; i--) {
		dig = (value >> i * 4 & 0xF) + '0';
		/* trvi_((value >> i * 4 & 0xF));
		   trvi_(((value >> (i * 4)) & 0xF));
		   trvi(dig-'0'); */
		if (dig > '0' && !v) {
			v = 1;
			print(VALUE);
		}
		if (dig > '9')
			dig += 'A' - '0' - 10;
		putchar(dig);
	}
	print(NOCOLOR);
	return 0;
}

Uint32 puts(char *s)
{
	print(s);
	print("\n");
}

#ifdef PRINTI
int udiv(unsigned int *a, unsigned int b)
{
	unsigned int a2 = *a;
	int r = 0;
	while (a2 >= b) {
		r++;
		a2 -= b;
	}
	*a = r;
	return a2;
}

int printi(int i)
{
	char buff[20];
	int d = sizeof(buff) - 1;
	if (i < 0) {
		print("-");
		i *= -1;
	}
	buff[d] = 0;
	while (i > 0 && d > 0) {
		d--;
		buff[d] = '0' + udiv(&i, 10);
	}
	print(&buff[d]);
}
#endif

int getch()
{
	int timerStatus = 1;
	int rc;
	// return UART_recvStringN(c,&len,FALSE);
	//DEVICE_TIMER0Start();
	do {
		rc = UART0->LSR & 1;
		//timerStatus = DEVICE_TIMER0Status();
	}
	while (!rc && timerStatus);

	if (timerStatus == 0)
		return -1;

	rc = UART0->RBR & 0xFF;

	// Check status for errors
	if (UART0->LSR & 0x1C)
		rc = -1;

	return rc;
}
