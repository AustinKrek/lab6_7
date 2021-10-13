

/**
 * main.c
 */
#ifndef SCANA
#define SCANA


#include "cyBot_Scan.h"
#include "Timer.h"
#include "lcd.h"
#include "stdlib.h"
#include "movementAuto.h"
#include "math.h"
#include "uart_extra_help.h"


typedef struct objectBuild{
        double objAngleData;                              // Average angle to object
        double objDistData;                           // Average dist to object
        double widthData;
}objectBuild;


int isObj(double irPrev2, double irPrev, double irCur);


int moveToObj(objectBuild *objs, oi_t* sensor_data);


objectBuild * parseData(int beginAngle, int endAngle, double beginDist, double endDist);


int goToThinnest(oi_t *sensor_data, int move);

int scanAuto(oi_t*sensor_data, int move);

#endif /* SCANA */
