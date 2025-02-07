#include <board.hpp>

Bitboard::Bitboard() : _value(0ULL) {}
Bitboard::Bitboard(uint64_t value) : _value(value) {}

bool Bitboard::isSet(Square square) const
{
    return (_value & (1ULL << square)) != 0;
};

void Bitboard::set(Square square)
{
    _value |= (1ULL << square);
}

void Bitboard::unset(Square square)
{
    _value &= (1ULL << square);
}

Board::Board() {};

void Board::setPlainBoard(char* board) {
    if (strlen(board) == 64) {
        for (int i = 0; i < 64; i++) {
            if (board[i] != ' ') {
                set((Square)i, FENtoPiece.at(board[i]));
            }
        }
    }
    else {
        std::cerr << "Invalid plain board!\n";
    }
}

char* Board::getPlainBoard() {
    char* board = new char[65];

    for (int i = 0; i < 64; i++) {
        board[i] = ' ';
    }
    board[64] = '\0';

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 64; j++) {
            if (_white_bitboards[i].isSet((Square)j)) {
                board[j] = PieceToFEN.at((Piece)(i + 1));
            }
        }
        for (int j = 0; j < 64; j++) {
            if (_black_bitboards[i].isSet((Square)j)) {
                board[j] = PieceToFEN.at((Piece)(i + 9));
            }
        }
    }

    return board;
}

void Board::loadFEN(char* fen)
{
    char *fen_copy = strdup(fen);
    char *argument = strtok(fen_copy, " ");

    size_t argument_index = 0;

    while (argument)
    {
        switch (argument_index)
        {
        case 0:
        {
            char *row = strtok(argument, "/");
            size_t square_index = 0;
            while (row)
            {
                while (*row)
                {
                    if (isdigit(*row))
                        square_index += (*row) - '0';
                    else
                    {
                        set((Square)square_index, FENtoPiece.at(*row));
                        square_index++;
                    }
                    row++;
                }
                square_index = ceil((float)square_index / 8) * 8;
                row = strtok(NULL, "/");
            }
            break;
        }

        default:
            break;
        }

        argument = strtok(NULL, " ");
        argument_index++;
    }

    free(fen_copy);
}

void Board::set(Square square, Piece piece)
{
    if (piece == EMPTY)
        return;

    if (piece / 8 == 0)
    {
        _white_bitboards[(piece - 1)].set(square);
        _white_bitboards[OCCUPIED].set(square);
    }
    else
    {
        _black_bitboards[(piece - 9)].set(square);
        _black_bitboards[OCCUPIED].set(square);
    }
    _occupied.set(square);
}

void Board::unset(Square square)
{
    for (int i = 0; i < 7; i++)
    {
        _white_bitboards[i].unset(square);
        _black_bitboards[i].unset(square);
    }
    _occupied.unset(square);
}