#ifndef __MAIN_H__
#define __MAIN_H__

#include "sql.h"
#include "weatherAPI.h"
#include "sensor.h"
#include <TaskScheduler.h>

#define SAME 0
#define _30MIN 1800000 

char ssid[] = "Secure";       
char password[] = "1CF0011189";       

void dbUpdateTask();

#endif
