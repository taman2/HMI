/*
 * OneWire.c
 *
 * Created: 10/18/2020 3:16:45 PM
 *  Author: HMI
 */
#include "DIO.h"
#define F_CPU 8000000UL

#include <util/delay.h>
#include "OneWire.h"


void OneWire_Init(uinteg8_t u8_OneWire_Pin)
{

	DIO_Init_Pin(u8_OneWire_Pin,OUTPUT,DIO_PIN_OUTPUT);
}

void OneWire_Get_The_Reset_Respond(uinteg8_t u8_OneWire_Pin)
{

	DIO_Init_Pin(u8_OneWire_Pin,OUTPUT,DIO_PIN_OUTPUT);
	DIO_Write_Pin(u8_OneWire_Pin,LOW);
	_delay_us(500u);
	DIO_Init_Pin(u8_OneWire_Pin,INPUT,DIO_PIN_LEFT_FLOAT);
	_delay_us(500u);

}


void OneWire_Byte_Write(uinteg8_t u8_OneWire_Pin,uinteg8_t u8_OneWire_Byte_Write_Byte)
{

	      //BYTE WRITE START START
	uinteg8_t u8_Index=0;//Don't hate on my use of i everywhere!  I know, I know bad programming Kevin!
          //We need to write a BYTE "command" to the digital pin "pin"

	for(u8_Index=0; u8_Index<8; u8_Index++)
	{//8 bits in a byte, do this 8 times, least significant bit
		DisableGeneralInterrupt();
		if(BIT_IS_SET(u8_OneWire_Byte_Write_Byte, u8_Index))
		{//if the first bit is a '1'
			DIO_Init_Pin(u8_OneWire_Pin, OUTPUT,DIO_PIN_OUTPUT);//get ready to drive LOW
			DIO_Write_Pin(u8_OneWire_Pin, LOW);//go low for a microsecond, just to let the device know something is coming
			_delay_us(1); //might get rid of this, probably not needed
			DIO_Init_Pin(u8_OneWire_Pin,INPUT,DIO_PIN_LEFT_FLOAT);//since this is a '1', change into an input, and let the pull-up resistor yank the line HIGH
			_delay_us(60);//chill out for 60micro secs, to let the DS18B20 get a read of the high signal
		}//true
		else
		{//nope it was a '0'
			DIO_Init_Pin(u8_OneWire_Pin, OUTPUT,DIO_PIN_OUTPUT);//get ready to write
			DIO_Write_Pin(u8_OneWire_Pin, LOW);//go LOW for the entire 60ish microseconds
			_delay_us(60);//the DS18B20 will come in and read the low line as a 0 here
			DIO_Init_Pin(u8_OneWire_Pin,INPUT,DIO_PIN_LEFT_FLOAT);//back to input, line gets yanked high, and ready for the next bit
			_delay_us(1);
		}
		EnableGeneralInterrupt();

	}

}

void OneWire_Byte_Read(uinteg8_t u8_OneWire_Pin ,uinteg8_t*pu8_OneWire_Byte_Read_Byte)
{

	//BYTE READ START START
	uinteg8_t u8_Index=0;
	uinteg8_t u8_Buffer=0;


	//reads a byte from the DS18B20, this is not a 'void' function so it returns the byte read in
	for(u8_Index=0; u8_Index<8; u8_Index++)
	{
		DisableGeneralInterrupt();

		//8 bits in a byte
		DIO_Init_Pin(u8_OneWire_Pin, OUTPUT,DIO_PIN_OUTPUT);//get ready
		DIO_Write_Pin(u8_OneWire_Pin, LOW);//drive low to tell the DS18B20 we're ready
		//used to have a delay of 1us here, turned out it was giving corrupt data
		DIO_Init_Pin(u8_OneWire_Pin,INPUT,DIO_PIN_LEFT_FLOAT);// change to an input to allow line to yank HIGH
		_delay_us(10);//The DS18B20 now has control over the line
		//if pulled low, then we read in a '0', if high, then the bit is a '1'
		DIO_Read_Pin(u8_OneWire_Pin,&u8_Buffer);
		if(u8_Buffer==HIGH)//grab the line status
		{
			BIT_IS_SET(*pu8_OneWire_Byte_Read_Byte,u8_Index);//set it or...
		}
		else
		{
			BIT_IS_CLR(*pu8_OneWire_Byte_Read_Byte,u8_Index);//clear it
		}
		_delay_us(49);//wait out the rest of the timing window
		 EnableGeneralInterrupt();
	 }//for



}

void OneWire_Two_Bytes_Read(uinteg8_t u8_OneWire_Pin ,uinteg16_t*pu16_OneWire_Two_Bytes_Read_Byte)
{

	//BYTE READ START START
	uinteg8_t u8_Index=0;
	uinteg8_t u8_Buffer=0;

	//reads a byte from the DS18B20, this is not a 'void' function so it returns the byte read in
	for(u8_Index=0; u8_Index<16; u8_Index++)
	{
		DisableGeneralInterrupt();
		//8 bits in a byte
		DIO_Init_Pin(u8_OneWire_Pin, OUTPUT,DIO_PIN_OUTPUT);//get ready
		DIO_Write_Pin(u8_OneWire_Pin, LOW);//drive low to tell the DS18B20 we're ready
		//used to have a delay of 1us here, turned out it was giving corrupt data
		DIO_Init_Pin(u8_OneWire_Pin,INPUT,DIO_PIN_LEFT_FLOAT);// change to an input to allow line to yank HIGH
		_delay_us(10);//The DS18B20 now has control over the line
		//if pulled low, then we read in a '0', if high, then the bit is a '1'
		DIO_Read_Pin(u8_OneWire_Pin,&u8_Buffer);
		if(u8_Buffer==HIGH)//grab the line status
		{
			SET_BIT(*pu16_OneWire_Two_Bytes_Read_Byte,u8_Index);//set it or...
		}
		else
		{
			CLR_BIT(*pu16_OneWire_Two_Bytes_Read_Byte,u8_Index);//clear it
		}
		_delay_us(49);//wait out the rest of the timing window
		EnableGeneralInterrupt();
	}//for
	}
