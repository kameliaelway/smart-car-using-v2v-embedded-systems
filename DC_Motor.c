/*
 * DC_Motor.c
 *
 *  Created on: 15 Apr 2021
 *      Author: DELL
 */

#include "DC_Motor.h"


void DC_Motor_Drive_Init(void)
{
	/* Configure pins as output */
	SET_BIT(MOTOR_DRV_A_DDR,MOTOR_DRV_A);
	SET_BIT(MOTOR_DRV_B_DDR,MOTOR_DRV_B);
	SET_BIT(MOTOR_DRV_C_DDR,MOTOR_DRV_C);
	SET_BIT(MOTOR_DRV_D_DDR,MOTOR_DRV_D);

	PWM_init();

	/* Stop the Motor */
	CLEAR_BIT(MOTOR_DRV_A_PORT,MOTOR_DRV_A);
	CLEAR_BIT(MOTOR_DRV_B_PORT,MOTOR_DRV_B);
	CLEAR_BIT(MOTOR_DRV_C_PORT,MOTOR_DRV_C);
	CLEAR_BIT(MOTOR_DRV_D_PORT,MOTOR_DRV_D);

	PWM_Duty_Cycle(0);
}


void DC_Motor_Drive_OUT(JoyStick_State_t State,  uint8 Speed)
{
	switch (State)
	{
	case STOP:

		/* Stop the Motor */
		CLEAR_BIT(MOTOR_DRV_A_PORT,MOTOR_DRV_A);
		CLEAR_BIT(MOTOR_DRV_B_PORT,MOTOR_DRV_B);
		CLEAR_BIT(MOTOR_DRV_C_PORT,MOTOR_DRV_C);
		CLEAR_BIT(MOTOR_DRV_D_PORT,MOTOR_DRV_D);

		PWM_Duty_Cycle(0);

		break;

	case LEFT:

		PWM_Duty_Cycle(Speed);
		SET_BIT(MOTOR_DRV_A_PORT,MOTOR_DRV_A); // PORTB |= (1<<PB4)
		SET_BIT(MOTOR_DRV_D_PORT,MOTOR_DRV_D);
		CLEAR_BIT(MOTOR_DRV_B_PORT,MOTOR_DRV_B);
		CLEAR_BIT(MOTOR_DRV_C_PORT,MOTOR_DRV_C);
		break;

	case RIGHT:

		PWM_Duty_Cycle(Speed);
		CLEAR_BIT(MOTOR_DRV_A_PORT,MOTOR_DRV_A);
		CLEAR_BIT(MOTOR_DRV_D_PORT,MOTOR_DRV_D);
		SET_BIT(MOTOR_DRV_B_PORT,MOTOR_DRV_B);
		SET_BIT(MOTOR_DRV_C_PORT,MOTOR_DRV_C);
		break;

	case FORWARD:

		PWM_Duty_Cycle(Speed);
		CLEAR_BIT(MOTOR_DRV_B_PORT,MOTOR_DRV_B);
		CLEAR_BIT(MOTOR_DRV_D_PORT,MOTOR_DRV_D);
		SET_BIT(MOTOR_DRV_A_PORT,MOTOR_DRV_A);
		SET_BIT(MOTOR_DRV_C_PORT,MOTOR_DRV_C);
		break;

	case REVERSE:

		PWM_Duty_Cycle(Speed);
		SET_BIT(MOTOR_DRV_B_PORT,MOTOR_DRV_B);
		SET_BIT(MOTOR_DRV_D_PORT,MOTOR_DRV_D);
		CLEAR_BIT(MOTOR_DRV_A_PORT,MOTOR_DRV_A);
		CLEAR_BIT(MOTOR_DRV_C_PORT,MOTOR_DRV_C);
		break;

	default:
		break;

	}
}
