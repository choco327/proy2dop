/*
 * application.h
 *
 *  Created on: 24/6/2016
 *      Author: marvin
 */

#ifndef SOURCES_APPLICATION_H_
#define SOURCES_APPLICATION_H_

#include "Cpu.h"
#include "Events.h"
#include "Pins1.h"
#include "FRTOS1.h"
#include "KSDK1.h"
#include "UTIL1.h"
#include "LCD1.h"
#include "RW1.h"
#include "BitIoLdd11.h"
#include "EN1.h"
#include "BitIoLdd1.h"
#include "RS1.h"
#include "BitIoLdd2.h"
#include "DB41.h"
#include "BitIoLdd7.h"
#include "DB51.h"
#include "BitIoLdd8.h"
#include "DB61.h"
#include "BitIoLdd9.h"
#include "DB71.h"
#include "BitIoLdd10.h"
#include "WAIT1.h"
#include "RTT1.h"
#include "SYS1.h"
#include "GI2C1.h"
#include "CI2C1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"


void applicationRun (void);

void accessSuperValuableResource(void);

xSemaphoreHandle myMutex;


#endif /* SOURCES_APPLICATION_H_ */
