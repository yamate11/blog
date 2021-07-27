---
author: "yamate11"
title: "行列木定理"
date: "2021-04-18"
tags: []
categories: ["topic"]
draft: false
---
行列木定理についての記事です．
これを使う問題が，[第二回日本最強プログラマー学生選手権 の G - Spanning Tree](https://atcoder.jp/contests/jsc2021/tasks/jsc2021_g) として出題されました．

## 定理

自己ループのない無向グラフ $G$ がある．頂点を $1, \ldots, N$ とする．
対称 $N\times N$ 行列 $A = (a_{ij})$ を，次で定める:

* $a_{ii} = $ 頂点$i$の出次数
* $a_{ij} = - ( i \text{と} j \text{を結ぶ辺の数} )$

このとき，A のすべての余因子は等しく，G の全域木の数と一致する．

## 例

{{< figure src="fig1.png" width=100em >}}


上のグラフでは，

$$ A =
\begin{bmatrix}
3 & -1 & 0 & -2 \\\\
-1 & 3 & -1 & -1 \\\\
0 & -1 & 2 & -1 \\\\
-2 & -1 & -1 & 4 
\end{bmatrix}
$$

$(4,4)-$余因子行列は

$$ M_{4,4} = 
\begin{bmatrix}
3 & -1 & 0  \\\\
-1 & 3 & -1  \\\\
0 & -1 & 2  
\end{bmatrix}
$$


この行列式の値 13 が，グラフの全域木の数である．
