#include "edit_dist_matrix.hpp"
#include <algorithm>
#include <iostream>

#define INSERT_OP 0
#define DEL_OP 1 
#define MISMATCH_OP 2  

namespace editdist {
    EditMatrix::EditMatrix(const std::string& s1, const std::string& s2) {
        this->str1 = s1;
        this->str2 = s2;
        this->str1.insert(0, " ");
        this->str2.insert(0, " ");
        int n = this->str1.size();
        int m = this->str2.size();
        // create matrix, save strings 
        this->matrix = std::vector<std::vector<int>>(n, std::vector<int>(m));
        for (int i = 0; i < n; i++) {
            this->matrix[0][i] = i;    // initialize first row
        }
        for (int j = 0; j < m; j++) {
            this->matrix[j][0] = j; // initialize first column
        }
    }

    void EditMatrix::printMatrix() {
        this->fillMatrix();
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

    int EditMatrix::getEditDist() {
        int n = this->matrix.size() - 1;
        int m = this->matrix[0].size() - 1;
        return this->matrix[n][m];
    }

    std::pair<std::string, std::string> EditMatrix::getAlignment() {
        std::string word1 = "";
        std::string word2 = "";
        int i = this->matrix.size() - 1;
        int j = this->matrix[0].size() - 1;
        std::vector<int> checks(3);

        while (i != 0 && j != 0) {
            checks[INSERT_OP] = this->matrix[i - 1][j];
            checks[DEL_OP] = this->matrix[i][j - 1];
            checks[MISMATCH_OP] = this->matrix[i - 1][j - 1];
            if (checks[MISMATCH_OP] == this->matrix[i][j] || 
                checks[MISMATCH_OP] + 1 == this->matrix[i][j]) {
                    word1 += this->str1[i];
                    word2 += this->str2[j];
                    i -= 1;
                    j -= 1;
            } else if (checks[INSERT_OP] + 1 == this->matrix[i][j]) {
                word1 += this->str1[i];
                word2 += '_';
                i -= 1;
            } else {
                word1 += '_';
                word2 += this->str2[j];
                j -= 1;
            }
        }
        std::reverse(word1.begin(), word1.end());
        std::reverse(word2.begin(), word2.end());

        return std::make_pair(word1, word2);
    }

    void EditMatrix::fillMatrix() {
        std::vector<int> checks(3);

        for (int i = 1; i < this->matrix.size(); i++) {
            for (int j = 1; j < this->matrix[i].size(); j++) {
                checks[INSERT_OP] = this->matrix[i - 1][j] + 1;
                checks[DEL_OP] = this->matrix[i][j - 1] + 1;
                if (this->str1[i] != this->str2[j]) {
                    checks[MISMATCH_OP] = this->matrix[i - 1][j - 1] + 1;
                } else {
                    checks[MISMATCH_OP] = this->matrix[i - 1][j - 1];
                }
                this->matrix[i][j] = *std::min_element(checks.begin(), checks.end());
            }
        }
    }

    EditMatrix::~EditMatrix() {
        //destructor
    }
}