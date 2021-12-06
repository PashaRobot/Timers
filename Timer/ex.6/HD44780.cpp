/* 
* HD44780.cpp
*
* Created: 29.09.2021 12:15:44
* Author: Pavel Bezdelev
*/


#include "HD44780.h"

// default constructor
HD44780::HD44780(uint8_t state, uint8_t shift)
{
	PORTA_DIR = 0xFF;
	PORTB_DIR = 0x3;
	_delay_ms(100);
	Send_Cmd(HD44780_Function_Set_8bit_2line_5x8_gc);
	_delay_ms(5);	// wait min 4.1ms
	Send_Cmd(HD44780_Function_Set_8bit_2line_5x8_gc);
	_delay_us(110); // wait min 100us
	Send_Cmd(HD44780_Function_Set_8bit_2line_5x8_gc);
	_delay_us(50); // wait min 37us

	Send_Cmd(HD44780_Function_Set_8bit_2line_5x8_gc);
	_delay_us(50); // wait min 37us

	Send_Cmd(HD44780_Display_Control_OFF_OFF_OFF_gc);
	_delay_us(50); // wait min 37us

	Send_Cmd(HD44780_Clear_Display_gc);
	_delay_ms(2); // wait min 37us

	Send_Cmd(shift);
	_delay_us(50); // wait min 37us

	Send_Cmd(HD44780_Return_Home_gc);
	_delay_ms(2); // wait min 37us

	Send_Cmd(state);
	_delay_us(50); // wait min 37us
	
} //HD44780

// default destructor
/*HD44780::~HD44780()
{
} //~HD44780
*/

void HD44780::Send_Cmd(uint8_t byte)
{
	PORTB_OUTCLR = 1;
	_PORTA_OUT_(byte);

	_delay_us(10);

	PORTB_OUTSET = 2;

	_delay_us(10);

	PORTB_OUTCLR = 2;

	_delay_us(10);
}

void HD44780::Send_Data(uint8_t byte)
{
	PORTB_OUTSET = 1;
	_PORTA_OUT_(byte);

	_delay_us(10);

	PORTB_OUTSET = 2;

	_delay_us(10);

	PORTB_OUTCLR = 2;

	_delay_us(10);
}

void HD44780::_PORTA_OUT_(uint8_t byte)
{
	PORTA_OUTCLR = 255;
	uint8_t j = 128;
	for (uint8_t i = 1; j > 0; i = i << 1){
		if (byte & i) PORTA_OUTSET = j;
		j = j >> 1;
	}
}

