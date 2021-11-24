---
author: "yamate11"
title: "AtCoder Beginner Contest 221 H - Count Multiset"
date: "2021-11-24T19:31:33+09:00"
# date_init: "2021-11-24"
tags: ["分割数", "DP"]
# categories: ["topic"]
categories: ["solution"]
summary: "解説ACです．"
---

AtCoder Beginner Contest 221 - ABC 221 H - Count Multiset の解法です．
解説ACです．
[noshi91さんの解説](https://atcoder.jp/contests/abc221/editorial/2738) 
をなぞっただけのものです．

## 問題概要

[問題へのリンク](https://atcoder.jp/contests/abc221/tasks/abc221_h)

正整数 $N$, $M$ が与えられる．
$k = 1, 2, \ldots, N$ について，
$N$ の サイズ $k$ の分割で，多重度が $M$ 以下のものの個数，
すなわち，以下を満たす多重集合 $A$ の個数を，
mod 998244353 で求めよ．

* $|A| = k$
* $\sum A = N$
* 任意の正整数 $x$ について，$A$ に含まれる $x$ の個数は $M$ 以下．

制約: $1 \leq M \leq N \leq 5000$


## 解法

$k, n \in [1, N]$ に対して，次のように定義する:

* $S(k, n)$: $n$ のサイズ $k$ の分割で，多重度が $M$ 以下のもの全体
* $T(k, n)$: $S(k, n)$ のうち，最小要素が 2 以上のもの全体
* $U(k, n) := S(k, n) \setminus T(k, n)$: 
              $S(k, n)$ のうち，最小要素が 1 であるもの全体
* $V(k, n)$: $S(k, n)$ のうち，1 の多重度が $M$ であるもの全体
* $s(k, n) := |S(k, n)|$,
  $t(k, n) := |T(k, n)|$,
  $u(k, n) := |U(k, n)|$,
  $v(k, n) := |V(k, n)|$.

以下が成り立つ．

* $ s(k, n) = t(k, n) + u(k, n) $
    * 自明
* $ t(k, n) = 
    \begin{cases}
    0 & \text{ if } 2k > n \\\\
    s(k, n-k) & \text{ if } 2k \leq n \\\\
    \end{cases} $
    * 各分割から1ずつ取り除く
* $ u(k, n) = 
    \begin{cases}
    0 & \text{ if } n < k \text{ or } k = 1 < n \\\\
    1 & \text{ if } k = n = 1 \\\\
    s(k - 1, n - 1) - v(k - 1, n - 1) & \text{ otherwise } \\\\
    \end{cases} $
    * 要素 1 を一つ取り除く
* $ v(k, n) = 
    \begin{cases}
    1 & \text{ if } k = M = n \\\\
    0 & \text{ else if } n \leq k \text{ or } k \leq M \\\\
    s(k - M, n - k) & \text{ otherwise } \\\\
    \end{cases} $
    * 各分割から1ずつ取り除く

これで DP ができる．

そのままメモ化して計算したら TLE してしまった．
配るDPに書き直してやっと通った．
