#$(wildcard ./*.c)获取当前目录下所有的.c文件
#src=$(wildcard ./*.c)
#test:$(src)
#	gcc $^ -o $@


test:test.o test1.o test2.o
	gcc $^ -o $@

%.o:%.c
	gcc -c  $< -o $@

#test.o:test.c
#	gcc -c $^ -o %@

#test1.o:test1.c
#	gcc -c $^ -o %@
#test2.o:test2.c
#	gcc -c $^ -o %@




