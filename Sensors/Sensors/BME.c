


#include <avr/io.h>
#define F_CPU 16000000UL    // ������� - 16MHz
#define baudrate 9600L
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <math.h>


#include "i2c.c"


// ���������� ������
int32_t temperature = 0;
int32_t    pressure = 0;
int32_t    altitude = 0;

int32_t temperature_1 = 0;
int32_t    pressure_1 = 0;

// ���������� ����������
int16_t ac1;
int16_t ac2;
int16_t ac3;
uint16_t ac4;
uint16_t ac5;
uint16_t ac6;
int16_t b1;
int16_t b2;
int16_t mb;
int16_t mc;
int16_t md;


// ========================================================================================================================
// ========================================================================================================================
// BMP085

// ������������� ����������
uint32_t D1;
uint32_t D2;
uint32_t D3;

// ������� ��� ������ � bmp085
#define OSS 3

#define BMP085_R 0xEF
#define BMP085_W 0xEE



// ������ �������� 16 ���
uint16_t Read(uint8_t address) {

	uint16_t msb=0;
	uint16_t lsb=0;
	uint16_t data;

	i2c_start_cond();               // ������ i2c
	i2c_send_byte(BMP085_W);        // �������� ������ ����������, ����� ������
	i2c_send_byte(address);	        // �������� ������ ������
	i2c_stop_cond();                // ��������� i2c

	i2c_start_cond();               // ������ i2c
	i2c_send_byte(BMP085_R);        // �������� ������ ����������, ����� ������
	msb = i2c_get_byte(0);
	lsb = i2c_get_byte(1);
	i2c_stop_cond();                // ��������� i2c

	data = (msb << 8) + lsb;
	return data;

}



// �������� ������ ��� ����������
void BMP085_Calibration (void) {

	ac1 = Read(0xAA);
	ac2 = Read(0xAC);
	ac3 = Read(0xAE);
	ac4 = Read(0xB0);
	ac5 = Read(0xB2);
	ac6 = Read(0xB4);
	b1  = Read(0xB6);
	b2  = Read(0xB8);
	mb  = Read(0xBA);
	mc  = Read(0xBC);
	md  = Read(0xBE);

}




// ��������� �������� �����������
void BMP085_get_temper(void){

	i2c_start_cond();               // ������ i2c
	i2c_send_byte(BMP085_W);        // �������� ������ ����������, ����� ������
	i2c_send_byte(0xF4);	        // �������� ������ ������
	i2c_send_byte(0x2E);	        // �������� ���������� (oss) ������ ������ ����������� (����� ��� �� ��� ��� ��������)
	i2c_stop_cond();                // ��������� i2c

	_delay_ms(5);                   // ����� �� ����� (�� 5 �� 26 �� � ����������� �� ���������� (oss))

	temperature_1 = Read(0xF6);     // ��������� �����������

}



// ��������� �������� ������������ ��������
void BMP085_get_pressure(void){

	i2c_start_cond();               // ������ i2c
	i2c_send_byte(BMP085_W);        // �������� ������ ����������, ����� ������
	i2c_send_byte(0xF4);	        // �������� ������ ������
	i2c_send_byte(0x34+(OSS<<6));	// �������� ���������� (oss) ������ ������ �����������
	i2c_stop_cond();                // ��������� i2c

	_delay_ms(26);                  // ����� �� ����� (�� 5 �� 26 �� � ����������� �� ���������� (oss))

	i2c_start_cond();               // ������ i2c
	i2c_send_byte(BMP085_W);        // �������� ������ ����������, ����� ������
	i2c_send_byte(0xF6);	        // �������� ������ ������
	i2c_stop_cond();                // ��������� i2c

	i2c_start_cond();               // ������ i2c
	i2c_send_byte(BMP085_R);        // �������� ������ ����������, ����� ������
	D1=i2c_get_byte(0);             // MSB
	D2=i2c_get_byte(0);             // LSB
	D3=i2c_get_byte(1);             // XLSB
	i2c_stop_cond();                // ��������� i2c

	pressure_1 = ((D1 << 16) + (D2 << 8) + D3) >> (8-OSS);  // ��������� �������� (� �� ?)

}


