---
author: "yamate11"
title: "Max Dot -- AtCoder Regular Contest 128 C"
date: "2021-10-29T19:26:39+09:00"
# date_init: "2021-10-29"
tags: []
# categories: ["topic"]
categories: ["solution"]
---

AtCoder Regular Contest 128 (ARC 128) C - Max Dot を解説ACしました．
公式解説より，多少行間が埋まっていると思います．

## 問題概要

```
整数N, M, Sと整数列 A = (A_1, .., A_N) が与えられる．
次の条件を満たす非負実数列 (x_1, ..., x_N) を作る:
・  0 <= x_1 <= x_2 <= ... <= x_N <= M
・  x_1 + x_2 + ... + x_N = S
\sum {A_i × x_i | i = 1, ..., N } の最大値を求めよ．
制約: N <= 5000;  M,S,A_i <= 10^6;  S <= NM;
```

[問題へのリンク](https://atcoder.jp/contests/arc128/tasks/arc128_c)

## 解法

$x_0 := 0$ として，$y_i := x_{i+1} - x_i$ ($i = 0, \ldots, N-1$) とすると，
次のように言い換えられる:

* 求める最大値: $\sum_{i = 0}^{N-1} B_i y_i$．
  ただし，$B_i := \sum_{j = i + 1}^{N} A_j$．
* 満たすべき条件:
  * $y_i \geq 0$
  * $y_0 + \cdots + y_{N-1} \leq M$
  * $N \cdot y_0 + (N-1) \cdot y_1 + \cdots + 1\cdot y_{N-1} = S$


さらに，$z_i := (N - i)\cdot y_i$ とすると，
次のように言い換えられる:

* 求める最大値: $\sum_{i = 0}^{N-1} C_i z_i$．
  ただし，$C_i := B_i / (N - i)$．
* 満たすべき条件:
  * $z_i \geq 0$
  * $\displaystyle\frac{z_0}{N} + \displaystyle\frac{z_1}{N - 1} + \cdots + 
     \displaystyle\frac{z_{N-1}}{1} \leq M$
  * $z_0 + z_1 + \cdots + z_{N-1} = S$

$C_i$ たちの最大値を与える $i$ を $I$ と書く (複数あったら
一番小さいものを取る)．
もし，$\displaystyle\frac{S}{N - I} \leq M$ であれば，
$z_I = S$, $z_i = 0 \\;(i \neq I)$ とすることで，最大値が実現できる．
以下，そうでないとする．

最大値を与える $(x_i)$ を取り，対応する $(y_i)$, $(z_i)$ を取る．
もし，$i > I$ かつ $z_i > 0$ なる
$i$ があったとすると，$z_{I}$ を $z_i$ だけ増やして，$z_i$ を $0$ に変えると，
条件を満たしたまま，値が増加してしまう．したがって，
$i > I$ ならば $z_i = 0$．すなわち，
$x_{I + 1} = x_{I + 2} = \cdots x_{N}$ である．

ここで，$x_{I + 1} < M$ だと仮定する．
$x_1 + \cdots x_I = S - (x_{I + 1} + \cdots x_N) 
= S - (N - I) x_{I + 1} > (N - I) (M - x_{I + 1}) > 0$
であるので，$0 = x_{i-1} < x_i$ となる $i \leq I$ が存在する．
小さな $\varepsilon > 0$ をとって，$x_i$ を $\varepsilon$ 減らし，
$x_{I+1}$ を $\varepsilon$ 増やすことによって，条件を満たしたまま
値を大きくすることができてしまう．したがって，$x_{I+1} = M$ で
なければならない．

以上により，もとの問題は，次の2条件を満たす列において，
$\sum_{i = 1}^{I} A_i x_i$ の最大値を求める問題に帰着された．

* $0 \leq x_1 \leq x_2 \leq \cdots \leq x_I \leq M$
* $x_1 + x_2 + \cdots + x_I = S - M(N - I)$

これを繰り返せば良い．計算量は $O(N^2)$．

## ACコード

[提出](https://atcoder.jp/contests/arc128/submissions/26866202)


