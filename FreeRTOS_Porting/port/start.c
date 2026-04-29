
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

/*
Bootup code below
It copies values from flash to RAM using symbols defined in the linker script, and then starts the FreeRTOS scheduler.
*/

extern uint32_t _stext;
extern uint32_t _etext; /* Start of text section in flash */

extern uint32_t _sdata; /*Address of start of initialized data in RAM */
extern uint32_t _edata;
extern uint32_t _sidata; /* Start of initialized data in flash */

extern uint32_t _sbss;
extern uint32_t _ebss;

void start(){

    uint32_t *src = &_sidata;
    uint32_t *dst_start = &_sdata;
    while(dst_start < &_edata){
        *dst_start = *src;
        dst_start++;
        src++;
    }

    dst_start = &_sbss;
    while(dst_start < &_ebss){
        *dst_start = 0;
        dst_start++;
    }

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
