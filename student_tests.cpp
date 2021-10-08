#include "catch.hpp"
#include "FileAllocManager.hpp"

TEST_CASE( "Test construction", "[FileAllocManager]" )
{
  //INFO("Hint: default constructor must work)");
    FileAllocManager m;
    REQUIRE(m.numOccupiedBlocks() == 0);
    
    m.addFile("file1", 2);
    REQUIRE(m.numOccupiedBlocks() == 3);
}

TEST_CASE("Test add file", "[FileAllocManager]") {
    FileAllocManager m;
    std::vector<unsigned int> empty;
    m.addFile("file1", 1);
    m.addFile("file2", 2);
    m.addFile("file3", 3);
    REQUIRE(m.numOccupiedBlocks() == 9);
    REQUIRE(m.addFile("file64", 100) == empty);
    REQUIRE(m.numOccupiedBlocks() == 9);
    REQUIRE(m.addFile("file0", 0) == empty);
    REQUIRE(m.addFile("file1", 2) == empty);
    REQUIRE(m.numOccupiedBlocks() == 9);
}


TEST_CASE("Test delete file", "[FileAllocManager]") {
    FileAllocManager m;
    std::vector<unsigned int> vect = m.addFile("file1", 1);
    m.addFile("file2", 2);
    m.addFile("file3", 3);
    REQUIRE(m.numOccupiedBlocks() == 9);
    REQUIRE(m.deleteFile("file1"));
    REQUIRE(m.numOccupiedBlocks() == 7);
    REQUIRE(m.deleteFile("file3"));
    REQUIRE(m.numOccupiedBlocks() == 3);
    REQUIRE_FALSE(m.deleteFile("file3"));
    REQUIRE(m.deleteFile("file2"));
    REQUIRE(m.numOccupiedBlocks() == 0);
}

TEST_CASE("Test seek file", "[FileAllocManager]") {
    FileAllocManager m;
    std::vector<unsigned int> vect = m.addFile("file3", 3);
    unsigned int first = vect.at(1);
    unsigned int second = vect.at(2);
    unsigned int third = vect.at(3);
    REQUIRE(m.seekFile("file3", 0) == first);
    REQUIRE(m.seekFile("file3", 1) == second);
    REQUIRE(m.seekFile("file3", 2) == third);
    REQUIRE(m.seekFile("file4", 10) == -1);
    REQUIRE(m.seekFile("file3", 10) == -1);
}

TEST_CASE("Test list files", "[FileAllocManager]") {
    FileAllocManager m;
    std::vector<std::string> answer{"file3", "file2", "file1"};
    m.addFile("file1", 1);
    m.addFile("file2", 2);
    m.addFile("file3", 3);
    REQUIRE(m.listFiles() == answer);
}

TEST_CASE("Test print disk", "[FileAllocManager]") {
    FileAllocManager m;
    m.addFile("file1", 1);
    m.addFile("file2", 2);
    m.addFile("file3", 3);
    REQUIRE_FALSE(m.printDisk().empty());
}