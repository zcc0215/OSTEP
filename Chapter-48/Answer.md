1.  awk -f q1.awk anon-deasna-021016-1300.txt  
    时间: 59.98 minutes  
    开始时间: 16 10 2002
2. ```
    $ awk '{ a[$8]++} END {for (n in a) print a[n], n}' anon-deasna-021016-1300.txt | sort -nk1 -r
    1610395 getattr
    1043752 read
    619819 write
    131453 lookup
    27699 access
    19485 setattr
    11640 remove
    9924 create
    9135 fsstat
    4290 link
    2297 readdirp
    1321 fsinfo
    918 readdir
    501 rename
    439 readlink
    187 pathconf
    136 symlink
    36 mkdir
    14 rmdir
    4 mknod

    $ awk '{ if ($5 == "C3" && ($8 == "read" || $8 == "write")) print $2, $8, $10, $12, $14 }' anon-deasna-021016-1300.txt | sort -u | wc -l
    469427

    $ awk '{ if ($5 == "C3" && ($8 == "read" || $8 == "write")) print $0 }' anon-deasna-021016-1300.txt | wc -l
    838995

    1 - 469427/838995 = 44.05% 读写重试操作
3. ```
   $ awk -f q3.awk anon-deasna-021016-1300.txt | sort -nk4 -r
    Average file size: 1682687 bytes
    Client 31.0320 requests 398535
    Client 40.03fe requests 224554
    Client 33.03fe requests 66200
    Client 45.0320 requests 14626
    Client 32.03ff requests 12915
    Client 37.03ff requests 11632
    ...
    Client 33.03ef requests 1
    136 clients
4. ```
   $ awk '{ if (($8 == "read" || $8 == "write") && $10 == "01122f009ead0d0120000000003669c1928f10016486000001122f009ead0d00" && $2 == "32.03fe") print $0}' sample

    $ awk '{ if (($8 == "read" || $8 == "write") && $10 == "01122f009ead0d0120000000003669d1c8a510016486000001122f009ead0d00" && $2 == "32.03ff") print $0}' sample

    $ awk '{ if (($8 == "read" || $8 == "write") && $10 == "01122f009ead0d01200000000087cd59588111016486000001122f009ead0d00" && $2 == "32.03fa") print $0}' sample
    写操作按顺序，读操作不是
5. ```
   $ awk -f q5.awk anon-deasna-021016-1300.txt | sort -nk4 -r
    Client 32.03ff requests 568181 replies 566186
    Client 31.0320 requests 436586 replies 434361
    Client 40.03fe requests 239866 replies 238238
    Client 32.03fe requests 112251 replies 111517
    Client 33.03fe requests 81760 replies 81166
    ...
    Client 32.03ca requests 1 replies 1
    219 clients
    只有五个客户有超过一万个请求和回复。
6. $ !awk -f q6.awk anon-deasna-021016-1300.txt | sort -n | uniq -c | python3 ./plot.py
7. 见问题二的答案
8. 查找attr缓存时间
