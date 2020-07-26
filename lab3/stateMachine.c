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

void playSong()
{
  switch (state)
  {
  case 1:
    buzzer_set_period(100);
    state = 1;
    break;
  case 2:
    buzzer_set_period(400);
    state = 2;
    break;
  default:
    break;
  }
}

void stateAdvance()
{
  switch (state)
  {
  case 1:
    buzzer_set_period(100);
    drawJet();
    redrawScreen = 1; // update the screen,
    state = 1;
    soundEffect();
    break;
  case 2:
    state = 0;
    break;
  case 3:
    clearScreen(COLOR_GREEN);
    state = 0;
    break;
  case 4:
    clearScreen(COLOR_DARK_ORANGE);
    state = 4;
    break;
  }
}

/***/