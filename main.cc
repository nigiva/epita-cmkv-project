#include <atomic>
#include <fstream>
#include <future>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "board.hh"
#include "piece.hh"

const int numWorkers = 2;
std::optional<std::string> result(std::nullopt);
std::atomic<int> workerDoneCount(0);
std::mutex lock;

std::string readFile(std::string filepath)
{
    std::string content;
    std::ifstream file(filepath);
    if (!file.is_open())
    {
        throw "Unable to open file";
    }

    std::string line;
    while (std::getline(file, line))
    {
        content += line + '\n';
    }
    file.close();
    return content;
}

void worker(std::string inputBoardContent)
{
    Board board = Board::fromString(inputBoardContent);
    auto success = board.solve(1'000'000, // epochMax
                               1, // initialTemperature
                               0.9999, // decayRate
                               false // verbose
    );
    if (success)
    {
        if (!result.has_value())
        {
            // std::cout << "hey" << std::endl;
            lock.lock();
            result = "success";
            lock.unlock();
        }
        }
    else
    {
        std::cerr << "Worker finish but not success (loss=" << board.loss()
                  << ")" << std::endl;
    }
    workerDoneCount++;
}

std::string runWorkers(std::string inputBoardContent)
{
    // thread list
    std::thread threads[numWorkers];

    // Launch threads
    for (int i = 0; i < numWorkers; i++)
    {
        threads[i] = std::thread(worker, inputBoardContent);
        threads[i].detach();
    }

    // Wait for threads to finish
    while (true)
    {
        if (result.has_value())
        {
            return *result;
        }
        if (workerDoneCount == numWorkers)
        {
            break;
        }
    }

    std::cerr << "Unable to solve the board" << std::endl;
    exit(1);
}

int main(int argc, char **argv)
{
    // Check arguments and parse them
    bool defaultArgsCondition = (argc == 3);
    bool debugArgsCondition = (argc == 4 && std::string(argv[3]) == "--debug");
    bool debug = debugArgsCondition;
    if (!defaultArgsCondition && !debugArgsCondition)
    {
        std::cout
            << "Usage: " << argv[0]
            << " <input board filepath> <output solution filepath> (--debug)"
            << std::endl;
        return 1;
    }

    std::string inputPath = argv[1];
    std::string outputPath = argv[2];

    // Read the input board
    std::string inputBoardContent = readFile(inputPath);

    // Run all threads to solve the board
    std::string result = runWorkers(inputBoardContent);

    // Write the solution to the output file
    if (debug)
    {
        std::cout << "\n---  RESULT  ---" << std::endl;
        std::cout << result << std::endl;
    }
    return 0;
}