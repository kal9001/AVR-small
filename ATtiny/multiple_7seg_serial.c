/*\
 *   multiple_7seg_serial - v0.1
 *   Web: http://home.kal9001.co.uk  Email: kal@kal9001.co.uk
 *   
 *   Copyright (C) 2016  Kal9001
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
 *   Displays a given number on a 7-segment LED display with upto 8 digits.
 *   Number is input over serial interface by methods not yet currently implemented.
 *   
 *   Pinout:
 *
 *           ATtiny84A
 *           ╔═══╦═══╗
 *   5v VCC -║1    14║- GND 0v
 *   (O)PB0 -║2    13║- PA0(O)
 *   (O)PB1 -║3    12║- PA1(O)
 *    RESET -║4    11║- PA2(O)
 *   (O)PB2 -║5    10║- PA3(O)
 *   (O)PA7 -║6     9║- PA4(O)
 *   (O)PA6 -║7     8║- PA5(O)
 *           ╚═══════╝
 *
\*/

//includes

//function prototypes

