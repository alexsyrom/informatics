#include <bits/stdc++.h>


template <class Class>
void Print(Class instance) {
    std::cout << instance << std::endl;
}

void Print() {
    std::cout << std::endl;
}


size_t FindSigma(size_t n) {
    size_t sigma = 0;
    size_t sqrt_n = std::floor(std::sqrt(n)) + 1;
    for (size_t index = 1; index < sqrt_n; ++index) {
        if (n % index == 0) {
            sigma += index + n / index;
        }
    }
    --sqrt_n;
    if (sqrt_n * sqrt_n == n) {
        sigma -= sqrt_n;
    }
    return sigma;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    // std::ifstream input("input.txt");
    // std::ofstream output("output.txt");
    size_t n;
    std::cin >> n;

    std::vector<size_t> pseudosigma(n + 1); 
    for (size_t index = 2; index < n + 1; ++index) {
        pseudosigma[index] = FindSigma(index) - index;
    }

    for (size_t index = 2; index < n + 1; ++index) {
        if (pseudosigma[index] < n + 1 && 
            pseudosigma[pseudosigma[index]] == index && 
            pseudosigma[index] > index) {
                std::cout << index << ' ' << pseudosigma[index] << std::endl;
        }
    }
    return 0;
}


