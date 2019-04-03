这个文件下的工具主要处理：
生成后的16进制文件，对应的点阵字符的注释字符显示乱码替换；

使用具体步骤：
1.使用PCtoLCD2002完美版 把裁剪的 gbkchar.txt 字符集转为点阵16进制 gbkbin.txt
2.把这个生成的 gbkbin.txt 复制到该目录下，替换
3.注：gbkchar.txt 原本和 chargbk.txt 是相同的; 只是在替换时发现 gbkchar.txt 中英文空格字符需替换为中文空格，故做了替换处理
4.运行该程序:
	./test gbkbin.txt chargbk.txt out.txt
	把数组和字符重新组合，使得每个字符可见
5.把生成的 out.txt 的数据替换上级目录下的数组，将其生成为.bin文件

