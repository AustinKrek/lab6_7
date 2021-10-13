
#include "movementAuto.h"
#include "open_interface.h"




int forwardAuto(double centimeters, oi_t*sensor)
{
    int sum = 0;
   //oi_init(sensor);
    int bumpDetected = 0;
    if(centimeters > 0)
    {

        while(sum < centimeters * 10)
        {
            oi_setWheels(220, 220);
            oi_update(sensor);
            sum += sensor->distance;

            if(sensor->bumpLeft == true || sensor->bumpRight == true){
                oi_setWheels(0, 0);
                bumpDetector(sensor);
                bumpDetected = 1;
                break;
            }
        }

    }


    oi_setWheels(0,0);
    return bumpDetected;
}

void turnAuto(double degrees, oi_t*sensor )
{

   //oi_init(sensor);
    //actualDegrees = degrees / 0.324056;

    double sum = 0;
    if (degrees <= 90){
        degrees = 90 - degrees;
        while (sum < degrees)
        {
                oi_setWheels(-50, 50);
                oi_update(sensor);
                sum += -(sensor->angle);
        }
    }
    else
    {
        degrees = abs(degrees - 90);
    while (sum < degrees)
        {

                    oi_setWheels(50, -50);
                    oi_update(sensor);
                    sum += (sensor->angle);
        }
     }
    oi_setWheels(0, 0);
}

void bumpDetector(oi_t*sensor){

    //int centimeters = 200; //This is the initial statement that makes it run forward two meters
    //double sum = 0;
    //while (sum < centimeters *10){


           //oi_setWheels(220, 220);
           //oi_update(sensor);
           //sum += sensor->distance;
           // double forwardSum = 0;
        oi_setWheels(0, 0);

        if(sensor->bumpLeft == true){  //Tests if Robot bumped into a left detection
            double backSum = 150;  //This is for the robot to back up 15 cm

            //back up 15cm
            while(backSum > 0)
            {
                oi_setWheels(-220, -220);  //Backs up
                oi_update(sensor);
                backSum += sensor->distance;  //Since its going backward, it will add a negative sum, so Backsum will be counting down from 150
            }
            backSum = 150;  //Re-initialize
            oi_setWheels(0, 0);

            double turnSum = 0;
            while (turnSum < 85)
                {
                    oi_setWheels(-50, 50); //Turn right
                    oi_update(sensor);
                    turnSum += -(sensor->angle);  //For clockwise turns, must Put negative parenthesis around angle
                }
            turnSum = 0;  //Re-initialize
            oi_setWheels(0, 0);


            if (forwardAuto(25,sensor) == 1){
                return;
            }

            /*
            forwardSum = 0;
            while(forwardSum < 250)  //This will move it forward 25 cm in the turned direction
            {
                 oi_setWheels(220, 220);  //.Moves forward until 250 forward sum
                 oi_update(sensor);
                 forwardSum += sensor->distance;
            }
            forwardSum = 0;  //re-initialize
            oi_setWheels(0, 0);
            //sum = sum - 100;  //This is to make sum equal to what it was when it initially bumped into the object
             */

             turnSum = 0;
            while (turnSum < 85)  //Turns back in the direction it was heading
            {
                oi_setWheels(50, -50);
                oi_update(sensor);
                turnSum += (sensor->angle);
            }
            turnSum = 0;
            oi_setWheels(0, 0);

        }


        if(sensor->bumpRight == true){  //Same stuff just reversed
                    double backSum = 150;
                    while(backSum > 0)
                    {
                        oi_setWheels(-220, -220);
                        oi_update(sensor);
                        backSum += sensor->distance;
                    }
                    backSum = 150;
                    oi_setWheels(0, 0);


                    double turnSum = 0;
                    while (turnSum < 85)
                        {
                            oi_setWheels(50, -50);
                            oi_update(sensor);
                            turnSum += (sensor->angle);
                        }
                    turnSum = 0;
                    oi_setWheels(0, 0);


                    if (forwardAuto(25,sensor) == 1){
                        return;
                    }
                    /*
                    forwardSum = 0;
                    while(forwardSum < 250)
                    {
                         oi_setWheels(220, 220);
                         oi_update(sensor);
                         forwardSum += sensor->distance;
                    }
                    forwardSum = 0;
                    oi_setWheels(0, 0);
                    */

                     turnSum = 0;
                    while (turnSum < 85)
                    {
                        oi_setWheels(-50, 50);
                        oi_update(sensor);
                        turnSum += -(sensor->angle);
                    }
                    turnSum = 0;
                    oi_setWheels(0, 0);

        }

        if (forwardAuto(25,sensor) == 1){
             return;
        }
        /*
        forwardSum = 0;
        while(forwardSum < 200)  //This will move it forward 25 cm in the turned direction
        {
              oi_setWheels(220, 220);  //.Moves forward until 250 forward sum
              oi_update(sensor);
              forwardSum += sensor->distance;
        }
        forwardSum = 0;  //re-initialize
        oi_setWheels(0, 0);
        */

    //}

}
