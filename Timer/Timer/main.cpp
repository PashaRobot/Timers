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
	PORTD_DIR = 0xF; // ����������� ���� D �� �����
	TCD0_CCA = 97;  // ������ ������ � ������� ��������� ������ � 
	TCD0_CTRLB = TC_WGMODE_FRQ_gc | (1 << 7); // �������� ����� ��������� ������� � ��������� ������������� �������� ����� ����� ������ ����� ��� ��������� ������� 
	TCD0_CTRLA = TC_CLKSEL_DIV1024_gc; // ��������� ������, ����� ������������ 
}

int main(void)
{
	TCD0_init();
	
	while(1)
	{
		//����� ��� � ������ �� ������ � �������� ���������
	}
}