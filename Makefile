CXX=clang++
CPPFLAGS=-g -std=c++20 -Wall -Wextra -Wpedantic -O3 -fpic

bin:
	$(CXX) $(CPPFLAGS) main.cc -o caskdb-demo
