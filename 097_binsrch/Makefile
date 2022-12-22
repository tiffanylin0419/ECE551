CPPFLAGS=-std=gnu++98 -pedantic -Wall -Werror -ggdb3
test: test-bsearch.o search.o
	g++ -o test search.o test-bsearch.o
search.o: search.cpp function.h
	g++ $(CPPFLAGS) -c search.cpp
test-bsearch.o: test-bsearch.cpp function.h
	g++ $(CPPFLAGS) -c test-bsearch.cpp
.PHONY: clean
clean:
	rm -f *.o *~ test
