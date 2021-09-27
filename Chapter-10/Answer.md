1. python3 ./multi.py -n 1 -L a:30:200 -c -t  
   Finished time 30
2. python3 ./multi.py -n 1 -L a:30:200 -M 300 -c -t  
   Finished time 20  
   默认 warmup time 为 10 个时间单位，10个时间单位后，处理速度翻倍（warmup rate）
3. python3 ./multi.py -n 1 -L a:30:200 -M 300 -c -t -T  
   前 10 个时间单位 最后一列每次减少 1  
   缓存进入 warm 模式后，处理速度翻倍，最后一列每次减少 2
4. python3 ./multi.py -n 1 -L a:30:200 -M 300 -c -t -T -C  
   第十个时间单位缓存变热（warm）  
   warmup time 变短，缓存更快进入热模式，处理速度加快
5. python3 ./multi.py -n 2 -L a:100:100,b:100:50,c:100:50 -c -t -C -T  
   Finished time 150  
   添加 -M 50 参数，发现时间也是 150，也就是说没有变得高效  
   可以看到，abc三个进程并没有在固定的 CPU 上运行，且缓存被清除
6. python3 ./multi.py -n 2 -L a:100:100,b:100:50,c:100:50 -A a:0,b:1,c:1 -c -C  -t -T  
  Finished time 110  
  这是最快的组合，a 作业独占cpu，应为它的工作所需缓存为 100，刚好占满空间，如果 a 与其他作业组合，则会导致两者都无法利用缓存  
7. ```
   python3 ./multi.py -n 1 -L a:100:100,b:100:100,c:100:100 -M 50 -c -C -t -T 
   Finished time 300
   python3 ./multi.py -n 2 -L a:100:100,b:100:100,c:100:100 -M 50 -c -C -t -T   
   Finished time 150
   python3 ./multi.py -n 3 -L a:100:100,b:100:100,c:100:100 -M 50 -c -C -t -T 
   Finished time 100
   python3 ./multi.py -n 4 -L a:100:100,b:100:100,c:100:100 -M 50 -c -C -t -T 
   Finished time 100

   python3 ./multi.py -n 1 -L a:100:100,b:100:100,c:100:100 -M 100 -c -C -t -T 
   Finished time 300
   python3 ./multi.py -n 2 -L a:100:100,b:100:100,c:100:100 -M 100 -c -C -t -T 
   Finished time 150
   python3 ./multi.py -n 3 -L a:100:100,b:100:100,c:100:100 -M 100 -c -C -t -T 
   Finished time 55
   python3 ./multi.py -n 4 -L a:100:100,b:100:100,c:100:100 -M 100 -c -C -t -T 
   Finished time 55

   上面四个是没有缓存的，下面四个有缓存，不过恰好只能缓存一个作业，因此，当只有两个 CPU 时，缓存并没有起作用，但 CPU 数量增加到 3 时，每个作业独占 CPU，缓存加速了作业处理
8. ``` 
   -p 参数可以让每个 CPU 拥有一个调度队列 -P 参数设置检查队列的间隔，用于 CPU 负载均衡
   python3 ./multi.py -L a:100:100,b:100:50,c:100:50 -c -p -P 0
   Finished time 200
   python3 ./multi.py -L a:100:100,b:100:50,c:100:50 -c -p -P 10
   Finished time 100
   python3 ./multi.py -L a:100:100,b:100:50,c:100:50 -c -p -P 40
   Finished time 115
   python3 ./multi.py -L a:100:100,b:100:50,c:100:50 -c -p -P 100
   Finished time 130