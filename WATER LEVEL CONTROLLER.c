//WATER LEVEL CONTROLLER 
//ABHISHEK YADAV 
// 1904082001
#include <REGX51.H>
//Led Represent water level
#define ON 1
#define OFF 0
sbit LED0=P1^0;
sbit LED1=P1^1;
sbit LED2=P1^2;
sbit LED3=P1^3;
sbit LED4=P1^4;
//Switch represent the
//Five wire
#define PRESS 1
#define NOT_PRESSED 0
sbit SW1=P3^3;
sbit SW2=P3^4;
sbit SW3=P3^5;
sbit SW4=P3^6;
sbit SW5=P3^7;
// Motor and buzzer
#define HIGH 1
#define LOW 0
sbit M_a=P1^5;
sbit M_b=P1^6;
sbit MOTOR=P3^2;

// Lcd
#define LCD P2
sbit RS =P3^0;
sbit EN =P3^1;
//Prototype for Lcd
void lcdCommand(const char command);
void displayOnLcd(const char *pszMessage);
void lcdStart(void);
void delay(unsigned int);
/*Function to write command on Lcd*/
void lcdCommand(const unsigned char command)
{
    LCD = command;
    RS = 0;
    EN  = 1;
    delay(300);
    EN=0;
}
void lcdData(const unsigned char dataPrint)
{
    LCD = dataPrint;
    RS=1;
    EN=1;
    delay(400);
    EN=0;
}
/*Function to Display string on Lcd*/
void displayOnLcd(const char *pData)
{
    while(*pData)
    {
        lcdData(*pData);
        ++pData;
        delay(300);
    }
}
/*Function to Provide delay*/
void delay(unsigned int time)
{
    unsigned int i;
    for(i=0; i<=time; i++);
}
/*Initialize the LCD*/
void lcdStart(void)
{
    delay(500);
	  lcdCommand(0x38);
	 lcdCommand(0x0C);
	 lcdCommand(0x06);
    lcdCommand(0x01);
  
    lcdCommand(0x80);
   
   
}
// Water Level Status



unsigned char checkWaterLevel(void)
{
    if(SW1==0)
    {
        LED0 = ON;
        if(SW2==0)
        {
            if(SW3 ==0)
            {
                if(SW4==0)
                {
                    if(SW5==0)
                    {
                        return 100;
                    }
                    return 80;
                }
                return 60;
            }
            return 40;
        }
        return 20;
    }
    return 0;
}
void showStatusofWaterLevel(unsigned char status)
{
	
	
    switch(status)
    {
    case 0:
        LED0 = OFF;
        LED1 = OFF;
        LED2 = OFF;
        LED3 = OFF;
        LED4 = OFF;
		displayOnLcd("WATER LEVEL:0%");
		lcdCommand(0xC0);
		displayOnLcd("MOTOR:ON   AUTO");
		
        break;
    case 20:
        LED0 = ON;
        LED1 = OFF;
        LED2 = OFF;
        LED3 = OFF;
        LED4 = OFF;
        displayOnLcd("WATER LEVEL:20%");
			lcdCommand(0xC0);
		displayOnLcd("MOTOR:ON   AUTO");
        break;
    case 40:
        LED0 = ON;
        LED1 = ON;
        LED2 = OFF;
        LED3 = OFF;
        LED4 = OFF;
        displayOnLcd("WATER LEVEL:40%");
			lcdCommand(0xC0);
		displayOnLcd("MOTOR:ON   AUTO");
        break;
    case 60:
        LED0 = ON;
        LED1 = ON;
        LED2 = ON;
        LED3 = OFF;
        LED4 = OFF;
        displayOnLcd("WATER LEVEL:60%");
			lcdCommand(0xC0);
		displayOnLcd("MOTOR:ON   AUTO");
        break;
    case 80:
        LED0 = ON;
        LED1 = ON;
        LED2 = ON;
        LED3 = ON;
        LED4 = OFF;
        displayOnLcd("WATER LEVEL:80%");
			lcdCommand(0xC0);
		displayOnLcd("MOTOR:ON   AUTO");
        break;
    case 100:
        LED0 = ON;
        LED1 = ON;
        LED2 = ON;
        LED3 = ON;
        LED4 = ON;
        displayOnLcd("WATER LEVEL:100%");
			lcdCommand(0xC0);
		displayOnLcd("MOTOR:OFF   AUTO");
        break;
    }
}
void motorRun()
{
	MOTOR=1;
    M_a=1;
    M_b=0;
    M_a=1;
    M_b=0;
}
void motorStop()
{ MOTOR=0;
    M_a=0;
    M_b=0;
    M_a=0;
    M_b=0;
}
int main()
	{ unsigned int i;
		unsigned char waterStatus = 0x00;
    unsigned char tmpWaterStatus = 0x01;
	lcdStart();
	
    for(i=0; i<=5; i++)
		{
		displayOnLcd("  Abhishek Yadav   ");
		lcdCommand(0xC0);
		displayOnLcd("  1904082001    ");
    delay(10000000000000000000000000000000000000000000000000000000000);
	  }
		lcdCommand(0x01);
		for(i=0; i<=5; i++)
		{
	  displayOnLcd("  WATER LEVEL");
		lcdCommand(0xC0);
		displayOnLcd("   CONTROLLER   ");
		delay(900000000000000000000000000000000000000000000000000000000);
		}
		lcdCommand(0x01);
    while(1)
    {
        waterStatus = checkWaterLevel();
        if(waterStatus != tmpWaterStatus)
        {
            lcdStart();
            showStatusofWaterLevel(waterStatus);
            tmpWaterStatus = waterStatus;
           /* if(tmpWaterStatus != 100)
            {
                motorRun();
            }
            else
            {
                motorStop();
            }*/
        
			if(SW1==1&&SW2==1&&SW3==1&&SW4==1&&SW5==1)
			{ motorRun();
				
	

			}
		/*	else if(SW1==0&&SW2==0&&SW3==1&&SW4==1&&SW5==1)
			{ 
			
			}
			else if(SW1==0&&SW2==0&&SW3==0&&SW4==1&&SW5==1)
			{ 
			}
			else if(SW1==0&&SW2==0&&SW3==0&&SW4==0&&SW5==1)
			{ 
			}*/
			else if(SW1==0&&SW2==0&&SW3==0&&SW4==0&&SW5==0)
			{ 
				motorStop();
			}
			} 
					}
    }
