#include "computations.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cassert>
#include <cmath>

int main() {
    std::cout << "[TEST] Running work() test...\n";

    std::vector<std::pair<std::string, double>> log;
    double elapsed = work(&log);

    std::cout << "\n[TEST] Results analysis:\n";
    std::cout << "Total time: " << elapsed << " s\n";

    if (log.size() != 7) {
        std::cerr << "[FAIL] Expected 7 operations, executed: " << log.size() << "\n";
        return 1;
    }

    std::map<std::string, double> times;
    for (const auto& [name, t] : log) {
        times[name] = t;
        std::cout << "  - " << name << " completed at " << t << " s\n";
    }

    const std::vector<std::string> expected = {"A1", "A2", "B1", "B2", "C", "D", "F"};
    for (const auto& name : expected) {
        if (times.find(name) == times.end()) {
            std::cerr << "[FAIL] Computation " << name << " is missing from logs!\n";
            return 2;
        }
    }

    if (times["A1"] >= times["A2"]) {
        std::cerr << "[FAIL] Dependency A2(A1) violated: A1 finished at " 
                  << times["A1"] << ", A2 at " << times["A2"] << "\n";
        return 3;
    }

    if (times["B1"] >= times["B2"]) {
        std::cerr << "[FAIL] Dependency B2(B1) violated: B1 finished at " 
                  << times["B1"] << ", B2 at " << times["B2"] << "\n";
        return 4;
    }

    if (times["C"] >= times["F"]) {
        std::cerr << "[FAIL] Dependency F(C) violated: C finished at " 
                  << times["C"] << ", F at " << times["F"] << "\n";
        return 5;
    }

    if (times["A2"] >= times["D"] || times["B2"] >= times["D"]) {
        std::cerr << "[FAIL] Dependency D(A2, B2) violated: D=" << times["D"]
                  << ", A2=" << times["A2"] << ", B2=" << times["B2"] << "\n";
        return 6;
    }

    if (elapsed < 8.85 || elapsed > 9.75) {
        std::cerr << "[FAIL] Total time " << elapsed 
                  << " s is out of expected range [8.85, 9.75] s!\n";
        return 7;
    }

    std::cout << "\n[PASS] All verification checks passed!\n";
    return 0;
}
