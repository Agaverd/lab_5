#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <atomic>
#include <chrono>


const int NUM_THREADS = 4;
//changing amount of threads to 8 twising runtime cause processor have only 4 cores
const int INCREMENTS_PER_THREAD = 2'000'000;

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
    //testing mutex
    int mutex_counter = 0;
    std::mutex mtx;
    std::vector<std::thread> threads;

    auto mutex_start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < NUM_THREADS; ++i) {
        threads.emplace_back(mutex_func, std::ref(mutex_counter), std::ref(mtx)); 
        //to share resource via link we have to overlap it into std::ref
    }
    for (auto& t : threads) t.join();

    auto mutex_end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> mutex_dur = mutex_end - mutex_start;

    std::cout << "Mutex func: counter = " << mutex_counter << ", time = " << mutex_dur.count() << " ms" << std::endl;

	//testing atomic

    std::atomic<int> atomic_counter(0);
    threads.clear(); 

    auto atomic_start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < NUM_THREADS; ++i) {
        threads.emplace_back(atomic_func, std::ref(atomic_counter));
    }
    for (auto& t : threads) t.join();

    auto atomic_end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> atomic_dur = atomic_end - atomic_start;

    std::cout << "Atomic version: counter = " << atomic_counter
        << ", time = " << atomic_dur.count() << " ms" << std::endl;

    return 0;
}