#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <array>

class board {
    struct piece_t {
        int8_t color; // White -- 1, Black -- -1, No piece -- 0
        int8_t type; // 0 -- Pawn, 1 -- Bishop, 2 -- Knight, 3 -- Rook, 4 -- Queen, 5 -- King
        int8_t index; // Notation as in README.md
    };

    // FOR MAP
    friend bool operator < (const piece_t& A, const piece_t& B)
    {
        if (A.color == B.color) {
            if (A.type == B.type) return (A.index < B.index);
            return (A.type < B.type);
        } 
        return (A.color < B.color);
    }
    friend bool operator == (const piece_t& A, const piece_t& B) {
        return (A.color == B.color && A.type == B.type && A.index == B.index);
    }

    // Grid[i][j] = square at column j and row i.
    // Label : <char[j]>i like Grid[8][5] = E8. So on.
    std::array<std::array<piece_t, 9>, 9> grid;
    struct coords {
        int8_t on;
        int8_t row; // The i of Grid[i][j]
        int8_t col; // The j of Grid[i][j]
    };
    std::map<piece_t, coords> pieces;

public:
    board() {
        for (int8_t i = 0; i < 9; i++)
            for (int8_t j = 0; j < 9; j++)
                grid[i][j] = {0, 0, 0};

        for (int8_t i = 1; i < 9; i++) {
            // PAWNS
            grid[2][i] = {1, 0, i};
            pieces[{1, 0, i}] = {1, 2, i};
            grid[7][i] = {-1, 0, i};
            pieces[{-1, 0, i}] = {1, 7, i};

            // PROMO-QUEENS
            pieces[{1, 4, i}] = {0, 0, 0};
            pieces[{-1, 4, i}] = {0, 0, 0};
        }
        // KINGS
        grid[1][5] = {1, 5, 0};
        grid[8][5] = {-1, 5, 0};
        pieces[{1, 5, 0}] = {1, 1, 5};
        pieces[{-1, 5, 0}] = {1, 8, 5};

        // QUEENS
        grid[1][4] = {1, 4, 0};
        grid[8][4] = {-1, 4, 0};
        pieces[{1, 4, 0}] = {1, 1, 4};
        pieces[{-1, 4, 0}] = {1, 8, 4};

        // ROOKS
        grid[1][1] = {1, 3, 1};
        grid[1][8] = {1, 3, 2};
        pieces[{1, 3, 1}] = {1, 1, 1};
        pieces[{1, 3, 2}] = {1, 1, 8};
        grid[8][1] = {-1, 3, 1};
        grid[8][8] = {-1, 3, 2};
        pieces[{-1, 3, 1}] = {1, 8, 1};
        pieces[{-1, 3, 2}] = {1, 8, 8};

        // BISHOPS
        grid[1][3] = {1, 1, 1};
        grid[1][6] = {1, 1, 2};
        pieces[{1, 1, 1}] = {1, 1, 3};
        pieces[{1, 1, 2}] = {1, 1, 6};
        grid[8][3] = {-1, 1, 1};
        grid[8][6] = {-1, 1, 2};
        pieces[{-1, 1, 1}] = {1, 8, 3};
        pieces[{-1, 1, 2}] = {1, 8, 6};

        // KNIGHTS
        grid[1][2] = {1, 2, 1};
        grid[1][7] = {1, 2, 2};
        pieces[{1, 2, 1}] = {1, 1, 2};
        pieces[{1, 2, 2}] = {1, 1, 7};
        grid[8][2] = {-1, 2, 1};
        grid[8][7] = {-1, 2, 2};
        pieces[{-1, 2, 1}] = {1, 8, 2};
        pieces[{-1, 2, 2}] = {1, 8, 7};
    }
    ~board() {}

    void printBoard() {
        printf("   ");
        for (int8_t j = 1; j < 9; j++) {
            printf("    %c   ", j+64);
        }
        printf("    \n   ");
        for (int8_t i = 8; i > 0; i--) {
            for (int8_t j = 1; j < 9; j++) {
                printf("+%s", "-------");
            }
            printf("+   \n   ");
            for (int8_t j = 1; j < 9; j++) {
                if (grid[i][j].color == 1)
                    printf("|%s", " WHITE ");
                else if (grid[i][j].color == -1)
                    printf("|%s", " BLACK ");
                else
                    printf("|%s", "       ");
            }
            printf("|  \n %d ", i);
            for (int8_t j = 1; j < 9; j++) {
                if ((i + j) % 2 == 0) printf("|%s", " @ @ @ ");
                else printf("|%s", "       ");
            }
            printf("| %d \n   ", i);
            for (int8_t j = 1; j < 9; j++) {
                if (grid[i][j].color == 0)
                    printf("|%s", "       ");
                else if (grid[i][j].type == 0)
                    printf("| %s %d ", "PWN", grid[i][j].index);
                else if (grid[i][j].type == 1)
                    printf("| %s %d ", "BSP", grid[i][j].index);
                else if (grid[i][j].type == 2)
                    printf("| %s %d ", "KNT", grid[i][j].index);
                else if (grid[i][j].type == 3)
                    printf("| %s %d ", "ROK", grid[i][j].index);
                else if (grid[i][j].type == 4)
                    printf("| %s %d ", "QWN", grid[i][j].index);
                else
                    printf("| KING  ");
            }
            printf("|   \n   ");
        }
        for (int8_t j = 1; j < 9; j++) {
            printf("+%s", "-------");
        }
        printf("+  \n  ");
        for (int8_t j = 1; j < 9; j++) {
            printf("    %c   ", j+64);
        }
        printf("    \n");
    }
    void getMove(std::string s);
};