void HD44780::Send_String(const char* str)
{
	uint8_t i = 0;
	while (*(str+i))    // ���� ��������� ���� �� ������ �� 0, ������� ����� � ����� ������
	{
		switch(*(str+i))
		{
			case '�': Send_Data('A'); break;
			case '�': Send_Data(0xA0); break;
			case '�': Send_Data('B'); break;
			case '�': Send_Data(0xA1); break;
			case '�': Send_Data(0xE0); break;
			case '�': Send_Data('E'); break;
			case '�': Send_Data(0xA2); break;
			case '�': Send_Data(0xA3); break;
			case '�': Send_Data(0xA4); break;
			case '�': Send_Data(0xA5); break;	
			case '�': Send_Data(0xA6); break;
			case '�': Send_Data('K'); break;
			case '�': Send_Data(0xA7); break;
			case '�': Send_Data('M'); break;
			case '�': Send_Data('H'); break;
			case '�': Send_Data('O'); break;
			case '�': Send_Data(0xA8); break;
			case '�': Send_Data('P'); break;
			case '�': Send_Data('C'); break;
			case '�': Send_Data('T'); break;
			case '�': Send_Data(0xA9); break;
			case '�': Send_Data(0xAA); break;
			case '�': Send_Data('X'); break;
			case '�': Send_Data(0xE1); break;
			case '�': Send_Data(0xAB); break;
			case '�': Send_Data(0xAC); break;
			case '�': Send_Data(0xE2); break;
			case '�': Send_Data(0xAD); break;
			case '�': Send_Data(0xAE); break;
			case '�': Send_Data(0x62); break;
			case '�': Send_Data(0xAF); break;
			case '�': Send_Data(0xB0); break;
			case '�': Send_Data(0xB1); break;
			case '�': Send_Data('a'); break;
			case '�': Send_Data(0xB2); break;
			case '�': Send_Data(0xB3); break;
			case '�': Send_Data(0xB4); break;
			case '�': Send_Data(0xE3); break;
			case '�': Send_Data('e'); break;
			case '�': Send_Data(0xB5); break;
			case '�': Send_Data(0xB6); break;
			case '�': Send_Data(0xB7); break;
			case '�': Send_Data(0xB8); break;
			case '�': Send_Data(0xB9); break;
			case '�': Send_Data(0xBA); break;
			case '�': Send_Data(0xBB); break;
			case '�': Send_Data(0xBC); break;
			case '�': Send_Data(0xBD); break;
			case '�': Send_Data('o'); break;
			case '�': Send_Data(0xBE); break;
			case '�': Send_Data('p'); break;
			case '�': Send_Data('c'); break;
			case '�': Send_Data(0xBF); break;
			case '�': Send_Data('y'); break;
			case '�': Send_Data(0xE4); break;
			case '�': Send_Data('x'); break;
			case '�': Send_Data(0xE5); break;
			case '�': Send_Data(0xC0); break;
			case '�': Send_Data(0xC1); break;
			case '�': Send_Data(0xE6); break;
			case '�': Send_Data(0xC2); break;
			case '�': Send_Data(0xC3); break;
			case '�': Send_Data(0xC4); break;
			case '�': Send_Data(0xC5); break;
			case '�': Send_Data(0xC6); break;
			case '�': Send_Data(0xC7); break;
				
			default: Send_Data(*(str+i));
		}
		i++;
	}
}

void HD44780::Set_X_Y(uint8_t x, uint8_t y)
{
	if((y == 1) && (x >= 1 && x <= 16))
	{
		Send_Cmd(1 << 7 | (x - 1));
	}
	else if((y == 2) && (x >= 1 && x <= 16))
	{
		Send_Cmd(1 << 7 | (x - 1 + 0x40));
	}
	else
	Send_Cmd(1 << 7 | 0x0);
	_delay_us(40);
}

void HD44780::Clear_Display()
{
	Send_Cmd(1);
	_delay_ms(2);
}

void HD44780::Send_Num(uint8_t Num)
{ 
	// ���������� � ������� �����
	uint8_t count = 0;
	uint8_t ch[3] = {0, 0, 0};
	
	for(int i = 0; (Num) || ((!Num) & (!count)); i++)
	{
		ch[i] = Num % 10;
		Num = Num / 10;
		count++;
	}
	
	for(int i = 2; i >= 0; i--)
	{
		Send_Data(ch[i] + 0x30);
	}
}

void HD44780::Send_Num(uint16_t Num)
{
	// ���������� � ������� �����
	uint8_t count = 0;
	uint8_t ch[5] = {0, 0, 0, 0, 0};
	
	for(int i = 0; (Num) || ((!Num) & (!count)); i++)
	{
		ch[i] = Num % 10;
		Num = Num / 10;
		count++;
	}
	
	for(int i = 4; i >= 0; i--)
	{
		Send_Data(ch[i] + 0x30);
	}
}

