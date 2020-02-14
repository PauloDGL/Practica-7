#ifndef PWM_H_
#define PWM_H_
	typedef unsigned char uint_8;

	extern void PWM_vfnDriverInit(void);
	extern uint_8 PWM_bfnSetDutyCycle (uint_8 bDutyCycleValue);

	#define TRUE 1;
	#define FALSE 0;

#endif /* PWM_H_ */
