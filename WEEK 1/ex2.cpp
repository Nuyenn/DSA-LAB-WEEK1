#include <iostream> 
using namespace std;

int factorial(int n) {
	if (n == 0 || n == 1) {
		return 1;
	}
	return n * factorial(n - 1);
}

int main() {
	int k;
	cout << "Nhap so: ";
	cin >> k;
	long long S = factorial(k);
	cout << S << endl;
	return 0;
}