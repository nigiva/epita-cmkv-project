CC := g++
CFLAGS := -Wall -Werror -Wextra -DNDEBUG -O5 -std=c++17 -lpthread -Wl,--no-as-needed # Release
#CFLAGS := -Wall -Werror -Wextra -pg -no-pie -fno-builtin -std=c++17 -lpthread -Wl,--no-as-needed # Debug
TARGET := solver

SRC := $(wildcard *.cc)
OBJ := $(SRC:.cc=.o)

all: $(TARGET)

test: $(TARGET)
	./$(TARGET) data/input/s4-01.txt export.txt --debug

benchmark: benchmark4 benchmark6

benchmark4: $(TARGET)
	cat grill-4x4.sh | xargs hyperfine -i

benchmark6: $(TARGET)
	cat grill-6x6.sh | xargs hyperfine -i

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
