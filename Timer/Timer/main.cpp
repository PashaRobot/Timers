/*
 * Timer.cpp
 *
 * Created: 18.10.2021 17:14:55
 * Author : Pavel Bezdelev
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "HD44780.h"

void TCD0_init()
{
	PORTD_DIR = 0xF; // Настраиваем порт D на выход
	TCD0_CCA = 97;  // Задаем период в регистр сравнения канала А 
	TCD0_CTRLB = TC_WGMODE_FRQ_gc | (1 << 7); // Выбираем режим генерации меандра и разрешаем использование таймером линии ввода вывода порта для генерации сигнала 
	TCD0_CTRLA = TC_CLKSEL_DIV1024_gc; // Запускаем таймер, задав предделитель 
}

int main(void)
{
	TCD0_init();
	
	while(1)
	{
		//Висим тут и ничего не делаем в основной программе
	}
}