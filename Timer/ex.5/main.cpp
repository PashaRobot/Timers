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
	PORTD_DIR = 0b00000001; // ����������� ���� D �� �����
	TCD0_PER = 39999; // ������ ������ � ������� ������� �������� ��������� �������
	TCD0_CCA = 4999;  // ������ ������ � ������� ��������� ������ � �������� ��������� ����������
	TCD0_CTRLB = TC_WGMODE_SINGLESLOPE_gc | TC0_CCAEN_bm; // �������� ����� ������������� ��� � ��������� ������������� �������� ����� ����� ������ ����� ��� ��������� �������
	TCD0_CTRLA = TC_CLKSEL_DIV1_gc; // ��������� ������, ����� ������������
}

void TCD1_init()
{
	TCD1_PER = 65535; // �������� ������ ������� 
	EVSYS_CH0MUX = EVSYS_CHMUX_PORTD_PIN0_gc; // �������� ����� ������� ������� � �������� ����� ������ �� ������� �������
	TCD1_CTRLD = TC_EVACT_PW_gc | TC_EVSEL_CH0_gc;  // �������� ����� ��������� ������� PW � ��������������� ����� ������� ������� � �������� ��������� ������� ��� �������
	TCD1_CTRLB = TC1_CCAEN_bm; // ��������� ������������ ������� �� ������ ������� � 
	TCD0_INTCTRLB = TC0_CCAINTLVL_gm; // ��������� ���������� �� ������� ��� ������ �, ����� ��� ���������
	TCD1_CTRLA = TC_CLKSEL_DIV1_gc; // ��������� ������, ����� ������������
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
	FirstDisplay.Send_Num((uint8_t)(TCD1_CCA / (F_CPU / 10000)));
	_delay_ms(1);
	FirstDisplay.Send_String("E-1");
}