#include "board.hh"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <sstream>
#include <stdexcept>

#include "piece.hh"

Board::Board(size_t size)
    : size(size)
    , board(size, std::vector<std::optional<Piece>>(size))
    , numPieces(size * size)
    , numEdges(4 * size)
{}

void Board::setPiece(size_t x, size_t y, Piece piece)
{
    if (x >= size || y >= size)
    {
        throw std::invalid_argument("Invalid coordinates");
    }
    board[x][y] = piece;
}

std::optional<Piece> Board::getPiece(long long int x, long long int y) const
{
    if (x < 0 || y < 0)
    {
        return std::nullopt;
    }

    if (static_cast<size_t>(x) >= size || static_cast<size_t>(y) >= size)
    {
        return std::nullopt;
    }

    return board[x][y];
}

std::string Board::getBoardSeperator(size_t size)
{
    std::string linePattern = "+" + std::string(5, '-');
    std::string buffer = "";
    for (size_t i = 0; i < size; i++)
    {
        buffer += linePattern;
    }
    return buffer + "+\n";
}

Board Board::fromString(std::string input)
{
    std::vector<Piece> pieces;
    std::istringstream stream(input);
    std::string line;
    while (std::getline(stream, line))
    {
        if (line.empty())
        {
            continue;
        }
        pieces.push_back(Piece::fromString(line));
    }

    size_t numPieces = pieces.size();
    size_t size = sqrt(numPieces);

    if (size == 0 || size * size != numPieces)
    {
        throw std::invalid_argument("Invalid board size");
    }

    Board board = Board(size);
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            board.setPiece(i, j, pieces[i * size + j]);
        }
    }
    return board;
}

size_t Board::getSize() const
{
    return size;
}

void Board::print() const
{
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            if (board[i][j].has_value())
            {
                std::cout << board[i][j].value() << std::endl;
            }
            else
            {
                std::cout << "-x-" << std::endl;
            }
        }
    }
}

std::string Board::getBoardOnePieceLine(std::vector<size_t> numberList)
{
    std::string buffer = "";
    for (size_t i = 0; i < numberList.size(); i++)
    {
        buffer += "|  " + std::to_string(numberList[i]) + "  ";
    }
    return buffer + "|\n";
}

std::string Board::getBoardTwoPieceLine(std::vector<size_t> firstNumberList,
                                        std::vector<bool> anchorList,
                                        std::vector<size_t> secondNumberList)
{
    std::string buffer = "";
    for (size_t i = 0; i < firstNumberList.size(); i++)
    {
        buffer += "| " + std::to_string(firstNumberList[i]);
        buffer += anchorList[i] ? "@" : " ";
        buffer += std::to_string(secondNumberList[i]) + " ";
    }
    return buffer + "|\n";
}

std::ostream &operator<<(std::ostream &os, const Board &board)
{
    os << Board::getBoardSeperator(board.getSize());
    for (size_t i = 0; i < board.getSize(); i++)
    {
        std::vector<size_t> northNumberList;
        std::vector<size_t> westNumberList;
        std::vector<size_t> eastNumberList;
        std::vector<size_t> southNumberList;
        std::vector<bool> anchorList;
        for (size_t j = 0; j < board.getSize(); j++)
        {
            std::optional<Piece> piece = board.getPiece(i, j);
            if (!piece.has_value())
            {
                piece = Piece(0, 0, 0, 0, true);
            }
            northNumberList.push_back(piece.value().getNorth());
            westNumberList.push_back(piece.value().getWest());
            eastNumberList.push_back(piece.value().getEast());
            southNumberList.push_back(piece.value().getSouth());
            anchorList.push_back(piece.value().getIsAnchored());
        }
        os << Board::getBoardOnePieceLine(northNumberList);
        os << Board::getBoardTwoPieceLine(westNumberList, anchorList,
                                          eastNumberList);
        os << Board::getBoardOnePieceLine(southNumberList);
        os << Board::getBoardSeperator(board.getSize());
    }
    return os;
}

std::vector<Coords> Board::getMovablePieceCoordsList() const
{
    std::vector<Coords> coordsList;
    for (size_t i = 0; i < this->size; i++)
    {
        for (size_t j = 0; j < this->size; j++)
        {
            std::optional<Piece> piece = this->getPiece(i, j);
            if (piece.has_value() && !piece.value().getIsAnchored())
            {
                coordsList.push_back(Coords(i, j));
            }
        }
    }
    return coordsList;
}

