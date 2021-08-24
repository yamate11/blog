---
author: "yamate11"
title: "Snack - Atcoder Regular Contest 125 E"
date: "2021-08-24T17:57:58+09:00"
# date_init: "2021-08-24"
tags: ["最小カット", "最大流"]
# categories: ["topic"]
categories: ["solution"]
description: "Atcoder Regular Contest 125 E Snack の解法です．公式解説そのままです．"
---

## 問題へのリンク

https://atcoder.jp/contests/arc125/tasks/arc125_e

## 経緯

ARC125 には参加できなかったので，バーチャルコンテストで解きました．
Cまでしか解けなかったので，バーチャルコンテスト終了後に考えましたが，
全然解けませんでした．フローは考えたのですが，間に合うはずがない
(それは正しい) と思って，そこから先には進めませんでした．

## 問題概要

正の整数列 $(A_i \mid i \in [1, N]), 
(B_j \mid j \in [1, M]), (C_j \mid j \in [1, M]) $
が与えられる．
$(D_{ij} \mid i \in [1, N], j \in [1, M])$ を次を満たすように取るとき，
$\sum \\{ D_{ij} \mid i \in [1, N], j \in [1, M] \\}$ の最大値を求めよ．
  * $\sum \\{ D_{ij} \mid j \in [1, M] \\} \leq A_i$
  * $D_{ij} \leq B_j$
  * $\sum \\{ D_{ij} \mid i \in [1, N] \\} \leq C_j$

制約: $N, M \leq 2\times 10^5$, 
$A_i, C_j \leq 10^{12}$, $B_j \leq 10^7$

## 解法

次のフローの最大流問題として定式化できる．
  * Source $\to L_i$  容量 $A_i$
  * $L_i \to R_j$  容量 $B_j$
  * $R_j \to$ Sink  容量 $C_j$

容量が大きくノードが多いので，Dinic などでは解けない．

最小カット $(A, B)$ を求める．Source $\in A$ とする．
$L_i$ たちのうち，$A$ に属するものの集合を $X$, $|X| = n$ とする．
$R_j$ については，

*  $R_j \in A$ とすると，カット容量への寄与は $C_j$
*  $R_j \in B$ とすると，カット容量への寄与は，$n B_j$

であるから，$(A, B)$ の最小性より，

* $C_j < n B_j$ なら $R_j \in A$
* $C_j > n B_j$ なら $R_j \in B$

となる必要がある．カット容量は全体として，

$$  \sum \\{ A_i \mid i \in [1, N] - X \\} 
    + \sum \\{ \min(C_j, n B_j) \mid j \in [1, M] \\}
$$
  
であるから，$A_i$ の大きい方から $n$ 個が $X$ に属するとして良い．
$n = 1, \ldots, N$ について計算して最小値を取れば良い．

