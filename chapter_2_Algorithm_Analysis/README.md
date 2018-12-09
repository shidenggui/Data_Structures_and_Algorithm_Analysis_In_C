# Chapter 2: Algorithm Analysis

主要介绍一些算法分析的基本概念。

## 2.1 Mathematical Background

介绍了 O(f(N))、o(f(N))、\sigma(f(N)) 的定义和之间的区别。

* O(f(N)): 上界
* o(f(N)): 下界
* \sigma(f(N)): 如果 O(f(N)) 和 o(f(N)) 相同，则可以用 \sigma(f(N)) 来代替。

实际中常用 O(f(N)) 比较多。

相关的常用结论:

* log^kN = O(N) for any constant. 也就是说 logorithms 的增长率非常慢。
* T_1(N) + T_2(N) = max(O(f(N), O(g(N))):  相加时取最大的即可，因为当 N 值非常大时，较小的可以忽略
* T_1(N) * T_2(N) = O(f(N) * g(N)) : 常用与与循环结合计算该循环的复杂度

## 2.2 Model

介绍了用于算法分析的计算机模型，相比《算法导论》中的假设更为宽松，此模型中所有操作都花费相同的常量操作时间。

## 2.3 What to Analyze

时间复杂度高的算法不一定跑得慢，这还取决于 N 的大小。

## 2.4 Running Time Calculations

为了简化分析过程，通常只考虑 Big-Oh，程序可能跑得比 Big-Oh 快，但绝不可能比他慢。

### 2.4.2 General Rules

* Rule1: For loops

The running time of a for loop is at most the running time of the statements inside the for loop (including tests) times the number of iterations.


对 for 循环而言：for 循环的运行时间最多为 for 循环内的代码的运行时间(包含判断) * 迭代次数。

* Rule2: Nested for loops

Analyze these inside out. The total running time of a statement inside a group of nested loops is the running time of the statement multipied by the product of the sizes of all the for loops.


对嵌套的 for 循环：从里向外分析。对在一组嵌套循环中的代码语句的运行时间是该代码的运行时间 * 所有 for 循环的次数

* Rule 3: Consecutive statements

These just add(Which mean that the maximum is the one that counts)


对连续的代码：只要把他们的时间复杂度相加就可以了（也意味着只要考虑其中最大的时间复杂度就可以了）。


* Rule 4: if/else statement

the running time of an if/else statement is never more than the running time of the test plus the larger of the running times of S1 and S2.


if/else 的运行时间为子语句中的运行最大的值。(这个很好理解)


下面举了一个分析递归求斐波那契数列第 N 项的算法复杂度的例子，而这个例子就是我之前曾经面试过的一家公司问我的问题，当时的我如此懵懂，对此一问三不知。

```c
long int fib(int n) {
    if (n <= 1)
        return 1;
    return fib(n - 1) + fib(n - 2);
}
```

对于 n 为 0 和 1 时，运行时间为常量。


而对 n > 2 时，运行时间则为 T(n) = T(n - 1) + T(n - 2) + 2


这里额外的 2 来自于 if 判断和 `fib(n - 1) + fib(n - 2)` 的相加操作。


而这里如何分析该式的复杂度呢，作者使用了一个非常巧妙的转换。


因为 fib(n) = fib(n - 1) + fib(n - 2)


所以 T(n) 必然比 fib(n) 稍大，而 fib(n) >= (3/2)^n (n > 4，证明可以用数学归纳法) ，所以 T(n) 必然是指数级的算法复杂读，原文称之为 grows exponentially.


书里面提到 fib 是使用递归非常糟糕的例子，可以通过使用循环来达到 O(N) 的时间复杂度。相关实现附在 chapter_2_Algorithm_Analysis/fib.c 中


## 2.4.3 Solutions for the Maximum Subsequence Sum Problem

这个小节非常精彩。将算法的优雅和强大彰显的淋漓尽致。

### Maximum Subsequence Sum Problem

是指给出一个由整数构成的序列，找出其连续子序列和的最大值(不考虑溢出的情况)。


例如给出 [1, -2, 3, 4, -8] 则此时使连续子序列和取得最大值的序列为 [3, 4]，最大值为 7。


这道题我记得我在校招的时候遇到过，当时的我完全不知道如何求解该问题，后来才知道这是非常经典的一道面试题。


作者这里还附加了一个条件，如果连续子序列和的最大值小于 0， 则返回 0。


### 那如何求解呢？


作者首先给出的是暴力求解法，这也是一般最简单的思路，列出所有的连续子序列和，然后找出其中的最大值就好来。


实现如下:

```c
int max_subsequence_sum(int *arr, int length) {
    int max_sum = 0;
    for (int i = 0; i < length; i++) {
        for (int j = i; j < length; j++) {
            int sum = 0;
            for (int k = i; k <= j; k++) {
                sum += arr[k];
            }

            if (sum > max_sum)
                max_sum = sum;
        }
    }
    return max_sum;
}
```

三重循环，经分析可知算法复杂度为 O(N^3)。


#### 第一次优化: 移除不必要的循环

第一版中的每次在 j + 1 后都要重新计算 i 到 j 之间的数组和，其实没有必要，只要提前保存好 i 到 j 之间的数组和，在 j + 1 后加上 arr[j + 1] 的值即可，这样就可以消除掉一层循环，代码如下:


```c
int max_subsequence_sum(int *arr, int length) { int max_sum = 0;
    for (int i = 0; i < length; i++) {
        int sum = 0;
        for (int j = 0; j < length; j++) {
            sum += arr[j];

            if (sum > max_sum)
                max_sum = sum;
        }
    }
    return max_sum;
}
```

两重循环，算法复杂度降为 O(N^2)。



#### 第二次优化: divide and conquer 分治法

在实际情况中，一般来说 O(N^2) 的算法复杂度在 N 取较大值时运行时间会难以接受。


那有没有更好的方法呢，作者说是有的，这时引入了一种新的思考方式，`divide and conquer` ，也即分治法。

* divide: 指将问题分成两个大概相等的子问题，然后递归的解决它们。
* conquer: 将子问题的解决方案拼接到一起，可能还需要额外做一些小工作以获得对整个问题的解。


考虑如果存在连续子序列和为最大值的序列 S 的话，则 S 要么位于该序列的左半部分，要么位于该序列的右半部分，要么横跨序列的中点。对于位于左右两边的情况，可以通过递归解决，如果位于中间的话，则可以通过分别求出两边和的最大值相加得出中间序列的最大值。然后再这三个值中取最大值就是整个序列的连续子序列和最大值了。

```c
int max3(int a, int b, int c) {
    if (a > b && a > c)
        return a;
    if (b > c)
        return b;
    return c;
}

int max_sub_sum(int *arr, int left, int right) {
    if (left == right) {
        if (arr[left] > 0)
            return arr[left];
        return 0;
    }

    int mid = left + (right - left) / 2;
    int max_left_sub_sum = max_sub_sum(arr, left, mid);
    int max_right_sub_sum = max_sub_sum(arr, mid + 1, right);

    int max_left_sum = 0;
    int left_sum = 0;
    for (int i = mid; i >= left; i--) {
        left_sum += arr[i];
        if (left_sum > max_left_sum)
            max_left_sum = left_sum;
    }
    int max_right_sum = 0;
    int right_sum = 0;
    for (int i = mid + 1; i <= right; i++) {
        right_sum += arr[i];
        if (right_sum > max_right_sum)
            max_right_sum = right_sum;
    }

    int max_cross_sum = max_left_sum + max_right_sum;
    return max3(max_left_sum, max_right_sum, max_cross_sum);
}

int max_subsequence_sum(int *arr, int length) {
    return max_sub_sum(arr, 0, length - 1);
}
```


明显分治法需要多的多的代码，但是作者也加了一句评注 "shorter code does not always mean better code"(不过后面的算法又推翻了这个结论，看来长的代码不一定比短的代码差，但能好多少也值得商榷)。


对该算法的分析如下:

```
T(1) = 1 // base cases
T(N) = 2T(N/2) + O(N)
```

这里作者说具体的分析被推迟到第七章(这种证明方法不经让人想到 proof by intimidation)，他代入了几个值，然后表示这个算法大概近似 O(N logN)。

### 还有吗？

很难让人相信还有比 `O(N logN)` 更好的算法来解决这样一个看似复杂的问题。但确实是有的，不由得让人感叹人的聪明才智。而且仅仅需要 `O(N)` 的复杂度和 O(1)  的空间复杂度，同时代码量也非常少，易于实现。这简直就是所谓的完美算法。

算法实现如下:


```c
int max_subsequence_sum(int *arr, int length) {
    int max_sum = 0;
    int sum = 0;
    for (int i = 0; i < length; i++) {
        sum += arr[i];
        if (sum > max_sum)
            max_sum = sum;
        else if (sum < 0)
            sum = 0;
    }
    return max_sum;
}
```

书里面并没有提供对该算法的解释，而且作者这里合并了一些条件选项，导致我一开始没看懂什么意思，后面是去 wiki 看了相关的解释才明白。


分析如下：


假设序列为 A，总共包含 N 个元素。构成连续最大子序列和的序列为 S，则该序列一定是以数组中某一个元素结尾，此时我们只需要遍历该序列，找出以当前元素作为最后结尾的连续子序列的最大和，然后比较数组中所有以该方式找出的序列和，求出最大值即可。


关键就是如何`找出以当前元素作为最后结尾的连续子序列的最大和`? 这里就涉及到一些非常巧妙的思考。


假设当前元素下标为 i，以该下标结尾的连续子序列和最大值只有两种情况：

* 该元素本身
* 以 i - 1 结尾的元素的最大值加上该元素本身


取这两者中的最大值既可。作者附加了小于 0 取零，此时在这三者中取最大值即可。


而`以 i - 1 结尾的元素的最大值`正好可以复用之前的结果，所以整体算法为 `O(N)`, 而且只需要额外的两个变量存储全局最大值和以当前下标结尾的序列最大值即可。


我能说什么呢？第一次看到整个分析，拍案叫绝，将代码的简洁跟数学的优雅完美无缺的结合在一起，淋漓尽致的展现着人类智慧的智慧光芒。


最后的算法被称为 "Kadane's algorithm"，它值得拥有一个名字。


```
山穷水尽疑无路，柳暗花明又一村
```

### on-line algorithm

"Kadane's algorithm" 这种空间复杂度为 O(1) 而时间复杂度为 O(N) 的算法被称为 "on-line algorithm"。


对某个问题的 "on-line" 算法解就算不是最好，也是最好的几种算法解之一了。


## 2.4.4  Logarithms in the Running Time

主要介绍了几种算法复杂度为 O(LogN) 的算法。

### 如何判断一个算法是 O(N) 还是 O(LogN) ?

An algorithm is O(LogN) if it takes constans O(1) time to cut the problem size by fraction(which is usually 1/2). On the other hand, if constant time is required to merely reduce the problem by a constant amount, then the algorihtm is O(N).


简单来说，就是如果一个算法在其运算过程中，只需要花费常量的 O(1) 时间将问题减少为原问题的一部分(通常是 1/2)，而不是只减少常量的数量，则这个算法是 O(LogN) 的，因为问题再按指数级缩小，而指数函数的反函数就是 Logarithm。


反之，如果在运算过程中需要常量的时间而仅仅只能将问题减少常量的一部分，则该算法是 O(N) 的。


而且作者这里排除了读取数据所花的时间，因为不管怎么样，读取 N 份数据都需要 O(N) 的时间。


这样想的话其实 O(LogN) 的算法是很少的，一般我只能想到 binary search, 而作者在后文中除此之外又介绍了另外两种算法，令人大开眼界。


#### O(LogN) 算法之一: binary search


这个算法应该不用多说了，每次判断都可以减少 1 / 2 的检索量。

代码实现如下:

```c
int binary_search(int *arr, int n , int k) {
    int center; // 预先声明变量，防止在循环中不断创建影响性能
    int left = 0;
    int right = n - 1;
    while (left <= right) {
        center = left + (right - left) / 2; // 防止溢出
        if (arr[center] > k) {
            right = center - 1;
        } else if (arr[center] < k) {
            left = center + 1;
        } else { // == 判断放最后，因为这个遇到的频率最低
            return center;
        }
    }
    return -1;
}
```

作者具了一个应用的例子，用于在元素周期表中检索对应的元素，这个例子有点牵强。


#### O(LogN) 算法之二: Euclid's Algorithm


又称之为碾转相除法，用于求解两个数的最大公约数。这个算法相信大家都学过，但是应该从来没人分析尝试过分析它的算法复杂度吧，而它也属于 O(LogN) 家族中的一员。


代码实现如下:

```c
int GCD(int m, int n) {
    int remainder; //预先声明所用变量，防止在循环中不断创建影响性能。
    while (n > 0) {
        remainder = m % n;
        m = n;
        n = remainder;
    }
    return m;
}
```

证明过程:

作者首先提出一条定理:

```
If M > N, then M mod N < M/2.
```

证明:

* 当 N < M/2 时，因为 M mod N 一定小于 N，所以 M mod N < M/2
* 当 N > M/2 时，因为 M > N 所以 M mod N = M - N < M/2

这时我们可以知道 remainder 第一次至多为 m 的一半, 第二次至多为 n 的一半，后面则以最少 1/2 的速度递减。所以可以表明该算法的复杂度为 O(LogN)。

#### O(LogN) 算法之三: Exponentiation

如何高效的计算指数幂？这便是该算法想要解决的。

对 X 的 N 次方来说，我们可以区分为如下两种情况:
* N 为 偶数, 令 N = 2k，则 X^(2k) = X^k * X^k = (X^2) ^ k
* N 为 奇数，令 N = 2k + 1，则 X^(2k + 1) = X^k * X^k * x = (X^2) ^ k * x

可以看到，我们最多只需要两次计算就可以将 X^N 的指数降为原来的一半。

代码实现如下:

```c
int power(int x, int n) {
    if (n == 0)
        return 1;
    if (n % 2)
        return exp(x * x, n / 2) * x;
    return exp(x * x, n / 2);
}
```

## 2.4.5 Checking your analysis

在作出对算法复杂度的分析后，如何确定你的分析是否正确呢，尤其是在实际情况下?

作者这里首先提出了一种我们通常使用的方法，也就是运行你的程序，然后逐渐增大程序输入 N（通常是 double），然后观察程序的运行时间。


如果程序是 O(N) 的话，则运行时间应该呈线性，O(N^2) 的话运行时间应该呈 N^2 变化，依次类推，但是这种方式也有一些局限性。


1. 很难区分 O(N) 和 O(N * LogN) 因为 LogN 的增长是在太慢了。
2. 当 N 很小而且影响算法的低阶项的系数比较大时，时间检测会不太准。
3. 还有一种是当算法复杂度太高时，比如 O(N^10)，double 一下 N 需要多出 1024 倍的运行时间，这在现实中是难以接受的。


而且一般直接观察程序输入 N 和运行时间之间的关系比较不直观，所以作者提出了一种更为实用的方法来判断算法复杂度，是基于上述方式的变种。

假设某些程序具有 O(f(N)) 的复杂度，则用它的运行时间 T(N)/O(f(N))，当 N 足够大时:


1. 如果 T(N)/O(f(N)) 收敛到一个常数，则说明 f(N) 是一个比较近似的算法复杂度，
2. 如果趋向增大，则说明实际的算法算法度比 f(N) 更高
2. 如果趋向减少，则说明实际的算法算法度比 f(N) 更低。

然后作者举了一个示例程序：从 1 到 N 之间随机选取两个值，他们互质的概率为多少？


代码示例如下:

```c
unsigned int gcd(unsigned int m, unsigned int n) {
    int rem = 0;
    while (n > 0) {
        rem = m % n;
        m = n;
        n = rem;
    }
    return m;
}

double relative_prime_percent(int n) {
    int total = n * n;
    int rel = 0;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            if (gcd(i, j) == 1)
                rel++;
        }
    }
    return total * 1.0 / rel;
}
```


该算法的复杂度因为有 2 重循环，而且 gcd 的复杂度为 LogN，所以整体的算法复杂度为 O(N^2 * LogN)。


然后应用作者的方法我们观察程序的运行时间并逐渐增大 N，可以得到以下输出，具体代码位于 chapter_2_Algorithm_Analysis/relative_prime_percent.c 中:


```shell
output in my computer:
number:    100 percent: 0.608700 time:     501   T(N)/N:   5.010000   T(N)/N^2:   0.050100   T(N)/N^3:   0.000501   T(N)/(N^2LogN):   0.010879
number:    200 percent: 0.611575 time:    2129   T(N)/N:  10.645000   T(N)/N^2:   0.053225   T(N)/N^3:   0.000266   T(N)/(N^2LogN):   0.010046
number:    400 percent: 0.608469 time:    9261   T(N)/N:  23.152500   T(N)/N^2:   0.057881   T(N)/N^3:   0.000145   T(N)/(N^2LogN):   0.009661
number:    800 percent: 0.608592 time:   41132   T(N)/N:  51.415000   T(N)/N^2:   0.064269   T(N)/N^3:   0.000080   T(N)/(N^2LogN):   0.009614
number:   1600 percent: 0.607993 time:  176895   T(N)/N: 110.559375   T(N)/N^2:   0.069100   T(N)/N^3:   0.000043   T(N)/(N^2LogN):   0.009366
number:   3200 percent: 0.608060 time:  812594   T(N)/N: 253.935625   T(N)/N^2:   0.079355   T(N)/N^3:   0.000025   T(N)/(N^2LogN):   0.009832
number:   6400 percent: 0.607980 time: 3523889   T(N)/N: 550.607656   T(N)/N^2:   0.086032   T(N)/N^3:   0.000013   T(N)/(N^2LogN):   0.009817
```


可以看到 T(N)/T(N^2 * LogN) 趋于稳定，而其他不是趋向增大就是趋向缩小。


## 2.4.6 A Grain of Salt

这个章节名一开始不明所以，后面查了下才知道是一个俚语，意为对某些事情将信将疑。因为我们之前的算法复杂度分析都是基于 O(f(N))，也就是最坏情况，而这往往会高估实际的算法复杂度。因为在现实情况中，最坏的情况可能根本不会发生，而平均运行复杂度因此远远小于 O(f(N))。又或者我们之前的 O(f(N)) 高估的太多，以至于在实际中根本没那么高的复杂度。

但是要准确计算 \sigma(f(N)) 以及算法的平均运行复杂度也过于复杂，所以实践中还是往往以 O(f(N)) 为主。

## summary

这章介绍了一些算法分析的基本概念。然后通过对 Max Subsequence Sum 问题的求解和优化来示例如何进行算法分析，非常精彩。我记得我大学毕业校招的时候笔试就曾经遇到过这个问题，当时完全是两眼一抹黑，现在想想这就是文盲的感觉吧。


然后作者介绍了一些 O(LogN) 的算法，包括 binary search、gcd、exponentiation。感觉很神奇，尤其是对 gcd 的算法分析。gcd 很早就在数学上学习过，但是从来没想过它到底需要多少次运算的问题，非常巧妙的分析，算法分析教我们从一些从没有过的视角观察以前学过的一些数学知识，非常有趣。


最后作者解释了为什么一般只考虑 O(f(N))，因为其他的算法复杂度分析往往太过复杂，这点我们在后面可以看到。

## Exercise

## 2.7 给出一个数 N，如何对前 N 个自然数生成一个随机排序？

这里用到了经典的 Fisher-Yates shuffle algothrim，该算法可以在 O(N) 时间内随机生成一个有限序列的随机组合。

```c
void shuffle(int *arr, int n) {
    for (int i = 0; i < n - 1; i++)
        // rand_int(i, n) produce value between [i, n)
        swap(&arr[i], &arr[ rand_int(i, n) ]);
}
```

书里面的实现每次 rand_int 都是取得 `rand_int(0, i)`, 跟 wiki 的实现有点差别，具体可见 [wiki](https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle)
