compile:
	g++ -g -std=c++11 *.cpp -o main.o
run:
	./main.o
leaks:
	leaks -atExit -- ./main.o
clean:
	rm *.o