#include <string>
#include <utility>
#include <vector>
#pragma once


namespace editdist {
    // Calculates edit distance using a dynamic programming style matrix
    // Example:
    //      std::string mystr1 = "evolution";
    //      std::string mystr2 = "revolution";
    //      editdist::EditMatrix my_matrix = editdist::EditMatrix(mystr1, mystr2);
    //      std::cout << my_matrix.getEditDist();
    class EditMatrix {
        public:
            EditMatrix(const std::string& s1, const std::string& s2);
            void printMatrix();
            int getEditDist();
            std::pair<std::string, std::string> getAlignment();
            ~EditMatrix();
        private:
            void fillMatrix();
            int getMinimumMove(int row, int col);
            std::vector<std::vector<int> > matrix;
            std::string str1;
            std::string str2;
    };
}