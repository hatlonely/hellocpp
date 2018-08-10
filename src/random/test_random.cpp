#include <boost/thread/shared_mutex.hpp>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>
#include <random>
#include <shared_mutex>
#include <thread>
#include <unordered_map>
#include <vector>

size_t rand_rand() {
    return rand();
}

size_t rand_rand_r() {
    static unsigned int seed = 123;
    return rand_r(&seed);
}

size_t rand_std_random_device() {
    std::random_device rd;
    return rd();
}

size_t rand_std_random_device_static() {
    static std::random_device rd;
    return rd();
}

size_t rand_std_mt19937_64() {
    std::random_device rd;
    std::mt19937_64    mt(rd());
    return mt();
}

size_t rand_std_mt19937_64_static() {
    static std::random_device rd;
    static std::mt19937_64    mt(rd());
    return mt();
}

size_t rand_std_uniform_int_distribution() {
    std::random_device                      rd;
    std::mt19937_64                         mt(rd());
    std::uniform_int_distribution<unsigned> dis(0, std::numeric_limits<int>::max());
    return dis(mt);
}

size_t rand_std_uniform_int_distribution_static() {
    static std::random_device                      rd;
    static std::mt19937_64                         mt(rd());
    static std::uniform_int_distribution<unsigned> dis(0, std::numeric_limits<int>::max());
    return dis(mt);
}

void test_rand(std::string name, size_t (*randfunc)()) {
    auto                      threadNum = 16;
    std::vector<std::thread*> vt;
    std::vector<size_t>       counter(threadNum);
    auto                      randMax = 16;

    boost::shared_mutex mutex;
    mutex.lock();
    for (int i = 0; i < threadNum; i++) {
        vt.emplace_back(new std::thread(
            [&](int idx) {
                mutex.lock_shared();
                counter[idx] = randfunc() % randMax;
                mutex.unlock_shared();
            },
            i));
    }
    mutex.unlock();
    for (auto& t : vt) {
        if (t->joinable()) {
            t->join();
        }
    }

    std::unordered_map<size_t, size_t> times;
    for (int i = 0; i < randMax; i++) {
        if (times.count(i) <= 0) {
            times[i] = 0;
        }
    }
    for (auto i : counter) {
        times[i]++;
    }

    double entropy = 0.0;
    for (auto [key, val] : times) {
        if (val == 0) {
            continue;
        }
        auto p = double(val) / double(threadNum);
        entropy -= p * log(p);
    }

    double variance = 0.0;
    double avg      = double(threadNum) / double(randMax);
    for (auto [key, val] : times) {
        variance += (double(val) - avg) * (double(val) - avg);
    }

    std::cout << std::setw(50) << std::setiosflags(std::ios::left) << name << " => " << entropy << ", " << variance << std::endl;
    // for (auto [key, val] : times) {
    //     std::cout << key << " => " << val << std::endl;
    // }
    // std::cout << std::endl;
}

int main(int argc, const char* argv[]) {
    auto v = {
        std::make_tuple("rand", rand_rand),
        std::make_tuple("rand_r", rand_rand_r),
        std::make_tuple("std::random_device", rand_std_random_device),
        std::make_tuple("static std::random_device", rand_std_random_device_static),
        std::make_tuple("std::mt19937_64", rand_std_mt19937_64),
        std::make_tuple("static std::mt19937_64", rand_std_mt19937_64_static),
        std::make_tuple("std::uniform_int_distribution_static", rand_std_uniform_int_distribution),
        std::make_tuple("static std::uniform_int_distribution_static", rand_std_uniform_int_distribution_static),
    };
    for (auto nf : v) {
        auto [name, func] = nf;
        test_rand(name, func);
    }
}