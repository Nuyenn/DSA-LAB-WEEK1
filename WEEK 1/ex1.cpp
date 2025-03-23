#include <iostream>
using namespace std;

int Fibonacci(int n) {
    if (n <= 1) 
        return n;
    return Fibonacci(n - 1) + Fibonacci(n - 2);
}

void printFibonacci(int n, int i = 0) {
    if (i >= n) {
        return;
    }
    cout << Fibonacci(i) << " ";
    printFibonacci(n, i + 1);
}

int main() {
    int x;
    cout << "Nhap so: ";
    cin >> x;
    printFibonacci(x);
    return 0;
}