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

int col = 10;
int row = 90;
int stateNum = 0;

/** Initializes everything, enables interrupts and green LED, 
 *  and handles the rendering for the screen
 */
// void main()
// {
//   P1DIR |= GREEN_LED; /**< Green led on when CPU on */
//   P1OUT |= GREEN_LED;

//   configureClocks();
//   lcd_init();
//   shapeInit();
//   p2sw_init(15);
//   buzzer_init();
//   led_init();
//   shapeInit();
//   clearScreen(COLOR_WHITE);

//   enableWDTInterrupts(); /**< enable periodic interrupt */
//   or_sr(0x8);            /**< GIE (enable interrupts) */

//   for (;;)
//   {
//     while (!redrawScreen)
//     {                      /**< Pause CPU if screen doesn't need updating */
//       P1OUT &= ~GREEN_LED; /**< Green led off witHo CPU */
//       or_sr(0x10);         /**< CPU OFF */
//     }
//     P1OUT |= GREEN_LED; /**< Green led on when CPU on */
//     redrawScreen = 0;
//     fillRectangle(col, 10, 50, 50, COLOR_ORANGE);
//     //movLayerDraw(&ml0, &layer0);
//   }
// }

// /** Watchdog timer interrupt handler. 15 interrupts/sec */
// void wdt_c_handler()
// {
//   u_int switches = p2sw_read();
//   static short count = 0;
//   P1OUT |= GREEN_LED; /**< Green LED on when cpu on */
//   count++;
//   if (count == 15)
//   {

//     switch (stateNum)
//     {
//     case 0:
//       row--;
//       if (~switches & SW1)
//       {
//         stateNum = 1;
//       }
//       break;
//       row++;
//     case 1:
//       col++;
//       row++;
//       if (col == 50)
//       {
//         stateNum = 1;
//       }
//       break;
//     case 2:
//       col++;
//       row--;
//       if (col == 90)
//       {
//         stateNum = 3;
//       }
//       break;
//     case 3:
//       row++;
//       if (row == 90)
//       {
//         col = 10;
//         row = 90;
//         stateNum = 0;
//       }
//       break;
//     }

//     //handles what buttons are pressed
//     if (~switches & SW1)
//     {
//       //clear screen and redraw the figure with a diferent position, same problem than above
//       //clearScreen(COLOR_BLUE);
//       buzzer_set_period(0);
//       redrawScreen = 1; //not update the screen,
//     }
//     if (~switches & SW2)
//     {
//       buzzer_set_period(0);
//       drawJet();
//     }
//     if (~switches & SW3)
//     {
//       buzzer_set_period(0);
//       drawJet();
//     }
//     if (~switches & SW4)
//     {
//       // song_();
//     }
//     //clear screen and write something to the screen
//     count = 0;
//   }
//   P1OUT &= ~GREEN_LED; /**< Green LED off when cpu off */
// }

void main()
{
  P1DIR |= GREEN_LED; /**< Green led on when CPU on */
  P1OUT |= GREEN_LED;

  configureClocks();
  lcd_init();
  shapeInit();
  p2sw_init(1);

  shapeInit();

  //layerInit(&layer0);
  //layerDraw(&layer0);

  //layerGetBounds(&fieldLayer, &fieldFence);

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
    //movLayerDraw(&ml0, &layer0);
  }
}

void wdt_c_handler()
{
  static short count = 0;
  P1OUT |= GREEN_LED; /**< Green LED on when cpu on */
  count++;
  if (count == 15)
  {
    //mlAdvance(&ml0, &fieldFence);
    if (p2sw_read())
      redrawScreen = 1;
    count = 0;
  }
  P1OUT &= ~GREEN_LED; /**< Green LED off when cpu off */
}