#include "edit_dist_matrix.hpp"
#include <iostream>
#include <utility>
#include <string>

int main() {
    std::string s1;
    std::string s2;
    std::pair<std::string, std::string> aligned;

    std::cout << "please enter the first word: ";
    std::getline(std::cin, s1);
    std::cout << std::endl << "please enter the second word: ";
    std::getline(std::cin, s2);
    std::cout << "words: " << s1 << " " << s2 << std::endl;
    editdist::EditMatrix edit_dist_matrix = editdist::EditMatrix(s1, s2);

    std::cout << "Matrix: " << std::endl;
    edit_dist_matrix.printMatrix();
    std::cout << "distance: " << edit_dist_matrix.getEditDist() << std::endl;
    aligned = edit_dist_matrix.getAlignment();
    std::cout << "alignment: " << std::endl;
    std::cout << aligned.first << std::endl << aligned.second << std::endl;

    return 0;
}