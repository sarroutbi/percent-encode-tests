GTESTFLAGS=-lgtest

.PHONY: all check compile clean test

all: compile

test: check

check: ./test-percent-encode
	./test-percent-encode

clean:
	rm -fv ./test-percent-encode
	rm -fv ./*~

compile:
	g++ -I. -o test-percent-encode test-percent-encode.cpp percent-encode.cpp $(GTESTFLAGS) 