void HD44780::Send_Num(uint32_t Num)
{
	// ���������� � ������� �����
	uint8_t count = 0;
	uint8_t ch[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	
	for(int i = 0; (Num) || ((!Num) & (!count)); i++)
	{
		ch[i] = Num % 10;
		Num = Num / 10;
		count++;
	}
	
	for(int i = 9; i >= 0; i--)
	{
		Send_Data(ch[i] + 0x30);
	}
}

void HD44780::Send_Num(int8_t Num)
{
	uint8_t count = 0;
	uint8_t ch[3];
	uint8_t Num_128 = 128;
	
	if(Num < 0 && Num != -128)
	{
		Num *= -1;
		Send_Data('-');
		for(int i = 0; Num; i++)
		{
			ch[i] = Num % 10;
			Num = Num / 10;
			count++;
		}
		
		for(int i = count - 1; i >= 0; i--)
		{
			Send_Data(ch[i] + 0x30);
		}
	}
	else if(Num == -128)
	{
		Send_Data('-');
		for(int i = 0; Num_128; i++)
		{
			ch[i] = Num_128 % 10;
			Num_128 = Num_128 / 10;
			count++;
		}
		
		for(int i = count - 1; i >= 0; i--)
		{
			Send_Data(ch[i] + 0x30);
		}
	}
	else
	{
		for(int i = 0; (Num) || ((!Num) & (!count)); i++)
		{
			ch[i] = Num % 10;
			Num = Num / 10;
			count++;
		}
		
		for(int i = count - 1; i >= 0; i--)
		{
			Send_Data(ch[i] + 0x30);
		}
	}
}

void HD44780::Send_Num(int16_t Num)
{
	uint8_t count = 0;
	uint8_t ch[5];
	uint16_t Num_32768 = -32768;
	
	if(Num < 0 && Num != -32768)
	{
		Num *= -1;
		Send_Data('-');
		for(int i = 0; Num; i++)
		{
			ch[i] = Num % 10;
			Num = Num / 10;
			count++;
		}
		
		for(int i = count - 1; i >= 0; i--)
		{
			Send_Data(ch[i] + 0x30);
		}
	}
	else if(Num == -32768)
	{
		Send_Data('-');
		for(int i = 0; Num_32768; i++)
		{
			ch[i] = Num_32768 % 10;
			Num_32768 = Num_32768 / 10;
			count++;
		}
		
		for(int i = count - 1; i >= 0; i--)
		{
			Send_Data(ch[i] + 0x30);
		}
	}
	else
	{
		for(int i = 0; (Num) || ((!Num) & (!count)); i++)
		{
			ch[i] = Num % 10;
			Num = Num / 10;
			count++;
		}
		
		for(int i = count - 1; i >= 0; i--)
		{
			Send_Data(ch[i] + 0x30);
		}
	}
}

void HD44780::Send_Num(int32_t Num)
{
	uint8_t count = 0;
	uint8_t ch[10];
	uint32_t Num2billion = 2147483648;
	
	if(Num < 0 && Num != -2147483648)
	{
		Num *= -1;
		Send_Data('-');
		for(int i = 0; Num; i++)
		{
			ch[i] = Num % 10;
			Num = Num / 10;
			count++;
		}
		
		for(int i = count - 1; i >= 0; i--)
		{
			Send_Data(ch[i] + 0x30);
		}
	}
	else if(Num == -2147483648)
	{
		Send_Data('-');
		for(int i = 0; Num2billion; i++)
		{
			ch[i] = Num2billion % 10;
			Num2billion = Num2billion / 10;
			count++;
		}
		
		for(int i = count - 1; i >= 0; i--)
		{
			Send_Data(ch[i] + 0x30);
		}
	}
	else
	{
		for(int i = 0; (Num) || ((!Num) & (!count)); i++)
		{
			ch[i] = Num % 10;
			Num = Num / 10;
			count++;
		}
		
		for(int i = count - 1; i >= 0; i--)
		{
			Send_Data(ch[i] + 0x30);
		}
	}
}

void HD44780::Set_CGRAM(uint8_t addr)
{
	Send_Cmd(0x40 | (addr & 0x3F));
}

void HD44780::Set_Symbol(uint8_t* symbol, uint8_t StringsNumber, uint8_t addrDDRAM, uint8_t addrCGRAM)
{
	Set_CGRAM(addrCGRAM);
	for (uint8_t i = 0; i < StringsNumber; i++)
	{
		Send_Data(*(symbol + i));
	}
	Send_Cmd(0x80 | addrDDRAM);
	Send_Data(addrCGRAM / 8);
}

void HD44780::Send_Hex(uint8_t* hex, uint8_t bytes)
{
	uint8_t ch[16];
	
	for(int i = 0; i < bytes ; i++)
	{
		ch[i*2] = *(hex + i) % 16;
		ch[i*2+1] =  *(hex + i) / 16;
	}
	
	for(int i = bytes * 2 - 1; i >= 0; i--)
	{
		if(ch[i] < 10) Send_Data(ch[i] + 0x30);
		else Send_Data(ch[i] + 0x37);
	}
}