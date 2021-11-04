/*
 * Timer.cpp
 *
 * Created: 18.10.2021 17:14:55
 * Author : Pavel Bezdelev
 */ 

#define F_CPU 2000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include "HD44780.h"


HD44780 FirstDisplay(HD44780_Display_Control_ON_OFF_ON_gc, HD44780_Entry_Mode_Set_ON_OFF_gc); 

void TCD0_init()
{
	PORTD_DIR = 0b00001000; // Настраиваем порт D на выход
	TCD0_CCA = 49999;  // Задаем период в регистр сравнения канала А
	TCD0_CTRLB = TC_WGMODE_FRQ_gc | (1 << 7); // Выбираем режим генерации меандра и разрешаем использование таймером линии ввода вывода порта для генерации сигнала
	TCD0_CTRLA = TC_CLKSEL_DIV2_gc; // Запускаем таймер, задав предделитель
}

void TCD1_init()
{
	TCD1_PER = 65535; // Выбираем период таймера 
	EVSYS_CH0MUX = EVSYS_CHMUX_PORTD_PIN3_gc; // Выбираем выход первого таймера в качестве входа одного из каналов событий
	TCD1_CTRLD = TC_EVACT_FRQ_gc | TC_EVSEL_CH0_gc;  // Выбираем режим обработки событий FRQ и соответствующий канал системы событий в качестве источника событий для таймера
	TCD1_CTRLB = TC1_CCAEN_bm; // Разрешаем срабатывание захвата на канале захвата А 
	TCD0_INTCTRLB = TC0_CCAINTLVL_gm; // Разрешаем прерывание по захвату для канала А, задав его приоритет
	TCD1_CTRLA = TC_CLKSEL_DIV4_gc; // Запускаем таймер, задав предделитель
}

int main(void)
{
	TCD0_init();
	TCD1_init();
	PMIC_CTRL = PMIC_HILVLEN_bm|PMIC_MEDLVLEN_bm|PMIC_LOLVLEN_bm; // разрешаем прерывания всех уровней
	sei();
	while(1)
	{
		//Висим тут и ничего не делаем в основной программе
	}
}

ISR(TCD0_CCA_vect)
{
	FirstDisplay.Set_X_Y(1, 1);
	_delay_ms(1);
	FirstDisplay.Send_Num((uint32_t)((F_CPU / 4) / TCD1_CCA));
	_delay_ms(1);
}