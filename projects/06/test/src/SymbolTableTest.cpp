#include "../../src/SymbolTable.cpp"
#include "gtest/gtest.h"

TEST(SymbolTableTest, entry)
{
    HackAssembler::SymbolTable table = HackAssembler::SymbolTable();

    ASSERT_FALSE(table.contains("entry"));
    ASSERT_NO_THROW(table.addEntry("entry", 42069));
    ASSERT_TRUE(table.contains("entry"));
    ASSERT_EQ(table.getAddress("entry"), 42069);
}
