#include <iostream>
#include <thread>
#include <vector>
#include <unistd.h>

int main(int argc, const char *argv[]) {
    std::cout << "hello world" << std::endl;
    
    std::vector<std::thread*> vt;
    for (int i = 0; i < 10; i++) {
        vt.emplace_back(new std::thread([&](){
            std::cout << "hello world 666" << std::endl;
        }));
    }
    for (auto t: vt) {
        if (t->joinable()) {
            t->join();
        }
    }
}
