#include <gtest/gtest.h>
#include <iostream>
#include <boost/program_options.hpp>

TEST(testProgramOptions, case1) {
    boost::program_options::options_description desc("Allowed options");
    
    desc.add_options()
        ("help", "produce help message")
        ("compression,C", boost::program_options::value<int>(), "set compression level")
        ("optimization,O", boost::program_options::value<int>()->default_value(10), "optimization level")
        ("include-path,I", boost::program_options::value<std::vector<std::string>>(), "include file");
    
    boost::program_options::variables_map vm;
    const char* argv[] = {"testProgramOptions", "-C2", "--include-path=a", "-Ib", "-I", "c"};
    boost::program_options::store(boost::program_options::parse_command_line(sizeof(argv)/sizeof(char*), argv, desc), vm);
    
    EXPECT_EQ(vm["compression"].as<int>(), 2);
    EXPECT_EQ(vm["optimization"].as<int>(), 10);
    EXPECT_EQ(vm["include-path"].as<std::vector<std::string>>(), std::vector<std::string>({"a", "b", "c"}));
    
    desc.print(std::cout);
}

TEST(testProgramOptions, case2) {
    boost::program_options::options_description desc1("desc 1");
    boost::program_options::options_description desc2("desc 2");
    
    desc1.add_options()("desc1", "desc1 option");
    desc2.add_options()("desc2", "desc2 option");
    
    boost::program_options::options_description desc("desc");
    desc.add(desc1).add(desc2);
    
    desc.print(std::cout);
}
