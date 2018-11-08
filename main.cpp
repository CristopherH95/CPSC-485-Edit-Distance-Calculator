#include "edit_dist_matrix.hpp"
#include <iostream>
#include <string>

int main() {
    std::string s1;
    std::string s2;
    std::cout << "please enter the first word: ";
    std::getline(std::cin, s1);
    std::cout << std::endl << "please enter the second word: ";
    std::getline(std::cin, s2);
    editdist::EditMatrix edit_dist_matrix = editdist::EditMatrix(s1, s2);
    std::cout << "words: " << s1 << " " << s2 << std::endl;
    edit_dist_matrix.printMatrix();

    return 0;
}