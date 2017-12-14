CC=g++
CFLAGS=-W -Wall -ansi -pedantic -std=c++11 -stdlib=libc++
LDFLAGS=
EXEC=main
SRC= $(wildcard *.cpp)
OBJ= $(SRC:.cpp=.o)

all: $(EXEC)

hello: $(OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.hpp

%.o: %.cpp
	@$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	@rm -rf *.o

mrproper: clean
	@rm -rf $(EXEC)