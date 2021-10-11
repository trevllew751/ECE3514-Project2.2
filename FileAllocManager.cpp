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
    for (int i = 0; i < MAX_BLOCKS; i++) {
        disk[i].occupied = false;
        delete[] disk[i].arr;
        disk[i].arr = nullptr;
        disk[i].arrSize = 0;
    }
    occupiedBlocks = 0;
    directory.clear();
}

std::vector<unsigned int> FileAllocManager::addFile(std::string filename, int filesize) {
    // Check invalid file size, if there are blocks, if the file exists already

    int blocksNeeded = (int) ceil((double) filesize / (double) BLOCK_SIZE_KiB);

    if (filesize < 0 ||
        filesize > TOTAL_SIZE_KiB ||
        (MAX_BLOCKS - numOccupiedBlocks()) < blocksNeeded + 1 ||
        findFile(filename) != -1 ||
        directory.getLength() >= MAX_FILES ||
        filename.empty())
    {
        return std::vector<unsigned int>();
    }
    std::vector<unsigned int> result;

    // Create index block for file
    int indexBlockLocation = findFirstAvailBlock(rand() % MAX_BLOCKS);   // Find first open location
    disk[indexBlockLocation].occupied = true;
    disk[indexBlockLocation].arrSize = blocksNeeded;
    disk[indexBlockLocation].arr = new int[blocksNeeded];
    result.push_back(indexBlockLocation);
    occupiedBlocks++;

    for (int i = 0; i < blocksNeeded; i++) {
        int location = findFirstAvailBlock(rand() % MAX_BLOCKS);
        disk[location].occupied = true;
        occupiedBlocks++;
        disk[indexBlockLocation].arr[i] = location;
        result.push_back(location);
    }
    File f{filename, filesize, &disk[indexBlockLocation]};
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
    delete[] index->arr;
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
    if (blocknumber >= f.size || blocknumber < 0) {
        return -1;
    }
    return f.indexBlock->arr[blocknumber];
}

std::vector<std::string> FileAllocManager::listFiles() const {
//    std::vector<File> files;
    std::vector<std::string> result;
    for (int i = 1; i < directory.getLength() + 1; i++) {
        result.push_back(directory.getEntry(i).name);
    }
//    for (auto it = files.rbegin(); it != files.rend(); ++it) {
//        result.push_back((*it).name);
//    }
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
