#仅仅只有一个目标，没有命令
all:hello


#既有目标也有依赖也有命令 多个规则可以是同一目标，比如下面就是有两个规则
hello:hello.o
	g++ hello.o -o hello
hello.o:hello.cpp
	g++ -c hello.cpp -o hello.o


#没有依赖只有目标和命令  多个目标可以指向一个规则
clean doclean:
	rm hello.[^.cpp]
