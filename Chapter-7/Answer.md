1. SJF	200	400  
   FIFO	200	400  
2. SJF	400/3	1000/3  
   FIFO	400/3	1000/3  
3. 长度为 200: RR:平均响应时间 = 1 平均周转时间 = 599  
   长度为 100, 200, 300: RR:平均响应时间 = 1 平均周转时间 = 456.67  
4. 运行时间相同的任务  
5. 运行时间 <= 时间片  
6. 响应时间越来越长  
7. 平均响应时间增加  
   时间片 >= 工作最长运行时间时,有最坏情况 即 ti 为作业运行时间 res_avg = (0 + t1 + (t1+t2) + (t1+t2+t3) + ... (t1+t2+t3 +...tN-1))/N