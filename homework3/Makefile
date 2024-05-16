all : homework3

homework3 : homework3.o do_TSomething.o
	g++ homework2.o do_TSomething.o do_TSomething.h -o homework3 `root-config --cflags --glibs`

homework3.o : homework3.C
	g++ -c homework3.C -o homework3.o

do_TSomething.o : do_TSomething.cc
	g++ -c do_TSomething.cc -o do_TSomething.o `root-config --cflags --glibs`

clean :
	rm -f homework3.o do_TSomething.o homework3