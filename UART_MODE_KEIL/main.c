#include <regx51.h>

void uartinit()
{
	SM0=0;
	SM1=1;
	TMOD=0X20;
	TH1=0XFD;
	TR1=1;
	TI=1;
	REN=1;
}

void uart_write(char c)
{
	while(TI==0);
	TI=0;
	SBUF=c;
}

char uart_read_data()
{
	return RI;
}
char uart_read()
{
	RI=0;
	return SBUF;
}

void uart_write_text(char * str)
{
	unsigned char i=0;
	while(str[i]!=0)
	{
		uart_write(str[i]);
		i++;
	}
}

void main()
{
	P3_2=P3_3=0;
	uartinit();
	while(1)
	{
		if( uart_read_data())
		{
			if(uart_read()=='1')
			{
				P3_2=1;
			}
			if(uart_read()=='2')
			{
				P3_3=1;
			}
			if(uart_read()=='3')
			{
				P3_2=0;
			}
			if(uart_read()=='4')
			{
				P3_3=0;
			}
		}
	}
}