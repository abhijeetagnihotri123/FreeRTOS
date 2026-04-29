
#include "FreeRTOS.h"
#include "task.h"

#define MOD_VALUE 1000000007

static void vTask1(void *pvParameters){

    volatile int a = 0;
    while(1){
        a = (a + 1) % MOD_VALUE;
    }

}

static void vTask2(void *pvParameters){

    volatile int b = 0;
    while(1){
        b = (b + 1) % MOD_VALUE;
    }
}

void start(){

    BaseType_t xReturned = xTaskCreate(
        vTask1,                      /* Function that implements the task. */
        "Task1",                     /* Text name for the task. */
        configMINIMAL_STACK_SIZE,    /* Stack size in words, not bytes. */
        NULL,                        /* Parameter passed into the task. */
       tskIDLE_PRIORITY + 1,        /* Priority at which the task is created. */
        NULL                         /* Used to pass out the created task's handle. */
    );

    BaseType_t xReturned2 = xTaskCreate(
        vTask2,                      /* Function that implements the task. */
        "Task2",                     /* Text name for the task. */
        configMINIMAL_STACK_SIZE,    /* Stack size in words, not bytes. */
        NULL,                        /* Parameter passed into the task. */
        tskIDLE_PRIORITY + 1,        /* Priority at which the task is created. */
        NULL                         /* Used to pass out the created task's handle. */
    );


    vTaskStartScheduler();

    return;
}
