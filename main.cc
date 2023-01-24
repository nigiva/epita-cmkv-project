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

std::optional<std::string> worker(std::string inputBoardContent)
{
    Board board = Board::fromString(inputBoardContent);
    auto success = board.solve(1'000'000, // epochMax
                               1, // initialTemperature
                               0.9999, // decayRate
                               false // verbose
    );
    if (success)
    {
        return "success";
    }
    else
    {
        //
        std::cerr << "Worker finish but not success (loss=" << board.loss()
                  << ")" << std::endl;
        return std::nullopt;
    }
}

std::string runWorkers(std::string inputBoardContent)
{
    std::vector<std::future<std::optional<std::string>>> futureList;
    std::string result;
    for (int i = 0; i < numWorkers; i++)
    {
        futureList.push_back(
            std::async(std::launch::async, worker, inputBoardContent));
    }

    int numberWorkersFinished = 0;
    while (numberWorkersFinished < numWorkers)
    {
        numberWorkersFinished = 0;
        for (auto &future : futureList)
        {
            if (future.wait_for(std::chrono::seconds(0))
                == std::future_status::ready)
            {
                numberWorkersFinished++;
                auto result = future.get();
                if (result.has_value())
                {
                    return result.value();
                }
            }
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