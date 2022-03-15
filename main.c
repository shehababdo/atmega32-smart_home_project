/*
 * SMARTT HOMEE.c
 *
 * Created: 2/27/2022 10:11:57 PM
 * Author : sheha
 */ 
#define F_CPU 16000000  //DEFINED EXTERNAL OSCILLATOR
#include <avr/io.h>
#include <avr/interrupt.h>  // define interrupt for avr
#include <util/delay.h>     // built in delay function
#include "Common/BitMath.h"
#include "Common/DataType.h"
#include "ECU/LED/LED.h"
#include "ECU/SWITCH/SWITCH.h"
#include "MCAL/TIMER/TIMER.h"
#include "MCAL/ADC/ADC.h"
#include "ECU/EEPROM/EEPROM.h"
#include "ECU/LCD/LCD.h"
#include "ECU/BUZZER/BUZZER.h"
#include "MCAL/UART/USART.h"
#include "MCAL/DIO/DIO.h"
#include "MCAL/TWI/TWI.h"
#include "ECU/SERVO/SERVO.h"
#include "ECU/TEMP_SENSOR/temp_sensor.h"
#include "ECU/DIMMER_LED/dimmer.h"


#define username_add  0  //for eeprom page 0
#define password_add  1  //for eeprom page 1

void alarm(void);
void ADD_USER(void);
void REMOVE_USER(void);
void USER(void);
void ADMIN(void);
int main ()
{
LCD_Init();
eeprom_init();
UART_INIT();	
BUZZ_INIT();
adc_init();
servo_init();
 /****************ADMIN SETTING USERNAME&PASSWORD************************/
 uint8 admin[4] ={"adm"} ;
 EEPROM_WriteString(2,0x0001,admin,4);
 uint8 pass_admin[4]={"123"};
 EEPROM_WriteString(3,0x0001,pass_admin,4);
 /******************DC MOTOR INITILIZATION*******************************/
DIO_SetDir(PORT_C,PIN_5,OUTPUT);
DIO_SetDir(PORT_C,PIN_6,OUTPUT);
DIO_SetDir(PORT_B,PIN_0,OUTPUT);
	
DIO_SetHigh(PORT_B,PIN_0);
/*********************LEDS INITILIZATION*******************************/
LED_Init(LED_0);
LED_Init(LED_1);
LED_Init(LED_2);
DIO_SetDir(PORT_C,PIN_3,OUTPUT);
DIO_SetDir(PORT_C,PIN_4,OUTPUT);
init_dimmer();
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/

 while(1)
 {
sint8 sys_user=0;
UART_Tx_String("please enter your checking character!\n");	
sys_user=UART_Rx();

/*********************ENTERING THE SYSTEM*******************************/
switch (sys_user) // choosing between (admin mode || user mode)
{
	
/************************************************************************ /
/ *                           ADMIN MODE                                 * /
/ ************************************************************************/
case 'A': 
	{
uint8 trial_admin=0;
uint8 looper=1;
while(looper)
{
			// checking admin signing in info
			UART_Tx_String("please enter username if admin\n");
			sint8 admin_check[4]={0};
			UART_Rx_String(admin_check,4);
			_delay_ms(100);
			LCD_WriteString("admin user:");
			LCD_WriteString(admin_check);
			UART_Tx_String("please enter Pass if admin:\n");
			sint8 pass_check[4]={0};
			UART_Rx_String(pass_check,4);
			LCD_WriteAtPosition(2,1);
			LCD_WriteString("admin pass:");
			LCD_WriteString(pass_check);
			_delay_ms(1000);
			LCD_Clear();
	if (trial_admin<2)
	{
		
		if ((*admin_check==*admin)&&(*pass_check==*pass_admin))
		{
			// WELCOME MSGS
			LCD_WriteString("welcome admin");
			UART_Tx_String("welcome admin!\n");
			LCD_Clear();
			ADMIN();				
		}

		else
		{
			LCD_WriteString("trials -1");
			_delay_ms(1000);
			LCD_Clear();
			trial_admin++;
		}
	
		}
	else
		{
		LCD_WriteString("no trials");
		LCD_WriteAtPosition(2,1);
		LCD_WriteString("alarm on");
		_delay_ms(1000);
		LCD_Clear();
		alarm();
		trial_admin=0;
		looper=0;
		}
	}
	 break;
	}
/************************************************************************ /
/ *                           USER MODE                                 * /
/ ************************************************************************/ 	
 case 'U':
	 {
uint8 looper=1;
uint8 trial_user=0;
while(looper)
{			// CHECK FOR THE DATA ENTERED 
			uint8 pos_add=0x0000;
			UART_Tx_String("please enter storing position\n");
			uint8 pos =UART_Rx();
			pos_add=pos_add+pos ;
			UART_Tx_String("please enter username if user\n");
			sint8 user=UART_Rx();
			UART_Tx_String("please enter pass if user\n");
			sint8 pass=UART_Rx() ;
			uint8 check_user =eeprom_read_byte(0,pos_add);
			uint8 check_pass =eeprom_read_byte(1,pos_add);			
 if (trial_user<2)
	{
		
	if ((check_user==user)&&(check_pass==pass))
		{
			LCD_WriteString("welcome user");
			UART_Tx_String("welcome user!\n");
			USER();
		}
	else
		{
			LCD_WriteString("trials -1");
			_delay_ms(1000);
			LCD_Clear();
			trial_user++;
		}
		
	}
 else
	{
		LCD_WriteString("no trials");
		LCD_WriteAtPosition(2,1);
		LCD_WriteString("alarm on");
		_delay_ms(1000);
		LCD_Clear();
		alarm();
		trial_user=0;
		looper=0;
	}
  }
		  break;	 
	 }
	}
	
	
 }
 return 0 ;
}

