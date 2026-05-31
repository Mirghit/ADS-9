// Copyright 2022 NNTU-CS
#include <chrono>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>
#include "tree.h"

int main() {
    std::vector<char> in = {'1', '2', '3'};
    PMTree tree(in);
    auto perms = getAllPerms(tree);
    std::cout << "Все перестановки {1,2,3}:\n";
    for (const auto& perm : perms) {
        for (char c : perm) std::cout << c;
        std::cout << "\n";
    }
    auto p1 = getPerm1(tree, 1);
    auto p2 = getPerm2(tree, 2);
    std::cout << "getPerm1(1): ";
    for (char c : p1) std::cout << c;
    std::cout << "\n";
    std::cout << "getPerm2(2): ";
    for (char c : p2) std::cout << c;
    std::cout << "\n\n";

    const int N_MAX = 10;
    const int REPEAT = 3;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "n\tgetAllPerms(s)\tgetPerm1(s)\tgetPerm2(s)\n";
    for (int n = 1; n <= N_MAX; ++n) {
        std::vector<char> chars;
        for (int i = 0; i < n; ++i) chars.push_back('a' + i);
        PMTree tree(chars);
        uint64_t total = factorial(n);
        std::uniform_int_distribution<uint64_t> dist(1, total);
        uint64_t rand_num = dist(gen);
        double sum_all = 0.0, sum_p1 = 0.0, sum_p2 = 0.0;
        for (int r = 0; r < REPEAT; ++r) {
            auto start = std::chrono::high_resolution_clock::now();
            auto all = getAllPerms(tree);
            auto end = std::chrono::high_resolution_clock::now();
            sum_all += std::chrono::duration<double>(end - start).count();

            start = std::chrono::high_resolution_clock::now();
            auto perm1 = getPerm1(tree, static_cast<int>(rand_num));
            end = std::chrono::high_resolution_clock::now();
            sum_p1 += std::chrono::duration<double>(end - start).count();

            start = std::chrono::high_resolution_clock::now();
            auto perm2 = getPerm2(tree, static_cast<int>(rand_num));
            end = std::chrono::high_resolution_clock::now();
            sum_p2 += std::chrono::duration<double>(end - start).count();
        }
        double t_all = sum_all / REPEAT;
        double t_p1  = sum_p1  / REPEAT;
        double t_p2  = sum_p2  / REPEAT;
        std::cout << n << "\t" << t_all << "\t" << t_p1 << "\t" << t_p2 << "\n";
    }
    return 0;
}
