#include "main.h"

int main(void)
{
	m17_init1();
	m17_init2();
	m17_init3();
	sm_init();
	
	while (1)
	{
		for (int k=0;k<=512;k++)
		{
			sm_forward();
			m17_left1();
			m17_right1();
		}
		_delay_ms(300);
		for (int k=0;k<=512;k++)
		{
			sm_back();
			m17_left1();
			m17_right1();
		}
		_delay_ms(300);
		
	}
}

