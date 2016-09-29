#include <bits/stdc++.h>


template <class Class>
void Print(Class instance) {
    std::cout << instance << std::endl;
}

void Print() {
    std::cout << std::endl;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    // std::ifstream input("input.txt");
    // std::ofstream output("output.txt");
    size_t n;
    std::cin >> n;

    size_t tau = 0;
    uint64_t sigma = 0;
    size_t sqrt_n = std::floor(std::sqrt(n)) + 1;
    for (size_t index = 1; index < sqrt_n; ++index) {
        if (n % index == 0) {
            tau += 2;
            sigma += index + n / index;
            
        }
    }
    --sqrt_n;
    if (sqrt_n * sqrt_n == n) {
        tau -= 1;
        sigma -= sqrt_n;
    }

    std::cout << tau << ' ' << sigma;
    return 0;
}


