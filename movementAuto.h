
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <inc/tm4c123gh6pm.h>
#include "Timer.h"
#include "open_interface.h"


int forwardAuto(double centimeters, oi_t*sensor);

void turnAuto(double degrees, oi_t*sensor);
void bumpDetector(oi_t*sensor);
