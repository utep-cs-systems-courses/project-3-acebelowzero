/** \file shapemotion.c
 *  \brief This is a simple shape motion demo.
 *  This demo creates two layers containing shapes.
 *  One layer contains a rectangle and the other a circle.
 *  While the CPU is running the green LED is on, and
 *  when the screen does not need to be redrawn the CPU
 *  is turned off along with the green LED.
 */
#include <msp430.h>
#include <libTimer.h>
#include <lcdutils.h>
#include <lcddraw.h>
#include "p2switches.h"
#include <shape.h>
#include <abCircle.h>
#include "buzzer.h"
#include "stateMachine.h"
#include "led.h"

#define GREEN_LED BIT6
#define RED_LED BIT0

int redrawScreen = 1; /**< Boolean for whether screen needs to be redrawn */
int col = 90;
int row = 10;
void main()
{
  P1DIR |= GREEN_LED; /**< Green led on when CPU on */
  P1OUT |= GREEN_LED;

  configureClocks();
  lcd_init();
  shapeInit();
  p2sw_init(15);
  buzzer_init();
  shapeInit();

  clearScreen(COLOR_WHITE);

  enableWDTInterrupts(); /**< enable periodic interrupt */
  or_sr(0x8);            /**< GIE (enable interrupts) */

  for (;;)
  {
    while (!redrawScreen)
    {                      /**< Pause CPU if screen doesn't need updating */
      P1OUT &= ~GREEN_LED; /**< Green led off witHo CPU */
      or_sr(0x10);         /**< CPU OFF */
    }
    P1OUT |= GREEN_LED; /**< Green led on when CPU on */
    redrawScreen = 0;
    drawString8x12(0, 70, "Welcome to Lab", COLOR_RED);
    drawString8x12(65, 75, "3", COLOR_RED);
    randomDraw(50, 20, COLOR_BLACK);
    drawRand(100, 150, COLOR_BLACK);
  }
}

void wdt_c_handler()
{
  u_int switches = p2sw_read();
  static short count = 0;
  P1OUT |= GREEN_LED; /**< Green LED on when cpu on */
  count++;
  if (count == 15)
  {
    stateAdvance_(); // assembly function
    count = 0;
  }
  P1OUT &= ~GREEN_LED; /**< Green LED off when cpu off */
}