void alarm(void)
{
	for (uint8 i=0 ; i<3 ;i++)
	{
		BUZZ_EN();
		_delay_ms(500);
		BUZZ_DIS();
		_delay_ms(500);
	}
}

void ADD_USER(void)
{
	/*********************User position check*******************************/
	uint8 pos_add=0x0000;
	UART_Tx_String("please enter storing position\n");
	uint8 pos =UART_Rx();
	pos_add=pos_add+pos ;
	UART_Tx_String("please enter username if new user\n");
	sint8 user=UART_Rx();
	eeprom_write_byte(username_add,pos_add,user);
	UART_Tx_String("please enter pass if new user\n");
	sint8 pass=UART_Rx() ;
	eeprom_write_byte(password_add,pos_add,pass);
	UART_Tx_String("please sign in again as a user\n");	
}

void REMOVE_USER(void)
{
	/*********************User position check*******************************/
	uint8 pos_add=0x0000;
	UART_Tx_String("please enter position to be removed\n");
	uint8 pos =UART_Rx();
	pos_add=pos_add+pos ;
	sint8 remove_val=0;
	//removing username
	eeprom_write_byte(username_add,pos_add,remove_val); 
	//removing password
	eeprom_write_byte(password_add,pos_add,remove_val);
	UART_Tx_String("user has been cleared successfully!\n");
}

