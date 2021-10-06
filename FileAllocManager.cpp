#include "FileAllocManager.hpp"

FileAllocManager::FileAllocManager() {

}

FileAllocManager::~FileAllocManager() {

}

void FileAllocManager::clear() {

}

std::vector<unsigned int> FileAllocManager::addFile(std::string filename, int filesize) {
    return std::vector<unsigned int>();
}

bool FileAllocManager::deleteFile(std::string filename) {
    return false;
}

int FileAllocManager::seekFile(std::string filename, int blocknumber) const {
    return 0;
}

std::vector<std::string> FileAllocManager::listFiles() const {
    return std::vector<std::string>();
}

std::vector<unsigned int> FileAllocManager::printDisk() const {
    return std::vector<unsigned int>();
}

int FileAllocManager::findFile(std::string filename) const {
    return 0;
}

int FileAllocManager::findFirstAvailBlock(int start) const {
    return 0;
}
