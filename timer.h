#pragma once
#include "std_types.h"
#include "avr/io.h"
#include "common_macros.h"
#include "gpio.h"
#define TIMER0_MAX 255

/* 
FOC0  - non pwm operation
wgm00 - wave config
COM00 - Control output compare pin behavior OC0  
CS00  - clock select, select prescaler
TCNT0 - value, current count
OCR0  - compared with tcnt in ctc mode
TIMSK - INTERRUPT MASK REGISTER, contains all masks for all timers, each timer has outputcompare match interrupt enable and overflow interrupt enable
 */

// typedef enum {      // for non-pwm:             |   for pwm:   
//     NORMAL,         //  OC0 disconnected        |   OC0 disconnected
//     TOGGLE,         //  toggle on compare match |   reserved
//     CLEAR,          //  clear on...             |   non inverting mode, clear oc0 on compare match
//     SET             //  set on...               |   inverting mode
// }OutputCompareMode;

// typedef enum {
//     NOCLOCK,
//     CLK_1,
//     CLK_8,
//     CLK_64,
//     CLK_256,
//     CLK_1024,
//     FALLING,    // external clock on T0 pin falling edge
//     RISING      // external clock on T0 pin rising edge
// }ClockPrescale;


// typedef enum {
//     OVERFLOW,
//     PHASE_CORRECT,
//     CTC,
//     FAST_PWM
// }WaveFormMode;



// void Timer_Init();

void PWM_Timer0_Start(uint8 dutyCycle);
