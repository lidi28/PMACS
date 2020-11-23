#include "Nema17.h"

void m17_init1(void)
{
	// Nema17 режим для STEP и DIR как OUTPUT
	NEMA_DDR  |= 1 << STEP1;
	NEMA_DDR  |= 1 << DIR1;

	// начальные значения Nema17
	NEMA_PORT |= (1 << STEP1); // устанавливаем 1
	NEMA_PORT &= ~(1 << DIR1); // устанавливаем 0
}

void m17_left1(void)
{
	// направление вращения
	NEMA_PORT |= (1 << DIR1); // устанавливаем 1
	
	// сделать 1 оборот
	for(int j = 0; j < STEP_ROUND; j++) 
	{
		NEMA_PORT |= (1 << STEP1); // устанавливаем 1
		TIME;
		NEMA_PORT &= ~(1 << STEP1); // устанавливаем 0
		TIME;	
	}
}

void m17_right1(void)
{
	// направление вращения
	NEMA_PORT &= ~(1 << DIR1); // устанавливаем 0
	
	// сделать 1 оборот
	for(int j = 0; j < STEP_ROUND; j++) 
	{
		NEMA_PORT |= (1 << STEP1); // устанавливаем 1
		TIME;
		NEMA_PORT &= ~(1 << STEP1); // устанавливаем 0
		TIME;
	}
}

void m17_init2(void)
{
	// Nema17 режим для STEP и DIR как OUTPUT
	NEMA_DDR  |= 1 << STEP2;
	NEMA_DDR  |= 1 << DIR2;

	// начальные значения Nema17
	NEMA_PORT |= (1 << STEP2); // устанавливаем 1
	NEMA_PORT &= ~(1 << DIR2); // устанавливаем 0
}

void m17_left2(void)
{
	// направление вращения
	NEMA_PORT |= (1 << DIR2); // устанавливаем 1
	
	// сделать 1 оборот
	for(int q = 0; q < STEP_ROUND; q++) 
	{
		NEMA_PORT |= (1 << STEP2); // устанавливаем 1
		TIME;
		NEMA_PORT &= ~(1 << STEP2); // устанавливаем 0
		TIME;	
	}
}

void m17_right2(void)
{
	// направление вращения
	NEMA_PORT &= ~(1 << DIR2); // устанавливаем 0
	
	// сделать 1 оборот
	for(int q = 0; q < STEP_ROUND; q++) 
	{
		NEMA_PORT |= (1 << STEP2); // устанавливаем 1
		TIME;
		NEMA_PORT &= ~(1 << STEP2); // устанавливаем 0
		TIME;
	}
}

void m17_init3(void)
{
	// Nema17 режим для STEP и DIR как OUTPUT
	NEMA_DDR  |= 1 << STEP3;
	NEMA_DDR  |= 1 << DIR3;

	// начальные значения Nema17
	NEMA_PORT |= (1 << STEP3); // устанавливаем 1
	NEMA_PORT &= ~(1 << DIR3); // устанавливаем 0
}

void m17_left3(void)
{
	// направление вращения
	NEMA_PORT |= (1 << DIR3); // устанавливаем 1
	
	// сделать 1 оборот
	for(int w = 0; w < STEP_ROUND; w++) 
	{
		NEMA_PORT |= (1 << STEP3); // устанавливаем 1
		TIME;
		NEMA_PORT &= ~(1 << STEP3); // устанавливаем 0
		TIME;
	}
}

void m17_right3(void)
{
	// направление вращения
	NEMA_PORT &= ~(1 << DIR3); // устанавливаем 0
		
	// сделать 1 оборот
	for(int w = 0; w < STEP_ROUND; w++) 
	{
		NEMA_PORT |= (1 << STEP3); // устанавливаем 1
		TIME;
		NEMA_PORT &= ~(1 << STEP3); // устанавливаем 0
		TIME;
	}
}	