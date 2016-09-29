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
    size_t res = n;
    for (size_t index = 2; res > 1 && index <= std::ceil(std::sqrt(n));) {
        if (res % index == 0) {
            std::cout << index << ' ';
            res /= index;
        } else {
            ++index;
        }
    }
    if (res > 1) {
        Print(res);
    }
    return 0;
}


