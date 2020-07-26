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
    drawJet();
    drawString8x12(50, 70, "I DREW TEXT", COLOR_PURPLE);
    clearScreen(COLOR_LIME_GREEN);
    redrawScreen = 1; // update the screen,
    state = 1;
    song_play();
    break;
  case 2:
    state = 0;
    break;
  case 3:
    clearScreen(COLOR_GREEN);
    redrawScreen = 1;
    state = 0;
    break;
  case 4:
    stopSong();
    clearScreen(COLOR_DARK_ORANGE);
    state = 4;
    break;
  }
}

void stopSong()
{
  buzzer_set_period(0);
}

/***/