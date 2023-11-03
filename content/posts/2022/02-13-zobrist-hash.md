---
author: "yamate11"
title: "Zobrist Hashing"
date: "2022-02-13T11:32:14+09:00"
# date_init: "2022-02-13"
tags: ["ハッシュ"]
categories: ["topic"]
# categories: ["solution"]
summary: "ABC238 G Cubic? を解くのに使うことができる Zobrist Hashing に関する記事です．"
---

ABC238 G Cubic? を解くのに使うことができる Zobrist Hashing に関する記事です．

## ネタ元

[Wikipedia](https://en.wikipedia.org/wiki/Zobrist_hashing)

## Zobrist Hashing とは

以下では，ビットごとの XOR を $\oplus$ と書く．

固定された有限集合 $S$ の部分集合 に対するハッシュ．
$R$ を2冪の大きな数 (たとえば $2^{63}$) として，
あらかじめ各 $x \in S$ に対して区間$[0, R)$ から一様乱数により $r(x)$ を選んでおく．
$X \subseteq S$のハッシュ値 を，$h(X) := \bigoplus \\{ r(x) \mid x \in X\\}$
で定める．

## 性質

* $h(Y) = h(X) \oplus h(X \setminus Y) \oplus h(Y \setminus X)$．
  * したがって，$h(X)$ がわかっていれば，
    $h(X \cup \\{x\\})$ や，$h(X \setminus \\{x\\})$ を $O(1)$ で計算できる．
* 衝突確率．$X, Y \subseteq S$, $X \neq Y$, $\\{d_1, d_2, \ldots, d_k\\} := (X \setminus Y) \cup (Y \setminus X)$ とする．衝突する条件は，$r(d_1) = \bigoplus \\{ r(d_j) \mid j = 2, \ldots, k \\}$ であるから，この確率は $1/R$ である．

## 使用例

[ABC238 G - Cubic?](../02-13-abc238-g-cubic/)
