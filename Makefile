CXX=clang++
CPPFLAGS=-g -std=c++20 -Wall -O1 -fpic

bin:
	$(CXX) $(CPPFLAGS) store.cc -o store
