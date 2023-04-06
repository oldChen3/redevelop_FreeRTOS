# redevelop_FreeRTOS
项目内容：基于 FreeRTOS 添加一些功能：如CFS、Memory SWAP 等等

# 变更履历：
## 上传 FreeRTOS_on_Linux 的基础代码


## 时间：2023/04/06
## 内容：
###      1.在FreeRTOS中实现类似于 Linux 的 CFS 调度策略（使用虚拟时间作为依据选择下一个要调度的task，虚拟时间=实际时间×优先级因子）
###      2.控制宏开关为 configUSE_CFS (FreeRTOSConfig.h)
###      3.=0(Disable),=1(Enable),不允许只定义不赋值。

### 代码运行测试如下：
### 环境：创建3个task0~2，优先级分别为 9,5,1
### 未加入CFS调度策略前：
### task(task_high_0) running 
### task(task_high_0) running 
### task(task_high_0) running 
### task(task_high_0) running 
### task(task_high_0) running 
### task(task_high_0) running 
### 理论上，根据实时调度策略特点，高优先级task未退出，则较低优先级的task则不能执行 => 实验结果符合预期。

### 加入CFS调度策略后：
### task(task_high_0) running run_cnt:2336 - vruntime:2336 
### task(task_high_0) running run_cnt:2337 - vruntime:2337 
### task(task_high_0) running run_cnt:2338 - vruntime:2338 
### task(task_high_0) running run_cnt:2339 - vruntime:2339 
### task(task_high_0) running run_cnt:2340 - vruntime:2340 
### task(task_high_1) running run_cnt:468 - vruntime:2340 
### task(task_high_1) running run_cnt:469 - vruntime:2345 
### task(task_low_0) running run_cnt:260 - vruntime:2340 
### task(task_low_0) running run_cnt:261 - vruntime:2349 
### task(task_high_0) running run_cnt:2341 - vruntime:2341 
### task(task_high_0) running run_cnt:2342 - vruntime:2342 
### task(task_high_0) running run_cnt:2343 - vruntime:2343 
### 理论上，task0具有更高的优先级，应该得到更多的CPU资源，task1 和 task2 优先级递减，得到的资源更少。
### 从实验结果上看，task0 执行了2340次，对应的vruntime为2340；task1执行260次，vruntime达到2340，而最低优先级的task2虽然优先级低，
### 但是在 task0 执行了 2340次中，也能得到260次的执行。=> 实验结果符合预期。

