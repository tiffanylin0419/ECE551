CCFLAGS=--std=gnu++98 -pedantic -Wall -Werror -ggdb3
code: code.o
	g++ -o code $(CCFLAGS) code.o

%.o: %.cpp
	g++ -c $(CCFLAGS) $<

clean:
	rm -f *.o  *~ code
