#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

#include "piece.hh"

class Board {
    private:
        size_t size;
        std::vector<std::vector<Piece>> board;
        size_t num_pieces;
        size_t num_edges;
        std::vector<std::vector<size_t>> last_random_swap;

    public:
        Board(size_t size) {
            this->size = size;
            this->num_edges = 4 * size;
            this->num_pieces = size * size;
            this->board = std::vector<std::vector<Piece>>(size, std::vector<Piece>(size, nullptr));
            this->last_random_swap = std::vector<std::vector<size_t>>(2, std::vector<size_t>(2, 0));
        }

        std::vector<std::vector<size_t>>  get_movable_piece_coords_list() {
            std::vector<std::vector<size_t>> movable_piece_coords_list;
            for (size_t i = 0; i < this->size; i++) {
                for (size_t j = 0; j < this->size; j++) {
                    if (this->board[i][j]->is_movable()) {
                        movable_piece_coords_list.push_back({i, j});
                    }
                }
            }
            return movable_piece_coords_list;
        }

        std::vector<std::vector<size_t>> get_2_random_movable_piece_coords() {
            std::vector<std::vector<size_t>> movable_piece_coords_list = this->get_movable_piece_coords_list();
            std::vector<std::vector<size_t>> random_movable_piece_coords_list;
            std::random_shuffle(movable_piece_coords_list.begin(), movable_piece_coords_list.end());
            random_movable_piece_coords_list.push_back(movable_piece_coords_list[0]);
            random_movable_piece_coords_list.push_back(movable_piece_coords_list[1]);
            return random_movable_piece_coords_list;
        }

        void random_swap() {
            std::vector<std::vector<size_t>> random_movable_piece_coords_list = this->get_2_random_movable_piece_coords();
            this->swap(random_movable_piece_coords_list[0], random_movable_piece_coords_list[1]);
        }

        void reverse_last_random_swap() {
            if (this->last_random_swap[0][0] == 0 && this->last_random_swap[0][1] == 0 && this->last_random_swap[1][0] == 0 && this->last_random_swap[1][1] == 0) {
                return;
            }
            this->swap(this->last_random_swap[0], this->last_random_swap[1]);
            this->last_random_swap = std::vector<std::vector<size_t>>(2, std::vector<size_t>(2, 0));
        }

        void swap(std::vector<size_t> coords1, std::vector<size_t> coords2) {
            Piece piece1 = this->board[coords1[0]][coords1[1]];
            Piece piece2 = this->board[coords2[0]][coords2[1]];
            this->board[coords1[0]][coords1[1]] = piece2;
            this->board[coords2[0]][coords2[1]] = piece1;
            this->last_random_swap[0] = coords1;
            this->last_random_swap[1] = coords2;
        }

        Piece get_piece(size_t i, size_t j) {
            return this->board[i][j];
        }

        float loss() {
            float loss = 0;

            for (size_t i = 0; i < this->size; i++) {
                for (size_t j = 0; j < this->size; j++) {
                    Piece piece = get_piece(i, j);

                    if (piece == nullptr) {
                        continue;
                    }

                    Piece north_piece = get_piece(i - 1, j);
                    Piece south_piece = get_piece(i + 1, j);
                    Piece east_piece = get_piece(i, j + 1);
                    Piece west_piece = get_piece(i, j - 1);

                    if (north_piece != nullptr && piece.getNorth() != north_piece.getSouth()) {
                        loss += 1;
                    }
                    if (south_piece != nullptr && piece.getSouth() != south_piece.getNorth()) {
                        loss += 1;
                    }
                    if (east_piece != nullptr && piece.getEast() != east_piece.getWest()) {
                        loss += 1;
                    }
                    if (west_piece != nullptr && piece.getWest() != west_piece.getEast()) {
                        loss += 1;
                    }
                }
            }

            return loss / this->num_edges;
        }

        Board copy() {
            Board new_board = Board(this->size);
            for (size_t i = 0; i < this->size; i++) {
                for (size_t j = 0; j < this->size; j++) {
                    new_board.board[i][j] = this->board[i][j];
                }
            }
            return new_board;
        }

        std::ostream &operator<<(std::ostream &os) {
            os << get_board_separator(this->size);

            for (size_t i = 0; i < this->size; i++) {
                os << std::endl;
                for (size_t j = 0; j < this->size; j++) {
                    os << "| " << this->board[i][j] << " ";
                }
                os << "|" << std::endl;
                os << get_board_separator(this->size);
            }

            return os;
        }

        static std::string get_board_separator(size_t size) {
            std::string separator = "";
            for (size_t i = 0; i < size; i++) {
                separator += "+---";
            }
            separator += "+";
            return separator;
        }
}