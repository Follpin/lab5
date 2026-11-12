#pragma once

#include <string>
#include <vector>
#include <utility>
#include <chrono>

void compute(const std::string& name, int duration_seconds, 
             std::vector<std::pair<std::string, double>>* log = nullptr,
             const std::chrono::steady_clock::time_point* start_time = nullptr);

void slow(const std::string& name, 
          std::vector<std::pair<std::string, double>>* log = nullptr,
          const std::chrono::steady_clock::time_point* start_time = nullptr);

void quick(const std::string& name, 
           std::vector<std::pair<std::string, double>>* log = nullptr,
           const std::chrono::steady_clock::time_point* start_time = nullptr);

double work(std::vector<std::pair<std::string, double>>* log = nullptr);
