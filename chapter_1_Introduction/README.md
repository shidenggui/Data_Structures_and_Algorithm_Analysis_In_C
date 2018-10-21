# Chapter 1: Introduction

这章节主要复习了一些算法分析需要的一些基础数学知识。

## 1.1 What's the Book About?
 
主要谈了下为什么要学习算法？因为有时候仅仅一个能够 work 的算法实现不够好，或者说在生产环境中不可用。

遗憾的是我目前的工作很多时候仅仅需要一个能够 work 的解决方案就够了，算法的魅力只有在受限的条件下才能得以最大程度的展现。

## 1.2 Mathematics Review

介绍了一些数学基本概念，包括 Exponents、Logarithms、Series、Modular Arithmetic。

目前我不太熟悉的定理:

$$\sum_{i=0}^{N}2^i = 2^{N+1} - 1$$

以及对应的推广:

$$\sum_{i=0}^{N}A^i = \frac{A^{N+1} - 1}{A - 1}$$

用于预估循环复杂度的:

$$\sum_{i = 1}^{N}i^k \approx\frac{N^{k + 1}}{|k + 1|}(k \neq -1)$$

当 k = -1 时对与 Hormonic Series 的预估:

$$H_N = \sum_{i = 1}^{N}\frac{1}{i} \approx log_eN$$

此时误差逐渐逼近 

$$\gamma \approx 0.57721566 (which\ known's\ as\ Euler's\ constant)$$

同时介绍了一个新的取模符号:

$$ A \equiv B \pmod N (if\ N\ divides\ A - B)$$

### 1.2.5 The P word

介绍了几种证明数学定理的方法，主要包括 Proof By Induction(可以用来思考代码循环的逻辑是否正确，类似算法导论中提到的 Loop Invariant)，Proof by Counterexample(编写完代码后代入简单的测试用例)，Proof By Contradiction。
最后还略带风趣的提到了 [Proof by Intimidation](https://en.wikipedia.org/wiki/Proof_by_intimidation)。

### 1.3 A Brief Introduction to Recursion

简单介绍了递归是什么，以及理解和编写递归代码的几条原则。

#### What's recursion?

A function that is defined in terms of itself is called *recursive*.

即在函数定义过程中涉及到自身的函数被称为是递归的。

#### Four basic rules of recursion

1. Base Cases. You must always have some base cases, which can be solved without recursion. (如果没有 base Cases 的话，递归将陷入死循环而不知道如何结束，最后导致 stack overflow)
2. Making progress. For the cases that are to be solved recursively, the recursive call must always be to a case that makes progress toward a base case.
2. 取得进展。对于那些需要递归解决的实例，递归调用必须使它转化为更接近基本实例的递归调用。(否则也有可能陷入死循环)
3. Design Rule. Assume taht all the recursive calls work.
3. 设计原则。假设所有的递归调用都能够正常工作。(类似与 Induction，假设第 k 次是成立的，这可以大大减少思考递归的心智负担，不光是在设计递归代码时，用于编写相关代码后思考递归代码的正确性也非常有益)
4. Compound interest rule. Never duplicate work by solving the same instance of a problem in separate recursive calls.
4. 复利原则. 绝对不要在不同的递归调用中解决相同的子问题。（斐波那契数列的递归实现就是最好的例子)

据作者而言，只要你时时将这几条关于递归的原则牢记脑海，那 recursive programming should be straightforward. 希望如此。

## References

里面介绍了很多好书。主要包括以下几类

* 数学相关的基础知识: 主要是关于 Discrete Mathematics 。
* 算法分析: TAOCP、《The Science of Programming  等。
* 编程相关的书:《A Discipline to Programming》、《The Elements of Programming Style》等。

突然感觉自己在编程领域还是个文盲，不过这反过也是一件幸事，还有那么多有趣的东西等待我发现，而我也可以在这个过程中充分享受并沐浴在前人智慧的结晶下。
