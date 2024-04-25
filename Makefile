GTESTFLAGS=-lgtest

all: compile check

check:
	./test-percent-encode

clean:
	rm -fv ./test-percent-encode

compile:
	g++ -I. -o test-percent-encode test-percent-encode.cpp percent-encode.cpp $(GTESTFLAGS) 
