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
	while (*(str+i))    // Цикл действует пока не дойдет до 0, который стоит в конце строки
	{
		switch(*(str+i))
		{
			case 'А': Send_Data('A'); break;
			case 'Б': Send_Data(0xA0); break;
			case 'В': Send_Data('B'); break;
			case 'Г': Send_Data(0xA1); break;
			case 'Д': Send_Data(0xE0); break;
			case 'Е': Send_Data('E'); break;
			case 'Ё': Send_Data(0xA2); break;
			case 'Ж': Send_Data(0xA3); break;
			case 'З': Send_Data(0xA4); break;
			case 'И': Send_Data(0xA5); break;	
			case 'Й': Send_Data(0xA6); break;
			case 'К': Send_Data('K'); break;
			case 'Л': Send_Data(0xA7); break;
			case 'М': Send_Data('M'); break;
			case 'Н': Send_Data('H'); break;
			case 'О': Send_Data('O'); break;
			case 'П': Send_Data(0xA8); break;
			case 'Р': Send_Data('P'); break;
			case 'С': Send_Data('C'); break;
			case 'Т': Send_Data('T'); break;
			case 'У': Send_Data(0xA9); break;
			case 'Ф': Send_Data(0xAA); break;
			case 'Х': Send_Data('X'); break;
			case 'Ц': Send_Data(0xE1); break;
			case 'Ч': Send_Data(0xAB); break;
			case 'Ш': Send_Data(0xAC); break;
			case 'Щ': Send_Data(0xE2); break;
			case 'Ъ': Send_Data(0xAD); break;
			case 'Ы': Send_Data(0xAE); break;
			case 'Ь': Send_Data(0x62); break;
			case 'Э': Send_Data(0xAF); break;
			case 'Ю': Send_Data(0xB0); break;
			case 'Я': Send_Data(0xB1); break;
			case 'а': Send_Data('a'); break;
			case 'б': Send_Data(0xB2); break;
			case 'в': Send_Data(0xB3); break;
			case 'г': Send_Data(0xB4); break;
			case 'д': Send_Data(0xE3); break;
			case 'е': Send_Data('e'); break;
			case 'ё': Send_Data(0xB5); break;
			case 'ж': Send_Data(0xB6); break;
			case 'з': Send_Data(0xB7); break;
			case 'и': Send_Data(0xB8); break;
			case 'й': Send_Data(0xB9); break;
			case 'к': Send_Data(0xBA); break;
			case 'л': Send_Data(0xBB); break;
			case 'м': Send_Data(0xBC); break;
			case 'н': Send_Data(0xBD); break;
			case 'о': Send_Data('o'); break;
			case 'п': Send_Data(0xBE); break;
			case 'р': Send_Data('p'); break;
			case 'с': Send_Data('c'); break;
			case 'т': Send_Data(0xBF); break;
			case 'у': Send_Data('y'); break;
			case 'ф': Send_Data(0xE4); break;
			case 'х': Send_Data('x'); break;
			case 'ц': Send_Data(0xE5); break;
			case 'ч': Send_Data(0xC0); break;
			case 'ш': Send_Data(0xC1); break;
			case 'щ': Send_Data(0xE6); break;
			case 'ъ': Send_Data(0xC2); break;
			case 'ы': Send_Data(0xC3); break;
			case 'ь': Send_Data(0xC4); break;
			case 'э': Send_Data(0xC5); break;
			case 'ю': Send_Data(0xC6); break;
			case 'я': Send_Data(0xC7); break;
				
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
	// Реализация с выводом нулей
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
	// Реализация с выводом нулей
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
	// Реализация с выводом нулей
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