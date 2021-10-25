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
	TCD0_PER = 4199;					//������ ������ �������
	TCD0_INTCTRLA = 3<<TC0_OVFINTLVL_gp;//������ ������������ ������� ���������� �� ������������
	TCD0_CTRLA = 0b00000111; //TC_CLKSEL_DIV1024_gc;	//������ ������������ � ������������ ��������� ������
}

int main(void)
{
	PORTD_DIRSET = 15;	//�������� �� ����� 2 ����� �����
	PORTD_OUTSET = 9;	//������� ��������� �� ����� ������� �����
	
	PMIC_CTRL = PMIC_HILVLEN_bm|PMIC_MEDLVLEN_bm|PMIC_LOLVLEN_bm; // ��������� ���������� ���� �������
	
	sei();				//��������� ��������� ����������
	TCD0_init();
	
	while(1)
	{
		//����� ��� � ������ �� ������ � �������� ���������
	}
}

ISR(TCD0_OVF_vect)
{
	PORTD_OUTTGL = 15; // � ���������� ����������� �� ���������� ��� � �������
}