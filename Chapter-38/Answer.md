1. ```
    python3 raid.py -n 10 -L 5 -5 LS -c -W seq

    LOGICAL READ from addr:0 size:4096
    read  [disk 0, offset 0]   
    LOGICAL READ from addr:1 size:4096
    read  [disk 1, offset 0]   
    LOGICAL READ from addr:2 size:4096
    read  [disk 2, offset 0]   
    LOGICAL READ from addr:3 size:4096
    read  [disk 3, offset 1]   
    LOGICAL READ from addr:4 size:4096
    read  [disk 0, offset 1]   
    LOGICAL READ from addr:5 size:4096
    read  [disk 1, offset 1]   
    LOGICAL READ from addr:6 size:4096
    read  [disk 2, offset 2]   
    LOGICAL READ from addr:7 size:4096
    read  [disk 3, offset 2]   
    LOGICAL READ from addr:8 size:4096
    read  [disk 0, offset 2]   
    LOGICAL READ from addr:9 size:4096
    read  [disk 1, offset 3]  

    python3 raid.py -n 10 -L 5 -5 LA -c -W seq

    LOGICAL READ from addr:0 size:4096
    read  [disk 0, offset 0]   
    LOGICAL READ from addr:1 size:4096
    read  [disk 1, offset 0]   
    LOGICAL READ from addr:2 size:4096
    read  [disk 2, offset 0]   
    LOGICAL READ from addr:3 size:4096
    read  [disk 0, offset 1]   
    LOGICAL READ from addr:4 size:4096
    read  [disk 1, offset 1]   
    LOGICAL READ from addr:5 size:4096
    read  [disk 3, offset 1]   
    LOGICAL READ from addr:6 size:4096
    read  [disk 0, offset 2]   
    LOGICAL READ from addr:7 size:4096
    read  [disk 2, offset 2]   
    LOGICAL READ from addr:8 size:4096
    read  [disk 3, offset 2]   
    LOGICAL READ from addr:9 size:4096
    read  [disk 1, offset 3] 

    从上面读取的磁盘与偏移可以推测 left- symmetric）和 left-asymmetric 的物理磁盘布局

    left-symmetric      left-asymmetric
    0  1  2  P          0  1  2  P
    4  5  P  3          3  4  P  5
    8  P  6  7          6  P  7  8
2. ```
    python3 raid.py -n 20 -L 5 -5 LS -c -W seq -C 8K
    ...
    LOGICAL READ from addr:0 size:4096
    read  [disk 0, offset 0]   
    LOGICAL READ from addr:1 size:4096
    read  [disk 0, offset 1]   
    LOGICAL READ from addr:2 size:4096
    read  [disk 1, offset 0]   
    LOGICAL READ from addr:3 size:4096
    read  [disk 1, offset 1]   
    LOGICAL READ from addr:4 size:4096
    read  [disk 2, offset 0]   
    LOGICAL READ from addr:5 size:4096
    read  [disk 2, offset 1]   
    LOGICAL READ from addr:6 size:4096
    read  [disk 3, offset 2]   
    LOGICAL READ from addr:7 size:4096
    read  [disk 3, offset 3]   
    LOGICAL READ from addr:8 size:4096
    read  [disk 0, offset 2]   
    LOGICAL READ from addr:9 size:4096
    read  [disk 0, offset 3]  
    ... 
    布局推测：
    0  2  4  P
    1  3  5  P
    8  10 P  6
    9  11 P  7
3. ```
    python3 raid.py -n 12 -L 5 -5 LS -c -W seq -C 8K -r
    LOGICAL READ from addr:0 size:4096
    read  [disk 0, offset 0]   
    LOGICAL READ from addr:1 size:4096
    read  [disk 0, offset 1]   
    LOGICAL READ from addr:2 size:4096
    read  [disk 1, offset 0]   
    LOGICAL READ from addr:3 size:4096
    read  [disk 1, offset 1]   
    LOGICAL READ from addr:4 size:4096
    read  [disk 2, offset 0]   
    LOGICAL READ from addr:5 size:4096
    read  [disk 2, offset 1]   
    LOGICAL READ from addr:6 size:4096
    read  [disk 3, offset 2]   
    LOGICAL READ from addr:7 size:4096
    read  [disk 3, offset 3]   
    LOGICAL READ from addr:8 size:4096
    read  [disk 0, offset 2]   
    LOGICAL READ from addr:9 size:4096
    read  [disk 0, offset 3]   
    LOGICAL READ from addr:10 size:4096
    read  [disk 1, offset 2] 
    LOGICAL READ from addr:11 size:4096
    read  [disk 1, offset 3] 
4. 当请求块大小超过磁盘块大小时，一个请求需要读写多个磁盘  
   对于 RAID-4 和 RAID-5，请求块大小为 16 K 时，效率更高，因为可以同时利用多个磁盘，相当于全条带写入  
   python3 ./raid.py -n 12 -L 4 -W seq -S 8K -r -c   
   python3 ./raid.py -n 12 -L 4 -W seq -S 12K -r -c  
   python3 ./raid.py -n 12 -L 4 -W seq -S 16K -r -c  

   python3 ./raid.py -n 12 -L 5 -W seq -S 8K -r -c   
   python3 ./raid.py -n 12 -L 5 -W seq -S 12K -r -c  
   python3 ./raid.py -n 12 -L 5 -W seq -S 16K -r -c  
5. python3 ./raid.py -L 0 -t -n 100 -c -D 4 # 275.7  
   python3 ./raid.py -L 1 -t -n 100 -c -D 4 # 278.7  
   python3 ./raid.py -L 4 -t -n 100 -c -D 4 # 386.1  
   python3 ./raid.py -L 5 -t -n 100 -c -D 4 # 276.7  
6. 随着磁盘数量增加性能提升
7. 随着磁盘数量增加性能提升，但RAID-4明显比其他性能低
8. 随着磁盘数量增加性能提升，但RAID-1性能提升速度比其他慢