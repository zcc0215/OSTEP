1. ```
   线程 0 调用在前
   ->add(0, 1)
   <-add(0, 1)
              ->add(0, 1)
              <-add(0, 1)
   或线程 0 调用在后:
              ->add(0, 1)
              <-add(0, 1)
   ->add(0, 1)
   <-add(0, 1)
2. ```
   死锁分析:
   线程 1:
   调用：vector_add(v1,v2)，获取 v1 的锁，切换到线程 2
   线程 2:
   调用：vector_add(v2,v1)，获取 v2 的锁，然后尝试获取 v1 的锁，最终循环等待造成死锁
3. 死锁概率变大， -n 0 、-n 1 不会发生死锁
4. 代码按照锁的地址大小获取锁，所有线程获取锁的顺序相同，因此不会发生上面的锁的调用顺序问题而造成死锁,当 vectors 相同时，锁只能获取一次
5. ```
   ./vector-global-order -t -n 2 -l 100000 -d
   Time: 0.05 seconds

   ./vector-global-order -t -n 2 -l 200000 -d
   Time: 0.09 seconds

   ./vector-global-order -t -n 4 -l 100000 -d
   Time: 0.25 seconds
6. ```
   ./vector-global-order -t -n 2 -l 100000 -d -p
   Time: 0.03 seconds

   ./vector-global-order -t -n 2 -l 200000 -d -p
   Time: 0.03 seconds

   ./vector-global-order -t -n 4 -l 100000 -d -p
   Time: 0.04 seconds

   多线程不需要竞争等待锁
7. 这种方法有小概率造成活锁  
   可以将第一个try_lock 替换为 Pthread_mutex_lock()，不会造成死锁  
   ```
   ./vector-try-wait -t -n 2 -l 100000 -d -p
   Retries: 0
   Time: 0.02 seconds

   ./vector-try-wait  -t -n 2 -l 200000 -d -p
   Retries: 0
   Time: 0.03 seconds

   ./vector-try-wait -t -n 4 -l 100000 -d -p
   Retries: 0
   Time: 0.03 seconds
8. 锁太多，影响性能
   ```
   ./vector-avoid-hold-and-wait -t -n 2 -l 100000 -d
   Time: 0.18 seconds

   ./vector-avoid-hold-and-wait   -t -n 2 -l 200000 -d
   Time: 0.41 seconds

   ./vector-avoid-hold-and-wait -t -n 4 -l 100000 -d
   Time: 0.40 seconds

   ./vector-avoid-hold-and-wait -t -n 2 -l 100000 -d -p
   Time: 0.06 seconds

   ./vector-avoid-hold-and-wait   -t -n 2 -l 200000 -d -p
   Time: 0.07 seconds

   ./vector-avoid-hold-and-wait -t -n 4 -l 100000 -d -p
   Time: 0.07 seconds
9. 使用 fetch_and_add 原语
10. ```
    ./vector-nolock -t -n 2 -l 100000 -d
    Time: 0.35 seconds

    ./vector-nolock  -t -n 2 -l 200000 -d
    Time: 0.77 seconds

    ./vector-nolock   -t -n 4 -l 100000 -d
    Time: 0.65 seconds

    ./vector-nolock -t -n 2 -l 100000 -d -p
    Time: 0.05 seconds

    ./vector-nolock  -t -n 2 -l 200000 -d -p
    Time: 0.10 seconds

    ./vector-nolock   -t -n 4 -l 100000 -d -p
    Time: 0.09 seconds