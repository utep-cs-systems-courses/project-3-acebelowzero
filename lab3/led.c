#include <msp430.h>
#include "led.h"

unsigned char red_on = 0, green_on = 0;
unsigned char led_changed = 0;

static char redVal[] = {0, LED_RED}, greenVal[] = {0, LED_GREEN};

void led_init()
{
  P1DIR |= LEDS; // bits attached to leds are output
  led_changed = 1;
  led_update();
}

void led_update()
{
  if (led_changed)
  {

    char ledFlags = redVal[red_on] | greenVal[green_on];
    // switch_init();
    P1OUT &= (0xff ^ LEDS) | ledFlags; // clear bit for off leds
    P1OUT |= ledFlags;                 // set bit for on leds
    led_changed = 0;
  }
}

void led_dim()
{
  for (int i = 0; i < 1000; i++)
  {
    P1OUT = LED_RED;
    __delay_cycles(10000);
    P1OUT = LED_GREEN;
    __delay_cycles(10000);
    P1OUT = !LED_RED;
    __delay_cycles(10000);
    P1OUT = !LED_GREEN;
    __delay_cycles(10000);
  }
}