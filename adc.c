
#include "avr/io.h" /* To use the ADC Registers */
#include <avr/interrupt.h> /* For ADC ISR */
#include "adc.h"
#include "common_macros.h" /* To use the macros like SET_BIT */

#if ADC_ENABLE_INTERRUPT
volatile uint16 g_adcResult = 0;

	ISR(ADC_vect)
	{
		g_adcResult = ADC;
	}
#endif

void ADC_init(const AdcConfigType * config_ptr)
{
	ADMUX = (config_ptr->voltage<<REFS0)|(ADC_LEFT_ADJUST<<ADLAR)&~(0x1f);
// ADATE, autotriggerenable- ADIE, interrupt enable  
	ADCSRA =
	((config_ptr->autoTrigger==DISABLED?0:config_ptr->autoTrigger)<<ADATE)    
	#if ADC_ENABLE_INTERRUPT
	|(1<<ADIE)
	#endif
	|(config_ptr->prescaler<<ADPS0)
	|(1<<ADEN);
}


uint16 ADC_readChannel(uint8 channel_num)
{
	channel_num &= 0x07; /* Input channel number must be from 0 --> 7 */
	ADMUX &= 0xE0; /* Clear first 5 bits in the ADMUX (channel number MUX4:0 bits) before set the required channel */
	ADMUX = ADMUX | channel_num; /* Choose the correct channel by setting the channel number in MUX4:0 bits */
	SET_BIT(ADCSRA,ADSC); /* Start conversion write '1' to ADSC */
#if ADC_ENABLE_INTERRUPT==0
	while(BIT_IS_CLEAR(ADCSRA,ADIF)); /* Wait for conversion to complete, ADIF becomes '1' */
	SET_BIT(ADCSRA,ADIF); /* Clear ADIF by write '1' to it :) */
	return ADC; /* Read the digital value from the data register */
#endif
        return 1;
}

void ADC_enable(void)
{
        SET_BIT(ADCSRA, ADEN);
}

ADC_disable()
{
        CLEAR_BIT(ADCSRA, ADEN);
}



/*  
    ADMUX: ADC MULTIPLEXER SELECTION
    REF1:0  00 AREF, INTERNAL VREF TURNED OFF
            AVCC     - 01 AVCC WITH EXTERNAL CAPACITOR AREF PIN
            RESERVED - 10 RESERVED
            INTERNAL - 2.56

    ADLAR    - ADC LEFT ADJUST 0 DEFAULT
    MUX4-0   - TO CHOOSE WHICH ADC CHANNEL, 00111, 7TH CHANNEL

    ADCSRA: adc control and stauts register
    ADEN     - ADC ENABLE
    ADSC     - ADC START CONVERSION
    ADATE    - ADC AUTO TRIGGER ENABLE
    ADIF     - ADC INTERRUPT FLAG
    ADIE     - ADC INTERRUPT ENABLE
    ADPS2:0   - PRESCALER SELECT
            0    2
            1    2
            2    4
            3    8
            4    16
            5    32
            6    64
            7    128
    
    ADC:   DATA REGISTER uint32

    SFIOR: special function io register adts2:0 bits control auto trigger source
    ADTS2:0  - 0 FREE RUNNING
    ADTS2:0  - 1 analog comparator
    ADTS2:0  - 2 external interrupt int0
    ADTS2:0  - 3 counter0 compare match
    ADTS2:0  - 4 counter0 overflow
    ADTS2:0  - 5 counter1 compare match
    ADTS2:0  - 6 counter1 overflow
    ADTS2:0  - 7 counter1 capture event (icu)
 */ 
