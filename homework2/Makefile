all : homework2

homework2 : homework2.o do_TSomething.o
	gcc homework2.o do_TSomething.o do_TSomething.h -o homework2 `root-config --cflags --glibs` -lstdc++

homework2.o : homework2.c
	gcc -c homework2.c -o homework2.o

do_TSomething.o : do_TSomething.cc
	g++ -c do_TSomething.cc -o do_TSomething.o `root-config --cflags --glibs`

clean :
	rm -f homework2.o do_TSomething.o homework2