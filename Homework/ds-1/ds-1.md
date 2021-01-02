# 数据结构与算法 作业1

**2019201409 于倬浩**

### 3.1-3 Explain why the statement, “The running time of algorithm A is at least $O(n^2)$” is meaningless.

$O(n^2)$表示算法的渐进时间复杂度的一个上界是$n^2$级别，然而这句话中“至少”则又想表明算法的时间复杂度下界为$n^2$

因此这句话并没有意义。



### 3.1-7 Prove that $o(g(n)) \cap \omega(g(n))$ is the empty set.

$o(g(n))$表示比g(n)严格高阶的f(n)集合，$\omega(g(n))$表示比g(n)严格低阶的f(n)集合，因此两个集合交集为空。



### 3-3 Ordering by asymptotic growth rates

- ​	a.
    - $2^{2^{n+1}}$
    - $2^{2^n}$  
    - $(n+1)!$
    - $n!$
    - $e^{n}$
    - $n*2^n$
    - $2^n$
    - $(\frac{3}{2})^n$ 
    - $(lgn)^{lgn}$ $n^{lglgn}$
    - $(lgn)!$
    - $n^3$
    - $n^2$
    - $4^{lgn}$
    - $lg(n!)$  $nlgn$
    - $n$  $2^{lgn}$ 
    - $\sqrt{2}^{lgn}$
    - $2^{\sqrt{2lgn}}$
    - $lnn$  $lg^2n$  
    - $\sqrt(lgn)$
    -  $ln(lnn)$ 
    - $2^{lg^*n}$
    - $lg^*(lgn)$ $lg^*n$ 
    -   $lg(lg^*n)$ 
    - $1$  $n^{\frac{1}{lgn}}$
- b.
    - $ \begin{equation} f(n)=\left\{ \begin{aligned} n^n (n = 2k) \\ 0 (n = 2k+1)\\\end{aligned} \right. \end{equation}$



### 3-4 Asymptotic notation properties

1. False
2. False
3. True
4. False
5. False
6. True
7. False
8. True



### 3-6 Iterated functions

1. n
2. $log^*n$
3. $log_2(n)$
4. $log_2(n)-1$
5. $log_2(log_2(n))$
6. $\infty$
7. $log_3(log_2(n))$
8. $o(log_2n)$

