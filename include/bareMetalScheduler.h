/*
 * bareMetalScheduler.h
 *
 *  Created on: 02.07.2020
 *      Author: Ritesh Singh
 */

#include <stdlib.h>

#ifndef BAREMETALSCHEDULER_H_
#define BAREMETALSCHEDULER_H_

#include <stdint.h>

#define MAX_NUM_OF_TASKS 10

typedef struct {
  uint32_t delay;
  uint32_t period;
  uint8_t run;
  void (*func)(void *handle);
  void *handle;
} stTask_t;


void schedulerInit();
void schedulerAddTask(void (*func)(void *), void *handle, uint32_t delay, uint32_t period);
void schedulerDelete(void (*func)(void *), void *handle);
void schedulerRun();
void schedulerUpdate();


#endif /* BAREMETALSCHEDULER_H_ */

