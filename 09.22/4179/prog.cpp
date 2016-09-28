#include <bits/stdc++.h>


template <class Class>
void Print(Class instance) {
    std::cout << instance << std::endl;
}

void Print() {
    std::cout << std::endl;
}

size_t GCD(size_t first, size_t second) {
    if (second > first) {
        std::swap(second, first);
    }
    while (second > 0) {
        size_t temp = first % second;
        first = second;
        second = temp;
    }
    return first;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    // std::ifstream input("input.txt");
    // std::ofstream output("output.txt");
    size_t first, second;
    std::cin >> first >> second;
    Print(GCD(first, second));
    return 0;
}


