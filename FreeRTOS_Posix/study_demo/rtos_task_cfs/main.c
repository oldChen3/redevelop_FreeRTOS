/**
  ******************************************************************************
  * @file    main.c
  * @author  Tuu
  * @version V1.0.0
  * @date    2020-01-28
  * @brief   Main program body
  ******************************************************************************
  * @attention
  * Freertos run in the linux
  * 2.second: rtos_task_2 ---> rtos_task_2.bin
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"

#include "config.h"

/* Private define ------------------------------------------------------------*/
#define ENABLE_DEBUG_INFO   1
/* Private typedef -----------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static TaskHandle_t xTask_0;
static TaskHandle_t xTask_1;
static TaskHandle_t xTask_2;

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  freertos first creat task
  * @note   This function is used to creat app task and delect self.
  * @param  *p
  * @param  None
  * @retval None
  */
static void task_high_0(void *p)
{
    os_printf("%s ready \n", __FUNCTION__);
    static int h0_cnt = 0,h0_cnt2 = 0;
    while(1){
        if(h0_cnt++>10*100*1000)
        {
#if(ENABLE_DEBUG_INFO)
	        os_printf("%s run", __FUNCTION__);
#endif
	        h0_cnt = 0;
            //if(h0_cnt2++>3000){
            //    os_printf("delete task", __FUNCTION__);
            //    vTaskDelete(xTask_0);
            //}
	    }
    }
}

static void task_high_1(void *p)
{
    os_printf("%s ready", __FUNCTION__);
    static int h1_cnt = 0;
    while(1){
        if(h1_cnt++>10*100*1000)
        {
#if(ENABLE_DEBUG_INFO)
	        os_printf("%s run", __FUNCTION__);
#endif
	        h1_cnt = 0;
	    }
    }
}

static void task_low_0(void *p)
{
    os_printf("%s ready", __FUNCTION__);
    static int low_cnt = 0;
    while(1){
        if(low_cnt++>10*100*1000)
        {
#if(ENABLE_DEBUG_INFO)
	        os_printf("%s run", __FUNCTION__);
#endif
	        low_cnt = 0;
	    }
    }
}
/**
  * @brief  main
  * @note   None
  * @param  None
  * @param  None
  * @retval None
  */
int main(void)
{
    BaseType_t xReturn = pdPASS;

    os_printf("Freertos v10.2.1 start ");

    /* first creat task in this 创建rtos第一个任务，用于创建其他任务 */
    xReturn = xTaskCreate(  (TaskFunction_t )task_high_0,
                            (const char *   )"task_high_0",
                            (unsigned short )128,
                            (void *         )NULL,
                            (UBaseType_t    )5,
                            (TaskHandle_t * )&xTask_0);

    if (pdPASS != xReturn){
        return -1;
    }

    xReturn = xTaskCreate(  (TaskFunction_t )task_high_1,
                            (const char *   )"task_high_1",
                            (unsigned short )128,
                            (void *         )NULL,
                            (UBaseType_t    )5,
                            (TaskHandle_t * )&xTask_1);

    if (pdPASS != xReturn){
        return -1;
    }

    xReturn = xTaskCreate(  (TaskFunction_t )task_low_0,
                            (const char *   )"task_low_0",
                            (unsigned short )128,
                            (void *         )NULL,
                            (UBaseType_t    )0,
                            (TaskHandle_t * )&xTask_2);

    if (pdPASS != xReturn){
        return -1;
    }

    /* start task 开启任务调度 */
    vTaskStartScheduler();

    while(1){
    }

    return 0;
}


/**
  * @}
  */

/******************************** (C) Tuu *********************END OF FILE****/
