---
author: "yamate11"
title: "「牛ゲー」"
date: "2021-08-30T11:09:47+09:00"
# date_init: "2021-08-30"
tags: ["牛ゲー", "最短路"]
categories: ["topic"]
# categories: ["solution"]
summary: "「牛ゲー」なる手法のまとめです" 
---

「牛ゲー」なる手法のまとめです．
[ABC216 G - 01Sequence](../08-30-abc216g-01sequence) で出てきました．

## 適用できる問題

$(c_{ij} \mid i, j \in [1, N])$ と，$S, T \in [1, N]$ が与えられる．
変数 $x_1, \ldots, x_N$ に対する制約

* $x_i - x_j \leq c_{ij}$

のもとで，$ x_T - x_S $ の最大値を求めよ．

## 解法

集合 $\\{1, .., N\\}$ 上に，$i$ から $j$ に距離 $c_{ij}$ の辺がある
グラフを考える．
以下のようになる 
([参照](https://qiita.com/tanabe13f/items/6c723c29a121de760790)):

* 制約を満たす解がある $\Leftrightarrow$ グラフに負閉路がない
* グラフに負閉路がない場合:
  * $ x_T - x_S $ の最大値がない (いくらでも大きくできる)
    $\Leftrightarrow$ $T$ は $S$ から到達できない
* グラフに負閉路がなく，$T$ が $S$ から到達できる場合
  * $ x_T - x_S $ の最大値は，グラフ上の $S$ から $T$ への最短路長に一致する．

最後の行が重要．特に，全部の $c_{ij}$ が非負なら，
ダイクストラで解ける．



