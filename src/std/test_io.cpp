#include <gtest/gtest.h>
#include <fstream>
#include <iostream>

TEST(testIO, caseFile) {
    {
        std::ofstream fout("/tmp/test.txt");
        fout << "做一个决定，并不难，难的是付诸行动，并且坚持到底";
        fout.flush();
        fout.close();
    }
    {
        std::ifstream fin("/tmp/test.txt");
        std::string   str;
        fin >> str;
        EXPECT_EQ(str, "做一个决定，并不难，难的是付诸行动，并且坚持到底");
    }
}

TEST(testIO, caseString) {
    std::stringstream ss;
    ss << "pi = " << 3.14;
    EXPECT_EQ(ss.str(), "pi = 3.14");
}
