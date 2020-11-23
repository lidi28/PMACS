/*
 * Motors Nema17HS4401 and Nema17HS4023
 */ 

#ifndef NEMA17_H_
#define NEMA17_H_

#include "main.h"

// порт и ddr для мотора
#define NEMA_PORT PORTA
#define NEMA_DDR DDRA

// пины для подключения контактов STEP, DIR 1 мотор
#define STEP1 PINA0
#define DIR1 PINA1

// пины для подключения контактов STEP, DIR 2 мотор
#define STEP2 PINA2
#define DIR2 PINA3

// пины для подключения контактов STEP, DIR 3 мотор
#define STEP3 PINA4
#define DIR3 PINA5

// количество шагов на 1 оборот
#define STEP_ROUND 200

// длительность вращения
#define TIME _delay_ms(100)

void m17_init1(void);
void m17_left1(void);
void m17_right1(void);

void m17_init2(void);
void m17_left2(void);
void m17_right2(void);

void m17_init3(void);
void m17_left3(void);
void m17_right3(void);

#endif /* NEMA17_H_ */