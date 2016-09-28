#include <bits/stdc++.h>


template <class Class>
void Print(Class instance) {
    std::cout << instance << std::endl;
}

void Print() {
    std::cout << std::endl;
}

template <class Number>
Number GCD(Number first, Number second) {
    if (second > first) {
        std::swap(second, first);
    }
    while (second > 0) {
        Number temp = first % second;
        first = second;
        second = temp;
    }
    return first;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    // std::ifstream input("input.txt");
    // std::ofstream output("output.txt");
    size_t n;
    std::cin >> n;
    for (size_t index = n / 2; index > 1; --index) {
        if (GCD(index, n - index) == 1) {
            std::cout << index << ' ' << n - index;
            return 0;
        }
    }
    std::cout << 1 << ' ' << n - 1;
    return 0;
}


