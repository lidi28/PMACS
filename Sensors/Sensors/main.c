
/*** Практическое применение термодатчиков DS18B20. Простой термометр ***/
#include <avr/io.h>
#define F_CPU 16000000UL    // Частота - 16MHz
#define baudrate 9600L
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>


//setup parameters
#define DHT22_DDR DDRC
#define DHT22_PORT PORTC
#define DHT22_PIN PINC
#define DHT22_INPUTPIN PC3

int8_t dht22_gettemperature();
int8_t dht22_gethumidity();


#define DHT22_ERROR 255

unsigned char Temp_H = 0,Temp_L = 0,OK_Flag = 0,temp_flag;

/*** Главная функция ***/
int main(void)
{
	
	char a = ' ';
	char b = ' ';
	char c = ' ';
	char d = ' ';
	unsigned int tempint = 0,tempint1,tempint2,tempint3; // переменные для целого значения температуры
	unsigned int temppoint = 0,temppoint1; // переменные для дробного значения температуры
	sei(); //глобально разрешаем прерывания
	
	while(1)
	{
		
		DS18B20_init();        // инициализация DS18B20
		write_18b20(0xCC);     // проверка кода датчика
		write_18b20(0x44);     // запуск температурного преобразования
		_delay_ms(200);
		DS18B20_init();        // инициализация DS18B20
		write_18b20(0xCC);     // проверка кода датчика
		write_18b20(0xBE);     // считываем содержимое ОЗУ
		Temp_L = read_18b20(); // читаем первые 2 байта блокнота
		Temp_H = read_18b20();
		temp_flag = 1;         // флаг знака температуры равен 1(плюс)
		if(Temp_H &(1 << 3))   // проверяем бит знака температуры на равенство единице
		{
			signed int tmp;
			temp_flag = 0;      // флаг знака равен 0(минус)
			tmp = (Temp_H << 8) | Temp_L;
			tmp = -tmp;
			Temp_L = tmp;
			Temp_H = tmp >> 8;
		}
		
		tempint = ((Temp_H << 4) & 0x70)|(Temp_L >> 4); // вычисляем целое значение температуры
		tempint1 = tempint % 1000 / 100;
		tempint2 = tempint % 100 / 10;
		tempint3 = tempint % 10;
		temppoint = Temp_L & 0x0F; // вычисляем дробное значение температуры
		temppoint = temppoint * 625;       // точность температуры
		temppoint1 = temppoint / 1000;
		
		
		// выводим значения на дисплей a,b,c,d
		a = tempint1 + 48;
		b = tempint2 + 48;
		c = tempint3 + 48;
		d = temppoint1 + 48;
		

		
	}
}

/*** Инициализация DS18B20 ***/
unsigned char DS18B20_init(void)
{
	PORTB &= ~(1 << PB7); // устанавливаем низкий уровень
	DDRB |= (1 << PB7);
	_delay_us(490);
	DDRB &= ~(1 << PB7);
	_delay_us(68);
	OK_Flag = (PINB & (1 << PB7)); // ловим импульс присутствия датчика
	// если OK_Flag = 0 датчик подключен, OK_Flag = 1 датчик не подключен
	_delay_us(422);
	return OK_Flag;
}
/*** Функция чтения байта из DS18B20 ***/
unsigned char read_18b20(void)
{
	unsigned char i;
	unsigned char dat = 0;
	for(i = 0;i < 8;i++)
	{
		DDRB |= (1 << PB7);
		_delay_us(2);
		DDRB &= ~(1 << PB7);
		_delay_us(4);
		dat = dat >> 1;
		if(PINB & (1 << PB7))
		{
			dat |= 0x80;
		}
		_delay_us(62);
	}
	return dat;
}
/*** функция записи байта в DS18B20 ***/
void write_18b20(unsigned char dat)
{
	unsigned char i;
	for(i = 0;i < 8;i++)
	{
		DDRB |= (1 << PB7);
		_delay_us(2);
		if(dat & 0x01)
		{
			DDRB &= ~(1 << PB7);
		}
		else
		{
			DDRB |= (1 << PB7);
		}
		dat = dat >> 1;
		_delay_us(62);
		DDRB &= ~(1 << PB7);
		_delay_us(2);
	}
}


/*
 * get data from dht22
 */
uint8_t dht22_getdata(uint8_t select) {
	uint8_t bits[5];
	uint8_t i,j = 0;

	memset(bits, 0, sizeof(bits));

	//reset port
	DHT22_DDR |= (1<<DHT22_INPUTPIN); //output
	DHT22_PORT |= (1<<DHT22_INPUTPIN); //high
	_delay_ms(100);

	//send request
	DHT22_PORT &= ~(1<<DHT22_INPUTPIN); //low
	_delay_ms(18);
	DHT22_PORT |= (1<<DHT22_INPUTPIN); //high
	_delay_us(1);
	DHT22_DDR &= ~(1<<DHT22_INPUTPIN); //input
	_delay_us(39);

	//check start condition 1
	if((DHT22_PIN & (1<<DHT22_INPUTPIN))) {
		return DHT22_ERROR;
	}
	_delay_us(80);
	//check start condition 2
	if(!(DHT22_PIN & (1<<DHT22_INPUTPIN))) {
		return DHT22_ERROR;
	}
	_delay_us(80);

	//read the data
	for (j=0; j<5; j++) { //read 5 byte
		uint8_t result=0;
		for(i=0; i<8; i++) {//read every bit
			while(!(DHT22_PIN & (1<<DHT22_INPUTPIN))); //wait for an high input
			_delay_us(30);
			if(DHT22_PIN & (1<<DHT22_INPUTPIN)) //if input is high after 30 us, get result
				result |= (1<<(7-i));
			while(DHT22_PIN & (1<<DHT22_INPUTPIN)); //wait until input get low
		}
		bits[j] = result;
	}

	//reset port
	DHT22_DDR |= (1<<DHT22_INPUTPIN); //output
	DHT22_PORT |= (1<<DHT22_INPUTPIN); //low
	_delay_ms(100);

	//check checksum
	if (bits[0] + bits[1] + bits[2] + bits[3] == bits[4]) {
		if (select == 0) { //return temperature
			return(bits[2]);
		} else if(select == 1){ //return humidity
			return(bits[0]);
		}
	}

	return DHT22_ERROR;
}

/*
 * get temperature (0..50C)
 */
int8_t dht22_gettemperature() {
	uint8_t ret = dht22_getdata(0);
	if(ret == DHT22_ERROR)
		return -1;
	else
		return ret;
}

/*
 * get humidity (20..90%)
 */
int8_t dht22_gethumidity() {
	uint8_t ret = dht22_getdata(1);
	if(ret == DHT22_ERROR)
		return -1;
	else
		return ret;
}



