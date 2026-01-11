#include <iostream>
#include <chrono>
#include <vector>
#include <set>
#include <numeric>
#include <algorithm>
#include <random>
#include <iomanip>
#include <string>

#include "BinaryTree.hpp"
#include "AVLTree.hpp"

// Helper structure to hold results
struct BenchResult {
    double insertTime;
    double removeTime;
    int finalHeight;
};

// Helper to measure a specific tree implementation
template<typename TreeType>
BenchResult measure(const std::vector<int>& data) {
    TreeType tree;
    
    // Measure Insert
    auto start_in = std::chrono::high_resolution_clock::now();
    for (int x : data) tree.insert(x);
    auto end_in = std::chrono::high_resolution_clock::now();
    
    int height = tree.getRoot() ? tree.getRoot()->getHeight() : 0;

    // Measure RemoveMin
    auto start_out = std::chrono::high_resolution_clock::now();
    size_t n = data.size();
    for (size_t i = 0; i < n; ++i) {
        tree.removeMin();
    }
    auto end_out = std::chrono::high_resolution_clock::now();

    return {
        std::chrono::duration<double>(end_in - start_in).count(),
        std::chrono::duration<double>(end_out - start_out).count(),
        height
    };
}

// Special measurement for std::multiset
BenchResult measureMultiset(const std::vector<int>& data) {
    std::multiset<int> ms;
    auto start_in = std::chrono::high_resolution_clock::now();
    for (int x : data) ms.insert(x);
    auto end_in = std::chrono::high_resolution_clock::now();

    auto start_out = std::chrono::high_resolution_clock::now();
    size_t n = data.size();
    for (size_t i = 0; i < n; ++i) {
        auto it = ms.begin();
        if (it != ms.end()) ms.erase(it);
    }
    auto end_out = std::chrono::high_resolution_clock::now();

    return {
        std::chrono::duration<double>(end_in - start_in).count(),
        std::chrono::duration<double>(end_out - start_out).count(),
        -1 
    };
}

void printHeader(const std::string& title, int N) {
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "  " << title << " (N = " << N << ")\n";
    std::cout << std::string(60, '=') << "\n";
    std::cout << std::left << std::setw(15) << "Structure" 
              << std::setw(15) << "Insert (s)" 
              << std::setw(15) << "Remove (s)" 
              << std::setw(10) << "Height" << std::endl;
    std::cout << std::string(60, '-') << std::endl;
}

void printRow(const std::string& name, BenchResult res) {
    std::cout << std::left << std::setw(15) << name 
              << std::setw(15) << res.insertTime 
              << std::setw(15) << res.removeTime;
    if (res.finalHeight >= 0) std::cout << std::setw(10) << res.finalHeight;
    else std::cout << std::setw(10) << "N/A";
    std::cout << std::endl;
}

int main() {
    std::cout << std::fixed << std::setprecision(6);

    // --- RANDOM DATA ---
    {
        const int N = 100000;
        std::vector<int> data(N);
        std::iota(data.begin(), data.end(), 1);
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(data.begin(), data.end(), g);

        printHeader("RANDOM DATA", N);
        printRow("BinaryTree", measure<adsc::BinaryTree<int>>(data));
        printRow("AVLTree", measure<adsc::AVLTree<int>>(data));
        printRow("std::multiset", measureMultiset(data));
    }

    // --- SORTED DATA ---
    {
        const int N = 15000; 
        std::vector<int> data(N);
        std::iota(data.begin(), data.end(), 1);

        printHeader("SORTED DATA", N);
        printRow("BinaryTree", measure<adsc::BinaryTree<int>>(data));
        printRow("AVLTree", measure<adsc::AVLTree<int>>(data));
        printRow("std::multiset", measureMultiset(data));
    }

    std::cout << std::string(60, '=') << std::endl;
    return 0;
}