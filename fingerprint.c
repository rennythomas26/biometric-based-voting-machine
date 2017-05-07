/*create by renny thomas
 *date 12/09/2016
 */ 



#include <avr/io.h>
#include <string.h>
#include <avr/interrupt.h>
#include "usart.h"
#include "lcd.h"
#include "delay.h"
#include "finger.h"

char keypad();
void put_finger();
void serial_puts(const char *k);
char receive(void);
void scan();
void enter();
void dev1()
{
PORTB|=(1<<0);	
}
void dev2()
{
PORTB|=(1<<1);	
}
void dev3()
{
PORTB|=(1<<2);	
}
void poweron()
{
PORTB|=(1<<3);	
}
void buzzer()
{
	PORTD=0xff;
	delay(100);
	PORTD=0x00;
}
void vot1();
void vot2();
void  key_matching();
char l1[7]="456";
char l2[7]="GET"; 
char d=123;
char x1,x2,x3,x4,x5;
char y1,y2,y3,y4,y5;
char n[7];
char match1;
char m[7],k=0,t;
char  i,sms[5],z=0;
char sms1[5],z1=0; 
char B,c[5];
char q=0;
char C1=0,C2=0;
char X=0,Z=0,A=0;
int main(void)
{   
	char flag=0;
	DDRA=0xf0;
	DDRB=0XFF;
	DDRC=0xFF;
	DDRD=0xFF;

	lcd_init();
	serial_init();
	lcd_command(0x01); 	
	UCSRB=0x18;
	lcd_command(0X80);
	lcd_puts("BIOMETRIC BASED ");
	lcd_command(0Xc0);
	lcd_puts("VOTING SYSTEM");
	delay(20);
	lcd_command(0X01);
	lcd_command(0x80);
	lcd_puts("Done By");
	delay(30);
	lcd_command(0xc0);
	lcd_puts("name 1   ");
	delay(50);
	lcd_command(0xc0);
	lcd_puts("name2     ");
	delay(50);
	lcd_command(0xc0);
	lcd_puts("name 3    ");
	delay(50);
	lcd_command(0xc0);
	lcd_puts("name 4         ");	
	delay(50);
	lcd_command(0x01);
	PORTD=0X00;
	while(1)
	{
		PORTB=0X00;
		lcd_command(0X80);
		lcd_puts("VOTING OPTION");
		lcd_command(0XC0);
		lcd_puts(" YES    NO");
		char J=keypad();
		if(J=='C')
		{
			scan();
		}	
		if(J=='F')
		{
				lcd_command(0X01);
			lcd_puts("ERROR");
			delay(40);	
		}	
	}		
			
}  	
	

