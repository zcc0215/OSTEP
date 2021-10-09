1. ```
   python3 vsfs.py -n 6 -s 17
   python3 vsfs.py -n 6 -s 18
   python3 vsfs.py -n 6 -s 19
   python3 vsfs.py -n 6 -s 20
2. ```
   python3 vsfs.py -s 21 -r
3. ```
   python3 vsfs.py -d 2 -c -n 100 -p
   在根目录下空文件与链接
4. ```
   python3 vsfs.py -i 2 -c -n 100 -p
   除了unlink其他操作都会失败，只有第一个inode可用
   换成3个inode,会有一个空目录或者小文件