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


明显分治法需要多的多的代码，但是作者也加了一句评注 "shorter code does not always mean better code"(不过后面的算法又推翻了这个结论，看来长的代码不一定比短的代码差，但能好多少也值得商榷)


对该算法的分析如下:

```
T(1) = 1 // base cases
T(N) = 2T(N/2) + O(N)
```

这里作者说具体的分析被推迟到第七章(这种证明方法不经让人想到 proof by intimidation)，他代入了几个值，然后表示这个算法大概近似 `O(N logN)。

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

