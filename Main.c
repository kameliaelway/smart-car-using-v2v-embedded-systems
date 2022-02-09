/*
 * Main.c
 *
 *  Created on: 15 Apr 2021
 *      Author: DELL
 */

#include "../HAL/ULTRASONIC.h"
#include "../HAL/BT.h"
#include "../HAL/DC_Motor.h"

#include "../ServiceLayer/PLATFORM_TYPES.h"
#include "../ServiceLayer/Scheduler.h"

uint8 Obstacle1 = 0;
uint8 Obstacle2 = 0;

void Task_2ms(void)
{

}
void Task_5ms(void)
{

}
void Task_10ms(void)
{

	char Data=0;
	static uint8 Speed =128;

	Data = BT_Rec_Byte();

	switch (Data)
	{

	case 'F':
		if(Obstacle1 != 1)
		{
			DC_Motor_Drive_OUT(FORWARD,Speed);
		}
		break;
	case 'B':
		if(Obstacle2 != 1)
		{
			DC_Motor_Drive_OUT(REVERSE,Speed);
		}
		break;
	case 'R':
		DC_Motor_Drive_OUT(RIGHT,Speed);
		break;
	case 'L':
		DC_Motor_Drive_OUT(LEFT,Speed);
		break;

	case 'A':
		if(Speed<=250)
		{
			Speed+=5;
		}
		else
		{
			/* Do nothing */
		}
		break;

	case 'D':
		if(Speed >= 5)
		{
			Speed-=5;
		}
		else
		{
			/* Do nothing */
		}
		break;

	case 'S':
		DC_Motor_Drive_OUT(STOP,Speed);
		break;

	default:
		/* Do nothing */
		break;
	}

}
void Task_100ms(void)
{
	long Distance1 = 0;
	long Distance2 = 0;

	Distance1 = UltraSonic_read(ULTRASONIC_1);
	if(Distance1 < 30)
	{
		Obstacle1 = 1;
	}
	else
	{
		Obstacle1 = 0;
	}


	Distance2 = UltraSonic_read(ULTRASONIC_2);
	if(Distance2 < 30)
	{
		Obstacle2 = 1;
	}
	else
	{
		Obstacle2 = 0;
	}

}
void Task_500ms(void)
{


}


void Task_1000ms(void)
{

}


int main(void)
{
	UltraSonic_init(ULTRASONIC_1);
	UltraSonic_init(ULTRASONIC_2);

	BT_Init(9600);

	DC_Motor_Drive_Init();


	/* Scheduler Initialisation */
	Scheduler_init();

	Scheduler_2ms_Task_Create(Task_2ms);
	Scheduler_5ms_Task_Create(Task_5ms);
	Scheduler_10ms_Task_Create(Task_10ms);
	Scheduler_100ms_Task_Create(Task_100ms);
	Scheduler_500ms_Task_Create(Task_500ms);
	Scheduler_1000ms_Task_Create(Task_1000ms);

	Scheduler_Run();

	while(1)
	{
		/* Do Nothing */
	}

	return 0;
}
