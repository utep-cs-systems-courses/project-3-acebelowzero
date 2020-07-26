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

void stateAdvance()
{
  switch (state)
  {
  case 1:
    s
        redrawScreen = 1; // update the screen,
    state = 1;
    break;
  case 2:
    clearScreen(COLOR_BLUE);

    drawPlane();
    state = 0;
    break;
  case 3:

    clearScreen(COLOR_BROWN);
    state = 0;
    break;
  case 4:
    clearScreen(COLOR_DARK_ORANGE);
    state = 4;
    break;
  }
}

/***/