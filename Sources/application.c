/*
 * application.c
 *
 *  Created on: 24/6/2016
 *      Author: marvin
 */
#include "FRTOS1.h"
#include "application.h"
#define MPU 0x68
int16_t AcX, AcY, AcZ, GcX, GcY, GcZ, Temp;
	int8_t id;

	uint16_t time=10;
	  byte PWR_MGMT=0x6B;
	  byte leido[15];


void accessSuperValuableResource(void)
{
	RTT1_WriteString(0, ">>>Using super Valuable Resource!! \r\n");
	GI2C1_SelectSlave(MPU);
	  //GI2C1_WriteByteAddress8(MPU, PWR_MGMT, 0);
	  GI2C1_ReadByteAddress8(MPU,0x3B,&leido[0]);
	  WAIT1_Waitms(time);
	  GI2C1_ReadByteAddress8(MPU,0x3C,&leido[1]);
	  WAIT1_Waitms(time);
	  AcX=leido[0];
	  AcX=AcX<< 8;
	  AcX=AcX| leido[1];
	  //RTT1_WriteString(0,"LEIDO!!\r\n");
	  GI2C1_ReadByteAddress8(MPU,0x43,&leido[6]);
	  WAIT1_Waitms(time);
	  GI2C1_ReadByteAddress8(MPU,0x44,&leido[7]);
	  WAIT1_Waitms(time);
	  GcX=leido[6];
	  GcX=GcX<< 8;
	  GcX=GcX| leido[7];


	  LCD1_Clear();
	  LCD1_GotoXY(1,1);
	  LCD1_WriteString("Ax");
	  uint8_t buf[16];
	  UTIL1_Num16sToStr(buf, sizeof(buf), AcX);
	  LCD1_WriteString((char*)buf);

	  LCD1_GotoXY(2,1);

	  LCD1_WriteString("Gx");
	  //uint8_t bufAy[16];
	  UTIL1_Num16sToStr(buf, sizeof(buf), GcX);
	  LCD1_WriteString((char*)buf);
}

static portTASK_FUNCTION(task1, pvParameters) {

  /* Write your task initialization code here ... */
	//portBASE_TYPE xStatus;

	 GI2C1_Init();
		  GI2C1_SelectSlave(MPU);
		  GI2C1_WriteByteAddress8(MPU, PWR_MGMT,0);
		  GI2C1_UnselectSlave();

	RTT1_WriteString(0,"Task 1 Stars!\r\n");
	int item;
	portBASE_TYPE xStatus;
  for(;;) {
//	  xStatus = xSemaphoreTake(myBinarySemaphore, portMAX_DELAY);
//	  RTT1_WriteString(0,"Switch Pressed!\r\n");


	  xStatus = xSemaphoreTake(myMutex, 500/portTICK_RATE_MS);
	  if(xStatus)
	  {
		  RTT1_WriteString(0, "Task 1 Got Access: ");
		  accessSuperValuableResource();
		  vTaskDelay(250/portTICK_RATE_MS);
		  xSemaphoreGive(myMutex);
	  }
	  vTaskDelay(1000/portTICK_RATE_MS);
  }
  /* Destroy the task */

  vTaskDelete(task1);
}

static portTASK_FUNCTION(task2, pvParameters) {

  /* Write your task initialization code here ... */
	//portBASE_TYPE xStatus;
//	GI2C1_Init();
//			  GI2C1_SelectSlave(MPU);
//			  GI2C1_WriteByteAddress8(MPU, PWR_MGMT,0);
//			  GI2C1_UnselectSlave();
	RTT1_WriteString(0,"Task 2 Stars!\r\n");
	int item;
	portBASE_TYPE xStatus;
  for(;;) {
//	  xStatus = xSemaphoreTake(myBinarySemaphore, portMAX_DELAY);
//	  RTT1_WriteString(0,"Switch Pressed!\r\n");
	  xStatus = xSemaphoreTake(myMutex, 500/portTICK_RATE_MS);
	  if(xStatus)
	  {
		  RTT1_WriteString(0, "Task 2 Got Access: ");
		  accessSuperValuableResource();
		  vTaskDelay(250/portTICK_RATE_MS);
		  xSemaphoreGive(myMutex);

	  }
	  else
	  {
		  RTT1_WriteString(0, "Task 2 FAILED to Get Access within 500 ms\r\n");
	  }
	  vTaskDelay(1000/portTICK_RATE_MS);
  }
  /* Destroy the task */

  vTaskDelete(task2);
}



void applicationRun(void)
{
	myMutex = xSemaphoreCreateMutex();

	if (FRTOS1_xTaskCreate(
	     task1,  /* pointer to the task */
	      "task1", /* task name for kernel awareness debugging */
	      configMINIMAL_STACK_SIZE + 100, /* task stack size */
	      (void*)NULL, /* optional task startup argument */
	      tskIDLE_PRIORITY + 2,  /* initial priority */
	      (xTaskHandle*)NULL /* optional task handle to create */
	    ) != pdPASS) {
	      /*lint -e527 */
	      for(;;){}; /* error! probably out of memory */
	      /*lint +e527 */
	  }

	if (FRTOS1_xTaskCreate(
		     task2,  /* pointer to the task */
		      "task2", /* task name for kernel awareness debugging */
		      configMINIMAL_STACK_SIZE + 100, /* task stack size */
		      (void*)NULL, /* optional task startup argument */
		      tskIDLE_PRIORITY + 2,  /* initial priority */
		      (xTaskHandle*)NULL /* optional task handle to create */
		    ) != pdPASS) {
		      /*lint -e527 */
		      for(;;){}; /* error! probably out of memory */
		      /*lint +e527 */
		  }

}


