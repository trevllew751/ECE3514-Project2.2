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
