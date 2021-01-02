# 数据结构与算法I 思考题6

**2019201409 于倬浩**

## 12-4

+   a.

    设$b_i$表示由`i`个节点构成的本质不同的二叉树的数量。两棵二叉树本质不同，当且仅当两棵树根节点的左子树或右子树的结构本质不同。

    因此，假设我们当前计算$b_n$，只需枚举左子树的大小$i$，那么右子树的大小为$n-1-i$，而左右子树各自的构造方案数为$b_i$和$b_{n-1-i}$，根据乘法原理，只需两项相乘即可。

    因此有$b_n=\sum_{i=0}^{n-1}b_ib_{n-1-i}$，边界条件$b_0=1$。



+   b.

    $xB(x)^2+1 \\ = 1 + x \sum_{n=0}^{\infty} x^n \sum_{i=0}^{n}b_i b_{n-i} \\ = 1 + \sum_{n=1}^{\infty}b_i b_{n-1-i} x^n \\ = B(x)$

    将这个式子视为一个二次方程：$xB(x)^2-B(x)+1=0$，则一组可行解即为$B(x)=\frac{1-\sqrt{1-4x}}{2x}$

    代入验证：

    $xB(x)^2-B(x) + 1 = x  \frac{(1-\sqrt{1-4x})^2}{4x^2} - \frac{1-\sqrt{1-4x}}{2x} + 1 \\ = \frac{1-2\sqrt{1-4x}+1-4x-2+2\sqrt{1-4x} + 4x}{4x} \\ = 0$

    即上述结果可以使得等式成立。



+   c. 

     $B(x) = \frac{1}{2x}(1 - \sqrt{1-4x})$
    
     $\sqrt{1-4x} = \sum_{i=0}^{\infty} x^i \frac{(-4)^i(\frac{1}{2}(\frac{1}{2} - 1) (\frac{1}{2} - 2) ...(\frac{1}{2} - (i-1)))}{i!} \\ = \sum_{i=0}^{\infty} x^i \frac{-(2(2-1*4)(2-2*4)...(2-(i-1)*4)) }{i!} \\ = 1 - \sum_{i=1}^{\infty}\frac{x^i}{i!} \prod_{j=0}^{i}2(2j-1) \\ = 1 - \sum_{i=1}^{\infty} \frac{2^i(2(i-1))!}{2^{i-1}(i-1)!}  \frac{x^i}{i!} \\ = 1 - \sum_{i=1}^{\infty} \frac{2(2(i-1))!}{(i-1)!i!} x^i $
    
    
    
    $B(x) = \frac{1}{2x}(1 - \sqrt{1-4x}) = \frac{1}{2x} \sum_{i=1}^{\infty} \frac{2(2(i-1))!}{(i-1)!i!} x^i \\ = \sum_{i=0}^{\infty} \frac{(2i)!}{(i+1)!i!} x^i \\ = \sum_{i=0}^{\infty} \frac{1}{i+1} \frac{(2i)!}{i!i!} x^i \\ = \sum_{i=0}^{\infty} \frac{1}{i+1} \binom{2i}{i} x^i $
    
    
    
    $\therefore b_i = \frac{1}{i+1} \binom{2i}{i}$
    
    
    
+   d.

    由斯特林公式：

    $b_n \approx \frac{\sqrt{4\pi n} (\frac{2n}{e})^{2n}}{2\pi n (\frac{n}{e})^{2n}} \frac{1}{n+1} \\ = \frac{4^n}{\sqrt{\pi n}(n+1)} \\ = \frac{4^n}{\sqrt{\pi} n^{\frac{3}{2}}} (1 + O(\frac{1}{n}))$

    即得证。