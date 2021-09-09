1. 页数为 1m/1k = 1024  
   页表大小 = 地址空间大小/页大小  页数多，页表大  
   当使用很大的页时会造成大量空间被浪费(页的空间没有被使用完也不能再分割)  
2. 有效页比例增大  
3. 第三个页太大(Linux 页的大小为 4k),导致太多空间被浪费  
4. python3 ./paging-linear-translate.py -P 0 ：页大小为0  
   python3 ,/paging-linear-translate.py -P 1m -a  512m  -p 256m -v -s 3：地址空间大于物理内存
