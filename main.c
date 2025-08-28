/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs 

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs  - 1.45
        Device            :  PIC16F1619
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.40
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "max31855.h"
#include "mcc_generated_files/mcc.h"

//unsigned char dummy;
unsigned long milliTime=0;

unsigned long millis(void);
//uint32_t spi_read_32bits(void);
//uint8_t spi_transfer(uint8_t data); 
//void spi_write(unsigned char );
void initDisplay(void);
void command(unsigned char );
void dataCMD(unsigned char );
void initOLED(void);
void setMotorSpeed(uint16_t, short int );
//float convert14BitToFloat(uint16_t );
//float convert12BitToFloat(uint16_t);
//void printByteValue(char *, unsigned char, int);
void reportfault( uint8_t);
void printADCValues(char *);
void stuffIntToCharsBuf(int , unsigned char * , int );
//void uint32_to_text(uint32_t value, char text12[16]);
//void stuffFloatToCharsBuf(float , unsigned char *, int , int );
/*
                         Main application

 * 
 *     Pinouts:     Pin  9  = RC7 = /RES reset for OLED
 *                  Pin 10  = RB7 = /CS for OLED
 *                  Pin 11  = RB6 = CLK
 *                  Pin 12  = RB5 = SDO  --> wire to SDI of Device to drive
 *                  Pin 13  = RB4 = SDI  -->>wire to SDO of Device to drive
 * 
 * 
 * 
 *                  SSPCLKPPS = 0x0E;   //RB6->MSSP:SCK;
 *                  SSPDATPPS = 0x0C;   //RB4->MSSP:SDI;
 *                  RB6PPS = 0x10;   //RB6->MSSP:SCK;
 *                  RB5PPS = 0x11;   //RB5->MSSP:SDO;
 *   
 * 
 * 
 * 
 * 
 * 
 * 
 *  */
unsigned char text1[] = {"    johnszy     "};
unsigned char text2[] = {"  Engineering   "};
unsigned char text3[] =    {"   Warming  Up  "};
//unsigned char faultStr[] = {" TC Fault =     "};

unsigned char text5[] = {" Powering Up... "};
unsigned char text6[] = {"     howdy      "};
unsigned char text7[] = {"                "};
//unsigned char text8[] = {"  Green Button  "};

unsigned char text9[] = {"  Pot1   Pot2   "};
unsigned char text10[] = {"  0000   0000   "};
unsigned char text11[] = {"  Temp  C       "};
char text12[16];

float tcTemp, dieTemp;
uint8_t faults;

//uint32_t TC_data = 0;
//float temp_float =0 ;
//unsigned char byteVal = '\x00' ;
//float dieTemp_float = 0;