char receive(void)
{
	while ((UCSRA & (1<<RXC))==0);
	UCSRA&=~(1<<RXC);
	return(UDR);
}
void put_finger()
{			
			
	        check_finger();
			delay(5);	
			if (z==0x00)
				{
					find_finger();delay(5);
					if (x==0x00)
					{
					match1=search_finger();
					if (y==0x00)
					{
					conv(match1);
					}
					else
					{
					lcd_command(0xc0);
					lcd_puts("Try Again");
					}
						
					}
					else
					{
					lcd_command(0xc0);
					lcd_puts("Try Again");
					}
					}
					else
					{
					lcd_command(0xc0);
					lcd_puts("Try Again");
					}
								
		
}
void scan()
{
	connect_finger();
	delay(2);
			delay(20);
			lcd_command(0x01);
			delay(20);
			lcd_puts("Press your ");
			lcd_command(0xc7);
			lcd_puts("finger");
			put_finger();
			char Q[8],T=0,Y;
			switch(match1)
			  {
				 case 101:
						 lcd_command(0x01);
						 lcd_puts("SUCCESS");
						 delay(30);
						 if(C1==0)
						 {
							
						  poweron();
						 vot1();
						 }
						 C1=C1+1;
						 if(C1==2)
						 {
							 lcd_command(0x01);
							lcd_puts("ALREADY LOGINED");
							buzzer();
							delay(30); 
						 }						 
						
						
			   	break;
				
				case 103:
						 lcd_command(0x01);
						 lcd_puts("SUCCESS");
						 delay(30);
						 delay(30);
						 poweron();
						 if(C2==0)
						 {
							
						  poweron();
						 vot2();
						 }
						 C2=C2+1;
						 if(C2==2)
						 {
							 lcd_command(0x01);
							lcd_puts("ALREADY LOGINED");
							buzzer();
							delay(30); 
						 }
				break;
									
				case 102:
				
						lcd_command(0x01);
						 lcd_puts("SECURE SYSTEM");
						 poweron();
						 delay(30);
						 lcd_command(0XC0);
						 lcd_puts("VOTING STATUSS");
						 delay(40);
						 lcd_command(0X01);
						 lcd_puts("XXX=");
						 lcd_data(X+0X30);
						 lcd_puts("  YYY=");
						 lcd_data(A+0X30);
						 lcd_command(0XC0);
						 lcd_puts("  ZZZ=");
						 lcd_data(Z+0X30);
						 
						
				break;
						
// 				case 4:
// 				
// 						lcd_command(0x80);
// 						lcd_puts("welcome4");
// 						delay(10);
// 						
// 				break;
		
				default:
					lcd_command(0x01);
					lcd_puts("sorry !!:('-')");
					
				break;

				 
			 }	 	 
	
}
void enter()
{
	
	lcd_command(0x01);
	lcd_puts("ENTER UR PASWRD");
	lcd_command(0xc0);
	for(k=0;k<3;k++)
			{
				
				t=keypad();
				delay(20);
				lcd_data(t);
				m[k]=t-0x30;
				delay(50); 				
 				x1=m[0]*100;
	 			x2=m[1]*10;
	 			x3=m[2]*1;
				 x4=x1+x2+x3;
			}
			if (strcmp(d,x4)==0x00)
			{
				lcd_command(0x01);
				lcd_puts("LOGIN SUCESS");
				lcd_command(0x01);
				lcd_puts(" SERVER STATUS.....");
						
				
	
				
			}
			else
			{
				lcd_command(0x01);
				lcd_puts("LOGIN ERROR");
			}
}
void vot1()
{
	lcd_command(0x01);
	lcd_puts("NAME: RINNY");
	lcd_command(0xc0);
	lcd_puts("ID NO:12345");
	delay(30);
	lcd_command(0x01);
	lcd_puts("WARD NAME:GISAT  ");
	lcd_command(0xc0);
	lcd_puts("WARD SECTION:ECE");
	delay(50);
	lcd_command(0x01);
	lcd_puts("PRESS UR OPTION");
	lcd_command(0xc0);
	lcd_puts("  YES     NO");
	delay(10);
	char V=keypad();
	if(V=='C')
	{
		lcd_command(0X01);
		lcd_puts("SUCCESS");
		delay(30);
		lcd_command(0X01);
		lcd_puts("LIST OF CANDIDATE");
		delay(40);
		lcd_command(0x01);
		lcd_puts("1:XXX     2:YYY");
		lcd_command(0XC0);
		lcd_puts("    3:ZZZ     ");
		char W=keypad();
		if(W=='1')
		{
			lcd_command(0x01);
			lcd_puts("VOTING SUCCESS");
			X=X+1;
			delay(20);
			dev1();
			delay(40);
		}
		if(W=='2')
		{
			lcd_command(0x01);
			lcd_puts("VOTING SUCCESS");
			A=A+1;
			delay(20);
			dev2();
			delay(40);
		}
		if(W=='3')
		{
			lcd_command(0x01);
			lcd_puts("VOTING SUCCESS");
			Z=Z+1;
			delay(20);
			dev3();
			delay(40);
		}
		
	}
	if(V=='F')
	{
		lcd_command(0X01);
		lcd_puts("ERROR");
		delay(30);
		lcd_command(0XC0);
		lcd_puts(" TRY AGAIN");
	}
	
	
}
void vot2()
{
	lcd_command(0x01);
	lcd_puts("NAME: RESHMA");
	lcd_command(0xc0);
	lcd_puts("ID NO:56789");
	delay(30);
	lcd_command(0x01);
	lcd_puts("WARD NAME:GISAT  ");
	lcd_command(0xc0);
	lcd_puts("WARD SECTION:EEE");
	delay(50);
	lcd_command(0x01);
	lcd_puts("PRESS UR OPTION");
	lcd_command(0xc0);
	lcd_puts("  YES     NO");
	delay(10);
	char V=keypad();
	if(V=='C')
	{
		lcd_command(0X01);
		lcd_puts("SUCCESS");
		delay(30);
		lcd_command(0X01);
		lcd_puts("LIST OF CANDIDATE");
		delay(40);
		lcd_command(0x01);
		lcd_puts("1:XXX     2:YYY");
		lcd_command(0XC0);
		lcd_puts("    3:ZZZ     ");
		char W=keypad();
		if(W=='1')
		{
			lcd_command(0x01);
			lcd_puts("VOTING SUCCESS");
			X=X+1;
			delay(20);
			dev1();
			delay(40);
		}
		if(W=='2')
		{
			lcd_command(0x01);
			lcd_puts("VOTING SUCCESS");
			A=A+1;
			delay(20);
			dev2();
			delay(40);
		}
		if(W=='3')
		{
			lcd_command(0x01);
			lcd_puts("VOTING SUCCESS");
			Z=Z+1;
			delay(20);
			dev3();
			delay(40);
		}
		
	}
	if(V=='F')
	{
		lcd_command(0X01);
		lcd_puts("ERROR");
		delay(30);
		lcd_command(0XC0);
		lcd_puts(" TRY AGAIN");
	}
	
	
}
void key_matching()
{
	lcd_command(0x01);
	lcd_puts("ENTER UR OTP");
	lcd_command(0xc0);
		for(k=0;k<3;k++)
			{
				
				t=keypad();
				delay(20);
				lcd_data(t);
				n[k]=t;
				delay(50); 				
//  				y1=n[0]*100;
// 	 			y2=n[1]*10;
// 	 			y3=n[2]*1;
// 				 y4=y1+y2+y3;
// 				 y4='\0';
			}
			n[k]='\0';
// 			lcd_command(0X01);
// 			lcd_puts(n);
			delay(10);
			if (strcmp(sms,n)==0x00)
			{
				lcd_command(0x01);
				lcd_puts("OTP LOGIN SUCESS");
				scan();
				
			}
			else
			{
				lcd_command(0x01);
				lcd_puts("OTP LOGIN ERROR");
				UDR=0X00;
			}
			k=0;
}
char keypad()
{	
char f,chr,a;
f=0;
while(1)
	{	
	f=0;
	PORTA=0X7F;
	a=PINA&0X0F;
	switch(a)
	{
		case 0X0E:
		chr='0';
		f=1;
		break;
		case 0X0D:
		chr='7';
			f=1;
		break;
// 		case 0X0B:
// 		chr='B';
// 		f=1;
// 		break;
		case 0X07:
		chr='F';
		f=1;
		break;
	}
							
	PORTA=0XBF;
	a=PINA&0X0F;
	switch(a)
	{
		case 0X0E:
		chr='1';
		f=1;
		break;
		case 0X0D:
		chr='6';
		f=1;
		break;
// 		case 0X0B:
// 		chr='A';
// 		f=1;
// 		break;
// 		case 0X07:
// 		chr='E';
// 		f=1;
// 		break;
	}	
	PORTA=0XDF;
	a=PINA&0X0F;
	switch(a)
	{
		case 0X0E:
		chr='2';
		f=1;
		break;
		case 0X0D:
		chr='5';
		f=1;
		break;
		case 0X0B:
		chr='9';
		f=1;
		break;
// 		case 0X07:
// 		chr='D';
// 		f=1;
// 		break;
	}
		
		
	PORTA=0XEF;
	a=PINA&0X0F;
	switch(a)
	{
		case 0X0E:
		chr='3';
		f=1;
		break;
		case 0X0D:
		chr='4';
		f=1;
		break;
		case 0X0B:
		chr='8';
		f=1;
		break;
		case 0X07:
		chr='C';
		f=1;
		break;
			
	}
				
		if(f==1)
	return(chr);
		
	}
}

void serial_puts(const char *k)
{
	while(*k)
	{
		transmit(*k++);
		delay(2);
	}
}


				