void ADMIN(void)
{
sint8 order=0;
uint8 loop_begin =1 ;
/**** CONTROLLING SYSTEM *****/
while(loop_begin)
{
temp_sensor();
UART_Tx_String("please enter order \n");
order=UART_Rx();
switch (order)
	{
		/*CONTROLLING LED0 */
		case 'A' :
		{
			LCD_Clear();
			LCD_WriteString("LED1 ON");
			LED_ON(LED_0);
			_delay_ms(500);
			break;
		}
		case 'B' :
		{
			LCD_Clear();
			LCD_WriteString("LED2 OFF");
			LED_OFF(LED_0);
			_delay_ms(500);
			break;
		}
		/*CONTROLLING LED2 */
		case 'C' :
		{
			LCD_Clear();
			LCD_WriteString("LED2 ON");
			LED_ON(LED_1);
			_delay_ms(500);
			break;
		}
		case 'D' :
		{
			LCD_Clear();
			LCD_WriteString("LED2 OFF");
			LED_OFF(LED_1);
			_delay_ms(500);
			break;
		}
		/*CONTROLLING LED2 */
		case 'E' :
		{
			LCD_Clear();
			LCD_WriteString("LED3 ON");
			LED_ON(LED_2);
			_delay_ms(500);
			break;
		}
		case 'F' :
		{
			LCD_Clear();
			LCD_WriteString("LED3 OFF");
			LED_OFF(LED_2);
			_delay_ms(500);
			break;
		}
		/*CONTROLLING LED4 */
		case 'G' :
		{
			LCD_Clear();
			LCD_WriteString("LED4 ON");
			DIO_SetHigh(PORT_C,PIN_3);
			_delay_ms(500);
			break;
		}
		case 'H' :
		{
			LCD_Clear();
			LCD_WriteString("LED4 OFF");
			DIO_SetLow(PORT_C,PIN_3);
			_delay_ms(500);
			break;
		}
		/*CONTROLLING LED5 */
		case 'R' :
		{
			LCD_Clear();
			LCD_WriteString("LED5 ON");
			DIO_SetHigh(PORT_C,PIN_4);
			_delay_ms(500);
			break;
		}
		case 'K' :
		{
			LCD_Clear();
			LCD_WriteString("LED5 OFF");
			DIO_SetLow(PORT_C,PIN_4);
			_delay_ms(500);
			break;
		}
		/* CONTROLLING DIMMER LED */

		case 'W':
		{
			uint8 brithness =100*(2.9/1023)*adc_read(ADC_PIN_0);
			LCD_WriteString("brithness=");
			LCD_WriteINTEGER(brithness);
			dimmer_brithness(brithness);
			LCD_WriteAtPosition(2,1);
			LCD_WriteString("DIMMER LED ON");
			_delay_ms(500);
			LCD_Clear();
			break;
		}
		/*Servo motor controlling */
		case 'S' :
		{

			servo_90_right();
			LCD_Clear();
			LCD_WriteString("DOOR OPENED");
			_delay_ms(1500);
			servo_stop();
			break;
		}
		case 'Q' :
		{
			servo_90_left();
			LCD_Clear();
			LCD_WriteString("DOOR CLOSED");
			_delay_ms(1500);
			servo_stop();
			break;
		}
		/*turning on DC motor manually */
		case 'M' :
		{
			uint8 temp =100*(0.39/1023)*adc_read(ADC_PIN_1);
			if (temp<21)
			{
				LCD_Clear();
				LCD_WriteString("sorry we can't");
				LCD_WriteAtPosition(2,1);
				LCD_WriteString("temp=");
				LCD_WriteINTEGER(temp);
				_delay_ms(500);
			}
			else
			{
				LCD_Clear();
				LCD_WriteString("DC MOTOR ON");
				DIO_SetLow(PORT_C,PIN_5);
				DIO_SetHigh(PORT_C,PIN_6);
				_delay_ms(500);
			}
			
			break;
		}
		/*turning off DC motor manually */
		case 'U' :
		{
			uint8 temp =100*(0.39/1023)*adc_read(ADC_PIN_1);
			if (temp>28)
			{
				LCD_Clear();
				LCD_WriteString("sorry we can't");
				LCD_WriteAtPosition(2,1);
				LCD_WriteString("temp=");
				LCD_WriteINTEGER(temp);
				_delay_ms(500);
			}
			else
			{
				LCD_Clear();
				LCD_WriteString("DC MOTOR OFF");
				DIO_SetLow(PORT_C,PIN_5);
				DIO_SetLow(PORT_C,PIN_6);
				_delay_ms(500);
			}
			
			break;
		}
		/* GETTING OUT OF ADMIN MODE */
		case '0' :
		{
			loop_begin=0;
			LCD_Clear();
			LCD_WriteString("YOU ARE NO ");
			LCD_WriteAtPosition(2,1);
			LCD_WriteString("LONGER AN ADMIN");
			UART_Tx_String("*****YOU ARE NO LONGER AN ADMIN*****\n");
			_delay_ms(1500);
			LCD_Clear();
			continue;
			break;
		}
		
		/****************ADDING OR REMOVING USER***********************/
		case 'a' :
		{
			ADD_USER();
			break;
		}
		case 'r' :
		{
			REMOVE_USER();
			break;
		}
		
		default :
		
		LCD_Clear();
		LCD_WriteString("waiting order!");
		temp_sensor();
		order=UART_Rx();
		break;	
}
}
}


