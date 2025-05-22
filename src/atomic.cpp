#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <atomic>
#include <chrono>


const int NUM_THREADS = 4;
const int INCREMENTS_PER_THREAD = 1'000'000;

void mutex_func(int& counter, std::mutex& mtx) {
    for (int i = 0; i < INCREMENTS_PER_THREAD; ++i) {
        std::lock_guard<std::mutex> lock(mtx);
        ++counter;
    }
}

void atomic_func(std::atomic<int>& counter) {
    for (int i = 0; i < INCREMENTS_PER_THREAD; ++i) {
        ++counter;
    }
}

int main() {

}