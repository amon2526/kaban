#include <board.hpp>

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

void Board::setPlainBoard(char *board)
{
    if (strlen(board) == 64)
    {
        for (int i = 0; i < 64; i++)
        {
            if (board[i] != ' ')
            {
                set((Square)i, FENtoPiece.at(board[i]));
            }
        }
    }
    else
    {
        UserIO::outputError(1, "Invalid plain board!");
    }
}

char *Board::getPlainBoard()
{
    char *board = new char[65];

    for (int i = 0; i < 64; i++)
    {
        board[i] = ' ';
    }
    board[64] = '\0';

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 64; j++)
        {
            if (_white_bitboards[i].isSet((Square)j))
            {
                board[j] = PieceToFEN.at((Piece)(i + 1));
            }
        }
        for (int j = 0; j < 64; j++)
        {
            if (_black_bitboards[i].isSet((Square)j))
            {
                board[j] = PieceToFEN.at((Piece)(i + 9));
            }
        }
    }

    return board;
}


void Board::loadFEN(std::string fen)
{
    std::string fen_copy = fen;
    std::istringstream iss(fen_copy);
    std::string argument;
    size_t argument_index = 0;
    while (iss >> argument) {
        switch (argument_index)
        {
        case 0:
        {
            std::string board;
            board.reserve(65);

            for (char c : argument)
            {
                if (c == '/')
                {
                    size_t new_position = ceil((float)(board.size() - 1) / 8) * 8;
                    board.resize(new_position, ' ');
                }
                else if (isdigit(c)) {
                    size_t new_position = board.size() + (c - '0');
                    board.resize(new_position, ' ');
                } 
                else {
                    board += c;
                }
            }

            setPlainBoard(board.data());
            break;
        }

        default:
            break;
        }
        argument_index++;
    }
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