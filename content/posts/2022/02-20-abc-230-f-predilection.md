---
author: "yamate11"
title: "Predilection - Atcoder Beginner Contest 230 F"
date: "2022-02-20T18:49:32+09:00"
# date_init: "2022-02-20"
tags: []
# categories: ["topic"]
categories: ["solution"]
summary: "解説ACです．"
---

AtCoder Beginner Contest 230 - ABC 230 F - Predilection の解法です．
解説ACです．

## 問題概要

長さ$N$ の数列 $A$ が与えられる．次の操作を好きな回数行う．

* 数列の長さが2以上のとき，隣接する2つの値を，それらの和で置き換える．

0回以上の操作の結果得られる数列の種類数を mod 998244353 で求めよ．

制約: $N \leq 2 \times 10^5$，$-10^9 \leq A_i \leq 10^9$

[問題へのリンク](https://atcoder.jp/contests/abc230/tasks/abc230_f)

## 解法

0-indexed で書く．

$A_0, \ldots, A_i$ から得られる数列の集合を $S_i$ とする．
$S_{i}$ の要素は，$S_{i - 1}$ の要素 $p_0, \ldots, p_m$ から，
いずれかの手段で得られる．

* (A) 末尾に $A_{i}$ を追加して，$p_0, \ldots, p_m, A_{i}$ とする．
* (B) 末尾の数に $A_{i}$ を加えて，$p_0, \ldots, p_{m-1}, p_m + A_{i}$ とする．


このように作成したものが重複する場合を調べる．
(A)どうし，(B)どうしは重複しない．
(A) 型の $p_0, \ldots, p_m, A_{i}$ と
(B) 型の $q_0, \ldots, q_{n-1}, q_n + A_{i}$ が一致する条件は，
$m = n - 1$, $A_{i} = q_n + A_{i}$，$p_j = q_j$ ($j = 0, \ldots, n - 1$)
である．
逆に，$n > 0$ かつ $q_n = 0$ であれば，
$Q_1 = q_0, \ldots, q_{n-1}, 0$ に対して (B) を適用した数列と，
$Q_2 = q_0, \ldots, q_{n-1}$ に対して (A) を適用した数列が一致する．
また，$Q_1$ が $S_{i - 1}$ の要素であれば，$Q_2$ も $S_{i - 1}$ の要素である．

したがって，

* $S_i$ の要素数を $dp[i]$ 
* $S_i$ の要素のうち，長さが2以上で末尾が0であるものの数を $f(i)$

とすれば，

* $dp[0] = 1$
* $dp[i] = 2 \times dp[i - 1] - f(i - 1)$

となる．$f(i)$ については，$A_k + A_{k + 1} + \cdots + A_i = 0$，
$0 < k \leq i$ となる $k$ が存在しなければ，$f(i) = 0$ である．
存在する場合には，そのような $k$ のうち最大のものを $k_0(i)$ として，
$f(i) = dp[k_0(i) - 1]$ である．

$k_0(i)$ は，累積和を用いて $O(N\log N)$ で計算できる．
全体の計算量は $O(N\log N)$ となる．

## 実装

[ACコード](https://atcoder.jp/contests/abc230/submissions/29500924)
