CC=clang++
CFLAGS=-std=c++11 -g -c -Wall -Wextra -pedantic -O0
LDFLAGS=
SOURCES=main.cpp regressioncomputer.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=regr

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)
