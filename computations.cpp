#include "computations.h"
#include <iostream>
#include <syncstream>
#include <chrono>
#include <thread>
#include <future>
#include <mutex>

static std::mutex g_log_mutex;

void compute(const std::string& name, int duration_seconds,
             std::vector<std::pair<std::string, double>>* log,
             const std::chrono::steady_clock::time_point* start_time) {
    std::this_thread::sleep_for(std::chrono::seconds(duration_seconds));
    std::osyncstream(std::cout) << name << '\n';

    if (log && start_time) {
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<double> diff = now - *start_time;
        std::lock_guard<std::mutex> lock(g_log_mutex);
        log->emplace_back(name, diff.count());
    }
}

void slow(const std::string& name,
          std::vector<std::pair<std::string, double>>* log,
          const std::chrono::steady_clock::time_point* start_time) {
    compute(name, 7, log, start_time);
}

void quick(const std::string& name,
           std::vector<std::pair<std::string, double>>* log,
           const std::chrono::steady_clock::time_point* start_time) {
    compute(name, 1, log, start_time);
}

double work(std::vector<std::pair<std::string, double>>* log) {
    const auto start_time = std::chrono::steady_clock::now();

    auto futB = std::async(std::launch::async, [log, &start_time]() {
        quick("B1", log, &start_time);
        slow("B2", log, &start_time);
    });

    auto futC = std::async(std::launch::async, [log, &start_time]() {
        quick("C", log, &start_time);
        quick("F", log, &start_time);
    });

    slow("A1", log, &start_time);
    quick("A2", log, &start_time);

    futB.get();

    quick("D", log, &start_time);

    futC.get();

    auto end_time = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;

    std::osyncstream(std::cout) << "Execution time: " << elapsed.count() << " seconds\n";
    std::osyncstream(std::cout) << "Work is done!\n";

    return elapsed.count();
}