void main(void)
{
    __delay_ms(50);
    // initialize the device
    SYSTEM_Initialize();
    
    
    //__delay_ms(100);
//    int i;
//    initOLED();
//    command(0x01);
//    __delay_ms(2);
//    for(i=0;i<16;i++){
//       dataCMD(text5[i]);
//    }
    
     __delay_ms(500);
    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
   
    
    adc_result_t adc_value0 = 0;
    adc_result_t adc_value1 = 0;
    
    uint16_t upper16 = 0;
    uint16_t lower16 = 0;
    int i;
    command(0x01);
    __delay_ms(2);
    for(i=0;i<16;i++){
       dataCMD(text9[i]);
    }
        
    
    while (1)
    {
            
        adc_value0 = ADC_GetConversion(channel_AN2);
        adc_value0 = adc_value0 >> 6;
        adc_value1 = ADC_GetConversion(channel_AN3);
        adc_value1 = adc_value1 >> 6;
        
        if (adc_value0< 45) 
            adc_value0 = 0;
        if (adc_value1< 45) 
            adc_value1 = 0;
       
        stuffIntToCharsBuf(adc_value0 , text10 , 2 );  
        stuffIntToCharsBuf(adc_value1 , text10 , 9 );
        command(0x01);
        __delay_ms(2);
        for(i=0;i<16;i++){
          dataCMD(text9[i]);
        }
        command(0xA0);
        for(i=0;i<16;i++){
          dataCMD(text10[i]);
        }
        setMotorSpeed(adc_value0, 1 );
        setMotorSpeed(adc_value1, 2 );
        __delay_ms(2000);
        command(0x01);
        __delay_ms(2);
        for(i=0;i<16;i++){
          dataCMD(text11[i]);
        }
        
        tcTemp = getTemp_TC();
        dieTemp = getDieTemp();
        
        faults  = getFaultCodes();
        if (faults > 0){
           reportfault( faults);
           __delay_ms(2000);
        }
        
        command(0x01);
        __delay_ms(2);
 
        for(i=0;i<16;i++){
            dataCMD(text11[i]);
        }
        
        
        stuffIntToCharsBuf( (int16_t)tcTemp , text10 , 2 );  
        stuffIntToCharsBuf( (int16_t)dieTemp  , text10 , 9 );
        command(0xA0);
        for(i=0;i<16;i++){
          dataCMD(text10[i]);
        }
        __delay_ms(2000);
        
        //stuffFloatToCharsBuf( 20.7877,  text7,  0,  2) ;
        //__delay_ms(2000);
        
        //stuffFloatToCharsBuf( -23.5544,  text7,  0,  4) ;
        //__delay_ms(2000);
        
        /*
        TC_data = spi_read_32bits();
        
        
        //uint32_to_text(TC_data, text12);
        
        upper16 = (TC_data >> 16) & 0xFFFF; // bits 31?16
        lower16 = TC_data & 0xFFFF;         // bits 15?0
        
        //check for faults in upper and lower bytes
        uint8_t fault = upper16 & 0x01;  //   = 1 if fault detected
        uint8_t fault_type = lower16 & 0x07;   // bit0: open circuit, bit1:shortToGND, bit2: shortToVCC
        if (fault > 0){
           reportfault( fault_type);
           __delay_ms(2000);
        }
        
        byteVal =  (upper16 >> 8) & 0xFF;
        printByteValue(text7, byteVal,0);
      
        byteVal =  upper16 & 0xFF;
        printByteValue(text7, byteVal,1);
        
        byteVal =  (lower16 >> 8) & 0xFF;
        printByteValue(text7, byteVal,2);
      
        byteVal =  lower16 & 0xFF;
        printByteValue(text7, byteVal,3);
        __delay_ms(2000);
        
        temp_float = convert14BitToFloat((upper16 >>2));
        
        stuffFloatToCharsBuf( temp_float,  text10,  0,  2) ;
        __delay_ms(2000);
        
        stuffFloatToCharsBuf( -12.344, text10, 0, 2) ;
        __delay_ms(2000);
        
        //dieTemp_float = convert12BitToFloat((lower16 >>6));
        stuffIntToCharsBuf( (int16_t)temp_float , text10 , 2 );  
        stuffIntToCharsBuf((lower16 >>8) , text10 , 9 );
        command(0xA0);
        for(i=0;i<16;i++){
          dataCMD(text10[i]);
        }
        
        __delay_ms(2000);
        */
    }

}
/*
void printByteValue(char * s, unsigned char byteVal, int pos)
{

   //unsigned char tempReg = '\x00' ;
   int i;
   
   
   //tempReg = OSCCON;  // INSERT REGISTER ASSIGNMENT HERE
   
   unsigned char lowerBits = byteVal & '\x0F';
   unsigned char upperBits =  (byteVal >> 4) & '\x0F';
   
   
   if (lowerBits< 10)
       s[2*pos+1]= lowerBits | '\x30';
   else
       s[2*pos+1] = ((lowerBits-1)&'\x07') | '\x40';
   
     
   if (upperBits< 10)
       s[2*pos]= upperBits | '\x30';
   else
       s[2*pos] = ((upperBits- 1)&'\x07') | '\x40';
   
   command(0x01);
   __delay_ms(2);
   for(i=0;i<16;i++){
      dataCMD(s[i]);
   }
        
  // for(i=0;i<16;i++){
  //    text6[i]= ' ';
  // }
 
   
   command(0xA0);
   for(i=0;i<16;i++){
      dataCMD( text6[i] );
   }

}
*/
void reportfault( uint8_t fault){
    unsigned char faultStr[] = {" TC Fault =     "};
    command(0x01);
    int i;
    faultStr[11]= fault | '\x30';
    for( i=0;i<16;i++){
      dataCMD(faultStr[i]);
    }
}

void setMotorSpeed(uint16_t num, short int motorNum){
    if (motorNum == 1)
        PWM3_LoadDutyValue(num);
    if (motorNum == 2)
        PWM4_LoadDutyValue(num);      

}

void stuffIntToCharsBuf(int num, unsigned char * buf, int pos ){

  printf("num= %d\n", num);
  int dig1, dig2, dig3, dig4, neg=0;
  
  if (num < 0) {
    neg = 1;
    buf[0+pos]= 45; // 45 is '-' in OLED character map
    num= num*(-1);
  }
  
  dig1 = num/1000;
  num = num - dig1*1000;
  dig2 = num /100;
  num = num - dig2*100;
  dig3 = num / 10;
  dig4 = num - dig3*10;

  printf("dig1 dig2 dig3 dig4\n");
  printf("  %d   %d   %d   %d   \n", dig1, dig2, dig3, dig4);


  buf[0+pos+neg] = dig1+48;  // 48 is '0' character offset in OLED character map
  buf[1+pos+neg] = dig2+48;
  buf[2+pos+neg] = dig3+48;
  buf[3+pos+neg] = dig4+48;

  if (dig1 == 0){
    buf[0+pos+neg] = ' ';
    if (dig2 == 0){
      buf[1+pos+neg] = ' ';
      if (dig3 == 0 )
        buf[2+pos+neg] = ' ';
    }
  }
}

