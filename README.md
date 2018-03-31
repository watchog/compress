编译在source文件夹下执行
make
会在文件夹下生成一个main可执行文件

压缩文件
./main 1 filename

解压缩文件
./main 2 filename


测试程序
在test目录下执行
g++ test.cc
将main拷贝到test目录下执行
./a.out > log 2>> err
出错信息会在err文件中
测试会很慢
