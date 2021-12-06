/*
 * ex.6.cpp
 *
 * Created: 06.12.2021 18:05:24
 * Author : Pavel Bezdelev
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "HD44780.h"

HD44780 FirstDisplay(HD44780_Display_Control_ON_OFF_ON_gc, HD44780_Entry_Mode_Set_ON_OFF_gc);

void TCD0_init()
{
	TCD0_PER = 0x00FF;			
	EVSYS_CH0MUX = EVSYS_CHMUX_PORTB_PIN2_gc;
	PORTB_PIN2CTRL = PORT_OPC_PULLUP_gc;// | PORT_ISC_LEVEL_gc;
	PORTB_PIN3CTRL = PORT_OPC_PULLUP_gc;// | PORT_ISC_LEVEL_gc;
	EVSYS_CH0CTRL = EVSYS_QDEN_bm | EVSYS_DIGFILT_8SAMPLES_gc;
	TCD0_CTRLD = TC_EVACT_QDEC_gc | TC_EVSEL_CH0_gc;
	TCD0_CTRLA = TC_CLKSEL_DIV1_gc;
}

int main(void)
{
	TCD0_init();
	
	while (1)
	{
		FirstDisplay.Set_X_Y(1, 1);
		_delay_ms(1);
		FirstDisplay.Send_Num(TCD0_CNT);
		_delay_ms(50);
	}
}