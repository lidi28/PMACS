/*
 * Motor 28YBJ-48
 */ 

#ifndef SM_H_
#define SM_H_

#include "main.h"

#define SM_PORT PORTB
#define SM_DDR DDRB

#define IN1 PINB4
#define IN2 PINB5
#define IN3 PINB5
#define IN4 PINB7

#define SM_DELAY _delay_ms(5)

void sm_init(void);
void sm_set1(void);
void sm_set2(void);
void sm_set3(void);
void sm_set4(void);
void sm_set5(void);
void sm_set6(void);
void sm_set7(void);
void sm_set8(void);
void sm_forward(void);
void sm_back(void);

#endif /* SM_H_ */