/* imd_controler.cpp */

#include "stdafx.h"
#include "prj_main.h"
#include "communication.h"
#include "sensor.h"
#include "actuator.h"

static int apl_cyc_count=0;


void setup()
{
    /*Initialize Communication (Serial/I2C...)*/
    com_init();
    /*Initialize Hardware (I/O pin mode)*/
    actuator_init();
    //fg_sensor_init();
    sensor_init();
}

void loop()
{
     //5msec task
	interval<5000>::run([]{
        switch (apl_cyc_count)
        {
            case 0:
                sensor_main();
                break;
            case 1:
                com_main();
                break;        
            case 2:
                actuator_main();
                break;
            default:
                break; 
        }
        if (apl_cyc_count>=2)
        {
            apl_cyc_count = 0;
        }
        else
        {
            apl_cyc_count++;
        }
	});

}
