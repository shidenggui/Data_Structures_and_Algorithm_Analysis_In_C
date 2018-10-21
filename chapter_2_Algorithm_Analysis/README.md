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

连续的代码语句：These just add




