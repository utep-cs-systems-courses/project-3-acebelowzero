#include <msp430.h>
#include "p2switches.h"
#include "led.h"
#include "stateMachine.h"

/*char SW1_state_down,SW2_state_down,SW3_state_down,SW4_state_down; */
//char state, switch_state_down, switch_state_changed; /* effectively boolean */
static unsigned char switch_mask;
static unsigned char switches_last_reported;
static unsigned char switches_current;
char sw1_state_down, sw2_state_down, sw3_state_down, sw4_state_down; /* effectively boolean */
char state = 0;

static void switch_update_interrupt_sense()
{
  switches_current = P2IN & switch_mask;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (switches_current);                /* if switch up, sense down */
  P2IES &= (switches_current | ~switch_mask); /* if switch down, sense up */
}

void p2sw_init(unsigned char mask)
{
  switch_mask = mask;
  P2REN |= mask;  /* enables resistors for switches */
  P2IE = mask;    /* enable interrupts from switches */
  P2OUT |= mask;  /* pull-ups for switches */
  P2DIR &= ~mask; /* set switches' bits for input */

  switch_update_interrupt_sense();
}

unsigned int
p2sw_read()
{
  unsigned int sw_changed = switches_current ^ switches_last_reported;
  switches_last_reported = switches_current;
  return switches_current | (sw_changed << 8);
}

void switch_interrupt_handler()
{
  unsigned int switches = p2sw_read();
  sw1_state_down = (~switches & SW1) ? 0 : 1; /* 0 when SW1 is up */
  sw2_state_down = (~switches & SW2) ? 0 : 1; /* 0 when SW2 is up */
  sw3_state_down = (~switches & SW3) ? 0 : 1; /* 0 when SW3 is up */
  sw4_state_down = (~switches & SW4) ? 0 : 1; /* 0 when SW4 is up */

  if (sw1_state_down)
  {
    state = 1;
  }
  if (sw2_state_down)
  {
    state = 2;
  }
  if (sw3_state_down)
  {
    state = 3;
  }
  if (sw4_state_down)
  {
    state = 4;
  }
}

void
    __interrupt_vec(PORT2_VECTOR) Port_2()
{
  if (P2IFG & switch_mask)
  {                        /* did a button cause this interrupt? */
    P2IFG &= ~switch_mask; /* clear pending sw interrupts */
    switch_update_interrupt_sense();
    switch_interrupt_handler(); /* single handler for all switches */
  }
}