void printADCValues(char * s)
{

   unsigned char tempReg = '\x00' ;
   int i;
   char buf0[4];
   char buf1[4];
   
   uint16_t adc_value0;
   uint16_t adc_value1;
   
   adc_value0 = ADC_GetConversion( channel_AN2 );
   
   adc_value1 = ADC_GetConversion( channel_AN3);
   
   //itoa(adc_value0, buf0,10);
   
   tempReg = OSCCON;  // INSERT REGISTER ASSIGNMENT HERE
   
   unsigned char lowerBits = tempReg & '\x0F';
   unsigned char upperBits =  (tempReg >> 4) & '\x0F';
   
   
   if (lowerBits< 10)
       s[11]= lowerBits | '\x30';
   else
       s[11] = ((lowerBits-1)&'\x07') | '\x40';
   
     
   if (upperBits< 10)
       s[10]= upperBits | '\x30';
   else
       s[10] = ((upperBits- 1)&'\x07') | '\x40';
   
   command(0x01);
   __delay_ms(2);
   for(i=0;i<16;i++){
      dataCMD(s[i]);
   }
        
  // for(i=0;i<16;i++){
  //    text6[i]= ' ';
  // }
 
   
   command(0xA0);
   for(i=0;i<16;i++){
      dataCMD( text6[i] );
   }

}

unsigned long millis(){
    return milliTime;
}

void command(unsigned char s)
{
   
    LATB7=0;   //  /CS chip select
    spi_write('\xF8');  // denotes command mode to U2066 controller
    
	unsigned char bit0 = '\x00' ;
	unsigned char sendByte = '\x00';
	
	for(int i=0; i< 8; i++)
	{   
		bit0 = s & 1;
		//printChar(bit0);
		s = s >> 1;
		sendByte = sendByte << 1;
		if (bit0 == 1){
			//printf("here\n");
			sendByte= sendByte | 1;}
		if (i==3)
		{	
		  sendByte = sendByte << 4;
		  spi_write(sendByte);
		  sendByte = '\x00';
	    }
	}
      sendByte = sendByte << 4;
	  spi_write(sendByte);
	 // sendByte = '\x00';	
     // __delay_ms(10); // delay 10 ms
	  LATB7=1;
}

void initDisplay(void)
{
    int i;
    initOLED();
    command(0x01);
    __delay_ms(2);
    for(i=0;i<16;i++){
       dataCMD(text5[i]);
    }

}
void dataCMD(unsigned char s)
{
   
    LATB7 =0;  // /CS chip select
    spi_write('\xFA');  // denotes data mode to U2066 controller
    
	unsigned char bit0 = '\x00' ;
	unsigned char sendByte = '\x00';
	
	for(int i=0; i< 8; i++)
	{   
		bit0 = s & 1;
		//printChar(bit0);
		s = s >>1;
		sendByte = sendByte <<1;
		if (bit0 == 1){
			//printf("here\n");
			sendByte= sendByte | 1;}
		if (i==3)
		{	
		  sendByte = sendByte << 4;
		  spi_write(sendByte);
		  sendByte = '\x00';
	    }
	}
      sendByte = sendByte << 4;
	  spi_write(sendByte);
	 // sendByte = '\x00';	
     // __delay_ms(30); // delay 100 ms
	  LATB7=1;
}

void initOLED()
{
    //SPI.begin();
     //digitalWrite(RES, HIGH);  // set /RES pin high
     LATC7 = 1;   // set /RES pin high
     
    __delay_ms(100); // delay 10 ms
    
    command(0x2A);  //function set (extended command set)
	command(0x71);  //function selection A, disable internal Vdd regualtor
	dataCMD(0x00);
	command(0x28);  //function set (fundamental command set)
	command(0x08);  //display off, cursor off, blink off
	command(0x2A);  //function set (extended command set)
	command(0x79);  //OLED command set enabled
	command(0xD5);  //set display clock divide ratio/oscillator frequency
	command(0x70);  //set display clock divide ratio/oscillator frequency
	command(0x78);  //OLED command set disabled
	command(0x09);  //extended function set (4-lines)
    command(0x06);  //COM SEG direction
	command(0x72);  //function selection B, disable internal Vdd regualtor
	dataCMD(0x00);     //ROM CGRAM selection
	command(0x2A);  //function set (extended command set)
	command(0x79);  //OLED command set enabled
	command(0xDA);  //set SEG pins hardware configuration
//	command(0x10);  //set SEG pins ... NOTE: When using NHD-0216AW-XB3 or NHD_0216MW_XB3 change to (0x00)
	command(0x00);  //set SEG pins ... NOTE: When using NHD-0216AW-XB3 or NHD_0216MW_XB3 change to (0x00)
	command(0xDC);  //function selection C
	command(0x00);  //function selection C
	command(0x81);  //set contrast control
	command(0x7F);  //set contrast control
	command(0xD9);  //set phase length
	command(0xF1);  //set phase length
	command(0xDB);  //set VCOMH deselect level
	command(0x40);  //set VCOMH deselect level
	command(0x78);  //OLED command set disabled
	command(0x28);  //function set (fundamental command set)
	command(0x01);  //clear display
	command(0x80);  //set DDRAM address to 0x00
	command(0x0C);  //display ON
      
    __delay_ms(100); // delay 100 ms
}
/**
 End of File
*/