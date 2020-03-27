#include <iostream>

template<int I> 
struct Fib {
	static const long int val = Fib<I-1>::val + Fib<I-2>::val;
};

template<>
struct Fib<0> {
	static const int val = 0;
};

template<>
struct Fib<1> {
	static const int val = 1;
};

int main() {
	std:: cout << Fib<80>::val << std::endl;
}