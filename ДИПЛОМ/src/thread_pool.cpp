#include "thread_pool.h"

ThreadPool::ThreadPool(size_t num_threads) {
    if (num_threads == 0) {
        num_threads = std::thread::hardware_concurrency();
        if (num_threads <= 4) {
        } else {
            num_threads += 2;
        }
        if (num_threads > 16) num_threads = 16;
        if (num_threads < 2) num_threads = 2;
    }

    std::cout << "[ThreadPool] Created with " << num_threads 
              << " threads (hardware concurrency: " 
              << std::thread::hardware_concurrency() << ")\n";

    for (size_t i = 0; i < num_threads; ++i) {
        workers.emplace_back([this] {
            while (true) {
                std::function<void()> task;

                {
                    std::unique_lock<std::mutex> lock(queue_mutex);
                    condition.wait(lock, [this] { return stop || !tasks.empty(); });

                    if (stop && tasks.empty()) {
                        return;
                    }

                    task = std::move(tasks.front());
                    tasks.pop();
                }

                if (task) {
                    task();
                }
            }
        });
    }
}

ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop = true;
    }
    condition.notify_all();

    for (std::thread& worker : workers) {
        if (worker.joinable()) {
            worker.join();
        }
    }
}

void ThreadPool::enqueue(std::function<void()> task) {
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        if (stop) return;
        tasks.emplace(std::move(task));
    }
    condition.notify_one();
}

void ThreadPool::wait() {
    std::unique_lock<std::mutex> lock(queue_mutex);
    condition.wait(lock, [this] { 
        return tasks.empty(); 
    });
}