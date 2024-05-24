compile:
	g++ -g -std=c++11 *.cpp -o main
run:
	./main
leaks:
	leaks -atExit -- ./main
clean:
	rm *.o