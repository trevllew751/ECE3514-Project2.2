#include "FileAllocManager.hpp"

FileAllocManager::FileAllocManager() {
    srand(time(nullptr));
    occupiedBlocks = 0;
    for (Block &b : disk) {
        b.occupied = false;
        b.arr = nullptr;
        b.arrSize = 0;
    }
}

FileAllocManager::~FileAllocManager() {
    clear();
}

void FileAllocManager::clear() {
    for (Block &b : disk) {
        b.occupied = false;
        delete[] b.arr;
        b.arr = nullptr;
        b.arrSize = 0;
    }
    directory.clear();
}

std::vector<unsigned int> FileAllocManager::addFile(std::string filename, int filesize) {
    // Check invalid file size, if there are blocks, if the file exists already
    if (filesize < 1 || (MAX_BLOCKS - numOccupiedBlocks()) < filesize + 1 || findFile(filename) != -1) {
        return std::vector<unsigned int>();
    }
    std::vector<unsigned int> result;

    // Create index block for the file
    Block *index = new Block{true, new int[filesize], filesize};
    int start = rand() % MAX_BLOCKS;                             // Random search start
    int indexBlockLocation = findFirstAvailBlock(start);         // Find first open location
    disk[indexBlockLocation] = *index;                            // Add index block to the disk
    result.push_back(indexBlockLocation);
    occupiedBlocks++;

    int arrIndex = 0;
    for (int i = 0; i < filesize; i++) {
        int start = rand() % MAX_BLOCKS;
        int location = findFirstAvailBlock(start);
        Block b{true, nullptr, 0};
        disk[location] = b;
        occupiedBlocks++;
        index->arr[arrIndex] = location;
        result.push_back(location);
        arrIndex++;
    }
    File f{filename, filesize, index};
    directory.insert(directory.getLength() + 1, f);
    return result;
}

bool FileAllocManager::deleteFile(std::string filename) {
    int location = findFile(filename);
    if (location == -1) {
        return false;
    }
    Block *index = directory.getEntry(location).indexBlock;
    for (int i = 0; i < index->arrSize; i++) {
        disk[index->arr[i]].occupied = false;
        occupiedBlocks--;
    }
//    delete[] index->arr;
    index->arr = nullptr;
    index->occupied = false;
    index->arrSize = 0;
    occupiedBlocks--;
    directory.remove(location);
    return true;
}

int FileAllocManager::seekFile(std::string filename, int blocknumber) const {
    int location = findFile(filename);
    if (location == -1) {
        return -1;
    }
    File f = directory.getEntry(location);
    if (blocknumber >= f.size) {
        return -1;
    }
    return f.indexBlock->arr[blocknumber];
}

std::vector<std::string> FileAllocManager::listFiles() const {
    std::vector<File> files;
    std::vector<std::string> result;
    for (int i = 1; i < directory.getLength() + 1; i++) {
        files.push_back(directory.getEntry(i));
    }
    for (auto it = files.rbegin(); it != files.rend(); ++it) {
        result.push_back((*it).name);
    }
    return result;
}

std::vector<unsigned int> FileAllocManager::printDisk() const {
    std::vector<unsigned int> result;
    for (int i = 0; i < MAX_BLOCKS; i++) {
        if (disk[i].occupied) {
            result.push_back(i);
        }
    }
    return result;
}

int FileAllocManager::findFile(std::string filename) const {
    for (int i = 1; i < directory.getLength() + 1; i++) {
        if (directory.getEntry(i).name == filename) {
            return i;
        }
    }
    return -1;
}

int FileAllocManager::findFirstAvailBlock(int start) const {
    for (int i = start; i < MAX_BLOCKS; i++) {
        if (!disk[i].occupied) {
            return i;
        }
    }
    for (int i = 0; i < start; i++) {
        if (!disk[i].occupied) {
            return i;
        }
    }
    return -1;
}
