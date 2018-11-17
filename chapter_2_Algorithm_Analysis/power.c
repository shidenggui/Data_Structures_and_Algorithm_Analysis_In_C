#include <assert.h>

int power(int x, int n) {
    if (n == 0)
        return 1;
    if (n % 2)
        return power(x * x, n / 2) * x;
    return power(x * x, n / 2);
}

void test_power() {
    assert(power(0, 0) == 1);
    assert(power(1, 0) == 1);
    assert(power(2, 1) == 2);
    assert(power(2, 2) == 4);
    assert(power(2, 3) == 8);
    assert(power(2, 10) == 1024);
}

int main() {
    test_power();
}
