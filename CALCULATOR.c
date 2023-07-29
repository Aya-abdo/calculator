/*
 * CALCULATOR.c
 *
 * Created: 8/3/2022 3:01:33 PM
 *  Author: MSI
 */ 
#include "LCD.h"
#include "KEY_PAD.h"
#define F_CPU 8000000UL
#define MAX_DIGITS 4
#include "util/delay.h"



int main(void)
{
	LCD_init();
	key_pad_init();
	long int value=0,digit1=0,digit2=0;
	 char counter1=0;
	 char counter2=0;
	  char op=0,f=0;
	 char arr[8]={0};
	signed char i,j;
    while(1)
    {
		label:while(counter1<MAX_DIGITS){
		if(counter1==0)
		{
			do{
				value=key_pad_check_press();
			}while(value==0xff);
			if(value!='A')
			{
				LCD_send_char(value);
				_delay_ms(250);
				digit1=value-'0';
				counter1++;
			}
			else
			{
				LCD_clear();
				value=0xff;
				counter1=0,counter2=0,digit1=0,digit2=0,op=0,f=0;
				goto label;
			}
		}
		else
		{
			value=0xff;
			
					do{
						value=key_pad_check_press();
					}while(value==0xff);
					if(value!='A'&&value!='+'&&value!='-'&&value!='*'&&value!='/')
					{
						digit1*=10;
						LCD_send_char(value);
						_delay_ms(250);
						value-='0';
						digit1=digit1+value;
						counter1++;
					}
						else if (value=='+'||value=='-'||value=='*'||value=='/')
						{
							op=value;
							LCD_send_char(value);
							_delay_ms(250);
							break;
						}
						else if(value=='A'){
						 LCD_clear();
						 value=0xff;
						 counter1=0,counter2=0,digit1=0,digit2=0,op=0,f=0;
						 goto label;
					}
				
			}
		}
					
	if (op==0)
	{
		do
		{
			value=key_pad_check_press();
		} while (value!='+'&&value!='-'&&value!='/'&&value!='*'&&value!='A');
		if (value!='A')
		{
			op=value;
			LCD_send_char(value);
			_delay_ms(250);
		}
		else
		{
			LCD_clear();
			value=0xff;
			counter1=0,counter2=0,digit1=0,digit2=0,op=0,f=0;
			goto label;
			
		}
	}
			
			
			value=0xff;
				while(counter2<MAX_DIGITS){
					if(counter2==0)
					{
						do{
							value=key_pad_check_press();
						}while(value==0xff);
						if(value!='A')
						{
							LCD_send_char(value);
							_delay_ms(250);
							digit2=value-'0';
							counter2++;
						}
						else 
						{
							LCD_clear();
							value=0xff;
							counter1=0,counter2=0,digit1=0,digit2=0,op=0,f=0;
							goto label;
						}
					}
					else
					{
						value=0xff;
						
						do{
							value=key_pad_check_press();
						}while(value==0xff);
						if(value!='A'&&value!='=')
						{
							digit2*=10;
							LCD_send_char(value);
							_delay_ms(250);
							value-='0';
							digit2=digit2+value;
							counter2++;
						}
						else if(value=='A')
						{
							LCD_clear();
							value=0xff;
							counter1=0,counter2=0,digit1=0,digit2=0,op=0,f=0;
							goto label;
						}
						else if(value=='=')
						{
							LCD_send_char(value);
							f=1;
							_delay_ms(250);
							break;
						}
						
					}
				}
				if (f==0){
						do
						{
							value=key_pad_check_press();
						} while (value!='='&&value!='A');
						}						
			
				
			
				if(value!='A')
				{
					if (f==0)
					{
						LCD_send_char(value);
						_delay_ms(250);
					}
					
					_delay_ms(250);
					switch (op)
					{
						case '+':
						digit1+=digit2;
						i=0;
						while(digit1!=0)
						{
							arr[i]=(digit1%10)+'0';
							digit1/=10;
							i++;
							
						}
						
						for (j=i-1;j>=0;j--)
						{
							LCD_send_char(arr[j]);
						}
						break;
						case '-':
							digit1-=digit2;
							i=0;
							while(digit1!=0)
							{
								arr[i]=(digit1%10)+'0';
								digit1/=10;
								i++;
								
							}

							
							for (j=i-1;j>=0;j--)
							{
								LCD_send_char(arr[j]);
							}
							break;
							case '*':
								digit1*=digit2;
								 i=0;
								while(digit1!=0)
								{
									arr[i]=(digit1%10)+'0';
									digit1/=10;
									i++;
									
								}
								if(i==8){
									LCD_move_cursor(2,1);
								}
								
								
								for (j=i-1;j>=0;j--)
								{
									LCD_send_char(arr[j]);
								}
								break;
						case '/':
						digit1/=digit2;
						 i=0;
						while(digit1!=0)
						{
							arr[i]=(digit1%10)+'0';
							digit1/=10;
							i++;
							
						}
			
						for (j=i-1;j>=0;j--)
						{
							LCD_send_char(arr[j]);
						}
						break;
					}
				}
				else
				{
						LCD_clear();
						value=0xff;
						counter1=0,counter2=0,digit1=0,digit2=0,op=0,f=0;
						goto label;
				}
			do 
			{
				value=key_pad_check_press();
			} while (value!='A');
			LCD_clear();
			value=0xff;
			counter1=0,counter2=0,digit1=0,digit2=0,op=0,f=0;
		}
		
							
    
    
}