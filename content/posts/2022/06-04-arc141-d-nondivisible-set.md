---
author: "yamate11"
title: "Non-divisible Set - Atcoder Regular Contest 141 D"
date: "2022-06-04T18:12:34+09:00"
# date_init: "2022-06-04"
tags: []
# categories: ["topic"]
categories: ["solution"]
summary: "解説ACです"
---

AtCoder Regular Contest 141 - ARC 141 D - Non-divisible Set の解法です．解説ACです．

## 問題概要

[問題へのリンク](https://atcoder.jp/contests/arc141/tasks/arc141_d)

$1 \leq M \leq N \leq 2M$ であるような整数$N, M$ と，
整数の集合 $S = \\{ A_1, \ldots, A_N \\}$ が与えられる．
ここで，$1 \leq A_1 < \cdots < A_N \leq 2M$ である．
各 $i = 1, 2, \ldots, N$ に対して，$A_i$を含む要素数$M$の$S$の部分集合$T$で，
任意の$a, b \in T$ ($a \neq b$) に対して $b$ が $a$ の倍数でないものが存在するかどうか，判定せよ．

制約: $M \leq 3\times 10^5$

## 解法

[公式解説](https://atcoder.jp/contests/arc141/editorial/4015) そのままです．

$S$ の要素を，$M$ 個のグループ $G_1, \ldots, G_M$ に分ける:
$x \in S$ に対して $x = 2^k y, \quad y = 2j - 1$ と書いたときに，$x$ は $G_j$ に属することとする．
$1 \leq j \leq M$ となることに注意．

題意を満たす部分集合としては，各グループから要素を1つずつ選んでこなければならない．
同じグループに属する2つの数は倍数の関係にあり，グループは全部で$M$個だからである．
さらに，$j < i$ のときに，
$2^k(2j - 1) \in G_j$ と $2^l(2i - 1) \in G_i$ が同時にに部分集合に属することができる条件は，
$2i - 1$ が $2j - 1$ の倍数でないか，$k > l$ となることである．

そこで，各グループ$G_j$で，使える最小の値 $L[j]$ と最大の値 $U[j]$ を，次のように定義する．

$$
L[j] =
\begin{cases}
\min G_j & 3(2j - 1) \geq 2M \text{の時} \\\\
\min \\{ 2^k(2j - 1) \in G_j \mid k > k_0 \\} & \text{ow} \\\\
\end{cases}
$$

$$
U[j] =
\begin{cases}
\max G_j & j = 1 \text{の時} \\\\
\max \\{ 2^k(2j - 1) \in G_j \mid k < k_1 \\} & \text{ow} \\\\
\end{cases}
$$

ここに，$k_0 := \max \\{ L[i] \mid j < i < M, \quad 2i - 1 は 2j - 1 の倍数 \\}$，
$k_1 := \min \\{ U[i] \mid 1 \leq i < j, \quad 2i - 1 は 2j - 1 の約数 \\}$．

$2^k(2j - 1) \in G_j$ を含む部分集合が存在する条件は，$L[j] \leq k \leq U[j]$ となることである．

## 実装

[ACコード](https://atcoder.jp/contests/arc141/submissions/32194628)



