/*
 * bareMetalScheduler.c
 *
 *  Created on: 02.07.2020
 *      Author: Ritesh Singh
 */

#include <stdlib.h>
#include "bareMetalScheduler.h"

stTask_t tasks[MAX_NUM_OF_TASKS];


void schedulerInit() {
  for (uint8_t i = 0; i < MAX_NUM_OF_TASKS; i++) {
    tasks[i].delay = 0;
    tasks[i].period = 0;
    tasks[i].run = 0;
    tasks[i].func = NULL;
    tasks[i].handle = NULL;
  }
}

void schedulerAddTask(void (*func)(void *), void *handle, uint32_t delay, uint32_t period) {
  for (uint8_t i = 0; i < MAX_NUM_OF_TASKS; i++) {
    if (tasks[i].func == NULL) {
      tasks[i].delay = delay;
      tasks[i].period = period;
      tasks[i].run = 0;
      tasks[i].func = func;
      tasks[i].handle = handle;
      break;
    }
  }
}

void schedulerDelete(void (*func)(void *), void *handle) {
  for (uint8_t i = 0; i < MAX_NUM_OF_TASKS; i++) {
    if ((tasks[i].func == func) && (tasks[i].handle == handle)) {
      tasks[i].func = NULL;
      break;
    }
  }
}

void schedulerRun() {
  for (uint8_t i = 0; i < MAX_NUM_OF_TASKS; i++) {
    if (tasks[i].func != NULL && tasks[i].run > 0) {
      tasks[i].run--;
      tasks[i].func(tasks[i].handle);
      if (tasks[i].period == 0) {
        tasks[i].func = NULL;
      }
    }
  }
}

void schedulerUpdate() {
  for (uint8_t i = 0; i < MAX_NUM_OF_TASKS; i++) {
    if (tasks[i].func != NULL) {
      if (tasks[i].delay == 0) {
        tasks[i].delay = tasks[i].period;
        tasks[i].run++;
      } else {
        tasks[i].delay--;
      }
    }
  }
}

