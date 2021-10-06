//
//  FileAllocManager.hpp
//  
//  C++ implementation of the Indexed File Allocation Method
//  Created by Sook Shin Ha on 9/26/21.
//

#ifndef FileAllocManager_hpp
#define FileAllocManager_hpp

#include <memory>
#include <ctime>
#include <math.h>
#include <iostream>
#include <vector>
#include "Node.hpp"
#include "LinkedList.hpp"

const int MAX_FILES = 64;      // 64 maximum files
const int MAX_BLOCKS = 64;     // 64 maximum blocks
const int TOTAL_SIZE_KiB = 64; // 64 maximum KiB
const int BLOCK_SIZE_KiB = 1;  // 1 KiB is a unit of information equal to 1024 bytes.

// Block struct
struct Block {
    bool occupied; // Tells if this block is belong to any file or not
    int *arr;      // If this block is an index block (not a storage block),
    // arr stores the indices of all storage blocks belonging to a file
    // arr = NULL ==> means the block is used for storage
    // arr != NULL ==> means the block is used as index block
    int arrSize;
};

// File struct
struct File {
    std::string name; // name of the file
    int size;    // size of the file in KiB (1 kibibyes = 1024B)
    Block *indexBlock; // pointer to the index block, each file has an index block
};

class FileAllocManager {
public:
    /** Seed the random number generator
        and set default values
    */
    FileAllocManager();

    /** Clear all files from the directory and
        deallocate the resources belong to the files
    */
    ~FileAllocManager();

    /** Clear all files from the directory and
        deallocate the resources belong to the files
    */
    void clear();

    /** Add a new file to the directory and allocate the required number of blocks to the file if
        the disk has enough unoccupied blocks.
        @param filename - a filename to add to the directory
        @param filesize - the size of the file in KiB
        @return indices of the blocks allocated to the file, starting with the index block, empty vector if unable to add the file
    */
    std::vector<unsigned int> addFile(std::string filename, int filesize);

    /** Delete a file from the directory and deallocate all the blocks belong to this file
        @param filename - a file of filename to delete from the directory
        @return whether the file could be deleted or not
    */
    bool deleteFile(std::string filename);

    /** Read file name and the index to storage block to seek and print out which block number that corresponds to on the disk
        @param filename - a filename to seek on disk
        @param blocknumber - a block index of the file to seek its position on disk
        @return index of the storage block on the disk corresponding to block number for the given file, -1 if invalid input
    */
    int seekFile(std::string filename, int blocknumber) const;

    /** List all the file names in the directory
        @return list of filenames in the directory, in reverse order of when they were added
    */
    std::vector<std::string> listFiles() const;

    /** Retruns the list of all occupied blocks on disk
        @return indices of allocated blocks, in ascending order
    */
    std::vector<unsigned int> printDisk() const;

    //the below are mostly to facilitate unit tests
    /** Return the total number of occupied blocks on disk
        @return occupiedBlocks - total number of occupied blocks on dis
    */
    unsigned int numOccupiedBlocks() const { return occupiedBlocks; };

    /** get method to access to the directory
        @return - the directory of fiels
    */
    const LinkedList<File> &getDirectory() const { return directory; }


private:
    // The disk divided into MAX_BLOCKS blocks
    Block disk[MAX_BLOCKS];

    // The directory of files
    LinkedList<File> directory;

    // Total numbef of occupied blocks in the disk
    int occupiedBlocks;

    /** Find the file in the directory using file name
        @param filename - the name of the file to find in the directory
        @return the position of the file in the directory list, -1 if the file could not be found
    */
    int findFile(std::string filename) const;

    /** Search will start at `start` position and go ahead till the last position. if all of these blocks are occupied, then search will continue from the first position to `start` - 1 position in the linked list
        @param start - the start position to search for the first unoccupied block in the disk,
        @return the position of the first unoccupied block in the disk
    */
    int findFirstAvailBlock(int start) const;

};

#endif /* FileAllocManager_hpp */
