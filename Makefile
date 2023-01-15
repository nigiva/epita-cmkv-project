CC := g++
CFLAGS := -Wall -Werror -Wextra -g -DNDEBUG -O5 -std=c++17 -lpthread -Wl,--no-as-needed
TARGET := solver

SRC := $(wildcard *.cc)
OBJ := $(SRC:.cc=.o)

all: $(TARGET)

test: $(TARGET)
	./$(TARGET) data/input/s2-02.txt export.txt

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.cc
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) -rf $(TARGET) *.o

.PHONY: all clean
