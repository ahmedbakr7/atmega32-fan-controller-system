
#ifndef ADC_H_
#define ADC_H_

#include "std_types.h"
#include "avr/io.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define ADC_MAXIMUM_VALUE       1023
#define ADC_REF_VOLT_VALUE      2.56
#define ADC_ENABLE_INTERRUPT    0
#define ADC_LEFT_ADJUST         0        // set one to left adjust
// #define ADC_REFERENCE_SELECTION 0        // AREF=0,AVCC=1,RESERVED=2,INTERNAL=3
//                                          AVCC internal capacitor at aref pin, internal 2.56v with external capacitor at aref pin
typedef enum {           
    AREF,                               
    AVCC,                               
    INTERNAL=3                               
}ADC_REFERENCE_SELECTION;           

typedef enum {
    DIVISION_2,
    DIVISION_4=2,
    DIVISION_8,
    DIVISION_16,
    DIVISION_32,
    DIVISION_64,
    DIVISION_128
}ADC_PRESCALER;

typedef enum {
    FREE_RUNNING, 
    ANALOG_COMPARATOR,
    EXT0,
    TIMER0_COMP,
    TIMER0_OVF,
    TIMER1_COMPB,
    TIMER1_OVERFLOW,
    TIMER1_CAPTURE_EVENT,
    DISABLED
}ADC_AUTOTRIGGER_SOURCE;

typedef struct {
    uint8 autoTrigger;  // if more than 7 then auto trigger is disabled, else set the adst bits
    ADC_PRESCALER prescaler;
    ADC_REFERENCE_SELECTION voltage;
}AdcConfigType;


#if ADC_ENABLE_INTERRUPT
/* Extern Public global variables to be used by other modules */
extern volatile uint16 g_adcResult;
#endif

/*
 * Description :
 * Function responsible for initialize the ADC driver.
 */
void ADC_init(const AdcConfigType *);
/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 */
uint16 ADC_readChannel(uint8 channel_num);


void ADC_enable(void);

void ADC_disable(void);

#endif /* ADC_H_ */

