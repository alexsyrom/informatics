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
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");
    int a, c;
    int b, d;
    input >> a >> b >> c >> d; 

    int numerator = a * d + b * c;
    int denominator = b * d;
    int gcd = GCD(std::abs(numerator), denominator);
    numerator /= gcd;
    denominator /= gcd;
    int integer = std::abs(numerator) / denominator;
    if (numerator < 0) {
        integer = -integer;
    }
    int fraction = std::abs(numerator) % denominator; 
    if (integer == 0 && numerator < 0) {
        fraction = -fraction;
    }

    if (integer != 0) {
        output << integer << ' ';
    }
    if (fraction != 0) {
        output << fraction << '/' << denominator;
    }
    if (integer == 0 && fraction == 0) {
        output << 0;
    }
    return 0;
}


