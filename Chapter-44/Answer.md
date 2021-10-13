1. python3 ./checksum.py
2. python3 ./checksum.py -s 1
3. python3 ./checksum.py -D 1,2,4,8 -c 每个二进制位置只被一个数字占据
4. python3 ./checksum.py -D 1,2,3,4 -c 有些二进制位置被多个数字占据
5. python3 ./checksum.py -D 3,12,48,192 -c  
   python3 ./checksum.py -D 129,66,36,24 -c 这些数字的总和是一样的
6. 这些数字的总和是一样的
7. 顺序对Fletcher来说很重要，但对其他两个校验和来说并不重要
8. python3 ./checksum.py -D 0,1,2,3 -c  
   python3 ./checksum.py -D 255,1,2,3 -c  
   当两个数字余255相同时