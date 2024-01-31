#include "gpio.h"
#include "lm35_sensor.h"
#include "motor.h"
#include "lcd.h"
#include "adc.h"
#include "std_types.h"
#include "common_macros.h"

int main(void)
{
	LCD_init();
	DcMotor_Init();

	
	AdcConfigType adc={DISABLED,DIVISION_8,INTERNAL};
	ADC_init(&adc);

	LCD_displayString("FAN is ");
	LCD_moveCursor(1,0);
	LCD_displayString("Temp =     C");

	uint8 temp=0;
	for (;;) 
	{
		temp=LM35_getTemperature();

		if (temp<30) 
			DcMotor_Rotate1(STOP, 0);
		
		else if (temp<60) 
			DcMotor_Rotate1(CLOCKWISE, 25);
		
		else if (temp<90) 
			DcMotor_Rotate1(CLOCKWISE, 50);
		
		else if (temp<120) 
			DcMotor_Rotate1(CLOCKWISE, 75);
		
		else
			DcMotor_Rotate1(CLOCKWISE, 100);
		

		LCD_moveCursor(0,7);
		(temp<30)?LCD_displayString("OFF"):LCD_displayString("ON ");

		/* Writing temperature value in LCD */
		LCD_moveCursor(1,7);
		if(temp >= 100)
			LCD_intgerToString(temp);
		else
		{
			LCD_intgerToString(temp);
			/* In case the digital value is two or one digits print space in the next digit place */
			LCD_displayCharacter(' ');
		}

	}
	
	
}
