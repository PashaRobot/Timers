/*
 * ex.2.cpp
 *
 * Created: 06.12.2021 17:59:38
 * Author : Pavel Bezdelev
 */ 

#include <avr/io.h>


#include <avr/io.h>
#include <avr/interrupt.h>
#include "HD44780.h"

void TCD0_init()
{
	PORTD_DIR = 0xF; // ����������� ���� D �� �����
	TCD0_CCA = 49999;  // ������ ������ � ������� ��������� ������ �
	TCD0_CTRLB = TC_WGMODE_FRQ_gc | (1 << 7); // �������� ����� ��������� ������� � ��������� ������������� �������� ����� ����� ������ ����� ��� ��������� �������
	TCD0_CTRLA = TC_CLKSEL_DIV2_gc; // ��������� ������, ����� ������������
}

int main(void)
{
	TCD0_init();
	
	while(1)
	{
		//����� ��� � ������ �� ������ � �������� ���������
	}
}