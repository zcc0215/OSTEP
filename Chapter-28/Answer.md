1. 这个简单的"锁有一个问题",导致它并不能保证互斥,
   比如线程0执行 mov  flag, %ax 完后,时钟终端,切到线程1执行,
   而线程1在执行 mov  %ax, count 中断,切到线程0,此时线程1是拥有锁的,
   线程0继续执行 test $0, %ax ,这时ax的值是0,因为线程有单独的寄存器!!,所以线程1也获得了锁
2. flag 最终为 0
3. count 增加 4 次(每个线程增加 2 次),flag 依然为 0
4. python3 ./x86.py -p flag.s -a bx=2,bx=2 -M flag,count -c -i 1
5. 当一个线程获取锁之后 mutex 变为 1,释放锁之后 mutex 变为 0,且操作为原子操作,解决的前面的方案带来的问题

   获取锁:

   mov  $1, %ax        
   xchg %ax, mutex  
   释放锁:

   mov  $0, mutex
6. 是, 单核cpu情况下,当一个线程持有锁进入临界区时被抢占,抢占的线程将会自旋一个时间片,导致cpu利用率不高,  
量化:计算 当一个线程持有锁进入临界区时被抢占,抢占线程的自旋时间长与总时间长百分比即可
7. python3 ./x86.py -p test-and-set.s -M mutex,count -R ax,bx -c -a bx=2,bx=2 -P 0011111  
结果正确
8. 能
9. ./x86.py -p peterson.s -M count,flag,turn -R ax,cx -a bx=0,bx=1 -c -i 2
10. ./x86.py -p peterson.s -M count,flag,turn -R ax,cx -a bx=0,bx=1 -c -P 0000011111
11. 是的,ticket+1 后,旧 ticket 值存入ax
12. python3 ./x86.py -p ticket.s -a bx=1000,bx=1000 -c -M count  
    是,大量时间用于自旋
13. python3 ./x86.py -p ticket.s -a bx=1000,bx=1000,bx=1000 -c -M count -t 3  
    线程变多,cpu 利用率下降
14. python3 ./x86.py -p test-and-set.s -a bx=2 -i 13 -t 4 | wc -l  
    python3 ./x86.py -p yield.s -a bx=2 -i 13 -t 4 | wc -l
15. 减少了写锁(xchg)操作, Pentium cpu 上, xchg需要三个时钟周期,参考 而mov只需要一个时钟周期