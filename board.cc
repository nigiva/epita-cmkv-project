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