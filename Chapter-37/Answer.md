1. ```
   python3 ./disk.py  -a 0 -G
   python3 ./disk.py  -a 30 -G
   python3 ./disk.py  -a 7,30,8 -G
   python3 ./disk.py  -a 10,11,12,13 -G
   5.5 * 30 + 30 = 195.0
   11.5 * 30 + 30 = 375.0
   0.5 * 30 + 30 + 10 * 30 + 30 + 40 * 2 + 310 + 30 = 795.0 当从 30 扇区旋转到 8 扇区时(更换磁道)，已经超过了 8 扇区的起始点，因此需要多花 310 个时间单位旋转到 8 扇区的起始点
   3.5 * 30 + 2 * 30 + 40 + 320 + 30 * 2 = 585.0
2. ```
   python3 ./disk.py  -a 0 -c -S 2 /-S 4 /-S 8 ...
   ['195', '195', '195', '195', '195', '195']
   ['375', '375', '375', '375', '375', '1095']
   ['795', '435', '435', '435', '435', '2235']
   ['585', '585', '585', '585', '585', '945']
3. ```
   python3 ./disk.py  -a 0 -c -R 0.1 /-R 0.5 /-R 0.01 ...
   ['1950', '390', '19500']
   ['3750', '750', '37501']
   ['4349', '1590', '43500']
   ['5850', '1170', '58501']
4. FIFO: 7,30,8 SSTF: 7,8,30  
   python3 ./disk.py -a 7,30,8 -c # 795  
   python3 ./disk.py -a 7,30,8 -c -p SSTF # 375
5. 对 -a 7,30,8，SATF 与 SSTF 没有区别  
   python3 ./disk.py -a 12,31 -c -S 40 -R 3 -p SSTF # Total: 405  
   python3 ./disk.py -a 12,31 -c -S 40 -R 3 -p SATF # Total:  65  
   寻道时间远小于旋转时间
6. 寻道时间太长，导致更换磁道时，刚好旋转超过了 12，导致需要重新旋转一个周期  
   python3 ./disk.py  -a 10,11,12,13 -G -o 2  
   可以看到内圈磁道与外圈磁道偏移了两个扇区
7. python3 ./disk.py -z 10,20,30 -a -1 -A 5,-1,0 -c -s 1  
   REQUESTS [7, 45, 41, 13, 26]  
   7,13,26 为外圈,用时为255，385，120  外圈带宽为：3/(255+385+120) = 0.0039  
   45，41为中间磁道，用时为115，280  中间带宽为为：2/(115+280) = 0.00506  
8. python3 ./disk.py -A 1000,-1,0 -w 1 -p SATF -c    # Total:220125  
   python3 ./disk.py -A 1000,-1,0 -w 10 -p SATF -c   # Total:64635  
   python3 ./disk.py -A 1000,-1,0 -w 1000 -p SATF -c # Total:35475
9. python3 ./disk.py -a 12,7,8,9,10,11 -p SATF -c          // 7,8,9,10,11,12 Total: 555  
   python3  ./disk.py -a 12,7,8,9,10,11 -p BSATF -w 4 -c    // 7,8,9,12,10,11 Total: 525
10. python3 ./disk.py -a 9,20 -c  # 435  
    python3 ./disk.py -a 9,20 -c -p SATF # 465  
    贪婪算法不能保证全局最优，只能保证局部最优.

