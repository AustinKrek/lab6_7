

/**
 * main.c
 */

#include "cyBot_Scan.h"
#include "Timer.h"
#include "lcd.h"
#include "stdlib.h"
#include "movementAuto.h"
#include "math.h"
#include "scanAuto.h"
#include "uart_extra_help.h"

extern volatile char flag;

/*
typedef struct{
        double objAngleData;                              // Average angle to object
        double objDistData;                           // Average dist to object
        double widthData;
} object_build;
*/


/*
 * This function detects the edges of objects
 */
int isObj(double irPrev2, double irPrev, double irCur)
{
    int found = 0;

    if((irPrev2 - irPrev) > 0 && abs(irPrev2 - irPrev) >= 60)
    {
        if((irPrev - irCur) > 0 && abs(irPrev - irCur) >= 60)
        {
            found = 1;
        }
    }

    if((irPrev2 - irPrev) < 0 && abs(irPrev2 - irPrev) >= 60)
    {
        if((irPrev - irCur) < 0 && abs(irPrev - irCur) >= 60)
        {
           found = 1;
        }
    }

    return found;
}


/*
 * this function moves to the object with the smallest width
 */
int moveToObj(objectBuild *objs, oi_t* sensor_data)
{
    int bumpDetected = 0;
    objectBuild *objectSmall;
    objectSmall = &objs[0];
    int i = 1;
    while(objs[i].objDistData != '\0')
    {
        if(objs[i].widthData < objectSmall->widthData)
        {
            objectSmall = &objs[i];
        }
        i++;
    }

    turnAuto(objectSmall->objAngleData, sensor_data);
    bumpDetected = forwardAuto(objectSmall->objDistData, sensor_data);

    return bumpDetected;
}


/*
 * this function parses the data gathered from the scans and creates an instance of objectBuild
 */
objectBuild * parseData(int beginAngle, int endAngle, double beginDist, double endDist)
{
    double PI = 3.1415;
    double objAngleData = beginAngle;                              // Average angle to object
    double objDistData = endAngle;                           // Average dist to object
    double widthData;

   objAngleData = (beginAngle + endAngle) /2;                              // Average angle to object
   widthData = (objDistData - objAngleData) * (PI/180) * ((beginDist+ endDist)/2);       // calculate width using Arc = theta × (PI/180) × r
   objDistData =  sqrt( abs(  (((beginDist + endDist)/2) * ((beginDist + endDist)/2)) - (widthData*widthData/4)));

   objectBuild ret;
   ret.objAngleData = objAngleData;
   ret.objDistData =objDistData ;
   ret.widthData = widthData;
   objectBuild *retPtr;
   retPtr = &ret;

   return retPtr;
}

/*
 * this function does a 180 scan of what ever is in front of it
 */
int scanObjs(objectBuild *objectsList, int numObj, int angleInp)
{
    cyBOT_init_Scan();
    cyBOT_Scan_t getScan;
    double distDataPrev =0;
    int angleDataPrev =0;
    int irDataCur =0;
    int irDataPrev =0;
    int irDataPrev2 =0;
    int edgeFound = 0;
    int onObj = 0;
    int beginAngle = 0;
    int endAngle = 0;
    double beginDist = 0;
    double endDist = 0;
    double distDataCur =0;
    int angleDataCur =0;
    int angle = 0;
    cyBOT_Scan(angle, &getScan);
    angleDataCur = angle + angleInp;
    angleDataPrev = angleDataCur;
    distDataCur = getScan.sound_dist;
    distDataPrev = distDataCur;
    irDataPrev2 = getScan.IR_raw_val;
    irDataPrev = getScan.IR_raw_val;
    irDataCur = getScan.IR_raw_val;

    //SCAN FOR OBJECTS
    angle = 0;
    while(angle <= 180)
    {
            //detect at angle take average RF value of 2 scans
            int scanNum = 0;
            int irAve = 0;
            while(scanNum <2){
              cyBOT_Scan(angle, &getScan);
              irAve = irAve + getScan.IR_raw_val;
              scanNum++;
            }
            irAve = irAve/2;



            //move old and new down
            angleDataPrev = angleDataCur;
            angleDataCur = angle + angleInp;

            distDataPrev = distDataCur;
            distDataCur = getScan.sound_dist;

            irDataPrev2 = irDataPrev;
            irDataPrev = irDataCur;
            irDataCur = irAve;



            //parse SCANED DATA
             edgeFound = isObj(irDataPrev2, irDataPrev, irDataCur);

             if (edgeFound == 1 && onObj == 0)
             {
                 beginAngle = angleDataCur;
                 beginDist = distDataCur;
                 onObj = 1;

             }
             else if (edgeFound == 1 && onObj == 1)
             {
                 endAngle = angleDataPrev;
                 endDist = distDataPrev;
                 onObj = 0;

                     //create object
                     objectBuild objectHold = *parseData(beginAngle, endAngle, beginDist, endDist);


                     if(objectHold.widthData > 1)
                     {
                         objectsList[numObj] = objectHold;
                         numObj++;
                     }




             }



            angle = angle +2;
     }
    return numObj;
}

int goToThinnest(oi_t *sensor_data, int move){


    int bumpDetected = 0;
    int numObjs = 0;
    int angle = 0;
    int i = 0;

    //initialize possible 20 objects as null
    objectBuild objectsList[20];
    while(i < (sizeof(objectsList)/sizeof(objectsList[0]))){
        objectsList[i].objAngleData = '\0';
        objectsList[i].objDistData = '\0';
        objectsList[i].widthData = '\0';
            i++;
        }

    numObjs = scanObjs(objectsList, numObjs, angle);

    //turn 180
    turnAuto(180, sensor_data);

    angle = 180;
    numObjs = scanObjs(objectsList, numObjs, angle);

    char toPutty[100];

        i = 0;
        while (objectsList[i].objDistData != '\0')
        {
          sprintf(toPutty, "\n\rObject Num: %d\t\tAngle: %f\tDistance: %f\t\tWidth: %f\0", i, objectsList[i].objAngleData, objectsList[i].objDistData, objectsList[i].widthData);
          i++;
          uart_sendStrB(toPutty);
        }

    //if set to move automatically
    if(move == 1){
        bumpDetected = moveToObj(objectsList, sensor_data);
    }


  //
    return bumpDetected;
}


int scanAuto(oi_t*sensor_data, int move)
{
    int bumpDetected = 1;

    while(bumpDetected == 1){
        bumpDetected = goToThinnest(sensor_data, move);
    }


    return 0;
}

