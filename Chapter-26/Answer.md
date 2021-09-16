1. ```
   dx          Thread 0             
   0     
   -1        1000 sub  $1,%dx  
   -1        1001 test $0,%dx  
   -1        1002 jgte .top  
2. ```
    dx          Thread 0                Thread 1           
    3     
    2    1000 sub  $1,%dx  
    2    1001 test $0,%dx  
    2    1002 jgte .top  
    1    1000 sub  $1,%dx  
    1    1001 test $0,%dx  
    1    1002 jgte .top  
    0    1000 sub  $1,%dx  
    0    1001 test $0,%dx  
    0    1002 jgte .top  
    -1   1000 sub  $1,%dx  
    -1   1001 test $0,%dx  
    -1   1002 jgte .top  
    -1   1003 halt  
   线程 1 运行结果与线程 0 相同, 多个线程不会影响计算,因为指令执行长度小于中断周期, 这段代码没有竞态条件
3. 中断频率会改变程序的行为, 当中断发生在临界区时可能会导致一些问题
4. ```
    2000          Thread 0         
    0   
    0   1000 mov 2000, %ax ; (%ax)=0
    0   1001 add $1, %ax ; (%ax)=1
    1   1002 mov %ax, 2000; 
    1   1003 sub  $1, %bx ; (%bx)=-1
    1   1004 test $0, %bx ;
    1   1005 jgt .top
    1   1006 halt
5. jgt 指令:如果测试值第二个参数大于第一个则跳转

   两个线程 bx 寄存器初始值都是 3,

   每次循环 bx 减 1,循环三次后 bx 值为 0,终止循环,因此循环三次

   x 最终值为(即内存地址 2000 的值) 6, 因为运行期间没有被中断,并且有 2 个线程修改内存地址 2000 的值
6. x 最终值为 2,

    其他情况算法类似,

    -s 1 时,x 为 1, -s 2时, x 为 2,

    中断发生在临界区时会出现问题,临界区是多线程访问共享变量的片段

    具体到本题,临界区是将 2000 区域内存复制到 ax 之后,将 ax 值写回 2000 之前
7. ax 最终值为 1,其余情况算法相同,分别为:

   -i 2时,最终值为 1,-i 3时最终值为 2,-i 3的结果是正确的
8.  python3 ./x86.py -p looping-race-nolock.s -a bx=1 -t 2 -M 2000 -i 1 -c   
    python3 ./x86.py -p looping-race-nolock.s -a bx=1 -t 2 -M 2000 -i 2 -c  
    python3 ./x86.py -p looping-race-nolock.s -a bx=1 -t 2 -M 2000 -i 3 -c  
    python3 ./x86.py -p looping-race-nolock.s -a bx=1 -t 2 -M 2000 -i 4 -c  
    python3 ./x86.py -p looping-race-nolock.s -a bx=1 -t 2 -M 2000 -i 5 -c  
    python3 ./x86.py -p looping-race-nolock.s -a bx=1 -t 2 -M 2000 -i 6 -c  
    python3 ./x86.py -p looping-race-nolock.s -a bx=1 -t 4 -M 2000 -i 8 -c  
9. ax 寄存器最值没有变化, 地址 2000 最终值为 1
10. 线程 0 一直在循环直到中断(等待 2000 内存的值变为 1), 没有高效利用 cpu,线程 0 一直占用 cpu 循环等待