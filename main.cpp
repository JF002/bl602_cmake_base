extern "C" {
#include <FreeRTOS.h>
#include <task.h>
#include <timers.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <vfs.h>
#include <aos/kernel.h>
#include <aos/yloop.h>
#include <event_device.h>
#include <cli.h>

#include <bl_uart.h>
#include <bl_chip.h>
#include <bl_wifi.h>
#include <bl_sec.h>
#include <bl_cks.h>
#include <bl_irq.h>
#include <bl_dma.h>
#include <hal_uart.h>
#include <hal_sys.h>
#include <hal_gpio.h>
#include <hal_boot2.h>
#include <hal_board.h>
#include <looprt.h>
#include <loopset.h>
#include <bl_sys_time.h>
#include <fdt.h>
#include <libfdt.h>

#include <utils_log.h>
#include <libfdt.h>
#include <blog.h>

extern uint8_t _heap_start;
extern uint8_t _heap_size; // @suppress("Type cannot be resolved")
extern uint8_t _heap_wifi_start;
extern uint8_t _heap_wifi_size; // @suppress("Type cannot be resolved")
static HeapRegion_t xHeapRegions[] =
    {
        { &_heap_start,  (unsigned int) &_heap_size}, //set on runtime
        { &_heap_wifi_start, (unsigned int) &_heap_wifi_size },
        { NULL, 0 }, /* Terminates the array. */
        { NULL, 0 } /* Terminates the array. */
    };

void user_vAssertCalled(void) __attribute__ ((weak, alias ("vAssertCalled")));
void vAssertCalled(void)
{
  volatile uint32_t ulSetTo1ToExitFunction = 0;
  printf("Assert\n");

  taskDISABLE_INTERRUPTS();
  while( ulSetTo1ToExitFunction != 1 ) {
    __asm volatile( "NOP" );
  }
}

void vApplicationIdleHook(void)
{
  __asm volatile(
  "   wfi     "
  );
  /*empty*/
}

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize)
{
  /* If the buffers to be provided to the Idle task are declared inside this
  function then they must be declared static - otherwise they will be allocated on
  the stack and so not exists after this function exits. */
  static StaticTask_t xIdleTaskTCB;
  static StackType_t uxIdleTaskStack[ configMINIMAL_STACK_SIZE ];

  /* Pass out a pointer to the StaticTask_t structure in which the Idle task's
  state will be stored. */
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;

  /* Pass out the array that will be used as the Idle task's stack. */
  *ppxIdleTaskStackBuffer = uxIdleTaskStack;

  /* Pass out the size of the array pointed to by *ppxIdleTaskStackBuffer.
  Note that, as the array is necessarily of type StackType_t,
  configMINIMAL_STACK_SIZE is specified in words, not bytes. */
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName )
{
  printf("Stack Overflow\n");

  while (1) {
    /*empty here*/
  }
}

void vApplicationMallocFailedHook(void) {
  printf("Malloc failed\n");
  while (1) {
    /*empty here*/
  }
}

void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize)
{
  /* If the buffers to be provided to the Timer task are declared inside this
  function then they must be declared static - otherwise they will be allocated on
  the stack and so not exists after this function exits. */
  static StaticTask_t xTimerTaskTCB;
  static StackType_t uxTimerTaskStack[ configTIMER_TASK_STACK_DEPTH ];

  /* Pass out a pointer to the StaticTask_t structure in which the Timer
  task's state will be stored. */
  *ppxTimerTaskTCBBuffer = &xTimerTaskTCB;

  /* Pass out the array that will be used as the Timer task's stack. */
  *ppxTimerTaskStackBuffer = uxTimerTaskStack;

  /* Pass out the size of the array pointed to by *ppxTimerTaskStackBuffer.
  Note that, as the array is necessarily of type StackType_t,
  configTIMER_TASK_STACK_DEPTH is specified in words, not bytes. */
  *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}
static void system_init(void)
{
  blog_init();
  bl_sec_init();
  bl_sec_test();
  bl_dma_init();
  bl_irq_init();
  hal_boot2_init();

  /* board config is set after system is init*/
  hal_board_cfg(0);
}
}

void HelloTask(void *params) {
  while (true) {
    printf("Hello World!\r\n");
    vTaskDelay(1000);
  }
}

extern "C" void bfl_main()
{
  static StackType_t stack[1024];
  static StaticTask_t eventLoopTaskHandle;

  bl_uart_init(0, 16, 7, 255, 255, 2 * 1000 * 1000);
  printf("Starting bl602 now....\r\n");

  vPortDefineHeapRegions(xHeapRegions);
  system_init();

  xTaskCreateStatic(HelloTask, (char*)"eventLoopTask", 1024, NULL, 15, stack, &eventLoopTaskHandle);
  vTaskStartScheduler();
}