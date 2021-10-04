#include "catch.hpp"
#include "FileAllocManager.hpp"

TEST_CASE("Test construction", "[FileAllocManager]")
{
    //INFO("Hint: default constructor must work)");
    FileAllocManager m;
    REQUIRE(m.numOccupiedBlocks() == 0);

    m.addFile("file1", 2);
    REQUIRE(m.numOccupiedBlocks() == 3);
}
