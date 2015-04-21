#ifndef UTILSTEST_H
#define UTILSTEST_H

#include "Utils.h"
#include "INamed.h"
#include "gtest/gtest.h"
#include <map>
#include <iostream>
#include <boost/assign/list_of.hpp>
#include <boost/scoped_ptr.hpp>

using namespace Utils;

class UtilsTest : public ::testing::Test
{
protected:
    UtilsTest(){}
    virtual ~UtilsTest(){}
};


TEST_F(UtilsTest, OrderedMapInsert)
{
    OrderedMap<int, std::string> omap;
    EXPECT_EQ( size_t(0), omap.size());

    std::vector<int> keys = boost::assign::list_of(3)(2)(1);
    std::vector<std::string> values = boost::assign::list_of("aaa")("bbb")("ccc");

    omap.insert(keys[0], values[0]);
    omap.insert(keys[1], values[1]);
    omap.insert(keys[2], values[2]);
    EXPECT_EQ( size_t(3), omap.size());

    // check that <key,value> are stored in the order of insertion and that there is no sorting
    // along key as in normal map
    int npos(0);
    for(OrderedMap<int, std::string>::const_iterator it = omap.begin(); it!= omap.end(); ++it) {
        EXPECT_EQ(keys[npos], it->first);
        EXPECT_EQ(values[npos], it->second);
        npos++;
    }

    omap.clear();
    EXPECT_EQ( size_t(0), omap.size());
}

TEST_F(UtilsTest, OrderedMapErase)
{
    OrderedMap<std::string, double> omap;

    std::vector<std::string> keys = boost::assign::list_of("ccc")("bbb")("aaa");
    std::vector<double> values = boost::assign::list_of(2.0)(1.0)(3.0);

    omap.insert(keys[0], values[0]);
    omap.insert(keys[1], values[1]);
    omap.insert(keys[2], values[2]);

    int npos(0);
    for(OrderedMap<std::string, double>::const_iterator it = omap.begin(); it!= omap.end(); ++it) {
        EXPECT_EQ(keys[npos], it->first);
        EXPECT_EQ(values[npos], it->second);
        npos++;
    }

    EXPECT_EQ(size_t(3), omap.size());

    EXPECT_EQ(omap.erase("ddd"), size_t(0));
    EXPECT_EQ(size_t(3), omap.size());

    EXPECT_EQ(omap.erase("bbb"), size_t(1));
    EXPECT_EQ(size_t(2), omap.size());

    keys = boost::assign::list_of("ccc")("aaa");
    values = boost::assign::list_of(2.0)(3.0);
    npos = 0;
    for(OrderedMap<std::string, double>::const_iterator it = omap.begin(); it!= omap.end(); ++it) {
        EXPECT_EQ(keys[npos], it->first);
        EXPECT_EQ(values[npos], it->second);
        npos++;
    }

    EXPECT_EQ(omap.erase("ccc"), size_t(1));
    EXPECT_EQ(omap.erase("aaa"), size_t(1));
    EXPECT_EQ(size_t(0), omap.size());

    omap.insert("ddd", 99.0);
    EXPECT_EQ(size_t(1), omap.size());
}

TEST_F(UtilsTest, OrderedMapGetValue)
{
    OrderedMap<const INamed *, INamed *> omap;

    INamed *key1 = new INamed("key1");
    INamed *key2 = new INamed("key2");
    INamed *key3 = new INamed("key3");
    INamed *val1 = new INamed("val1");
    INamed *val2 = new INamed("val2");
    INamed *val3 = new INamed("val3");

    omap.insert(key1, val1);
    omap.insert(key2, val2);
    omap.insert(key3, val3);

    EXPECT_EQ(omap.value(key1), val1);
    EXPECT_EQ(omap.value(key2), val2);
    EXPECT_EQ(omap.value(key3), val3);

    delete key1; delete key2; delete key3; delete val1; delete val2; delete val3;
}

TEST_F(UtilsTest, OrderedMapFind)
{
    OrderedMap<const INamed *, std::string> omap;

    INamed *n1 = new INamed("named1");
    INamed *n2 = new INamed("named2");
    INamed *n3 = new INamed("named3");
    INamed *n4 = new INamed("named4");

    omap.insert(n1, "aaa");
    omap.insert(n2, "bbb");
    omap.insert(n3, "ccc");
    EXPECT_EQ( size_t(3), omap.size());

    EXPECT_EQ(omap.find(n1)->first, n1);
    EXPECT_EQ(omap.find(n1)->first->getName(), "named1");
    EXPECT_EQ(omap.find(n1)->second, std::string("aaa"));

    EXPECT_EQ(omap.find(n2)->first, n2);
    EXPECT_EQ(omap.find(n2)->first->getName(), "named2");
    EXPECT_EQ(omap.find(n2)->second, std::string("bbb"));

    EXPECT_EQ(omap.find(n3)->first, n3);
    EXPECT_EQ(omap.find(n3)->first->getName(), "named3");
    EXPECT_EQ(omap.find(n3)->second, std::string("ccc"));

    EXPECT_EQ(omap.find(n4), omap.end());

    delete n1; delete n2; delete n3; delete n4;
}

TEST_F(UtilsTest, OrderedMapReInsert)
{
    boost::scoped_ptr<INamed> n1(new INamed("named1"));
    boost::scoped_ptr<INamed> n2(new INamed("named2"));
    boost::scoped_ptr<INamed> n3(new INamed("named3"));
    boost::scoped_ptr<INamed> n4(new INamed("named4"));

    OrderedMap<INamed *, double> omap;
    omap.insert(n1.get(), 1.0);
    omap.insert(n2.get(), 2.0);
    omap.insert(n3.get(), 3.0);
    EXPECT_EQ(omap.size(), size_t(3));

    omap.insert(n2.get(), 99.0);
    EXPECT_EQ(omap.size(), size_t(3));
    EXPECT_EQ(omap.value(n2.get()), 99.0);


}

#endif
