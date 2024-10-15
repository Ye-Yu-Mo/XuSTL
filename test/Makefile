.PHONY:all
all:clean test
test:main.cpp
	g++ $^ -o $@ -std=c++11 -I../include/

clean:
	rm -rf test