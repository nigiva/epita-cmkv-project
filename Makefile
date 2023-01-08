CC := g++
CFLAGS := -Wall -Werror -Wextra -g -DNDEBUG -O5 -std=c++17 -lpthread -Wl,--no-as-needed
TARGET := a.out

SRCS := $(wildcard *.cc)
OBJS := $(patsubst %.cc,%.o,$(SRC))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.cc
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) -rf $(TARGET) *.o

.PHONY: all clean