void USER(void)
{
_delay_ms(500);
LCD_Clear();
sint8 order=0;
uint8 loop_begin =1 ;
	/**** CONTROLLING SYSTEM *****/
while(loop_begin)
{
temp_sensor();
UART_Tx_String("please enter order \n");
order=UART_Rx();
switch (order)
{
	/*CONTROLLING LED0 */
	case 'A' :
	{
		LCD_Clear();
		LCD_WriteString("LED1 ON");
		LED_ON(LED_0);
		_delay_ms(500);
		break;
	}
	case 'B' :
	{
		LCD_Clear();
		LCD_WriteString("LED2 OFF");
		LED_OFF(LED_0);
		_delay_ms(500);
		break;
	}
	/*CONTROLLING LED2 */
	case 'C' :
	{
		LCD_Clear();
		LCD_WriteString("LED2 ON");
		LED_ON(LED_1);
		_delay_ms(500);
		break;
	}
	case 'D' :
	{
		LCD_Clear();
		LCD_WriteString("LED2 OFF");
		LED_OFF(LED_1);
		_delay_ms(500);
		break;
	}
	/*CONTROLLING LED2 */
	case 'E' :
	{
		LCD_Clear();
		LCD_WriteString("LED3 ON");
		LED_ON(LED_2);
		_delay_ms(500);
		break;
	}
	case 'F' :
	{
		LCD_Clear();
		LCD_WriteString("LED3 OFF");
		LED_OFF(LED_2);
		_delay_ms(500);
		break;
	}
	/*CONTROLLING LED4 */
	case 'G' :
	{
		LCD_Clear();
		LCD_WriteString("LED4 ON");
		DIO_SetHigh(PORT_C,PIN_3);
		_delay_ms(500);
		break;
	}
	case 'H' :
	{
		LCD_Clear();
		LCD_WriteString("LED4 OFF");
		DIO_SetLow(PORT_C,PIN_3);
		_delay_ms(500);
		break;
	}
	/*CONTROLLING LED5 */
	case 'R' :
	{
		LCD_Clear();
		LCD_WriteString("LED5 ON");
		DIO_SetHigh(PORT_C,PIN_4);
		_delay_ms(500);
		break;
	}
	case 'K' :
	{
		LCD_Clear();
		LCD_WriteString("LED5 OFF");
		DIO_SetLow(PORT_C,PIN_4);
		_delay_ms(500);
		break;
	}
	/* CONTROLLING DIMMER LED */

	case 'W':
	{
		uint8 brithness =100*(2.9/1023)*adc_read(ADC_PIN_0);
		LCD_WriteString("brithness=");
		LCD_WriteINTEGER(brithness);
		dimmer_brithness(brithness);
		LCD_WriteAtPosition(2,1);
		LCD_WriteString("DIMMER LED ON");
		_delay_ms(500);
		LCD_Clear();
		break;
	}
	/*Servo motor controlling */
	case 'S' :
	{
		LCD_Clear();
		LCD_WriteString("sorry you don't");
		LCD_WriteAtPosition(2,1);
		LCD_WriteString("have permission");
		UART_Tx_String("sorry you don't have permission \n");
		_delay_ms(1500);
		break;
	}
	case 'Q' :
	{
		LCD_Clear();
		LCD_WriteString("sorry you don't");
		LCD_WriteAtPosition(2,1);
		LCD_WriteString("have permission");
		UART_Tx_String("sorry you don't have permission \n");
		_delay_ms(1500);
		break;
	}
	/*turning on DC motor manually */
	case 'M' :
	{
		uint8 temp =100*(0.39/1023)*adc_read(ADC_PIN_1);
		if (temp<21)
		{
			LCD_Clear();
			LCD_WriteString("sorry we can't");
			LCD_WriteAtPosition(2,1);
			LCD_WriteString("temp=");
			LCD_WriteINTEGER(temp);
			_delay_ms(500);
		}
		else
		{
			LCD_Clear();
			LCD_WriteString("DC MOTOR ON");
			DIO_SetLow(PORT_C,PIN_5);
			DIO_SetHigh(PORT_C,PIN_6);
			_delay_ms(500);
		}
				
		break;
	}
	/*turning off DC motor manually */
	case 'U' :
	{
		uint8 temp =100*(0.39/1023)*adc_read(ADC_PIN_1);
		if (temp>28)
		{
			LCD_Clear();
			LCD_WriteString("sorry we can't");
			LCD_WriteAtPosition(2,1);
			LCD_WriteString("temp=");
			LCD_WriteINTEGER(temp);
			_delay_ms(500);
		}
		else
		{
			LCD_Clear();
			LCD_WriteString("DC MOTOR OFF");
			DIO_SetLow(PORT_C,PIN_5);
			DIO_SetLow(PORT_C,PIN_6);
			_delay_ms(500);
		}
				
		break;
	}
	/* GETTING OUT OF USER MODE */
	case '0' :
	{
		loop_begin=0;
		LCD_Clear();
		LCD_WriteString("YOU ARE NO ");
		LCD_WriteAtPosition(2,1);
		LCD_WriteString("LONGER AN USER");
		UART_Tx_String("*****YOU ARE NO LONGER AN USER*****\n");
		_delay_ms(1000);
		LCD_Clear();
		continue;
		break;
	}
			
	default :
			
	temp_sensor();
	LCD_Clear();
	LCD_WriteString("waiting order!");
	_delay_ms(500);
	order=UART_Rx();
	break;
			
}
}
}