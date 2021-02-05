clean:
	rm -rf $(obj) test
#$(wildcard ./*.c) //获取当前目录下以.c结尾的文件

.PHONY:

test:$(obj)    
	gcc $^ -o $@

%.o:%.c
	gcc -c $< -o $@




