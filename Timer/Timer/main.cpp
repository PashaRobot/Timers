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
	PORTD_DIR = 0b00001000; // ����������� ���� D �� �����
	TCD0_CCA = 49999;  // ������ ������ � ������� ��������� ������ �
	TCD0_CTRLB = TC_WGMODE_FRQ_gc | (1 << 7); // �������� ����� ��������� ������� � ��������� ������������� �������� ����� ����� ������ ����� ��� ��������� �������
	TCD0_CTRLA = TC_CLKSEL_DIV2_gc; // ��������� ������, ����� ������������
}

void TCD1_init()
{
	TCD1_PER = 65535; // �������� ������ ������� 
	EVSYS_CH0MUX = EVSYS_CHMUX_PORTD_PIN3_gc; // �������� ����� ������� ������� � �������� ����� ������ �� ������� �������
	TCD1_CTRLD = TC_EVACT_FRQ_gc | TC_EVSEL_CH0_gc;  // �������� ����� ��������� ������� FRQ � ��������������� ����� ������� ������� � �������� ��������� ������� ��� �������
	TCD1_CTRLB = TC1_CCAEN_bm; // ��������� ������������ ������� �� ������ ������� � 
	TCD0_INTCTRLB = TC0_CCAINTLVL_gm; // ��������� ���������� �� ������� ��� ������ �, ����� ��� ���������
	TCD1_CTRLA = TC_CLKSEL_DIV4_gc; // ��������� ������, ����� ������������
}

int main(void)
{
	TCD0_init();
	TCD1_init();
	PMIC_CTRL = PMIC_HILVLEN_bm|PMIC_MEDLVLEN_bm|PMIC_LOLVLEN_bm; // ��������� ���������� ���� �������
	sei();
	while(1)
	{
		//����� ��� � ������ �� ������ � �������� ���������
	}
}

ISR(TCD0_CCA_vect)
{
	FirstDisplay.Set_X_Y(1, 1);
	_delay_ms(1);
	FirstDisplay.Send_Num((uint32_t)((F_CPU / 4) / TCD1_CCA));
	_delay_ms(1);
}