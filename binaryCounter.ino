/*\
 *  binaryCounter - v1.0
 *  Web: http://home.kal9001.co.uk  Email: kal@kal9001.co.uk
 *
 *  Copyright (C) 2018  Kal9001
 *   
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  called GPLv3.txt in the root directory where this source file is located.
 *  If not, see <http://www.gnu.org/licenses/>.
\*/

/*\
 *  The circuit requires:
 *  An Arduino Uno, or direct equivelant - modifications for other boards are possible.
 *  A button attacheck to pin D2, such that it will pull the pin low when pressed. no pull up resistor is needed.
 *  8 LED's attached to pins D4:D11 with current limiting resistors to ground.
 *
 *  A binary representation of an 8 bit number is displayed on the LED's, starting at zero, and incrementing by 1 each time
 *  the button is pressed - simple.
\*/

//count variable - will roll over to zero after 255 automatically.
uint8_t counter;

//buffering the values here prevents flickering or the output LED's.
uint8_t portB;
uint8_t portD;

//change this if your button is more or less bouncy that mine.
#define DEBOUNCE_DELAY 250

void setup() {
  counter = 0;
  
  //set pins for output - this translates to:
  //digital pins 4 though 11, inclusive.
  DDRD = 0xf0;
  DDRB = 0x0f;

  //PD2 internal pullup.
  PORTD = 0x04;

  //enable digital pin 2 external interrput.
  //set to a falling edge interrupt.
  EICRA = 0x02;
  EIMSK = 0x01;
}

void loop() {
  //Pins D4:D7 will show the least significant nibble.
  portD = 0x04;
  portD |= 0xf0 & (counter<<4);
  PORTD = portD;

  //Pins D8:D11 will show the most significant nibble.
  portB = 0x00;
  portB |= 0x0f & (counter>>4);
  PORTB = portB;
}

/*
 * Digital pin 2 interrupt service.
 * Once again... this is BAD! due to the large delays used, you will very likely need to 
 * rewrite this ISR if you expect the MCU to do something else you're adding in!
 */
ISR(INT0_vect) {
  EIMSK = 0x00; 
  delay(DEBOUNCE_DELAY); 
  if(!(PIND & (1<<PD2))) {
    counter++;
  }
  delay(DEBOUNCE_DELAY);
  EIMSK = 0x01;
}
