#include "MKL27Z644.h"
#include "PWM_Driver.h"

void PWM_vfnDriverInit(void)
{
	SIM->SCGC6 |= SIM_SCGC6_TPM1(1); /*Activation of TPM clocks*/
	SIM->SCGC6 |= SIM_SCGC6_TPM2(1);

	PORTB->PCR[18] |= PORT_PCR_MUX(3); /*Declarations of the PORTS as PWM*/
	PORTB->PCR[19] |= PORT_PCR_MUX(3);
	PORTA->PCR[13] |= PORT_PCR_MUX(3);

	SIM->SOPT2 = SIM_SOPT2_TPMSRC(3); /*We indicate that the TPM will use the 8 MHz Clock*/

	TPM2->SC = TPM_SC_CMOD(1);
	TPM2->SC |= TPM_SC_CPWMS(1);
	TPM2->SC |= TPM_SC_PS(7);
	TPM1->SC = TPM_SC_CMOD(1);
	TPM1->SC |= TPM_SC_CPWMS(1);
	TPM1->SC |= TPM_SC_PS(7);

	TPM1->CNT = 0; /*We define our CNT and our MOD according to the formula (16 ms = 2*MOD*1/62500)*/
	TPM1->MOD = 520;
	TPM2->CNT = 0;
	TPM2->MOD = 520;

	TPM1->CONTROLS[1].CnSC = 40;
	TPM2->CONTROLS[0].CnSC = 40;
	TPM2->CONTROLS[1].CnSC = 40;

	TPM2->CONF |= TPM_CONF_DBGMODE(3); /*We indicate to the TPM to keep working while the programm is running*/
	TPM1->CONF |= TPM_CONF_DBGMODE(3);
}

uint_8 PWM_bfnSetDutyCycle (uint_8 bDutyCycleValue)
{
uint_8 dwCorrectRange;
	if((bDutyCycleValue>=0)&&(bDutyCycleValue<=25))
	{
		/*Color White*/
		TPM2->CONTROLS[0].CnV = 0;
		TPM2->CONTROLS[1].CnV = 0;
		TPM1->CONTROLS[1].CnV = 0;
	}
	else if((bDutyCycleValue>=26)&&(bDutyCycleValue<=76))
	{
		/*Color Blue*/
		TPM2->CONTROLS[0].CnV = 520;
		TPM2->CONTROLS[1].CnV = 520;
		TPM1->CONTROLS[1].CnV = 0;
	}
	else if((bDutyCycleValue>=77)&&(bDutyCycleValue<=90))
	{
		/*Color Yellow*/
		TPM2->CONTROLS[0].CnV = 0;
		TPM2->CONTROLS[1].CnV = 0;
		TPM1->CONTROLS[1].CnV = 520;
	}
	else if((bDutyCycleValue>=91)&&(bDutyCycleValue<=100))
	{
		/*Color Purple*/
		TPM2->CONTROLS[0].CnV = 261;
		TPM2->CONTROLS[1].CnV = 520;
		TPM1->CONTROLS[1].CnV = 261;
	}

	if((bDutyCycleValue>=0)&&(bDutyCycleValue<=100))
	{
		dwCorrectRange=TRUE;
	}
	else if(bDutyCycleValue>=101)
	{
		dwCorrectRange=FALSE;
	}
return dwCorrectRange;
}

