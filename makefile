CC = clang++
LIBS = -I/usr/include/jsoncpp -ljsoncpp
FLAGS = -g -std=c++11 -Wall -pedantic -o
PROGRAM = flt4
FILES=$(addprefix build/, $(patsubst %.cpp, %.o, $(wildcard *.cpp)))

all: $(PROGRAM)

$(PROGRAM): $(FILES)
	$(CC) $(FLAGS) $@ $^ $(LIBS)

build/%.o: %.cpp
	$(CC) $(FLAGS) $@ -c $^ $(LIBS)

.PHONY: clean
clean:
	rm -rf build/* $(PROGRAM)
