#include <string>
#include <vector>
#pragma once


namespace editdist {
    class EditMatrix {
        public:
            EditMatrix(const std::string& s1, const std::string& s2);
            void printMatrix();
            ~EditMatrix();
        private:
            void fillMatrix();
            std::vector<std::vector<int>> matrix;
            std::string str1;
            std::string str2;
    };
}