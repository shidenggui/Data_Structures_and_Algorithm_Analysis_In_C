#include <assert.h>

// n >= 0
int fib(int n) {
    if (n <= 1)
        return 1;
    return fib(n - 1) + fib(n - 2);
}

// n >= 0
int fib_directly(int n) {
    if (n <= 1)
        return 1;

    int n_minus_1  = 1;
    int n_minus_2 = 1;
    int result = 0;
    for (int i = 2; i <= n; i++) {
        result = n_minus_1 + n_minus_2;
        n_minus_2 = n_minus_1;
        n_minus_1 = result;
    }
    return result;
}
// fib sequence: 1 1 2 3 5 8 13 21
void test_fib() {
    assert(fib(0) == fib_directly(0));
    assert(fib(1) == fib_directly(1));
    assert(fib(2) == fib_directly(2));
    assert(fib(3) == 3);
    assert(fib(3) == fib_directly(3));
    assert(fib(7) == 21);
    assert(fib(7) == fib_directly(7));
}

int main() {
    test_fib();
}






