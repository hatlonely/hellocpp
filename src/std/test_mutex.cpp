#include <gtest/gtest.h>
#include <chrono>
#include <iostream>
#include <random>
#include <shared_mutex>
#include <thread>
#include <unordered_map>

using namespace std::chrono_literals;

template <typename T>
class BlockingQueue {
    std::mutex              _mutex;
    std::condition_variable _not_full;
    std::condition_variable _not_empty;
    int                     _start;
    int                     _end;
    int                     _capacity;
    std::vector<T>          _vt;

   public:
    BlockingQueue(const BlockingQueue<T>& other) = delete;
    BlockingQueue<T>& operator=(const BlockingQueue<T>& other) = delete;
    BlockingQueue(int capacity) : _capacity(capacity), _vt(capacity + 1), _start(0), _end(0) {}

    bool isempty() {
        return _end == _start;
    }

    bool isfull() {
        return (_start + _capacity - _end) % (_capacity + 1) == 0;
    }

    bool offer(const T& e, std::chrono::milliseconds ms = 0ms) {
        std::unique_lock<std::mutex> lock(_mutex);

        if (ms == 0ms) {
            _not_full.wait(lock, [this] { return !isfull(); });
        } else {
            if (!_not_full.wait_for(lock, ms, [this] { return !isfull(); })) {
                return false;
            }
        }

        _vt[_end++] = e;
        _end %= (_capacity + 1);
        _not_empty.notify_one();

        return true;
    }

    bool poll(T& e, std::chrono::milliseconds ms = 0ms) {
        std::unique_lock<std::mutex> lock(_mutex);

        if (ms == 0ms) {
            _not_empty.wait(lock, [this] { return !isempty(); });
        } else {
            if (!_not_empty.wait_for(lock, ms, [this] { return !isempty(); })) {
                return false;
            }
        }

        e = _vt[_start++];
        _start %= (_capacity + 1);
        _not_full.notify_one();
        return true;
    }
};

TEST(testMutex, caseBlockingQueue) {
    BlockingQueue<int>       q(4);
    std::vector<std::thread> ps(10);
    std::vector<std::thread> cs(20);

    auto now = std::chrono::system_clock::now();
    for (int i = 0; i < ps.size(); i++) {
        ps[i] = std::thread([&now](BlockingQueue<int>& q, int i) {
            while (std::chrono::system_clock::now() - now < 1s) {
                std::random_device rd;
                auto               p  = rd() % 10;
                auto               ok = q.offer(p, 20ms);
                std::cout << "produce " << i << " ok [" << ok << "] [" << p << "]" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(15 + rd() % 50));
            }
        },
                            std::ref(q), i);
    }
    for (int i = 0; i < cs.size(); i++) {
        cs[i] = std::thread([&now](BlockingQueue<int>& q, int i) {
            while (std::chrono::system_clock::now() - now < 1s) {
                std::random_device rd;
                int                p;
                auto               ok = q.poll(p, 20ms);
                std::cout << "consume " << i << " ok [" << ok << "] [" << p << "]" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(15 + rd() % 50));
            }
        },
                            std::ref(q), i);
    }
    for (int i = 0; i < ps.size(); i++) {
        ps[i].join();
    }
    for (int i = 0; i < cs.size(); i++) {
        cs[i].join();
    }
}

TEST(testMutex, caseRWLock) {
    std::unordered_map<int, int> map;

    std::vector<std::thread> ps(10);
    std::vector<std::thread> cs(20);
    std::shared_mutex        mutex;

    auto now = std::chrono::system_clock::now();
    for (int i = 0; i < ps.size(); i++) {
        ps[i] = std::thread([&] {
            while (std::chrono::system_clock::now() - now < 1s) {
                std::lock_guard<std::shared_mutex> lock(mutex);  // 写锁
                std::random_device                 rd;
                map[rd() % 100] = rd() % 100;
            }
        });
    }
    for (int i = 0; i < cs.size(); i++) {
        cs[i] = std::thread([&] {
            while (std::chrono::system_clock::now() - now < 1s) {
                std::shared_lock<std::shared_mutex> lock(mutex);  // 读锁
                std::random_device                  rd;
                auto                                key = rd() % 100;
                std::cout << key << " => " << map[key] << std::endl;
            }
        });
    }
    for (int i = 0; i < ps.size(); i++) {
        ps[i].join();
    }
    for (int i = 0; i < cs.size(); i++) {
        cs[i].join();
    }
}
