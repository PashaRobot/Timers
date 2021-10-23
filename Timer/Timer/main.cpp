/*
 * Timer.cpp
 *
 * Created: 18.10.2021 17:14:55
 * Author : Pavel Bezdelev
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "HD44780.h"

void TCD0_init(){
	TCD0_PER = 1953;					//задаем период таймера
	TCD0_INTCTRLA = 3<<TC0_OVFINTLVL_gp;//задаем максимальный уровень прерывания по переполнению
	TCD0_CTRLA = TC_CLKSEL_DIV1024_gc;	//задаем предделитель и одновременно запускаем таймер
}

int main(void)
{
	PORTD_DIRSET = 9;	//настроим на выход 2 линии порта
	PORTD_OUTSET = 8;	//включим светодиод на одной стороне платы
	
	PMIC_CTRL = PMIC_HILVLEN_bm|PMIC_MEDLVLEN_bm|PMIC_LOLVLEN_bm; // разрешаем прерывания всех уровней
	
	sei();				//глобально разрешаем прерывания
	TCD0_init();
	
	while(1)
	{
		//Висим тут и ничего не делаем в основной программе
	}
}

ISR(TCD0_OVF_vect){
	PORTD_OUTTGL = 9; // а светодиоды переключаем по прерыванию раз в секунду
}