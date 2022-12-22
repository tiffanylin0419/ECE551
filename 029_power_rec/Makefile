test-power: test-power.o power.o
	gcc -o test-power test-power.o power.o
test-power.o: test-power.c power.o 
	gcc -std=gnu99 -pedantic -c test-power.c power.o 
power.o: power.c
	gcc -std=gnu99 -pedantic -c -Wall power.c
