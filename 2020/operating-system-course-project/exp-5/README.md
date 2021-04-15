# 复制文件

**Description:**

完成一个目录复制命令mycp，包括目录下的文件和子目录, 运行结果如下：

```shell
$ ls -l sem
total 56
drwxr-xr-x 3 beta beta 4096 Dec 19 02:53 ./
drwxr-xr-x 8 beta beta 4096 Nov 27 08:49 ../
-rw-r--r-- 1 beta beta 128 Nov 27 09:31 Makefile
-rwxr-xr-x 1 beta beta 5705 Nov 27 08:50 consumer*
-rw-r--r-- 1 beta beta 349 Nov 27 09:30 consumer.c
drwxr-xr-x 2 beta beta 4096 Dec 19 02:53 subdir/
$ mycp sem target
$ ls -l targe
ttotal 56
drwxr-xr-x 3 beta beta 4096 Dec 19 02:53 ./
drwxr-xr-x 8 beta beta 4096 Nov 27 08:49 ../
-rw-r--r-- 1 beta beta 128 Nov 27 09:31 Makefile
-rwxr-xr-x 1 beta beta 5705 Nov 27 08:50 consumer*
-rw-r--r-- 1 beta beta 349 Nov 27 09:30 consumer.c
drwxr-xr-x 2 beta beta 4096 Dec 19 02:53 subdir/ 
```

说明：

Linux: creat，read，write等系统调用

Windows: CreateFile(), ReadFile(), WriteFile(), CloseHandle()等函数

要求能够复制嵌套文件夹(文件夹里有文件夹)、链接文件