// �������� �������� ����������� � ������������ �������� � ������ ������������� �������������
void BMP085_calculation (int32_t* temperature, int32_t* pressure) {

	//int8_t i;
	int32_t ut=0;
	int32_t up=0;
	int32_t x1, x2, b5, b6, x3, b3, p;
	uint32_t b4, b7;

	BMP085_get_temper();
	ut+=temperature_1;

	BMP085_get_pressure();
	up=pressure_1;



	x1 = ((int32_t)ut - (int32_t)ac6) * (int32_t)ac5 >> 15;
	x2 = ((int32_t)mc << 11) / (x1 + md);
	b5 = x1 + x2;
	*temperature = (b5 + 8) >> 4;
	
	b6 = b5 - 4000;
	x1 = (b2 * ((b6 * b6) >> 12)) >> 11;
	x2 = (ac2 * b6) >> 11;
	x3 = x1 + x2;
	b3 = (((((int32_t) ac1) * 4 + x3)<<OSS) + 2)>> 2;
	x1 = (ac3 * b6) >> 13;
	x2 = (b1 * ((b6 * b6) >> 12)) >> 16;
	x3 = ((x1 + x2) + 2) >> 2;
	b4 = (ac4 * (uint32_t) (x3 + 32768)) >> 15;
	b7 = ((uint32_t) (up - b3) * (50000 >> OSS));
	//p = b7 < 0x80000000 ? (b7 * 2) / b4 : (b7 / b4) * 2;
	
	if (b7 < 0x80000000)
	{
		p = (b7 << 1) / b4;
	}
	else
	{
		p = (b7 / b4) << 1;
	}

	x1 = (p >> 8) * (p >> 8);
	x1 = (x1 * 3038) >> 16;
	x2 = (-7357 * p) >> 16;
	*pressure = p + ((x1 + x2 + 3791) >> 4);

}


// ������� ������� ������ ��� ������� ���� (���������) (������� ����� ����� ����� ������ ��-�� �������������� ������� !!!)
void bmp085CalcAltitude(int32_t pressure){
	float temp;

	temp = (float) pressure/101325;
	temp = 1-pow(temp, 0.19029);
	//altitude = round(44330*temp*10);
	altitude = 44330*temp*100;
	//get altitude in dm
}



// ========================================================================================================================
// ========================================================================================================================



int main (void)
{
		char a = ' ';
		char b = ' ';
		char c = ' ';
		
		char d = ' ';
		char e = ' ';
		char f = ' ';
		char g = ' ';
		char k = ' ';
		char l = ' ';

		unsigned int tempint1 = 0,tempint2,tempint3; // ���������� ��� ������ �������� �����������
		unsigned int presint1 = 0,presint2,presint3,presint4,presint5,presint6;

	// �������������
	i2c_init();
	BMP085_Calibration();


	while (1)
	{  
		BMP085_calculation (&temperature, &pressure);
		bmp085CalcAltitude(pressure);


	/*	int pressure1 = pressure/1000;
		int pressure2 = pressure-pressure1*1000;

		int pressure3 = pressure/133.322;    // ������� �� �� � ��.��.��

		int temp1 = temperature/10;
		int temp2 = temperature-temp1*10;*/

		// ����������� (���������� �� ������� - 00,0 �)
		/*LCD_Goto(0, 0);
		    
		BCD_2Lcd(temp1);  // ������� �� 10 ������ ���������� �������� �� �����������
		LCD_WriteData(',');
		BCD_1Lcd(temp2);
		LCD_SendStr(" C");
*/
	/*	LCD_Goto(7, 0);
		BCD_3IntLcd(pressure3);  // � �� �� ��
		LCD_SendStr(" mm Hg");

		// ������ ��� ������� ���� (���������� �� ������� �����)
		LCD_Goto(0, 1);
		BCD_4IntLcd(altitude/100);  // ������� �� 100 �������� �� ����� �����
		LCD_SendStr(" m");

		// ����������� �������� � ��������
		LCD_Goto(7, 1);
		BCD_3IntLcd(pressure1);
		BCD_3IntLcd(pressure2);
		LCD_SendStr(" Pa");
*/     
		tempint1 = temperature % 1000 / 100;
		tempint2 = temperature % 100 / 10;
		tempint3 = temperature % 10;
		// ������� �������� �� �������
		a = tempint1 + 48;
		b = tempint2 + 48;
		c = tempint3 + 48;
		
		presint1 = pressure / 100000;
		presint2 = pressure % 100000 / 10000;
		presint3 = pressure % 10000 / 1000;
		presint4 = pressure % 1000 / 100;
		presint5 = pressure % 100 / 10;
		presint6 = pressure % 10;
		
		d = presint1 + 48;
		e = presint2 + 48;
		f = presint3 + 48;
		g = presint4 + 48;
		k = presint5 + 48;
		l = presint6 + 48;
	}
}

