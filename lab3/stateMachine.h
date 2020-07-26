#ifndef stateMachine_included
#define stateMachine_included
/** plays a song */

char moveShape(int c, int r);
extern int redrawScreen;
extern char state;
void stateAdvance();
#endif /* stateMachine_included */