#include "ADC_Driver.h"
#include "MKL27Z644.h"
#include <stdio.h>

void ADC_vfnDriverInit(void)
{
	SIM -> SCGC6 = SIM_SCGC6_ADC0(1); /*Activo el reloj para el ADC*/
	PORTE->PCR[20] = PORT_PCR_MUX(0); /*Activo el Puerto E20 como opción de ADC*/
	ADC0->SC1[0] = ADC_SC1_DIFF(0);
	ADC0->CFG1 = ADC_CFG1_MODE(0);
	ADC0->SC2 = ADC_SC2_DMAEN(0);
	ADC0->SC2 = ADC_SC2_ACFE(0);
	ADC0->SC3 = ADC_SC3_ADCO(1);
	ADC0->SC3 |= ADC_SC3_AVGE(1);
	ADC0->SC3 |= ADC_SC3_AVGS(0x3);
}


extern uint_8 ADC_bfnReadADC (uint_8 bChannel, uint_8 *bpADCValue)
{
uint_8 bwValidState= FALSE;
uint_8 *pbwCheckCoco;

	ADC0->SC1[0] = ADC_SC1_ADCH(bChannel);
	pbwCheckCoco = (uint_8 *) (COCO);

	while(!((*pbwCheckCoco)&1))
		{
		*bpADCValue=ADC0->R[0];
		bwValidState= TRUE;
		break;
		}
	return bwValidState;
}

