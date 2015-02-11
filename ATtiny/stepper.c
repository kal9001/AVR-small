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
 *                  PB1 -║3    12║- PA1(I) Step backward
 *                RESET -║4    11║- PA2(I) Step clock
 *                  PB2 -║5    10║- PA3
 *       Coil 2A (O)PA7 -║6     9║- PA4(O) Coil 1A
 *       Coil 2B (O)PA6 -║7     8║- PA5(O) Coil 1B
 *                       ╚═══════╝
 *
\*/
 
#define F_CPU _000000

#include <avr/io.h>

void singleStep(byte direction, byte stepPosition);
void halfStep(byte direction, byte stepPosition);


void main(void)
{
   byte stepPosition;//the step that was made last.
   byte direction;//which way are we going.


}

void singleStep(byte direction, byte stepPosition)
{

return;
}
void halfStep(byte direction, byte stepPosition)
{

return;
}
