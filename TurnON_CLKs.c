#include "MKL27Z644.h"
#include "TurnON_CLKs.h"

void  ClockPORTS_vfnDriverInit(void)
{
	SIM->SCGC5=0x3E00;
}
