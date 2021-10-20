
#include "movement.h"
#include "open_interface.h"
#include "lcd.h"
#include "scanAuto.h"



void manualForward(oi_t*sensor)
{

    oi_setWheels(220, 220);
    oi_update(sensor);
    return;

}

void manualBackward(oi_t*sensor)
{

        oi_setWheels(-220, -220);
        oi_update(sensor);
        return;
}

void manualStop(oi_t*sensor)
{
        oi_setWheels(0,0);
    oi_update(sensor);
    return;
}

void manualTurnL(oi_t*sensor)
{


        oi_setWheels(50, -50);
        oi_update(sensor);
        return;

}
void manualTurnR(oi_t*sensor)
{
        oi_setWheels(-50, 50);
        oi_update(sensor);
        return;
}


void manualScan(oi_t*sensor)
{

       scanAuto(sensor, 0);
        return;
}










