
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <inc/tm4c123gh6pm.h>
#include "Timer.h"
#include "scanAuto.h"
#include "open_interface.h"


void manualForward(oi_t*sensor);

void manualBackward(oi_t*sensor);

void manualStop(oi_t*sensor);

void manualTurnR(oi_t*sensor);

void manualTurnL(oi_t*sensor);

void manualScan(oi_t*sensor);
