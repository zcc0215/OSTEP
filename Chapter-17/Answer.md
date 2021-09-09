1. ptr[0] = Alloc(3)  returned 1000  
   List[ Size 1 ]: [addr: 1003 sz:97]   
     
   Free(ptr[0]) returned 0  
   List[ Size 2 ]: [addr:1000 sz 3] [addr: 1003 sz:97]  
     
   ptr[1] = Alloc(5)  returned 1003  
   List[ Size 2 ]: [addr:1000 sz 3] [addr: 1008 sz:92]  
     
   Free(ptr[1]) returned 0  
   List[ Size 3 ]: [addr:1000 sz 3] [addr: 1003 sz:5] [addr: 1008 sz:92]  
     
   ptr[2] = Alloc(8)  returned 1008  
   List[ Size 3 ]: [addr:1000 sz 3] [addr: 1003 sz:5]  [addr: 1016 sz:84]  
     
   Free(ptr[2]) returned 0  
   List[ Size 4 ]: [addr:1000 sz 3] [addr: 1003 sz:5] [addr: 1008 sz:8] [addr: 1016 sz:84]  
     
   ptr[3] = Alloc(8)  returned 1008  
   List[ Size 3 ]: [addr:1000 sz 3] [addr: 1003 sz:5] [addr: 1016 sz:84]   
     
   Free(ptr[3]) returned 0  
   List[ Size 4 ]: [addr:1000 sz 3] [addr: 1003 sz:5] [addr: 1008 sz:8] [addr: 1016 sz:84]   
     
   ptr[4] = Alloc(2)  returned 1000  
   List[ Size 4 ]: [addr:1002, sz 1] [addr: 1003 sz:5] [addr: 1008 sz:8] [addr: 1016 sz:84]   
     
   ptr[5] = Alloc(7)  returned 1008  
   List[ Size 4 ]: [addr:1002 sz 1] [addr: 1003 sz:5] [addr: 1015 sz:1] [addr: 1016 sz:84] 
       
   由于没有合并,空闲空间碎片越来越多  
2. 空闲空间碎片更多  
3. 遍历时间变短  
4. 三种排序方式在 free 时会变慢,因为插入空闲块时需要遍历空闲列表,来达成某种排序方式  
   按照空闲块大小递减排序:该方式会让最差适应算法搜索更快  
5. 空闲列表没有合并,随着时间推移,大型分配请求会因为内存空间不足而返回 NULL,且空间碎片越来越多 排序后搜索可能更快  
6. 高于 50 时,内存空间分配多于释放,可能导致内存不够  
   接近 0 时, 释放多余分配  
7. 使用最差适应算法申请大量空间大小为 1 的块,然后释放,且不合并  