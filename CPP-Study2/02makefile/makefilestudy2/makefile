#条件选择
ifeq ($(COMPILE),g++)
CCC := g++
else
CCC := gcc
endif



#变量
var1 = main.o
var1 += add.o

CC :=g++



#规则
#第一个依赖关系
all:add

add:$(var1)
#	g++ main.o add.o -o add  使用模式匹配符号可以改为
	$(CCC) $^ -o $@

#main.o:main.cpp
#	g++ -c main.cpp -o main.o
#add.o:add.cpp
#	g++ -c add.cpp -o add.o

#同样可以将上述两个规则利用模式匹配符号统一为一个规则
#此时的%表示所有的Makefile内容，不能换成*
%.o:%.cpp
	$(CC) -c $< -o $@


clean:
	rm -f *.o add	
	#利用通配符删去add.o和main.o 和add程序
