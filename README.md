# redevelop_FreeRTOS
项目内容：基于 FreeRTOS 添加一些功能：如CFS、Memory SWAP 等等  
# 变更履历：
## 时间：2023/04/08，内容：完善CFS调度策略
    1.规定优先级 [0,6] 使用 CFS 调度策略；  
    2.规定优先级 [7,9] 使用 RT 调度策略；  
实验结果如下：  
实验一：测试单独使用CFS调度类是否能正常工作  
  创建3个task，优先级分别为：task0:5， task1:2，task2:0  
  运行结果如下：  
task:task_high_0 , runCnt:465, vruntime:23250   
task:task_high_0 , runCnt:466, vruntime:23300   
task:task_high_0 , runCnt:467, vruntime:23350   
task:task_high_1 , runCnt:292, vruntime:23360   
task:task_high_1 , runCnt:293, vruntime:23440   
task:task_low_0 , runCnt:234, vruntime:23400  
由log可知，在task0运行467次之内，task1和task2分别运行了292\234次。  
因为3个task中，task0优先级最高，且3者都使用CFS调度器，因此使用CPU资源的时间依次递减。  
=>  实验结果符合预期。    
  
实验二：测试混合使用 CFS+RT 两种调度类的工作情况  
  创建3个task，优先级分别为：task0:8(使用RT调度器)， task1:2，task2:0  
  运行结果如下：  
task:task_high_0 , runCnt:7107, vruntime:142140   
task:task_high_0 , runCnt:7108, vruntime:142160   
task:task_high_0 , runCnt:7109, vruntime:142180   
task:task_high_0 , runCnt:7110, vruntime:142200  
由log可知，系统中只有task0在运行。  
因为此时task优先级为8，使用RT调度器，除非其退出/挂起，否则使用CFS策略的其他task将得不到运行  
=>  实验结果符合预期。   


## 时间：2023/04/06: 添加 CFS 调度策略
内容：    
      1.在FreeRTOS中实现类似于 Linux 的 CFS 调度策略（使用虚拟时间作为依据选择下一个要调度的task，虚拟时间=实际时间×优先级因子）  
      2.控制宏开关为 configUSE_CFS (FreeRTOSConfig.h)   
      3.=0(Disable),=1(Enable),不允许只定义不赋值。  

 代码运行测试如下：  
 环境：创建3个task0~2，优先级分别为 9,5,1  
 未加入CFS调度策略前：  
 task(task_high_0) running   
 task(task_high_0) running   
 task(task_high_0) running   
 task(task_high_0) running   
 task(task_high_0) running   
 task(task_high_0) running   
 理论上，根据实时调度策略特点，高优先级task未退出，则较低优先级的task则不能执行 => 实验结果符合预期。  
  
 加入CFS调度策略后：  
 task(task_high_0) running run_cnt:2336 - vruntime:2336   
 task(task_high_0) running run_cnt:2337 - vruntime:2337   
 task(task_high_0) running run_cnt:2338 - vruntime:2338   
 task(task_high_0) running run_cnt:2339 - vruntime:2339   
 task(task_high_0) running run_cnt:2340 - vruntime:2340   
 task(task_high_1) running run_cnt:468 - vruntime:2340   
 task(task_high_1) running run_cnt:469 - vruntime:2345   
 task(task_low_0) running run_cnt:260 - vruntime:2340   
 task(task_low_0) running run_cnt:261 - vruntime:2349   
 task(task_high_0) running run_cnt:2341 - vruntime:2341   
 task(task_high_0) running run_cnt:2342 - vruntime:2342   
 task(task_high_0) running run_cnt:2343 - vruntime:2343   
 理论上，task0具有更高的优先级，应该得到更多的CPU资源，task1 和 task2 优先级递减，得到的资源更少。   
 从实验结果上看，task0 执行了2340次，对应的vruntime为2340；task1执行260次，vruntime达到2340，而最低优先级的task2虽然优先级低，  
 但是在 task0 执行了 2340次中，也能得到260次的执行。=> 实验结果符合预期。  

## 上传 FreeRTOS_on_Linux 的基础代码     


