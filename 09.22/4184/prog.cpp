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
    int a, b, c, d;
    std::cin >> a >> b >> c >> d;

    int first = std::abs(c - a);
    int second = std::abs(d - b);
    int gcd = GCD(first, second);
    first /= gcd;
    second /= gcd;
    int answer = (first + second - 1) * gcd;

    Print(answer);
    return 0;
}


