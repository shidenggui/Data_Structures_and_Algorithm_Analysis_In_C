/*
 * the program fragment computes the probability that two distinct positive integers, less than or equal to N and chosen randomly, are relatively prime 
*/
#include <stdio.h>
#include <time.h>
#include <math.h>

// when m < n, algorithm will swap them in first iteration.
unsigned int gcd(unsigned int m, unsigned int n) {
    int rem = 0;
    while (n > 0) {
        rem = m % n;
        m = n;
        n = rem;
    }
    return m;
}

double relative_prime_percent(unsigned int n) {
    int total = n * n;
    int rel = 0;
    for (unsigned int i = 1; i <= n; i++) {
        for (unsigned int j = 1; j <= n; j++)
            if (gcd(i, j) == 1)
                rel++;
    }
    return rel * 1.0 / total;
}

void test_relative_prime_percent() {
    int size = 100;
    for (int i = 1; i <= 64; i *= 2) {
        unsigned int n = i * size;
        clock_t start = clock();
        double percent = relative_prime_percent(n);
        double use = (double)(clock() - start) * 1000000 / CLOCKS_PER_SEC;
        printf("number: %6d percent: %f time: %7.0f   T(N)/N: %10f   T(N)/N^2: %10f   T(N)/N^3: %10f   T(N)/(N^2LogN): %10f\n", 
                n, percent, use, use / n, use / n / n, use / n / n / n, use / n / n / log(n));
    }
}

/*
 * output in my computer:
number:    100 percent: 0.608700 time:     501   T(N)/N:   5.010000   T(N)/N^2:   0.050100   T(N)/N^3:   0.000501   T(N)/(N^2LogN):   0.010879
number:    200 percent: 0.611575 time:    2129   T(N)/N:  10.645000   T(N)/N^2:   0.053225   T(N)/N^3:   0.000266   T(N)/(N^2LogN):   0.010046
number:    400 percent: 0.608469 time:    9261   T(N)/N:  23.152500   T(N)/N^2:   0.057881   T(N)/N^3:   0.000145   T(N)/(N^2LogN):   0.009661
number:    800 percent: 0.608592 time:   41132   T(N)/N:  51.415000   T(N)/N^2:   0.064269   T(N)/N^3:   0.000080   T(N)/(N^2LogN):   0.009614
number:   1600 percent: 0.607993 time:  176895   T(N)/N: 110.559375   T(N)/N^2:   0.069100   T(N)/N^3:   0.000043   T(N)/(N^2LogN):   0.009366
number:   3200 percent: 0.608060 time:  812594   T(N)/N: 253.935625   T(N)/N^2:   0.079355   T(N)/N^3:   0.000025   T(N)/(N^2LogN):   0.009832
number:   6400 percent: 0.607980 time: 3523889   T(N)/N: 550.607656   T(N)/N^2:   0.086032   T(N)/N^3:   0.000013   T(N)/(N^2LogN):   0.009817
*/
int main() {
    test_relative_prime_percent();
}
