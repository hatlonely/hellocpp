#include <atomic>
#include <boost/thread/shared_mutex.hpp>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>
#include <mutex>
#include <random>
#include <thread>
#include <unordered_map>
#include <vector>

size_t rand_rand() {
    return rand();
}

size_t rand_rand_mutex() {
    static std::mutex mutex;
    mutex.lock();
    auto r = rand();
    mutex.unlock();
    return r;
}

size_t rand_rand_r() {
    static unsigned int seed = time(nullptr);
    return rand_r(&seed);
}

size_t rand_rand_r_thread_local() {
    thread_local unsigned int seed = std::hash<std::thread::id>{}(std::this_thread::get_id());
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

size_t rand_std_uniform_int_distribution_thread_local() {
    thread_local std::random_device                      rd;
    thread_local std::mt19937_64                         mt(rd());
    thread_local std::uniform_int_distribution<unsigned> dis(0, std::numeric_limits<int>::max());
    return dis(mt);
}

size_t rand_std_uniform_int_distribution_static_mutex() {
    static std::random_device                      rd;
    static std::mt19937_64                         mt(rd());
    static std::uniform_int_distribution<unsigned> dis(0, std::numeric_limits<int>::max());
    static std::mutex                              mutex;
    mutex.lock();
    auto r = dis(mt);
    mutex.unlock();
    return r;
}

size_t atomic_inc() {
    static std::atomic<int> ai;
    ai++;
    return ai;
}

std::tuple<std::unordered_map<size_t, size_t>, size_t, size_t> test_rand(const std::string& name, size_t (*randfunc)()) {
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
    return std::make_tuple(times, threadNum, randMax);
}

double entropy(const std::unordered_map<size_t, size_t>& times, size_t threadNum, size_t randMax) {
    double e = 0.0;
    for (const auto& kv : times) {
        if (kv.second == 0) {
            continue;
        }
        auto p = double(kv.second) / double(threadNum);
        e -= p * log(p);
    }
    return e;
}

double variance(const std::unordered_map<size_t, size_t>& times, size_t threadNum, size_t randMax) {
    double v   = 0.0;
    double avg = double(threadNum) / double(randMax);
    for (const auto& kv : times) {
        v += (double(kv.second) - avg) * (double(kv.second) - avg);
    }
    return v;
}

double avg(const std::vector<double>& vd) {
    double sum = 0.0;
    for (auto d : vd) {
        sum += d;
    }
    return sum / double(vd.size());
}

int main(int argc, const char* argv[]) {
    srand(time(nullptr));

    auto v = {
        std::make_tuple("rand", rand_rand),
        std::make_tuple("mutex rand", rand_rand_mutex),
        std::make_tuple("rand_r", rand_rand_r),
        std::make_tuple("thread_local rand_r", rand_rand_r_thread_local),
        std::make_tuple("std::random_device", rand_std_random_device),
        std::make_tuple("static std::random_device", rand_std_random_device_static),
        std::make_tuple("std::mt19937_64", rand_std_mt19937_64),
        std::make_tuple("static std::mt19937_64", rand_std_mt19937_64_static),
        std::make_tuple("std::uniform_int_distribution_static", rand_std_uniform_int_distribution),
        std::make_tuple("static std::uniform_int_distribution_static", rand_std_uniform_int_distribution_static),
        std::make_tuple("thread_local std::uniform_int_distribution_static", rand_std_uniform_int_distribution_thread_local),
        std::make_tuple("static mutex std::uniform_int_distribution_static", rand_std_uniform_int_distribution_static_mutex),
        std::make_tuple("atomic int", atomic_inc),
    };

    for (const auto& nf : v) {
        auto name = std::get<0>(nf);
        auto func = std::get<1>(nf);

        auto                num = 100;
        std::vector<double> es(num);
        std::vector<double> vs(num);
        for (int i = 0; i < num; i++) {
            int                                threadNum = 0;
            int                                randMax   = 0;
            std::unordered_map<size_t, size_t> times;
            std::tie(times, threadNum, randMax) = test_rand(name, func);

            es[i] = entropy(times, threadNum, randMax);
            vs[i] = variance(times, threadNum, randMax);
        }

        std::cout << std::setw(50) << std::setiosflags(std::ios::left) << name << " => " << avg(es) << ", " << avg(vs) << std::endl;
        // for (auto [key, val] : times) {
        //     std::cout << key << " => " << val << std::endl;
        // }
        // std::cout << std::endl;
    }
}