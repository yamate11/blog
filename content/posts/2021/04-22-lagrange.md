---
author: "yamate11"
title: "Lagrange補間"
date: "2021-04-22"
tags: []
categories: ["topic"]
draft: false
---
Lagrange補間に関する記事です．

## 要約

$$
f(x) = \sum_{i = 0}^{k}\frac{ f(i) }{  (-1)^{k - i} \\; i ! \\; (k - i) !  }
          \cdot \frac{ 1 }{ x - i } \cdot \prod\_{j=0}\^{k} ( x - j )
$$

## 詳細

\\( k \\) 次多項式 $f(x)$ について，$x = 0, \ldots, k$ の値が，$f(0) = v_0, \ldots, f(k) = v_k$ と分かっているときに，
$f(x)$ (の各係数) を決める方法．
連立方程式を解く方法だと，逆行列を計算する必要があるから，\\( \Omega( k^3 ) \\) になってしまうが， 
Lagrange補間だと，$O(k\^2)$ で済む．

$I = \\{0, \ldots, k\\}$, 
$I_i = I \setminus \\{ i \\}$ とする．$i = 0, \ldots, k$ について，$k$ 次の多項式 $g_i(x)$ を，
次で定義する．

$$g_i(x) = \frac{ \prod \\{ x - j \mid j \in I_i \\} }{  \prod \\{  i - j \mid j \in I_i \\}  } 
$$

$j = 0, \ldots, k$ について，

$$ g_i (j) = \begin{cases}
  1 & \text{ if } i =j \\\\
  0 & \text{ if } i \neq j
\end{cases}$$

であることに注意すると，

$$ f(x) = \sum_{i = 0}^{k} g_i(x)v_i $$

となることがわかる (左右両辺とも $k$ 次多項式で，$k+1$ 個の値が一致する)．

$ g_i(x) $ の分母を $c_i$ と書くと，

$$ c_i = (-1)^{k - i} \\; i ! \\; (k - i) ! $$

であるから，これらは，事前に $k$ までの階乗を $O(k)$ で計算しておけば，$O(1)$ で求められる．

$g_i(x)$ の分子は，

$$
\frac{1}{x - i}\cdot\prod\_{j=0}^{k} (x-j)
$$

であるから，まず $\prod\_{j=0}^{k} (x-j)$ を $O(k\^2)$ で計算しておけば，各$i$について$O(k)$で，全体で$O(k\^2)$で
計算できる．

## AtCoder

AtCoder [ABC137 F - Polynomial Construction](https://atcoder.jp/contests/abc137/tasks/abc137_f) は，
Lagrange補間を用いて解ける．
ただし，[解説](https://img.atcoder.jp/abc137/editorial.pdf) に書かれている方法の方が簡単．
