/*\
 *   stepper - v1.0
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
 *   Control of a stepper motor using a L293D or SN754410 chip.
 *   
 *   Pinout:
 *
 *                       ATtiny84A
 *                       ╔═══╦═══╗
 *               5v VCC -║1    14║- VCC 5V5
 *  Motor enable (O)PB0 -║2    13║- PA0(I) Step forward
 *        Unused (X)PB1 -║3    12║- PA1(I) Step backward
 *                RESET -║4    11║- PA2(I) Step clock
 *        Unused (X)PB2 -║5    10║- PA3(X) Unused
 *       Coil 2A (O)PA7 -║6     9║- PA4(O) Coil 1A
 *       Coil 2B (O)PA6 -║7     8║- PA5(O) Coil 1B
 *                       ╚═══════╝
 *
\*/
 
#define F_CPU 8000000

#include <avr/io.h>

void singleStep(uint8_t *direction, uint8_t *stepPosition);
void halfStep(uint8_t *direction, uint8_t *stepPosition);
void getDirection(uint8_t *direction);


int main(void)
{
   uint8_t stepPosition = 0x00;//the step that was made last.
   //stepPosition holds the current step phases for the motor
   //       full steps    half steps
   //      1122
   //      ABAB
   // 0000 1000 = 0x08 - Full
   // 0000 1100 = 0x0c - Half
   // 0000 0100 = 0x04 - Full
   // 0000 0110 = 0x06 - Half
   // 0000 0010 = 0x02 - Full
   // 0000 0011 = 0x03 - Half
   // 0000 0001 = 0x01 - Full
   // 0000 1001 = 0x09 - Half
   
   uint8_t direction = 0x03;//which way are we going.
   //0x00 = free running
   //0x01 = forwards
   //0x02 = backwards
   //0x03 = brake
      
   singleStep(&direction, &stepPosition);

}

void singleStep(uint8_t *direction, uint8_t *stepPosition)
{
   getDirection(direction);
   
   switch(*direction)
   {
   case 0x00://free running
   break;
   case 0x01://go forwards
      switch(*stepPosition)
      {
      case 0x08:
         *stepPosition = 0x04;
         PORTA = 0x04;
      break;
      case 0x04:
         *stepPosition = 0x02;
         PORTA = 0x02;
      break;
      case 0x02:
         *stepPosition = 0x01;
         PORTA = 0x01;
      break;
      case 0x01:
         *stepPosition = 0x08;
         PORTA = 0x08;
      break;
      }
   break;
   case 0x02://go backwards
      switch(*stepPosition)
      {
      case 0x08:
         *stepPosition = 0x01;
         PORTA = 0x01;
      break;
      case 0x04:
         *stepPosition = 0x02;
         PORTA = 0x02;
      break;
      case 0x02:
         *stepPosition = 0x04;
         PORTA = 0x04;
      break;
      case 0x01:
         *stepPosition = 0x08;
         PORTA = 0x08;
      break;
      }
   break;
   case 0x03://motor brake
   break;
   }
return;
}

void halfStep(uint8_t *direction, uint8_t *stepPosition)
{
   
return;
}

void getDirection(uint8_t *direction)
{  
   switch(PINA & 0x03)
   {
      case 0x00://free running
         *direction = 0x00;
         break;
      case 0x01://forwards
         *direction = 0x01;
         break;
      case 0x02://backwards
         *direction = 0x02;
         break;
      case 0x03://brake
         *direction = 0x03;
         break;
   }
return;
}
