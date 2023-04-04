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
    int cnt = 0;
    while(1){
        if(cnt++>10*100*1000){
	    os_printf("%s run", __FUNCTION__);
	    cnt = 0;
	}
    }
}

static void task_high_1(void *p)
{
    os_printf("%s ready", __FUNCTION__);
    int cnt = 0;
    while(1){
        if(cnt++>10*100*1000){
	    os_printf("%s run", __FUNCTION__);
	    cnt = 0;
	}
    }
}

static void task_low_0(void *p)
{
    os_printf("%s ready", __FUNCTION__);
    int cnt = 0;
    while(1){
        if(cnt++>100*1000){
	    os_printf("%s run", __FUNCTION__);
	    cnt = 0;
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
                            (UBaseType_t    )2,
                            (TaskHandle_t * )&xTask_0);

    if (pdPASS != xReturn){
        return -1;
    }

    xReturn = xTaskCreate(  (TaskFunction_t )task_high_1,
                            (const char *   )"task_high_1",
                            (unsigned short )128,
                            (void *         )NULL,
                            (UBaseType_t    )2,
                            (TaskHandle_t * )&xTask_1);

    if (pdPASS != xReturn){
        return -1;
    }

    xReturn = xTaskCreate(  (TaskFunction_t )task_low_0,
                            (const char *   )"task_low_0",
                            (unsigned short )128,
                            (void *         )NULL,
                            (UBaseType_t    )1,
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
