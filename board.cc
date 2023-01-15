#include "board.hh"

#include <cmath>
#include <iostream>
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