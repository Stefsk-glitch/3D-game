#include <fstream>
#include <iostream>
#include <string>
#include <exception>

#include "fileIO.h"

int FileIO::readScoreFromFile(std::string& score) {
    try {
        std::ifstream file("score.txt");
        if (!file.is_open()) {
            throw std::ios_base::failure("File doesn't exist. You never played before");
        }

        std::getline(file, score);
        file.close();
        return 0; 
    }
    catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return -1;
    }
}

int FileIO::writeScoreToFile(int score) {
    try {
        std::ofstream file("score.txt");
        if (!file.is_open()) {
            throw std::ios_base::failure("Failed to open the file.");
        }
        file << "Your final score: " << score << std::endl;

        if (file.fail()) {
            throw std::ios_base::failure("Failed to write to the file.");
        }

        file.close();

        if (file.fail()) {
            throw std::ios_base::failure("Failed to close the file.");
        }

        std::cout << "File written successfully." << std::endl;
        return 0; 
    }
    catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return -1;
    }
}