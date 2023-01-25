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
	bash checkref.sh

check: $(TARGET)
	mkdir -p export
	./$(TARGET) data/input/s4-01.txt export/s4-01.txt --debug

bench: benchmark

benchmark: benchmark2 benchmark3 benchmark4 benchmark5 benchmark6

benchmark2: $(TARGET)
	mkdir -p export
	cat grill-args/grill-2x2.args.txt | xargs hyperfine $(BENCHMARK_ARGS)

benchmark3: $(TARGET)
	mkdir -p export
	cat grill-args/grill-3x3.args.txt | xargs hyperfine $(BENCHMARK_ARGS)

benchmark4: $(TARGET)
	mkdir -p export
	cat grill-args/grill-4x4.args.txt | xargs hyperfine $(BENCHMARK_ARGS)

benchmark5: $(TARGET)
	mkdir -p export
	cat grill-args/grill-5x5.args.txt | xargs hyperfine $(BENCHMARK_ARGS)

benchmark6: $(TARGET)
	mkdir -p export
	cat grill-args/grill-6x6.args.txt | xargs hyperfine $(BENCHMARK_ARGS)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.cc
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) -rf $(TARGET) *.o gmon.out

profile:
	./$(TARGET) data/input/s4-04.txt export/s4-01.txt
	rm -f profile.txt
	gprof ./$(TARGET) gmon.out > profile.txt

.PHONY: all clean
