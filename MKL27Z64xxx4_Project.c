#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL27Z644.h"
#include "fsl_debug_console.h"
#include "TurnON_CLKs.h"
#include "PWM_Driver.h"
#include "ADC_Driver.h"

typedef unsigned long uint_32;

int main(void) {
uint_8 dwADC_Conversion;
uint_8 dwGoodValue;
uint_8 dwGoodPercentage;
uint_8 dwDutyCycle;
uint_32 dwDelay = 350000;

	ClockPORTS_vfnDriverInit();
	ADC_vfnDriverInit();
	PWM_vfnDriverInit();

	while(1)
	{
    dwGoodValue= ADC_bfnReadADC(DAD0, &dwADC_Conversion);
    dwDutyCycle = ((dwADC_Conversion)*(100))*(0.00392); /*We do a simple rule of three*/
    dwGoodPercentage= PWM_bfnSetDutyCycle(dwDutyCycle);
	for (uint_32 dwCuenta=0; dwCuenta < dwDelay; dwCuenta++)
	dwCuenta += 1;
	printf("Does the ADC conversion end \n %d",dwGoodValue);
	printf("\n");
	printf("\n");
	printf("Is the porcentage between 0-100 \n %d",dwGoodPercentage);
	}
    return 0 ;
}
