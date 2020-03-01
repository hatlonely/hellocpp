#include <gtest/gtest.h>
#include <boost/property_tree/info_parser.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <iostream>
#include <sstream>

TEST(testPropertyTree, casePTree) {
    boost::property_tree::ptree tree;
    tree.put("menu.foo", true);
    tree.put("menu.bar", "true");
    tree.put("menu.value", 102.3E+06);

    boost::property_tree::ptree sub1, sub2;
    sub1.put("value", "New");
    sub1.put("onclick", "CreateNewDoc()");
    sub2.put("value", "Open");
    sub2.put("onclick", "OpenDoc()");

    boost::property_tree::ptree child;
    child.push_back(std::make_pair("", sub1));
    child.push_back(std::make_pair("", sub2));

    tree.put_child("menu.popup", child);

    std::stringstream ss;
    boost::property_tree::write_json(ss, tree);
    std::cout << ss.str() << std::endl;
}

TEST(testPropertyTree, caseJson) {
    boost::property_tree::ptree tree;

    std::stringstream ss;
    ss << "{" << std::endl;
    ss << "   \"menu\":" << std::endl;
    ss << "   {" << std::endl;
    ss << "      \"foo\": true," << std::endl;
    ss << "      \"bar\": \"true\"," << std::endl;
    ss << "      \"value\": 102.3E+06," << std::endl;
    ss << "      \"popup\":" << std::endl;
    ss << "      [" << std::endl;
    ss << "         {\"value\": \"New\", \"onclick\": \"CreateNewDoc()\"}," << std::endl;
    ss << "         {\"value\": \"Open\", \"onclick\": \"OpenDoc()\"}" << std::endl;
    ss << "      ]" << std::endl;
    ss << "   }" << std::endl;
    ss << "}" << std::endl;
    boost::property_tree::read_json(ss, tree);
    EXPECT_TRUE(tree.get<bool>("menu.foo"));
    EXPECT_EQ(tree.get<std::string>("menu.foo"), "true");
}

TEST(testPropertyTree, caseInfo) {
    boost::property_tree::ptree tree;

    std::stringstream ss;
    ss << "key1 value1" << std::endl;
    ss << "key2" << std::endl;
    ss << "{" << std::endl;
    ss << "    key3 value3" << std::endl;
    ss << "    {" << std::endl;
    ss << "        key4 \"value4 with spaces\"" << std::endl;
    ss << "    }" << std::endl;
    ss << "    key5 value5" << std::endl;
    ss << "}" << std::endl;

    boost::property_tree::read_info(ss, tree);
    EXPECT_EQ(tree.get<std::string>("key1"), "value1");
    EXPECT_EQ(tree.get<std::string>("key2.key3"), "value3");
}

TEST(testPropertyTree, caseXML) {
    boost::property_tree::ptree tree;

    std::stringstream ss;

    ss << "<debug>" << std::endl;
    ss << "    <filename>debug.log</filename>" << std::endl;
    ss << "    <modules>" << std::endl;
    ss << "        <module>Finance</module>" << std::endl;
    ss << "        <module>Admin</module>" << std::endl;
    ss << "        <module>HR</module>" << std::endl;
    ss << "    </modules>" << std::endl;
    ss << "    <level>2</level>" << std::endl;
    ss << "</debug>" << std::endl;

    boost::property_tree::read_xml(ss, tree);
    EXPECT_EQ(tree.get<std::string>("debug.filename"), "debug.log");
    EXPECT_EQ(tree.get<int>("debug.level"), 2);
}
