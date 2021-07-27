---
author: "yamate11"
title: "binom(n, r) を小さい素数pに対して mod p で求める"
date: "2021-04-27"
tags: []
categories: ["topic"]
draft: false
---

二項係数 binom(n, r) を，小さい素数 p に対して mod p で求める方法に関する記事です．

## 観察

p = 3 に関していくつか書いてみると次のようになっている．

```
  0                1
  1               1 1
  2              1 2 1
 10             1 0 0 1
 11            1 1 0 1 1
 12           1 2 1 1 2 1
 20          1 0 0 2 0 0 1
 21         1 1 0 2 2 0 1 1
 22        1 2 1 2 1 2 1 2 1
100       1 0 0 0 0 0 0 0 0 1
101      1 1 0 0 0 0 0 0 0 1 1
102     1 2 1 0 0 0 0 0 0 1 2 1
110    1 0 0 1 0 0 0 0 0 1 0 0 1
111   1 1 0 1 1 0 0 0 0 1 1 0 1 1
112  1 2 1 1 2 1 0 0 0 1 2 1 1 2 1
120 1 0 0 2 0 0 1 0 0 1 0 0 2 0 0 1
```

こんな感じの構造になっている:

{{< figure src="fig1.png" width=270em >}}

## 例: p = 3

例として $p = 3$ の場合には，
上の図から，以下のように計算できる．ただし，$q < 3\^k$．

$$
\begin{eqnarray}
%
\binom00 &=& 1
\\\\
%
\binom{3\^k + q}{r} 
&=& 
\begin{cases}
\displaystyle{\binom{q}{r}} & \text{if }\\; 0 \leq r \leq q \\\\
\displaystyle{\binom{q}{r - 3\^k}} & \text{if }\\; 3\^k \leq r \\\\
0 & \text{if }\\; q < r < 3\^k \\\\
\end{cases}
\\\\
%
\binom{2\cdot 3\^k + q}{r} 
&=& 
\begin{cases}
\displaystyle{\binom{q}{r}} & \text{if }\\; 0 \leq r \leq q \\\\
\displaystyle{2\binom{q}{r - 3\^k}} & \text{if }\\; 3\^k \leq r \leq 2\cdot 3\^k + q \\\\
\displaystyle{\binom{q}{r - 2\cdot 3\^k}} & \text{if }\\; 2\cdot 3\^k \leq r \\\\
0 & \text{if }\\; q < r < 3\^k,\\; 3\^k + q < r < 2\cdot 3\^k \\\\
\end{cases}
\\\\
%
\end{eqnarray}
$$


列 $s(n) := [\binom{n}{r} \mid 0 \leq r \leq n]$ が必要ならば，以下のように計算できる．
$$
\begin{eqnarray}
s(0) &=& [1] 
\\\\
s(3\^k + q) &=& s(q) ⧺ z ⧺ s(q) 
\\\\
s(2\cdot 3\^k + q) &=& s(q) ⧺ z ⧺ 2 \cdot s(q) ⧺ z ⧺ s(q) 
\end{eqnarray}
$$
ただし，$z$ は，$0$ を $3\^k - q - 1$ 個並べた列．


## binom(n, r)

一般に，小さい素数$p$ に対しては，以下のようになる．

$n = c\cdot p\^k + q$，$1 \leq c < p$，$q < p\^k$，$r = d\cdot p\^k + t$，$0 \leq d < p$，$t < p\^k$ とすると，

$$
\begin{eqnarray}
\binom{0}{0} &=& 1
\\\\
\binom{n}{r} = 
\binom{c\cdot p\^k + q}{d\cdot p\^k + t} 
&=& 
\begin{cases}
\displaystyle{\binom{c}{d}\binom{q}{t}} & \text{if }\\; 0 \leq t \leq q \\\\
0 & \text{if }\\; q < t \\\\
\end{cases}
\\\\
\end{eqnarray}
$$

$\binom{n}{r}$ の時間計算量は $O(\log n)$．

列 $s(n) := [\binom{n}{r} \mid 0 \leq r \leq n]$ が必要ならば，以下のように計算できる．
記号は上と同様．
$$
\newcommand{\mybinom}[2]{\displaystyle{\binom{#1}{#2}}}
\begin{eqnarray}
s(0) &=& [1] 
\\\\
s(n) = s(c\cdot p\^k + q) 
&=&
\mybinom{c}{0}s(q) ⧺ z ⧺ \mybinom{c}{1}s(q)  ⧺ z ⧺ \cdots ⧺ \mybinom{c}{c}s(q) 
\\\\
\end{eqnarray}
$$
$z$は，$0$ を $p\^k - q - 1$ 個並べた列．
$s(n)$ の時間計算量は $O(n)$．

## AtCoder

AtCoder [ARC117 C - Tricolor Pyramid](https://atcoder.jp/contests/arc117/tasks/arc117_c) で，上の手順が使える．ただし，[解説](https://atcoder.jp/contests/arc117/editorial/1113) の方法の方が思いつきやすいし，(列を求めるだけだから) 計算量は同じ．
