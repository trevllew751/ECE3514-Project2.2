#include "FileAllocManager.hpp"
#include <fstream>
#include <iostream>
#include <string>

int readFile(FileAllocManager &m, std::string filename);

int readInput(FileAllocManager &m);

int printCommands(FileAllocManager &m, const std::string &line);

std::vector<std::string> splitString(const std::string &str);

int main(int argc, char *argv[]) {
    FileAllocManager m;
    if (argc == 3) {
        return readFile(m, argv[2]);
    } else if (argc == 1) {
        return readInput(m);
    } else {
        return EXIT_FAILURE;
    }
}

int readFile(FileAllocManager &m, std::string filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::cout << ">>> " << line << std::endl;
            printCommands(m, line);
        }
    } else {
        std::cout << "Error opening file." << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int readInput(FileAllocManager &m) {
    std::string line;
    while (true) {
        std::cout << ">>> ";
        std::getline(std::cin, line);
        if (line == "exit") {
            std::cout << "Bye!" << std::endl;
            break;
        }
        printCommands(m, line);
    }
    return EXIT_SUCCESS;
}

int printCommands(FileAllocManager &m, const std::string &line) {
    std::vector<std::string> strings = splitString(line);
    std::string command = strings.at(0);
    if (command == "add") {
        int size = std::stoi(strings.at(2));
        std::vector<unsigned int> indices = m.addFile(strings.at(1), size);
        if (indices.empty()) {
            if (MAX_BLOCKS - m.numOccupiedBlocks() < size + 1) {
                std::cout << "Not enough disk space." << std::endl;
            } else {
                std::cout << "File already in directory." << std::endl;
            }
        } else {
            std::cout << "Index block at position " << indices.at(0) << "." << std::endl;
            for (int i = 1; i < indices.size(); i++) {
                std::cout << "Block " << (i - 1) << " is at position " << indices.at(i) << "." << std::endl;
            }
        }
    } else if (command == "del") {
        std::string fName = strings.at(1);
        if (m.deleteFile(fName)) {
            std::cout << fName << " is deleted successfully!" << std::endl;
        } else {
            std::cout << fName << " does not exist on the disk." << std::endl;
        }
    } else if (command == "list") {
        std::vector<std::string> files = m.listFiles();
        if (files.empty()) {
            std::cout << "Empty Directory." << std::endl;
        } else {
            for (std::string &f: files) {
                std::cout << f << std::endl;
            }
        }
    } else if (command == "seek") {
        std::string fName = strings.at(1);
        int blockNum = std::stoi(strings.at(2));
        int location = m.seekFile(fName, blockNum);
        if (location != -1) {
            std::cout << fName << ": Block number " << blockNum << " on disk is " << location << "."
                      << std::endl;
        } else {
            std::cout << fName << " does not have block " << blockNum << std::endl;
        }
    } else if (command == "disk") {
        std::vector<unsigned int> indices = m.printDisk();
        if (m.numOccupiedBlocks() == 0) {
            std::cout << "Out of 64 blocks, none are occupied.";
        } else {
            std::cout << "Out of 64 blocks, the following blocks are occupied: " << std::endl;
            for (unsigned int i : indices) {
                std::cout << i << " ";
            }
        }
        std::cout << std::endl;
    } else {
        std::cout << "Invalid command!" << std::endl;
    }
    std::cout << std::endl;
    return EXIT_SUCCESS;
}

std::vector<std::string> splitString(const std::string &str) {
    std::vector<std::string> result;
    std::string temp;
    for (char c: str) {
        if (isalnum(c)) {
            temp += c;
        } else {
            result.push_back(temp);
            temp.clear();
        }
    }
    if (!temp.empty()) {
        result.push_back(temp);
    }
    return result;
}