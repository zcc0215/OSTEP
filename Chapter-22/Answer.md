1. Access: 8  Miss  State of Memory:[8]  
   Access: 7  Miss  State of Memory:[8,7]  
   Access: 4  Miss  State of Memory:[8,7,4]  
   Access: 2  Miss  State of Memory:[7,4,2]  
   Access: 5  Miss  State of Memory:[4,2,5]  
   Access: 4  Hit   State of Memory:[4,2,5]  
   Access: 7  Miss  State of Memory:[2,5,7]  
   Access: 3  Miss  State of Memory:[5,7,3]  
   Access: 4  Miss  State of Memory:[7,3,4]  
   Access: 5  Miss  State of Memory:[3,4,5]  
2. 最差情况需要缓存增大到与页号相同
3. python3 ./paging-policy.py -s 0 -n 10 -c -p FIFO  
   FINALSTATS hits 1   misses 9   hitrate 10.00  
   python3 ./paging-policy.py -s 0 -n 10 -c -p LRU  
   FINALSTATS hits 2   misses 8   hitrate 20.00  
   python3 ./paging-policy.py -s 0 -n 10 -c -p OPT  
   FINALSTATS hits 4   misses 6   hitrate 40.00    
   python3 ./paging-policy.py -s 0 -n 10 -c -p UNOPT  
   FINALSTATS hits 0   misses 10   hitrate 0.00  
   python3 ./paging-policy.py -s 0 -n 10 -c -p RAND  
   FINALSTATS hits 0   misses 10   hitrate 0.00  
   python3 ./paging-policy.py -s 0 -n 10 -c -p CLOCK  
   FINALSTATS hits 1   misses 9   hitrate 10.00  
4. ```
   python3 ./paging-policy.py -p LRU -c -a  $(python3 tool.py -t)  
   python3 ./paging-policy.py -p LRU -c -a  $(python3 tool.py -s)  
   
   python3 ./paging-policy.py -p RAND -c -a  $(python3 tool.py -t)  
   python3 ./paging-policy.py -p RAND -c -a  $(python3 tool.py -s)  

   python3 ./paging-policy.py -p CLOCK -c -a  $(python3 tool.py -t)  
   python3 ./paging-policy.py -p CLOCK -c -a  $(python3 tool.py -s)  
5. valgrind --tool=lackey --trace-mem=yes ls &> check.txt  
   python3 ./run.py