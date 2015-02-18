/*\
 *   7seg - v0.1
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
 *   Counts in hex from 0x000 to 0xfff and displays each step on a 3x7segment display.
 *   
 *   Pinout:
 *
 *            ATtiny84A
 *            ╔═══╦═══╗
 *    5v VCC -║1    14║- GND 0v
 *  1 (O)PB0 -║2    13║- PA0(O) A
 *  2 (O)PB1 -║3    12║- PA1(O) B
 *     RESET -║4    11║- PA2(O) C
 *  3 (O)PB2 -║5    10║- PA3(O) D
 *  P (O)PA7 -║6     9║- PA4(O) E
 *  G (O)PA6 -║7     8║- PA5(O) F
 *            ╚═══════╝
 *
\*/

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

void displayLoop(uint8_t counter1, uint8_t counter2, uint8_t counter3, uint8_t *charMap);

int main(void)
{
                          // 0  // 1  // 2  // 3  // 4  // 5  // 6  // 7  // 8  // 9  // a  // b  // c  // d  // e  // f
  uint8_t charMap[16] = { 0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71 };
  uint8_t counter1, counter2, counter3;
  
  DDRA = 0xff;
  DDRB = 0x07;
  PORTA = 0xff;
  PORTB = 0x00;
  
  while(1)
  {
    for(counter1 = 0; counter1 < 16; counter1++)
    {
      for(counter2 = 0; counter2 < 16; counter2++)
      {
        for(counter3 = 0; counterThree < 16; counter3++)
        {
          displayLoop(counter1, counter2, counter3, charMap);
        }      
      }    
    }
  }
}

void displayLoop(uint8_t counter1, uint8_t counter2, uint8_t counter3, uint8_t *charMap)
{
  uint8_t counter;
  
  for(counter = 0; counter < 66; counter++)
  {
    PORTA = ~(charMap[counter1]);
    PORTB = 0x01;
    _delay_ms(1);
      
    PORTA = ~(charMap[counter2]);
    PORTB = 0x02;
    _delay_ms(1);
    
    PORTA = ~(charMap[counter3]);
    PORTB = 0x04;
    _delay_ms(1);
  }
}
