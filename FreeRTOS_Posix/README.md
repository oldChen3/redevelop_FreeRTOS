## 运行：
### 1.进入到目录 FreeRTOS_Posix/study_demo/
### 2.选择一个 demo 进入（如 rtos_task_cfs）
### 3.执行 ./build.sh

## 目录结构：
FreeRTOS_Posix
### - - - FreeRTOS_Kernel/
### - - - include/ => 存放系统功能的头文件
### - - - - - queue.h,  timer.h  task.h etc... 
### - - - queue.c, task.c, timers.c etc...  => 系统提供的功能：队列、任务、定时器 等等
### - - - portable/  => 可移植文件，系统功能相当于中间层，最终调用该目录下的函数（相当于硬件驱动层），驱动层需要按要求实现中间层的接口和宏定义
### - - - - - - GCC/Posix    =>  
### - - - - - - - - - - portmacro.h  => 宏定义+API 定义
### - - - - - - - - - - port.c  =>  中断操作实现、原子操作实现（挂起、停止调度、恢复调度、保护现场）
### - - - - - - MemMang  => 内存管理相关
### - - - - - - - - - - heap_3.c
### - - - demo/
### - - - FreeRTOSConfig.h  =>  freertos 提供的功能（使用宏开关控制）
### - - - config.h  => 用户配置系统功能（使用宏）
