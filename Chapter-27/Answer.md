1. 可以看到有竞争状态提示:Possible data race during read of size 4 at 0x10C014 by thread #1

   代码行提示:at 0x1095A6: worker (main-race.c:8)

   地址提示: Address 0x10c014 is 0 bytes inside data symbol "balance"
2. 删除第 15 行代码或第 8 行代码,程序正确运行  

   加一个锁报错,依然有竞争条件, 所有变量更新周围添加锁:cd code && make && valgrind --tool=helgrind ./main-race 结果正确
3. 死锁情况:

   线程 0 获取锁 1,中断,线程 1 执行, 获取锁 2,造成死锁
4. ==28961== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 7 from 7)
5. ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 7 from 7)  
   main-deadlock-global.c 代码是没有问题的,但 valgrind 工具依然报错, 因此推断 helgrind 靠执行周期与上下文切换次数 判断死锁,因此,helgrind 并不能很好地判断死锁
6. 父线程使用大量时间自旋等待
7. ==30421== Possible data race during write of size 1 at 0x52861A5 by thread #1  
   ==30421==    by 0x109633: main (main-signal.c:17)  
   ==30421==    by 0x1095CC: worker (main-signal.c:8)  
   =30326== ERROR SUMMARY: 23 errors from 2 contexts (suppressed: 40 from 36)
8. 结果正确,性能比之前的版本要好, 对 done 变量加锁, 且将自旋等待替换为 Pthread_cond_wait, 释放锁并让出 CPU,收到信号时被唤醒,重新获取锁
9. 没有