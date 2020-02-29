#include <gtest/gtest.h>
#include <boost/poly_collection/base_collection.hpp>
#include <iostream>
#include <list>

namespace test {
namespace poly {

class A {
   public:
    A(int id) : id(id) {}
    virtual void show() const {
        std::cout << "A(" << id << ")" << std::endl;
    }

   protected:
    int id;
};

class B : public A {
   public:
    B(int id) : A(id) {}
    virtual void show() const {
        std::cout << "B(" << id << ")" << std::endl;
    }
};

class C : public A {
   public:
    C(int id) : A(id) {}
    virtual void show() const {
        std::cout << "C(" << id << ")" << std::endl;
    }
};

class D : public B {
   public:
    D(int id) : B(id) {}
    virtual void show() const {
        std::cout << "D(" << id << ")" << std::endl;
    }
};
}
}

TEST(testPolyCollection, caseStdVector) {
    // stl 标准容器没有多态特性
    std::vector<test::poly::A> va;
    for (int i = 0; i < 8; i++) {
        switch (i % 3) {
            case 0:
                va.push_back(test::poly::B(i));
                break;
            case 1:
                va.push_back(test::poly::C(i));
                break;
            case 2:
                va.push_back(test::poly::D(i));
                break;
        }
    }
    std::for_each(va.begin(), va.end(), [](test::poly::A& x) { x.show(); });
}

TEST(testPolyCollection, caseStdVectorPointer) {
    // 想要获得多态特性，需要使用指针
    std::vector<test::poly::A*> va;
    for (int i = 0; i < 8; i++) {
        switch (i % 3) {
            case 0:
                va.push_back(new test::poly::B(i));
                break;
            case 1:
                va.push_back(new test::poly::C(i));
                break;
            case 2:
                va.push_back(new test::poly::D(i));
                break;
        }
    }
    std::for_each(va.begin(), va.end(), [](test::poly::A* x) { x->show(); });
    std::for_each(va.begin(), va.end(), [](test::poly::A* x) { delete x; });
}

TEST(testPolyCollection, casePolyCollection) {
    // 可以保留多态特性的容器
    boost::base_collection<test::poly::A> ca;
    for (int i = 0; i < 8; i++) {
        switch (i % 3) {
            case 0:
                ca.insert(test::poly::B(i));
                break;
            case 1:
                ca.insert(test::poly::C(i));
                break;
            case 2:
                ca.insert(test::poly::D(i));
                break;
        }
    }
    std::for_each(ca.begin(), ca.end(), [](test::poly::A& x) { x.show(); });
}
