
#include "timer.h"

// ISR(TIMER0_OVF_vect){}
// ISR(TIMER0_COMP_vect){}
// ISR(TIMER1_OVF_vect){}
// ISR(TIMER1_COMPA_vect){}
// ISR(TIMER1_COMPB_vect){}
// ISR(TIMER1_CAPT_vect){}
// ISR(TIMER2_OVF_vect){}
// ISR(TIMER2_COMP_vect){}

void PWM_Timer0_Start(uint8 dutyCycle)
{
    OCR0= TIMER0_MAX*(dutyCycle/100.0);
    GPIO_setupPinDirection(PORTB_ID, PIN3_ID, PIN_OUTPUT);
    // SET_BIT(TCCR0, FOC0);
    SET_BIT(TCCR0, WGM01);    // PWM MODE
    SET_BIT(TCCR0, WGM00);
    SET_BIT(TCCR0, COM01);   // NON INVERTING
    SET_BIT(TCCR0, CS01);   // prescaler 8
}


