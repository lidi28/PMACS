#include "SM.h"

void sm_init(void)
{
	SM_DDR |= (1 << IN4)|(1 << IN3)|(1 << IN2)|(1 << IN1);
	SM_PORT &= ~((1 << IN4)|(1 << IN3)|(1 << IN2)|(1 << IN1));
}

void sm_set1(void)
{
	SM_PORT |= 1 << IN1;
	SM_PORT &= ~(1 << IN2);
	SM_PORT &= ~(1 << IN3);
	SM_PORT &= ~(1 << IN4);
	SM_DELAY;
}

void sm_set2(void)
{
	SM_PORT |= 1 << IN1;
	SM_PORT |= 1 << IN4;
	SM_PORT &= ~(1 << IN2);
	SM_PORT &= ~(1 << IN3);
	SM_DELAY;
}

void sm_set3(void)
{
	SM_PORT |= 1 << IN4;
	SM_PORT &= ~(1 << IN1);
	SM_PORT &= ~(1 << IN2);
	SM_PORT &= ~(1 << IN3);
	SM_DELAY;
}

void sm_set4(void)
{
	SM_PORT |= 1 << IN4;
	SM_PORT |= 1 << IN3;
	SM_PORT &= ~(1 << IN1);
	SM_PORT &= ~(1 << IN2);
	SM_DELAY;
}

void sm_set5(void)
{
	SM_PORT |= 1 << IN3;
	SM_PORT &= ~(1 << IN1);
	SM_PORT &= ~(1 << IN2);
	SM_PORT &= ~(1 << IN4);
	SM_DELAY;
}

void sm_set6(void)
{
	SM_PORT |= 1 << IN3;
	SM_PORT |= 1 << IN2;
	SM_PORT &= ~(1 << IN1);
	SM_PORT &= ~(1 << IN4);
	SM_DELAY;
}

void sm_set7(void)
{
	SM_PORT |= 1 << IN2;
	SM_PORT &= ~(1 << IN1);
	SM_PORT &= ~(1 << IN3);
	SM_PORT &= ~(1 << IN4);
	SM_DELAY;
}

void sm_set8(void)
{
	SM_PORT |= 1 << IN2;
	SM_PORT |= 1 << IN1;
	SM_PORT &= ~(1 << IN3);
	SM_PORT &= ~(1 << IN4);
	SM_DELAY;
}

void sm_forward(void)
{
	sm_set1();
	sm_set2();
	sm_set3();
	sm_set4();
	sm_set5();
	sm_set6();
	sm_set7();
	sm_set8();
}

void sm_back(void)
{
	sm_set8();
	sm_set7();
	sm_set6();
	sm_set5();
	sm_set4();
	sm_set3();
	sm_set2();
	sm_set1();
}