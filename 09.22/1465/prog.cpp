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
    size_t A, B;
    std::cin >> A >> B;

    if (A < B) {
        std::swap(A, B);
    }
    size_t square_count = 0;
    while (B > 0) {
        square_count += A / B;
        size_t temp = B;
        B = A % B;
        A = temp;
    }

    Print(square_count);
    return 0;
}


