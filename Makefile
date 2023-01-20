CC := g++
CFLAGS := -Wall -Werror -Wextra -DNDEBUG -O5 -std=c++17 -lpthread -Wl,--no-as-needed # Release
#CFLAGS := -Wall -Werror -Wextra -pg -no-pie -fno-builtin -std=c++17 -lpthread -Wl,--no-as-needed # Debug
TARGET := solver

SRC := $(wildcard *.cc)
OBJ := $(SRC:.cc=.o)

all: $(TARGET)

test: $(TARGET)
	./$(TARGET) data/input/s2-02.txt export.txt --debug

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.cc
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) -rf $(TARGET) *.o

profile:
	./$(TARGET) data/input/s4-02.txt export.txt
	rm -f profile.txt
	gprof ./$(TARGET) gmon.out > profile.txt

.PHONY: all clean
