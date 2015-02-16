/*\
 *   stepper - v0.2
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
 *  Motor enable (O)PB0 -║2    13║- PA0(O) Coil 1A
 *        Unused (X)PB1 -║3    12║- PA1(O) Coil 1B
 *                RESET -║4    11║- PA2(O) Coil 2A
 *        Unused (X)PB2 -║5    10║- PA3(O) Coil 2B
 *     half step (I)PA7 -║6     9║- PA4(I) step forward
 *    step clock (I)PA6 -║7     8║- PA5(I) step backward
 *                       ╚═══════╝
 *
\*/

//includes
#include <avr/io.h>

//Function prototypes
uint8_t executeStep(uint8_t newStepValue, uint8_t *stepPositions);
  //executes the current step values when step clock is high
uint8_t stepValues(uint8_t direction, uint8_t currentPosition, int8_t *stepRounding);
  //Generates new step values based on current position and intended direction
  void getDirection(uint8_t *direction);
    //decodes the step direction pins
void correction(uint8_t *currentValue);
  //does the currentValue / stepPositions wrap around

int main(void)
{
  uint8_t direction = 0x00;
    //which direction are we going
    //0x00 = free running
    //0x01 = forwards
    //0x02 = backwards
    //0x03 = brake
  uint8_t newPosition = 0x00;
    //The new value that will be used.
  uint8_t currentPosition = 0x02;
    //the last value executed
   int8_t stepRounding = 0x00;
  uint8_t stepPositions[14] = {0x03, 0x01, 0x09, 0x08, 0x0c, 0x04, 0x06, 0x02, 0x03, 0x01, 0x09, 0x08, 0x0c, 0x04};
    //stepPositions holds the current step phases for the motor
      // 0000 0011 = 0x03 - Half
      // 0000 0001 = 0x01 - Full
      // 0000 1001 = 0x09 - Half
    // 0000 1000 = 0x08 - Full
    // 0000 1100 = 0x0c - Half
    // 0000 0100 = 0x04 - Full
    // 0000 0110 = 0x06 - Half
    // 0000 0010 = 0x02 - Full
    // 0000 0011 = 0x03 - Half
    // 0000 0001 = 0x01 - Full
    // 0000 1001 = 0x09 - Half
      // 0000 1000 = 0x08 - Full
      // 0000 1100 = 0x0c - Half
      // 0000 0100 = 0x04 - Full
  
    DDRB = 0x01;//b00000001
    DDRA = 0x0f;//b00001111
  
  while(1)
  {
    getDirection(&direction);
    newPosition = stepValues(direction, currentPosition, &stepRounding);
    if(PINA & 0x40)
    {
      currentPosition = executeStep(newPosition, stepPositions);
    }
  correction(&currentPosition);
  }
}

uint8_t executeStep(uint8_t newPosition, uint8_t *stepPositions)
{
  PORTA = stepPositions[newPosition];//sets motor pins
  PORTB = 0x01;
  while(PINA & 0x40){}//wait until the step clock pin goes back low.
return newPosition;
}

void getDirection(uint8_t *direction)
{
  *direction = ((PINA & 0x30) >> 4); //b00110000
}

uint8_t stepValues(uint8_t direction, uint8_t currentPosition, int8_t *stepRounding)
{
  uint8_t step;
  uint8_t newPosition = 0x00;

  if(PINA & 0x80)
    { 
      step = 1;
    }
  else
    {
      step = 2;
      if(currentPosition % 2)
      {
        if(*stepRounding == 1)
        {
          step -= 1;
          *stepRounding = 0;
        }
        else
        {
          step += 1;
          *stepRounding = 1;
        }
      }        
    }
  
  switch(direction)
  {
  case 0x00://free running
  break;
  case 0x01://forwards
    newPosition = currentPosition + step;
  break;
  case 0x02://backwards
    newPosition = currentPosition - step;
  break;
  case 0x03://brake
  break;
  }
return newPosition;
}

void correction(uint8_t *currentValue)
{
  uint8_t correctedValue = *currentValue;

  if(*currentValue < 3)
  {
    correctedValue = *currentValue + 8;
  }
  if(*currentValue > 11)
  {
    correctedValue = *currentValue - 8;
  }
  *currentValue = correctedValue;
}