std::pair<Coords, Coords> Board::get2RandomMovablePieceCoords() const
{
    std::vector<Coords> coordsList = this->getMovablePieceCoordsList();
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(coordsList.begin(), coordsList.end(), g);
    return std::make_pair(coordsList[0], coordsList[1]);
}

void Board::randomSwap()
{
    std::pair<Coords, Coords> coordsPair = this->get2RandomMovablePieceCoords();
    this->lastRandomSwap = coordsPair;
    this->swap(coordsPair.first, coordsPair.second);
}

void Board::reverseLastRandomSwap()
{
    if (this->lastRandomSwap.has_value())
    {
        this->swap(this->lastRandomSwap.value().first,
                   this->lastRandomSwap.value().second);
        this->lastRandomSwap = std::nullopt;
    }
}

void Board::swap(const Coords &coords1, const Coords &coords2)
{
    size_t x1 = coords1.x;
    size_t y1 = coords1.y;
    size_t x2 = coords2.x;
    size_t y2 = coords2.y;
    std::optional<Piece> temp = this->board[x1][y1];
    this->board[x1][y1] = this->board[x2][y2];
    this->board[x2][y2] = temp;
}

float Board::loss() const
{
    float loss = 0;
    for (int i = 0; i < static_cast<int>(this->size); i++)
    {
        for (int j = 0; j < static_cast<int>(this->size); j++)
        {
            std::optional<Piece> piece = this->getPiece(i, j);
            if (!piece.has_value())
            {
                continue;
            }
            std::optional<Piece> topPiece = this->getPiece(i - 1, j);
            std::optional<Piece> bottomPiece = this->getPiece(i + 1, j);
            std::optional<Piece> leftPiece = this->getPiece(i, j - 1);
            std::optional<Piece> rightPiece = this->getPiece(i, j + 1);
            if (topPiece.has_value()
                && piece.value().getNorth() != topPiece.value().getSouth())
            {
                loss += 1;
            }
            if (bottomPiece.has_value()
                && piece.value().getSouth() != bottomPiece.value().getNorth())
            {
                loss += 1;
            }
            if (leftPiece.has_value()
                && piece.value().getWest() != leftPiece.value().getEast())
            {
                loss += 1;
            }
            if (rightPiece.has_value()
                && piece.value().getEast() != rightPiece.value().getWest())
            {
                loss += 1;
            }
        }
    }
    return loss / this->numEdges;
}

Board Board::copy() const
{
    return Board(*this);
}

// Generate a random float between 0 and 1
float normalizedRandom()
{
    return std::rand() / static_cast<float>(RAND_MAX);
}

bool Board::solve(size_t epochMax = 1'000'000, float initialTemperature = 1,
                  float decayRate = 0.9999, bool verbose = false)
{
    auto p = [&](float delta, float temperature) -> float {
        return std::exp(-delta / temperature);
    };

    Board optimalBoard = this->copy();
    float loss = this->loss();
    float optimalLoss = optimalBoard.loss();
    size_t epoch = 0;
    float temperature = initialTemperature;
    bool success = false;
    size_t epochPerPercent = epochMax / 100;

    for (epoch = 0; epoch < epochMax; epoch++)
    {
        this->randomSwap();
        float epochLoss = this->loss();
        float lossDelta = std::abs(epochLoss - loss);

        if (epochLoss < loss || normalizedRandom() < p(lossDelta, temperature))
        {
            loss = epochLoss;
            // Second optimisation
            // Because some time we fall in local minimum and the temperature
            // continue to decrease The resolver is stuck in a local minimum To
            // avoid this, we can freeze the temperature each time we fail to
            // find a better solution So when we are stuck in a local minimum,
            // the temperature is high enough to escape at some point
            temperature *= decayRate;
        }
        else
        {
            // First optimisation
            // Instead of copying the board and replace by the previous one
            // we can just reverse the last swap
            // With this optimisation, we can go from 4s to 1s
            this->reverseLastRandomSwap();
        }

        if (loss < optimalLoss)
        {
            optimalLoss = loss;
            optimalBoard = this->copy();
        }

        if (epoch % epochPerPercent == 0 && verbose)
        {
            std::cout << "[" << epoch << "] Optimal loss : " << optimalLoss
                      << std::endl;
        }

        if (optimalLoss == 0)
        {
            if (verbose)
            {
                std::cout << "[" << epoch << "] Optimal loss : " << optimalLoss
                          << std::endl;
            }
            success = true;
            break;
        }
    }

    this->board = optimalBoard.board;
    return success;
}