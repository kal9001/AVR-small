/*\
 *   single_output_clock - v1.0
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
 *   Very basic program to turn a single pin on and off at a set interval.
 *
 *   Pinout:
 *
 *              ATtiny85
 *              ╔═══╦═══╗
 *       RESET -║1     8║- VCC 5V5
 *           x -║2     7║- x  
 *           x -║3     6║- x  
 *      GND 0V -║4     5║- PB0 (O)
 *              ╚═══════╝
 *
\*/ 

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
  DDRB = 0x01;
   
  while(1)
  {
  PORTB = 0x00; //Port B all off
  _delay_ms(1000); //delay one second
  PORTB = 0x01; //Port B all on
  _delay_ms(1000); //delay one second
  }
return 0;
}
