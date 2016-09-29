#include <bits/stdc++.h>


template <class Class>
void Print(Class instance) {
    std::cout << instance << std::endl;
}

void Print() {
    std::cout << std::endl;
}

bool IsPrime(size_t number) {
    if (number < 2) {
        return false;
    }
    if (number == 2) {
        return true;
    }
    size_t sqrt_n = std::ceil(std::sqrt(number));
    for (size_t index = 2; index < sqrt_n + 1; ++index) {
        if (number % index == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    // std::ifstream input("input.txt");
    // std::ofstream output("output.txt");
    size_t n;
    std::cin >> n;

    if (n == 4) {
        std::cout << 2 << ' ' << 2;
        return 0;
    }
    for (size_t index = 3; index < n / 2 + 1; index += 2) {
        if (IsPrime(index) && IsPrime(n - index)) {
            std::cout << index << ' ' << n - index;
            return 0;
        }
    }
    return 0;
}


