/*\
 *   ADC counter - v1.0
 *   Web: http://home.kal9001.co.uk  Email: kal@kal9001.co.uk
 *   
 *   Copyright (C) 2015  Kal9001
 *   
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   called GPLv3.txt in the root directory where this source file is located.
 *   If not, see <http://www.gnu.org/licenses/>.
\*/

/*\
 *
 *  The program simply samples the two pots (ADC2 and 3) and passes the data into a function to shift
 *  shift out using the USI with a manual clock.
 *
 *                     ATtiny 85P
 *                      ╔═══╦═══╗
 *               RESET -║1    28║- 5V VCC
 *  pot 1 (ADC3)(A)PB3 -║2    27║- PB2(O)(USCK) clock pin
 *  pot 2 (ADC2)(A)PB4 -║3    26║- PB1(O)(DO) data output
 *              GND 0V -║4    25║- PB0(O)(DI) SS chip select
 *                      ╚═══════╝
 *
\*/

#define F_CPU 8000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void init_hardware_ADC(void);
void init_hardware_USI(void);
uint8_t getAnalogResult(uint8_t whichOne);
void displayData(uint8_t data[2], uint8_t numberOfBytes);

int main(void)
{
  uint8_t ADCresult[2] = { 0x00 };
  uint8_t whichOne = 0;

  DDRB  = 0x07;
  PORTB = 0x01;

  init_hardware_ADC();//sets up the ADC
  init_hardware_USI();//sets up the USI
  
  while(1)
  {
    for(whichOne = 2; whichOne <= 3; whichOne++)
    {
      ADCresult[(whichOne - 2)] = getAnalogResult(whichOne);
    }
    displayData(ADCresult, 2);
        
    _delay_ms(500);
    
  }
  return 0;//we will never get here
}

void init_hardware_ADC(void)
{
  ADMUX  = 0x22;//0010 0010//using AVCC, ADLAR 1 and ADC2 preselected.
  DIDR0  = 0x18;//Disable digital input for ACD2 and 3
  ADCSRA = 0x87;//ADC enable with 128 clock division
  return;
}

void init_hardware_USI(void)
{
  USICR = 0x5a;//sets USI to three wire mode with software clock set to USITC
  return;
}

uint8_t getAnalogResult(uint8_t whichOne)
{
  ADMUX = 0x20 + whichOne;//select input
  ADCSRA |= 0x40;//start conversion.
  while(ADCSRA & 0x40);//wait for conversion to finish

  return ADCH; 
}

void displayData(uint8_t data[2], uint8_t numberOfBytes)
{
  uint8_t counter_a, counter_b;
  
  PORTB &= 0xfe;//PB0 (SS) low
  USICR = 0x5a;//sets USI to three wire mode with software clock
  
  for(counter_a = 0; counter_a < numberOfBytes; counter_a++)
  {
    USIDR = data[counter_a];//loads data to send
    for(counter_b = 0; counter_b < 8; counter_b++)
    {
      USICR = 0x11;//toggle the USI clock
      USICR = 0x13;//toggle the USE clock and the USI data register
    }
  }

  USICR = 0x00;//Turns USI off to resume normal port operation.
  PORTB |= 0x01;//PB0 (SS) high
  return;
}
