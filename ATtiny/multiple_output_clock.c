/*\
 *   multiple_output_clock - v1.0
 *   Web: http://home.kal9001.co.uk  Email: kal@kal9001.co.uk
 *   
 *   Copyright (C) 2014  Kal9001
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
 *   Turns on and then off pins PB0 through PB4 at a set interval and duty cycle.
 *   All outputs are independent.
 *
 *  Pinout:
 *
 *              ATtiny85
 *              ╔═══╦═══╗
 *       RESET -║1     8║- VCC 5V5
 *     (o) PB3 -║2     7║- PB2 (O)
 *     (o) PB4 -║3     6║- PB1 (O)
 *      GND 0V -║4     5║- PB0 (O)
 *              ╚═══════╝
 *
\*/
 
#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{                //_PB0, _PB1, _PB2, _PB3, _PB4
  int pinOn[] =  { 250,   75, 1000,  100,   50}; // Select each pins 'on' time in miliseconds.
  int pinOff[] = { 250,   75,  100, 1111,  500}; // Select each pins 'off' time in miliseconds.
  int pinState[] = {0, 0, 0, 0, 0};
  int pinTime[] = {0, 0, 0, 0, 0};
  int i = 0;
  
  DDRB = 0x1f;
  while(1)
  {
    for(i = 0; i < 5; i++)
    {
      if(pinTime[i] > 0)
      {
        pinTime[i] = (pinTime[i] - 1);
      }
      else
      {
        if(pinState[i])
        {
          PORTB &= ~(1<<i);
          pinState[i] = 0;
          pinTime[i] = pinOff[i];
        }
        else
        {
          PORTB |= (1<<i);
          pinState[i] = 1;
          pinTime[i] = pinOn[i];
        }
      }
    _delay_us(930); //wait 1 milisecond minus apx 70 microseconds to execute the loop
    }
  }
return(0);
} 
