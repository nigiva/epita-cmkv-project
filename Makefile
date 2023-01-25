CC := g++
CFLAGS := -Wall -Werror -Wextra -DNDEBUG -O5 -std=c++17 -lpthread -Wl,--no-as-needed # Release
#CFLAGS := -Wall -Werror -Wextra -g3 -no-pie -fno-builtin -std=c++17 -lpthread -Wl,--no-as-needed # Debug (Benchmark)
#CFLAGS := -Wall -Werror -Wextra -pg -no-pie -fno-builtin -std=c++17 -Wl,--no-as-needed # Debug (GDB)

BENCHMARK_ARGS := -w 4 # --export-markdown benchmark.md

TARGET := solver

SRC := $(wildcard *.cc)
OBJ := $(SRC:.cc=.o)

all: $(TARGET)

test: $(TARGET)
	bash testsuite.sh

check: $(TARGET)
	./$(TARGET) data/input/s4-01.txt export/s4-01.txt --debug

bench: benchmark

benchmark: benchmark2 benchmark3 benchmark4 benchmark5 benchmark6

benchmark2: $(TARGET)
	cat grill-2x2.sh | xargs hyperfine $(BENCHMARK_ARGS)

benchmark3: $(TARGET)
	cat grill-3x3.sh | xargs hyperfine $(BENCHMARK_ARGS)

benchmark4: $(TARGET)
	cat grill-4x4.sh | xargs hyperfine $(BENCHMARK_ARGS)

benchmark5: $(TARGET)
	cat grill-5x5.sh | xargs hyperfine $(BENCHMARK_ARGS)

benchmark6: $(TARGET)
	cat grill-6x6.sh | xargs hyperfine $(BENCHMARK_ARGS)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.cc
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) -rf $(TARGET) *.o

profile:
	./$(TARGET) data/input/s4-04.txt export.txt
	rm -f profile.txt
	gprof ./$(TARGET) gmon.out > profile.txt

.PHONY: all clean
