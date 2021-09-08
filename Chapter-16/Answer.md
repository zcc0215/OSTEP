1. VA  0: 0x0000006c (decimal:  108) --> sPA(段1)(物理地址492)  
   VA  1: 0x00000061 (decimal:   97) --> segmentation violation(段1)  
   VA  2: 0x00000035 (decimal:   53) --> segmentation violation(段0)  
   VA  3: 0x00000021 (decimal:   33) --> segmentation violation(段0)  
   VA  4: 0x00000041 (decimal:   65) --> segmentation violation(段1)  
     
   VA  0: 0x00000011 (decimal:   17) --> PA(段0)(物理地址:17)  
   VA  1: 0x0000006c (decimal:  108) --> PA(段1)(物理地址:492)  
   VA  2: 0x00000061 (decimal:   97) --> segmentation violation(段1)  
   VA  3: 0x00000020 (decimal:   32) --> segmentation violation(段0)  
   VA  4: 0x0000003f (decimal:   63) --> segmentation violation(段0)  
     
   VA  0: 0x0000007a (decimal:  122) --> PA(段1)(物理地址:506)  
   VA  1: 0x00000079 (decimal:  121) --> PA(段1)(物理地址:505)  
   VA  2: 0x00000007 (decimal:    7) --> PA(段0)(物理地址:7)  
   VA  3: 0x0000000a (decimal:   10) --> PA(段0)(物理地址:10)  
   VA  4: 0x0000006a (decimal:  106) --> segmentation violation(段1)  
2. 0 中最高的合法虚拟地址 19  
   段 1 中最低的合法虚拟地址 108  
   在整个地址空间中,最低和最高的非法地址是 20,107  
   运行以下代码进行测试  
   python3 ./segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 1 -A 19,108,20,107 -c  
3. python4 ./segmentation.py -a 16 -p 128 -A 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 --b0 0 --l0 2 --b1 15 --l1 2  
4. python3 ./segmentation.py -a 100 -p 200 --b0 0 --l0 80 --b1 100 --l1 10  
   只要段 0 段 1 界限寄存器的值占地址空间 90%即可  
5. --b0 0 --l0 0 --b1 0 --l1 0