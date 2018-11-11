#include "edit_dist_matrix.hpp"
#include <algorithm>
#include <climits>
#include <iostream>


namespace editdist {
    // constant symbols to represent operations
    const int INSERT_OP = 0;
    const int DEL_OP = 1;
    const int MISMATCH_OP = 2;

    // constructor for EditMatrix
    // requires two strings from which the matrix should be generated
    EditMatrix::EditMatrix(const std::string& s1, const std::string& s2) {
        this->str1 = s1;
        this->str2 = s2;
        this->str1.insert(0, " ");
        this->str2.insert(0, " ");
        int n = this->str1.size();
        int m = this->str2.size();
        // create matrix, save strings 
        this->matrix = std::vector<std::vector<int> >(n, std::vector<int>(m));
        std::cerr << this->matrix.size() << " " << this->matrix[0].size() << std::endl;
        for (int i = 0; i < n; i++) {
            std::cerr << "init first row" << std::endl;
            this->matrix[0][i] = i;    // initialize first row
            std::cerr << this->matrix[0][i] << std::endl;
        }
        for (int j = 0; j < m; j++) {
            std::cerr << "init first col" << std::endl;
            this->matrix[j][0] = j; // initialize first column
            std::cerr << this->matrix[j][0] << std::endl;
        }
        this->fillMatrix();     // fill the matrix
    }

    // prints out the matrix in a formatted manner
    void EditMatrix::printMatrix() {
        std::cout << "  | ";
        for (int i = 0; i < this->str2.size(); i++) {
            std::cout << this->str2[i] << " | ";
        }
        std::cout << std::endl;
        for (int n = 0; n < this->matrix.size(); n++) {
            std::cout << this->str1[n] << " | ";
            for (int m = 0; m < this->matrix[n].size(); m++) {
                std::cout << this->matrix[n][m] << " | ";
            }
            std::cout << std::endl;
        }
    }

    // returns the minimum edit distance value
    int EditMatrix::getEditDist() {
        int n = this->matrix.size() - 1;
        int m = this->matrix[0].size() - 1;
        return this->matrix[n][m];
    }

    // returns a pair of strings which are aligned versions of str1 and str2
    // starts at final position in the matrix and works its way to the start at 0, 0
    // at each stage it takes the minimum move and constructs the aligned string
    // appropriately
    std::pair<std::string, std::string> EditMatrix::getAlignment() {
        std::string word1 = "";
        std::string word2 = "";
        int i = this->matrix.size() - 1;
        int j = this->matrix[0].size() - 1;
        int min_move;

        std::cerr << "alignment" << std::endl;

        while (i != 0 || j != 0) {
            min_move = this->getMinimumMove(i, j);
            
            if (min_move == MISMATCH_OP) {
                    // if match/mismatch move diagonal and add the letters
                    word1 += this->str1[i];
                    word2 += this->str2[j];
                    i -= 1;
                    j -= 1;
            } else if (min_move == INSERT_OP) {
                // if insert move up and add a letter from str1 with a blank for str2
                word1 += this->str1[i];
                word2 += '_';
                i -= 1;
            } else {
                // if delete move left and add a blank for str1 and a letter from str2
                word1 += '_';
                word2 += this->str2[j];
                j -= 1;
            }
        }
        // reverse strings (since they were constructed backwards)
        std::reverse(word1.begin(), word1.end());
        std::reverse(word2.begin(), word2.end());

        return std::make_pair(word1, word2);
    }

    // fills the matrix with the minimum moves for each possible configuration
    // of the two strings
    void EditMatrix::fillMatrix() {
        std::vector<int> checks(3);

        std::cerr << "fill matrix" << std::endl;

        for (int i = 1; i < this->matrix.size(); i++) {
            for (int j = 1; j < this->matrix[i].size(); j++) {
                // insert/delete adds one edit distance
                checks[INSERT_OP] = this->matrix[i - 1][j] + 1;
                checks[DEL_OP] = this->matrix[i][j - 1] + 1;
                // mismatch adds one edit distance, match gets same value
                if (this->str1[i] != this->str2[j]) {
                    checks[MISMATCH_OP] = this->matrix[i - 1][j - 1] + 1;
                } else {
                    checks[MISMATCH_OP] = this->matrix[i - 1][j - 1];
                }
                // choose the minimum of the options
                this->matrix[i][j] = *std::min_element(checks.begin(), checks.end());
            }
        }
    }

    // returns the next minimum move in the matrix from the given row and column
    int EditMatrix::getMinimumMove(int row, int col) {
        int checks[3];
        int move_idx = MISMATCH_OP; // assume match/mismatch

        if (row > 0) {
            // if can move up get insert/match/mismatch scores
            checks[INSERT_OP] = this->matrix[row - 1][col];
            checks[MISMATCH_OP] = this->matrix[row - 1][col - 1];
        } else {
            // if cannot move up ensure these options will not be chosen
            checks[INSERT_OP] = INT_MAX;
            checks[MISMATCH_OP] = INT_MAX;
        }
        if (col > 0) {
            // if can move left get delete score
            checks[DEL_OP] = this->matrix[row][col - 1];
        } else {
            // if cannot move left ensure delete will not be chosen
            checks[DEL_OP] = INT_MAX;
        }

        // check operations other than match/mismatch and see which is less
        for (int i = DEL_OP; i >= INSERT_OP; i--) {
            if (checks[i] < checks[move_idx]) {
                move_idx = i;
            }
        }

        return move_idx;
    }

    EditMatrix::~EditMatrix() {
        //destructor
    }
}